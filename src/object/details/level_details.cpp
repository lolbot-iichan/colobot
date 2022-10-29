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
 * \file object/details/level_details.cpp
 * \brief CObjectLevelDetails - set of tweaks for Level objects
 */

#include "level/parser/parser.h"

#include "object/details/macro.h"
#include "object/details/level_details.h"

#include "object/hardcode/level_hardcode.h"

void CObjectLevelDetails::ReadHardcode(ObjectType type)
{
    drive     = CLevelHardcodeCollection::GetDriveType(type);
    tool      = CLevelHardcodeCollection::GetToolType(type);
    quickLost = CLevelHardcodeCollection::IsObjectQuickLost(type);
}

bool CObjectLevelDetails::Read(CLevelParserLine* line)
{
    READ_LINE( "SetObjectLevel" );
    READ_ARG( "drive",     AsDriveType, drive     );
    READ_ARG( "tool",      AsToolType,  tool      );
    READ_ARG( "quickLost", AsBool,      quickLost );
    READ_END();

    return false;
}

void CObjectLevelDetails::Write(CLevelParser* parser, ObjectType type)
{
    WRITE_LINE( "SetObjectLevel" );
    WRITE_ARG( "drive",     AsDriveType, drive     );
    WRITE_ARG( "tool",      AsToolType,  tool      );
    WRITE_ARG( "quickLost", AsBool,      quickLost );
    WRITE_END();
}
