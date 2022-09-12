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

#include "common/make_unique.h"

#include "graphics/engine/engine.h"
#include "graphics/engine/lightning.h"
#include "graphics/engine/oldmodelmanager.h"
#include "graphics/engine/terrain.h"

#include "graphics/model/model_manager.h"

#include "level/robotmain.h"

#include "math/geometry.h"

#include "object/object_create_params.h"
#include "object/object_details.h"
#include "object/old_object.h"

#include "object/auto/autoegg.h"
#include "object/auto/autoflag.h"
#include "object/auto/autojostle.h"
#include "object/auto/autokid.h"
#include "object/auto/automush.h"
#include "object/auto/autoroot.h"

#include "object/subclass/base_alien.h"
#include "object/subclass/base_building.h"
#include "object/subclass/base_robot.h"
#include "object/subclass/exchange_post.h"
#include "object/subclass/shielder.h"
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

    BaseClass bc = GetObjectDetails().GetCreationBaseClass(params.type);
    switch (bc)
    {
        case BASE_CLASS_NONE:
            return nullptr;

        case BASE_CLASS_SIMPLE:
            return CreateSimpleObject(params);

        case BASE_CLASS_BUILDING:
            return CBaseBuilding::Create(params, m_oldModelManager, m_engine);

        case BASE_CLASS_INFO:
            return CExchangePost::Create(params, m_oldModelManager, m_engine);

        case BASE_CLASS_ALIEN:
            return CBaseAlien::Create(params, m_oldModelManager, m_engine);

        case BASE_CLASS_ROBOT:
            return CBaseRobot::Create(params, m_oldModelManager, m_engine);

        case BASE_CLASS_SHIELDER:
            return CShielder::Create(params, m_oldModelManager, m_engine);

        default:
            break;
    }

    return nullptr;
}

// Creates a small object set on the ground.

CObjectUPtr CObjectFactory::CreateSimpleObject(const ObjectCreateParams& params)
{
    Math::Vector pos = params.pos;
    float angle = params.angle;
    float height = params.height;
    ObjectType type = params.type;

    auto obj = MakeUnique<COldObject>(params.id);

    obj->SetType(type);
    obj->SetTeam(params.team);
    obj->SetEnergyLevel(params.power);
    obj->SetOption(params.option);

    float fShadow = Math::Norm(1.0f-height/10.0f);

    auto model = GetObjectDetails().GetCreationModel(type);
    for ( auto it : model )
    {
        int rank = m_engine->CreateObject();
        m_engine->SetObjectType(rank, it.gfxType);
        obj->SetObjectRank(it.chunkId, rank);

        if ( it.copyModel ) 
            m_oldModelManager->AddModelCopy(it.modFile, false, rank, obj->GetTeam());
        else
            m_oldModelManager->AddModelReference(it.modFile, false, rank, obj->GetTeam());

        if ( it.parentId != -1)
        {
            obj->SetObjectParent(it.chunkId, it.parentId);
            obj->SetPartPosition(it.chunkId, it.position);
            if (it.rotation.x != 0.0f) obj->SetPartRotationX(it.chunkId, it.rotation.x);
            if (it.rotation.y != 0.0f) obj->SetPartRotationY(it.chunkId, it.rotation.y);
            if (it.rotation.z != 0.0f) obj->SetPartRotationZ(it.chunkId, it.rotation.z);
        }
    }

    obj->SetPosition(pos);
    obj->SetRotationY(angle);

    if ( model.size() > 0 )
    {
        height += model[0].position.y;
        Math::Vector rotation = model[0].rotation;
        if (rotation.x != 0.0f) obj->SetRotationX(obj->GetRotationX() + rotation.x);
        if (rotation.y != 0.0f) obj->SetRotationZ(obj->GetRotationX() + rotation.y);
        if (rotation.z != 0.0f) obj->SetRotationZ(obj->GetRotationX() + rotation.z);
    }

    float scale = GetObjectDetails().GetCreationScale(type);
    if ( scale != 1.0f )
        obj->SetScale(scale);

    for ( auto it : GetObjectDetails().GetCreationCrashSpheres(type) )
        obj->AddCrashSphere(it);

    for ( auto it : GetObjectDetails().GetCreationCameraCollisionSpheres(type) )
        obj->SetCameraCollisionSphere(it);

    for ( auto it : GetObjectDetails().GetCreationJostlingSpheres(type) )
        obj->SetJostlingSphere(it);

    for ( auto it : GetObjectDetails().GetCreationBuildingLevels(type) )
        m_terrain->AddBuildingLevel(pos, it.min, it.max, it.height, it.factor);

    auto shadowCircle = GetObjectDetails().GetCreationShadowCircle(type);
    if ( shadowCircle.intensity > 0.0f )
    {
        float intensity = shadowCircle.factored ? shadowCircle.intensity*fShadow : shadowCircle.intensity;
        obj->CreateShadowCircle(shadowCircle.radius, intensity, shadowCircle.type);
    }

    if ( GetObjectDetails().IsCreationForceLoadTextures(type) )
        m_engine->LoadAllTextures();

    if ( !GetObjectDetails().IsCreationFixedPosition(type) )
    {
        pos = obj->GetPosition();
        obj->SetPosition(pos);  // to display the shadows immediately
    
        if ( GetObjectDetails().IsCreationSetFloorHeight(type) )
            obj->SetFloorHeight(0.0f);
    
        if ( GetObjectDetails().IsCreationFloorAdjust(type) )
            obj->FloorAdjust();
    
        pos = obj->GetPosition();
        pos.y += height;
        obj->SetPosition(pos);
    }

    AddObjectAuto(obj.get());
    AddObjectHacks(obj.get());

    return std::move(obj);
}

