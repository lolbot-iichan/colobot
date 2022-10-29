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


#include "object/motion/motionqueen.h"

#include "graphics/engine/engine.h"
#include "graphics/engine/oldmodelmanager.h"

#include "math/func.h"

#include "object/old_object.h"

#include "physics/physics.h"

#include <stdio.h>


const float START_TIME = 1000.0f;       // beginning of the relative time



// Object's constructor.

CMotionQueen::CMotionQueen(COldObject* object)
    : CMotion(object),
      m_armAngles()
{
    m_armMember      = START_TIME;
    m_armTimeAbs     = START_TIME;
    m_armTimeMarch   = START_TIME;
}

// Object's destructor.

CMotionQueen::~CMotionQueen()
{
}

// Creates a vehicle traveling any lands on the ground.

void CMotionQueen::Create()
{
    CMotion::Create();

    int member[] =
    {
    //  x1,y1,z1,       x2,y2,z2,       x3,y3,z3,       // in the air:
        30,30,10,       35,-15,10,      35,-35,10,      // t0: legs 1..3
        -80,-45,-35,        -115,-40,-35,       -90,10,-55,     // t0: feet 1..3
        0,0,0,          0,0,0,          0,0,0,          // t0: unused
                                                        // on the ground:
        15,-5,10,       10,-30,10,      5,-50,10,       // t1: legs 1..3
        -90,-15,-15,        -110,-55,-35,       -75,-75,-30,        // t1: feet 1..3
        0,0,0,          0,0,0,          0,0,0,          // t1: unused
                                                        // on the ground back:
        0,40,10,        5,5,10,         0,-15,10,       // t2: legs 1..3
        -45,0,-55,      -65,10,-50,     -125,-85,-45,       // t2: feet 1..3
        0,0,0,          0,0,0,          0,0,0,          // t2: unused
    };

    int i;
    for (i=0 ; i<3*3*3*3 ; i++ )
    {
        m_armAngles[i] = member[i];
    }
}


// Management of an event.

bool CMotionQueen::EventProcess(const Event &event)
{
    CMotion::EventProcess(event);

    if ( event.type == EVENT_FRAME )
    {
        return EventFrame(event);
    }

    return true;
}

// Management of an event.

