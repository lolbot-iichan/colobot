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


#include "object/task/tasktake.h"

#include "graphics/engine/engine.h"
#include "graphics/engine/terrain.h"
#include "graphics/engine/water.h"

#include "level/robotmain.h"

#include "math/geometry.h"

#include "object/object_manager.h"
#include "object/old_object.h"

#include "object/details/details_provider.h"
#include "object/details/slotted_details.h"
#include "object/details/task_executor_details.h"
#include "object/details/transportable_details.h"

#include "object/helpers/cargo_helpers.h"

#include "object/interface/slotted_object.h"

#include "object/motion/motionhuman.h"

#include "physics/physics.h"

#include "sound/sound.h"

const int INVALID_SLOT = -1;

// Object's constructor.

CTaskTake::CTaskTake(COldObject* object) : CForegroundTask(object)
{
}

// Object's destructor.

CTaskTake::~CTaskTake()
{
}


// Management of an event.

bool CTaskTake::EventProcess(const Event &event)
{
    float       a, g, cirSpeed;

    if ( m_engine->GetPause() )  return true;
    if ( event.type != EVENT_FRAME )  return true;
    if ( m_bError )  return false;

    if ( m_bTurn )  // preliminary rotation?
    {
        a = m_object->GetRotationY();
        g = m_angle;
        cirSpeed = Math::Direction(a, g)*2.0f;
        if ( cirSpeed >  1.0f )  cirSpeed =  1.0f;
        if ( cirSpeed < -1.0f )  cirSpeed = -1.0f;

        m_physics->SetMotorSpeedZ(cirSpeed);  // turns left / right
        return true;
    }

    m_progress += event.rTime*m_speed;  // others advance

    m_physics->SetMotorSpeed(glm::vec3(0.0f, 0.0f, 0.0f));  // immobile!

    return true;
}


// Assigns the goal was achieved.

Error CTaskTake::Start()
{
    m_height   = 0.0f;
    m_step     = 0;
    m_progress = 0.0f;

    float iAngle = m_object->GetRotationY();
    iAngle = Math::NormAngle(iAngle);  // 0..2*Math::PI
    float oAngle = iAngle;

    m_bError = true;  // operation impossible

    auto task = GetObjectTaskExecutorDetails(m_object).take;

    Error err = CanStartTask(&task);
    if ( err != ERR_OK )  return err;

    if (!HasCargoSlot(m_object))
        return ERR_WRONG_BOT;

    if (!m_object->Implements(ObjectInterfaceType::Movable))
        return ERR_WRONG_BOT;

    m_physics->SetMotorSpeed(glm::vec3(0.0f, 0.0f, 0.0f));

    m_order = HasObjectInCargoSlot(m_object) ? TTO_DEPOSE : TTO_TAKE;

    if ( m_order == TTO_TAKE )
    {
        glm::vec3 pos = m_object->GetPosition();
        float h = m_water->GetLevel(m_object);
        if ( pos.y < h )  return ERR_MANIP_WATER;  // impossible under water

        int slotNum = -1;
        CObject* other = SearchFriendObject(oAngle, 1.5f, Math::PI*0.50f, m_height, slotNum);
        CSlottedObject* otherAsSlotted = dynamic_cast<CSlottedObject*>(other);
        assert(other == nullptr || slotNum >= 0);

        if (other != nullptr && GetObjectInSlot(other, slotNum) != nullptr)
        {
            CObject* power = GetObjectInSlot(other, slotNum);
            assert(power->Implements(ObjectInterfaceType::Transportable));
            if ( GetObjectTransportableDetails(power).radioactive )  return ERR_MANIP_RADIO;
//?         m_camera->StartCentering(m_object, Math::PI*0.3f, -Math::PI*0.1f, 0.0f, 0.8f);
            m_arm = TTA_FRIEND;
        }
        else
        {
            other = SearchTakeObject(oAngle, 1.5f, Math::PI*0.45f);
            if ( other == nullptr )  return ERR_MANIP_NIL;
            assert(other->Implements(ObjectInterfaceType::Transportable));
            if ( GetObjectTransportableDetails(other).radioactive )  return ERR_MANIP_RADIO;
//?         m_camera->StartCentering(m_object, Math::PI*0.3f, 99.9f, 0.0f, 0.8f);
            m_arm = TTA_FFRONT;
            m_main->HideDropZone(other);  // hides buildable area
        }
    }

    if ( m_order == TTO_DEPOSE )
    {
        int slotNum = -1;
        CObject* other = SearchFriendObject(oAngle, 1.5f, Math::PI*0.50f, m_height, slotNum);
        CSlottedObject* otherAsSlotted = dynamic_cast<CSlottedObject*>(other);
        assert(other == nullptr || slotNum >= 0);

        if (other != nullptr && GetObjectInSlot(other, slotNum) == nullptr)
        {
//?         m_camera->StartCentering(m_object, Math::PI*0.3f, -Math::PI*0.1f, 0.0f, 0.8f);
            m_arm = TTA_FRIEND;
        }
        else
        {
            if ( !IsFreeDeposeObject(glm::vec3(2.5f, 0.0f, 0.0f)) )  return ERR_MANIP_OCC;
//?         m_camera->StartCentering(m_object, Math::PI*0.3f, 99.9f, 0.0f, 0.8f);
            m_arm = TTA_FFRONT;
        }
    }

    m_bTurn = true;  // preliminary rotation necessary
    m_angle = oAngle;  // angle was reached

    m_physics->SetFreeze(true);  // it does not move

    m_bError = false;  // ok
    return ERR_OK;
}

