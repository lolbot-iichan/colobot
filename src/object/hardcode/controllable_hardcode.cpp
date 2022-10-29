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

#include "common/event.h"

#include "object/object_type.h"

#include "object/details/controllable_details.h"

#include "object/hardcode/controllable_hardcode.h"

/* Macro to mark which texts are translatable by gettext
 * It doesn't do anything at compile-time, as all texts represented here are used later
 * in explicit call to gettext(), but it is used by xgettext executable to filter extracted
 * texts from this file.
 */
#define TR(x) x

/* Please run `cmake --build <path_to_build_folder> --target update-pot`
 * after changing this file in order to update translation files. Thank you.
 */

bool CControllableHardcodeCollection::IsControllable(ObjectType type)
{
    // TODO: You have been hacked!
    if (type == OBJECT_HUMAN    ||
        type == OBJECT_TOTO     ||
        type == OBJECT_MOBILEfa ||
        type == OBJECT_MOBILEta ||
        type == OBJECT_MOBILEwa ||
        type == OBJECT_MOBILEia ||
        type == OBJECT_MOBILEfb ||
        type == OBJECT_MOBILEtb ||
        type == OBJECT_MOBILEwb ||
        type == OBJECT_MOBILEib ||
        type == OBJECT_MOBILEfc ||
        type == OBJECT_MOBILEtc ||
        type == OBJECT_MOBILEwc ||
        type == OBJECT_MOBILEic ||
        type == OBJECT_MOBILEfi ||
        type == OBJECT_MOBILEti ||
        type == OBJECT_MOBILEwi ||
        type == OBJECT_MOBILEii ||
        type == OBJECT_MOBILEfs ||
        type == OBJECT_MOBILEts ||
        type == OBJECT_MOBILEws ||
        type == OBJECT_MOBILEis ||
        type == OBJECT_MOBILErt ||
        type == OBJECT_MOBILErc ||
        type == OBJECT_MOBILErr ||
        type == OBJECT_MOBILErs ||
        type == OBJECT_MOBILEsa ||
        type == OBJECT_MOBILEft ||
        type == OBJECT_MOBILEtt ||
        type == OBJECT_MOBILEwt ||
        type == OBJECT_MOBILEit ||
        type == OBJECT_MOBILErp ||
        type == OBJECT_MOBILEst ||
        type == OBJECT_MOBILEtg ||
        type == OBJECT_MOBILEdr ||
        type == OBJECT_APOLLO2  ||
        type == OBJECT_BASE     ||
        type == OBJECT_DERRICK  ||
        type == OBJECT_FACTORY  ||
        type == OBJECT_REPAIR   ||
        type == OBJECT_DESTROYER||
        type == OBJECT_STATION  ||
        type == OBJECT_CONVERT  ||
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
        type == OBJECT_ANT      ||
        type == OBJECT_WORM     ||
        type == OBJECT_SPIDER   ||
        type == OBJECT_BEE      ||
        type == OBJECT_MOTHER   ||
        type == OBJECT_CONTROLLER) return true;
    return false;
}

bool CControllableHardcodeCollection::IsSelectableByDefault(ObjectType type)
{
    if ( type == OBJECT_MOTHER   ||
         type == OBJECT_ANT      ||
         type == OBJECT_SPIDER   ||
         type == OBJECT_BEE      ||
         type == OBJECT_WORM     )
    {
        return false;
    }
    return true;
}

bool CControllableHardcodeCollection::IsInfectable(ObjectType type)
{
    if ( type != OBJECT_MOBILEfa &&
         type != OBJECT_MOBILEta &&
         type != OBJECT_MOBILEwa &&
         type != OBJECT_MOBILEia &&
         type != OBJECT_MOBILEfb &&
         type != OBJECT_MOBILEtb &&
         type != OBJECT_MOBILEwb &&
         type != OBJECT_MOBILEib &&
         type != OBJECT_MOBILEfc &&
         type != OBJECT_MOBILEtc &&
         type != OBJECT_MOBILEwc &&
         type != OBJECT_MOBILEic &&
         type != OBJECT_MOBILEfi &&
         type != OBJECT_MOBILEti &&
         type != OBJECT_MOBILEwi &&
         type != OBJECT_MOBILEii &&
         type != OBJECT_MOBILEfs &&
         type != OBJECT_MOBILEts &&
         type != OBJECT_MOBILEws &&
         type != OBJECT_MOBILEis &&
         type != OBJECT_MOBILErt &&
         type != OBJECT_MOBILErc &&
         type != OBJECT_MOBILErr &&
         type != OBJECT_MOBILErs &&
         type != OBJECT_MOBILEsa &&
         type != OBJECT_MOBILEtg &&
         type != OBJECT_MOBILEft &&
         type != OBJECT_MOBILEtt &&
         type != OBJECT_MOBILEwt &&
         type != OBJECT_MOBILEit &&
         type != OBJECT_MOBILErp &&
         type != OBJECT_MOBILEst &&
         type != OBJECT_MOBILEdr &&
         type != OBJECT_DERRICK  &&
         type != OBJECT_STATION  &&
         type != OBJECT_FACTORY  &&
         type != OBJECT_REPAIR   &&
         type != OBJECT_DESTROYER &&
         type != OBJECT_CONVERT  &&
         type != OBJECT_TOWER    &&
         type != OBJECT_RESEARCH &&
         type != OBJECT_RADAR    &&
         type != OBJECT_INFO     &&
         type != OBJECT_ENERGY   &&
         type != OBJECT_LABO     &&
         type != OBJECT_NUCLEAR  &&
         type != OBJECT_PARA     &&
         type != OBJECT_SAFE     &&
         type != OBJECT_HUSTON   )  return false;

    return true;
}

bool CControllableHardcodeCollection::IsTrainable(ObjectType type)
{
    if ( type == OBJECT_HUMAN ||
         type == OBJECT_TECH  ) return false;

    return true;
}

