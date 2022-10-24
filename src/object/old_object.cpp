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


#include "object/old_object.h"

#include "app/app.h"

#include "common/global.h"
#include "common/make_unique.h"
#include "common/settings.h"
#include "common/stringutils.h"

#include "graphics/engine/lightman.h"
#include "graphics/engine/lightning.h"
#include "graphics/engine/particle.h"
#include "graphics/engine/pyro_manager.h"
#include "graphics/engine/terrain.h"

#include "level/robotmain.h"
#include "level/scoreboard.h"

#include "level/parser/parserexceptions.h"
#include "level/parser/parserline.h"
#include "level/parser/parserparam.h"

#include "math/geometry.h"

#include "object/object_details.h"
#include "object/object_manager.h"

#include "object/auto/auto.h"
#include "object/auto/autobase.h"
#include "object/auto/autojostle.h"

#include "object/details/controllable_details.h"
#include "object/details/damageable_details.h"
#include "object/details/destroyable_details.h"
#include "object/details/flying_details.h"
#include "object/details/fragile_details.h"
#include "object/details/jet_flying_details.h"
#include "object/details/jostleable_details.h"
#include "object/details/movable_details.h"
#include "object/details/power_container_details.h"
#include "object/details/programmable_details.h"
#include "object/details/shielded_details.h"
#include "object/details/shielded_auto_regen_details.h"
#include "object/details/slotted_details.h"
#include "object/details/ranged_details.h"
#include "object/details/thumpable_details.h"
#include "object/details/trace_drawing_details.h"
#include "object/details/transportable_details.h"

#include "object/motion/motion.h"
#include "object/motion/motionvehicle.h"

#include "object/subclass/exchange_post.h"

#include "physics/physics.h"

#include "script/cbottoken.h"
#include "script/script.h"
#include "script/scriptfunc.h"

#include "ui/object_interface.h"
#include "ui/studio.h"

#include "ui/controls/edit.h"

#include <boost/lexical_cast.hpp>
#include <iomanip>


const float VIRUS_DELAY     = 60.0f;        // duration of virus infection

// Object's constructor.

COldObject::COldObject(int id)
    : CObject(id, OBJECT_NULL),
      CInteractiveObject(m_implementedInterfaces),
      CTransportableObject(m_implementedInterfaces),
      CTaskExecutorObjectImpl(m_implementedInterfaces, this),
      CProgramStorageObjectImpl(m_implementedInterfaces, this),
      CProgrammableObjectImpl(m_implementedInterfaces, this),
      CJostleableObject(m_implementedInterfaces),
      CSlottedObject(m_implementedInterfaces),
      CJetFlyingObject(m_implementedInterfaces),
      CControllableObject(m_implementedInterfaces),
      CPowerContainerObjectImpl(m_implementedInterfaces),
      CRangedObject(m_implementedInterfaces),
      CTraceDrawingObject(m_implementedInterfaces),
      CShieldedAutoRegenObject(m_implementedInterfaces),
      CThumpableObject(m_implementedInterfaces),
      CShielderObject(m_implementedInterfaces)
{
    m_implementedInterfaces[static_cast<int>(ObjectInterfaceType::Old)] = true;

    m_sound       = CApplication::GetInstancePointer()->GetSound();
    m_engine      = Gfx::CEngine::GetInstancePointer();
    m_lightMan    = m_engine->GetLightManager();
    m_particle    = m_engine->GetParticle();
    m_main        = CRobotMain::GetInstancePointer();
    m_terrain     = m_main->GetTerrain();
    m_camera      = m_main->GetCamera();

    m_type = OBJECT_NULL;
    m_option = 0;
    m_name = "";
    m_shadowLight   = -1;
    m_shadowHeight  = 0.0f;
    m_linVibration  = Math::Vector(0.0f, 0.0f, 0.0f);
    m_cirVibration  = Math::Vector(0.0f, 0.0f, 0.0f);
    m_tilt   = Math::Vector(0.0f, 0.0f, 0.0f);

    m_otherSlot = nullptr;
    m_powerSlot = nullptr;
    m_cargoSlot = nullptr;
    m_transporter = nullptr;
    m_transporterLink = 0;
    m_shield   = 1.0f;
    m_range    = 30.0f;
    m_lastEnergy = 999.9f;
    m_bSelect = false;
    m_bSelectable = true;
    m_bCheckToken = true;
    m_underground = false;
    m_bTrainer = false;
    m_bToy = false;
    m_bManual = false;
    m_aTime = 0.0f;
    m_shotTime = 0.0f;
    m_bVirusMode = false;
    m_virusTime = 0.0f;
    m_lastVirusParticle = 0.0f;
    m_damaging = false;
    m_damageTime = 0.0f;
    m_dying = DeathType::Alive;
    m_bFlat  = false;
    m_gunGoalV = 0.0f;
    m_gunGoalH = 0.0f;
    m_shieldRadius = 0.0f;
    m_magnifyDamage = 1.0f;

    m_cameraType = Gfx::CAM_TYPE_BACK;
    m_bCameraLock = false;

    for (int i=0 ; i<OBJECTMAXPART ; i++ )
    {
        m_objectPart[i].bUsed = false;
    }
    m_totalPart = 0;

    m_time = 0.0f;
    m_burnTime = 0.0f;

    m_buttonAxe    = EVENT_NULL;

    m_reactorRange       = 1.0f;

    m_traceDown = false;
    m_traceColor = TraceColor::Black;
    m_traceWidth = 0.5f;
    
    m_fixed = false;

    DeleteAllCrashSpheres();
}

// Object's destructor.

COldObject::~COldObject()
{
    m_main->HideDropZone(this);
}


// Removes an object.
// If bAll = true, it does not help,
// because all objects in the scene are quickly destroyed!

void COldObject::DeleteObject(bool bAll)
{
    CScriptFunctions::DestroyObjectVar(m_botVar, false);

    if ( m_camera->GetControllingObject() == this )
    {
        m_camera->SetControllingObject(nullptr);
    }
    m_main->RemoveFromSelectionHistory(this);

    if ( !bAll )
    {
        m_engine->GetPyroManager()->CutObjectLink(this);
        m_particle->CutObjectLink(this);

        if ( m_bSelect )
        {
            SetSelect(false);
        }

        if ( GetObjectDestroyableDetails(this).removeBuildingLevel ) // building?
        {
            m_terrain->DeleteBuildingLevel(GetPosition());  // flattens the field
        }
    }

    m_type = OBJECT_NULL;  // invalid object until complete destruction

    if ( m_shadowLight != -1 )
    {
        m_lightMan->DeleteLight(m_shadowLight);
        m_shadowLight = -1;
    }

    if ( m_physics != nullptr )
    {
        m_physics->DeleteObject(bAll);
    }

    if ( m_objectInterface != nullptr )
    {
        m_objectInterface->DeleteObject(bAll);
    }

    if ( m_motion != nullptr )
    {
        m_motion->DeleteObject(bAll);
    }

    if ( m_auto != nullptr )
    {
        m_auto->DeleteObject(bAll);
    }

    for (int i=0 ; i<OBJECTMAXPART ; i++ )
    {
        if ( m_objectPart[i].bUsed )
        {
            m_objectPart[i].bUsed = false;
            m_engine->DeleteObject(m_objectPart[i].object);

            if ( m_objectPart[i].masterParti != -1 )
            {
                m_particle->DeleteParticle(m_objectPart[i].masterParti);
                m_objectPart[i].masterParti = -1;
            }
        }
    }

    if (!bAll)
    {
        for (int i = 0; i < GetNumSlots(); i++ )
        {
            CObject* item = GetSlotContainedObject(i);
            if (item->Implements(ObjectInterfaceType::Old))
            {
                dynamic_cast<COldObject*>(item)->SetTransporter(nullptr);
                dynamic_cast<COldObject*>(item)->DeleteObject(bAll);
            }
            SetSlotContainedObject(i, nullptr);
        }
    }

    if ( !bAll )  m_main->CreateShortcuts();
}

// Simplifies a object (destroys all logic classes, making it a static object)

void COldObject::Simplify()
{
    if ( Implements(ObjectInterfaceType::Programmable) )
    {
        StopProgram();
    }
    m_main->SaveOneScript(this);

    m_implementedInterfaces[static_cast<int>(ObjectInterfaceType::ProgramStorage)] = false;
    m_implementedInterfaces[static_cast<int>(ObjectInterfaceType::Programmable)] = false;

    if ( m_physics != nullptr )
    {
        m_physics->DeleteObject();
        m_physics.reset();
    }
    if ( m_motion != nullptr )
    {
        m_motion->DeleteObject();
        m_motion.reset();
    }
    m_implementedInterfaces[static_cast<int>(ObjectInterfaceType::Movable)] = false;

    if ( m_objectInterface != nullptr )
    {
        m_objectInterface->DeleteObject();
        m_objectInterface.reset();
    }

    if ( m_auto != nullptr )
    {
        m_auto->DeleteObject();
        m_auto.reset();
    }

    m_main->CreateShortcuts();
}


