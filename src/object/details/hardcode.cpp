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

#include <unordered_set>

#include "graphics/engine/lightning.h"

#include "object/details/hardcode.h"

/* Macro to mark which texts are translatable by gettext
 * It doesn't do anything at compile-time, as all texts represented here are used later
 * in explicit call to gettext(), but it is used by xgettext executable to filter extracted
 * texts from this file.
 */
#define TR(x) x

/* Please run `cmake --build <path_to_build_folder> --target update-pot`
 * after changing this file in order to update translation files. Thank you.
 */

float CHardcodeCollection::GetCollisionOtherObjectRadiusToIgnore(ObjectType type)
{
    if ( type == OBJECT_MOTHER ) return 1.2f;
    if ( type == OBJECT_ANT    ) return 1.2f;
    if ( type == OBJECT_SPIDER ) return 1.2f;
    if ( type == OBJECT_BEE    ) return 1.2f;
    if ( type == OBJECT_WORM   ) return 1.2f;

    return 0.0f;
}

bool CHardcodeCollection::IsCollisionDamagable(ObjectType type)
{
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
         type == OBJECT_MOBILEwt ||
         type == OBJECT_MOBILEtt ||
         type == OBJECT_MOBILEft ||
         type == OBJECT_MOBILEit ||
         type == OBJECT_MOBILErp ||
         type == OBJECT_MOBILEst ||
         type == OBJECT_MOBILEdr ||
         type == OBJECT_APOLLO2  ) return true;

    return false;
}

float CHardcodeCollection::GetCollisionSoftness(ObjectType type)
{
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
         type == OBJECT_HUSTON   )  // building?
    {
        return 200.0f;
    }
    else if ( type == OBJECT_MOTHER ||
              type == OBJECT_ANT    ||
              type == OBJECT_SPIDER ||
              type == OBJECT_BEE    ||
              type == OBJECT_WORM   )  // insect?
    {
        return 400.0f;
    }
    else
    if ( type == OBJECT_STONE ||
         type == OBJECT_METAL )
    {
        return 500.0f;
    }
    else
    if ( type == OBJECT_URANIUM ||
         type == OBJECT_POWER   ||
         type == OBJECT_ATOMIC  )
    {
        return 100.0f;
    }
    else
    {
        return 200.0f;
    }
}

float CHardcodeCollection::GetMaxSafeWaterLevel(ObjectType type)
{
    if ( type == OBJECT_HUMAN ||
         type == OBJECT_TECH  )
    {
        return 3.0f;
    }

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
         type == OBJECT_MOBILEdr )
    {
        return 2.0f;
    }

    return 0.0f; 
}

bool CHardcodeCollection::IsExhaustBubblesOnEnteringWater(ObjectType type)
{
    if ( type == OBJECT_MOBILEia ||
         type == OBJECT_MOBILEib ||
         type == OBJECT_MOBILEic ||
         type == OBJECT_MOBILEii ||
         type == OBJECT_MOBILEis ||
         type == OBJECT_MOBILEit ||  // legs?
         type == OBJECT_MOBILEdr ||
         type == OBJECT_MOTHER   ||
         type == OBJECT_ANT      ||
         type == OBJECT_SPIDER   ||
         type == OBJECT_BEE      ||
         type == OBJECT_WORM     ||
         type == OBJECT_APOLLO2  )  return false;

    return true;
}

float CHardcodeCollection::IsExhaustBubblesOnEnteringWaterTime(ObjectType type)
{
    if ( type == OBJECT_HUMAN )  return 3.0f;
    return 8.0f;
}

bool CHardcodeCollection::IsExhaustDropsOnLeavingWater(ObjectType type)
{
    if ( type == OBJECT_MOBILEia ||
         type == OBJECT_MOBILEib ||
         type == OBJECT_MOBILEic ||
         type == OBJECT_MOBILEii ||
         type == OBJECT_MOBILEis ||
         type == OBJECT_MOBILEit ||  // legs?
         type == OBJECT_MOBILEdr ||
         type == OBJECT_MOTHER   ||
         type == OBJECT_ANT      ||
         type == OBJECT_SPIDER   ||
         type == OBJECT_BEE      ||
         type == OBJECT_WORM     ||
         type == OBJECT_APOLLO2  )  return false;

    return true;
}

bool CHardcodeCollection::IsExhaustOnCrashAsHuman(ObjectType type)
{
    if ( (type == OBJECT_HUMAN ||
          type == OBJECT_TECH  ) )   return true;
    return false;
}

bool CHardcodeCollection::IsExhaustOnCrashAsTrackedRobot(ObjectType type)
{
    if ((type == OBJECT_MOBILEta ||
         type == OBJECT_MOBILEtb ||
         type == OBJECT_MOBILEtc ||
         type == OBJECT_MOBILEti ||
         type == OBJECT_MOBILEts ||
         type == OBJECT_MOBILEtt  ) )   return true;
    return false;
}

bool CHardcodeCollection::IsExhaustOnCrashAsHeavyRobot(ObjectType type)
{
    if ((type == OBJECT_MOBILErt ||
         type == OBJECT_MOBILErc ||
         type == OBJECT_MOBILErr ||
         type == OBJECT_MOBILErs ||
         type == OBJECT_MOBILErp  ) )   return true;
    return false;
}

bool CHardcodeCollection::IsExhaustOnLandAsHuman(ObjectType type)
{
    if ( (type == OBJECT_HUMAN ||
          type == OBJECT_TECH  ) )   return true;
    return false;
}

bool CHardcodeCollection::IsExhaustOnLandAsWingedRobot(ObjectType type)
{
    if ((type == OBJECT_MOBILEfa ||
         type == OBJECT_MOBILEfb ||
         type == OBJECT_MOBILEfc ||
         type == OBJECT_MOBILEfi ||
         type == OBJECT_MOBILEfs ||
         type == OBJECT_MOBILEft  ) )   return true;
    return false;
}

bool CHardcodeCollection::IsExhaustOnFlightAsHuman(ObjectType type)
{
    if ( (type == OBJECT_HUMAN ||
          type == OBJECT_TECH  ) )   return true;
    return false;
}

bool  CHardcodeCollection::IsExhaustOnLandAsHeavyRobot(ObjectType type)
{
    if ((type == OBJECT_MOBILErt ||
         type == OBJECT_MOBILErc ||
         type == OBJECT_MOBILErr ||
         type == OBJECT_MOBILErs ||
         type == OBJECT_MOBILErp  ) )   return true;
    return false;
}

bool  CHardcodeCollection::IsExhaustOnLandAsNormalRobot(ObjectType type)
{
    if ((type == OBJECT_MOBILEta ||
         type == OBJECT_MOBILEtb ||
         type == OBJECT_MOBILEtc ||
         type == OBJECT_MOBILEti ||
         type == OBJECT_MOBILEts ||
         type == OBJECT_MOBILEtt ||
         type == OBJECT_MOBILEtg ||
         type == OBJECT_MOBILEwa ||
         type == OBJECT_MOBILEwb ||
         type == OBJECT_MOBILEwc ||
         type == OBJECT_MOBILEwi ||
         type == OBJECT_MOBILEws ||
         type == OBJECT_MOBILEwt ||
         type == OBJECT_MOBILEsa ||
         type == OBJECT_MOBILEst  ) )   return true;
    return false;
}

bool CHardcodeCollection::IsExhaustOnFlightAsWingedRobot(ObjectType type)
{
    if ((type == OBJECT_MOBILEfa ||
         type == OBJECT_MOBILEfb ||
         type == OBJECT_MOBILEfc ||
         type == OBJECT_MOBILEfi ||
         type == OBJECT_MOBILEfs ||
         type == OBJECT_MOBILEft  ) )   return true;
    return false;
}

bool CHardcodeCollection::IsExhaustOnSwimAsHuman(ObjectType type)
{
    if ( (type == OBJECT_HUMAN ||
          type == OBJECT_TECH  ) )   return true;
    return false;
}

bool CHardcodeCollection::IsExhaustOnSwimAsAmphibiousRobot(ObjectType type)
{
    if ( (type == OBJECT_MOBILEst ||
          type == OBJECT_MOBILEsa  ) )   return true;
    return false;
}

float CHardcodeCollection::GetThumperSafeRadius(ObjectType type)
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


    return -1;
}

Gfx::PyroType CHardcodeCollection::GetThumperPyroType(ObjectType type)
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

    return Gfx::PT_NULL;
}

float CHardcodeCollection::GetThumperExplosionDamage(ObjectType type)
{
    if ( type == OBJECT_TNT || type == OBJECT_BOMB ) // Explosives?
    {
        return 0.9f;
    }

    return 0.0f;
}

bool CHardcodeCollection::GetThumperTurnOnBack(ObjectType type)
{
    return type == OBJECT_ANT || type == OBJECT_SPIDER;
}

float CHardcodeCollection::GetWaterSplashLevelMin(ObjectType type)
{
    if ( (type == OBJECT_HUMAN ||
          type == OBJECT_TECH  ) )   return 3.0f;

    return 0.0f;
}

float CHardcodeCollection::GetWaterSplashLevelMax(ObjectType type)
{
    if ( (type == OBJECT_HUMAN ||
          type == OBJECT_TECH  ) )   return 3.0f;

    return 9.0f;
}

float CHardcodeCollection::GetWaterSplashDiameter(ObjectType type)
{
    if ( (type == OBJECT_HUMAN ||
          type == OBJECT_TECH  ) )   return 5.0f;

    return 2.5f;
}

float CHardcodeCollection::GetWaterSplashForce(ObjectType type)
{
    if ( (type == OBJECT_HUMAN ||
          type == OBJECT_TECH  ) )   return 1.0f;

    return 1.3f;
}

float CHardcodeCollection::GetLightningRodHeight(ObjectType type)
{
    if (type == OBJECT_BASE)
    {
        return 120.0f;
    }
    if (type == OBJECT_PARA)
    {
        return 67.0f;
    }

    return 0.0f; 
}






//////////////////////////////////////////////////////////////////////////////
// Object naming details
//////////////////////////////////////////////////////////////////////////////

std::string CHardcodeCollection::GetNameInLevelFiles(ObjectType type)
{
    if ( type == OBJECT_PORTICO ) return "Portico";
    if ( type == OBJECT_BASE ) return "SpaceShip";
    if ( type == OBJECT_MOBILEwt ) return "WheeledTrainer";
    if ( type == OBJECT_MOBILEft ) return "WingedTrainer";
    if ( type == OBJECT_MOBILEtt ) return "TrackedTrainer";
    if ( type == OBJECT_MOBILEit ) return "LeggedTrainer";
    if ( type == OBJECT_MOBILErp ) return "HeavyTrainer";
    if ( type == OBJECT_MOBILEst ) return "AmphibiousTrainer";
    if ( type == OBJECT_MOBILEfa ) return "WingedGrabber";
    if ( type == OBJECT_MOBILEta ) return "TrackedGrabber";
    if ( type == OBJECT_MOBILEwa ) return "WheeledGrabber";
    if ( type == OBJECT_MOBILEia ) return "LeggedGrabber";
    if ( type == OBJECT_MOBILEfc ) return "WingedShooter";
    if ( type == OBJECT_MOBILEtc ) return "TrackedShooter";
    if ( type == OBJECT_MOBILEwc ) return "WheeledShooter";
    if ( type == OBJECT_MOBILEic ) return "LeggedShooter";
    if ( type == OBJECT_MOBILEfi ) return "WingedOrgaShooter";
    if ( type == OBJECT_MOBILEti ) return "TrackedOrgaShooter";
    if ( type == OBJECT_MOBILEwi ) return "WheeledOrgaShooter";
    if ( type == OBJECT_MOBILEii ) return "LeggedOrgaShooter";
    if ( type == OBJECT_MOBILEfs ) return "WingedSniffer";
    if ( type == OBJECT_MOBILEts ) return "TrackedSniffer";
    if ( type == OBJECT_MOBILEws ) return "WheeledSniffer";
    if ( type == OBJECT_MOBILEis ) return "LeggedSniffer";
    if ( type == OBJECT_MOBILEfb ) return "WingedBuilder";
    if ( type == OBJECT_MOBILEtb ) return "TrackedBuilder";
    if ( type == OBJECT_MOBILEwb ) return "WheeledBuilder";
    if ( type == OBJECT_MOBILEib ) return "LeggedBuilder";
    if ( type == OBJECT_MOBILErt ) return "Thumper";
    if ( type == OBJECT_MOBILErc ) return "PhazerShooter";
    if ( type == OBJECT_MOBILErr ) return "Recycler";
    if ( type == OBJECT_MOBILErs ) return "Shielder";
    if ( type == OBJECT_MOBILEsa ) return "Subber";
    if ( type == OBJECT_MOBILEtg ) return "TargetBot";
    if ( type == OBJECT_MOBILEdr ) return "Scribbler";
    if ( type == OBJECT_MARKPOWER ) return "PowerSpot";
    if ( type == OBJECT_MARKSTONE ) return "TitaniumSpot";
    if ( type == OBJECT_MARKURANIUM ) return "UraniumSpot";
    if ( type == OBJECT_MARKKEYa ) return "KeyASpot";
    if ( type == OBJECT_MARKKEYb ) return "KeyBSpot";
    if ( type == OBJECT_MARKKEYc ) return "KeyCSpot";
    if ( type == OBJECT_MARKKEYd ) return "KeyDSpot";
    if ( type == OBJECT_WAYPOINT ) return "WayPoint";
    if ( type == OBJECT_FLAGb ) return "BlueFlag";
    if ( type == OBJECT_FLAGr ) return "RedFlag";
    if ( type == OBJECT_FLAGg ) return "GreenFlag";
    if ( type == OBJECT_FLAGy ) return "YellowFlag";
    if ( type == OBJECT_FLAGv ) return "VioletFlag";
    if ( type == OBJECT_POWER ) return "PowerCell";
    if ( type == OBJECT_ATOMIC ) return "NuclearCell";
    if ( type == OBJECT_STONE ) return "TitaniumOre";
    if ( type == OBJECT_URANIUM ) return "UraniumOre";
    if ( type == OBJECT_METAL ) return "Titanium";
    if ( type == OBJECT_BULLET ) return "OrgaMatter";
    if ( type == OBJECT_BBOX ) return "BlackBox";
    if ( type == OBJECT_KEYa ) return "KeyA";
    if ( type == OBJECT_KEYb ) return "KeyB";
    if ( type == OBJECT_KEYc ) return "KeyC";
    if ( type == OBJECT_KEYd ) return "KeyD";
    if ( type == OBJECT_TNT ) return "TNT";
    if ( type == OBJECT_BOMB ) return "Mine";
    if ( type == OBJECT_WINFIRE ) return "Firework";
    if ( type == OBJECT_BAG ) return "Bag";
    if ( type == OBJECT_PLANT0 ) return "Greenery0";
    if ( type == OBJECT_PLANT1 ) return "Greenery1";
    if ( type == OBJECT_PLANT2 ) return "Greenery2";
    if ( type == OBJECT_PLANT3 ) return "Greenery3";
    if ( type == OBJECT_PLANT4 ) return "Greenery4";
    if ( type == OBJECT_PLANT5 ) return "Greenery5";
    if ( type == OBJECT_PLANT6 ) return "Greenery6";
    if ( type == OBJECT_PLANT7 ) return "Greenery7";
    if ( type == OBJECT_PLANT8 ) return "Greenery8";
    if ( type == OBJECT_PLANT9 ) return "Greenery9";
    if ( type == OBJECT_PLANT10 ) return "Greenery10";
    if ( type == OBJECT_PLANT11 ) return "Greenery11";
    if ( type == OBJECT_PLANT12 ) return "Greenery12";
    if ( type == OBJECT_PLANT13 ) return "Greenery13";
    if ( type == OBJECT_PLANT14 ) return "Greenery14";
    if ( type == OBJECT_PLANT15 ) return "Greenery15";
    if ( type == OBJECT_PLANT16 ) return "Greenery16";
    if ( type == OBJECT_PLANT17 ) return "Greenery17";
    if ( type == OBJECT_PLANT18 ) return "Greenery18";
    if ( type == OBJECT_PLANT19 ) return "Greenery19";
    if ( type == OBJECT_TREE0 ) return "Tree0";
    if ( type == OBJECT_TREE1 ) return "Tree1";
    if ( type == OBJECT_TREE2 ) return "Tree2";
    if ( type == OBJECT_TREE3 ) return "Tree3";
    if ( type == OBJECT_TREE4 ) return "Tree4";
    if ( type == OBJECT_TREE5 ) return "Tree5";
    if ( type == OBJECT_MUSHROOM1 ) return "Mushroom1";
    if ( type == OBJECT_MUSHROOM2 ) return "Mushroom2";
    if ( type == OBJECT_HOME1 ) return "Home";
    if ( type == OBJECT_DERRICK ) return "Derrick";
    if ( type == OBJECT_FACTORY ) return "BotFactory";
    if ( type == OBJECT_STATION ) return "PowerStation";
    if ( type == OBJECT_CONVERT ) return "Converter";
    if ( type == OBJECT_REPAIR ) return "RepairCenter";
    if ( type == OBJECT_DESTROYER ) return "Destroyer";
    if ( type == OBJECT_TOWER ) return "DefenseTower";
    if ( type == OBJECT_NEST ) return "AlienNest";
    if ( type == OBJECT_RESEARCH ) return "ResearchCenter";
    if ( type == OBJECT_RADAR ) return "RadarStation";
    if ( type == OBJECT_INFO ) return "ExchangePost";
    if ( type == OBJECT_ENERGY ) return "PowerPlant";
    if ( type == OBJECT_LABO ) return "AutoLab";
    if ( type == OBJECT_NUCLEAR ) return "NuclearPlant";
    if ( type == OBJECT_PARA ) return "PowerCaptor";
    if ( type == OBJECT_SAFE ) return "Vault";
    if ( type == OBJECT_HUSTON ) return "Houston";
    if ( type == OBJECT_TARGET1 ) return "Target1";
    if ( type == OBJECT_TARGET2 ) return "Target2";
    if ( type == OBJECT_START ) return "StartArea";
    if ( type == OBJECT_END ) return "GoalArea";
    if ( type == OBJECT_MOTHER ) return "AlienQueen";
    if ( type == OBJECT_EGG ) return "AlienEgg";
    if ( type == OBJECT_ANT ) return "AlienAnt";
    if ( type == OBJECT_SPIDER ) return "AlienSpider";
    if ( type == OBJECT_BEE ) return "AlienWasp";
    if ( type == OBJECT_WORM ) return "AlienWorm";
    if ( type == OBJECT_RUINmobilew1 ) return "WreckBotw1";
    if ( type == OBJECT_RUINmobilew2 ) return "WreckBotw2";
    if ( type == OBJECT_RUINmobilet1 ) return "WreckBott1";
    if ( type == OBJECT_RUINmobilet2 ) return "WreckBott2";
    if ( type == OBJECT_RUINmobiler1 ) return "WreckBotr1";
    if ( type == OBJECT_RUINmobiler2 ) return "WreckBotr2";
    if ( type == OBJECT_RUINfactory ) return "RuinBotFactory";
    if ( type == OBJECT_RUINdoor ) return "RuinDoor";
    if ( type == OBJECT_RUINsupport ) return "RuinSupport";
    if ( type == OBJECT_RUINradar ) return "RuinRadar";
    if ( type == OBJECT_RUINconvert ) return "RuinConvert";
    if ( type == OBJECT_RUINbase ) return "RuinBaseCamp";
    if ( type == OBJECT_RUINhead ) return "RuinHeadCamp";
    if ( type == OBJECT_BARRIER0 ) return "Barrier0";
    if ( type == OBJECT_BARRIER1 ) return "Barrier1";
    if ( type == OBJECT_BARRIER2 ) return "Barrier2";
    if ( type == OBJECT_BARRIER3 ) return "Barrier3";
    if ( type == OBJECT_BARRICADE0 ) return "Barricade0";
    if ( type == OBJECT_BARRICADE1 ) return "Barricade1";
    if ( type == OBJECT_TEEN0 ) return "Teen0";
    if ( type == OBJECT_TEEN1 ) return "Teen1";
    if ( type == OBJECT_TEEN2 ) return "Teen2";
    if ( type == OBJECT_TEEN3 ) return "Teen3";
    if ( type == OBJECT_TEEN4 ) return "Teen4";
    if ( type == OBJECT_TEEN5 ) return "Teen5";
    if ( type == OBJECT_TEEN6 ) return "Teen6";
    if ( type == OBJECT_TEEN7 ) return "Teen7";
    if ( type == OBJECT_TEEN8 ) return "Teen8";
    if ( type == OBJECT_TEEN9 ) return "Teen9";
    if ( type == OBJECT_TEEN10 ) return "Teen10";
    if ( type == OBJECT_TEEN11 ) return "Teen11";
    if ( type == OBJECT_TEEN12 ) return "Teen12";
    if ( type == OBJECT_TEEN13 ) return "Teen13";
    if ( type == OBJECT_TEEN14 ) return "Teen14";
    if ( type == OBJECT_TEEN15 ) return "Teen15";
    if ( type == OBJECT_TEEN16 ) return "Teen16";
    if ( type == OBJECT_TEEN17 ) return "Teen17";
    if ( type == OBJECT_TEEN18 ) return "Teen18";
    if ( type == OBJECT_TEEN19 ) return "Teen19";
    if ( type == OBJECT_TEEN20 ) return "Teen20";
    if ( type == OBJECT_TEEN21 ) return "Teen21";
    if ( type == OBJECT_TEEN22 ) return "Teen22";
    if ( type == OBJECT_TEEN23 ) return "Teen23";
    if ( type == OBJECT_TEEN24 ) return "Teen24";
    if ( type == OBJECT_TEEN25 ) return "Teen25";
    if ( type == OBJECT_TEEN26 ) return "Teen26";
    if ( type == OBJECT_TEEN27 ) return "Teen27";
    if ( type == OBJECT_TEEN28 ) return "Teen28";
    if ( type == OBJECT_TEEN29 ) return "Teen29";
    if ( type == OBJECT_TEEN30 ) return "Teen30";
    if ( type == OBJECT_TEEN31 ) return "Teen31";
    if ( type == OBJECT_TEEN32 ) return "Teen32";
    if ( type == OBJECT_TEEN33 ) return "Teen33";
    if ( type == OBJECT_TEEN34 ) return "Stone";
    if ( type == OBJECT_TEEN35 ) return "Teen35";
    if ( type == OBJECT_TEEN36 ) return "Teen36";
    if ( type == OBJECT_TEEN37 ) return "Teen37";
    if ( type == OBJECT_TEEN38 ) return "Teen38";
    if ( type == OBJECT_TEEN39 ) return "Teen39";
    if ( type == OBJECT_TEEN40 ) return "Teen40";
    if ( type == OBJECT_TEEN41 ) return "Teen41";
    if ( type == OBJECT_TEEN42 ) return "Teen42";
    if ( type == OBJECT_TEEN43 ) return "Teen43";
    if ( type == OBJECT_TEEN44 ) return "Teen44";
    if ( type == OBJECT_QUARTZ0 ) return "Quartz0";
    if ( type == OBJECT_QUARTZ1 ) return "Quartz1";
    if ( type == OBJECT_QUARTZ2 ) return "Quartz2";
    if ( type == OBJECT_QUARTZ3 ) return "Quartz3";
    if ( type == OBJECT_ROOT0 ) return "MegaStalk0";
    if ( type == OBJECT_ROOT1 ) return "MegaStalk1";
    if ( type == OBJECT_ROOT2 ) return "MegaStalk2";
    if ( type == OBJECT_ROOT3 ) return "MegaStalk3";
    if ( type == OBJECT_ROOT4 ) return "MegaStalk4";
    if ( type == OBJECT_ROOT5 ) return "MegaStalk5";
    if ( type == OBJECT_APOLLO1 ) return "ApolloLEM";
    if ( type == OBJECT_APOLLO2 ) return "ApolloJeep";
    if ( type == OBJECT_APOLLO3 ) return "ApolloFlag";
    if ( type == OBJECT_APOLLO4 ) return "ApolloModule";
    if ( type == OBJECT_APOLLO5 ) return "ApolloAntenna";
    if ( type == OBJECT_HUMAN ) return "Me";
    if ( type == OBJECT_TECH ) return "Tech";
    if ( type == OBJECT_CONTROLLER ) return "MissionController";
    return "";   
}

std::string CHardcodeCollection::GetAliasInLevelFiles(ObjectType type)
{
    if ( type == OBJECT_MOBILEwt    )  return "PracticeBot";
    if ( type == OBJECT_MARKURANIUM )  return "PlatinumSpot";
    if ( type == OBJECT_URANIUM     )  return "PlatinumOre";
    if ( type == OBJECT_ATOMIC      )  return "FuelCell";
    if ( type == OBJECT_NUCLEAR     )  return "FuelCellPlant";
    return "";
}

std::string CHardcodeCollection::GetNameInScriptFiles(ObjectType type)
{
    if ( type == OBJECT_PORTICO     )  return "Portico";
    if ( type == OBJECT_BASE        )  return "SpaceShip";
    if ( type == OBJECT_DERRICK     )  return "Derrick";
    if ( type == OBJECT_FACTORY     )  return "BotFactory";
    if ( type == OBJECT_STATION     )  return "PowerStation";
    if ( type == OBJECT_CONVERT     )  return "Converter";
    if ( type == OBJECT_REPAIR      )  return "RepairCenter";
    if ( type == OBJECT_DESTROYER   )  return "Destroyer";
    if ( type == OBJECT_TOWER       )  return "DefenseTower";
    if ( type == OBJECT_NEST        )  return "AlienNest";
    if ( type == OBJECT_RESEARCH    )  return "ResearchCenter";
    if ( type == OBJECT_RADAR       )  return "RadarStation";
    if ( type == OBJECT_INFO        )  return "ExchangePost";
    if ( type == OBJECT_ENERGY      )  return "PowerPlant";
    if ( type == OBJECT_LABO        )  return "AutoLab";
    if ( type == OBJECT_NUCLEAR     )  return "NuclearPlant";
    if ( type == OBJECT_PARA        )  return "PowerCaptor";
    if ( type == OBJECT_SAFE        )  return "Vault";
    if ( type == OBJECT_HUSTON      )  return "Houston";
    if ( type == OBJECT_TARGET1     )  return "Target1";
    if ( type == OBJECT_TARGET2     )  return "Target2";
    if ( type == OBJECT_START       )  return "StartArea";
    if ( type == OBJECT_END         )  return "GoalArea";
    if ( type == OBJECT_TEEN34      )  return "Stone";
    if ( type == OBJECT_STONE       )  return "TitaniumOre";
    if ( type == OBJECT_URANIUM     )  return "UraniumOre";
    if ( type == OBJECT_METAL       )  return "Titanium";
    if ( type == OBJECT_POWER       )  return "PowerCell";
    if ( type == OBJECT_ATOMIC      )  return "NuclearCell";
    if ( type == OBJECT_BULLET      )  return "OrgaMatter";
    if ( type == OBJECT_BBOX        )  return "BlackBox";
    if ( type == OBJECT_KEYa        )  return "KeyA";
    if ( type == OBJECT_KEYb        )  return "KeyB";
    if ( type == OBJECT_KEYc        )  return "KeyC";
    if ( type == OBJECT_KEYd        )  return "KeyD";
    if ( type == OBJECT_TNT         )  return "TNT";
    if ( type == OBJECT_BOMB        )  return "Mine";
    if ( type == OBJECT_BARRIER1    )  return "Barrier";
    if ( type == OBJECT_WAYPOINT    )  return "WayPoint";
    if ( type == OBJECT_FLAGb       )  return "BlueFlag";
    if ( type == OBJECT_FLAGr       )  return "RedFlag";
    if ( type == OBJECT_FLAGg       )  return "GreenFlag";
    if ( type == OBJECT_FLAGy       )  return "YellowFlag";
    if ( type == OBJECT_FLAGv       )  return "VioletFlag";
    if ( type == OBJECT_MARKPOWER   )  return "PowerSpot";
    if ( type == OBJECT_MARKSTONE   )  return "TitaniumSpot";
    if ( type == OBJECT_MARKURANIUM )  return "UraniumSpot";
    if ( type == OBJECT_MARKKEYa    )  return "KeyASpot";
    if ( type == OBJECT_MARKKEYb    )  return "KeyBSpot";
    if ( type == OBJECT_MARKKEYc    )  return "KeyCSpot";
    if ( type == OBJECT_MARKKEYd    )  return "KeyDSpot";
    if ( type == OBJECT_MOBILEwt    )  return "WheeledTrainer";
    if ( type == OBJECT_MOBILEtt    )  return "TrackedTrainer";
    if ( type == OBJECT_MOBILEft    )  return "WingedTrainer";
    if ( type == OBJECT_MOBILEit    )  return "LeggedTrainer";
    if ( type == OBJECT_MOBILErp    )  return "HeavyTrainer";
    if ( type == OBJECT_MOBILEst    )  return "AmphibiousTrainer";
    if ( type == OBJECT_MOBILEwa    )  return "WheeledGrabber";
    if ( type == OBJECT_MOBILEta    )  return "TrackedGrabber";
    if ( type == OBJECT_MOBILEfa    )  return "WingedGrabber";
    if ( type == OBJECT_MOBILEia    )  return "LeggedGrabber";
    if ( type == OBJECT_MOBILEwc    )  return "WheeledShooter";
    if ( type == OBJECT_MOBILEtc    )  return "TrackedShooter";
    if ( type == OBJECT_MOBILEfc    )  return "WingedShooter";
    if ( type == OBJECT_MOBILEic    )  return "LeggedShooter";
    if ( type == OBJECT_MOBILEwi    )  return "WheeledOrgaShooter";
    if ( type == OBJECT_MOBILEti    )  return "TrackedOrgaShooter";
    if ( type == OBJECT_MOBILEfi    )  return "WingedOrgaShooter";
    if ( type == OBJECT_MOBILEii    )  return "LeggedOrgaShooter";
    if ( type == OBJECT_MOBILEws    )  return "WheeledSniffer";
    if ( type == OBJECT_MOBILEts    )  return "TrackedSniffer";
    if ( type == OBJECT_MOBILEfs    )  return "WingedSniffer";
    if ( type == OBJECT_MOBILEis    )  return "LeggedSniffer";
    if ( type == OBJECT_MOBILEwb    )  return "WheeledBuilder";
    if ( type == OBJECT_MOBILEtb    )  return "TrackedBuilder";
    if ( type == OBJECT_MOBILEfb    )  return "WingedBuilder";
    if ( type == OBJECT_MOBILEib    )  return "LeggedBuilder";
    if ( type == OBJECT_MOBILErt    )  return "Thumper";
    if ( type == OBJECT_MOBILErc    )  return "PhazerShooter";
    if ( type == OBJECT_MOBILErr    )  return "Recycler";
    if ( type == OBJECT_MOBILErs    )  return "Shielder";
    if ( type == OBJECT_MOBILEsa    )  return "Subber";
    if ( type == OBJECT_MOBILEtg    )  return "TargetBot";
    if ( type == OBJECT_MOBILEdr    )  return "Scribbler";
    if ( type == OBJECT_MOBILEpr    )  return "PracticeBot";
    if ( type == OBJECT_HUMAN       )  return "Me";
    if ( type == OBJECT_TECH        )  return "Tech";
    if ( type == OBJECT_MOTHER      )  return "AlienQueen";
    if ( type == OBJECT_EGG         )  return "AlienEgg";
    if ( type == OBJECT_ANT         )  return "AlienAnt";
    if ( type == OBJECT_SPIDER      )  return "AlienSpider";
    if ( type == OBJECT_BEE         )  return "AlienWasp";
    if ( type == OBJECT_WORM        )  return "AlienWorm";
    if ( type == OBJECT_RUINmobilew1)  return "Wreck";
    if ( type == OBJECT_RUINfactory )  return "Ruin";
    if ( type == OBJECT_PLANT0      )  return "Bush";
    if ( type == OBJECT_ROOT5       )  return "GraviPlant";
    if ( type == OBJECT_QUARTZ0     )  return "Crystal";
    if ( type == OBJECT_MUSHROOM1   )  return "BrownMushroom";
    if ( type == OBJECT_MUSHROOM2   )  return "GreenMushroom";
    return "";
}

std::string CHardcodeCollection::GetAliasInScriptFiles(ObjectType type)
{
    if ( type == OBJECT_MARKURANIUM )  return "PlatinumSpot";
    if ( type == OBJECT_URANIUM     )  return "PlatinumOre";
    if ( type == OBJECT_ATOMIC      )  return "FuelCell";
    if ( type == OBJECT_NUCLEAR     )  return "FuelCellPlant";
    return "";
}

