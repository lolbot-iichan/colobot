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


#include "object/auto/autovault.h"

#include "graphics/engine/engine.h"

#include "level/robotmain.h"

#include "level/parser/parserline.h"
#include "level/parser/parserparam.h"

#include "math/geometry.h"

#include "object/object.h"
#include "object/object_manager.h"

#include "object/details/details_provider.h"
#include "object/details/automated_details.h"

#include "object/helpers/cargo_helpers.h"
#include "object/helpers/modeled_helpers.h"

#include "object/interface/slotted_object.h"

#include "sound/sound.h"

#include "ui/controls/interface.h"
#include "ui/controls/window.h"


const float OPEN_DELAY  = 8.0f; // duration of opening


// Object's constructor.

CAutoVault::CAutoVault(CObject* object) : CAuto(object)
{
    m_bLock = false;
    m_lastParticle = 0.0f;
    m_channelSound = -1;
    Init();

    assert( GetNumSlots(object) == GetObjectAutomatedDetails(m_object).vault.keys.size() );
}

// Object's destructor.

CAutoVault::~CAutoVault()
{
}


// Destroys the object.

void CAutoVault::DeleteObject(bool bAll)
{
    CObject* obj = SearchVehicle();
    if ( obj != nullptr )
    {
        CObjectManager::GetInstancePointer()->DeleteObject(obj);
    }

    if ( m_channelSound != -1 )
    {
        m_sound->FlushEnvelope(m_channelSound);
        m_sound->AddEnvelope(m_channelSound, 0.0f, 1.0f, 1.0f, SOPER_STOP);
        m_channelSound = -1;
    }

    CAuto::DeleteObject(bAll);
}


// Initialize the object.

void CAutoVault::Init()
{
    m_time = 0.0f;
    m_timeVirus = 0.0f;
    m_lastParticle = 0.0f;

    m_countKeys   = 0;

    m_phase    = ASAP_WAIT;  // waiting ...
    m_progress = 0.0f;
    m_speed    = 1.0f/1.0f;

    CAuto::Init();
}


// Management of an event.

