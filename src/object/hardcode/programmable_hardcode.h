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

struct CProgrammableHardcodeCollection
{
    static bool IsProgrammable(ObjectType type);
    static bool GetNoSaveState(ObjectType type);

    static bool IsFunctionImplementedBuild(ObjectType type);
    static bool IsFunctionImplementedFlags(ObjectType type);
    static bool IsFunctionImplementedSniff(ObjectType type);
    static bool IsFunctionImplementedShield(ObjectType type);
    static bool IsFunctionImplementedRecycle(ObjectType type);
    static bool IsFunctionImplementedThump(ObjectType type);
    static bool IsFunctionImplementedDrawAsRobot(ObjectType type);
    static bool IsFunctionImplementedGrabAsHuman(ObjectType type);
    static bool IsFunctionImplementedGrabAsRobot(ObjectType type);
    static bool IsFunctionImplementedShootAsAnt(ObjectType type);
    static bool IsFunctionImplementedShootAsSpider(ObjectType type);
    static bool IsFunctionImplementedShootAsRobot(ObjectType type);
};