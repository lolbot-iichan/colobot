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
 * \file object/details/transportable_details.cpp
 * \brief CObjectTransportableDetails - set of tweaks for Transportable objects
 */

#include "level/parser/parser.h"

#include "object/details/details_provider.h"
#include "object/details/hardcode.h"
#include "object/details/macro.h"
#include "object/details/transportable_details.h"

void CObjectTransportableDetails::ReadHardcode(ObjectType type)
{
    CHardcodeCollection hardcode;

    enabled      = hardcode.IsTransportable(type);
    showDropZone = hardcode.IsDropZoneShownOnPut(type);
}

bool CObjectTransportableDetails::Read(CLevelParserLine* line)
{
    READ_LINE( "SetObjectTransportable" );
    READ_ARG( "enabled",      AsBool, enabled      );
    READ_ARG( "showDropZone", AsBool, showDropZone );
    READ_END();

    return false;
}

void CObjectTransportableDetails::Write(CLevelParser* parser, ObjectType type)
{
    CObjectTransportableDetails def;

    WRITE_LINE( "SetObjectTransportable" );
    WRITE_ARG( "enabled",      def, enabled      );
    WRITE_ARG( "showDropZone", def, showDropZone );
    WRITE_END();
}

CObjectTransportableDetails GetObjectTransportableDetails(CObject* obj)
{
    return CObjectDetails::GetInstance().GetObjectDetails(obj).transportable;
}