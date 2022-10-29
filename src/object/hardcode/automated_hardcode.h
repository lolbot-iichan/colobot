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

struct CAutomatedHardcodeCollection
{
    static AutoClass GetCreationAutoClass(ObjectType type);

    static bool IsBlockingBuilding(ObjectType type);
    static bool IsAutoTargetedByTower(ObjectType type);
    static bool IsAutoTargetedByMushroom(ObjectType type);
    static bool IsAutoChargedAtPowerStation(ObjectType type);
    static bool IsAutoCommentedByAssistant(ObjectType type);
    static bool IsAutoBlockingPowerPlant(ObjectType type);
    static bool IsAutoBlockingNuclearPlant(ObjectType type);
    static bool IsAutoBlockingFactory(ObjectType type);

    static CObjectFactoryAutomatedDetails GetFactory(ObjectType type);
    static CObjectEggAutomatedDetails GetEgg(ObjectType type);
    static CObjectProductionAutomatedDetails GetProduction(ObjectType type);
    static CObjectDiggingAutomatedDetails GetDigging(ObjectType type);
    static CObjectVaultAutomatedDetails GetVault(ObjectType type);
    static CObjectQuarzAutomatedDetails GetQuarz(ObjectType type);
    static CObjectLampAutomatedDetails GetLamp(ObjectType type);
};