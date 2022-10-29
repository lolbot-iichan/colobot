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


#include "object/motion/motiontracked.h"

#include "common/stringutils.h"

#include "graphics/engine/engine.h"
#include "graphics/engine/oldmodelmanager.h"
#include "graphics/engine/particle.h"
#include "graphics/engine/terrain.h"

#include "math/geometry.h"

#include "object/object_manager.h"
#include "object/old_object.h"

#include "object/details/details_provider.h"
#include "object/details/movable_details.h"

#include "physics/physics.h"

#include <stdio.h>
#include <string.h>



// Object's constructor.

CMotionTracked::CMotionTracked(COldObject* object)
    : CMotion(object)
{
    m_posTrackLeft  = 0.0f;
    m_posTrackRight = 0.0f;
}

// Object's destructor.

CMotionTracked::~CMotionTracked()
{
}

// Management of an event.

bool CMotionTracked::EventProcess(const Event &event)
{
    CMotion::EventProcess(event);

    if ( event.type == EVENT_FRAME )
    {
        return EventFrame(event);
    }

    return true;
}

// Management of an event.

bool CMotionTracked::EventFrame(const Event &event)
{
    Character*  character;
    glm::vec3    pos, angle;
    float       s, a, a1, a2;
    float       limit[2];

    if ( m_engine->GetPause() )  return true;
    if ( !m_engine->IsVisiblePoint(m_object->GetPosition()) )  return true;

    s = m_physics->GetLinMotionX(MO_MOTSPEED)*0.7f;
    a = m_physics->GetCirMotionY(MO_MOTSPEED)*2.5f;

    m_posTrackLeft  += event.rTime*(s+a);
    m_posTrackRight += event.rTime*(s-a);

    UpdateTrackMapping(m_posTrackLeft, m_posTrackRight);

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

        auto tracked = GetObjectMovableDetails(m_object).tracked;
        limit[0] = tracked.rotationMax;
        limit[1] = tracked.rotationMin;

        if ( glm::distance(pos, m_engine->GetEyePt()) < 50.0f )  // suspension?
        {
            character = m_object->GetCharacter();
            glm::mat4 mat = m_object->GetWorldMatrix(0);

            pos.x =  character->wheelFront;  // right front wheel
            pos.z = -character->wheelRight;
            pos.y =  0.0f;
            pos = Math::Transform(mat, pos);
            a1 = atanf(m_terrain->GetHeightToFloor(pos)/character->wheelFront);

            pos.x = -character->wheelBack;  // right back wheel
            pos.z = -character->wheelRight;
            pos.y =  0.0f;
            pos = Math::Transform(mat, pos);
            a2 = atanf(m_terrain->GetHeightToFloor(pos)/character->wheelBack);

            a = (a2-a1)/2.0f;
            if ( a > limit[0] )  a = limit[0];
            if ( a < limit[1] )  a = limit[1];
            m_object->SetPartRotationZ(6, a);

            pos.x =  character->wheelFront;  // left front wheel
            pos.z =  character->wheelLeft;
            pos.y =  0.0f;
            pos = Math::Transform(mat, pos);
            a1 = atanf(m_terrain->GetHeightToFloor(pos)/character->wheelFront);

            pos.x = -character->wheelBack;  // left back wheel
            pos.z =  character->wheelLeft;
            pos.y =  0.0f;
            pos = Math::Transform(mat, pos);
            a2 = atanf(m_terrain->GetHeightToFloor(pos)/character->wheelBack);

            a = (a2-a1)/2.0f;
            if ( a > limit[0] )  a = limit[0];
            if ( a < limit[1] )  a = limit[1];
            m_object->SetPartRotationZ(7, a);
        }
        else
        {
            m_object->SetPartRotationZ(6, 0.0f);
            m_object->SetPartRotationZ(7, 0.0f);
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

// Updates the mapping of the texture of the caterpillars.

void CMotionTracked::UpdateTrackMapping(float left, float right)
{
    int rRank = m_object->GetObjectRank(6);
    int lRank = m_object->GetObjectRank(7);

    std::string teamStr = StrUtils::ToString<int>(m_object->GetTeam());
    if(m_object->GetTeam() == 0) teamStr = "";

    constexpr float scale = 0.25f / 8.0f;

    left = left - std::floor(left);
    right = right - std::floor(right);

    m_engine->SetUVTransform(rRank, "tracker_right",
        { (1.0f - right) * scale, 0.0f }, { 1.0f, 1.0f });

    m_engine->SetUVTransform(lRank, "tracker_left",
        { (1.0f - left) * scale, 0.0f }, { 1.0f, 1.0f });
}