bool COldObject::DamageObject(DamageType type, float force, CObject* killer)
{
    assert(Implements(ObjectInterfaceType::Damageable));
    assert(!Implements(ObjectInterfaceType::Destroyable) || Implements(ObjectInterfaceType::Shielded) || Implements(ObjectInterfaceType::Fragile));

    if ( IsDying() )  return false;
    if ( Implements(ObjectInterfaceType::Jostleable) ) return false;

    auto damageable = GetObjectDamageableDetails(this);
    if ( type == DamageType::Fire          && !damageable.fire.enabled          ) return false;
    if ( type == DamageType::Organic       && !damageable.organic.enabled       ) return false;
    if ( type == DamageType::Phazer        && !damageable.phazer.enabled        ) return false;
    if ( type == DamageType::Tower         && !damageable.tower.enabled         ) return false;
    if ( type == DamageType::FallingObject && !damageable.fallingObject.enabled ) return false;
    if ( type == DamageType::Explosive     && !damageable.explosive.enabled     ) return false;
    if ( type == DamageType::Collision     && !damageable.collision.enabled     ) return false;
    if ( type == DamageType::Lightning     && !damageable.lightning.enabled     ) return false;
    if ( type == DamageType::Fall          && !damageable.fall.enabled          ) return false;

    if ( Implements(ObjectInterfaceType::Fragile) )
    {
        auto fragile = GetObjectFragileDetails(this);
        if ( fragile.burnable )
        {
            // Fragile, but can have fire effect
            // TODO: IsBurnable()
            force = -1.0f;
        }

        if ( m_magnifyDamage * m_main->GetGlobalMagnifyDamage() == 0 ) return false; // Don't destroy if magnifyDamage=0

        DestroyObject(DestructionType::Explosion, killer);
        return true;
    }

    if ( type == DamageType::Organic )
    {
        // TODO: I don't understand, why does it apply damage only once every 0.5 second?
        if ( m_shotTime < 0.5f )  return false;
        m_shotTime = 0.0f;
    }

    float loss = 1.0f;
    bool dead = true;
    if (Implements(ObjectInterfaceType::Shielded))
    {
        float magnifyDamage = m_magnifyDamage * m_main->GetGlobalMagnifyDamage();
        if (force != std::numeric_limits<float>::infinity())
        {
            // Calculate the shield lost by the explosion
            loss = force * magnifyDamage;
            if (m_type == OBJECT_HUMAN) loss /= 2.5f; // Me is more resistant
            if (loss > 1.0f) loss = 1.0f;

            // Decreases the the shield
            SetShield(GetShield() - loss);

            // Sending info about taking damage
            if (!IsDamaging())
            {
                SetDamaging(true);
                m_main->UpdateShortcuts();
            }
            m_damageTime = m_time;
        }
        else
        {
            if ( magnifyDamage != 0.0f )
            {
                // Dead immediately
                SetShield(0.0f);
                SetDamaging(false);
            }
        }
        dead = (GetShield() <= 0.0f);
    }

    if (dead && Implements(ObjectInterfaceType::Destroyable))
    {
        if (type == DamageType::Fire)
        {
            DestroyObject(DestructionType::Burn, killer);
        }
        else
        {
            DestroyObject(DestructionType::Explosion, killer);
        }
        return true;
    }

    m_engine->GetPyroManager()->Create(damageable.effect, this, loss);
    return false;
}

void COldObject::DestroyObject(DestructionType type, CObject* killer)
{
    assert(Implements(ObjectInterfaceType::Destroyable));

    if(type == DestructionType::NoEffect) assert(!!"DestructionType::NoEffect should not be passed to DestroyObject()!");
    assert(type != DestructionType::Drowned || m_type == OBJECT_HUMAN);

    if ( IsDying() )  return;

    if (Implements(ObjectInterfaceType::Shielded))
    {
        SetShield(0.0f);
        SetDamaging(false);
    }

    auto destroyable = GetObjectDestroyableDetails(this);

    Gfx::PyroType pyroType = Gfx::PT_NULL;
    if ( type == DestructionType::Explosion )   // explosion?
    {
        pyroType = destroyable.explosion.effect;
    }
    else if ( type == DestructionType::ExplosionWater )
    {
        pyroType = destroyable.water.effect;
    }
    else if ( type == DestructionType::Burn )  // burning?
    {
        pyroType = destroyable.burning.effect;

        if (destroyable.burning.isKilledByBurning)
            SetDying(DeathType::Burning);

        SetVirusMode(false);
    }
    else if ( type == DestructionType::Drowned )
    {
        pyroType = destroyable.drowned.effect;
    }
    else if ( type == DestructionType::Win )
    {
        pyroType = destroyable.win.effect;
    }
    else if ( type == DestructionType::Squash )
    {
        pyroType = destroyable.squash.effect;
        DeleteAllCrashSpheres();
    }

    assert(pyroType != Gfx::PT_NULL);
    if (pyroType == Gfx::PT_FRAGT ||
        pyroType == Gfx::PT_FRAGO ||
        pyroType == Gfx::PT_FRAGW)
    {
        SetDying(DeathType::Exploding);
    }
    m_engine->GetPyroManager()->Create(pyroType, this);

    if ( Implements(ObjectInterfaceType::Programmable) )
    {
        StopProgram();
    }
    m_main->SaveOneScript(this);

    if ( GetSelect() )
    {
        SetSelect(false);  // deselects the object
        m_camera->SetType(Gfx::CAM_TYPE_EXPLO);
        m_main->DeselectAll();
    }
    m_main->RemoveFromSelectionHistory(this);

    CScoreboard* scoreboard = m_main->GetScoreboard();
    if (scoreboard)
        scoreboard->ProcessKill(this, killer);

    m_team = 0; // Back to neutral on destruction

    if ( m_botVar != nullptr )
    {
        if ( Implements(ObjectInterfaceType::Transportable) )  // (*)
        {
            CScriptFunctions::DestroyObjectVar(m_botVar, false);
        }
    }
}

// (*)  If a robot or cosmonaut dies, the subject must continue to exist,
//  so that programs of the ants continue to operate as usual.


// Initializes a new part.

void COldObject::InitPart(int part)
{
    m_objectPart[part].bUsed      = true;
    m_objectPart[part].object     = -1;
    m_objectPart[part].parentPart = -1;

    m_objectPart[part].position   = Math::Vector(0.0f, 0.0f, 0.0f);
    m_objectPart[part].angle.y    = 0.0f;
    m_objectPart[part].angle.x    = 0.0f;
    m_objectPart[part].angle.z    = 0.0f;
    m_objectPart[part].zoom       = Math::Vector(1.0f, 1.0f, 1.0f);

    m_objectPart[part].bTranslate = true;
    m_objectPart[part].bRotate    = true;
    m_objectPart[part].bZoom      = false;

    m_objectPart[part].matTranslate.LoadIdentity();
    m_objectPart[part].matRotate.LoadIdentity();
    m_objectPart[part].matTransform.LoadIdentity();
    m_objectPart[part].matWorld.LoadIdentity();;

    m_objectPart[part].masterParti = -1;
}

// Removes part.

void COldObject::DeletePart(int part)
{
    if ( !m_objectPart[part].bUsed )  return;

    if ( m_objectPart[part].masterParti != -1 )
    {
        m_particle->DeleteParticle(m_objectPart[part].masterParti);
        m_objectPart[part].masterParti = -1;
    }

    m_objectPart[part].bUsed = false;
    m_engine->DeleteObject(m_objectPart[part].object);
    UpdateTotalPart();
}

void COldObject::UpdateTotalPart()
{
    int     i;

    m_totalPart = 0;
    for ( i=0 ; i<OBJECTMAXPART ; i++ )
    {
        if ( m_objectPart[i].bUsed )
        {
            m_totalPart = i+1;
        }
    }
}


// Specifies the number of the object of a part.

void COldObject::SetObjectRank(int part, int objRank)
{
    if ( !m_objectPart[part].bUsed )  // object not created?
    {
        InitPart(part);
        UpdateTotalPart();
    }
    m_objectPart[part].object = objRank;
}

// Returns the number of part.

int COldObject::GetObjectRank(int part)
{
    if ( !m_objectPart[part].bUsed )  return -1;
    return m_objectPart[part].object;
}

// Specifies what is the parent of a part.
// Reminder: Part 0 is always the father of all
// and therefore the main part (eg the chassis of a car).

void COldObject::SetObjectParent(int part, int parent)
{
    m_objectPart[part].parentPart = parent;
}


// Specifies the type of the object.

void COldObject::SetType(ObjectType type)
{
    m_type = type;
    m_name = GetObjectName(m_type);

    SetSelectable(IsSelectableByDefault());

    auto transportable       = GetObjectTransportableDetails(this);
    auto programmable        = GetObjectProgrammableDetails(this);
    auto task_executor       = GetObjectTaskExecutorDetails(this);
    auto jostleable          = GetObjectJostleableDetails(this);
    auto movable             = GetObjectMovableDetails(this);
    auto flying              = GetObjectFlyingDetails(this);
    auto jet_flying          = GetObjectJetFlyingDetails(this);
    auto controllable        = GetObjectControllableDetails(this);
    auto power_container     = GetObjectPowerContainerDetails(this);
    auto ranged              = GetObjectRangedDetails(this);
    auto trace_drawing       = GetObjectTraceDrawingDetails(this);
    auto damageable          = GetObjectDamageableDetails(this);
    auto destroyable         = GetObjectDestroyableDetails(this);
    auto fragile             = GetObjectFragileDetails(this);
    auto shielded            = GetObjectShieldedDetails(this);
    auto shielded_auto_regen = GetObjectShieldedAutoRegenDetails(this);
    auto slotted             = GetObjectSlottedDetails(this);
    auto thumpable           = GetObjectThumpableDetails(this);
    auto shielder            = GetObjectShielderDetails(this);

    bool interactiveEnabled    = true;
    bool oldEnabled            = true;
    bool programStorageEnabled = programmable.enabled;

    m_implementedInterfaces[static_cast<int>(ObjectInterfaceType::Interactive)]       = interactiveEnabled;
    m_implementedInterfaces[static_cast<int>(ObjectInterfaceType::Transportable)]     = transportable.enabled;
    m_implementedInterfaces[static_cast<int>(ObjectInterfaceType::ProgramStorage)]    = programStorageEnabled;
    m_implementedInterfaces[static_cast<int>(ObjectInterfaceType::Programmable)]      = programmable.enabled;
    m_implementedInterfaces[static_cast<int>(ObjectInterfaceType::TaskExecutor)]      = task_executor.enabled;
    m_implementedInterfaces[static_cast<int>(ObjectInterfaceType::Jostleable)]        = jostleable.enabled;
    m_implementedInterfaces[static_cast<int>(ObjectInterfaceType::Movable)]           = movable.enabled;
    m_implementedInterfaces[static_cast<int>(ObjectInterfaceType::Flying)]            = flying.enabled;
    m_implementedInterfaces[static_cast<int>(ObjectInterfaceType::JetFlying)]         = jet_flying.enabled;
    m_implementedInterfaces[static_cast<int>(ObjectInterfaceType::Controllable)]      = controllable.enabled;
    m_implementedInterfaces[static_cast<int>(ObjectInterfaceType::PowerContainer)]    = power_container.enabled;
    m_implementedInterfaces[static_cast<int>(ObjectInterfaceType::Ranged)]            = ranged.enabled;
    m_implementedInterfaces[static_cast<int>(ObjectInterfaceType::TraceDrawing)]      = trace_drawing.enabled;
    m_implementedInterfaces[static_cast<int>(ObjectInterfaceType::Damageable)]        = damageable.enabled;
    m_implementedInterfaces[static_cast<int>(ObjectInterfaceType::Destroyable)]       = destroyable.enabled;
    m_implementedInterfaces[static_cast<int>(ObjectInterfaceType::Fragile)]           = fragile.enabled;
    m_implementedInterfaces[static_cast<int>(ObjectInterfaceType::Shielded)]          = shielded.enabled;
    m_implementedInterfaces[static_cast<int>(ObjectInterfaceType::ShieldedAutoRegen)] = shielded_auto_regen.enabled;
    m_implementedInterfaces[static_cast<int>(ObjectInterfaceType::Old)]               = oldEnabled;
    m_implementedInterfaces[static_cast<int>(ObjectInterfaceType::Slotted)]           = slotted.enabled;
    m_implementedInterfaces[static_cast<int>(ObjectInterfaceType::Thumpable)]         = thumpable.enabled;
    m_implementedInterfaces[static_cast<int>(ObjectInterfaceType::Shielder)]          = shielder.enabled;

    m_cameraType = controllable.camera.defaultCamera;
}

