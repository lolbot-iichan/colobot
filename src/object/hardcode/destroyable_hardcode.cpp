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

#include "graphics/engine/pyro_type.h"

#include "object/object_type.h"

#include "object/hardcode/destroyable_hardcode.h"

/* Macro to mark which texts are translatable by gettext
 * It doesn't do anything at compile-time, as all texts represented here are used later
 * in explicit call to gettext(), but it is used by xgettext executable to filter extracted
 * texts from this file.
 */
#define TR(x) x

/* Please run `cmake --build <path_to_build_folder> --target update-pot`
 * after changing this file in order to update translation files. Thank you.
 */

bool CDestroyableHardcodeCollection::IsDestroyable(ObjectType type)
{
    // TODO: Hacking some more
    if ( type == OBJECT_MOBILEtg ||
         type == OBJECT_STONE    ||
         type == OBJECT_METAL    ||
         type == OBJECT_URANIUM  ||
         type == OBJECT_POWER    ||
         type == OBJECT_ATOMIC   ||
         type == OBJECT_TNT      ||
         type == OBJECT_BULLET   ||
         type == OBJECT_EGG      ||
         type == OBJECT_BOMB     ||
         type == OBJECT_ANT      ||
         type == OBJECT_WORM     ||
         type == OBJECT_SPIDER   ||
         type == OBJECT_BEE      ||
         type == OBJECT_TEEN28    )
    {
        return true;
    }
    else if (type == OBJECT_HUMAN ||
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
         type == OBJECT_FACTORY  ||
         type == OBJECT_REPAIR   ||
         type == OBJECT_DESTROYER||
         type == OBJECT_DERRICK  ||
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
         type == OBJECT_MOTHER    )
    {
        return true;
    }
    else if (type == OBJECT_HUSTON ||
             type == OBJECT_BASE    )
    {
        return false;
    }
    else if (type == OBJECT_RUINmobilew1 ||
             type == OBJECT_RUINmobilew2 ||
             type == OBJECT_RUINmobilet1 ||
             type == OBJECT_RUINmobilet2 ||
             type == OBJECT_RUINmobiler1 ||
             type == OBJECT_RUINmobiler2 ||
             type == OBJECT_RUINfactory  ||
             type == OBJECT_RUINdoor     ||
             type == OBJECT_RUINsupport  ||
             type == OBJECT_RUINradar    ||
             type == OBJECT_RUINconvert   )
    {
        return true;
    }
    else if (type == OBJECT_PLANT0  ||
             type == OBJECT_PLANT1  ||
             type == OBJECT_PLANT2  ||
             type == OBJECT_PLANT3  ||
             type == OBJECT_PLANT4  ||
             type == OBJECT_PLANT15 ||
             type == OBJECT_PLANT16 ||
             type == OBJECT_PLANT17 ||
             type == OBJECT_PLANT18 )
    {
        return true;
    }

    return false;
}

bool CDestroyableHardcodeCollection::IsDestructionRemoveBuildingLevel(ObjectType type)
{
    if ( type == OBJECT_BASE     ||
         type == OBJECT_FACTORY  ||
         type == OBJECT_REPAIR   ||
         type == OBJECT_DESTROYER||
         type == OBJECT_DERRICK  ||
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
         type == OBJECT_END      ) return true;

    // but why? maybe just check objects that has AddBuildingLevels() in model?
    // also, ruins have building levels as well.....

    return false;
}

std::string CDestroyableHardcodeCollection::GetDestroyMessage(ObjectType type)
{
    if ( type == OBJECT_MOTHER )  return TR("Alien Queen killed");
    if ( type == OBJECT_ANT    )  return TR("Ant fatally wounded");
    if ( type == OBJECT_BEE    )  return TR("Wasp fatally wounded");
    if ( type == OBJECT_WORM   )  return TR("Worm fatally wounded");
    if ( type == OBJECT_SPIDER )  return TR("Spider fatally wounded");

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
         type == OBJECT_MOBILEwt ||
         type == OBJECT_MOBILEtt ||
         type == OBJECT_MOBILEft ||
         type == OBJECT_MOBILEit ||
         type == OBJECT_MOBILErp ||
         type == OBJECT_MOBILEst ||
         type == OBJECT_MOBILEdr )
    {
        return TR("Bot destroyed");
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
         type == OBJECT_START    ||
         type == OBJECT_END      )
    {
        return TR("Building destroyed");
    }

    return "";
}

