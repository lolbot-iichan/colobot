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


#include "object/motion/motionwinged.h"

#include "common/stringutils.h"

#include "graphics/engine/engine.h"
#include "graphics/engine/oldmodelmanager.h"
#include "graphics/engine/particle.h"
#include "graphics/engine/terrain.h"

#include "math/geometry.h"

#include "object/object_manager.h"
#include "object/old_object.h"

#include "physics/physics.h"

#include <stdio.h>
#include <string.h>



// Object's constructor.

CMotionWinged::CMotionWinged(COldObject* object)
    : CMotion(object),
      m_flyPaw()
{
    m_wheelLastPos   = glm::vec3(0.0f, 0.0f, 0.0f);
    m_wheelLastAngle = glm::vec3(0.0f, 0.0f, 0.0f);
    m_bFlyFix = false;
}

// Object's destructor.

CMotionWinged::~CMotionWinged()
{
}

// Management of an event.

bool CMotionWinged::EventProcess(const Event &event)
{
    CMotion::EventProcess(event);

    if ( event.type == EVENT_FRAME )
    {
        return EventFrame(event);
    }

    return true;
}

// Management of an event.

bool CMotionWinged::EventFrame(const Event &event)
{
    if ( m_engine->GetPause() )  return true;
    if ( !m_engine->IsVisiblePoint(m_object->GetPosition()) )  return true;

    EventFrameFly(event);

    if ( m_object->GetToy() )  // toy is key?
    {
        float scale = 1.0;
        if ( m_object->GetSelect() &&
             m_camera->GetType() == Gfx::CAM_TYPE_ONBOARD )
        {
            scale = 0.00001f;  // out of sight!
        }
        m_object->SetPartScale(2, scale);

        float s;
        s  = -fabs(m_physics->GetLinMotionX(MO_MOTSPEED)*0.1f);
        s += -fabs(m_physics->GetCirMotionY(MO_MOTSPEED)*1.5f);
        m_object->SetPartRotationY(2, m_object->GetPartRotationY(2)+event.rTime*s);  // turns the key
    }

    return true;
}

// Managing an event for a flying robot.

bool CMotionWinged::EventFrameFly(const Event &event)
{
    glm::vec3    pos, angle, paw[3];
    float       hope[3], actual, final, h, a;
    int         i;

    pos = m_object->GetPosition();
    angle = m_object->GetRotation();
    if ( m_bFlyFix                     &&
         pos.x   == m_wheelLastPos.x   &&
         pos.y   == m_wheelLastPos.y   &&
         pos.z   == m_wheelLastPos.z   &&
         angle.x == m_wheelLastAngle.x &&
         angle.y == m_wheelLastAngle.y &&
         angle.z == m_wheelLastAngle.z )  return true;

    m_wheelLastPos = pos;
    m_wheelLastAngle = angle;

    if ( m_physics->GetLand() )  // on the ground?
    {
        glm::mat4 mat = m_object->GetWorldMatrix(0);
        paw[0] = Math::Transform(mat, glm::vec3( 4.2f, 0.0f,  0.0f));  // front
        paw[1] = Math::Transform(mat, glm::vec3(-3.0f, 0.0f, -3.7f));  // right back
        paw[2] = Math::Transform(mat, glm::vec3(-3.0f, 0.0f,  3.7f));  // left back

        for ( i=0 ; i<3 ; i++ )
        {
            h = m_terrain->GetHeightToFloor(paw[i]);
            a = -atanf(h*0.5f);
            if ( a >  Math::PI*0.2f )  a =  Math::PI*0.2f;
            if ( a < -Math::PI*0.2f )  a = -Math::PI*0.2f;
            hope[i] = a;
        }
    }
    else    // in flight?
    {
        hope[0] = 0.0f;  // front
        hope[1] = 0.0f;  // right back
        hope[2] = 0.0f;  // left back
    }

    m_bFlyFix = true;
    for ( i=0 ; i<3 ; i++ )
    {
        actual = m_object->GetPartRotationZ(6+i);
        final = Math::Smooth(actual, hope[i], event.rTime*5.0f);
        if ( final != actual )
        {
            m_bFlyFix = false;  // it is moving
            m_object->SetPartRotationZ(6+i, final);
        }
    }

    return true;
}
