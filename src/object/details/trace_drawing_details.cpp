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
 * \file object/details/trace_drawing_details.cpp
 * \brief CObjectTraceDrawingDetails - set of tweaks for TraceDrawing objects
 */

#include "level/parser/parser.h"

#include "object/details/macro.h"
#include "object/details/trace_drawing_details.h"

#include "object/hardcode/trace_drawing_hardcode.h"

void CObjectTraceDrawingDetails::ReadHardcode(ObjectType type)
{
    enabled     = CTraceDrawingHardcodeCollection::IsTraceDrawing(type);
    penAnimated = CTraceDrawingHardcodeCollection::IsTraceDrawingAnimated(type);
}

bool CObjectTraceDrawingDetails::Read(CLevelParserLine* line)
{
    READ_LINE( "SetObjectTraceDrawing" );
    READ_ARG( "enabled",     AsBool, enabled );
    READ_ARG( "penAnimated", AsBool, enabled );
    READ_END();

    return false;
}

void CObjectTraceDrawingDetails::Write(CLevelParser* parser, ObjectType type)
{
    WRITE_LINE( "SetObjectTraceDrawing" );
    WRITE_ARG( "enabled",     AsBool, enabled );
    WRITE_ARG( "penAnimated", AsBool, enabled );
    WRITE_END();
}