Gfx::PyroType CDestroyableHardcodeCollection::GetDestructionByExplosion(ObjectType type)
{
    if ( type == OBJECT_ANT    ||
         type == OBJECT_SPIDER ||
         type == OBJECT_BEE    ||
         type == OBJECT_WORM   )
    {
        return Gfx::PT_EXPLOO;
    }
    else if ( type == OBJECT_MOTHER ||
              type == OBJECT_NEST   ||
              type == OBJECT_BULLET )
    {
        return Gfx::PT_FRAGO;
    }
    else if ( type == OBJECT_HUMAN )
    {
        return Gfx::PT_DEADG;
    }
    else if ( type == OBJECT_BASE     ||
              type == OBJECT_DERRICK  ||
              type == OBJECT_FACTORY  ||
              type == OBJECT_STATION  ||
              type == OBJECT_CONVERT  ||
              type == OBJECT_REPAIR   ||
              type == OBJECT_DESTROYER||
              type == OBJECT_TOWER    ||
              type == OBJECT_NEST     ||
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
              type == OBJECT_END      ||
              type == OBJECT_RUINfactory ||
              type == OBJECT_RUINdoor    ||
              type == OBJECT_RUINsupport ||
              type == OBJECT_RUINradar   ||
              type == OBJECT_RUINconvert  )  // building?
    {
        return Gfx::PT_FRAGT;
    }
    else if ( type == OBJECT_MOBILEtg )
    {
        return Gfx::PT_FRAGT;
    }
    else
    {
        return Gfx::PT_EXPLOT;
    }
}

bool CDestroyableHardcodeCollection::IsExplodesInWater(ObjectType type)
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
         type == OBJECT_MOBILEft ||
         type == OBJECT_MOBILEtt ||
         type == OBJECT_MOBILEwt ||
         type == OBJECT_MOBILEit ||
         type == OBJECT_MOBILErp ||
         type == OBJECT_MOBILEtg ||
         type == OBJECT_MOBILEdr ||
         type == OBJECT_APOLLO2 ) return true;

    return false;
}

Gfx::PyroType CDestroyableHardcodeCollection::GetDestructionByWater(ObjectType type)
{
    return Gfx::PT_FRAGW;
}

Gfx::PyroType CDestroyableHardcodeCollection::GetDestructionByBurning(ObjectType type)
{
    if ( type == OBJECT_MOTHER ||
         type == OBJECT_ANT    ||
         type == OBJECT_SPIDER ||
         type == OBJECT_BEE    ||
         type == OBJECT_WORM   ||
         type == OBJECT_BULLET )
    {
        return Gfx::PT_BURNO;
    }
    else if ( type == OBJECT_HUMAN )
    {
        return Gfx::PT_DEADG;
    }
    else
    {
        return Gfx::PT_BURNT;
    }
}

bool CDestroyableHardcodeCollection::IsDestructionKilledByBurning(ObjectType type)
{
    return type != OBJECT_HUMAN;
}

