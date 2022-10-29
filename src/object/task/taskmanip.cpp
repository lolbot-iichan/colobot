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


#include "object/task/taskmanip.h"

#include "graphics/engine/engine.h"
#include "graphics/engine/pyro_manager.h"
#include "graphics/engine/terrain.h"

#include "level/robotmain.h"

#include "math/geometry.h"

#include "object/object_manager.h"
#include "object/old_object.h"

#include "object/details/details_provider.h"
#include "object/details/slotted_details.h"
#include "object/details/task_executor_details.h"
#include "object/details/transportable_details.h"

#include "object/helpers/cargo_helpers.h"
#include "object/helpers/power_helpers.h"

#include "object/interface/slotted_object.h"

#include "physics/physics.h"

#include "sound/sound.h"

const int INVALID_SLOT = -1;

//?const float MARGIN_FRONT     = 2.0f;
//?const float MARGIN_BACK      = 2.0f;
//?const float MARGIN_FRIEND    = 2.0f;
//?const float MARGIN_BEE       = 5.0f;
const float MARGIN_FRONT    = 4.0f;  //OK 1.9
const float MARGIN_BACK     = 4.0f;  //OK 1.9
const float MARGIN_FRIEND   = 4.0f;  //OK 1.9
const float MARGIN_BEE      = 5.0f;  //OK 1.9




// Object's constructor.

CTaskManip::CTaskManip(COldObject* object) : CForegroundTask(object)
{
    m_arm  = TMA_NEUTRAL;
    m_hand = TMH_OPEN;
}

// Object's destructor.

CTaskManip::~CTaskManip()
{
}


// Management of an event.

bool CTaskManip::EventProcess(const Event &event)
{
    glm::vec3    pos;
    float       angle, a, g, cirSpeed, progress;
    int         i;

    if ( m_engine->GetPause() )  return true;
    if ( event.type != EVENT_FRAME )  return true;
    if ( m_bError )  return false;

    if ( m_bBee )  // bee?
    {
        return true;
    }

    if ( m_bTurn )  // preliminary rotation?
    {
        a = m_object->GetRotationY();
        g = m_angle;
        cirSpeed = Math::Direction(a, g)*1.0f;
        if ( m_object->Implements(ObjectInterfaceType::Flying) )  // flying on the ground?
        {
            cirSpeed *= 4.0f;  // more fishing
        }
        if ( cirSpeed >  1.0f )  cirSpeed =  1.0f;
        if ( cirSpeed < -1.0f )  cirSpeed = -1.0f;

        m_physics->SetMotorSpeedZ(cirSpeed);  // turns left / right
        return true;
    }

    if ( m_move != 0 )  // preliminary advance?
    {
        m_timeLimit -= event.rTime;
        m_physics->SetMotorSpeedX(m_move);  // forward/backward
        return true;
    }

    m_progress += event.rTime*m_speed;  // others advance
    progress = m_progress;
    if ( progress > 1.0f )  progress = 1.0f;

    if ( m_bSubm )  // submarine?
    {
        if ( m_order == TMO_GRAB )
        {
            if ( m_step == 0 )  // fall?
            {
                pos = m_object->GetPartPosition(1);
                pos.y = 3.0f-progress*2.0f;
                m_object->SetPartPosition(1, pos);
            }
            if ( m_step == 1 )  // farm?
            {
                pos = m_object->GetPartPosition(2);
                pos.z = -1.5f+progress*0.5f;
                m_object->SetPartPosition(2, pos);

                pos = m_object->GetPartPosition(3);
                pos.z = 1.5f-progress*0.5f;
                m_object->SetPartPosition(3, pos);
            }
            if ( m_step == 2 )  // up?
            {
                pos = m_object->GetPartPosition(1);
                pos.y = 3.0f-(1.0f-progress)*2.0f;
                m_object->SetPartPosition(1, pos);
            }
        }
        else
        {
            if ( m_step == 0 )  // fall?
            {
                pos = m_object->GetPartPosition(1);
                pos.y = 3.0f-progress*2.0f;
                m_object->SetPartPosition(1, pos);
            }
            if ( m_step == 1 )  // farm?
            {
                pos = m_object->GetPartPosition(2);
                pos.z = -1.5f+(1.0f-progress)*0.5f;
                m_object->SetPartPosition(2, pos);

                pos = m_object->GetPartPosition(3);
                pos.z = 1.5f-(1.0f-progress)*0.5f;
                m_object->SetPartPosition(3, pos);
            }
            if ( m_step == 2 )  // up?
            {
                pos = m_object->GetPartPosition(1);
                pos.y = 3.0f-(1.0f-progress)*2.0f;
                m_object->SetPartPosition(1, pos);
            }
        }
    }
    else
    {
        for ( i=0 ; i<5 ; i++ )
        {
            angle = (m_finalAngle[i]-m_initialAngle[i])*progress;
            angle += m_initialAngle[i];
            m_object->SetPartRotationZ(i+1, angle);
        }
    }

    return true;
}


