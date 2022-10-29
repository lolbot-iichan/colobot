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

struct CDetectableHardcodeCollection
{
    static bool IsRadarExplicitOnly(ObjectType type);
    static ObjectType GetBaseType(ObjectType type);
    
    static bool GetMapShowEvenUnselectable(ObjectType type);
    static MapColor GetMapIconColor(ObjectType type);

    // -1      for objects with empty icon
    // 0-63    for textures on button1.png 
    // 64-127  for textures on button2.png 
    // 128-191 for textures on button3.png 
    // 192-255 for textures on button4.png 
    static int GetMapIcon(ObjectType type);
};