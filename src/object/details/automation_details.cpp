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
 * \file object/details/automation_details.cpp
 * \brief CObjectAutomationDetails - set of tweaks for Automation objects
 */

#include "level/parser/parser.h"

#include "object/details/details_provider.h"
#include "object/details/hardcode.h"
#include "object/details/macro.h"
#include "object/details/automation_details.h"

void CObjectAutomationDetails::ReadHardcode(ObjectType type)
{
    CHardcodeCollection hardcode;

    autoClass                      = hardcode.GetCreationAutoClass(type);

    blocking.blocksBuilding        = hardcode.IsBlockingBuilding(type);
    blocking.blocksPowerPlant      = hardcode.IsAutoBlockingPowerPlant(type);
    blocking.blocksNuclearPlant    = hardcode.IsAutoBlockingNuclearPlant(type);
    blocking.blocksFactory         = hardcode.IsAutoBlockingFactory(type);

    targeted.attackedByTower       = hardcode.IsAutoTargetedByTower(type);
    targeted.attackedByMushroom    = hardcode.IsAutoTargetedByMushroom(type);
    targeted.chargedByPowerStation = hardcode.IsAutoChargedAtPowerStation(type);
    targeted.commentedByAssistant  = hardcode.IsAutoCommentedByAssistant(type);
    
    production                     = hardcode.GetProduction(type);
    digging                        = hardcode.GetDigging(type);
}

bool CObjectAutomationDetails::Read(CLevelParserLine* line)
{
    READ_LINE( "SetObjectAutomation" );
    READ_ARG( "class", AsInt, autoClass );
    READ_END();

    READ_LINE( "SetObjectAutomationBlock" );
    READ_ARG( "building",   AsBool, blocking.blocksBuilding     );
    READ_ARG( "powerplant", AsBool, blocking.blocksPowerPlant   );
    READ_ARG( "nuclear",    AsBool, blocking.blocksNuclearPlant );
    READ_ARG( "factory",    AsBool, blocking.blocksFactory      );
    READ_END();

    READ_LINE( "SetObjectAutomationTarget" );
    READ_ARG( "byTower",        AsBool, targeted.attackedByTower       );
    READ_ARG( "byMushroom",     AsBool, targeted.attackedByMushroom    );
    READ_ARG( "byPowerStation", AsBool, targeted.chargedByPowerStation );
    READ_ARG( "byAssistant",    AsBool, targeted.commentedByAssistant  );
    READ_END();

    READ_LINE( "SetObjectAutomationDigging" );
    READ_ARG( "noSoil",   AsString, digging.noSoil   );
    READ_ARG( "partNum",  AsInt,    digging.partNum  );
    READ_ARG( "position", AsPoint,  digging.position );
    READ_END();

    READ_IT_LINE( "AddObjectAutomationDigging", "UpdObjectAutomationDigging", "ClrObjectAutomationDigging", digging.objects );
    READ_IT_ARG( "soil",     AsTerrainRes, soil     );
    READ_IT_ARG( "output",   AsObjectType, output   );
    READ_IT_ARG( "maxCount", AsInt,        maxCount );
    READ_IT_ARG( "duration", AsFloat,      duration );
    READ_IT_ARG( "message",  AsString,     message  );
    READ_IT_END();

    READ_LINE( "SetObjectAutomationProduction" );
    READ_ARG( "noInput",  AsString, production.noInput  );
    READ_ARG( "badInput", AsString, production.badInput );
    READ_END();

    READ_IT_LINE( "AddObjectAutomationProduction", "UpdObjectAutomationProduction", "ClrObjectAutomationProduction", production.objects );
    READ_IT_ARG( "input",   AsObjectType, input   );
    READ_IT_ARG( "output",  AsObjectType, output  );
    READ_IT_ARG( "message", AsString,     message );
    READ_IT_END();

    return false;
}

void CObjectAutomationDetails::Write(CLevelParser* parser, ObjectType type)
{
    WRITE_LINE( "SetObjectAutomation" );
    WRITE_ARG( "class", AsInt, autoClass );
    WRITE_END();

    WRITE_LINE( "SetObjectAutomationBlock" );
    WRITE_ARG( "building",   AsBool, blocking.blocksBuilding     );
    WRITE_ARG( "powerplant", AsBool, blocking.blocksPowerPlant   );
    WRITE_ARG( "nuclear",    AsBool, blocking.blocksNuclearPlant );
    WRITE_ARG( "factory",    AsBool, blocking.blocksFactory      );
    WRITE_END();

    WRITE_LINE( "SetObjectAutomationTarget" );
    WRITE_ARG( "byTower",        AsBool, targeted.attackedByTower       );
    WRITE_ARG( "byMushroom",     AsBool, targeted.attackedByMushroom    );
    WRITE_ARG( "byPowerStation", AsBool, targeted.chargedByPowerStation );
    WRITE_ARG( "byAssistant",    AsBool, targeted.commentedByAssistant  );
    WRITE_END();

    WRITE_LINE( "SetObjectAutomationDigging" );
    WRITE_ARG( "noSoil",   AsString, digging.noSoil   );
    WRITE_ARG( "partNum",  AsInt,    digging.partNum  );
    WRITE_ARG( "position", AsPoint,  digging.position );
    WRITE_END();

    WRITE_IT_LINE( "AddObjectAutomationDigging", digging.objects );
    WRITE_IT_ARG( "soil",     AsTerrainRes, soil     );
    WRITE_IT_ARG( "output",   AsObjectType, output   );
    WRITE_IT_ARG( "maxCount", AsInt,        maxCount );
    WRITE_IT_ARG( "duration", AsFloat,      duration );
    WRITE_IT_ARG( "message",  AsString,     message  );
    WRITE_IT_END();

    WRITE_LINE( "SetObjectAutomationProduction" );
    WRITE_ARG( "noInput",  AsString, production.noInput  );
    WRITE_ARG( "badInput", AsString, production.badInput );
    WRITE_END();

    WRITE_IT_LINE( "AddObjectAutomationProduction", production.objects );
    WRITE_IT_ARG( "input",   AsObjectType, input   );
    WRITE_IT_ARG( "output",  AsObjectType, output  );
    WRITE_IT_ARG( "message", AsString,     message );
    WRITE_IT_END();
}

CObjectAutomationDetails GetObjectAutomationDetails(CObject* obj)
{
    return CObjectDetails::GetInstance().GetObjectDetails(obj).automation;
}
