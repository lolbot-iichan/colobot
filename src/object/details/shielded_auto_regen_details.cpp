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
 * \file object/details/shielded_auto_regen_details.cpp
 * \brief CObjectShieldedAutoRegenDetails - set of tweaks for ShieldedAutoRegen objects
 */

#include "level/parser/parser.h"

#include "object/details/macro.h"
#include "object/details/shielded_auto_regen_details.h"

#include "object/hardcode/shielded_auto_regen_hardcode.h"

void CObjectShieldedAutoRegenDetails::ReadHardcode(ObjectType type)
{
    enabled = CShieldedAutoRegenHardcodeCollection::IsShieldedAutoRegen(type);
    time    = CShieldedAutoRegenHardcodeCollection::GetShieldedAutoRegenTime(type);
}

bool CObjectShieldedAutoRegenDetails::Read(CLevelParserLine* line)
{
    READ_LINE( "SetObjectShieldedAutoRegen" );
    READ_ARG( "enabled", AsBool,  enabled );
    READ_ARG( "time",    AsFloat, time    );
    READ_END();

    return false;
}

void CObjectShieldedAutoRegenDetails::Write(CLevelParser* parser, ObjectType type)
{
    WRITE_LINE( "SetObjectShieldedAutoRegen" );
    WRITE_ARG( "enabled", AsBool,  enabled );
    WRITE_ARG( "time",    AsFloat, time    );
    WRITE_END();
}
