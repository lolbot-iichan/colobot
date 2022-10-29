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

#include "object/hardcode/naming_hardcode.h"

const char* CNamingHardcodeCollection::GetNameInLevelFiles(ObjectType type)
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

const char* CNamingHardcodeCollection::GetAliasInLevelFiles(ObjectType type)
{
    if ( type == OBJECT_MOBILEwt    )  return "PracticeBot";
    if ( type == OBJECT_MARKURANIUM )  return "PlatinumSpot";
    if ( type == OBJECT_URANIUM     )  return "PlatinumOre";
    if ( type == OBJECT_ATOMIC      )  return "FuelCell";
    if ( type == OBJECT_NUCLEAR     )  return "FuelCellPlant";
    return "";
}