// Indicates whether the action is finished.

Error CTaskTake::IsEnded()
{
    if ( m_engine->GetPause() )  return ERR_CONTINUE;
    if ( m_bError )  return ERR_STOP;

    if ( m_bTurn )  // preliminary rotation?
    {
        float angle = m_object->GetRotationY();
        angle = Math::NormAngle(angle);  // 0..2*Math::PI

        if ( Math::TestAngle(angle, m_angle-Math::PI*0.01f, m_angle+Math::PI*0.01f) )
        {
            m_bTurn = false;  // rotation ended
            m_physics->SetMotorSpeedZ(0.0f);

            if ( m_arm == TTA_FFRONT )
            {
                m_motion->SetAction(MHS_TAKE, 0.2f);  // will decrease
            }
            if ( m_arm == TTA_FRIEND )
            {
                if ( m_height <= 3.0f )
                {
                    m_motion->SetAction(MHS_TAKEOTHER, 0.2f);  // will decrease
                }
                else
                {
                    m_motion->SetAction(MHS_TAKEHIGH, 0.2f);  // will decrease
                }
            }
            m_progress = 0.0f;
            m_speed = 1.0f/0.6f;
        }
        return ERR_CONTINUE;
    }

    if ( m_progress < 1.0f )  return ERR_CONTINUE;
    m_progress = 0.0f;

    m_step ++;

    if ( m_order == TTO_TAKE )
    {
        if ( m_step == 1 )
        {
            if ( TransporterTakeObject() )
            {
                CObject* cargo = GetObjectInCargoSlot(m_object);
                if ( m_arm == TTA_FRIEND && cargo != nullptr &&
                     cargo->Implements(ObjectInterfaceType::PowerContainer) )
                {
                    m_sound->Play(SOUND_POWEROFF, m_object->GetPosition());
                }
            }
            m_motion->SetAction(MHS_UPRIGHT, 0.4f);  // gets up
            m_progress = 0.0f;
            m_speed = 1.0f/0.8f;
            m_camera->StopCentering(m_object, 0.8f);
            return ERR_CONTINUE;
        }
    }

    if ( m_order == TTO_DEPOSE )
    {
        if ( m_step == 1 )
        {
            CObject* cargo = GetObjectInCargoSlot(m_object);
            TransporterDeposeObject();
            if ( m_arm == TTA_FRIEND && cargo->Implements(ObjectInterfaceType::PowerContainer) )
            {
                m_sound->Play(SOUND_POWERON, m_object->GetPosition());
            }
            if ( m_arm == TTA_FFRONT && cargo != nullptr )
            {
                if ( GetObjectTransportableDetails(cargo).showDropZone )
                {
                    m_main->ShowDropZone(cargo, m_object);  // shows buildable area
                }
            }
            m_motion->SetAction(-1);  // gets up
            m_progress = 0.0f;
            m_speed = 1.0f/0.4f;
            m_camera->StopCentering(m_object, 0.8f);
            return ERR_CONTINUE;
        }
    }

    Abort();
    return ERR_STOP;
}

// Suddenly ends the current action.

bool CTaskTake::Abort()
{
    m_motion->SetAction(-1);
    m_camera->StopCentering(m_object, 0.8f);
    m_physics->SetFreeze(false);  // is moving again
    return true;
}


// Seeks the object to take in front.

