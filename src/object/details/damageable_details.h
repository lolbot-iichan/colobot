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
 * \file object/details/damageable_details.h
 * \brief CObjectDamageableDetails - set of tweaks for Damageable objects
 */

#pragma once

class CObject;
class CLevelParser;
class CLevelParserLine;

#include "graphics/engine/pyro_type.h"

#include "sound/sound_type.h"

//////////////////////////////////////////////////////////////////////////////
// Child structs
//////////////////////////////////////////////////////////////////////////////

struct CObjectFireDamageDetails
{
    bool enabled = true;
};

struct CObjectOrganicDamageDetails
{
    bool      enabled   = true;
    bool      byInsects = true;
    bool      byRobots  = true;
    SoundType sound     = SOUND_TOUCH;
};

struct CObjectPhazerDamageDetails
{
    bool enabled = true;
};

struct CObjectTowerDamageDetails
{
    bool enabled = false;
};

struct CObjectFallingObjectDamageDetails
{
    bool enabled = true;
};

struct CObjectExplosiveDamageDetails
{
    bool enabled = true;
};

struct CObjectCollisionDamageDetails
{
    bool  enabled      = true;
    bool  byItself     = false;
    bool  byOthers     = true;
    float ignoreRadius = 0.0f;
    float resistance   = -1.0f;
};

struct CObjectLightningDamageDetails
{
    bool  enabled                 = true;
    float lightningRodHeight      = 0.0f;
    float lightningHitProbability = 0.0f;
};

struct CObjectFallDamageDetails
{
    bool enabled = true;
};

struct CObjectSpiderDamageDetails
{
    bool enabled = true;
};

//////////////////////////////////////////////////////////////////////////////
// Main struct
//////////////////////////////////////////////////////////////////////////////

struct CObjectDamageableDetails
{
    bool enabled = false;

    Gfx::PyroType                     effect = Gfx::PT_SHOTT;

    CObjectFireDamageDetails          fire;
    CObjectOrganicDamageDetails       organic;
    CObjectPhazerDamageDetails        phazer;
    CObjectTowerDamageDetails         tower;
    CObjectFallingObjectDamageDetails fallingObject;
    CObjectExplosiveDamageDetails     explosive;
    CObjectCollisionDamageDetails     collision;
    CObjectLightningDamageDetails     lightning;
    CObjectFallDamageDetails          fall;
    CObjectSpiderDamageDetails        spider;

    void ReadHardcode(ObjectType type);
    bool Read(CLevelParserLine* line);
    void Write(CLevelParser* parser, ObjectType type);
};
