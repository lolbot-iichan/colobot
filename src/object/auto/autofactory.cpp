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


#include "object/auto/autofactory.h"

#include "graphics/engine/engine.h"

#include "level/robotmain.h"

#include "level/parser/parserline.h"
#include "level/parser/parserparam.h"
#include "level/parser/path_inject.h"

#include "math/geometry.h"

#include "object/object.h"
#include "object/object_create_params.h"
#include "object/object_manager.h"

#include "object/details/details_provider.h"
#include "object/details/automated_details.h"
#include "object/details/controllable_details.h"

#include "object/helpers/cargo_helpers.h"
#include "object/helpers/common_helpers.h"
#include "object/helpers/modeled_helpers.h"

#include "object/interface/movable_object.h"
#include "object/interface/program_storage_object.h"
#include "object/interface/programmable_object.h"

#include "physics/physics.h"

#include "script/script.h"

#include "sound/sound.h"

#include "ui/controls/button.h"
#include "ui/controls/interface.h"
#include "ui/controls/window.h"


#include <boost/regex.hpp>

#include <libintl.h>


// Object's constructor.

CAutoFactory::CAutoFactory(CObject* object) : CAuto(object)
{
    Init();
    m_phase = AFP_WAIT;  // paused until the first Init ()
    m_channelSound = -1;

    m_partNum     = 0;
    m_position    = {2.0f, 0.0f, 0.0f};
    m_rotateTweak = false;
}

// Object's destructor.

CAutoFactory::~CAutoFactory()
{
}


// Destroys the object.

void CAutoFactory::DeleteObject(bool all)
{
    if ( !all )
    {
        CObject* cargo = SearchCargo();  // transform metal?
        if ( cargo != nullptr )
        {
            CObjectManager::GetInstancePointer()->DeleteObject(cargo);
        }

        CObject* vehicle = SearchVehicle();
        if ( vehicle != nullptr )
        {
            CObjectManager::GetInstancePointer()->DeleteObject(vehicle);
        }
    }

    if ( m_channelSound != -1 )
    {
        m_sound->FlushEnvelope(m_channelSound);
        m_sound->AddEnvelope(m_channelSound, 0.0f, 1.0f, 1.0f, SOPER_STOP);
        m_channelSound = -1;
    }

    CAuto::DeleteObject(all);
}


// Initialize the object.

void CAutoFactory::Init()
{
    m_phase    = AFP_WAIT;
    m_progress = 0.0f;
    m_speed    = 1.0f/2.0f;

    m_time = 0.0f;
    m_lastParticle = 0.0f;

    m_cargoPos = m_object->GetPosition();

    m_program = "";

    CAuto::Init();
}


// Starts an action

Error CAutoFactory::StartAction(int param)
{
    CObject*   cargo;
    ObjectType type = static_cast<ObjectType>(param);

    if ( type != OBJECT_NULL )
    {
        if ( m_phase != AFP_WAIT )
        {
            return ERR_OBJ_BUSY;
        }

        Error err = CanFactoryError(type, m_object->GetTeam());
        if ( err != ERR_OK )
        {
            return err;
        }

        m_type = type;

        cargo = SearchCargo();  // transform metal?
        if ( cargo == nullptr )
        {
            return ERR_FACTORY_NULL;
        }
        if ( NearestVehicle() )
        {
            return ERR_FACTORY_NEAR;
        }

        m_program = "";
        SetBusy(true);
        InitProgressTotal(3.0f+2.0f+15.0f+2.0f+3.0f);
        UpdateInterface();

        cargo->SetLock(true);  // usable metal
        SoundManip(3.0f, 1.0f, 0.5f);

        m_phase    = AFP_CLOSE_S;
        m_progress = 0.0f;
        m_speed    = 1.0f/3.0f;
        return ERR_OK;
    }
    return ERR_UNKNOWN;
}


// Sets program for created robot

void CAutoFactory::SetProgram(const std::string& program)
{
    m_program = program;
}

// Management of an event.

