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


#include "object/motion/motionlegged.h"

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

CMotionLegged::CMotionLegged(COldObject* object)
    : CMotion(object)
{
    m_armTimeAbs     = 1000.0f;
    m_armMember      = 1000.0f;
}

// Object's destructor.

CMotionLegged::~CMotionLegged()
{
}

// Management of an event.

bool CMotionLegged::EventProcess(const Event &event)
{
    CMotion::EventProcess(event);

    if ( event.type == EVENT_FRAME )
    {
        return EventFrame(event);
    }

    return true;
}

// Management of an event.

bool CMotionLegged::EventFrame(const Event &event)
{
    if ( m_engine->GetPause() )  return true;
    if ( !m_engine->IsVisiblePoint(m_object->GetPosition()) )  return true;

    EventFrameInsect(event);

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

// Event management for insect legs.

bool CMotionLegged::EventFrameInsect(const Event &event)
{
    glm::vec3    dir;
    float       s, a, prog = 0.0f, time;
    int         i, st, nd, action;
    bool        bStop, bOnBoard;

    static int table[] =
    {
    //  x1,y1,z1,   x2,y2,z2,   x3,y3,z3,   // in the air:
        60,25,0,    60,0,0,     60,-25,0,   // t0: thighs 1..4
        -35,0,0,    -35,0,0,    -35,0,0,    // t0: legs 1..4
        -65,0,0,    -65,0,0,    -65,0,0,    // t0: feet 1..4
                                            // on the ground:
        30,10,0,    30,-15,0,   30,-40,0,   // t1: thighs 1..4
        -45,0,0,    -45,0,0,    -45,0,0,    // t1: legs 1..4
        -20,0,0,    -20,0,0,    -20,0,0,    // t1: feet 1..4
                                            // on the ground back:
        35,40,0,    40,15,0,    40,-10,0,   // t2: thighs 1..4
        -35,0,0,    -35,0,0,    -35,0,0,    // t2: legs 1..4
        -50,0,0,    -65,0,0,    -65,0,0,    // t2: feet 1..4
                                            // stop:
        35,35,0,    40,10,0,    40,-15,0,   // s0: thighs 1..4
        -35,0,0,    -35,0,0,    -35,0,0,    // s0: legs 1..4
        -50,0,0,    -65,0,0,    -65,0,0,    // s0: feet 1..4
    };

    bOnBoard = false;
    if ( m_object->GetSelect() &&
         m_camera->GetType() == Gfx::CAM_TYPE_ONBOARD )
    {
        bOnBoard = true;
    }

    s =     m_physics->GetLinMotionX(MO_MOTSPEED)*1.5f;
    a = fabs(m_physics->GetCirMotionY(MO_MOTSPEED)*2.0f);

    if ( s == 0.0f && a != 0.0f )  a *= 1.5f;

    m_armTimeAbs += event.rTime;
    m_armMember += (s+a)*event.rTime*0.15f;

    bStop = ( a == 0.0f && s == 0.0f );  // stop?

    action = 0;  // walking
    if ( s == 0.0f && a == 0.0f )
    {
        action = 3;  // stop
    }

    if ( bStop )
    {
        prog = Math::Mod(m_armTimeAbs, 2.0f)/10.0f;
        a = Math::Mod(m_armMember, 1.0f);
        a = (prog-a)*event.rTime*2.0f;  // stop position is pleasantly
        m_armMember += a;
    }

    assert(m_object->Implements(ObjectInterfaceType::Destroyable));
    if ( dynamic_cast<CDestroyableObject*>(m_object)->IsDying() )  // burn or explode?
    {
        action = 3;
    }

    for ( i=0 ; i<6 ; i++ )  // the six legs
    {
        if ( action != 0 )  // special action in progress?
        {
            st = 3*3*3*action + (i%3)*3;
            nd = st;
            time = event.rTime*5.0f;
        }
        else
        {
            if ( i < 3 )  prog = Math::Mod(m_armMember+(2.0f-(i%3))*0.33f+0.0f, 1.0f);
            else          prog = Math::Mod(m_armMember+(2.0f-(i%3))*0.33f+0.3f, 1.0f);
            if ( prog < 0.33f )  // t0..t1 ?
            {
                prog = prog/0.33f;  // 0..1
                st = 0;  // index start
                nd = 1;  // index end
            }
            else if ( prog < 0.67f )  // t1..t2 ?
            {
                prog = (prog-0.33f)/0.33f;  // 0..1
                st = 1;  // index start
                nd = 2;  // index end
            }
            else    // t2..t0 ?
            {
                prog = (prog-0.67f)/0.33f;  // 0..1
                st = 2;  // index start
                nd = 0;  // index end
            }
            st = 3*3*3*action + st*3*3*3 + (i%3)*3;
            nd = 3*3*3*action + nd*3*3*3 + (i%3)*3;

            // Less and less soft ...
            time = event.rTime*20.0f;
        }

        if ( i < 3 )  // right leg (1..3) ?
        {
            m_object->SetPartRotationX(6+3*i+0, Math::Smooth(m_object->GetPartRotationX(6+3*i+0), Math::PropAngle(table[st+ 0], table[nd+ 0], prog), time));
            m_object->SetPartRotationY(6+3*i+0, Math::Smooth(m_object->GetPartRotationY(6+3*i+0), Math::PropAngle(table[st+ 1], table[nd+ 1], prog), time));
            m_object->SetPartRotationZ(6+3*i+0, Math::Smooth(m_object->GetPartRotationZ(6+3*i+0), Math::PropAngle(table[st+ 2], table[nd+ 2], prog), time));
            m_object->SetPartRotationX(6+3*i+1, Math::Smooth(m_object->GetPartRotationX(6+3*i+1), Math::PropAngle(table[st+ 9], table[nd+ 9], prog), time));
            m_object->SetPartRotationY(6+3*i+1, Math::Smooth(m_object->GetPartRotationY(6+3*i+1), Math::PropAngle(table[st+10], table[nd+10], prog), time));
            m_object->SetPartRotationZ(6+3*i+1, Math::Smooth(m_object->GetPartRotationZ(6+3*i+1), Math::PropAngle(table[st+11], table[nd+11], prog), time));
            m_object->SetPartRotationX(6+3*i+2, Math::Smooth(m_object->GetPartRotationX(6+3*i+2), Math::PropAngle(table[st+18], table[nd+18], prog), time));
            m_object->SetPartRotationY(6+3*i+2, Math::Smooth(m_object->GetPartRotationY(6+3*i+2), Math::PropAngle(table[st+19], table[nd+19], prog), time));
            m_object->SetPartRotationZ(6+3*i+2, Math::Smooth(m_object->GetPartRotationZ(6+3*i+2), Math::PropAngle(table[st+20], table[nd+20], prog), time));
        }
        else    // left leg (4..6) ?
        {
            m_object->SetPartRotationX(6+3*i+0, Math::Smooth(m_object->GetPartRotationX(6+3*i+0), Math::PropAngle(-table[st+ 0], -table[nd+ 0], prog), time));
            m_object->SetPartRotationY(6+3*i+0, Math::Smooth(m_object->GetPartRotationY(6+3*i+0), Math::PropAngle(-table[st+ 1], -table[nd+ 1], prog), time));
            m_object->SetPartRotationZ(6+3*i+0, Math::Smooth(m_object->GetPartRotationZ(6+3*i+0), Math::PropAngle( table[st+ 2],  table[nd+ 2], prog), time));
            m_object->SetPartRotationX(6+3*i+1, Math::Smooth(m_object->GetPartRotationX(6+3*i+1), Math::PropAngle(-table[st+ 9], -table[nd+ 9], prog), time));
            m_object->SetPartRotationY(6+3*i+1, Math::Smooth(m_object->GetPartRotationY(6+3*i+1), Math::PropAngle(-table[st+10], -table[nd+10], prog), time));
            m_object->SetPartRotationZ(6+3*i+1, Math::Smooth(m_object->GetPartRotationZ(6+3*i+1), Math::PropAngle( table[st+11],  table[nd+11], prog), time));
            m_object->SetPartRotationX(6+3*i+2, Math::Smooth(m_object->GetPartRotationX(6+3*i+2), Math::PropAngle(-table[st+18], -table[nd+18], prog), time));
            m_object->SetPartRotationY(6+3*i+2, Math::Smooth(m_object->GetPartRotationY(6+3*i+2), Math::PropAngle(-table[st+19], -table[nd+19], prog), time));
            m_object->SetPartRotationZ(6+3*i+2, Math::Smooth(m_object->GetPartRotationZ(6+3*i+2), Math::PropAngle( table[st+20],  table[nd+20], prog), time));
        }
    }

    if ( bStop )
    {
    }
    else
    {
        a = Math::Mod(m_armMember, 1.0f);
        if ( a < 0.5f )  a = -1.0f+4.0f*a;  // -1..1
        else             a =  3.0f-4.0f*a;  // 1..-1
        dir.x = sinf(a)*0.05f;

        s = Math::Mod(m_armMember/2.0f, 1.0f);
        if ( s < 0.5f )  s = -1.0f+4.0f*s;  // -1..1
        else             s =  3.0f-4.0f*s;  // 1..-1
        dir.z = sinf(s)*0.1f;

        dir.y = 0.0f;

        if ( bOnBoard )  dir *= 0.6f;
        SetTilt(dir);
    }

    return true;
}
