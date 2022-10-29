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
 * \file object/details/global_details.h
 * \brief CObjectGlobalDetails - set of tweaks for Global objects
 */

#pragma once

class CLevelParser;
class CLevelParserLine;

#include "object/object_type.h"

#include <string>
#include <vector>

//////////////////////////////////////////////////////////////////////////////
// Children structs
//////////////////////////////////////////////////////////////////////////////

struct CObjectDebugButton
{
    ObjectType  type = OBJECT_NULL;
    int         icon = -1;
    std::string text = "";
};

struct CGlobalDefaultObjects
{
    ObjectType player           = OBJECT_NULL;
    ObjectType controller       = OBJECT_NULL;
    ObjectType base             = OBJECT_NULL;
    ObjectType assistant        = OBJECT_NULL;
    ObjectType arrow            = OBJECT_NULL;
    ObjectType destroyPerformer = OBJECT_NULL;
    ObjectType factoryPerformer = OBJECT_NULL;
    ObjectType takeoffPerformer = OBJECT_NULL;
    ObjectType receivePerformer = OBJECT_NULL;
};

//////////////////////////////////////////////////////////////////////////////
// Main struct
//////////////////////////////////////////////////////////////////////////////

struct CObjectGlobalDetails
{
    CGlobalDefaultObjects      defaults;

    std::vector<CObjectDebugButton> debugMenu;

    void ReadHardcode();
    bool Read(CLevelParserLine* line);
    void Write(CLevelParser* parser);
};
