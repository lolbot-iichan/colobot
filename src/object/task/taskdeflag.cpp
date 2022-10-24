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

#include "object/task/taskdeflag.h"

#include "graphics/engine/particle.h"
#include "graphics/engine/pyro_manager.h"

#include "level/robotmain.h"

#include "math/geometry.h"

#include "object/object_manager.h"
#include "object/old_object.h"

#include "object/details/task_executor_details.h"

#include "object/motion/motionhuman.h"

#include "sound/sound.h"



// Object's constructor.

CTaskDeflag::CTaskDeflag(COldObject* object) : CForegroundTask(object)
{
}

// Object's destructor.

CTaskDeflag::~CTaskDeflag()
{
}


// Management of an event.

bool CTaskDeflag::EventProcess(const Event &event)
{
    if ( m_bError )  return true;
    if ( m_engine->GetPause() )  return true;
    if ( event.type != EVENT_FRAME )  return true;

    m_time += event.rTime;

    if ( GetObjectTaskExecutorDetails(m_object).deflag.execution == ExecutionAsRobot )
    {
        float angle =  110.0f*Math::PI/180.0f;
        float diff  =  -10.0f*Math::PI/180.0f;
        if ( m_time <= 0.5f )
        {
            m_object->SetPartRotationZ(1, angle+diff*m_time*2.0f);
        }
        else if ( m_time >= 1.5f && m_time < 2.0f )
        {
            m_object->SetPartRotationZ(1, angle+diff*(2.0f-m_time)*2.0f);
        }
    }

    return true;
}

// Assigns the goal was achieved.

Error CTaskDeflag::Start()
{
    Error err;

    m_time = 0.0f;

    m_bError = true;  // operation impossible

    auto deflag = GetObjectTaskExecutorDetails(m_object).deflag;

    err = CanStartTask(&deflag);
    if ( err != ERR_OK )  return err;

    err = DeleteFlag();
    if ( err != ERR_OK )  return err;

    m_bError = false;

    if ( deflag.execution == ExecutionAsHuman )
    {
        m_motion->SetAction(MHS_FLAG);
    }
    if ( deflag.execution == ExecutionAsRobot )
    {
        int i = m_sound->Play(SOUND_MANIP, m_object->GetPosition(), 0.0f, 0.3f, true);
        m_sound->AddEnvelope(i, 0.5f, 1.0f, 0.1f, SOPER_CONTINUE);
        m_sound->AddEnvelope(i, 0.5f, 1.0f, 0.3f, SOPER_CONTINUE);
        m_sound->AddEnvelope(i, 0.0f, 0.3f, 0.1f, SOPER_CONTINUE);
        m_sound->AddEnvelope(i, 0.0f, 0.3f, 1.0f, SOPER_CONTINUE);
        m_sound->AddEnvelope(i, 0.5f, 1.0f, 0.1f, SOPER_CONTINUE);
        m_sound->AddEnvelope(i, 0.5f, 1.0f, 0.3f, SOPER_CONTINUE);
        m_sound->AddEnvelope(i, 0.0f, 0.3f, 0.1f, SOPER_STOP);
    }

    m_camera->StartCentering(m_object, Math::PI*0.3f, 99.9f, 0.0f, 0.5f);

    return ERR_OK;
}

// Indicates whether the action is finished.

Error CTaskDeflag::IsEnded()
{
    if ( m_engine->GetPause() )  return ERR_CONTINUE;

    if ( m_bError )  return ERR_STOP;
    if ( m_time < 2.0f )  return ERR_CONTINUE;

    Abort();
    return ERR_STOP;
}

// Suddenly ends the current action.

bool CTaskDeflag::Abort()
{
    auto deflag = GetObjectTaskExecutorDetails(m_object).deflag;
    if ( deflag.execution == ExecutionAsHuman )
    {
        m_motion->SetAction(-1);
    }
    if ( deflag.execution == ExecutionAsRobot )
    {
        m_object->SetPartRotationZ(1, 110.0f*Math::PI/180.0f);
    }

    m_camera->StopCentering(m_object, 2.0f);
    return true;
}

// Returns the closest object to a given position.

CObject* CTaskDeflag::SearchNearest(Math::Vector pos)
{
    std::vector<ObjectType> types;
    for ( auto it : GetObjectTaskExecutorDetails(m_object).deflag.objects )
        types.push_back(it.input);
    return CObjectManager::GetInstancePointer()->FindNearest(nullptr, pos, types);
}

// Deletes a color indicator.

Error CTaskDeflag::DeleteFlag()
{
    auto deflag = GetObjectTaskExecutorDetails(m_object).deflag;
    Math::Matrix* mat = m_object->GetWorldMatrix(deflag.partNum);
    Math::Vector iPos = Transform(*mat, deflag.position);

    CObject* pObj = SearchNearest(iPos);
    if ( pObj == nullptr || Math::Distance(iPos, pObj->GetPosition()) > deflag.radius )
    {
        return ERR_FLAG_DELETE;
    }

    Math::Vector oPos = pObj->GetPosition();
    if (oPos.x != iPos.x || iPos.z != oPos.z)
    {
        float iAngle = Math::NormAngle(m_object->GetRotationY());  // 0..2*Math::PI
        float angle = Math::RotateAngle(oPos.x-iPos.x, iPos.z-oPos.z);  // CW !
        float aLimit = 45.0f*Math::PI/180.0f;
        if ( !Math::TestAngle(angle, iAngle-aLimit, iAngle+aLimit) )
        {
            return ERR_FLAG_DELETE;
        }
    }

    std::vector<CObjectDeflagTaskExecutorObject> matched;
    for ( auto it : deflag.objects )
    {
        if (it.input != pObj->GetType())  continue;
        matched.push_back(it);
    }

    if ( matched.size() > 0 )
    {
        CObjectDeflagTaskExecutorObject matchedFinal = matched[ std::rand() % matched.size() ];

        // TODO: Should we use DestroyObject instead ?!
        m_sound->Play(SOUND_WAYPOINT, iPos);
        m_engine->GetPyroManager()->Create(matchedFinal.effect, pObj);

        if ( matchedFinal.output != OBJECT_NULL )
        {
            CObject* pNew = CObjectManager::GetInstancePointer()->CreateObject(oPos, 0.0f, matchedFinal.output);
            m_engine->GetPyroManager()->Create(Gfx::PT_FLCREATE, pNew);
        }
        m_main->DisplayText(matchedFinal.message, m_object, Ui::TT_INFO);  // displays the message
    }

    return ERR_OK;
}
