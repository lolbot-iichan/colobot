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

#include "object/details/global_details.h"

#include "object/hardcode/global_hardcode.h"

ObjectType CGlobalHardcodeCollection::GetPlayerType()
{
    return OBJECT_HUMAN;
}

ObjectType CGlobalHardcodeCollection::GetAssistantType()
{
    return OBJECT_TOTO;
}

ObjectType CGlobalHardcodeCollection::GetControllerType()
{
    return OBJECT_CONTROLLER;
}

ObjectType CGlobalHardcodeCollection::GetBaseType()
{
    return OBJECT_BASE;
}

ObjectType CGlobalHardcodeCollection::GetArrowType()
{
    return OBJECT_SHOW;
}

ObjectType CGlobalHardcodeCollection::GetFunctionDestroyPerformerObject()
{
    return OBJECT_DESTROYER;
}

ObjectType CGlobalHardcodeCollection::GetFunctionFactoryPerformerObject()
{
    return OBJECT_FACTORY;
}

ObjectType CGlobalHardcodeCollection::GetFunctionTakeOffPerformerObject()
{
    return OBJECT_BASE;
}

ObjectType CGlobalHardcodeCollection::GetFunctionReceivePerformerObject()
{
    return OBJECT_INFO;
}

std::vector<CObjectDebugButton> CGlobalHardcodeCollection::GetDebugMenuButtons()
{
    std::vector<CObjectDebugButton> result;
    result.push_back({OBJECT_HUMAN,    128+8,  "Me"});
    result.push_back({OBJECT_MOBILEwa, 128+9,  "Wheeled grabber"});
    result.push_back({OBJECT_MOBILEwc, 128+15, "Wheeled shooter"});
    result.push_back({OBJECT_MOBILErc, 128+19, "Phazer shooter"});
    result.push_back({OBJECT_FACTORY,  128+32, "Bot factory"});
    result.push_back({OBJECT_CONVERT,  128+34, "Converter"});
    result.push_back({OBJECT_DERRICK,  128+33, "Derrick"});
    result.push_back({OBJECT_STATION,  128+36, "Power station"});
    result.push_back({OBJECT_METAL,    -1,     "Titanium"});
    result.push_back({OBJECT_STONE,    -1,     "TitaniumOre"});
    result.push_back({OBJECT_URANIUM,  -1,     "UraniumOre"});
    result.push_back({OBJECT_POWER,    -1,     "PowerCell"});
    result.push_back({OBJECT_ATOMIC,   -1,     "NuclearCell"});
    return result;
}