std::vector<CObjectControlLightsDetails> CControllableHardcodeCollection::GetControlLights(ObjectType type)
{
    std::vector<CObjectControlLightsDetails> result;

    if ( type == OBJECT_MOBILErt ||
         type == OBJECT_MOBILErc ||
         type == OBJECT_MOBILErr ||
         type == OBJECT_MOBILErs ||
         type == OBJECT_MOBILErp )  // large caterpillars?
    {
        result.push_back({Gfx::PARTISELY, glm::vec3(4.2f, 2.8f,  1.5f), 0, 1.5f});
        result.push_back({Gfx::PARTISELY, glm::vec3(4.2f, 2.8f, -1.5f), 0, 1.5f});
    }
    else if ( type == OBJECT_MOBILEsa ||
              type == OBJECT_MOBILEst )  // submarine?
    {
        result.push_back({Gfx::PARTISELY, glm::vec3( 3.6f, 4.0f,  2.0f), 0, 1.0f});
        result.push_back({Gfx::PARTISELY, glm::vec3( 3.6f, 4.0f, -2.0f), 0, 1.0f});
    }
    else if ( type == OBJECT_MOBILEtg )  // target?
    {
        result.push_back({Gfx::PARTISELY, glm::vec3( 3.4f, 6.5f,  2.0f), 0, 1.0f});
        result.push_back({Gfx::PARTISELY, glm::vec3( 3.4f, 6.5f, -2.0f), 0, 1.0f});
    }
    else if ( type == OBJECT_MOBILEdr )  // designer?
    {
        result.push_back({Gfx::PARTISELY, glm::vec3( 4.9f, 3.5f,  2.5f), 0, 1.0f});
        result.push_back({Gfx::PARTISELY, glm::vec3( 4.9f, 3.5f, -2.5f), 0, 1.0f});
    }
    else if ( type == OBJECT_MOBILEwt ||
              type == OBJECT_MOBILEtt ||
              type == OBJECT_MOBILEft ||
              type == OBJECT_MOBILEit)                // trainer ?
    {
        result.push_back({Gfx::PARTISELY, glm::vec3(4.2f, 2.5f,  1.2f), 0, 1.5f});
        result.push_back({Gfx::PARTISELY, glm::vec3(4.2f, 2.5f, -1.2f), 0, 1.5f});
    }
    else if ( type == OBJECT_MOBILEfa ||
              type == OBJECT_MOBILEta ||
              type == OBJECT_MOBILEwa ||
              type == OBJECT_MOBILEia ||
              type == OBJECT_MOBILEfb ||
              type == OBJECT_MOBILEtb ||
              type == OBJECT_MOBILEwb ||
              type == OBJECT_MOBILEib ||
              type == OBJECT_MOBILEfc ||
              type == OBJECT_MOBILEtc ||
              type == OBJECT_MOBILEwc ||
              type == OBJECT_MOBILEic ||
              type == OBJECT_MOBILEfi ||
              type == OBJECT_MOBILEti ||
              type == OBJECT_MOBILEwi ||
              type == OBJECT_MOBILEii ||
              type == OBJECT_MOBILEfs ||
              type == OBJECT_MOBILEts ||
              type == OBJECT_MOBILEws ||
              type == OBJECT_MOBILEis )
    {
        result.push_back({Gfx::PARTISELY, glm::vec3(4.2f, 2.5f,  1.5f), 0, 1.0f, PART_TRAINER_FALSE|PART_OPTION_ANY});
        result.push_back({Gfx::PARTISELY, glm::vec3(4.2f, 2.5f, -1.5f), 0, 1.0f, PART_TRAINER_FALSE|PART_OPTION_ANY});
        result.push_back({Gfx::PARTISELY, glm::vec3(4.2f, 2.5f,  1.2f), 0, 1.5f, PART_TRAINER_TRUE|PART_OPTION_ANY});
        result.push_back({Gfx::PARTISELY, glm::vec3(4.2f, 2.5f, -1.2f), 0, 1.5f, PART_TRAINER_TRUE|PART_OPTION_ANY});
    }

    if ( type == OBJECT_MOBILEsa ||
         type == OBJECT_MOBILEst )  // submarine?
    {
        result.push_back({Gfx::PARTISELR, glm::vec3(-3.6f, 4.0f,  2.0f), 0, 1.2f});
        result.push_back({Gfx::PARTISELR, glm::vec3(-3.6f, 4.0f, -2.0f), 0, 1.2f});
    }
    else if ( type == OBJECT_MOBILEtg )  // target?
    {
        result.push_back({Gfx::PARTISELR, glm::vec3(-2.4f, 6.5f,  2.0f), 0, 1.2f});
        result.push_back({Gfx::PARTISELR, glm::vec3(-2.4f, 6.5f, -2.0f), 0, 1.2f});
    }
    else if ( type == OBJECT_MOBILEdr )  // designer?
    {
        result.push_back({Gfx::PARTISELR, glm::vec3(-5.3f, 2.7f,  1.8f), 0, 1.2f});
        result.push_back({Gfx::PARTISELR, glm::vec3(-5.3f, 2.7f, -1.8f), 0, 1.2f});
    }
    else if ( type == OBJECT_MOBILEwt ||
              type == OBJECT_MOBILEtt ||
              type == OBJECT_MOBILEft ||
              type == OBJECT_MOBILEit )  // trainer?
    {
        result.push_back({Gfx::PARTISELR, glm::vec3(-4.0f, 2.5f,  2.2f), 0, 1.2f});
        result.push_back({Gfx::PARTISELR, glm::vec3(-4.0f, 2.5f, -2.2f), 0, 1.2f});
    }
    else if ( type == OBJECT_MOBILErp )  // trainer?
    {
        result.push_back({Gfx::PARTISELR, glm::vec3(-4.6f, 5.2f,  2.6f), 0, 1.2f});
        result.push_back({Gfx::PARTISELR, glm::vec3(-4.6f, 5.2f, -2.6f), 0, 1.2f});
    }
    else if ( type == OBJECT_MOBILErt ||
              type == OBJECT_MOBILErc ||
              type == OBJECT_MOBILErr ||
              type == OBJECT_MOBILErs )  // large caterpillars?
    {
        result.push_back({Gfx::PARTISELR, glm::vec3(-5.0f, 5.2f,  2.5f), 0, 1.2f, PART_TRAINER_FALSE|PART_OPTION_ANY});
        result.push_back({Gfx::PARTISELR, glm::vec3(-5.0f, 5.2f, -2.5f), 0, 1.2f, PART_TRAINER_FALSE|PART_OPTION_ANY});
        result.push_back({Gfx::PARTISELR, glm::vec3(-4.6f, 5.2f,  2.6f), 0, 1.2f, PART_TRAINER_TRUE|PART_OPTION_ANY});
        result.push_back({Gfx::PARTISELR, glm::vec3(-4.6f, 5.2f, -2.6f), 0, 1.2f, PART_TRAINER_TRUE|PART_OPTION_ANY});
    }
    else if ( type == OBJECT_MOBILEfa ||
              type == OBJECT_MOBILEfb ||
              type == OBJECT_MOBILEfc ||
              type == OBJECT_MOBILEfi ||
              type == OBJECT_MOBILEfs )  // flying?
    {
        result.push_back({Gfx::PARTISELR, glm::vec3(-4.0f, 3.1f,  4.5f), 0, 0.6f, PART_TRAINER_FALSE|PART_OPTION_ANY});
        result.push_back({Gfx::PARTISELR, glm::vec3(-4.0f, 3.1f, -4.5f), 0, 0.6f, PART_TRAINER_FALSE|PART_OPTION_ANY});
        result.push_back({Gfx::PARTISELR, glm::vec3(-4.0f, 2.5f,  2.2f), 0, 1.2f, PART_TRAINER_TRUE|PART_OPTION_ANY});
        result.push_back({Gfx::PARTISELR, glm::vec3(-4.0f, 2.5f, -2.2f), 0, 1.2f, PART_TRAINER_TRUE|PART_OPTION_ANY});
    }
    else if ( type == OBJECT_MOBILEwa ||
              type == OBJECT_MOBILEwb ||
              type == OBJECT_MOBILEwc ||
              type == OBJECT_MOBILEwi ||
              type == OBJECT_MOBILEws )  // wheels?
    {
        result.push_back({Gfx::PARTISELR, glm::vec3(-4.5f, 2.7f,  2.8f), 0, 1.2f, PART_TRAINER_FALSE|PART_OPTION_ANY});
        result.push_back({Gfx::PARTISELR, glm::vec3(-4.5f, 2.7f, -2.8f), 0, 1.2f, PART_TRAINER_FALSE|PART_OPTION_ANY});
        result.push_back({Gfx::PARTISELR, glm::vec3(-4.0f, 2.5f,  2.2f), 0, 1.2f, PART_TRAINER_TRUE|PART_OPTION_ANY});
        result.push_back({Gfx::PARTISELR, glm::vec3(-4.0f, 2.5f, -2.2f), 0, 1.2f, PART_TRAINER_TRUE|PART_OPTION_ANY});
    }
    else if ( type == OBJECT_MOBILEia ||
              type == OBJECT_MOBILEib ||
              type == OBJECT_MOBILEic ||
              type == OBJECT_MOBILEii ||
              type == OBJECT_MOBILEis )  // legs?
    {
        result.push_back({Gfx::PARTISELR, glm::vec3(-4.5f, 2.7f,  2.8f), 0, 1.2f, PART_TRAINER_FALSE|PART_OPTION_ANY});
        result.push_back({Gfx::PARTISELR, glm::vec3(-4.5f, 2.7f, -2.8f), 0, 1.2f, PART_TRAINER_FALSE|PART_OPTION_ANY});
        result.push_back({Gfx::PARTISELR, glm::vec3(-4.0f, 2.5f,  2.2f), 0, 1.2f, PART_TRAINER_TRUE|PART_OPTION_ANY});
        result.push_back({Gfx::PARTISELR, glm::vec3(-4.0f, 2.5f, -2.2f), 0, 1.2f, PART_TRAINER_TRUE|PART_OPTION_ANY});
    }
    else if ( type == OBJECT_MOBILEta ||
              type == OBJECT_MOBILEtb ||
              type == OBJECT_MOBILEtc ||
              type == OBJECT_MOBILEti ||
              type == OBJECT_MOBILEts )  // caterpillars?
    {
        result.push_back({Gfx::PARTISELR, glm::vec3(-3.6f, 4.2f,  3.0f), 0, 1.2f, PART_TRAINER_FALSE|PART_OPTION_ANY});
        result.push_back({Gfx::PARTISELR, glm::vec3(-3.6f, 4.2f, -3.0f), 0, 1.2f, PART_TRAINER_FALSE|PART_OPTION_ANY});
        result.push_back({Gfx::PARTISELR, glm::vec3(-4.0f, 2.5f,  2.2f), 0, 1.2f, PART_TRAINER_TRUE|PART_OPTION_ANY});
        result.push_back({Gfx::PARTISELR, glm::vec3(-4.0f, 2.5f, -2.2f), 0, 1.2f, PART_TRAINER_TRUE|PART_OPTION_ANY});
    }

    return result;
}

