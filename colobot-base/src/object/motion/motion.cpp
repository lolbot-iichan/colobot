/*
 * This file is part of the Colobot: Gold Edition source code
 * Copyright (C) 2001-2023, Daniel Roux, EPSITEC SA & TerranovaTeam
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


#include "object/motion/motion.h"

#include "app/app.h"

#include "graphics/engine/engine.h"
#include "graphics/engine/water.h"

#include "level/robotmain.h"

#include "level/parser/parserline.h"
#include "level/parser/parserparam.h"

#include "math/func.h"

#include "object/old_object.h"



#include <cstdio>
#include <cstring>


// Object's constructor.

CMotion::CMotion(COldObject* object)
{
    m_app       = CApplication::GetInstancePointer();
    m_sound     = m_app->GetSound();
    m_engine    = Gfx::CEngine::GetInstancePointer();
    m_particle  = m_engine->GetParticle();
    m_water     = m_engine->GetWater();
    m_main      = CRobotMain::GetInstancePointer();
    m_terrain   = m_main->GetTerrain();
    m_camera    = m_main->GetCamera();

    m_object    = object;
    m_physics   = nullptr;

    m_actionType = -1;
    m_actionTime = 0.0f;
    m_progress   = 0.0f;

    m_linVibration  = glm::vec3(0.0f, 0.0f, 0.0f);
    m_cirVibration  = glm::vec3(0.0f, 0.0f, 0.0f);
    m_inclinaison   = glm::vec3(0.0f, 0.0f, 0.0f);
}

// Object's destructor.

CMotion::~CMotion()
{
}

void CMotion::SetPhysics(CPhysics* physics)
{
    m_physics = physics;
}

// Management of an event.

bool CMotion::EventProcess(const Event &event)
{
    glm::vec3    pos, dir;
    float       time;

    if ( m_object->GetType() != OBJECT_TOTO &&
         m_engine->GetPause() )  return true;

    if ( event.type != EVENT_FRAME )  return true;

    m_progress += event.rTime*m_actionTime;
    if ( m_progress > 1.0f )  m_progress = 1.0f;  // (*)

    pos = m_object->GetPosition();
    if ( pos.y < m_water->GetLevel(m_object) )  // underwater?
    {
        time = event.rTime*3.0f;  // everything is slower
    }
    else
    {
        time = event.rTime*10.0f;
    }

    dir = m_object->GetLinVibration();
    dir.x = Math::Smooth(dir.x, m_linVibration.x, time);
    dir.y = Math::Smooth(dir.y, m_linVibration.y, time);
    dir.z = Math::Smooth(dir.z, m_linVibration.z, time);
    m_object->SetLinVibration(dir);

    dir = m_object->GetCirVibration();
    dir.x = Math::Smooth(dir.x, m_cirVibration.x, time);
    dir.y = Math::Smooth(dir.y, m_cirVibration.y, time);
    dir.z = Math::Smooth(dir.z, m_cirVibration.z, time);
    m_object->SetCirVibration(dir);

    dir = m_object->GetTilt();
    dir.x = Math::Smooth(dir.x, m_inclinaison.x, time);
    dir.y = Math::Smooth(dir.y, m_inclinaison.y, time);
    dir.z = Math::Smooth(dir.z, m_inclinaison.z, time);
    m_object->SetTilt(dir);

    return true;
}

// (*)  Avoids the bug of ants returned by the thumper and
//      whose abdomen grown to infinity!


// Start an action.

Error CMotion::SetAction(int action, float time)
{
    m_actionType = action;
    m_actionTime = 1.0f/time;
    m_progress = 0.0f;
    return ERR_OK;
}

// Returns the current action.

int CMotion::GetAction()
{
    return m_actionType;
}


// Specifies a special parameter.

bool CMotion::SetParam(int rank, float value)
{
    return false;
}

float CMotion::GetParam(int rank)
{
    return 0.0f;
}


// Saves all parameters of the object.

bool CMotion::Write(CLevelParserLine* line)
{
    if ( m_actionType == -1 )  return false;

    line->AddParam("mType", std::make_unique<CLevelParserParam>(m_actionType));
    line->AddParam("mTime", std::make_unique<CLevelParserParam>(m_actionTime));
    line->AddParam("mProgress", std::make_unique<CLevelParserParam>(m_progress));

    return false;
}

// Restores all parameters of the object.

bool CMotion::Read(CLevelParserLine* line)
{
    m_actionType = line->GetParam("mType")->AsInt(-1);
    m_actionTime = line->GetParam("mTime")->AsFloat(0.0f);
    m_progress = line->GetParam("mProgress")->AsFloat(0.0f);

    return false;
}


// Getes the linear vibration.

void CMotion::SetLinVibration(glm::vec3 dir)
{
    m_linVibration = dir;
}

glm::vec3 CMotion::GetLinVibration()
{
    return m_linVibration;
}

// Getes the circular vibration.

void CMotion::SetCirVibration(glm::vec3 dir)
{
    m_cirVibration = dir;
}

glm::vec3 CMotion::GetCirVibration()
{
    return m_cirVibration;
}

// Getes the tilt.

void CMotion::SetTilt(glm::vec3 dir)
{
    m_inclinaison = dir;
}

glm::vec3 CMotion::GetTilt()
{
    return m_inclinaison;
}
