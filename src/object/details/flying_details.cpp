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
 * \file object/details/flying_details.cpp
 * \brief CObjectFlyingDetails - set of tweaks for Flying objects
 */

#include "level/parser/parser.h"

#include "object/details/macro.h"
#include "object/details/flying_details.h"

#include "object/hardcode/flying_hardcode.h"

void CObjectFlyingDetails::ReadHardcode(ObjectType type)
{
    enabled        = CFlyingHardcodeCollection::IsFlying(type);
    noFlyWithCargo = CFlyingHardcodeCollection::GetNoFlyWithCargo(type);
    landingAccel   = CFlyingHardcodeCollection::GetLandingAccel(type);
    energyFactor   = CFlyingHardcodeCollection::GetFlyingEnergyFactor(type);
}

bool CObjectFlyingDetails::Read(CLevelParserLine* line)
{
    READ_LINE( "SetObjectFlying" );
    READ_ARG( "enabled",        AsBool,  enabled        );
    READ_ARG( "noFlyWithCargo", AsBool,  noFlyWithCargo );
    READ_ARG( "landingAccel",   AsFloat, landingAccel   );
    READ_ARG( "energyFactor",   AsFloat, energyFactor   );
    READ_END();

    return false;
}

void CObjectFlyingDetails::Write(CLevelParser* parser, ObjectType type)
{
    WRITE_LINE( "SetObjectFlying" );
    WRITE_ARG( "enabled",        AsBool,  enabled        );
    WRITE_ARG( "noFlyWithCargo", AsBool,  noFlyWithCargo );
    WRITE_ARG( "landingAccel",   AsFloat, landingAccel   );
    WRITE_ARG( "energyFactor",   AsFloat, energyFactor   );
    WRITE_END();
}
