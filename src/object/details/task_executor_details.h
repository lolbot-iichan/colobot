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

#include "graphics/engine/pyro_type.h"
#include "graphics/engine/terrain.h"

#include "math/vector.h"

#include "object/tool_type.h"

#include "object/task/task.h"

//////////////////////////////////////////////////////////////////////////////
// Child structs
//////////////////////////////////////////////////////////////////////////////

struct CObjectAimTaskExecutorDetails
{
    bool  enabled  = false;
    int   partNum = -1;

    float minY    = 0.0f;
    float maxY    = 0.0f;
    float minZ    = 0.0f;
    float maxZ    = 0.0f;
};

struct CObjectBuildTaskExecutorObject
{
    ObjectType  input   = OBJECT_NULL;
    ObjectType  output  = OBJECT_NULL;
    std::string message = "";

    int         icon    = -1;
    std::string text    = "";
};

struct CObjectBuildTaskExecutorDetails : public CTaskConditions
{
    TaskExecutionType execution  = ExecutionNoMotion;
    int               partNum    = 0;
    Math::Vector      position   = Math::Vector(0.0f, 0.0f, 0.0f);

    std::vector<CObjectBuildTaskExecutorObject> objects;
};

struct CObjectDeflagTaskExecutorObject
{
    ObjectType    input   = OBJECT_NULL;
    ObjectType    output  = OBJECT_NULL;
    std::string   message = "";
    
    Gfx::PyroType effect  = Gfx::PT_FLDELETE;
};

struct CObjectDeflagTaskExecutorDetails : public CTaskConditions
{
    TaskExecutionType execution  = ExecutionNoMotion;
    int               partNum    = 0;
    Math::Vector      position   = Math::Vector(0.0f, 0.0f, 0.0f);

    float             radius     = 10.0f;

    std::vector<CObjectDeflagTaskExecutorObject> objects;
};

struct CObjectFlagTaskExecutorObject
{
    ObjectType  output  = OBJECT_NULL;
    std::string message = "";

    int         maxCount = 5;
};

struct CObjectFlagTaskExecutorDetails : public CTaskConditions
{
    TaskExecutionType execution  = ExecutionNoMotion;
    int               partNum    = 0;
    Math::Vector      position   = Math::Vector(0.0f, 0.0f, 0.0f);

    std::vector<CObjectFlagTaskExecutorObject> objects;
};

struct CObjectRecycleTaskExecutorObject
{
    ObjectType  input   = OBJECT_NULL;
    ObjectType  output  = OBJECT_NULL;
    std::string message = "";
};

struct CObjectRecycleTaskExecutorDetails
{
//TODO    bool              enabled    = false;
//TODO    TaskExecutionType execution  = ExecutionNoMotion;
//TODO    int               partNum    = 0;
//TODO    Math::Vector      position   = Math::Vector(0.0f, 0.0f, 0.0f);

    std::vector<CObjectRecycleTaskExecutorObject> objects;
};

struct CObjectSniffTaskExecutorObject
{
    Gfx::TerrainRes soil    = Gfx::TR_ANY;
    ObjectType      output  = OBJECT_NULL;
    std::string     message = "";
};

struct CObjectSniffTaskExecutorDetails : public CTaskConditions
{
    TaskExecutionType execution  = ExecutionNoMotion;
    int               partNum    = 0;
    Math::Vector      position   = Math::Vector(0.0f, 0.0f, 0.0f);

    std::vector<CObjectSniffTaskExecutorObject> objects;
};

struct CObjectThumpTaskExecutorObject
{
    ObjectType      target   = OBJECT_NULL;
    int             action   = -1;
    float           min      = 0.0f;
    float           max      = 9.9f;
};

struct CObjectThumpTaskExecutorDetails
{
    bool              enabled    = false;
    TaskExecutionType execution  = ExecutionNoMotion;

    std::vector<CObjectThumpTaskExecutorObject> objects;
};

//////////////////////////////////////////////////////////////////////////////
// Main struct
//////////////////////////////////////////////////////////////////////////////

struct CObjectTaskExecutorDetails
{
    bool     enabled = true;
    ToolType tool    = ToolType::Other;

    CObjectAimTaskExecutorDetails     aim;      // for CTaskGunGoal (aim)
    CObjectBuildTaskExecutorDetails   build;    // for CTaskBuild (build)
    CObjectDeflagTaskExecutorDetails  deflag;   // for CTaskDeflag (deflag)
    CObjectFlagTaskExecutorDetails    flag;     // for CTaskFlag (flag)
    CObjectRecycleTaskExecutorDetails recycle;  // for CTaskRecover (recycle)
    CObjectSniffTaskExecutorDetails   sniff;    // for CTaskDeleteMark, CTaskSearch (sniff, deletemark)
//    CObjectThumpTaskExecutorDetails   thump;    // for CTaskTerraform (thump)

    void ReadHardcode(ObjectType type);
    bool Read(CLevelParserLine* line);
    void Write(CLevelParser* parser, ObjectType type);
};


//////////////////////////////////////////////////////////////////////////////
// Provider
//////////////////////////////////////////////////////////////////////////////

CObjectTaskExecutorDetails GetObjectTaskExecutorDetails(CObject* obj);
CObjectTaskExecutorDetails GetObjectTaskExecutorDetails(ObjectType type);