std::vector<CPyroBurnPartDetails> CDestroyableHardcodeCollection::GetBurnParts(ObjectType type)
{
    std::vector<CPyroBurnPartDetails> result;

    if ( type == OBJECT_DERRICK  ||
         type == OBJECT_FACTORY  ||
         type == OBJECT_REPAIR   ||
         type == OBJECT_DESTROYER||
         type == OBJECT_CONVERT  ||
         type == OBJECT_TOWER    ||
         type == OBJECT_RESEARCH ||
         type == OBJECT_ENERGY   ||
         type == OBJECT_LABO     )
    {
        glm::vec3 pos(0.0f, -4.0f, 0.0f);
        glm::vec3 posR(0.0f, -4.0f, 0.0f);
        glm::vec3 angle(-0.2f, 0.0f, -0.2f);
        glm::vec3 angleR(0.4f, 0.0f, 0.4f);
        result.push_back({0, pos, posR, angle, angleR});  // movement of the main part
    }
    else if ( type == OBJECT_STATION ||
              type == OBJECT_RADAR   ||
              type == OBJECT_INFO    )
    {
        glm::vec3 pos(0.0f, -1.0f, 0.0f);
        glm::vec3 posR(0.0f, -1.0f, 0.0f);
        glm::vec3 angle(-0.1f, 0.0f, -0.1f);
        glm::vec3 angleR(0.2f, 0.0f, 0.2f);
        result.push_back({0, pos, posR, angle, angleR});  // movement of the main part
    }
    else if ( type == OBJECT_NUCLEAR )
    {
        glm::vec3 pos(0.0f, -10.0f, 0.0f);
        glm::vec3 posR(0.0f, -10.0f, 0.0f);
        glm::vec3 angle(-0.2f, 0.0f, -0.2f);
        glm::vec3 angleR(0.4f, 0.0f, 0.4f);
        result.push_back({0, pos, posR, angle, angleR});  // movement of the main part
    }
    else if ( type == OBJECT_PARA )
    {
        glm::vec3 pos(0.0f, -10.0f, 0.0f);
        glm::vec3 posR(0.0f, -10.0f, 0.0f);
        glm::vec3 angle(-0.2f, 0.0f, -0.2f);
        glm::vec3 angleR(0.4f, 0.0f, 0.4f);
        result.push_back({0, pos, posR, angle, angleR});  // movement of the main part
    }
    else if ( type == OBJECT_SAFE )
    {
        glm::vec3 pos(0.0f, -10.0f, 0.0f);
        glm::vec3 posR(0.0f, -10.0f, 0.0f);
        glm::vec3 angle(-0.2f, 0.0f, -0.2f);
        glm::vec3 angleR(0.4f, 0.0f, 0.4f);
        result.push_back({0, pos, posR, angle, angleR});  // movement of the main part
    }
    else if ( type == OBJECT_HUSTON )
    {
        glm::vec3 pos(0.0f, -10.0f, 0.0f);
        glm::vec3 posR(0.0f, -10.0f, 0.0f);
        glm::vec3 angle(-0.2f, 0.0f, -0.2f);
        glm::vec3 angleR(0.4f, 0.0f, 0.4f);
        result.push_back({0, pos, posR, angle, angleR});  // movement of the main part
    }
    else if ( type == OBJECT_MOBILEwa ||
              type == OBJECT_MOBILEwb ||
              type == OBJECT_MOBILEwc ||
              type == OBJECT_MOBILEwi ||
              type == OBJECT_MOBILEws ||
              type == OBJECT_MOBILEwt )
    {
        glm::vec3 pos(0.0f, -0.5f, 0.0f);
        glm::vec3 posR(0.0f, -1.0f, 0.0f);
        glm::vec3 angle(-0.4f, 0.0f, -0.2f);
        glm::vec3 angleR(0.8f, 0.0f, 0.4f);
        result.push_back({0, pos, posR, angle, angleR});  // movement of the main part
    }
    else if ( type == OBJECT_TEEN31 )  // basket?
    {
        glm::vec3 pos(0.0f, 0.0f, 0.0f);
        glm::vec3 posR(0.0f, 0.0f, 0.0f);
        glm::vec3 angle(-0.4f, 0.0f, -0.1f);
        glm::vec3 angleR(0.8f, 0.0f, 0.2f);
        result.push_back({0, pos, posR, angle, angleR});  // movement of the main part
    }
    else if ( IsDestroyable(type) ) //TODO: another criteria?
    {
        glm::vec3 pos(0.0f, -2.0f, 0.0f);
        glm::vec3 posR(0.0f, -2.0f, 0.0f);
        glm::vec3 angle(-0.4f, 0.0f, -0.4f);
        glm::vec3 angleR(0.8f, 0.0f, 0.8f);
        result.push_back({0, pos, posR, angle, angleR});  // movement of the main part
    }

    if ( type == OBJECT_DERRICK )
    {
        glm::vec3 pos(0.0f, -40.0f, 0.0f);
        glm::vec3 posR(0.0f, 0.0f, 0.0f);
        glm::vec3 angle(0.0f, 0.0f, 0.0f);
        glm::vec3 angleR(0.0f, 0.0f, 0.0f);
        result.push_back({1, pos, posR, angle, angleR});  // down the drill
    }
    if ( type == OBJECT_REPAIR )
    {
        glm::vec3 pos(0.0f, -12.0f, 0.0f);
        glm::vec3 posR(0.0f, 0.0f, 0.0f);
        glm::vec3 angle(-0.1f, -0.1f, -90.0f*Math::PI/180.0f);
        glm::vec3 angleR(0.2f, 0.2f, 0.0f);
        result.push_back({1, pos, posR, angle, angleR});  // down the sensor
    }
    if ( type == OBJECT_DESTROYER )
    {
        glm::vec3 pos(0.0f, -12.0f, 0.0f);
        glm::vec3 posR(0.0f, 0.0f, 0.0f);
        glm::vec3 angle(-0.1f, -0.1f, -90.0f*Math::PI/180.0f);
        glm::vec3 angleR(0.2f, 0.2f, 0.0f);
        result.push_back({1, pos, posR, angle, angleR});  // down the sensor
    }
    if ( type == OBJECT_CONVERT )
    {
        glm::vec3 pos(0.0f, -200.0f, 0.0f);
        glm::vec3 posR(0.0f, 0.0f, 0.0f);
        glm::vec3 angle(-0.25f, -0.25f, 0.0f);
        glm::vec3 angleR(0.5f, 0.5f, 0.0f);
        result.push_back({1, pos, posR, angle, angleR});  // down the cover
        result.push_back({2, pos, posR, angle, angleR});
        result.push_back({3, pos, posR, angle, angleR});
    }
    if ( type == OBJECT_TOWER )
    {
        glm::vec3 pos(0.0f, -7.0f, 0.0f);
        glm::vec3 posR(0.0f, 0.0f, 0.0f);
        glm::vec3 angle(-0.2f, -0.2f, 0.0f);
        glm::vec3 angleR(0.4f, 0.4f, 0.0f);
        result.push_back({1, pos, posR, angle, angleR});  // down the cannon
    }
    if ( type == OBJECT_RESEARCH )
    {
        glm::vec3 pos(0.0f, -7.0f, 0.0f);
        glm::vec3 posR(0.0f, 0.0f, 0.0f);
        glm::vec3 angle(-0.1f, -0.1f, 0.0f);
        glm::vec3 angleR(0.2f, 0.2f, 0.0f);
        result.push_back({1, pos, posR, angle, angleR});  // down the anemometer
    }
    if ( type == OBJECT_RADAR )
    {
        glm::vec3 pos(0.0f, -14.0f, 0.0f);
        glm::vec3 posR(0.0f, 0.0f, 0.0f);
        glm::vec3 angle(-0.2f, -0.2f, 0.0f);
        glm::vec3 angleR(0.4f, 0.4f, 0.0f);
        result.push_back({1, pos, posR, angle, angleR});  // down the radar
        result.push_back({2, pos, posR, angle, angleR});
    }
    if ( type == OBJECT_INFO )
    {
        glm::vec3 pos(0.0f, -14.0f, 0.0f);
        glm::vec3 posR(0.0f, 0.0f, 0.0f);
        glm::vec3 angle(-0.2f, -0.2f, 0.0f);
        glm::vec3 angleR(0.4f, 0.4f, 0.0f);
        result.push_back({1, pos, posR, angle, angleR});  // down the information terminal
        result.push_back({2, pos, posR, angle, angleR});
    }
    if ( type == OBJECT_LABO )
    {
        glm::vec3 pos(0.0f, -12.0f, 0.0f);
        glm::vec3 posR(0.0f, 0.0f, 0.0f);
        glm::vec3 angle(0.0f, 0.0f, 0.0f);
        glm::vec3 angleR(0.0f, 0.0f, 0.0f);
        result.push_back({1, pos, posR, angle, angleR});  // down the arm
    }
    if ( type == OBJECT_NUCLEAR )
    {
        glm::vec3 pos(0.0f, 0.0f, 0.0f);
        glm::vec3 posR(0.0f, 0.0f, 0.0f);
        glm::vec3 angle(0.0f, 0.0f, -135.0f*Math::PI/180.0f);
        glm::vec3 angleR(0.0f, 0.0f, 0.0f);
        result.push_back({1, pos, posR, angle, angleR});  // down the cover
    }
    if ( type == OBJECT_MOBILEfa ||
         type == OBJECT_MOBILEta ||
         type == OBJECT_MOBILEwa ||
         type == OBJECT_MOBILEia )
    {
        glm::vec3 pos(2.0f, -5.0f, 0.0f);
        glm::vec3 posR(0.0f, 0.0f, 0.0f);
        glm::vec3 angle(-0.1f, -0.1f, 40.0f*Math::PI/180.0f);
        glm::vec3 angleR(0.2f, 0.2f, 0.0f);
        result.push_back({1, pos, posR, angle, angleR});  // down the arm
    }
    if ( type == OBJECT_MOBILEfs ||
         type == OBJECT_MOBILEts ||
         type == OBJECT_MOBILEws ||
         type == OBJECT_MOBILEis )
    {
        glm::vec3 pos(0.0f, -7.0f, 0.0f);
        glm::vec3 posR(0.0f, 0.0f, 0.0f);
        glm::vec3 angle(-0.1f, -0.1f, 50.0f*Math::PI/180.0f);
        glm::vec3 angleR(0.2f, 0.2f, 0.0f);
        result.push_back({1, pos, posR, angle, angleR});  // down the sensor
    }
    if ( type == OBJECT_MOBILEfc ||
         type == OBJECT_MOBILEtc ||
         type == OBJECT_MOBILEwc ||
         type == OBJECT_MOBILEic )
    {
        glm::vec3 pos(-1.5f, -5.0f, 0.0f);
        glm::vec3 posR(0.0f, 0.0f, 0.0f);
        glm::vec3 angle(-0.1f, -0.1f, -25.0f*Math::PI/180.0f);
        glm::vec3 angleR(0.2f, 0.2f, 0.0f);
        result.push_back({1, pos, posR, angle, angleR});  // down the cannon
    }
    if ( type == OBJECT_MOBILEfi ||
         type == OBJECT_MOBILEti ||
         type == OBJECT_MOBILEwi ||
         type == OBJECT_MOBILEii )
    {
        glm::vec3 pos(-1.5f, -5.0f, 0.0f);
        glm::vec3 posR(0.0f, 0.0f, 0.0f);
        glm::vec3 angle(-0.1f, -0.1f, -25.0f*Math::PI/180.0f);
        glm::vec3 angleR(0.2f, 0.2f, 0.0f);
        result.push_back({1, pos, posR, angle, angleR});  // down the insect-cannon
    }
    if ( type == OBJECT_MOBILEfb ||
         type == OBJECT_MOBILEtb ||
         type == OBJECT_MOBILEwb ||
         type == OBJECT_MOBILEib )
    {
        glm::vec3 pos(-1.5f, -5.0f, 0.0f);
        glm::vec3 posR(0.0f, 0.0f, 0.0f);
        glm::vec3 angle(-0.1f, -0.1f, -25.0f*Math::PI/180.0f);
        glm::vec3 angleR(0.2f, 0.2f, 0.0f);
        result.push_back({1, pos, posR, angle, angleR});  // down the neutron gun
    }
    if ( type == OBJECT_MOBILErt ||
         type == OBJECT_MOBILErc )
    {
        {
            glm::vec3 pos(0.0f, -10.0f, 0.0f);
            glm::vec3 posR(0.0f, 0.0f, 0.0f);
            glm::vec3 angle(0.0f, 0.0f, 0.0f);
            glm::vec3 angleR(0.0f, 0.0f, 0.0f);
            result.push_back({1, pos, posR, angle, angleR});  // down the holder
        }
        {
            glm::vec3 pos(0.0f, -10.0f, 0.0f);
            glm::vec3 posR(0.0f, 0.0f, 0.0f);
            glm::vec3 angle(0.0f, 0.0f, 0.0f);
            glm::vec3 angleR(0.0f, 0.0f, 0.0f);
            result.push_back({2, pos, posR, angle, angleR});  // down the pestle/cannon
        }
    }
    if ( type == OBJECT_MOBILErr )
    {
        {
            glm::vec3 pos(0.0f, -10.0f, 0.0f);
            glm::vec3 posR(0.0f, 0.0f, 0.0f);
            glm::vec3 angle(0.0f, 0.0f, 0.0f);
            glm::vec3 angleR(0.0f, 0.0f, 0.0f);
            result.push_back({1, pos, posR, angle, angleR});  // down the holder
        }
        {
            glm::vec3 pos(0.0f, 0.0f, 0.0f);
            glm::vec3 posR(0.0f, 0.0f, 0.0f);
            glm::vec3 angle(0.0f, 0.0f, -Math::PI/2.0f);
            glm::vec3 angleR(0.0f, 0.0f, 0.0f);
            result.push_back({4, pos, posR, angle, angleR});
        }
        {
            glm::vec3 pos(0.0f, 0.0f, 0.0f);
            glm::vec3 posR(0.0f, 0.0f, 0.0f);
            glm::vec3 angle(0.0f, 0.0f, Math::PI/2.0f);
            glm::vec3 angleR(0.0f, 0.0f, 0.0f);
            result.push_back({2, pos, posR, angle, angleR});
        }
    }
    if ( type == OBJECT_MOBILErs )
    {
        {
            glm::vec3 pos(0.0f, -10.0f, 0.0f);
            glm::vec3 posR(0.0f, 0.0f, 0.0f);
            glm::vec3 angle(0.0f, 0.0f, 0.0f);
            glm::vec3 angleR(0.0f, 0.0f, 0.0f);
            result.push_back({1, pos, posR, angle, angleR});  // down the holder
        }
        {
            glm::vec3 pos(0.0f, -5.0f, 0.0f);
            glm::vec3 posR(0.0f, 0.0f, 0.0f);
            glm::vec3 angle(0.0f, 0.0f, 0.0f);
            glm::vec3 angleR(0.0f, 0.0f, 0.0f);
            result.push_back({2, pos, posR, angle, angleR});
        }
        {
            glm::vec3 pos(0.0f, -5.0f, 0.0f);
            glm::vec3 posR(0.0f, 0.0f, 0.0f);
            glm::vec3 angle(0.0f, 0.0f, 0.0f);
            glm::vec3 angleR(0.0f, 0.0f, 0.0f);
            result.push_back({3, pos, posR, angle, angleR});
        }
    }
    if ( type == OBJECT_MOBILEsa )
    {
        glm::vec3 pos(0.0f, -10.0f, 0.0f);
        glm::vec3 posR(0.0f, 0.0f, 0.0f);
        glm::vec3 angle(0.0f, 0.0f, 0.0f);
        glm::vec3 angleR(0.0f, 0.0f, 0.0f);
        result.push_back({1, pos, posR, angle, angleR});  // down the holder
    }
    if ( type == OBJECT_MOBILEwa ||
         type == OBJECT_MOBILEwb ||
         type == OBJECT_MOBILEwc ||
         type == OBJECT_MOBILEwi ||
         type == OBJECT_MOBILEws ||
         type == OBJECT_MOBILEwt )  // wheels?
    {
        int i = 0;
        for (; i < 4; i++)
        {
            glm::vec3 pos(0.0f, 0.0f, 0.0f);
            glm::vec3 posR(0.0f, 0.5f, 0.0f);
            glm::vec3 angle(-0.5f*Math::PI/2.0f, -0.5f*Math::PI/2.0f, 0.0f);
            glm::vec3 angleR(Math::PI/2.0f, Math::PI/2.0f, 0.0f);
            result.push_back({6+i, pos, posR, angle, angleR, true});  // wheel
        }
    }
    if ( type == OBJECT_MOBILEta ||
         type == OBJECT_MOBILEtb ||
         type == OBJECT_MOBILEtc ||
         type == OBJECT_MOBILEti ||
         type == OBJECT_MOBILEts ||
         type == OBJECT_MOBILEtt ||
         type == OBJECT_MOBILErt ||
         type == OBJECT_MOBILErc ||
         type == OBJECT_MOBILErr ||
         type == OBJECT_MOBILErs ||
         type == OBJECT_MOBILErp ||
         type == OBJECT_MOBILEsa ||
         type == OBJECT_MOBILEst ||
         type == OBJECT_MOBILEdr )  // caterpillars?
    {
        {
            glm::vec3 pos(0.0f, -4.0f, 2.0f);
            glm::vec3 posR(0.0f, 0.0f, 0.0f);
            glm::vec3 angle(-0.5f*20.0f*Math::PI/180.0f, -0.5f*10.0f*Math::PI/180.0f, -0.5f*30.0f*Math::PI/180.0f);
            glm::vec3 angleR(20.0f*Math::PI/180.0f, 10.0f*Math::PI/180.0f, 30.0f*Math::PI/180.0f);
            result.push_back({6, pos, posR, angle, angleR});  // down the right caterpillar
        }
        {
            glm::vec3 pos(0.0f, -4.0f, -2.0f);
            glm::vec3 posR(0.0f, 0.0f, 0.0f);
            glm::vec3 angle(-0.5f*20.0f*Math::PI/180.0f, -0.5f*10.0f*Math::PI/180.0f, -0.5f*30.0f*Math::PI/180.0f);
            glm::vec3 angleR(20.0f*Math::PI/180.0f, 10.0f*Math::PI/180.0f, 30.0f*Math::PI/180.0f);
            result.push_back({7, pos, posR, angle, angleR});  // down the left caterpillar
        }
    }
    if ( type == OBJECT_MOBILEfa ||
         type == OBJECT_MOBILEfb ||
         type == OBJECT_MOBILEfc ||
         type == OBJECT_MOBILEfi ||
         type == OBJECT_MOBILEfs ||
         type == OBJECT_MOBILEft )  // flying?
    {
        int i = 0;
        for (; i<3; i++)
        {
            glm::vec3 pos(0.0f, -3.0f, 0.0f);
            glm::vec3 posR(0.0f, 0.0f, 0.0f);
            glm::vec3 angle(0.0f, 0.0f, -0.5f*Math::PI/2.0f);
            glm::vec3 angleR(0.0f, 0.0f, Math::PI/2.0f);
            result.push_back({6+i, pos, posR, angle, angleR});  // foot
        }
    }
    if ( type == OBJECT_MOBILEia ||
         type == OBJECT_MOBILEib ||
         type == OBJECT_MOBILEic ||
         type == OBJECT_MOBILEii ||
         type == OBJECT_MOBILEis ||
         type == OBJECT_MOBILEit )  // legs?
    {
        for (int i = 0; i < 6; i++)
        {
            glm::vec3 pos(0.0f, -3.0f, 0.0f);
            glm::vec3 posR(0.0f, 0.0f, 0.0f);
            glm::vec3 angle(0.0f, -0.5f*Math::PI/4.0f, -0.5f*Math::PI/4.0f);
            glm::vec3 angleR(0.0f, Math::PI/4.0f, Math::PI/4.0f);
            result.push_back({6+i, pos, posR, angle, angleR});  // leg
        }
    }
    return result;
}