bool CAutoVault::EventProcess(const Event &event)
{
    CObject*    pObj;
    glm::vec3   pos, speed;
    glm::vec2     dim;
    int         i, count;

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
        }
        return true;
    }

    EventProgress(event.rTime);

    if ( !m_bLock && CRobotMain::GetInstancePointer()->GetGameTime() < 1.0f )
    {
        pObj = SearchVehicle();
        if ( pObj != nullptr )
        {
            pObj->SetLock(true);  // object not yet usable
            m_main->CreateShortcuts();
            m_bLock = true;
        }
    }

    if ( m_phase == ASAP_WAIT )
    {
        if ( m_progress >= 1.0f )
        {
            count = CountKeys();  // count these key
            if ( count != m_countKeys )
            {
                m_countKeys = count;

                int totalKeys = GetObjectAutomatedDetails(m_object).vault.keys.size();
                if ( count == totalKeys )  // all the keys?
                {
                    LockKeys();

                    m_channelSound = m_sound->Play(SOUND_MANIP, m_object->GetPosition(), 1.0f, 0.25f, true);
                    m_sound->AddEnvelope(m_channelSound, 1.0f, 2.00f, OPEN_DELAY, SOPER_STOP);

                    m_phase    = ASAP_OPEN;
                    m_progress = 0.0f;
                    m_speed    = 1.0f/OPEN_DELAY;
                    return true;
                }
                else
                {
                    m_channelSound = m_sound->Play(SOUND_MANIP, m_object->GetPosition(), 1.0f, 0.25f, true);
                    m_sound->AddEnvelope(m_channelSound, 1.0f, 0.35f, 0.5f, SOPER_STOP);
                }
            }

            m_phase    = ASAP_WAIT;
            m_progress = 0.0f;
            m_speed    = 1.0f/1.0f;
        }
    }

    if ( m_phase == ASAP_OPEN )
    {
        if ( m_progress < 1.0f )
        {
            DownKeys(m_progress);

            if ( m_lastParticle+m_engine->ParticleAdapt(0.05f) <= m_time )
            {
                m_lastParticle = m_time;

                for ( i=0 ; i<10 ; i++ )
                {
                    pos = m_object->GetPosition();
                    pos.x += (Math::Rand()-0.5f)*10.0f;
                    pos.z += (Math::Rand()-0.5f)*10.0f;
                    speed.x = (Math::Rand()-0.5f)*4.0f;
                    speed.z = (Math::Rand()-0.5f)*4.0f;
                    speed.y = Math::Rand()*15.0f;
                    dim.x = Math::Rand()*6.0f+4.0f;
                    dim.y = dim.x;
                    m_particle->CreateParticle(pos, speed, dim, Gfx::PARTIBLUE, 1.0f, 0.0f, 0.0f);
                }

                pos = m_object->GetPosition();
                pos.x += (Math::Rand()-0.5f)*10.0f;
                pos.z += (Math::Rand()-0.5f)*10.0f;
                speed.x = (Math::Rand()-0.5f)*4.0f;
                speed.z = (Math::Rand()-0.5f)*4.0f;
                speed.y = Math::Rand()*10.0f;
                dim.x = Math::Rand()*3.0f+2.0f;
                dim.y = dim.x;
                m_particle->CreateParticle(pos, speed, dim, Gfx::PARTIGLINT, 1.0f, 0.0f, 0.0f);

                for ( auto & key : m_keyInfo )
                {
                    speed.x = (Math::Rand()-0.5f)*2.0f;
                    speed.z = (Math::Rand()-0.5f)*2.0f;
                    speed.y = 1.0f+Math::Rand()*1.0f;
                    dim.x = Math::Rand()*1.5f+1.5f;
                    dim.y = dim.x;
//TODO                    m_particle->CreateParticle(key.position, speed, dim, Gfx::PARTISMOKE3, 4.0f, 0.0f, 0.0f);
                }
            }
        }
        else
        {
            DeleteKeys();

            pObj = SearchVehicle();
            if ( pObj != nullptr )
            {
                pObj->SetLock(false);  // object usable
                m_main->CreateShortcuts();
            }

            m_object->DeleteAllCrashSpheres();
            m_object->SetCameraCollisionSphere(Math::Sphere(glm::vec3(0.0f, 0.0f, 0.0f), 0.0f));

            m_sound->Play(SOUND_FINDING, m_object->GetPosition());

            m_phase    = ASAP_FINISH;
            m_progress = 0.0f;
            m_speed    = 1.0f/100.0f;
        }
    }

    if ( m_phase == ASAP_FINISH )
    {
        if ( m_progress >= 1.0f )
        {
            m_phase    = ASAP_FINISH;
            m_progress = 0.0f;
            m_speed    = 1.0f/100.0f;
        }
    }

    // Opens or closes the doors.
    for ( auto it : GetObjectAutomatedDetails(m_object).vault.doors )
    {
        int partNum  = it.partNum;
        if ( it.needKeys != m_countKeys ) continue;

        auto newVal = [](float value, float target, float delta)
        {
            if (value < target)
                return Math::Min(value + delta, target);
            else
                return Math::Max(value - delta, target);
        };

        float dPos  = 30.0f*event.rTime/OPEN_DELAY;
        glm::vec3 newPos = { newVal( GetPartPosition(m_object, partNum).x, it.position.x, dPos),
                             newVal( GetPartPosition(m_object, partNum).y, it.position.y, dPos),
                             newVal( GetPartPosition(m_object, partNum).z, it.position.z, dPos)};
        SetPartPosition(m_object,  partNum, newPos );

        float dAngle  = (105.0f*Math::PI/180.0f)*event.rTime/OPEN_DELAY;
        glm::vec3 newRot = { newVal( GetPartRotation(m_object, partNum).x, it.rotation.x, dAngle),
                             newVal( GetPartRotation(m_object, partNum).y, it.rotation.y, dAngle),
                             newVal( GetPartRotation(m_object, partNum).z, it.rotation.z, dAngle)};
        SetPartRotation(m_object,  partNum, newRot );
    }

    // Blinks the keys.
    speed = glm::vec3(0.0f, 0.0f, 0.0f);
    dim.x = 2.0f;
    dim.y = dim.x;

    for ( auto & key : m_keyInfo )
    {
        if ( m_phase != ASAP_WAIT || !key.isPlaced || Math::Mod(m_time, 1.0f) < 0.4f )
        {
            m_particle->DeleteParticle(key.particleId);
            key.particleId = -1;
        }
        else
        {
            if ( key.particleId != -1 ) continue;

            pos = key.position;
            pos.y += 2.2f;
            key.particleId = m_particle->CreateParticle(pos, speed, dim, Gfx::PARTISELY, 1.0f, 0.0f, 0.0f);
        }
    }

    return true;
}

