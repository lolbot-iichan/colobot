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

#include <glm/glm.hpp>

#include "math/const.h"

#include "object/object_type.h"
#include "object/details/slotted_details.h"

#include "object/hardcode/slotted_hardcode.h"

#include "object/interface/slotted_object.h"

bool CSlottedHardcodeCollection::IsSlotted(ObjectType type)
{
    return GetSlots(type).size() > 0;
}

bool CSlottedHardcodeCollection::IsCreatedWithBattery(ObjectType type)
{
    if ( type == OBJECT_MOBILEwa ||
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
         type == OBJECT_MOBILEdr ) return true;

    return false;
}

std::vector<CObjectSlotDetails> CSlottedHardcodeCollection::GetSlots(ObjectType type)
{
    std::vector<CObjectSlotDetails> result;

    if ( type == OBJECT_MOBILEwa ||
         type == OBJECT_MOBILEwb ||
         type == OBJECT_MOBILEwc ||
         type == OBJECT_MOBILEwi ||
         type == OBJECT_MOBILEws ||
         type == OBJECT_MOBILEwt || // wheels?
         type == OBJECT_MOBILEtg || // target?
         type == OBJECT_MOBILEta ||
         type == OBJECT_MOBILEtb ||
         type == OBJECT_MOBILEtc ||
         type == OBJECT_MOBILEti ||
         type == OBJECT_MOBILEts ||
         type == OBJECT_MOBILEtt || // caterpillars?
         type == OBJECT_MOBILEia ||
         type == OBJECT_MOBILEib ||
         type == OBJECT_MOBILEic ||
         type == OBJECT_MOBILEii ||
         type == OBJECT_MOBILEis ||
         type == OBJECT_MOBILEit || // legs?
         type == OBJECT_MOBILEfa ||
         type == OBJECT_MOBILEfb ||
         type == OBJECT_MOBILEfc ||
         type == OBJECT_MOBILEfi ||
         type == OBJECT_MOBILEfs ||
         type == OBJECT_MOBILEft )  // flying?
    {
        result.push_back({SLOT_POWER, 0, {-3.2f, 3.0f, 0.0f}, {0,0,0}, Math::PI, 45.0f*Math::PI/180.0f});
    }
    if ( type == OBJECT_MOBILErt ||
         type == OBJECT_MOBILErc ||
         type == OBJECT_MOBILErr ||
         type == OBJECT_MOBILErs ||
         type == OBJECT_MOBILErp)  // large caterpillars?
    {
        result.push_back({SLOT_POWER, 0, {-5.8f, 4.0f, 0.0f}, {0,0,0}, Math::PI, 45.0f*Math::PI/180.0f});
    }
    if ( type == OBJECT_MOBILEsa ||
         type == OBJECT_MOBILEst )
    {
        result.push_back({SLOT_POWER, 0, {-5.0f, 3.0f, 0.0f}, {0,0,0}, Math::PI, 45.0f*Math::PI/180.0f});
    }
    if ( type == OBJECT_MOBILEdr )
    {
//        result.push_back({SLOT_POWER, 0, {-5.0f, 3.0f, 0.0f}, {0,0,0}, Math::PI, 45.0f*Math::PI/180.0f});
    }

    if ( type == OBJECT_RESEARCH )
    {
        result.push_back({SLOT_POWER, 0, {7.5f, 3.0f, 0.0f}, {0,0,0}, 0.0f, 45.0f*Math::PI/180.0f});
    }
    if ( type == OBJECT_TOWER )
    {
        result.push_back({SLOT_POWER, 0, {5.0f, 3.0f, 0.0f}, {0,0,0}, 0.0f, 45.0f*Math::PI/180.0f});
    }

    switch( type )
    {
        case OBJECT_HUMAN:
        case OBJECT_TECH:
            result.push_back({SLOT_CARGO, 4, {1.7f, -0.5f, 1.1f}, {0.0f, 0.1f, 0.8f}, 0.0f, 0.0f});
            break;
        case OBJECT_BEE:
            result.push_back({SLOT_CARGO, 0, {0.0f, -3.0f, 0.0f}, {0,0,0}, 0.0f, 0.0f});
            break;
        case OBJECT_MOBILEsa: // subber
            result.push_back({SLOT_CARGO, 2, {1.1f, -1.0f, 1.0f}, {0,0,0}, 0.0f, 0.0f});
            break;
        case OBJECT_MOBILEfa: // Grabbers
        case OBJECT_MOBILEta:
        case OBJECT_MOBILEwa:
        case OBJECT_MOBILEia:
//??        // This is just wrong - cargo turns 90 degrees when grabbed
//??        result.push_back({SLOT_CARGO, 3, {4.7f, 0.0f, 0.0f}, {0,0,Math::PI/2.0f}, 0.0f, 0.0f});
            result.push_back({SLOT_CARGO, 3, {4.7f, 0.0f, 0.0f}, {-Math::PI/2.0f,Math::PI/2.0f,0.0f}, 0.0f, 0.0f});
            break;
        default:
            break;
    }

    if ( type == OBJECT_ENERGY )
    {
        result.push_back({SLOT_OTHER, 0, {0.0f, 3.0f, 0.0f}, {0,0,0}, 0.0f, 90.0f*Math::PI/180.0f});
    }
    if ( type == OBJECT_LABO )
    {
        result.push_back({SLOT_OTHER, 0, {0.0f, 3.0f, 0.0f}, {0,0,0}, 0.0f, 120.0f*Math::PI/180.0f});
    }
    if ( type == OBJECT_NUCLEAR )
    {
        result.push_back({SLOT_OTHER, 0, {22.0f, 3.0f, 0.0f}, {0,0,0}, 0.0f, 45.0f*Math::PI/180.0f});
    }

    if ( type == OBJECT_SAFE )
    {
        result.push_back({SLOT_OTHER, 0, {-16.0f, 1.0f,   0.0f}, {0,0,0}, 0.0f, 150.0f*Math::PI/180.0f});
        result.push_back({SLOT_OTHER, 0, { 16.0f, 1.0f,   0.0f}, {0,0,0}, 0.0f, 150.0f*Math::PI/180.0f});
        result.push_back({SLOT_OTHER, 0, {  0.0f, 1.0f, -16.0f}, {0,0,0}, 0.0f, 150.0f*Math::PI/180.0f});
        result.push_back({SLOT_OTHER, 0, {  0.0f, 1.0f,  16.0f}, {0,0,0}, 0.0f, 150.0f*Math::PI/180.0f});
    }

    return result;
}
