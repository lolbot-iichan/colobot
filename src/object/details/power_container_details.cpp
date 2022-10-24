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

#include "object/details/details_provider.h"
#include "object/details/hardcode.h"
#include "object/details/macro.h"
#include "object/details/power_container_details.h"

void CObjectPowerContainerDetails::ReadHardcode(ObjectType type)
{
    CHardcodeCollection hardcode;

    enabled = hardcode.IsPowerContainer(type);
}

bool CObjectPowerContainerDetails::Read(CLevelParserLine* line)
{
    READ_LINE( "SetObjectPowerContainer" );
    READ_ARG( "enabled", AsBool, enabled);
    READ_END();

    return false;
}

void CObjectPowerContainerDetails::Write(CLevelParser* parser, ObjectType type)
{
    WRITE_LINE( "SetObjectPowerContainer" );
    WRITE_ARG( "enabled", AsBool, enabled );
    WRITE_END();
}

CObjectPowerContainerDetails GetObjectPowerContainerDetails(CObject* obj)
{
    return CObjectDetails::GetInstance().GetObjectDetails(obj).power_container;
}