bool CAutoFactory::EventProcess(const Event &event)
{
    CObject*    cargo;
    CObject*    vehicle;
    glm::mat4   mat;
    CPhysics*   physics;
    glm::vec3   pos, speed;
    glm::vec2   dim;
    float       zoom, angle, prog;
    int         i;

    CAuto::EventProcess(event);

    if ( m_engine->GetPause() )  return true;

    if ( IsObjectSelected(m_object) )  // factory selected?
    {
        if ( event.type == EVENT_UPDINTERFACE )
        {
            CreateInterface(true);
        }

        auto buildObjects = GetObjectControllableDetails(m_object).controls.build;
        size_t len = EVENT_OBJECT_FACTORY_MAX - EVENT_OBJECT_FACTORY_01 + 1;
        len = buildObjects.size() > len ? len : buildObjects.size();

        int i = event.type - EVENT_OBJECT_FACTORY_01;
        if ( i >= 0 && i < len )
        {
            Error err = StartAction(buildObjects[i].output);
            if( err != ERR_OK && err != ERR_UNKNOWN )
                m_main->DisplayError(err, m_object);
    
            if( err != ERR_UNKNOWN )
                return false;
        }
    }

    if ( event.type != EVENT_FRAME )  return true;

    m_progress += event.rTime*m_speed;
    EventProgress(event.rTime);

    if ( m_phase == AFP_WAIT )
    {
        if ( m_progress >= 1.0f )
        {
            m_phase    = AFP_WAIT;  // still waiting ...
            m_progress = 0.0f;
            m_speed    = 1.0f/2.0f;
        }
    }

    if ( m_phase == AFP_CLOSE_S )
    {
        if ( m_progress < 1.0f )
        {
            for ( i=0 ; i<9 ; i++ )
            {
                zoom = 0.30f+(m_progress-0.5f+i/16.0f)*2.0f*0.70f;
                if ( zoom < 0.30f )  zoom = 0.30f;
                if ( zoom > 1.00f )  zoom = 1.00f;
                SetPartScaleZ(m_object,  1+i, zoom);
                SetPartScaleZ(m_object, 10+i, zoom);
            }
        }
        else
        {
            for ( i=0 ; i<9 ; i++ )
            {
                SetPartScaleZ(m_object,  1+i, 1.0f);
                SetPartScaleZ(m_object, 10+i, 1.0f);
            }

            SoundManip(2.0f, 1.0f, 1.2f);

            m_phase    = AFP_CLOSE_T;
            m_progress = 0.0f;
            m_speed    = 1.0f/2.0f;
        }
    }

    if ( m_phase == AFP_CLOSE_T )
    {
        if ( m_progress < 1.0f )
        {
            for ( i=0 ; i<9 ; i++ )
            {
                angle = -m_progress*(Math::PI/2.0f)+Math::PI/2.0f;
                SetPartRotationZ(m_object,  1+i,  angle);
                SetPartRotationZ(m_object, 10+i, -angle);
            }
        }
        else
        {
            for ( i=0 ; i<9 ; i++ )
            {
                SetPartRotationZ(m_object,  1+i, 0.0f);
                SetPartRotationZ(m_object, 10+i, 0.0f);
            }

            m_channelSound = m_sound->Play(SOUND_FACTORY, m_object->GetPosition(), 0.0f, 1.0f, true);
            m_sound->AddEnvelope(m_channelSound, 1.0f, 1.0f,  2.0f, SOPER_CONTINUE);
            m_sound->AddEnvelope(m_channelSound, 1.0f, 1.0f, 11.0f, SOPER_CONTINUE);
            m_sound->AddEnvelope(m_channelSound, 0.0f, 1.0f,  2.0f, SOPER_STOP);

            m_phase    = AFP_BUILD;
            m_progress = 0.0f;
            m_speed    = 1.0f/15.0f;
        }
    }

    if ( m_phase == AFP_BUILD )
    {
        if ( m_progress == 0.0f )
        {
            if ( !CreateVehicle() )
            {
                cargo = SearchCargo();  // transform metal?
                if ( cargo != nullptr )
                {
                    cargo->SetLock(false);  // metal usable again
                }

                if ( m_channelSound != -1 )
                {
                    m_sound->FlushEnvelope(m_channelSound);
                    m_sound->AddEnvelope(m_channelSound, 0.0f, 1.0f, 1.0f, SOPER_STOP);
                    m_channelSound = -1;
                }

                m_phase    = AFP_OPEN_T;
                m_progress = 0.0f;
                m_speed    = 1.0f/2.0f;
                return true;
            }
        }

        if ( m_progress < 1.0f )
        {
            cargo = SearchCargo();  // transform metal?
            if ( cargo != nullptr )
            {
                cargo->SetScale(1.0f-m_progress);
            }

            // TODO: Why do we even need this?
            if ( m_rotateTweak )
            {
                prog = 1.0f-m_progress*1.5f;
                if ( prog < 0.0f )  prog = 0.0f;
            }
            else
            {
                prog = 1.0f-m_progress;
            }
            angle = powf(prog*10.0f, 2.0f)+m_object->GetRotationY();

            vehicle = SearchVehicle();
            if ( vehicle != nullptr )
            {
                vehicle->SetRotationY(angle+Math::PI);
                vehicle->SetScale(m_progress);
            }

            if ( m_lastParticle+m_engine->ParticleAdapt(0.05f) <= m_time )
            {
                m_lastParticle = m_time;

                mat = m_object->GetWorldMatrix(0);
                pos = glm::vec3(-12.0f, 20.0f, -4.0f);  // position of chimney
                pos = Math::Transform(mat, pos);
                pos.y += 2.0f;
                pos.x += (Math::Rand()-0.5f)*2.0f;
                pos.z += (Math::Rand()-0.5f)*2.0f;
                speed.x = 0.0f;
                speed.z = 0.0f;
                speed.y = 6.0f+Math::Rand()*6.0f;
                dim.x = Math::Rand()*1.5f+1.0f;
                dim.y = dim.x;
                m_particle->CreateParticle(pos, speed, dim, Gfx::PARTISMOKE3, 4.0f);
            }
        }
        else
        {
            m_main->DisplayText(m_onCompleted, m_object, Ui::TT_INFO);
            SoundManip(2.0f, 1.0f, 1.2f);

            cargo = SearchCargo();  // transform metal?
            if ( cargo != nullptr )
            {
                CObjectManager::GetInstancePointer()->DeleteObject(cargo);
            }

            vehicle = SearchVehicle();
            if ( vehicle != nullptr )
            {
                assert(vehicle->Implements(ObjectInterfaceType::Movable));
                physics = dynamic_cast<CMovableObject&>(*vehicle).GetPhysics();
                physics->SetFreeze(false);  // can move

                vehicle->SetLock(false);  // vehicle useable
                vehicle->SetRotationY(m_object->GetRotationY()+Math::PI);
                vehicle->SetScale(1.0f);

                if ( !m_program.empty() )
                {
                    if (vehicle->Implements(ObjectInterfaceType::Programmable) && vehicle->Implements(ObjectInterfaceType::ProgramStorage))
                    {
                        Program* program = dynamic_cast<CProgramStorageObject&>(*vehicle).AddProgram();

                        if (boost::regex_match(m_program, boost::regex("[A-Za-z0-9_]+"))) // Public function name?
                        {
                            std::string code = "extern void object::Start_"+m_program+"()\n{\n\t\n\t//Automatically generated by object.factory()\n\t"+m_program+"();\n\t\n}\n";
                            program->script->SendScript(code.c_str());
                        }
                        else if (boost::regex_match(m_program, boost::regex(".*\\.txt"))) // File name (with .txt extension)?
                        {
                            program->script->ReadScript(m_program.c_str());
                        }
                        else // Program code?
                        {
                            program->script->SendScript(m_program.c_str());
                        }

                        dynamic_cast<CProgrammableObject&>(*vehicle).RunProgram(program);
                    }
                }
            }

            m_main->CreateShortcuts();

            m_phase    = AFP_OPEN_T;
            m_progress = 0.0f;
            m_speed    = 1.0f/2.0f;
        }
    }

    if ( m_phase == AFP_OPEN_T )
    {
        if ( m_progress < 1.0f )
        {
            for ( i=0 ; i<9 ; i++ )
            {
                angle = -(1.0f-m_progress)*(Math::PI/2.0f)+Math::PI/2.0f;
                SetPartRotationZ(m_object,  1+i,  angle);
                SetPartRotationZ(m_object, 10+i, -angle);
            }

            if ( m_lastParticle+m_engine->ParticleAdapt(0.1f) <= m_time )
            {
                m_lastParticle = m_time;

                pos = m_cargoPos;
                pos.x += (Math::Rand()-0.5f)*10.0f;
                pos.z += (Math::Rand()-0.5f)*10.0f;
                pos.y += Math::Rand()*10.0f;
                speed = glm::vec3(0.0f, 0.0f, 0.0f);
                dim.x = 2.0f;
                dim.y = dim.x;
                m_particle->CreateParticle(pos, speed, dim, Gfx::PARTIGLINT, 2.0f, 0.0f, 0.0f);
            }
        }
        else
        {
            for ( i=0 ; i<9 ; i++ )
            {
                SetPartRotationZ(m_object,  1+i,  Math::PI/2.0f);
                SetPartRotationZ(m_object, 10+i, -Math::PI/2.0f);
            }

            SoundManip(3.0f, 1.0f, 0.5f);

            m_phase    = AFP_OPEN_S;
            m_progress = 0.0f;
            m_speed    = 1.0f/3.0f;
        }
    }

    if ( m_phase == AFP_OPEN_S )
    {
        if ( m_progress < 1.0f )
        {
            for ( i=0 ; i<9 ; i++ )
            {
                zoom = 0.30f+((1.0f-m_progress)-0.5f+i/16.0f)*2.0f*0.70f;
                if ( zoom < 0.30f )  zoom = 0.30f;
                if ( zoom > 1.00f )  zoom = 1.00f;
                SetPartScaleZ(m_object,  1+i, zoom);
                SetPartScaleZ(m_object, 10+i, zoom);
            }

            if ( m_lastParticle+m_engine->ParticleAdapt(0.1f) <= m_time )
            {
                m_lastParticle = m_time;

                pos = m_cargoPos;
                pos.x += (Math::Rand()-0.5f)*10.0f;
                pos.z += (Math::Rand()-0.5f)*10.0f;
                pos.y += Math::Rand()*10.0f;
                speed = glm::vec3(0.0f, 0.0f, 0.0f);
                dim.x = 2.0f;
                dim.y = dim.x;
                m_particle->CreateParticle(pos, speed, dim, Gfx::PARTIGLINT, 2.0f, 0.0f, 0.0f);
            }
        }
        else
        {
            for ( i=0 ; i<9 ; i++ )
            {
                SetPartScaleZ(m_object,  1+i, 0.30f);
                SetPartScaleZ(m_object, 10+i, 0.30f);
            }

            SetBusy(false);
            UpdateInterface();

            m_phase    = AFP_WAIT;
            m_progress = 0.0f;
            m_speed    = 1.0f/2.0f;
        }
    }

    return true;
}


