/*
 * This file is part of the Colobot: Gold Edition source code
 * Copyright (C) 2001-2021, Daniel Roux, EPSITEC SA & TerranovaTeam
 * http://epsitec.ch; http://colobot.info; http://github.com/colobot
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see http://gnu.org/licenses
 */

#include "object/object_factory.h"

#include "graphics/engine/engine.h"
#include "graphics/engine/engine_types.h"
#include "graphics/engine/lightning.h"
#include "graphics/engine/oldmodelmanager.h"
#include "graphics/engine/terrain.h"

#include "graphics/model/model_manager.h"

#include "level/robotmain.h"

#include "math/geometry.h"

#include "object/object_create_params.h"
#include "object/object_manager.h"
#include "object/object_part_filter.h"
#include "object/old_object.h"

#include "object/auto/autojostle.h"

#include "object/auto/autoegg.h"
#include "object/auto/autoflag.h"
#include "object/auto/automush.h"
#include "object/auto/autoroot.h"

#include "object/auto/autobase.h"
#include "object/auto/autoconvert.h"
#include "object/auto/autoderrick.h"
#include "object/auto/autodestroyer.h"
#include "object/auto/autofactory.h"
#include "object/auto/autohouston.h"
#include "object/auto/autoinfo.h"
#include "object/auto/autolabo.h"
#include "object/auto/autolamp.h"
#include "object/auto/autonest.h"
#include "object/auto/autonuclearplant.h"
#include "object/auto/autoportico.h"
#include "object/auto/autopowercaptor.h"
#include "object/auto/autopowerplant.h"
#include "object/auto/autopowerstation.h"
#include "object/auto/autoradar.h"
#include "object/auto/autorepair.h"
#include "object/auto/autoresearch.h"
#include "object/auto/autotower.h"
#include "object/auto/autovault.h"
#include "object/auto/autoworm.h"
#include "object/auto/autoquarz.h"

#include "object/auto/autoboat.h"
#include "object/auto/autofan.h"
#include "object/auto/autotrunk.h"

#include "object/details/details_provider.h"
#include "object/details/automated_details.h"
#include "object/details/controllable_details.h"
#include "object/details/jostleable_details.h"
#include "object/details/modeled_details.h"
#include "object/details/movable_details.h"
#include "object/details/power_container_details.h"

#include "object/helpers/cargo_helpers.h"

#include "object/motion/motion.h"
#include "object/motion/motionant.h"
#include "object/motion/motionbee.h"
#include "object/motion/motionhuman.h"
#include "object/motion/motionlegged.h"
#include "object/motion/motionqueen.h"
#include "object/motion/motionspider.h"
#include "object/motion/motiontoto.h"
#include "object/motion/motiontracked.h"
#include "object/motion/motionwheeled.h"
#include "object/motion/motionwinged.h"
#include "object/motion/motionworm.h"

#include "object/subclass/static_object.h"

#include "physics/physics.h"

using COldObjectUPtr = std::unique_ptr<COldObject>;

CObjectFactory::CObjectFactory(Gfx::CEngine* engine,
                               Gfx::CTerrain* terrain,
                               Gfx::COldModelManager* oldModelManager,
                               Gfx::CModelManager* modelManager,
                               Gfx::CParticle* particle)
   : m_engine(engine)
   , m_terrain(terrain)
   , m_oldModelManager(oldModelManager)
   , m_modelManager(modelManager)
   , m_particle(particle)
{}

