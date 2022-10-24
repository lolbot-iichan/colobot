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

#include "object/details/details_provider.h"
#include "object/details/hardcode.h"
#include "object/details/macro.h"
#include "object/details/task_executor_details.h"

void CObjectTaskExecutorDetails::ReadHardcode(ObjectType type)
{
    CHardcodeCollection hardcode;

    enabled = hardcode.IsTaskExecutor(type);
    tool = hardcode.GetToolType(type);
    
    aim           = hardcode.GetAimTaskExecutionDetails(type);

    build         = hardcode.GetBuildTaskExecutionDetails(type);
    build.objects = hardcode.GetBuilderMenuButtons(type);

    deflag        = hardcode.GetDeflagTaskExecutionDetails(type);
    deflag.objects= hardcode.GetDeflagTaskExecutionObjects(type);

    flag          = hardcode.GetFlagTaskExecutionDetails(type);
    flag.objects  = hardcode.GetFlagTaskExecutionObjects(type);

    sniff         = hardcode.GetSniffTaskExecutionDetails(type);
    sniff.objects = hardcode.GetSniffTaskExecutionObjects(type);

//TODO    recycle         = hardcode.GetRecycleTaskExecutionDetails(type);
    recycle.objects = hardcode.GetRecycleTaskExecutionObjects(type);

}

bool CObjectTaskExecutorDetails::Read(CLevelParserLine* line)
{
    READ_LINE( "SetObjectTaskExecutor" );
    READ_ARG( "enabled", AsBool,              enabled        );
    READ_ARG( "tool",    AsToolType,          tool           );
    READ_END();

    READ_LINE( "SetObjectTaskAim" );
    READ_ARG( "partNum", AsInt,   aim.partNum );
    READ_ARG( "minY",    AsFloat, aim.minY    );
    READ_ARG( "maxY",    AsFloat, aim.maxY    );
    READ_ARG( "minZ",    AsFloat, aim.minZ    );
    READ_ARG( "maxZ",    AsFloat, aim.maxZ    );
    READ_END();

    READ_LINE( "SetObjectTaskBuild" );
    READ_ARG( "enabled",    AsBool,              build.enabled    );
    READ_ARG( "onWater",    AsBool,              build.onWater    );
    READ_ARG( "onFlying",   AsBool,              build.onFlying   );
    READ_ARG( "onMoving",   AsBool,              build.onMoving   );
    READ_ARG( "onCarrying", AsBool,              build.onCarrying );
    READ_ARG( "onCarried",  AsBool,              build.onCarried  );
    READ_ARG( "exec",       AsTaskExecutionType, build.execution  );
    READ_ARG( "partNum",    AsInt,               build.partNum    );
    READ_ARG( "position",   AsPoint,             build.position   );
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

    READ_IT_LINE( "AddObjectTaskBuildObject", "UpdObjectTaskBuildObject", "ClrObjectTaskBuildObject", build.objects );
    READ_IT_ARG( "input",   AsObjectType, input   );
    READ_IT_ARG( "output",  AsObjectType, output  );
    READ_IT_ARG( "message", AsString,     message );
    READ_IT_ARG( "icon",    AsInt,        icon    );
    READ_IT_ARG( "text",    AsString,     text    );
    READ_IT_END();

    READ_IT_LINE( "AddObjectTaskDeflagObject", "UpdObjectTaskDeflagObject", "ClrObjectTaskDeflagObject", deflag.objects );
    READ_IT_ARG( "input",   AsObjectType, input   );
    READ_IT_ARG( "output",  AsObjectType, output  );
    READ_IT_ARG( "message", AsString,     message );
    READ_IT_ARG( "effect",  AsPyroType,   effect  );
    READ_IT_END();

    READ_IT_LINE( "AddObjectTaskFlagObject", "UpdObjectTaskFlagObject", "ClrObjectTaskFlagObject", flag.objects );
    READ_IT_ARG( "output",   AsObjectType, output   );
    READ_IT_ARG( "message",  AsString,     message  );
    READ_IT_ARG( "maxCount", AsInt,        maxCount );
    READ_IT_END();    

    READ_IT_LINE( "AddObjectTaskSniffObject", "UpdObjectTaskSniffObject", "ClrObjectTaskSniffObject", sniff.objects );
    READ_IT_ARG( "soil",    AsTerrainRes, soil    );
    READ_IT_ARG( "output",  AsObjectType, output  );
    READ_IT_ARG( "message", AsString,     message );
    READ_IT_END();

    READ_IT_LINE( "AddObjectTaskRecycleObject", "UpdObjectTaskRecycleObject", "ClrObjectTaskRecycleObject", recycle.objects );
    READ_IT_ARG( "input",   AsObjectType, input   );
    READ_IT_ARG( "output",  AsObjectType, output  );
    READ_IT_ARG( "message", AsString,     message );
    READ_IT_END();

    return false;
}