std::string CHardcodeCollection::GetHelpTopicPathName(ObjectType type)
{
    if ( type == OBJECT_BASE        )  return "object/base";
    if ( type == OBJECT_DERRICK     )  return "object/derrick";
    if ( type == OBJECT_FACTORY     )  return "object/factory";
    if ( type == OBJECT_STATION     )  return "object/station";
    if ( type == OBJECT_CONVERT     )  return "object/convert";
    if ( type == OBJECT_REPAIR      )  return "object/repair";
    if ( type == OBJECT_DESTROYER   )  return "object/destroy";
    if ( type == OBJECT_TOWER       )  return "object/tower";
    if ( type == OBJECT_NEST        )  return "object/nest";
    if ( type == OBJECT_RESEARCH    )  return "object/research";
    if ( type == OBJECT_RADAR       )  return "object/radar";
    if ( type == OBJECT_INFO        )  return "object/exchange";
    if ( type == OBJECT_ENERGY      )  return "object/energy";
    if ( type == OBJECT_LABO        )  return "object/labo";
    if ( type == OBJECT_NUCLEAR     )  return "object/nuclear";
    if ( type == OBJECT_PARA        )  return "object/captor";
    if ( type == OBJECT_SAFE        )  return "object/safe";
    if ( type == OBJECT_HUSTON      )  return "object/huston";
    if ( type == OBJECT_START       )  return "object/start";
    if ( type == OBJECT_END         )  return "object/goal";
    if ( type == OBJECT_STONE       )  return "object/titanore";
    if ( type == OBJECT_URANIUM     )  return "object/uranore";
    if ( type == OBJECT_METAL       )  return "object/titan";
    if ( type == OBJECT_POWER       )  return "object/power";
    if ( type == OBJECT_ATOMIC      )  return "object/atomic";
    if ( type == OBJECT_BULLET      )  return "object/bullet";
    if ( type == OBJECT_BBOX        )  return "object/bbox";
    if ( type == OBJECT_KEYa        )  return "object/key";
    if ( type == OBJECT_KEYb        )  return "object/key";
    if ( type == OBJECT_KEYc        )  return "object/key";
    if ( type == OBJECT_KEYd        )  return "object/key";
    if ( type == OBJECT_TNT         )  return "object/tnt";
    if ( type == OBJECT_BOMB        )  return "object/mine";
    if ( type == OBJECT_BARRIER1    )  return "object/barrier";
    if ( type == OBJECT_WAYPOINT    )  return "object/waypoint";
    if ( type == OBJECT_FLAGb       )  return "object/flag";
    if ( type == OBJECT_FLAGr       )  return "object/flag";
    if ( type == OBJECT_FLAGg       )  return "object/flag";
    if ( type == OBJECT_FLAGy       )  return "object/flag";
    if ( type == OBJECT_FLAGv       )  return "object/flag";
    if ( type == OBJECT_MARKPOWER   )  return "object/enerspot";
    if ( type == OBJECT_MARKSTONE   )  return "object/stonspot";
    if ( type == OBJECT_MARKURANIUM )  return "object/uranspot";
    if ( type == OBJECT_MOBILEwa    )  return "object/botgr";
    if ( type == OBJECT_MOBILEta    )  return "object/botgc";
    if ( type == OBJECT_MOBILEfa    )  return "object/botgj";
    if ( type == OBJECT_MOBILEia    )  return "object/botgs";
    if ( type == OBJECT_MOBILEws    )  return "object/botsr";
    if ( type == OBJECT_MOBILEts    )  return "object/botsc";
    if ( type == OBJECT_MOBILEfs    )  return "object/botsj";
    if ( type == OBJECT_MOBILEis    )  return "object/botss";
    if ( type == OBJECT_MOBILEwi    )  return "object/botor";
    if ( type == OBJECT_MOBILEti    )  return "object/botoc";
    if ( type == OBJECT_MOBILEfi    )  return "object/botoj";
    if ( type == OBJECT_MOBILEii    )  return "object/botos";
    if ( type == OBJECT_MOBILEwc    )  return "object/botfr";
    if ( type == OBJECT_MOBILEtc    )  return "object/botfc";
    if ( type == OBJECT_MOBILEfc    )  return "object/botfj";
    if ( type == OBJECT_MOBILEic    )  return "object/botfs";
    if ( type == OBJECT_MOBILEwb    )  return "object/botbr";
    if ( type == OBJECT_MOBILEtb    )  return "object/botbc";
    if ( type == OBJECT_MOBILEfb    )  return "object/botbj";
    if ( type == OBJECT_MOBILEib    )  return "object/botbs";
    if ( type == OBJECT_MOBILErt    )  return "object/bottump";
    if ( type == OBJECT_MOBILErc    )  return "object/botphaz";
    if ( type == OBJECT_MOBILErr    )  return "object/botrecy";
    if ( type == OBJECT_MOBILErs    )  return "object/botshld";
    if ( type == OBJECT_MOBILEsa    )  return "object/botsub";
    if ( type == OBJECT_MOBILEwt    )  return "object/bottr";
    if ( type == OBJECT_MOBILEtt    )  return "object/bottr";
    if ( type == OBJECT_MOBILEft    )  return "object/bottr";
    if ( type == OBJECT_MOBILEit    )  return "object/bottr";
    if ( type == OBJECT_MOBILErp    )  return "object/bottr";
    if ( type == OBJECT_MOBILEst    )  return "object/bottr";
    if ( type == OBJECT_MOBILEtg    )  return "object/bottarg";
    if ( type == OBJECT_MOBILEdr    )  return "object/botdraw";
    if ( type == OBJECT_MOBILEpr    )  return "object/bottr";
    if ( type == OBJECT_APOLLO2     )  return "object/lrv";
    if ( type == OBJECT_HUMAN       )  return "object/human";
    if ( type == OBJECT_MOTHER      )  return "object/mother";
    if ( type == OBJECT_EGG         )  return "object/egg";
    if ( type == OBJECT_ANT         )  return "object/ant";
    if ( type == OBJECT_SPIDER      )  return "object/spider";
    if ( type == OBJECT_BEE         )  return "object/wasp";
    if ( type == OBJECT_WORM        )  return "object/worm";
    if ( type == OBJECT_RUINmobilew1)  return "object/wreck";
    if ( type == OBJECT_RUINfactory )  return "object/ruin";
    if ( type == OBJECT_PLANT0      )  return "object/bush";
    if ( type == OBJECT_ROOT5       )  return "object/gravi";
    if ( type == OBJECT_QUARTZ0     )  return "object/crystal";
    if ( type == OBJECT_MUSHROOM1   )  return "object/bromush";
    if ( type == OBJECT_MUSHROOM2   )  return "object/gremush";
    return "";
}

bool CHardcodeCollection::IsDisplayedNameAsPlayer(ObjectType type)
{
    if ( type == OBJECT_HUMAN ) return true;

    return false;
}

std::string CHardcodeCollection::GetDisplayedName(ObjectType type)
{
    if( type == OBJECT_PORTICO ) return TR("Gantry crane");
    if( type == OBJECT_BASE ) return TR("Spaceship");
    if( type == OBJECT_DERRICK ) return TR("Derrick");
    if( type == OBJECT_FACTORY ) return TR("Bot factory");
    if( type == OBJECT_REPAIR ) return TR("Repair center");
    if( type == OBJECT_DESTROYER ) return TR("Destroyer");
    if( type == OBJECT_STATION ) return TR("Power station");
    if( type == OBJECT_CONVERT ) return TR("Converts ore to titanium");
    if( type == OBJECT_TOWER ) return TR("Defense tower");
    if( type == OBJECT_NEST ) return TR("Nest");
    if( type == OBJECT_RESEARCH ) return TR("Research center");
    if( type == OBJECT_RADAR ) return TR("Radar station");
    if( type == OBJECT_INFO ) return TR("Information exchange post");
    if( type == OBJECT_ENERGY ) return TR("Power cell factory");
    if( type == OBJECT_LABO ) return TR("Autolab");
    if( type == OBJECT_NUCLEAR ) return TR("Nuclear power station");
    if( type == OBJECT_PARA ) return TR("Lightning conductor");
    if( type == OBJECT_SAFE ) return TR("Vault");
    if( type == OBJECT_HUSTON ) return TR("Houston Mission Control");
    if( type == OBJECT_TARGET1 ) return TR("Target");
    if( type == OBJECT_TARGET2 ) return TR("Target");
    if( type == OBJECT_START ) return TR("Start");
    if( type == OBJECT_END ) return TR("Finish");
    if( type == OBJECT_STONE ) return TR("Titanium ore");
    if( type == OBJECT_URANIUM ) return TR("Uranium ore");
    if( type == OBJECT_BULLET ) return TR("Organic matter");
    if( type == OBJECT_METAL ) return TR("Titanium");
    if( type == OBJECT_POWER ) return TR("Power cell");
    if( type == OBJECT_ATOMIC ) return TR("Nuclear power cell");
    if( type == OBJECT_BBOX ) return TR("Black box");
    if( type == OBJECT_KEYa ) return TR("Key A");
    if( type == OBJECT_KEYb ) return TR("Key B");
    if( type == OBJECT_KEYc ) return TR("Key C");
    if( type == OBJECT_KEYd ) return TR("Key D");
    if( type == OBJECT_TNT ) return TR("Explosive");
    if( type == OBJECT_BOMB ) return TR("Fixed mine");
    if( type == OBJECT_BAG ) return TR("Survival kit");
    if( type == OBJECT_WAYPOINT ) return TR("Checkpoint");
    if( type == OBJECT_FLAGb ) return TR("Blue flag");
    if( type == OBJECT_FLAGr ) return TR("Red flag");
    if( type == OBJECT_FLAGg ) return TR("Green flag");
    if( type == OBJECT_FLAGy ) return TR("Yellow flag");
    if( type == OBJECT_FLAGv ) return TR("Violet flag");
    if( type == OBJECT_MARKPOWER ) return TR("Energy deposit (site for power station)");
    if( type == OBJECT_MARKURANIUM ) return TR("Uranium deposit (site for derrick)");
    if( type == OBJECT_MARKKEYa ) return TR("Found key A (site for derrick)");
    if( type == OBJECT_MARKKEYb ) return TR("Found key B (site for derrick)");
    if( type == OBJECT_MARKKEYc ) return TR("Found key C (site for derrick)");
    if( type == OBJECT_MARKKEYd ) return TR("Found key D (site for derrick)");
    if( type == OBJECT_MARKSTONE ) return TR("Titanium deposit (site for derrick)");
    if( type == OBJECT_MOBILEft ) return TR("Practice bot");
    if( type == OBJECT_MOBILEtt ) return TR("Practice bot");
    if( type == OBJECT_MOBILEwt ) return TR("Practice bot");
    if( type == OBJECT_MOBILEit ) return TR("Practice bot");
    if( type == OBJECT_MOBILErp ) return TR("Practice bot");
    if( type == OBJECT_MOBILEst ) return TR("Practice bot");
    if( type == OBJECT_MOBILEfa ) return TR("Winged grabber");
    if( type == OBJECT_MOBILEta ) return TR("Tracked grabber");
    if( type == OBJECT_MOBILEwa ) return TR("Wheeled grabber");
    if( type == OBJECT_MOBILEia ) return TR("Legged grabber");
    if( type == OBJECT_MOBILEfb ) return TR("Winged builder");
    if( type == OBJECT_MOBILEtb ) return TR("Tracked builder");
    if( type == OBJECT_MOBILEwb ) return TR("Wheeled builder");
    if( type == OBJECT_MOBILEib ) return TR("Legged builder");
    if( type == OBJECT_MOBILEfc ) return TR("Winged shooter");
    if( type == OBJECT_MOBILEtc ) return TR("Tracked shooter");
    if( type == OBJECT_MOBILEwc ) return TR("Wheeled shooter");
    if( type == OBJECT_MOBILEic ) return TR("Legged shooter");
    if( type == OBJECT_MOBILEfi ) return TR("Winged orga shooter");
    if( type == OBJECT_MOBILEti ) return TR("Tracked orga shooter");
    if( type == OBJECT_MOBILEwi ) return TR("Wheeled orga shooter");
    if( type == OBJECT_MOBILEii ) return TR("Legged orga shooter");
    if( type == OBJECT_MOBILEfs ) return TR("Winged sniffer");
    if( type == OBJECT_MOBILEts ) return TR("Tracked sniffer");
    if( type == OBJECT_MOBILEws ) return TR("Wheeled sniffer");
    if( type == OBJECT_MOBILEis ) return TR("Legged sniffer");
    if( type == OBJECT_MOBILErt ) return TR("Thumper");
    if( type == OBJECT_MOBILErc ) return TR("Phazer shooter");
    if( type == OBJECT_MOBILErr ) return TR("Recycler");
    if( type == OBJECT_MOBILErs ) return TR("Shielder");
    if( type == OBJECT_MOBILEsa ) return TR("Subber");
    if( type == OBJECT_MOBILEtg ) return TR("Target bot");
    if( type == OBJECT_MOBILEdr ) return TR("Drawer bot");
    if( type == OBJECT_TECH ) return TR("Engineer");
    if( type == OBJECT_TOTO ) return TR("Robbie");
    if( type == OBJECT_MOTHER ) return TR("Alien Queen");
    if( type == OBJECT_ANT ) return TR("Ant");
    if( type == OBJECT_SPIDER ) return TR("Spider");
    if( type == OBJECT_BEE ) return TR("Wasp");
    if( type == OBJECT_WORM ) return TR("Worm");
    if( type == OBJECT_EGG ) return TR("Egg");
    if( type == OBJECT_RUINmobilew1 ) return TR("Wreckage");
    if( type == OBJECT_RUINmobilew2 ) return TR("Wreckage");
    if( type == OBJECT_RUINmobilet1 ) return TR("Wreckage");
    if( type == OBJECT_RUINmobilet2 ) return TR("Wreckage");
    if( type == OBJECT_RUINmobiler1 ) return TR("Wreckage");
    if( type == OBJECT_RUINmobiler2 ) return TR("Wreckage");
    if( type == OBJECT_RUINfactory ) return TR("Ruin");
    if( type == OBJECT_RUINdoor ) return TR("Ruin");
    if( type == OBJECT_RUINsupport ) return TR("Waste");
    if( type == OBJECT_RUINradar ) return TR("Ruin");
    if( type == OBJECT_RUINconvert ) return TR("Ruin");
    if( type == OBJECT_RUINbase ) return TR("Spaceship ruin");
    if( type == OBJECT_RUINhead ) return TR("Spaceship ruin");
    if( type == OBJECT_APOLLO1 ) return TR("Remains of Apollo mission");
    if( type == OBJECT_APOLLO3 ) return TR("Remains of Apollo mission");
    if( type == OBJECT_APOLLO4 ) return TR("Remains of Apollo mission");
    if( type == OBJECT_APOLLO5 ) return TR("Remains of Apollo mission");
    if( type == OBJECT_APOLLO2 ) return TR("Lunar Roving Vehicle");
    return "";
}



//////////////////////////////////////////////////////////////////////////////
// Object scripting details
//////////////////////////////////////////////////////////////////////////////

bool CHardcodeCollection::IsFunctionImplementedBuild(ObjectType type)
{
    if ( type != OBJECT_MOBILEfb &&  // allowed only for builder bots && humans
         type != OBJECT_MOBILEtb &&
         type != OBJECT_MOBILEwb &&
         type != OBJECT_MOBILEib &&
         type != OBJECT_HUMAN    &&
         type != OBJECT_TECH      ) return false;
    return true;
}

bool CHardcodeCollection::IsFunctionImplementedFlags(ObjectType type)
{
    if ( type != OBJECT_MOBILEfs &&  // allowed only for sniffer bots && humans
         type != OBJECT_MOBILEts &&
         type != OBJECT_MOBILEws &&
         type != OBJECT_MOBILEis &&
         type != OBJECT_HUMAN    &&
         type != OBJECT_TECH      ) return false;
    return true;
}

bool CHardcodeCollection::IsFunctionImplementedSniff(ObjectType type)
{
    return type == OBJECT_MOBILErs;
}

bool CHardcodeCollection::IsFunctionImplementedShield(ObjectType type)
{
    return type == OBJECT_MOBILErs;
}

bool CHardcodeCollection::IsFunctionImplementedRecycle(ObjectType type)
{
    return type == OBJECT_MOBILErr;
}

bool CHardcodeCollection::IsFunctionImplementedDrawAsRobot(ObjectType type)
{
    return type == OBJECT_MOBILEdr;
}

bool CHardcodeCollection::IsFunctionImplementedGrabAsHuman(ObjectType type)
{
    return type == OBJECT_HUMAN || type == OBJECT_TECH;
}

bool CHardcodeCollection::IsFunctionImplementedGrabAsRobot(ObjectType type)
{
    if ( (type == OBJECT_MOBILEfa ||
          type == OBJECT_MOBILEta ||
          type == OBJECT_MOBILEwa ||
          type == OBJECT_MOBILEia ) )   return true;

    if ( (type == OBJECT_MOBILEsa ||
          type == OBJECT_BEE ) )   return true;

    return false;
}

bool CHardcodeCollection::IsFunctionImplementedShootAsAnt(ObjectType type)
{
    return type == OBJECT_ANT;
}

bool CHardcodeCollection::IsFunctionImplementedShootAsSpider(ObjectType type)
{
    return type == OBJECT_SPIDER;
}

bool CHardcodeCollection::IsFunctionImplementedShootAsRobot(ObjectType type)
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

bool CHardcodeCollection::IsValidObjectTypeId(ObjectType type)
{
    static const std::unordered_set<int> validIds{
        OBJECT_PORTICO,
        OBJECT_BASE,
        OBJECT_DERRICK,
        OBJECT_FACTORY,
        OBJECT_STATION,
        OBJECT_CONVERT,
        OBJECT_REPAIR,
        OBJECT_TOWER,
        OBJECT_NEST,
        OBJECT_RESEARCH,
        OBJECT_RADAR,
        OBJECT_ENERGY,
        OBJECT_LABO,
        OBJECT_NUCLEAR,
        OBJECT_START,
        OBJECT_END,
        OBJECT_INFO,
        OBJECT_PARA,
        OBJECT_TARGET1,
        OBJECT_TARGET2,
        OBJECT_SAFE,
        OBJECT_HUSTON,
        OBJECT_DESTROYER,
        OBJECT_STONE,
        OBJECT_URANIUM,
        OBJECT_METAL,
        OBJECT_POWER,
        OBJECT_ATOMIC,
        OBJECT_BULLET,
        OBJECT_BBOX,
        OBJECT_TNT,
        OBJECT_MARKPOWER,
        OBJECT_MARKSTONE,
        OBJECT_MARKURANIUM,
        OBJECT_MARKKEYa,
        OBJECT_MARKKEYb,
        OBJECT_MARKKEYc,
        OBJECT_MARKKEYd,
        OBJECT_BOMB,
        OBJECT_WINFIRE,
        OBJECT_SHOW,
        OBJECT_BAG,
        OBJECT_PLANT0,
        OBJECT_PLANT1,
        OBJECT_PLANT2,
        OBJECT_PLANT3,
        OBJECT_PLANT4,
        OBJECT_PLANT5,
        OBJECT_PLANT6,
        OBJECT_PLANT7,
        OBJECT_PLANT8,
        OBJECT_PLANT9,
        OBJECT_PLANT10,
        OBJECT_PLANT11,
        OBJECT_PLANT12,
        OBJECT_PLANT13,
        OBJECT_PLANT14,
        OBJECT_PLANT15,
        OBJECT_PLANT16,
        OBJECT_PLANT17,
        OBJECT_PLANT18,
        OBJECT_PLANT19,
        OBJECT_TREE0,
        OBJECT_TREE1,
        OBJECT_TREE2,
        OBJECT_TREE3,
        OBJECT_TREE4,
        OBJECT_TREE5,
        OBJECT_MOBILEwt,
        OBJECT_MOBILEtt,
        OBJECT_MOBILEft,
        OBJECT_MOBILEit,
        OBJECT_MOBILErp,
        OBJECT_MOBILEst,
        OBJECT_MOBILEwa,
        OBJECT_MOBILEta,
        OBJECT_MOBILEfa,
        OBJECT_MOBILEia,
        OBJECT_MOBILEwc,
        OBJECT_MOBILEtc,
        OBJECT_MOBILEfc,
        OBJECT_MOBILEic,
        OBJECT_MOBILEwi,
        OBJECT_MOBILEti,
        OBJECT_MOBILEfi,
        OBJECT_MOBILEii,
        OBJECT_MOBILEws,
        OBJECT_MOBILEts,
        OBJECT_MOBILEfs,
        OBJECT_MOBILEis,
        OBJECT_MOBILErt,
        OBJECT_MOBILErc,
        OBJECT_MOBILErr,
        OBJECT_MOBILErs,
        OBJECT_MOBILEsa,
        OBJECT_MOBILEtg,
        OBJECT_MOBILEdr,
        OBJECT_CONTROLLER,
        OBJECT_MOBILEwb,
        OBJECT_MOBILEtb,
        OBJECT_MOBILEfb,
        OBJECT_MOBILEib,
        OBJECT_WAYPOINT,
        OBJECT_FLAGb,
        OBJECT_FLAGr,
        OBJECT_FLAGg,
        OBJECT_FLAGy,
        OBJECT_FLAGv,
        OBJECT_KEYa,
        OBJECT_KEYb,
        OBJECT_KEYc,
        OBJECT_KEYd,
        OBJECT_HUMAN,
        OBJECT_TOTO,
        OBJECT_TECH,
        OBJECT_BARRIER0,
        OBJECT_BARRIER1,
        OBJECT_BARRIER2,
        OBJECT_BARRIER3,
        OBJECT_BARRICADE0,
        OBJECT_BARRICADE1,
        OBJECT_MOTHER,
        OBJECT_EGG,
        OBJECT_ANT,
        OBJECT_SPIDER,
        OBJECT_BEE,
        OBJECT_WORM,
        OBJECT_RUINmobilew1,
        OBJECT_RUINmobilew2,
        OBJECT_RUINmobilet1,
        OBJECT_RUINmobilet2,
        OBJECT_RUINmobiler1,
        OBJECT_RUINmobiler2,
        OBJECT_RUINfactory,
        OBJECT_RUINdoor,
        OBJECT_RUINsupport,
        OBJECT_RUINradar,
        OBJECT_RUINconvert,
        OBJECT_RUINbase,
        OBJECT_RUINhead,
        OBJECT_TEEN0,
        OBJECT_TEEN1,
        OBJECT_TEEN2,
        OBJECT_TEEN3,
        OBJECT_TEEN4,
        OBJECT_TEEN5,
        OBJECT_TEEN6,
        OBJECT_TEEN7,
        OBJECT_TEEN8,
        OBJECT_TEEN9,
        OBJECT_TEEN10,
        OBJECT_TEEN11,
        OBJECT_TEEN12,
        OBJECT_TEEN13,
        OBJECT_TEEN14,
        OBJECT_TEEN15,
        OBJECT_TEEN16,
        OBJECT_TEEN17,
        OBJECT_TEEN18,
        OBJECT_TEEN19,
        OBJECT_TEEN20,
        OBJECT_TEEN21,
        OBJECT_TEEN22,
        OBJECT_TEEN23,
        OBJECT_TEEN24,
        OBJECT_TEEN25,
        OBJECT_TEEN26,
        OBJECT_TEEN27,
        OBJECT_TEEN28,
        OBJECT_TEEN29,
        OBJECT_TEEN30,
        OBJECT_TEEN31,
        OBJECT_TEEN32,
        OBJECT_TEEN33,
        OBJECT_TEEN34,
        OBJECT_TEEN35,
        OBJECT_TEEN36,
        OBJECT_TEEN37,
        OBJECT_TEEN38,
        OBJECT_TEEN39,
        OBJECT_TEEN40,
        OBJECT_TEEN41,
        OBJECT_TEEN42,
        OBJECT_TEEN43,
        OBJECT_TEEN44,
        OBJECT_QUARTZ0,
        OBJECT_QUARTZ1,
        OBJECT_QUARTZ2,
        OBJECT_QUARTZ3,
        OBJECT_ROOT0,
        OBJECT_ROOT1,
        OBJECT_ROOT2,
        OBJECT_ROOT3,
        OBJECT_ROOT4,
        OBJECT_ROOT5,
        OBJECT_MUSHROOM1,
        OBJECT_MUSHROOM2,
        OBJECT_APOLLO1,
        OBJECT_APOLLO2,
        OBJECT_APOLLO3,
        OBJECT_APOLLO4,
        OBJECT_APOLLO5,
        OBJECT_HOME1,
    };
    return validIds.count(type);
}

std::vector<ObjectType> CHardcodeCollection::GetObjectsFindableByType(ObjectType type)
{
    std::vector<ObjectType> result;

    if ( type == OBJECT_MOBILEpr)
    {
        result.push_back(OBJECT_MOBILEwt);
        result.push_back(OBJECT_MOBILEtt);
        result.push_back(OBJECT_MOBILEft);
        result.push_back(OBJECT_MOBILEit);
        result.push_back(OBJECT_MOBILErp);
        result.push_back(OBJECT_MOBILEst);
    }



    return result;
}

ObjectType CHardcodeCollection::GetProduceContainer(ObjectType type)
{
    if (type == OBJECT_ANT   ||
        type == OBJECT_SPIDER ||
        type == OBJECT_BEE    ||
        type == OBJECT_WORM   ) return OBJECT_EGG;

    return OBJECT_NULL;
}

bool CHardcodeCollection::IsProduceAlreadyCharged(ObjectType type)
{
    return (type == OBJECT_POWER || type == OBJECT_ATOMIC);
}

bool CHardcodeCollection::IsProduceManual(ObjectType type)
{
    return (type == OBJECT_MOBILEdr);
}

bool CHardcodeCollection::IsRadarExplicitOnly(ObjectType type)
{
    return (type == OBJECT_TOTO || type == OBJECT_CONTROLLER);
}

ObjectType CHardcodeCollection::GetBaseType(ObjectType type)
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


//////////////////////////////////////////////////////////////////////////////
// Creation details
//////////////////////////////////////////////////////////////////////////////

BaseClass CHardcodeCollection::GetCreationBaseClass(ObjectType type)
{
    switch(type)
    {
        case OBJECT_PORTICO:
        case OBJECT_BASE:
        case OBJECT_DERRICK:
        case OBJECT_FACTORY:
        case OBJECT_STATION:
        case OBJECT_CONVERT:
        case OBJECT_REPAIR:
        case OBJECT_DESTROYER:
        case OBJECT_TOWER:
        case OBJECT_NEST:
        case OBJECT_RESEARCH:
        case OBJECT_RADAR:
        case OBJECT_ENERGY:
        case OBJECT_LABO:
        case OBJECT_NUCLEAR:
        case OBJECT_PARA:
        case OBJECT_SAFE:
        case OBJECT_HUSTON:
        case OBJECT_TARGET1:
        case OBJECT_TARGET2:
        case OBJECT_START:
        case OBJECT_END:
            return BASE_CLASS_BUILDING;

        case OBJECT_INFO:
            return BASE_CLASS_INFO;

        case OBJECT_STONE:
        case OBJECT_URANIUM:
        case OBJECT_METAL:
        case OBJECT_POWER:
        case OBJECT_ATOMIC:
        case OBJECT_BULLET:
        case OBJECT_BBOX:
        case OBJECT_KEYa:
        case OBJECT_KEYb:
        case OBJECT_KEYc:
        case OBJECT_KEYd:
        case OBJECT_TNT:
        case OBJECT_BOMB:
        case OBJECT_WAYPOINT:
        case OBJECT_SHOW:
        case OBJECT_WINFIRE:
        case OBJECT_BAG:
        case OBJECT_MARKPOWER:
        case OBJECT_MARKSTONE:
        case OBJECT_MARKURANIUM:
        case OBJECT_MARKKEYa:
        case OBJECT_MARKKEYb:
        case OBJECT_MARKKEYc:
        case OBJECT_MARKKEYd:
        case OBJECT_EGG:
            return BASE_CLASS_SIMPLE;

        case OBJECT_FLAGb:
        case OBJECT_FLAGr:
        case OBJECT_FLAGg:
        case OBJECT_FLAGy:
        case OBJECT_FLAGv:
            return BASE_CLASS_SIMPLE;

        case OBJECT_BARRIER0:
        case OBJECT_BARRIER1:
        case OBJECT_BARRIER2:
        case OBJECT_BARRIER3:
        case OBJECT_BARRICADE0:
        case OBJECT_BARRICADE1:
            return BASE_CLASS_SIMPLE;

        case OBJECT_PLANT0:
        case OBJECT_PLANT1:
        case OBJECT_PLANT2:
        case OBJECT_PLANT3:
        case OBJECT_PLANT4:
        case OBJECT_PLANT5:
        case OBJECT_PLANT6:
        case OBJECT_PLANT7:
        case OBJECT_PLANT8:
        case OBJECT_PLANT9:
        case OBJECT_PLANT10:
        case OBJECT_PLANT11:
        case OBJECT_PLANT12:
        case OBJECT_PLANT13:
        case OBJECT_PLANT14:
        case OBJECT_PLANT15:
        case OBJECT_PLANT16:
        case OBJECT_PLANT17:
        case OBJECT_PLANT18:
        case OBJECT_PLANT19:
        case OBJECT_TREE0:
        case OBJECT_TREE1:
        case OBJECT_TREE2:
        case OBJECT_TREE3:
        case OBJECT_TREE4:
        case OBJECT_TREE5:
            return BASE_CLASS_SIMPLE;

        case OBJECT_MUSHROOM1:
        case OBJECT_MUSHROOM2:
            return BASE_CLASS_SIMPLE;

        case OBJECT_TEEN0:
        case OBJECT_TEEN1:
        case OBJECT_TEEN2:
        case OBJECT_TEEN3:
        case OBJECT_TEEN4:
        case OBJECT_TEEN5:
        case OBJECT_TEEN6:
        case OBJECT_TEEN7:
        case OBJECT_TEEN8:
        case OBJECT_TEEN9:
        case OBJECT_TEEN10:
        case OBJECT_TEEN11:
        case OBJECT_TEEN12:
        case OBJECT_TEEN13:
        case OBJECT_TEEN14:
        case OBJECT_TEEN15:
        case OBJECT_TEEN16:
        case OBJECT_TEEN17:
        case OBJECT_TEEN18:
        case OBJECT_TEEN19:
        case OBJECT_TEEN20:
        case OBJECT_TEEN21:
        case OBJECT_TEEN22:
        case OBJECT_TEEN23:
        case OBJECT_TEEN24:
        case OBJECT_TEEN25:
        case OBJECT_TEEN26:
        case OBJECT_TEEN27:
        case OBJECT_TEEN28:
        case OBJECT_TEEN29:
        case OBJECT_TEEN30:
        case OBJECT_TEEN31:
        case OBJECT_TEEN32:
        case OBJECT_TEEN33:
        case OBJECT_TEEN34:
        case OBJECT_TEEN35:
        case OBJECT_TEEN36:
        case OBJECT_TEEN37:
        case OBJECT_TEEN38:
        case OBJECT_TEEN39:
        case OBJECT_TEEN40:
        case OBJECT_TEEN41:
        case OBJECT_TEEN42:
        case OBJECT_TEEN43:
        case OBJECT_TEEN44:
            return BASE_CLASS_SIMPLE;

        case OBJECT_QUARTZ0:
        case OBJECT_QUARTZ1:
        case OBJECT_QUARTZ2:
        case OBJECT_QUARTZ3:
            return BASE_CLASS_SIMPLE;

        case OBJECT_ROOT0:
        case OBJECT_ROOT1:
        case OBJECT_ROOT2:
        case OBJECT_ROOT3:
        case OBJECT_ROOT4:
        case OBJECT_ROOT5:
            return BASE_CLASS_SIMPLE;

        case OBJECT_HOME1:
            return BASE_CLASS_SIMPLE;

        case OBJECT_RUINmobilew1:
        case OBJECT_RUINmobilew2:
        case OBJECT_RUINmobilet1:
        case OBJECT_RUINmobilet2:
        case OBJECT_RUINmobiler1:
        case OBJECT_RUINmobiler2:
        case OBJECT_RUINfactory:
        case OBJECT_RUINdoor:
        case OBJECT_RUINsupport:
        case OBJECT_RUINradar:
        case OBJECT_RUINconvert:
        case OBJECT_RUINbase:
        case OBJECT_RUINhead:
            return BASE_CLASS_SIMPLE;

        case OBJECT_APOLLO1:
        case OBJECT_APOLLO3:
        case OBJECT_APOLLO4:
        case OBJECT_APOLLO5:
            return BASE_CLASS_SIMPLE;

        case OBJECT_CONTROLLER:
            return BASE_CLASS_SIMPLE;

        case OBJECT_MOTHER:
        case OBJECT_ANT:
        case OBJECT_SPIDER:
        case OBJECT_BEE:
        case OBJECT_WORM:
            return BASE_CLASS_MOVABLE;

        case OBJECT_HUMAN:
        case OBJECT_TECH:
        case OBJECT_TOTO:
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
        case OBJECT_MOBILEsa:
        case OBJECT_MOBILEtg:
        case OBJECT_MOBILEft:
        case OBJECT_MOBILEtt:
        case OBJECT_MOBILEwt:
        case OBJECT_MOBILEit:
        case OBJECT_MOBILErp:
        case OBJECT_MOBILEst:
        case OBJECT_MOBILEdr:
        case OBJECT_APOLLO2:
            return BASE_CLASS_MOVABLE;

        case OBJECT_MOBILErs:
            return BASE_CLASS_SHIELDER;

        default:
            return BASE_CLASS_SIMPLE;
    }
}

AutoClass CHardcodeCollection::GetCreationAutoClass(ObjectType type)
{

    if ( type == OBJECT_EGG )       return AUTO_CLASS_EGG;
    if ( type == OBJECT_ROOT5 )     return AUTO_CLASS_ROOT;
    if ( type == OBJECT_MUSHROOM2 ) return AUTO_CLASS_MUSHROOM;
    if ( type == OBJECT_FLAGb ||
         type == OBJECT_FLAGr ||
         type == OBJECT_FLAGg ||
         type == OBJECT_FLAGy ||
         type == OBJECT_FLAGv )     return AUTO_CLASS_FLAG;
    if ( type == OBJECT_TEEN36 )    return AUTO_CLASS_TRUNK;   // trunk?
    if ( type == OBJECT_TEEN37 )    return AUTO_CLASS_BOAT;    // boat?
    if ( type == OBJECT_TEEN38 )    return AUTO_CLASS_FAN;     // fan?

    return AUTO_CLASS_NONE;
}

