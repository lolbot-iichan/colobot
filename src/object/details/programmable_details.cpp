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
 * \file object/details/programmable_details.cpp
 * \brief CObjectProgrammableDetails - set of tweaks for Programmable objects
 */

#include "level/parser/parser.h"

#include "object/details/details_provider.h"
#include "object/details/hardcode.h"
#include "object/details/macro.h"
#include "object/details/programmable_details.h"

void CObjectProgrammableDetails::ReadHardcode(ObjectType type)
{
    CHardcodeCollection hardcode;

    enabled = hardcode.IsProgrammable(type);

    allowed.build = hardcode.IsFunctionImplementedBuild(type);
    allowed.flag = hardcode.IsFunctionImplementedFlags(type);
    allowed.sniff = hardcode.IsFunctionImplementedSniff(type);
    allowed.shield = hardcode.IsFunctionImplementedShield(type);
    allowed.recycle = hardcode.IsFunctionImplementedRecycle(type);
    allowed.pen = hardcode.IsFunctionImplementedDrawAsRobot(type);
    allowed.grabNoParam = hardcode.IsFunctionImplementedGrabAsHuman(type);
    allowed.grabEnumParam = hardcode.IsFunctionImplementedGrabAsRobot(type);
    allowed.shootNoParam = hardcode.IsFunctionImplementedShootAsSpider(type);
    allowed.shootTimeParam = hardcode.IsFunctionImplementedShootAsRobot(type);
    allowed.shootPointParam = hardcode.IsFunctionImplementedShootAsAnt(type);
}

bool CObjectProgrammableDetails::Read(CLevelParserLine* line)
{
    READ_LINE( "SetObjectProgrammable" );
    READ_ARG( "enabled", AsBool, enabled                 );
    READ_ARG( "build",   AsBool, allowed.build           );
    READ_ARG( "flag",    AsBool, allowed.flag            );
    READ_ARG( "sniff",   AsBool, allowed.sniff           );
    READ_ARG( "shield",  AsBool, allowed.shield          );
    READ_ARG( "recycle", AsBool, allowed.recycle         );
    READ_ARG( "pen",     AsBool, allowed.pen             );
    READ_ARG( "grab0",   AsBool, allowed.grabNoParam     );
    READ_ARG( "grabE",   AsBool, allowed.grabEnumParam   );
    READ_ARG( "shoot0",  AsBool, allowed.shootNoParam    );
    READ_ARG( "shootT",  AsBool, allowed.shootTimeParam  );
    READ_ARG( "shootP",  AsBool, allowed.shootPointParam );
    READ_END();

    return false;
}

void CObjectProgrammableDetails::Write(CLevelParser* parser, ObjectType type)
{
    WRITE_LINE( "SetObjectProgrammable" );
    WRITE_ARG( "enabled", AsBool, enabled                 );
    WRITE_ARG( "build",   AsBool, allowed.build           );
    WRITE_ARG( "flag",    AsBool, allowed.flag            );
    WRITE_ARG( "sniff",   AsBool, allowed.sniff           );
    WRITE_ARG( "shield",  AsBool, allowed.shield          );
    WRITE_ARG( "recycle", AsBool, allowed.recycle         );
    WRITE_ARG( "pen",     AsBool, allowed.pen             );
    WRITE_ARG( "grab0",   AsBool, allowed.grabNoParam     );
    WRITE_ARG( "grabE",   AsBool, allowed.grabEnumParam   );
    WRITE_ARG( "shoot0",  AsBool, allowed.shootNoParam    );
    WRITE_ARG( "shootT",  AsBool, allowed.shootTimeParam  );
    WRITE_ARG( "shootP",  AsBool, allowed.shootPointParam );
    WRITE_END();
}

CObjectProgrammableDetails GetObjectProgrammableDetails(CObject* obj)
{
    return CObjectDetails::GetInstance().GetObjectDetails(obj).programmable;
}