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
 * \file object/details/shielded_details.cpp
 * \brief CObjectShieldedDetails - set of tweaks for Shielded objects
 */

#include "level/parser/parser.h"

#include "object/details/details_provider.h"
#include "object/details/hardcode.h"
#include "object/details/macro.h"
#include "object/details/shielded_details.h"

void CObjectShieldedDetails::ReadHardcode(ObjectType type)
{
    CHardcodeCollection hardcode;

    enabled = hardcode.IsShielded(type);
    repairable = hardcode.IsRepairable(type);
}

bool CObjectShieldedDetails::Read(CLevelParserLine* line)
{
    READ_LINE( "SetObjectShielded" );
    READ_ARG( "enabled",    AsBool, enabled    );
    READ_ARG( "repairable", AsBool, repairable );
    READ_END();

    return false;
}

void CObjectShieldedDetails::Write(CLevelParser* parser, ObjectType type)
{
    CObjectShieldedDetails def;

    WRITE_LINE( "SetObjectShielded" );
    WRITE_ARG( "enabled",    def, enabled    );
    WRITE_ARG( "repairable", def, repairable );
    WRITE_END();
}

CObjectShieldedDetails GetObjectShieldedDetails(CObject* obj)
{
    return CObjectDetails::GetInstance().GetObjectDetails(obj).shielded;
}