// Initializes the initial and final angles.

void CTaskManip::InitAngle()
{
    if ( m_bSubm || m_bBee )  return;

    if ( m_arm == TMA_NEUTRAL ||
         m_arm == TMA_GRAB    )
    {
        m_finalAngle[0] = ARM_NEUTRAL_ANGLE1;  // arm
        m_finalAngle[1] = ARM_NEUTRAL_ANGLE2;  // forearm
        m_finalAngle[2] = ARM_NEUTRAL_ANGLE3;  // hand
    }
    if ( m_arm == TMA_STOCK )
    {
        m_finalAngle[0] = ARM_STOCK_ANGLE1;  // arm
        m_finalAngle[1] = ARM_STOCK_ANGLE2;  // forearm
        m_finalAngle[2] = ARM_STOCK_ANGLE3;  // hand
    }
    if ( m_arm == TMA_FFRONT )
    {
        m_finalAngle[0] =   35.0f*Math::PI/180.0f;  // arm
        m_finalAngle[1] =  -95.0f*Math::PI/180.0f;  // forearm
        m_finalAngle[2] =  -27.0f*Math::PI/180.0f;  // hand
    }
    if ( m_arm == TMA_FBACK )
    {
        m_finalAngle[0] =  145.0f*Math::PI/180.0f;  // arm
        m_finalAngle[1] =   95.0f*Math::PI/180.0f;  // forearm
        m_finalAngle[2] =   27.0f*Math::PI/180.0f;  // hand
    }
    if ( m_arm == TMA_POWER )
    {
        m_finalAngle[0] =   95.0f*Math::PI/180.0f;  // arm
        m_finalAngle[1] =  125.0f*Math::PI/180.0f;  // forearm
        m_finalAngle[2] =   50.0f*Math::PI/180.0f;  // hand
    }
    if ( m_arm == TMA_OTHER )
    {
        if ( m_height <= 3.0f )
        {
            m_finalAngle[0] =  55.0f*Math::PI/180.0f;  // arm
            m_finalAngle[1] = -90.0f*Math::PI/180.0f;  // forearm
            m_finalAngle[2] = -35.0f*Math::PI/180.0f;  // hand
        }
        else
        {
            m_finalAngle[0] =  70.0f*Math::PI/180.0f;  // arm
            m_finalAngle[1] = -90.0f*Math::PI/180.0f;  // forearm
            m_finalAngle[2] = -50.0f*Math::PI/180.0f;  // hand
        }
    }

    if ( m_hand == TMH_OPEN )  // open clamp?
    {
        m_finalAngle[3] = -Math::PI*0.10f;  // clamp close
        m_finalAngle[4] =  Math::PI*0.10f;  // clamp remote
    }
    if ( m_hand == TMH_CLOSE )  // clamp closed?
    {
        m_finalAngle[3] =  Math::PI*0.05f;  // clamp close
        m_finalAngle[4] = -Math::PI*0.05f;  // clamp remote
    }

    for (int i = 0; i < 5; i++)
    {
        m_initialAngle[i] = m_object->GetPartRotationZ(i+1);
    }

    float max = 0.0f;
    for (int i = 0;  i < 5; i++)
    {
        max = Math::Max(max, fabs(m_initialAngle[i] - m_finalAngle[i]));
    }
    m_speed = (Math::PI*1.0f)/max;
    if ( m_speed > 3.0f )  m_speed = 3.0f;  // piano, ma non troppo (?)

    float energy = GetObjectEnergy(m_object);
    if ( energy == 0.0f )
    {
        m_speed *= 0.7f;  // slower if no more energy!
    }
}

// Assigns the goal was achieved.