// Creates all sub-objects for managing the object.

void CObjectFactory::AddObjectAuto(COldObject* obj)
{
    std::unique_ptr<CAuto> objAuto;

    auto type = obj->GetType();

    if ( type == OBJECT_EGG )
    {
        objAuto = MakeUnique<CAutoEgg>(obj);
    }
    if ( type == OBJECT_ROOT5 )
    {
        objAuto = MakeUnique<CAutoRoot>(obj);
    }
    if ( type == OBJECT_MUSHROOM2 )
    {
        objAuto = MakeUnique<CAutoMush>(obj);
    }
    if ( type == OBJECT_FLAGb ||
         type == OBJECT_FLAGr ||
         type == OBJECT_FLAGg ||
         type == OBJECT_FLAGy ||
         type == OBJECT_FLAGv )
    {
        objAuto = MakeUnique<CAutoFlag>(obj);
    }
    if ( type == OBJECT_TEEN36 ||  // trunk?
         type == OBJECT_TEEN37 ||  // boat?
         type == OBJECT_TEEN38 )   // fan?
    {
        objAuto = MakeUnique<CAutoKid>(obj);
    }

    if (objAuto != nullptr)
    {
        objAuto->Init();
        obj->SetAuto(std::move(objAuto));
    }
}

// Hacks for several Teen objects

