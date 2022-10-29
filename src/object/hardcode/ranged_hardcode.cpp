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

#include "graphics/engine/lightning.h"

#include "object/object_type.h"

#include "object/hardcode/ranged_hardcode.h"

bool CRangedHardcodeCollection::IsRanged(ObjectType type)
{
    return true; // huh
}

float CRangedHardcodeCollection::GetRangedRadius(ObjectType type)
{
    if ( type == OBJECT_BASE     ) return 200.0f; // SpaceShip
    if ( type == OBJECT_MOBILErt ) return 400.0f; // Thumper
    if ( type == OBJECT_TOWER    ) return Gfx::LTNG_PROTECTION_RADIUS; // DefenseTower
    if ( type == OBJECT_PARA     ) return Gfx::LTNG_PROTECTION_RADIUS; // PowerCaptor
    return 0.0f;
}
