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


#include "object/motion/motionant.h"

#include "graphics/engine/engine.h"
#include "graphics/engine/oldmodelmanager.h"
#include "graphics/engine/particle.h"

#include "math/func.h"

#include "object/old_object.h"

#include "object/interface/thumpable_object.h"

#include "physics/physics.h"

#include <stdio.h>


const float START_TIME = 1000.0f;       // beginning of the relative time



// Object's constructor.

CMotionAnt::CMotionAnt(COldObject* object)
    : CMotion(object),
      m_armAngles()
{
    m_armMember      = START_TIME;
    m_armTimeAbs     = START_TIME;
    m_armTimeMarch   = START_TIME;
    m_armTimeAction  = START_TIME;
    m_lastParticle = 0.0f;
}

// Object's destructor.

CMotionAnt::~CMotionAnt()
{
}

// Creates a vehicle poses some rolling on the floor.

void CMotionAnt::Create()
{
    CMotion::Create();

    int member_march[] =
    {
    //  x1,y1,z1,   x2,y2,z2,   x3,y3,z3,   // in the air:
        0,45,0,     0,45,0,     0,50,0,     // t0: thighs 1..3
        30,-70,0,   20,-105,20, 25,-100,0,  // t0: legs 1..3
        -70,75,0,   -30,80,0,   -80,80,0,   // t0: feet 1..3
                                            // on the ground:
        0,30,0,     0,20,0,     0,15,0,     // t1: thighs 1..3
        -15,-50,0,  -20,-60,0,  -10,-75,0,  // t1: legs 1..3
        -40,50,0,   -25,15,0,   -50,35,0,   // t1: feet 1..3
                                            // on the ground back:
        0,35,0,     0,30,0,     0,20,0,     // t2: thighs 1..3
        -20,-15,0,  -30,-55,0,  -25,-70,15, // t2: legs 1..3
        -25,25,0,   -20,60,0,   -30,95,0,   // t2: feet 1..3
    };

    int member_stop[] =
    {
    //  x1,y1,z1,   x2,y2,z2,   x3,y3,z3,   // in the air:
        0,30,0,     0,20,0,     0,15,0,     // t0: thighs 1..3
        -15,-35,0,  -20,-60,0,  -15,-75,0,  // t0: legs 1..3
        -35,35,0,   -25,40,0,   -40,65,0,   // t0: feet 1..3
                                            // on the ground:
        0,30,0,     0,20,0,     0,15,0,     // t1: thighs 1..3
        -15,-35,0,  -20,-60,0,  -15,-75,0,  // t1: legs 1..3
        -35,35,0,   -25,40,0,   -40,65,0,   // t1: feet 1..3
                                            // on the ground back:
        0,30,0,     0,20,0,     0,15,0,     // t2: thighs 1..3
        -15,-35,0,  -20,-60,0,  -15,-75,0,  // t2: legs 1..3
        -35,35,0,   -25,40,0,   -40,65,0,   // t2: feet 1..3
    };

    int member_spec[] =
    {
    //  x1,y1,z1,   x2,y2,z2,   x3,y3,z3,   // prepares the fire:
        0,20,0,     0,10,0,     0,50,0,     // s0: thighs 1..3
        -50,-30,0,  -20,-15,0,  35,-65,0,   // s0: legs 1..3
        -5,-40,0,   20,-70,0,   -10,-40,0,  // s0: feet 1..3
                                            // shot:
        0,20,0,     0,10,0,     0,50,0,     // s1: thighs 1..3
        -50,-30,0,  -20,-15,0,  35,-65,0,   // s1: legs 1..3
        -5,-40,0,   20,-70,0,   -10,-40,0,  // s1: feet 1..3
                                            // ends the fire:
        0,30,0,     0,20,0,     0,15,0,     // s2: thighs 1..3
        -15,-50,0,  -20,-60,0,  -10,-75,0,  // s2: legs 1..3
        -40,50,0,   -25,15,0,   -50,35,0,   // s2: feet 1..3
                                            // burning:
        0,30,0,     0,20,0,     0,15,0,     // s3: thighs 1..3
        -15,-35,0,  -20,-60,0,  -15,-75,0,  // s3: legs 1..3
        -35,35,0,   -25,40,0,   -40,65,0,   // s3: feet 1..3
                                            // destroyed:
        0,30,0,     0,20,0,     0,15,0,     // s4: thighs 1..3
        -15,-35,0,  -20,-60,0,  -15,-75,0,  // s4: legs 1..3
        -35,35,0,   -25,40,0,   -40,65,0,   // s4: feet 1..3
                                            // back1 :
        0,30,0,     0,20,0,     0,15,0,     // s5: thighs 1..3
        -15,-35,0,  -20,-60,0,  -15,-75,0,  // s5: legs 1..3
        -35,35,0,   -25,40,0,   -40,65,0,   // s5: feet 1..3
                                            // back2 :
        0,45,0,     0,45,0,     0,50,0,     // s6: thighs 1..3
        -35,-70,0,  -20,-85,-25,    -25,-100,0, // s6: legs 1..3
        -110,75,-15,    -130,80,-25,    -125,40,0,  // s6: feet 1..3
                                            // back3 :
        0,30,0,     0,20,0,     0,15,0,     // s7: thighs 1..3
        -15,-35,0,  -20,-60,0,  -15,-75,0,  // s7: legs 1..3
        -35,35,0,   -25,40,0,   -40,65,0,   // s7: feet 1..3
    };

    int i;
    for ( i=0 ; i<3*3*3*3 ; i++ )
    {
        m_armAngles[3*3*3*3*MA_MARCH+i] = member_march[i];
    }
    for ( i=0 ; i<3*3*3*3 ; i++ )
    {
        m_armAngles[3*3*3*3*MA_STOP+i] = member_stop[i];
    }
    for ( i=0 ; i<3*3*3*8 ; i++ )
    {
        m_armAngles[3*3*3*3*MA_SPEC+i] = member_spec[i];
    }
}