bool CControllableHardcodeCollection::IsShortcutBuilding(ObjectType type)
{
    switch ( type )
    {
        case OBJECT_FACTORY:
        case OBJECT_DERRICK:
        case OBJECT_CONVERT:
        case OBJECT_RESEARCH:
        case OBJECT_STATION:
        case OBJECT_TOWER:
        case OBJECT_LABO:
        case OBJECT_ENERGY:
        case OBJECT_RADAR:
        case OBJECT_INFO:
        case OBJECT_REPAIR:
        case OBJECT_DESTROYER:
        case OBJECT_NUCLEAR:
        case OBJECT_PARA:
        case OBJECT_SAFE:
        case OBJECT_HUSTON:
        case OBJECT_BASE:
            return true;
        default:
            return false;
    }
}

bool CControllableHardcodeCollection::IsShortcutMovable(ObjectType type)
{
    switch ( type )
    {
        case OBJECT_HUMAN:
        case OBJECT_MOBILEfa:
        case OBJECT_MOBILEta:
        case OBJECT_MOBILEwa:
        case OBJECT_MOBILEia:
        case OBJECT_MOBILEfb:
        case OBJECT_MOBILEtb:
        case OBJECT_MOBILEwb:
        case OBJECT_MOBILEib:
        case OBJECT_MOBILEfc:
        case OBJECT_MOBILEtc:
        case OBJECT_MOBILEwc:
        case OBJECT_MOBILEic:
        case OBJECT_MOBILEfi:
        case OBJECT_MOBILEti:
        case OBJECT_MOBILEwi:
        case OBJECT_MOBILEii:
        case OBJECT_MOBILEfs:
        case OBJECT_MOBILEts:
        case OBJECT_MOBILEws:
        case OBJECT_MOBILEis:
        case OBJECT_MOBILErt:
        case OBJECT_MOBILErc:
        case OBJECT_MOBILErr:
        case OBJECT_MOBILErs:
        case OBJECT_MOBILEsa:
        case OBJECT_MOBILEft:
        case OBJECT_MOBILEtt:
        case OBJECT_MOBILEwt:
        case OBJECT_MOBILEit:
        case OBJECT_MOBILErp:
        case OBJECT_MOBILEst:
        case OBJECT_MOBILEtg:
        case OBJECT_MOBILEdr:
        case OBJECT_APOLLO2:
            return true;
        default:
            return false;
    }
}

int CControllableHardcodeCollection::GetShortcutIcon(ObjectType type)
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

bool CControllableHardcodeCollection::HasUserInterfaceProgramUI(ObjectType type)
{
    if ( type == OBJECT_MOBILEfa ||
         type == OBJECT_MOBILEta ||
         type == OBJECT_MOBILEwa ||
         type == OBJECT_MOBILEia ||
         type == OBJECT_MOBILEfb ||
         type == OBJECT_MOBILEtb ||
         type == OBJECT_MOBILEwb ||
         type == OBJECT_MOBILEib ||
         type == OBJECT_MOBILEfc ||
         type == OBJECT_MOBILEtc ||
         type == OBJECT_MOBILEwc ||
         type == OBJECT_MOBILEic ||
         type == OBJECT_MOBILEfi ||
         type == OBJECT_MOBILEti ||
         type == OBJECT_MOBILEwi ||
         type == OBJECT_MOBILEii ||
         type == OBJECT_MOBILEfs ||
         type == OBJECT_MOBILEts ||
         type == OBJECT_MOBILEws ||
         type == OBJECT_MOBILEis ||
         type == OBJECT_MOBILErt ||
         type == OBJECT_MOBILErc ||
         type == OBJECT_MOBILErr ||
         type == OBJECT_MOBILErs ||
         type == OBJECT_MOBILEsa ||
         type == OBJECT_MOBILEtg ||
         type == OBJECT_MOBILEft ||
         type == OBJECT_MOBILEtt ||
         type == OBJECT_MOBILEwt ||
         type == OBJECT_MOBILEit ||
         type == OBJECT_MOBILErp ||
         type == OBJECT_MOBILEst ||
         type == OBJECT_MOBILEdr ||
         type == OBJECT_MOTHER   ||
         type == OBJECT_ANT      ||
         type == OBJECT_SPIDER   ||
         type == OBJECT_BEE      ||
         type == OBJECT_WORM     ||
         type == OBJECT_CONTROLLER)  return true;

    return false;
}

bool CControllableHardcodeCollection::HasUserInterfaceProgramUIBlink(ObjectType type)
{
    if ( type == OBJECT_HUMAN    || // HUMAN ?!
         type == OBJECT_TECH     || // TECH ?!
         type == OBJECT_MOBILEfa ||
         type == OBJECT_MOBILEta ||
         type == OBJECT_MOBILEwa ||
         type == OBJECT_MOBILEia ||
         type == OBJECT_MOBILEfb ||
         type == OBJECT_MOBILEtb ||
         type == OBJECT_MOBILEwb ||
         type == OBJECT_MOBILEib ||
         type == OBJECT_MOBILEfc ||
         type == OBJECT_MOBILEtc ||
         type == OBJECT_MOBILEwc ||
         type == OBJECT_MOBILEic ||
         type == OBJECT_MOBILEfi ||
         type == OBJECT_MOBILEti ||
         type == OBJECT_MOBILEwi ||
         type == OBJECT_MOBILEii ||
         type == OBJECT_MOBILEfs ||
         type == OBJECT_MOBILEts ||
         type == OBJECT_MOBILEws ||
         type == OBJECT_MOBILEis ||
         type == OBJECT_MOBILErt ||
         type == OBJECT_MOBILErc ||
         type == OBJECT_MOBILErr ||
         type == OBJECT_MOBILErs ||
         type == OBJECT_MOBILEsa ||
         type == OBJECT_MOBILEtg ||
         type == OBJECT_MOBILEft ||
         type == OBJECT_MOBILEtt ||
         type == OBJECT_MOBILEwt ||
         type == OBJECT_MOBILEit ||
         type == OBJECT_MOBILErp ||
         type == OBJECT_MOBILEst ||
         type == OBJECT_MOBILEdr ||
         type == OBJECT_MOTHER   ||
         type == OBJECT_ANT      ||
         type == OBJECT_SPIDER   ||
         type == OBJECT_BEE      ||
         type == OBJECT_WORM     ||
         type == OBJECT_CONTROLLER)  return true;

    return false;
}

