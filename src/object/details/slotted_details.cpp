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
 * \file object/details/slotted_details.cpp
 * \brief CObjectSlottedDetails - set of tweaks for Slotted objects
 */

#include "level/parser/parser.h"

#include "object/details/details_provider.h"
#include "object/details/hardcode.h"
#include "object/details/macro.h"
#include "object/details/slotted_details.h"

void CObjectSlottedDetails::ReadHardcode(ObjectType type)
{
    CHardcodeCollection hardcode;

    enabled         = hardcode.IsSloted(type);
    cargo.enabled   = hardcode.HasCargoSlot(type);
    cargo.partNum   = hardcode.GetCargoSlotPartNumber(type);
    cargo.position  = hardcode.GetCargoSlotPosition(type);
    power.enabled   = hardcode.HasPowerSlot(type);
    power.position  = hardcode.GetPowerSlotPosition(type);
    other.enabled   = hardcode.HasOtherSlot(type);
    other.position  = hardcode.GetOtherSlotPosition(type);
}

bool CObjectSlottedDetails::Read(CLevelParserLine* line)
{
    READ_LINE( "SetObjectSlotted" );
    READ_ARG( "enabled", AsBool,  enabled );
    READ_ARG( "cSlot",   AsBool,  cargo.enabled );
    READ_ARG( "cPart",   AsInt,   cargo.partNum );
    READ_ARG( "cPos",    AsPoint, cargo.position );
    READ_ARG( "pSlot",   AsBool,  power.enabled );
    READ_ARG( "pPos",    AsPoint, power.position );
    READ_ARG( "oSlot",   AsBool,  other.enabled );
    READ_ARG( "oPos",    AsPoint, other.position );
    READ_END();

    return false;
}

void CObjectSlottedDetails::Write(CLevelParser* parser, ObjectType type)
{
    CObjectSlottedDetails def;

    WRITE_LINE( "SetObjectSlotted" );
    WRITE_ARG( "enabled", def, enabled );
    WRITE_ARG( "cSlot",   def, cargo.enabled );
    WRITE_ARG( "cPart",   def, cargo.partNum );
    WRITE_ARG( "cPos",    def, cargo.position );
    WRITE_ARG( "pSlot",   def, power.enabled );
    WRITE_ARG( "pPos",    def, power.position );
    WRITE_ARG( "oSlot",   def, other.enabled );
    WRITE_ARG( "oPos",    def, other.position );
    WRITE_END();
}

CObjectSlottedDetails GetObjectSlottedDetails(CObject* obj)
{
    return CObjectDetails::GetInstance().GetObjectDetails(obj).slotted;
}