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
 * \file object/details/automation_details.h
 * \brief CObjectAutomationDetails - set of tweaks for Automation objects
 */

#pragma once

class CObject;
class CLevelParser;
class CLevelParserLine;

#include "graphics/engine/terrain.h"

//////////////////////////////////////////////////////////////////////////////
// Child structs
//////////////////////////////////////////////////////////////////////////////

enum AutoClass
{
    AUTO_CLASS_NONE = 0,

    // jostling, has Start()
    AUTO_CLASS_FLAG = 10,

    // growing object, self-destroy
    AUTO_CLASS_EGG = 20,

    // dig something with CObjectDiggingAutomationDetails
    AUTO_CLASS_DERRICK = 30,
    AUTO_CLASS_NEST    = 31,

    // convert something with CObjectProductionAutomationDetails
    AUTO_CLASS_CONVERT      = 40,
    AUTO_CLASS_NUCLEARPLANT = 41,
    AUTO_CLASS_POWERPLANT   = 42,

    // unlocking objects
    AUTO_CLASS_VAULT = 50,

    // research tasks executors
    AUTO_CLASS_LABO     = 60,
    AUTO_CLASS_RESEARCH = 61,

    // other tasks executors
    AUTO_CLASS_BASE      = 70,
    AUTO_CLASS_DESTROYER = 71,
    AUTO_CLASS_FACTORY   = 72,

    // auto-targeting something
    AUTO_CLASS_MUSHROOM     = 80,
    AUTO_CLASS_RADAR        = 81,
    AUTO_CLASS_ROOT         = 82,
    AUTO_CLASS_POWERCAPTOR  = 83,
    AUTO_CLASS_POWERSTATION = 84,
    AUTO_CLASS_REPAIR       = 85,
    AUTO_CLASS_TOWER        = 86,

    // just nice animation
    AUTO_CLASS_HUSTON       = 90,
    AUTO_CLASS_TEEN_BOAT    = 91,
    AUTO_CLASS_TEEN_FAN     = 92,
    AUTO_CLASS_TEEN_TRUNK   = 93,

    // half-vehicle, half-building
    AUTO_CLASS_PORTICO      = 99,
};

struct CObjectBlockingAutomationDetails
{
    bool blocksBuilding        = false;
    bool blocksPowerPlant      = false;
    bool blocksNuclearPlant    = false;
    bool blocksFactory         = false;
};

struct CObjectTargetedAutomationDetails
{
    bool attackedByTower       = false;
    bool attackedByMushroom    = false;
    bool chargedByPowerStation = false;
    bool commentedByAssistant  = false;
};

struct CObjectProductionAutomation
{
    ObjectType  input  = OBJECT_NULL;
    ObjectType  output = OBJECT_NULL;
    std::string message;
};

struct CObjectProductionAutomationDetails
{
    std::string                              noInput;
    std::string                              badInput;
    std::vector<CObjectProductionAutomation> objects;
};

struct CObjectDiggingAutomation
{
    Gfx::TerrainRes soil     = Gfx::TR_ANY;
    ObjectType      output   = OBJECT_NULL;
    int             maxCount = -1;
    float           duration = 10.0f;
    std::string     message;
};

struct CObjectDiggingAutomationDetails
{
    std::string     noSoil;
    int             partNum = 0;
    Math::Vector    position;

    std::vector<CObjectDiggingAutomation> objects;
};

//////////////////////////////////////////////////////////////////////////////
// Main struct
//////////////////////////////////////////////////////////////////////////////


struct CObjectAutomationDetails
{
    int   autoClass                 = AUTO_CLASS_NONE;

    CObjectBlockingAutomationDetails blocking;
    CObjectTargetedAutomationDetails targeted;

    CObjectProductionAutomationDetails production;
    CObjectDiggingAutomationDetails    digging;

    void ReadHardcode(ObjectType type);
    bool Read(CLevelParserLine* line);
    void Write(CLevelParser* parser, ObjectType type);
};

//////////////////////////////////////////////////////////////////////////////
// Provider
//////////////////////////////////////////////////////////////////////////////

CObjectAutomationDetails GetObjectAutomationDetails(CObject* obj);
