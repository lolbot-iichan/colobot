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

#include "object/details/macro.h"
#include "object/details/naming_details.h"

#include "object/hardcode/naming_hardcode.h"

void CObjectNamingDetails::ReadHardcode(ObjectType type)
{
    name  = CNamingHardcodeCollection::GetNameInLevelFiles(type);
    alias = CNamingHardcodeCollection::GetAliasInLevelFiles(type);
}

bool CObjectNamingDetails::Read(CLevelParserLine* line)
{
    READ_LINE( "SetObjectNaming" );
    keys  = {"type", "value", "alias", "template"};
    name  = line->GetParam("type")->GetValue();
    alias = line->GetParam("alias")->GetValue();
    READ_END();

    return false;
}

void CObjectNamingDetails::Write(CLevelParser* parser, ObjectType type)
{
    auto line = std::make_unique<CLevelParserLine>("SetObjectNaming");
    line->AddParam(("type"),std::make_unique<CLevelParserParam>( type ));
    line->AddParam(("value"),std::make_unique<CLevelParserParam>( int(type) ));
    if ( alias.size() )
        line->AddParam(("alias"),std::make_unique<CLevelParserParam>( "alias", alias ));
    if ( line->GetParam("type")->GetValue() != line->GetParam("value")->GetValue() )
        parser->AddLine(std::move(line));
}
