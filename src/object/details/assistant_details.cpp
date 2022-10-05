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
 * \file object/details/assistant_details.cpp
 * \brief CObjectAssistantDetails - set of tweaks for Assistant objects
 */

#include "level/parser/parser.h"

#include "object/details/details_provider.h"
#include "object/details/hardcode.h"
#include "object/details/macro.h"
#include "object/details/assistant_details.h"

void CObjectAssistantDetails::ReadHardcode(ObjectType type)
{
    CHardcodeCollection hardcode;

    enabled          = hardcode.GetAssistantType() == type;

    reactOnSatcom    = hardcode.GetAssistantType() == type;
    reactOnMessages  = hardcode.GetAssistantType() == type;
    moveWithCamera   = hardcode.GetAssistantType() == type;
    ignoreOnSaveLoad = hardcode.GetAssistantType() == type;
    clickable        = hardcode.GetAssistantType() == type;
    unpausable       = hardcode.GetAssistantType() == type;
}

bool CObjectAssistantDetails::Read(CLevelParserLine* line)
{
    READ_LINE( "SetObjectAssistant" );
    READ_ARG( "enabled",          AsBool, enabled          );
    READ_ARG( "reactOnSatcom",    AsBool, reactOnSatcom    );
    READ_ARG( "reactOnMessages",  AsBool, reactOnMessages  );
    READ_ARG( "moveWithCamera",   AsBool, moveWithCamera   );
    READ_ARG( "ignoreOnSaveLoad", AsBool, ignoreOnSaveLoad );
    READ_ARG( "clickable",        AsBool, clickable        );
    READ_ARG( "unpausable",       AsBool, unpausable       );
    READ_END();

    return false;
}

void CObjectAssistantDetails::Write(CLevelParser* parser, ObjectType type)
{
    CObjectAssistantDetails def;

    WRITE_LINE( "SetObjectAssistant" );
    WRITE_ARG( "enabled",          def, enabled          );
    WRITE_ARG( "reactOnSatcom",    def, reactOnSatcom    );
    WRITE_ARG( "reactOnMessages",  def, reactOnMessages  );
    WRITE_ARG( "moveWithCamera",   def, moveWithCamera   );
    WRITE_ARG( "ignoreOnSaveLoad", def, ignoreOnSaveLoad );
    WRITE_ARG( "clickable",        def, clickable        );
    WRITE_ARG( "unpausable",       def, unpausable       );
    WRITE_END();
}

CObjectAssistantDetails GetObjectAssistantDetails(CObject* obj)
{
    return CObjectDetails::GetInstance().GetObjectDetails(obj).assistant;
}