const char* COldObject::GetName()
{
    return m_name.c_str();
}

// Choosing the option to use.

void COldObject::SetOption(int option)
{
    m_option = option;
}

int COldObject::GetOption()
{
    return m_option;
}


// Saves all the parameters of the object.

void COldObject::Write(CLevelParserLine* line)
{
    Math::Vector    pos;

    line->AddParam("camera", MakeUnique<CLevelParserParam>(GetCameraType()));

    if ( GetCameraLock() )
        line->AddParam("cameraLock", MakeUnique<CLevelParserParam>(GetCameraLock()));

    if ( IsBulletWall() )
        line->AddParam("bulletWall", MakeUnique<CLevelParserParam>(IsBulletWall()));

    if ( GetEnergyLevel() != 0.0f )
        line->AddParam("energy", MakeUnique<CLevelParserParam>(GetEnergyLevel()));

    if ( GetShield() != 1.0f )
        line->AddParam("shield", MakeUnique<CLevelParserParam>(GetShield()));

    if ( GetRange() != 1.0f )
        line->AddParam("range", MakeUnique<CLevelParserParam>(GetRange()));

    if ( !GetSelectable() )
        line->AddParam("selectable", MakeUnique<CLevelParserParam>(GetSelectable()));

    if ( !GetCollisions() )
        line->AddParam("clip", MakeUnique<CLevelParserParam>(GetCollisions()));

    if ( GetLock() )
        line->AddParam("lock", MakeUnique<CLevelParserParam>(GetLock()));

    if ( !GetActivity() )
        line->AddParam("activity", MakeUnique<CLevelParserParam>(GetActivity()));

    if ( GetProxyActivate() )
    {
        line->AddParam("proxyActivate", MakeUnique<CLevelParserParam>(GetProxyActivate()));
        line->AddParam("proxyDistance", MakeUnique<CLevelParserParam>(GetProxyDistance()/g_unit));
    }

    if ( GetMagnifyDamage() != 1.0f )
        line->AddParam("magnifyDamage", MakeUnique<CLevelParserParam>(GetMagnifyDamage()));

    if ( GetTeam() != 0 )
        line->AddParam("team", MakeUnique<CLevelParserParam>(GetTeam()));

    if ( GetGunGoalV() != 0.0f )
        line->AddParam("aimV", MakeUnique<CLevelParserParam>(GetGunGoalV()));

    if ( GetGunGoalH() != 0.0f )
        line->AddParam("aimH", MakeUnique<CLevelParserParam>(GetGunGoalH()));

    if ( GetAnimateOnReset() )
    {
        line->AddParam("reset", MakeUnique<CLevelParserParam>(GetAnimateOnReset()));
    }

    if ( m_bVirusMode )
        line->AddParam("virusMode", MakeUnique<CLevelParserParam>(m_bVirusMode));

    if ( m_virusTime != 0.0f )
        line->AddParam("virusTime", MakeUnique<CLevelParserParam>(m_virusTime));

    line->AddParam("lifetime", MakeUnique<CLevelParserParam>(m_aTime));

    // Sets the parameters of the command line.
    CLevelParserParamVec cmdline;
    for(float value : GetCmdLine())
    {
        cmdline.push_back(MakeUnique<CLevelParserParam>(value));
    }
    if (cmdline.size() > 0)
        line->AddParam("cmdline", MakeUnique<CLevelParserParam>(std::move(cmdline)));

    if ( m_motion != nullptr )
    {
        m_motion->Write(line);
    }

    if ( Implements(ObjectInterfaceType::Programmable) )
    {
        line->AddParam("bVirusActive", MakeUnique<CLevelParserParam>(GetActiveVirus()));
    }

    if ( Implements(ObjectInterfaceType::Shielder) )
    {
        line->AddParam("bShieldActive", MakeUnique<CLevelParserParam>(IsBackgroundTask()));
    }

    if (GetFixed())
        line->AddParam("fixed", MakeUnique<CLevelParserParam>(GetFixed()));
        
    if ( m_physics != nullptr )
    {
        m_physics->Write(line);
    }

    if ( m_auto != nullptr )
    {
        m_auto->Write(line);
    }
}

// Returns all parameters of the object.

void COldObject::Read(CLevelParserLine* line)
{
    Math::Vector zoom = line->GetParam("zoom")->AsPoint(Math::Vector(1.0f, 1.0f, 1.0f));
    if (zoom.x != 1.0f || zoom.y != 1.0f || zoom.z != 1.0f)
        SetScale(zoom);

    if (line->GetParam("camera")->IsDefined())
        SetCameraType(line->GetParam("camera")->AsCameraType());
    SetCameraLock(line->GetParam("cameraLock")->AsBool(false));

    if (line->GetParam("pyro")->IsDefined())
        m_engine->GetPyroManager()->Create(line->GetParam("pyro")->AsPyroType(), this);

    SetBulletWall(line->GetParam("bulletWall")->AsBool(IsBulletWallByDefault(m_type)));

    SetProxyActivate(line->GetParam("proxyActivate")->AsBool(false));
    SetProxyDistance(line->GetParam("proxyDistance")->AsFloat(15.0f)*g_unit);
    SetCollisions(line->GetParam("clip")->AsBool(true));
    SetAnimateOnReset(line->GetParam("reset")->AsBool(false));
    if (Implements(ObjectInterfaceType::Controllable))
    {
        SetSelectable(line->GetParam("selectable")->AsBool(IsSelectableByDefault()));
    }
    if (Implements(ObjectInterfaceType::JetFlying))
    {
        SetRange(line->GetParam("range")->AsFloat(30.0f));
    }
    if (Implements(ObjectInterfaceType::Fragile))
    {
        SetMagnifyDamage(line->GetParam("magnifyDamage")->AsFloat(1.0f)); // TODO: This is a temporary hack for now - CFragileObject doesn't have SetMagnifyDamage ~krzys_h
    }
    if (Implements(ObjectInterfaceType::Shielded))
    {
        SetShield(line->GetParam("shield")->AsFloat(1.0f));
        SetMagnifyDamage(line->GetParam("magnifyDamage")->AsFloat(1.0f));
    }
    if (Implements(ObjectInterfaceType::Programmable))
    {
        SetCheckToken(!line->GetParam("checkToken")->IsDefined() ? GetSelectable() : line->GetParam("checkToken")->AsBool(true));

        if (line->GetParam("cmdline")->IsDefined())
        {
            const auto& cmdline = line->GetParam("cmdline")->AsArray();
            for (unsigned int i = 0; i < cmdline.size(); i++)
            {
                SetCmdLine(i, cmdline[i]->AsFloat());
            }
        }
    }

    if ( Implements(ObjectInterfaceType::Shielder) )
    {
        if( line->GetParam("bShieldActive")->AsBool(false) )
        {
            StartTaskShield(TSM_START);
        }
    }

    // SetManual will affect bot speed
    if (m_type == OBJECT_MOBILEdr)
    {
        // TODO: Merge these two settings?
        SetManual(!GetTrainer());
    }

    // AlienWorm time up/down
    // TODO: Refactor function names
    if (m_type == OBJECT_WORM)
    {
        assert(Implements(ObjectInterfaceType::Movable));
        CMotion* motion = GetMotion();
        if (line->GetParam("param")->IsDefined())
        {
            const auto& p = line->GetParam("param")->AsArray();
            for (unsigned int i = 0; i < 10 && i < p.size(); i++)
            {
                motion->SetParam(i, p[i]->AsFloat());
            }
        }
    }

    if (m_auto != nullptr)
    {
        // TODO: Is it used for anything else than AlienEggs?
        m_auto->SetType(line->GetParam("autoType")->AsObjectType(OBJECT_NULL));
        for (int i = 0; i < 5; i++)
        {
            std::string op = "autoValue" + boost::lexical_cast<std::string>(i+1); // autoValue1..autoValue5
            m_auto->SetValue(i, line->GetParam(op)->AsFloat(0.0f));
        }
        m_auto->SetString(const_cast<char*>(line->GetParam("autoString")->AsString("").c_str()));

        int i = line->GetParam("run")->AsInt(-1);
        if (i != -1)
        {
            if (i != PARAM_FIXSCENE && !CSettings::GetInstancePointer()->GetMovies()) i = 0;
            m_auto->Start(i);  // starts the film
        }
    }


    // Everthing below is for use only by saved scenes
    if (line->GetParam("energy")->IsDefined())
        SetEnergyLevel(line->GetParam("energy")->AsFloat());
    SetLock(line->GetParam("lock")->AsBool(false));
    SetActivity(line->GetParam("activity")->AsBool(true));
    SetGunGoalV(line->GetParam("aimV")->AsFloat(0.0f));
    SetGunGoalH(line->GetParam("aimH")->AsFloat(0.0f));

    if (line->GetParam("burnMode")->AsBool(false))
        SetDying(DeathType::Burning);
    m_bVirusMode = line->GetParam("virusMode")->AsBool(false);
    m_virusTime = line->GetParam("virusTime")->AsFloat(0.0f);

    m_aTime = line->GetParam("lifetime")->AsFloat(0.0f);

    if ( m_motion != nullptr )
    {
        m_motion->Read(line);
    }

    if (Implements(ObjectInterfaceType::Programmable))
    {
        SetActiveVirus(line->GetParam("bVirusActive")->AsBool(false));
    }

    SetFixed(line->GetParam("fixed")->AsBool(false));

    if ( m_physics != nullptr )
    {
        m_physics->Read(line);
    }

    if ( m_auto != nullptr )
    {
        m_auto->Read(line);
    }
}