std::vector<CObjectCreationModelNode> CHardcodeCollection::GetCreationModel(ObjectType type)
{
    std::vector<CObjectCreationModelNode> result;

    std::string name;
    if ( type == OBJECT_STONE       )  name = "stone.mod";
    if ( type == OBJECT_URANIUM     )  name = "uranium.mod";
    if ( type == OBJECT_METAL       )  name = "metal.mod";
    if ( type == OBJECT_BULLET      )  name = "bullet.mod";
    if ( type == OBJECT_BBOX        )  name = "bbox.mod";
    if ( type == OBJECT_KEYa        )  name = "keya.mod";
    if ( type == OBJECT_KEYb        )  name = "keyb.mod";
    if ( type == OBJECT_KEYc        )  name = "keyc.mod";
    if ( type == OBJECT_KEYd        )  name = "keyd.mod";
    if ( type == OBJECT_TNT         )  name = "tnt.mod";
    if ( type == OBJECT_BOMB        )  name = "bomb.mod";
    if ( type == OBJECT_WAYPOINT    )  name = "waypoint.mod";
    if ( type == OBJECT_SHOW        )  name = "show.mod";
    if ( type == OBJECT_WINFIRE     )  name = "winfire.mod";
    if ( type == OBJECT_MARKSTONE   )  name = "cross1.mod";
    if ( type == OBJECT_MARKURANIUM )  name = "cross3.mod";
    if ( type == OBJECT_MARKPOWER   )  name = "cross2.mod";
    if ( type == OBJECT_MARKKEYa    )  name = "crossa.mod";
    if ( type == OBJECT_MARKKEYb    )  name = "crossb.mod";
    if ( type == OBJECT_MARKKEYc    )  name = "crossc.mod";
    if ( type == OBJECT_MARKKEYd    )  name = "crossd.mod";
    if ( name.size() > 0 )
    {
        result.push_back({0, -1, Gfx::ENG_OBJTYPE_FIX, name});
        return result;
    }

    if ( type == OBJECT_BAG         )  name = "bag.mod";
    if ( type == OBJECT_EGG         )  name = "egg.mod";
    if ( name.size() > 0 )
    {
        result.push_back({0, -1, Gfx::ENG_OBJTYPE_FIX, name, Math::Vector(0.0f, -1.4f, 0.0f)});
        return result;
    }

    if ( type == OBJECT_POWER       )  name = "power.mod";
    if ( type == OBJECT_ATOMIC      )  name = "atomic.mod";
    if ( name.size() > 0 )
    {
        result.push_back({0, -1, Gfx::ENG_OBJTYPE_FIX, name, Math::Vector(), Math::Vector(), true});
        return result;
    }

    if ( type == OBJECT_FLAGb )  name = "flag1b.mod";
    if ( type == OBJECT_FLAGr )  name = "flag1r.mod";
    if ( type == OBJECT_FLAGg )  name = "flag1g.mod";
    if ( type == OBJECT_FLAGy )  name = "flag1y.mod";
    if ( type == OBJECT_FLAGv )  name = "flag1v.mod";
    if ( name.size() > 0 )
    {
        result.push_back({0, -1, Gfx::ENG_OBJTYPE_FIX, name});
    }
    if ( type == OBJECT_FLAGb )  name = "flag2b.mod";
    if ( type == OBJECT_FLAGr )  name = "flag2r.mod";
    if ( type == OBJECT_FLAGg )  name = "flag2g.mod";
    if ( type == OBJECT_FLAGy )  name = "flag2y.mod";
    if ( type == OBJECT_FLAGv )  name = "flag2v.mod";
    if ( name.size() > 0 )
    {
        result.push_back({1, 0, Gfx::ENG_OBJTYPE_DESCENDANT, name, Math::Vector(0.15f, 5.0f, 0.0f)});
        result.push_back({2, 1, Gfx::ENG_OBJTYPE_DESCENDANT, name, Math::Vector(0.79f, 0.0f, 0.0f)});
        result.push_back({3, 2, Gfx::ENG_OBJTYPE_DESCENDANT, name, Math::Vector(0.79f, 0.0f, 0.0f)});
        result.push_back({4, 3, Gfx::ENG_OBJTYPE_DESCENDANT, name, Math::Vector(0.79f, 0.0f, 0.0f)});
        return result;
    }

    if ( type == OBJECT_BARRIER0 ) name = "barrier0.mod";
    if ( type == OBJECT_BARRIER1 ) name = "barrier1.mod";
    if ( type == OBJECT_BARRIER2 ) name = "barrier2.mod";
    if ( type == OBJECT_BARRIER3 ) name = "barrier3.mod";
    if ( type == OBJECT_BARRICADE0 ) name = "barricade0.mod";
    if ( type == OBJECT_BARRICADE1 ) name = "barricade1.mod";
    if ( name.size() > 0 )
    {
        result.push_back({0, -1, Gfx::ENG_OBJTYPE_FIX, name});
        return result;
    }

    if ( type == OBJECT_PLANT0 ) name = "plant0.mod";
    if ( type == OBJECT_PLANT1 ) name = "plant1.mod";
    if ( type == OBJECT_PLANT2 ) name = "plant2.mod";
    if ( type == OBJECT_PLANT3 ) name = "plant3.mod";
    if ( type == OBJECT_PLANT4 ) name = "plant4.mod";
    if ( name.size() > 0 )
    {
        result.push_back({0, -1, Gfx::ENG_OBJTYPE_FIX, name, Math::Vector(0.0f, -2.0f, 0.0f)});
        return result;
    }

    if ( type == OBJECT_PLANT5 ) name = "plant5.mod";
    if ( type == OBJECT_PLANT6 ) name = "plant6.mod";
    if ( type == OBJECT_PLANT7 ) name = "plant7.mod";
    if ( type == OBJECT_PLANT8 ) name = "plant8.mod";
    if ( type == OBJECT_PLANT9 ) name = "plant9.mod";
    if ( type == OBJECT_PLANT10 ) name = "plant10.mod";
    if ( type == OBJECT_PLANT11 ) name = "plant11.mod";
    if ( type == OBJECT_PLANT12 ) name = "plant12.mod";
    if ( type == OBJECT_PLANT13 ) name = "plant13.mod";
    if ( type == OBJECT_PLANT14 ) name = "plant14.mod";
    if ( type == OBJECT_PLANT15 ) name = "plant15.mod";
    if ( type == OBJECT_PLANT16 ) name = "plant16.mod";
    if ( type == OBJECT_PLANT17 ) name = "plant17.mod";
    if ( type == OBJECT_PLANT18 ) name = "plant18.mod";
    if ( type == OBJECT_PLANT19 ) name = "plant19.mod";
    if ( type == OBJECT_TREE0 ) name = "tree0.mod";
    if ( type == OBJECT_TREE1 ) name = "tree1.mod";
    if ( type == OBJECT_TREE2 ) name = "tree2.mod";
    if ( type == OBJECT_TREE3 ) name = "tree3.mod";
    if ( type == OBJECT_TREE4 ) name = "tree4.mod";
    if ( type == OBJECT_TREE5 ) name = "tree5.mod";
    if ( name.size() > 0 )
    {
        result.push_back({0, -1, Gfx::ENG_OBJTYPE_FIX, name});
        return result;
    }

    if ( type == OBJECT_MUSHROOM1 ) name = "mush1.mod";
    if ( type == OBJECT_MUSHROOM2 ) name = "mush2.mod";
    if ( name.size() > 0 )
    {
        result.push_back({0, -1, Gfx::ENG_OBJTYPE_FIX, name});
        return result;
    }

    if ( type == OBJECT_TEEN0 ) name = "teen0.mod";
    if ( type == OBJECT_TEEN1 ) name = "teen1.mod";
    if ( type == OBJECT_TEEN2 ) name = "teen2.mod";
    if ( type == OBJECT_TEEN4 ) name = "teen4.mod";
    if ( type == OBJECT_TEEN5 ) name = "teen5.mod";
    if ( type == OBJECT_TEEN6 ) name = "teen6.mod";
    if ( type == OBJECT_TEEN7 ) name = "teen7.mod";
    if ( type == OBJECT_TEEN8 ) name = "teen8.mod";
    if ( type == OBJECT_TEEN9 ) name = "teen9.mod";
    if ( type == OBJECT_TEEN10 ) name = "teen10.mod";
    if ( type == OBJECT_TEEN11 ) name = "teen11.mod";
    if ( type == OBJECT_TEEN13 ) name = "teen13.mod";
    if ( type == OBJECT_TEEN14 ) name = "teen14.mod";
    if ( type == OBJECT_TEEN15 ) name = "teen15.mod";
    if ( type == OBJECT_TEEN16 ) name = "teen16.mod";
    if ( type == OBJECT_TEEN17 ) name = "teen17.mod";
    if ( type == OBJECT_TEEN18 ) name = "teen18.mod";
    if ( type == OBJECT_TEEN19 ) name = "teen19.mod";
    if ( type == OBJECT_TEEN20 ) name = "teen20.mod";
    if ( type == OBJECT_TEEN21 ) name = "teen21.mod";
    if ( type == OBJECT_TEEN22 ) name = "teen22.mod";
    if ( type == OBJECT_TEEN23 ) name = "teen23.mod";
    if ( type == OBJECT_TEEN24 ) name = "teen24.mod";
    if ( type == OBJECT_TEEN25 ) name = "teen25.mod";
    if ( type == OBJECT_TEEN26 ) name = "teen26.mod";
    if ( type == OBJECT_TEEN27 ) name = "teen27.mod";
    if ( type == OBJECT_TEEN29 ) name = "teen29.mod";
    if ( type == OBJECT_TEEN30 ) name = "teen30.mod";
    if ( type == OBJECT_TEEN31 ) name = "teen31.mod";
    if ( type == OBJECT_TEEN32 ) name = "teen32.mod";
    if ( type == OBJECT_TEEN33 ) name = "teen33.mod";
    if ( type == OBJECT_TEEN34 ) name = "teen34.mod";
    if ( type == OBJECT_TEEN35 ) name = "teen35.mod";
    if ( type == OBJECT_TEEN36 ) name = "teen36.mod";
    if ( type == OBJECT_TEEN37 ) name = "teen37.mod";
    if ( type == OBJECT_TEEN39 ) name = "teen39.mod";
    if ( type == OBJECT_TEEN40 ) name = "teen40.mod";
    if ( type == OBJECT_TEEN41 ) name = "teen41.mod";
    if ( type == OBJECT_TEEN42 ) name = "teen42.mod";
    if ( type == OBJECT_TEEN43 ) name = "teen43.mod";
    if ( type == OBJECT_TEEN44 ) name = "teen44.mod";
    if ( name.size() > 0 )
    {
        result.push_back({0, -1, Gfx::ENG_OBJTYPE_FIX, name});
        return result;
    }

    if ( type == OBJECT_TEEN3 )  name = "teen3.mod";
    if ( type == OBJECT_TEEN12 ) name = "teen12.mod";
    if ( type == OBJECT_TEEN28 ) name = "teen28.mod";
    if ( name.size() > 0 )
    {
        result.push_back({0, -1, Gfx::ENG_OBJTYPE_METAL, name});
        return result;
    }

    if ( type == OBJECT_TEEN38 )
    {
        result.push_back({0, -1, Gfx::ENG_OBJTYPE_FIX,        "teen38a.mod"});
        result.push_back({1,  0, Gfx::ENG_OBJTYPE_DESCENDANT, "teen38b.mod", Math::Vector(0.0f, 30.0f, 0.0f)}); // engine
        result.push_back({2,  1, Gfx::ENG_OBJTYPE_DESCENDANT, "teen38c.mod"});  // propeller
        return result;
    }

    if ( type == OBJECT_QUARTZ0 ) name = "quartz0.mod";
    if ( type == OBJECT_QUARTZ1 ) name = "quartz1.mod";
    if ( type == OBJECT_QUARTZ2 ) name = "quartz2.mod";
    if ( type == OBJECT_QUARTZ3 ) name = "quartz3.mod";
    if ( name.size() > 0 )
    {
        result.push_back({0, -1, Gfx::ENG_OBJTYPE_QUARTZ, name});
        return result;
    }


    if ( type == OBJECT_ROOT0 ) name = "root0.mod";
    if ( type == OBJECT_ROOT1 ) name = "root1.mod";
    if ( type == OBJECT_ROOT2 ) name = "root2.mod";
    if ( type == OBJECT_ROOT3 ) name = "root3.mod";
    if ( type == OBJECT_ROOT4 ) name = "root4.mod";
    if ( type == OBJECT_HOME1 ) name = "home1.mod";
    if ( name.size() > 0 )
    {
        result.push_back({0, -1, Gfx::ENG_OBJTYPE_FIX, name});
        return result;
    }

    if ( type == OBJECT_ROOT5 )
    {
        result.push_back({0, -1, Gfx::ENG_OBJTYPE_FIX,        "root4.mod"});
        result.push_back({1,  0, Gfx::ENG_OBJTYPE_DESCENDANT, "root5.mod", Math::Vector(-5.0f, 28.0f, -4.0f), Math::Vector(-30.0f*Math::PI/180.0f, 0.0f, 20.0f*Math::PI/180.0f)});
        return result;
    }

    if ( type == OBJECT_RUINmobilew1 )  // vehicle had wheels?
    {
        result.push_back({0, -1, Gfx::ENG_OBJTYPE_FIX,        "ruin1.mod",  Math::Vector( 0.0f, -0.5f, 0.0f), Math::Vector(-0.1f, 0.0f, 0.0f)});
        result.push_back({6,  0, Gfx::ENG_OBJTYPE_DESCENDANT, "ruin1w.mod", Math::Vector(-3.0f, 1.8f, -4.0f), Math::Vector(-Math::PI/2.0f, 0.0f, 0.0f)}); // Creates the right-back wheel
        result.push_back({7,  0, Gfx::ENG_OBJTYPE_DESCENDANT, "ruin1w.mod", Math::Vector(-3.0f, 1.0f,  3.0f), Math::Vector(-0.3f, Math::PI-0.3f, 0.0f)}); // Creates the left-back wheel
        result.push_back({8,  0, Gfx::ENG_OBJTYPE_DESCENDANT, "ruin1w.mod", Math::Vector( 2.0f, 1.6f, -3.0f), Math::Vector(0.0f, 0.3f, 0.0f)}); // Creates the right-front wheel
        result.push_back({9,  0, Gfx::ENG_OBJTYPE_DESCENDANT, "ruin1w.mod", Math::Vector( 2.0f, 1.0f,  3.0f), Math::Vector(0.2f, Math::PI-0.2f, 0.0f)}); // Creates the left-front wheel
        return result;
    }

    if ( type == OBJECT_RUINmobilew2 )  // vehicle had wheels?
    {
        result.push_back({0, -1, Gfx::ENG_OBJTYPE_FIX,        "ruin1.mod",  Math::Vector(0.0f, -1.5f, 0.0f),  Math::Vector(-0.9f, 0.0f, 0.1f)});
        result.push_back({7,  0, Gfx::ENG_OBJTYPE_DESCENDANT, "ruin1w.mod", Math::Vector(-3.0f, 1.0f, 3.0f),  Math::Vector(0.4f, Math::PI+0.3f, 0.0f)}); // Creates the left-back wheel
        result.push_back({9,  0, Gfx::ENG_OBJTYPE_DESCENDANT, "ruin1w.mod", Math::Vector(2.0f, 1.0f, 3.0f),   Math::Vector(-0.3f, Math::PI+0.3f, 0.0f)}); // Creates the left-front wheel
        return result;
    }

    if ( type == OBJECT_RUINmobilet1 )  // vehicle had wheels?
    {
        result.push_back({0, -1, Gfx::ENG_OBJTYPE_FIX,        "ruin2.mod",  Math::Vector(0.0f, -0.9f, 0.0f),  Math::Vector(-0.3f, 0.0f, 0.0f)});
        result.push_back({1,  0, Gfx::ENG_OBJTYPE_DESCENDANT, "ruin2c.mod", Math::Vector(3.0f, 5.0f, -2.5f),  Math::Vector(-Math::PI*0.85f, -0.4f, -0.1f)}); // Creates the left track
        return result;
    }

    if ( type == OBJECT_RUINmobilet2 )
    {
        result.push_back({0, -1, Gfx::ENG_OBJTYPE_FIX, "ruin2.mod", Math::Vector(0.0f, -1.5f, 0.0f), Math::Vector(-0.3f, 0.0f, 0.8f)});
        return result;
    }

    if ( type == OBJECT_RUINmobiler1 )
    {
        result.push_back({0, -1, Gfx::ENG_OBJTYPE_FIX, "ruin3.mod", Math::Vector(0.0f, 4.0f, 0.0f), Math::Vector(-Math::PI*0.6f, 0.0f, -0.2f)});
        return result;
    }

    if ( type == OBJECT_RUINmobiler2 )
    {
        result.push_back({0, -1, Gfx::ENG_OBJTYPE_FIX, "ruin3.mod", Math::Vector(0.0f, 2.0f, 0.0f), Math::Vector(-0.1f, 0.0f, -0.3f)});
        return result;
    }

    if ( type == OBJECT_RUINfactory  )
    {
        result.push_back({0, -1, Gfx::ENG_OBJTYPE_FIX, "ruin4.mod"});
        return result;
    }

    if ( type == OBJECT_RUINdoor     )
    {
        result.push_back({0, -1, Gfx::ENG_OBJTYPE_FIX, "ruin5.mod", Math::Vector(0.0f, -0.5f, 0.0f), Math::Vector(0.1f, 0.0f, -0.1f)});
        return result;
    }

    if ( type == OBJECT_RUINsupport  )
    {
        result.push_back({0, -1, Gfx::ENG_OBJTYPE_FIX, "ruin6.mod", Math::Vector(0.0f, 0.5f, 0.0f), Math::Vector(0.1f, 0.0f, 0.1f)});
        return result;
    }

    if ( type == OBJECT_RUINradar    )
    {
        result.push_back({0, -1, Gfx::ENG_OBJTYPE_FIX, "ruin7.mod", Math::Vector(0.0f, -0.5f, 0.0f), Math::Vector(0.15f, 0.0f, 0.1f)});
        return result;
    }

    if ( type == OBJECT_RUINconvert  )
    {
        result.push_back({0, -1, Gfx::ENG_OBJTYPE_FIX, "ruin8.mod"});
        return result;
    }

    if ( type == OBJECT_RUINbase     )
    {
        result.push_back({0, -1, Gfx::ENG_OBJTYPE_FIX, "ruin9.mod", Math::Vector(0.0f, -1.0f, 0.0f), Math::Vector(0.15f, 0.0f, 0.0f)});
        return result;
    }

    if ( type == OBJECT_RUINhead     )
    {
        result.push_back({0, -1, Gfx::ENG_OBJTYPE_FIX, "ruin10.mod", Math::Vector(0.0f, 8.0f, 0.0f), Math::Vector(Math::PI*0.4f, 0.0f, 0.0f)});
        return result;
    }

    if ( type == OBJECT_APOLLO1 )
    {
        result.push_back({0, -1, Gfx::ENG_OBJTYPE_FIX,        "apollol1.mod"});
        for (int i=0 ; i<4 ; i++ )  // creates feet
            result.push_back({i+1,  0, Gfx::ENG_OBJTYPE_DESCENDANT, "apollol2.mod", Math::Vector(),  Math::Vector(0.0f, Math::PI/2.0f*i, 0)});
        result.push_back({5,  0, Gfx::ENG_OBJTYPE_DESCENDANT, "apollol3.mod"}); // ladder
        return result;
    }

    if ( type == OBJECT_APOLLO3 ) name ="apollof.mod"; // flag?
    if ( type == OBJECT_APOLLO4 ) name ="apollom.mod"; // module?
    if ( name.size() > 0 )
    {
        result.push_back({0, -1, Gfx::ENG_OBJTYPE_FIX, name});
        return result;
    }

    if ( type == OBJECT_APOLLO5 )  // antenna?
    {
        result.push_back({0, -1, Gfx::ENG_OBJTYPE_FIX,        "apolloa.mod"});
        result.push_back({1,  0, Gfx::ENG_OBJTYPE_DESCENDANT, "apolloj2.mod", Math::Vector(0.0f, 5.0f, 0.0f),  Math::Vector(0, -120.0f*Math::PI/180.0f, 45.0f*Math::PI/180.0f)});
        return result;
    }

    if ( type == OBJECT_CONTROLLER )
    {
        result.push_back({0, -1, Gfx::ENG_OBJTYPE_VEHICLE}); // No model!
        return result;
    }

    return result;
}

