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
 * \file object/details/automated_details.h
 * \brief CObjectAutomatedDetails - set of tweaks for Automated objects
 */

#pragma once

class CObject;
class CLevelParser;
class CLevelParserLine;

#include "graphics/engine/terrain.h"

#include "object/object_type.h"

//////////////////////////////////////////////////////////////////////////////
// Child structs
//////////////////////////////////////////////////////////////////////////////

enum AutoClass
{
    AUTO_CLASS_NONE = 0,

    // jostling, has Start()
    AUTO_CLASS_FLAG = 10,

    // grow something with CObjectEggAutomatedDetails
    AUTO_CLASS_EGG = 20,

    // dig something with CObjectDiggingAutomatedDetails
    AUTO_CLASS_DERRICK = 30,
    AUTO_CLASS_NEST    = 31,

    // convert something with CObjectProductionAutomatedDetails
    AUTO_CLASS_CONVERT      = 40,
    AUTO_CLASS_NUCLEARPLANT = 41,
    AUTO_CLASS_POWERPLANT   = 42,

    // unlock on something with CObjectVaultAutomatedDetails
    AUTO_CLASS_VAULT = 50,

    // research automated
    AUTO_CLASS_LABO     = 60,
    AUTO_CLASS_RESEARCH = 61,

    // other interactive automated executors
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
    AUTO_CLASS_WORM_INFECT  = 87,

    // just nice animation
    AUTO_CLASS_HUSTON       = 90,
    AUTO_CLASS_QUARZ        = 91,
    AUTO_CLASS_TEEN_BOAT    = 92,
    AUTO_CLASS_TEEN_FAN     = 93,
    AUTO_CLASS_TEEN_LAMP    = 94,
    AUTO_CLASS_TEEN_TRUNK   = 95,

    // storing info
    AUTO_CLASS_INFO         = 100,

    // vehicle automated
    AUTO_CLASS_PORTICO      = 110,
    AUTO_CLASS_ORGA_CANNON  = 111,

    // teen objects
};

struct CObjectBlockingAutomatedDetails
{
    bool blocksBuilding        = false;
    bool blocksPowerPlant      = false;
    bool blocksNuclearPlant    = false;
    bool blocksFactory         = false;
};

struct CObjectTargetedAutomatedDetails
{
    bool attackedByTower       = false;
    bool attackedByMushroom    = false;
    bool chargedByPowerStation = false;
    bool commentedByAssistant  = false;
};

struct CObjectFactoryAutomatedObject
{
    ObjectType  input       = OBJECT_NULL;
    ObjectType  output      = OBJECT_NULL;
    std::string message     = "";
    int         partNum     = 0;
    glm::vec3   position    = {0.0f, 0.0f, 0.0f};
    int         researches  = 0;
    bool        rotateTweak = false;
};

struct CObjectFactoryAutomatedDetails
{
    std::vector<CObjectFactoryAutomatedObject> objects;
};

struct CObjectEggAutomated
{
    ObjectType  input      = OBJECT_NULL;
    float       duration   = 5.0;
    float       beginScale = 0.2;
    float       endScale   = 1.0;
    std::string message;
};

struct CObjectEggAutomatedDetails
{
    std::string                       noInput;
    std::vector<CObjectEggAutomated> objects;
};

struct CObjectDiggingAutomated
{
    Gfx::TerrainRes soil     = Gfx::TR_ANY;
    ObjectType      output   = OBJECT_NULL;
    int             maxCount = -1;
    float           duration = 10.0f;
    std::string     message;
};

struct CObjectDiggingAutomatedDetails
{
    std::string     noSoil;
    int             partNum  = 0;
    glm::vec3       position = {0.0f, 0.0f, 0.0f};

    std::vector<CObjectDiggingAutomated> objects;
};

struct CObjectProductionAutomated
{
    ObjectType  input  = OBJECT_NULL;
    ObjectType  output = OBJECT_NULL;
    std::string message;
};

struct CObjectProductionAutomatedDetails
{
    std::string                              noInput;
    std::string                              badInput;
    std::vector<CObjectProductionAutomated> objects;
};

struct CObjectVaultKey
{
    ObjectType      input    = OBJECT_NULL;
    int             slotNum  = -1;
};

struct CObjectVaultMovement
{
    int             needKeys = -1;
    int             partNum  = 0;
    glm::vec3       position = {0.0f, 0.0f, 0.0f};
    glm::vec3       rotation = {0.0f, 0.0f, 0.0f};
};

struct CObjectVaultAutomatedDetails
{
    std::vector<CObjectVaultKey>      keys;
    std::vector<CObjectVaultMovement> doors;
};

struct CObjectLampAutomatedParticle
{
    int             partNum   = 0;
    glm::vec3       position  = {0.0f, 0.0f, 0.0f};
    float           size      = 0.0f;
};

struct CObjectLampAutomatedSpot
{
    int             partNum   = 0;
    glm::vec3       position  = {0.0f, 0.0f, 0.0f};
    Gfx::Color      color     = {};
};

struct CObjectLampAutomatedDetails
{
    CObjectLampAutomatedParticle particle;
    CObjectLampAutomatedSpot     spot;
};

struct CObjectQuarzAutomatedDetails
{
    int             numLights = 0;
    int             partNum   = 0;
    glm::vec3       position  = {0.0f, 0.0f, 0.0f};
    float           radius    = 0.0f;
};

//////////////////////////////////////////////////////////////////////////////
// Main struct
//////////////////////////////////////////////////////////////////////////////


struct CObjectAutomatedDetails
{
    int   autoClass                 = AUTO_CLASS_NONE;

    CObjectBlockingAutomatedDetails blocking;
    CObjectTargetedAutomatedDetails targeted;

    CObjectFactoryAutomatedDetails    factory;
    CObjectEggAutomatedDetails        egg;
    CObjectProductionAutomatedDetails production;
    CObjectDiggingAutomatedDetails    digging;
    CObjectVaultAutomatedDetails      vault;
    CObjectQuarzAutomatedDetails      quarz;
    CObjectLampAutomatedDetails       lamp;

    void ReadHardcode(ObjectType type);
    bool Read(CLevelParserLine* line);
    void Write(CLevelParser* parser, ObjectType type);
};