Error CTaskManip::Start(TaskManipOrder order, TaskManipArm arm)
{
    CObject      *front, *other;
    float        iAngle, dist, len;
    float        fDist, fAngle, oDist, oAngle, oHeight;
    glm::vec3    pos, fPos, oPos;

    m_arm      = arm;
    m_height   = 0.0f;
    m_step     = 0;
    m_progress = 0.0f;
    m_speed    = 1.0f/1.5f;

    iAngle = m_object->GetRotationY();
    iAngle = Math::NormAngle(iAngle);  // 0..2*Math::PI
    oAngle = iAngle;

    m_bError = true;  // operation impossible

    auto task = GetObjectTaskExecutorDetails(m_object).manip;
    m_bBee = task.execution == ExecutionNoMotion || task.execution == ExecutionAsInsect;  // bee?
    m_bSubm = task.execution == ExecutionAsSubber;  // submarine?

    if ( m_arm == TMA_GRAB )  // takes immediately?
    {
        TransporterTakeObject();
        Abort();
        return ERR_OK;
    }

    Error err = CanStartTask(&task);
    if ( err != ERR_OK )  return err;

    if ( m_arm == TMA_POWER && !HasPowerCellSlot(m_object) )
        return ERR_WRONG_BOT;

    if (!HasCargoSlot(m_object))
        return ERR_WRONG_BOT;

    if ( m_arm != TMA_FFRONT &&
         m_arm != TMA_FBACK  &&
         m_arm != TMA_POWER  )  return ERR_WRONG_BOT;

    if (m_object->Implements(ObjectInterfaceType::Movable))
        m_physics->SetMotorSpeed(glm::vec3(0.0f, 0.0f, 0.0f));

    if (m_bBee)  // bee?
    {
        if (!HasObjectInCargoSlot(m_object))
        {
            if ( !m_physics->GetLand() )  return ERR_MANIP_FLY;

            CObject* cargo = SearchTakeUnderObject(m_targetPos, MARGIN_BEE);

            if (cargo == nullptr)  return ERR_MANIP_NIL;

            SetObjectInCargoSlot(m_object, cargo);  // takes the ball
        }
        else
        {
            other = GetObjectInCargoSlot(m_object);  // other = ball
            SetObjectInCargoSlot(m_object, nullptr);   // lick the ball

            pos = m_object->GetPosition();
            other->SetPosition(pos + glm::vec3(0.0f, -3.0f, 0.0f));
            m_object->SetPosition(pos + glm::vec3(0.0f, 2.0f, 0.0f));  // against the top of jump

            m_engine->GetPyroManager()->Create(Gfx::PT_FALL, other);  // the ball falls
        }

        m_bBee = true;
        m_bError = false;  // ok
        return ERR_OK;
    }

    m_energy = GetObjectEnergy(m_object);

    if ( m_bSubm )  // submarine?
    {
        m_arm = TMA_FFRONT;  // only possible in front!
    }

    m_move = 0.0f;  // advance not necessary
    m_angle = iAngle;

    if ( order == TMO_AUTO )
    {
        m_order = HasObjectInCargoSlot(m_object) ? TMO_DROP : TMO_GRAB;
    }
    else
    {
        m_order = order;
    }

    if (m_order == TMO_GRAB && HasObjectInCargoSlot(m_object))
    {
        return ERR_MANIP_BUSY;
    }
    if (m_order == TMO_DROP && !HasObjectInCargoSlot(m_object))
    {
        return ERR_MANIP_EMPTY;
    }

    if ( m_order == TMO_GRAB )
    {
        if ( m_arm == TMA_FFRONT )
        {
            front = SearchTakeFrontObject(true, fPos, fDist, fAngle);
            int slotNum;
            other = SearchOtherObject(true, oPos, oDist, oAngle, oHeight, slotNum);

            if ( front != nullptr && fDist < oDist )
            {
                m_targetPos = fPos;
                m_angle = fAngle;
                m_move = 1.0f;  // advance required
            }
            else if ( other != nullptr && oDist < fDist )
            {
                if (GetObjectInSlot(other, slotNum) == nullptr) return ERR_MANIP_NIL;
                m_targetPos = oPos;
                m_angle = oAngle;
                m_height = oHeight;
                m_move = 1.0f;  // advance required
                m_arm = TMA_OTHER;
            }
            else
            {
                return ERR_MANIP_NIL;
            }
            m_main->HideDropZone(front);  // hides buildable area
        }
        if ( m_arm == TMA_FBACK )
        {
            if ( SearchTakeBackObject(true, m_targetPos, fDist, m_angle) == nullptr )
            {
                return ERR_MANIP_NIL;
            }
            m_angle += Math::PI;
            m_move = -1.0f;  // back necessary
        }
        if ( m_arm == TMA_POWER )
        {
            if (!HasObjectInPowerCellSlot(m_object))  return ERR_MANIP_NIL;
        }
    }

    if ( m_order == TMO_DROP )
    {
        if ( m_arm == TMA_FFRONT )
        {
            int slotNum;
            other = SearchOtherObject(true, oPos, oDist, oAngle, oHeight, slotNum);
            if (other != nullptr && GetObjectInSlot(other, slotNum) == nullptr)
            {
                m_targetPos = oPos;
                m_angle = oAngle;
                m_height = oHeight;
                m_move = 1.0f;  // advance required
                m_arm = TMA_OTHER;
            }
            else
            {
                if ( !IsFreeDeposeObject(glm::vec3(TAKE_DIST, 0.0f, 0.0f)) )  return ERR_MANIP_OCC;
            }
        }
        if ( m_arm == TMA_FBACK )
        {
            if ( !IsFreeDeposeObject(glm::vec3(-TAKE_DIST, 0.0f, 0.0f)) )  return ERR_MANIP_OCC;
        }
        if ( m_arm == TMA_POWER )
        {
            if (HasObjectInPowerCellSlot(m_object))  return ERR_MANIP_OCC;
        }
    }

    dist = glm::distance(m_object->GetPosition(), m_targetPos);
    len = dist-TAKE_DIST;
    if ( m_arm == TMA_OTHER ) len -= TAKE_DIST_OTHER;
    if ( len < 0.0f )  len = 0.0f;
    if ( m_arm == TMA_FBACK ) len = -len;

    if (m_object->Implements(ObjectInterfaceType::Movable))
    {
        m_advanceLength = dist-m_physics->GetLinLength(len);
        if ( dist <= m_advanceLength+0.2f )  m_move = 0.0f;  // not necessary to advance
    }

    if ( m_energy == 0.0f )  m_move = 0.0f;

    if ( m_move != 0.0f )  // forward or backward?
    {
        m_timeLimit = m_physics->GetLinTimeLength(fabs(len))*1.5f;
        if ( m_timeLimit < 0.5f )  m_timeLimit = 0.5f;
    }

    m_hand = HasObjectInCargoSlot(m_object) ? TMH_CLOSE : TMH_OPEN;  // open/closed clamp

    InitAngle();

    if ( iAngle == m_angle || m_energy == 0.0f )
    {
        m_bTurn = false;  // preliminary rotation unnecessary
        SoundManip(1.0f/m_speed);
    }
    else
    {
        m_bTurn = true;  // preliminary rotation necessary
    }

    if ( m_bSubm )
    {
        m_camera->StartCentering(m_object, Math::PI*0.8f, 99.9f, 0.0f, 0.5f);
    }

    if (m_object->Implements(ObjectInterfaceType::Movable))
        m_physics->SetFreeze(true);  // it does not move

    m_bError = false;  // ok
    return ERR_OK;
}

