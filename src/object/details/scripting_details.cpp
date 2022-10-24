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
 * \file object/details/scripting_details.cpp
 * \brief CObjectScriptingDetails - set of tweaks for Scripting objects
 */

#include "level/parser/parser.h"

#include "object/details/details_provider.h"
#include "object/details/hardcode.h"
#include "object/details/macro.h"
#include "object/details/scripting_details.h"

void CObjectScriptingDetails::ReadHardcode(ObjectType type)
{
    CHardcodeCollection hardcode;

    name           = hardcode.GetNameInScriptFiles(type);
    alias          = hardcode.GetAliasInScriptFiles(type);
    helpTopicPath  = hardcode.GetHelpTopicPathName(type);

    produce.isProducable      = hardcode.IsValidObjectTypeId(type);
    produce.isProducedCharged = hardcode.IsProduceAlreadyCharged(type);
    produce.isProducedManual  = hardcode.IsProduceManual(type);
    produce.container         = hardcode.GetProduceContainer(type);

    findableByRadar = hardcode.GetObjectsFindableByType(type);
}

bool CObjectScriptingDetails::Read(CLevelParserLine* line)
{
    READ_LINE( "SetObjectScripting" );
    READ_ARG( "name",  AsString, name          );
    READ_ARG( "alias", AsString, alias         );
    READ_ARG( "help",  AsString, helpTopicPath );
    READ_END();

    READ_LINE( "SetObjectScriptingProduce" );
    READ_ARG( "enabled",   AsBool,       produce.isProducable      );
    READ_ARG( "charged",   AsBool,       produce.isProducedCharged );
    READ_ARG( "manual",    AsBool,       produce.isProducedManual  );
    READ_ARG( "container", AsObjectType, produce.container         );
    READ_END();

    READ_IT_LINE( "AddObjectScriptingRadarAlias", "UpdObjectScriptingRadarAlias", "ClrObjectScriptingRadarAlias", findableByRadar );
    READ_IT_ARG( "value", AsObjectType, value );
    READ_IT_END();

    return false;
}

void CObjectScriptingDetails::Write(CLevelParser* parser, ObjectType type)
{
    WRITE_LINE( "SetObjectScripting" );
    WRITE_ARG( "name",  AsString, name          );
    WRITE_ARG( "alias", AsString, alias         );
    WRITE_ARG( "help",  AsString, helpTopicPath );
    WRITE_END();

    WRITE_LINE( "SetObjectScriptingProduce" );
    WRITE_ARG( "enabled",   AsBool,       produce.isProducable      );
    WRITE_ARG( "charged",   AsBool,       produce.isProducedCharged );
    WRITE_ARG( "manual",    AsBool,       produce.isProducedManual  );
    WRITE_ARG( "container", AsObjectType, produce.container         );
    WRITE_END();

    WRITE_IT_LINE( "AddObjectScriptingRadarAlias", findableByRadar );
    WRITE_IT_ARG( "value", AsObjectType, value );
    WRITE_IT_END();
}

CObjectScriptingDetails GetObjectScriptingDetails(ObjectType type)
{
    return CObjectDetails::GetInstance().GetObjectDetails(type).scripting;
}