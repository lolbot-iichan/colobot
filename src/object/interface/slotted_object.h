/*
 * This file is part of the Colobot: Gold Edition source code
 * Copyright (C) 2001-2020, Daniel Roux, EPSITEC SA & TerranovaTeam
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

#pragma once

#include "object/object.h"
#include "object/object_interface_type.h"

#include <assert.h>

#include <glm/glm.hpp>

class CObject;

/**
 * \class CSlottedObject
 * \brief Interface for objects that hold other objects
 */
class CSlottedObject
{
public:
    ///! Object-independent identifiers for certain special slots
    enum class Pseudoslot
    {
        POWER    = -1,
        CARRYING = -2
    };

    explicit CSlottedObject(ObjectInterfaceTypes& types)
    {
        types[static_cast<int>(ObjectInterfaceType::Slotted)] = true;
    }
    virtual ~CSlottedObject()
    {}

    //! Given one of the PSEUDOSLOT enums, returns real slot number, or -1 if specified pseudoslot is not present in this object.
    virtual int MapPseudoSlot(Pseudoslot pseudoslot) = 0;

    //! Get number of slots. Valid slot numbers are 0 up to GetNumSlots()-1. Using invalid slot numbers in the other functions will crash the game.
    virtual int GetNumSlots() = 0;

    //! Get relative position of a slot.
    virtual glm::vec3 GetSlotPosition(int slotNum) = 0;

    //! Get relative angle (in radians) where robot should be positioned when inserting into a slot.
    virtual float GetSlotAngle(int slotNum) = 0;

    //! Get the maximum angular distance from the ideal angle (in radians) where robot should be positioned when inserting into a slot.
    virtual float GetSlotAcceptanceAngle(int slotNum) = 0;

    //! Get object contained in a slot.
    virtual CObject *GetSlotContainedObject(int slotNum) = 0;

    //! Set object contained in a slot.
    virtual void SetSlotContainedObject(int slotNum, CObject *object) = 0;
};
