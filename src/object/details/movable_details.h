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

/**
 * \file object/details/movable_details.h
 * \brief CObjectMovableDetails - set of tweaks for Movable objects
 */

#pragma once

class CObject;
class CLevelParser;
class CLevelParserLine;

#include "object/drive_type.h"
#include "object/old_object_interface.h"

#include "physics/physics.h"

//////////////////////////////////////////////////////////////////////////////
// Camera child structs
//////////////////////////////////////////////////////////////////////////////

struct CObjectExhaustPhysicsDetails
{
    bool bubblesOnEnteringWater      = true;
    float bubblesOnEnteringWaterTime = 8.0f;

    bool dropsOnLeavingWater     = true;
    bool onCrashAsHuman          = false;
    bool onCrashAsTrackedRobot   = false;
    bool onCrashAsHeavyRobot     = false;
    bool onLandAsHuman           = false;
    bool onLandAsWingedRobot     = false;
    bool onLandAsHeavyRobot      = false;
    bool onLandAsNormalRobot     = false;
    bool onFlightAsHuman         = false;
    bool onFlightAsWingedRobot   = false;
    bool onSwimAsHuman           = false;
    bool onSwimAsAmphibiousRobot = false;
};

struct CObjectWaterPhysicsDetails
{
    float waterLevel         = 0.0f;
    float splashLevelMin     = 0.0f;
    float splashLevelMax     = 9.0f;
    float splashDiameter     = 2.5f;
    float splashForce        = 1.3f;
};

//////////////////////////////////////////////////////////////////////////////
// Main struct
//////////////////////////////////////////////////////////////////////////////

struct CObjectMovableDetails
{
    bool      enabled = false;
    DriveType drive   = DriveType::Other;

    Motion    linMotion;
    Motion    cirMotion;
    Character wheels;

    CObjectExhaustPhysicsDetails exhaust;
    CObjectWaterPhysicsDetails   water;

    void ReadHardcode(ObjectType type);
    bool Read(CLevelParserLine* line);
    void Write(CLevelParser* parser, ObjectType type);
};

//////////////////////////////////////////////////////////////////////////////
// Provider
//////////////////////////////////////////////////////////////////////////////

CObjectMovableDetails GetObjectMovableDetails(CObject* obj);
CObjectMovableDetails GetObjectMovableDetails(ObjectType type);