std::vector<CrashSphere> CHardcodeCollection::GetCreationCrashSpheres(ObjectType type)
{
    std::vector<CrashSphere> result;

    if ( type == OBJECT_EGG )
    {
        result.push_back(CrashSphere(Math::Vector(-1.0f, 2.8f, 0.0f), 3.0f, SOUND_BOUMm, 0.45f));
    }
    else if ( type == OBJECT_BOMB )
    {
        result.push_back(CrashSphere(Math::Vector(0.0f, 0.0f, 0.0f), 3.0f, SOUND_BOUMm, 0.45f));
    }
    else if ( type == OBJECT_BAG )
    {
        result.push_back(CrashSphere(Math::Vector(0.0f, 0.0f, 0.0f), 4.0f, SOUND_BOUMm, 0.45f));
    }
    else if ( type == OBJECT_STONE   ||
              type == OBJECT_URANIUM ||
              type == OBJECT_METAL   ||
              type == OBJECT_BULLET  ||
              type == OBJECT_BBOX    ||
              type == OBJECT_KEYa    ||
              type == OBJECT_KEYb    ||
              type == OBJECT_KEYc    ||
              type == OBJECT_KEYd    ||
              type == OBJECT_TNT     ||
              type == OBJECT_SHOW    ||
              type == OBJECT_WINFIRE )
    {
        result.push_back(CrashSphere(Math::Vector(0.0f, 1.0f, 0.0f), 1.0f, SOUND_BOUMm, 0.45f));
    }

    if ( type == OBJECT_BARRIER0 )
    {
        result.push_back(CrashSphere(Math::Vector( 3.5f, 3.0f, 0.0f), 0.7f, SOUND_BOUMm, 0.45f));
        result.push_back(CrashSphere(Math::Vector( 0.0f, 3.0f, 0.0f), 0.7f, SOUND_BOUMm, 0.45f));
        result.push_back(CrashSphere(Math::Vector(-3.5f, 3.0f, 0.0f), 0.7f, SOUND_BOUMm, 0.45f));
    }

    if ( type == OBJECT_BARRIER1 )
    {
        result.push_back(CrashSphere(Math::Vector( 8.5f, 3.0f, 0.0f), 0.7f, SOUND_BOUMm, 0.45f));
        result.push_back(CrashSphere(Math::Vector( 3.5f, 3.0f, 0.0f), 0.7f, SOUND_BOUMm, 0.45f));
        result.push_back(CrashSphere(Math::Vector( 0.0f, 3.0f, 0.0f), 0.7f, SOUND_BOUMm, 0.45f));
        result.push_back(CrashSphere(Math::Vector(-3.5f, 3.0f, 0.0f), 0.7f, SOUND_BOUMm, 0.45f));
        result.push_back(CrashSphere(Math::Vector(-8.5f, 3.0f, 0.0f), 0.7f, SOUND_BOUMm, 0.45f));
    }

    if ( type == OBJECT_BARRIER2 )  // cardboard?
    {
        result.push_back(CrashSphere(Math::Vector( 8.5f, 3.0f, 0.0f), 0.7f, SOUND_BOUMm, 0.45f));
        result.push_back(CrashSphere(Math::Vector( 3.5f, 3.0f, 0.0f), 0.7f, SOUND_BOUMm, 0.45f));
        result.push_back(CrashSphere(Math::Vector( 0.0f, 3.0f, 0.0f), 0.7f, SOUND_BOUMm, 0.45f));
        result.push_back(CrashSphere(Math::Vector(-3.5f, 3.0f, 0.0f), 0.7f, SOUND_BOUMm, 0.45f));
        result.push_back(CrashSphere(Math::Vector(-8.5f, 3.0f, 0.0f), 0.7f, SOUND_BOUMm, 0.45f));
    }

    if ( type == OBJECT_BARRIER3 )  // match + straw?
    {
        result.push_back(CrashSphere(Math::Vector( 8.5f, 3.0f, 0.0f), 0.7f, SOUND_BOUMm, 0.45f));
        result.push_back(CrashSphere(Math::Vector( 3.5f, 3.0f, 0.0f), 0.7f, SOUND_BOUMm, 0.45f));
        result.push_back(CrashSphere(Math::Vector( 0.0f, 3.0f, 0.0f), 0.7f, SOUND_BOUMm, 0.45f));
        result.push_back(CrashSphere(Math::Vector(-3.5f, 3.0f, 0.0f), 0.7f, SOUND_BOUMm, 0.45f));
        result.push_back(CrashSphere(Math::Vector(-8.5f, 3.0f, 0.0f), 0.7f, SOUND_BOUMm, 0.45f));
    }

    if ( type == OBJECT_BARRICADE0 )
    {
        result.push_back(CrashSphere(Math::Vector( 3.5f, 3.0f, 0.0f), 0.7f, SOUND_BOUMm, 0.45f));
        result.push_back(CrashSphere(Math::Vector( 0.0f, 3.0f, 0.0f), 0.7f, SOUND_BOUMm, 0.45f));
        result.push_back(CrashSphere(Math::Vector(-3.5f, 3.0f, 0.0f), 0.7f, SOUND_BOUMm, 0.45f));
        result.push_back(CrashSphere(Math::Vector( 3.5f, 6.0f, 0.0f), 0.7f, SOUND_BOUMm, 0.45f));
        result.push_back(CrashSphere(Math::Vector( 0.0f, 6.0f, 0.0f), 0.7f, SOUND_BOUMm, 0.45f));
        result.push_back(CrashSphere(Math::Vector(-3.5f, 6.0f, 0.0f), 0.7f, SOUND_BOUMm, 0.45f));
    }

    if ( type == OBJECT_BARRICADE1 )
    {
        result.push_back(CrashSphere(Math::Vector( 8.5f, 3.0f, 0.0f), 0.7f, SOUND_BOUMm, 0.45f));
        result.push_back(CrashSphere(Math::Vector( 3.5f, 3.0f, 0.0f), 0.7f, SOUND_BOUMm, 0.45f));
        result.push_back(CrashSphere(Math::Vector( 0.0f, 3.0f, 0.0f), 0.7f, SOUND_BOUMm, 0.45f));
        result.push_back(CrashSphere(Math::Vector(-3.5f, 3.0f, 0.0f), 0.7f, SOUND_BOUMm, 0.45f));
        result.push_back(CrashSphere(Math::Vector(-8.5f, 3.0f, 0.0f), 0.7f, SOUND_BOUMm, 0.45f));
        result.push_back(CrashSphere(Math::Vector( 8.5f, 6.0f, 0.0f), 0.7f, SOUND_BOUMm, 0.45f));
        result.push_back(CrashSphere(Math::Vector( 3.5f, 6.0f, 0.0f), 0.7f, SOUND_BOUMm, 0.45f));
        result.push_back(CrashSphere(Math::Vector( 0.0f, 6.0f, 0.0f), 0.7f, SOUND_BOUMm, 0.45f));
        result.push_back(CrashSphere(Math::Vector(-3.5f, 6.0f, 0.0f), 0.7f, SOUND_BOUMm, 0.45f));
        result.push_back(CrashSphere(Math::Vector(-8.5f, 6.0f, 0.0f), 0.7f, SOUND_BOUMm, 0.45f));
    }

    if ( type == OBJECT_PLANT0 ||
         type == OBJECT_PLANT1 ||
         type == OBJECT_PLANT2 ||
         type == OBJECT_PLANT3 ||
         type == OBJECT_PLANT4 )  // standard?
    {
        result.push_back(CrashSphere(Math::Vector(0.0f, 0.0f, 0.0f), 4.0f, SOUND_BOUM, 0.10f));
    }

    if ( type == OBJECT_PLANT5 ||
         type == OBJECT_PLANT6 ||
         type == OBJECT_PLANT7 )  // clover?
    {
//?     result.push_back(CrashSphere(Math::Vector(0.0f, 0.0f, 0.0f), 3.0f, SOUND_BOUM, 0.10f));
    }

    if ( type == OBJECT_PLANT8 ||
         type == OBJECT_PLANT9 )  // squash?
    {
        result.push_back(CrashSphere(Math::Vector(0.0f,  2.0f, 0.0f), 4.0f, SOUND_BOUM, 0.10f));
        result.push_back(CrashSphere(Math::Vector(0.0f, 10.0f, 0.0f), 4.0f, SOUND_BOUM, 0.10f));
    }

    if ( type == OBJECT_PLANT10 ||
         type == OBJECT_PLANT11 ||
         type == OBJECT_PLANT12 ||
         type == OBJECT_PLANT13 ||
         type == OBJECT_PLANT14 )  // succulent?
    {
        result.push_back(CrashSphere(Math::Vector(0.0f, 12.0f, 0.0f), 5.0f, SOUND_BOUM, 0.10f));
    }

    if ( type == OBJECT_PLANT15 ||
         type == OBJECT_PLANT16 ||
         type == OBJECT_PLANT17 ||
         type == OBJECT_PLANT18 )  // fern?
    {
        result.push_back(CrashSphere(Math::Vector(0.0f, 0.0f, 0.0f), 4.0f, SOUND_BOUM, 0.10f));
    }

    if ( type == OBJECT_PLANT19 )  // fern?
    {
    }

    if ( type == OBJECT_TREE0 )
    {
        result.push_back(CrashSphere(Math::Vector( 0.0f,  3.0f, 2.0f), 3.0f, SOUND_BOUMs, 0.20f));
        result.push_back(CrashSphere(Math::Vector(-1.0f, 10.0f, 1.0f), 2.0f, SOUND_BOUMs, 0.20f));
        result.push_back(CrashSphere(Math::Vector( 0.0f, 17.0f, 0.0f), 2.0f, SOUND_BOUMs, 0.20f));
        result.push_back(CrashSphere(Math::Vector( 1.0f, 27.0f, 0.0f), 2.0f, SOUND_BOUMs, 0.20f));
    }

    if ( type == OBJECT_TREE1 )
    {
        result.push_back(CrashSphere(Math::Vector( 0.0f,  3.0f, 2.0f), 3.0f, SOUND_BOUMs, 0.20f));
        result.push_back(CrashSphere(Math::Vector(-2.0f, 11.0f, 1.0f), 2.0f, SOUND_BOUMs, 0.20f));
        result.push_back(CrashSphere(Math::Vector(-2.0f, 19.0f, 2.0f), 2.0f, SOUND_BOUMs, 0.20f));
        result.push_back(CrashSphere(Math::Vector( 2.0f, 26.0f, 0.0f), 2.0f, SOUND_BOUMs, 0.20f));
        result.push_back(CrashSphere(Math::Vector( 2.0f, 34.0f,-2.0f), 2.0f, SOUND_BOUMs, 0.20f));
    }

    if ( type == OBJECT_TREE2 )
    {
        result.push_back(CrashSphere(Math::Vector( 0.0f,  3.0f, 1.0f), 3.0f, SOUND_BOUMs, 0.20f));
        result.push_back(CrashSphere(Math::Vector(-2.0f, 10.0f, 1.0f), 2.0f, SOUND_BOUMs, 0.20f));
        result.push_back(CrashSphere(Math::Vector(-2.0f, 19.0f, 2.0f), 2.0f, SOUND_BOUMs, 0.20f));
        result.push_back(CrashSphere(Math::Vector( 2.0f, 25.0f, 0.0f), 2.0f, SOUND_BOUMs, 0.20f));
        result.push_back(CrashSphere(Math::Vector( 3.0f, 32.0f,-2.0f), 2.0f, SOUND_BOUMs, 0.20f));
    }

    if ( type == OBJECT_TREE3 )
    {
        result.push_back(CrashSphere(Math::Vector(-2.0f,  3.0f, 2.0f), 3.0f, SOUND_BOUMs, 0.20f));
        result.push_back(CrashSphere(Math::Vector(-3.0f,  9.0f, 1.0f), 2.0f, SOUND_BOUMs, 0.20f));
        result.push_back(CrashSphere(Math::Vector( 0.0f, 18.0f, 0.0f), 2.0f, SOUND_BOUMs, 0.20f));
        result.push_back(CrashSphere(Math::Vector( 0.0f, 27.0f, 7.0f), 2.0f, SOUND_BOUMs, 0.20f));
    }

    if ( type == OBJECT_TREE4 )
    {
        result.push_back(CrashSphere(Math::Vector(0.0f, 10.0f, 0.0f), 10.0f, SOUND_BOUMs, 0.20f));
        result.push_back(CrashSphere(Math::Vector(0.0f, 21.0f, 0.0f),  8.0f, SOUND_BOUMs, 0.20f));
        result.push_back(CrashSphere(Math::Vector(0.0f, 32.0f, 0.0f),  7.0f, SOUND_BOUMs, 0.20f));
    }

    if ( type == OBJECT_TREE5 )  // giant tree (for the world "teen")
    {
        result.push_back(CrashSphere(Math::Vector(  0.0f, 5.0f,-10.0f), 25.0f, SOUND_BOUMs, 0.20f));
        result.push_back(CrashSphere(Math::Vector(-65.0f, 5.0f, 65.0f), 20.0f, SOUND_BOUMs, 0.20f));
        result.push_back(CrashSphere(Math::Vector( 38.0f, 5.0f, 21.0f), 18.0f, SOUND_BOUMs, 0.20f));
    }

    if ( type == OBJECT_MUSHROOM1 )
    {
        result.push_back(CrashSphere(Math::Vector(0.0f, 4.0f, 0.0f), 3.0f, SOUND_BOUM, 0.10f));
    }

    if ( type == OBJECT_MUSHROOM2 )
    {
        result.push_back(CrashSphere(Math::Vector(0.0f, 5.0f, 0.0f), 3.0f, SOUND_BOUM, 0.10f));
    }

    if ( type == OBJECT_TEEN0 )  // orange pencil lg=10
    {
        result.push_back(CrashSphere(Math::Vector( 5.0f, 1.0f, 0.0f), 1.0f, SOUND_BOUMm, 0.45f));
        result.push_back(CrashSphere(Math::Vector( 2.5f, 1.0f, 0.0f), 1.0f, SOUND_BOUMm, 0.45f));
        result.push_back(CrashSphere(Math::Vector( 0.0f, 1.0f, 0.0f), 1.0f, SOUND_BOUMm, 0.45f));
        result.push_back(CrashSphere(Math::Vector(-2.5f, 1.0f, 0.0f), 1.0f, SOUND_BOUMm, 0.45f));
        result.push_back(CrashSphere(Math::Vector(-5.0f, 1.0f, 0.0f), 1.0f, SOUND_BOUMm, 0.45f));
    }

    if ( type == OBJECT_TEEN1 )  // blue pencil lg=14
    {
        result.push_back(CrashSphere(Math::Vector( 6.0f, 1.0f, 0.0f), 1.0f, SOUND_BOUMm, 0.45f));
        result.push_back(CrashSphere(Math::Vector( 4.0f, 1.0f, 0.0f), 1.0f, SOUND_BOUMm, 0.45f));
        result.push_back(CrashSphere(Math::Vector( 2.0f, 1.0f, 0.0f), 1.0f, SOUND_BOUMm, 0.45f));
        result.push_back(CrashSphere(Math::Vector( 0.0f, 1.0f, 0.0f), 1.0f, SOUND_BOUMm, 0.45f));
        result.push_back(CrashSphere(Math::Vector(-2.0f, 1.0f, 0.0f), 1.0f, SOUND_BOUMm, 0.45f));
        result.push_back(CrashSphere(Math::Vector(-4.0f, 1.0f, 0.0f), 1.0f, SOUND_BOUMm, 0.45f));
        result.push_back(CrashSphere(Math::Vector(-6.0f, 1.0f, 0.0f), 1.0f, SOUND_BOUMm, 0.45f));
    }

    if ( type == OBJECT_TEEN2 )  // red pencil lg=16
    {
        result.push_back(CrashSphere(Math::Vector( 7.0f, 1.0f, 0.0f), 1.0f, SOUND_BOUMm, 0.45f));
        result.push_back(CrashSphere(Math::Vector( 4.7f, 1.0f, 0.0f), 1.0f, SOUND_BOUMm, 0.45f));
        result.push_back(CrashSphere(Math::Vector( 2.3f, 1.0f, 0.0f), 1.0f, SOUND_BOUMm, 0.45f));
        result.push_back(CrashSphere(Math::Vector( 0.0f, 1.0f, 0.0f), 1.0f, SOUND_BOUMm, 0.45f));
        result.push_back(CrashSphere(Math::Vector(-2.3f, 1.0f, 0.0f), 1.0f, SOUND_BOUMm, 0.45f));
        result.push_back(CrashSphere(Math::Vector(-4.7f, 1.0f, 0.0f), 1.0f, SOUND_BOUMm, 0.45f));
        result.push_back(CrashSphere(Math::Vector(-7.0f, 1.0f, 0.0f), 1.0f, SOUND_BOUMm, 0.45f));
    }

    if ( type == OBJECT_TEEN3 )  // jar with pencils
    {
        result.push_back(CrashSphere(Math::Vector( 0.0f, 4.0f, 0.0f), 4.0f, SOUND_BOUMm, 0.45f));
    }

    if ( type == OBJECT_TEEN4 )  // scissors
    {
        result.push_back(CrashSphere(Math::Vector(-9.0f, 1.0f, 0.0f), 1.0f, SOUND_BOUMm, 0.45f));
        result.push_back(CrashSphere(Math::Vector(-6.0f, 1.0f, 0.0f), 1.1f, SOUND_BOUMm, 0.45f));
        result.push_back(CrashSphere(Math::Vector(-3.0f, 1.0f, 0.0f), 1.2f, SOUND_BOUMm, 0.45f));
        result.push_back(CrashSphere(Math::Vector( 0.0f, 1.0f, 0.0f), 1.3f, SOUND_BOUMm, 0.45f));
        result.push_back(CrashSphere(Math::Vector( 5.1f, 1.0f,-1.3f), 2.6f, SOUND_BOUMm, 0.45f));
        result.push_back(CrashSphere(Math::Vector( 8.0f, 1.0f, 2.2f), 2.3f, SOUND_BOUMm, 0.45f));
        result.push_back(CrashSphere(Math::Vector( 9.4f, 1.0f,-2.0f), 2.0f, SOUND_BOUMm, 0.45f));
    }

    if ( type == OBJECT_TEEN6 )  // book 1
    {
        result.push_back(CrashSphere(Math::Vector(-5.0f, 3.0f, 7.5f), 5.0f, SOUND_BOUMm, 0.45f));
        result.push_back(CrashSphere(Math::Vector( 4.5f, 3.0f, 7.5f), 5.0f, SOUND_BOUMm, 0.45f));
        result.push_back(CrashSphere(Math::Vector(-5.0f, 3.0f, 0.0f), 5.0f, SOUND_BOUMm, 0.45f));
        result.push_back(CrashSphere(Math::Vector( 4.5f, 3.0f, 0.0f), 5.0f, SOUND_BOUMm, 0.45f));
        result.push_back(CrashSphere(Math::Vector(-5.0f, 3.0f,-7.5f), 5.0f, SOUND_BOUMm, 0.45f));
        result.push_back(CrashSphere(Math::Vector( 4.5f, 3.0f,-7.5f), 5.0f, SOUND_BOUMm, 0.45f));
    }

    if ( type == OBJECT_TEEN7 )  // book 2
    {
        result.push_back(CrashSphere(Math::Vector(-5.0f, 3.0f, 7.5f), 5.0f, SOUND_BOUMm, 0.45f));
        result.push_back(CrashSphere(Math::Vector( 4.5f, 3.0f, 7.5f), 5.0f, SOUND_BOUMm, 0.45f));
        result.push_back(CrashSphere(Math::Vector(-5.0f, 3.0f, 0.0f), 5.0f, SOUND_BOUMm, 0.45f));
        result.push_back(CrashSphere(Math::Vector( 4.5f, 3.0f, 0.0f), 5.0f, SOUND_BOUMm, 0.45f));
        result.push_back(CrashSphere(Math::Vector(-5.0f, 3.0f,-7.5f), 5.0f, SOUND_BOUMm, 0.45f));
        result.push_back(CrashSphere(Math::Vector( 4.5f, 3.0f,-7.5f), 5.0f, SOUND_BOUMm, 0.45f));
    }

    if ( type == OBJECT_TEEN8 )  // a stack of books 1
    {
        result.push_back(CrashSphere(Math::Vector(-5.0f, 3.0f, 7.5f), 5.0f, SOUND_BOUMm, 0.45f));
        result.push_back(CrashSphere(Math::Vector( 4.5f, 3.0f, 7.5f), 5.0f, SOUND_BOUMm, 0.45f));
        result.push_back(CrashSphere(Math::Vector(-5.0f, 3.0f, 0.0f), 5.0f, SOUND_BOUMm, 0.45f));
        result.push_back(CrashSphere(Math::Vector( 4.5f, 3.0f, 0.0f), 5.0f, SOUND_BOUMm, 0.45f));
        result.push_back(CrashSphere(Math::Vector(-5.0f, 3.0f,-7.5f), 5.0f, SOUND_BOUMm, 0.45f));
        result.push_back(CrashSphere(Math::Vector( 4.5f, 3.0f,-7.5f), 5.0f, SOUND_BOUMm, 0.45f));
    }

    if ( type == OBJECT_TEEN9 )  // a stack of books 2
    {
        result.push_back(CrashSphere(Math::Vector(-5.0f, 3.0f, 7.5f), 5.0f, SOUND_BOUMm, 0.45f));
        result.push_back(CrashSphere(Math::Vector( 4.5f, 3.0f, 7.5f), 5.0f, SOUND_BOUMm, 0.45f));
        result.push_back(CrashSphere(Math::Vector(-5.0f, 3.0f, 0.0f), 5.0f, SOUND_BOUMm, 0.45f));
        result.push_back(CrashSphere(Math::Vector( 4.5f, 3.0f, 0.0f), 5.0f, SOUND_BOUMm, 0.45f));
        result.push_back(CrashSphere(Math::Vector(-5.0f, 3.0f,-7.5f), 5.0f, SOUND_BOUMm, 0.45f));
        result.push_back(CrashSphere(Math::Vector( 4.5f, 3.0f,-7.5f), 5.0f, SOUND_BOUMm, 0.45f));
    }

    if ( type == OBJECT_TEEN10 )  // bookcase
    {
        result.push_back(CrashSphere(Math::Vector(-26.0f, 3.0f, 0.0f), 6.0f, SOUND_BOUMm, 0.45f));
        result.push_back(CrashSphere(Math::Vector(-15.0f, 3.0f,-4.0f), 6.0f, SOUND_BOUMm, 0.45f));
        result.push_back(CrashSphere(Math::Vector(-15.0f, 3.0f, 5.0f), 6.0f, SOUND_BOUMm, 0.45f));
        result.push_back(CrashSphere(Math::Vector( -4.0f, 3.0f,-4.0f), 6.0f, SOUND_BOUMm, 0.45f));
        result.push_back(CrashSphere(Math::Vector( -4.0f, 3.0f, 5.0f), 6.0f, SOUND_BOUMm, 0.45f));
        result.push_back(CrashSphere(Math::Vector(  6.0f, 3.0f,-4.0f), 6.0f, SOUND_BOUMm, 0.45f));
        result.push_back(CrashSphere(Math::Vector(  6.0f, 3.0f, 4.0f), 6.0f, SOUND_BOUMm, 0.45f));
        result.push_back(CrashSphere(Math::Vector( 14.0f, 3.0f,-3.0f), 6.0f, SOUND_BOUMm, 0.45f));
        result.push_back(CrashSphere(Math::Vector( 14.0f, 3.0f, 2.0f), 6.0f, SOUND_BOUMm, 0.45f));
        result.push_back(CrashSphere(Math::Vector( 24.0f, 3.0f, 5.0f), 6.0f, SOUND_BOUMm, 0.45f));
    }

    if ( type == OBJECT_TEEN12 )  // coke
    {
        result.push_back(CrashSphere(Math::Vector( 0.0f, 4.0f, 0.0f), 4.0f, SOUND_BOUMm, 0.45f));
    }

    if ( type == OBJECT_TEEN13 )  // cardboard farm
    {
        result.push_back(CrashSphere(Math::Vector(-10.0f, 4.0f,-7.0f), 5.0f, SOUND_BOUMm, 0.45f));
        result.push_back(CrashSphere(Math::Vector(  0.0f, 4.0f,-7.0f), 5.0f, SOUND_BOUMm, 0.45f));
        result.push_back(CrashSphere(Math::Vector( 10.0f, 4.0f,-7.0f), 5.0f, SOUND_BOUMm, 0.45f));
        result.push_back(CrashSphere(Math::Vector(-10.0f, 4.0f, 0.0f), 5.0f, SOUND_BOUMm, 0.45f));
        result.push_back(CrashSphere(Math::Vector(  0.0f, 4.0f, 0.0f), 5.0f, SOUND_BOUMm, 0.45f));
        result.push_back(CrashSphere(Math::Vector( 10.0f, 4.0f, 0.0f), 5.0f, SOUND_BOUMm, 0.45f));
        result.push_back(CrashSphere(Math::Vector(-10.0f, 4.0f, 7.0f), 5.0f, SOUND_BOUMm, 0.45f));
        result.push_back(CrashSphere(Math::Vector(  0.0f, 4.0f, 7.0f), 5.0f, SOUND_BOUMm, 0.45f));
        result.push_back(CrashSphere(Math::Vector( 10.0f, 4.0f, 7.0f), 5.0f, SOUND_BOUMm, 0.45f));
    }

    if ( type == OBJECT_TEEN14 )  // open box
    {
        result.push_back(CrashSphere(Math::Vector(-10.0f, 4.0f,-7.0f), 5.0f, SOUND_BOUMm, 0.45f));
        result.push_back(CrashSphere(Math::Vector(  0.0f, 4.0f,-7.0f), 5.0f, SOUND_BOUMm, 0.45f));
        result.push_back(CrashSphere(Math::Vector( 10.0f, 4.0f,-7.0f), 5.0f, SOUND_BOUMm, 0.45f));
        result.push_back(CrashSphere(Math::Vector(-10.0f, 4.0f, 0.0f), 5.0f, SOUND_BOUMm, 0.45f));
        result.push_back(CrashSphere(Math::Vector(  0.0f, 4.0f, 0.0f), 5.0f, SOUND_BOUMm, 0.45f));
        result.push_back(CrashSphere(Math::Vector( 10.0f, 4.0f, 0.0f), 5.0f, SOUND_BOUMm, 0.45f));
        result.push_back(CrashSphere(Math::Vector(-10.0f, 4.0f, 7.0f), 5.0f, SOUND_BOUMm, 0.45f));
        result.push_back(CrashSphere(Math::Vector(  0.0f, 4.0f, 7.0f), 5.0f, SOUND_BOUMm, 0.45f));
        result.push_back(CrashSphere(Math::Vector( 10.0f, 4.0f, 7.0f), 5.0f, SOUND_BOUMm, 0.45f));
    }

    if ( type == OBJECT_TEEN15 )  // stack of cartons
    {
        result.push_back(CrashSphere(Math::Vector(-10.0f, 4.0f,-7.0f), 5.0f, SOUND_BOUMm, 0.45f));
        result.push_back(CrashSphere(Math::Vector(  0.0f, 4.0f,-7.0f), 5.0f, SOUND_BOUMm, 0.45f));
        result.push_back(CrashSphere(Math::Vector( 10.0f, 4.0f,-7.0f), 5.0f, SOUND_BOUMm, 0.45f));
        result.push_back(CrashSphere(Math::Vector(-10.0f, 4.0f, 0.0f), 5.0f, SOUND_BOUMm, 0.45f));
        result.push_back(CrashSphere(Math::Vector(  0.0f, 4.0f, 0.0f), 5.0f, SOUND_BOUMm, 0.45f));
        result.push_back(CrashSphere(Math::Vector( 10.0f, 4.0f, 0.0f), 5.0f, SOUND_BOUMm, 0.45f));
        result.push_back(CrashSphere(Math::Vector(-10.0f, 4.0f, 7.0f), 5.0f, SOUND_BOUMm, 0.45f));
        result.push_back(CrashSphere(Math::Vector(  0.0f, 4.0f, 7.0f), 5.0f, SOUND_BOUMm, 0.45f));
        result.push_back(CrashSphere(Math::Vector( 10.0f, 4.0f, 7.0f), 5.0f, SOUND_BOUMm, 0.45f));
    }

    if ( type == OBJECT_TEEN16 )  // watering can
    {
        result.push_back(CrashSphere(Math::Vector(-8.0f, 4.0f, 0.0f), 12.0f, SOUND_BOUMm, 0.45f));
        result.push_back(CrashSphere(Math::Vector( 8.0f, 4.0f, 0.0f), 12.0f, SOUND_BOUMm, 0.45f));
    }

    if ( type == OBJECT_TEEN17 )  // wheel |
    {
        result.push_back(CrashSphere(Math::Vector( 0.0f, 31.0f, 0.0f), 31.0f, SOUND_BOUMm, 0.45f));
    }

    if ( type == OBJECT_TEEN18 )  // wheel /
    {
        result.push_back(CrashSphere(Math::Vector( 0.0f, 31.0f, 0.0f), 31.0f, SOUND_BOUMm, 0.45f));
    }

    if ( type == OBJECT_TEEN19 )  // wheel =
    {
        result.push_back(CrashSphere(Math::Vector( 0.0f, 10.0f, 0.0f), 32.0f, SOUND_BOUMm, 0.45f));
    }

    if ( type == OBJECT_TEEN20 )  // wall with shelf
    {
        result.push_back(CrashSphere(Math::Vector(-175.0f, 0.0f,  -5.0f), 4.0f, SOUND_BOUMm, 0.45f));
        result.push_back(CrashSphere(Math::Vector(-175.0f, 0.0f, -35.0f), 4.0f, SOUND_BOUMm, 0.45f));
        result.push_back(CrashSphere(Math::Vector( -55.0f, 0.0f,  -5.0f), 4.0f, SOUND_BOUMm, 0.45f));
        result.push_back(CrashSphere(Math::Vector( -55.0f, 0.0f, -35.0f), 4.0f, SOUND_BOUMm, 0.45f));
        result.push_back(CrashSphere(Math::Vector( -37.0f, 0.0f,  -5.0f), 4.0f, SOUND_BOUMm, 0.45f));
        result.push_back(CrashSphere(Math::Vector( -37.0f, 0.0f, -35.0f), 4.0f, SOUND_BOUMm, 0.45f));
        result.push_back(CrashSphere(Math::Vector(  83.0f, 0.0f,  -5.0f), 4.0f, SOUND_BOUMm, 0.45f));
        result.push_back(CrashSphere(Math::Vector(  83.0f, 0.0f, -35.0f), 4.0f, SOUND_BOUMm, 0.45f));
    }

    if ( type == OBJECT_TEEN22 )  // wall with door and shelf
    {
        result.push_back(CrashSphere(Math::Vector(-135.0f, 0.0f,  -5.0f), 4.0f, SOUND_BOUMm, 0.45f));
        result.push_back(CrashSphere(Math::Vector(-135.0f, 0.0f, -35.0f), 4.0f, SOUND_BOUMm, 0.45f));
        result.push_back(CrashSphere(Math::Vector( -15.0f, 0.0f,  -5.0f), 4.0f, SOUND_BOUMm, 0.45f));
        result.push_back(CrashSphere(Math::Vector( -15.0f, 0.0f, -35.0f), 4.0f, SOUND_BOUMm, 0.45f));
    }

    if ( type == OBJECT_TEEN23 )  // skateboard on wheels
    {
        result.push_back(CrashSphere(Math::Vector(-23.0f, 2.0f, 7.0f), 3.0f, SOUND_BOUMm, 0.45f));
        result.push_back(CrashSphere(Math::Vector(-23.0f, 2.0f, 0.0f), 3.0f, SOUND_BOUMm, 0.45f));
        result.push_back(CrashSphere(Math::Vector(-23.0f, 2.0f,-7.0f), 3.0f, SOUND_BOUMm, 0.45f));
        result.push_back(CrashSphere(Math::Vector( 23.0f, 2.0f, 7.0f), 3.0f, SOUND_BOUMm, 0.45f));
        result.push_back(CrashSphere(Math::Vector( 23.0f, 2.0f, 0.0f), 3.0f, SOUND_BOUMm, 0.45f));
        result.push_back(CrashSphere(Math::Vector( 23.0f, 2.0f,-7.0f), 3.0f, SOUND_BOUMm, 0.45f));
    }

    if ( type == OBJECT_TEEN24 )  // skate /
    {
        result.push_back(CrashSphere(Math::Vector(-12.0f, 0.0f, -3.0f), 3.0f, SOUND_BOUMm, 0.45f));
        result.push_back(CrashSphere(Math::Vector(-12.0f, 0.0f,  3.0f), 3.0f, SOUND_BOUMm, 0.45f));
    }

    if ( type == OBJECT_TEEN25 )  // skate /
    {
        result.push_back(CrashSphere(Math::Vector(-12.0f, 0.0f, -3.0f), 3.0f, SOUND_BOUMm, 0.45f));
        result.push_back(CrashSphere(Math::Vector(-12.0f, 0.0f,  3.0f), 3.0f, SOUND_BOUMm, 0.45f));
    }

    if ( type == OBJECT_TEEN27 )  // large plant?
    {
        result.push_back(CrashSphere(Math::Vector(0.0f, 0.0f, 0.0f), 4.0f, SOUND_BOUM, 0.10f));
    }

    if ( type == OBJECT_TEEN28 )  // bottle?
    {
        result.push_back(CrashSphere(Math::Vector(0.0f, 2.0f, 0.0f), 5.0f, SOUND_BOUM, 0.10f));
    }

    if ( type == OBJECT_TEEN30 )  // jump?
    {
        result.push_back(CrashSphere(Math::Vector(0.0f, 4.0f, 0.0f), 15.0f, SOUND_BOUM, 0.10f));
    }

    if ( type == OBJECT_TEEN31 )  // basket?
    {
        result.push_back(CrashSphere(Math::Vector(-10.0f, 2.0f, 0.0f), 5.0f, SOUND_BOUM, 0.10f));
        result.push_back(CrashSphere(Math::Vector(  0.0f, 2.0f, 0.0f), 6.0f, SOUND_BOUM, 0.10f));
        result.push_back(CrashSphere(Math::Vector(  9.0f, 4.0f, 1.0f), 6.0f, SOUND_BOUM, 0.10f));
    }

    if ( type == OBJECT_TEEN32 )  // chair?
    {
        result.push_back(CrashSphere(Math::Vector( 17.5f, 1.0f,  17.5f), 3.5f, SOUND_BOUM, 0.10f));
        result.push_back(CrashSphere(Math::Vector( 17.5f, 1.0f, -17.5f), 3.5f, SOUND_BOUM, 0.10f));
        result.push_back(CrashSphere(Math::Vector(-17.5f, 1.0f,  17.5f), 3.5f, SOUND_BOUM, 0.10f));
        result.push_back(CrashSphere(Math::Vector(-17.5f, 1.0f, -17.5f), 3.5f, SOUND_BOUM, 0.10f));
    }

    if ( type == OBJECT_TEEN33 )  // panel?
    {
        result.push_back(CrashSphere(Math::Vector(0.0f, 2.0f, 0.0f), 4.0f, SOUND_BOUM, 0.10f));
    }

    if ( type == OBJECT_TEEN34 )  // stone?
    {
        result.push_back(CrashSphere(Math::Vector(0.0f, 2.0f, 0.0f), 4.0f, SOUND_BOUM, 0.10f));
    }

    if ( type == OBJECT_TEEN35 )  // pipe?
    {
        result.push_back(CrashSphere(Math::Vector(-40.0f, 5.0f, 0.0f), 10.0f, SOUND_BOUM, 0.10f));
        result.push_back(CrashSphere(Math::Vector(-20.0f, 5.0f, 0.0f), 10.0f, SOUND_BOUM, 0.10f));
        result.push_back(CrashSphere(Math::Vector(  0.0f, 5.0f, 0.0f), 10.0f, SOUND_BOUM, 0.10f));
        result.push_back(CrashSphere(Math::Vector( 20.0f, 5.0f, 0.0f), 10.0f, SOUND_BOUM, 0.10f));
        result.push_back(CrashSphere(Math::Vector( 40.0f, 5.0f, 0.0f), 10.0f, SOUND_BOUM, 0.10f));
    }

    if ( type == OBJECT_TEEN38 )  // fan?
    {
        result.push_back(CrashSphere(Math::Vector(0.0f, 2.0f, 0.0f), 10.0f, SOUND_BOUM, 0.10f));
    }

    if ( type == OBJECT_TEEN39 )  // potted plant?
    {
        result.push_back(CrashSphere(Math::Vector(0.0f, 2.0f, 0.0f), 8.5f, SOUND_BOUM, 0.10f));
    }

    if ( type == OBJECT_TEEN40 )  // balloon?
    {
        result.push_back(CrashSphere(Math::Vector(0.0f, 5.0f, 0.0f), 11.0f, SOUND_BOUM, 0.10f));
    }

    if ( type == OBJECT_TEEN42 )  // clover?
    {
        result.push_back(CrashSphere(Math::Vector(0.0f, 2.0f, 0.0f), 2.0f, SOUND_BOUM, 0.10f));
    }

    if ( type == OBJECT_TEEN43 )  // clover?
    {
        result.push_back(CrashSphere(Math::Vector(0.0f, 2.0f, 0.0f), 2.0f, SOUND_BOUM, 0.10f));
    }

    if ( type == OBJECT_TEEN44 )  // car?
    {
        result.push_back(CrashSphere(Math::Vector(0.0f, 10.0f, 0.0f), 55.0f, SOUND_BOUM, 0.10f));
    }

    if ( type == OBJECT_HOME1 )
    {
        result.push_back(CrashSphere(Math::Vector(0.0f, 5.0f, 0.0f), 10.0f, SOUND_BOUMs, 0.25f));
    }

    if ( type == OBJECT_QUARTZ0 )
    {
        result.push_back(CrashSphere(Math::Vector(0.0f, 2.0f, 0.0f), 3.5f, SOUND_BOUMm, 0.45f));
    }
    if ( type == OBJECT_QUARTZ1 )
    {
        result.push_back(CrashSphere(Math::Vector(0.0f, 4.0f, 0.0f), 5.0f, SOUND_BOUMm, 0.45f));
    }
    if ( type == OBJECT_QUARTZ2 )
    {
        result.push_back(CrashSphere(Math::Vector(0.0f, 6.0f, 0.0f), 6.0f, SOUND_BOUMm, 0.45f));
    }
    if ( type == OBJECT_QUARTZ3 )
    {
        result.push_back(CrashSphere(Math::Vector(0.0f, 10.0f, 0.0f), 10.0f, SOUND_BOUMm, 0.45f));
    }

    if ( type == OBJECT_ROOT0 )
    {
        result.push_back(CrashSphere(Math::Vector(-5.0f,  1.0f,  0.0f), 2.0f, SOUND_BOUMv, 0.15f));
        result.push_back(CrashSphere(Math::Vector( 4.0f,  1.0f,  2.0f), 2.0f, SOUND_BOUMv, 0.15f));
        result.push_back(CrashSphere(Math::Vector( 4.0f,  1.0f, -3.0f), 2.0f, SOUND_BOUMv, 0.15f));
        result.push_back(CrashSphere(Math::Vector( 2.0f,  5.0f, -1.0f), 1.5f, SOUND_BOUMv, 0.15f));
        result.push_back(CrashSphere(Math::Vector(-4.0f,  5.0f, -1.0f), 1.0f, SOUND_BOUMv, 0.15f));
        result.push_back(CrashSphere(Math::Vector(-2.0f,  8.0f, -0.5f), 1.0f, SOUND_BOUMv, 0.15f));
        result.push_back(CrashSphere(Math::Vector( 0.0f, 10.0f, -0.5f), 1.0f, SOUND_BOUMv, 0.15f));
    }
    if ( type == OBJECT_ROOT1 )
    {
        result.push_back(CrashSphere(Math::Vector(-4.0f,  1.0f,  1.0f), 2.0f, SOUND_BOUMv, 0.15f));
        result.push_back(CrashSphere(Math::Vector( 0.0f,  1.0f,  2.0f), 1.5f, SOUND_BOUMv, 0.15f));
        result.push_back(CrashSphere(Math::Vector( 3.0f,  1.0f, -2.0f), 2.0f, SOUND_BOUMv, 0.15f));
        result.push_back(CrashSphere(Math::Vector(-2.0f,  5.0f,  1.0f), 1.0f, SOUND_BOUMv, 0.15f));
        result.push_back(CrashSphere(Math::Vector( 2.0f,  5.0f,  0.0f), 1.0f, SOUND_BOUMv, 0.15f));
        result.push_back(CrashSphere(Math::Vector( 0.0f,  8.0f,  1.0f), 1.0f, SOUND_BOUMv, 0.15f));
        result.push_back(CrashSphere(Math::Vector( 0.0f, 12.0f,  1.0f), 1.0f, SOUND_BOUMv, 0.15f));
    }
    if ( type == OBJECT_ROOT2 )
    {
        result.push_back(CrashSphere(Math::Vector(-3.0f,  1.0f,  0.5f), 2.0f, SOUND_BOUMv, 0.15f));
        result.push_back(CrashSphere(Math::Vector( 3.0f,  1.0f, -1.0f), 2.0f, SOUND_BOUMv, 0.15f));
        result.push_back(CrashSphere(Math::Vector(-1.0f,  4.5f,  0.0f), 1.0f, SOUND_BOUMv, 0.15f));
        result.push_back(CrashSphere(Math::Vector( 3.0f,  7.0f,  1.0f), 1.0f, SOUND_BOUMv, 0.15f));
        result.push_back(CrashSphere(Math::Vector( 0.0f,  7.0f, -1.0f), 1.0f, SOUND_BOUMv, 0.15f));
        result.push_back(CrashSphere(Math::Vector( 4.0f, 11.0f,  1.0f), 1.0f, SOUND_BOUMv, 0.15f));
    }
    if ( type == OBJECT_ROOT3 )
    {
        result.push_back(CrashSphere(Math::Vector(-4.0f,  1.0f,  1.0f), 3.0f, SOUND_BOUMv, 0.15f));
        result.push_back(CrashSphere(Math::Vector( 4.0f,  1.0f, -3.0f), 3.0f, SOUND_BOUMv, 0.15f));
        result.push_back(CrashSphere(Math::Vector( 6.0f,  1.0f,  4.0f), 3.0f, SOUND_BOUMv, 0.15f));
        result.push_back(CrashSphere(Math::Vector(-2.5f,  7.0f,  2.0f), 2.0f, SOUND_BOUMv, 0.15f));
        result.push_back(CrashSphere(Math::Vector( 4.0f,  7.0f,  2.0f), 2.0f, SOUND_BOUMv, 0.15f));
        result.push_back(CrashSphere(Math::Vector( 3.0f,  6.0f, -1.0f), 1.0f, SOUND_BOUMv, 0.15f));
        result.push_back(CrashSphere(Math::Vector( 0.0f, 12.0f,  0.0f), 2.0f, SOUND_BOUMv, 0.15f));
        result.push_back(CrashSphere(Math::Vector( 1.0f, 16.0f,  0.0f), 1.0f, SOUND_BOUMv, 0.15f));
    }
    if ( type == OBJECT_ROOT4 )
    {
        result.push_back(CrashSphere(Math::Vector( -7.0f,  2.0f,  3.0f), 4.0f, SOUND_BOUMv, 0.15f));
        result.push_back(CrashSphere(Math::Vector(  5.0f,  2.0f, -6.0f), 4.0f, SOUND_BOUMv, 0.15f));
        result.push_back(CrashSphere(Math::Vector(  6.0f,  2.0f,  6.0f), 3.0f, SOUND_BOUMv, 0.15f));
        result.push_back(CrashSphere(Math::Vector(-11.0f,  1.0f, -2.0f), 2.0f, SOUND_BOUMv, 0.15f));
        result.push_back(CrashSphere(Math::Vector(  1.0f,  1.0f, -7.0f), 2.0f, SOUND_BOUMv, 0.15f));
        result.push_back(CrashSphere(Math::Vector( -4.0f, 10.0f,  3.0f), 2.0f, SOUND_BOUMv, 0.15f));
        result.push_back(CrashSphere(Math::Vector(  1.0f, 11.0f,  7.0f), 2.0f, SOUND_BOUMv, 0.15f));
        result.push_back(CrashSphere(Math::Vector(  3.0f, 11.0f, -3.0f), 2.0f, SOUND_BOUMv, 0.15f));
        result.push_back(CrashSphere(Math::Vector( -3.0f, 17.0f,  1.0f), 2.0f, SOUND_BOUMv, 0.15f));
        result.push_back(CrashSphere(Math::Vector( -3.0f, 23.0f, -1.0f), 2.0f, SOUND_BOUMv, 0.15f));
    }
    if ( type == OBJECT_ROOT5 )  // gravity root ?
    {
        result.push_back(CrashSphere(Math::Vector( -7.0f,  2.0f,  3.0f), 4.0f, SOUND_BOUMv, 0.15f));
        result.push_back(CrashSphere(Math::Vector(  5.0f,  2.0f, -6.0f), 4.0f, SOUND_BOUMv, 0.15f));
        result.push_back(CrashSphere(Math::Vector(  6.0f,  2.0f,  6.0f), 3.0f, SOUND_BOUMv, 0.15f));
        result.push_back(CrashSphere(Math::Vector(-11.0f,  1.0f, -2.0f), 2.0f, SOUND_BOUMv, 0.15f));
        result.push_back(CrashSphere(Math::Vector(  1.0f,  1.0f, -7.0f), 2.0f, SOUND_BOUMv, 0.15f));
        result.push_back(CrashSphere(Math::Vector( -4.0f, 10.0f,  3.0f), 2.0f, SOUND_BOUMv, 0.15f));
        result.push_back(CrashSphere(Math::Vector(  1.0f, 11.0f,  7.0f), 2.0f, SOUND_BOUMv, 0.15f));
        result.push_back(CrashSphere(Math::Vector(  3.0f, 11.0f, -3.0f), 2.0f, SOUND_BOUMv, 0.15f));
        result.push_back(CrashSphere(Math::Vector( -3.0f, 17.0f,  1.0f), 2.0f, SOUND_BOUMv, 0.15f));
        result.push_back(CrashSphere(Math::Vector( -3.0f, 23.0f, -1.0f), 2.0f, SOUND_BOUMv, 0.15f));
    }

    if ( type == OBJECT_RUINmobilew1 )  // vehicle had wheels?
    {
        result.push_back(CrashSphere(Math::Vector(0.0f, 2.8f, 0.0f), 3.0f, SOUND_BOUMm, 0.45f));
    }

    if ( type == OBJECT_RUINmobilew2 )  // vehicle has wheels?
    {
        result.push_back(CrashSphere(Math::Vector(0.0f, 2.8f, 0.0f), 3.0f, SOUND_BOUMm, 0.45f));
    }

    if ( type == OBJECT_RUINmobilet1 )  // vehicle have caterpillars?
    {
        result.push_back(CrashSphere(Math::Vector(1.0f, 2.8f, -1.0f), 5.0f, SOUND_BOUMm, 0.45f));
    }

    if ( type == OBJECT_RUINmobilet2 )  // vehicle have caterpillars?
    {
        result.push_back(CrashSphere(Math::Vector(0.0f, 2.8f, 0.0f), 5.0f, SOUND_BOUMm, 0.45f));
    }

    if ( type == OBJECT_RUINmobiler1 )  // vehicle skating?
    {
        result.push_back(CrashSphere(Math::Vector(1.0f, 2.8f, -1.0f), 5.0f, SOUND_BOUMm, 0.45f));
    }

    if ( type == OBJECT_RUINmobiler2 )  // vehicle skating?
    {
        result.push_back(CrashSphere(Math::Vector(0.0f, 1.0f, 0.0f), 5.0f, SOUND_BOUMm, 0.45f));
    }

    if ( type == OBJECT_RUINfactory )  // factory ?
    {
        result.push_back(CrashSphere(Math::Vector(  9.0f,  1.0f, -11.0f), 5.0f, SOUND_BOUMm, 0.45f));
        result.push_back(CrashSphere(Math::Vector(  0.0f,  2.0f, -11.0f), 4.0f, SOUND_BOUMm, 0.45f));
        result.push_back(CrashSphere(Math::Vector(-10.0f,  4.0f, -10.0f), 5.0f, SOUND_BOUMm, 0.45f));
        result.push_back(CrashSphere(Math::Vector(-12.0f, 11.0f,  -4.0f), 3.0f, SOUND_BOUMm, 0.45f));
        result.push_back(CrashSphere(Math::Vector(-10.0f,  4.0f,  -2.0f), 3.0f, SOUND_BOUMm, 0.45f));
        result.push_back(CrashSphere(Math::Vector(-11.0f,  8.0f,   3.0f), 3.0f, SOUND_BOUMm, 0.45f));
        result.push_back(CrashSphere(Math::Vector(-11.0f,  2.0f,   4.0f), 3.0f, SOUND_BOUMm, 0.45f));
        result.push_back(CrashSphere(Math::Vector(-11.0f,  2.0f,  10.0f), 3.0f, SOUND_BOUMm, 0.45f));
        result.push_back(CrashSphere(Math::Vector( -4.0f,  0.0f,  10.0f), 3.0f, SOUND_BOUMm, 0.45f));
    }

    if ( type == OBJECT_RUINdoor )  // converter holder?
    {
        result.push_back(CrashSphere(Math::Vector(0.0f, 0.0f, 0.0f), 5.0f, SOUND_BOUMm, 0.45f));
    }

    if ( type == OBJECT_RUINsupport )  // radar holder?
    {
        result.push_back(CrashSphere(Math::Vector(0.0f, 0.0f, 0.0f), 3.0f, SOUND_BOUMm, 0.45f));
    }

    if ( type == OBJECT_RUINradar )  // radar base?
    {
        result.push_back(CrashSphere(Math::Vector(0.0f, 0.0f, 0.0f), 5.0f, SOUND_BOUMm, 0.45f));
    }

    if ( type == OBJECT_RUINconvert )  // converter?
    {
        result.push_back(CrashSphere(Math::Vector(-10.0f,  0.0f,  4.0f), 5.0f, SOUND_BOUMm, 0.45f));
        result.push_back(CrashSphere(Math::Vector(-10.0f,  0.0f, -4.0f), 5.0f, SOUND_BOUMm, 0.45f));
    }

    if ( type == OBJECT_RUINbase )  // base?
    {
        result.push_back(CrashSphere(Math::Vector(  0.0f, 15.0f,   0.0f),28.0f, SOUND_BOUMm, 0.45f));
        result.push_back(CrashSphere(Math::Vector( 17.0f,  6.0f,  42.0f), 6.0f, SOUND_BOUMm, 0.45f));
        result.push_back(CrashSphere(Math::Vector( 17.0f, 17.0f,  42.0f), 4.0f, SOUND_BOUMm, 0.45f));
        result.push_back(CrashSphere(Math::Vector(-17.0f,  6.0f,  42.0f), 6.0f, SOUND_BOUMm, 0.45f));
        result.push_back(CrashSphere(Math::Vector(-17.0f, 17.0f,  42.0f), 4.0f, SOUND_BOUMm, 0.45f));
        result.push_back(CrashSphere(Math::Vector(-42.0f,  6.0f,  17.0f), 6.0f, SOUND_BOUMm, 0.45f));
        result.push_back(CrashSphere(Math::Vector(-42.0f, 17.0f,  17.0f), 4.0f, SOUND_BOUMm, 0.45f));
        result.push_back(CrashSphere(Math::Vector(-42.0f,  6.0f, -17.0f), 6.0f, SOUND_BOUMm, 0.45f));
        result.push_back(CrashSphere(Math::Vector(-42.0f, 17.0f, -17.0f), 4.0f, SOUND_BOUMm, 0.45f));
        result.push_back(CrashSphere(Math::Vector(-17.0f,  6.0f, -42.0f), 6.0f, SOUND_BOUMm, 0.45f));
        result.push_back(CrashSphere(Math::Vector(-17.0f, 10.0f, -42.0f), 4.0f, SOUND_BOUMm, 0.45f));
        result.push_back(CrashSphere(Math::Vector( 15.0f, 13.0f, -34.0f), 3.0f, SOUND_BOUMm, 0.45f));
        result.push_back(CrashSphere(Math::Vector( 31.0f, 15.0f, -13.0f), 3.0f, SOUND_BOUMm, 0.45f));
        result.push_back(CrashSphere(Math::Vector( 21.0f,  8.0f, -39.0f), 5.0f, SOUND_BOUMm, 0.45f));
        result.push_back(CrashSphere(Math::Vector( 26.0f,  8.0f, -33.0f), 5.0f, SOUND_BOUMm, 0.45f));
    }

    if ( type == OBJECT_RUINhead )  // base cap?
    {
        result.push_back(CrashSphere(Math::Vector(  0.0f, 13.0f,   0.0f),20.0f, SOUND_BOUMm, 0.45f));
        result.push_back(CrashSphere(Math::Vector(  0.0f, -8.0f,   0.0f), 5.0f, SOUND_BOUMm, 0.45f));
        result.push_back(CrashSphere(Math::Vector(  0.0f,-16.0f,   0.0f), 3.0f, SOUND_BOUMm, 0.45f));
        result.push_back(CrashSphere(Math::Vector(  0.0f,-22.0f,   0.0f), 3.0f, SOUND_BOUMm, 0.45f));
        result.push_back(CrashSphere(Math::Vector(-21.0f,  7.0f,   9.0f), 8.0f, SOUND_BOUMm, 0.45f));
        result.push_back(CrashSphere(Math::Vector( -9.0f,  7.0f,  21.0f), 8.0f, SOUND_BOUMm, 0.45f));
        result.push_back(CrashSphere(Math::Vector( 21.0f,  7.0f,   9.0f), 8.0f, SOUND_BOUMm, 0.45f));
        result.push_back(CrashSphere(Math::Vector(  9.0f,  7.0f,  21.0f), 8.0f, SOUND_BOUMm, 0.45f));
        result.push_back(CrashSphere(Math::Vector(-21.0f,  7.0f,  -9.0f), 8.0f, SOUND_BOUMm, 0.45f));
        result.push_back(CrashSphere(Math::Vector( -9.0f,  7.0f, -21.0f), 8.0f, SOUND_BOUMm, 0.45f));
        result.push_back(CrashSphere(Math::Vector( 21.0f,  7.0f,  -9.0f), 8.0f, SOUND_BOUMm, 0.45f));
        result.push_back(CrashSphere(Math::Vector(  9.0f,  7.0f, -21.0f), 8.0f, SOUND_BOUMm, 0.45f));
    }

    if ( type == OBJECT_APOLLO1 )  // LEM ?
    {
        result.push_back(CrashSphere(Math::Vector(  0.0f, 4.0f,   0.0f), 9.0f, SOUND_BOUMm, 0.45f));
        result.push_back(CrashSphere(Math::Vector( 11.0f, 5.0f,   0.0f), 3.0f, SOUND_BOUMm, 0.45f));
        result.push_back(CrashSphere(Math::Vector(-11.0f, 5.0f,   0.0f), 3.0f, SOUND_BOUMm, 0.45f));
        result.push_back(CrashSphere(Math::Vector(  0.0f, 5.0f, -11.0f), 3.0f, SOUND_BOUMm, 0.45f));
        result.push_back(CrashSphere(Math::Vector(  0.0f, 5.0f,  11.0f), 3.0f, SOUND_BOUMm, 0.45f));
    }

    if ( type == OBJECT_APOLLO4 )  // module?
    {
        result.push_back(CrashSphere(Math::Vector(0.0f, 2.0f, 0.0f), 2.0f, SOUND_BOUMm, 0.45f));
    }

    if ( type == OBJECT_APOLLO5 )  // antenna?
    {
        result.push_back(CrashSphere(Math::Vector(0.0f, 4.0f, 0.0f), 3.0f, SOUND_BOUMm, 0.35f));
    }

    return result;
}