// Management of an event.

bool CMotionAnt::EventProcess(const Event &event)
{
    CMotion::EventProcess(event);

    if ( event.type == EVENT_FRAME )
    {
        return EventFrame(event);
    }

    return true;
}

// Management of an event.

bool CMotionAnt::EventFrame(const Event &event)
{
    glm::vec3    dir, pos, speed;
    glm::vec2       dim;
    float       s, a, prog = 0.0f, time;
    float       tSt[9], tNd[9];
    int         i, ii, st, nd, action;
    bool        bStop;

    if ( m_engine->GetPause() )  return true;
    if ( !m_engine->IsVisiblePoint(m_object->GetPosition()) )  return true;

    s =     m_physics->GetLinMotionX(MO_MOTSPEED)*1.5f;
    a = fabs(m_physics->GetCirMotionY(MO_MOTSPEED)*2.0f);

    if ( s == 0.0f && a != 0.0f )  a *= 1.5f;

    m_armTimeAbs += event.rTime;
    m_armTimeMarch += (s)*event.rTime*0.15f;
    m_armMember += (s+a)*event.rTime*0.15f;

    bStop = ( a == 0.0f && s == 0.0f );  // stopped?

    action = MA_MARCH;  // walking
    if ( s == 0.0f && a == 0.0f )
    {
        action = MA_STOP;  // stop
    }

    if ( bStop )
    {
        prog = Math::Mod(m_armTimeAbs, 2.0f)/10.0f;
        a = Math::Mod(m_armMember, 1.0f);
        a = (prog-a)*event.rTime*2.0f;  // stop position is pleasantly
        m_armMember += a;
    }

    assert(m_object->Implements(ObjectInterfaceType::Destroyable));
    if ( dynamic_cast<CDestroyableObject*>(m_object)->GetDying() == DeathType::Burning )  // burning?
    {
        assert(m_object->Implements(ObjectInterfaceType::Thumpable));
        if ( dynamic_cast<CThumpableObject*>(m_object)->GetFixed() )
        {
            m_actionType = MAS_BURN;
        }
        else
        {
            m_actionType = -1;
        }
    }
    else if ( dynamic_cast<CDestroyableObject*>(m_object)->IsDying() )  // destroyed?
    {
        m_actionType = MAS_RUIN;
    }

    for ( i=0 ; i<6 ; i++ )  // the six legs
    {
        if ( m_actionType != -1 )  // special action in progress?
        {
            st = 3*3*3*3*MA_SPEC + 3*3*3*m_actionType + (i%3)*3;
            nd = st;
            time = event.rTime*m_actionTime;
            m_armTimeAction = 0.0f;
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
            st = 3*3*3*3*action + st*3*3*3 + (i%3)*3;
            nd = 3*3*3*3*action + nd*3*3*3 + (i%3)*3;

            // More and more soft ...
            time = event.rTime*(10.0f+Math::Min(m_armTimeAction*100.0f, 200.0f));
        }

        tSt[0] = m_armAngles[st+ 0];  // x
        tSt[1] = m_armAngles[st+ 1];  // y
        tSt[2] = m_armAngles[st+ 2];  // z
        tSt[3] = m_armAngles[st+ 9];  // x
        tSt[4] = m_armAngles[st+10];  // y
        tSt[5] = m_armAngles[st+11];  // z
        tSt[6] = m_armAngles[st+18];  // x
        tSt[7] = m_armAngles[st+19];  // y
        tSt[8] = m_armAngles[st+20];  // z

        tNd[0] = m_armAngles[nd+ 0];  // x
        tNd[1] = m_armAngles[nd+ 1];  // y
        tNd[2] = m_armAngles[nd+ 2];  // z
        tNd[3] = m_armAngles[nd+ 9];  // x
        tNd[4] = m_armAngles[nd+10];  // y
        tNd[5] = m_armAngles[nd+11];  // z
        tNd[6] = m_armAngles[nd+18];  // x
        tNd[7] = m_armAngles[nd+19];  // y
        tNd[8] = m_armAngles[nd+20];  // z

        if ( m_actionType == MAS_BACK2 )   // on the back?
        {
            for ( ii=0 ; ii<9 ; ii++ )
            {
                tSt[ii] += Math::Rand()*50.0f;
                tNd[ii] = tSt[ii];
            }
//?         time = 100.0f;
            time = event.rTime*10.0f;
        }

        if ( i < 3 )  // right leg (1..3) ?
        {
            m_object->SetPartRotationX(3+3*i+0, Math::Smooth(m_object->GetPartRotationX(3+3*i+0), Math::PropAngle(tSt[0], tNd[0], prog), time));
            m_object->SetPartRotationY(3+3*i+0, Math::Smooth(m_object->GetPartRotationY(3+3*i+0), Math::PropAngle(tSt[1], tNd[1], prog), time));
            m_object->SetPartRotationZ(3+3*i+0, Math::Smooth(m_object->GetPartRotationZ(3+3*i+0), Math::PropAngle(tSt[2], tNd[2], prog), time));
            m_object->SetPartRotationX(3+3*i+1, Math::Smooth(m_object->GetPartRotationX(3+3*i+1), Math::PropAngle(tSt[3], tNd[3], prog), time));
            m_object->SetPartRotationY(3+3*i+1, Math::Smooth(m_object->GetPartRotationY(3+3*i+1), Math::PropAngle(tSt[4], tNd[4], prog), time));
            m_object->SetPartRotationZ(3+3*i+1, Math::Smooth(m_object->GetPartRotationZ(3+3*i+1), Math::PropAngle(tSt[5], tNd[5], prog), time));
            m_object->SetPartRotationX(3+3*i+2, Math::Smooth(m_object->GetPartRotationX(3+3*i+2), Math::PropAngle(tSt[6], tNd[6], prog), time));
            m_object->SetPartRotationY(3+3*i+2, Math::Smooth(m_object->GetPartRotationY(3+3*i+2), Math::PropAngle(tSt[7], tNd[7], prog), time));
            m_object->SetPartRotationZ(3+3*i+2, Math::Smooth(m_object->GetPartRotationZ(3+3*i+2), Math::PropAngle(tSt[8], tNd[8], prog), time));
        }
        else    // left leg (4..6) ?
        {
            m_object->SetPartRotationX(3+3*i+0, Math::Smooth(m_object->GetPartRotationX(3+3*i+0), Math::PropAngle(-tSt[0], -tNd[0], prog), time));
            m_object->SetPartRotationY(3+3*i+0, Math::Smooth(m_object->GetPartRotationY(3+3*i+0), Math::PropAngle(-tSt[1], -tNd[1], prog), time));
            m_object->SetPartRotationZ(3+3*i+0, Math::Smooth(m_object->GetPartRotationZ(3+3*i+0), Math::PropAngle( tSt[2],  tNd[2], prog), time));
            m_object->SetPartRotationX(3+3*i+1, Math::Smooth(m_object->GetPartRotationX(3+3*i+1), Math::PropAngle(-tSt[3], -tNd[3], prog), time));
            m_object->SetPartRotationY(3+3*i+1, Math::Smooth(m_object->GetPartRotationY(3+3*i+1), Math::PropAngle(-tSt[4], -tNd[4], prog), time));
            m_object->SetPartRotationZ(3+3*i+1, Math::Smooth(m_object->GetPartRotationZ(3+3*i+1), Math::PropAngle( tSt[5],  tNd[5], prog), time));
            m_object->SetPartRotationX(3+3*i+2, Math::Smooth(m_object->GetPartRotationX(3+3*i+2), Math::PropAngle(-tSt[6], -tNd[6], prog), time));
            m_object->SetPartRotationY(3+3*i+2, Math::Smooth(m_object->GetPartRotationY(3+3*i+2), Math::PropAngle(-tSt[7], -tNd[7], prog), time));
            m_object->SetPartRotationZ(3+3*i+2, Math::Smooth(m_object->GetPartRotationZ(3+3*i+2), Math::PropAngle( tSt[8],  tNd[8], prog), time));
        }
    }

    if ( m_actionType == MAS_PREPARE )  // prepares the shooting?
    {
        prog = m_progress;

        dir.x = 0.0f;
        dir.y = 0.0f;
        dir.z = Math::PropAngle(0, -50, prog);
        SetTilt(dir);
        m_object->SetPartRotationZ(1, Math::PropAngle(0,  65, prog));  // head
        m_object->SetPartRotationZ(2, Math::PropAngle(0, -95, prog));  // tail
    }
    else if ( m_actionType == MAS_FIRE )  // shooting?
    {
        if ( m_progress < 0.75f )  a = m_progress/0.75f;
        else                       a = (1.0f-m_progress)/0.25f;
        m_object->SetPartScale(2, (a*0.5f)+1.0f);  // tail
        m_object->SetPartRotationX(2, (Math::Rand()-0.5f)*0.3f*a);
        m_object->SetPartRotationY(2, (Math::Rand()-0.5f)*0.3f*a);

        dir.x = (Math::Rand()-0.5f)*0.02f*a;
        dir.y = (Math::Rand()-0.5f)*0.05f*a;
        dir.z = (Math::Rand()-0.5f)*0.03f*a;
        SetCirVibration(dir);
    }
    else if ( m_actionType == MAS_TERMINATE )  // ends the shooting?
    {
        prog = 1.0f-m_progress;

        dir.x = 0.0f;
        dir.y = 0.0f;
        dir.z = Math::PropAngle(0, -50, prog);
        SetTilt(dir);
        m_object->SetPartRotationZ(1, Math::PropAngle(0,  65, prog));  // head
        m_object->SetPartRotationZ(2, Math::PropAngle(0, -95, prog));  // tail
    }
    else if ( m_actionType == MAS_BURN )  // burning?
    {
        dir = glm::vec3(Math::PI, 0.0f, 0.0f);
        SetCirVibration(dir);
        dir = glm::vec3(0.0f, -1.5f, 0.0f);
        SetLinVibration(dir);
        dir = glm::vec3(0.0f, 0.0f, 0.0f);
        SetTilt(dir);

        time = event.rTime*1.0f;
        m_object->SetPartRotationZ(1, Math::Smooth(m_object->GetPartRotationZ(1), 0.0f, time));  // head
        m_object->SetPartRotationZ(2, Math::Smooth(m_object->GetPartRotationZ(2), 0.0f, time));  // tail
    }
    else if ( m_actionType == MAS_RUIN )  // destroyed?
    {
        dir = glm::vec3(0.0f, 0.0f, 0.0f);
        SetLinVibration(dir);
        SetCirVibration(dir);
        SetTilt(dir);
    }
    else if ( m_actionType == MAS_BACK1 )  // starts on the back?
    {
        if ( m_lastParticle+m_engine->ParticleAdapt(0.05f) <= m_armTimeAbs )
        {
            m_lastParticle = m_armTimeAbs;

            pos = m_object->GetPosition();
            speed.x = (Math::Rand()-0.5f)*10.0f;
            speed.z = (Math::Rand()-0.5f)*10.0f;
            speed.y = Math::Rand()*5.0f;
            dim.x = Math::Rand()*3.0f+2.0f;
            dim.y = dim.x;
            m_particle->CreateParticle(pos, speed, dim, Gfx::PARTICRASH, 2.0f);
        }

        if ( m_progress < 0.5f )
        {
            dir.x = 0.0f;
            dir.y = powf(m_progress/0.5f, 2.0f)*12.0f;
            dir.z = 0.0f;
            SetLinVibration(dir);
        }
        else
        {
            dir.x = 0.0f;
            dir.y = powf(2.0f-m_progress/0.5f, 2.0f)*12.0f;
            dir.z = 0.0f;
            SetLinVibration(dir);
        }
        dir.x = m_progress*Math::PI;
        dir.y = 0.0f;
        dir.z = 0.0f;
        SetCirVibration(dir);

        dir = glm::vec3(0.0f, 0.0f, 0.0f);
        SetTilt(dir);

        if ( m_progress >= 1.0f )
        {
            SetAction(MAS_BACK2, 55.0f+Math::Rand()*10.0f);
        }
    }
    else if ( m_actionType == MAS_BACK2 )  // moves on the back?
    {
        if ( m_lastParticle+m_engine->ParticleAdapt(0.05f) <= m_armTimeAbs )
        {
            m_lastParticle = m_armTimeAbs;

            if ( rand()%10 == 0 )
            {
                pos = m_object->GetPosition();
                pos.x += (Math::Rand()-0.5f)*5.0f;
                pos.z += (Math::Rand()-0.5f)*5.0f;
                pos.y -= 1.0f;
                speed.x = (Math::Rand()-0.5f)*2.0f;
                speed.z = (Math::Rand()-0.5f)*2.0f;
                speed.y = Math::Rand()*2.0f;
                dim.x = Math::Rand()*1.0f+1.0f;
                dim.y = dim.x;
                m_particle->CreateParticle(pos, speed, dim, Gfx::PARTICRASH, 2.0f);
            }
        }

        dir = glm::vec3(0.0f, -1.0f, 0.0f);
        SetLinVibration(dir);
        dir.x = sinf(m_armTimeAbs* 4.0f)*0.10f+
                sinf(m_armTimeAbs* 7.0f)*0.20f+
                sinf(m_armTimeAbs*10.0f)*0.40f+
                sinf(m_armTimeAbs*21.0f)*0.50f+Math::PI;
        dir.y = sinf(m_armTimeAbs* 3.0f)*0.01f+
                sinf(m_armTimeAbs* 6.0f)*0.02f+
                sinf(m_armTimeAbs*11.0f)*0.04f+
                sinf(m_armTimeAbs*20.0f)*0.02f;
        dir.z = sinf(m_armTimeAbs* 5.0f)*0.01f+
                sinf(m_armTimeAbs* 8.0f)*0.02f+
                sinf(m_armTimeAbs* 9.0f)*0.04f+
                sinf(m_armTimeAbs*23.0f)*0.03f;
        SetCirVibration(dir);
        dir = glm::vec3(0.0f, 0.0f, 0.0f);
        SetTilt(dir);

        m_object->SetPartRotationY(1, sinf(m_armTimeAbs*8.0f)*0.7f);  // head
        m_object->SetPartRotationY(2, cosf(m_armTimeAbs*8.0f)*0.7f);  // tail
        m_object->SetPartRotationZ(1, 0.0f);  // head
        m_object->SetPartRotationZ(2, 0.0f);  // tail

        if ( m_progress >= 1.0f )
        {
            SetAction(MAS_BACK3, 0.4f);
        }
    }
    else if ( m_actionType == MAS_BACK3 )  // goes back on the legs?
    {
        if ( m_lastParticle+m_engine->ParticleAdapt(0.05f) <= m_armTimeAbs )
        {
            m_lastParticle = m_armTimeAbs;

            pos = m_object->GetPosition();
            speed.x = (Math::Rand()-0.5f)*10.0f;
            speed.z = (Math::Rand()-0.5f)*10.0f;
            speed.y = Math::Rand()*5.0f;
            dim.x = Math::Rand()*3.0f+2.0f;
            dim.y = dim.x;
            m_particle->CreateParticle(pos, speed, dim, Gfx::PARTICRASH, 2.0f);
        }

        if ( m_progress < 0.5f )
        {
            dir.x = 0.0f;
            dir.y = powf(m_progress/0.5f, 2.0f)*5.0f;
            dir.z = 0.0f;
            SetLinVibration(dir);
        }
        else
        {
            dir.x = 0.0f;
            dir.y = powf(2.0f-m_progress/0.5f, 2.0f)*5.0f;
            dir.z = 0.0f;
            SetLinVibration(dir);
        }
        dir.x = (1.0f-m_progress)*Math::PI;
        dir.y = 0.0f;
        dir.z = 0.0f;
        SetCirVibration(dir);

        dir = glm::vec3(0.0f, 0.0f, 0.0f);
        SetTilt(dir);

        if ( m_progress >= 1.0f )
        {
            SetAction(-1);
            assert(m_object->Implements(ObjectInterfaceType::Thumpable));
            dynamic_cast<CThumpableObject*>(m_object)->SetFixed(false);  // moving again
        }
    }
    else
    {
        m_object->SetPartScale(2, 1.0f);  // tail
        m_object->SetPartRotationX(2, 0.0f);
        m_object->SetPartRotationY(2, 0.0f);

        if ( bStop )
        {
            m_object->SetPartRotationZ(2, sinf(m_armTimeAbs*1.7f)*0.15f);  // tail

            dir = glm::vec3(0.0f, 0.0f, 0.0f);
            SetLinVibration(dir);
            SetTilt(dir);
        }
        else
        {
            a = Math::Mod(m_armTimeMarch, 1.0f);
            if ( a < 0.5f )  a = -1.0f+4.0f*a;  // -1..1
            else             a =  3.0f-4.0f*a;  // 1..-1
            dir.x = sinf(a)*0.05f;

            s = Math::Mod(m_armTimeMarch/2.0f, 1.0f);
            if ( s < 0.5f )  s = -1.0f+4.0f*s;  // -1..1
            else             s =  3.0f-4.0f*s;  // 1..-1
            dir.z = sinf(s)*0.1f;

            dir.y = 0.0f;
            SetTilt(dir);

            m_object->SetPartRotationZ(2, -sinf(a)*0.3f);  // tail

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
            SetLinVibration(dir);
        }

        dir = glm::vec3(0.0f, 0.0f, 0.0f);
        SetCirVibration(dir);

        m_object->SetPartRotationZ(1, sinf(m_armTimeAbs*1.4f)*0.20f);  // head
        m_object->SetPartRotationX(1, sinf(m_armTimeAbs*1.9f)*0.10f);  // head
        m_object->SetPartRotationY(1, sinf(m_armTimeAbs*2.1f)*0.50f);  // head
    }

    return true;
}
