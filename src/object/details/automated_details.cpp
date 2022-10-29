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
 * \file object/details/automated_details.cpp
 * \brief CObjectAutomatedDetails - set of tweaks for Automated objects
 */

#include "level/parser/parser.h"

#include "object/details/macro.h"
#include "object/details/automated_details.h"

#include "object/hardcode/automated_hardcode.h"

void CObjectAutomatedDetails::ReadHardcode(ObjectType type)
{
    autoClass                      = CAutomatedHardcodeCollection::GetCreationAutoClass(type);

    blocking.blocksBuilding        = CAutomatedHardcodeCollection::IsBlockingBuilding(type);
    blocking.blocksPowerPlant      = CAutomatedHardcodeCollection::IsAutoBlockingPowerPlant(type);
    blocking.blocksNuclearPlant    = CAutomatedHardcodeCollection::IsAutoBlockingNuclearPlant(type);
    blocking.blocksFactory         = CAutomatedHardcodeCollection::IsAutoBlockingFactory(type);

    targeted.attackedByTower       = CAutomatedHardcodeCollection::IsAutoTargetedByTower(type);
    targeted.attackedByMushroom    = CAutomatedHardcodeCollection::IsAutoTargetedByMushroom(type);
    targeted.chargedByPowerStation = CAutomatedHardcodeCollection::IsAutoChargedAtPowerStation(type);
    targeted.commentedByAssistant  = CAutomatedHardcodeCollection::IsAutoCommentedByAssistant(type);
    
    factory                        = CAutomatedHardcodeCollection::GetFactory(type);
    egg                            = CAutomatedHardcodeCollection::GetEgg(type);
    production                     = CAutomatedHardcodeCollection::GetProduction(type);
    digging                        = CAutomatedHardcodeCollection::GetDigging(type);
    vault                          = CAutomatedHardcodeCollection::GetVault(type);
    quarz                          = CAutomatedHardcodeCollection::GetQuarz(type);
    lamp                           = CAutomatedHardcodeCollection::GetLamp(type);
}

