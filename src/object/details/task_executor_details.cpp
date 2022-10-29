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
 * \file object/details/task_executor_details.cpp
 * \brief CObjectTaskExecutorDetails - set of tweaks for TaskExecutor objects
 */

#include "level/parser/parser.h"

#include "object/details/macro.h"
#include "object/details/task_executor_details.h"

#include "object/hardcode/task_executor_hardcode.h"

void CObjectTaskExecutorDetails::ReadHardcode(ObjectType type)
{
    enabled         = CTaskExecutorHardcodeCollection::IsTaskExecutor(type);

    advance         = CTaskExecutorHardcodeCollection::GetUniversalTaskExecutionDetails(type);
    info            = CTaskExecutorHardcodeCollection::GetUniversalTaskExecutionDetails(type);
    pen             = CTaskExecutorHardcodeCollection::GetUniversalTaskExecutionDetails(type);
    turn            = CTaskExecutorHardcodeCollection::GetUniversalTaskExecutionDetails(type);
    wait            = CTaskExecutorHardcodeCollection::GetUniversalTaskExecutionDetails(type);

    aim             = CTaskExecutorHardcodeCollection::GetAimTaskExecutionDetails(type);
    
    build           = CTaskExecutorHardcodeCollection::GetBuildTaskExecutionDetails(type);
    build.objects   = CTaskExecutorHardcodeCollection::GetBuildTaskExecutionObjects(type);
    build.remove    = CTaskExecutorHardcodeCollection::GetBuildTaskExecutionRemove(type);

    deflag          = CTaskExecutorHardcodeCollection::GetDeflagTaskExecutionDetails(type);
    deflag.objects  = CTaskExecutorHardcodeCollection::GetDeflagTaskExecutionObjects(type);

    demark          = CTaskExecutorHardcodeCollection::GetDemarkTaskExecutionDetails(type);
    demark.objects  = CTaskExecutorHardcodeCollection::GetDemarkTaskExecutionObjects(type);

    explode         = CTaskExecutorHardcodeCollection::GetExplodeTaskExecutionDetails(type);

    fire            = CTaskExecutorHardcodeCollection::GetFireTaskExecutionDetails(type);

    fireant         = CTaskExecutorHardcodeCollection::GetFireAntTaskExecutionDetails(type);

    flag            = CTaskExecutorHardcodeCollection::GetFlagTaskExecutionDetails(type);
    flag.objects    = CTaskExecutorHardcodeCollection::GetFlagTaskExecutionObjects(type);

    recycle         = CTaskExecutorHardcodeCollection::GetRecycleTaskExecutionDetails(type);
    recycle.objects = CTaskExecutorHardcodeCollection::GetRecycleTaskExecutionObjects(type);

    shield          = CTaskExecutorHardcodeCollection::GetShieldTaskExecutionDetails(type);

    sniff           = CTaskExecutorHardcodeCollection::GetSniffTaskExecutionDetails(type);
    sniff.objects   = CTaskExecutorHardcodeCollection::GetSniffTaskExecutionObjects(type);

    take            = CTaskExecutorHardcodeCollection::GetTakeTaskExecutionDetails(type);

    manip           = CTaskExecutorHardcodeCollection::GetManipTaskExecutionDetails(type);

    thump           = CTaskExecutorHardcodeCollection::GetThumpTaskExecutionDetails(type);
    thump.objects   = CTaskExecutorHardcodeCollection::GetThumpTaskExecutionObjects(type);

    GOTO            = CTaskExecutorHardcodeCollection::GetGotoTaskExecutionDetails(type);
}

