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
    
    flag          = hardcode.GetFlagTaskExecutionDetails(type);
    flag.objects  = hardcode.GetFlagTaskExecutionObjects(type);

    sniff         = hardcode.GetSniffTaskExecutionDetails(type);
    sniff.objects = hardcode.GetSniffTaskExecutionObjects(type);
}

bool CObjectTaskExecutorDetails::Read(CLevelParserLine* line)
{
    READ_LINE( "SetObjectTaskExecutor" );
    READ_ARG( "enabled", AsBool,              enabled        );
    READ_ARG( "tool",    AsToolType,          tool           );
    READ_END();

    READ_LINE( "SetObjectTaskFlag" );
    READ_ARG( "exec",    AsTaskExecutionType, flag.execution );
    READ_ARG( "partNum", AsInt,               flag.partNum   );
    READ_ARG( "pos",     AsPoint,             flag.pos       );
    READ_END();

    READ_LINE( "SetObjectTaskSniff" );
    READ_ARG( "exec",    AsTaskExecutionType, sniff.execution );
    READ_ARG( "partNum", AsInt,               sniff.partNum   );
    READ_ARG( "pos",     AsPoint,             sniff.pos       );
    READ_END();

    READ_LINE( "AddObjectTaskFlagObject" );
    READ_NEW( id,                       flag.objects );
    READ_ARG( "output",   AsObjectType, flag.objects[id].output   );
    READ_ARG( "maxCount", AsInt,        flag.objects[id].maxCount );
    READ_END();    

    READ_LINE( "AddObjectTaskSniffObject" );
    READ_NEW( id,                      sniff.objects             );
    READ_ARG( "soil",    AsTerrainRes, sniff.objects[id].soil    );
    READ_ARG( "output",  AsObjectType, sniff.objects[id].output  );
    READ_ARG( "message", AsString,     sniff.objects[id].message );
    READ_END();

    return false;
}

void CObjectTaskExecutorDetails::Write(CLevelParser* parser, ObjectType type)
{
    CObjectTaskExecutorDetails def;

    WRITE_LINE( "SetObjectTaskExecutor" );
    WRITE_ARG( "enabled", def, enabled        );
    WRITE_ARG( "tool",    def, tool           );
    WRITE_END();

    WRITE_LINE( "SetObjectTaskFlag" );
    WRITE_ARG( "exec",    def, flag.execution );
    WRITE_ARG( "partNum", def, flag.partNum   );
    WRITE_ARG( "pos",     def, flag.pos       );
    WRITE_END();

    WRITE_LINE( "SetObjectTaskSniff" );
    WRITE_ARG( "exec",    def, sniff.execution );
    WRITE_ARG( "partNum", def, sniff.partNum   );
    WRITE_ARG( "pos",     def, sniff.pos       );
    WRITE_END();

    CObjectFlagTaskExecutorObject defF;
    for ( auto it : flag.objects )
    {
        WRITE_LINE( "AddObjectTaskFlagObject" );
        WRITE_IT( "output",   defF, output   );
        WRITE_IT( "maxCount", defF, maxCount );
        WRITE_END();    
    }

    CObjectSniffTaskExecutorObject defS;
    for ( auto it : sniff.objects )
    {
        WRITE_LINE( "AddObjectTaskSniffObject" );
        WRITE_IT( "soil",    defS, soil    );
        WRITE_IT( "output",  defS, output  );
        WRITE_IT( "message", defS, message );
        WRITE_END();    
    }
}

CObjectTaskExecutorDetails GetObjectTaskExecutorDetails(CObject* obj)
{
    return CObjectDetails::GetInstance().GetObjectDetails(obj).task_executor;
}

CObjectTaskExecutorDetails GetObjectTaskExecutorDetails(ObjectType type)
{
    return CObjectDetails::GetInstance().GetObjectDetails(type).task_executor;
}
