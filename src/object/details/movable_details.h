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

#include "object/old_object_interface.h"

#include "physics/physics.h"

#include "sound/sound_type.h"

//////////////////////////////////////////////////////////////////////////////
// Motion child structs
//////////////////////////////////////////////////////////////////////////////

enum MotionClass
{
    MOTION_CLASS_SIMPLE  = 0,

    MOTION_CLASS_HUMAN   = 1,

    MOTION_CLASS_ANT     = 11,
    MOTION_CLASS_BEE     = 12,
    MOTION_CLASS_SPIDER  = 13,
    MOTION_CLASS_WORM    = 14,
    MOTION_CLASS_MOTHER  = 15,

    MOTION_CLASS_WHEELED = 20,
    MOTION_CLASS_TRACKED = 21,
    MOTION_CLASS_WINGED  = 22,
    MOTION_CLASS_LEGGED  = 23,

    MOTION_CLASS_TOTO    = 30,
};

enum MotionSoundsType
{
    MOTION_SOUND_NONE    = 0,

    MOTION_SOUND_HUMAN   = 1,

    MOTION_SOUND_ANT     = 11,
    MOTION_SOUND_BEE     = 12,
    MOTION_SOUND_SPIDER  = 13,
    MOTION_SOUND_WORM    = 14,
    MOTION_SOUND_MOTHER  = 15,

    MOTION_SOUND_WHEELED = 20,
    MOTION_SOUND_APOLLO  = 21,
    MOTION_SOUND_TRACKED = 22,
    MOTION_SOUND_HEAVY   = 23,
    MOTION_SOUND_SUBBER  = 24,
    MOTION_SOUND_WINGED  = 25,
    MOTION_SOUND_LEGGED  = 26,
};

struct CObjectTiltPhysicsDetails
{
    bool  onLandAsHuman              = false;
    bool  onLandAsWingedRobot        = false;
    bool  onLandAsNormalRobot        = false;
    bool  onLandAsApolloRobot        = false;
    bool  onFlightAsAlienWasp        = false;
    bool  onFlightAsHuman            = false;
    bool  onFlightAsWingedRobot      = false;
    bool  onSwimAsHuman              = false;
};

struct CObjectExhaustPhysicsDetails
{
    bool  bubblesOnEnteringWater     = true;
    float bubblesOnEnteringWaterTime = 8.0f;

    bool  dropsOnLeavingWater        = true;
    bool  onCrashAsHuman             = false;
    bool  onCrashAsTrackedRobot      = false;
    bool  onCrashAsHeavyRobot        = false;
    bool  onLandAsHuman              = false;
    bool  onLandAsWingedRobot        = false;
    bool  onLandAsHeavyRobot         = false;
    bool  onLandAsNormalRobot        = false;
    bool  onFlightAsHuman            = false;
    bool  onFlightAsWingedRobot      = false;
    bool  onSwimAsHuman              = false;
    bool  onSwimAsAmphibiousRobot    = false;
};

struct CObjectWaterPhysicsDetails
{
    float waterLevel         = 0.0f;
    float splashLevelMin     = 0.0f;
    float splashLevelMax     = 9.0f;
    float splashDiameter     = 2.5f;
    float splashForce        = 1.3f;
};

struct CObjectTrackedMovableDetails
{
    float rotationMin        = 0.0f; 
    float rotationMax        = 0.0f; 
};

struct CObjectWheeledMovableDetails
{
    float back                = -3.0f;  // back wheels position
    float front               =  2.0f;  // front wheels position
    float dist                =  3.0f;  // distancing wheels Z
    float radius              =  1.0f;
    float rotationSpeed       =  1.0f;
    bool  hasMudCovers        = false; 
};

//////////////////////////////////////////////////////////////////////////////
// Main struct
//////////////////////////////////////////////////////////////////////////////

struct CObjectMovableDetails
{
    bool      enabled        = false;
    int       motionClass    = MOTION_CLASS_SIMPLE;
    int       sounds         = MOTION_SOUND_NONE;
    bool      pshhh          = false;
    bool      slowUnderWater = false;
    bool      haveSatCom     = false;

    SoundType onSlide        = SOUND_SLIDE;

    float     energyFactor   = 0.005f;

    Motion    linMotion;
    Motion    cirMotion;
    Character wheels;

    CObjectTiltPhysicsDetails    tilt;
    CObjectExhaustPhysicsDetails exhaust;
    CObjectWaterPhysicsDetails   water;

    // fine tuning for some motion classes
    CObjectTrackedMovableDetails tracked;
    CObjectWheeledMovableDetails wheeled;

    void ReadHardcode(ObjectType type);
    bool Read(CLevelParserLine* line);
    void Write(CLevelParser* parser, ObjectType type);
};
