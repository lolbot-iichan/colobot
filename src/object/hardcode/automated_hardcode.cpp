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

#include "level/research_type.h"

#include "object/object_type.h"

#include "object/details/automated_details.h"

#include "object/hardcode/automated_hardcode.h"

/* Macro to mark which texts are translatable by gettext
 * It doesn't do anything at compile-time, as all texts represented here are used later
 * in explicit call to gettext(), but it is used by xgettext executable to filter extracted
 * texts from this file.
 */
#define TR(x) x

/* Please run `cmake --build <path_to_build_folder> --target update-pot`
 * after changing this file in order to update translation files. Thank you.
 */

AutoClass CAutomatedHardcodeCollection::GetCreationAutoClass(ObjectType type)
{
    if ( type == OBJECT_FLAGb     ) return AUTO_CLASS_FLAG;
    if ( type == OBJECT_FLAGr     ) return AUTO_CLASS_FLAG;
    if ( type == OBJECT_FLAGg     ) return AUTO_CLASS_FLAG;
    if ( type == OBJECT_FLAGy     ) return AUTO_CLASS_FLAG;
    if ( type == OBJECT_FLAGv     ) return AUTO_CLASS_FLAG;

    if ( type == OBJECT_EGG       ) return AUTO_CLASS_EGG;
    if ( type == OBJECT_ROOT5     ) return AUTO_CLASS_ROOT;
    if ( type == OBJECT_MUSHROOM2 ) return AUTO_CLASS_MUSHROOM;

    if ( type == OBJECT_BASE      ) return AUTO_CLASS_BASE;
    if ( type == OBJECT_CONVERT   ) return AUTO_CLASS_CONVERT;
    if ( type == OBJECT_DERRICK   ) return AUTO_CLASS_DERRICK;
    if ( type == OBJECT_DESTROYER ) return AUTO_CLASS_DESTROYER;
    if ( type == OBJECT_FACTORY   ) return AUTO_CLASS_FACTORY;
    if ( type == OBJECT_HUSTON    ) return AUTO_CLASS_HUSTON;
    if ( type == OBJECT_LABO      ) return AUTO_CLASS_LABO;
    if ( type == OBJECT_NEST      ) return AUTO_CLASS_NEST;
    if ( type == OBJECT_NUCLEAR   ) return AUTO_CLASS_NUCLEARPLANT;
    if ( type == OBJECT_PORTICO   ) return AUTO_CLASS_PORTICO;
    if ( type == OBJECT_PARA      ) return AUTO_CLASS_POWERCAPTOR;
    if ( type == OBJECT_ENERGY    ) return AUTO_CLASS_POWERPLANT;
    if ( type == OBJECT_STATION   ) return AUTO_CLASS_POWERSTATION;
    if ( type == OBJECT_RADAR     ) return AUTO_CLASS_RADAR;
    if ( type == OBJECT_REPAIR    ) return AUTO_CLASS_REPAIR;
    if ( type == OBJECT_RESEARCH  ) return AUTO_CLASS_RESEARCH;
    if ( type == OBJECT_TOWER     ) return AUTO_CLASS_TOWER;
    if ( type == OBJECT_SAFE      ) return AUTO_CLASS_VAULT;

    if ( type == OBJECT_QUARTZ0   ) return AUTO_CLASS_QUARZ;
    if ( type == OBJECT_QUARTZ1   ) return AUTO_CLASS_QUARZ;
    if ( type == OBJECT_QUARTZ2   ) return AUTO_CLASS_QUARZ;
    if ( type == OBJECT_QUARTZ3   ) return AUTO_CLASS_QUARZ;

    if ( type == OBJECT_TEEN11    ) return AUTO_CLASS_TEEN_LAMP;    // lamp?
    if ( type == OBJECT_TEEN26    ) return AUTO_CLASS_TEEN_LAMP;    // ceiling lamp?
    if ( type == OBJECT_TEEN36    ) return AUTO_CLASS_TEEN_TRUNK;   // trunk?
    if ( type == OBJECT_TEEN37    ) return AUTO_CLASS_TEEN_BOAT;    // boat?
    if ( type == OBJECT_TEEN38    ) return AUTO_CLASS_TEEN_FAN;     // fan?

    if ( type == OBJECT_INFO      ) return AUTO_CLASS_INFO;

    if ( type == OBJECT_WORM      ) return AUTO_CLASS_WORM_INFECT;

    if ( type == OBJECT_MOBILEwi  ) return AUTO_CLASS_ORGA_CANNON;
    if ( type == OBJECT_MOBILEti  ) return AUTO_CLASS_ORGA_CANNON;
    if ( type == OBJECT_MOBILEfi  ) return AUTO_CLASS_ORGA_CANNON;
    if ( type == OBJECT_MOBILEii  ) return AUTO_CLASS_ORGA_CANNON;

    return AUTO_CLASS_NONE;
}