// Indicates whether the action is complete.

Error CTaskManip::IsEnded()
{
    float       angle, dist;
    int         i;

    if ( m_engine->GetPause() )  return ERR_CONTINUE;
    if ( m_bError )  return ERR_STOP;

    if ( m_bBee )  // bee?
    {
        return ERR_STOP;
    }

    if ( m_bTurn )  // preliminary rotation?
    {
        angle = m_object->GetRotationY();
        angle = Math::NormAngle(angle);  // 0..2*Math::PI

        if ( Math::TestAngle(angle, m_angle-Math::PI*0.01f, m_angle+Math::PI*0.01f) )
        {
            m_bTurn = false;  // rotation ended
            m_physics->SetMotorSpeedZ(0.0f);
            if ( m_move == 0.0f )
            {
                SoundManip(1.0f/m_speed);
            }
        }
        return ERR_CONTINUE;
    }

    if ( m_move != 0.0f )  // preliminary advance?
    {
        if ( m_timeLimit <= 0.0f )
        {
//OK 1.9
            dist = glm::distance(m_object->GetPosition(), m_targetPos);
            if ( dist <= m_advanceLength + 2.0f )
            {
                m_move = 0.0f;  // advance ended
                m_physics->SetMotorSpeedX(0.0f);
                SoundManip(1.0f/m_speed);
                return ERR_CONTINUE;
            }
            else
            {
//EOK 1.9
                m_move = 0.0f;  // advance ended
                m_physics->SetMotorSpeedX(0.0f);  // stops
                Abort();
                return ERR_STOP;
            }
        }

        dist = glm::distance(m_object->GetPosition(), m_targetPos);
        if ( dist <= m_advanceLength )
        {
            m_move = 0.0f;  // advance ended
            m_physics->SetMotorSpeedX(0.0f);
            SoundManip(1.0f/m_speed);
        }
        return ERR_CONTINUE;
    }

    if ( m_progress < 1.0f )  return ERR_CONTINUE;
    m_progress = 0.0f;

    if ( !m_bSubm )
    {
        for ( i=0 ; i<5 ; i++ )
        {
            m_object->SetPartRotationZ(i+1, m_finalAngle[i]);
        }
    }
    m_step ++;

    if ( m_order == TMO_GRAB )
    {
        if ( m_step == 1 )
        {
            if ( m_bSubm )  m_speed = 1.0f/0.7f;
            m_hand = TMH_CLOSE;  // closes the clamp to take
            InitAngle();
            SoundManip(1.0f/m_speed, 0.8f, 1.5f);
            return ERR_CONTINUE;
        }
        if ( m_step == 2 )
        {
            if ( m_bSubm )  m_speed = 1.0f/1.5f;

            if ( !TransporterTakeObject() && !GetObjectInCargoSlot(m_object) )
            {
                m_hand = TMH_OPEN;  // reopens the clamp
                m_arm = TMA_NEUTRAL;
                InitAngle();
                SoundManip(1.0f/m_speed, 0.8f, 1.5f);
            }
            else
            {
                CObject* cargo = GetObjectInCargoSlot(m_object);
                if ( (m_arm == TMA_OTHER || m_arm == TMA_POWER ) && cargo != nullptr &&
                     cargo->Implements(ObjectInterfaceType::PowerContainer) )
                {
                    m_sound->Play(SOUND_POWEROFF, m_object->GetPosition());
                }
                m_arm = TMA_STOCK;
                InitAngle();
                SoundManip(1.0f/m_speed);
            }
            return ERR_CONTINUE;
        }
    }

    if ( m_order == TMO_DROP )
    {
        if ( m_step == 1 )
        {
            if ( m_bSubm )  m_speed = 1.0f/0.7f;
            CObject* cargo = GetObjectInCargoSlot(m_object);
            if (TransporterDeposeObject() && cargo != nullptr)
            {
                if ( (m_arm == TMA_OTHER || m_arm == TMA_POWER ) &&
                     cargo->Implements(ObjectInterfaceType::PowerContainer) )
                {
                    m_sound->Play(SOUND_POWERON, m_object->GetPosition());
                }
                if ( m_arm == TMA_FFRONT && GetObjectTransportableDetails(cargo).showDropZone )
                {
                    m_main->ShowDropZone(cargo, m_object);  // shows buildable area
                }
                m_hand = TMH_OPEN;  // opens the clamp to deposit
                SoundManip(1.0f/m_speed, 0.8f, 1.5f);
            }
            InitAngle();
            return ERR_CONTINUE;
        }
        if ( m_step == 2 )
        {
            if ( m_bSubm )  m_speed = 1.0f/1.5f;
            m_arm = TMA_NEUTRAL;
            InitAngle();
            SoundManip(1.0f/m_speed);
            return ERR_CONTINUE;
        }
    }

    Abort();
    return ERR_STOP;
}

