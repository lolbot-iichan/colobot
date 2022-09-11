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

#include "object/object_details.h"

/* Macro to mark which texts are translatable by gettext
 * It doesn't do anything at compile-time, as all texts represented here are used later
 * in explicit call to gettext(), but it is used by xgettext executable to filter extracted
 * texts from this file.
 */
#define TR(x) x

/* Please run `cmake --build <path_to_build_folder> --target update-pot`
 * after changing this file in order to update translation files. Thank you.
 */

CObjectDetails::CObjectDetails()
{
    m_objects[OBJECT_PORTICO].displayedName      = TR("Gantry crane");
    m_objects[OBJECT_BASE].displayedName         = TR("Spaceship");
    m_objects[OBJECT_DERRICK].displayedName      = TR("Derrick");
    m_objects[OBJECT_FACTORY].displayedName      = TR("Bot factory");
    m_objects[OBJECT_REPAIR].displayedName       = TR("Repair center");
    m_objects[OBJECT_DESTROYER].displayedName    = TR("Destroyer");
    m_objects[OBJECT_STATION].displayedName      = TR("Power station");
    m_objects[OBJECT_CONVERT].displayedName      = TR("Converts ore to titanium");
    m_objects[OBJECT_TOWER].displayedName        = TR("Defense tower");
    m_objects[OBJECT_NEST].displayedName         = TR("Nest");
    m_objects[OBJECT_RESEARCH].displayedName     = TR("Research center");
    m_objects[OBJECT_RADAR].displayedName        = TR("Radar station");
    m_objects[OBJECT_INFO].displayedName         = TR("Information exchange post");
    m_objects[OBJECT_ENERGY].displayedName       = TR("Power cell factory");
    m_objects[OBJECT_LABO].displayedName         = TR("Autolab");
    m_objects[OBJECT_NUCLEAR].displayedName      = TR("Nuclear power station");
    m_objects[OBJECT_PARA].displayedName         = TR("Lightning conductor");
    m_objects[OBJECT_SAFE].displayedName         = TR("Vault");
    m_objects[OBJECT_HUSTON].displayedName       = TR("Houston Mission Control");
    m_objects[OBJECT_TARGET1].displayedName      = TR("Target");
    m_objects[OBJECT_TARGET2].displayedName      = TR("Target");
    m_objects[OBJECT_START].displayedName        = TR("Start");
    m_objects[OBJECT_END].displayedName          = TR("Finish");
    m_objects[OBJECT_STONE].displayedName        = TR("Titanium ore");
    m_objects[OBJECT_URANIUM].displayedName      = TR("Uranium ore");
    m_objects[OBJECT_BULLET].displayedName       = TR("Organic matter");
    m_objects[OBJECT_METAL].displayedName        = TR("Titanium");
    m_objects[OBJECT_POWER].displayedName        = TR("Power cell");
    m_objects[OBJECT_ATOMIC].displayedName       = TR("Nuclear power cell");
    m_objects[OBJECT_BBOX].displayedName         = TR("Black box");
    m_objects[OBJECT_KEYa].displayedName         = TR("Key A");
    m_objects[OBJECT_KEYb].displayedName         = TR("Key B");
    m_objects[OBJECT_KEYc].displayedName         = TR("Key C");
    m_objects[OBJECT_KEYd].displayedName         = TR("Key D");
    m_objects[OBJECT_TNT].displayedName          = TR("Explosive");
    m_objects[OBJECT_BOMB].displayedName         = TR("Fixed mine");
    m_objects[OBJECT_BAG].displayedName          = TR("Survival kit");
    m_objects[OBJECT_WAYPOINT].displayedName     = TR("Checkpoint");
    m_objects[OBJECT_FLAGb].displayedName        = TR("Blue flag");
    m_objects[OBJECT_FLAGr].displayedName        = TR("Red flag");
    m_objects[OBJECT_FLAGg].displayedName        = TR("Green flag");
    m_objects[OBJECT_FLAGy].displayedName        = TR("Yellow flag");
    m_objects[OBJECT_FLAGv].displayedName        = TR("Violet flag");
    m_objects[OBJECT_MARKPOWER].displayedName    = TR("Energy deposit (site for power station)");
    m_objects[OBJECT_MARKURANIUM].displayedName  = TR("Uranium deposit (site for derrick)");
    m_objects[OBJECT_MARKKEYa].displayedName     = TR("Found key A (site for derrick)");
    m_objects[OBJECT_MARKKEYb].displayedName     = TR("Found key B (site for derrick)");
    m_objects[OBJECT_MARKKEYc].displayedName     = TR("Found key C (site for derrick)");
    m_objects[OBJECT_MARKKEYd].displayedName     = TR("Found key D (site for derrick)");
    m_objects[OBJECT_MARKSTONE].displayedName    = TR("Titanium deposit (site for derrick)");
    m_objects[OBJECT_MOBILEft].displayedName     = TR("Practice bot");
    m_objects[OBJECT_MOBILEtt].displayedName     = TR("Practice bot");
    m_objects[OBJECT_MOBILEwt].displayedName     = TR("Practice bot");
    m_objects[OBJECT_MOBILEit].displayedName     = TR("Practice bot");
    m_objects[OBJECT_MOBILErp].displayedName     = TR("Practice bot");
    m_objects[OBJECT_MOBILEst].displayedName     = TR("Practice bot");
    m_objects[OBJECT_MOBILEfa].displayedName     = TR("Winged grabber");
    m_objects[OBJECT_MOBILEta].displayedName     = TR("Tracked grabber");
    m_objects[OBJECT_MOBILEwa].displayedName     = TR("Wheeled grabber");
    m_objects[OBJECT_MOBILEia].displayedName     = TR("Legged grabber");
    m_objects[OBJECT_MOBILEfb].displayedName     = TR("Winged builder");
    m_objects[OBJECT_MOBILEtb].displayedName     = TR("Tracked builder");
    m_objects[OBJECT_MOBILEwb].displayedName     = TR("Wheeled builder");
    m_objects[OBJECT_MOBILEib].displayedName     = TR("Legged builder");
    m_objects[OBJECT_MOBILEfc].displayedName     = TR("Winged shooter");
    m_objects[OBJECT_MOBILEtc].displayedName     = TR("Tracked shooter");
    m_objects[OBJECT_MOBILEwc].displayedName     = TR("Wheeled shooter");
    m_objects[OBJECT_MOBILEic].displayedName     = TR("Legged shooter");
    m_objects[OBJECT_MOBILEfi].displayedName     = TR("Winged orga shooter");
    m_objects[OBJECT_MOBILEti].displayedName     = TR("Tracked orga shooter");
    m_objects[OBJECT_MOBILEwi].displayedName     = TR("Wheeled orga shooter");
    m_objects[OBJECT_MOBILEii].displayedName     = TR("Legged orga shooter");
    m_objects[OBJECT_MOBILEfs].displayedName     = TR("Winged sniffer");
    m_objects[OBJECT_MOBILEts].displayedName     = TR("Tracked sniffer");
    m_objects[OBJECT_MOBILEws].displayedName     = TR("Wheeled sniffer");
    m_objects[OBJECT_MOBILEis].displayedName     = TR("Legged sniffer");
    m_objects[OBJECT_MOBILErt].displayedName     = TR("Thumper");
    m_objects[OBJECT_MOBILErc].displayedName     = TR("Phazer shooter");
    m_objects[OBJECT_MOBILErr].displayedName     = TR("Recycler");
    m_objects[OBJECT_MOBILErs].displayedName     = TR("Shielder");
    m_objects[OBJECT_MOBILEsa].displayedName     = TR("Subber");
    m_objects[OBJECT_MOBILEtg].displayedName     = TR("Target bot");
    m_objects[OBJECT_MOBILEdr].displayedName     = TR("Drawer bot");
    m_objects[OBJECT_TECH].displayedName         = TR("Engineer");
    m_objects[OBJECT_TOTO].displayedName         = TR("Robbie");
    m_objects[OBJECT_MOTHER].displayedName       = TR("Alien Queen");
    m_objects[OBJECT_ANT].displayedName          = TR("Ant");
    m_objects[OBJECT_SPIDER].displayedName       = TR("Spider");
    m_objects[OBJECT_BEE].displayedName          = TR("Wasp");
    m_objects[OBJECT_WORM].displayedName         = TR("Worm");
    m_objects[OBJECT_EGG].displayedName          = TR("Egg");
    m_objects[OBJECT_RUINmobilew1].displayedName = TR("Wreckage");
    m_objects[OBJECT_RUINmobilew2].displayedName = TR("Wreckage");
    m_objects[OBJECT_RUINmobilet1].displayedName = TR("Wreckage");
    m_objects[OBJECT_RUINmobilet2].displayedName = TR("Wreckage");
    m_objects[OBJECT_RUINmobiler1].displayedName = TR("Wreckage");
    m_objects[OBJECT_RUINmobiler2].displayedName = TR("Wreckage");
    m_objects[OBJECT_RUINfactory].displayedName  = TR("Ruin");
    m_objects[OBJECT_RUINdoor].displayedName     = TR("Ruin");
    m_objects[OBJECT_RUINsupport].displayedName  = TR("Waste");
    m_objects[OBJECT_RUINradar].displayedName    = TR("Ruin");
    m_objects[OBJECT_RUINconvert].displayedName  = TR("Ruin");
    m_objects[OBJECT_RUINbase].displayedName     = TR("Spaceship ruin");
    m_objects[OBJECT_RUINhead].displayedName     = TR("Spaceship ruin");
    m_objects[OBJECT_APOLLO1].displayedName      = TR("Remains of Apollo mission");
    m_objects[OBJECT_APOLLO3].displayedName      = TR("Remains of Apollo mission");
    m_objects[OBJECT_APOLLO4].displayedName      = TR("Remains of Apollo mission");
    m_objects[OBJECT_APOLLO5].displayedName      = TR("Remains of Apollo mission");
    m_objects[OBJECT_APOLLO2].displayedName      = TR("Lunar Roving Vehicle");

    m_builderMenuObjects[0]  = { OBJECT_RESEARCH, 128+35, TR("Build a research center") };
    m_builderMenuObjects[1]  = { OBJECT_FACTORY,  128+32, TR("Build a bot factory") };
    m_builderMenuObjects[2]  = { OBJECT_CONVERT,  128+34, TR("Build a converter") };
    m_builderMenuObjects[3]  = { OBJECT_STATION,  128+36, TR("Build a power station") };
    m_builderMenuObjects[4]  = { OBJECT_RADAR,    128+40, TR("Build a radar station") };
    m_builderMenuObjects[5]  = { OBJECT_REPAIR,   128+41, TR("Build a repair center") };
    m_builderMenuObjects[6]  = { OBJECT_INFO,     128+44, TR("Build a exchange post") };
    m_builderMenuObjects[7]  = { OBJECT_TOWER,    128+37, TR("Build a defense tower") };
    m_builderMenuObjects[8]  = { OBJECT_ENERGY,   128+39, TR("Build a power cell factory") };
    m_builderMenuObjects[9]  = { OBJECT_DERRICK,  128+33, TR("Build a derrick") };
    m_builderMenuObjects[10] = { OBJECT_NUCLEAR,  128+42, TR("Build a nuclear power plant") };
    m_builderMenuObjects[11] = { OBJECT_LABO,     128+38, TR("Build an autolab") };
    m_builderMenuObjects[12] = { OBJECT_PARA,     128+46, TR("Build a lightning conductor") };
    m_builderMenuObjects[13] = { OBJECT_SAFE,     128+47, TR("Build a vault") };

    m_debugMenuObjects[0]  = {OBJECT_HUMAN,    128+8,  ""};
    m_debugMenuObjects[1]  = {OBJECT_MOBILEwa, 128+9,  ""};
    m_debugMenuObjects[2]  = {OBJECT_MOBILEwc, 128+15, ""};
    m_debugMenuObjects[3]  = {OBJECT_MOBILErc, 128+19, ""};
    m_debugMenuObjects[4]  = {OBJECT_FACTORY,  128+32, ""};
    m_debugMenuObjects[5]  = {OBJECT_CONVERT,  128+34, ""};
    m_debugMenuObjects[6]  = {OBJECT_DERRICK,  128+33, ""};
    m_debugMenuObjects[7]  = {OBJECT_STATION,  128+36, ""};
    m_debugMenuObjects[8]  = {OBJECT_METAL,    -1,     "Titanium"};
    m_debugMenuObjects[9]  = {OBJECT_STONE,    -1,     "TitaniumOre"};
    m_debugMenuObjects[10] = {OBJECT_URANIUM,  -1,     "UraniumOre"};
    m_debugMenuObjects[11] = {OBJECT_POWER,    -1,     "PowerCell"};
    m_debugMenuObjects[12] = {OBJECT_ATOMIC,   -1,     "NuclearCell"};

    m_aliasToSearchList[OBJECT_MOBILEpr].push_back(OBJECT_MOBILEwt);
    m_aliasToSearchList[OBJECT_MOBILEpr].push_back(OBJECT_MOBILEtt);
    m_aliasToSearchList[OBJECT_MOBILEpr].push_back(OBJECT_MOBILEft);
    m_aliasToSearchList[OBJECT_MOBILEpr].push_back(OBJECT_MOBILEit);
    m_aliasToSearchList[OBJECT_MOBILEpr].push_back(OBJECT_MOBILErp);
    m_aliasToSearchList[OBJECT_MOBILEpr].push_back(OBJECT_MOBILEst);

    for ( int i = 0 ; i < OBJECT_MAX ; i++ )
    {
        ObjectType type = static_cast<ObjectType>(i);

        std::string name = GetNameInLevelFiles(type);
        if (name.size())
        {
            m_nameToObjectType[name] = type;
        }

        std::string alias = GetAliasInLevelFiles(type);
        if (alias.size())
        {
            m_nameToObjectType[alias] = type;
        }
    }
}

