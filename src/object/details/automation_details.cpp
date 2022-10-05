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

    blocking.blocksBuilding        = hardcode.IsBlockingBuilding(type);
    blocking.blocksPowerPlant      = hardcode.IsAutoBlockingPowerPlant(type);
    blocking.blocksNuclearPlant    = hardcode.IsAutoBlockingNuclearPlant(type);
    blocking.blocksFactory         = hardcode.IsAutoBlockingFactory(type);

    targeted.attackedByTower       = hardcode.IsAutoTargetedByTower(type);
    targeted.attackedByMushroom    = hardcode.IsAutoTargetedByMushroom(type);
    targeted.chargedByPowerStation = hardcode.IsAutoChargedAtPowerStation(type);
    targeted.commentedByAssistant  = hardcode.IsAutoCommentedByAssistant(type);
    
    production                     = hardcode.GetProduction(type);
}

bool CObjectAutomationDetails::Read(CLevelParserLine* line)
{
    READ_LINE( "SetObjectAutomationBlock" );
    READ_ARG( "building",   AsBool, blocking.blocksBuilding    );
    READ_ARG( "powerplant", AsBool, blocking.blocksPowerPlant  );
    READ_ARG( "nuclear",    AsBool, blocking.blocksNuclearPlant);
    READ_ARG( "factory",    AsBool, blocking.blocksFactory     );
    READ_END();

    READ_LINE( "SetObjectAutomationTarget" );
    READ_ARG( "byTower",        AsBool, targeted.attackedByTower       );
    READ_ARG( "byMushroom",     AsBool, targeted.attackedByMushroom    );
    READ_ARG( "byPowerStation", AsBool, targeted.chargedByPowerStation );
    READ_ARG( "byAssistant",    AsBool, targeted.commentedByAssistant  );
    READ_END();

    READ_LINE( "AddObjectAutomationProduction" );
    READ_NEW( id,                     production            );
    READ_ARG( "input",  AsObjectType, production[id].input  );
    READ_ARG( "output", AsObjectType, production[id].output );
    READ_END();

    READ_LINE( "UpdateObjectAutomationProduction" );
    READ_IDX( id );
    READ_ARG( "input",  AsObjectType, production[id].input  );
    READ_ARG( "output", AsObjectType, production[id].output );
    READ_END();

    return false;
}

void CObjectAutomationDetails::Write(CLevelParser* parser, ObjectType type)
{
    CObjectAutomationDetails def;

    WRITE_LINE( "SetObjectAutomationBlock" );
    WRITE_ARG( "building",   def, blocking.blocksBuilding     );
    WRITE_ARG( "powerplant", def, blocking.blocksPowerPlant   );
    WRITE_ARG( "nuclear",    def, blocking.blocksNuclearPlant );
    WRITE_ARG( "factory",    def, blocking.blocksFactory      );
    WRITE_END();

    WRITE_LINE( "SetObjectAutomationTarget" );
    WRITE_ARG( "byTower",        def, targeted.attackedByTower       );
    WRITE_ARG( "byMushroom",     def, targeted.attackedByMushroom    );
    WRITE_ARG( "byPowerStation", def, targeted.chargedByPowerStation );
    WRITE_ARG( "byAssistant",    def, targeted.commentedByAssistant  );
    WRITE_END();

    CObjectProductionAutomationDetails defP;
    for ( auto it : production )
    {
        WRITE_LINE( "AddObjectAutomationProduction" );
        WRITE_IT( "input",  defP, input  );
        WRITE_IT( "output", defP, output );
        WRITE_END();
    }
}

CObjectAutomationDetails GetObjectAutomationDetails(CObject* obj)
{
    return CObjectDetails::GetInstance().GetObjectDetails(obj).automation;
}