// Suddenly ends the current action.

bool CTaskManip::Abort()
{
    if (!HasObjectInCargoSlot(m_object))  // not carrying anything?
    {
        m_hand = TMH_OPEN;  // open clamp
        m_arm = TMA_NEUTRAL;
    }
    else
    {
        m_hand = TMH_CLOSE;  // closed clamp
        m_arm = TMA_STOCK;
    }
    InitAngle();

    if ( !m_bSubm )
    {
        for (int i = 0; i < 5; i++)
        {
            m_object->SetPartRotationZ(i+1, m_finalAngle[i]);
        }
    }

    m_camera->StopCentering(m_object, 2.0f);

    if (m_object->Implements(ObjectInterfaceType::Movable))
        m_physics->SetFreeze(false);  // is moving again

    return true;
}


// Seeks the object below to take (for bees).

CObject* CTaskManip::SearchTakeUnderObject(glm::vec3 &pos, float dLimit)
{
    CObject    *pBest;
    glm::vec3    iPos, oPos;
    float       min, distance;

    iPos   = m_object->GetPosition();

    min = 1000000.0f;
    pBest = nullptr;
    for (CObject* pObj : CObjectManager::GetInstancePointer()->GetAllObjects())
    {
        if ( !pObj->Implements(ObjectInterfaceType::Transportable) )  continue;

        if (IsObjectBeingTransported(pObj))  continue;
        if ( pObj->GetLock() )  continue;
        if ( pObj->GetScaleY() != 1.0f )  continue;

        oPos = pObj->GetPosition();
        distance = glm::distance(oPos, iPos);
        if ( distance <= dLimit &&
             distance < min     )
        {
            min = distance;
            pBest = pObj;
        }
    }
    if ( pBest != nullptr )
    {
        pos = pBest->GetPosition();
    }
    return pBest;
}