// Saves all parameters of the controller.

bool CAutoFactory::Write(CLevelParserLine* line)
{
    if ( m_phase == AFP_WAIT )  return false;

    line->AddParam("aExist", std::make_unique<CLevelParserParam>(true));
    CAuto::Write(line);
    line->AddParam("aPhase", std::make_unique<CLevelParserParam>(static_cast<int>(m_phase)));
    line->AddParam("aProgress", std::make_unique<CLevelParserParam>(m_progress));
    line->AddParam("aSpeed", std::make_unique<CLevelParserParam>(m_speed));

    return true;
}

// Restores all parameters of the controller

bool CAutoFactory::Read(CLevelParserLine* line)
{
    if ( !line->GetParam("aExist")->AsBool(false) )  return false;

    CAuto::Read(line);
    m_phase = static_cast< AutoFactoryPhase >(line->GetParam("aPhase")->AsInt(AFP_WAIT));
    m_progress = line->GetParam("aProgress")->AsFloat(0.0f);
    m_speed = line->GetParam("aSpeed")->AsFloat(1.0f);

    m_lastParticle = 0.0f;
    m_cargoPos = m_object->GetPosition();

    return true;
}


//Seeks the cargo.

CObject* CAutoFactory::SearchCargo()
{
    ObjectType input = OBJECT_NULL;

    auto factoryObjects = GetObjectAutomatedDetails(m_object).factory.objects;
    for (size_t i = 0; i < factoryObjects.size(); i++ )
    {
        if ( m_type == factoryObjects[i].output )
        {
            input = factoryObjects[i].input;
            m_onCompleted = factoryObjects[i].message;
            m_partNum     = factoryObjects[i].partNum;
            m_position    = factoryObjects[i].position;
            m_rotateTweak = factoryObjects[i].rotateTweak;
        }
    }
    
    for (CObject* obj : CObjectManager::GetInstancePointer()->GetAllObjects())
    {
        if ( obj->GetType() != input )  continue;
        if ( IsObjectBeingTransported(obj) )  continue;
        if ( glm::distance(obj->GetPosition(), m_cargoPos) >= 8.0f )  continue;

        return obj;
    }

    return nullptr;
}