bool CObjectTaskExecutorDetails::Read(CLevelParserLine* line)
{
    READ_LINE( "SetObjectTaskExecutor" );
    READ_ARG( "enabled", AsBool, enabled );
    READ_END();

    READ_LINE( "SetObjectTaskAim" );
    READ_ARG( "enabled",    AsBool,              aim.enabled    );
    READ_ARG( "onWater",    AsBool,              aim.onWater    );
    READ_ARG( "onFlying",   AsBool,              aim.onFlying   );
    READ_ARG( "onMoving",   AsBool,              aim.onMoving   );
    READ_ARG( "onCarrying", AsBool,              aim.onCarrying );
    READ_ARG( "onCarried",  AsBool,              aim.onCarried  );
    READ_ARG( "partNum",    AsInt,               aim.partNum    );
    READ_ARG( "minY",       AsFloat,             aim.minY       );
    READ_ARG( "maxY",       AsFloat,             aim.maxY       );
    READ_ARG( "minZ",       AsFloat,             aim.minZ       );
    READ_ARG( "maxZ",       AsFloat,             aim.maxZ       );
    READ_END();

    READ_LINE( "SetObjectTaskAdvance" );
    READ_ARG( "enabled",    AsBool,              advance.enabled    );
    READ_ARG( "onWater",    AsBool,              advance.onWater    );
    READ_ARG( "onFlying",   AsBool,              advance.onFlying   );
    READ_ARG( "onMoving",   AsBool,              advance.onMoving   );
    READ_ARG( "onCarrying", AsBool,              advance.onCarrying );
    READ_ARG( "onCarried",  AsBool,              advance.onCarried  );
    READ_END();

    READ_LINE( "SetObjectTaskBuild" );
    READ_ARG( "enabled",        AsBool,              build.enabled        );
    READ_ARG( "onWater",        AsBool,              build.onWater        );
    READ_ARG( "onFlying",       AsBool,              build.onFlying       );
    READ_ARG( "onMoving",       AsBool,              build.onMoving       );
    READ_ARG( "onCarrying",     AsBool,              build.onCarrying     );
    READ_ARG( "onCarried",      AsBool,              build.onCarried      );
    READ_ARG( "exec",           AsTaskExecutionType, build.execution      );
    READ_ARG( "cancelOnMotion", AsBool,              build.cancelOnMotion );
    READ_ARG( "partNum",        AsInt,               build.partNum        );
    READ_ARG( "particlePos",    AsPoint,             build.particlePos    );
    READ_END();

    READ_LINE( "SetObjectTaskDeflag" );
    READ_ARG( "enabled",    AsBool,              deflag.enabled    );
    READ_ARG( "onWater",    AsBool,              deflag.onWater    );
    READ_ARG( "onFlying",   AsBool,              deflag.onFlying   );
    READ_ARG( "onMoving",   AsBool,              deflag.onMoving   );
    READ_ARG( "onCarrying", AsBool,              deflag.onCarrying );
    READ_ARG( "onCarried",  AsBool,              deflag.onCarried  );
    READ_ARG( "exec",       AsTaskExecutionType, deflag.execution  );
    READ_ARG( "partNum",    AsInt,               deflag.partNum    );
    READ_ARG( "position",   AsPoint,             deflag.position   );
    READ_ARG( "radius",     AsFloat,             deflag.radius     );
    READ_END();

    READ_LINE( "SetObjectTaskDemark" );
    READ_ARG( "enabled",    AsBool,              demark.enabled    );
    READ_ARG( "onWater",    AsBool,              demark.onWater    );
    READ_ARG( "onFlying",   AsBool,              demark.onFlying   );
    READ_ARG( "onMoving",   AsBool,              demark.onMoving   );
    READ_ARG( "onCarrying", AsBool,              demark.onCarrying );
    READ_ARG( "onCarried",  AsBool,              demark.onCarried  );
    READ_ARG( "radius",     AsFloat,             demark.radius     );
    READ_END();

    READ_LINE( "SetObjectTaskExplode" );
    READ_ARG( "enabled",    AsBool,              explode.enabled    );
    READ_ARG( "onWater",    AsBool,              explode.onWater    );
    READ_ARG( "onFlying",   AsBool,              explode.onFlying   );
    READ_ARG( "onMoving",   AsBool,              explode.onMoving   );
    READ_ARG( "onCarrying", AsBool,              explode.onCarrying );
    READ_ARG( "onCarried",  AsBool,              explode.onCarried  );
    READ_END();

    READ_LINE( "SetObjectTaskFire" );
    READ_ARG( "enabled",      AsBool,            fire.enabled      );
    READ_ARG( "onWater",      AsBool,            fire.onWater      );
    READ_ARG( "onFlying",     AsBool,            fire.onFlying     );
    READ_ARG( "onMoving",     AsBool,            fire.onMoving     );
    READ_ARG( "onCarrying",   AsBool,            fire.onCarrying   );
    READ_ARG( "onCarried",    AsBool,            fire.onCarried    );
    READ_ARG( "partNum",      AsInt,             fire.partNum      );
    READ_ARG( "position",     AsPoint,           fire.position     );
    READ_ARG( "fireType",     AsInt,             fire.fireType     );
    READ_ARG( "particle",     AsParticleType,    fire.particle     );
    READ_ARG( "duration",     AsFloat,           fire.duration     );
    READ_ARG( "energyPerSec", AsFloat,           fire.energyPerSec );
    READ_END();

    READ_LINE( "SetObjectTaskFireAnt" );
    READ_ARG( "enabled",    AsBool,              fireant.enabled    );
    READ_ARG( "onWater",    AsBool,              fireant.onWater    );
    READ_ARG( "onFlying",   AsBool,              fireant.onFlying   );
    READ_ARG( "onMoving",   AsBool,              fireant.onMoving   );
    READ_ARG( "onCarrying", AsBool,              fireant.onCarrying );
    READ_ARG( "onCarried",  AsBool,              fireant.onCarried  );
    READ_END();

    READ_LINE( "SetObjectTaskFlag" );
    READ_ARG( "enabled",    AsBool,              flag.enabled    );
    READ_ARG( "onWater",    AsBool,              flag.onWater    );
    READ_ARG( "onFlying",   AsBool,              flag.onFlying   );
    READ_ARG( "onMoving",   AsBool,              flag.onMoving   );
    READ_ARG( "onCarrying", AsBool,              flag.onCarrying );
    READ_ARG( "onCarried",  AsBool,              flag.onCarried  );
    READ_ARG( "exec",       AsTaskExecutionType, flag.execution  );
    READ_ARG( "partNum",    AsInt,               flag.partNum    );
    READ_ARG( "position",   AsPoint,             flag.position   );
    READ_END();

    READ_LINE( "SetObjectTaskInfo" );
    READ_ARG( "enabled",    AsBool,              info.enabled    );
    READ_ARG( "onWater",    AsBool,              info.onWater    );
    READ_ARG( "onFlying",   AsBool,              info.onFlying   );
    READ_ARG( "onMoving",   AsBool,              info.onMoving   );
    READ_ARG( "onCarrying", AsBool,              info.onCarrying );
    READ_ARG( "onCarried",  AsBool,              info.onCarried  );
    READ_END();

    READ_LINE( "SetObjectTaskPen" );
    READ_ARG( "enabled",    AsBool,              pen.enabled    );
    READ_ARG( "onWater",    AsBool,              pen.onWater    );
    READ_ARG( "onFlying",   AsBool,              pen.onFlying   );
    READ_ARG( "onMoving",   AsBool,              pen.onMoving   );
    READ_ARG( "onCarrying", AsBool,              pen.onCarrying );
    READ_ARG( "onCarried",  AsBool,              pen.onCarried  );
    READ_END();

    READ_LINE( "SetObjectTaskRecycle" );
    READ_ARG( "enabled",    AsBool,              recycle.enabled    );
    READ_ARG( "onWater",    AsBool,              recycle.onWater    );
    READ_ARG( "onFlying",   AsBool,              recycle.onFlying   );
    READ_ARG( "onMoving",   AsBool,              recycle.onMoving   );
    READ_ARG( "onCarrying", AsBool,              recycle.onCarrying );
    READ_ARG( "onCarried",  AsBool,              recycle.onCarried  );
    READ_ARG( "exec",       AsTaskExecutionType, recycle.execution  );
    READ_ARG( "partNum",    AsInt,               recycle.partNum    );
    READ_ARG( "position",   AsPoint,             recycle.position   );
    READ_ARG( "distance",   AsFloat,             recycle.distance   );
    READ_END();

    READ_LINE( "SetObjectTaskShield" );
    READ_ARG( "enabled",    AsBool,              shield.enabled    );
    READ_ARG( "onWater",    AsBool,              shield.onWater    );
    READ_ARG( "onFlying",   AsBool,              shield.onFlying   );
    READ_ARG( "onMoving",   AsBool,              shield.onMoving   );
    READ_ARG( "onCarrying", AsBool,              shield.onCarrying );
    READ_ARG( "onCarried",  AsBool,              shield.onCarried  );
    READ_END();

    READ_LINE( "SetObjectTaskSniff" );
    READ_ARG( "enabled",    AsBool,              sniff.enabled    );
    READ_ARG( "onWater",    AsBool,              sniff.onWater    );
    READ_ARG( "onFlying",   AsBool,              sniff.onFlying   );
    READ_ARG( "onMoving",   AsBool,              sniff.onMoving   );
    READ_ARG( "onCarrying", AsBool,              sniff.onCarrying );
    READ_ARG( "onCarried",  AsBool,              sniff.onCarried  );
    READ_ARG( "exec",       AsTaskExecutionType, sniff.execution  );
    READ_ARG( "partNum",    AsInt,               sniff.partNum    );
    READ_ARG( "position",   AsPoint,             sniff.position   );
    READ_END();

    READ_LINE( "SetObjectTaskManip" );
    READ_ARG( "enabled",    AsBool,              manip.enabled    );
    READ_ARG( "onWater",    AsBool,              manip.onWater    );
    READ_ARG( "onFlying",   AsBool,              manip.onFlying   );
    READ_ARG( "onMoving",   AsBool,              manip.onMoving   );
    READ_ARG( "onCarrying", AsBool,              manip.onCarrying );
    READ_ARG( "onCarried",  AsBool,              manip.onCarried  );
    READ_ARG( "exec",       AsTaskExecutionType, manip.execution  );
    READ_END();

    READ_LINE( "SetObjectTaskTake" );
    READ_ARG( "enabled",    AsBool,              take.enabled    );
    READ_ARG( "onWater",    AsBool,              take.onWater    );
    READ_ARG( "onFlying",   AsBool,              take.onFlying   );
    READ_ARG( "onMoving",   AsBool,              take.onMoving   );
    READ_ARG( "onCarrying", AsBool,              take.onCarrying );
    READ_ARG( "onCarried",  AsBool,              take.onCarried  );
    READ_END();

    READ_LINE( "SetObjectTaskThump" );
    READ_ARG( "enabled",    AsBool,              thump.enabled    );
    READ_ARG( "onWater",    AsBool,              thump.onWater    );
    READ_ARG( "onFlying",   AsBool,              thump.onFlying   );
    READ_ARG( "onMoving",   AsBool,              thump.onMoving   );
    READ_ARG( "onCarrying", AsBool,              thump.onCarrying );
    READ_ARG( "onCarried",  AsBool,              thump.onCarried  );
    READ_ARG( "exec",       AsTaskExecutionType, thump.execution  );
    READ_ARG( "partNum",    AsInt,               thump.partNum    );
    READ_ARG( "position",   AsPoint,             thump.position   );
    READ_ARG( "radius",     AsFloat,             thump.radius     );
    READ_END();

    READ_LINE( "SetObjectTaskTurn" );
    READ_ARG( "enabled",    AsBool,              turn.enabled    );
    READ_ARG( "onWater",    AsBool,              turn.onWater    );
    READ_ARG( "onFlying",   AsBool,              turn.onFlying   );
    READ_ARG( "onMoving",   AsBool,              turn.onMoving   );
    READ_ARG( "onCarrying", AsBool,              turn.onCarrying );
    READ_ARG( "onCarried",  AsBool,              turn.onCarried  );
    READ_END();

    READ_LINE( "SetObjectTaskWait" );
    READ_ARG( "enabled",    AsBool,              wait.enabled    );
    READ_ARG( "onWater",    AsBool,              wait.onWater    );
    READ_ARG( "onFlying",   AsBool,              wait.onFlying   );
    READ_ARG( "onMoving",   AsBool,              wait.onMoving   );
    READ_ARG( "onCarrying", AsBool,              wait.onCarrying );
    READ_ARG( "onCarried",  AsBool,              wait.onCarried  );
    READ_END();

    READ_LINE( "SetObjectTaskGoto" );
    READ_ARG( "enabled",      AsBool,            GOTO.enabled      );
    READ_ARG( "onWater",      AsBool,            GOTO.onWater      );
    READ_ARG( "onFlying",     AsBool,            GOTO.onFlying     );
    READ_ARG( "onMoving",     AsBool,            GOTO.onMoving     );
    READ_ARG( "onCarrying",   AsBool,            GOTO.onCarrying   );
    READ_ARG( "onCarried",    AsBool,            GOTO.onCarried    );
    READ_ARG( "acceptWater",  AsBool,            GOTO.acceptWater  );
    READ_ARG( "acceptFlying", AsBool,            GOTO.acceptFlying );
    READ_ARG( "angleLimit",   AsFloat,           GOTO.angleLimit   );
    READ_ARG( "approximate",  AsBool,            GOTO.approximate  );
    READ_ARG( "defaultGoal",  AsInt,             GOTO.defaultGoal  );
    READ_ARG( "defaultCrash", AsInt,             GOTO.defaultCrash );
    READ_END();

    READ_LINE( "SetObjectTaskGotoRepulse" );
    READ_ARG( "enabled",     AsBool,             GOTO.repulseEnabled );
    READ_ARG( "custom",      AsBool,             GOTO.repulseCustom  );
    READ_ARG( "onLand",      AsFloat,            GOTO.repulseLand    );
    READ_ARG( "onOther",     AsFloat,            GOTO.repulseNoLand  );
    READ_ARG( "factor",      AsFloat,            GOTO.repulseFactor  );
    READ_END();

    READ_IT_LINE( "AddObjectTaskBuild", "UpdObjectTaskBuild", "ClrObjectTaskBuild", build.objects );
    READ_IT_ARG( "input",      AsObjectType, input      );
    READ_IT_ARG( "output",     AsObjectType, output     );
    READ_IT_ARG( "message",    AsString,     message    );
    READ_IT_ARG( "reqRadius",  AsFloat,      reqRadius  );
    READ_IT_ARG( "needRecede", AsBool,       needRecede );
    READ_IT_END();

    READ_IT_LINE( "AddObjectTaskBuildRemove", "UpdObjectTaskBuildRemove", "ClrObjectTaskBuildRemove", build.remove );
    READ_IT_ARG( "input",      AsObjectType, input      );
    READ_IT_END();

    READ_IT_LINE( "AddObjectTaskDeflag", "UpdObjectTaskDeflag", "ClrObjectTaskDeflag", deflag.objects );
    READ_IT_ARG( "input",   AsObjectType, input   );
    READ_IT_ARG( "output",  AsObjectType, output  );
    READ_IT_ARG( "message", AsString,     message );
    READ_IT_ARG( "effect",  AsPyroType,   effect  );
    READ_IT_END();

    READ_IT_LINE( "AddObjectTaskFlag", "UpdObjectTaskFlag", "ClrObjectTaskFlag", flag.objects );
    READ_IT_ARG( "output",   AsObjectType, output   );
    READ_IT_ARG( "message",  AsString,     message  );
    READ_IT_ARG( "maxCount", AsInt,        maxCount );
    READ_IT_END();    

    READ_IT_LINE( "AddObjectTaskRecycle", "UpdObjectTaskRecycle", "ClrObjectTaskRecycle", recycle.objects );
    READ_IT_ARG( "input",   AsObjectType, input   );
    READ_IT_ARG( "output",  AsObjectType, output  );
    READ_IT_ARG( "message", AsString,     message );
    READ_IT_END();

    READ_IT_LINE( "AddObjectTaskDemark", "UpdObjectTaskDemark", "ClrObjectTaskDemark", demark.objects );
    READ_IT_ARG( "input",   AsObjectType,  input  );
    READ_IT_END();

    READ_IT_LINE( "AddObjectTaskSniff", "UpdObjectTaskSniff", "ClrObjectTaskSniff", sniff.objects );
    READ_IT_ARG( "soil",    AsTerrainRes, soil    );
    READ_IT_ARG( "output",  AsObjectType, output  );
    READ_IT_ARG( "message", AsString,     message );
    READ_IT_END();

    READ_IT_LINE( "AddObjectTaskThump", "UpdObjectTaskThump", "ClrObjectTaskThump", thump.objects );
    READ_IT_ARG( "target",  AsObjectType, target );
    READ_IT_ARG( "action",  AsInt,        action );
    READ_IT_END();

    return false;
}