CObjectButton CObjectDetails::GetBuilderMenuItem(int index)
{
    if (index < 0 || index >= 14) return CObjectButton();
    return m_builderMenuObjects[index];
}

CObjectButton CObjectDetails::GetDebugMenuItem(int index)
{
    if (index < 0 || index >= 14) return CObjectButton();
    return m_debugMenuObjects[index];
}

ObjectType CObjectDetails::ParseNameOrAliasInLevelFiles(std::string value)
{
    auto it = m_nameToObjectType.find(value);
    if (it != m_nameToObjectType.end())
        return it->second;
    return OBJECT_NULL;
}

std::vector<ObjectType> CObjectDetails::GetObjectsFindableByType(ObjectType type)
{
    auto it = m_aliasToSearchList.find(type);
    if (it != m_aliasToSearchList.end())
        return it->second;

    std::vector<ObjectType> result;
    result.push_back(type);
    return result;
}

bool CObjectDetails::IsBlockingBuilding(ObjectType type)
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

bool CObjectDetails::IsCameraTypeChangable(ObjectType type)
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

bool CObjectDetails::IsCameraTypePersistent(ObjectType type)
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

float CObjectDetails::GetBackCameraDistance(ObjectType type)
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

float CObjectDetails::GetBackCameraDistanceMin(ObjectType type)
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