bool CMotionQueen::EventFrame(const Event &event)
{
    glm::vec3    dir;
    float       s, a, prog;
    int         i, st, nd;
    bool        bStop;

    if ( m_engine->GetPause() )  return true;
    if ( !m_engine->IsVisiblePoint(m_object->GetPosition()) )  return true;

    s =     m_physics->GetLinMotionX(MO_MOTSPEED)*1.5f;
    a = fabs(m_physics->GetCirMotionY(MO_MOTSPEED)*26.0f);

    if ( s == 0.0f && a != 0.0f )  a *= 1.5f;

    m_armTimeAbs += event.rTime;
    m_armTimeMarch += (s)*event.rTime*0.05f;
    m_armMember += (s+a)*event.rTime*0.05f;

    bStop = ( a == 0.0f && s == 0.0f );  // stop?

    if ( bStop )
    {
        prog = Math::Mod(m_armTimeAbs, 2.0f)/10.0f;
        a = Math::Mod(m_armMember, 1.0f);
        a = (prog-a)*event.rTime*1.0f;  // stop position just pleasantly
        m_armMember += a;
    }

    for ( i=0 ; i<6 ; i++ )  // the six legs
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
        st = st*27+(i%3)*3;
        nd = nd*27+(i%3)*3;
        if ( i < 3 )  // right leg (1..3) ?
        {
            m_object->SetPartRotationX(2+2*i+0, Math::PropAngle(m_armAngles[st+ 0], m_armAngles[nd+ 0], prog));
            m_object->SetPartRotationY(2+2*i+0, Math::PropAngle(m_armAngles[st+ 1], m_armAngles[nd+ 1], prog));
            m_object->SetPartRotationZ(2+2*i+0, Math::PropAngle(m_armAngles[st+ 2], m_armAngles[nd+ 2], prog));
            m_object->SetPartRotationX(2+2*i+1, Math::PropAngle(m_armAngles[st+ 9], m_armAngles[nd+ 9], prog));
            m_object->SetPartRotationY(2+2*i+1, Math::PropAngle(m_armAngles[st+10], m_armAngles[nd+10], prog));
            m_object->SetPartRotationZ(2+2*i+1, Math::PropAngle(m_armAngles[st+11], m_armAngles[nd+11], prog));
        }
        else    // left leg (4..6) ?
        {
            m_object->SetPartRotationX(2+2*i+0, Math::PropAngle(    m_armAngles[st+ 0],     m_armAngles[nd+ 0], prog));
            m_object->SetPartRotationY(2+2*i+0, Math::PropAngle(180-m_armAngles[st+ 1], 180-m_armAngles[nd+ 1], prog));
            m_object->SetPartRotationZ(2+2*i+0, Math::PropAngle(   -m_armAngles[st+ 2],    -m_armAngles[nd+ 2], prog));
            m_object->SetPartRotationX(2+2*i+1, Math::PropAngle(    m_armAngles[st+ 9],     m_armAngles[nd+ 9], prog));
            m_object->SetPartRotationY(2+2*i+1, Math::PropAngle(   -m_armAngles[st+10],    -m_armAngles[nd+10], prog));
            m_object->SetPartRotationZ(2+2*i+1, Math::PropAngle(   -m_armAngles[st+11],    -m_armAngles[nd+11], prog));
        }
    }

    assert(m_object->Implements(ObjectInterfaceType::Destroyable));
    if ( !bStop && !dynamic_cast<CDestroyableObject*>(m_object)->IsDying() )
    {
        a = Math::Mod(m_armTimeMarch, 1.0f);
        if ( a < 0.5f )  a = -1.0f+4.0f*a;  // -1..1
        else             a =  3.0f-4.0f*a;  // 1..-1
        dir.x = sinf(a)*0.03f;

        s = Math::Mod(m_armTimeMarch/2.0f, 1.0f);
        if ( s < 0.5f )  s = -1.0f+4.0f*s;  // -1..1
        else             s =  3.0f-4.0f*s;  // 1..-1
        dir.z = sinf(s)*0.05f;

        dir.y = 0.0f;
        m_object->SetTilt(dir);

        a = Math::Mod(m_armMember-0.1f, 1.0f);
        if ( a < 0.33f )
        {
            dir.y = -(1.0f-(a/0.33f))*0.3f;
        }
        else if ( a < 0.67f )
        {
            dir.y = 0.0f;
        }
        else
        {
            dir.y = -(a-0.67f)/0.33f*0.3f;
        }
        dir.x = 0.0f;
        dir.z = 0.0f;
        m_object->SetLinVibration(dir);
    }

    m_object->SetPartRotationZ(1, sinf(m_armTimeAbs*0.5f)*0.20f);  // head
    m_object->SetPartRotationX(1, sinf(m_armTimeAbs*0.6f)*0.10f);  // head
    m_object->SetPartRotationY(1, sinf(m_armTimeAbs*0.7f)*0.20f);  // head

    m_object->SetPartRotationZ(14,  0.50f);
    m_object->SetPartRotationZ(16,  0.50f);
    m_object->SetPartRotationY(14,  0.80f+sinf(m_armTimeAbs*1.1f)*0.53f);  // right antenna
    m_object->SetPartRotationY(15,  0.70f-sinf(m_armTimeAbs*1.7f)*0.43f);
    m_object->SetPartRotationY(16, -0.80f+sinf(m_armTimeAbs*0.9f)*0.53f);  // left antenna
    m_object->SetPartRotationY(17, -0.70f-sinf(m_armTimeAbs*1.3f)*0.43f);

    m_object->SetPartRotationY(18, sinf(m_armTimeAbs*1.1f)*0.20f);  // right claw
    m_object->SetPartRotationZ(18, -0.20f);
    m_object->SetPartRotationY(19, sinf(m_armTimeAbs*0.9f)*0.20f);  // left claw
    m_object->SetPartRotationZ(19, -0.20f);

    return true;
}