// Seeking the nth son of a father.

int COldObject::SearchDescendant(int parent, int n)
{
    int     i;

    for ( i=0 ; i<m_totalPart ; i++ )
    {
        if ( !m_objectPart[i].bUsed )  continue;

        if ( parent == m_objectPart[i].parentPart )
        {
            if ( n-- == 0 )  return i;
        }
    }
    return -1;
}

void COldObject::TransformCrashSphere(Math::Sphere& crashSphere)
{
    if(!Implements(ObjectInterfaceType::Jostleable)) crashSphere.radius *= GetScaleX();

    // Returns to the sphere collisions,
    // which ignores the tilt of the vehicle.
    // This is necessary to collisions with vehicles,
    // so as not to reflect SetTilt, for example.
    // The sphere must necessarily have a center (0, y, 0).
    if (m_crashSpheres.size() == 1 &&
        crashSphere.pos.x == 0.0f &&
        crashSphere.pos.z == 0.0f )
    {
        crashSphere.pos += m_objectPart[0].position;
        return;
    }

    if (m_objectPart[0].bTranslate ||
        m_objectPart[0].bRotate)
    {
        UpdateTransformObject();
    }

    crashSphere.pos = Math::Transform(m_objectPart[0].matWorld, crashSphere.pos);
}

void COldObject::TransformCameraCollisionSphere(Math::Sphere& collisionSphere)
{
    collisionSphere.pos = Math::Transform(m_objectPart[0].matWorld, collisionSphere.pos);
    collisionSphere.radius *= GetScaleX();
}


// Specifies the sphere of jostling, relative to the object.

void COldObject::SetJostlingSphere(const Math::Sphere& jostlingSphere)
{
    m_jostlingSphere = jostlingSphere;
}

// Specifies the sphere of jostling, in the world.

Math::Sphere COldObject::GetJostlingSphere() const
{
    Math::Sphere transformedJostlingSphere = m_jostlingSphere;
    transformedJostlingSphere.pos = Math::Transform(m_objectPart[0].matWorld, transformedJostlingSphere.pos);
    return transformedJostlingSphere;
}


// Positioning an object on a certain height, above the ground.

void COldObject::SetFloorHeight(float height)
{
    Math::Vector    pos;

    pos = m_objectPart[0].position;
    m_terrain->AdjustToFloor(pos);

    if ( m_physics != nullptr )
    {
        m_physics->SetLand(height == 0.0f);
        m_physics->SetMotor(height != 0.0f);
    }

    m_objectPart[0].position.y = pos.y+height+m_character.height;
    m_objectPart[0].bTranslate = true;  // it will recalculate the matrices
}

// Adjust the inclination of an object laying on the ground.

void COldObject::FloorAdjust()
{
    Math::Vector        pos, n;
    Math::Point         nn;
    float           a;

    pos = GetPosition();
    if ( m_terrain->GetNormal(n, pos) )
    {
        a = GetRotationY();
        nn = Math::RotatePoint(-a, Math::Point(n.z, n.x));
        SetRotationX( sinf(nn.x));
        SetRotationZ(-sinf(nn.y));
    }
}


// Getes the linear vibration.

void COldObject::SetLinVibration(Math::Vector dir)
{
    if ( m_linVibration.x != dir.x ||
         m_linVibration.y != dir.y ||
         m_linVibration.z != dir.z )
    {
        m_linVibration = dir;
        m_objectPart[0].bTranslate = true;
    }
}

Math::Vector COldObject::GetLinVibration()
{
    return m_linVibration;
}

// Getes the circular vibration.

void COldObject::SetCirVibration(Math::Vector dir)
{
    if ( m_cirVibration.x != dir.x ||
         m_cirVibration.y != dir.y ||
         m_cirVibration.z != dir.z )
    {
        m_cirVibration = dir;
        m_objectPart[0].bRotate = true;
    }
}

Math::Vector COldObject::GetCirVibration()
{
    return m_cirVibration;
}

// Getes the inclination.

void COldObject::SetTilt(Math::Vector dir)
{
    if ( m_tilt.x != dir.x ||
         m_tilt.y != dir.y ||
         m_tilt.z != dir.z )
    {
        m_tilt = dir;
        m_objectPart[0].bRotate = true;
    }
}

Math::Vector COldObject::GetTilt()
{
    return m_tilt;
}


// Getes the position of center of the object.

void COldObject::SetPartPosition(int part, const Math::Vector &pos)
{
    m_objectPart[part].position = pos;
    m_objectPart[part].bTranslate = true;  // it will recalculate the matrices

    if ( part == 0 && !m_bFlat )  // main part?
    {
        int rank = m_objectPart[0].object;

        Math::Vector shPos = pos;
        m_terrain->AdjustToFloor(shPos, true);
        m_engine->SetObjectShadowSpotPos(rank, shPos);

        float height = 0.0f;
        if ( Implements(ObjectInterfaceType::Flying) )
        {
            height = pos.y-shPos.y;
        }
        m_engine->SetObjectShadowSpotHeight(rank, height);

        m_engine->UpdateObjectShadowSpotNormal(rank);

        if ( m_shadowLight != -1 )
        {
            Math::Vector lightPos = pos;
            lightPos.y += m_shadowHeight;
            m_lightMan->SetLightPos(m_shadowLight, lightPos);
        }
    }
}

Math::Vector COldObject::GetPartPosition(int part) const
{
    return m_objectPart[part].position;
}

// Getes the rotation around three axis.

void COldObject::SetPartRotation(int part, const Math::Vector &angle)
{
    m_objectPart[part].angle = angle;
    m_objectPart[part].bRotate = true;  // it will recalculate the matrices

    if ( part == 0 && !m_bFlat )  // main part?
    {
        m_engine->SetObjectShadowSpotAngle(m_objectPart[0].object, m_objectPart[0].angle.y);
    }
}

Math::Vector COldObject::GetPartRotation(int part) const
{
    return m_objectPart[part].angle;
}

// Getes the rotation about the axis Y.

void COldObject::SetPartRotationY(int part, float angle)
{
    m_objectPart[part].angle.y = angle;
    m_objectPart[part].bRotate = true;  // it will recalculate the matrices

    if ( part == 0 && !m_bFlat )  // main part?
    {
        m_engine->SetObjectShadowSpotAngle(m_objectPart[0].object, m_objectPart[0].angle.y);
    }
}

// Getes the rotation about the axis X.

void COldObject::SetPartRotationX(int part, float angle)
{
    m_objectPart[part].angle.x = angle;
    m_objectPart[part].bRotate = true;  // it will recalculate the matrices
}

// Getes the rotation about the axis Z.

void COldObject::SetPartRotationZ(int part, float angle)
{
    m_objectPart[part].angle.z = angle;
    m_objectPart[part].bRotate = true;  //it will recalculate the matrices
}

float COldObject::GetPartRotationY(int part)
{
    return m_objectPart[part].angle.y;
}

float COldObject::GetPartRotationX(int part)
{
    return m_objectPart[part].angle.x;
}

float COldObject::GetPartRotationZ(int part)
{
    return m_objectPart[part].angle.z;
}


// Getes the global zoom.

void COldObject::SetPartScale(int part, float zoom)
{
    m_objectPart[part].bTranslate = true;  // it will recalculate the matrices
    m_objectPart[part].zoom.x = zoom;
    m_objectPart[part].zoom.y = zoom;
    m_objectPart[part].zoom.z = zoom;

    m_objectPart[part].bZoom = ( m_objectPart[part].zoom.x != 1.0f ||
                                 m_objectPart[part].zoom.y != 1.0f ||
                                 m_objectPart[part].zoom.z != 1.0f );
}

void COldObject::SetPartScale(int part, Math::Vector zoom)
{
    m_objectPart[part].bTranslate = true;  // it will recalculate the matrices
    m_objectPart[part].zoom = zoom;

    m_objectPart[part].bZoom = ( m_objectPart[part].zoom.x != 1.0f ||
                                 m_objectPart[part].zoom.y != 1.0f ||
                                 m_objectPart[part].zoom.z != 1.0f );
}

Math::Vector COldObject::GetPartScale(int part) const
{
    return m_objectPart[part].zoom;
}

void COldObject::SetPartScaleX(int part, float zoom)
{
    m_objectPart[part].bTranslate = true;  // it will recalculate the matrices
    m_objectPart[part].zoom.x = zoom;

    m_objectPart[part].bZoom = ( m_objectPart[part].zoom.x != 1.0f ||
                                 m_objectPart[part].zoom.y != 1.0f ||
                                 m_objectPart[part].zoom.z != 1.0f );
}

void COldObject::SetPartScaleY(int part, float zoom)
{
    m_objectPart[part].bTranslate = true;  // it will recalculate the matrices
    m_objectPart[part].zoom.y = zoom;

    m_objectPart[part].bZoom = ( m_objectPart[part].zoom.x != 1.0f ||
                                 m_objectPart[part].zoom.y != 1.0f ||
                                 m_objectPart[part].zoom.z != 1.0f );
}

void COldObject::SetPartScaleZ(int part, float zoom)
{
    m_objectPart[part].bTranslate = true;  // it will recalculate the matrices
    m_objectPart[part].zoom.z = zoom;

    m_objectPart[part].bZoom = ( m_objectPart[part].zoom.x != 1.0f ||
                                 m_objectPart[part].zoom.y != 1.0f ||
                                 m_objectPart[part].zoom.z != 1.0f );
}

float COldObject::GetPartScaleX(int part)
{
    return m_objectPart[part].zoom.x;
}

float COldObject::GetPartScaleY(int part)
{
    return m_objectPart[part].zoom.y;
}

float COldObject::GetPartScaleZ(int part)
{
    return m_objectPart[part].zoom.z;
}

void COldObject::SetTrainer(bool bEnable)
{
    m_bTrainer = bEnable;

    if ( m_bTrainer )  // training?
    {
        m_cameraType = Gfx::CAM_TYPE_FIX;
    }
}

bool COldObject::GetTrainer()
{
    return m_bTrainer;
}

bool COldObject::GetPlusTrainer()
{
    return m_main->GetPlusTrainer();
}

