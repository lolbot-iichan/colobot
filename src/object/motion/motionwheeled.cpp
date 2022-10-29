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


#include "object/motion/motionwheeled.h"

#include "common/stringutils.h"

#include "graphics/engine/engine.h"
#include "graphics/engine/oldmodelmanager.h"
#include "graphics/engine/particle.h"
#include "graphics/engine/terrain.h"

#include "math/geometry.h"

#include "object/old_object.h"

#include "object/details/details_provider.h"
#include "object/details/movable_details.h"

#include "physics/physics.h"

#include <stdio.h>
#include <string.h>



// Object's constructor.

CMotionWheeled::CMotionWheeled(COldObject* object)
    : CMotion(object),
      m_wheelTurn()
{
    m_wheelLastPos   = glm::vec3(0.0f, 0.0f, 0.0f);
    m_wheelLastAngle = glm::vec3(0.0f, 0.0f, 0.0f);
}

// Object's destructor.

CMotionWheeled::~CMotionWheeled()
{
}

// Management of an event.

bool CMotionWheeled::EventProcess(const Event &event)
{
    CMotion::EventProcess(event);

    if ( event.type == EVENT_FRAME )
    {
        return EventFrame(event);
    }

    return true;
}

// Management of an event.

bool CMotionWheeled::EventFrame(const Event &event)
{
    Character*  character;
    glm::vec3    pos, angle;
    float       s, a, speedBL, speedBR, speedFL, speedFR, h;

    if ( m_engine->GetPause() )  return true;
    if ( !m_engine->IsVisiblePoint(m_object->GetPosition()) )  return true;

    auto wheeled = GetObjectMovableDetails(m_object).wheeled;

    s = m_physics->GetLinMotionX(MO_MOTSPEED)*1.0f*wheeled.rotationSpeed;
    a = m_physics->GetCirMotionY(MO_MOTSPEED)*3.0f;

    speedBR = -s+a;
    speedBL =  s+a;
    speedFR = -s+a;
    speedFL =  s+a;

    m_object->SetPartRotationZ(6, m_object->GetPartRotationZ(6)+event.rTime*speedBR);  // turning the wheels
    m_object->SetPartRotationZ(7, m_object->GetPartRotationZ(7)+event.rTime*speedBL);
    m_object->SetPartRotationZ(8, m_object->GetPartRotationZ(8)+event.rTime*speedFR);
    m_object->SetPartRotationZ(9, m_object->GetPartRotationZ(9)+event.rTime*speedFL);

    if ( s > 0.0f )
    {
        m_wheelTurn[0] = -a*0.05f;
        m_wheelTurn[1] = -a*0.05f+Math::PI;
        m_wheelTurn[2] =  a*0.05f;
        m_wheelTurn[3] =  a*0.05f+Math::PI;
    }
    else if ( s < 0.0f )
    {
        m_wheelTurn[0] =  a*0.05f;
        m_wheelTurn[1] =  a*0.05f+Math::PI;
        m_wheelTurn[2] = -a*0.05f;
        m_wheelTurn[3] = -a*0.05f+Math::PI;
    }
    else
    {
        m_wheelTurn[0] =  fabs(a)*0.05f;
        m_wheelTurn[1] = -fabs(a)*0.05f+Math::PI;
        m_wheelTurn[2] = -fabs(a)*0.05f;
        m_wheelTurn[3] =  fabs(a)*0.05f+Math::PI;
    }
    m_object->SetPartRotationY(6, m_object->GetPartRotationY(6)+(m_wheelTurn[0]-m_object->GetPartRotationY(6))*event.rTime*8.0f);
    m_object->SetPartRotationY(7, m_object->GetPartRotationY(7)+(m_wheelTurn[1]-m_object->GetPartRotationY(7))*event.rTime*8.0f);
    m_object->SetPartRotationY(8, m_object->GetPartRotationY(8)+(m_wheelTurn[2]-m_object->GetPartRotationY(8))*event.rTime*8.0f);
    m_object->SetPartRotationY(9, m_object->GetPartRotationY(9)+(m_wheelTurn[3]-m_object->GetPartRotationY(9))*event.rTime*8.0f);

    if ( wheeled.hasMudCovers )
    {
        m_object->SetPartRotationY(10, m_object->GetPartRotationY(6)+(m_wheelTurn[0]-m_object->GetPartRotationY(6))*event.rTime*8.0f);
        m_object->SetPartRotationY(11, m_object->GetPartRotationY(7)+(m_wheelTurn[1]-m_object->GetPartRotationY(7))*event.rTime*8.0f+Math::PI);
        m_object->SetPartRotationY(12, m_object->GetPartRotationY(8)+(m_wheelTurn[2]-m_object->GetPartRotationY(8))*event.rTime*8.0f);
        m_object->SetPartRotationY(13, m_object->GetPartRotationY(9)+(m_wheelTurn[3]-m_object->GetPartRotationY(9))*event.rTime*8.0f+Math::PI);
    }

    pos = m_object->GetPosition();
    angle = m_object->GetRotation();
    if ( pos.x   != m_wheelLastPos.x   ||
         pos.y   != m_wheelLastPos.y   ||
         pos.z   != m_wheelLastPos.z   ||
         angle.x != m_wheelLastAngle.x ||
         angle.y != m_wheelLastAngle.y ||
         angle.z != m_wheelLastAngle.z )
    {
        m_wheelLastPos = pos;
        m_wheelLastAngle = angle;

        if ( glm::distance(pos, m_engine->GetEyePt()) < 50.0f )  // suspension?
        {
            character = m_object->GetCharacter();
            glm::mat4 mat = m_object->GetWorldMatrix(0);

            pos.x = -character->wheelBack;  // right back wheel
            pos.z = -character->wheelRight;
            pos.y =  0.0f;
            pos = Math::Transform(mat, pos);
            h = m_terrain->GetHeightToFloor(pos);
            if ( h >  0.5f )  h =  0.5f;
            if ( h < -0.5f )  h = -0.5f;
            pos.x =  wheeled.back;
            pos.y =  wheeled.radius-h;
            pos.z = -wheeled.dist;
            m_object->SetPartPosition(6, pos);
            if ( wheeled.hasMudCovers )  m_object->SetPartPosition(10, pos);

            pos.x = -character->wheelBack;  // left back wheel
            pos.z =  character->wheelLeft;
            pos.y =  0.0f;
            pos = Math::Transform(mat, pos);
            h = m_terrain->GetHeightToFloor(pos);
            if ( h >  0.5f )  h =  0.5f;
            if ( h < -0.5f )  h = -0.5f;
            pos.x =  wheeled.back;
            pos.y =  wheeled.radius-h;
            pos.z =  wheeled.dist;
            m_object->SetPartPosition(7, pos);
            if ( wheeled.hasMudCovers )  m_object->SetPartPosition(11, pos);

            pos.x =  character->wheelFront;  // right front wheel
            pos.z = -character->wheelRight;
            pos.y =  0.0f;
            pos = Math::Transform(mat, pos);
            h = m_terrain->GetHeightToFloor(pos);
            if ( h >  0.5f )  h =  0.5f;
            if ( h < -0.5f )  h = -0.5f;
            pos.x =  wheeled.front;
            pos.y =  wheeled.radius-h;
            pos.z = -wheeled.dist;
            m_object->SetPartPosition(8, pos);
            if ( wheeled.hasMudCovers )  m_object->SetPartPosition(12, pos);

            pos.x =  character->wheelFront;  // left front wheel
            pos.z =  character->wheelLeft;
            pos.y =  0.0f;
            pos = Math::Transform(mat, pos);
            h = m_terrain->GetHeightToFloor(pos);
            if ( h >  0.5f )  h =  0.5f;
            if ( h < -0.5f )  h = -0.5f;
            pos.x =  wheeled.front;
            pos.y =  wheeled.radius-h;
            pos.z =  wheeled.dist;
            m_object->SetPartPosition(9, pos);
            if ( wheeled.hasMudCovers )  m_object->SetPartPosition(13, pos);
        }
        else
        {
            m_object->SetPartPosition(6, glm::vec3(wheeled.back,  wheeled.radius, -wheeled.dist));
            m_object->SetPartPosition(7, glm::vec3(wheeled.back,  wheeled.radius,  wheeled.dist));
            m_object->SetPartPosition(8, glm::vec3(wheeled.front, wheeled.radius, -wheeled.dist));
            m_object->SetPartPosition(9, glm::vec3(wheeled.front, wheeled.radius,  wheeled.dist));

            if ( wheeled.hasMudCovers )
            {
                m_object->SetPartPosition(10, glm::vec3(wheeled.back,  wheeled.radius, -wheeled.dist));
                m_object->SetPartPosition(11, glm::vec3(wheeled.back,  wheeled.radius,  wheeled.dist));
                m_object->SetPartPosition(12, glm::vec3(wheeled.front, wheeled.radius, -wheeled.dist));
                m_object->SetPartPosition(13, glm::vec3(wheeled.front, wheeled.radius,  wheeled.dist));
            }
        }
    }

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