ObjectType CDestroyableHardcodeCollection::GetTypeAfterBurn(ObjectType type)
{
    if ( type == OBJECT_DERRICK  ||
         type == OBJECT_STATION  ||
         type == OBJECT_FACTORY  ||
         type == OBJECT_REPAIR   ||
         type == OBJECT_DESTROYER||
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
         type == OBJECT_END      )
    {
        return (OBJECT_RUINfactory); // Ruin
    }
    else if ( IsDestroyable(type) )
    {
        return (OBJECT_RUINmobilew1); // Wreck (recoverable by Recycler)
    }
    else
    {
        return OBJECT_NULL;
    }
}

Gfx::PyroType CDestroyableHardcodeCollection::GetDestructionByDrowned(ObjectType type)
{
    return Gfx::PT_DEADW;
}

Gfx::PyroType CDestroyableHardcodeCollection::GetDestructionByWin(ObjectType type)
{
    return Gfx::PT_WPCHECK;
}

bool CDestroyableHardcodeCollection::IsSquashedByHeavy(ObjectType type)
{
    if (type == OBJECT_PLANT0  ||
        type == OBJECT_PLANT1  ||
        type == OBJECT_PLANT2  ||
        type == OBJECT_PLANT3  ||
        type == OBJECT_PLANT4  ||
        type == OBJECT_PLANT15 ||
        type == OBJECT_PLANT16 ||
        type == OBJECT_PLANT17 ||
        type == OBJECT_PLANT18) return true;

    return false;
}