void COldObject::SetToy(bool bEnable)
{
    m_bToy = bEnable;
}

bool COldObject::GetToy()
{
    return m_bToy;
}

void COldObject::SetManual(bool bManual)
{
    m_bManual = bManual;
}

bool COldObject::GetManual()
{
    return m_bManual;
}

// Management of the particle master.

void COldObject::SetMasterParticle(int part, int parti)
{
    m_objectPart[part].masterParti = parti;
}


// Management of the stack transport.


int COldObject::GetNumSlots()
{
    auto slots = GetObjectSlottedDetails(this).slots;
    return slots.size();
}

int COldObject::MapPseudoSlot(Pseudoslot pseudoslot)
{
    auto slots = GetObjectSlottedDetails(this).slots;

    for (unsigned int i = 0; i < slots.size(); i++)
    {
        if (slots[i].category == SLOT_POWER && pseudoslot == Pseudoslot::POWER)
            return i;
        if (slots[i].category == SLOT_CARGO && pseudoslot == Pseudoslot::CARRYING)
            return i;
    }

    return -1;
}

Math::Vector COldObject::GetSlotPosition(int slotNum)
{
    auto slots = GetObjectSlottedDetails(this).slots;

    assert(unsigned(slotNum) < slots.size());
    if (slots[slotNum].partNum == 0)
        return slots[slotNum].position;

    return Math::Transform(GetWorldMatrix(0)->Inverse(), Math::Transform(*GetWorldMatrix(slots[slotNum].partNum), slots[slotNum].position));
}

float COldObject::GetSlotAngle(int slotNum)
{
    auto slots = GetObjectSlottedDetails(this).slots;

    assert(unsigned(slotNum) < slots.size());
    if (slots[slotNum].category != SLOT_CARGO)
    {
        switch (m_type)
        {
        case OBJECT_TOWER:
        case OBJECT_RESEARCH:
        case OBJECT_ENERGY:
        case OBJECT_LABO:
        case OBJECT_NUCLEAR:
            return 0;
        default: // robots
            return Math::PI;
        }
    }

    return 0;
}

float COldObject::GetSlotAcceptanceAngle(int slotNum)
{
    auto slots = GetObjectSlottedDetails(this).slots;

    assert(unsigned(slotNum) < slots.size());
    if (slots[slotNum].category != SLOT_CARGO)
    {
        switch (m_type)
        {
        case OBJECT_TOWER:
        case OBJECT_RESEARCH:
            return 45.0f*Math::PI/180.0f;
        case OBJECT_ENERGY:
            return 90.0f*Math::PI/180.0f;
        case OBJECT_LABO:
            return 120.0f*Math::PI/180.0f;
        case OBJECT_NUCLEAR:
            return 45.0f*Math::PI/180.0f;
        default:
            return 45.0f*Math::PI/180.0f;
        }
    }

    return 0; // no acceptance angle for cargo slot
}

CObject *COldObject::GetSlotContainedObject(int slotNum)
{
    auto slots = GetObjectSlottedDetails(this).slots;

    assert(unsigned(slotNum) < slots.size());

    if (slots[slotNum].category == SLOT_CARGO)
        return m_cargoSlot;

    if (slots[slotNum].category == SLOT_POWER)
        return m_powerSlot;

    return m_otherSlot;
}

void COldObject::SetSlotContainedObject(int slotNum, CObject *object)
{
    auto slots = GetObjectSlottedDetails(this).slots;

    assert(unsigned(slotNum) < slots.size());

    if (slots[slotNum].category == SLOT_CARGO)
        m_cargoSlot = object;

    if (slots[slotNum].category == SLOT_POWER)
        m_powerSlot = object;

    m_otherSlot = object;
}


// Management of the object "transporter" that transports it.

void COldObject::SetTransporter(CObject* transporter)
{
    m_transporter = transporter;

    // Invisible shadow if the object is transported.
    m_engine->SetObjectShadowSpotHide(m_objectPart[0].object, (m_transporter != nullptr));
}

CObject* COldObject::GetTransporter()
{
    return m_transporter;
}

// Management of the conveying portion.

void COldObject::SetTransporterPart(int part)
{
    m_transporterLink = part;
}


// Returns matrices of an object portion.

Math::Matrix* COldObject::GetRotateMatrix(int part)
{
    return &m_objectPart[part].matRotate;
}

Math::Matrix* COldObject::GetWorldMatrix(int part)
{
    if ( m_objectPart[0].bTranslate ||
         m_objectPart[0].bRotate    )
    {
        UpdateTransformObject();
    }

    return &m_objectPart[part].matWorld;
}


// Indicates whether the object should be drawn over the interface.

void COldObject::SetDrawFront(bool bDraw)
{
    int     i;

    for ( i=0 ; i<OBJECTMAXPART ; i++ )
    {
        if ( m_objectPart[i].bUsed )
        {
            m_engine->SetObjectDrawFront(m_objectPart[i].object, bDraw);
        }
    }
}

// Creates shade under a vehicle as a negative light.

bool COldObject::CreateShadowLight(float height, Gfx::Color color)
{
    if ( !m_engine->GetLightMode() )  return true;

    Math::Vector pos = GetPosition();
    m_shadowHeight = height;

    Gfx::Light light;
    light.type          = Gfx::LIGHT_SPOT;
    light.diffuse       = color;
    light.ambient       = color * 0.1f;
    light.position      = Math::Vector(pos.x, pos.y+height, pos.z);
    light.direction     = Math::Vector(0.0f, -1.0f, 0.0f); // against the bottom
    light.spotIntensity = 128;
    light.attenuation0  = 1.0f;
    light.attenuation1  = 0.0f;
    light.attenuation2  = 0.0f;
    light.spotAngle = 90.0f*Math::PI/180.0f;

    m_shadowLight = m_lightMan->CreateLight();
    if ( m_shadowLight == -1 )  return false;

    m_lightMan->SetLight(m_shadowLight, light);

    // Only illuminates the objects on the ground.
    m_lightMan->SetLightIncludeType(m_shadowLight, Gfx::ENG_OBJTYPE_TERRAIN);

    return true;
}

// Returns the number of negative light shade.

int COldObject::GetShadowLight()
{
    return m_shadowLight;
}

// Creates the circular shadow underneath a vehicle.

bool COldObject::CreateShadowCircle(float radius, float intensity,
                                 Gfx::EngineShadowType type)
{
    float   zoom;

    if ( intensity == 0.0f )  return true;

    zoom = GetScaleX();

    m_engine->CreateShadowSpot(m_objectPart[0].object);

    m_engine->SetObjectShadowSpotRadius(m_objectPart[0].object, radius*zoom);
    m_engine->SetObjectShadowSpotIntensity(m_objectPart[0].object, intensity);
    m_engine->SetObjectShadowSpotHeight(m_objectPart[0].object, 0.0f);
    m_engine->SetObjectShadowSpotAngle(m_objectPart[0].object, m_objectPart[0].angle.y);
    m_engine->SetObjectShadowSpotType(m_objectPart[0].object, type);

    return true;
}

// Calculates the matrix for transforming the object.
// Returns true if the matrix has changed.
// The rotations occur in the order Y, Z and X.

bool COldObject::UpdateTransformObject(int part, bool bForceUpdate)
{
    Math::Vector    position, angle, eye;
    bool        bModif = false;
    int         parent;

    if ( m_transporter != nullptr )  // transported by transporter?
    {
        m_objectPart[part].bTranslate = true;
        m_objectPart[part].bRotate = true;
    }

    if ( !bForceUpdate                  &&
         !m_objectPart[part].bTranslate &&
         !m_objectPart[part].bRotate    )  return false;

    position = m_objectPart[part].position;
    angle    = m_objectPart[part].angle;

    if ( part == 0 )  // main part?
    {
        position += m_linVibration;
        angle    += m_cirVibration+m_tilt;
    }

    if ( m_objectPart[part].bTranslate ||
         m_objectPart[part].bRotate    )
    {
        if ( m_objectPart[part].bTranslate )
        {
            m_objectPart[part].matTranslate.LoadIdentity();
            m_objectPart[part].matTranslate.Set(1, 4, position.x);
            m_objectPart[part].matTranslate.Set(2, 4, position.y);
            m_objectPart[part].matTranslate.Set(3, 4, position.z);
        }

        if ( m_objectPart[part].bRotate )
        {
            Math::LoadRotationZXYMatrix(m_objectPart[part].matRotate, angle);
        }

        if ( m_objectPart[part].bZoom )
        {
            Math::Matrix    mz;
            mz.LoadIdentity();
            mz.Set(1, 1, m_objectPart[part].zoom.x);
            mz.Set(2, 2, m_objectPart[part].zoom.y);
            mz.Set(3, 3, m_objectPart[part].zoom.z);
            m_objectPart[part].matTransform = Math::MultiplyMatrices(m_objectPart[part].matTranslate,
                                                Math::MultiplyMatrices(m_objectPart[part].matRotate, mz));
        }
        else
        {
            m_objectPart[part].matTransform = Math::MultiplyMatrices(m_objectPart[part].matTranslate,
                                                                     m_objectPart[part].matRotate);
        }
        bModif = true;
    }

    if ( bForceUpdate                  ||
         m_objectPart[part].bTranslate ||
         m_objectPart[part].bRotate    )
    {
        parent = m_objectPart[part].parentPart;

        if ( part == 0 && m_transporter != nullptr )  // transported by a transporter?
        {
            Math::Matrix*   matWorldTransporter;
            matWorldTransporter = m_transporter->GetWorldMatrix(m_transporterLink);
            m_objectPart[part].matWorld = Math::MultiplyMatrices(*matWorldTransporter,
                                                                 m_objectPart[part].matTransform);
        }
        else
        {
            if ( parent == -1 )  // no parent?
            {
                m_objectPart[part].matWorld = m_objectPart[part].matTransform;
            }
            else
            {
                m_objectPart[part].matWorld = Math::MultiplyMatrices(m_objectPart[parent].matWorld,
                                                                     m_objectPart[part].matTransform);
            }
        }
        bModif = true;
    }

    if ( bModif )
    {
        m_engine->SetObjectTransform(m_objectPart[part].object,
                                     m_objectPart[part].matWorld);
    }

    m_objectPart[part].bTranslate = false;
    m_objectPart[part].bRotate    = false;

    return bModif;
}

