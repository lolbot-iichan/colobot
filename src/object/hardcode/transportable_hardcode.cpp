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

#include "object/object_type.h"

#include "object/hardcode/transportable_hardcode.h"

bool CTransportableHardcodeCollection::IsTransportable(ObjectType type)
{
    if ( type == OBJECT_STONE   ||
         type == OBJECT_URANIUM ||
         type == OBJECT_BULLET  ||
         type == OBJECT_METAL   ||
         type == OBJECT_POWER   ||
         type == OBJECT_ATOMIC  ||
         type == OBJECT_BBOX    ||
         type == OBJECT_KEYa    ||
         type == OBJECT_KEYb    ||
         type == OBJECT_KEYc    ||
         type == OBJECT_KEYd    ||
         type == OBJECT_TNT     ) return true;
    return false;
}

bool CTransportableHardcodeCollection::IsTransportableRadioactive(ObjectType type)
{
    return type == OBJECT_URANIUM;
}


bool CTransportableHardcodeCollection::IsDropZoneShownOnPut(ObjectType type)
{
    return type == OBJECT_METAL;
}