bool CAutomatedHardcodeCollection::IsBlockingBuilding(ObjectType type)
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

bool CAutomatedHardcodeCollection::IsAutoTargetedByTower(ObjectType type)
{
    if (type == OBJECT_ANT      ||
        type == OBJECT_SPIDER   ||
        type == OBJECT_BEE      ||
        type == OBJECT_WORM     ||
        type == OBJECT_MOTHER) return true;

     return false;
}

bool CAutomatedHardcodeCollection::IsAutoTargetedByMushroom(ObjectType type)
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

bool CAutomatedHardcodeCollection::IsAutoCommentedByAssistant(ObjectType type)
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

bool CAutomatedHardcodeCollection::IsAutoChargedAtPowerStation(ObjectType type)
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

bool CAutomatedHardcodeCollection::IsAutoBlockingPowerPlant(ObjectType type)
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

bool CAutomatedHardcodeCollection::IsAutoBlockingNuclearPlant(ObjectType type)
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

bool CAutomatedHardcodeCollection::IsAutoBlockingFactory(ObjectType type)
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

CObjectFactoryAutomatedDetails CAutomatedHardcodeCollection::GetFactory(ObjectType type)
{
    CObjectFactoryAutomatedDetails result;

    if (type == OBJECT_FACTORY)
    {
        result.objects.push_back({ OBJECT_METAL, OBJECT_MOBILEwt, TR("New bot available"), 0, {4.0f, 0.0f, 0.0f}, 0             });
        result.objects.push_back({ OBJECT_METAL, OBJECT_MOBILEtt, TR("New bot available"), 0, {4.0f, 0.0f, 0.0f}, RESEARCH_TANK });
        result.objects.push_back({ OBJECT_METAL, OBJECT_MOBILEft, TR("New bot available"), 0, {4.0f, 0.0f, 0.0f}, RESEARCH_FLY  });
        result.objects.push_back({ OBJECT_METAL, OBJECT_MOBILEit, TR("New bot available"), 0, {4.0f, 0.0f, 0.0f}, RESEARCH_iPAW });

        result.objects.push_back({ OBJECT_METAL, OBJECT_MOBILEwa, TR("New bot available"), 0, {4.0f, 0.0f, 0.0f}, 0             });
        result.objects.push_back({ OBJECT_METAL, OBJECT_MOBILEta, TR("New bot available"), 0, {4.0f, 0.0f, 0.0f}, RESEARCH_TANK });
        result.objects.push_back({ OBJECT_METAL, OBJECT_MOBILEfa, TR("New bot available"), 0, {4.0f, 0.0f, 0.0f}, RESEARCH_FLY  });
        result.objects.push_back({ OBJECT_METAL, OBJECT_MOBILEia, TR("New bot available"), 0, {4.0f, 0.0f, 0.0f}, RESEARCH_iPAW });
    
        result.objects.push_back({ OBJECT_METAL, OBJECT_MOBILEws, TR("New bot available"), 0, {4.0f, 0.0f, 0.0f}, RESEARCH_SNIFFER               });
        result.objects.push_back({ OBJECT_METAL, OBJECT_MOBILEts, TR("New bot available"), 0, {4.0f, 0.0f, 0.0f}, RESEARCH_SNIFFER|RESEARCH_TANK });
        result.objects.push_back({ OBJECT_METAL, OBJECT_MOBILEfs, TR("New bot available"), 0, {4.0f, 0.0f, 0.0f}, RESEARCH_SNIFFER|RESEARCH_FLY  });
        result.objects.push_back({ OBJECT_METAL, OBJECT_MOBILEis, TR("New bot available"), 0, {4.0f, 0.0f, 0.0f}, RESEARCH_SNIFFER|RESEARCH_iPAW });
    
        result.objects.push_back({ OBJECT_METAL, OBJECT_MOBILEwc, TR("New bot available"), 0, {4.0f, 0.0f, 0.0f}, RESEARCH_CANON               });
        result.objects.push_back({ OBJECT_METAL, OBJECT_MOBILEtc, TR("New bot available"), 0, {4.0f, 0.0f, 0.0f}, RESEARCH_CANON|RESEARCH_TANK });
        result.objects.push_back({ OBJECT_METAL, OBJECT_MOBILEfc, TR("New bot available"), 0, {4.0f, 0.0f, 0.0f}, RESEARCH_CANON|RESEARCH_FLY  });
        result.objects.push_back({ OBJECT_METAL, OBJECT_MOBILEic, TR("New bot available"), 0, {4.0f, 0.0f, 0.0f}, RESEARCH_CANON|RESEARCH_iPAW });
    
        result.objects.push_back({ OBJECT_METAL, OBJECT_MOBILEwi, TR("New bot available"), 0, {4.0f, 0.0f, 0.0f}, RESEARCH_iGUN               });
        result.objects.push_back({ OBJECT_METAL, OBJECT_MOBILEti, TR("New bot available"), 0, {4.0f, 0.0f, 0.0f}, RESEARCH_iGUN|RESEARCH_TANK });
        result.objects.push_back({ OBJECT_METAL, OBJECT_MOBILEfi, TR("New bot available"), 0, {4.0f, 0.0f, 0.0f}, RESEARCH_iGUN|RESEARCH_FLY  });
        result.objects.push_back({ OBJECT_METAL, OBJECT_MOBILEii, TR("New bot available"), 0, {4.0f, 0.0f, 0.0f}, RESEARCH_iGUN|RESEARCH_iPAW });
    
        result.objects.push_back({ OBJECT_METAL, OBJECT_MOBILEwb, TR("New bot available"), 0, {4.0f, 0.0f, 0.0f}, RESEARCH_BUILDER               });
        result.objects.push_back({ OBJECT_METAL, OBJECT_MOBILEtb, TR("New bot available"), 0, {4.0f, 0.0f, 0.0f}, RESEARCH_BUILDER|RESEARCH_TANK });
        result.objects.push_back({ OBJECT_METAL, OBJECT_MOBILEfb, TR("New bot available"), 0, {4.0f, 0.0f, 0.0f}, RESEARCH_BUILDER|RESEARCH_FLY  });
        result.objects.push_back({ OBJECT_METAL, OBJECT_MOBILEib, TR("New bot available"), 0, {4.0f, 0.0f, 0.0f}, RESEARCH_BUILDER|RESEARCH_iPAW });
    
        result.objects.push_back({ OBJECT_METAL, OBJECT_MOBILErp, TR("New bot available"), 0, {4.0f, 0.0f, 0.0f}, RESEARCH_TANK });
        result.objects.push_back({ OBJECT_METAL, OBJECT_MOBILErt, TR("New bot available"), 0, {2.0f, 0.0f, 0.0f}, RESEARCH_TANK|RESEARCH_THUMP    });
        result.objects.push_back({ OBJECT_METAL, OBJECT_MOBILErc, TR("New bot available"), 0, {2.0f, 0.0f, 0.0f}, RESEARCH_TANK|RESEARCH_PHAZER   });
        result.objects.push_back({ OBJECT_METAL, OBJECT_MOBILErr, TR("New bot available"), 0, {2.0f, 0.0f, 0.0f}, RESEARCH_TANK|RESEARCH_RECYCLER });
        result.objects.push_back({ OBJECT_METAL, OBJECT_MOBILErs, TR("New bot available"), 0, {2.0f, 0.0f, 0.0f}, RESEARCH_TANK|RESEARCH_SHIELD   });
    
        result.objects.push_back({ OBJECT_METAL, OBJECT_MOBILEsa, TR("New bot available"), 0, {4.0f, 0.0f, 0.0f}, RESEARCH_SUBM });
        result.objects.push_back({ OBJECT_METAL, OBJECT_MOBILEst, TR("New bot available"), 0, {4.0f, 0.0f, 0.0f}, RESEARCH_SUBM });

        result.objects.push_back({ OBJECT_METAL, OBJECT_MOBILEtg, TR("New bot available"), 0, {4.0f, 0.0f, 0.0f}, RESEARCH_TARGET });

        result.objects.push_back({ OBJECT_METAL, OBJECT_MOBILEdr, TR("New bot available"), 0, {4.0f, 0.0f, 0.0f}, 0 });
    }

    return result;
}