// Updates all matrices to transform the object father and all his sons.
// Assume a maximum of 4 degrees of freedom.
// Appropriate, for example, to a body, an arm, forearm, hand and fingers.

bool COldObject::UpdateTransformObject()
{
    bool    bUpdate1, bUpdate2, bUpdate3, bUpdate4;
    int     level1, level2, level3, level4, rank;
    int     parent1, parent2, parent3, parent4;

    if ( m_bFlat )
    {
        for ( level1=0 ; level1<m_totalPart ; level1++ )
        {
            if ( !m_objectPart[level1].bUsed )  continue;
            UpdateTransformObject(level1, false);
        }
    }
    else
    {
        parent1 = 0;
        bUpdate1 = UpdateTransformObject(parent1, false);

        for ( level1=0 ; level1<m_totalPart ; level1++ )
        {
            rank = SearchDescendant(parent1, level1);
            if ( rank == -1 )  break;

            parent2 = rank;
            bUpdate2 = UpdateTransformObject(rank, bUpdate1);

            for ( level2=0 ; level2<m_totalPart ; level2++ )
            {
                rank = SearchDescendant(parent2, level2);
                if ( rank == -1 )  break;

                parent3 = rank;
                bUpdate3 = UpdateTransformObject(rank, bUpdate2);

                for ( level3=0 ; level3<m_totalPart ; level3++ )
                {
                    rank = SearchDescendant(parent3, level3);
                    if ( rank == -1 )  break;

                    parent4 = rank;
                    bUpdate4 = UpdateTransformObject(rank, bUpdate3);

                    for ( level4=0 ; level4<m_totalPart ; level4++ )
                    {
                        rank = SearchDescendant(parent4, level4);
                        if ( rank == -1 )  break;

                        UpdateTransformObject(rank, bUpdate4);
                    }
                }
            }
        }
    }

    return true;
}


// Puts all the progeny flat (there is more than fathers).
// This allows for debris independently from each other in all directions.

void COldObject::FlatParent()
{
    int     i;

    for ( i=0 ; i<m_totalPart ; i++ )
    {
        m_objectPart[i].position.x = m_objectPart[i].matWorld.Get(1, 4);
        m_objectPart[i].position.y = m_objectPart[i].matWorld.Get(2, 4);
        m_objectPart[i].position.z = m_objectPart[i].matWorld.Get(3, 4);

        m_objectPart[i].matWorld.Set(1, 4, 0.0f);
        m_objectPart[i].matWorld.Set(2, 4, 0.0f);
        m_objectPart[i].matWorld.Set(3, 4, 0.0f);

        m_objectPart[i].matTranslate.Set(1, 4, 0.0f);
        m_objectPart[i].matTranslate.Set(2, 4, 0.0f);
        m_objectPart[i].matTranslate.Set(3, 4, 0.0f);

        m_objectPart[i].parentPart = -1;  // more parents
    }

    m_bFlat = true;
}



// Updates the mapping of the texture of the pile.

void COldObject::UpdateEnergyMapping()
{
    if (Math::IsEqual(GetEnergyLevel(), m_lastEnergy, 0.01f))
        return;

    m_lastEnergy = GetEnergyLevel();

    Gfx::Material mat;
    mat.diffuse = Gfx::Color(1.0f, 1.0f, 1.0f);  // white
    mat.ambient = Gfx::Color(0.5f, 0.5f, 0.5f);

    float a = 0.0f, b = 0.0f;

    if ( m_type == OBJECT_POWER  ||
         m_type == OBJECT_ATOMIC )
    {
        a = 2.0f;
        b = 0.0f;  // dimensions of the battery (according to y)
    }
    else if ( m_type == OBJECT_STATION )
    {
        a = 10.0f;
        b =  4.0f;  // dimensions of the battery (according to y)
    }
    else if ( m_type == OBJECT_ENERGY )
    {
        a = 9.0f;
        b = 3.0f;  // dimensions of the battery (according to y)
    }

    float i = 0.50f+0.25f*GetEnergyLevel();  // origin
    float s = i+0.25f;  // width

    float au = (s-i)/(b-a);
    float bu = s-b*(s-i)/(b-a);

    std::string teamStr = StrUtils::ToString<int>(GetTeam());
    if(GetTeam() == 0) teamStr = "";
    m_engine->ChangeTextureMapping(m_objectPart[0].object,
                                   mat, Gfx::ENG_RSTATE_PART3, "objects/lemt.png"+teamStr, "",
                                   Gfx::ENG_TEX_MAPPING_1Y,
                                   au, bu, 1.0f, 0.0f);
}


// Manual action.

bool COldObject::EventProcess(const Event &event)
{
    // NOTE: This should be called befoce CProgrammableObjectImpl::EventProcess, see the other note inside this function
    if (!CTaskExecutorObjectImpl::EventProcess(event)) return false;

    if ( m_physics != nullptr )
    {
        if ( !m_physics->EventProcess(event) )  // object destroyed?
        {
            if ( GetSelect()             &&
                 m_type != OBJECT_ANT    &&
                 m_type != OBJECT_SPIDER &&
                 m_type != OBJECT_BEE    )
            {
                if ( !IsDying() )  m_camera->SetType(Gfx::CAM_TYPE_EXPLO);
                m_main->DeselectAll();
            }
            return false;
        }
    }

    if (Implements(ObjectInterfaceType::Movable) && m_physics != nullptr)
    {
        bool deselectedStop = !GetSelect();
        if (Implements(ObjectInterfaceType::Programmable))
        {
            deselectedStop = deselectedStop && !IsProgram();
        }
        if (Implements(ObjectInterfaceType::TaskExecutor))
        {
            deselectedStop = deselectedStop && !IsForegroundTask();
        }

        if ( deselectedStop )
        {
            float axeX = 0.0f;
            float axeY = 0.0f;
            float axeZ = 0.0f;
            if ( GetDying() == DeathType::Burning )  // Burning?
            {
                axeZ = -1.0f;  // tomb

                if ( (m_type == OBJECT_ANT    ||
                      m_type == OBJECT_SPIDER ||
                      m_type == OBJECT_WORM   ) )
                {
                    if (Implements(ObjectInterfaceType::Thumpable) && GetFixed() )
                    {
                        // just burn
                    }
                    else
                    {
                        axeY = 2.0f;  // zigzag disorganized fast
                        if ( m_type == OBJECT_WORM )  axeY = 5.0f;
                        axeX = 0.5f+sinf(m_time* 1.0f)*0.5f+
                                    sinf(m_time* 6.0f)*2.0f+
                                    sinf(m_time*21.0f)*0.2f;
                        float factor = 1.0f-m_burnTime/15.0f;  // slow motion
                        if ( factor < 0.0f )  factor = 0.0f;
                        axeY *= factor;
                        axeX *= factor;
                    }
                }
            }
            m_physics->SetMotorSpeedX(axeY);  // move forward/move back
            m_physics->SetMotorSpeedY(axeZ);  // up / down
            m_physics->SetMotorSpeedZ(axeX);  // rotate
        }
        else if (GetSelect())
        {
            bool canMove = true;
            if (Implements(ObjectInterfaceType::TaskExecutor))
            {
                canMove = canMove && (!IsForegroundTask() || GetForegroundTask()->IsPilot());
            }
            if (Implements(ObjectInterfaceType::Programmable))
            {
                canMove = canMove && !IsProgram();
            }
            if (Implements(ObjectInterfaceType::Thumpable))
            {
                canMove = canMove && !GetFixed();
            }

            if ( canMove )
            {
                if ( event.type == EVENT_OBJECT_LEFT    ||
                     event.type == EVENT_OBJECT_RIGHT   ||
                     event.type == EVENT_OBJECT_UP      ||
                     event.type == EVENT_OBJECT_DOWN    ||
                     event.type == EVENT_OBJECT_GASUP   ||
                     event.type == EVENT_OBJECT_GASDOWN )
                {
                    m_buttonAxe = event.type;
                }
                if ( event.type == EVENT_MOUSE_BUTTON_UP )
                {
                    m_buttonAxe = EVENT_NULL;
                }

                float axeX = event.motionInput.x;
                float axeY = event.motionInput.y;
                float axeZ = event.motionInput.z;

                if ( (!m_main->GetTrainerPilot() &&
                      GetTrainer()) ||
                     !m_main->CanPlayerInteract() )  // drive vehicle?
                {
                    axeX = 0.0f;
                    axeY = 0.0f;
                    axeZ = 0.0f;  // Remote control impossible!
                }

                if ( m_buttonAxe == EVENT_OBJECT_LEFT    )  axeX = -1.0f;
                if ( m_buttonAxe == EVENT_OBJECT_RIGHT   )  axeX =  1.0f;
                if ( m_buttonAxe == EVENT_OBJECT_UP      )  axeY =  1.0f;
                if ( m_buttonAxe == EVENT_OBJECT_DOWN    )  axeY = -1.0f;
                if ( m_buttonAxe == EVENT_OBJECT_GASUP   )  axeZ =  1.0f;
                if ( m_buttonAxe == EVENT_OBJECT_GASDOWN )  axeZ = -1.0f;

                if ( m_type == OBJECT_MOBILEdr && GetManual() )  // scribbler in manual mode?
                {
                    if ( axeX != 0.0f )  axeY = 0.0f;  // if running -> not moving!
                    axeX *= 0.5f;
                    axeY *= 0.5f;
                }

                if ( !m_main->IsResearchDone(RESEARCH_FLY, GetTeam()) )
                {
                    axeZ = -1.0f;  // tomb
                }

                if ( axeX >  1.0f )  axeX =  1.0f;
                if ( axeX < -1.0f )  axeX = -1.0f;

                m_physics->SetMotorSpeedX(axeY);  // move forward/move back
                m_physics->SetMotorSpeedY(axeZ);  // up/down
                m_physics->SetMotorSpeedZ(axeX);  // rotate
            }
        }
    }

    if ( m_objectInterface != nullptr )
    {
        m_objectInterface->EventProcess(event);
    }

    if ( m_auto != nullptr )
    {
        if (!GetLock())
        {
            m_auto->EventProcess(event);
        }

        if ( event.type == EVENT_FRAME &&
             m_auto->IsEnded() != ERR_CONTINUE )
        {
            m_auto->DeleteObject();
            m_auto.reset();
        }
    }

    if ( m_motion != nullptr )
    {
        if (!m_motion->EventProcess(event)) return false;
    }

    if (!CProgrammableObjectImpl::EventProcess(event)) return false;

    if ( event.type == EVENT_FRAME )
    {
        return EventFrame(event);
    }

    return true;
}