float CObjectDetails::GetBackCameraHeight(ObjectType type)
{
         if (type == OBJECT_BASE ) return 40.0f;
    else if (type == OBJECT_HUMAN) return 1.0f;
    else if (type == OBJECT_TECH ) return 1.0f;
    else                           return 4.0f;
}

float CObjectDetails::GetBackCameraRotationY(ObjectType type)
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

float CObjectDetails::GetBackCameraRotationZ(ObjectType type)
{
    if (type == OBJECT_MOBILEdr)  // designer?
        return 0.1f;
    return 0.0;
}


bool CObjectDetails::GetBackCameraCanForceTransparency(ObjectType type)
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
         type == OBJECT_HUSTON   )  return false;
    return true;
}

bool CObjectDetails::GetBackCameraCanViewAsTransparent(ObjectType type)
{
    if ( type == OBJECT_HUMAN  ||
         type == OBJECT_TECH   ||
         type == OBJECT_TOTO   ||
         type == OBJECT_ANT    ||
         type == OBJECT_SPIDER ||
         type == OBJECT_BEE    ||
         type == OBJECT_WORM   )  return false;
    return true;
}

bool CObjectDetails::GetFixCameraCanCollide(ObjectType type)
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
         type == OBJECT_WORM ) return false;
    return true;
}