void CObjectFactory::AddObjectHacks(COldObject* obj)
{
    Math::Vector pos = obj->GetPosition();
    ObjectType type = obj->GetType();

    if ( type == OBJECT_TEEN23 )  // skateboard on wheels
    {
        if ( obj->GetOption() == 1 )  // passage under the prohibited skateboard?
        {
            obj->AddCrashSphere(CrashSphere(Math::Vector(-10.0f, 2.0f, 0.0f), 11.0f, SOUND_BOUMm, 0.45f));
            obj->AddCrashSphere(CrashSphere(Math::Vector( 10.0f, 2.0f, 0.0f), 11.0f, SOUND_BOUMm, 0.45f));
        }
    }

    if ( type == OBJECT_TEEN11 )  // lamp
    {
        {
            Math::Matrix* mat = obj->GetWorldMatrix(0);
            pos = Math::Transform(*mat, Math::Vector(-56.0f, 22.0f, 0.0f));
            m_particle->CreateParticle(pos, Math::Vector(0.0f, 0.0f, 0.0f), Math::Point(20.0f, 20.0f), Gfx::PARTISELY, 1.0f, 0.0f, 0.0f);
        }

        {
            Math::Matrix* mat = obj->GetWorldMatrix(0);
            pos = Math::Transform(*mat, Math::Vector(-65.0f, 40.0f, 0.0f));
            Gfx::Color color;
            color.r = 4.0f;
            color.g = 2.0f;
            color.b = 0.0f;  // yellow-orange
            color.a = 0.0f;
            CRobotMain::GetInstancePointer()->CreateSpot(pos, color); // TODO: Don't use singleton
        }
    }

    if ( type == OBJECT_TEEN26 )  // ceiling lamp
    {
        {
            Math::Matrix* mat = obj->GetWorldMatrix(0);
            pos = Math::Transform(*mat, Math::Vector(0.0f, 50.0f, 0.0f));
            m_particle->CreateParticle(pos, Math::Vector(0.0f, 0.0f, 0.0f), Math::Point(100.0f, 100.0f), Gfx::PARTISELY, 1.0f, 0.0f, 0.0f);
        }

        {
            Math::Matrix* mat = obj->GetWorldMatrix(0);
            pos = Math::Transform(*mat, Math::Vector(0.0f, 50.0f, 0.0f));
            Gfx::Color color;
            color.r = 4.0f;
            color.g = 2.0f;
            color.b = 0.0f;  // yellow-orange
            color.a = 0.0f;
            CRobotMain::GetInstancePointer()->CreateSpot(pos, color); // TODO: Don't use singleton
        }
    }

    if ( type == OBJECT_QUARTZ0 )
    {
        pos.y += 4.0f;
        float radius = 2.0f;
        m_particle->CreateParticle(pos, pos, Math::Point(2.0f, 2.0f), Gfx::PARTIQUARTZ, 0.7f+Math::Rand()*0.7f, radius, 0.0f);
        m_particle->CreateParticle(pos, pos, Math::Point(2.0f, 2.0f), Gfx::PARTIQUARTZ, 0.7f+Math::Rand()*0.7f, radius, 0.0f);
    }
    if ( type == OBJECT_QUARTZ1 )
    {
        pos.y += 6.0f;
        float radius = 4.0f;
        m_particle->CreateParticle(pos, pos, Math::Point(2.0f, 2.0f), Gfx::PARTIQUARTZ, 0.7f+Math::Rand()*0.7f, radius, 0.0f);
        m_particle->CreateParticle(pos, pos, Math::Point(2.0f, 2.0f), Gfx::PARTIQUARTZ, 0.7f+Math::Rand()*0.7f, radius, 0.0f);
    }
    if ( type == OBJECT_QUARTZ2 )
    {
        pos.y += 10.0f;
        float radius = 5.0f;
        m_particle->CreateParticle(pos, pos, Math::Point(2.0f, 2.0f), Gfx::PARTIQUARTZ, 0.7f+Math::Rand()*0.7f, radius, 0.0f);
        m_particle->CreateParticle(pos, pos, Math::Point(2.0f, 2.0f), Gfx::PARTIQUARTZ, 0.7f+Math::Rand()*0.7f, radius, 0.0f);
    }

    if ( type == OBJECT_QUARTZ3 )
    {
        pos.y += 16.0f;
        float radius = 8.0f;
        m_particle->CreateParticle(pos, pos, Math::Point(2.0f, 2.0f), Gfx::PARTIQUARTZ, 0.7f+Math::Rand()*0.7f, radius, 0.0f);
        m_particle->CreateParticle(pos, pos, Math::Point(2.0f, 2.0f), Gfx::PARTIQUARTZ, 0.7f+Math::Rand()*0.7f, radius, 0.0f);
    }

}
