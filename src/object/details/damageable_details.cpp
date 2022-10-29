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

#include "object/details/macro.h"
#include "object/details/damageable_details.h"

#include "object/hardcode/damageable_hardcode.h"

void CObjectDamageableDetails::ReadHardcode(ObjectType type)
{
    enabled               = CDamageableHardcodeCollection::IsDamageable(type);
    effect                = CDamageableHardcodeCollection::GetDamageEffect(type);

    fire.enabled          = ! CDamageableHardcodeCollection::IsImmuneToFireballs(type);
    organic.byInsects     = ! CDamageableHardcodeCollection::IsImmuneToInsects(type);
    organic.byRobots      = ! CDamageableHardcodeCollection::IsImmuneToOrgashooters(type);
    organic.enabled       = organic.byInsects || organic.byRobots;

    phazer.enabled        = ! CDamageableHardcodeCollection::IsImmuneToPhazers(type);
    tower.enabled         = ! CDamageableHardcodeCollection::IsImmuneToTowerRays(type);
    fallingObject.enabled = ! CDamageableHardcodeCollection::IsImmuneToOrgaballs(type);
    explosive.enabled     = ! CDamageableHardcodeCollection::IsImmuneToExplosive(type);
    collision.byItself    = ! CDamageableHardcodeCollection::IsImmuneToCollisionsByItself(type);
    collision.byOthers    = ! CDamageableHardcodeCollection::IsImmuneToCollisionsByOthers(type);
    collision.enabled     = collision.byItself || collision.byOthers;

    lightning.enabled     = ! CDamageableHardcodeCollection::IsImmuneToLightning(type);
    fall.enabled          = ! CDamageableHardcodeCollection::IsImmuneToFall(type);
    spider.enabled        = ! CDamageableHardcodeCollection::IsImmuneToSpiders(type);

    organic.sound                     = CDamageableHardcodeCollection::GetInsectDamageSound(type);
    collision.ignoreRadius            = CDamageableHardcodeCollection::GetCollisionOtherObjectRadiusToIgnore(type);
    collision.resistance              = CDamageableHardcodeCollection::GetCollisionResistance(type);
    lightning.lightningRodHeight      = CDamageableHardcodeCollection::GetLightningRodHeight(type);
    lightning.lightningHitProbability = CDamageableHardcodeCollection::GetLightningHitProbability(type);
}

bool CObjectDamageableDetails::Read(CLevelParserLine* line)
{
    READ_LINE( "SetObjectDamageable" );
    READ_ARG( "enabled",      AsBool,     enabled );
    READ_ARG( "effect",       AsPyroType, effect  );
    READ_END();

    READ_LINE( "SetObjectDamageableFire" );
    READ_ARG( "enabled",      AsBool,     fire.enabled );
    READ_END();

    READ_LINE( "SetObjectDamageableOrganic" );
    READ_ARG( "enabled",      AsBool,     organic.enabled   );
    READ_ARG( "byInsects",    AsBool,     organic.byInsects );
    READ_ARG( "byRobots",     AsBool,     organic.byRobots  );
    READ_END();

    READ_LINE( "SetObjectDamageablePhazer" );
    READ_ARG( "enabled",      AsBool,     phazer.enabled         );
    READ_END();

    READ_LINE( "SetObjectDamageableTower" );
    READ_ARG( "enabled",      AsBool,     tower.enabled          );
    READ_END();

    READ_LINE( "SetObjectDamageableWasp" );
    READ_ARG( "enabled",      AsBool,     fallingObject.enabled  );
    READ_END();

    READ_LINE( "SetObjectDamageableExplosive" );
    READ_ARG( "enabled",      AsBool,     explosive.enabled      );
    READ_END();

    READ_LINE( "SetObjectDamageableCollision" );
    READ_ARG( "enabled",      AsBool,     collision.enabled      );
    READ_ARG( "byItself",     AsBool,     collision.byItself     );
    READ_ARG( "byOthers",     AsBool,     collision.byOthers     );
    READ_ARG( "ignoreRadius", AsFloat,    collision.ignoreRadius );
    READ_ARG( "resistance",   AsFloat,    collision.resistance   );
    READ_END();

    READ_LINE( "SetObjectDamageableLightning" );
    READ_ARG( "enabled",      AsBool,     lightning.enabled                 );
    READ_ARG( "height",       AsFloat,    lightning.lightningRodHeight      );
    READ_ARG( "probability",  AsFloat,    lightning.lightningHitProbability );
    READ_END();

    READ_LINE( "SetObjectDamageableFall" );
    READ_ARG( "enabled",      AsBool,     fall.enabled           );
    READ_END();

    READ_LINE( "SetObjectDamageableSpider" );
    READ_ARG( "enabled",      AsBool,     spider.enabled         );
    READ_END();

    return false;
}

void CObjectDamageableDetails::Write(CLevelParser* parser, ObjectType type)
{
    WRITE_LINE( "SetObjectDamageable" );
    WRITE_ARG( "enabled",      AsBool,     enabled );
    WRITE_ARG( "effect",       AsPyroType, effect  );
    WRITE_END();

    WRITE_LINE( "SetObjectDamageableFire" );
    WRITE_ARG( "enabled",      AsBool,     fire.enabled );
    WRITE_END();

    WRITE_LINE( "SetObjectDamageableOrganic" );
    WRITE_ARG( "enabled",      AsBool,     organic.enabled   );
    WRITE_ARG( "byInsects",    AsBool,     organic.byInsects );
    WRITE_ARG( "byRobots",     AsBool,     organic.byRobots  );
    WRITE_END();

    WRITE_LINE( "SetObjectDamageablePhazer" );
    WRITE_ARG( "enabled",      AsBool,     phazer.enabled         );
    WRITE_END();

    WRITE_LINE( "SetObjectDamageableTower" );
    WRITE_ARG( "enabled",      AsBool,     tower.enabled          );
    WRITE_END();

    WRITE_LINE( "SetObjectDamageableWasp" );
    WRITE_ARG( "enabled",      AsBool,     fallingObject.enabled  );
    WRITE_END();

    WRITE_LINE( "SetObjectDamageableExplosive" );
    WRITE_ARG( "enabled",      AsBool,     explosive.enabled      );
    WRITE_END();

    WRITE_LINE( "SetObjectDamageableCollision" );
    WRITE_ARG( "enabled",      AsBool,     collision.enabled      );
    WRITE_ARG( "byItself",     AsBool,     collision.byItself     );
    WRITE_ARG( "byOthers",     AsBool,     collision.byOthers     );
    WRITE_ARG( "ignoreRadius", AsFloat,    collision.ignoreRadius );
    WRITE_ARG( "resistance",   AsFloat,    collision.resistance   );
    WRITE_END();

    WRITE_LINE( "SetObjectDamageableLightning" );
    WRITE_ARG( "enabled",      AsBool,     lightning.enabled                 );
    WRITE_ARG( "height",       AsFloat,    lightning.lightningRodHeight      );
    WRITE_ARG( "probability",  AsFloat,    lightning.lightningHitProbability );
    WRITE_END();

    WRITE_LINE( "SetObjectDamageableFall" );
    WRITE_ARG( "enabled",      AsBool,     fall.enabled           );
    WRITE_END();

    WRITE_LINE( "SetObjectDamageableSpider" );
    WRITE_ARG( "enabled",      AsBool,     spider.enabled         );
    WRITE_END();
}
