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


#include "object/auto/autotower.h"

#include "graphics/engine/engine.h"

#include "level/robotmain.h"

#include "level/parser/parserline.h"
#include "level/parser/parserparam.h"

#include "math/geometry.h"

#include "object/object.h"
#include "object/object_manager.h"

#include "object/details/details_provider.h"
#include "object/details/automated_details.h"

#include "object/helpers/modeled_helpers.h"
#include "object/helpers/power_helpers.h"

#include "sound/sound.h"

const float TOWER_SCOPE     = 200.0f;   // range of beam
const float ENERGY_FIRE     = 0.125f;   // energy consumed by fire


// Object's constructor.

CAutoTower::CAutoTower(CObject* object) : CAuto(object)
{
    for (int i = 0; i < 4; i++)
    {
        m_partiStop[i] = -1;
    }

    Init();
    m_phase = ATP_WAIT;  // paused until the first Init ()
    m_time = 0.0f;
    m_lastUpdateTime = 0.0f;
}

// Object's destructor.

CAutoTower::~CAutoTower()
{
}


// Destroys the object.

void CAutoTower::DeleteObject(bool bAll)
{
    FireStopUpdate(0.0f, false);
    CAuto::DeleteObject(bAll);
}


// Initialize the object.

void CAutoTower::Init()
{
    m_phase    = ATP_ZERO;
    m_progress = 0.0f;
    m_speed    = 1.0f/1.0f;

    m_time = 0.0f;
    m_timeVirus = 0.0f;
    m_lastUpdateTime = 0.0f;
    m_lastParticle = 0.0f;
}


// Management of an event.