// Seeks the object in front to take.

CObject* CTaskManip::SearchTakeFrontObject(bool bAdvance, glm::vec3 &pos,
                                           float &distance, float &angle)
{
    CObject     *pBest;
    glm::vec3    iPos, oPos;
    float       min, iAngle, bAngle, aLimit, dLimit, f;

    iPos   = m_object->GetPosition();
    iAngle = m_object->GetRotationY();
    iAngle = Math::NormAngle(iAngle);  // 0..2*Math::PI

    if ( bAdvance && m_energy > 0.0f )
    {
        aLimit = 60.0f*Math::PI/180.0f;
        dLimit = MARGIN_FRONT+10.0f;
    }
    else
    {
//?     aLimit = 7.0f*Math::PI/180.0f;
        aLimit = 15.0f*Math::PI/180.0f;  //OK 1.9
        dLimit = MARGIN_FRONT;
    }

    min = 1000000.0f;
    pBest = nullptr;
    bAngle = 0.0f;
    for (CObject* pObj : CObjectManager::GetInstancePointer()->GetAllObjects())
    {
        if ( !pObj->Implements(ObjectInterfaceType::Transportable) )  continue;

        if (IsObjectBeingTransported(pObj))  continue;
        if ( pObj->GetLock() )  continue;
        if ( pObj->GetScaleY() != 1.0f )  continue;

        oPos = pObj->GetPosition();
        distance = fabs(glm::distance(oPos, iPos)-TAKE_DIST);
        f = 1.0f-distance/50.0f;
        if ( f < 0.5f )  f = 0.5f;

        angle = Math::RotateAngle(oPos.x-iPos.x, iPos.z-oPos.z);  // CW !
        if ( !Math::TestAngle(angle, iAngle-aLimit*f, iAngle+aLimit*f) )  continue;

        if ( distance < -dLimit ||
             distance >  dLimit )  continue;

        if ( distance < min )
        {
            min = distance;
            pBest = pObj;
            bAngle = angle;
        }
    }
    if ( pBest == nullptr )
    {
        distance = 1000000.0f;
        angle = 0.0f;
    }
    else
    {
        pos = pBest->GetPosition();
        distance = min;
        angle = bAngle;
    }
    return pBest;
}

// Seeks the object back to take.

CObject* CTaskManip::SearchTakeBackObject(bool bAdvance, glm::vec3 &pos,
                                          float &distance, float &angle)
{
    CObject     *pBest;
    glm::vec3    iPos, oPos;
    float       min, iAngle, bAngle, aLimit, dLimit, f;

    iPos   = m_object->GetPosition();
    iAngle = m_object->GetRotationY()+Math::PI;
    iAngle = Math::NormAngle(iAngle);  // 0..2*Math::PI

    if ( bAdvance && m_energy > 0.0f )
    {
        aLimit = 60.0f*Math::PI/180.0f;
        dLimit = MARGIN_BACK+5.0f;
    }
    else
    {
        aLimit = 7.0f*Math::PI/180.0f;
        dLimit = MARGIN_BACK;
    }

    min = 1000000.0f;
    pBest = nullptr;
    bAngle = 0.0f;
    for (CObject* pObj : CObjectManager::GetInstancePointer()->GetAllObjects())
    {
        if ( !pObj->Implements(ObjectInterfaceType::Transportable) )  continue;

        if (IsObjectBeingTransported(pObj))  continue;
        if ( pObj->GetLock() )  continue;
        if ( pObj->GetScaleY() != 1.0f )  continue;

        oPos = pObj->GetPosition();
        distance = fabs(glm::distance(oPos, iPos)-TAKE_DIST);
        f = 1.0f-distance/50.0f;
        if ( f < 0.5f )  f = 0.5f;

        angle = Math::RotateAngle(oPos.x-iPos.x, iPos.z-oPos.z);  // CW !
        if ( !Math::TestAngle(angle, iAngle-aLimit*f, iAngle+aLimit*f) )  continue;

        if ( distance < -dLimit ||
             distance >  dLimit )  continue;

        if ( distance < min )
        {
            min = distance;
            pBest = pObj;
            bAngle = angle;
        }
    }
    if ( pBest == nullptr )
    {
        distance = 1000000.0f;
        angle = 0.0f;
    }
    else
    {
        pos = pBest->GetPosition();
        distance = min;
        angle = bAngle;
    }
    return pBest;
}

// Seeks the robot or building on which it wants to put a battery or or other object.

