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

#pragma once

enum ObjectType : unsigned int;

#include <string>

#include "object/details/destroyable_details.h"

struct CDestroyableHardcodeCollection
{
    static bool IsDestroyable(ObjectType type);
    static bool IsDestructionRemoveBuildingLevel(ObjectType type);
    static std::string GetDestroyMessage(ObjectType type);

    static Gfx::PyroType GetDestructionByExplosion(ObjectType type);

    static bool IsExplodesInWater(ObjectType type);
    static Gfx::PyroType GetDestructionByWater(ObjectType type);

    static Gfx::PyroType GetDestructionByBurning(ObjectType type);
    static bool IsDestructionKilledByBurning(ObjectType type);
    static std::vector<CPyroBurnPartDetails> GetBurnParts(ObjectType type);
    static ObjectType GetTypeAfterBurn(ObjectType);

    static Gfx::PyroType GetDestructionByDrowned(ObjectType type);

    static Gfx::PyroType GetDestructionByWin(ObjectType type);

    static bool IsSquashedByHeavy(ObjectType type);
    static Gfx::PyroType GetDestructionBySquash(ObjectType type);

    static float GetThumperSafeRadius(ObjectType type);
    static Gfx::PyroType GetThumperPyroType(ObjectType type);
    static float GetThumperExplosionDamage(ObjectType type);

    static bool GetDestroyableByDestroyer(ObjectType type);
};
