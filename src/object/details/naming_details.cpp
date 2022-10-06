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
 * \file object/details/naming_details.cpp
 * \brief CObjectNamingDetails - set of tweaks for Naming objects
 */

#include "level/parser/parser.h"

#include "object/details/details_provider.h"
#include "object/details/hardcode.h"
#include "object/details/macro.h"
#include "object/details/naming_details.h"

void CObjectNamingDetails::ReadHardcode(ObjectType type)
{
    CHardcodeCollection hardcode;

    name  = hardcode.GetNameInLevelFiles(type);
    alias = hardcode.GetAliasInLevelFiles(type);
}

bool CObjectNamingDetails::Read(CLevelParserLine* line)
{
    if (line->GetCommand() == "SetObjectNaming") {
        name  = line->GetParam("type")->GetValue();
        alias = line->GetParam("alias")->GetValue();

        std::set<std::string> keys = {"type", "value", "alias"};
        for ( auto k: line->GetKeys() )
            if (!keys.count(k))
                UnusedArg(line, k);

        return true;
    }

    return false;
}

void CObjectNamingDetails::Write(CLevelParser* parser, ObjectType type)
{
    CObjectNamingDetails def;

    auto line = MakeUnique<CLevelParserLine>("SetObjectNaming");
    line->AddParam(("type"),MakeUnique<CLevelParserParam>( type ));
    line->AddParam(("value"),MakeUnique<CLevelParserParam>( int(type) ));
    if ( alias.size() )
        line->AddParam(("alias"),MakeUnique<CLevelParserParam>( "alias", alias ));
    parser->AddLine(std::move(line));
}

CObjectNamingDetails GetObjectNamingDetails(ObjectType type)
{
    return CObjectDetails::GetInstance().GetObjectDetails(type).naming;
}