bool CObjectDetails::GetOnboardCameraCorners(ObjectType type)
{
    if (type == OBJECT_HUMAN ||
        type == OBJECT_TECH) return false;
    return true;
}

float CObjectDetails::GetVisitCameraDistance(ObjectType type)
{
    if ( type == OBJECT_PORTICO )  return 200.0f;
    if ( type == OBJECT_BASE    )  return 200.0f;
    if ( type == OBJECT_NUCLEAR )  return 100.0f;
    if ( type == OBJECT_PARA    )  return 100.0f;
    if ( type == OBJECT_SAFE    )  return 100.0f;
    if ( type == OBJECT_TOWER   )  return  80.0f;
    return 60.0f;
}

float CObjectDetails::GetVisitCameraHeight(ObjectType type)
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

bool CObjectDetails::GetImmuneToFireballs(ObjectType type)
{
    if (type == OBJECT_MOTHER)  return true;
    return false;
}

bool CObjectDetails::GetImmuneToInsects(ObjectType type)
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

bool CObjectDetails::GetImmuneToSpiders(ObjectType type)
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

bool CObjectDetails::GetImmuneToOrgaballs(ObjectType type)
{
    if (type == OBJECT_MOTHER)  return true;
    return false;
}

bool CObjectDetails::GetImmuneToPhazers(ObjectType type)
{
    return false;
}

