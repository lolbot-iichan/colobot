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

#include "object/hardcode/fragile_hardcode.h"

bool CFragileHardcodeCollection::IsFragile(ObjectType type)
{
    if ( type == OBJECT_MOBILEtg ||
         type == OBJECT_STONE    ||
         type == OBJECT_METAL    ||
         type == OBJECT_URANIUM  ||
         type == OBJECT_POWER    ||
         type == OBJECT_ATOMIC   ||
         type == OBJECT_TNT      ||
         type == OBJECT_BULLET   ||
         type == OBJECT_EGG      ||
         type == OBJECT_BOMB     ||
         type == OBJECT_ANT      ||
         type == OBJECT_WORM     ||
         type == OBJECT_SPIDER   ||
         type == OBJECT_BEE      ||
         type == OBJECT_TEEN28    )
    {
        return true;
    }
    else if (type == OBJECT_RUINmobilew1 ||
             type == OBJECT_RUINmobilew2 ||
             type == OBJECT_RUINmobilet1 ||
             type == OBJECT_RUINmobilet2 ||
             type == OBJECT_RUINmobiler1 ||
             type == OBJECT_RUINmobiler2 ||
             type == OBJECT_RUINfactory  ||
             type == OBJECT_RUINdoor     ||
             type == OBJECT_RUINsupport  ||
             type == OBJECT_RUINradar    ||
             type == OBJECT_RUINconvert   )
    {
        return true;
    }
    else if (type == OBJECT_PLANT0  ||
             type == OBJECT_PLANT1  ||
             type == OBJECT_PLANT2  ||
             type == OBJECT_PLANT3  ||
             type == OBJECT_PLANT4  ||
             type == OBJECT_PLANT15 ||
             type == OBJECT_PLANT16 ||
             type == OBJECT_PLANT17 ||
             type == OBJECT_PLANT18 )
    {
        return true;
    }

    return false;
}

bool CFragileHardcodeCollection::IsFragileBurnable(ObjectType type)
{
    if ( type == OBJECT_ANT    ||
         type == OBJECT_WORM   ||
         type == OBJECT_SPIDER ||
         type == OBJECT_BEE     ) return true;

    return false;
}