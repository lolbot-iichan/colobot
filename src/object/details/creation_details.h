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
 * \file object/details/creation_details.h
 * \brief CObjectCreationDetails - set of tweaks for Creation objects
 */

#pragma once

class CObject;
class CLevelParser;
class CLevelParserLine;

#include <vector>

#include "graphics/engine/engine_types.h"

#include "math/sphere.h"
#include "math/vector.h"

//////////////////////////////////////////////////////////////////////////////
// Child structs
//////////////////////////////////////////////////////////////////////////////

enum BaseClass
{
    BASE_CLASS_SIMPLE,
    BASE_CLASS_BUILDING,
    BASE_CLASS_INFO,
    BASE_CLASS_MOVABLE,
    BASE_CLASS_SHIELDER,
};

enum AutoClass
{
    AUTO_CLASS_NONE,
    AUTO_CLASS_EGG,
    AUTO_CLASS_ROOT,
    AUTO_CLASS_MUSHROOM,
    AUTO_CLASS_FLAG,
    AUTO_CLASS_TRUNK,
    AUTO_CLASS_BOAT,
    AUTO_CLASS_FAN,
};

struct CObjectCreationModelNode
{
    int                   chunkId   = -1;
    int                   parentId  = -1;
    Gfx::EngineObjectType gfxType   = Gfx::ENG_OBJTYPE_FIX;
    std::string           modFile   = "";
    Math::Vector          position  = Math::Vector();
    Math::Vector          rotation  = Math::Vector();
    bool                  copyModel = false;
};

struct CObjectCreationBuildingLevel
{
    float min    = 0.0;
    float max    = 0.0;
    float height = 0.0;
    float factor = 0.0;
};

struct CObjectCreationShadowCircle
{
    float                 radius     = 0.0;
    float                 intensity  = 0.0;
    Gfx::EngineShadowType shadowType = Gfx::ENG_SHADOW_NORM;
    bool                  factored   = false;
};

//////////////////////////////////////////////////////////////////////////////
// Main struct
//////////////////////////////////////////////////////////////////////////////

struct CObjectCreationDetails
{
    int   baseClass                 = BASE_CLASS_SIMPLE;
    int   autoClass                 = AUTO_CLASS_NONE;

// TODO split into creation and model details

    bool  isForceLoadTextures       = false;
    bool  isSetFloorHeight          = false;
    bool  isFloorAdjust             = false;
    bool  isFixedPosition           = false;
    float zoom                      = 1.0f;

    Math::Sphere                              cameraCollisionSphere;
    CObjectCreationShadowCircle               shadowCircle;
    std::string                               displayedName;

    std::vector<CObjectCreationModelNode>     model;
    std::vector<CrashSphere>                  crashSpheres;
    std::vector<CObjectCreationBuildingLevel> buildingLevels;

    void ReadHardcode(ObjectType type);
    bool Read(CLevelParserLine* line);
    void Write(CLevelParser* parser, ObjectType type);
};

//////////////////////////////////////////////////////////////////////////////
// Provider
//////////////////////////////////////////////////////////////////////////////

CObjectCreationDetails GetObjectCreationDetails(CObject* obj);
CObjectCreationDetails GetObjectCreationDetails(ObjectType type);
