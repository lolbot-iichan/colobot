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


#include "object/auto/autopowercaptor.h"

#include "graphics/engine/engine.h"
#include "graphics/engine/particle.h"

#include "level/parser/parserline.h"
#include "level/parser/parserparam.h"

#include "math/geometry.h"

#include "object/object.h"
#include "object/object_manager.h"

#include "object/helpers/cargo_helpers.h"
#include "object/helpers/power_helpers.h"

#include "sound/sound.h"

#include "ui/controls/interface.h"
#include "ui/controls/window.h"



// Object's constructor.

CAutoPowerCaptor::CAutoPowerCaptor(CObject* object) : CAuto(object)
{
    m_channelSound = -1;
    Init();
}

// Object's destructor.

CAutoPowerCaptor::~CAutoPowerCaptor()
{
}


// Destroys the object.

void CAutoPowerCaptor::DeleteObject(bool bAll)
{
    if ( m_channelSound != -1 )
    {
        m_sound->FlushEnvelope(m_channelSound);
        m_sound->AddEnvelope(m_channelSound, 0.0f, 1.0f, 1.0f, SOPER_STOP);
        m_channelSound = -1;
    }

    CAuto::DeleteObject(bAll);
}


// Initialize the object.

void CAutoPowerCaptor::Init()
{
    m_time = 0.0f;
    m_timeVirus = 0.0f;
    m_lastParticle = 0.0f;

    glm::mat4 mat = m_object->GetWorldMatrix(0);
    m_pos = Math::Transform(mat, glm::vec3(22.0f, 4.0f, 0.0f));

    m_phase    = APAP_WAIT;  // waiting ...
    m_progress = 0.0f;
    m_speed    = 1.0f/1.0f;

    CAuto::Init();
}


// Reception of lightning.

void CAutoPowerCaptor::StartLightning()
{
    m_phase    = APAP_LIGHTNING;
    m_progress = 0.0f;
    m_speed    = 1.0f/2.0f;
}


// Management of an event.

bool CAutoPowerCaptor::EventProcess(const Event &event)
{
    glm::vec3    pos, speed;
    glm::vec2     dim;
    int         i;

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

    if ( m_phase == APAP_LIGHTNING )
    {
        if ( m_progress < 1.0f )
        {
            if ( m_lastParticle+m_engine->ParticleAdapt(0.05f) <= m_time )
            {
                m_lastParticle = m_time;

                for ( i=0 ; i<10 ; i++ )
                {
                    pos = m_object->GetPosition();
                    pos.x += (Math::Rand()-0.5f)*m_progress*40.0f;
                    pos.z += (Math::Rand()-0.5f)*m_progress*40.0f;
                    pos.y += 50.0f-m_progress*50.0f;
                    speed.x = (Math::Rand()-0.5f)*20.0f;
                    speed.z = (Math::Rand()-0.5f)*20.0f;
                    speed.y = 5.0f+Math::Rand()*5.0f;
                    dim.x = 2.0f;
                    dim.y = dim.x;
                    m_particle->CreateParticle(pos, speed, dim, Gfx::PARTIBLITZ, 1.0f, 20.0f, 0.5f);
                }
            }
        }
        else
        {
            m_phase    = APAP_CHARGE;
            m_progress = 0.0f;
            m_speed    = 1.0f/2.0f;
        }
    }

    if ( m_phase == APAP_CHARGE )
    {
        if ( m_progress < 1.0f )
        {
            if ( m_lastParticle+m_engine->ParticleAdapt(0.05f) <= m_time )
            {
                m_lastParticle = m_time;

                for ( i=0 ; i<2 ; i++ )
                {
                    pos = m_object->GetPosition();
                    pos.y += 16.0f;
                    speed.x = (Math::Rand()-0.5f)*10.0f;
                    speed.z = (Math::Rand()-0.5f)*10.0f;
                    speed.y = -Math::Rand()*30.0f;
                    dim.x = 1.0f;
                    dim.y = dim.x;
                    m_particle->CreateParticle(pos, speed, dim, Gfx::PARTIBLITZ, 1.0f, 0.0f, 0.0f);
                }
            }

            ChargeObject(event.rTime);
        }
        else
        {
            m_phase    = APAP_WAIT;
            m_progress = 0.0f;
            m_speed    = 1.0f/1.0f;
        }
    }

    return true;
}

// Load all objects under the lightning rod.

void CAutoPowerCaptor::ChargeObject(float rTime)
{
    glm::vec3 sPos = m_object->GetPosition();

    for (CObject* obj : CObjectManager::GetInstancePointer()->GetAllObjects())
    {
        glm::vec3 oPos = obj->GetPosition();
        float dist = glm::distance(oPos, sPos);
        if ( dist > 20.0f )  continue;

        if (! IsObjectBeingTransported(obj) && obj->Implements(ObjectInterfaceType::PowerContainer) )
        {
            float energy = rTime/2.0f;
            ChargeObjectEnergy(obj, energy);
        }

        for (int slot = GetNumSlots(obj) - 1; slot >= 0; slot--)
        {
            CObject *held = GetObjectInSlot(obj, slot);
            if (held != nullptr && held->Implements(ObjectInterfaceType::PowerContainer))
            {
                float energy = rTime/2.0f;
                ChargeObjectEnergy(held, energy);
            }
        }
    }
}


// Saves all parameters of the controller.

bool CAutoPowerCaptor::Write(CLevelParserLine* line)
{
    if ( m_phase == APAP_WAIT )  return false;

    line->AddParam("aExist", std::make_unique<CLevelParserParam>(true));
    CAuto::Write(line);
    line->AddParam("aPhase", std::make_unique<CLevelParserParam>(static_cast<int>(m_phase)));
    line->AddParam("aProgress", std::make_unique<CLevelParserParam>(m_progress));
    line->AddParam("aSpeed", std::make_unique<CLevelParserParam>(m_speed));

    return true;
}

// Restores all parameters of the controller.

bool CAutoPowerCaptor::Read(CLevelParserLine* line)
{
    if ( !line->GetParam("aExist")->AsBool(false) )  return false;

    CAuto::Read(line);
    m_phase = static_cast< AutoPowerCaptorPhase >(line->GetParam("aPhase")->AsInt(APAP_WAIT));
    m_progress = line->GetParam("aProgress")->AsFloat(0.0f);
    m_speed = line->GetParam("aSpeed")->AsFloat(1.0f);

    m_lastParticle = 0.0f;

    return true;
}
