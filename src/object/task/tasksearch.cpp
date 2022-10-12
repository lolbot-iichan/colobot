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


#include "object/task/tasksearch.h"

#include "graphics/engine/particle.h"
#include "graphics/engine/terrain.h"

#include "level/robotmain.h"

#include "math/geometry.h"

#include "object/object_manager.h"
#include "object/old_object.h"

#include "object/details/task_executor_details.h"

#include "physics/physics.h"

#include "sound/sound.h"


// Object's constructor.

CTaskSearch::CTaskSearch(COldObject* object) : CForegroundTask(object)
{
    m_hand = TSH_UP;
}

// Object's destructor.

CTaskSearch::~CTaskSearch()
{
}


// Management of an event.

bool CTaskSearch::EventProcess(const Event &event)
{
    Math::Matrix*   mat;
    Math::Vector    pos, speed;
    Math::Point     dim;
    float       angle;
    int         i;

    if ( m_engine->GetPause() )  return true;
    if ( event.type != EVENT_FRAME )  return true;
    if ( m_bError )  return false;

    m_progress += event.rTime*m_speed;  // others advance
    m_time += event.rTime;

    if ( m_phase == TSP_DOWN ||
         m_phase == TSP_UP   )
    {
        auto sniff = GetObjectTaskExecutorDetails(m_object).sniff;
        if (sniff.execution == ExecutionAsSniffer)
        {
            for ( i=0 ; i<3 ; i++ )
            {
                angle = (m_finalAngle[i]-m_initialAngle[i])*m_progress;
                angle += m_initialAngle[i];
                m_object->SetPartRotationZ(i+1, angle);
            }
        }
    }

    if ( m_phase == TSP_SEARCH &&
         m_lastParticle+m_engine->ParticleAdapt(0.05f) <= m_time )
    {
        m_lastParticle = m_time;

        mat = m_object->GetWorldMatrix(0);
        pos = Math::Vector(6.5f, 0.2f, 0.0f);
        pos = Math::Transform(*mat, pos);  // sensor position

        speed.x = (Math::Rand()-0.5f)*20.0f;
        speed.z = (Math::Rand()-0.5f)*20.0f;
        speed.y = 0.0f;
        dim.x = Math::Rand()*1.0f+1.0f;
        dim.y = dim.x;
        m_particle->CreateParticle(pos, speed, dim, Gfx::PARTIGAS);
    }

    return true;
}


// Initializes the initial and final angles.

void CTaskSearch::InitAngle()
{
    int     i;

    if ( m_hand == TSH_UP )
    {
        m_finalAngle[0] =  110.0f*Math::PI/180.0f;  // arm
        m_finalAngle[1] = -110.0f*Math::PI/180.0f;  // forearm
        m_finalAngle[2] =  -65.0f*Math::PI/180.0f;  // sensor
    }
    if ( m_hand == TSH_DOWN )
    {
        m_finalAngle[0] =   25.0f*Math::PI/180.0f;  // arm
        m_finalAngle[1] =  -70.0f*Math::PI/180.0f;  // forearm
        m_finalAngle[2] =  -45.0f*Math::PI/180.0f;  // sensor
    }

    for ( i=0 ; i<3 ; i++ )
    {
        m_initialAngle[i] = m_object->GetPartRotationZ(i+1);
    }
}


// Assigns the goal was achieved.