CObjectEggAutomatedDetails CAutomatedHardcodeCollection::GetEgg(ObjectType type)
{
    CObjectEggAutomatedDetails result;

    if ( type == OBJECT_EGG )
    {
        result = {""};
        result.objects.push_back({OBJECT_ANT,    5.0f, 0.2f,  1.0f,  ""});
        result.objects.push_back({OBJECT_BEE,    5.0f, 0.2f,  1.0f,  ""});
        result.objects.push_back({OBJECT_SPIDER, 5.0f, 0.2f,  1.0f,  ""});
        result.objects.push_back({OBJECT_WORM,   5.0f, 0.01f, 0.01f, ""});
    }

    return result;
}

CObjectDiggingAutomatedDetails CAutomatedHardcodeCollection::GetDigging(ObjectType type)
{
    CObjectDiggingAutomatedDetails result;

    if ( type == OBJECT_DERRICK )
    {
        result = {TR("No ore in the subsoil"), 0, glm::vec3(7.0f, 0.0f, 0.0f)};
        result.objects.push_back({Gfx::TR_STONE,   OBJECT_STONE,   -1, 10.0f, ""});
        result.objects.push_back({Gfx::TR_URANIUM, OBJECT_URANIUM, -1, 30.0f, ""});
        result.objects.push_back({Gfx::TR_KEY_A,   OBJECT_KEYa,     1, 10.0f, ""});
        result.objects.push_back({Gfx::TR_KEY_B,   OBJECT_KEYb,     1, 10.0f, ""});
        result.objects.push_back({Gfx::TR_KEY_C,   OBJECT_KEYc,     1, 10.0f, ""});
        result.objects.push_back({Gfx::TR_KEY_D,   OBJECT_KEYd,     1, 10.0f, ""});
    }
    if ( type == OBJECT_NEST )
    {
        result = {"", 0, glm::vec3(0.0f, 0.0f, 0.0f)};
        result.objects.push_back({Gfx::TR_ANY,     OBJECT_BULLET,  -1,  5.0f, ""});
    }

    return result;
}

