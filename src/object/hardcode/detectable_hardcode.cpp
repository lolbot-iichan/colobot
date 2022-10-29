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

#include "math/sphere.h"

#include "object/object_type.h"

#include "object/details/detectable_details.h"

#include "object/hardcode/detectable_hardcode.h"

bool CDetectableHardcodeCollection::IsRadarExplicitOnly(ObjectType type)
{
    return (type == OBJECT_TOTO || type == OBJECT_CONTROLLER);
}

ObjectType CDetectableHardcodeCollection::GetBaseType(ObjectType type)
{
    if ( type == OBJECT_RUINmobilew2 ||
        type == OBJECT_RUINmobilet1 ||
        type == OBJECT_RUINmobilet2 ||
        type == OBJECT_RUINmobiler1 ||
        type == OBJECT_RUINmobiler2 )
    {
        return OBJECT_RUINmobilew1;  // any wreck
    }

    if ( type == OBJECT_BARRIER2 ||
         type == OBJECT_BARRIER3 ||
         type == OBJECT_BARRICADE0 ||
         type == OBJECT_BARRICADE1 )  // barriers?
    {
        return OBJECT_BARRIER1;  // any barrier
    }

    if ( type == OBJECT_RUINdoor    ||
         type == OBJECT_RUINsupport ||
         type == OBJECT_RUINradar   ||
         type == OBJECT_RUINconvert )  // ruins?
    {
        return OBJECT_RUINfactory;  // any ruin
    }

    if ( type == OBJECT_PLANT1  ||
         type == OBJECT_PLANT2  ||
         type == OBJECT_PLANT3  ||
         type == OBJECT_PLANT4  ||
         type == OBJECT_PLANT15 ||
         type == OBJECT_PLANT16 ||
         type == OBJECT_PLANT17 ||
         type == OBJECT_PLANT18 )  // bushes?
    {
        return OBJECT_PLANT0;  // any bush
    }

    if ( type == OBJECT_QUARTZ1 ||
         type == OBJECT_QUARTZ2 ||
         type == OBJECT_QUARTZ3 )  // crystals?
    {
        return OBJECT_QUARTZ0;  // any crystal
    }

    return OBJECT_NULL;
}

bool CDetectableHardcodeCollection::GetMapShowEvenUnselectable(ObjectType type)
{
    if ( type == OBJECT_MOTHER   ||
         type == OBJECT_ANT      ||
         type == OBJECT_SPIDER   ||
         type == OBJECT_BEE      ||
         type == OBJECT_WORM     ||
         type == OBJECT_MOBILEtg ) return true;

    return false;
}

MapColor CDetectableHardcodeCollection::GetMapIconColor(ObjectType type)
{
    MapColor color = MAPCOLOR_NULL;
    if ( type == OBJECT_BASE )
    {
        color = MAPCOLOR_BASE;
    }
    if ( type == OBJECT_DERRICK  ||
         type == OBJECT_FACTORY  ||
         type == OBJECT_STATION  ||
         type == OBJECT_CONVERT  ||
         type == OBJECT_REPAIR   ||
         type == OBJECT_DESTROYER||
         type == OBJECT_TOWER    ||
         type == OBJECT_RESEARCH ||
         type == OBJECT_RADAR    ||
         type == OBJECT_INFO     ||
         type == OBJECT_ENERGY   ||
         type == OBJECT_LABO     ||
         type == OBJECT_NUCLEAR  ||
         type == OBJECT_PARA     ||
         type == OBJECT_SAFE     ||
         type == OBJECT_HUSTON   ||
         type == OBJECT_TARGET1  ||
         type == OBJECT_START    ||
         type == OBJECT_END      ||  // stationary object?
         type == OBJECT_TEEN28    ||  // bottle?
         type == OBJECT_TEEN34    )   // stone?
    {
        color = MAPCOLOR_FIX;
    }
    if ( type == OBJECT_BBOX ||
         type == OBJECT_KEYa ||
         type == OBJECT_KEYb ||
         type == OBJECT_KEYc ||
         type == OBJECT_KEYd )
    {
        color = MAPCOLOR_BBOX;
    }
    if ( type == OBJECT_HUMAN    ||
         type == OBJECT_MOBILEwa ||
         type == OBJECT_MOBILEta ||
         type == OBJECT_MOBILEfa ||
         type == OBJECT_MOBILEia ||
         type == OBJECT_MOBILEwb ||
         type == OBJECT_MOBILEtb ||
         type == OBJECT_MOBILEfb ||
         type == OBJECT_MOBILEib ||
         type == OBJECT_MOBILEwc ||
         type == OBJECT_MOBILEtc ||
         type == OBJECT_MOBILEfc ||
         type == OBJECT_MOBILEic ||
         type == OBJECT_MOBILEwi ||
         type == OBJECT_MOBILEti ||
         type == OBJECT_MOBILEfi ||
         type == OBJECT_MOBILEii ||
         type == OBJECT_MOBILEws ||
         type == OBJECT_MOBILEts ||
         type == OBJECT_MOBILEfs ||
         type == OBJECT_MOBILEis ||
         type == OBJECT_MOBILErt ||
         type == OBJECT_MOBILErc ||
         type == OBJECT_MOBILErr ||
         type == OBJECT_MOBILErs ||
         type == OBJECT_MOBILEsa ||
         type == OBJECT_MOBILEtg ||
         type == OBJECT_MOBILEwt ||
         type == OBJECT_MOBILEtt ||
         type == OBJECT_MOBILEft ||
         type == OBJECT_MOBILEit ||
         type == OBJECT_MOBILErp ||
         type == OBJECT_MOBILEst ||
         type == OBJECT_MOBILEdr ||
         type == OBJECT_APOLLO2  )  // moving vehicle?
    {
        color = MAPCOLOR_MOVE;
    }
    if ( type == OBJECT_ANT      ||
         type == OBJECT_BEE      ||
         type == OBJECT_WORM     ||
         type == OBJECT_SPIDER   )  // mobile enemy?
    {
        color = MAPCOLOR_ALIEN;
    }
    if ( type == OBJECT_WAYPOINT ||
         type == OBJECT_FLAGb    )
    {
        color = MAPCOLOR_WAYPOINTb;
    }
    if ( type == OBJECT_FLAGr )
    {
        color = MAPCOLOR_WAYPOINTr;
    }
    if ( type == OBJECT_FLAGg )
    {
        color = MAPCOLOR_WAYPOINTg;
    }
    if ( type == OBJECT_FLAGy )
    {
        color = MAPCOLOR_WAYPOINTy;
    }
    if ( type == OBJECT_FLAGv )
    {
        color = MAPCOLOR_WAYPOINTv;
    }
    return color;
}