bool CControllableHardcodeCollection::HasUserInterfaceBuilderUIHuman(ObjectType type)
{
    return type == OBJECT_HUMAN;
}

bool CControllableHardcodeCollection::HasUserInterfaceBuilderUIRobot(ObjectType type)
{
    if ( (type == OBJECT_MOBILEfb ||
          type == OBJECT_MOBILEtb ||
          type == OBJECT_MOBILEwb ||
          type == OBJECT_MOBILEib) )  return true;

    return false;
}

bool CControllableHardcodeCollection::HasUserInterfaceShielderUIRobot(ObjectType type)
{
    return type == OBJECT_MOBILErs;
}

bool CControllableHardcodeCollection::HasUserInterfaceScribblerUIRobot(ObjectType type)
{
    return type == OBJECT_MOBILEdr;
}

bool CControllableHardcodeCollection::HasUserInterfaceDisableFlyWhileGrabbing(ObjectType type)
{
    if ( (type == OBJECT_HUMAN ||
          type == OBJECT_TECH  ) )   return true;

    return false;
}

std::vector<Ui::CWidget> CControllableHardcodeCollection::GetUserInterfaceWidgetList(ObjectType type)
{
    std::vector<Ui::CWidget> result;
    Ui::CWidgetParams params = {-1};
    
    if ( (type == OBJECT_HUMAN ||
          type == OBJECT_TECH  ) )
    {
        result.push_back({glm::vec2(7.7f, 0.5f), glm::vec2(1.0f, 1.0f), Ui::WIDGET_ICON_BUTTON, 31, EVENT_OBJECT_HTAKE, true, false, PART_PLUSEXPLORER_FALSE|PART_OPTION_ANY});
    }

    if ( (type == OBJECT_HUMAN ||
          type == OBJECT_TECH  ) )
    {
        result.push_back({glm::vec2(10.1f, 0.5f), glm::vec2(1.0f, 1.0f), Ui::WIDGET_ICON_BUTTON, 64+54, EVENT_OBJECT_FCREATE, false, false, PART_PLUSEXPLORER_FALSE|PART_OPTION_ANY, BUILD_FLAG});
        result.push_back({glm::vec2(11.1f, 0.5f), glm::vec2(1.0f, 1.0f), Ui::WIDGET_ICON_BUTTON, 64+55, EVENT_OBJECT_FDELETE, false, false, PART_PLUSEXPLORER_FALSE|PART_OPTION_ANY, BUILD_FLAG});     
        params.color = Gfx::Color(0.28f, 0.56f, 1.0f, 0.0f);
        result.push_back({glm::vec2(10.1f, 1.6f), glm::vec2(0.4f, 0.4f), Ui::WIDGET_COLOR_BUTTON, params, EVENT_OBJECT_FCOLORb, false, false, PART_PLUSEXPLORER_FALSE|PART_OPTION_ANY, BUILD_FLAG});
        params.color = Gfx::Color(1.0f, 0.0f, 0.0f, 0.0f);
        result.push_back({glm::vec2(10.5f, 1.6f), glm::vec2(0.4f, 0.4f), Ui::WIDGET_COLOR_BUTTON, params, EVENT_OBJECT_FCOLORr, false, false, PART_PLUSEXPLORER_FALSE|PART_OPTION_ANY, BUILD_FLAG});
        params.color = Gfx::Color(0.0f, 0.8f, 0.0f, 0.0f);
        result.push_back({glm::vec2(10.9f, 1.6f), glm::vec2(0.4f, 0.4f), Ui::WIDGET_COLOR_BUTTON, params, EVENT_OBJECT_FCOLORg, false, false, PART_PLUSEXPLORER_FALSE|PART_OPTION_ANY, BUILD_FLAG});
        params.color = Gfx::Color(1.0f, 0.93f, 0.0f, 0.0f);
        result.push_back({glm::vec2(11.3f, 1.6f), glm::vec2(0.4f, 0.4f), Ui::WIDGET_COLOR_BUTTON, params, EVENT_OBJECT_FCOLORy, false, false, PART_PLUSEXPLORER_FALSE|PART_OPTION_ANY, BUILD_FLAG});
        params.color = Gfx::Color(0.82f, 0.004f, 0.99f, 0.0f);
        result.push_back({glm::vec2(11.7f, 1.6f), glm::vec2(0.4f, 0.4f), Ui::WIDGET_COLOR_BUTTON, params, EVENT_OBJECT_FCOLORv, false, false, PART_PLUSEXPLORER_FALSE|PART_OPTION_ANY, BUILD_FLAG});
    }

    if ( (type == OBJECT_HUMAN ) )
    {
        result.push_back({glm::vec2(9.0f, 0.5f), glm::vec2(1.0f, 1.0f), Ui::WIDGET_ICON_BUTTON, 64+47, EVENT_OBJECT_GFLAT, false, false, PART_PLUSEXPLORER_FALSE|PART_OPTION_ANY, BUILD_GFLAT});
    }

    if ( (type == OBJECT_MOBILEfa ||
          type == OBJECT_MOBILEta ||
          type == OBJECT_MOBILEwa ||
          type == OBJECT_MOBILEia ) )
    {
        result.push_back({glm::vec2(7.7f,  0.5f), glm::vec2(1.0f, 1.0f), Ui::WIDGET_ICON_BUTTON, 32, EVENT_OBJECT_MTAKE,  true, false,  PART_TRAINER_FALSE|PART_OPTION_ANY});
        result.push_back({glm::vec2(8.9f,  0.5f), glm::vec2(1.0f, 1.0f), Ui::WIDGET_ICON_BUTTON, 34, EVENT_OBJECT_MBACK,  false, false, PART_TRAINER_FALSE|PART_OPTION_ANY});
        result.push_back({glm::vec2(9.9f,  0.5f), glm::vec2(1.0f, 1.0f), Ui::WIDGET_ICON_BUTTON, 35, EVENT_OBJECT_MPOWER, false, false, PART_TRAINER_FALSE|PART_OPTION_ANY});
        result.push_back({glm::vec2(10.9f, 0.5f), glm::vec2(1.0f, 1.0f), Ui::WIDGET_ICON_BUTTON, 33, EVENT_OBJECT_MFRONT, false, false, PART_TRAINER_FALSE|PART_OPTION_ANY});
    }

    if ( (type == OBJECT_MOBILEsa ) )
    {
        result.push_back({glm::vec2(7.7f,  0.5f), glm::vec2(1.0f, 1.0f), Ui::WIDGET_ICON_BUTTON, 32, EVENT_OBJECT_MTAKE,  true, false, PART_TRAINER_FALSE|PART_OPTION_ANY});
    }

    if ( (type == OBJECT_MOBILEfs ||
          type == OBJECT_MOBILEts ||
          type == OBJECT_MOBILEws ||
          type == OBJECT_MOBILEis ) )
    {
        result.push_back({glm::vec2(7.7f, 0.5f), glm::vec2(1.0f, 1.0f), Ui::WIDGET_ICON_BUTTON, 40, EVENT_OBJECT_SEARCH, true, false, PART_TRAINER_FALSE|PART_OPTION_ANY});
        result.push_back({glm::vec2(9.0f, 0.5f), glm::vec2(1.0f, 1.0f), Ui::WIDGET_ICON_BUTTON, 11, EVENT_OBJECT_DELSEARCH, false, false, PART_TRAINER_FALSE|PART_OPTION_ANY});
        
        result.push_back({glm::vec2(10.1f, 0.5f), glm::vec2(1.0f, 1.0f), Ui::WIDGET_ICON_BUTTON, 64+54, EVENT_OBJECT_FCREATE, false, false, PART_TRAINER_FALSE|PART_OPTION_ANY, BUILD_FLAG});
        result.push_back({glm::vec2(11.1f, 0.5f), glm::vec2(1.0f, 1.0f), Ui::WIDGET_ICON_BUTTON, 64+55, EVENT_OBJECT_FDELETE, false, false, PART_TRAINER_FALSE|PART_OPTION_ANY, BUILD_FLAG});     
        params.color = Gfx::Color(0.28f, 0.56f, 1.0f, 0.0f);
        result.push_back({glm::vec2(10.1f, 1.6f), glm::vec2(0.4f, 0.4f), Ui::WIDGET_COLOR_BUTTON, params, EVENT_OBJECT_FCOLORb, false, false, PART_TRAINER_FALSE|PART_OPTION_ANY, BUILD_FLAG});
        params.color = Gfx::Color(1.0f, 0.0f, 0.0f, 0.0f);
        result.push_back({glm::vec2(10.5f, 1.6f), glm::vec2(0.4f, 0.4f), Ui::WIDGET_COLOR_BUTTON, params, EVENT_OBJECT_FCOLORr, false, false, PART_TRAINER_FALSE|PART_OPTION_ANY, BUILD_FLAG});
        params.color = Gfx::Color(0.0f, 0.8f, 0.0f, 0.0f);
        result.push_back({glm::vec2(10.9f, 1.6f), glm::vec2(0.4f, 0.4f), Ui::WIDGET_COLOR_BUTTON, params, EVENT_OBJECT_FCOLORg, false, false, PART_TRAINER_FALSE|PART_OPTION_ANY, BUILD_FLAG});
        params.color = Gfx::Color(1.0f, 0.93f, 0.0f, 0.0f);
        result.push_back({glm::vec2(11.3f, 1.6f), glm::vec2(0.4f, 0.4f), Ui::WIDGET_COLOR_BUTTON, params, EVENT_OBJECT_FCOLORy, false, false, PART_TRAINER_FALSE|PART_OPTION_ANY, BUILD_FLAG});
        params.color = Gfx::Color(0.82f, 0.004f, 0.99f, 0.0f);
        result.push_back({glm::vec2(11.7f, 1.6f), glm::vec2(0.4f, 0.4f), Ui::WIDGET_COLOR_BUTTON, params, EVENT_OBJECT_FCOLORv, false, false, PART_TRAINER_FALSE|PART_OPTION_ANY, BUILD_FLAG});
    }

    if ( (type == OBJECT_MOBILErt ) )
    {
        result.push_back({glm::vec2(7.7f,  0.5f), glm::vec2(1.0f, 1.0f), Ui::WIDGET_ICON_BUTTON, 128+18, EVENT_OBJECT_TERRAFORM, true, false,  PART_TRAINER_FALSE|PART_OPTION_ANY});
        result.push_back({glm::vec2(10.2f, 0.5f), glm::vec2(1.0f, 1.0f), Ui::WIDGET_ICON_BUTTON, 41, EVENT_OBJECT_LIMIT});
    }

    if ( (type == OBJECT_MOBILErr ) )
    {
        result.push_back({glm::vec2(7.7f, 0.5f), glm::vec2(1.0f, 1.0f), Ui::WIDGET_ICON_BUTTON, 128+20, EVENT_OBJECT_RECOVER, true, false, PART_TRAINER_FALSE|PART_OPTION_ANY});
    }

    if ( (type == OBJECT_MOBILEfc ||
          type == OBJECT_MOBILEtc ||
          type == OBJECT_MOBILEwc ||
          type == OBJECT_MOBILEic ||
          type == OBJECT_MOBILEfi ||
          type == OBJECT_MOBILEti ||
          type == OBJECT_MOBILEwi ||
          type == OBJECT_MOBILEii ||
          type == OBJECT_MOBILErc ) )
    {
        result.push_back({glm::vec2(7.7f,  0.5f), glm::vec2(1.0f, 1.0f), Ui::WIDGET_ICON_BUTTON, 42, EVENT_OBJECT_FIRE, true, true, PART_TRAINER_FALSE|PART_OPTION_ANY});
    }

    if ( (type == OBJECT_BEE ) )
    {
        result.push_back({glm::vec2(7.7f,  0.5f), glm::vec2(1.0f, 1.0f), Ui::WIDGET_ICON_BUTTON, 32, EVENT_OBJECT_MTAKE, true, false});
    }

    if ( (type == OBJECT_SPIDER ) )
    {
        result.push_back({glm::vec2(7.7f,  0.5f), glm::vec2(1.0f, 1.0f), Ui::WIDGET_ICON_BUTTON, 42, EVENT_OBJECT_SPIDEREXPLO,  true, true});
    }
    
    if (type == OBJECT_CONVERT ||
        type == OBJECT_DERRICK ||
        type == OBJECT_DESTROYER ||
        type == OBJECT_FACTORY ||
        type == OBJECT_LABO ||
        type == OBJECT_NEST ||
        type == OBJECT_NUCLEAR ||
        type == OBJECT_PORTICO ||
        type == OBJECT_PARA ||
        type == OBJECT_ENERGY ||
        type == OBJECT_STATION ||
        type == OBJECT_RADAR ||
        type == OBJECT_REPAIR ||
        type == OBJECT_RESEARCH ||
        type == OBJECT_TOWER)
    {
        result.push_back({glm::vec2(2.1f,  0.0f), glm::vec2(0.6f, 0.6f), Ui::WIDGET_ICON_BUTTON, 12, EVENT_OBJECT_DELETE});
    }

    if (type == OBJECT_BASE )
    {
        result.push_back({glm::vec2(0.0f,  0.0f), glm::vec2(2.0f, 2.0f), Ui::WIDGET_ICON_LOGO, 128+43, EVENT_OBJECT_TYPE});
//      result.push_back({glm::vec2(7.25f, 0.25f), glm::vec2(1.5f, 1.5f), Ui::WIDGET_ICON_BUTTON, 63, EVENT_OBJECT_BHELP,  false, false, PART_TRAINER_FALSE|PART_OPTION_ANY});
        result.push_back({glm::vec2(8.0f,  0.25f), glm::vec2(1.5f, 1.5f), Ui::WIDGET_ICON_BUTTON, 28, EVENT_OBJECT_BTAKEOFF,  false, false, PART_TRAINER_FALSE|PART_OPTION_ANY});
        result.push_back({glm::vec2(10.2f, 0.5f), glm::vec2(1.0f, 1.0f), Ui::WIDGET_ICON_BUTTON, 41, EVENT_OBJECT_LIMIT, false, false, PART_LIGHTNING_TRUE|PART_OPTION_ANY}); 
    }
    if (type == OBJECT_FACTORY )
    {
        result.push_back({glm::vec2(0.0f,  0.0f), glm::vec2(2.0f, 2.0f), Ui::WIDGET_ICON_LOGO, 128+32, EVENT_OBJECT_TYPE});
    }
    if (type == OBJECT_RESEARCH )
    {
        result.push_back({glm::vec2(0.0f,  0.0f), glm::vec2(2.0f, 2.0f), Ui::WIDGET_ICON_LOGO, 128+35, EVENT_OBJECT_TYPE});
    }
    if (type == OBJECT_CONVERT )
    {
        result.push_back({glm::vec2(0.0f,  0.0f), glm::vec2(2.0f, 2.0f), Ui::WIDGET_ICON_LOGO, 128+34, EVENT_OBJECT_TYPE});
    }
    if (type == OBJECT_STATION )
    {
        result.push_back({glm::vec2(0.0f,  0.0f), glm::vec2(2.0f, 2.0f), Ui::WIDGET_ICON_LOGO, 128+36, EVENT_OBJECT_TYPE});
    }
    if (type == OBJECT_RADAR )
    {
        result.push_back({glm::vec2(0.0f,  0.0f), glm::vec2(2.0f, 2.0f), Ui::WIDGET_ICON_LOGO, 128+40, EVENT_OBJECT_TYPE});
    }
    if (type == OBJECT_REPAIR )
    {
        result.push_back({glm::vec2(0.0f,  0.0f), glm::vec2(2.0f, 2.0f), Ui::WIDGET_ICON_LOGO, 128+41, EVENT_OBJECT_TYPE});
    }
    if (type == OBJECT_TOWER )
    {
        result.push_back({glm::vec2(0.0f,  0.0f), glm::vec2(2.0f, 2.0f), Ui::WIDGET_ICON_LOGO, 128+37, EVENT_OBJECT_TYPE});
        result.push_back({glm::vec2(10.2f, 0.5f), glm::vec2(1.0f, 1.0f), Ui::WIDGET_ICON_BUTTON, 41, EVENT_OBJECT_LIMIT}); 
    }
    if (type == OBJECT_ENERGY )
    {
        result.push_back({glm::vec2(0.0f,  0.0f), glm::vec2(2.0f, 2.0f), Ui::WIDGET_ICON_LOGO, 128+39, EVENT_OBJECT_TYPE});
    }
    if (type == OBJECT_DERRICK )
    {
        result.push_back({glm::vec2(0.0f,  0.0f), glm::vec2(2.0f, 2.0f), Ui::WIDGET_ICON_LOGO, 128+33, EVENT_OBJECT_TYPE});
    }
    if (type == OBJECT_NUCLEAR )
    {
        result.push_back({glm::vec2(0.0f,  0.0f), glm::vec2(2.0f, 2.0f), Ui::WIDGET_ICON_LOGO, 128+42, EVENT_OBJECT_TYPE});
    }
    if (type == OBJECT_LABO )
    {
        result.push_back({glm::vec2(0.0f,  0.0f), glm::vec2(2.0f, 2.0f), Ui::WIDGET_ICON_LOGO, 128+38, EVENT_OBJECT_TYPE});
    }
    if (type == OBJECT_INFO )
    {
        result.push_back({glm::vec2(0.0f,  0.0f), glm::vec2(2.0f, 2.0f), Ui::WIDGET_ICON_LOGO, 128+44, EVENT_OBJECT_TYPE});
    }
    if (type == OBJECT_PARA )
    {
        result.push_back({glm::vec2(0.0f,  0.0f), glm::vec2(2.0f, 2.0f), Ui::WIDGET_ICON_LOGO, 128+46, EVENT_OBJECT_TYPE});
        result.push_back({glm::vec2(10.2f, 0.5f), glm::vec2(1.0f, 1.0f), Ui::WIDGET_ICON_BUTTON, 41, EVENT_OBJECT_LIMIT}); 
    }
    if (type == OBJECT_SAFE )
    {
        result.push_back({glm::vec2(0.0f,  0.0f), glm::vec2(2.0f, 2.0f), Ui::WIDGET_ICON_LOGO, 128+47, EVENT_OBJECT_TYPE});
    }
    if (type == OBJECT_HUSTON )
    {
        result.push_back({glm::vec2(0.0f,  0.0f), glm::vec2(2.0f, 2.0f), Ui::WIDGET_ICON_LOGO, 128+48, EVENT_OBJECT_TYPE});
    }
    if (type == OBJECT_DESTROYER )
    {
        result.push_back({glm::vec2(0.0f,  0.0f), glm::vec2(2.0f, 2.0f), Ui::WIDGET_ICON_LOGO, 128+41, EVENT_OBJECT_TYPE});
    }

    return result;
}

