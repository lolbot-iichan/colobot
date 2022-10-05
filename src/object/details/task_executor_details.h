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
 * \file object/details/task_executor_details.h
 * \brief CObjectTaskExecutorDetails - set of tweaks for TaskExecutor objects
 */

#pragma once

class CObject;
class CLevelParser;
class CLevelParserLine;

#include "graphics/engine/terrain.h"

#include "math/vector.h"

#include "object/tool_type.h"

//////////////////////////////////////////////////////////////////////////////
// Child structs
//////////////////////////////////////////////////////////////////////////////

enum TaskExecutionType
{
    ExecutionDisabled  = -1,
    ExecutionNoMotion  = 0,
    ExecutionAsHuman   = 1,
    ExecutionAsInsect  = 2,
    ExecutionAsSniffer = 3,
};

struct CObjectFlagTaskExecutorObject
{
    ObjectType output   = OBJECT_NULL;
    int        maxCount = 5;
};

struct CObjectFlagTaskExecutorDetails
{
    TaskExecutionType execution  = ExecutionNoMotion;
    int               partNum    = 0;
    Math::Vector      pos        = Math::Vector(0.0f, 0.0f, 0.0f);

    std::vector<CObjectFlagTaskExecutorObject> objects;
};

struct CObjectSniffTaskExecutorObject
{
    Gfx::TerrainRes soil   = Gfx::TR_NULL;
    ObjectType      output = OBJECT_NULL;
    std::string     message;
};

struct CObjectSniffTaskExecutorDetails
{
    TaskExecutionType execution  = ExecutionNoMotion;
    int               partNum    = 0;
    Math::Vector      pos        = Math::Vector(0.0f, 0.0f, 0.0f);

    std::vector<CObjectSniffTaskExecutorObject> objects;
};

//////////////////////////////////////////////////////////////////////////////
// Main struct
//////////////////////////////////////////////////////////////////////////////

struct CObjectTaskExecutorDetails
{
    bool     enabled = true;
    ToolType tool    = ToolType::Other;

    CObjectFlagTaskExecutorDetails  flag;  // for CTaskFlag
    CObjectSniffTaskExecutorDetails sniff; // for CTaskDeleteMark, CTaskSearch

    void ReadHardcode(ObjectType type);
    bool Read(CLevelParserLine* line);
    void Write(CLevelParser* parser, ObjectType type);
};


//////////////////////////////////////////////////////////////////////////////
// Provider
//////////////////////////////////////////////////////////////////////////////

CObjectTaskExecutorDetails GetObjectTaskExecutorDetails(CObject* obj);
CObjectTaskExecutorDetails GetObjectTaskExecutorDetails(ObjectType type);
