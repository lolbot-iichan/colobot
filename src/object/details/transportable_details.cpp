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

#include "object/details/macro.h"
#include "object/details/transportable_details.h"

#include "object/hardcode/transportable_hardcode.h"

void CObjectTransportableDetails::ReadHardcode(ObjectType type)
{
    

    enabled      = CTransportableHardcodeCollection::IsTransportable(type);
    radioactive  = CTransportableHardcodeCollection::IsTransportableRadioactive(type);
    showDropZone = CTransportableHardcodeCollection::IsDropZoneShownOnPut(type);
    position     = {0,0,0};
    rotation     = {0,0,0};
}

bool CObjectTransportableDetails::Read(CLevelParserLine* line)
{
    READ_LINE( "SetObjectTransportable" );
    READ_ARG( "enabled",      AsBool,  enabled      );
    READ_ARG( "radioactive",  AsBool,  radioactive  );
    READ_ARG( "showDropZone", AsBool,  showDropZone );
    READ_ARG( "position",     AsPoint, position     );
    READ_ARG( "rotation",     AsPoint, rotation     );
    READ_END();

    return false;
}

void CObjectTransportableDetails::Write(CLevelParser* parser, ObjectType type)
{
    WRITE_LINE( "SetObjectTransportable" );
    WRITE_ARG( "enabled",      AsBool,  enabled      );
    WRITE_ARG( "radioactive",  AsBool,  radioactive  );
    WRITE_ARG( "showDropZone", AsBool,  showDropZone );
    WRITE_ARG( "position",     AsPoint, position     );
    WRITE_ARG( "rotation",     AsPoint, rotation     );
    WRITE_END();
}