int CDetectableHardcodeCollection::GetMapIcon(ObjectType type)
{
    int icon = -1;
    switch ( type )
    {
        case OBJECT_FACTORY:    icon = 32; break;
        case OBJECT_DERRICK:    icon = 33; break;
        case OBJECT_CONVERT:    icon = 34; break;
        case OBJECT_RESEARCH:   icon = 35; break;
        case OBJECT_STATION:    icon = 36; break;
        case OBJECT_TOWER:      icon = 37; break;
        case OBJECT_LABO:       icon = 38; break;
        case OBJECT_ENERGY:     icon = 39; break;
        case OBJECT_RADAR:      icon = 40; break;
        case OBJECT_INFO:       icon = 44; break;
        case OBJECT_REPAIR:     icon = 41; break;
        case OBJECT_DESTROYER:  icon = 41; break;
        case OBJECT_NUCLEAR:    icon = 42; break;
        case OBJECT_PARA:       icon = 46; break;
        case OBJECT_SAFE:       icon = 47; break;
        case OBJECT_HUSTON:     icon = 48; break;
        case OBJECT_TARGET1:    icon = 45; break;
        case OBJECT_BASE:       icon = 43; break;

        case OBJECT_HUMAN:      icon =  8; break;
        case OBJECT_MOBILEfa:   icon = 11; break;
        case OBJECT_MOBILEta:   icon = 10; break;
        case OBJECT_MOBILEwa:   icon =  9; break;
        case OBJECT_MOBILEia:   icon = 22; break;
        case OBJECT_MOBILEfb:   icon =  2; break; // button4
        case OBJECT_MOBILEtb:   icon =  1; break;
        case OBJECT_MOBILEwb:   icon =  0; break;
        case OBJECT_MOBILEib:   icon =  3; break;
        case OBJECT_MOBILEfc:   icon = 17; break;
        case OBJECT_MOBILEtc:   icon = 16; break;
        case OBJECT_MOBILEwc:   icon = 15; break;
        case OBJECT_MOBILEic:   icon = 23; break;
        case OBJECT_MOBILEfi:   icon = 27; break;
        case OBJECT_MOBILEti:   icon = 26; break;
        case OBJECT_MOBILEwi:   icon = 25; break;
        case OBJECT_MOBILEii:   icon = 28; break;
        case OBJECT_MOBILEfs:   icon = 14; break;
        case OBJECT_MOBILEts:   icon = 13; break;
        case OBJECT_MOBILEws:   icon = 12; break;
        case OBJECT_MOBILEis:   icon = 24; break;
        case OBJECT_MOBILErt:   icon = 18; break;
        case OBJECT_MOBILErc:   icon = 19; break;
        case OBJECT_MOBILErr:   icon = 20; break;
        case OBJECT_MOBILErs:   icon = 29; break;
        case OBJECT_MOBILEsa:   icon = 21; break;
        case OBJECT_MOBILEft:   icon =  6; break;
        case OBJECT_MOBILEtt:   icon =  5; break;
        case OBJECT_MOBILEwt:   icon = 30; break;
        case OBJECT_MOBILEit:   icon =  7; break;
        case OBJECT_MOBILErp:   icon =  9; break;
        case OBJECT_MOBILEst:   icon = 10; break;
        case OBJECT_MOBILEtg:   icon = 45; break;
        case OBJECT_MOBILEdr:   icon = 48; break;
        case OBJECT_APOLLO2:    icon = 49; break;

        case OBJECT_MOTHER:     icon = 31; break;
        case OBJECT_ANT:        icon = 31; break;
        case OBJECT_SPIDER:     icon = 31; break;
        case OBJECT_BEE:        icon = 31; break;
        case OBJECT_WORM:       icon = 31; break;
        case OBJECT_TEEN28:     icon = 48; break;  // bottle
        case OBJECT_TEEN34:     icon = 48; break;  // stone
        default:                return -1;
    }

    switch ( type )
    {
        case OBJECT_MOBILEfb:
        case OBJECT_MOBILEtb:
        case OBJECT_MOBILEwb:
        case OBJECT_MOBILEib:
        case OBJECT_MOBILEft:
        case OBJECT_MOBILEtt:
        case OBJECT_MOBILEit:
        case OBJECT_MOBILErp:
        case OBJECT_MOBILEst:
            return 192+icon;
        default:
            return 128+icon;
    }
}