bool CObjectDetails::GetImmuneToTowerRays(ObjectType type)
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

bool CObjectDetails::IsAutoTargetedByTower(ObjectType type)
{
    if (type == OBJECT_ANT      ||
        type == OBJECT_SPIDER   ||
        type == OBJECT_BEE      ||
        type == OBJECT_WORM     ||
        type == OBJECT_MOTHER) return true;

     return false;
}

bool CObjectDetails::IsAutoBlockingPowerStation(ObjectType type)
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

bool CObjectDetails::IsAutoBlockingPowerPlant(ObjectType type)
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

bool CObjectDetails::IsAutoBlockingNuclearPlant(ObjectType type)
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

bool CObjectDetails::IsAutoBlockingFactory(ObjectType type)
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

std::string CObjectDetails::GetNameInLevelFiles(ObjectType type)
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

std::string CObjectDetails::GetAliasInLevelFiles(ObjectType type)
{
    if ( type == OBJECT_MOBILEwt    )  return "PracticeBot";
    if ( type == OBJECT_MARKURANIUM )  return "PlatinumSpot";
    if ( type == OBJECT_URANIUM     )  return "PlatinumOre";
    if ( type == OBJECT_ATOMIC      )  return "FuelCell";
    if ( type == OBJECT_NUCLEAR     )  return "FuelCellPlant";
    return "";
}

std::string CObjectDetails::GetNameInScriptFiles(ObjectType type)
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

std::string CObjectDetails::GetAliasInScriptFiles(ObjectType type)
{
    if ( type == OBJECT_MARKURANIUM )  return "PlatinumSpot";
    if ( type == OBJECT_URANIUM     )  return "PlatinumOre";
    if ( type == OBJECT_ATOMIC      )  return "FuelCell";
    if ( type == OBJECT_NUCLEAR     )  return "FuelCellPlant";
    return "";
}

std::string CObjectDetails::GetHelpTopicPathName(ObjectType type)
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

ObjectType CObjectDetails::GetFunctionDestroyPerformerObject()
{
    return OBJECT_DESTROYER;
}

ObjectType CObjectDetails::GetFunctionFactoryPerformerObject()
{
    return OBJECT_FACTORY;
}

ObjectType CObjectDetails::GetFunctionResearchPerformerObject(ResearchType type)
{
    if ( type == RESEARCH_iPAW       ||
         type == RESEARCH_iGUN       ||
         type == RESEARCH_TARGET      ) return OBJECT_LABO;
    return OBJECT_RESEARCH;
}

ObjectType CObjectDetails::GetFunctionTakeOffPerformerObject()
{
    return OBJECT_BASE;
}

ObjectType CObjectDetails::GetFunctionReceivePerformerObject()
{
    return OBJECT_INFO;
}

ObjectType CObjectDetails::GetProduceContainer(ObjectType type)
{
    if (type == OBJECT_ANT   ||
        type == OBJECT_SPIDER ||
        type == OBJECT_BEE    ||
        type == OBJECT_WORM   ) return OBJECT_EGG;

    return OBJECT_NULL;
}