void CObjectTaskExecutorDetails::Write(CLevelParser* parser, ObjectType type)
{
    WRITE_LINE( "SetObjectTaskExecutor" );
    WRITE_ARG( "enabled", AsBool, enabled );
    WRITE_END();

    WRITE_LINE( "SetObjectTaskAim" );
    WRITE_ARG( "enabled",    AsBool,              aim.enabled    );
    WRITE_ARG( "onWater",    AsBool,              aim.onWater    );
    WRITE_ARG( "onFlying",   AsBool,              aim.onFlying   );
    WRITE_ARG( "onMoving",   AsBool,              aim.onMoving   );
    WRITE_ARG( "onCarrying", AsBool,              aim.onCarrying );
    WRITE_ARG( "onCarried",  AsBool,              aim.onCarried  );
    WRITE_ARG( "partNum",    AsInt,               aim.partNum    );
    WRITE_ARG( "minY",       AsFloat,             aim.minY       );
    WRITE_ARG( "maxY",       AsFloat,             aim.maxY       );
    WRITE_ARG( "minZ",       AsFloat,             aim.minZ       );
    WRITE_ARG( "maxZ",       AsFloat,             aim.maxZ       );
    WRITE_END();

    WRITE_LINE( "SetObjectTaskAdvance" );
    WRITE_ARG( "enabled",    AsBool,              advance.enabled    );
    WRITE_ARG( "onWater",    AsBool,              advance.onWater    );
    WRITE_ARG( "onFlying",   AsBool,              advance.onFlying   );
    WRITE_ARG( "onMoving",   AsBool,              advance.onMoving   );
    WRITE_ARG( "onCarrying", AsBool,              advance.onCarrying );
    WRITE_ARG( "onCarried",  AsBool,              advance.onCarried  );
    WRITE_END();

    WRITE_LINE( "SetObjectTaskBuild" );
    WRITE_ARG( "enabled",        AsBool,              build.enabled        );
    WRITE_ARG( "onWater",        AsBool,              build.onWater        );
    WRITE_ARG( "onFlying",       AsBool,              build.onFlying       );
    WRITE_ARG( "onMoving",       AsBool,              build.onMoving       );
    WRITE_ARG( "onCarrying",     AsBool,              build.onCarrying     );
    WRITE_ARG( "onCarried",      AsBool,              build.onCarried      );
    WRITE_ARG( "exec",           AsTaskExecutionType, build.execution      );
    WRITE_ARG( "cancelOnMotion", AsBool,              build.cancelOnMotion );
    WRITE_ARG( "partNum",        AsInt,               build.partNum        );
    WRITE_ARG( "particlePos",    AsPoint,             build.particlePos    );
    WRITE_END();

    WRITE_LINE( "SetObjectTaskDeflag" );
    WRITE_ARG( "enabled",    AsBool,              deflag.enabled    );
    WRITE_ARG( "onWater",    AsBool,              deflag.onWater    );
    WRITE_ARG( "onFlying",   AsBool,              deflag.onFlying   );
    WRITE_ARG( "onMoving",   AsBool,              deflag.onMoving   );
    WRITE_ARG( "onCarrying", AsBool,              deflag.onCarrying );
    WRITE_ARG( "onCarried",  AsBool,              deflag.onCarried  );
    WRITE_ARG( "exec",       AsTaskExecutionType, deflag.execution  );
    WRITE_ARG( "partNum",    AsInt,               deflag.partNum    );
    WRITE_ARG( "position",   AsPoint,             deflag.position   );
    WRITE_ARG( "radius",     AsFloat,             deflag.radius     );
    WRITE_END();

    WRITE_LINE( "SetObjectTaskDemark" );
    WRITE_ARG( "enabled",    AsBool,              demark.enabled    );
    WRITE_ARG( "onWater",    AsBool,              demark.onWater    );
    WRITE_ARG( "onFlying",   AsBool,              demark.onFlying   );
    WRITE_ARG( "onMoving",   AsBool,              demark.onMoving   );
    WRITE_ARG( "onCarrying", AsBool,              demark.onCarrying );
    WRITE_ARG( "onCarried",  AsBool,              demark.onCarried  );
    WRITE_ARG( "radius",     AsFloat,             demark.radius     );
    WRITE_END();

    WRITE_LINE( "SetObjectTaskExplode" );
    WRITE_ARG( "enabled",    AsBool,              explode.enabled    );
    WRITE_ARG( "onWater",    AsBool,              explode.onWater    );
    WRITE_ARG( "onFlying",   AsBool,              explode.onFlying   );
    WRITE_ARG( "onMoving",   AsBool,              explode.onMoving   );
    WRITE_ARG( "onCarrying", AsBool,              explode.onCarrying );
    WRITE_ARG( "onCarried",  AsBool,              explode.onCarried  );
    WRITE_END();

    WRITE_LINE( "SetObjectTaskFire" );
    WRITE_ARG( "enabled",      AsBool,            fire.enabled      );
    WRITE_ARG( "onWater",      AsBool,            fire.onWater      );
    WRITE_ARG( "onFlying",     AsBool,            fire.onFlying     );
    WRITE_ARG( "onMoving",     AsBool,            fire.onMoving     );
    WRITE_ARG( "onCarrying",   AsBool,            fire.onCarrying   );
    WRITE_ARG( "onCarried",    AsBool,            fire.onCarried    );
    WRITE_ARG( "partNum",      AsInt,             fire.partNum      );
    WRITE_ARG( "position",     AsPoint,           fire.position     );
    WRITE_ARG( "fireType",     AsInt,             fire.fireType     );
    WRITE_ARG( "particle",     AsParticleType,    fire.particle     );
    WRITE_ARG( "duration",     AsFloat,           fire.duration     );
    WRITE_ARG( "energyPerSec", AsFloat,           fire.energyPerSec );
    WRITE_END();

    WRITE_LINE( "SetObjectTaskFireAnt" );
    WRITE_ARG( "enabled",    AsBool,              fireant.enabled    );
    WRITE_ARG( "onWater",    AsBool,              fireant.onWater    );
    WRITE_ARG( "onFlying",   AsBool,              fireant.onFlying   );
    WRITE_ARG( "onMoving",   AsBool,              fireant.onMoving   );
    WRITE_ARG( "onCarrying", AsBool,              fireant.onCarrying );
    WRITE_ARG( "onCarried",  AsBool,              fireant.onCarried  );
    WRITE_END();

    WRITE_LINE( "SetObjectTaskFlag" );
    WRITE_ARG( "enabled",    AsBool,              flag.enabled    );
    WRITE_ARG( "onWater",    AsBool,              flag.onWater    );
    WRITE_ARG( "onFlying",   AsBool,              flag.onFlying   );
    WRITE_ARG( "onMoving",   AsBool,              flag.onMoving   );
    WRITE_ARG( "onCarrying", AsBool,              flag.onCarrying );
    WRITE_ARG( "onCarried",  AsBool,              flag.onCarried  );
    WRITE_ARG( "exec",       AsTaskExecutionType, flag.execution  );
    WRITE_ARG( "partNum",    AsInt,               flag.partNum    );
    WRITE_ARG( "position",   AsPoint,             flag.position   );
    WRITE_END();

    WRITE_LINE( "SetObjectTaskInfo" );
    WRITE_ARG( "enabled",    AsBool,              info.enabled    );
    WRITE_ARG( "onWater",    AsBool,              info.onWater    );
    WRITE_ARG( "onFlying",   AsBool,              info.onFlying   );
    WRITE_ARG( "onMoving",   AsBool,              info.onMoving   );
    WRITE_ARG( "onCarrying", AsBool,              info.onCarrying );
    WRITE_ARG( "onCarried",  AsBool,              info.onCarried  );
    WRITE_END();

    WRITE_LINE( "SetObjectTaskPen" );
    WRITE_ARG( "enabled",    AsBool,              pen.enabled    );
    WRITE_ARG( "onWater",    AsBool,              pen.onWater    );
    WRITE_ARG( "onFlying",   AsBool,              pen.onFlying   );
    WRITE_ARG( "onMoving",   AsBool,              pen.onMoving   );
    WRITE_ARG( "onCarrying", AsBool,              pen.onCarrying );
    WRITE_ARG( "onCarried",  AsBool,              pen.onCarried  );
    WRITE_END();

    WRITE_LINE( "SetObjectTaskRecycle" );
    WRITE_ARG( "enabled",    AsBool,              recycle.enabled    );
    WRITE_ARG( "onWater",    AsBool,              recycle.onWater    );
    WRITE_ARG( "onFlying",   AsBool,              recycle.onFlying   );
    WRITE_ARG( "onMoving",   AsBool,              recycle.onMoving   );
    WRITE_ARG( "onCarrying", AsBool,              recycle.onCarrying );
    WRITE_ARG( "onCarried",  AsBool,              recycle.onCarried  );
    WRITE_ARG( "exec",       AsTaskExecutionType, recycle.execution  );
    WRITE_ARG( "partNum",    AsInt,               recycle.partNum    );
    WRITE_ARG( "position",   AsPoint,             recycle.position   );
    WRITE_ARG( "distance",   AsFloat,             recycle.distance   );
    WRITE_END();

    WRITE_LINE( "SetObjectTaskShield" );
    WRITE_ARG( "enabled",    AsBool,              shield.enabled    );
    WRITE_ARG( "onWater",    AsBool,              shield.onWater    );
    WRITE_ARG( "onFlying",   AsBool,              shield.onFlying   );
    WRITE_ARG( "onMoving",   AsBool,              shield.onMoving   );
    WRITE_ARG( "onCarrying", AsBool,              shield.onCarrying );
    WRITE_ARG( "onCarried",  AsBool,              shield.onCarried  );
    WRITE_END();

    WRITE_LINE( "SetObjectTaskSniff" );
    WRITE_ARG( "enabled",    AsBool,              sniff.enabled    );
    WRITE_ARG( "onWater",    AsBool,              sniff.onWater    );
    WRITE_ARG( "onFlying",   AsBool,              sniff.onFlying   );
    WRITE_ARG( "onMoving",   AsBool,              sniff.onMoving   );
    WRITE_ARG( "onCarrying", AsBool,              sniff.onCarrying );
    WRITE_ARG( "onCarried",  AsBool,              sniff.onCarried  );
    WRITE_ARG( "exec",       AsTaskExecutionType, sniff.execution  );
    WRITE_ARG( "partNum",    AsInt,               sniff.partNum    );
    WRITE_ARG( "position",   AsPoint,             sniff.position   );
    WRITE_END();

    WRITE_LINE( "SetObjectTaskManip" );
    WRITE_ARG( "enabled",    AsBool,              manip.enabled    );
    WRITE_ARG( "onWater",    AsBool,              manip.onWater    );
    WRITE_ARG( "onFlying",   AsBool,              manip.onFlying   );
    WRITE_ARG( "onMoving",   AsBool,              manip.onMoving   );
    WRITE_ARG( "onCarrying", AsBool,              manip.onCarrying );
    WRITE_ARG( "onCarried",  AsBool,              manip.onCarried  );
    WRITE_ARG( "exec",       AsTaskExecutionType, manip.execution  );
    WRITE_END();

    WRITE_LINE( "SetObjectTaskTake" );
    WRITE_ARG( "enabled",    AsBool,              take.enabled    );
    WRITE_ARG( "onWater",    AsBool,              take.onWater    );
    WRITE_ARG( "onFlying",   AsBool,              take.onFlying   );
    WRITE_ARG( "onMoving",   AsBool,              take.onMoving   );
    WRITE_ARG( "onCarrying", AsBool,              take.onCarrying );
    WRITE_ARG( "onCarried",  AsBool,              take.onCarried  );
    WRITE_END();

    WRITE_LINE( "SetObjectTaskThump" );
    WRITE_ARG( "enabled",    AsBool,              thump.enabled    );
    WRITE_ARG( "onWater",    AsBool,              thump.onWater    );
    WRITE_ARG( "onFlying",   AsBool,              thump.onFlying   );
    WRITE_ARG( "onMoving",   AsBool,              thump.onMoving   );
    WRITE_ARG( "onCarrying", AsBool,              thump.onCarrying );
    WRITE_ARG( "onCarried",  AsBool,              thump.onCarried  );
    WRITE_ARG( "exec",       AsTaskExecutionType, thump.execution  );
    WRITE_ARG( "partNum",    AsInt,               thump.partNum    );
    WRITE_ARG( "position",   AsPoint,             thump.position   );
    WRITE_ARG( "radius",     AsFloat,             thump.radius     );
    WRITE_END();

    WRITE_LINE( "SetObjectTaskTurn" );
    WRITE_ARG( "enabled",    AsBool,              turn.enabled    );
    WRITE_ARG( "onWater",    AsBool,              turn.onWater    );
    WRITE_ARG( "onFlying",   AsBool,              turn.onFlying   );
    WRITE_ARG( "onMoving",   AsBool,              turn.onMoving   );
    WRITE_ARG( "onCarrying", AsBool,              turn.onCarrying );
    WRITE_ARG( "onCarried",  AsBool,              turn.onCarried  );
    WRITE_END();

    WRITE_LINE( "SetObjectTaskWait" );
    WRITE_ARG( "enabled",    AsBool,              wait.enabled    );
    WRITE_ARG( "onWater",    AsBool,              wait.onWater    );
    WRITE_ARG( "onFlying",   AsBool,              wait.onFlying   );
    WRITE_ARG( "onMoving",   AsBool,              wait.onMoving   );
    WRITE_ARG( "onCarrying", AsBool,              wait.onCarrying );
    WRITE_ARG( "onCarried",  AsBool,              wait.onCarried  );
    WRITE_END();

    WRITE_LINE( "SetObjectTaskGoto" );
    WRITE_ARG( "enabled",      AsBool,            GOTO.enabled      );
    WRITE_ARG( "onWater",      AsBool,            GOTO.onWater      );
    WRITE_ARG( "onFlying",     AsBool,            GOTO.onFlying     );
    WRITE_ARG( "onMoving",     AsBool,            GOTO.onMoving     );
    WRITE_ARG( "onCarrying",   AsBool,            GOTO.onCarrying   );
    WRITE_ARG( "onCarried",    AsBool,            GOTO.onCarried    );
    WRITE_ARG( "acceptWater",  AsBool,            GOTO.acceptWater  );
    WRITE_ARG( "acceptFlying", AsBool,            GOTO.acceptFlying );
    WRITE_ARG( "angleLimit",   AsFloat,           GOTO.angleLimit   );
    WRITE_ARG( "approximate",  AsBool,            GOTO.approximate  );
    WRITE_ARG( "defaultGoal",  AsInt,             GOTO.defaultGoal  );
    WRITE_ARG( "defaultCrash", AsInt,             GOTO.defaultCrash );
    WRITE_END();

    WRITE_LINE( "SetObjectTaskGotoRepulse" );
    WRITE_ARG( "enabled",     AsBool,             GOTO.repulseEnabled );
    WRITE_ARG( "custom",      AsBool,             GOTO.repulseCustom  );
    WRITE_ARG( "onLand",      AsFloat,            GOTO.repulseLand    );
    WRITE_ARG( "onOther",     AsFloat,            GOTO.repulseNoLand  );
    WRITE_ARG( "factor",      AsFloat,            GOTO.repulseFactor  );
    WRITE_END();

    WRITE_IT_LINE( "AddObjectTaskBuild", build.objects );
    WRITE_IT_ARG( "input",      AsObjectType, input      );
    WRITE_IT_ARG( "output",     AsObjectType, output     );
    WRITE_IT_ARG( "message",    AsString,     message    );
    WRITE_IT_ARG( "reqRadius",  AsFloat,      reqRadius  );
    WRITE_IT_ARG( "needRecede", AsBool,       needRecede );
    WRITE_IT_END();

    WRITE_IT_LINE( "AddObjectTaskBuildRemove", build.remove );
    WRITE_IT_ARG( "input",      AsObjectType, input      );
    WRITE_IT_END();

    WRITE_IT_LINE( "AddObjectTaskDeflag", deflag.objects );
    WRITE_IT_ARG( "input",   AsObjectType, input   );
    WRITE_IT_ARG( "output",  AsObjectType, output  );
    WRITE_IT_ARG( "message", AsString,     message );
    WRITE_IT_ARG( "effect",  AsPyroType,   effect  );
    WRITE_IT_END();

    WRITE_IT_LINE( "AddObjectTaskFlag", flag.objects );
    WRITE_IT_ARG( "output",   AsObjectType, output   );
    WRITE_IT_ARG( "message",  AsString,     message  );
    WRITE_IT_ARG( "maxCount", AsInt,        maxCount );
    WRITE_IT_END();    

    WRITE_IT_LINE( "AddObjectTaskRecycle", recycle.objects );
    WRITE_IT_ARG( "input",   AsObjectType, input   );
    WRITE_IT_ARG( "output",  AsObjectType, output  );
    WRITE_IT_ARG( "message", AsString,     message );
    WRITE_IT_END();

    WRITE_IT_LINE( "AddObjectTaskDemark", demark.objects );
    WRITE_IT_ARG( "input",   AsObjectType,  input  );
    WRITE_IT_END();

    WRITE_IT_LINE( "AddObjectTaskSniff", sniff.objects );
    WRITE_IT_ARG( "soil",    AsTerrainRes, soil    );
    WRITE_IT_ARG( "output",  AsObjectType, output  );
    WRITE_IT_ARG( "message", AsString,     message );
    WRITE_IT_END();

    WRITE_IT_LINE( "AddObjectTaskThump", thump.objects );
    WRITE_IT_ARG( "target",  AsObjectType, target );
    WRITE_IT_ARG( "action",  AsInt,        action );
    WRITE_IT_END();

}