bool CObjectAutomatedDetails::Read(CLevelParserLine* line)
{
    READ_LINE( "SetObjectAutomated" );
    READ_ARG( "class", AsInt, autoClass );
    READ_END();

    READ_LINE( "SetObjectAutomatedBlock" );
    READ_ARG( "building",   AsBool, blocking.blocksBuilding     );
    READ_ARG( "powerplant", AsBool, blocking.blocksPowerPlant   );
    READ_ARG( "nuclear",    AsBool, blocking.blocksNuclearPlant );
    READ_ARG( "factory",    AsBool, blocking.blocksFactory      );
    READ_END();

    READ_LINE( "SetObjectAutomatedTarget" );
    READ_ARG( "byTower",        AsBool, targeted.attackedByTower       );
    READ_ARG( "byMushroom",     AsBool, targeted.attackedByMushroom    );
    READ_ARG( "byPowerStation", AsBool, targeted.chargedByPowerStation );
    READ_ARG( "byAssistant",    AsBool, targeted.commentedByAssistant  );
    READ_END();

    READ_IT_LINE( "AddObjectAutomatedFactory", "UpdObjectAutomatedFactory", "ClrObjectAutomatedFactory", factory.objects );
    READ_IT_ARG( "input",       AsObjectType, input       );
    READ_IT_ARG( "output",      AsObjectType, output      );
    READ_IT_ARG( "message",     AsString,     message     );
    READ_IT_ARG( "partNum",     AsInt,        partNum     );
    READ_IT_ARG( "position",    AsPoint,      position    );
    READ_IT_ARG( "researches",  AsInt,        researches  );
    READ_IT_ARG( "rotateTweak", AsBool,       rotateTweak );
    READ_IT_END();

    READ_LINE( "SetObjectAutomatedEgg" );
    READ_ARG( "noInput", AsString, egg.noInput );
    READ_END();

    READ_IT_LINE( "AddObjectAutomatedEgg", "UpdObjectAutomatedEgg", "ClrObjectAutomatedEgg", egg.objects );
    READ_IT_ARG( "input",      AsObjectType, input      );
    READ_IT_ARG( "duration",   AsFloat,      duration   );
    READ_IT_ARG( "beginScale", AsFloat,      beginScale );
    READ_IT_ARG( "endScale",   AsFloat,      endScale   );
    READ_IT_ARG( "message",    AsString,     message    );
    READ_IT_END();

    READ_LINE( "SetObjectAutomatedDigging" );
    READ_ARG( "noSoil",   AsString, digging.noSoil   );
    READ_ARG( "partNum",  AsInt,    digging.partNum  );
    READ_ARG( "position", AsPoint,  digging.position );
    READ_END();

    READ_IT_LINE( "AddObjectAutomatedDigging", "UpdObjectAutomatedDigging", "ClrObjectAutomatedDigging", digging.objects );
    READ_IT_ARG( "soil",     AsTerrainRes, soil     );
    READ_IT_ARG( "output",   AsObjectType, output   );
    READ_IT_ARG( "maxCount", AsInt,        maxCount );
    READ_IT_ARG( "duration", AsFloat,      duration );
    READ_IT_ARG( "message",  AsString,     message  );
    READ_IT_END();

    READ_LINE( "SetObjectAutomatedProduction" );
    READ_ARG( "noInput",  AsString, production.noInput  );
    READ_ARG( "badInput", AsString, production.badInput );
    READ_END();

    READ_IT_LINE( "AddObjectAutomatedProduction", "UpdObjectAutomatedProduction", "ClrObjectAutomatedProduction", production.objects );
    READ_IT_ARG( "input",   AsObjectType, input   );
    READ_IT_ARG( "output",  AsObjectType, output  );
    READ_IT_ARG( "message", AsString,     message );
    READ_IT_END();

    READ_IT_LINE( "AddObjectAutomatedVaultKey", "UpdObjectAutomatedVaultKey", "ClrObjectAutomatedVaultKey", vault.keys );
    READ_IT_ARG( "input",    AsObjectType, input   );
    READ_IT_ARG( "slotNum",  AsInt,        slotNum );
    READ_IT_END();

    READ_IT_LINE( "AddObjectAutomatedVaultDoor", "UpdObjectAutomatedVaultDoor", "ClrObjectAutomatedVaultDoor", vault.doors );
    READ_IT_ARG( "needKeys", AsInt,   needKeys );
    READ_IT_ARG( "partNum",  AsFloat, partNum  );
    READ_IT_ARG( "position", AsPoint, position );
    READ_IT_ARG( "rotation", AsPoint, rotation );
    READ_IT_END();

    READ_LINE( "SetObjectAutomatedQuarz" );
    READ_ARG( "numLights", AsInt,   quarz.numLights );
    READ_ARG( "partNum",   AsInt,   quarz.partNum   );
    READ_ARG( "position",  AsPoint, quarz.position  );
    READ_ARG( "radius",    AsFloat, quarz.radius    );
    READ_END();

    READ_LINE( "SetObjectAutomatedLampParticle" );
    READ_ARG( "partNum",   AsInt,   lamp.particle.partNum  );
    READ_ARG( "position",  AsPoint, lamp.particle.position );
    READ_ARG( "size",      AsFloat, lamp.particle.size     );
    READ_END();

    READ_LINE( "SetObjectAutomatedLampSpot" );
    READ_ARG( "partNum",   AsInt,   lamp.spot.partNum  );
    READ_ARG( "position",  AsPoint, lamp.spot.position );
    READ_ARG( "color",     AsColor, lamp.spot.color    );
    READ_END();

    return false;
}

