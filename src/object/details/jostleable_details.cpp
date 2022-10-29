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
 * \file object/details/jostleable_details.cpp
 * \brief CObjectJostleableDetails - set of tweaks for Jostleable objects
 */

#include "level/parser/parser.h"

#include "object/details/macro.h"
#include "object/details/jostleable_details.h"

#include "object/hardcode/jostleable_hardcode.h"

void CObjectJostleableDetails::ReadHardcode(ObjectType type)
{
    enabled = CJostleableHardcodeCollection::IsJostleable(type);
    special = CJostleableHardcodeCollection::IsJostleableSpecial(type);
    factor  = CJostleableHardcodeCollection::GetJostleFactor(type);
    sphere  = CJostleableHardcodeCollection::GetJostlingSphere(type);
}

bool CObjectJostleableDetails::Read(CLevelParserLine* line)
{
    READ_LINE( "SetObjectJostleable" );
    READ_ARG( "enabled",  AsBool,  enabled       );
    READ_ARG( "special",  AsBool,  special       );
    READ_ARG( "factor",   AsFloat, factor        );
    READ_ARG( "radius",   AsFloat, sphere.radius );
    READ_ARG( "position", AsPoint, sphere.pos    );
    READ_END();

    return false;
}

void CObjectJostleableDetails::Write(CLevelParser* parser, ObjectType type)
{
    WRITE_LINE( "SetObjectJostleable" );
    WRITE_ARG( "enabled",  AsBool,  enabled       );
    WRITE_ARG( "special",  AsBool,  special       );
    WRITE_ARG( "factor",   AsFloat, factor        );
    WRITE_ARG( "radius",   AsFloat, sphere.radius );
    WRITE_ARG( "position", AsPoint, sphere.pos    );
    WRITE_END();
}
