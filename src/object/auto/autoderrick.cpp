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


#include "object/auto/autoderrick.h"

#include "graphics/engine/engine.h"
#include "graphics/engine/terrain.h"

#include "level/robotmain.h"

#include "level/parser/parserline.h"
#include "level/parser/parserparam.h"

#include "math/geometry.h"

#include "object/object.h"
#include "object/object_manager.h"

#include "object/details/details_provider.h"
#include "object/details/automated_details.h"

#include "object/helpers/modeled_helpers.h"

#include "sound/sound.h"

#include "ui/controls/interface.h"
#include "ui/controls/window.h"

#include "ui/displaytext.h"

// Object's constructor.

CAutoDerrick::CAutoDerrick(CObject* object) : CAuto(object)
{
    Init();
    m_phase = ADP_WAIT;  // paused until the first Init ()
    m_soundChannel = -1;
}

// Object's destructor.

CAutoDerrick::~CAutoDerrick()
{
}


// Destroys the object.

void CAutoDerrick::DeleteObject(bool all)
{
    if ( !all )
    {
        CObject* cargo = SearchCargo();
        if ( cargo != nullptr && cargo->GetLock() )
        {
            CObjectManager::GetInstancePointer()->DeleteObject(cargo);
        }
    }

    if ( m_soundChannel != -1 )
    {
        m_sound->FlushEnvelope(m_soundChannel);
        m_sound->AddEnvelope(m_soundChannel, 0.0f, 1.0f, 1.0f, SOPER_STOP);
        m_soundChannel = -1;
    }

    CAuto::DeleteObject(all);
}


// Initialize the object.

void CAutoDerrick::Init()
{
    FindSomethingToDig();

    m_time = 0.0f;
    m_timeVirus = 0.0f;
    m_lastParticle = 0.0f;
    m_lastTrack = 0.0f;
}

void CAutoDerrick::FindSomethingToDig()
{
    auto digging = GetObjectAutomatedDetails(m_object).digging;

    Gfx::TerrainRes res = m_terrain->GetResource(m_object->GetPosition());

    std::vector<CObjectDiggingAutomated> matched;
    for ( auto it: digging.objects )
    {
        if (it.soil != Gfx::TR_ANY && it.soil != res)    continue;
        if (it.maxCount != -1)
        {
            size_t maxCount = static_cast<size_t>(it.maxCount);
            size_t count    = CObjectManager::GetInstancePointer()->RadarAll(nullptr, it.output).size();
            if ( count >= maxCount ) continue;
        }
        matched.push_back(it);
    }

    if ( matched.size() > 0 )
    {
        CObjectDiggingAutomated matchedFinal = matched[ std::rand() % matched.size() ];
        m_type        = matchedFinal.output;
        m_onCompleted = matchedFinal.message;

        m_typeTime    = matchedFinal.duration;

        m_phase    = ADP_EXCAVATE;
        m_progress = 0.0f;
        m_speed    = 1.0f/m_typeTime;
    }
    else
    {
        m_phase    = ADP_WAIT;
        m_progress = 0.0f;
        m_speed    = 1.0f/10.0f;
    }
}

glm::vec3 CAutoDerrick::GetCargoPos()
{
    auto digging = GetObjectAutomatedDetails(m_object).digging;
    glm::mat4 mat = m_object->GetWorldMatrix(digging.partNum);
    glm::vec3 pos = Math::Transform(mat, digging.position);
    m_terrain->AdjustToFloor(pos);
    return pos;
}

// Management of an event.