// Animates the object.

bool COldObject::EventFrame(const Event &event)
{
    if ( m_type == OBJECT_HUMAN && m_main->GetMainMovie() == MM_SATCOMopen )
    {
        UpdateTransformObject();
        return true;
    }

    m_time += event.rTime;

    if ( m_engine->GetPause() && m_type != OBJECT_SHOW )  return true;

    if ( GetDying() == DeathType::Burning )  m_burnTime += event.rTime;

    m_aTime += event.rTime;
    m_shotTime += event.rTime;

    VirusFrame(event.rTime);
    PartiFrame(event.rTime);

    UpdateMapping();
    UpdateTransformObject();
    UpdateSelectParticle();

    if (Implements(ObjectInterfaceType::ShieldedAutoRegen))
    {
        float autoregenTime = GetShieldFullRegenTime();
        if ( autoregenTime )
            SetShield(GetShield() + event.rTime*(1.0f/autoregenTime));
    }

    if (IsDamaging() && m_time - m_damageTime > 2.0f)
    {
        SetDamaging(false);
        m_main->UpdateShortcuts();
    }

    return true;
}

// Updates the mapping of the object.

void COldObject::UpdateMapping()
{
    if ( Implements(ObjectInterfaceType::PowerContainer) )
    {
        UpdateEnergyMapping();
    }
}


// Management of viruses.

void COldObject::VirusFrame(float rTime)
{
    if ( !m_bVirusMode )  return;  // healthy object?

    m_virusTime += rTime;
    if ( m_virusTime >= VIRUS_DELAY )
    {
        m_bVirusMode = false;  // the virus is no longer active
    }

    if ( m_lastVirusParticle+m_engine->ParticleAdapt(0.2f) <= m_aTime )
    {
        m_lastVirusParticle = m_aTime;

        Math::Vector pos = GetPosition();
        pos.x += (Math::Rand()-0.5f)*10.0f;
        pos.z += (Math::Rand()-0.5f)*10.0f;
        Math::Vector speed;
        speed.x = (Math::Rand()-0.5f)*2.0f;
        speed.z = (Math::Rand()-0.5f)*2.0f;
        speed.y = Math::Rand()*4.0f+4.0f;
        Math::Point dim;
        dim.x = Math::Rand()*0.3f+0.3f;
        dim.y = dim.x;

        m_particle->CreateParticle(pos, speed, dim, Gfx::PARTIVIRUS, 3.0f);
    }
}

// Management particles mistresses.

void COldObject::PartiFrame(float rTime)
{
    Math::Vector    pos, angle, factor;
    int         i, channel;

    for ( i=0 ; i<OBJECTMAXPART ; i++ )
    {
        if ( !m_objectPart[i].bUsed )  continue;

        channel = m_objectPart[i].masterParti;
        if ( channel == -1 )  continue;

        if ( !m_particle->GetPosition(channel, pos) )
        {
            m_objectPart[i].masterParti = -1;  // particle no longer exists!
            continue;
        }

        SetPartPosition(i, pos);

        // Each song spins differently.
        switch( i%5 )
        {
            case 0:  factor = Math::Vector( 0.5f, 0.3f, 0.6f); break;
            case 1:  factor = Math::Vector(-0.3f, 0.4f,-0.2f); break;
            case 2:  factor = Math::Vector( 0.4f,-0.6f,-0.3f); break;
            case 3:  factor = Math::Vector(-0.6f,-0.2f, 0.0f); break;
            case 4:  factor = Math::Vector( 0.4f, 0.1f,-0.7f); break;
        }

        angle = GetPartRotation(i);
        angle += rTime*Math::PI*factor;
        SetPartRotation(i, angle);
    }
}


// Changes the perspective to view if it was like in the vehicle,
// or behind the vehicle.

void COldObject::AdjustCamera(Math::Vector &eye, float &dirH, float &dirV,
                              Math::Vector  &lookat, Math::Vector &upVec,
                              Gfx::CameraType type)
{
    float   speed;
    int     part;

    UpdateTransformObject();

    auto controllable = GetObjectControllableDetails(this);
    part = controllable.camera.onboard.partNum;
    eye  = controllable.camera.onboard.position;

    if ( type == Gfx::CAM_TYPE_BACK )
    {
        eye.x -= 20.0f;
        eye.y +=  1.0f;
    }

    lookat.x = eye.x+1.0f;
    lookat.y = eye.y+0.0f;
    lookat.z = eye.z+0.0f;

    eye    = Math::Transform(m_objectPart[part].matWorld, eye);
    lookat = Math::Transform(m_objectPart[part].matWorld, lookat);

    // Camera tilts when turning.
    upVec = Math::Vector(0.0f, 1.0f, 0.0f);
    if ( m_physics != nullptr )
    {
        if ( m_physics->GetLand() )  // on ground?
        {
            speed = m_physics->GetLinMotionX(MO_REASPEED);
            lookat.y -= speed*0.002f;

            speed = m_physics->GetCirMotionY(MO_REASPEED);
            upVec.z -= speed*0.04f;
        }
        else    // in flight?
        {
            speed = m_physics->GetLinMotionX(MO_REASPEED);
            lookat.y += speed*0.002f;

            speed = m_physics->GetCirMotionY(MO_REASPEED);
            upVec.z += speed*0.08f;
        }
    }
    upVec = Math::Transform(m_objectPart[0].matRotate, upVec);

    dirH = -(m_objectPart[part].angle.y+Math::PI/2.0f);
    dirV = 0.0f;

}


// Management of features.

Character* COldObject::GetCharacter()
{
    return &m_character;
}


// Returns the absolute time.

float COldObject::GetAbsTime()
{
    return m_aTime;
}


float COldObject::GetCapacity()
{
    return m_type == OBJECT_ATOMIC ? m_main->GetGlobalNuclearCapacity() : m_main->GetGlobalCellCapacity() ;
}

bool COldObject::IsRechargeable()
{
    return m_type == OBJECT_POWER;
}


// Management of the shield.

void COldObject::SetShield(float level)
{
    if (level > 1.0f) level = 1.0f;
    if (level < 0.0f) level = 0.0f;
    m_shield = level;
}

float COldObject::GetShield()
{
    if (Implements(ObjectInterfaceType::Fragile))  return 0.0f;
    return m_shield;
}


// Management of flight range (zero = infinity).

void COldObject::SetRange(float delay)
{
    m_range = delay;
}

float COldObject::GetRange()
{
    return m_range;
}

void COldObject::SetReactorRange(float reactorRange)
{
    if (reactorRange > 1.0f) reactorRange = 1.0f;
    if (reactorRange < 0.0f) reactorRange = 0.0f;
    m_reactorRange = reactorRange;
}

float COldObject::GetReactorRange()
{
    return m_reactorRange;
}


// Management of transparency of the object.

void COldObject::SetTransparency(float value)
{
    int     i;

    for ( i=0 ; i<m_totalPart ; i++ )
    {
        if ( m_objectPart[i].bUsed )
        {
            if ( m_type == OBJECT_BASE )
            {
                if ( i != 9 )  continue;  // no central pillar?
            }

            m_engine->SetObjectTransparency(m_objectPart[i].object, value);
        }
    }
}


// Pushes an object.

bool COldObject::JostleObject(float force)
{
    if ( m_type == OBJECT_FLAGb ||
         m_type == OBJECT_FLAGr ||
         m_type == OBJECT_FLAGg ||
         m_type == OBJECT_FLAGy ||
         m_type == OBJECT_FLAGv )  // flag?
    {
        if ( m_auto == nullptr )  return false;

        m_auto->Start(1);
    }
    else
    {
        if ( m_auto != nullptr )  return false;

        auto autoJostle = MakeUnique<CAutoJostle>(this);
        autoJostle->Start(0, force);
        m_auto = std::move(autoJostle);
    }

    return true;
}



// Management of time from which a virus is active.

void COldObject::SetVirusMode(bool bEnable)
{
    m_bVirusMode = bEnable;
    m_virusTime = 0.0f;

    if ( m_bVirusMode && Implements(ObjectInterfaceType::Programmable) )
    {
        if ( !IntroduceVirus() )  // tries to infect
        {
            m_bVirusMode = false;  // program was not contaminated!
        }
    }
}

bool COldObject::GetVirusMode()
{
    return m_bVirusMode;
}


// Management mode of the camera.

void COldObject::SetCameraType(Gfx::CameraType type)
{
    m_cameraType = type;
}

Gfx::CameraType COldObject::GetCameraType()
{
    return m_cameraType;
}

void COldObject::SetCameraLock(bool lock)
{
    m_bCameraLock = lock;
}

bool COldObject::GetCameraLock()
{
    return m_bCameraLock;
}



// Management of the demonstration of the object.

void COldObject::SetHighlight(bool highlight)
{
    if (highlight)
    {
        int list[OBJECTMAXPART+1];

        int j = 0;
        for (int i = 0; i < m_totalPart; i++)
        {
            if ( m_objectPart[i].bUsed )
            {
                list[j++] = m_objectPart[i].object;
            }
        }
        list[j] = -1;  // terminate

        m_engine->SetHighlightRank(list);  // gives the list of selected parts
    }
}


// Indicates whether the object is selected or not.

void COldObject::SetSelect(bool select, bool bDisplayError)
{
    m_bSelect = select;

    // NOTE: Right now, Ui::CObjectInterface is only for programmable objects. Right now all selectable objects are programmable anyway.
    // TODO: All UI-related stuff should be moved out of CObject classes
    if (Implements(ObjectInterfaceType::Programmable))
    {
        if ( m_objectInterface == nullptr )
        {
            m_objectInterface = MakeUnique<Ui::CObjectInterface>(this);
        }
        m_objectInterface->CreateInterface(m_bSelect);
    }

    if ( m_auto != nullptr )
    {
        m_auto->CreateInterface(m_bSelect);
    }

    CreateSelectParticle();  // creates / removes particles

    if ( !m_bSelect )
        return;  // if not selected, we're done

    Error err = ERR_OK;

    if ( GetVirusMode() )
    {
        if (Implements(ObjectInterfaceType::ProgramStorage) && GetActiveVirus())
            err = ERR_VEH_VIRUS;
        else
            err = ERR_BAT_VIRUS;
    }

    if (HasPowerCellSlot(this))
    {
        CPowerContainerObject* power = GetObjectPowerCell(this);
        if (power == nullptr)
            err = ERR_VEH_POWER;
        else if ( power->GetEnergy() == 0.0f )
            err = ERR_VEH_ENERGY;
    }

    if ( err == ERR_OK && m_auto != nullptr )
    {
        err = m_auto->GetError();
    }
    if ( err != ERR_OK && bDisplayError )
    {
        m_main->DisplayError(err, this);
    }
}