std::vector<CObjectBuilderMenuButtons> CControllableHardcodeCollection::GetBuilderMenuButtons(ObjectType type)
{
    std::vector<CObjectBuilderMenuButtons> result;

    if (type == OBJECT_HUMAN    ||
        type == OBJECT_MOBILEwb ||
        type == OBJECT_MOBILEfb ||
        type == OBJECT_MOBILEib ||
        type == OBJECT_MOBILEtb  )
    {
        result.push_back({ OBJECT_RESEARCH, 128+35, TR("Build a research center") });
        result.push_back({ OBJECT_FACTORY,  128+32, TR("Build a bot factory") });
        result.push_back({ OBJECT_CONVERT,  128+34, TR("Build a converter") });
        result.push_back({ OBJECT_STATION,  128+36, TR("Build a power station") });
        result.push_back({ OBJECT_RADAR,    128+40, TR("Build a radar station") });
        result.push_back({ OBJECT_REPAIR,   128+41, TR("Build a repair center") });
        result.push_back({ OBJECT_INFO,     128+44, TR("Build a exchange post") });
        result.push_back({ OBJECT_TOWER,    128+37, TR("Build a defense tower") });
        result.push_back({ OBJECT_ENERGY,   128+39, TR("Build a power cell factory") });
        result.push_back({ OBJECT_DERRICK,  128+33, TR("Build a derrick") });
        result.push_back({ OBJECT_NUCLEAR,  128+42, TR("Build a nuclear power plant") });
        result.push_back({ OBJECT_LABO,     128+38, TR("Build an autolab") });
        result.push_back({ OBJECT_PARA,     128+46, TR("Build a lightning conductor") });
        result.push_back({ OBJECT_SAFE,     128+47, TR("Build a vault") });
    }

    if (type == OBJECT_FACTORY )
    {
        result.push_back({ OBJECT_MOBILEwa, 128+9,  TR("Build a wheeled grabber") });
        result.push_back({ OBJECT_MOBILEta, 128+10, TR("Build a tracked grabber") });
        result.push_back({ OBJECT_MOBILEfa, 128+11, TR("Build a winged grabber") });
        result.push_back({ OBJECT_MOBILEia, 128+22, TR("Build a legged grabber") });
    
        result.push_back({ OBJECT_MOBILEws, 128+12, TR("Build a wheeled sniffer") });
        result.push_back({ OBJECT_MOBILEts, 128+13, TR("Build a tracked sniffer") });
        result.push_back({ OBJECT_MOBILEfs, 128+14, TR("Build a winged sniffer") });
        result.push_back({ OBJECT_MOBILEis, 128+24, TR("Build a legged sniffer") });
    
        result.push_back({ OBJECT_MOBILEwc, 128+15, TR("Build a wheeled shooter") });
        result.push_back({ OBJECT_MOBILEtc, 128+16, TR("Build a tracked shooter") });
        result.push_back({ OBJECT_MOBILEfc, 128+17, TR("Build a winged shooter") });
        result.push_back({ OBJECT_MOBILEic, 128+23, TR("Build a legged shooter") });
    
        result.push_back({ OBJECT_MOBILEwi, 128+25, TR("Build a wheeled orga shooter") });
        result.push_back({ OBJECT_MOBILEti, 128+26, TR("Build a tracked orga shooter") });
        result.push_back({ OBJECT_MOBILEfi, 128+27, TR("Build a winged orga shooter") });
        result.push_back({ OBJECT_MOBILEii, 128+28, TR("Build a legged orga shooter") });
    
        result.push_back({ OBJECT_MOBILEwb, 192+0,  TR("Build a wheeled builder") });
        result.push_back({ OBJECT_MOBILEtb, 192+1,  TR("Build a tracked builder") });
        result.push_back({ OBJECT_MOBILEfb, 192+2,  TR("Build a winged builder") });
        result.push_back({ OBJECT_MOBILEib, 192+3,  TR("Build a legged builder") });
    
        result.push_back({ OBJECT_MOBILErt, 128+18, TR("Build a thumper") });
        result.push_back({ OBJECT_MOBILErc, 128+19, TR("Build a phazer shooter") });
        result.push_back({ OBJECT_MOBILErr, 128+20, TR("Build a recycler") });
        result.push_back({ OBJECT_MOBILErs, 128+29, TR("Build a shielder") });
    
        result.push_back({ OBJECT_MOBILEsa, 128+21, TR("Build a subber") });
        result.push_back({ OBJECT_MOBILEtg, 128+45, TR("Build a target bot") });
    }

    return result;
}