bool CAutoDerrick::EventProcess(const Event &event)
{
    CObject*    cargo;
    glm::vec3    pos, speed;
    glm::vec2     dim;
    float       angle, duration, factor;

    CAuto::EventProcess(event);

    if ( m_engine->GetPause() )  return true;
    if ( event.type != EVENT_FRAME )  return true;

    m_progress += event.rTime*m_speed;
    m_timeVirus -= event.rTime;

    if ( m_object->GetVirusMode() )  // contaminated by a virus?
    {
        if ( m_timeVirus <= 0.0f )
        {
            m_timeVirus = 0.1f+Math::Rand()*0.3f;

            pos.x = 0.0f;
            pos.z = 0.0f;
            pos.y = -2.0f*Math::Rand();
            SetPartPosition(m_object, 1, pos);  // up / down the drill

            SetPartRotationY(m_object, 1, Math::Rand()*0.5f);  // rotates the drill
        }
        return true;
    }

    if ( m_phase == ADP_WAIT )
    {
        if ( m_progress >= 1.0f )
        {
            FindSomethingToDig();
        }
    }

    if ( m_phase == ADP_EXCAVATE )
    {
        if ( m_soundChannel == -1 )
        {
            factor = m_typeTime;

            m_soundChannel = m_sound->Play(SOUND_DERRICK, m_object->GetPosition(), 1.0f, 0.5f, true);
            m_sound->AddEnvelope(m_soundChannel, 1.0f, 0.5f, 0.4f*factor, SOPER_CONTINUE);
            m_sound->AddEnvelope(m_soundChannel, 1.0f, 0.3f, 0.6f*factor, SOPER_CONTINUE);
            m_sound->AddEnvelope(m_soundChannel, 1.0f, 0.5f, 1.0f, SOPER_CONTINUE);
            m_sound->AddEnvelope(m_soundChannel, 1.0f, 0.5f, 4.0f, SOPER_STOP);
        }

        if ( m_progress >= 6.0f/16.0f &&  // penetrates into the ground?
             m_lastParticle+m_engine->ParticleAdapt(0.05f) <= m_time )
        {
            m_lastParticle = m_time;

            pos = m_object->GetPosition();
            speed.x = (Math::Rand()-0.5f)*10.0f;
            speed.z = (Math::Rand()-0.5f)*10.0f;
            speed.y = Math::Rand()*5.0f;
            dim.x = Math::Rand()*3.0f+2.0f;
            dim.y = dim.x;
            m_particle->CreateParticle(pos, speed, dim, Gfx::PARTICRASH, 2.0f);
        }

        if ( m_progress >= 6.0f/16.0f &&  // penetrates into the ground?
             m_lastTrack+m_engine->ParticleAdapt(0.5f) <= m_time )
        {
            m_lastTrack = m_time;

            pos = m_object->GetPosition();
            speed.x = (Math::Rand()-0.5f)*12.0f;
            speed.z = (Math::Rand()-0.5f)*12.0f;
            speed.y = Math::Rand()*10.0f+10.0f;
            dim.x = 0.6f;
            dim.y = dim.x;
            pos.y += dim.y;
            duration = Math::Rand()*2.0f+2.0f;
            m_particle->CreateTrack(pos, speed, dim, Gfx::PARTITRACK5,
                                     duration, Math::Rand()*10.0f+15.0f,
                                     duration*0.2f, 1.0f);
        }

        if ( m_progress < 1.0f )
        {
            pos.x = 0.0f;
            pos.z = 0.0f;
            pos.y = -m_progress*16.0f;
            SetPartPosition(m_object, 1, pos);  // down the drill

            angle = GetPartRotationY(m_object, 1);
            angle += event.rTime*8.0f;
            SetPartRotationY(m_object, 1, angle);  // rotates the drill
        }
        else
        {
            m_phase    = ADP_ASCEND;
            m_progress = 0.0f;
            m_speed    = 1.0f/5.0f;
        }
    }

    if ( m_phase == ADP_ASCEND )
    {
        if ( m_progress <= 7.0f/16.0f &&
             m_lastParticle+m_engine->ParticleAdapt(0.1f) <= m_time )
        {
            m_lastParticle = m_time;

            pos = m_object->GetPosition();
            speed.x = (Math::Rand()-0.5f)*10.0f;
            speed.z = (Math::Rand()-0.5f)*10.0f;
            speed.y = Math::Rand()*5.0f;
            dim.x = Math::Rand()*3.0f+2.0f;
            dim.y = dim.x;
            m_particle->CreateParticle(pos, speed, dim, Gfx::PARTICRASH, 2.0f);
        }

        if ( m_progress <= 4.0f/16.0f &&
             m_lastTrack+m_engine->ParticleAdapt(1.0f) <= m_time )
        {
            m_lastTrack = m_time;

            pos = m_object->GetPosition();
            speed.x = (Math::Rand()-0.5f)*12.0f;
            speed.z = (Math::Rand()-0.5f)*12.0f;
            speed.y = Math::Rand()*10.0f+10.0f;
            dim.x = 0.6f;
            dim.y = dim.x;
            pos.y += dim.y;
            duration = Math::Rand()*2.0f+2.0f;
            m_particle->CreateTrack(pos, speed, dim, Gfx::PARTITRACK5,
                                     duration, Math::Rand()*10.0f+15.0f,
                                     duration*0.2f, 1.0f);
        }

        if ( m_progress < 1.0f )
        {
            pos.x = 0.0f;
            pos.z = 0.0f;
            pos.y = -(1.0f-m_progress)*16.0f;
            SetPartPosition(m_object, 1, pos);  // back the drill

            angle = GetPartRotationY(m_object, 1);
            angle -= event.rTime*2.0f;
            SetPartRotationY(m_object, 1, angle);  // rotates the drill
        }
        else
        {
            m_soundChannel = -1;
            m_bSoundFall = false;

            m_phase    = ADP_EXPORT;
            m_progress = 0.0f;
            m_speed    = 1.0f/5.0f;
        }
    }

    if ( m_phase == ADP_ISFREE )
    {
        if ( m_progress >= 1.0f )
        {
            m_bSoundFall = false;

            m_phase    = ADP_EXPORT;
            m_progress = 0.0f;
            m_speed    = 1.0f/5.0f;
        }
    }

    if ( m_phase == ADP_EXPORT )
    {
        if ( m_progress == 0.0f )
        {
            glm::vec3 cargoPos = GetCargoPos();
            if ( SearchFree(cargoPos) )
            {
                angle = m_object->GetRotationY();
                if (m_type != OBJECT_NULL)
                    CreateCargo(cargoPos, angle, m_type, 16.0f);
            }
            else
            {
                m_phase    = ADP_ISFREE;
                m_progress = 0.0f;
                m_speed    = 1.0f/2.0f;
                return true;
            }
        }

        cargo = SearchCargo();

        if ( cargo != nullptr &&
             m_progress <= 0.5f &&
             m_lastParticle+m_engine->ParticleAdapt(0.1f) <= m_time )
        {
            m_lastParticle = m_time;

            if ( m_progress < 0.3f )
            {
                pos = cargo->GetPosition();
                pos.x += (Math::Rand()-0.5f)*5.0f;
                pos.z += (Math::Rand()-0.5f)*5.0f;
                pos.y += (Math::Rand()-0.5f)*5.0f;
                speed = glm::vec3(0.0f, 0.0f, 0.0f);
                dim.x = 3.0f;
                dim.y = dim.x;
                m_particle->CreateParticle(pos, speed, dim, Gfx::PARTIFIRE, 1.0f, 0.0f, 0.0f);
            }
            else
            {
                pos = cargo->GetPosition();
                pos.x += (Math::Rand()-0.5f)*5.0f;
                pos.z += (Math::Rand()-0.5f)*5.0f;
                pos.y += Math::Rand()*2.5f;
                speed = glm::vec3(0.0f, 0.0f, 0.0f);
                dim.x = 1.0f;
                dim.y = dim.x;
                m_particle->CreateParticle(pos, speed, dim, Gfx::PARTIGLINT, 2.0f, 0.0f, 0.0f);
            }
        }

        if ( m_progress < 1.0f )
        {
            if ( cargo != nullptr )
            {
                glm::vec3 cargoPos = GetCargoPos();
                pos = cargo->GetPosition();
                pos.y -= event.rTime*20.0f;  // grave
                if ( !m_bSoundFall && pos.y < cargoPos.y )
                {
                    m_sound->Play(SOUND_BOUM, cargoPos);
                    m_bSoundFall = true;
                }
                if ( pos.y < cargoPos.y )
                {
                    pos.y = cargoPos.y;
                    cargo->SetLock(false);  // object usable
                }
                cargo->SetPosition(pos);
            }
        }
        else
        {
            m_main->DisplayText(m_onCompleted, m_object, Ui::TT_INFO);
            FindSomethingToDig();
        }
    }

    return true;
}

