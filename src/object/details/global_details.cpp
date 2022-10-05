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
 * \file object/details/global_details.cpp
 * \brief CObjectGlobalDetails - set of tweaks for Global objects
 */

#include "level/parser/parser.h"

#include "object/details/details_provider.h"
#include "object/details/hardcode.h"
#include "object/details/macro.h"
#include "object/details/global_details.h"

void CObjectGlobalDetails::ReadHardcode()
{
    CHardcodeCollection hardcode;

    defaults.player           = hardcode.GetPlayerType();
    defaults.base             = hardcode.GetBaseType();
    defaults.assistant        = hardcode.GetAssistantType();
    defaults.destroyPerformer = hardcode.GetFunctionDestroyPerformerObject();
    defaults.factoryPerformer = hardcode.GetFunctionFactoryPerformerObject();
    defaults.takeoffPerformer = hardcode.GetFunctionTakeOffPerformerObject();
    defaults.receivePerformer = hardcode.GetFunctionReceivePerformerObject();
    
    builderMenu = hardcode.GetBuilderMenuButtons();
    debugMenu   = hardcode.GetDebugMenuButtons();
}

bool CObjectGlobalDetails::Read(CLevelParserLine* line)
{
    READ_LINE( "SetGlobals" );
    READ_ARG( "player",    AsObjectType, defaults.player           );
    READ_ARG( "base",      AsObjectType, defaults.base             );
    READ_ARG( "assistant", AsObjectType, defaults.assistant        );
    READ_ARG( "destroy",   AsObjectType, defaults.destroyPerformer );
    READ_ARG( "factory",   AsObjectType, defaults.factoryPerformer );
    READ_ARG( "takeoff",   AsObjectType, defaults.takeoffPerformer );
    READ_ARG( "receive",   AsObjectType, defaults.receivePerformer );
    READ_END();

    READ_LINE( "AddBuilderMenuItem" );
    READ_NEW( id,                     builderMenu          )
    READ_ARG( "object", AsObjectType, builderMenu[id].type );
    READ_ARG( "icon",   AsInt,        builderMenu[id].icon );
    READ_ARG( "text",   AsString,     builderMenu[id].text );
    READ_END();

    READ_LINE( "AddDebugMenuItem" );
    READ_NEW( id,                     debugMenu          )
    READ_ARG( "object", AsObjectType, debugMenu[id].type );
    READ_ARG( "icon",   AsInt,        debugMenu[id].icon );
    READ_ARG( "text",   AsString,     debugMenu[id].text );
    READ_END();

    READ_LINE( "UpdateBuilderMenuItem" );
    READ_IDX( id );
    READ_ARG( "object", AsObjectType, builderMenu[id].type );
    READ_ARG( "icon",   AsInt,        builderMenu[id].icon );
    READ_ARG( "text",   AsString,     builderMenu[id].text );
    READ_END();

    READ_LINE( "UpdateDebugMenuItem" );
    READ_IDX( id );
    READ_ARG( "object", AsObjectType, debugMenu[id].type );
    READ_ARG( "icon",   AsInt,        debugMenu[id].icon );
    READ_ARG( "text",   AsString,     debugMenu[id].text );
    READ_END();

    READ_LINE( "ClearBuilderMenuItems" );
    builderMenu.clear();
    READ_END();

    READ_LINE( "ClearDebugMenuItems" );
    debugMenu.clear();
    READ_END();

    return false;
}

void CObjectGlobalDetails::Write(CLevelParser* parser)
{
    CObjectGlobalDetails def;

    WRITE_GLOB( "SetGlobals" );
    WRITE_ARG( "player",    def, defaults.player           );
    WRITE_ARG( "base",      def, defaults.base             );
    WRITE_ARG( "assistant", def, defaults.assistant        );
    WRITE_ARG( "destroy",   def, defaults.destroyPerformer );
    WRITE_ARG( "factory",   def, defaults.factoryPerformer );
    WRITE_ARG( "takeoff",   def, defaults.takeoffPerformer );
    WRITE_ARG( "receive",   def, defaults.receivePerformer );
    WRITE_END();

    CObjectButton defB;
    for ( auto it : builderMenu )
    {
        WRITE_GLOB( "AddBuilderMenuItem" );
        WRITE_IT( "object", defB, type );
        WRITE_IT( "icon",   defB, icon );
        WRITE_IT( "text",   defB, text );
        WRITE_END();
    }
    for ( auto it : debugMenu )
    {
        WRITE_GLOB( "AddDebugMenuItem" );
        WRITE_IT( "object", defB, type );
        WRITE_IT( "icon",   defB, icon );
        WRITE_IT( "text",   defB, text );
        WRITE_END();
    }
}

CObjectGlobalDetails GetObjectGlobalDetails()
{
    return CObjectDetails::GetInstance().GetGlobalDetails();
}