bool CObjectDetails::IsProduceAlreadyCharged(ObjectType type)
{
    return (type == OBJECT_POWER || type == OBJECT_ATOMIC);
}

bool CObjectDetails::IsProduceManual(ObjectType type)
{
    return (type == OBJECT_MOBILEdr);
}

bool CObjectDetails::IsFunctionImplementedBuild(ObjectType type)
{
    if ( type != OBJECT_MOBILEfb &&  // allowed only for builder bots && humans
         type != OBJECT_MOBILEtb &&
         type != OBJECT_MOBILEwb &&
         type != OBJECT_MOBILEib &&
         type != OBJECT_HUMAN    &&
         type != OBJECT_TECH      ) return false;
    return true;
}

bool CObjectDetails::IsFunctionImplementedFlags(ObjectType type)
{
    if ( type != OBJECT_MOBILEfs &&  // allowed only for sniffer bots && humans
         type != OBJECT_MOBILEts &&
         type != OBJECT_MOBILEws &&
         type != OBJECT_MOBILEis &&
         type != OBJECT_HUMAN    &&
         type != OBJECT_TECH      ) return false;
    return true;
}

bool CObjectDetails::IsFunctionImplementedShield(ObjectType type)
{
    return type == OBJECT_MOBILErs;
}

bool CObjectDetails::IsFunctionImplementedDrawAsRobot(ObjectType type)
{
    return type == OBJECT_MOBILEdr;
}

bool CObjectDetails::IsFunctionImplementedGrabAsHuman(ObjectType type)
{
    return type == OBJECT_HUMAN || type == OBJECT_TECH;
}

bool CObjectDetails::IsFunctionImplementedGrabAsRobot(ObjectType type)
{
    if ( (type == OBJECT_MOBILEfa ||
          type == OBJECT_MOBILEta ||
          type == OBJECT_MOBILEwa ||
          type == OBJECT_MOBILEia ) )   return true;

    if ( (type == OBJECT_MOBILEsa ||
          type == OBJECT_BEE ) )   return true;

    return false;
}

bool CObjectDetails::IsFunctionImplementedShootAsAnt(ObjectType type)
{
    return type == OBJECT_ANT;
}

bool CObjectDetails::IsFunctionImplementedShootAsSpider(ObjectType type)
{
    return type == OBJECT_SPIDER;
}

bool CObjectDetails::IsFunctionImplementedShootAsRobot(ObjectType type)
{
    return type == OBJECT_MOBILEdr;
}


bool CObjectDetails::IsValidObjectTypeId(ObjectType type)
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

bool CObjectDetails::IsNotPhysicalObject(ObjectType type)
{
    if ( type == OBJECT_TOTO ) return true;
    return false;
}

bool CObjectDetails::IsExplodesInWater(ObjectType type)
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

float CObjectDetails::GetCollisionOtherObjectRadiusToIgnore(ObjectType type)
{
    if ( type == OBJECT_MOTHER ) return 1.2f;
    if ( type == OBJECT_ANT    ) return 1.2f;
    if ( type == OBJECT_SPIDER ) return 1.2f;
    if ( type == OBJECT_BEE    ) return 1.2f;
    if ( type == OBJECT_WORM   ) return 1.2f;

    return 0.0f;
}

bool CObjectDetails::IsCollisionDamagable(ObjectType type)
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

float CObjectDetails::GetCollisionSoftness(ObjectType type)
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

float CObjectDetails::GetMaxSafeWaterLevel(ObjectType type)
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

bool CObjectDetails::IsExhaustBubblesOnEnteringWater(ObjectType type)
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

float CObjectDetails::IsExhaustBubblesOnEnteringWaterTime(ObjectType type)
{
    if ( type == OBJECT_HUMAN )  return 3.0f;
    return 8.0f;
}

bool CObjectDetails::IsExhaustDropsOnLeavingWater(ObjectType type)
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

bool CObjectDetails::IsExhaustOnCrashAsHuman(ObjectType type)
{
    if ( (type == OBJECT_HUMAN ||
          type == OBJECT_TECH  ) )   return true;
    return false;
}