CObjectUPtr CObjectFactory::CreateObject(const ObjectCreateParams& params)
{
    if ( params.type == OBJECT_NULL ) return nullptr;

    if (CStaticObject::IsStaticObject(params.type))
    {
        return CStaticObject::Create(params.id,
                                     params.type,
                                     params.pos,
                                     params.angle,
                                     params.height,
                                     m_engine,
                                     m_modelManager,
                                     m_engine->GetTerrain());
    }

    glm::vec3 pos = params.pos;
    float angle = params.angle;
    float height = params.height;
    float power = params.power;

    auto obj = std::make_unique<COldObject>(params.id);
    obj->SetType(params.type);

    auto controllableDetails = GetObjectControllableDetails(obj.get());

    obj->SetToy(params.toy);
    obj->SetTeam(params.team);
    obj->SetOption(params.option);
    obj->SetTrainer(controllableDetails.trainable ? (params.trainer || obj->GetPlusTrainer()) : false);

    auto modeledDetails = GetObjectModeledDetails(obj.get());

    std::vector<CObjectModeledNode> model;
    if ( obj->Implements(ObjectInterfaceType::Modeled) )
    {
        if ( CRobotMain::GetInstancePointer()->GetGamerOnlyHead() )
            model = modeledDetails.headModel;
        else
            model = modeledDetails.model;
    }
    if ( model.size() == 0)
    {
        model.push_back({0, -1, Gfx::ENG_OBJTYPE_VEHICLE});
    }
    
    for ( auto it : model )
    {
        if ( !MatchObjectPartFilter(obj.get(), it.filter) ) continue;
        if ( it.glasses && it.glasses != CRobotMain::GetInstancePointer()->GetGamerGlasses() ) continue;

        int rank = m_engine->CreateObject();
        m_engine->SetObjectType(rank, it.gfxType);
        obj->SetObjectRank(it.chunkId, rank);

        if ( it.modFile.size() )
        {
            if ( it.copyModel ) 
                assert(m_oldModelManager->AddModelCopy(it.modFile, it.mirrored, rank, obj->GetTeam()));
            else
                assert(m_oldModelManager->AddModelReference(it.modFile, it.mirrored, rank, obj->GetTeam()));
        }

        if ( it.parentId != -1)
        {
            obj->SetObjectParent(it.chunkId, it.parentId);
            obj->SetPartPosition(it.chunkId, it.position);
            obj->SetPartRotation(it.chunkId, it.rotation);
            obj->SetPartScale(it.chunkId, it.zoom);
        }
    }

    obj->SetPosition(pos);
    obj->SetRotationY(obj->GetRotationY() + angle);
    
    if ( obj->Implements(ObjectInterfaceType::Modeled) )
    {
        obj->SetScaleFactor(modeledDetails.zoom);

        auto shadowCircle = modeledDetails.shadowCircle;
        if ( shadowCircle.intensity )
        {
            float fShadow = Math::Norm(1.0f-height/10.0f);
            Gfx::EngineShadowType shadowType = shadowCircle.wormLike ? Gfx::EngineShadowType::WORM : Gfx::EngineShadowType::NORMAL;
            float intensity = shadowCircle.factored ? shadowCircle.intensity * fShadow : shadowCircle.intensity;
            obj->CreateShadowCircle(shadowCircle.radius, intensity, shadowType);
        }
    
        auto shadowLight = modeledDetails.shadowLight;
        if ( shadowLight.height )
        {
            obj->CreateShadowLight(shadowLight.height, shadowLight.color);
        }

        obj->SetCameraCollisionSphere(modeledDetails.cameraCollisionSphere);
    
        for ( auto it : modeledDetails.crashSpheres )
        {
            if ( !MatchObjectPartFilter(obj.get(), it.filter) ) continue;
    
            obj->AddCrashSphere(it.sphere);
        }
    
        if ( modeledDetails.isForceLoadTextures )
            m_engine->LoadAllTextures();
    
        if ( !modeledDetails.isFixedPosition )
        {
            pos = obj->GetPosition();
            pos.y += height;
            obj->SetPosition(pos);
            
            if ( modeledDetails.isSetFloorHeight )
                obj->SetFloorHeight(0.0f);
        
            if ( modeledDetails.isFloorAdjust )
                obj->FloorAdjust();
        }

        for ( auto it : modeledDetails.buildingLevels )
            m_terrain->AddBuildingLevel(pos, it.min, it.max, it.height, it.factor);

        if ( !modeledDetails.isFixedPosition && model.size() > 0 )
        {
            obj->SetPosition(obj->GetPosition() + model[0].position);
            obj->SetRotation(obj->GetRotation() + model[0].rotation);
        }
    }

    AddObjectAuto(obj.get());

    if ( obj->Implements(ObjectInterfaceType::Jostleable) )
    {
        obj->SetJostlingSphere(GetObjectJostleableDetails(obj.get()).sphere);
    }

    if ( obj->Implements(ObjectInterfaceType::PowerContainer) )
    {
        float max = GetObjectPowerContainerDetails(obj.get()).clamp;
        power = glm::clamp(power, 0.0f, max);
        obj->SetEnergyLevel(power);
        obj->UpdateMapping();
    }

    if ( obj->Implements(ObjectInterfaceType::Slotted) )
    {
        if (power > 0.0f && HasPowerCellSlot(obj.get()))
        {
            ObjectCreateParams p;
            if (power <= 1.0f)
            {
                p.type = OBJECT_POWER;
                p.power = power;
            }
            else
            {
                p.type = OBJECT_ATOMIC;
                p.power = power/100.0;
            }

            CObject* powerCell = CObjectManager::GetInstancePointer()->CreateObject(p);

            SetObjectInPowerCellSlot(obj.get(), powerCell);
        }
    }

    if ( obj->Implements(ObjectInterfaceType::Movable) )
    {
        auto motionClass = GetObjectMovableDetails(obj.get()).motionClass;

        std::unique_ptr<CMotion> motion;
        if ( motionClass == MOTION_CLASS_HUMAN )
            motion = std::make_unique<CMotionHuman>(obj.get());
        else if ( motionClass == MOTION_CLASS_ANT )
            motion = std::make_unique<CMotionAnt>(obj.get());
        else if ( motionClass == MOTION_CLASS_BEE )
            motion = std::make_unique<CMotionBee>(obj.get());
        else if ( motionClass == MOTION_CLASS_SPIDER )
            motion = std::make_unique<CMotionSpider>(obj.get());
        else if ( motionClass == MOTION_CLASS_WORM )
            motion = std::make_unique<CMotionWorm>(obj.get());
        else if ( motionClass == MOTION_CLASS_MOTHER )
            motion = std::make_unique<CMotionQueen>(obj.get());
        else if ( motionClass == MOTION_CLASS_WHEELED )
            motion = std::make_unique<CMotionWheeled>(obj.get());
        else if ( motionClass == MOTION_CLASS_TRACKED )
            motion = std::make_unique<CMotionTracked>(obj.get());
        else if ( motionClass == MOTION_CLASS_WINGED )
            motion = std::make_unique<CMotionWinged>(obj.get());
        else if ( motionClass == MOTION_CLASS_LEGGED )
            motion = std::make_unique<CMotionLegged>(obj.get());
        else if ( motionClass == MOTION_CLASS_TOTO )
            motion = std::make_unique<CMotionToto>(obj.get());
        else
            motion = std::make_unique<CMotion>(obj.get());

        if ( motionClass == MOTION_CLASS_TOTO )
        {
            motion->Create();
            obj->SetMovable(std::move(motion), nullptr);
        }
        else
        {
            auto physics = std::make_unique<CPhysics>(obj.get());
            motion->SetPhysics(physics.get());
            physics->SetMotion(motion.get());
            motion->Create();
            obj->SetMovable(std::move(motion), std::move(physics));
        }
    }

    return std::move(obj);
}