// Indicates whether the object is selected or not.

bool COldObject::GetSelect()
{
    return m_bSelect;
}


// Indicates whether the object is selectable or not.

void COldObject::SetSelectable(bool bMode)
{
    m_bSelectable = bMode;
}

// Indicates whether the object is selecionnable or not.

bool COldObject::GetSelectable()
{
    return m_bSelectable;
}


// Indicates if necessary to check the tokens of the object.

void COldObject::SetCheckToken(bool bMode)
{
    m_bCheckToken = bMode;
}

// Indicates if necessary to check the tokens of the object.

bool COldObject::GetCheckToken()
{
    return m_bCheckToken;
}


// Sets if this object is underground or not. Underground objects are not detectable. Used by AlienWorm

void COldObject::SetUnderground(bool underground)
{
    m_underground = underground;
}


// Management of the method of increasing damage.

void COldObject::SetMagnifyDamage(float factor)
{
    m_magnifyDamage = factor;
}

float COldObject::GetMagnifyDamage()
{
    return m_magnifyDamage;
}

void COldObject::SetDamaging(bool damaging)
{
    m_damaging = damaging;
}

bool COldObject::IsDamaging()
{
    return m_damaging;
}

void COldObject::SetDying(DeathType deathType)
{
    m_dying = deathType;
    m_burnTime = 0.0f;

    if ( IsDying() && Implements(ObjectInterfaceType::Programmable) )
    {
        StopProgram();  // stops the current task
    }
}

DeathType COldObject::GetDying()
{
    return m_dying;
}

bool COldObject::IsDying()
{
    return m_dying != DeathType::Alive;
}

bool COldObject::GetActive()
{
    // Dying astronaut (m_dying == DeathType::Dead) should be treated as active
    // This is for EndMissionTake to not detect him as actually dead until the animation is finished

    return !GetLock() && !(Implements(ObjectInterfaceType::Destroyable) && IsDying() && GetDying() != DeathType::Dead) && !m_bFlat;
}

bool COldObject::GetDetectable()
{
    return GetActive() && !m_underground;
}


// Management of the point of aim.

void COldObject::SetGunGoalV(float gunGoal)
{
    auto aim = GetObjectTaskExecutorDetails(this).aim;
    if ( !aim.enabled ) return;

    if ( gunGoal < aim.minZ ) gunGoal = aim.minZ;
    if ( gunGoal > aim.maxZ ) gunGoal = aim.maxZ;
        
    if ( aim.partNum != -1 )
        SetPartRotationZ(aim.partNum, gunGoal);

    m_gunGoalV = gunGoal;
}

void COldObject::SetGunGoalH(float gunGoal)
{
    auto aim = GetObjectTaskExecutorDetails(this).aim;
    if ( !aim.enabled ) return;

    if ( gunGoal < aim.minY ) gunGoal = aim.minY;
    if ( gunGoal > aim.maxY ) gunGoal = aim.maxY;
        
    if ( aim.partNum != -1 )
        SetPartRotationY(aim.partNum, gunGoal);

    m_gunGoalH = gunGoal;
}

float COldObject::GetGunGoalV()
{
    return m_gunGoalV;
}

float COldObject::GetGunGoalH()
{
    return m_gunGoalH;
}

float COldObject::GetShowLimitRadius()
{
    return GetObjectRangedDetails(this).radius;
}


// Creates or removes particles associated to the object.

void COldObject::CreateSelectParticle()
{
    // Removes particles preceding.
    for ( int it: m_partiSel )
    {
        if ( it != -1 )
            m_particle->DeleteParticle(it);
    }
    m_partiSel.clear();

    if ( m_bSelect || IsProgram() || m_main->GetMissionType() == MISSION_RETRO )
    {
        // Creates particles lens for the headlights.
        auto lights = GetObjectControllableDetails(this).lights;
        for ( auto it: lights )
        {
            int particle = -1;
            if ( it.trainerMatcher == TRAINER_ANY || it.trainerMatcher == GetTrainer() )
            {
                particle = m_particle->CreateParticle(Math::Vector(), Math::Vector(), Math::Point(), it.color, 1.0f, 0.0f, 0.0f);
            }
            m_partiSel.push_back(particle);
        }
        if ( lights.size() )
            UpdateSelectParticle();
    }
}

// Updates the particles associated to the object.

void COldObject::UpdateSelectParticle()
{
    if ( !m_bSelect && !IsProgram() && m_main->GetMissionType() != MISSION_RETRO )  return;

    float angle = GetRotationY()/Math::PI;
    float zoom  = 1.0f;

    if ( ( IsProgram() ||  // current program?
         m_main->GetMissionType() == MISSION_RETRO ) && // Retro mode?
         Math::Mod(m_aTime, 0.7f) < 0.3f )
    {
        zoom = 0.0f;  // blinks
    }

    // Updates lens.
    auto lights = GetObjectControllableDetails(this).lights;
    for (unsigned int i = 0 ; i < m_partiSel.size() ; i++)
    {
        if (m_partiSel[i] == -1) continue;
        Math::Vector pos = Math::Transform(m_objectPart[lights[i].partNum].matWorld, lights[i].position);
        Math::Point dim  = Math::Point(lights[i].zoom, lights[i].zoom);
        m_particle->SetParam(m_partiSel[i], pos, dim, zoom, angle, 1.0f);
    }
}


// Returns the physics associated to the object.

CPhysics* COldObject::GetPhysics()
{
    return m_physics.get();
}

// Returns the movement associated to the object.

CMotion* COldObject::GetMotion()
{
    return m_motion.get();
}

void COldObject::SetMovable(std::unique_ptr<CMotion> motion, std::unique_ptr<CPhysics> physics)
{
    m_motion = std::move(motion);
    m_physics = std::move(physics);
}

// Returns the controller associated to the object.

CAuto* COldObject::GetAuto()
{
    return m_auto.get();
}

void COldObject::SetAuto(std::unique_ptr<CAuto> automat)
{
    m_auto = std::move(automat);
}


Math::Vector COldObject::GetPosition() const
{
    return GetPartPosition(0);
}

void COldObject::SetPosition(const Math::Vector& pos)
{
    SetPartPosition(0, pos);
}

Math::Vector COldObject::GetRotation() const
{
    return GetPartRotation(0);
}

void COldObject::SetRotation(const Math::Vector& rotation)
{
    SetPartRotation(0, rotation);
}

Math::Vector COldObject::GetScale() const
{
    return GetPartScale(0) / m_scaleFactor;
}

void COldObject::SetScale(const Math::Vector& scale)
{
    SetPartScale(0, scale * m_scaleFactor);
}

void COldObject::UpdateInterface()
{
    if (m_objectInterface != nullptr && GetSelect())
    {
        m_objectInterface->UpdateInterface();
    }

    CreateSelectParticle();
    m_main->UpdateShortcuts();
}

void COldObject::StopProgram()
{
    CProgrammableObjectImpl::StopProgram();

    //TODO: I don't want CProgrammableObjectImpl to depend on motion and physics, refactor this somehow
    if (Implements(ObjectInterfaceType::Movable))
    {
        m_physics->SetMotorSpeedX(0.0f);
        m_physics->SetMotorSpeedY(0.0f);
        m_physics->SetMotorSpeedZ(0.0f);

        if (m_type != OBJECT_HUMAN) // Be sure not to stop the death animation!
        {
            m_motion->SetAction(-1);
        }
    }
}

// State management of the pencil drawing robot.

bool COldObject::GetTraceDown()
{
    return m_traceDown;
}

void COldObject::SetTraceDown(bool down)
{
    m_traceDown = down;
}

TraceColor COldObject::GetTraceColor()
{
    return m_traceColor;
}

void COldObject::SetTraceColor(TraceColor color)
{
    m_traceColor = color;
}

float COldObject::GetTraceWidth()
{
    return m_traceWidth;
}

void COldObject::SetTraceWidth(float width)
{
    m_traceWidth = width;
}

bool COldObject::IsRepairable()
{
    auto shielded = GetObjectShieldedDetails(this);
    return shielded.enabled && shielded.repairable;
}

float COldObject::GetShieldFullRegenTime()
{
    auto shielded_auto_regen = GetObjectShieldedAutoRegenDetails(this);
    assert(shielded_auto_regen.enabled);
    return shielded_auto_regen.time;
}

float COldObject::GetLightningHitProbability()
{
    auto damageable = GetObjectDamageableDetails(this);
    return damageable.lightning.lightningHitProbability;
}

bool COldObject::IsSelectableByDefault()
{
    auto controllable = GetObjectControllableDetails(this);
    return controllable.selectable;
}

void COldObject::SetBulletWall(bool bulletWall)
{
    m_bulletWall = bulletWall;
}

bool COldObject::IsBulletWall()
{
    return m_bulletWall;
}

bool COldObject::IsBulletWallByDefault(ObjectType type)
{
    if ( type == OBJECT_BARRICADE0 ||
         type == OBJECT_BARRICADE1 )
    {
        return true;
    }
    return false;
}

void COldObject::SetFixed(bool fixed)
{
    m_fixed = fixed;
}

bool COldObject::GetFixed()
{
    return m_fixed;
}

void COldObject::SetShieldRadius(float shieldRadius)
{
    m_shieldRadius = shieldRadius;
}

float COldObject::GetShieldRadius()
{
    return m_shieldRadius;
}

float COldObject::GetActiveShieldRadius()
{
    if (IsBackgroundTask())
    {
        CTaskShield* taskShield = dynamic_cast<CTaskShield*>(GetBackgroundTask());
        if (taskShield != nullptr)
        {
            return taskShield->GetActiveRadius();
        }
    }
    return 0.0f;
}
