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
 * \file object/details/modeled_details.h
 * \brief CObjectModeledDetails - set of tweaks for Modeled objects
 */

#pragma once

class CObject;
class CLevelParser;
class CLevelParserLine;

#include "graphics/engine/engine_types.h"

#include "object/crash_sphere.h"
#include "object/object_part_filter.h"

#include "math/sphere.h"

#include <string>
#include <vector>

//////////////////////////////////////////////////////////////////////////////
// Child structs
//////////////////////////////////////////////////////////////////////////////

struct CObjectModeledNode
{
    int                   chunkId   = -1;
    int                   parentId  = -1;
    Gfx::EngineObjectType gfxType   = Gfx::ENG_OBJTYPE_FIX;
    std::string           modFile   = "";
    glm::vec3             position  = glm::vec3();
    glm::vec3             rotation  = glm::vec3();
    glm::vec3             zoom      = glm::vec3(1.0f, 1.0f, 1.0f);
    bool                  mirrored  = false;
    bool                  copyModel = false;
    int                   filter    = PART_ALWAYS;
    int                   glasses   = 0;
};

struct CObjectModeledLevel
{
    float min    = 0.0;
    float max    = 0.0;
    float height = 0.0;
    float factor = 0.0;
};

struct CObjectModeledShadowCircle
{
    float radius     = 0.0;
    float intensity  = 0.0;
    bool  wormLike   = false;
    bool  factored   = false;
};

struct CObjectModeledShadowLight
{
    float      height = 0.0f;
    Gfx::Color color  = {0.0f, 0.0f, 0.0f};
};

struct CObjectModeledCrashSphere
{
    CrashSphere           sphere;
    int                   filter    = PART_ALWAYS;
};

//////////////////////////////////////////////////////////////////////////////
// Main struct
//////////////////////////////////////////////////////////////////////////////

struct CObjectModeledDetails
{
    bool         enabled = false;
    std::string  displayedName             = {};
    bool         isForceLoadTextures       = false;
    bool         isSetFloorHeight          = false;
    bool         isFloorAdjust             = false;
    bool         isFixedPosition           = false;
    float        zoom                      = 1.0f;

    CObjectModeledShadowCircle       shadowCircle;
    CObjectModeledShadowLight        shadowLight;
    Math::Sphere                     cameraCollisionSphere;

    std::vector<CObjectModeledNode>  model;
    std::vector<CObjectModeledNode>  headModel;

    std::vector<CObjectModeledLevel> buildingLevels;
    std::vector<CObjectModeledCrashSphere>   crashSpheres;

    void ReadHardcode(ObjectType type);
    bool Read(CLevelParserLine* line);
    void Write(CLevelParser* parser, ObjectType type);
};
