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

/**
 * \file object/details/power_container_details.cpp
 * \brief CObjectPowerContainerDetails - set of tweaks for PowerContainer objects
 */

#include "level/parser/parser.h"

#include "object/details/macro.h"
#include "object/details/power_container_details.h"

#include "object/hardcode/power_container_hardcode.h"

void CObjectPowerContainerDetails::ReadHardcode(ObjectType type)
{
    enabled      = CPowerContainerHardcodeCollection::IsPowerContainer(type);
    rechargeable = CPowerContainerHardcodeCollection::GetPowerContainerRechargeable(type);
    capacity     = CPowerContainerHardcodeCollection::GetPowerContainerCapacity(type);
    clamp        = CPowerContainerHardcodeCollection::GetPowerContainerClamp(type);
    dim_a        = CPowerContainerHardcodeCollection::GetPowerContainerDimA(type);
    dim_b        = CPowerContainerHardcodeCollection::GetPowerContainerDimB(type);
}

bool CObjectPowerContainerDetails::Read(CLevelParserLine* line)
{
    READ_LINE( "SetObjectPowerContainer" );
    READ_ARG( "enabled",      AsBool,  enabled      );
    READ_ARG( "rechargeable", AsBool,  rechargeable );
    READ_ARG( "capacity",     AsFloat, capacity     );
    READ_ARG( "clamp",        AsFloat, clamp        );
    READ_ARG( "dim_a",        AsFloat, dim_a        );
    READ_ARG( "dim_b",        AsFloat, dim_b        );
    READ_END();

    return false;
}

void CObjectPowerContainerDetails::Write(CLevelParser* parser, ObjectType type)
{
    WRITE_LINE( "SetObjectPowerContainer" );
    WRITE_ARG( "enabled",      AsBool,  enabled      );
    WRITE_ARG( "rechargeable", AsBool,  rechargeable );
    WRITE_ARG( "capacity",     AsFloat, capacity     );
    WRITE_ARG( "clamp",        AsFloat, clamp        );
    WRITE_ARG( "dim_a",        AsFloat, dim_a        );
    WRITE_ARG( "dim_b",        AsFloat, dim_b        );
    WRITE_END();
}