bool CAutoTower::EventProcess(const Event &event)
{
    CObject*    target;
    glm::vec3    pos;
    float       angle, quick;

    CAuto::EventProcess(event);

    if ( m_engine->GetPause() )  return true;
    if ( event.type != EVENT_FRAME )  return true;

    m_timeVirus -= event.rTime;

    if ( m_object->GetVirusMode() )  // contaminated by a virus?
    {
        if ( m_timeVirus <= 0.0f )
        {
            m_timeVirus = 0.1f+Math::Rand()*0.3f;

            angle = GetPartRotationY(m_object, 1);
            angle += Math::Rand()*0.5f;
            SetPartRotationY(m_object, 1, angle);

            SetPartRotationZ(m_object, 2, Math::Rand()*0.5f);
        }
        return true;
    }

    float energy = GetObjectEnergy(m_object);

    UpdateInterface(event.rTime);

    if ( m_phase == ATP_WAIT )  return true;

    m_progress += event.rTime*m_speed;

    if ( m_phase == ATP_ZERO )
    {
        FireStopUpdate(m_progress, true);  // blinks
        if ( m_progress < 1.0f )
        {
            if ( energy >= ENERGY_FIRE )
            {
                m_phase    = ATP_SEARCH;
                m_progress = 0.0f;
                m_speed    = 1.0f/3.0f;
            }
        }
        else
        {
            m_phase    = ATP_ZERO;
            m_progress = 0.0f;
            m_speed    = 1.0f/1.0f;
        }
    }

    if ( m_phase == ATP_SEARCH )
    {
        FireStopUpdate(m_progress, false);  // extinguished
        if ( m_progress < 1.0f )
        {
            quick = 1.0f;

            angle = GetPartRotationY(m_object, 1);
            angle -= event.rTime*quick*2.0f;
            SetPartRotationY(m_object, 1, angle);

            angle = GetPartRotationZ(m_object, 2);
            angle += event.rTime*quick*0.5f;
            if ( angle > 0.0f )  angle = 0.0f;
            SetPartRotationZ(m_object, 2, angle);
        }
        else
        {
            target = SearchTarget(m_targetPos);
            if ( energy < ENERGY_FIRE )
            {
                m_main->DisplayError(ERR_TOWER_ENERGY, m_object);
            }
            if ( target == nullptr || energy < ENERGY_FIRE )
            {
                m_phase    = ATP_ZERO;
                m_progress = 0.0f;
                m_speed    = 1.0f/1.0f;
            }
            else
            {
                pos = m_object->GetPosition();
                pos.y += 24.5f;
                m_angleYfinal = Math::RotateAngle(m_targetPos.x-pos.x, pos.z-m_targetPos.z);  // CW !
                m_angleYfinal += Math::PI*2.0f;
                m_angleYfinal -= m_object->GetRotationY();
                m_angleYactual = Math::NormAngle(GetPartRotationY(m_object, 1));

                m_angleZfinal = -Math::PI/2.0f;
                m_angleZfinal -= Math::RotateAngle(Math::DistanceProjected(m_targetPos, pos), pos.y-m_targetPos.y);  // CW !
                m_angleZactual = GetPartRotationZ(m_object, 2);

                m_phase    = ATP_TURN;
                m_progress = 0.0f;
                m_speed    = 1.0f/1.0f;
            }
        }
    }

    if ( m_phase == ATP_TURN )
    {
        if ( m_progress < 1.0f )
        {
            angle = m_angleYactual+(m_angleYfinal-m_angleYactual)*m_progress;
            SetPartRotationY(m_object, 1, angle);

            angle = m_angleZactual+(m_angleZfinal-m_angleZactual)*m_progress;
            SetPartRotationZ(m_object, 2, angle);
        }
        else
        {
            SetPartRotationY(m_object, 1, m_angleYfinal);
            SetPartRotationZ(m_object, 2, m_angleZfinal);

            float energy = ENERGY_FIRE;
            DecreaseObjectEnergy(m_object, energy);

            m_sound->Play(SOUND_GGG, m_object->GetPosition());

            m_phase    = ATP_FIRE;
            m_progress = 0.0f;
            m_speed    = 1.0f/1.5f;
        }
    }

    if ( m_phase == ATP_FIRE )
    {
        if ( m_progress == 0.0f )
        {
            pos = m_object->GetPosition();
            pos.y += 24.5f;
            m_particle->CreateRay(pos, m_targetPos, Gfx::PARTIRAY1,
                { 5.0f, 5.0f }, 1.5f);
        }
        if ( m_progress >= 1.0f )
        {
            m_phase    = ATP_ZERO;
            m_progress = 0.0f;
            m_speed    = 1.0f/1.0f;
        }
    }

    return true;
}


// Seeks the nearest target object.

CObject* CAutoTower::SearchTarget(glm::vec3 &impact)
{
    glm::vec3 iPos = m_object->GetPosition();
    float min = 1000000.0f;

    CObject* best = nullptr;
    for (CObject* obj : CObjectManager::GetInstancePointer()->GetAllObjects())
    {
        int oTeam=obj->GetTeam();
        int myTeam=m_object->GetTeam();

        // TODO: Maybe should not attack everything from other teams? You can easily discharge tower by using immune units...
        
        auto targeted = GetObjectAutomatedDetails(obj).targeted; 
        if (!targeted.attackedByTower && (oTeam == myTeam || oTeam == 0))  continue;

        if ( !obj->GetDetectable() )  continue;  // inactive?

        if (obj->GetCrashSphereCount() == 0) continue;

        glm::vec3 oPos = obj->GetFirstCrashSphere().sphere.pos;
        float distance = glm::distance(oPos, iPos);
        if ( distance > TOWER_SCOPE )  continue;  // too far
        if ( distance < min )
        {
            min = distance; best = obj;
        }
    }
    if ( best == nullptr )  return nullptr;

    impact = best->GetPosition();
    return best;
}


// Returns an error due the state of the automated.

Error CAutoTower::GetError()
{
    if (GetObjectEnergyLevel(m_object) < ENERGY_FIRE )
    {
        return ERR_TOWER_ENERGY;  // not enough energy
    }

    return ERR_OK;
}