void CObjectAutomatedDetails::Write(CLevelParser* parser, ObjectType type)
{
    WRITE_LINE( "SetObjectAutomated" );
    WRITE_ARG( "class", AsInt, autoClass );
    WRITE_END();

    WRITE_LINE( "SetObjectAutomatedBlock" );
    WRITE_ARG( "building",   AsBool, blocking.blocksBuilding     );
    WRITE_ARG( "powerplant", AsBool, blocking.blocksPowerPlant   );
    WRITE_ARG( "nuclear",    AsBool, blocking.blocksNuclearPlant );
    WRITE_ARG( "factory",    AsBool, blocking.blocksFactory      );
    WRITE_END();

    WRITE_LINE( "SetObjectAutomatedTarget" );
    WRITE_ARG( "byTower",        AsBool, targeted.attackedByTower       );
    WRITE_ARG( "byMushroom",     AsBool, targeted.attackedByMushroom    );
    WRITE_ARG( "byPowerStation", AsBool, targeted.chargedByPowerStation );
    WRITE_ARG( "byAssistant",    AsBool, targeted.commentedByAssistant  );
    WRITE_END();

    WRITE_IT_LINE( "AddObjectAutomatedFactory", factory.objects );
    WRITE_IT_ARG( "input",       AsObjectType, input       );
    WRITE_IT_ARG( "output",      AsObjectType, output      );
    WRITE_IT_ARG( "message",     AsString,     message     );
    WRITE_IT_ARG( "partNum",     AsInt,        partNum     );
    WRITE_IT_ARG( "position",    AsPoint,      position    );
    WRITE_IT_ARG( "researches",  AsInt,        researches  );
    WRITE_IT_ARG( "rotateTweak", AsBool,       rotateTweak );
    WRITE_IT_END();

    WRITE_LINE( "SetObjectAutomatedEgg" );
    WRITE_ARG( "noInput", AsString, egg.noInput );
    WRITE_END();

    WRITE_IT_LINE( "AddObjectAutomatedEgg", egg.objects );
    WRITE_IT_ARG( "input",      AsObjectType, input      );
    WRITE_IT_ARG( "duration",   AsFloat,      duration   );
    WRITE_IT_ARG( "beginScale", AsFloat,      beginScale );
    WRITE_IT_ARG( "endScale",   AsFloat,      endScale   );
    WRITE_IT_ARG( "message",    AsString,     message    );
    WRITE_IT_END();

    WRITE_LINE( "SetObjectAutomatedDigging" );
    WRITE_ARG( "noSoil",   AsString, digging.noSoil   );
    WRITE_ARG( "partNum",  AsInt,    digging.partNum  );
    WRITE_ARG( "position", AsPoint,  digging.position );
    WRITE_END();

    WRITE_IT_LINE( "AddObjectAutomatedDigging", digging.objects );
    WRITE_IT_ARG( "soil",     AsTerrainRes, soil     );
    WRITE_IT_ARG( "output",   AsObjectType, output   );
    WRITE_IT_ARG( "maxCount", AsInt,        maxCount );
    WRITE_IT_ARG( "duration", AsFloat,      duration );
    WRITE_IT_ARG( "message",  AsString,     message  );
    WRITE_IT_END();

    WRITE_LINE( "SetObjectAutomatedProduction" );
    WRITE_ARG( "noInput",  AsString, production.noInput  );
    WRITE_ARG( "badInput", AsString, production.badInput );
    WRITE_END();

    WRITE_IT_LINE( "AddObjectAutomatedProduction", production.objects );
    WRITE_IT_ARG( "input",   AsObjectType, input   );
    WRITE_IT_ARG( "output",  AsObjectType, output  );
    WRITE_IT_ARG( "message", AsString,     message );
    WRITE_IT_END();

    WRITE_IT_LINE( "AddObjectAutomatedVaultKey", vault.keys );
    WRITE_IT_ARG( "input",    AsObjectType, input   );
    WRITE_IT_ARG( "slotNum",  AsInt,        slotNum );
    WRITE_IT_END();

    WRITE_IT_LINE( "AddObjectAutomatedVaultDoor", vault.doors );
    WRITE_IT_ARG( "needKeys", AsInt,   needKeys );
    WRITE_IT_ARG( "partNum",  AsFloat, partNum  );
    WRITE_IT_ARG( "position", AsPoint, position );
    WRITE_IT_ARG( "rotation", AsPoint, rotation );
    WRITE_IT_END();

    WRITE_LINE( "SetObjectAutomatedQuarz" );
    WRITE_ARG( "numLights", AsInt,   quarz.numLights );
    WRITE_ARG( "partNum",   AsInt,   quarz.partNum   );
    WRITE_ARG( "position",  AsPoint, quarz.position  );
    WRITE_ARG( "radius",    AsFloat, quarz.radius    );
    WRITE_END();

    WRITE_LINE( "SetObjectAutomatedLampParticle" );
    WRITE_ARG( "partNum",   AsInt,   lamp.particle.partNum  );
    WRITE_ARG( "position",  AsPoint, lamp.particle.position );
    WRITE_ARG( "size",      AsFloat, lamp.particle.size     );
    WRITE_END();

    WRITE_LINE( "SetObjectAutomatedLampSpot" );
    WRITE_ARG( "partNum",   AsInt,   lamp.spot.partNum  );
    WRITE_ARG( "position",  AsPoint, lamp.spot.position );
    WRITE_ARG( "color",     AsColor, lamp.spot.color    );
    WRITE_END();

}
