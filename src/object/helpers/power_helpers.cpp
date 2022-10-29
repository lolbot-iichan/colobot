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
#include "object/helpers/power_helpers.h"

#include "object/interface/power_container_object.h"

inline CPowerContainerObject* GetObjectPowerContainer(CObject *object)
{
    if (object->Implements(ObjectInterfaceType::PowerContainer))
    {
        return dynamic_cast<CPowerContainerObject*>(object);
    }

    if (CObject* powerSlotObj = GetObjectInPowerCellSlot(object))
    {
        if (powerSlotObj->Implements(ObjectInterfaceType::PowerContainer))
        {
            return dynamic_cast<CPowerContainerObject*>(powerSlotObj);
        }
    }
    return nullptr;
}

bool HasObjectPowerContainer(CObject *object)
{
    return GetObjectPowerContainer(object) != nullptr;
}

float GetObjectEnergy(CObject* object)
{
    if (CPowerContainerObject* power = GetObjectPowerContainer(object))
        return power->GetEnergy();
    return 0.0f;
}

float GetObjectEnergyCapacity(CObject* object)
{
    if (CPowerContainerObject* power = GetObjectPowerContainer(object))
        return power->GetCapacity();
    return 0.0f;
}

float GetObjectEnergyLevel(CObject* object)
{
    if (CPowerContainerObject* power = GetObjectPowerContainer(object))
        return power->GetEnergyLevel();
    return 0.0f;
}

void DecreaseObjectEnergy(CObject* object, float delta)
{
    assert(delta >= 0);
    if (CPowerContainerObject* power = GetObjectPowerContainer(object))
    {
        float energy = power->GetEnergy();
        energy -= delta;
        if ( energy < 0.0f )  energy = 0.0f;
        power->SetEnergy(energy);
    }
}

void ChargeObjectEnergy(CObject* object, float delta)
{
    assert(delta >= 0);
    if (CPowerContainerObject* power = GetObjectPowerContainer(object))
    {
        if (!power->IsRechargeable()) return;

        float energy = power->GetEnergy();
        float capacity = power->GetCapacity();
        energy += delta;
        if ( energy >= capacity )  energy = capacity;
        power->SetEnergy(energy);
    }
}

void SetObjectEnergy(CObject* object, float energy=1.0f)
{
    if (CPowerContainerObject *power = GetObjectPowerContainer(object))
    {
        float capacity = power->GetCapacity();
        if ( energy < 0.0f )  energy = 0.0f;
        if ( energy > capacity )  energy = capacity;
        power->SetEnergy(energy);
    }
}

void SetObjectEnergyLevel(CObject* object, float level=1.0f)
{
    if (CPowerContainerObject *power = GetObjectPowerContainer(object))
    {
        if ( level < 0.0f )  level = 0.0f;
        if ( level > 1.0f )  level = 1.0f;
        power->SetEnergyLevel(level);
    }
}
