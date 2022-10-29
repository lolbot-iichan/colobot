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

#include "common/global.h"

#include "graphics/engine/particle.h"
#include "graphics/engine/pyro_type.h"
#include "graphics/engine/terrain.h"

#include "object/task/task.h"
#include "object/task/taskgoto.h"

#include "object/object_type.h"

//////////////////////////////////////////////////////////////////////////////
// Child structs
//////////////////////////////////////////////////////////////////////////////

struct CObjectAimTaskExecutorDetails : public CTaskConditions
{
    int   partNum = -1;
    float minY    = 0.0f;
    float maxY    = 0.0f;
    float minZ    = 0.0f;
    float maxZ    = 0.0f;
};

struct CObjectBuildTaskExecutorObject
{
    ObjectType  input      = OBJECT_NULL;
    ObjectType  output     = OBJECT_NULL;
    std::string message    = "";
    float       reqRadius  = 0.0f;
    bool        needRecede = false;
};

struct CObjectDemarkTaskExecutorObject;

struct CObjectBuildTaskExecutorDetails : public CTaskConditions
{
    TaskExecutionType execution      = ExecutionNoMotion;
    bool              cancelOnMotion = false;
    int               partNum        = 0;
    glm::vec3         particlePos    = glm::vec3(0.0f, 0.0f, 0.0f);

    std::vector<CObjectBuildTaskExecutorObject> objects;
    std::vector<CObjectDemarkTaskExecutorObject> remove;
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
    glm::vec3         position   = glm::vec3(0.0f, 0.0f, 0.0f);

    float             radius     = 10.0f;

    std::vector<CObjectDeflagTaskExecutorObject> objects;
};

struct CObjectDemarkTaskExecutorObject
{
    ObjectType      input   = OBJECT_NULL;
};

struct CObjectDemarkTaskExecutorDetails : public CTaskConditions
{
    float radius = 8.0f;

    std::vector<CObjectDemarkTaskExecutorObject> objects;
};

enum FireType
{
    FIRE_CANNON = 1,
    FIRE_ORGA   = 2,
    FIRE_PHAZER = 3
};

struct CObjectFireTaskExecutorDetails : public CTaskConditions
{
    int               partNum      = 0;
    glm::vec3         position     = glm::vec3(0.0f, 0.0f, 0.0f);
    int               fireType     = FIRE_CANNON;
    Gfx::ParticleType particle     = static_cast<Gfx::ParticleType>(0);
    float             duration     = 1.0f;
    float             energyPerSec = 0.0f;
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
    glm::vec3         position   = glm::vec3(0.0f, 0.0f, 0.0f);

    std::vector<CObjectFlagTaskExecutorObject> objects;
};

struct CObjectRecycleTaskExecutorObject
{
    ObjectType  input   = OBJECT_NULL;
    ObjectType  output  = OBJECT_NULL;
    std::string message = "";
};

struct CObjectRecycleTaskExecutorDetails : public CTaskConditions
{
    TaskExecutionType execution  = ExecutionNoMotion;
    int               partNum    = 0;
    glm::vec3         position   = glm::vec3(0.0f, 0.0f, 0.0f);
    float             distance   = 0.0f;

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
    glm::vec3         position   = glm::vec3(0.0f, 0.0f, 0.0f);

    std::vector<CObjectSniffTaskExecutorObject> objects;
};

struct CObjectTakeTaskExecutorDetails : public CTaskConditions
{
};

struct CObjectManipTaskExecutorDetails : public CTaskConditions
{
    TaskExecutionType execution  = ExecutionNoMotion;
};

struct CObjectThumpTaskExecutorObject
{
    ObjectType      target   = OBJECT_NULL;
    int             action   = -1;
};

struct CObjectThumpTaskExecutorDetails : public CTaskConditions
{
    TaskExecutionType execution  = ExecutionNoMotion;
    int               partNum    = 0;
    glm::vec3         position   = glm::vec3(0.0f, 0.0f, 0.0f);
    float             radius     = 0.0f;

    std::vector<CObjectThumpTaskExecutorObject> objects;
};

struct CObjectGotoTaskExecutorDetails : public CTaskConditions
{
    bool                  acceptWater  = false;
    bool                  acceptFlying = false;
    float                 angleLimit   = 20.0f*Math::PI/180.0f;

    bool                  approximate  = false;
    bool                  noAdjusting  = false;    // target object's center, not battery
    int /*TaskGotoGoal*/  defaultGoal  = TGG_STOP;
    int /*TaskGotoCrash*/ defaultCrash = TGC_BEAM;

    bool                  repulseEnabled = true;
    bool                  repulseCustom  = false;
    float                 repulseLand    = 0.0f;
    float                 repulseNoLand  = 0.0f;
    float                 repulseFactor  = 2.0f;
};

typedef CTaskConditions CObjectAdvanceTaskExecutorDetails;
typedef CTaskConditions CObjectExplodeTaskExecutorDetails;
typedef CTaskConditions CObjectFireAntTaskExecutorDetails;
typedef CTaskConditions CObjectInfoTaskExecutorDetails;
typedef CTaskConditions CObjectPenTaskExecutorDetails;
typedef CTaskConditions CObjectShieldTaskExecutorDetails;
typedef CTaskConditions CObjectTurnTaskExecutorDetails;
typedef CTaskConditions CObjectWaitTaskExecutorDetails;

//////////////////////////////////////////////////////////////////////////////
// Main struct
//////////////////////////////////////////////////////////////////////////////

struct CObjectTaskExecutorDetails
{
    bool     enabled = true;

    CObjectAimTaskExecutorDetails     aim;      // for CTaskGunGoal (aim)
    CObjectAdvanceTaskExecutorDetails advance;  // for CTaskAdvance (move)
    CObjectBuildTaskExecutorDetails   build;    // for CTaskBuild (build)
    CObjectDeflagTaskExecutorDetails  deflag;   // for CTaskDeflag (deflag)
    CObjectDemarkTaskExecutorDetails  demark;   // for CTaskDeleteMark (deletemark)
    CObjectExplodeTaskExecutorDetails explode;  // for CTaskSpiderExplo (fire)
    CObjectFireTaskExecutorDetails    fire;     // for CTaskFire (fire)
    CObjectFireAntTaskExecutorDetails fireant;  // for CTaskFireAnt (fire)
    CObjectFlagTaskExecutorDetails    flag;     // for CTaskFlag (flag)
    CObjectGotoTaskExecutorDetails    GOTO;     // for CTaskGoto (goto)
    CObjectInfoTaskExecutorDetails    info;     // for CTaskInfo (send/receive)
    CObjectPenTaskExecutorDetails     pen;      // for CTaskPen (pendown/penup/pencolor)
    CObjectRecycleTaskExecutorDetails recycle;  // for CTaskRecover (recycle)
    CObjectShieldTaskExecutorDetails  shield;   // for CTaskShield (shield)
    CObjectSniffTaskExecutorDetails   sniff;    // for CTaskSearch (sniff)
    CObjectTakeTaskExecutorDetails    take;     // for CTaskTake (grab/drop)
    CObjectManipTaskExecutorDetails   manip;    // for CTaskManip (grab/drop)
    CObjectThumpTaskExecutorDetails   thump;    // for CTaskTerraform (thump)
    CObjectTurnTaskExecutorDetails    turn;     // for CTaskTurn (turn)
    CObjectWaitTaskExecutorDetails    wait;     // for CTaskWait (wait)

    void ReadHardcode(ObjectType type);
    bool Read(CLevelParserLine* line);
    void Write(CLevelParser* parser, ObjectType type);
};