// Search if a vehicle is too close.

bool CAutoFactory::NearestVehicle()
{
    glm::vec3 cPos = m_object->GetPosition();

    for (CObject* obj : CObjectManager::GetInstancePointer()->GetAllObjects())
    {
        auto blocking = GetObjectAutomatedDetails(obj).blocking;
        if (!blocking.blocksFactory) continue;

        if (obj->GetCrashSphereCount() == 0) continue;

        auto crashSphere = obj->GetFirstCrashSphere();
        if (Math::DistanceToSphere(cPos, crashSphere.sphere) < 10.0f)
            return true;
    }

    return false;
}


// Creates a vehicle.

bool CAutoFactory::CreateVehicle()
{
    float angle = m_object->GetRotationY();

    glm::vec3 pos = m_position;
    glm::mat4 mat = m_object->GetWorldMatrix(m_partNum);
    pos = Math::Transform(mat, pos);

    ObjectCreateParams params;
    params.pos = pos;
    params.angle = angle;
    params.type = m_type;
    params.team = m_object->GetTeam();
    params.trainer = IsObjectTrainer(m_object);
    CObject* vehicle = CObjectManager::GetInstancePointer()->CreateObject(params);

    vehicle->SetLock(true);  // not usable

    assert(vehicle->Implements(ObjectInterfaceType::Movable));
    CPhysics* physics = dynamic_cast<CMovableObject&>(*vehicle).GetPhysics();
    physics->SetFreeze(true);  // it doesn't move

    if (vehicle->Implements(ObjectInterfaceType::ProgramStorage))
    {
        CProgramStorageObject* programStorage = dynamic_cast<CProgramStorageObject*>(vehicle);
        for (const std::string& name : m_main->GetNewScriptNames(m_type))
        {
            Program* prog = programStorage->AddProgram();
            programStorage->ReadProgram(prog, InjectLevelPathsForCurrentLevel(name, "ai"));
            prog->readOnly = true;
            prog->filename = name;
        }
    }

    return true;
}

