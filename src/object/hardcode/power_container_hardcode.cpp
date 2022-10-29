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

#include "math/sphere.h"

#include "object/object_type.h"

#include "object/hardcode/power_container_hardcode.h"

bool CPowerContainerHardcodeCollection::IsPowerContainer(ObjectType type)
{
    // TODO: Another one? :/
    if ( type == OBJECT_POWER   || // PowerCell
         type == OBJECT_ATOMIC  || // NuclearCell
         type == OBJECT_STATION || // PowerStation
         type == OBJECT_ENERGY   ) // PowerPlant
             return true;
    return false;
}

bool  CPowerContainerHardcodeCollection::GetPowerContainerRechargeable(ObjectType type)
{
    if ( type == OBJECT_POWER   || // PowerCell
         type == OBJECT_STATION || // PowerStation
         type == OBJECT_ENERGY   ) // PowerPlant
             return true;
    return false;
}

float CPowerContainerHardcodeCollection::GetPowerContainerCapacity(ObjectType type)
{
    if ( type == OBJECT_POWER ) return 1.0f;
    if ( type == OBJECT_ATOMIC ) return 100.0f;
    return 1.0f;
}

float CPowerContainerHardcodeCollection::GetPowerContainerClamp(ObjectType type)
{
    if ( type == OBJECT_POWER   || // PowerCell
         type == OBJECT_ATOMIC   ) // NuclearCell
             return 1.0f;

    return 100;
}

float CPowerContainerHardcodeCollection::GetPowerContainerDimA(ObjectType type)
{
    if ( type == OBJECT_POWER ) return 2.0f;
    if ( type == OBJECT_ATOMIC ) return 2.0f;
    if ( type == OBJECT_STATION ) return 10.0f;
    if ( type == OBJECT_ENERGY ) return 9.0f;
    return 0.0f;
}

float CPowerContainerHardcodeCollection::GetPowerContainerDimB(ObjectType type)
{
    if ( type == OBJECT_POWER ) return 0.0f;
    if ( type == OBJECT_ATOMIC ) return 0.0f;
    if ( type == OBJECT_STATION ) return 4.0f;
    if ( type == OBJECT_ENERGY ) return 3.0f;
    return 0.0f;
}