// Saves all parameters of the controller.

bool CAutoDerrick::Write(CLevelParserLine* line)
{
    if ( m_phase == ADP_WAIT )  return false;

    line->AddParam("aExist", std::make_unique<CLevelParserParam>(true));
    CAuto::Write(line);
    line->AddParam("aPhase", std::make_unique<CLevelParserParam>(static_cast<int>(m_phase)));
    line->AddParam("aProgress", std::make_unique<CLevelParserParam>(m_progress));
    line->AddParam("aSpeed", std::make_unique<CLevelParserParam>(m_speed));
    line->AddParam("aTime", std::make_unique<CLevelParserParam>(m_typeTime));

    return true;
}

// Restores all parameters of the controller.

bool CAutoDerrick::Read(CLevelParserLine* line)
{
    if ( !line->GetParam("aExist")->AsBool(false) )  return false;

    CAuto::Read(line);
    m_phase = static_cast< AutoDerrickPhase >(line->GetParam("aPhase")->AsInt(ADP_WAIT));
    m_progress = line->GetParam("aProgress")->AsFloat(0.0f);
    m_speed = line->GetParam("aSpeed")->AsFloat(1.0f);
    m_typeTime = line->GetParam("aTime")->AsFloat(10.0f);

    m_lastParticle = 0.0f;

    return true;
}