Gfx::PyroType CDestroyableHardcodeCollection::GetDestructionBySquash(ObjectType type)
{
    return Gfx::PT_SQUASH;
}

float CDestroyableHardcodeCollection::GetThumperSafeRadius(ObjectType type)
{
    if ( type == OBJECT_BULLET ||
         type == OBJECT_NEST   ||
         type == OBJECT_EGG    ) // Alien Organic?
    {
        return 5.0f;
    }
    else if ( type == OBJECT_TNT  ||
              type == OBJECT_BOMB ) // Explosives?
    {
        return 5.0f;
    }
    else if ( type == OBJECT_PLANT0    ||
              type == OBJECT_PLANT1    ||
              type == OBJECT_PLANT2    ||
              type == OBJECT_PLANT3    ||
              type == OBJECT_PLANT4    ||
              type == OBJECT_PLANT5    ||
              type == OBJECT_PLANT6    ||
              type == OBJECT_PLANT7    ||
              type == OBJECT_PLANT15   ||
              type == OBJECT_PLANT16   ||
              type == OBJECT_PLANT17   ||
              type == OBJECT_PLANT18   ||
              type == OBJECT_PLANT19   ) // Plants?
    {
        return 7.5f;

    }
    else  if ( type == OBJECT_TEEN0        ||
     type == OBJECT_TEEN1        ||
     type == OBJECT_TEEN2        ||
     type == OBJECT_TEEN4        ||
     type == OBJECT_TEEN5        ||
     type == OBJECT_TEEN34       ||
     type == OBJECT_POWER        ||
     type == OBJECT_ATOMIC       ||
     type == OBJECT_STONE        ||
     type == OBJECT_URANIUM      ||
     type == OBJECT_METAL        ||
     type == OBJECT_BBOX         ||
     type == OBJECT_KEYa         ||
     type == OBJECT_KEYb         ||
     type == OBJECT_KEYc         ||
     type == OBJECT_KEYd         ||
     type == OBJECT_WINFIRE      ||
     type == OBJECT_BAG          ||
     type == OBJECT_RUINmobilew1 ||
     type == OBJECT_RUINmobilew2 ||
     type == OBJECT_RUINmobilet1 ||
     type == OBJECT_RUINmobilet2 ||
     type == OBJECT_RUINdoor     ||
     type == OBJECT_RUINsupport  ||
     type == OBJECT_RUINradar    ||
     type == OBJECT_BARRIER0     ||
     type == OBJECT_BARRIER1     ||
     type == OBJECT_BARRIER2     ||
     type == OBJECT_BARRIER3     ||
     type == OBJECT_APOLLO4      )  // everything what fits?
    {
        return 5.0f;
    }

    else  if ( type == OBJECT_BEE || type == OBJECT_WORM )
    {
        return 5.0f;
    }

    else  if ( type == OBJECT_ANT || type == OBJECT_SPIDER )
    {
        return 5.0f;
    }

    return 0.0f;
}