bool CControllableHardcodeCollection::IsCameraTypeChangable(ObjectType type)
{
    if ( type != OBJECT_HUMAN &&
         type != OBJECT_TECH &&
         type != OBJECT_MOBILEfa &&
         type != OBJECT_MOBILEta &&
         type != OBJECT_MOBILEwa &&
         type != OBJECT_MOBILEia &&
         type != OBJECT_MOBILEfb &&
         type != OBJECT_MOBILEtb &&
         type != OBJECT_MOBILEwb &&
         type != OBJECT_MOBILEib &&
         type != OBJECT_MOBILEfc &&
         type != OBJECT_MOBILEtc &&
         type != OBJECT_MOBILEwc &&
         type != OBJECT_MOBILEic &&
         type != OBJECT_MOBILEfi &&
         type != OBJECT_MOBILEti &&
         type != OBJECT_MOBILEwi &&
         type != OBJECT_MOBILEii &&
         type != OBJECT_MOBILEfs &&
         type != OBJECT_MOBILEts &&
         type != OBJECT_MOBILEws &&
         type != OBJECT_MOBILEis &&
         type != OBJECT_MOBILErt &&
         type != OBJECT_MOBILErc &&
         type != OBJECT_MOBILErr &&
         type != OBJECT_MOBILErs &&
         type != OBJECT_MOBILEsa &&
         type != OBJECT_MOBILEtg &&
         type != OBJECT_MOBILEft &&
         type != OBJECT_MOBILEtt &&
         type != OBJECT_MOBILEwt &&
         type != OBJECT_MOBILEit &&
         type != OBJECT_MOBILErp &&
         type != OBJECT_MOBILEst &&
         type != OBJECT_MOBILEdr &&
         type != OBJECT_APOLLO2 )  return false;

    return true;
}

