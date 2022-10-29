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

class Motion;
class Character;

enum ObjectType : unsigned int;

struct CMovableHardcodeCollection
{
    static bool IsMovable(ObjectType type);
    static int GetMotionClass(ObjectType type);
    static int GetMotionSounds(ObjectType type);
    static bool GetMotionSoundPshhh(ObjectType type);

    static Motion GetLinMotion(ObjectType type);
    static Motion GetCirMotion(ObjectType type);
    static Character GetWheels(ObjectType type);

    static bool GetSlowUnderWater(ObjectType type);
    static bool GetHaveSatCom(ObjectType type);
    static SoundType GetSoundOnSlide(ObjectType type);

    static float GetMovableEnergyFactor(ObjectType type);

    static bool IsTiltOnLandAsHuman(ObjectType type);
    static bool IsTiltOnLandAsWingedRobot(ObjectType type);
    static bool IsTiltOnLandAsNormalRobot(ObjectType type);
    static bool IsTiltOnLandAsApolloRobot(ObjectType type);
    static bool IsTiltOnFlightAsAlienWasp(ObjectType type);
    static bool IsTiltOnFlightAsHuman(ObjectType type);
    static bool IsTiltOnFlightAsWingedRobot(ObjectType type);
    static bool IsTiltOnSwimAsHuman(ObjectType type);
    
    static bool IsExhaustBubblesOnEnteringWater(ObjectType type);
    static float IsExhaustBubblesOnEnteringWaterTime(ObjectType type);
    static bool IsExhaustDropsOnLeavingWater(ObjectType type);
    static bool IsExhaustOnCrashAsHuman(ObjectType type);
    static bool IsExhaustOnCrashAsTrackedRobot(ObjectType type);
    static bool IsExhaustOnCrashAsHeavyRobot(ObjectType type);
    static bool IsExhaustOnLandAsHuman(ObjectType type);
    static bool IsExhaustOnLandAsWingedRobot(ObjectType type);
    static bool IsExhaustOnLandAsHeavyRobot(ObjectType type);
    static bool IsExhaustOnLandAsNormalRobot(ObjectType type);
    static bool IsExhaustOnFlightAsHuman(ObjectType type);
    static bool IsExhaustOnFlightAsWingedRobot(ObjectType type);
    static bool IsExhaustOnSwimAsHuman(ObjectType type);
    static bool IsExhaustOnSwimAsAmphibiousRobot(ObjectType type);
    
    static float GetMaxSafeWaterLevel(ObjectType type);
    static float GetWaterSplashLevelMin(ObjectType type);
    static float GetWaterSplashLevelMax(ObjectType type);
    static float GetWaterSplashDiameter(ObjectType type);
    static float GetWaterSplashForce(ObjectType type);
    
    static CObjectTrackedMovableDetails GetTrackedDetails(ObjectType type);
    static CObjectWheeledMovableDetails GetWheeledDetails(ObjectType type);
};