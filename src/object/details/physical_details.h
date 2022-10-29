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
 * \file object/details/physical_details.h
 * \brief CObjectPhysicalDetails - set of tweaks for Physical objects
 */

#pragma once

class CObject;
class CLevelParser;
class CLevelParserLine;

#include "math/sphere.h"

#include "object/object_part_filter.h"

//////////////////////////////////////////////////////////////////////////////
// Child structs
//////////////////////////////////////////////////////////////////////////////

struct CObjectExplosivePhysicalDetails
{
    bool  enabled        = false;
    float collisionForce = 0.0f;
};

struct CObjectHotPointPhysicalDetails
{
    bool      enabled    = false;
    int       partNum    = {};
    glm::vec3 position   = {};
    float     suppl      = 0.0f;
    bool      dxTake     = false;
    bool      dxOther    = false;
    bool      dxDistance = false;
    bool      dxSuppl    = false;
    bool      flyingOnly = false;
};

struct CObjectApproachingPhysicalDetails
{
    bool      gotoSmallDistance = false;
    bool      gotoPowerCell     = false;
};

//////////////////////////////////////////////////////////////////////////////
// Main struct
//////////////////////////////////////////////////////////////////////////////

struct CObjectPhysicalDetails
{
    // related to collisions
    bool  squashing         = false;
    float collisionSoftness = 200.0f;

    CObjectExplosivePhysicalDetails   explosive;
    CObjectHotPointPhysicalDetails    hotpoint;
    CObjectApproachingPhysicalDetails approaching;

    // related to build task
    float height            = 0.0f;
    float noBuildRadius     = 0.0f;
    bool  hasBuildMargin    = false;

    // related to shooting
    bool  isBulletWall      = false;

    void ReadHardcode(ObjectType type);
    bool Read(CLevelParserLine* line);
    void Write(CLevelParser* parser, ObjectType type);
};