bool CControllableHardcodeCollection::IsCameraTypePersistent(ObjectType type)
{
    if ( type == OBJECT_HUMAN    ||
         type == OBJECT_MOBILEfa ||
         type == OBJECT_MOBILEta ||
         type == OBJECT_MOBILEwa ||
         type == OBJECT_MOBILEia ||
         type == OBJECT_MOBILEfb ||
         type == OBJECT_MOBILEtb ||
         type == OBJECT_MOBILEwb ||
         type == OBJECT_MOBILEib ||
         type == OBJECT_MOBILEfc ||
         type == OBJECT_MOBILEtc ||
         type == OBJECT_MOBILEwc ||
         type == OBJECT_MOBILEic ||
         type == OBJECT_MOBILEfi ||
         type == OBJECT_MOBILEti ||
         type == OBJECT_MOBILEwi ||
         type == OBJECT_MOBILEii ||
         type == OBJECT_MOBILEfs ||
         type == OBJECT_MOBILEts ||
         type == OBJECT_MOBILEws ||
         type == OBJECT_MOBILEis ||
         type == OBJECT_MOBILErt ||
         type == OBJECT_MOBILErc ||
         type == OBJECT_MOBILErr ||
         type == OBJECT_MOBILErs ||
         type == OBJECT_MOBILEsa ||
         type == OBJECT_MOBILEft ||
         type == OBJECT_MOBILEtt ||
         type == OBJECT_MOBILEwt ||
         type == OBJECT_MOBILEit ||
         type == OBJECT_MOBILErp ||
         type == OBJECT_MOBILEst ||
         type == OBJECT_MOBILEdr ||
         type == OBJECT_APOLLO2 )  return true;

    return false;
}

Gfx::CameraType CControllableHardcodeCollection::GetDefaultCameraType(ObjectType type)
{
    if ( type == OBJECT_MOBILEwc ||
         type == OBJECT_MOBILEtc ||
         type == OBJECT_MOBILEfc ||
         type == OBJECT_MOBILEic ||
         type == OBJECT_MOBILEwi ||
         type == OBJECT_MOBILEti ||
         type == OBJECT_MOBILEfi ||
         type == OBJECT_MOBILEii ||
         type == OBJECT_MOBILErc )  // cannon vehicle?
    {
        return Gfx::CAM_TYPE_ONBOARD;
    }
    return Gfx::CAM_TYPE_BACK;
}

float CControllableHardcodeCollection::GetBackCameraDistance(ObjectType type)
{
    float m_backDist = 30.0f;
    if ( type == OBJECT_BASE     )  m_backDist = 200.0f;
    if ( type == OBJECT_HUMAN    )  m_backDist =  20.0f;
    if ( type == OBJECT_TECH     )  m_backDist =  20.0f;
    if ( type == OBJECT_FACTORY  )  m_backDist =  50.0f;
    if ( type == OBJECT_RESEARCH )  m_backDist =  40.0f;
    if ( type == OBJECT_DERRICK  )  m_backDist =  40.0f;
    if ( type == OBJECT_REPAIR   )  m_backDist =  35.0f;
    if ( type == OBJECT_DESTROYER)  m_backDist =  35.0f;
    if ( type == OBJECT_TOWER    )  m_backDist =  45.0f;
    if ( type == OBJECT_NUCLEAR  )  m_backDist =  70.0f;
    if ( type == OBJECT_PARA     )  m_backDist = 180.0f;
    if ( type == OBJECT_SAFE     )  m_backDist =  50.0f;
    if ( type == OBJECT_HUSTON   )  m_backDist = 120.0f;
    if ( type == OBJECT_MOTHER   )  m_backDist =  55.0f;
    return m_backDist;
}

float CControllableHardcodeCollection::GetBackCameraDistanceMin(ObjectType type)
{
    float m_backDist = GetBackCameraDistance(type);
    float m_backMin = m_backDist/3.0f;
    if ( type == OBJECT_HUMAN    )  m_backMin =  10.0f;
    if ( type == OBJECT_TECH     )  m_backMin =  10.0f;
    if ( type == OBJECT_FACTORY  )  m_backMin =  30.0f;
    if ( type == OBJECT_RESEARCH )  m_backMin =  20.0f;
    if ( type == OBJECT_NUCLEAR  )  m_backMin =  32.0f;
    if ( type == OBJECT_PARA     )  m_backMin =  40.0f;
    if ( type == OBJECT_SAFE     )  m_backMin =  25.0f;
    if ( type == OBJECT_HUSTON   )  m_backMin =  80.0f;
    return m_backMin;
}

float CControllableHardcodeCollection::GetBackCameraHeight(ObjectType type)
{
         if (type == OBJECT_BASE ) return 40.0f;
    else if (type == OBJECT_HUMAN) return 1.0f;
    else if (type == OBJECT_TECH ) return 1.0f;
    else                           return 4.0f;
}

float CControllableHardcodeCollection::GetBackCameraRotationY(ObjectType type)
{
    if ( type == OBJECT_DERRICK  ||
         type == OBJECT_FACTORY  ||
         type == OBJECT_REPAIR   ||
         type == OBJECT_DESTROYER||
         type == OBJECT_STATION  ||
         type == OBJECT_CONVERT  ||
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
         type == OBJECT_START    ||
         type == OBJECT_END      )  // building?
    {
        return 0.20f;  // nearly face
    }
    else    // vehicle?
    {
        return 1.0f;  // back
    }
}

