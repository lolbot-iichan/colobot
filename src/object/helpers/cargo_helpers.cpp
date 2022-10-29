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

#include "object/object.h"

#include "object/helpers/cargo_helpers.h"

#include "object/details/details_provider.h"
#include "object/details/slotted_details.h"
#include "object/details/transportable_details.h"

#include "object/interface/movable_object.h"
#include "object/interface/slotted_object.h"
#include "object/interface/transportable_object.h"

#include "physics/physics.h"

bool IsObjectBeingTransported(CObject* object)
{
    return GetObjectTransporter(object) != nullptr;
}

CObject* GetObjectTransporter(CObject* object)
{
    if (!object->Implements(ObjectInterfaceType::Transportable))  return nullptr;

    CTransportableObject* transportable = dynamic_cast<CTransportableObject*>(object);
    CObject* result = transportable->GetTransporter();
    return result;
}

int GetNumSlots(CObject *object)
{
    if (!object->Implements(ObjectInterfaceType::Slotted))  return 0;

    CSlottedObject* slotted = dynamic_cast<CSlottedObject*>(object);
    return slotted->GetNumSlots();
}

bool HasPowerCellSlot(CObject *object)
{
    if (!object->Implements(ObjectInterfaceType::Slotted))  return false;

    CSlottedObject* slotted = dynamic_cast<CSlottedObject*>(object);
    int slotNum = slotted->MapPseudoSlot(CSlottedObject::Pseudoslot::POWER);
    return slotNum >= 0;
}

bool HasCargoSlot(CObject *object)
{
    if (!object->Implements(ObjectInterfaceType::Slotted))  return false;

    CSlottedObject* slotted = dynamic_cast<CSlottedObject*>(object);
    int slotNum = slotted->MapPseudoSlot(CSlottedObject::Pseudoslot::CARRYING);
    return slotNum >= 0;
}

CObject *GetObjectInSlot(CObject *object, int slotNum)
{
    if (!object->Implements(ObjectInterfaceType::Slotted))  return nullptr;

    CSlottedObject* slotted = dynamic_cast<CSlottedObject*>(object);
    assert(unsigned(slotNum) < slotted->GetNumSlots());
    return slotted->GetSlotContainedObject(slotNum);
}

CObject *GetObjectInPowerCellSlot(CObject *object)
{
    if (!object->Implements(ObjectInterfaceType::Slotted))  return nullptr;

    CSlottedObject* slotted = dynamic_cast<CSlottedObject*>(object);
    int slotNum = slotted->MapPseudoSlot(CSlottedObject::Pseudoslot::POWER);
    return slotNum >= 0 ? slotted->GetSlotContainedObject(slotNum) : nullptr;
}

CObject *GetObjectInCargoSlot(CObject *object)
{
    if (!object->Implements(ObjectInterfaceType::Slotted))  return nullptr;

    CSlottedObject* slotted = dynamic_cast<CSlottedObject*>(object);
    int slotNum = slotted->MapPseudoSlot(CSlottedObject::Pseudoslot::CARRYING);
    return slotNum >= 0 ? slotted->GetSlotContainedObject(slotNum) : nullptr;
}

bool HasObjectInPowerCellSlot(CObject* object)
{
    return GetObjectInPowerCellSlot(object) != nullptr;
}

bool HasObjectInCargoSlot(CObject* object)
{
    return GetObjectInCargoSlot(object) != nullptr;
}

void SetObjectInSlot(CObject *obj, int slotNum, CObject *cargo)
{
    assert(obj->Implements(ObjectInterfaceType::Slotted));
    CSlottedObject* slotted = dynamic_cast<CSlottedObject*>(obj);

    assert(cargo != obj);
    assert(unsigned(slotNum) < slotted->GetNumSlots());
    assert(cargo == nullptr || cargo->Implements(ObjectInterfaceType::Transportable));

    if (cargo != nullptr)
    {
        auto sDetails = GetObjectSlottedDetails(obj).slots[slotNum];
        auto tDetails = GetObjectTransportableDetails(cargo);

        CTransportableObject* transportable = dynamic_cast<CTransportableObject*>(cargo);
        transportable->SetTransporter(obj);
        transportable->SetTransporterPart(sDetails.partNum);  // takes with the hand
        if ( cargo->Implements(ObjectInterfaceType::Movable) )
        {
            CPhysics* physics = dynamic_cast<CMovableObject&>(*cargo).GetPhysics();
            physics->SetFreeze(true);
        }

        cargo->SetPosition(sDetails.position + tDetails.position);
        cargo->SetRotation(sDetails.rotation + tDetails.rotation);

        slotted->SetSlotContainedObject(slotNum, cargo);
    }
    else
    {
        CObject* old = slotted->GetSlotContainedObject(slotNum);
        assert(old == nullptr || old->Implements(ObjectInterfaceType::Transportable));

        if ( old != nullptr)
        {
            CTransportableObject* transportable = dynamic_cast<CTransportableObject*>(old);
            transportable->SetTransporter(nullptr);
            transportable->SetTransporterPart(0);
            if ( old->Implements(ObjectInterfaceType::Movable) )
            {
                CPhysics* physics = dynamic_cast<CMovableObject&>(*old).GetPhysics();
                physics->SetFreeze(false);
            }
        }

        slotted->SetSlotContainedObject(slotNum, nullptr);
    }
}

void SetObjectInPowerCellSlot(CObject *object, CObject *cargo)
{
    assert(object->Implements(ObjectInterfaceType::Slotted));
    CSlottedObject* slotted = dynamic_cast<CSlottedObject*>(object);

    int slotNum = slotted->MapPseudoSlot(CSlottedObject::Pseudoslot::POWER);

    SetObjectInSlot(object, slotNum, cargo);
}

void SetObjectInCargoSlot(CObject *object, CObject *cargo)
{
    assert(object->Implements(ObjectInterfaceType::Slotted));
    CSlottedObject* slotted = dynamic_cast<CSlottedObject*>(object);

    int slotNum = slotted->MapPseudoSlot(CSlottedObject::Pseudoslot::CARRYING);

    SetObjectInSlot(object, slotNum, cargo);
}