// Seeks the subject cargo.

CObject* CAutoDerrick::SearchCargo()
{
    glm::vec3 cargoPos = GetCargoPos();
    for (CObject* obj : CObjectManager::GetInstancePointer()->GetAllObjects())
    {
        if (obj == m_object) continue;

        glm::vec3 oPos = obj->GetPosition();
        if ( oPos.x == cargoPos.x &&
             oPos.z == cargoPos.z )  return obj;
    }

    return nullptr;
}

// Seeks if a site is free.

bool CAutoDerrick::SearchFree(glm::vec3 pos)
{
    for (CObject* obj : CObjectManager::GetInstancePointer()->GetAllObjects())
    {
        if (obj == m_object) continue;

        for (const auto& crashSphere : obj->GetAllCrashSpheres())
        {
            glm::vec3 sPos = crashSphere.sphere.pos;
            float sRadius = crashSphere.sphere.radius;

            float distance = glm::distance(sPos, pos);
            distance -= sRadius;
            if ( distance < 2.0f )  return false;  // location occupied
        }
    }

    return true;  // location free
}

// Create a transportable object.

void CAutoDerrick::CreateCargo(glm::vec3 pos, float angle, ObjectType type,
                              float height)
{
    CObject* cargo = CObjectManager::GetInstancePointer()->CreateObject(pos, angle, type);
    cargo->SetLock(true);  // object not yet usable

    pos = cargo->GetPosition();
    pos.y += height;
    cargo->SetPosition(pos);
}

// returns an error due the state of the automaton.

Error CAutoDerrick::GetError()
{
    if ( m_phase == ADP_WAIT )
    {
        m_main->DisplayText(GetObjectAutomatedDetails(m_object).digging.noSoil, m_object, Ui::TT_WARNING);
    }
    return ERR_OK;
}