float CControllableHardcodeCollection::GetBackCameraRotationZ(ObjectType type)
{
    if (type == OBJECT_MOBILEdr)  // designer?
        return 0.09375f;
    return 0.0;
}

float CControllableHardcodeCollection::GetVisitCameraDistance(ObjectType type)
{
    if ( type == OBJECT_PORTICO )  return 200.0f;
    if ( type == OBJECT_BASE    )  return 200.0f;
    if ( type == OBJECT_NUCLEAR )  return 100.0f;
    if ( type == OBJECT_PARA    )  return 100.0f;
    if ( type == OBJECT_SAFE    )  return 100.0f;
    if ( type == OBJECT_TOWER   )  return  80.0f;
    return 60.0f;
}

float CControllableHardcodeCollection::GetVisitCameraHeight(ObjectType type)
{
    if ( type == OBJECT_DERRICK  )  return 35.0f;
    if ( type == OBJECT_FACTORY  )  return 22.0f;
    if ( type == OBJECT_REPAIR   )  return 30.0f;
    if ( type == OBJECT_DESTROYER)  return 30.0f;
    if ( type == OBJECT_STATION  )  return 13.0f;
    if ( type == OBJECT_CONVERT  )  return 20.0f;
    if ( type == OBJECT_TOWER    )  return 30.0f;
    if ( type == OBJECT_RESEARCH )  return 22.0f;
    if ( type == OBJECT_RADAR    )  return 19.0f;
    if ( type == OBJECT_INFO     )  return 19.0f;
    if ( type == OBJECT_ENERGY   )  return 20.0f;
    if ( type == OBJECT_LABO     )  return 16.0f;
    if ( type == OBJECT_NUCLEAR  )  return 40.0f;
    if ( type == OBJECT_PARA     )  return 40.0f;
    if ( type == OBJECT_SAFE     )  return 20.0f;
    return 15.0f;
}

bool CControllableHardcodeCollection::DisableBackCameraCanForceTransparency(ObjectType type)
{
    if ( type == OBJECT_BASE     ||  // building?
         type == OBJECT_DERRICK  ||
         type == OBJECT_FACTORY  ||
         type == OBJECT_STATION  ||
         type == OBJECT_CONVERT  ||
         type == OBJECT_REPAIR   ||
         type == OBJECT_DESTROYER||
         type == OBJECT_TOWER    ||
         type == OBJECT_RESEARCH ||
         type == OBJECT_RADAR    ||
         type == OBJECT_ENERGY   ||
         type == OBJECT_LABO     ||
         type == OBJECT_NUCLEAR  ||
         type == OBJECT_PARA     ||
         type == OBJECT_SAFE     ||
         type == OBJECT_HUSTON   )  return true;
    return false;
}

bool CControllableHardcodeCollection::DisableBackCameraCanViewAsTransparent(ObjectType type)
{
    if ( type == OBJECT_HUMAN  ||
         type == OBJECT_TECH   ||
         type == OBJECT_TOTO   ||
         type == OBJECT_ANT    ||
         type == OBJECT_SPIDER ||
         type == OBJECT_BEE    ||
         type == OBJECT_WORM   )  return true;
    return false;
}

bool CControllableHardcodeCollection::HasGateTransparencyOnBackCamera(ObjectType type)
{
    if (type == OBJECT_FACTORY)  return true;
    return false;
}


bool CControllableHardcodeCollection::DisableCollisionsOnFixCamera(ObjectType type)
{
    if ( type == OBJECT_TOTO    ||
         type == OBJECT_STONE   ||
         type == OBJECT_URANIUM ||
         type == OBJECT_METAL   ||
         type == OBJECT_POWER   ||
         type == OBJECT_ATOMIC  ||
         type == OBJECT_BULLET  ||
         type == OBJECT_BBOX    ||
         type == OBJECT_KEYa    ||
         type == OBJECT_KEYb    ||
         type == OBJECT_KEYc    ||
         type == OBJECT_KEYd    ||
         type == OBJECT_ANT     ||
         type == OBJECT_SPIDER  ||
         type == OBJECT_BEE     ||
         type == OBJECT_WORM ) return true;
    return false;
}

bool CControllableHardcodeCollection::DisableOnboardCameraCorners(ObjectType type)
{
    if (type == OBJECT_HUMAN ||
        type == OBJECT_TECH) return true;
    return false;
}

bool CControllableHardcodeCollection::HasOnboardCameraCrosshair(ObjectType type)
{
    if ( (type == OBJECT_MOBILEfc ||
          type == OBJECT_MOBILEtc ||
          type == OBJECT_MOBILEwc ||
          type == OBJECT_MOBILEic ||
          type == OBJECT_MOBILEfi ||
          type == OBJECT_MOBILEti ||
          type == OBJECT_MOBILEwi ||
          type == OBJECT_MOBILEii ||
          type == OBJECT_MOBILErc ) )  return true;

    return false;
}

glm::vec3 CControllableHardcodeCollection::GetOnboardCameraPosition(ObjectType type)
{
    glm::vec3 eye;

    if ( type == OBJECT_HUMAN ||
         type == OBJECT_TECH  )
    {
        eye.x = -0.2f;
        eye.y =  3.3f;
        eye.z =  0.0f;
//?     eye.x =  1.0f;
//?     eye.y =  3.3f;
//?     eye.z =  0.0f;
    }
    else if ( type == OBJECT_MOBILErt ||
              type == OBJECT_MOBILErr ||
              type == OBJECT_MOBILErs ||
              type == OBJECT_MOBILErp )
    {
        eye.x = -1.1f;  // on the cap
        eye.y =  7.9f;
        eye.z =  0.0f;
    }
    else if ( type == OBJECT_MOBILEwc ||
              type == OBJECT_MOBILEtc ||
              type == OBJECT_MOBILEfc ||
              type == OBJECT_MOBILEic )  // fireball?
    {
//?     eye.x = -0.9f;  // on the cannon
//?     eye.y =  3.0f;
//?     eye.z =  0.0f;
//?     part = 1;
        eye.x = -0.9f;  // on the cannon
        eye.y =  8.3f;
        eye.z =  0.0f;
    }
    else if ( type == OBJECT_MOBILEwi ||
              type == OBJECT_MOBILEti ||
              type == OBJECT_MOBILEfi ||
              type == OBJECT_MOBILEii )  // orgaball ?
    {
//?     eye.x = -3.5f;  // on the cannon
//?     eye.y =  5.1f;
//?     eye.z =  0.0f;
//?     part = 1;
        eye.x = -2.5f;  // on the cannon
        eye.y = 10.4f;
        eye.z =  0.0f;
    }
    else if ( type == OBJECT_MOBILErc )
    {
//?     eye.x =  2.0f;  // in the cannon
//?     eye.y =  0.0f;
//?     eye.z =  0.0f;
//?     part = 2;
        eye.x =  4.0f;  // on the cannon
        eye.y = 11.0f;
        eye.z =  0.0f;
    }
    else if ( type == OBJECT_MOBILEsa ||
              type == OBJECT_MOBILEst )
    {
        eye.x =  3.0f;
        eye.y =  4.5f;
        eye.z =  0.0f;
    }
    else if ( type == OBJECT_MOBILEdr )
    {
        eye.x =  1.0f;
        eye.y =  6.5f;
        eye.z =  0.0f;
    }
    else if ( type == OBJECT_APOLLO2 )
    {
        eye.x = -3.0f;
        eye.y =  6.0f;
        eye.z = -2.0f;
    }
    else
    {
        eye.x = 0.7f;  // between the brackets
        eye.y = 4.8f;
        eye.z = 0.0f;
    }    

    return eye;
}