CObject* CTaskTake::SearchTakeObject(float &angle,
                                     float dLimit, float aLimit)
{
    CObject     *pBest;
    glm::vec3    iPos, oPos;
    float       min, iAngle, bAngle, a, distance;

    iPos   = m_object->GetPosition();
    iAngle = m_object->GetRotationY();
    iAngle = Math::NormAngle(iAngle);  // 0..2*Math::PI

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
        distance = glm::distance(oPos, iPos);
        if ( distance >= 4.0f-dLimit &&
             distance <= 4.0f+dLimit )
        {
            angle = Math::RotateAngle(oPos.x-iPos.x, iPos.z-oPos.z);  // CW !
            if ( Math::TestAngle(angle, iAngle-aLimit, iAngle+aLimit) )
            {
                a = fabs(angle-iAngle);
                if ( a > Math::PI )  a = Math::PI*2.0f-a;
                if ( a < min )
                {
                    min = a;
                    pBest = pObj;
                    bAngle = angle;
                }
            }
        }
    }
    angle = bAngle;
    return pBest;
}

// Seeks the robot on which you want take or put a battery.

CObject* CTaskTake::SearchFriendObject(float &angle,
                                       float dLimit, float aLimit,
                                       float &height, int &slotNumOut)
{
    if (m_object->GetCrashSphereCount() == 0) return nullptr;

    auto crashSphere = m_object->GetFirstCrashSphere();
    glm::vec3 iPos = crashSphere.sphere.pos;
    float iRad = crashSphere.sphere.radius;

    float iAngle = m_object->GetRotationY();
    iAngle = Math::NormAngle(iAngle);  // 0..2*Math::PI

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
                float distance = fabs(glm::distance(worldSlotPos, iPos)-(iRad + 1.0f));
                // The robot must be close enough to the slot
                if ( distance <= dLimit )
                {
                    // The slot must be in the correct position relative to the robot (the robot must be facing towards the slot, not sideways or away)
                    angle = Math::RotateAngle(worldSlotPos.x-iPos.x, iPos.z-worldSlotPos.z);  // CW !
                    if ( Math::TestAngle(angle, iAngle-aLimit, iAngle+aLimit) )
                    {
                        glm::vec3 powerPos = obj->GetSlotPosition(slot);
                        height = powerPos.y;
                        slotNumOut = slot;
                        return pObj;
                    }
                }
            }
        }
    }

    return nullptr;
}

// Takes the object in front.

bool CTaskTake::TransporterTakeObject()
{
    float angle = 0.0f;

    CObject* cargo = nullptr;

    if (m_arm == TTA_FFRONT)  // takes on the ground in front?
    {
//?     cargo = SearchTakeObject(angle, 1.5f, Math::PI*0.04f);
        cargo = SearchTakeObject(angle, 1.5f, Math::PI*0.15f);  //OK 1.9
    }

    if (m_arm == TTA_FRIEND)  // takes friend's battery?
    {
        int slotNum = INVALID_SLOT;
        CObject* other = SearchFriendObject(angle, 1.5f, Math::PI*0.04f, m_height, slotNum);
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

bool CTaskTake::TransporterDeposeObject()
{
    CObject* cargo = GetObjectInCargoSlot(m_object);
    if (cargo == nullptr)  return false;  // does nothing?
    assert(cargo->Implements(ObjectInterfaceType::Transportable));

    if ( m_arm == TTA_FFRONT )  // deposes on the ground in front?
    {
        glm::mat4 mat = cargo->GetWorldMatrix(0);
        glm::vec3 pos = Math::Transform(mat, glm::vec3(-0.5f, 1.0f, 0.0f));
        m_terrain->AdjustToFloor(pos);
        cargo->SetPosition(pos);
//??        cargo->SetRotationY(m_object->GetRotationY()+Math::PI/2.0f);
//??        cargo->SetRotationY(m_object->GetRotationY());
        cargo->SetRotationY(0.0f);
        cargo->SetRotationX(0.0f);
        cargo->SetRotationZ(0.0f);
        cargo->SetFloorHeight(0.0f);
        cargo->FloorAdjust();  // plate well on the ground

        SetObjectInCargoSlot(m_object, nullptr);  // deposit
    }

    if ( m_arm == TTA_FRIEND )  // deposes battery on friends?
    {
        float angle = 0.0f;

        int slotNum = INVALID_SLOT;
        CObject* other = SearchFriendObject(angle, 1.5f, Math::PI*0.04f, m_height, slotNum);
        if (other == nullptr)  return false;
        assert(slotNum != INVALID_SLOT);

        if (GetObjectInSlot(other, slotNum) != nullptr)  return false;  // the other already has a battery?

        SetObjectInCargoSlot(m_object, nullptr);  // deposit
        SetObjectInSlot(other, slotNum, cargo);
    }

    return true;
}

// Seeks if a location allows to deposit an object.

bool CTaskTake::IsFreeDeposeObject(glm::vec3 pos)
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
            if ( glm::distance(iPos, crashSphere.sphere.pos)-(crashSphere.sphere.radius+1.0f) < 1.0f )
            {
                return false;  // location occupied
            }
        }
    }
    return true;  // location free
}
