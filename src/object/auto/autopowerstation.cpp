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


#include "object/auto/autopowerstation.h"

#include "graphics/engine/engine.h"
#include "graphics/engine/particle.h"
#include "graphics/engine/terrain.h"

#include "math/geometry.h"

#include "object/object.h"
#include "object/object_manager.h"

#include "object/details/details_provider.h"
#include "object/details/automated_details.h"

#include "object/helpers/cargo_helpers.h"
#include "object/helpers/power_helpers.h"

#include "sound/sound.h"

// Object's constructor.

CAutoPowerStation::CAutoPowerStation(CObject* object) : CAuto(object)
{
    assert(object->Implements(ObjectInterfaceType::PowerContainer));
    Init();
}

// Object's destructor.

CAutoPowerStation::~CAutoPowerStation()
{
}


// Destroys the object.

void CAutoPowerStation::DeleteObject(bool bAll)
{
    if ( m_soundChannel != -1 )
    {
        m_sound->Stop(m_soundChannel);
        m_soundChannel = -1;
    }

    CAuto::DeleteObject(bAll);
}


// Initialize the object.

void CAutoPowerStation::Init()
{
    m_time = 0.0f;
    m_timeVirus = 0.0f;
    m_lastUpdateTime = 0.0f;
    m_lastParticle = 0.0f;
    m_soundChannel = -1;
    m_bLastVirus = false;

    CAuto::Init();
}


// Management of an event.

bool CAutoPowerStation::EventProcess(const Event &event)
{
    CAuto::EventProcess(event);

    if ( m_engine->GetPause() )  return true;
    if ( event.type != EVENT_FRAME )  return true;

    m_timeVirus -= event.rTime;

    if ( m_object->GetVirusMode() )  // contaminated by a virus?
    {
        if ( !m_bLastVirus )
        {
            m_bLastVirus = true;
            m_energyVirus = GetObjectEnergyLevel(m_object);
        }

        if ( m_timeVirus <= 0.0f )
        {
            m_timeVirus = 0.1f+Math::Rand()*0.3f;

            SetObjectEnergyLevel(m_object, Math::Rand());
        }
        return true;
    }
    else
    {
        if ( m_bLastVirus )
        {
            m_bLastVirus = false;
            SetObjectEnergyLevel(m_object, m_energyVirus);
        }
    }

    UpdateInterface(event.rTime);

    Gfx::TerrainRes res = m_terrain->GetResource(m_object->GetPosition());
    if ( res == Gfx::TR_POWER )
    {
        float energy = event.rTime*0.01f;
        ChargeObjectEnergy(m_object, energy);  // recharges the large battery
    }

    bool used = false;
    float freq = 1.0f;
    if (GetObjectEnergy(m_object) > 0.0f)
    {
        if (CObject* vehicle = SearchVehicle())
        {
            for (int slot = GetNumSlots(vehicle) - 1; slot >= 0; slot--)
            {
                CObject *power = GetObjectInSlot(vehicle, slot);
                if (power != nullptr && power->Implements(ObjectInterfaceType::PowerContainer))
                {
                    float before = GetObjectEnergy(power);

                    float add = event.rTime*0.2f;
                    float max = GetObjectEnergy(m_object)*4.0;
                    if ( add > max )  add = max;
                    ChargeObjectEnergy(power, add);  // Charging the battery

                    float energy = GetObjectEnergy(power);
                    if ( energy < freq )  freq = energy;

                    float delta = (energy - before)/4.0;
                    DecreaseObjectEnergy(m_object, delta);  // discharge the large battery
                    used = used || (delta != 0);
                }
            }
        }
    }

    if ( freq < 1.0f )  // charging in progress?
    {
        freq = 1.0f+3.0f*freq;
        if ( m_soundChannel == -1 )
        {
            m_soundChannel = m_sound->Play(SOUND_STATION, m_object->GetPosition(),
                                           0.3f, freq, true);
        }
        m_sound->Frequency(m_soundChannel, freq);
    }
    else
    {
        if ( m_soundChannel != -1 )
        {
            m_sound->Stop(m_soundChannel);
            m_soundChannel = -1;
        }
    }

    if ( used && m_lastParticle+m_engine->ParticleAdapt(0.05f) <= m_time )
    {
        m_lastParticle = m_time;

        glm::vec3    pos, ppos, speed;
        glm::vec2     dim;

        glm::mat4 mat = m_object->GetWorldMatrix(0);
        pos = glm::vec3(-15.0f, 7.0f, 0.0f);  // battery position
        pos = Math::Transform(mat, pos);
        speed.x = (Math::Rand()-0.5f)*20.0f;
        speed.y = (Math::Rand()-0.5f)*20.0f;
        speed.z = (Math::Rand()-0.5f)*20.0f;
        ppos.x = pos.x;
        ppos.y = pos.y+(Math::Rand()-0.5f)*4.0f;
        ppos.z = pos.z;
        dim.x = 1.5f;
        dim.y = 1.5f;
        m_particle->CreateParticle(ppos, speed, dim, Gfx::PARTIBLITZ, 1.0f, 0.0f, 0.0f);

        ppos = pos;
        ppos.y += 1.0f;
        ppos.x += (Math::Rand()-0.5f)*3.0f;
        ppos.z += (Math::Rand()-0.5f)*3.0f;
        speed.x = 0.0f;
        speed.z = 0.0f;
        speed.y = 2.5f+Math::Rand()*5.0f;
        dim.x = Math::Rand()*1.0f+0.6f;
        dim.y = dim.x;
        m_particle->CreateParticle(ppos, speed, dim, Gfx::PARTIVAPOR, 3.0f);
    }

    return true;
}


// Seeking the vehicle on the station.

CObject* CAutoPowerStation::SearchVehicle()
{
    glm::vec3 sPos = m_object->GetPosition();

    for (CObject* obj : CObjectManager::GetInstancePointer()->GetAllObjects())
    {
        auto targeted = GetObjectAutomatedDetails(obj).targeted;
        if (!targeted.chargedByPowerStation) continue;

        glm::vec3 oPos = obj->GetPosition();
        float dist = glm::distance(oPos, sPos);
        if ( dist <= 5.0f )  return obj;
    }

    return nullptr;
}


// Returns an error due the state of the automated.

Error CAutoPowerStation::GetError()
{
    Gfx::TerrainRes  res;
    res = m_terrain->GetResource(m_object->GetPosition());
    if ( res != Gfx::TR_POWER )  return ERR_STATION_NULL;

    return ERR_OK;
}
