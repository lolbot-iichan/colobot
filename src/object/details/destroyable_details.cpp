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
 * \file object/details/destroyable_details.cpp
 * \brief CObjectDestroyableDetails - set of tweaks for Destroyable objects
 */

#include "level/parser/parser.h"

#include "object/details/details_provider.h"
#include "object/details/hardcode.h"
#include "object/details/macro.h"
#include "object/details/destroyable_details.h"

void CObjectDestroyableDetails::ReadHardcode(ObjectType type)
{
    CHardcodeCollection hardcode;

    enabled = hardcode.IsDestroyable(type);
    removeBuildingLevel = hardcode.IsDestructionRemoveBuildingLevel(type);
    explosion.effect = hardcode.GetDestructionByExplosion(type);
    water.effect = hardcode.GetDestructionByWater(type);
    water.enabled = hardcode.IsExplodesInWater(type);
    burning.effect = hardcode.GetDestructionByBurning(type);
    burning.isKilledByBurning = hardcode.IsDestructionKilledByBurning(type);
    burning.parts = hardcode.GetBurnParts(type);
    burning.ruins = hardcode.GetTypeAfterBurn(type);
    drowned.effect = hardcode.GetDestructionByDrowned(type);
    win.effect = hardcode.GetDestructionByWin(type);
    squash.effect = hardcode.GetDestructionBySquash(type);
    squash.enabled = hardcode.IsSquashedByHeavy(type);
}

bool CObjectDestroyableDetails::Read(CLevelParserLine* line)
{
    READ_LINE( "SetObjectDestroyable" );
    READ_ARG( "enabled",             AsBool,       enabled);
    READ_ARG( "removeBuildingLevel", AsBool,       removeBuildingLevel);
    READ_ARG( "eEffect",             AsPyroType,   explosion.effect );
    READ_ARG( "wEffect",             AsPyroType,   water.effect );
    READ_ARG( "wDestroy",            AsBool,       water.enabled );
    READ_ARG( "bEffect",             AsPyroType,   burning.effect );
    READ_ARG( "bKills",              AsBool,       burning.isKilledByBurning );
    READ_ARG( "wreck",               AsObjectType, burning.ruins );
    READ_ARG( "dEffect",             AsPyroType,   drowned.effect );
    READ_ARG( "xEffect",             AsPyroType,   win.effect );
    READ_ARG( "sEffect",             AsPyroType,   squash.effect );
    READ_ARG( "sDestroy",            AsBool,       squash.enabled );
    READ_END();

    READ_LINE( "AddObjectBurningPart" );
    READ_NEW( id,                     burning.parts                );
    READ_ARG( "partNum",     AsInt,   burning.parts[id].partNum    );
    READ_ARG( "pos",         AsPoint, burning.parts[id].pos        );
    READ_ARG( "posRandom",   AsPoint, burning.parts[id].posRandom  );
    READ_ARG( "angle",       AsPoint, burning.parts[id].angle      );
    READ_ARG( "angleRandom", AsPoint, burning.parts[id].angleRandom);
    READ_ARG( "keep",        AsBool,  burning.parts[id].keep);
    READ_END();

    return false;
}

void CObjectDestroyableDetails::Write(CLevelParser* parser, ObjectType type)
{
    CObjectDestroyableDetails def;

    WRITE_LINE( "SetObjectDestroyable" );
    WRITE_ARG( "enabled",             def, enabled );
    WRITE_ARG( "removeBuildingLevel", def, removeBuildingLevel );
    WRITE_ARG( "eEffect",             def, explosion.effect );
    WRITE_ARG( "wEffect",             def, water.effect );
    WRITE_ARG( "wDestroy",            def, water.enabled );
    WRITE_ARG( "bEffect",             def, burning.effect );
    WRITE_ARG( "bKills",              def, burning.isKilledByBurning );
    WRITE_ARG( "wreck",               def, burning.ruins );
    WRITE_ARG( "dEffect",             def, drowned.effect );
    WRITE_ARG( "xEffect",             def, win.effect );
    WRITE_ARG( "sEffect",             def, squash.effect );
    WRITE_ARG( "sDestroy",            def, squash.enabled );
    WRITE_END();

    CPyroBurnPartDetails defB;
    for ( auto it: burning.parts )
    {
        WRITE_LINE( "AddObjectBurningPart" );
        WRITE_IT( "partNum",     defB, partNum     );
        WRITE_IT( "pos",         defB, pos         );
        WRITE_IT( "posRandom",   defB, posRandom   );
        WRITE_IT( "angle",       defB, angle       );
        WRITE_IT( "angleRandom", defB, angleRandom );
        WRITE_IT( "keep",        defB, keep        );
        WRITE_END();
    }
}

CObjectDestroyableDetails GetObjectDestroyableDetails(CObject* obj)
{
    return CObjectDetails::GetInstance().GetObjectDetails(obj).destroyable;
}