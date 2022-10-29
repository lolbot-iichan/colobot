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

#include "object/hardcode/scripting_hardcode.h"

const char* CScriptingHardcodeCollection::GetNameInScriptFiles(ObjectType type)
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

const char* CScriptingHardcodeCollection::GetAliasInScriptFiles(ObjectType type)
{
    if ( type == OBJECT_MARKURANIUM )  return "PlatinumSpot";
    if ( type == OBJECT_URANIUM     )  return "PlatinumOre";
    if ( type == OBJECT_ATOMIC      )  return "FuelCell";
    if ( type == OBJECT_NUCLEAR     )  return "FuelCellPlant";
    return "";
}

const char* CScriptingHardcodeCollection::GetHelpTopicPathName(ObjectType type)
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

bool CScriptingHardcodeCollection::IsValidObjectTypeId(ObjectType type)
{
    if (type == OBJECT_PORTICO       ||
        type == OBJECT_BASE          ||
        type == OBJECT_DERRICK       ||
        type == OBJECT_FACTORY       ||
        type == OBJECT_STATION       ||
        type == OBJECT_CONVERT       ||
        type == OBJECT_REPAIR        ||
        type == OBJECT_TOWER         ||
        type == OBJECT_NEST          ||
        type == OBJECT_RESEARCH      ||
        type == OBJECT_RADAR         ||
        type == OBJECT_ENERGY        ||
        type == OBJECT_LABO          ||
        type == OBJECT_NUCLEAR       ||
        type == OBJECT_START         ||
        type == OBJECT_END           ||
        type == OBJECT_INFO          ||
        type == OBJECT_PARA          ||
        type == OBJECT_TARGET1       ||
        type == OBJECT_TARGET2       ||
        type == OBJECT_SAFE          ||
        type == OBJECT_HUSTON        ||
        type == OBJECT_DESTROYER     ||
        type == OBJECT_STONE         ||
        type == OBJECT_URANIUM       ||
        type == OBJECT_METAL         ||
        type == OBJECT_POWER         ||
        type == OBJECT_ATOMIC        ||
        type == OBJECT_BULLET        ||
        type == OBJECT_BBOX          ||
        type == OBJECT_TNT           ||
        type == OBJECT_MARKPOWER     ||
        type == OBJECT_MARKSTONE     ||
        type == OBJECT_MARKURANIUM   ||
        type == OBJECT_MARKKEYa      ||
        type == OBJECT_MARKKEYb      ||
        type == OBJECT_MARKKEYc      ||
        type == OBJECT_MARKKEYd      ||
        type == OBJECT_BOMB          ||
        type == OBJECT_WINFIRE       ||
        type == OBJECT_SHOW          ||
        type == OBJECT_BAG           ||
        type == OBJECT_PLANT0        ||
        type == OBJECT_PLANT1        ||
        type == OBJECT_PLANT2        ||
        type == OBJECT_PLANT3        ||
        type == OBJECT_PLANT4        ||
        type == OBJECT_PLANT5        ||
        type == OBJECT_PLANT6        ||
        type == OBJECT_PLANT7        ||
        type == OBJECT_PLANT8        ||
        type == OBJECT_PLANT9        ||
        type == OBJECT_PLANT10       ||
        type == OBJECT_PLANT11       ||
        type == OBJECT_PLANT12       ||
        type == OBJECT_PLANT13       ||
        type == OBJECT_PLANT14       ||
        type == OBJECT_PLANT15       ||
        type == OBJECT_PLANT16       ||
        type == OBJECT_PLANT17       ||
        type == OBJECT_PLANT18       ||
        type == OBJECT_PLANT19       ||
        type == OBJECT_TREE0         ||
        type == OBJECT_TREE1         ||
        type == OBJECT_TREE2         ||
        type == OBJECT_TREE3         ||
        type == OBJECT_TREE4         ||
        type == OBJECT_TREE5         ||
        type == OBJECT_MOBILEwt      ||
        type == OBJECT_MOBILEtt      ||
        type == OBJECT_MOBILEft      ||
        type == OBJECT_MOBILEit      ||
        type == OBJECT_MOBILErp      ||
        type == OBJECT_MOBILEst      ||
        type == OBJECT_MOBILEwa      ||
        type == OBJECT_MOBILEta      ||
        type == OBJECT_MOBILEfa      ||
        type == OBJECT_MOBILEia      ||
        type == OBJECT_MOBILEwc      ||
        type == OBJECT_MOBILEtc      ||
        type == OBJECT_MOBILEfc      ||
        type == OBJECT_MOBILEic      ||
        type == OBJECT_MOBILEwi      ||
        type == OBJECT_MOBILEti      ||
        type == OBJECT_MOBILEfi      ||
        type == OBJECT_MOBILEii      ||
        type == OBJECT_MOBILEws      ||
        type == OBJECT_MOBILEts      ||
        type == OBJECT_MOBILEfs      ||
        type == OBJECT_MOBILEis      ||
        type == OBJECT_MOBILErt      ||
        type == OBJECT_MOBILErc      ||
        type == OBJECT_MOBILErr      ||
        type == OBJECT_MOBILErs      ||
        type == OBJECT_MOBILEsa      ||
        type == OBJECT_MOBILEtg      ||
        type == OBJECT_MOBILEdr      ||
        type == OBJECT_CONTROLLER    ||
        type == OBJECT_MOBILEwb      ||
        type == OBJECT_MOBILEtb      ||
        type == OBJECT_MOBILEfb      ||
        type == OBJECT_MOBILEib      ||
        type == OBJECT_WAYPOINT      ||
        type == OBJECT_FLAGb         ||
        type == OBJECT_FLAGr         ||
        type == OBJECT_FLAGg         ||
        type == OBJECT_FLAGy         ||
        type == OBJECT_FLAGv         ||
        type == OBJECT_KEYa          ||
        type == OBJECT_KEYb          ||
        type == OBJECT_KEYc          ||
        type == OBJECT_KEYd          ||
        type == OBJECT_HUMAN         ||
        type == OBJECT_TOTO          ||
        type == OBJECT_TECH          ||
        type == OBJECT_BARRIER0      ||
        type == OBJECT_BARRIER1      ||
        type == OBJECT_BARRIER2      ||
        type == OBJECT_BARRIER3      ||
        type == OBJECT_BARRICADE0    ||
        type == OBJECT_BARRICADE1    ||
        type == OBJECT_MOTHER        ||
        type == OBJECT_EGG           ||
        type == OBJECT_ANT           ||
        type == OBJECT_SPIDER        ||
        type == OBJECT_BEE           ||
        type == OBJECT_WORM          ||
        type == OBJECT_RUINmobilew1  ||
        type == OBJECT_RUINmobilew2  ||
        type == OBJECT_RUINmobilet1  ||
        type == OBJECT_RUINmobilet2  ||
        type == OBJECT_RUINmobiler1  ||
        type == OBJECT_RUINmobiler2  ||
        type == OBJECT_RUINfactory   ||
        type == OBJECT_RUINdoor      ||
        type == OBJECT_RUINsupport   ||
        type == OBJECT_RUINradar     ||
        type == OBJECT_RUINconvert   ||
        type == OBJECT_RUINbase      ||
        type == OBJECT_RUINhead      ||
        type == OBJECT_TEEN0         ||
        type == OBJECT_TEEN1         ||
        type == OBJECT_TEEN2         ||
        type == OBJECT_TEEN3         ||
        type == OBJECT_TEEN4         ||
        type == OBJECT_TEEN5         ||
        type == OBJECT_TEEN6         ||
        type == OBJECT_TEEN7         ||
        type == OBJECT_TEEN8         ||
        type == OBJECT_TEEN9         ||
        type == OBJECT_TEEN10        ||
        type == OBJECT_TEEN11        ||
        type == OBJECT_TEEN12        ||
        type == OBJECT_TEEN13        ||
        type == OBJECT_TEEN14        ||
        type == OBJECT_TEEN15        ||
        type == OBJECT_TEEN16        ||
        type == OBJECT_TEEN17        ||
        type == OBJECT_TEEN18        ||
        type == OBJECT_TEEN19        ||
        type == OBJECT_TEEN20        ||
        type == OBJECT_TEEN21        ||
        type == OBJECT_TEEN22        ||
        type == OBJECT_TEEN23        ||
        type == OBJECT_TEEN24        ||
        type == OBJECT_TEEN25        ||
        type == OBJECT_TEEN26        ||
        type == OBJECT_TEEN27        ||
        type == OBJECT_TEEN28        ||
        type == OBJECT_TEEN29        ||
        type == OBJECT_TEEN30        ||
        type == OBJECT_TEEN31        ||
        type == OBJECT_TEEN32        ||
        type == OBJECT_TEEN33        ||
        type == OBJECT_TEEN34        ||
        type == OBJECT_TEEN35        ||
        type == OBJECT_TEEN36        ||
        type == OBJECT_TEEN37        ||
        type == OBJECT_TEEN38        ||
        type == OBJECT_TEEN39        ||
        type == OBJECT_TEEN40        ||
        type == OBJECT_TEEN41        ||
        type == OBJECT_TEEN42        ||
        type == OBJECT_TEEN43        ||
        type == OBJECT_TEEN44        ||
        type == OBJECT_QUARTZ0       ||
        type == OBJECT_QUARTZ1       ||
        type == OBJECT_QUARTZ2       ||
        type == OBJECT_QUARTZ3       ||
        type == OBJECT_ROOT0         ||
        type == OBJECT_ROOT1         ||
        type == OBJECT_ROOT2         ||
        type == OBJECT_ROOT3         ||
        type == OBJECT_ROOT4         ||
        type == OBJECT_ROOT5         ||
        type == OBJECT_MUSHROOM1     ||
        type == OBJECT_MUSHROOM2     ||
        type == OBJECT_APOLLO1       ||
        type == OBJECT_APOLLO2       ||
        type == OBJECT_APOLLO3       ||
        type == OBJECT_APOLLO4       ||
        type == OBJECT_APOLLO5       ||
        type == OBJECT_HOME1          ) return true;

    return false;
}