// Seeking the vehicle during manufacture.

CObject* CAutoFactory::SearchVehicle()
{
    for (CObject* obj : CObjectManager::GetInstancePointer()->GetAllObjects())
    {
        if ( !obj->GetLock() )  continue;

        ObjectType  type = obj->GetType();
        if ( type != m_type )  continue;
        if (IsObjectBeingTransported(obj))  continue;

        glm::vec3 oPos = obj->GetPosition();
        float dist = glm::distance(oPos, m_cargoPos);

        if ( dist < 8.0f )  return obj;
    }

    return nullptr;
}

// Creates all the interface when the object is selected.

bool CAutoFactory::CreateInterface(bool bSelect)
{
    Ui::CWindow*    pw;
    glm::vec2     pos, dim, ddim;
    float       ox, oy, sx, sy;

    CAuto::CreateInterface(bSelect);

    if ( !bSelect )  return true;

    pw = static_cast< Ui::CWindow* >(m_interface->SearchControl(EVENT_WINDOW0));
    if ( pw == nullptr )  return false;

    dim.x = 33.0f/640.0f;
    dim.y = 33.0f/480.0f;
    ox = 3.0f/640.0f;
    oy = 3.0f/480.0f;
    sx = 33.0f/640.0f;
    sy = 33.0f/480.0f;
    if( !IsObjectTrainer(m_object) )
    {
        pos.x = 0.0f;
        pos.y = oy+sy*2.6f;
        ddim.x = 138.0f/640.0f;
        ddim.y = 258.0f/480.0f;
        pw->CreateGroup(pos, ddim, 6, EVENT_WINDOW3);

        auto buildObjects = GetObjectControllableDetails(m_object).controls.build;
        size_t len = EVENT_OBJECT_FACTORY_MAX - EVENT_OBJECT_FACTORY_01 + 1;
        len = buildObjects.size() > len ? len : buildObjects.size();

        for (size_t i = 0; i < len; i++)
        {
            pos.x = ox + sx*(i%4);
            pos.y = oy + sy*(9.3f - (i/4)*1.1f);
            EventType e = static_cast<EventType>(EVENT_OBJECT_FACTORY_01 + i);

            Ui::CButton* pb = pw->CreateButton(pos, dim, buildObjects[i].icon, e);
            if ( buildObjects[i].text.size() )
                pb->SetTooltip(gettext(buildObjects[i].text.c_str())); // TODO: gettext in separate file
        }
    }

    UpdateInterface();
    return true;
}