CObjectProductionAutomatedDetails CAutomatedHardcodeCollection::GetProduction(ObjectType type)
{
    CObjectProductionAutomatedDetails result;

    if ( type == OBJECT_CONVERT )
    {
        result = {TR("No titanium ore to convert"), ""};
        result.objects.push_back({OBJECT_STONE,   OBJECT_METAL,  TR("Titanium available")});
    }
    if ( type == OBJECT_ENERGY )
    {
        result = {TR("No titanium to transform"), TR("Transforms only titanium")};
        result.objects.push_back({OBJECT_METAL,   OBJECT_POWER,  TR("Power cell available")});
    }
    if ( type == OBJECT_NUCLEAR )
    {
        result = {TR("No uranium to transform"), TR("Transforms only uranium")};
        result.objects.push_back({OBJECT_URANIUM, OBJECT_ATOMIC, TR("Nuclear power cell available")});
    }

    return result;
}

CObjectVaultAutomatedDetails CAutomatedHardcodeCollection::GetVault(ObjectType type)
{
    CObjectVaultAutomatedDetails result;

    if ( type == OBJECT_SAFE )
    {
        result.keys.push_back({OBJECT_KEYa, 0});
        result.keys.push_back({OBJECT_KEYb, 1});
        result.keys.push_back({OBJECT_KEYc, 2});
        result.keys.push_back({OBJECT_KEYd, 3});

        result.doors.push_back({0, 1, glm::vec3(), glm::vec3({0.0f, 0.0f,   0.0f*Math::PI/180.0f})});
        result.doors.push_back({0, 2, glm::vec3(), glm::vec3({0.0f, 0.0f,  -0.0f*Math::PI/180.0f})});
        result.doors.push_back({1, 1, glm::vec3(), glm::vec3({0.0f, 0.0f,   5.0f*Math::PI/180.0f})});
        result.doors.push_back({1, 2, glm::vec3(), glm::vec3({0.0f, 0.0f,  -5.0f*Math::PI/180.0f})});
        result.doors.push_back({2, 1, glm::vec3(), glm::vec3({0.0f, 0.0f,  10.0f*Math::PI/180.0f})});
        result.doors.push_back({2, 2, glm::vec3(), glm::vec3({0.0f, 0.0f, -10.0f*Math::PI/180.0f})});
        result.doors.push_back({3, 1, glm::vec3(), glm::vec3({0.0f, 0.0f,  15.0f*Math::PI/180.0f})});
        result.doors.push_back({3, 2, glm::vec3(), glm::vec3({0.0f, 0.0f, -15.0f*Math::PI/180.0f})});
        result.doors.push_back({4, 1, glm::vec3(), glm::vec3({0.0f, 0.0f, 120.0f*Math::PI/180.0f})});
        result.doors.push_back({4, 2, glm::vec3(), glm::vec3({0.0f, 0.0f,-120.0f*Math::PI/180.0f})});
    }
    
    return result;
}