Math::Sphere CHardcodeCollection::GetCreationCameraCollisionSphere(ObjectType type)
{
    if ( type == OBJECT_EGG )
    {
        return (Math::Sphere(Math::Vector(0.0f, 5.0f, 0.0f), 10.0f));
    }
    else if ( type == OBJECT_BOMB )
    {
        return (Math::Sphere(Math::Vector(0.0f, 0.0f, 0.0f), 3.0f));
    }
    else if ( type == OBJECT_BAG )
    {
        return (Math::Sphere(Math::Vector(0.0f, 0.0f, 0.0f), 4.0f));
    }
    else if ( type == OBJECT_STONE   ||
              type == OBJECT_URANIUM ||
              type == OBJECT_METAL   ||
              type == OBJECT_BULLET  ||
              type == OBJECT_BBOX    ||
              type == OBJECT_KEYa    ||
              type == OBJECT_KEYb    ||
              type == OBJECT_KEYc    ||
              type == OBJECT_KEYd    ||
              type == OBJECT_TNT     ||
              type == OBJECT_SHOW    ||
              type == OBJECT_WINFIRE )
    {
        return (Math::Sphere(Math::Vector(0.0f, 1.0f, 0.0f), 1.5f));
    }

    if ( type == OBJECT_PLANT0 ||
         type == OBJECT_PLANT1 ||
         type == OBJECT_PLANT2 ||
         type == OBJECT_PLANT3 ||
         type == OBJECT_PLANT4 )  // standard?
    {
        return (Math::Sphere(Math::Vector(0.0f, 3.0f, 0.0f), 6.0f));
    }

    if ( type == OBJECT_PLANT10 ||
         type == OBJECT_PLANT11 ||
         type == OBJECT_PLANT12 ||
         type == OBJECT_PLANT13 ||
         type == OBJECT_PLANT14 )  // succulent?
    {
        return (Math::Sphere(Math::Vector(0.0f, 6.0f, 0.0f), 6.0f));
    }

    if ( type == OBJECT_PLANT15 ||
         type == OBJECT_PLANT16 ||
         type == OBJECT_PLANT17 ||
         type == OBJECT_PLANT18 )  // fern?
    {
        return (Math::Sphere(Math::Vector(0.0f, 3.0f, 0.0f), 6.0f));
    }

    if ( type == OBJECT_MUSHROOM1 )
    {
        return (Math::Sphere(Math::Vector(0.0f, 3.0f, 0.0f), 5.5f));
    }

    if ( type == OBJECT_MUSHROOM2 )
    {
        return (Math::Sphere(Math::Vector(0.0f, 4.0f, 0.0f), 5.5f));
    }

    if ( type == OBJECT_TEEN3 )  // jar with pencils
    {
        return (Math::Sphere(Math::Vector(0.0f, 4.0f, 0.0f), 4.0f));
    }

    if ( type == OBJECT_TEEN8 )  // a stack of books 1
    {
        return (Math::Sphere(Math::Vector(0.0f, 10.0f, 0.0f), 12.0f));
    }

    if ( type == OBJECT_TEEN9 )  // a stack of books 2
    {
        return (Math::Sphere(Math::Vector(0.0f, 10.0f, 0.0f), 12.0f));
    }

    if ( type == OBJECT_TEEN10 )  // bookcase
    {
        return (Math::Sphere(Math::Vector(0.0f, 6.0f, 0.0f), 20.0f));
    }

    if ( type == OBJECT_TEEN12 )  // coke
    {
        return (Math::Sphere(Math::Vector(0.0f, 9.0f, 0.0f), 5.0f));
    }

    if ( type == OBJECT_TEEN13 )  // cardboard farm
    {
        return (Math::Sphere(Math::Vector(0.0f, 5.0f, 0.0f), 15.0f));
    }

    if ( type == OBJECT_TEEN14 )  // open box
    {
        return (Math::Sphere(Math::Vector(0.0f, 5.0f, 0.0f), 15.0f));
    }

    if ( type == OBJECT_TEEN15 )  // stack of cartons
    {
        return (Math::Sphere(Math::Vector(0.0f, 5.0f, 0.0f), 15.0f));
    }

    if ( type == OBJECT_TEEN16 )  // watering can
    {
        return (Math::Sphere(Math::Vector(0.0f, 13.0f, 0.0f), 20.0f));
    }

    if ( type == OBJECT_TEEN17 )  // wheel |
    {
        return (Math::Sphere(Math::Vector(0.0f, 31.0f, 0.0f), 31.0f));
    }

    if ( type == OBJECT_TEEN18 )  // wheel /
    {
        return (Math::Sphere(Math::Vector(0.0f, 31.0f, 0.0f), 31.0f));
    }

    if ( type == OBJECT_TEEN19 )  // wheel =
    {
        return (Math::Sphere(Math::Vector(0.0f, 10.0f, 0.0f), 32.0f));
    }

    if ( type == OBJECT_TEEN30 )  // jump?
    {
        return (Math::Sphere(Math::Vector(0.0f, 15.0f, 0.0f), 17.0f));
    }

    if ( type == OBJECT_TEEN31 )  // basket?
    {
        return (Math::Sphere(Math::Vector(0.0f, 0.0f, 0.0f), 10.0f));
    }

    if ( type == OBJECT_TEEN32 )  // chair?
    {
        return (Math::Sphere(Math::Vector(0.0f, 0.0f, 0.0f), 26.0f));
    }


    if ( type == OBJECT_TEEN38 )  // fan?
    {
        return (Math::Sphere(Math::Vector(0.0f, 2.0f, 0.0f), 10.0f));
    }

    if ( type == OBJECT_TEEN39 )  // potted plant?
    {
        return (Math::Sphere(Math::Vector(0.0f, 2.0f, 0.0f), 8.5f));
    }

    if ( type == OBJECT_TEEN40 )  // balloon?
    {
        return (Math::Sphere(Math::Vector(0.0f, 14.0f, 0.0f), 15.0f));
    }

    if ( type == OBJECT_TEEN44 )  // car?
    {
        return (Math::Sphere(Math::Vector(0.0f, 10.0f, 0.0f), 55.0f));
    }

    if ( type == OBJECT_QUARTZ0 )
    {
        return (Math::Sphere(Math::Vector(0.0f, 2.0f, 0.0f), 3.5f));
    }
    if ( type == OBJECT_QUARTZ1 )
    {
        return (Math::Sphere(Math::Vector(0.0f, 4.0f, 0.0f), 5.0f));
    }
    if ( type == OBJECT_QUARTZ2 )
    {
        return (Math::Sphere(Math::Vector(0.0f, 6.0f, 0.0f), 6.0f));
    }
    if ( type == OBJECT_QUARTZ3 )
    {
        return (Math::Sphere(Math::Vector(0.0f, 10.0f, 0.0f), 10.0f));
    }

    if ( type == OBJECT_ROOT0 )
    {
//?     return (Math::Sphere(Math::Vector(0.0f, 6.0f, 0.0f), 11.0f));
    }
    if ( type == OBJECT_ROOT1 )
    {
//?     return (Math::Sphere(Math::Vector(0.0f, 6.0f, 0.0f), 12.0f));
    }
    if ( type == OBJECT_ROOT2 )
    {
//?     return (Math::Sphere(Math::Vector(0.0f, 6.0f, 0.0f), 10.0f));
    }
    if ( type == OBJECT_ROOT3 )
    {
//?     return (Math::Sphere(Math::Vector(0.0f, 10.0f, 0.0f), 14.0f));
    }
    if ( type == OBJECT_ROOT4 )
    {
//?     return (Math::Sphere(Math::Vector(0.0f, 12.0f, 0.0f), 20.0f));
    }
    if ( type == OBJECT_ROOT5 )  // gravity root ?
    {
//?     return (Math::Sphere(Math::Vector(0.0f, 12.0f, 0.0f), 20.0f));
    }

    if ( type == OBJECT_HOME1 )
    {
//?     return (Math::Sphere(Math::Vector(0.0f, 6.0f, 0.0f), 11.0f));
    }

    if ( type == OBJECT_RUINmobilew1 )  // vehicle had wheels?
    {
//?     return (Math::Sphere(Math::Vector(0.0f, 5.0f, 0.0f), 10.0f));
    }

    if ( type == OBJECT_RUINmobilew2 )  // vehicle has wheels?
    {
//?     return (Math::Sphere(Math::Vector(0.0f, 5.0f, 0.0f), 10.0f));
    }

    if ( type == OBJECT_RUINmobilet1 )  // vehicle have caterpillars?
    {
//?     return (Math::Sphere(Math::Vector(1.0f, 5.0f, -1.0f), 10.0f));
    }

    if ( type == OBJECT_RUINmobilet2 )  // vehicle have caterpillars?
    {
//?     return (Math::Sphere(Math::Vector(0.0f, 5.0f, 0.0f), 10.0f));
    }

    if ( type == OBJECT_RUINmobiler1 )  // vehicle skating?
    {
        return (Math::Sphere(Math::Vector(1.0f, 5.0f, -1.0f), 10.0f));
    }

    if ( type == OBJECT_RUINmobiler2 )  // vehicle skating?
    {
        return (Math::Sphere(Math::Vector(0.0f, 5.0f, 0.0f), 10.0f));
    }

    if ( type == OBJECT_RUINfactory )  // factory ?
    {
        return (Math::Sphere(Math::Vector(0.0f, 0.0f, 0.0f), 18.0f));
    }

    if ( type == OBJECT_RUINdoor )  // converter holder?
    {
//?     return (Math::Sphere(Math::Vector(0.0f, 0.0f, 0.0f), 6.0f));
    }

    if ( type == OBJECT_RUINsupport )  // radar holder?
    {
//?     return (Math::Sphere(Math::Vector(0.0f, 0.0f, 0.0f), 4.0f));
    }

    if ( type == OBJECT_RUINradar )  // radar base?
    {
//?     return (Math::Sphere(Math::Vector(0.0f, 0.0f, 0.0f), 6.0f));
    }

    if ( type == OBJECT_RUINconvert )  // converter?
    {
//?     return (Math::Sphere(Math::Vector(-3.0f, 0.0f, 0.0f), 14.0f));
    }

    if ( type == OBJECT_RUINbase )  // base?
    {
        return (Math::Sphere(Math::Vector(0.0f, 0.0f, 0.0f), 48.0f));
    }

    if ( type == OBJECT_RUINhead )  // base cap?
    {
        return (Math::Sphere(Math::Vector(0.0f, 0.0f, 0.0f), 35.0f));
    }

    if ( type == OBJECT_APOLLO1 )  // LEM ?
    {
        return (Math::Sphere(Math::Vector(0.0f, 4.0f, 0.0f), 9.0f));
    }

    return Math::Sphere();
}

bool CHardcodeCollection::IsJosteable(ObjectType type)
{
    if ( type == OBJECT_FLAGb ||
         type == OBJECT_FLAGr ||
         type == OBJECT_FLAGg ||
         type == OBJECT_FLAGy ||
         type == OBJECT_FLAGv ) return true;
    if ( type == OBJECT_PLANT0 ||
         type == OBJECT_PLANT1 ||
         type == OBJECT_PLANT2 ||
         type == OBJECT_PLANT3 ||
         type == OBJECT_PLANT4 ) return true;
    if ( type == OBJECT_PLANT5 ||
         type == OBJECT_PLANT6 ||
         type == OBJECT_PLANT7 ) return true;
    if ( type == OBJECT_PLANT10 ||
         type == OBJECT_PLANT11 ||
         type == OBJECT_PLANT12 ||
         type == OBJECT_PLANT13 ||
         type == OBJECT_PLANT14 ) return true;
    if ( type == OBJECT_PLANT15 ||
         type == OBJECT_PLANT16 ||
         type == OBJECT_PLANT17 ||
         type == OBJECT_PLANT18 ) return true;
    if ( type == OBJECT_PLANT19 ) return true;
    if ( type == OBJECT_MUSHROOM1 ) return true;
    if ( type == OBJECT_MUSHROOM2 ) return true;
    if ( type == OBJECT_APOLLO3 ) return true;

    return false;
}

float CHardcodeCollection::GetJosteFactor(ObjectType type)
{
    if ( type >= OBJECT_PLANT5 &&
         type <= OBJECT_PLANT7 )  // clover?
    {
        return 3.0f;
    }
    return 1.0f;
}

Math::Sphere CHardcodeCollection::GetJostlingSphere(ObjectType type)
{
    if ( type == OBJECT_FLAGb ||
         type == OBJECT_FLAGr ||
         type == OBJECT_FLAGg ||
         type == OBJECT_FLAGy ||
         type == OBJECT_FLAGv )
    {
        return (Math::Sphere(Math::Vector(0.0f, 4.0f, 0.0f), 1.0f));
    }

    if ( type == OBJECT_PLANT0 ||
         type == OBJECT_PLANT1 ||
         type == OBJECT_PLANT2 ||
         type == OBJECT_PLANT3 ||
         type == OBJECT_PLANT4 )  // standard?
    {
        return (Math::Sphere(Math::Vector(0.0f, 0.0f, 0.0f), 8.0f));
    }

    if ( type == OBJECT_PLANT5 ||
         type == OBJECT_PLANT6 ||
         type == OBJECT_PLANT7 )  // clover?
    {
        return (Math::Sphere(Math::Vector(0.0f, 0.0f, 0.0f), 4.0f));
    }

    if ( type == OBJECT_PLANT10 ||
         type == OBJECT_PLANT11 ||
         type == OBJECT_PLANT12 ||
         type == OBJECT_PLANT13 ||
         type == OBJECT_PLANT14 )  // succulent?
    {
        return (Math::Sphere(Math::Vector(0.0f, 4.0f, 0.0f), 8.0f));
    }

    if ( type == OBJECT_PLANT15 ||
         type == OBJECT_PLANT16 ||
         type == OBJECT_PLANT17 ||
         type == OBJECT_PLANT18 )  // fern?
    {
        return (Math::Sphere(Math::Vector(0.0f, 0.0f, 0.0f), 8.0f));
    }

    if ( type == OBJECT_PLANT19 )  // fern?
    {
        return (Math::Sphere(Math::Vector(0.0f, 0.0f, 0.0f), 8.0f));
    }

    if ( type == OBJECT_MUSHROOM1 )
    {
        return (Math::Sphere(Math::Vector(0.0f, 3.0f, 0.0f), 5.5f));
    }

    if ( type == OBJECT_MUSHROOM2 )
    {
        return (Math::Sphere(Math::Vector(0.0f, 4.0f, 0.0f), 5.5f));
    }

    if ( type == OBJECT_APOLLO3 )  // flag?
    {
        return (Math::Sphere(Math::Vector(0.0f, 4.0f, 0.0f), 1.0f));
    }

    return Math::Sphere();
}

std::vector<CObjectCreationBuildingLevel> CHardcodeCollection::GetCreationBuildingLevels(ObjectType type)
{
    std::vector<CObjectCreationBuildingLevel> result;

    if ( type == OBJECT_TEEN5 )  // CD
    {
        result.push_back({5.9f, 6.1f, 0.2f, 0.5f});
    }

    if ( type == OBJECT_RUINconvert )  // converter?
    {
        result.push_back({7.0f, 9.0f, 1.0f, 0.5f});
    }

    if ( type == OBJECT_APOLLO1 )  // LEM ?
    {
//       result.push_back({10.0f, 13.0f, 12.0f, 0.0f});
    }

    return result;
}

CObjectCreationShadowCircle CHardcodeCollection::GetCreationShadowCircle(ObjectType type)
{
    if ( type == OBJECT_MARKSTONE   ||
         type == OBJECT_MARKURANIUM ||
         type == OBJECT_MARKKEYa    ||
         type == OBJECT_MARKKEYb    ||
         type == OBJECT_MARKKEYc    ||
         type == OBJECT_MARKKEYd    ||
         type == OBJECT_MARKPOWER   ||
         type == OBJECT_WAYPOINT    )
    {
        return {3.0f, 1.0f};
    }
    else if ( type == OBJECT_EGG )
    {
        return {3.0f, 1.0f};
    }
    else if ( type == OBJECT_BOMB )
    {
        return {3.0f, 1.0f};
    }
    else if ( type == OBJECT_BAG )
    {
        return {5.0f, 1.0f};
    }
    else if ( type == OBJECT_FLAGb ||
              type == OBJECT_FLAGr ||
              type == OBJECT_FLAGg ||
              type == OBJECT_FLAGy ||
              type == OBJECT_FLAGv )
    {
        return {2.0f, 0.3f};
    }
    else if ( type == OBJECT_STONE   ||
              type == OBJECT_URANIUM ||
              type == OBJECT_METAL   ||
              type == OBJECT_BULLET  ||
              type == OBJECT_BBOX    ||
              type == OBJECT_KEYa    ||
              type == OBJECT_KEYb    ||
              type == OBJECT_KEYc    ||
              type == OBJECT_KEYd    ||
              type == OBJECT_TNT     ||
              type == OBJECT_SHOW    ||
              type == OBJECT_WINFIRE )
    {
        return {1.5f, 1.0f};
    }

    if ( type == OBJECT_BARRIER0 )
    {
        return {6.0f, 0.5f, Gfx::ENG_SHADOW_WORM};
    }

    if ( type == OBJECT_BARRIER1 )
    {
        return {12.0f, 0.5f, Gfx::ENG_SHADOW_WORM};
    }

    if ( type == OBJECT_BARRIER2 )  // cardboard?
    {
        return {12.0f, 0.8f, Gfx::ENG_SHADOW_WORM};
    }

    if ( type == OBJECT_BARRIER3 )  // match + straw?
    {
        return {10.0f, 0.5f, Gfx::ENG_SHADOW_WORM};
    }

    if ( type == OBJECT_BARRICADE0 )
    {
        return {6.0f, 0.5f, Gfx::ENG_SHADOW_WORM};
    }

    if ( type == OBJECT_BARRICADE1 )
    {
        return {12.0f, 0.5f, Gfx::ENG_SHADOW_WORM};
    }

    if ( type == OBJECT_PLANT0 ||
         type == OBJECT_PLANT1 ||
         type == OBJECT_PLANT2 ||
         type == OBJECT_PLANT3 ||
         type == OBJECT_PLANT4 )  // standard?
    {
        return {8.0f, 0.5f};
    }

    if ( type == OBJECT_PLANT5 ||
         type == OBJECT_PLANT6 ||
         type == OBJECT_PLANT7 )  // clover?
    {
        return {5.0f, 0.3f};
    }

    if ( type == OBJECT_PLANT8 ||
         type == OBJECT_PLANT9 )  // squash?
    {
        return {10.0f, 0.5f};
    }

    if ( type == OBJECT_PLANT10 ||
         type == OBJECT_PLANT11 ||
         type == OBJECT_PLANT12 ||
         type == OBJECT_PLANT13 ||
         type == OBJECT_PLANT14 )  // succulent?
    {
        return {8.0f, 0.3f};
    }

    if ( type == OBJECT_PLANT15 ||
         type == OBJECT_PLANT16 ||
         type == OBJECT_PLANT17 ||
         type == OBJECT_PLANT18 )  // fern?
    {
        return {8.0f, 0.5f};
    }

    if ( type == OBJECT_PLANT19 )  // fern?
    {
        return {8.0f, 0.5f};
    }

    if ( type == OBJECT_TREE0 )
    {
        return {8.0f, 0.5f};
    }

    if ( type == OBJECT_TREE1 )
    {
        return {8.0f, 0.5f};
    }

    if ( type == OBJECT_TREE2 )
    {
        return {8.0f, 0.5f};
    }

    if ( type == OBJECT_TREE3 )
    {
        return {8.0f, 0.5f};
    }

    if ( type == OBJECT_TREE4 )
    {
        return {8.0f, 0.5f};
    }

    if ( type == OBJECT_TREE5 )  // giant tree (for the world "teen")
    {
        return {50.0f, 0.5f};
    }

    if ( type == OBJECT_MUSHROOM1 )
    {
       return {6.0f, 0.5f};
    }

    if ( type == OBJECT_MUSHROOM2 )
    {
       return {5.0f, 0.5f};
    }

    if ( type == OBJECT_TEEN0 )  // orange pencil lg=10
    {
       return {5.0f, 0.8f, Gfx::ENG_SHADOW_WORM, true};
    }

    if ( type == OBJECT_TEEN1 )  // blue pencil lg=14
    {
       return {6.0f, 0.8f, Gfx::ENG_SHADOW_WORM, true};
    }

    if ( type == OBJECT_TEEN2 )  // red pencil lg=16
    {
       return {6.0f, 0.8f, Gfx::ENG_SHADOW_WORM, true};
    }

    if ( type == OBJECT_TEEN3 )  // jar with pencils
    {
       return {6.0f, 0.5f, Gfx::ENG_SHADOW_NORM, true};
    }

    if ( type == OBJECT_TEEN4 )  // scissors
    {
       return {10.0f, 0.5f, Gfx::ENG_SHADOW_WORM, true};
    }

    if ( type == OBJECT_TEEN5 )  // CD
    {
       return {8.0f, 0.2f, Gfx::ENG_SHADOW_NORM, true};
    }

    if ( type == OBJECT_TEEN6 )  // book 1
    {
       return {20.0f, 0.2f, Gfx::ENG_SHADOW_NORM, true};
    }

    if ( type == OBJECT_TEEN7 )  // book 2
    {
       return {20.0f, 0.2f, Gfx::ENG_SHADOW_NORM, true};
    }

    if ( type == OBJECT_TEEN8 )  // a stack of books 1
    {
       return {20.0f, 0.2f, Gfx::ENG_SHADOW_NORM, true};
    }

    if ( type == OBJECT_TEEN9 )  // a stack of books 2
    {
       return {20.0f, 0.2f, Gfx::ENG_SHADOW_NORM, true};
    }

    if ( type == OBJECT_TEEN10 )  // bookcase
    {
       return {40.0f, 0.2f, Gfx::ENG_SHADOW_NORM, true};
    }

    if ( type == OBJECT_TEEN12 )  // coke
    {
       return {4.5f, 1.0f, Gfx::ENG_SHADOW_NORM, true};
    }

    if ( type == OBJECT_TEEN13 )  // cardboard farm
    {
       return {20.0f, 1.0f, Gfx::ENG_SHADOW_NORM, true};
    }

    if ( type == OBJECT_TEEN14 )  // open box
    {
       return {20.0f, 1.0f, Gfx::ENG_SHADOW_NORM, true};
    }

    if ( type == OBJECT_TEEN15 )  // stack of cartons
    {
       return {20.0f, 1.0f, Gfx::ENG_SHADOW_NORM, true};
    }

    if ( type == OBJECT_TEEN16 )  // watering can
    {
       return {18.0f, 1.0f, Gfx::ENG_SHADOW_NORM, true};
    }

    if ( type == OBJECT_TEEN17 )  // wheel |
    {
       return {24.0f, 0.5f, Gfx::ENG_SHADOW_NORM, true};
    }

    if ( type == OBJECT_TEEN18 )  // wheel /
    {
       return {24.0f, 0.5f, Gfx::ENG_SHADOW_NORM, true};
    }

    if ( type == OBJECT_TEEN19 )  // wheel =
    {
       return {33.0f, 1.0f, Gfx::ENG_SHADOW_NORM, true};
    }

    if ( type == OBJECT_TEEN23 )  // skateboard on wheels
    {
       return {35.0f, 0.8f, Gfx::ENG_SHADOW_WORM, true};
    }

    if ( type == OBJECT_TEEN24 )  // skate /
    {
       return {20.0f, 0.2f, Gfx::ENG_SHADOW_NORM, true};
    }

    if ( type == OBJECT_TEEN25 )  // skate /
    {
       return {20.0f, 0.2f, Gfx::ENG_SHADOW_NORM, true};
    }

    if ( type == OBJECT_TEEN27 )  // large plant?
    {
       return {40.0f, 0.5f};
    }

    if ( type == OBJECT_TEEN28 )  // bottle?
    {
       return {7.0f, 0.6f, Gfx::ENG_SHADOW_NORM, true};
    }

    if ( type == OBJECT_TEEN30 )  // jump?
    {
       return {20.0f, 1.0f, Gfx::ENG_SHADOW_NORM, true};
    }

    if ( type == OBJECT_TEEN31 )  // basket?
    {
       return {16.0f, 0.6f, Gfx::ENG_SHADOW_NORM, true};
    }

    if ( type == OBJECT_TEEN32 )  // chair?
    {
       return {35.0f, 0.3f, Gfx::ENG_SHADOW_NORM, true};
    }

    if ( type == OBJECT_TEEN33 )  // panel?
    {
       return {10.0f, 0.3f, Gfx::ENG_SHADOW_NORM, true};
    }

    if ( type == OBJECT_TEEN34 )  // stone?
    {
       return {3.0f, 1.0f, Gfx::ENG_SHADOW_NORM, true};
    }

    if ( type == OBJECT_TEEN35 )  // pipe?
    {
       return {40.0f, 0.8f, Gfx::ENG_SHADOW_WORM, true};
    }

    if ( type == OBJECT_TEEN38 )  // fan?
    {
       return {15.0f, 0.5f, Gfx::ENG_SHADOW_NORM, true};
    }

    if ( type == OBJECT_TEEN39 )  // potted plant?
    {
       return {10.0f, 1.0f, Gfx::ENG_SHADOW_NORM, true};
    }

    if ( type == OBJECT_TEEN40 )  // balloon?
    {
       return {15.0f, 0.7f, Gfx::ENG_SHADOW_NORM, true};
    }

    if ( type == OBJECT_TEEN42 )  // clover?
    {
       return {15.0f, 0.4f, Gfx::ENG_SHADOW_NORM, true};
    }

    if ( type == OBJECT_TEEN43 )  // clover?
    {
       return {15.0f, 0.4f, Gfx::ENG_SHADOW_NORM, true};
    }

    if ( type == OBJECT_TEEN44 )  // car?
    {
       return {55.0f, 1.0f, Gfx::ENG_SHADOW_NORM, true};
    }


    if ( type == OBJECT_QUARTZ0 )
    {
        return {4.0f, 0.5f};
    }
    if ( type == OBJECT_QUARTZ1 )
    {
        return {5.0f, 0.5f};
    }
    if ( type == OBJECT_QUARTZ2 )
    {
        return {6.0f, 0.5f};
    }
    if ( type == OBJECT_QUARTZ3 )
    {
        return {10.0f, 0.5f};
    }

    if ( type == OBJECT_ROOT0 )
    {
        return {16.0f, 0.5f};
    }
    if ( type == OBJECT_ROOT1 )
    {
        return {16.0f, 0.5f};
    }
    if ( type == OBJECT_ROOT2 )
    {
        return {16.0f, 0.5f};
    }
    if ( type == OBJECT_ROOT3 )
    {
        return {22.0f, 0.5f};
    }
    if ( type == OBJECT_ROOT4 )
    {
        return {30.0f, 0.5f};
    }
    if ( type == OBJECT_ROOT5 )  // gravity root ?
    {
        return {30.0f, 0.5f};
    }

    if ( type == OBJECT_HOME1 )
    {
        return {16.0f, 0.5f};
    }

    if ( type == OBJECT_RUINmobilew1 )  // vehicle had wheels?
    {
        return {4.0f, 1.0f};
    }

    if ( type == OBJECT_RUINmobilew2 )  // vehicle has wheels?
    {
        return {4.0f, 1.0f};
    }

    if ( type == OBJECT_RUINmobilet1 )  // vehicle have caterpillars?
    {
        return {5.0f, 1.0f};
    }

    if ( type == OBJECT_RUINmobilet2 )  // vehicle have caterpillars?
    {
        return {5.0f, 1.0f};
    }

    if ( type == OBJECT_RUINmobiler1 )  // vehicle skating?
    {
        return {5.0f, 1.0f};
    }

    if ( type == OBJECT_RUINmobiler2 )  // vehicle skating?
    {
        return {6.0f, 1.0f};
    }

    if ( type == OBJECT_RUINfactory )  // factory ?
    {
        return {20.0f, 0.7f};
    }

    if ( type == OBJECT_RUINdoor )  // converter holder?
    {
        return {6.0f, 1.0f};
    }

    if ( type == OBJECT_RUINsupport )  // radar holder?
    {
        return {3.0f, 1.0f};
    }

    if ( type == OBJECT_RUINradar )  // radar base?
    {
        return {6.0f, 1.0f};
    }

    if ( type == OBJECT_RUINbase )  // base?
    {
        return {40.0f, 1.0f};
    }

    if ( type == OBJECT_RUINhead )  // base cap?
    {
        return {30.0f, 1.0f};
    }

    if ( type == OBJECT_APOLLO1 )  // LEM ?
    {
        return {16.0f, 0.5f};
    }


    if ( type == OBJECT_APOLLO3 )  // flag?
    {
        return {2.0f, 0.3f};
    }

    if ( type == OBJECT_APOLLO4 )  // module?
    {
        return {5.0f, 0.8f};
    }

    if ( type == OBJECT_APOLLO5 )  // antenna?
    {
        return {3.0f, 0.7f};
    }

    return CObjectCreationShadowCircle();
}

float CHardcodeCollection::GetCreationScale(ObjectType type)
{
    if ( type == OBJECT_BAG )   return 1.5f;
    if ( type == OBJECT_ROOT0 ) return 2.0f;
    if ( type == OBJECT_ROOT1 ) return 2.0f;
    if ( type == OBJECT_ROOT2 ) return 2.0f;
    if ( type == OBJECT_ROOT3 ) return 2.0f;
    if ( type == OBJECT_ROOT4 ) return 2.0f;
    if ( type == OBJECT_ROOT5 ) return 2.0f;
    if ( type == OBJECT_HOME1 ) return 1.3f;
    if ( type == OBJECT_APOLLO1 ) return 1.2f;
    return 1.0f;
}

bool CHardcodeCollection::IsCreationForceLoadTextures(ObjectType type)
{
    switch(type)
    {
        case OBJECT_STONE:
        case OBJECT_URANIUM:
        case OBJECT_METAL:
        case OBJECT_POWER:
        case OBJECT_ATOMIC:
        case OBJECT_BULLET:
        case OBJECT_BBOX:
        case OBJECT_KEYa:
        case OBJECT_KEYb:
        case OBJECT_KEYc:
        case OBJECT_KEYd:
        case OBJECT_TNT:
        case OBJECT_BOMB:
        case OBJECT_WAYPOINT:
        case OBJECT_SHOW:
        case OBJECT_WINFIRE:
        case OBJECT_BAG:
        case OBJECT_MARKPOWER:
        case OBJECT_MARKSTONE:
        case OBJECT_MARKURANIUM:
        case OBJECT_MARKKEYa:
        case OBJECT_MARKKEYb:
        case OBJECT_MARKKEYc:
        case OBJECT_MARKKEYd:
        case OBJECT_EGG:
            return true;

        case OBJECT_FLAGb:
        case OBJECT_FLAGr:
        case OBJECT_FLAGg:
        case OBJECT_FLAGy:
        case OBJECT_FLAGv:
            return true;

        default:
            return false;
    }
}