// Updates the status of all interface buttons.

void CAutoFactory::UpdateInterface()
{
    Ui::CWindow*    pw;

    if ( IsObjectSelected(m_object) )  return;

    CAuto::UpdateInterface();

    pw = static_cast< Ui::CWindow* >(m_interface->SearchControl(EVENT_WINDOW0));

    auto buildObjects = GetObjectControllableDetails(m_object).controls.build;
    size_t len = EVENT_OBJECT_FACTORY_MAX - EVENT_OBJECT_FACTORY_01 + 1;
    len = buildObjects.size() > len ? len : buildObjects.size();

    for (size_t i = 0; i < len; i++ )
    {
        EventType e = static_cast<EventType>(EVENT_OBJECT_FACTORY_01 + i);
        EnableInterface(pw, e, !m_bBusy);
        Error canFactory = CanFactoryError(buildObjects[i].output, m_object->GetTeam());
        DeadInterface(pw, e, canFactory == ERR_OK);
    }
}

// Plays the sound of the manipulator arm.

void CAutoFactory::SoundManip(float time, float amplitude, float frequency)
{
    int i = m_sound->Play(SOUND_MANIP, m_object->GetPosition(), 0.0f, 0.3f*frequency, true);
    m_sound->AddEnvelope(i, 0.5f*amplitude, 1.0f*frequency, 0.1f, SOPER_CONTINUE);
    m_sound->AddEnvelope(i, 0.5f*amplitude, 1.0f*frequency, time-0.1f, SOPER_CONTINUE);
    m_sound->AddEnvelope(i, 0.0f, 0.3f*frequency, 0.1f, SOPER_STOP);
}

Error CAutoFactory::CanFactoryError(ObjectType type, int team)
{
    auto factoryObjects = GetObjectAutomatedDetails(m_object).factory.objects;
    for (size_t i = 0; i < factoryObjects.size(); i++ )
    {
        if ( type != factoryObjects[i].output )  continue;

        return m_main->IsResearchesDone(factoryObjects[i].researches, team) ? ERR_OK : ERR_WRONG_OBJ;
    }

    return ERR_WRONG_OBJ;
}