bool CObjectDetails::IsExhaustOnCrashAsTrackedRobot(ObjectType type)
{
    if ((type == OBJECT_MOBILEta ||
         type == OBJECT_MOBILEtb ||
         type == OBJECT_MOBILEtc ||
         type == OBJECT_MOBILEti ||
         type == OBJECT_MOBILEts ||
         type == OBJECT_MOBILEtt  ) )   return true;
    return false;
}

bool CObjectDetails::IsExhaustOnCrashAsHeavyRobot(ObjectType type)
{
    if ((type == OBJECT_MOBILErt ||
         type == OBJECT_MOBILErc ||
         type == OBJECT_MOBILErr ||
         type == OBJECT_MOBILErs ||
         type == OBJECT_MOBILErp  ) )   return true;
    return false;
}

bool CObjectDetails::IsExhaustOnLandAsHuman(ObjectType type)
{
    if ( (type == OBJECT_HUMAN ||
          type == OBJECT_TECH  ) )   return true;
    return false;
}

bool CObjectDetails::IsExhaustOnLandAsWingedRobot(ObjectType type)
{
    if ((type == OBJECT_MOBILEfa ||
         type == OBJECT_MOBILEfb ||
         type == OBJECT_MOBILEfc ||
         type == OBJECT_MOBILEfi ||
         type == OBJECT_MOBILEfs ||
         type == OBJECT_MOBILEft  ) )   return true;
    return false;
}

bool CObjectDetails::IsExhaustOnFlightAsHuman(ObjectType type)
{
    if ( (type == OBJECT_HUMAN ||
          type == OBJECT_TECH  ) )   return true;
    return false;
}

bool  CObjectDetails::IsExhaustOnLandAsHeavyRobot(ObjectType type)
{
    if ((type == OBJECT_MOBILErt ||
         type == OBJECT_MOBILErc ||
         type == OBJECT_MOBILErr ||
         type == OBJECT_MOBILErs ||
         type == OBJECT_MOBILErp  ) )   return true;
    return false;
}

bool  CObjectDetails::IsExhaustOnLandAsNormalRobot(ObjectType type)
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

bool CObjectDetails::IsExhaustOnFlightAsWingedRobot(ObjectType type)
{
    if ((type == OBJECT_MOBILEwa ||
         type == OBJECT_MOBILEwb ||
         type == OBJECT_MOBILEwc ||
         type == OBJECT_MOBILEwi ||
         type == OBJECT_MOBILEws ||
         type == OBJECT_MOBILEwt  ) )   return true;
    return false;
}

bool CObjectDetails::IsExhaustOnSwimAsHuman(ObjectType type)
{
    if ( (type == OBJECT_HUMAN ||
          type == OBJECT_TECH  ) )   return true;
    return false;
}

bool CObjectDetails::IsExhaustOnSwimAsAmphibiousRobot(ObjectType type)
{
    if ( (type == OBJECT_MOBILEst ||
          type == OBJECT_MOBILEsa  ) )   return true;
    return false;
}

float CObjectDetails::GetWaterSplashLevelMin(ObjectType type)
{
    if ( (type == OBJECT_HUMAN ||
          type == OBJECT_TECH  ) )   return 3.0f;

    return 0.0f;
}

float CObjectDetails::GetWaterSplashLevelMax(ObjectType type)
{
    if ( (type == OBJECT_HUMAN ||
          type == OBJECT_TECH  ) )   return 3.0f;

    return 9.0f;
}

float CObjectDetails::GetWaterSplashDiameter(ObjectType type)
{
    if ( (type == OBJECT_HUMAN ||
          type == OBJECT_TECH  ) )   return 5.0f;

    return 2.5f;
}

float CObjectDetails::GetWaterSplashForce(ObjectType type)
{
    if ( (type == OBJECT_HUMAN ||
          type == OBJECT_TECH  ) )   return 1.0f;

    return 1.3f;
}

float CObjectDetails::GetLightningRodHeight(ObjectType type)
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

bool CObjectDetails::IsInterfaceDisableFlyWhileGrabbing(ObjectType type)
{
    if ( (type == OBJECT_HUMAN ||
          type == OBJECT_TECH  ) )   return true;

    return false;
}

bool CObjectDetails::GetInterfaceProgram(ObjectType type)
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