bool CHardcodeCollection::IsCreationSetFloorHeight(ObjectType type)
{
    switch(type)
    {
        case OBJECT_STONE:
        case OBJECT_URANIUM:
        case OBJECT_METAL:
        case OBJECT_POWER:
        case OBJECT_ATOMIC:
        case OBJECT_BULLET:
        case OBJECT_BBOX:
        case OBJECT_KEYa:
        case OBJECT_KEYb:
        case OBJECT_KEYc:
        case OBJECT_KEYd:
        case OBJECT_TNT:
        case OBJECT_BOMB:
        case OBJECT_WAYPOINT:
        case OBJECT_SHOW:
        case OBJECT_WINFIRE:
        case OBJECT_BAG:
        case OBJECT_MARKPOWER:
        case OBJECT_MARKSTONE:
        case OBJECT_MARKURANIUM:
        case OBJECT_MARKKEYa:
        case OBJECT_MARKKEYb:
        case OBJECT_MARKKEYc:
        case OBJECT_MARKKEYd:
        case OBJECT_EGG:
            return true;

        case OBJECT_FLAGb:
        case OBJECT_FLAGr:
        case OBJECT_FLAGg:
        case OBJECT_FLAGy:
        case OBJECT_FLAGv:
            return true;

        case OBJECT_BARRIER0:
        case OBJECT_BARRIER1:
        case OBJECT_BARRIER2:
        case OBJECT_BARRIER3:
        case OBJECT_BARRICADE0:
        case OBJECT_BARRICADE1:
            return true;

        case OBJECT_PLANT0:
        case OBJECT_PLANT1:
        case OBJECT_PLANT2:
        case OBJECT_PLANT3:
        case OBJECT_PLANT4:
        case OBJECT_PLANT5:
        case OBJECT_PLANT6:
        case OBJECT_PLANT7:
        case OBJECT_PLANT8:
        case OBJECT_PLANT9:
        case OBJECT_PLANT10:
        case OBJECT_PLANT11:
        case OBJECT_PLANT12:
        case OBJECT_PLANT13:
        case OBJECT_PLANT14:
        case OBJECT_PLANT15:
        case OBJECT_PLANT16:
        case OBJECT_PLANT17:
        case OBJECT_PLANT18:
        case OBJECT_PLANT19:
        case OBJECT_TREE0:
        case OBJECT_TREE1:
        case OBJECT_TREE2:
        case OBJECT_TREE3:
        case OBJECT_TREE4:
        case OBJECT_TREE5:
            return true;

        case OBJECT_MUSHROOM1:
        case OBJECT_MUSHROOM2:
            return true;

        case OBJECT_TEEN0:
        case OBJECT_TEEN1:
        case OBJECT_TEEN2:
        case OBJECT_TEEN3:
        case OBJECT_TEEN4:
        case OBJECT_TEEN5:
        case OBJECT_TEEN6:
        case OBJECT_TEEN7:
        case OBJECT_TEEN8:
        case OBJECT_TEEN9:
        case OBJECT_TEEN10:
        case OBJECT_TEEN11:
        case OBJECT_TEEN12:
        case OBJECT_TEEN13:
        case OBJECT_TEEN14:
        case OBJECT_TEEN15:
        case OBJECT_TEEN16:
        case OBJECT_TEEN17:
        case OBJECT_TEEN18:
        case OBJECT_TEEN19:
        case OBJECT_TEEN20:
        case OBJECT_TEEN21:
        case OBJECT_TEEN22:
        case OBJECT_TEEN23:
        case OBJECT_TEEN24:
        case OBJECT_TEEN25:
        case OBJECT_TEEN26:
        case OBJECT_TEEN27:
        case OBJECT_TEEN28:
        case OBJECT_TEEN30:
        case OBJECT_TEEN31:
        case OBJECT_TEEN32:
        case OBJECT_TEEN33:
        case OBJECT_TEEN34:
        case OBJECT_TEEN35:
        case OBJECT_TEEN38:
        case OBJECT_TEEN39:
        case OBJECT_TEEN40:
        case OBJECT_TEEN41:
        case OBJECT_TEEN42:
        case OBJECT_TEEN43:
        case OBJECT_TEEN44:
            return true;

        case OBJECT_TEEN29:
        case OBJECT_TEEN36:
        case OBJECT_TEEN37:
            return false;

        case OBJECT_QUARTZ0:
        case OBJECT_QUARTZ1:
        case OBJECT_QUARTZ2:
        case OBJECT_QUARTZ3:
            return true;

        case OBJECT_ROOT0:
        case OBJECT_ROOT1:
        case OBJECT_ROOT2:
        case OBJECT_ROOT3:
        case OBJECT_ROOT4:
        case OBJECT_ROOT5:
            return true;

        case OBJECT_HOME1:
            return true;

        case OBJECT_RUINmobilew1:
        case OBJECT_RUINmobilew2:
        case OBJECT_RUINmobilet1:
        case OBJECT_RUINmobilet2:
        case OBJECT_RUINmobiler1:
        case OBJECT_RUINmobiler2:
        case OBJECT_RUINdoor:
        case OBJECT_RUINsupport:
        case OBJECT_RUINradar:
        case OBJECT_RUINhead:
        case OBJECT_RUINfactory:
        case OBJECT_RUINconvert:
        case OBJECT_RUINbase:
            return true;
        
        case OBJECT_APOLLO1:
        case OBJECT_APOLLO3:
        case OBJECT_APOLLO4:
            return true;

        case OBJECT_APOLLO5:
            return false;

        default:
            return false;
    }
}

bool CHardcodeCollection::IsCreationFloorAdjust(ObjectType type)
{
    switch(type)
    {
        case OBJECT_STONE:
        case OBJECT_URANIUM:
        case OBJECT_METAL:
        case OBJECT_POWER:
        case OBJECT_ATOMIC:
        case OBJECT_BULLET:
        case OBJECT_BBOX:
        case OBJECT_KEYa:
        case OBJECT_KEYb:
        case OBJECT_KEYc:
        case OBJECT_KEYd:
        case OBJECT_TNT:
        case OBJECT_BOMB:
        case OBJECT_WAYPOINT:
        case OBJECT_SHOW:
        case OBJECT_WINFIRE:
        case OBJECT_BAG:
        case OBJECT_MARKPOWER:
        case OBJECT_MARKSTONE:
        case OBJECT_MARKURANIUM:
        case OBJECT_MARKKEYa:
        case OBJECT_MARKKEYb:
        case OBJECT_MARKKEYc:
        case OBJECT_MARKKEYd:
        case OBJECT_EGG:
            return true;

        case OBJECT_FLAGb:
        case OBJECT_FLAGr:
        case OBJECT_FLAGg:
        case OBJECT_FLAGy:
        case OBJECT_FLAGv:
            return true;

        case OBJECT_BARRIER0:
        case OBJECT_BARRIER1:
        case OBJECT_BARRIER2:
        case OBJECT_BARRIER3:
        case OBJECT_BARRICADE0:
        case OBJECT_BARRICADE1:
            return true;

        case OBJECT_TEEN0:
        case OBJECT_TEEN1:
        case OBJECT_TEEN2:
        case OBJECT_TEEN3:
        case OBJECT_TEEN4:
        case OBJECT_TEEN6:
        case OBJECT_TEEN7:
        case OBJECT_TEEN8:
        case OBJECT_TEEN9:
        case OBJECT_TEEN10:
        case OBJECT_TEEN11:
        case OBJECT_TEEN12:
        case OBJECT_TEEN13:
        case OBJECT_TEEN14:
        case OBJECT_TEEN15:
        case OBJECT_TEEN16:
        case OBJECT_TEEN17:
        case OBJECT_TEEN18:
        case OBJECT_TEEN19:
        case OBJECT_TEEN20:
        case OBJECT_TEEN21:
        case OBJECT_TEEN22:
        case OBJECT_TEEN23:
        case OBJECT_TEEN24:
        case OBJECT_TEEN25:
        case OBJECT_TEEN26:
        case OBJECT_TEEN27:
        case OBJECT_TEEN28:
        case OBJECT_TEEN30:
        case OBJECT_TEEN31:
        case OBJECT_TEEN32:
        case OBJECT_TEEN33:
        case OBJECT_TEEN34:
        case OBJECT_TEEN35:
        case OBJECT_TEEN38:
        case OBJECT_TEEN39:
        case OBJECT_TEEN40:
        case OBJECT_TEEN41:
        case OBJECT_TEEN42:
        case OBJECT_TEEN43:
        case OBJECT_TEEN44:
            return true;

        case OBJECT_TEEN5:
        case OBJECT_TEEN29:
        case OBJECT_TEEN36:
        case OBJECT_TEEN37:
            return false;

        case OBJECT_QUARTZ0:
        case OBJECT_QUARTZ1:
        case OBJECT_QUARTZ2:
        case OBJECT_QUARTZ3:
            return false;

        case OBJECT_ROOT0:
        case OBJECT_ROOT1:
        case OBJECT_ROOT2:
        case OBJECT_ROOT3:
        case OBJECT_ROOT4:
        case OBJECT_ROOT5:
            return false;

        case OBJECT_HOME1:
            return true;

        case OBJECT_RUINmobilew1:
        case OBJECT_RUINmobilew2:
        case OBJECT_RUINmobilet1:
        case OBJECT_RUINmobilet2:
        case OBJECT_RUINmobiler1:
        case OBJECT_RUINmobiler2:
        case OBJECT_RUINdoor:
        case OBJECT_RUINsupport:
        case OBJECT_RUINradar:
        case OBJECT_RUINhead:
            return true;

        case OBJECT_RUINfactory:
        case OBJECT_RUINconvert:
        case OBJECT_RUINbase:
            return false;

        case OBJECT_APOLLO4:
            return true;

        case OBJECT_APOLLO1:
        case OBJECT_APOLLO3:
        case OBJECT_APOLLO5:
            return false;

        default:
            return false;
    }
}

bool CHardcodeCollection::IsCreationFixedPosition(ObjectType type)
{
    return type == OBJECT_SHOW;
}



//////////////////////////////////////////////////////////////////////////////
// Common interface details
//////////////////////////////////////////////////////////////////////////////

DriveType CHardcodeCollection::GetDriveType(ObjectType type)
{
    switch(type)
    {
        case OBJECT_MOBILEwt:
        case OBJECT_MOBILEwa:
        case OBJECT_MOBILEwc:
        case OBJECT_MOBILEwi:
        case OBJECT_MOBILEws:
        case OBJECT_MOBILEwb:
            return DriveType::Wheeled;

        case OBJECT_MOBILEtt:
        case OBJECT_MOBILEta:
        case OBJECT_MOBILEtc:
        case OBJECT_MOBILEti:
        case OBJECT_MOBILEts:
        case OBJECT_MOBILEtb:
            return DriveType::Tracked;

        case OBJECT_MOBILEft:
        case OBJECT_MOBILEfa:
        case OBJECT_MOBILEfc:
        case OBJECT_MOBILEfi:
        case OBJECT_MOBILEfs:
        case OBJECT_MOBILEfb:
            return DriveType::Winged;

        case OBJECT_MOBILEit:
        case OBJECT_MOBILEia:
        case OBJECT_MOBILEic:
        case OBJECT_MOBILEii:
        case OBJECT_MOBILEis:
        case OBJECT_MOBILEib:
            return DriveType::Legged;

        case OBJECT_MOBILErp:
        case OBJECT_MOBILErt:
        case OBJECT_MOBILErc:
        case OBJECT_MOBILErr:
        case OBJECT_MOBILErs:
            return DriveType::Heavy;

        case OBJECT_MOBILEst:
        case OBJECT_MOBILEsa:
           return DriveType::Amphibious;

        default:
            return DriveType::Other;
    }
}

ToolType CHardcodeCollection::GetToolType(ObjectType type)
{
    switch (type)
    {
        case OBJECT_MOBILEwa:
        case OBJECT_MOBILEta:
        case OBJECT_MOBILEfa:
        case OBJECT_MOBILEia:
            return ToolType::Grabber;

        case OBJECT_MOBILEws:
        case OBJECT_MOBILEts:
        case OBJECT_MOBILEfs:
        case OBJECT_MOBILEis:
            return ToolType::Sniffer;

        case OBJECT_MOBILEwc:
        case OBJECT_MOBILEtc:
        case OBJECT_MOBILEfc:
        case OBJECT_MOBILEic:
            return ToolType::Shooter;

        case OBJECT_MOBILEwi:
        case OBJECT_MOBILEti:
        case OBJECT_MOBILEfi:
        case OBJECT_MOBILEii:
            return ToolType::OrganicShooter;

        case OBJECT_MOBILEwb:
        case OBJECT_MOBILEtb:
        case OBJECT_MOBILEfb:
        case OBJECT_MOBILEib:
            return ToolType::Builder;

        default:
            return ToolType::Other;
    }
}

bool CHardcodeCollection::IsTransportable(ObjectType type)
{
    // TODO: Hacking in progress...
    if ( type == OBJECT_STONE   ||
         type == OBJECT_URANIUM ||
         type == OBJECT_BULLET  ||
         type == OBJECT_METAL   ||
         type == OBJECT_POWER   ||
         type == OBJECT_ATOMIC  ||
         type == OBJECT_BBOX    ||
         type == OBJECT_KEYa    ||
         type == OBJECT_KEYb    ||
         type == OBJECT_KEYc    ||
         type == OBJECT_KEYd    ||
         type == OBJECT_TNT     ) return true;
    return false;
}

bool CHardcodeCollection::IsDropZoneShownOnPut(ObjectType type)
{
    return type == OBJECT_METAL;
}

CObjectFlagTaskExecutorDetails CHardcodeCollection::GetFlagTaskExecutionDetails(ObjectType type)
{
    switch(type)
    {
        case OBJECT_HUMAN:
        case OBJECT_TECH:
            return {ExecutionAsHuman, 0, Math::Vector(4.0f, 0.0f, 0.0f)};
        case OBJECT_MOBILEws:
        case OBJECT_MOBILEts:
        case OBJECT_MOBILEfs:
        case OBJECT_MOBILEis:
            return {ExecutionAsSniffer, 0, Math::Vector(6.0f, 0.0f, 0.0f)};
        default:
            return {ExecutionNoMotion, 0, Math::Vector(0.0f, 0.0f, 0.0f)};
    }
}

std::vector<CObjectFlagTaskExecutorObject> CHardcodeCollection::GetFlagTaskExecutionObjects(ObjectType type)
{
    std::vector<CObjectFlagTaskExecutorObject> result;

    switch(type)
    {
        case OBJECT_HUMAN:
        case OBJECT_TECH:
        case OBJECT_MOBILEws:
        case OBJECT_MOBILEts:
        case OBJECT_MOBILEfs:
        case OBJECT_MOBILEis:
            return {{OBJECT_FLAGb,5}, {OBJECT_FLAGr,5}, {OBJECT_FLAGg,5}, {OBJECT_FLAGy,5}, {OBJECT_FLAGv,5}};
        default:
            return result;
    }
}

CObjectSniffTaskExecutorDetails CHardcodeCollection::GetSniffTaskExecutionDetails(ObjectType type)
{
    switch(type)
    {
        case OBJECT_MOBILEws:
        case OBJECT_MOBILEts:
        case OBJECT_MOBILEfs:
        case OBJECT_MOBILEis:
            return {ExecutionAsSniffer, 0, Math::Vector(7.5f, 0.0f, 0.0f)};
        default:
            return {ExecutionNoMotion, 0, Math::Vector(0.0f, 0.0f, 0.0f)};
    }
}

std::vector<CObjectSniffTaskExecutorObject> CHardcodeCollection::GetSniffTaskExecutionObjects(ObjectType type)
{
    std::vector<CObjectSniffTaskExecutorObject> result;

    if ( (type == OBJECT_MOBILEfs ||
          type == OBJECT_MOBILEts ||
          type == OBJECT_MOBILEws ||
          type == OBJECT_MOBILEis ) )
    {
        result.push_back({Gfx::TR_POWER,   OBJECT_MARKPOWER,   TR("Found a site for power station")});
        result.push_back({Gfx::TR_STONE,   OBJECT_MARKSTONE,   TR("Found a site for a derrick")});
        result.push_back({Gfx::TR_URANIUM, OBJECT_MARKURANIUM, TR("Found a site for a derrick")});
        result.push_back({Gfx::TR_KEY_A,   OBJECT_MARKKEYa,    TR("Found a site for a derrick")});
        result.push_back({Gfx::TR_KEY_B,   OBJECT_MARKKEYb,    TR("Found a site for a derrick")});
        result.push_back({Gfx::TR_KEY_C,   OBJECT_MARKKEYc,    TR("Found a site for a derrick")});
        result.push_back({Gfx::TR_KEY_D,   OBJECT_MARKKEYd,    TR("Found a site for a derrick")});
    }
          
    return result;
}

bool CHardcodeCollection::IsMovable(ObjectType type)
{
    if ( type == OBJECT_MOTHER ) return true;
    if ( type == OBJECT_ANT ) return true;
    if ( type == OBJECT_SPIDER ) return true;
    if ( type == OBJECT_BEE ) return true;
    if ( type == OBJECT_WORM ) return true;
    if ( type == OBJECT_HUMAN ) return true;
    if ( type == OBJECT_TECH ) return true;
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

bool CHardcodeCollection::IsProgrammable(ObjectType type)
{
    if ( type == OBJECT_MOTHER ) return true;
    if ( type == OBJECT_ANT ) return true;
    if ( type == OBJECT_SPIDER ) return true;
    if ( type == OBJECT_BEE ) return true;
    if ( type == OBJECT_WORM ) return true;
    if ( type == OBJECT_HUMAN ) return true;
    if ( type == OBJECT_TECH ) return true;
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

Motion CHardcodeCollection::GetLinMotion(ObjectType type)
{
    CPhysics physics(nullptr);

    if ( type == OBJECT_MOTHER )
    {
        physics.SetLinMotionX(MO_ADVSPEED,   8.0f);
        physics.SetLinMotionX(MO_RECSPEED,   8.0f);
        physics.SetLinMotionX(MO_ADVACCEL,  10.0f);
        physics.SetLinMotionX(MO_RECACCEL,  10.0f);
        physics.SetLinMotionX(MO_STOACCEL,  40.0f);
        physics.SetLinMotionX(MO_TERSLIDE,   5.0f);
        physics.SetLinMotionZ(MO_TERSLIDE,   5.0f);
        physics.SetLinMotionX(MO_TERFORCE,  30.0f);
        physics.SetLinMotionZ(MO_TERFORCE,  20.0f);
        physics.SetLinMotionZ(MO_MOTACCEL,  40.0f);
    }
    if ( type == OBJECT_ANT )
    {
        physics.SetLinMotionX(MO_ADVSPEED,  12.0f);
        physics.SetLinMotionX(MO_RECSPEED,  12.0f);
        physics.SetLinMotionX(MO_ADVACCEL,  15.0f);
        physics.SetLinMotionX(MO_RECACCEL,  15.0f);
        physics.SetLinMotionX(MO_STOACCEL,  40.0f);
        physics.SetLinMotionX(MO_TERSLIDE,   5.0f);
        physics.SetLinMotionZ(MO_TERSLIDE,   5.0f);
        physics.SetLinMotionX(MO_TERFORCE,   5.0f);
        physics.SetLinMotionZ(MO_TERFORCE,   5.0f);
        physics.SetLinMotionZ(MO_MOTACCEL,  10.0f);
    }
    if ( type == OBJECT_SPIDER )
    {
        physics.SetLinMotionX(MO_ADVSPEED,  12.0f);
        physics.SetLinMotionX(MO_RECSPEED,  12.0f);
        physics.SetLinMotionX(MO_ADVACCEL,  15.0f);
        physics.SetLinMotionX(MO_RECACCEL,  15.0f);
        physics.SetLinMotionX(MO_STOACCEL,  40.0f);
        physics.SetLinMotionX(MO_TERSLIDE,   5.0f);
        physics.SetLinMotionZ(MO_TERSLIDE,   5.0f);
        physics.SetLinMotionX(MO_TERFORCE,   5.0f);
        physics.SetLinMotionZ(MO_TERFORCE,   5.0f);
        physics.SetLinMotionZ(MO_MOTACCEL,  10.0f);
    }
    if ( type == OBJECT_BEE )
    {
        physics.SetLinMotionX(MO_ADVSPEED,  50.0f);
        physics.SetLinMotionX(MO_RECSPEED,  50.0f);
        physics.SetLinMotionX(MO_ADVACCEL,  20.0f);
        physics.SetLinMotionX(MO_RECACCEL,  20.0f);
        physics.SetLinMotionX(MO_STOACCEL,  20.0f);
        physics.SetLinMotionX(MO_TERSLIDE,   5.0f);
        physics.SetLinMotionZ(MO_TERSLIDE,   5.0f);
        physics.SetLinMotionX(MO_TERFORCE,  10.0f);
        physics.SetLinMotionZ(MO_TERFORCE,  10.0f);
        physics.SetLinMotionZ(MO_MOTACCEL,  40.0f);
        physics.SetLinMotionY(MO_ADVSPEED,  60.0f);
        physics.SetLinMotionY(MO_RECSPEED,  60.0f);
        physics.SetLinMotionY(MO_ADVACCEL,  20.0f);
        physics.SetLinMotionY(MO_RECACCEL,  50.0f);
        physics.SetLinMotionY(MO_STOACCEL,  50.0f);
    }
    if ( type == OBJECT_WORM )
    {
        physics.SetLinMotionX(MO_ADVSPEED,   3.0f);
        physics.SetLinMotionX(MO_RECSPEED,   3.0f);
        physics.SetLinMotionX(MO_ADVACCEL,  10.0f);
        physics.SetLinMotionX(MO_RECACCEL,  10.0f);
        physics.SetLinMotionX(MO_STOACCEL,  40.0f);
        physics.SetLinMotionX(MO_TERSLIDE,   5.0f);
        physics.SetLinMotionZ(MO_TERSLIDE,   5.0f);
        physics.SetLinMotionX(MO_TERFORCE,   5.0f);
        physics.SetLinMotionZ(MO_TERFORCE,   5.0f);
        physics.SetLinMotionZ(MO_MOTACCEL,  40.0f);
    }
    if ( type == OBJECT_HUMAN )
    {
        physics.SetLinMotionX(MO_ADVSPEED, 50.0f);
        physics.SetLinMotionX(MO_RECSPEED, 35.0f);
        physics.SetLinMotionX(MO_ADVACCEL, 20.0f);
        physics.SetLinMotionX(MO_RECACCEL, 20.0f);
        physics.SetLinMotionX(MO_STOACCEL, 20.0f);
        physics.SetLinMotionX(MO_TERSLIDE,  5.0f);
        physics.SetLinMotionZ(MO_TERSLIDE,  5.0f);
        physics.SetLinMotionX(MO_TERFORCE, 70.0f);
        physics.SetLinMotionZ(MO_TERFORCE, 40.0f);
        physics.SetLinMotionZ(MO_MOTACCEL, 40.0f);
        physics.SetLinMotionY(MO_ADVSPEED, 60.0f);
        physics.SetLinMotionY(MO_RECSPEED, 60.0f);
        physics.SetLinMotionY(MO_ADVACCEL, 20.0f);
        physics.SetLinMotionY(MO_RECACCEL, 50.0f);
        physics.SetLinMotionY(MO_STOACCEL, 50.0f);
    }
    if ( type == OBJECT_TECH )
    {
        physics.SetLinMotionX(MO_ADVSPEED, 40.0f);
        physics.SetLinMotionX(MO_RECSPEED, 15.0f);
        physics.SetLinMotionX(MO_ADVACCEL,  8.0f);
        physics.SetLinMotionX(MO_RECACCEL,  8.0f);
        physics.SetLinMotionX(MO_STOACCEL,  8.0f);
        physics.SetLinMotionX(MO_TERSLIDE,  5.0f);
        physics.SetLinMotionZ(MO_TERSLIDE,  5.0f);
        physics.SetLinMotionX(MO_TERFORCE, 50.0f);
        physics.SetLinMotionZ(MO_TERFORCE, 50.0f);
        physics.SetLinMotionZ(MO_MOTACCEL, 40.0f);
        physics.SetLinMotionY(MO_ADVSPEED, 60.0f);
        physics.SetLinMotionY(MO_RECSPEED, 60.0f);
        physics.SetLinMotionY(MO_ADVACCEL, 20.0f);
        physics.SetLinMotionY(MO_RECACCEL, 50.0f);
        physics.SetLinMotionY(MO_STOACCEL, 50.0f);
    }
    if ( type == OBJECT_CONTROLLER )
    {
        physics.SetLinMotionX(MO_ADVSPEED, 50.0f);
        physics.SetLinMotionX(MO_RECSPEED, 50.0f);
        physics.SetLinMotionX(MO_ADVACCEL, 20.0f);
        physics.SetLinMotionX(MO_RECACCEL, 20.0f);
        physics.SetLinMotionX(MO_STOACCEL, 20.0f);
        physics.SetLinMotionX(MO_TERSLIDE,  0.0f);
        physics.SetLinMotionZ(MO_TERSLIDE,  0.0f);
        physics.SetLinMotionX(MO_TERFORCE,  0.0f);
        physics.SetLinMotionZ(MO_TERFORCE,  0.0f);
        physics.SetLinMotionZ(MO_MOTACCEL, 40.0f);
        physics.SetLinMotionY(MO_ADVSPEED, 60.0f);
        physics.SetLinMotionY(MO_RECSPEED, 60.0f);
        physics.SetLinMotionY(MO_ADVACCEL, 20.0f);
        physics.SetLinMotionY(MO_RECACCEL, 50.0f);
        physics.SetLinMotionY(MO_STOACCEL, 50.0f);
    }
    if ( type == OBJECT_APOLLO2 )  // jeep?
    {
        physics.SetLinMotionX(MO_ADVSPEED, 15.0f);
        physics.SetLinMotionX(MO_RECSPEED, 10.0f);
        physics.SetLinMotionX(MO_ADVACCEL, 20.0f);
        physics.SetLinMotionX(MO_RECACCEL, 20.0f);
        physics.SetLinMotionX(MO_STOACCEL, 40.0f);
        physics.SetLinMotionX(MO_TERSLIDE,  2.0f);
        physics.SetLinMotionZ(MO_TERSLIDE,  2.0f);
        physics.SetLinMotionX(MO_TERFORCE, 30.0f);
        physics.SetLinMotionZ(MO_TERFORCE, 10.0f);
        physics.SetLinMotionZ(MO_MOTACCEL, 20.0f);
    }
    if ( type == OBJECT_MOBILEdr )
    {
        physics.SetLinMotionX(MO_ADVSPEED, 15.0f);
        physics.SetLinMotionX(MO_RECSPEED, 10.0f);
        physics.SetLinMotionX(MO_ADVACCEL, 20.0f);
        physics.SetLinMotionX(MO_RECACCEL, 10.0f);
        physics.SetLinMotionX(MO_STOACCEL, 40.0f);
        physics.SetLinMotionX(MO_TERSLIDE,  5.0f);
        physics.SetLinMotionZ(MO_TERSLIDE,  5.0f);
        physics.SetLinMotionX(MO_TERFORCE, 20.0f);
        physics.SetLinMotionZ(MO_TERFORCE, 10.0f);
        physics.SetLinMotionZ(MO_MOTACCEL, 40.0f);
    }
    if ( type == OBJECT_MOBILEsa ||
         type == OBJECT_MOBILEst )
    {
        physics.SetLinMotionX(MO_ADVSPEED, 15.0f);
        physics.SetLinMotionX(MO_RECSPEED, 10.0f);
        physics.SetLinMotionX(MO_ADVACCEL, 20.0f);
        physics.SetLinMotionX(MO_RECACCEL, 10.0f);
        physics.SetLinMotionX(MO_STOACCEL, 40.0f);
        physics.SetLinMotionX(MO_TERSLIDE,  5.0f);
        physics.SetLinMotionZ(MO_TERSLIDE,  5.0f);
        physics.SetLinMotionX(MO_TERFORCE, 20.0f);
        physics.SetLinMotionZ(MO_TERFORCE, 10.0f);
        physics.SetLinMotionZ(MO_MOTACCEL, 40.0f);
    }
    if ( type == OBJECT_MOBILErt ||
         type == OBJECT_MOBILErc ||
         type == OBJECT_MOBILErr ||
         type == OBJECT_MOBILErs ||
         type == OBJECT_MOBILErp)  // large caterpillars?
    {
        physics.SetLinMotionX(MO_ADVSPEED, 10.0f);
        physics.SetLinMotionX(MO_RECSPEED,  5.0f);
        physics.SetLinMotionX(MO_ADVACCEL, 10.0f);
        physics.SetLinMotionX(MO_RECACCEL,  5.0f);
        physics.SetLinMotionX(MO_STOACCEL, 40.0f);
        physics.SetLinMotionX(MO_TERSLIDE,  5.0f);
        physics.SetLinMotionZ(MO_TERSLIDE,  5.0f);
        physics.SetLinMotionX(MO_TERFORCE, 20.0f);
        physics.SetLinMotionZ(MO_TERFORCE, 10.0f);
        physics.SetLinMotionZ(MO_MOTACCEL, 40.0f);
    }
    if ( type == OBJECT_MOBILEfa ||
         type == OBJECT_MOBILEfb ||
         type == OBJECT_MOBILEfc ||
         type == OBJECT_MOBILEfi ||
         type == OBJECT_MOBILEfs ||
         type == OBJECT_MOBILEft )  // flying?
    {

        physics.SetLinMotionX(MO_ADVSPEED, 50.0f);
        physics.SetLinMotionX(MO_RECSPEED, 50.0f);
        physics.SetLinMotionX(MO_ADVACCEL, 20.0f);
        physics.SetLinMotionX(MO_RECACCEL, 20.0f);
        physics.SetLinMotionX(MO_STOACCEL, 20.0f);
        physics.SetLinMotionX(MO_TERSLIDE,  5.0f);
        physics.SetLinMotionZ(MO_TERSLIDE,  5.0f);
        physics.SetLinMotionX(MO_TERFORCE, 50.0f);
        physics.SetLinMotionZ(MO_TERFORCE, 50.0f);
        physics.SetLinMotionZ(MO_MOTACCEL, 40.0f);
        physics.SetLinMotionY(MO_ADVSPEED, 60.0f);
        physics.SetLinMotionY(MO_RECSPEED, 60.0f);
        physics.SetLinMotionY(MO_ADVACCEL, 20.0f);
        physics.SetLinMotionY(MO_RECACCEL, 50.0f);
        physics.SetLinMotionY(MO_STOACCEL, 50.0f);
    }
    if ( type == OBJECT_MOBILEia ||
         type == OBJECT_MOBILEib ||
         type == OBJECT_MOBILEic ||
         type == OBJECT_MOBILEii ||
         type == OBJECT_MOBILEis ||
         type == OBJECT_MOBILEit)  // legs?
    {

        physics.SetLinMotionX(MO_ADVSPEED, 15.0f);
        physics.SetLinMotionX(MO_RECSPEED,  8.0f);
        physics.SetLinMotionX(MO_ADVACCEL, 40.0f);
        physics.SetLinMotionX(MO_RECACCEL, 20.0f);
        physics.SetLinMotionX(MO_STOACCEL, 40.0f);
        physics.SetLinMotionX(MO_TERSLIDE,  5.0f);
        physics.SetLinMotionZ(MO_TERSLIDE,  5.0f);
        physics.SetLinMotionX(MO_TERFORCE, 10.0f);
//?     physics.SetLinMotionX(MO_TERFORCE, 15.0f);
        physics.SetLinMotionZ(MO_TERFORCE, 10.0f);
        physics.SetLinMotionZ(MO_MOTACCEL, 40.0f);
    }
    if ( type == OBJECT_MOBILEta ||
         type == OBJECT_MOBILEtb ||
         type == OBJECT_MOBILEtc ||
         type == OBJECT_MOBILEti ||
         type == OBJECT_MOBILEts ||
         type == OBJECT_MOBILEtt )  // caterpillars?
    {

        physics.SetLinMotionX(MO_ADVSPEED, 15.0f);
        physics.SetLinMotionX(MO_RECSPEED,  8.0f);
        physics.SetLinMotionX(MO_ADVACCEL, 15.0f);
        physics.SetLinMotionX(MO_RECACCEL,  8.0f);
        physics.SetLinMotionX(MO_STOACCEL, 40.0f);
        physics.SetLinMotionX(MO_TERSLIDE,  5.0f);
        physics.SetLinMotionZ(MO_TERSLIDE,  5.0f);
        physics.SetLinMotionX(MO_TERFORCE, 20.0f);
        physics.SetLinMotionZ(MO_TERFORCE, 10.0f);
        physics.SetLinMotionZ(MO_MOTACCEL, 40.0f);
    }
    if ( type == OBJECT_MOBILEtg )
    {

        physics.SetLinMotionX(MO_ADVSPEED, 20.0f);
        physics.SetLinMotionX(MO_RECSPEED, 10.0f);
        physics.SetLinMotionX(MO_ADVACCEL, 40.0f);
        physics.SetLinMotionX(MO_RECACCEL, 20.0f);
        physics.SetLinMotionX(MO_STOACCEL, 40.0f);
        physics.SetLinMotionX(MO_TERSLIDE,  5.0f);
        physics.SetLinMotionZ(MO_TERSLIDE,  5.0f);
        physics.SetLinMotionX(MO_TERFORCE, 50.0f);
        physics.SetLinMotionZ(MO_TERFORCE, 20.0f);
        physics.SetLinMotionZ(MO_MOTACCEL, 20.0f);
    }
    if ( type == OBJECT_MOBILEwa ||
         type == OBJECT_MOBILEwb ||
         type == OBJECT_MOBILEwc ||
         type == OBJECT_MOBILEwi ||
         type == OBJECT_MOBILEws ||
         type == OBJECT_MOBILEwt )  // wheels?
    {
        physics.SetLinMotionX(MO_ADVSPEED, 20.0f);
        physics.SetLinMotionX(MO_RECSPEED, 10.0f);
        physics.SetLinMotionX(MO_ADVACCEL, 40.0f);
        physics.SetLinMotionX(MO_RECACCEL, 20.0f);
        physics.SetLinMotionX(MO_STOACCEL, 40.0f);
        physics.SetLinMotionX(MO_TERSLIDE,  5.0f);
        physics.SetLinMotionZ(MO_TERSLIDE,  5.0f);
        physics.SetLinMotionX(MO_TERFORCE, 50.0f);
        physics.SetLinMotionZ(MO_TERFORCE, 30.0f);
        physics.SetLinMotionZ(MO_MOTACCEL, 20.0f);
    }

    Motion result;
    result.advanceAccel = physics.GetLinMotion(MO_ADVACCEL);
    result.recedeAccel  = physics.GetLinMotion(MO_RECACCEL);
    result.stopAccel    = physics.GetLinMotion(MO_STOACCEL);
    result.terrainSpeed = physics.GetLinMotion(MO_TERSPEED);
    result.terrainSlide = physics.GetLinMotion(MO_TERSLIDE);
    result.motorAccel   = physics.GetLinMotion(MO_MOTACCEL);
    result.terrainForce = physics.GetLinMotion(MO_TERFORCE);
    result.advanceSpeed = physics.GetLinMotion(MO_ADVSPEED);
    result.recedeSpeed  = physics.GetLinMotion(MO_RECSPEED);
    result.motorSpeed   = physics.GetLinMotion(MO_MOTSPEED);
    result.currentSpeed = physics.GetLinMotion(MO_CURSPEED);
    result.realSpeed    = physics.GetLinMotion(MO_REASPEED);
    return result;
}

Motion CHardcodeCollection::GetCirMotion(ObjectType type)
{
    CPhysics physics(nullptr);

    if ( type == OBJECT_MOTHER )
    {
        physics.SetCirMotionY(MO_ADVSPEED,   0.1f*Math::PI);
        physics.SetCirMotionY(MO_RECSPEED,   0.1f*Math::PI);
        physics.SetCirMotionY(MO_ADVACCEL,  10.0f);
        physics.SetCirMotionY(MO_RECACCEL,  10.0f);
        physics.SetCirMotionY(MO_STOACCEL,  20.0f);
    }
    if ( type == OBJECT_ANT )
    {
        physics.SetCirMotionY(MO_ADVSPEED,   1.0f*Math::PI);
        physics.SetCirMotionY(MO_RECSPEED,   1.0f*Math::PI);
        physics.SetCirMotionY(MO_ADVACCEL,  20.0f);
        physics.SetCirMotionY(MO_RECACCEL,  20.0f);
        physics.SetCirMotionY(MO_STOACCEL,  40.0f);
    }
    if ( type == OBJECT_SPIDER )
    {    
        physics.SetCirMotionY(MO_ADVSPEED,   1.0f*Math::PI);
        physics.SetCirMotionY(MO_RECSPEED,   1.0f*Math::PI);
        physics.SetCirMotionY(MO_ADVACCEL,  20.0f);
        physics.SetCirMotionY(MO_RECACCEL,  20.0f);
        physics.SetCirMotionY(MO_STOACCEL,  40.0f);

    }
    if ( type == OBJECT_BEE )
    {
        physics.SetCirMotionY(MO_ADVSPEED,   1.0f*Math::PI);
        physics.SetCirMotionY(MO_RECSPEED,   1.0f*Math::PI);
        physics.SetCirMotionY(MO_ADVACCEL,  20.0f);
        physics.SetCirMotionY(MO_RECACCEL,  20.0f);
        physics.SetCirMotionY(MO_STOACCEL,  40.0f);
    }
    if ( type == OBJECT_WORM )
    {
        physics.SetCirMotionY(MO_ADVSPEED,   0.2f*Math::PI);
        physics.SetCirMotionY(MO_RECSPEED,   0.2f*Math::PI);
        physics.SetCirMotionY(MO_ADVACCEL,  10.0f);
        physics.SetCirMotionY(MO_RECACCEL,  10.0f);
        physics.SetCirMotionY(MO_STOACCEL,  20.0f);
    }
    if ( type == OBJECT_HUMAN )
    {
        physics.SetCirMotionY(MO_ADVSPEED,  0.8f*Math::PI);
        physics.SetCirMotionY(MO_RECSPEED,  0.8f*Math::PI);
        physics.SetCirMotionY(MO_ADVACCEL,  6.0f);
        physics.SetCirMotionY(MO_RECACCEL,  6.0f);
        physics.SetCirMotionY(MO_STOACCEL,  4.0f);
    }
    if ( type == OBJECT_TECH )
    {
        physics.SetCirMotionY(MO_ADVSPEED,  0.6f*Math::PI);
        physics.SetCirMotionY(MO_RECSPEED,  0.6f*Math::PI);
        physics.SetCirMotionY(MO_ADVACCEL,  4.0f);
        physics.SetCirMotionY(MO_RECACCEL,  4.0f);
        physics.SetCirMotionY(MO_STOACCEL,  3.0f);
    }
    if ( type == OBJECT_CONTROLLER )
    {
        physics.SetCirMotionY(MO_ADVSPEED,  0.4f*Math::PI);
        physics.SetCirMotionY(MO_RECSPEED,  0.4f*Math::PI);
        physics.SetCirMotionY(MO_ADVACCEL,  2.0f);
        physics.SetCirMotionY(MO_RECACCEL,  2.0f);
        physics.SetCirMotionY(MO_STOACCEL,  2.0f);
    }
    if ( type == OBJECT_APOLLO2 )  // jeep?
    {
        physics.SetCirMotionY(MO_ADVSPEED,  0.4f*Math::PI);
        physics.SetCirMotionY(MO_RECSPEED,  0.4f*Math::PI);
        physics.SetCirMotionY(MO_ADVACCEL,  2.0f);
        physics.SetCirMotionY(MO_RECACCEL,  2.0f);
        physics.SetCirMotionY(MO_STOACCEL,  4.0f);
    }
    if ( type == OBJECT_MOBILEdr )
    {
        physics.SetCirMotionY(MO_ADVSPEED,  0.5f*Math::PI);
        physics.SetCirMotionY(MO_RECSPEED,  0.5f*Math::PI);
        physics.SetCirMotionY(MO_ADVACCEL,  5.0f);
        physics.SetCirMotionY(MO_RECACCEL,  5.0f);
        physics.SetCirMotionY(MO_STOACCEL, 10.0f);
    }
    if ( type == OBJECT_MOBILEsa ||
         type == OBJECT_MOBILEst )
    {
        physics.SetCirMotionY(MO_ADVSPEED,  0.5f*Math::PI);
        physics.SetCirMotionY(MO_RECSPEED,  0.5f*Math::PI);
        physics.SetCirMotionY(MO_ADVACCEL,  5.0f);
        physics.SetCirMotionY(MO_RECACCEL,  5.0f);
        physics.SetCirMotionY(MO_STOACCEL, 10.0f);
    }
    if ( type == OBJECT_MOBILErt ||
         type == OBJECT_MOBILErc ||
         type == OBJECT_MOBILErr ||
         type == OBJECT_MOBILErs ||
         type == OBJECT_MOBILErp)  // large caterpillars?
    {
        physics.SetCirMotionY(MO_ADVSPEED,  0.3f*Math::PI);
        physics.SetCirMotionY(MO_RECSPEED,  0.3f*Math::PI);
        physics.SetCirMotionY(MO_ADVACCEL,  2.0f);
        physics.SetCirMotionY(MO_RECACCEL,  2.0f);
        physics.SetCirMotionY(MO_STOACCEL,  4.0f);
    }
    if ( type == OBJECT_MOBILEfa ||
         type == OBJECT_MOBILEfb ||
         type == OBJECT_MOBILEfc ||
         type == OBJECT_MOBILEfi ||
         type == OBJECT_MOBILEfs ||
         type == OBJECT_MOBILEft )  // flying?
    {

        physics.SetCirMotionY(MO_ADVSPEED,  0.4f*Math::PI);
        physics.SetCirMotionY(MO_RECSPEED,  0.4f*Math::PI);
        physics.SetCirMotionY(MO_ADVACCEL,  2.0f);
        physics.SetCirMotionY(MO_RECACCEL,  2.0f);
        physics.SetCirMotionY(MO_STOACCEL,  2.0f);
    }
    if ( type == OBJECT_MOBILEia ||
         type == OBJECT_MOBILEib ||
         type == OBJECT_MOBILEic ||
         type == OBJECT_MOBILEii ||
         type == OBJECT_MOBILEis ||
         type == OBJECT_MOBILEit)  // legs?
    {

        physics.SetCirMotionY(MO_ADVSPEED,  0.5f*Math::PI);
        physics.SetCirMotionY(MO_RECSPEED,  0.5f*Math::PI);
        physics.SetCirMotionY(MO_ADVACCEL, 10.0f);
        physics.SetCirMotionY(MO_RECACCEL, 10.0f);
        physics.SetCirMotionY(MO_STOACCEL, 15.0f);
    }
    if ( type == OBJECT_MOBILEta ||
         type == OBJECT_MOBILEtb ||
         type == OBJECT_MOBILEtc ||
         type == OBJECT_MOBILEti ||
         type == OBJECT_MOBILEts ||
         type == OBJECT_MOBILEtt )  // caterpillars?
    {

        physics.SetCirMotionY(MO_ADVSPEED,  0.5f*Math::PI);
        physics.SetCirMotionY(MO_RECSPEED,  0.5f*Math::PI);
        physics.SetCirMotionY(MO_ADVACCEL, 10.0f);
        physics.SetCirMotionY(MO_RECACCEL, 10.0f);
        physics.SetCirMotionY(MO_STOACCEL,  6.0f);
    }
    if ( type == OBJECT_MOBILEtg )
    {

        physics.SetCirMotionY(MO_ADVSPEED,  0.8f*Math::PI);
        physics.SetCirMotionY(MO_RECSPEED,  0.8f*Math::PI);
        physics.SetCirMotionY(MO_ADVACCEL, 10.0f);
        physics.SetCirMotionY(MO_RECACCEL, 10.0f);
        physics.SetCirMotionY(MO_STOACCEL, 15.0f);
    }
    if ( type == OBJECT_MOBILEwa ||
         type == OBJECT_MOBILEwb ||
         type == OBJECT_MOBILEwc ||
         type == OBJECT_MOBILEwi ||
         type == OBJECT_MOBILEws ||
         type == OBJECT_MOBILEwt )  // wheels?
    {
        physics.SetCirMotionY(MO_ADVSPEED,  0.8f*Math::PI);
        physics.SetCirMotionY(MO_RECSPEED,  0.8f*Math::PI);
        physics.SetCirMotionY(MO_ADVACCEL,  8.0f);
        physics.SetCirMotionY(MO_RECACCEL,  8.0f);
        physics.SetCirMotionY(MO_STOACCEL, 12.0f);
    }

    Motion result;
    result.advanceAccel = physics.GetCirMotion(MO_ADVACCEL);
    result.recedeAccel  = physics.GetCirMotion(MO_RECACCEL);
    result.stopAccel    = physics.GetCirMotion(MO_STOACCEL);
    result.terrainSpeed = physics.GetCirMotion(MO_TERSPEED);
    result.terrainSlide = physics.GetCirMotion(MO_TERSLIDE);
    result.motorAccel   = physics.GetCirMotion(MO_MOTACCEL);
    result.terrainForce = physics.GetCirMotion(MO_TERFORCE);
    result.advanceSpeed = physics.GetCirMotion(MO_ADVSPEED);
    result.recedeSpeed  = physics.GetCirMotion(MO_RECSPEED);
    result.motorSpeed   = physics.GetCirMotion(MO_MOTSPEED);
    result.currentSpeed = physics.GetCirMotion(MO_CURSPEED);
    result.realSpeed    = physics.GetCirMotion(MO_REASPEED);
    return result;
}

Character CHardcodeCollection::GetWheels(ObjectType type)
{
    Character character;
    if ( type == OBJECT_MOTHER )
    {
        character.wheelFront = 10.0f;
        character.wheelBack  = 10.0f;
        character.wheelLeft  = 20.0f;
        character.wheelRight = 20.0f;
        character.height     =  3.0f;
    }
    if ( type == OBJECT_ANT )
    {
        character.wheelFront = 3.0f;
        character.wheelBack  = 3.0f;
        character.wheelLeft  = 5.0f;
        character.wheelRight = 5.0f;
        character.height     = 1.2f;
    }
    if ( type == OBJECT_SPIDER )
    {    
        character.wheelFront = 4.0f;
        character.wheelBack  = 4.0f;
        character.wheelLeft  = 6.0f;
        character.wheelRight = 6.0f;
        character.height     = 0.6f;
    }
    if ( type == OBJECT_BEE )
    {
        character.wheelFront = 3.0f;
        character.wheelBack  = 3.0f;
        character.wheelLeft  = 5.0f;
        character.wheelRight = 5.0f;
        character.height     = 2.5f;
    }
    if ( type == OBJECT_WORM )
    {
        character.wheelFront = 10.0f;
        character.wheelBack  = 10.0f;
        character.wheelLeft  =  2.0f;
        character.wheelRight =  2.0f;
        character.height     = -0.2f;
    }
    if ( type == OBJECT_HUMAN )
    {
        character.wheelFront = 4.0f;
        character.wheelBack  = 4.0f;
        character.wheelLeft  = 4.0f;
        character.wheelRight = 4.0f;
        character.height     = 3.5f;
    }
    if ( type == OBJECT_TECH )
    {
        character.wheelFront = 4.0f;
        character.wheelBack  = 4.0f;
        character.wheelLeft  = 4.0f;
        character.wheelRight = 4.0f;
        character.height     = 3.5f;
    }
    if ( type == OBJECT_CONTROLLER )
    {
        // default
    }
    if ( type == OBJECT_APOLLO2 )  // jeep?
    {
        character.wheelFront = 6.0f;
        character.wheelBack  = 6.0f;
        character.wheelLeft  = 5.0f;
        character.wheelRight = 5.0f;
    }
    if ( type == OBJECT_MOBILEdr )
    {
        character.wheelFront = 4.0f;
        character.wheelBack  = 4.0f;
        character.wheelLeft  = 4.0f;
        character.wheelRight = 4.0f;
    }
    if ( type == OBJECT_MOBILEsa ||
         type == OBJECT_MOBILEst )
    {
        character.wheelFront = 4.0f;
        character.wheelBack  = 4.0f;
        character.wheelLeft  = 4.0f;
        character.wheelRight = 4.0f;
    }
    if ( type == OBJECT_MOBILErt ||
         type == OBJECT_MOBILErc ||
         type == OBJECT_MOBILErr ||
         type == OBJECT_MOBILErs ||
         type == OBJECT_MOBILErp)  // large caterpillars?
    {
        character.wheelFront = 5.0f;
        character.wheelBack  = 5.0f;
        character.wheelLeft  = 6.0f;
        character.wheelRight = 6.0f;
    }
    if ( type == OBJECT_MOBILEfa ||
         type == OBJECT_MOBILEfb ||
         type == OBJECT_MOBILEfc ||
         type == OBJECT_MOBILEfi ||
         type == OBJECT_MOBILEfs ||
         type == OBJECT_MOBILEft )  // flying?
    {
        character.wheelFront = 5.0f;
        character.wheelBack  = 4.0f;
        character.wheelLeft  = 4.5f;
        character.wheelRight = 4.5f;
    }
    if ( type == OBJECT_MOBILEia ||
         type == OBJECT_MOBILEib ||
         type == OBJECT_MOBILEic ||
         type == OBJECT_MOBILEii ||
         type == OBJECT_MOBILEis ||
         type == OBJECT_MOBILEit)  // legs?
    {
        character.wheelFront = 4.0f;
        character.wheelBack  = 4.0f;
        character.wheelLeft  = 5.0f;
        character.wheelRight = 5.0f;
    }
    if ( type == OBJECT_MOBILEta ||
         type == OBJECT_MOBILEtb ||
         type == OBJECT_MOBILEtc ||
         type == OBJECT_MOBILEti ||
         type == OBJECT_MOBILEts ||
         type == OBJECT_MOBILEtt )  // caterpillars?
    {
        character.wheelFront = 4.0f;
        character.wheelBack  = 4.0f;
        character.wheelLeft  = 4.8f;
        character.wheelRight = 4.8f;
    }
    if ( type == OBJECT_MOBILEtg )
    {
        character.wheelFront = 4.0f;
        character.wheelBack  = 3.0f;
        character.wheelLeft  = 4.0f;
        character.wheelRight = 4.0f;
    }
    if ( type == OBJECT_MOBILEwa ||
         type == OBJECT_MOBILEwb ||
         type == OBJECT_MOBILEwc ||
         type == OBJECT_MOBILEwi ||
         type == OBJECT_MOBILEws ||
         type == OBJECT_MOBILEwt )  // wheels?
    {
        character.wheelFront = 3.0f;
        character.wheelBack  = 4.0f;
        character.wheelLeft  = 4.0f;
        character.wheelRight = 4.0f;
    }

    return character;
}

bool CHardcodeCollection::IsFlying(ObjectType type)
{
    // TODO: Temporary hack
    if ( type == OBJECT_MOBILEfa || // WingedGrabber
         type == OBJECT_MOBILEfb || // WingedBuilder
         type == OBJECT_MOBILEfs || // WingedSniffer
         type == OBJECT_MOBILEfc || // WingedShooter
         type == OBJECT_MOBILEfi || // WingedOrgaShooter
         type == OBJECT_MOBILEft || // WingedTrainer
         type == OBJECT_HUMAN    || // Me
         type == OBJECT_TECH     || // Tech
         type == OBJECT_BEE      ||
         type == OBJECT_CONTROLLER) return true;
    return false;
}

bool CHardcodeCollection::IsJetFlying(ObjectType type)
{
    // TODO: Temporary hack
    if ( type == OBJECT_MOBILEfa || // WingedGrabber
         type == OBJECT_MOBILEfb || // WingedBuilder
         type == OBJECT_MOBILEfs || // WingedSniffer
         type == OBJECT_MOBILEfc || // WingedShooter
         type == OBJECT_MOBILEfi || // WingedOrgaShooter
         type == OBJECT_MOBILEft || // WingedTrainer
         type == OBJECT_HUMAN    || // Me
         type == OBJECT_TECH     || // Tech
         type == OBJECT_CONTROLLER) return true;
    return false;
}

bool CHardcodeCollection::IsSelectableByDefault(ObjectType type)
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


bool CHardcodeCollection::IsControllable(ObjectType type)
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

bool CHardcodeCollection::IsPowerContainer(ObjectType type)
{
    // TODO: Another one? :/
    if ( type == OBJECT_POWER   || // PowerCell
         type == OBJECT_ATOMIC  || // NuclearCell
         type == OBJECT_STATION || // PowerStation
         type == OBJECT_ENERGY   ) // PowerPlant
             return true;
    return false;
}

bool CHardcodeCollection::IsTaskExecutor(ObjectType type)
{
    return true; // huh!!!
}

bool CHardcodeCollection::IsTraceDrawing(ObjectType type)
{
    return true; // huh!!!
}

bool CHardcodeCollection::IsRanged(ObjectType type)
{
    return true; // huh
}

float CHardcodeCollection::GetRangedRadius(ObjectType type)
{
    if ( type == OBJECT_BASE     ) return 200.0f; // SpaceShip
    if ( type == OBJECT_MOBILErt ) return 400.0f; // Thumper
    if ( type == OBJECT_TOWER    ) return Gfx::LTNG_PROTECTION_RADIUS; // DefenseTower
    if ( type == OBJECT_PARA     ) return Gfx::LTNG_PROTECTION_RADIUS; // PowerCaptor
    return 0.0f;
}

bool CHardcodeCollection::IsDamageable(ObjectType type)
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
        return true;
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

bool CHardcodeCollection::IsDestroyable(ObjectType type)
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

bool CHardcodeCollection::IsFragile(ObjectType type)
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
        return false;
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

bool CHardcodeCollection::IsFragileBurnable(ObjectType type)
{
    if ( type == OBJECT_ANT    ||
         type == OBJECT_WORM   ||
         type == OBJECT_SPIDER ||
         type == OBJECT_BEE     ) return true;

    return false;
}

bool CHardcodeCollection::IsShielded(ObjectType type)
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
        return false;
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
        return false;
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
        return false;
    }

    return false;
}