// Saves all parameters of the controller.

bool CAutoVault::Write(CLevelParserLine* line)
{
    if ( m_phase == ASAP_WAIT )  return false;

    line->AddParam("aExist", std::make_unique<CLevelParserParam>(true));
    CAuto::Write(line);
    line->AddParam("aPhase", std::make_unique<CLevelParserParam>(static_cast<int>(m_phase)));
    line->AddParam("aProgress", std::make_unique<CLevelParserParam>(m_progress));
    line->AddParam("aSpeed", std::make_unique<CLevelParserParam>(m_speed));

    return true;
}

// Restores all parameters of the controller.

bool CAutoVault::Read(CLevelParserLine* line)
{
    if ( !line->GetParam("aExist")->AsBool(false) )  return false;

    CAuto::Read(line);
    m_phase = static_cast< AutoVaultPhase >(line->GetParam("aPhase")->AsInt(ASAP_WAIT));
    m_progress = line->GetParam("aProgress")->AsFloat(0.0f);
    m_speed = line->GetParam("aSpeed")->AsFloat(1.0f);

    m_lastParticle = 0.0f;

    return true;
}

// Counts the number of keys

int CAutoVault::CountKeys()
{
    int result = 0;

    m_keyInfo.resize( GetObjectAutomatedDetails(m_object).vault.keys.size() );

    int index = 0;
    for (auto it : GetObjectAutomatedDetails(m_object).vault.keys)
    {
        CObject* obj = GetObjectInSlot(m_object, it.slotNum);
        bool placed = obj && obj->GetType() == it.input;

        glm::mat4 mat = m_object->GetWorldMatrix(0);
        m_keyInfo[index].position = Math::Transform(mat, dynamic_cast<CSlottedObject*>(m_object)->GetSlotPosition(it.slotNum));
        m_keyInfo[index].isPlaced = placed;
        index ++;

        if ( placed ) result ++;
    }

    return result;
}

// Blocks all keys.

void CAutoVault::LockKeys()
{
    for (auto it : GetObjectAutomatedDetails(m_object).vault.keys)
    {
        CObject* obj = GetObjectInSlot(m_object, it.slotNum);
        bool placed = obj && obj->GetType() == it.input;

        if ( placed )
        {
            obj->SetLock(true);
        }
    }
}

// Sent down all the keys.

void CAutoVault::DownKeys(float progress)
{
    for (auto it : GetObjectAutomatedDetails(m_object).vault.keys)
    {
        CObject* obj = GetObjectInSlot(m_object, it.slotNum);
        bool placed = obj && obj->GetType() == it.input;

        if ( placed )
        {
            glm::vec3 oPos = obj->GetPosition();
            oPos.y = -progress*2.2f;
            obj->SetPosition(oPos);
        }
    }
}

// Delete all the keys.

void CAutoVault::DeleteKeys()
{
    for (auto it : GetObjectAutomatedDetails(m_object).vault.keys)
    {
        CObject* obj = GetObjectInSlot(m_object, it.slotNum);
        bool placed = obj && obj->GetType() == it.input;

        if ( placed )
        {
            CObjectManager::GetInstancePointer()->DeleteObjectInSlot(m_object, it.slotNum);
        }
    }
}

// Seeking a vehicle in the safe.

CObject* CAutoVault::SearchVehicle()
{
    glm::vec3 cPos = m_object->GetPosition();

    for (CObject* obj : CObjectManager::GetInstancePointer()->GetAllObjects())
    {
        if ( obj == m_object )  continue;
        if (IsObjectBeingTransported(obj))  continue;

        glm::vec3 oPos = obj->GetPosition();
        float dist = Math::DistanceProjected(oPos, cPos);
        if ( dist <= 4.0f )  return obj;
    }
    return nullptr;
}