CObject* CTaskManip::SearchOtherObject(bool bAdvance, glm::vec3 &pos,
                                       float &distance, float &angle,
                                       float &height, int &slotNumOut)
{
    slotNumOut = INVALID_SLOT;
    distance = 1000000.0f;
    angle = 0.0f;

    float       iAngle, aLimit, dLimit;

    if ( m_bSubm )  return nullptr;  // impossible with the submarine

    if (m_object->GetCrashSphereCount() == 0) return nullptr;

    auto crashSphere = m_object->GetFirstCrashSphere();
    glm::vec3 iPos = crashSphere.sphere.pos;
    float iRad = crashSphere.sphere.radius;

    iAngle = m_object->GetRotationY();
    iAngle = Math::NormAngle(iAngle);  // 0..2*Math::PI

    if ( bAdvance && m_energy > 0.0f )
    {
        aLimit = 60.0f*Math::PI/180.0f;
        dLimit = MARGIN_FRIEND+10.0f;
    }
    else
    {
        aLimit = 7.0f*Math::PI/180.0f;
        dLimit = MARGIN_FRIEND;
    }

    for (CObject* pObj : CObjectManager::GetInstancePointer()->GetAllObjects())
    {
        if ( pObj == m_object )  continue;  // yourself?
        if (!pObj->Implements(ObjectInterfaceType::Slotted))  continue;
        if (IsObjectBeingTransported(pObj))  continue;
 
        CSlottedObject *obj = dynamic_cast<CSlottedObject*>(pObj);
        int slotNum = GetNumSlots(pObj);
        for (int slot = 0; slot < slotNum; slot++)
        {
            CObject *objectInSlot = GetObjectInSlot(pObj, slot);
            if (objectInSlot != nullptr && (objectInSlot->GetLock() || objectInSlot->GetScaleY() != 1.0f))
                continue;

            float objectAngleOffsetLimit = obj->GetSlotAcceptanceAngle(slot);
            if (objectAngleOffsetLimit == 0)
                continue; // slot isn't take-able

            glm::mat4 mat = pObj->GetWorldMatrix(0);
            glm::vec3 worldSlotPos = Math::Transform(mat, obj->GetSlotPosition(slot));

            // The robot must be in the correct angle relative to the slot (it can't be on the other side of the object)
            float angleFromObjectToRobot = Math::RotateAngle(iPos.x-worldSlotPos.x, worldSlotPos.z-iPos.z);  // CW !
            float objectIdealAngle = Math::NormAngle(pObj->GetRotationY() + obj->GetSlotAngle(slot));

            if ( Math::TestAngle(angleFromObjectToRobot, objectIdealAngle - objectAngleOffsetLimit, objectIdealAngle + objectAngleOffsetLimit) )
            {
                distance = fabs(glm::distance(worldSlotPos, iPos)-TAKE_DIST);
                // The robot must be close enough to the slot
                if ( distance <= dLimit )
                {
                    // The slot must be in the correct position relative to the robot (the robot must be facing towards the slot, not sideways or away)
                    angle = Math::RotateAngle(worldSlotPos.x-iPos.x, iPos.z-worldSlotPos.z);  // CW !
                    if ( Math::TestAngle(angle, iAngle-aLimit, iAngle+aLimit) )
                    {
                        glm::vec3 powerPos = obj->GetSlotPosition(slot);
                        height = powerPos.y;
                        pos = worldSlotPos;
                        slotNumOut = slot;
                        return pObj;
                    }
                }
            }
        }
    }

    distance = 1000000.0f;
    angle = 0.0f;
    return nullptr;
}

// Takes the object placed in front.

bool CTaskManip::TransporterTakeObject()
{
    glm::vec3 pos;
    float dist = 0.0f;
    float angle = 0.0f;

    CObject *cargo = nullptr;

    if (m_arm == TMA_GRAB)  // takes immediately?
    {
        cargo = GetObjectInCargoSlot(m_object);
    }
    if (m_arm == TMA_FFRONT)  // takes on the ground in front?
    {
        cargo = SearchTakeFrontObject(false, pos, dist, angle);
    }
    if (m_arm == TMA_FBACK)  // takes on the ground behind?
    {
        cargo = SearchTakeBackObject(false, pos, dist, angle);
    }
    if (m_arm == TMA_POWER)  // takes battery in the back?
    {
        cargo = GetObjectInPowerCellSlot(m_object);
        SetObjectInPowerCellSlot(m_object, nullptr);
    }
    if (m_arm == TMA_OTHER)  // battery takes from friend?
    {
        int slotNum = INVALID_SLOT;
        CObject* other = SearchOtherObject(false, pos, dist, angle, m_height, slotNum);
        if (other == nullptr)  return false;
        assert(slotNum != INVALID_SLOT);

        cargo = GetObjectInSlot(other, slotNum);

        SetObjectInSlot(other, slotNum, nullptr);
    }

    if (cargo == nullptr)  return false;  // nothing to take ?

    SetObjectInCargoSlot(m_object, cargo);  // takes

    return true;
}