bool CScriptingHardcodeCollection::IsProduceAlreadyCharged(ObjectType type)
{
    if (type == OBJECT_POWER  ||
        type == OBJECT_ATOMIC  ) return true;

    return false;
}

bool CScriptingHardcodeCollection::IsProduceManual(ObjectType type)
{
    return type == OBJECT_MOBILEdr;
}

ObjectType CScriptingHardcodeCollection::GetProduceContainer(ObjectType type)
{
    if (type == OBJECT_ANT    ||
        type == OBJECT_SPIDER ||
        type == OBJECT_BEE    ||
        type == OBJECT_WORM    ) return OBJECT_EGG;

    return OBJECT_NULL;
}

std::vector<CObjectProduceScriptingFindable> CScriptingHardcodeCollection::GetObjectsFindableByType(ObjectType type)
{
    std::vector<CObjectProduceScriptingFindable> result;

    if ( type == OBJECT_MOBILEpr)
    {
        result.push_back({OBJECT_MOBILEwt});
        result.push_back({OBJECT_MOBILEtt});
        result.push_back({OBJECT_MOBILEft});
        result.push_back({OBJECT_MOBILEit});
        result.push_back({OBJECT_MOBILErp});
        result.push_back({OBJECT_MOBILEst});
    }

    return result;
}
