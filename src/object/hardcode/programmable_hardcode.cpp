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

#include "object/object_type.h"

#include "object/hardcode/programmable_hardcode.h"

bool CProgrammableHardcodeCollection::IsProgrammable(ObjectType type)
{
    if ( type == OBJECT_HUMAN ) return true;
    if ( type == OBJECT_TECH ) return true;
    if ( type == OBJECT_MOTHER ) return true;
    if ( type == OBJECT_ANT ) return true;
    if ( type == OBJECT_SPIDER ) return true;
    if ( type == OBJECT_BEE ) return true;
    if ( type == OBJECT_WORM ) return true;
    if ( type == OBJECT_TOTO ) return true;
    if ( type == OBJECT_CONTROLLER ) return true;
    if ( type == OBJECT_APOLLO2 ) return true;
    if ( type == OBJECT_MOBILEdr ) return true;
    if ( type == OBJECT_MOBILEsa ||
         type == OBJECT_MOBILEst ) return true;
    if ( type == OBJECT_MOBILErt ||
         type == OBJECT_MOBILErc ||
         type == OBJECT_MOBILErr ||
         type == OBJECT_MOBILErs ||
         type == OBJECT_MOBILErp) return true;
    if ( type == OBJECT_MOBILEfa ||
         type == OBJECT_MOBILEfb ||
         type == OBJECT_MOBILEfc ||
         type == OBJECT_MOBILEfi ||
         type == OBJECT_MOBILEfs ||
         type == OBJECT_MOBILEft ) return true;
    if ( type == OBJECT_MOBILEia ||
         type == OBJECT_MOBILEib ||
         type == OBJECT_MOBILEic ||
         type == OBJECT_MOBILEii ||
         type == OBJECT_MOBILEis ||
         type == OBJECT_MOBILEit) return true;
    if ( type == OBJECT_MOBILEta ||
         type == OBJECT_MOBILEtb ||
         type == OBJECT_MOBILEtc ||
         type == OBJECT_MOBILEti ||
         type == OBJECT_MOBILEts ||
         type == OBJECT_MOBILEtt ) return true;
    if ( type == OBJECT_MOBILEtg ) return true;
    if ( type == OBJECT_MOBILEwa ||
         type == OBJECT_MOBILEwb ||
         type == OBJECT_MOBILEwc ||
         type == OBJECT_MOBILEwi ||
         type == OBJECT_MOBILEws ||
         type == OBJECT_MOBILEwt ) return true;

    return false;
}

bool CProgrammableHardcodeCollection::GetNoSaveState(ObjectType type)
{
    if ( type == OBJECT_HUMAN ) return true;

    return false;
}
bool CProgrammableHardcodeCollection::IsFunctionImplementedBuild(ObjectType type)
{
    if ( type != OBJECT_MOBILEfb &&  // allowed only for builder bots && humans
         type != OBJECT_MOBILEtb &&
         type != OBJECT_MOBILEwb &&
         type != OBJECT_MOBILEib &&
         type != OBJECT_HUMAN    &&
         type != OBJECT_TECH      ) return false;
    return true;
}

bool CProgrammableHardcodeCollection::IsFunctionImplementedFlags(ObjectType type)
{
    if ( type != OBJECT_MOBILEfs &&  // allowed only for sniffer bots && humans
         type != OBJECT_MOBILEts &&
         type != OBJECT_MOBILEws &&
         type != OBJECT_MOBILEis &&
         type != OBJECT_HUMAN    &&
         type != OBJECT_TECH      ) return false;
    return true;
}

bool CProgrammableHardcodeCollection::IsFunctionImplementedSniff(ObjectType type)
{
    if ( type == OBJECT_MOBILEfs || // allowed only for sniffer bots && humans
         type == OBJECT_MOBILEts ||
         type == OBJECT_MOBILEws ||
         type == OBJECT_MOBILEis ) return true;
    return false;
}

bool CProgrammableHardcodeCollection::IsFunctionImplementedShield(ObjectType type)
{
    return type == OBJECT_MOBILErs;
}

bool CProgrammableHardcodeCollection::IsFunctionImplementedRecycle(ObjectType type)
{
    return type == OBJECT_MOBILErr;
}

bool CProgrammableHardcodeCollection::IsFunctionImplementedThump(ObjectType type)
{
    return type == OBJECT_MOBILErt;
}

bool CProgrammableHardcodeCollection::IsFunctionImplementedDrawAsRobot(ObjectType type)
{
    return type == OBJECT_MOBILEdr;
}

bool CProgrammableHardcodeCollection::IsFunctionImplementedGrabAsHuman(ObjectType type)
{
    if ( type == OBJECT_HUMAN ||
         type == OBJECT_TECH ) return true;
    return false;
}

bool CProgrammableHardcodeCollection::IsFunctionImplementedGrabAsRobot(ObjectType type)
{
    if ( (type == OBJECT_MOBILEfa ||
          type == OBJECT_MOBILEta ||
          type == OBJECT_MOBILEwa ||
          type == OBJECT_MOBILEia ) )   return true;

    if ( (type == OBJECT_MOBILEsa ||
          type == OBJECT_BEE ) )   return true;

    return false;
}

bool CProgrammableHardcodeCollection::IsFunctionImplementedShootAsAnt(ObjectType type)
{
    return type == OBJECT_ANT;
}

bool CProgrammableHardcodeCollection::IsFunctionImplementedShootAsSpider(ObjectType type)
{
    return type == OBJECT_SPIDER;
}

bool CProgrammableHardcodeCollection::IsFunctionImplementedShootAsRobot(ObjectType type)
{
    if ( type == OBJECT_MOBILEfc ||
         type == OBJECT_MOBILEtc ||
         type == OBJECT_MOBILEwc ||
         type == OBJECT_MOBILEic ||
         type == OBJECT_MOBILEfi ||
         type == OBJECT_MOBILEti ||
         type == OBJECT_MOBILEwi ||
         type == OBJECT_MOBILEii ||
         type == OBJECT_MOBILErc ) return true;

    return false;
}
