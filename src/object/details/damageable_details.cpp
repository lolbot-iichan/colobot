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
 * \file object/details/damageable_details.cpp
 * \brief CObjectDamageableDetails - set of tweaks for Damageable objects
 */

#include "level/parser/parser.h"

#include "object/details/details_provider.h"
#include "object/details/hardcode.h"
#include "object/details/macro.h"
#include "object/details/damageable_details.h"

void CObjectDamageableDetails::ReadHardcode(ObjectType type)
{
    CHardcodeCollection hardcode;

    enabled               = hardcode.IsDamageable(type);
    effect                = hardcode.GetDamageEffect(type);

    fire.enabled          = ! hardcode.IsImmuneToFireballs(type);
    organic.enabled       = ! hardcode.IsImmuneToInsects(type);
    phazer.enabled        = ! hardcode.IsImmuneToPhazers(type);
    tower.enabled         = ! hardcode.IsImmuneToTowerRays(type);
    fallingObject.enabled = ! hardcode.IsImmuneToOrgaballs(type);
    explosive.enabled     = ! hardcode.IsImmuneToExplosive(type);
    collision.enabled     = ! hardcode.IsImmuneToCollisions(type);
    lightning.enabled     = ! hardcode.IsImmuneToLightning(type);
    fall.enabled          = ! hardcode.IsImmuneToFall(type);
    spider.enabled        = ! hardcode.IsImmuneToSpiders(type);

    lightning.lightningRodHeight      = hardcode.GetLightningRodHeight(type);
    lightning.lightningHitProbability = hardcode.GetLightningHitProbability(type);
}

bool CObjectDamageableDetails::Read(CLevelParserLine* line)
{
    READ_LINE( "SetObjectDamageable" );
    READ_ARG( "enabled",      AsBool,     enabled               );
    READ_ARG( "effect",       AsPyroType, effect                );
    READ_ARG( "fDamage",      AsBool,     fire.enabled          );
    READ_ARG( "oDamage",      AsBool,     organic.enabled       );
    READ_ARG( "pDamage",      AsBool,     phazer.enabled        );
    READ_ARG( "tDamage",      AsBool,     tower.enabled         );
    READ_ARG( "wDamage",      AsBool,     fallingObject.enabled );
    READ_ARG( "eDamage",      AsBool,     explosive.enabled     );
    READ_ARG( "cDamage",      AsBool,     collision.enabled     );
    READ_ARG( "lDamage",      AsBool,     lightning.enabled     );
    READ_ARG( "hDamage",      AsBool,     fall.enabled          );
    READ_ARG( "sDamage",      AsBool,     spider.enabled        );
    READ_ARG( "lRod",         AsFloat,    lightning.lightningRodHeight );
    READ_ARG( "lProbability", AsFloat,    lightning.lightningHitProbability );
    READ_END();

    return false;
}

void CObjectDamageableDetails::Write(CLevelParser* parser, ObjectType type)
{
    CObjectDamageableDetails def;

    WRITE_LINE( "SetObjectDamageable" );
    WRITE_ARG( "enabled",      def, enabled               );
    WRITE_ARG( "effect",       def, effect                );
    WRITE_ARG( "fDamage",      def, fire.enabled          );
    WRITE_ARG( "oDamage",      def, organic.enabled       );
    WRITE_ARG( "pDamage",      def, phazer.enabled        );
    WRITE_ARG( "tDamage",      def, tower.enabled         );
    WRITE_ARG( "wDamage",      def, fallingObject.enabled );
    WRITE_ARG( "eDamage",      def, explosive.enabled     );
    WRITE_ARG( "cDamage",      def, collision.enabled     );
    WRITE_ARG( "lDamage",      def, lightning.enabled     );
    WRITE_ARG( "hDamage",      def, fall.enabled          );
    WRITE_ARG( "sDamage",      def, spider.enabled        );
    WRITE_ARG( "lRod",         def, lightning.lightningRodHeight );
    WRITE_ARG( "lProbability", def, lightning.lightningHitProbability );
    WRITE_END();
}

CObjectDamageableDetails GetObjectDamageableDetails(CObject* obj)
{
    return CObjectDetails::GetInstance().GetObjectDetails(obj).damageable;
}