CObjectQuarzAutomatedDetails CAutomatedHardcodeCollection::GetQuarz(ObjectType type)
{
    if ( type == OBJECT_QUARTZ0 )
        return {2, 0, {0.0f, 4.0f, 0.0f}, 2.0f};

    if ( type == OBJECT_QUARTZ1 )
        return {2, 0, {0.0f, 6.0f, 0.0f}, 4.0f};

    if ( type == OBJECT_QUARTZ2 )
        return {2, 0, {0.0f,10.0f, 0.0f}, 5.0f};

    if ( type == OBJECT_QUARTZ3 )
        return {2, 0, {0.0f,16.0f, 0.0f}, 8.0f};
    
    return CObjectQuarzAutomatedDetails();
}

CObjectLampAutomatedDetails CAutomatedHardcodeCollection::GetLamp(ObjectType type)
{
    if ( type == OBJECT_TEEN11 )
        return {{0, {-56.0f, 22.0f, 0.0f}, 20.0f}, {0, {-65.0f, 40.0f, 0.0f}, Gfx::Color(4.0f, 2.0f, 0.0f, 0.0f)}};

    if ( type == OBJECT_TEEN26 )
        return {{0, {0.0f, 50.0f, 0.0f}, 100.0f}, {0, {0.0f, 50.0f, 0.0f}, Gfx::Color(4.0f, 2.0f, 0.0f, 0.0f)}};
    
    return CObjectLampAutomatedDetails();
}