bool CObjectDetails::GetInterfaceProgramBlink(ObjectType type)
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

bool CObjectDetails::GetInterfaceGrabberHuman(ObjectType type)
{
    if ( (type == OBJECT_HUMAN ||
          type == OBJECT_TECH  ) )   return true;

    return false;
}

bool CObjectDetails::GetInterfaceFlaggerHuman(ObjectType type)
{
    if ( (type == OBJECT_HUMAN ||
          type == OBJECT_TECH  ) )   return true;

    return false;
}

bool CObjectDetails::GetInterfaceBuilderHuman(ObjectType type)
{
    if ( type == OBJECT_HUMAN )  return true;

    return false;
}

bool CObjectDetails::GetInterfaceGrabberRobotArm(ObjectType type)
{
    if ( (type == OBJECT_MOBILEfa ||
          type == OBJECT_MOBILEta ||
          type == OBJECT_MOBILEwa ||
          type == OBJECT_MOBILEia ) )   return true;

    return false;
}

bool CObjectDetails::GetInterfaceGrabberRobotSimple(ObjectType type)
{
    if ( (type == OBJECT_MOBILEsa ||
          type == OBJECT_BEE ) )   return true;

    return false;
}

bool CObjectDetails::GetInterfaceBuilderRobot(ObjectType type)
{
    if ( (type == OBJECT_MOBILEfb ||
          type == OBJECT_MOBILEtb ||
          type == OBJECT_MOBILEwb ||
          type == OBJECT_MOBILEib) )  return true;

    return false;
}

bool CObjectDetails::GetInterfaceSnifferRobot(ObjectType type)
{
    if ( (type == OBJECT_MOBILEfs ||
          type == OBJECT_MOBILEts ||
          type == OBJECT_MOBILEws ||
          type == OBJECT_MOBILEis ) )  return true;

    return false;
}

bool CObjectDetails::GetInterfaceFlaggerRobot(ObjectType type)
{
    if ( (type == OBJECT_MOBILEfs ||
          type == OBJECT_MOBILEts ||
          type == OBJECT_MOBILEws ||
          type == OBJECT_MOBILEis ) )  return true;

    return false;
}

bool CObjectDetails::GetInterfaceThumperRobot(ObjectType type)
{
    if ( (type == OBJECT_MOBILErt ) )  return true;

    return false;
}

bool CObjectDetails::GetInterfaceRecyclerRobot(ObjectType type)
{
    if ( (type == OBJECT_MOBILErr ) )  return true;

    return false;
}

bool CObjectDetails::GetInterfaceShielderRobot(ObjectType type)
{
    if ( (type == OBJECT_MOBILErs ) )  return true;

    return false;
}

bool CObjectDetails::GetInterfaceShooterRobot(ObjectType type)
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

bool CObjectDetails::GetInterfaceScribblerRobot(ObjectType type)
{
    if ( (type == OBJECT_MOBILEdr ) )  return true;

    return false;
}

bool CObjectDetails::GetInterfaceExploderAlien(ObjectType type)
{
    if ( (type == OBJECT_SPIDER ) )  return true;

    return false;
}

bool CObjectDetails::GetMapShowEvenUnselectable(ObjectType type)
{
    if ( type == OBJECT_MOTHER   ||
         type == OBJECT_ANT      ||
         type == OBJECT_SPIDER   ||
         type == OBJECT_BEE      ||
         type == OBJECT_WORM     ||
         type == OBJECT_MOBILEtg ) return true;

    return false;
}

MapColor CObjectDetails::GetMapIconColor(ObjectType type)
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

int CObjectDetails::GetMapIcon(ObjectType type)
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

bool CObjectDetails::IsShortcutBuilding(ObjectType type)
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

bool CObjectDetails::IsShortcutMovable(ObjectType type)
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

int CObjectDetails::GetShortcutIcon(ObjectType type)
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

bool CObjectDetails::IsDisplayedNameAsPlayer(ObjectType type)
{
    if ( type == OBJECT_HUMAN ) return true;

    return false;
}

std::string CObjectDetails::GetDisplayedName(ObjectType type)
{
    auto it = m_objects.find(type);
    if (it != m_objects.end())
        return it->second.displayedName;
    return "";
}
