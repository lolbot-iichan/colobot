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


#include "object/motion/motionworm.h"

#include "graphics/engine/engine.h"
#include "graphics/engine/oldmodelmanager.h"
#include "graphics/engine/particle.h"
#include "graphics/engine/terrain.h"

#include "math/geometry.h"

#include "object/old_object.h"

#include "physics/physics.h"

#include <stdio.h>


const float START_TIME      = 1000.0f;  // beginning of the relative time
const float TIME_UPDOWN     = 2.0f;     // time for up / down
const float DOWN_ALTITUDE   = 3.0f;     // underground distance
const int WORM_PART = 7;        // number of parts of a worm



// Object's constructor.

CMotionWorm::CMotionWorm(COldObject* object)
    : CMotion(object),
      m_armAngles()
{
    m_timeUp         = 18.0f;
    m_timeDown       = 18.0f;
    m_armMember      = START_TIME;
    m_armTimeAbs     = START_TIME;
    m_armTimeMarch   = START_TIME;
    m_armTimeAction  = START_TIME;
    m_armTimeIndex   = 0;
    m_armPartIndex   = 0;
    m_armMemberIndex = 0;
    m_armLinSpeed    = 0.0f;
    m_armCirSpeed    = 0.0f;
    m_armLastAction  = -1;
    m_specAction     = -1;
    m_specTime       = 0.0f;
    m_lastParticle  = 0.0f;
    m_bArmStop = false;
}

// Object's destructor.

CMotionWorm::~CMotionWorm()
{
}

// Creates a vehicle traveling any lands on the ground.

void CMotionWorm::Create()
{
    CMotion::Create();
}


// Specifies a special parameter.

bool CMotionWorm::SetParam(int rank, float value)
{
    if ( rank == 0 )
    {
        m_timeDown = value;
        return true;
    }

    if ( rank == 1 )
    {
        m_timeUp = value;
        return true;
    }

    return false;
}

float CMotionWorm::GetParam(int rank)
{
    if ( rank == 0 )  return m_timeDown;
    if ( rank == 1 )  return m_timeUp;
    return 0.0f;
}



// Management of an event.

bool CMotionWorm::EventProcess(const Event &event)
{
    CMotion::EventProcess(event);

    if ( event.type == EVENT_FRAME )
    {
        return EventFrame(event);
    }

    if ( event.type == EVENT_KEY_DOWN )
    {
    }

    return true;
}

// Management of an event.