Error CTaskSearch::Start()
{
    Math::Vector    speed;
    int         i;

    m_bError = true;

    auto sniff = GetObjectTaskExecutorDetails(m_object).sniff;
    if ( sniff.execution != ExecutionNoMotion &&
         sniff.execution != ExecutionAsSniffer )
    {
        return ERR_WRONG_BOT;
    }

    if (m_object->Implements(ObjectInterfaceType::Movable))
    {
        if ( !m_physics->GetLand() )  return ERR_SEARCH_FLY;
    
        speed = m_physics->GetMotorSpeed();
        if ( speed.x != 0.0f ||
             speed.z != 0.0f )  return ERR_SEARCH_MOTOR;
    }

    m_hand     = TSH_DOWN;
    m_phase    = TSP_DOWN;
    m_progress = 0.0f;
    m_speed    = 1.0f/1.0f;
    m_time     = 0.0f;
    m_lastParticle = 0.0f;

    InitAngle();
    m_bError = false;  // ok

    m_camera->StartCentering(m_object, Math::PI*0.50f, 99.9f, 0.0f, 1.0f);

    i = m_sound->Play(SOUND_MANIP, m_object->GetPosition(), 0.0f, 0.3f, true);
    m_sound->AddEnvelope(i, 0.5f, 1.0f, 0.1f, SOPER_CONTINUE);
    m_sound->AddEnvelope(i, 0.5f, 1.0f, 0.9f, SOPER_CONTINUE);
    m_sound->AddEnvelope(i, 0.0f, 0.3f, 0.1f, SOPER_STOP);

    if (m_object->Implements(ObjectInterfaceType::Movable))
    {
        m_physics->SetFreeze(true);  // it does not move
    }

    return ERR_OK;
}

// Indicates whether the action is finished.

Error CTaskSearch::IsEnded()
{
    int     i;

    if ( m_engine->GetPause() )  return ERR_CONTINUE;
    if ( m_bError )  return ERR_STOP;

    if ( m_progress < 1.0f )  return ERR_CONTINUE;
    m_progress = 0.0f;

    if ( m_phase == TSP_DOWN ||
         m_phase == TSP_UP   )
    {
        auto sniff = GetObjectTaskExecutorDetails(m_object).sniff;
        if (sniff.execution == ExecutionAsSniffer)
        {
            for ( i=0 ; i<3 ; i++ )
            {
                m_object->SetPartRotationZ(i+1, m_finalAngle[i]);
            }
        }
    }

    if ( m_phase == TSP_DOWN )
    {
        m_sound->Play(SOUND_REPAIR, m_object->GetPosition());

        m_phase = TSP_SEARCH;
        m_speed = 1.0f/4.0f;
        return ERR_CONTINUE;
    }

    if ( m_phase == TSP_SEARCH )
    {
        CreateMark();

        m_hand  = TSH_UP;
        InitAngle();

        i = m_sound->Play(SOUND_MANIP, m_object->GetPosition(), 0.0f, 0.3f, true);
        m_sound->AddEnvelope(i, 0.5f, 1.0f, 0.1f, SOPER_CONTINUE);
        m_sound->AddEnvelope(i, 0.5f, 1.0f, 0.9f, SOPER_CONTINUE);
        m_sound->AddEnvelope(i, 0.0f, 0.3f, 0.1f, SOPER_STOP);

        m_phase = TSP_UP;
        m_speed = 1.0f/1.0f;
        return ERR_CONTINUE;
    }

    Abort();
    return ERR_STOP;
}

// Suddenly ends the current action.

bool CTaskSearch::Abort()
{
    m_hand  = TSH_UP;
    InitAngle();

    auto sniff = GetObjectTaskExecutorDetails(m_object).sniff;
    if (sniff.execution == ExecutionAsSniffer)
    {
        for (int i = 0; i < 3; i++)
        {
            m_object->SetPartRotationZ(i+1, m_finalAngle[i]);
        }
        m_physics->SetFreeze(false);  // is moving again
    }

    m_camera->StopCentering(m_object, 2.0f);
    return true;
}


// Creates a mark if possible.

bool CTaskSearch::CreateMark()
{
    auto sniff = GetObjectTaskExecutorDetails(m_object).sniff;

    Math::Matrix* mat = m_object->GetWorldMatrix(sniff.partNum);
    Math::Vector pos = Math::Transform(*mat, sniff.pos);  // sensor position

    Gfx::TerrainRes res = m_terrain->GetResource(pos);

    for ( auto it : sniff.objects )
    {
        if ( it.soil != res ) continue;

        CObject* mark = CObjectManager::GetInstancePointer()->CreateObject(pos, 0.0f, it.output);
        m_main->DisplayText(it.message, mark, Ui::TT_INFO, 5.0f, 50.0f);  // displays the message

        return true;
    }

    return false;
}
