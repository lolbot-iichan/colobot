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
    message = hardcode.GetDestroyMessage(type);

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

    thumper.enabled         = hardcode.GetThumperSafeRadius(type) != -1.0f;
    thumper.safeRadius      = hardcode.GetThumperSafeRadius(type);
    thumper.effect          = hardcode.GetThumperPyroType(type);
    thumper.explosionDamage = hardcode.GetThumperExplosionDamage(type);
}

bool CObjectDestroyableDetails::Read(CLevelParserLine* line)
{
    READ_LINE( "SetObjectDestroyable" );
    READ_ARG( "enabled",             AsBool,       enabled                   );
    READ_ARG( "removeBuildingLevel", AsBool,       removeBuildingLevel       );
    READ_ARG( "message",             AsString,     message                   );
    READ_ARG( "eEffect",             AsPyroType,   explosion.effect          );
    READ_ARG( "wEffect",             AsPyroType,   water.effect              );
    READ_ARG( "wDestroy",            AsBool,       water.enabled             );
    READ_ARG( "bEffect",             AsPyroType,   burning.effect            );
    READ_ARG( "bKills",              AsBool,       burning.isKilledByBurning );
    READ_ARG( "wreck",               AsObjectType, burning.ruins             );
    READ_ARG( "dEffect",             AsPyroType,   drowned.effect            );
    READ_ARG( "xEffect",             AsPyroType,   win.effect                );
    READ_ARG( "sEffect",             AsPyroType,   squash.effect             );
    READ_ARG( "sDestroy",            AsBool,       squash.enabled            );
    READ_ARG( "tEffect",             AsPyroType,   thumper.effect            );
    READ_ARG( "tDestroy",            AsBool,       thumper.enabled           );
    READ_ARG( "tSafe",               AsFloat,      thumper.safeRadius        );
    READ_ARG( "tDamage",             AsFloat,      thumper.explosionDamage   );
    READ_END();

    READ_IT_LINE( "AddObjectBurningPart", "UpdObjectBurningPart", "ClrObjectBurningPart", burning.parts );
    READ_IT_ARG( "partNum",     AsInt,   partNum     );
    READ_IT_ARG( "position",    AsPoint, position    );
    READ_IT_ARG( "posRandom",   AsPoint, posRandom   );
    READ_IT_ARG( "angle",       AsPoint, angle       );
    READ_IT_ARG( "angleRandom", AsPoint, angleRandom );
    READ_IT_ARG( "keep",        AsBool,  keep        );
    READ_IT_END();

    return false;
}

void CObjectDestroyableDetails::Write(CLevelParser* parser, ObjectType type)
{
    WRITE_LINE( "SetObjectDestroyable" );
    WRITE_ARG( "enabled",             AsBool,       enabled                   );
    WRITE_ARG( "removeBuildingLevel", AsBool,       removeBuildingLevel       );
    WRITE_ARG( "message",             AsString,     message                   );
    WRITE_ARG( "eEffect",             AsPyroType,   explosion.effect          );
    WRITE_ARG( "wEffect",             AsPyroType,   water.effect              );
    WRITE_ARG( "wDestroy",            AsBool,       water.enabled             );
    WRITE_ARG( "bEffect",             AsPyroType,   burning.effect            );
    WRITE_ARG( "bKills",              AsBool,       burning.isKilledByBurning );
    WRITE_ARG( "wreck",               AsObjectType, burning.ruins             );
    WRITE_ARG( "dEffect",             AsPyroType,   drowned.effect            );
    WRITE_ARG( "xEffect",             AsPyroType,   win.effect                );
    WRITE_ARG( "sEffect",             AsPyroType,   squash.effect             );
    WRITE_ARG( "sDestroy",            AsBool,       squash.enabled            );
    WRITE_ARG( "tEffect",             AsPyroType,   thumper.effect            );
    WRITE_ARG( "tDestroy",            AsBool,       thumper.enabled           );
    WRITE_ARG( "tSafe",               AsFloat,      thumper.safeRadius        );
    WRITE_ARG( "tDamage",             AsFloat,      thumper.explosionDamage   );
    WRITE_END();

    WRITE_IT_LINE( "AddObjectBurningPart", burning.parts );
    WRITE_IT_ARG( "partNum",     AsInt,   partNum     );
    WRITE_IT_ARG( "position",    AsPoint, position    );
    WRITE_IT_ARG( "posRandom",   AsPoint, posRandom   );
    WRITE_IT_ARG( "angle",       AsPoint, angle       );
    WRITE_IT_ARG( "angleRandom", AsPoint, angleRandom );
    WRITE_IT_ARG( "keep",        AsBool,  keep        );
    WRITE_IT_END();
}

CObjectDestroyableDetails GetObjectDestroyableDetails(CObject* obj)
{
    return CObjectDetails::GetInstance().GetObjectDetails(obj).destroyable;
}