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
 * \file object/details/detectable_details.cpp
 * \brief CObjectDetectableDetails - set of tweaks for Detectable objects
 */

#include "level/parser/parser.h"

#include "object/details/details_provider.h"
#include "object/details/hardcode.h"
#include "object/details/macro.h"
#include "object/details/detectable_details.h"

void CObjectDetectableDetails::ReadHardcode(ObjectType type)
{
    CHardcodeCollection hardcode;

    isExplicit           = hardcode.IsRadarExplicitOnly(type);
    baseType             = hardcode.GetBaseType(type);

    map.color            = hardcode.GetMapIconColor(type);
    map.icon             = hardcode.GetMapIcon(type);
    map.isForced         = hardcode.GetMapShowEvenUnselectable(type);
}

bool CObjectDetectableDetails::Read(CLevelParserLine* line)
{
    READ_LINE( "SetObjectDetectable" );
    READ_ARG( "radarExplicit", AsBool,       isExplicit   );
    READ_ARG( "baseType",      AsObjectType, baseType     );
    READ_ARG( "icon",          AsInt,        map.icon     );
    READ_ARG( "iconType",      AsInt,        map.color    );
    READ_ARG( "mapForced",     AsBool,       map.isForced );
    READ_END();

    return false;
}

void CObjectDetectableDetails::Write(CLevelParser* parser, ObjectType type)
{
    WRITE_LINE( "SetObjectDetectable" );
    WRITE_ARG( "radarExplicit", AsBool,       isExplicit   );
    WRITE_ARG( "baseType",      AsObjectType, baseType     );
    WRITE_ARG( "icon",          AsInt,        map.icon     );
    WRITE_ARG( "iconType",      AsInt,        map.color    );
    WRITE_ARG( "mapForced",     AsBool,       map.isForced );
    WRITE_END();
}

CObjectDetectableDetails GetObjectDetectableDetails(CObject* obj)
{
    return CObjectDetails::GetInstance().GetObjectDetails(obj).detectable;
}