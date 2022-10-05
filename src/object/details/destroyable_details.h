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
 * \file object/details/destroyable_details.h
 * \brief CObjectDestroyableDetails - set of tweaks for Destroyable objects
 */

#pragma once

class CObject;
class CLevelParser;
class CLevelParserLine;

#include "graphics/engine/pyro_type.h"

//////////////////////////////////////////////////////////////////////////////
// Child structs
//////////////////////////////////////////////////////////////////////////////

struct CObjectExplosionDestroyableDetails
{
    Gfx::PyroType effect      = Gfx::PT_EXPLOT;
};

struct CObjectWaterDestroyableDetails
{
    bool enabled              = false;
    Gfx::PyroType effect      = Gfx::PT_FRAGW;
};

struct CPyroBurnPartDetails
{
    int          partNum = -1;
    Math::Vector pos;
    Math::Vector posRandom;
    Math::Vector angle;
    Math::Vector angleRandom;
    bool         keep = false;
};

struct CObjectBurningDestroyableDetails
{
    Gfx::PyroType effect            = Gfx::PT_BURNT;
    bool          isKilledByBurning = true;
    ObjectType    ruins             = OBJECT_NULL;
    std::vector<CPyroBurnPartDetails> parts;
};

struct CObjectDrownedDestroyableDetails
{
    Gfx::PyroType effect      = Gfx::PT_DEADW;
};

struct CObjectWinDestroyableDetails
{
    Gfx::PyroType effect      = Gfx::PT_WPCHECK;
};

struct CObjectSquashDestroyableDetails
{
    bool enabled              = false;
    Gfx::PyroType effect      = Gfx::PT_SQUASH;
};

//////////////////////////////////////////////////////////////////////////////
// Main struct
//////////////////////////////////////////////////////////////////////////////

struct CObjectDestroyableDetails
{
    bool enabled              = false;
    bool removeBuildingLevel  = false; // TODO: maybe we should just check for BuildingLevel in creation model ?!

    CObjectExplosionDestroyableDetails explosion;
    CObjectWaterDestroyableDetails     water;
    CObjectBurningDestroyableDetails   burning;
    CObjectDrownedDestroyableDetails   drowned;
    CObjectWinDestroyableDetails       win;
    CObjectSquashDestroyableDetails    squash;

    void ReadHardcode(ObjectType type);
    bool Read(CLevelParserLine* line);
    void Write(CLevelParser* parser, ObjectType type);
};

//////////////////////////////////////////////////////////////////////////////
// Provider
//////////////////////////////////////////////////////////////////////////////

CObjectDestroyableDetails GetObjectDestroyableDetails(CObject* obj);