// Deposes the object taken.

bool CTaskManip::TransporterDeposeObject()
{
    CObject* cargo = GetObjectInCargoSlot(m_object);
    if (cargo == nullptr)  return false;  // nothing transported?
    assert(cargo->Implements(ObjectInterfaceType::Transportable));

    if (m_arm == TMA_FFRONT)  // deposits on the ground in front?
    {
        glm::mat4 mat = cargo->GetWorldMatrix(0);
        glm::vec3 pos = Math::Transform(mat, glm::vec3(0.0f, 1.0f, 0.0f));
        m_terrain->AdjustToFloor(pos);
        cargo->SetPosition(pos);
//??    cargo->SetRotationY(m_object->GetRotationY()+Math::PI/2.0f);
        cargo->SetRotationY(0.0f);
        cargo->SetRotationX(0.0f);
        cargo->SetRotationZ(0.0f);
        cargo->SetFloorHeight(0.0f);
        cargo->FloorAdjust();  // plate well on the ground

        SetObjectInCargoSlot(m_object, nullptr);  // deposit
    }

    if (m_arm == TMA_FBACK)  // deposited on the ground behind?
    {
        glm::mat4 mat = cargo->GetWorldMatrix(0);
        glm::vec3 pos = Math::Transform(mat, glm::vec3(0.0f, 1.0f, 0.0f));
        m_terrain->AdjustToFloor(pos);
        cargo->SetPosition(pos);
//??    cargo->SetRotationY(m_object->GetRotationY()+Math::PI/2.0f);
        cargo->SetRotationY(0.0f);
        cargo->SetRotationX(0.0f);
        cargo->SetRotationZ(0.0f);
        cargo->SetFloorHeight(0.0f);
        cargo->FloorAdjust();  // plate well on the ground

        SetObjectInCargoSlot(m_object, nullptr);  // deposit
    }

    if (m_arm == TMA_POWER)  // deposits battery in the back?
    {
        if (HasObjectInPowerCellSlot(m_object))  return false;

        SetObjectInCargoSlot(m_object, nullptr);  // deposit
        SetObjectInPowerCellSlot(m_object, cargo);  // deposit
    }

    if (m_arm == TMA_OTHER)  // deposits battery on friend?
    {
        glm::vec3 pos;
        float angle = 0.0f, dist = 0.0f;

        int slotNum = INVALID_SLOT;
        CObject* other = SearchOtherObject(false, pos, dist, angle, m_height, slotNum);
        if (other == nullptr)  return false;
        assert(slotNum != INVALID_SLOT);

        if (GetObjectInSlot(other, slotNum) != nullptr)  return false;  // the other already has a battery?

        SetObjectInCargoSlot(m_object, nullptr);  // deposit
        SetObjectInSlot(other, slotNum, cargo);
    }

    return true;
}

// Seeks if a location allows to deposit an object.

bool CTaskManip::IsFreeDeposeObject(glm::vec3 pos)
{
    glm::mat4 mat = m_object->GetWorldMatrix(0);
    glm::vec3 iPos = Math::Transform(mat, pos);

    for (CObject* obj : CObjectManager::GetInstancePointer()->GetAllObjects())
    {
        if ( obj == m_object )  continue;
        if ( !obj->GetDetectable() )  continue;  // inactive?
        if (IsObjectBeingTransported(obj))  continue;

        for (const auto& crashSphere : obj->GetAllCrashSpheres())
        {
            if ( glm::distance(iPos, crashSphere.sphere.pos)-(crashSphere.sphere.radius+1.0f) < 2.0f )
            {
                return false;  // location occupied
            }
        }
    }
    return true;  // location free
}

// Plays the sound of the manipulator arm.

void CTaskManip::SoundManip(float time, float amplitude, float frequency)
{
    int i = m_sound->Play(SOUND_MANIP, m_object->GetPosition(), 0.0f, 0.3f*frequency, true);
    m_sound->AddEnvelope(i, 0.5f*amplitude, 1.0f*frequency, 0.1f, SOPER_CONTINUE);
    m_sound->AddEnvelope(i, 0.5f*amplitude, 1.0f*frequency, time-0.1f, SOPER_CONTINUE);
    m_sound->AddEnvelope(i, 0.0f, 0.3f*frequency, 0.1f, SOPER_STOP);
}