void CObjectTaskExecutorDetails::Write(CLevelParser* parser, ObjectType type)
{
    WRITE_LINE( "SetObjectTaskExecutor" );
    WRITE_ARG( "enabled", AsBool,              enabled        );
    WRITE_ARG( "tool",    AsToolType,          tool           );
    WRITE_END();

    WRITE_LINE( "SetObjectTaskAim" );
    WRITE_ARG( "partNum", AsInt,   aim.partNum );
    WRITE_ARG( "minY",    AsFloat, aim.minY    );
    WRITE_ARG( "maxY",    AsFloat, aim.maxY    );
    WRITE_ARG( "minZ",    AsFloat, aim.minZ    );
    WRITE_ARG( "maxZ",    AsFloat, aim.maxZ    );
    WRITE_END();

    WRITE_LINE( "SetObjectTaskBuild" );
    WRITE_ARG( "enabled",    AsBool,              build.enabled    );
    WRITE_ARG( "onWater",    AsBool,              build.onWater    );
    WRITE_ARG( "onFlying",   AsBool,              build.onFlying   );
    WRITE_ARG( "onMoving",   AsBool,              build.onMoving   );
    WRITE_ARG( "onCarrying", AsBool,              build.onCarrying );
    WRITE_ARG( "onCarried",  AsBool,              build.onCarried  );
    WRITE_ARG( "exec",       AsTaskExecutionType, build.execution  );
    WRITE_ARG( "partNum",    AsInt,               build.partNum    );
    WRITE_ARG( "position",   AsPoint,             build.position   );
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

    WRITE_IT_LINE( "AddObjectTaskBuildObject", build.objects );
    WRITE_IT_ARG( "input",   AsObjectType, input   );
    WRITE_IT_ARG( "output",  AsObjectType, output  );
    WRITE_IT_ARG( "message", AsString,     message );
    WRITE_IT_ARG( "icon",    AsInt,        icon    );
    WRITE_IT_ARG( "text",    AsString,     text    );
    WRITE_IT_END();

    WRITE_IT_LINE( "AddObjectTaskDeflagObject", deflag.objects );
    WRITE_IT_ARG( "input",   AsObjectType, input   );
    WRITE_IT_ARG( "output",  AsObjectType, output  );
    WRITE_IT_ARG( "message", AsString,     message );
    WRITE_IT_ARG( "effect",  AsPyroType,   effect  );
    WRITE_IT_END();

    WRITE_IT_LINE( "AddObjectTaskFlagObject", flag.objects );
    WRITE_IT_ARG( "output",   AsObjectType, output   );
    WRITE_IT_ARG( "message",  AsString,     message  );
    WRITE_IT_ARG( "maxCount", AsInt,        maxCount );
    WRITE_IT_END();    

    WRITE_IT_LINE( "AddObjectTaskSniffObject", sniff.objects );
    WRITE_IT_ARG( "soil",    AsTerrainRes, soil    );
    WRITE_IT_ARG( "output",  AsObjectType, output  );
    WRITE_IT_ARG( "message", AsString,     message );
    WRITE_IT_END();

    WRITE_IT_LINE( "AddObjectTaskRecycleObject", recycle.objects );
    WRITE_IT_ARG( "input",   AsObjectType, input   );
    WRITE_IT_ARG( "output",  AsObjectType, output  );
    WRITE_IT_ARG( "message", AsString,     message );
    WRITE_IT_END();
}

CObjectTaskExecutorDetails GetObjectTaskExecutorDetails(CObject* obj)
{
    return CObjectDetails::GetInstance().GetObjectDetails(obj).task_executor;
}

CObjectTaskExecutorDetails GetObjectTaskExecutorDetails(ObjectType type)
{
    return CObjectDetails::GetInstance().GetObjectDetails(type).task_executor;
}