Gfx::PyroType CDestroyableHardcodeCollection::GetThumperPyroType(ObjectType type)
{
        if ( type == OBJECT_BULLET ||
             type == OBJECT_NEST   ||
             type == OBJECT_EGG    ) // Alien Organic?
        {
            return Gfx::PT_FRAGO;
        }
        else if ( type == OBJECT_TNT  ||
                  type == OBJECT_BOMB ) // Explosives?
        {
            return Gfx::PT_EXPLOT;
        }
        else if ( type == OBJECT_PLANT0    ||
                  type == OBJECT_PLANT1    ||
                  type == OBJECT_PLANT2    ||
                  type == OBJECT_PLANT3    ||
                  type == OBJECT_PLANT4    ||
                  type == OBJECT_PLANT5    ||
                  type == OBJECT_PLANT6    ||
                  type == OBJECT_PLANT7    ||
                  type == OBJECT_PLANT15   ||
                  type == OBJECT_PLANT16   ||
                  type == OBJECT_PLANT17   ||
                  type == OBJECT_PLANT18   ||
                  type == OBJECT_PLANT19   ) // Plants?
        {
            return Gfx::PT_FRAGV;

        }
        else  if ( type == OBJECT_TEEN0        ||
         type == OBJECT_TEEN1        ||
         type == OBJECT_TEEN2        ||
         type == OBJECT_TEEN4        ||
         type == OBJECT_TEEN5        ||
         type == OBJECT_TEEN34       ||
         type == OBJECT_POWER        ||
         type == OBJECT_ATOMIC       ||
         type == OBJECT_STONE        ||
         type == OBJECT_URANIUM      ||
         type == OBJECT_METAL        ||
         type == OBJECT_BBOX         ||
         type == OBJECT_KEYa         ||
         type == OBJECT_KEYb         ||
         type == OBJECT_KEYc         ||
         type == OBJECT_KEYd         ||
         type == OBJECT_WINFIRE      ||
         type == OBJECT_BAG          ||
         type == OBJECT_RUINmobilew1 ||
         type == OBJECT_RUINmobilew2 ||
         type == OBJECT_RUINmobilet1 ||
         type == OBJECT_RUINmobilet2 ||
         type == OBJECT_RUINdoor     ||
         type == OBJECT_RUINsupport  ||
         type == OBJECT_RUINradar    ||
         type == OBJECT_BARRIER0     ||
         type == OBJECT_BARRIER1     ||
         type == OBJECT_BARRIER2     ||
         type == OBJECT_BARRIER3     ||
         type == OBJECT_APOLLO4      )  // everything what fits?
        {
            return Gfx::PT_FRAGT;
        }

        else  if ( type == OBJECT_BEE || type == OBJECT_WORM )
        {
            return Gfx::PT_EXPLOO;
        }

        else  if ( type == OBJECT_ANT || type == OBJECT_SPIDER )
        {
            return Gfx::PT_EXPLOO;
        }

    return Gfx::PT_FRAGT;
}

float CDestroyableHardcodeCollection::GetThumperExplosionDamage(ObjectType type)
{
    if ( type == OBJECT_TNT || type == OBJECT_BOMB ) // Explosives?
    {
        return 0.9f;
    }

    return 0.0f;
}

bool CDestroyableHardcodeCollection::GetDestroyableByDestroyer(ObjectType type)
{
    if (type == OBJECT_HUMAN ||
        type == OBJECT_TECH   ) return false;

    return IsDestroyable(type);
}