// Updates the stop lights.

void CAutoTower::FireStopUpdate(float progress, bool bLightOn)
{
    glm::vec3    pos, speed;
    glm::vec2     dim;
    int         i;

    static float listpos[8] =
    {
         4.5f,   0.0f,
         0.0f,   4.5f,
        -4.5f,   0.0f,
         0.0f,  -4.5f,
    };

    if ( !bLightOn )  // extinguished?
    {
        for ( i=0 ; i<4 ; i++ )
        {
            if ( m_partiStop[i] != -1 )
            {
                m_particle->DeleteParticle(m_partiStop[i]);
                m_partiStop[i] = -1;
            }
        }
        return;
    }

    glm::mat4 mat = m_object->GetWorldMatrix(0);

    speed = glm::vec3(0.0f, 0.0f, 0.0f);
    dim.x = 2.0f;
    dim.y = dim.x;

    for ( i=0 ; i<4 ; i++ )
    {
        if ( Math::Mod(progress+i*0.125f, 0.5f) < 0.2f )
        {
            if ( m_partiStop[i] != -1 )
            {
                m_particle->DeleteParticle(m_partiStop[i]);
                m_partiStop[i] = -1;
            }
        }
        else
        {
            if ( m_partiStop[i] == -1 )
            {
                pos.x = listpos[i*2+0];
                pos.y = 18.0f;
                pos.z = listpos[i*2+1];
                pos = Math::Transform(mat, pos);

                m_partiStop[i] = m_particle->CreateParticle(pos, speed,
                                                              dim, Gfx::PARTISELR,
                                                              1.0f, 0.0f, 0.0f);
            }
        }
    }
}

// Saves all parameters of the controller.

bool CAutoTower::Write(CLevelParserLine* line)
{
    if ( m_phase == ATP_WAIT )  return false;

    line->AddParam("aExist", std::make_unique<CLevelParserParam>(true));
    CAuto::Write(line);
    line->AddParam("aPhase", std::make_unique<CLevelParserParam>(static_cast<int>(m_phase)));
    line->AddParam("aProgress", std::make_unique<CLevelParserParam>(m_progress));
    line->AddParam("aSpeed", std::make_unique<CLevelParserParam>(m_speed));
    line->AddParam("aTargetPos", std::make_unique<CLevelParserParam>(m_targetPos));
    line->AddParam("aAngleYactual", std::make_unique<CLevelParserParam>(m_angleYactual));
    line->AddParam("aAngleZactual", std::make_unique<CLevelParserParam>(m_angleZactual));
    line->AddParam("aAngleYfinal", std::make_unique<CLevelParserParam>(m_angleYfinal));
    line->AddParam("aAngleZfinal", std::make_unique<CLevelParserParam>(m_angleZfinal));

    return true;
}

// Restores all parameters of the controller.

bool CAutoTower::Read(CLevelParserLine* line)
{
    if ( !line->GetParam("aExist")->AsBool(false) )  return false;

    CAuto::Read(line);
    m_phase = static_cast< AutoTowerPhase >(line->GetParam("aPhase")->AsInt(ATP_WAIT));
    m_progress = line->GetParam("aProgress")->AsFloat(0.0f);
    m_speed = line->GetParam("aSpeed")->AsFloat(1.0f);
    m_targetPos = line->GetParam("aTargetPos")->AsPoint(glm::vec3(0.0f, 0.0f, 0.0f));
    m_angleYactual = line->GetParam("aAngleYactual")->AsFloat(0.0f);
    m_angleZactual = line->GetParam("aAngleZactual")->AsFloat(0.0f);
    m_angleYfinal = line->GetParam("aAngleYfinal")->AsFloat(0.0f);
    m_angleZfinal = line->GetParam("aAngleZfinal")->AsFloat(0.0f);

    m_lastUpdateTime = 0.0f;

    return true;
}
