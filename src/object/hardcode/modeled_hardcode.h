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

#include "math/sphere.h"

#include <vector>

class CObjectModeledNode;
class CObjectModeledCrashSphere;
class CObjectModeledLevel;
class CObjectModeledShadowCircle;
class CObjectModeledShadowLight;

enum ObjectType : unsigned int;

struct CModeledHardcodeCollection
{
    static std::string GetDisplayedName(ObjectType type);

    static std::vector<CObjectModeledNode> GetModel(ObjectType type);
    static std::vector<CObjectModeledNode> GetModeledHead(ObjectType type);
    static std::vector<CObjectModeledCrashSphere> GetModeledCrashSpheres(ObjectType type);
    static Math::Sphere GetModeledCameraCollisionSphere(ObjectType type);
    static std::vector<CObjectModeledLevel> GetModeledLevels(ObjectType type);
    static CObjectModeledShadowCircle GetModeledShadowCircle(ObjectType type);
    static CObjectModeledShadowLight GetModeledShadowLight(ObjectType type);

    static float GetModeledScale(ObjectType type);
    static bool IsModeledForceLoadTextures(ObjectType type);
    static bool IsModeledSetFloorHeight(ObjectType type);
    static bool IsModeledFloorAdjust(ObjectType type);
    static bool IsModeledFixedPosition(ObjectType type);
};