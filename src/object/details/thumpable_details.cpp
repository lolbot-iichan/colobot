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
 * \file object/details/thumpable_details.cpp
 * \brief CObjectThumpableDetails - set of tweaks for Thumpable objects
 */

#include "level/parser/parser.h"

#include "object/details/macro.h"
#include "object/details/thumpable_details.h"

#include "object/hardcode/thumpable_hardcode.h"

void CObjectThumpableDetails::ReadHardcode(ObjectType type)
{
    enabled     = CThumpableHardcodeCollection::IsThumpable(type);
    minDuration = CThumpableHardcodeCollection::GetThumpDurationMin(type);
    maxDuration = CThumpableHardcodeCollection::GetThumpDurationMax(type);
}

bool CObjectThumpableDetails::Read(CLevelParserLine* line)
{
    READ_LINE( "SetObjectThumpable" );
    READ_ARG( "enabled", AsBool,  enabled     );
    READ_ARG( "min",     AsFloat, minDuration );
    READ_ARG( "max",     AsFloat, maxDuration );
    READ_END();

    return false;
}

void CObjectThumpableDetails::Write(CLevelParser* parser, ObjectType type)
{
    WRITE_LINE( "SetObjectThumpable" );
    WRITE_ARG( "enabled", AsBool,  enabled     );
    WRITE_ARG( "min",     AsFloat, minDuration );
    WRITE_ARG( "max",     AsFloat, maxDuration );
    WRITE_END();
}