// Creates all sub-objects for managing the object.

void CObjectFactory::AddObjectAuto(COldObject* obj)
{
    std::unique_ptr<CAuto> objAuto;

    auto autoClass = GetObjectAutomatedDetails(obj).autoClass;

    if ( autoClass == AUTO_CLASS_EGG          )
        objAuto = std::make_unique<CAutoEgg>(obj);
    if ( autoClass == AUTO_CLASS_FLAG         )
        objAuto = std::make_unique<CAutoFlag>(obj);
    if ( autoClass == AUTO_CLASS_MUSHROOM     )
        objAuto = std::make_unique<CAutoMush>(obj);
    if ( autoClass == AUTO_CLASS_ROOT         )
        objAuto = std::make_unique<CAutoRoot>(obj);

    if ( autoClass == AUTO_CLASS_BASE         )
        objAuto = std::make_unique<CAutoBase>(obj);
    if ( autoClass == AUTO_CLASS_CONVERT      )
        objAuto = std::make_unique<CAutoConvert>(obj);
    if ( autoClass == AUTO_CLASS_DERRICK      )
        objAuto = std::make_unique<CAutoDerrick>(obj);
    if ( autoClass == AUTO_CLASS_DESTROYER    )
        objAuto = std::make_unique<CAutoDestroyer>(obj);
    if ( autoClass == AUTO_CLASS_FACTORY      )
        objAuto = std::make_unique<CAutoFactory>(obj);
    if ( autoClass == AUTO_CLASS_HUSTON       )
        objAuto = std::make_unique<CAutoHouston>(obj);
    if ( autoClass == AUTO_CLASS_LABO         )
        objAuto = std::make_unique<CAutoLabo>(obj);
    if ( autoClass == AUTO_CLASS_NEST         )
        objAuto = std::make_unique<CAutoNest>(obj);
    if ( autoClass == AUTO_CLASS_NUCLEARPLANT )
        objAuto = std::make_unique<CAutoNuclearPlant>(obj);
    if ( autoClass == AUTO_CLASS_PORTICO      )
        objAuto = std::make_unique<CAutoPortico>(obj);
    if ( autoClass == AUTO_CLASS_POWERCAPTOR  )
        objAuto = std::make_unique<CAutoPowerCaptor>(obj);
    if ( autoClass == AUTO_CLASS_POWERPLANT   )
        objAuto = std::make_unique<CAutoPowerPlant>(obj);
    if ( autoClass == AUTO_CLASS_POWERSTATION )
        objAuto = std::make_unique<CAutoPowerStation>(obj);
    if ( autoClass == AUTO_CLASS_RADAR        )
        objAuto = std::make_unique<CAutoRadar>(obj);
    if ( autoClass == AUTO_CLASS_REPAIR       )
        objAuto = std::make_unique<CAutoRepair>(obj);
    if ( autoClass == AUTO_CLASS_RESEARCH     )
        objAuto = std::make_unique<CAutoResearch>(obj);
    if ( autoClass == AUTO_CLASS_TOWER        )
        objAuto = std::make_unique<CAutoTower>(obj);
    if ( autoClass == AUTO_CLASS_VAULT        )
        objAuto = std::make_unique<CAutoVault>(obj);

    if ( autoClass == AUTO_CLASS_QUARZ        )
        objAuto = std::make_unique<CAutoQuarz>(obj);

    if ( autoClass == AUTO_CLASS_TEEN_TRUNK   )
        objAuto = std::make_unique<CAutoTrunk>(obj);
    if ( autoClass == AUTO_CLASS_TEEN_BOAT    )
        objAuto = std::make_unique<CAutoBoat>(obj);
    if ( autoClass == AUTO_CLASS_TEEN_FAN     )
        objAuto = std::make_unique<CAutoFan>(obj);
        
    if ( autoClass == AUTO_CLASS_TEEN_LAMP    )
        objAuto = std::make_unique<CAutoLamp>(obj);

    if ( autoClass == AUTO_CLASS_INFO    )
        objAuto = std::make_unique<CAutoInfo>(obj);

    if ( autoClass == AUTO_CLASS_WORM_INFECT  )
        objAuto = std::make_unique<CAutoWorm>(obj);

    if (objAuto != nullptr)
    {
        objAuto->Init();
        obj->SetAuto(std::move(objAuto));
    }
}