bool CMotionWorm::EventFrame(const Event &event)
{
    glm::vec3    pos, p, angle, speed;
    glm::vec2     center, pp, dim;
    float       height[WORM_PART+2];
    float       floor, a, s, px, curve, phase, h, zoom, radius;
    int         i, under;

    if ( m_engine->GetPause() )  return true;

    s = m_physics->GetLinMotionX(MO_MOTSPEED)/m_physics->GetLinMotionX(MO_ADVSPEED);
    a = m_physics->GetCirMotionY(MO_MOTSPEED)/m_physics->GetCirMotionY(MO_ADVSPEED);

    if ( s == 0.0f && a != 0.0f )  s = a;

    m_armLinSpeed += (s-m_armLinSpeed)*event.rTime*3.0f;
    m_armCirSpeed += (a-m_armCirSpeed)*event.rTime*1.5f;

    m_armTimeAbs   += event.rTime;
    m_armTimeMarch += event.rTime*m_armLinSpeed;

    assert(m_object->Implements(ObjectInterfaceType::Destroyable));
    under = 0;  // no piece under the ground
    for ( i=0 ; i<WORM_PART+2 ; i++ )
    {
        phase = Math::Mod(m_armTimeMarch-i*0.3f, TIME_UPDOWN+m_timeDown+TIME_UPDOWN+m_timeUp);
        if ( phase < TIME_UPDOWN )  // descends?
        {
            h = -(phase/TIME_UPDOWN)*DOWN_ALTITUDE;
        }
        else if ( phase < TIME_UPDOWN+m_timeDown )  // advance underground?
        {
            h = -DOWN_ALTITUDE;
            under ++;  // the most of a piece entirely under ground
        }
        else if ( phase < TIME_UPDOWN+m_timeDown+TIME_UPDOWN )  // up?
        {
            h = -(1.0f-(phase-TIME_UPDOWN-m_timeDown)/TIME_UPDOWN)*DOWN_ALTITUDE;
        }
        else  // advance on earth?
        {
            h = 0.0f;
        }
        if ( dynamic_cast<CDestroyableObject*>(m_object)->IsDying() )  // is burning?
        {
            h = 0.0f;  // remains on earth
        }
        h += 0.3f;
        height[i] = h;
    }
    m_object->SetUnderground(under == WORM_PART+2);

    if ( !m_engine->IsVisiblePoint(m_object->GetPosition()) )  return true;

    pos = m_object->GetPosition();
    floor = m_terrain->GetFloorLevel(pos, true);

    glm::mat4 mat = m_object->GetWorldMatrix(0);

    px = 1.0f+WORM_PART/2;
    for ( i=0 ; i<WORM_PART+2 ; i++ )
    {
        radius = 1.0f+(height[i]-0.3f)/DOWN_ALTITUDE;  // 0 = underground, 1 = surface
        radius = radius*1.3f-0.3f;
        if ( radius < 0.0f )  radius = 0.0f;
        radius *= 5.0f;
        m_engine->SetObjectShadowSpotRadius(m_object->GetObjectRank(0), radius);

        pos.x = px+       sinf(m_armTimeMarch*4.0f+0.5f*i)*0.6f;
        pos.y = height[i]+sinf(m_armTimeMarch*4.0f+0.5f*i)*0.2f*m_armLinSpeed;
        pos.y +=          sinf(m_armTimeAbs  *1.3f+0.2f*i)*0.1f;
        pos.z =           sinf(m_armTimeAbs  *2.0f+0.7f*i)*0.2f;

        curve = (static_cast< float >(i) -(WORM_PART+2)/2)*m_armCirSpeed*0.1f;
        center.x = 0.0f;
        center.y = 0.0f;
        pp.x = pos.x;
        pp.y = pos.z;
        pp = Math::RotatePoint(center, curve, pp);
        pos.x = pp.x;
        pos.z = pp.y;

        p = Math::Transform(mat, pos);
        pos.y += m_terrain->GetFloorLevel(p, true)-floor;
        m_object->SetPartPosition(i+1, pos);

        zoom = Math::Mod(m_armTimeAbs*0.5f+100.0f-i*0.1f, 2.0f);
        if ( zoom > 1.0f )  zoom = 2.0f-zoom;
        zoom *= 1.6f;
        if ( zoom < 1.0f )  zoom = 1.0f;
        m_object->SetPartScaleY(i+1, 0.2f+zoom*0.8f);
        m_object->SetPartScaleZ(i+1, zoom);

        if ( height[i] >= -1.0f && height[i] < -0.2f &&
             m_lastParticle+m_engine->ParticleAdapt(0.2f) <= m_armTimeMarch )
        {
            m_lastParticle = m_armTimeMarch;

            pos = p;
            pos.y += -height[i];
            pos.x += (Math::Rand()-0.5f)*4.0f;
            pos.z += (Math::Rand()-0.5f)*4.0f;
            speed = glm::vec3(0.0f, 0.0f, 0.0f);
            dim.x = Math::Rand()*2.0f+1.5f;
            dim.y = dim.x;
            m_particle->CreateParticle(pos, speed, dim, Gfx::PARTICRASH, 2.0f);
        }

        px -= 1.0f;
    }

    for ( i=0 ; i<WORM_PART+1 ; i++ )
    {
        pos  = m_object->GetPartPosition(i+2);
        pos -= m_object->GetPartPosition(i+1);

        angle.z = -Math::RotateAngle(glm::length(glm::vec2(pos.x, pos.z)), pos.y);
        angle.y = Math::PI-Math::RotateAngle(pos.x, pos.z);
        angle.x = 0.0f;
        m_object->SetPartRotation(i+1, angle);

        if ( i == WORM_PART )
        {
            m_object->SetPartRotation(i+2, angle);
        }
    }

    return true;
}
