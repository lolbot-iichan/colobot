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
 * \file object/details/scripting_details.h
 * \brief CObjectScriptingDetails - set of tweaks for Scripting objects
 */

#pragma once

#include <string>

class CObject;
class CLevelParser;
class CLevelParserLine;

#include "object/object_type.h"

//////////////////////////////////////////////////////////////////////////////
// Child structs
//////////////////////////////////////////////////////////////////////////////

struct CObjectProduceScriptingDetails
{
    bool       isProducable      = false;
    bool       isProducedCharged = false;
    bool       isProducedManual  = false;
    ObjectType container         = OBJECT_NULL;
};

struct CObjectProduceScriptingFindable
{
    ObjectType value = OBJECT_NULL;
};

//////////////////////////////////////////////////////////////////////////////
// Main struct
//////////////////////////////////////////////////////////////////////////////

struct CObjectScriptingDetails
{
    std::string name          = "";
    std::string alias         = "";
    std::string helpTopicPath = "";

    CObjectProduceScriptingDetails produce;

    std::vector<CObjectProduceScriptingFindable> findableByRadar;

    void ReadHardcode(ObjectType type);
    bool Read(CLevelParserLine* line);
    void Write(CLevelParser* parser, ObjectType type);
};