bool CHardcodeCollection::IsImmuneToFireballs(ObjectType type)
{
    if (type == OBJECT_MOTHER)  return true;
    return false;
}

bool CHardcodeCollection::IsImmuneToInsects(ObjectType type)
{
    return ( type == OBJECT_ANT      ||
             type == OBJECT_SPIDER   ||
             type == OBJECT_BEE      ||
             type == OBJECT_WORM     ||
             type == OBJECT_MOTHER   ||
             type == OBJECT_NEST     ||
             type == OBJECT_BULLET   ||
             type == OBJECT_EGG      ||
             type == OBJECT_TEEN28   ||
             type == OBJECT_TEEN31   );
}

bool CHardcodeCollection::IsImmuneToSpiders(ObjectType type)
{
    return ( type == OBJECT_ANT      ||
             type == OBJECT_SPIDER   ||
             type == OBJECT_BEE      ||
             type == OBJECT_WORM     ||
             type == OBJECT_MOTHER   ||
             type == OBJECT_NEST     ||
             type == OBJECT_BULLET   ||
             type == OBJECT_EGG      ||
             type == OBJECT_TEEN28   ||
             type == OBJECT_TEEN31   );
}

bool CHardcodeCollection::IsImmuneToOrgaballs(ObjectType type)
{
    if (type == OBJECT_MOTHER)  return true;
    return false;
}

bool CHardcodeCollection::IsImmuneToPhazers(ObjectType type)
{
    return false;
}

bool CHardcodeCollection::IsImmuneToTowerRays(ObjectType type)
{
    if (type == OBJECT_MOBILEtg ||
     type == OBJECT_TEEN28   ||
     type == OBJECT_TEEN31   ||
     type == OBJECT_ANT      ||
     type == OBJECT_SPIDER   ||
     type == OBJECT_BEE      ||
     type == OBJECT_WORM     ||
     type == OBJECT_MOTHER   ||
     type == OBJECT_NEST) return false;

     return true;
}

bool CHardcodeCollection::IsShieldAutoregen(ObjectType type)
{
    return type == OBJECT_HUMAN;
}

float CHardcodeCollection::GetShieldAutoregenTime(ObjectType type)
{
    return type == OBJECT_HUMAN ? 120.0f : 0.0f;
}

bool CHardcodeCollection::IsSloted(ObjectType type)
{
    return HasCargoSlot(type) || HasPowerSlot(type) || HasOtherSlot(type);
}

bool CHardcodeCollection::HasCargoSlot(ObjectType type)
{
    if ( type == OBJECT_HUMAN ||
         type == OBJECT_TECH ||
         type == OBJECT_MOBILEfa || // Grabbers
         type == OBJECT_MOBILEta ||
         type == OBJECT_MOBILEwa ||
         type == OBJECT_MOBILEia ||
         type == OBJECT_MOBILEsa) // subber
         return true;

    // DEV BRACH MISSED THIS
    if ( type == OBJECT_BEE ) return true;

    return false;
}

bool CHardcodeCollection::HasPowerSlot(ObjectType type)
{
    // TODO: Another temporary hack
    if (type == OBJECT_MOBILEfa ||
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
        type == OBJECT_TOWER    ||
        type == OBJECT_RESEARCH ) return true;

    return false;
}

int CHardcodeCollection::GetCargoSlotPartNumber(ObjectType type)
{
    switch (type)
    {
        case OBJECT_HUMAN:
        case OBJECT_TECH:
            return 4;
        case OBJECT_BEE:
            return 3;
        case OBJECT_MOBILEsa: // subber
            return 2;
        case OBJECT_MOBILEfa: // Grabbers
        case OBJECT_MOBILEta:
        case OBJECT_MOBILEwa:
        case OBJECT_MOBILEia:
            return 3;
        default:
            return 0;
    }
}

Math::Vector CHardcodeCollection::GetCargoSlotPosition(ObjectType type)
{
    switch (type)
    {
        case OBJECT_HUMAN:
        case OBJECT_TECH:
            return Math::Vector(1.7f, -0.5f, 1.1f);
        case OBJECT_BEE:
            return Math::Vector(4.7f, 0.0f, 0.0f);
        case OBJECT_MOBILEsa: // subber
            return Math::Vector(1.1f, -1.0f, 1.0f);
        case OBJECT_MOBILEfa: // Grabbers
        case OBJECT_MOBILEta:
        case OBJECT_MOBILEwa:
        case OBJECT_MOBILEia:
            return Math::Vector(4.7f, 0.0f, 0.0f);
        default:
            return Math::Vector();
    }
}

Math::Vector CHardcodeCollection::GetPowerSlotPosition(ObjectType type)
{
    if ( type == OBJECT_MOBILEwa ||
         type == OBJECT_MOBILEwb ||
         type == OBJECT_MOBILEwc ||
         type == OBJECT_MOBILEwi ||
         type == OBJECT_MOBILEws ||
         type == OBJECT_MOBILEwt )  // wheels?
    {
        return (Math::Vector(-3.2f, 3.0f, 0.0f));
    }
    if ( type == OBJECT_MOBILEtg )
    {
        return (Math::Vector(-3.2f, 3.0f, 0.0f));
    }
    if ( type == OBJECT_MOBILEta ||
         type == OBJECT_MOBILEtb ||
         type == OBJECT_MOBILEtc ||
         type == OBJECT_MOBILEti ||
         type == OBJECT_MOBILEts ||
         type == OBJECT_MOBILEtt )  // caterpillars?
    {
        return (Math::Vector(-3.2f, 3.0f, 0.0f));
    }
    if ( type == OBJECT_MOBILEia ||
         type == OBJECT_MOBILEib ||
         type == OBJECT_MOBILEic ||
         type == OBJECT_MOBILEii ||
         type == OBJECT_MOBILEis ||
         type == OBJECT_MOBILEit)  // legs?
    {
        return (Math::Vector(-3.2f, 3.0f, 0.0f));
    }
    if ( type == OBJECT_MOBILEfa ||
         type == OBJECT_MOBILEfb ||
         type == OBJECT_MOBILEfc ||
         type == OBJECT_MOBILEfi ||
         type == OBJECT_MOBILEfs ||
         type == OBJECT_MOBILEft )  // flying?
    {
        return (Math::Vector(-3.2f, 3.0f, 0.0f));
    }
    if ( type == OBJECT_MOBILErt ||
         type == OBJECT_MOBILErc ||
         type == OBJECT_MOBILErr ||
         type == OBJECT_MOBILErs ||
         type == OBJECT_MOBILErp)  // large caterpillars?
    {
        return (Math::Vector(-5.8f, 4.0f, 0.0f));
    }
    if ( type == OBJECT_MOBILEsa ||
         type == OBJECT_MOBILEst )
    {
        return (Math::Vector(-5.0f, 3.0f, 0.0f));
    }

    if ( type == OBJECT_MOBILEdr )
    {
        return (Math::Vector(-5.0f, 3.0f, 0.0f));
    }

    if ( type == OBJECT_RESEARCH )
    {
        return (Math::Vector(7.5f, 3.0f, 0.0f));
    }
    if ( type == OBJECT_TOWER )
    {
        return (Math::Vector(5.0f, 3.0f, 0.0f));
    }
    return Math::Vector();
}

bool CHardcodeCollection::HasOtherSlot(ObjectType type)
{
    if (type == OBJECT_ENERGY   ||
        type == OBJECT_LABO     ||
        type == OBJECT_NUCLEAR  ) return true;
    return false;
}

Math::Vector CHardcodeCollection::GetOtherSlotPosition(ObjectType type)
{
    if ( type == OBJECT_ENERGY )
    {
        return (Math::Vector(0.0f, 3.0f, 0.0f));
    }
    if ( type == OBJECT_LABO )
    {
        return (Math::Vector(0.0f, 3.0f, 0.0f));
    }
    if ( type == OBJECT_NUCLEAR )
    {
        return (Math::Vector(22.0f, 3.0f, 0.0f));
    }
    return Math::Vector();
}

bool CHardcodeCollection::IsThumpable(ObjectType type)
{
    if (type == OBJECT_ANT) return true;
    if (type == OBJECT_SPIDER) return true;
    
    return false;
}

bool CHardcodeCollection::IsSquashedByHeavy(ObjectType type)
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

bool CHardcodeCollection::IsDestructionRemoveBuildingLevel(ObjectType type)
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

Gfx::PyroType CHardcodeCollection::GetDestructionByExplosion(ObjectType type)
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

Gfx::PyroType CHardcodeCollection::GetDestructionByWater(ObjectType type)
{
    return Gfx::PT_FRAGW;
}

Gfx::PyroType CHardcodeCollection::GetDestructionByBurning(ObjectType type)
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

Gfx::PyroType CHardcodeCollection::GetDestructionByDrowned(ObjectType type)
{
    return Gfx::PT_DEADW;
}

Gfx::PyroType CHardcodeCollection::GetDestructionByWin(ObjectType type)
{
    return Gfx::PT_WPCHECK;
}

Gfx::PyroType CHardcodeCollection::GetDestructionBySquash(ObjectType type)
{
    return Gfx::PT_SQUASH;
}

bool CHardcodeCollection::IsDestructionKilledByBurning(ObjectType type)
{
    return type != OBJECT_HUMAN;
}

