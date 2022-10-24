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

    enabled = hardcode.IsSloted(type);
    slots   = hardcode.GetSlots(type);
}

bool CObjectSlottedDetails::Read(CLevelParserLine* line)
{
    READ_LINE( "SetObjectSlotted"         );
    READ_ARG( "enabled", AsBool,  enabled );
    READ_END();

    READ_IT_LINE( "AddObjectSlot", "UpdObjectSlot", "ClrObjectSlot", slots );
    READ_IT_ARG( "category", AsInt,   category );
    READ_IT_ARG( "partNum",  AsInt,   partNum  );
    READ_IT_ARG( "position", AsPoint, position );
    READ_IT_END();

    return false;
}

void CObjectSlottedDetails::Write(CLevelParser* parser, ObjectType type)
{
    WRITE_LINE( "SetObjectSlotted"        ); 
    WRITE_ARG( "enabled", AsBool, enabled );
    WRITE_END();

    WRITE_IT_LINE( "AddObjectSlot",    slots    );
    WRITE_IT_ARG( "category", AsInt,   category );
    WRITE_IT_ARG( "partNum",  AsInt,   partNum  );
    WRITE_IT_ARG( "position", AsPoint, position );
    WRITE_IT_END();
}

CObjectSlottedDetails GetObjectSlottedDetails(CObject* obj)
{
    return CObjectDetails::GetInstance().GetObjectDetails(obj).slotted;
}