std::vector<CPyroBurnPartDetails> CHardcodeCollection::GetBurnParts(ObjectType type)
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
        Math::Vector pos(0.0f, -4.0f, 0.0f);
        Math::Vector posR(0.0f, -4.0f, 0.0f);
        Math::Vector angle(-0.2f, 0.0f, -0.2f);
        Math::Vector angleR(0.4f, 0.0f, 0.4f);
        result.push_back({0, pos, posR, angle, angleR});  // movement of the main part
    }
    else if ( type == OBJECT_STATION ||
              type == OBJECT_RADAR   ||
              type == OBJECT_INFO    )
    {
        Math::Vector pos(0.0f, -1.0f, 0.0f);
        Math::Vector posR(0.0f, -1.0f, 0.0f);
        Math::Vector angle(-0.1f, 0.0f, -0.1f);
        Math::Vector angleR(0.2f, 0.0f, 0.2f);
        result.push_back({0, pos, posR, angle, angleR});  // movement of the main part
    }
    else if ( type == OBJECT_NUCLEAR )
    {
        Math::Vector pos(0.0f, -10.0f, 0.0f);
        Math::Vector posR(0.0f, -10.0f, 0.0f);
        Math::Vector angle(-0.2f, 0.0f, -0.2f);
        Math::Vector angleR(0.4f, 0.0f, 0.4f);
        result.push_back({0, pos, posR, angle, angleR});  // movement of the main part
    }
    else if ( type == OBJECT_PARA )
    {
        Math::Vector pos(0.0f, -10.0f, 0.0f);
        Math::Vector posR(0.0f, -10.0f, 0.0f);
        Math::Vector angle(-0.2f, 0.0f, -0.2f);
        Math::Vector angleR(0.4f, 0.0f, 0.4f);
        result.push_back({0, pos, posR, angle, angleR});  // movement of the main part
    }
    else if ( type == OBJECT_SAFE )
    {
        Math::Vector pos(0.0f, -10.0f, 0.0f);
        Math::Vector posR(0.0f, -10.0f, 0.0f);
        Math::Vector angle(-0.2f, 0.0f, -0.2f);
        Math::Vector angleR(0.4f, 0.0f, 0.4f);
        result.push_back({0, pos, posR, angle, angleR});  // movement of the main part
    }
    else if ( type == OBJECT_HUSTON )
    {
        Math::Vector pos(0.0f, -10.0f, 0.0f);
        Math::Vector posR(0.0f, -10.0f, 0.0f);
        Math::Vector angle(-0.2f, 0.0f, -0.2f);
        Math::Vector angleR(0.4f, 0.0f, 0.4f);
        result.push_back({0, pos, posR, angle, angleR});  // movement of the main part
    }
    else if ( type == OBJECT_MOBILEwa ||
              type == OBJECT_MOBILEwb ||
              type == OBJECT_MOBILEwc ||
              type == OBJECT_MOBILEwi ||
              type == OBJECT_MOBILEws ||
              type == OBJECT_MOBILEwt )
    {
        Math::Vector pos(0.0f, -0.5f, 0.0f);
        Math::Vector posR(0.0f, -1.0f, 0.0f);
        Math::Vector angle(-0.4f, 0.0f, -0.2f);
        Math::Vector angleR(0.8f, 0.0f, 0.4f);
        result.push_back({0, pos, posR, angle, angleR});  // movement of the main part
    }
    else if ( type == OBJECT_TEEN31 )  // basket?
    {
        Math::Vector pos(0.0f, 0.0f, 0.0f);
        Math::Vector posR(0.0f, 0.0f, 0.0f);
        Math::Vector angle(-0.4f, 0.0f, -0.1f);
        Math::Vector angleR(0.8f, 0.0f, 0.2f);
        result.push_back({0, pos, posR, angle, angleR});  // movement of the main part
    }
    else
    {
        Math::Vector pos(0.0f, -2.0f, 0.0f);
        Math::Vector posR(0.0f, -2.0f, 0.0f);
        Math::Vector angle(-0.4f, 0.0f, -0.4f);
        Math::Vector angleR(0.8f, 0.0f, 0.8f);
        result.push_back({0, pos, posR, angle, angleR});  // movement of the main part
    }

    if ( type == OBJECT_DERRICK )
    {
        Math::Vector pos(0.0f, -40.0f, 0.0f);
        Math::Vector posR(0.0f, 0.0f, 0.0f);
        Math::Vector angle(0.0f, 0.0f, 0.0f);
        Math::Vector angleR(0.0f, 0.0f, 0.0f);
        result.push_back({1, pos, posR, angle, angleR});  // down the drill
    }
    if ( type == OBJECT_REPAIR )
    {
        Math::Vector pos(0.0f, -12.0f, 0.0f);
        Math::Vector posR(0.0f, 0.0f, 0.0f);
        Math::Vector angle(-0.1f, -0.1f, -90.0f*Math::PI/180.0f);
        Math::Vector angleR(0.2f, 0.2f, 0.0f);
        result.push_back({1, pos, posR, angle, angleR});  // down the sensor
    }
    if ( type == OBJECT_DESTROYER )
    {
        Math::Vector pos(0.0f, -12.0f, 0.0f);
        Math::Vector posR(0.0f, 0.0f, 0.0f);
        Math::Vector angle(-0.1f, -0.1f, -90.0f*Math::PI/180.0f);
        Math::Vector angleR(0.2f, 0.2f, 0.0f);
        result.push_back({1, pos, posR, angle, angleR});  // down the sensor
    }
    if ( type == OBJECT_CONVERT )
    {
        Math::Vector pos(0.0f, -200.0f, 0.0f);
        Math::Vector posR(0.0f, 0.0f, 0.0f);
        Math::Vector angle(-0.25f, -0.25f, 0.0f);
        Math::Vector angleR(0.5f, 0.5f, 0.0f);
        result.push_back({1, pos, posR, angle, angleR});  // down the cover
        result.push_back({2, pos, posR, angle, angleR});
        result.push_back({3, pos, posR, angle, angleR});
    }
    if ( type == OBJECT_TOWER )
    {
        Math::Vector pos(0.0f, -7.0f, 0.0f);
        Math::Vector posR(0.0f, 0.0f, 0.0f);
        Math::Vector angle(-0.2f, -0.2f, 0.0f);
        Math::Vector angleR(0.4f, 0.4f, 0.0f);
        result.push_back({1, pos, posR, angle, angleR});  // down the cannon
    }
    if ( type == OBJECT_RESEARCH )
    {
        Math::Vector pos(0.0f, -7.0f, 0.0f);
        Math::Vector posR(0.0f, 0.0f, 0.0f);
        Math::Vector angle(-0.1f, -0.1f, 0.0f);
        Math::Vector angleR(0.2f, 0.2f, 0.0f);
        result.push_back({1, pos, posR, angle, angleR});  // down the anemometer
    }
    if ( type == OBJECT_RADAR )
    {
        Math::Vector pos(0.0f, -14.0f, 0.0f);
        Math::Vector posR(0.0f, 0.0f, 0.0f);
        Math::Vector angle(-0.2f, -0.2f, 0.0f);
        Math::Vector angleR(0.4f, 0.4f, 0.0f);
        result.push_back({1, pos, posR, angle, angleR});  // down the radar
        result.push_back({2, pos, posR, angle, angleR});
    }
    if ( type == OBJECT_INFO )
    {
        Math::Vector pos(0.0f, -14.0f, 0.0f);
        Math::Vector posR(0.0f, 0.0f, 0.0f);
        Math::Vector angle(-0.2f, -0.2f, 0.0f);
        Math::Vector angleR(0.4f, 0.4f, 0.0f);
        result.push_back({1, pos, posR, angle, angleR});  // down the information terminal
        result.push_back({2, pos, posR, angle, angleR});
    }
    if ( type == OBJECT_LABO )
    {
        Math::Vector pos(0.0f, -12.0f, 0.0f);
        Math::Vector posR(0.0f, 0.0f, 0.0f);
        Math::Vector angle(0.0f, 0.0f, 0.0f);
        Math::Vector angleR(0.0f, 0.0f, 0.0f);
        result.push_back({1, pos, posR, angle, angleR});  // down the arm
    }
    if ( type == OBJECT_NUCLEAR )
    {
        Math::Vector pos(0.0f, 0.0f, 0.0f);
        Math::Vector posR(0.0f, 0.0f, 0.0f);
        Math::Vector angle(0.0f, 0.0f, -135.0f*Math::PI/180.0f);
        Math::Vector angleR(0.0f, 0.0f, 0.0f);
        result.push_back({1, pos, posR, angle, angleR});  // down the cover
    }
    if ( type == OBJECT_MOBILEfa ||
         type == OBJECT_MOBILEta ||
         type == OBJECT_MOBILEwa ||
         type == OBJECT_MOBILEia )
    {
        Math::Vector pos(2.0f, -5.0f, 0.0f);
        Math::Vector posR(0.0f, 0.0f, 0.0f);
        Math::Vector angle(-0.1f, -0.1f, 40.0f*Math::PI/180.0f);
        Math::Vector angleR(0.2f, 0.2f, 0.0f);
        result.push_back({1, pos, posR, angle, angleR});  // down the arm
    }
    if ( type == OBJECT_MOBILEfs ||
         type == OBJECT_MOBILEts ||
         type == OBJECT_MOBILEws ||
         type == OBJECT_MOBILEis )
    {
        Math::Vector pos(0.0f, -7.0f, 0.0f);
        Math::Vector posR(0.0f, 0.0f, 0.0f);
        Math::Vector angle(-0.1f, -0.1f, 50.0f*Math::PI/180.0f);
        Math::Vector angleR(0.2f, 0.2f, 0.0f);
        result.push_back({1, pos, posR, angle, angleR});  // down the sensor
    }
    if ( type == OBJECT_MOBILEfc ||
         type == OBJECT_MOBILEtc ||
         type == OBJECT_MOBILEwc ||
         type == OBJECT_MOBILEic )
    {
        Math::Vector pos(-1.5f, -5.0f, 0.0f);
        Math::Vector posR(0.0f, 0.0f, 0.0f);
        Math::Vector angle(-0.1f, -0.1f, -25.0f*Math::PI/180.0f);
        Math::Vector angleR(0.2f, 0.2f, 0.0f);
        result.push_back({1, pos, posR, angle, angleR});  // down the cannon
    }
    if ( type == OBJECT_MOBILEfi ||
         type == OBJECT_MOBILEti ||
         type == OBJECT_MOBILEwi ||
         type == OBJECT_MOBILEii )
    {
        Math::Vector pos(-1.5f, -5.0f, 0.0f);
        Math::Vector posR(0.0f, 0.0f, 0.0f);
        Math::Vector angle(-0.1f, -0.1f, -25.0f*Math::PI/180.0f);
        Math::Vector angleR(0.2f, 0.2f, 0.0f);
        result.push_back({1, pos, posR, angle, angleR});  // down the insect-cannon
    }
    if ( type == OBJECT_MOBILEfb ||
         type == OBJECT_MOBILEtb ||
         type == OBJECT_MOBILEwb ||
         type == OBJECT_MOBILEib )
    {
        Math::Vector pos(-1.5f, -5.0f, 0.0f);
        Math::Vector posR(0.0f, 0.0f, 0.0f);
        Math::Vector angle(-0.1f, -0.1f, -25.0f*Math::PI/180.0f);
        Math::Vector angleR(0.2f, 0.2f, 0.0f);
        result.push_back({1, pos, posR, angle, angleR});  // down the neutron gun
    }
    if ( type == OBJECT_MOBILErt ||
         type == OBJECT_MOBILErc )
    {
        {
            Math::Vector pos(0.0f, -10.0f, 0.0f);
            Math::Vector posR(0.0f, 0.0f, 0.0f);
            Math::Vector angle(0.0f, 0.0f, 0.0f);
            Math::Vector angleR(0.0f, 0.0f, 0.0f);
            result.push_back({1, pos, posR, angle, angleR});  // down the holder
        }
        {
            Math::Vector pos(0.0f, -10.0f, 0.0f);
            Math::Vector posR(0.0f, 0.0f, 0.0f);
            Math::Vector angle(0.0f, 0.0f, 0.0f);
            Math::Vector angleR(0.0f, 0.0f, 0.0f);
            result.push_back({2, pos, posR, angle, angleR});  // down the pestle/cannon
        }
    }
    if ( type == OBJECT_MOBILErr )
    {
        {
            Math::Vector pos(0.0f, -10.0f, 0.0f);
            Math::Vector posR(0.0f, 0.0f, 0.0f);
            Math::Vector angle(0.0f, 0.0f, 0.0f);
            Math::Vector angleR(0.0f, 0.0f, 0.0f);
            result.push_back({1, pos, posR, angle, angleR});  // down the holder
        }
        {
            Math::Vector pos(0.0f, 0.0f, 0.0f);
            Math::Vector posR(0.0f, 0.0f, 0.0f);
            Math::Vector angle(0.0f, 0.0f, -Math::PI/2.0f);
            Math::Vector angleR(0.0f, 0.0f, 0.0f);
            result.push_back({4, pos, posR, angle, angleR});
        }
        {
            Math::Vector pos(0.0f, 0.0f, 0.0f);
            Math::Vector posR(0.0f, 0.0f, 0.0f);
            Math::Vector angle(0.0f, 0.0f, Math::PI/2.0f);
            Math::Vector angleR(0.0f, 0.0f, 0.0f);
            result.push_back({2, pos, posR, angle, angleR});
        }
    }
    if ( type == OBJECT_MOBILErs )
    {
        {
            Math::Vector pos(0.0f, -10.0f, 0.0f);
            Math::Vector posR(0.0f, 0.0f, 0.0f);
            Math::Vector angle(0.0f, 0.0f, 0.0f);
            Math::Vector angleR(0.0f, 0.0f, 0.0f);
            result.push_back({1, pos, posR, angle, angleR});  // down the holder
        }
        {
            Math::Vector pos(0.0f, -5.0f, 0.0f);
            Math::Vector posR(0.0f, 0.0f, 0.0f);
            Math::Vector angle(0.0f, 0.0f, 0.0f);
            Math::Vector angleR(0.0f, 0.0f, 0.0f);
            result.push_back({2, pos, posR, angle, angleR});
        }
        {
            Math::Vector pos(0.0f, -5.0f, 0.0f);
            Math::Vector posR(0.0f, 0.0f, 0.0f);
            Math::Vector angle(0.0f, 0.0f, 0.0f);
            Math::Vector angleR(0.0f, 0.0f, 0.0f);
            result.push_back({3, pos, posR, angle, angleR});
        }
    }
    if ( type == OBJECT_MOBILEsa )
    {
        Math::Vector pos(0.0f, -10.0f, 0.0f);
        Math::Vector posR(0.0f, 0.0f, 0.0f);
        Math::Vector angle(0.0f, 0.0f, 0.0f);
        Math::Vector angleR(0.0f, 0.0f, 0.0f);
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
            Math::Vector pos(0.0f, 0.0f, 0.0f);
            Math::Vector posR(0.0f, 0.5f, 0.0f);
            Math::Vector angle(-0.5f*Math::PI/2.0f, -0.5f*Math::PI/2.0f, 0.0f);
            Math::Vector angleR(Math::PI/2.0f, Math::PI/2.0f, 0.0f);
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
            Math::Vector pos(0.0f, -4.0f, 2.0f);
            Math::Vector posR(0.0f, 0.0f, 0.0f);
            Math::Vector angle(-0.5f*20.0f*Math::PI/180.0f, -0.5f*10.0f*Math::PI/180.0f, -0.5f*30.0f*Math::PI/180.0f);
            Math::Vector angleR(20.0f*Math::PI/180.0f, 10.0f*Math::PI/180.0f, 30.0f*Math::PI/180.0f);
            result.push_back({6, pos, posR, angle, angleR});  // down the right caterpillar
        }
        {
            Math::Vector pos(0.0f, -4.0f, -2.0f);
            Math::Vector posR(0.0f, 0.0f, 0.0f);
            Math::Vector angle(-0.5f*20.0f*Math::PI/180.0f, -0.5f*10.0f*Math::PI/180.0f, -0.5f*30.0f*Math::PI/180.0f);
            Math::Vector angleR(20.0f*Math::PI/180.0f, 10.0f*Math::PI/180.0f, 30.0f*Math::PI/180.0f);
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
            Math::Vector pos(0.0f, -3.0f, 0.0f);
            Math::Vector posR(0.0f, 0.0f, 0.0f);
            Math::Vector angle(0.0f, 0.0f, -0.5f*Math::PI/2.0f);
            Math::Vector angleR(0.0f, 0.0f, Math::PI/2.0f);
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
            Math::Vector pos(0.0f, -3.0f, 0.0f);
            Math::Vector posR(0.0f, 0.0f, 0.0f);
            Math::Vector angle(0.0f, -0.5f*Math::PI/4.0f, -0.5f*Math::PI/4.0f);
            Math::Vector angleR(0.0f, Math::PI/4.0f, Math::PI/4.0f);
            result.push_back({6+i, pos, posR, angle, angleR});  // leg
        }
    }
    return result;
}

ObjectType CHardcodeCollection::GetTypeAfterBurn(ObjectType type)
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
    else
    {
        return (OBJECT_RUINmobilew1); // Wreck (recoverable by Recycler)
    }
}

bool CHardcodeCollection::IsExplodesInWater(ObjectType type)
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


//////////////////////////////////////////////////////////////////////////////
// Camera Details
//////////////////////////////////////////////////////////////////////////////

bool CHardcodeCollection::IsCameraTypeChangable(ObjectType type)
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

bool CHardcodeCollection::IsCameraTypePersistent(ObjectType type)
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

Gfx::CameraType CHardcodeCollection::GetDefaultCameraType(ObjectType type)
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

float CHardcodeCollection::GetBackCameraDistance(ObjectType type)
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

float CHardcodeCollection::GetBackCameraDistanceMin(ObjectType type)
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

float CHardcodeCollection::GetBackCameraHeight(ObjectType type)
{
         if (type == OBJECT_BASE ) return 40.0f;
    else if (type == OBJECT_HUMAN) return 1.0f;
    else if (type == OBJECT_TECH ) return 1.0f;
    else                           return 4.0f;
}

float CHardcodeCollection::GetBackCameraRotationY(ObjectType type)
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

float CHardcodeCollection::GetBackCameraRotationZ(ObjectType type)
{
    if (type == OBJECT_MOBILEdr)  // designer?
        return 0.09375f;
    return 0.0;
}

float CHardcodeCollection::GetVisitCameraDistance(ObjectType type)
{
    if ( type == OBJECT_PORTICO )  return 200.0f;
    if ( type == OBJECT_BASE    )  return 200.0f;
    if ( type == OBJECT_NUCLEAR )  return 100.0f;
    if ( type == OBJECT_PARA    )  return 100.0f;
    if ( type == OBJECT_SAFE    )  return 100.0f;
    if ( type == OBJECT_TOWER   )  return  80.0f;
    return 60.0f;
}

float CHardcodeCollection::GetVisitCameraHeight(ObjectType type)
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

bool CHardcodeCollection::DisableBackCameraCanForceTransparency(ObjectType type)
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

bool CHardcodeCollection::DisableBackCameraCanViewAsTransparent(ObjectType type)
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

bool CHardcodeCollection::HasGateTransparencyOnBackCamera(ObjectType type)
{
    if (type == OBJECT_FACTORY)  return true;
    return false;
}


bool CHardcodeCollection::DisableCollisionsOnFixCamera(ObjectType type)
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

bool CHardcodeCollection::DisableOnboardCameraCorners(ObjectType type)
{
    if (type == OBJECT_HUMAN ||
        type == OBJECT_TECH) return true;
    return false;
}

bool CHardcodeCollection::HasOnboardCameraCrosshair(ObjectType type)
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



//////////////////////////////////////////////////////////////////////////////
// Automation Details
//////////////////////////////////////////////////////////////////////////////

bool CHardcodeCollection::IsBlockingBuilding(ObjectType type)
{
    if ( type == OBJECT_DERRICK  ||
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
         type == OBJECT_START    ||
         type == OBJECT_END      ||
         type == OBJECT_INFO     ||
         type == OBJECT_PARA     ||
         type == OBJECT_SAFE     ||
         type == OBJECT_HUSTON   ) return true;
    return false;
}

bool CHardcodeCollection::IsAutoTargetedByTower(ObjectType type)
{
    if (type == OBJECT_ANT      ||
        type == OBJECT_SPIDER   ||
        type == OBJECT_BEE      ||
        type == OBJECT_WORM     ||
        type == OBJECT_MOTHER) return true;

     return false;
}

bool CHardcodeCollection::IsAutoTargetedByMushroom(ObjectType type)
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
             type == OBJECT_DERRICK  ||
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
             type == OBJECT_HUMAN    )  return true;
             
    return false;
}

bool CHardcodeCollection::IsAutoCommentedByAssistant(ObjectType type)
{
    if (type == OBJECT_HUMAN    ||
        type == OBJECT_TECH     ||
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
        type == OBJECT_MOBILEwt ||
        type == OBJECT_MOBILEtt ||
        type == OBJECT_MOBILEft ||
        type == OBJECT_MOBILEit ||
        type == OBJECT_MOBILErp ||
        type == OBJECT_MOBILEst ||
        type == OBJECT_MOBILEtg ||
        type == OBJECT_MOBILEdr ) return true;

    return false;
}

bool CHardcodeCollection::IsAutoChargedAtPowerStation(ObjectType type)
{
    if ( type != OBJECT_HUMAN    &&
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
         type != OBJECT_MOBILEft &&
         type != OBJECT_MOBILEtt &&
         type != OBJECT_MOBILEwt &&
         type != OBJECT_MOBILEit &&
         type != OBJECT_MOBILErp &&
         type != OBJECT_MOBILEst &&
         type != OBJECT_MOBILEtg &&
         type != OBJECT_MOBILEdr) return false;

     return true;
}

bool CHardcodeCollection::IsAutoBlockingPowerPlant(ObjectType type)
{
    if ( type != OBJECT_HUMAN    &&
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
         type != OBJECT_MOTHER   &&
         type != OBJECT_ANT      &&
         type != OBJECT_SPIDER   &&
         type != OBJECT_BEE      &&
         type != OBJECT_WORM) return false;

     return true;
}

bool CHardcodeCollection::IsAutoBlockingNuclearPlant(ObjectType type)
{
    if ( type != OBJECT_HUMAN    &&
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
         type != OBJECT_MOTHER   &&
         type != OBJECT_ANT      &&
         type != OBJECT_SPIDER   &&
         type != OBJECT_BEE      &&
         type != OBJECT_WORM) return false;

     return true;
}

bool CHardcodeCollection::IsAutoBlockingFactory(ObjectType type)
{
    if ( type != OBJECT_HUMAN    &&
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
         type != OBJECT_MOTHER   &&
         type != OBJECT_ANT      &&
         type != OBJECT_SPIDER   &&
         type != OBJECT_BEE      &&
         type != OBJECT_WORM ) return false;

     return true;
}

std::vector<CObjectProductionAutomationDetails> CHardcodeCollection::GetProduction(ObjectType type)
{
    std::vector<CObjectProductionAutomationDetails> result;

    if ( type == OBJECT_CONVERT )
        result.push_back({OBJECT_STONE, OBJECT_METAL});
    if ( type == OBJECT_ENERGY )
        result.push_back({OBJECT_METAL, OBJECT_POWER});
    if ( type == OBJECT_NUCLEAR )
        result.push_back({OBJECT_URANIUM, OBJECT_ATOMIC});
    if ( type == OBJECT_NEST )
        result.push_back({OBJECT_NULL, OBJECT_BULLET});
    if ( type == OBJECT_MOBILErr)
    {
        result.push_back({OBJECT_RUINmobilew1, OBJECT_METAL});
        result.push_back({OBJECT_RUINmobilew2, OBJECT_METAL});
        result.push_back({OBJECT_RUINmobilet1, OBJECT_METAL});
        result.push_back({OBJECT_RUINmobilet2, OBJECT_METAL});
        result.push_back({OBJECT_RUINmobiler1, OBJECT_METAL});
        result.push_back({OBJECT_RUINmobiler2, OBJECT_METAL});
    }

    return result;
}

//////////////////////////////////////////////////////////////////////////////
// UI Icon Details
//////////////////////////////////////////////////////////////////////////////

bool CHardcodeCollection::GetMapShowEvenUnselectable(ObjectType type)
{
    if ( type == OBJECT_MOTHER   ||
         type == OBJECT_ANT      ||
         type == OBJECT_SPIDER   ||
         type == OBJECT_BEE      ||
         type == OBJECT_WORM     ||
         type == OBJECT_MOBILEtg ) return true;

    return false;
}

MapColor CHardcodeCollection::GetMapIconColor(ObjectType type)
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

int CHardcodeCollection::GetMapIcon(ObjectType type)
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

bool CHardcodeCollection::IsShortcutBuilding(ObjectType type)
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

bool CHardcodeCollection::IsShortcutMovable(ObjectType type)
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

int CHardcodeCollection::GetShortcutIcon(ObjectType type)
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



//////////////////////////////////////////////////////////////////////////////
// User Interface Details
//////////////////////////////////////////////////////////////////////////////

bool CHardcodeCollection::HasUserInterfaceProgramUI(ObjectType type)
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

bool CHardcodeCollection::HasUserInterfaceProgramUIBlink(ObjectType type)
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

std::vector<Ui::CWidget> CHardcodeCollection::GetUserInterfaceWidgetList(ObjectType type)
{
    std::vector<Ui::CWidget> result;
    Ui::CWidgetParams params = {-1};
    
    if ( (type == OBJECT_HUMAN ||
          type == OBJECT_TECH  ) )
    {
        result.push_back({Math::Point(7.7f, 0.5f), Math::Point(1.0f, 1.0f), Ui::WIDGET_ICON_BUTTON, 31, EVENT_OBJECT_HTAKE, true, false, false, true});

        result.push_back({Math::Point(10.1f, 0.5f), Math::Point(1.0f, 1.0f), Ui::WIDGET_ICON_BUTTON, 64+54, EVENT_OBJECT_FCREATE, false, false, false, true, BUILD_FLAG});
        result.push_back({Math::Point(11.1f, 0.5f), Math::Point(1.0f, 1.0f), Ui::WIDGET_ICON_BUTTON, 64+55, EVENT_OBJECT_FDELETE, false, false, false, true, BUILD_FLAG});     
        params.color = Gfx::Color(0.28f, 0.56f, 1.0f, 0.0f);
        result.push_back({Math::Point(10.1f, 1.6f), Math::Point(0.4f, 0.4f), Ui::WIDGET_COLOR_BUTTON, params, EVENT_OBJECT_FCOLORb, false, false, false, true, BUILD_FLAG});
        params.color = Gfx::Color(1.0f, 0.0f, 0.0f, 0.0f);
        result.push_back({Math::Point(10.5f, 1.6f), Math::Point(0.4f, 0.4f), Ui::WIDGET_COLOR_BUTTON, params, EVENT_OBJECT_FCOLORr, false, false, false, true, BUILD_FLAG});
        params.color = Gfx::Color(0.0f, 0.8f, 0.0f, 0.0f);
        result.push_back({Math::Point(10.9f, 1.6f), Math::Point(0.4f, 0.4f), Ui::WIDGET_COLOR_BUTTON, params, EVENT_OBJECT_FCOLORg, false, false, false, true, BUILD_FLAG});
        params.color = Gfx::Color(1.0f, 0.93f, 0.0f, 0.0f);
        result.push_back({Math::Point(11.3f, 1.6f), Math::Point(0.4f, 0.4f), Ui::WIDGET_COLOR_BUTTON, params, EVENT_OBJECT_FCOLORy, false, false, false, true, BUILD_FLAG});
        params.color = Gfx::Color(0.82f, 0.004f, 0.99f, 0.0f);
        result.push_back({Math::Point(11.7f, 1.6f), Math::Point(0.4f, 0.4f), Ui::WIDGET_COLOR_BUTTON, params, EVENT_OBJECT_FCOLORv, false, false, false, true, BUILD_FLAG});
    }

    if ( (type == OBJECT_HUMAN ) )
    {
        result.push_back({Math::Point(9.0f, 0.5f), Math::Point(1.0f, 1.0f), Ui::WIDGET_ICON_BUTTON, 64+47, EVENT_OBJECT_GFLAT, false, false, false, true, BUILD_GFLAT});
    }

    if ( (type == OBJECT_MOBILEfa ||
          type == OBJECT_MOBILEta ||
          type == OBJECT_MOBILEwa ||
          type == OBJECT_MOBILEia ) )
    {
        result.push_back({Math::Point(7.7f,  0.5f), Math::Point(1.0f, 1.0f), Ui::WIDGET_ICON_BUTTON, 32, EVENT_OBJECT_MTAKE,  true, false,  true, false});
        result.push_back({Math::Point(8.9f,  0.5f), Math::Point(1.0f, 1.0f), Ui::WIDGET_ICON_BUTTON, 34, EVENT_OBJECT_MBACK,  false, false, true, false});
        result.push_back({Math::Point(9.9f,  0.5f), Math::Point(1.0f, 1.0f), Ui::WIDGET_ICON_BUTTON, 35, EVENT_OBJECT_MPOWER, false, false, true, false});
        result.push_back({Math::Point(10.9f, 0.5f), Math::Point(1.0f, 1.0f), Ui::WIDGET_ICON_BUTTON, 33, EVENT_OBJECT_MFRONT, false, false, true, false});
    }

    if ( (type == OBJECT_MOBILEsa ) )
    {
        result.push_back({Math::Point(7.7f,  0.5f), Math::Point(1.0f, 1.0f), Ui::WIDGET_ICON_BUTTON, 32, EVENT_OBJECT_MTAKE,  true, false,  true, false});
    }

    if ( (type == OBJECT_MOBILEfs ||
          type == OBJECT_MOBILEts ||
          type == OBJECT_MOBILEws ||
          type == OBJECT_MOBILEis ) )
    {
        result.push_back({Math::Point(7.7f, 0.5f), Math::Point(1.0f, 1.0f), Ui::WIDGET_ICON_BUTTON, 40, EVENT_OBJECT_SEARCH, true, false, true, false});
        result.push_back({Math::Point(9.0f, 0.5f), Math::Point(1.0f, 1.0f), Ui::WIDGET_ICON_BUTTON, 11, EVENT_OBJECT_DELSEARCH, false, false, true, false});
        
        result.push_back({Math::Point(10.1f, 0.5f), Math::Point(1.0f, 1.0f), Ui::WIDGET_ICON_BUTTON, 64+54, EVENT_OBJECT_FCREATE, false, false, true, false, BUILD_FLAG});
        result.push_back({Math::Point(11.1f, 0.5f), Math::Point(1.0f, 1.0f), Ui::WIDGET_ICON_BUTTON, 64+55, EVENT_OBJECT_FDELETE, false, false, true, false, BUILD_FLAG});     
        params.color = Gfx::Color(0.28f, 0.56f, 1.0f, 0.0f);
        result.push_back({Math::Point(10.1f, 1.6f), Math::Point(0.4f, 0.4f), Ui::WIDGET_COLOR_BUTTON, params, EVENT_OBJECT_FCOLORb, false, false, true, false, BUILD_FLAG});
        params.color = Gfx::Color(1.0f, 0.0f, 0.0f, 0.0f);
        result.push_back({Math::Point(10.5f, 1.6f), Math::Point(0.4f, 0.4f), Ui::WIDGET_COLOR_BUTTON, params, EVENT_OBJECT_FCOLORr, false, false, true, false, BUILD_FLAG});
        params.color = Gfx::Color(0.0f, 0.8f, 0.0f, 0.0f);
        result.push_back({Math::Point(10.9f, 1.6f), Math::Point(0.4f, 0.4f), Ui::WIDGET_COLOR_BUTTON, params, EVENT_OBJECT_FCOLORg, false, false, true, false, BUILD_FLAG});
        params.color = Gfx::Color(1.0f, 0.93f, 0.0f, 0.0f);
        result.push_back({Math::Point(11.3f, 1.6f), Math::Point(0.4f, 0.4f), Ui::WIDGET_COLOR_BUTTON, params, EVENT_OBJECT_FCOLORy, false, false, true, false, BUILD_FLAG});
        params.color = Gfx::Color(0.82f, 0.004f, 0.99f, 0.0f);
        result.push_back({Math::Point(11.7f, 1.6f), Math::Point(0.4f, 0.4f), Ui::WIDGET_COLOR_BUTTON, params, EVENT_OBJECT_FCOLORv, false, false, true, false, BUILD_FLAG});
    }

    if ( (type == OBJECT_MOBILErt ) )
    {
        result.push_back({Math::Point(7.7f,  0.5f), Math::Point(1.0f, 1.0f), Ui::WIDGET_ICON_BUTTON, 128+18, EVENT_OBJECT_TERRAFORM, true, false,  true, false});
        result.push_back({Math::Point(10.2f, 0.5f), Math::Point(1.0f, 1.0f), Ui::WIDGET_ICON_BUTTON, 41, EVENT_OBJECT_LIMIT, false, false, true, false});
    }

    if ( (type == OBJECT_MOBILErr ) )
    {
        result.push_back({Math::Point(7.7f, 0.5f), Math::Point(1.0f, 1.0f), Ui::WIDGET_ICON_BUTTON, 128+20, EVENT_OBJECT_RECOVER, true, false, true, false});
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
        result.push_back({Math::Point(7.7f,  0.5f), Math::Point(1.0f, 1.0f), Ui::WIDGET_ICON_BUTTON, 42, EVENT_OBJECT_FIRE,  true, true,  true, false});
    }

    if ( (type == OBJECT_MOBILEdr ) )
    {

    }

    if ( (type == OBJECT_BEE ) )
    {
        result.push_back({Math::Point(7.7f,  0.5f), Math::Point(1.0f, 1.0f), Ui::WIDGET_ICON_BUTTON, 32, EVENT_OBJECT_MTAKE,  true, false,  false, false});
    }

    if ( (type == OBJECT_SPIDER ) )
    {
        result.push_back({Math::Point(7.7f,  0.5f), Math::Point(1.0f, 1.0f), Ui::WIDGET_ICON_BUTTON, 42, EVENT_OBJECT_SPIDEREXPLO,  true, true,  false, false});
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
        result.push_back({Math::Point(2.1f,  0.0f), Math::Point(0.6f, 0.6f), Ui::WIDGET_ICON_BUTTON, 12, EVENT_OBJECT_DELETE,  false, false,  false, false});
    }

    if (type == OBJECT_BASE )
    {
        result.push_back({Math::Point(0.0f,  0.0f), Math::Point(2.0f, 2.0f), Ui::WIDGET_ICON_LOGO, 128+43, EVENT_OBJECT_TYPE,  false, false,  false, false});
    }
    if (type == OBJECT_FACTORY )
    {
        result.push_back({Math::Point(0.0f,  0.0f), Math::Point(2.0f, 2.0f), Ui::WIDGET_ICON_LOGO, 128+32, EVENT_OBJECT_TYPE,  false, false,  false, false});
    }
    if (type == OBJECT_RESEARCH )
    {
        result.push_back({Math::Point(0.0f,  0.0f), Math::Point(2.0f, 2.0f), Ui::WIDGET_ICON_LOGO, 128+35, EVENT_OBJECT_TYPE,  false, false,  false, false});
    }
    if (type == OBJECT_CONVERT )
    {
        result.push_back({Math::Point(0.0f,  0.0f), Math::Point(2.0f, 2.0f), Ui::WIDGET_ICON_LOGO, 128+34, EVENT_OBJECT_TYPE,  false, false,  false, false});
    }
    if (type == OBJECT_STATION )
    {
        result.push_back({Math::Point(0.0f,  0.0f), Math::Point(2.0f, 2.0f), Ui::WIDGET_ICON_LOGO, 128+36, EVENT_OBJECT_TYPE,  false, false,  false, false});
    }
    if (type == OBJECT_RADAR )
    {
        result.push_back({Math::Point(0.0f,  0.0f), Math::Point(2.0f, 2.0f), Ui::WIDGET_ICON_LOGO, 128+40, EVENT_OBJECT_TYPE,  false, false,  false, false});
    }
    if (type == OBJECT_REPAIR )
    {
        result.push_back({Math::Point(0.0f,  0.0f), Math::Point(2.0f, 2.0f), Ui::WIDGET_ICON_LOGO, 128+41, EVENT_OBJECT_TYPE,  false, false,  false, false});
    }
    if (type == OBJECT_TOWER )
    {
        result.push_back({Math::Point(0.0f,  0.0f), Math::Point(2.0f, 2.0f), Ui::WIDGET_ICON_LOGO, 128+37, EVENT_OBJECT_TYPE,  false, false,  false, false});
    }
    if (type == OBJECT_ENERGY )
    {
        result.push_back({Math::Point(0.0f,  0.0f), Math::Point(2.0f, 2.0f), Ui::WIDGET_ICON_LOGO, 128+39, EVENT_OBJECT_TYPE,  false, false,  false, false});
    }
    if (type == OBJECT_DERRICK )
    {
        result.push_back({Math::Point(0.0f,  0.0f), Math::Point(2.0f, 2.0f), Ui::WIDGET_ICON_LOGO, 128+33, EVENT_OBJECT_TYPE,  false, false,  false, false});
    }
    if (type == OBJECT_NUCLEAR )
    {
        result.push_back({Math::Point(0.0f,  0.0f), Math::Point(2.0f, 2.0f), Ui::WIDGET_ICON_LOGO, 128+42, EVENT_OBJECT_TYPE,  false, false,  false, false});
    }
    if (type == OBJECT_LABO )
    {
        result.push_back({Math::Point(0.0f,  0.0f), Math::Point(2.0f, 2.0f), Ui::WIDGET_ICON_LOGO, 128+38, EVENT_OBJECT_TYPE,  false, false,  false, false});
    }
    if (type == OBJECT_INFO )
    {
        result.push_back({Math::Point(0.0f,  0.0f), Math::Point(2.0f, 2.0f), Ui::WIDGET_ICON_LOGO, 128+44, EVENT_OBJECT_TYPE,  false, false,  false, false});
    }
    if (type == OBJECT_PARA )
    {
        result.push_back({Math::Point(0.0f,  0.0f), Math::Point(2.0f, 2.0f), Ui::WIDGET_ICON_LOGO, 128+46, EVENT_OBJECT_TYPE,  false, false,  false, false});
    }
    if (type == OBJECT_SAFE )
    {
        result.push_back({Math::Point(0.0f,  0.0f), Math::Point(2.0f, 2.0f), Ui::WIDGET_ICON_LOGO, 128+47, EVENT_OBJECT_TYPE,  false, false,  false, false});
    }
    if (type == OBJECT_HUSTON )
    {
        result.push_back({Math::Point(0.0f,  0.0f), Math::Point(2.0f, 2.0f), Ui::WIDGET_ICON_LOGO, 128+48, EVENT_OBJECT_TYPE,  false, false,  false, false});
    }
    if (type == OBJECT_DESTROYER )
    {
        result.push_back({Math::Point(0.0f,  0.0f), Math::Point(2.0f, 2.0f), Ui::WIDGET_ICON_LOGO, 128+41, EVENT_OBJECT_TYPE,  false, false,  false, false});
    }


    return result;
}

bool CHardcodeCollection::HasUserInterfaceBuilderUIHuman(ObjectType type)
{
    if ( type == OBJECT_HUMAN )  return true;

    return false;
}

bool CHardcodeCollection::HasUserInterfaceBuilderUIRobot(ObjectType type)
{
    if ( (type == OBJECT_MOBILEfb ||
          type == OBJECT_MOBILEtb ||
          type == OBJECT_MOBILEwb ||
          type == OBJECT_MOBILEib) )  return true;

    return false;
}

bool CHardcodeCollection::HasUserInterfaceShielderUIRobot(ObjectType type)
{
    if ( (type == OBJECT_MOBILErs ) )  return true;

    return false;
}

bool CHardcodeCollection::HasUserInterfaceScribblerUIRobot(ObjectType type)
{
    if ( (type == OBJECT_MOBILEdr ) )  return true;

    return false;
}

bool CHardcodeCollection::HasUserInterfaceDisableFlyWhileGrabbing(ObjectType type)
{
    if ( (type == OBJECT_HUMAN ||
          type == OBJECT_TECH  ) )   return true;

    return false;
}



//////////////////////////////////////////////////////////////////////////////
// Global details
//////////////////////////////////////////////////////////////////////////////

ObjectType CHardcodeCollection::GetPlayerType()
{
    return OBJECT_HUMAN;
}

ObjectType CHardcodeCollection::GetBaseType()
{
    return OBJECT_BASE;
}

ObjectType CHardcodeCollection::GetAssistantType()
{
    return OBJECT_TOTO;
}

ObjectType CHardcodeCollection::GetFunctionDestroyPerformerObject()
{
    return OBJECT_DESTROYER;
}

ObjectType CHardcodeCollection::GetFunctionFactoryPerformerObject()
{
    return OBJECT_FACTORY;
}

ObjectType CHardcodeCollection::GetFunctionTakeOffPerformerObject()
{
    return OBJECT_BASE;
}

ObjectType CHardcodeCollection::GetFunctionReceivePerformerObject()
{
    return OBJECT_INFO;
}

std::vector<CObjectButton> CHardcodeCollection::GetBuilderMenuButtons()
{
    std::vector<CObjectButton> result;
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
    return result;
}

std::vector<CObjectButton> CHardcodeCollection::GetDebugMenuButtons()
{
    std::vector<CObjectButton> result;
    result.push_back({OBJECT_HUMAN,    128+8,  ""});
    result.push_back({OBJECT_MOBILEwa, 128+9,  ""});
    result.push_back({OBJECT_MOBILEwc, 128+15, ""});
    result.push_back({OBJECT_MOBILErc, 128+19, ""});
    result.push_back({OBJECT_FACTORY,  128+32, ""});
    result.push_back({OBJECT_CONVERT,  128+34, ""});
    result.push_back({OBJECT_DERRICK,  128+33, ""});
    result.push_back({OBJECT_STATION,  128+36, ""});
    result.push_back({OBJECT_METAL,    -1,     "Titanium"});
    result.push_back({OBJECT_STONE,    -1,     "TitaniumOre"});
    result.push_back({OBJECT_URANIUM,  -1,     "UraniumOre"});
    result.push_back({OBJECT_POWER,    -1,     "PowerCell"});
    result.push_back({OBJECT_ATOMIC,   -1,     "NuclearCell"});
    return result;
}
