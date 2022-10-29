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

#include "math/const.h"
#include "math/geometry.h"

#include "graphics/core/color.h"

#include "object/object_type.h"

#include "object/details/modeled_details.h"

#include "object/hardcode/modeled_hardcode.h"

const float ARM_NEUTRAL_ANGLE1 = 110.0f*Math::PI/180.0f;
const float ARM_NEUTRAL_ANGLE2 = -130.0f*Math::PI/180.0f;
const float ARM_NEUTRAL_ANGLE3 = -50.0f*Math::PI/180.0f;

/* Macro to mark which texts are translatable by gettext
 * It doesn't do anything at compile-time, as all texts represented here are used later
 * in explicit call to gettext(), but it is used by xgettext executable to filter extracted
 * texts from this file.
 */
#define TR(x) x

/* Please run `cmake --build <path_to_build_folder> --target update-pot`
 * after changing this file in order to update translation files. Thank you.
 */

std::string CModeledHardcodeCollection::GetDisplayedName(ObjectType type)
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

std::vector<CObjectModeledNode> CModeledHardcodeCollection::GetModel(ObjectType type)
{
    std::vector<CObjectModeledNode> result;

    std::string name;
    if ( type == OBJECT_STONE       )  name = "stone";
    if ( type == OBJECT_URANIUM     )  name = "uranium";
    if ( type == OBJECT_METAL       )  name = "metal";
    if ( type == OBJECT_BULLET      )  name = "bullet";
    if ( type == OBJECT_BBOX        )  name = "bbox";
    if ( type == OBJECT_KEYa        )  name = "keya";
    if ( type == OBJECT_KEYb        )  name = "keyb";
    if ( type == OBJECT_KEYc        )  name = "keyc";
    if ( type == OBJECT_KEYd        )  name = "keyd";
    if ( type == OBJECT_TNT         )  name = "tnt";
    if ( type == OBJECT_BOMB        )  name = "bomb";
    if ( type == OBJECT_WAYPOINT    )  name = "waypoint";
    if ( type == OBJECT_SHOW        )  name = "show";
    if ( type == OBJECT_WINFIRE     )  name = "winfire";
    if ( type == OBJECT_MARKSTONE   )  name = "cross1";
    if ( type == OBJECT_MARKURANIUM )  name = "cross3";
    if ( type == OBJECT_MARKPOWER   )  name = "cross2";
    if ( type == OBJECT_MARKKEYa    )  name = "crossa";
    if ( type == OBJECT_MARKKEYb    )  name = "crossb";
    if ( type == OBJECT_MARKKEYc    )  name = "crossc";
    if ( type == OBJECT_MARKKEYd    )  name = "crossd";
    if ( name.size() > 0 )
    {
        result.push_back({0, -1, Gfx::ENG_OBJTYPE_FIX, name});
        return result;
    }

    if ( type == OBJECT_BAG         )  name = "bag";
    if ( type == OBJECT_EGG         )  name = "egg";
    if ( name.size() > 0 )
    {
        result.push_back({0, -1, Gfx::ENG_OBJTYPE_FIX, name, glm::vec3(0.0f, -1.4f, 0.0f)});
        return result;
    }

    if ( type == OBJECT_POWER       )  name = "power";
    if ( type == OBJECT_ATOMIC      )  name = "atomic";
    if ( name.size() > 0 )
    {
        result.push_back({0, -1, Gfx::ENG_OBJTYPE_FIX, name, glm::vec3(), glm::vec3(), glm::vec3(1.0f, 1.0f, 1.0f), false, true});
        return result;
    }

    if ( type == OBJECT_FLAGb )  name = "flag1b";
    if ( type == OBJECT_FLAGr )  name = "flag1r";
    if ( type == OBJECT_FLAGg )  name = "flag1g";
    if ( type == OBJECT_FLAGy )  name = "flag1y";
    if ( type == OBJECT_FLAGv )  name = "flag1v";
    if ( name.size() > 0 )
    {
        result.push_back({0, -1, Gfx::ENG_OBJTYPE_FIX, name});
    }
    if ( type == OBJECT_FLAGb )  name = "flag2b";
    if ( type == OBJECT_FLAGr )  name = "flag2r";
    if ( type == OBJECT_FLAGg )  name = "flag2g";
    if ( type == OBJECT_FLAGy )  name = "flag2y";
    if ( type == OBJECT_FLAGv )  name = "flag2v";
    if ( name.size() > 0 )
    {
        result.push_back({1, 0, Gfx::ENG_OBJTYPE_DESCENDANT, name, glm::vec3(0.15f, 5.0f, 0.0f)});
        result.push_back({2, 1, Gfx::ENG_OBJTYPE_DESCENDANT, name, glm::vec3(0.79f, 0.0f, 0.0f)});
        result.push_back({3, 2, Gfx::ENG_OBJTYPE_DESCENDANT, name, glm::vec3(0.79f, 0.0f, 0.0f)});
        result.push_back({4, 3, Gfx::ENG_OBJTYPE_DESCENDANT, name, glm::vec3(0.79f, 0.0f, 0.0f)});
        return result;
    }

    if ( type == OBJECT_BARRIER0 ) name = "barrier0";
    if ( type == OBJECT_BARRIER1 ) name = "barrier1";
    if ( type == OBJECT_BARRIER2 ) name = "barrier2";
    if ( type == OBJECT_BARRIER3 ) name = "barrier3";
    if ( type == OBJECT_BARRICADE0 ) name = "barricade0";
    if ( type == OBJECT_BARRICADE1 ) name = "barricade1";
    if ( name.size() > 0 )
    {
        result.push_back({0, -1, Gfx::ENG_OBJTYPE_FIX, name});
        return result;
    }

    if ( type == OBJECT_PLANT0 ) name = "plant0";
    if ( type == OBJECT_PLANT1 ) name = "plant1";
    if ( type == OBJECT_PLANT2 ) name = "plant2";
    if ( type == OBJECT_PLANT3 ) name = "plant3";
    if ( type == OBJECT_PLANT4 ) name = "plant4";
    if ( name.size() > 0 )
    {
        result.push_back({0, -1, Gfx::ENG_OBJTYPE_FIX, name, glm::vec3(0.0f, -2.0f, 0.0f)});
        return result;
    }

    if ( type == OBJECT_PLANT5 ) name = "plant5";
    if ( type == OBJECT_PLANT6 ) name = "plant6";
    if ( type == OBJECT_PLANT7 ) name = "plant7";
    if ( type == OBJECT_PLANT8 ) name = "plant8";
    if ( type == OBJECT_PLANT9 ) name = "plant9";
    if ( type == OBJECT_PLANT10 ) name = "plant10";
    if ( type == OBJECT_PLANT11 ) name = "plant11";
    if ( type == OBJECT_PLANT12 ) name = "plant12";
    if ( type == OBJECT_PLANT13 ) name = "plant13";
    if ( type == OBJECT_PLANT14 ) name = "plant14";
    if ( type == OBJECT_PLANT15 ) name = "plant15";
    if ( type == OBJECT_PLANT16 ) name = "plant16";
    if ( type == OBJECT_PLANT17 ) name = "plant17";
    if ( type == OBJECT_PLANT18 ) name = "plant18";
    if ( type == OBJECT_PLANT19 ) name = "plant19";
    if ( type == OBJECT_TREE0 ) name = "tree0";
    if ( type == OBJECT_TREE1 ) name = "tree1";
    if ( type == OBJECT_TREE2 ) name = "tree2";
    if ( type == OBJECT_TREE3 ) name = "tree3";
    if ( type == OBJECT_TREE4 ) name = "tree4";
    if ( type == OBJECT_TREE5 ) name = "tree5";
    if ( name.size() > 0 )
    {
        result.push_back({0, -1, Gfx::ENG_OBJTYPE_FIX, name});
        return result;
    }

    if ( type == OBJECT_MUSHROOM1 ) name = "mush1";
    if ( type == OBJECT_MUSHROOM2 ) name = "mush2";
    if ( name.size() > 0 )
    {
        result.push_back({0, -1, Gfx::ENG_OBJTYPE_FIX, name});
        return result;
    }

    if ( type == OBJECT_TEEN0 ) name = "teen0";
    if ( type == OBJECT_TEEN1 ) name = "teen1";
    if ( type == OBJECT_TEEN2 ) name = "teen2";
    if ( type == OBJECT_TEEN4 ) name = "teen4";
    if ( type == OBJECT_TEEN5 ) name = "teen5";
    if ( type == OBJECT_TEEN6 ) name = "teen6";
    if ( type == OBJECT_TEEN7 ) name = "teen7";
    if ( type == OBJECT_TEEN8 ) name = "teen8";
    if ( type == OBJECT_TEEN9 ) name = "teen9";
    if ( type == OBJECT_TEEN10 ) name = "teen10";
    if ( type == OBJECT_TEEN11 ) name = "teen11";
    if ( type == OBJECT_TEEN13 ) name = "teen13";
    if ( type == OBJECT_TEEN14 ) name = "teen14";
    if ( type == OBJECT_TEEN15 ) name = "teen15";
    if ( type == OBJECT_TEEN16 ) name = "teen16";
    if ( type == OBJECT_TEEN17 ) name = "teen17";
    if ( type == OBJECT_TEEN18 ) name = "teen18";
    if ( type == OBJECT_TEEN19 ) name = "teen19";
    if ( type == OBJECT_TEEN20 ) name = "teen20";
    if ( type == OBJECT_TEEN21 ) name = "teen21";
    if ( type == OBJECT_TEEN22 ) name = "teen22";
    if ( type == OBJECT_TEEN23 ) name = "teen23";
    if ( type == OBJECT_TEEN24 ) name = "teen24";
    if ( type == OBJECT_TEEN25 ) name = "teen25";
    if ( type == OBJECT_TEEN26 ) name = "teen26";
    if ( type == OBJECT_TEEN27 ) name = "teen27";
    if ( type == OBJECT_TEEN29 ) name = "teen29";
    if ( type == OBJECT_TEEN30 ) name = "teen30";
    if ( type == OBJECT_TEEN31 ) name = "teen31";
    if ( type == OBJECT_TEEN32 ) name = "teen32";
    if ( type == OBJECT_TEEN33 ) name = "teen33";
    if ( type == OBJECT_TEEN34 ) name = "teen34";
    if ( type == OBJECT_TEEN35 ) name = "teen35";
    if ( type == OBJECT_TEEN36 ) name = "teen36";
    if ( type == OBJECT_TEEN37 ) name = "teen37";
    if ( type == OBJECT_TEEN39 ) name = "teen39";
    if ( type == OBJECT_TEEN40 ) name = "teen40";
    if ( type == OBJECT_TEEN41 ) name = "teen41";
    if ( type == OBJECT_TEEN42 ) name = "teen42";
    if ( type == OBJECT_TEEN43 ) name = "teen43";
    if ( type == OBJECT_TEEN44 ) name = "teen44";
    if ( name.size() > 0 )
    {
        result.push_back({0, -1, Gfx::ENG_OBJTYPE_FIX, name});
        return result;
    }

    if ( type == OBJECT_TEEN3 )  name = "teen3";
    if ( type == OBJECT_TEEN12 ) name = "teen12";
    if ( type == OBJECT_TEEN28 ) name = "teen28";
    if ( name.size() > 0 )
    {
        result.push_back({0, -1, Gfx::ENG_OBJTYPE_METAL, name});
        return result;
    }

    if ( type == OBJECT_TEEN38 )
    {
        result.push_back({0, -1, Gfx::ENG_OBJTYPE_FIX,        "teen38a"});
        result.push_back({1,  0, Gfx::ENG_OBJTYPE_DESCENDANT, "teen38b", glm::vec3(0.0f, 30.0f, 0.0f)}); // engine
        result.push_back({2,  1, Gfx::ENG_OBJTYPE_DESCENDANT, "teen38c"});  // propeller
        return result;
    }

    if ( type == OBJECT_QUARTZ0 ) name = "quartz0";
    if ( type == OBJECT_QUARTZ1 ) name = "quartz1";
    if ( type == OBJECT_QUARTZ2 ) name = "quartz2";
    if ( type == OBJECT_QUARTZ3 ) name = "quartz3";
    if ( name.size() > 0 )
    {
        result.push_back({0, -1, Gfx::ENG_OBJTYPE_QUARTZ, name});
        return result;
    }


    if ( type == OBJECT_ROOT0 ) name = "root0";
    if ( type == OBJECT_ROOT1 ) name = "root1";
    if ( type == OBJECT_ROOT2 ) name = "root2";
    if ( type == OBJECT_ROOT3 ) name = "root3";
    if ( type == OBJECT_ROOT4 ) name = "root4";
    if ( type == OBJECT_HOME1 ) name = "home1";
    if ( name.size() > 0 )
    {
        result.push_back({0, -1, Gfx::ENG_OBJTYPE_FIX, name});
        return result;
    }

    if ( type == OBJECT_ROOT5 )
    {
        result.push_back({0, -1, Gfx::ENG_OBJTYPE_FIX,        "root4"});
        result.push_back({1,  0, Gfx::ENG_OBJTYPE_DESCENDANT, "root5", glm::vec3(-5.0f, 28.0f, -4.0f), glm::vec3(-30.0f*Math::PI/180.0f, 0.0f, 20.0f*Math::PI/180.0f)});
        return result;
    }

    if ( type == OBJECT_RUINmobilew1 )  // vehicle had wheels?
    {
        result.push_back({0, -1, Gfx::ENG_OBJTYPE_FIX,        "ruin1",  glm::vec3( 0.0f, -0.5f, 0.0f), glm::vec3(-0.1f, 0.0f, 0.0f)});
        result.push_back({6,  0, Gfx::ENG_OBJTYPE_DESCENDANT, "ruin1w", glm::vec3(-3.0f, 1.8f, -4.0f), glm::vec3(-Math::PI/2.0f, 0.0f, 0.0f)}); // Creates the right-back wheel
        result.push_back({7,  0, Gfx::ENG_OBJTYPE_DESCENDANT, "ruin1w", glm::vec3(-3.0f, 1.0f,  3.0f), glm::vec3(-0.3f, Math::PI-0.3f, 0.0f)}); // Creates the left-back wheel
        result.push_back({8,  0, Gfx::ENG_OBJTYPE_DESCENDANT, "ruin1w", glm::vec3( 2.0f, 1.6f, -3.0f), glm::vec3(0.0f, 0.3f, 0.0f)}); // Creates the right-front wheel
        result.push_back({9,  0, Gfx::ENG_OBJTYPE_DESCENDANT, "ruin1w", glm::vec3( 2.0f, 1.0f,  3.0f), glm::vec3(0.2f, Math::PI-0.2f, 0.0f)}); // Creates the left-front wheel
        return result;
    }

    if ( type == OBJECT_RUINmobilew2 )  // vehicle had wheels?
    {
        result.push_back({0, -1, Gfx::ENG_OBJTYPE_FIX,        "ruin1",  glm::vec3(0.0f, -1.5f, 0.0f),  glm::vec3(-0.9f, 0.0f, 0.1f)});
        result.push_back({7,  0, Gfx::ENG_OBJTYPE_DESCENDANT, "ruin1w", glm::vec3(-3.0f, 1.0f, 3.0f),  glm::vec3(0.4f, Math::PI+0.3f, 0.0f)}); // Creates the left-back wheel
        result.push_back({9,  0, Gfx::ENG_OBJTYPE_DESCENDANT, "ruin1w", glm::vec3(2.0f, 1.0f, 3.0f),   glm::vec3(-0.3f, Math::PI+0.3f, 0.0f)}); // Creates the left-front wheel
        return result;
    }

    if ( type == OBJECT_RUINmobilet1 )  // vehicle had wheels?
    {
        result.push_back({0, -1, Gfx::ENG_OBJTYPE_FIX,        "ruin2",  glm::vec3(0.0f, -0.9f, 0.0f),  glm::vec3(-0.3f, 0.0f, 0.0f)});
        result.push_back({1,  0, Gfx::ENG_OBJTYPE_DESCENDANT, "ruin2c", glm::vec3(3.0f, 5.0f, -2.5f),  glm::vec3(-Math::PI*0.85f, -0.4f, -0.1f)}); // Creates the left track
        return result;
    }

    if ( type == OBJECT_RUINmobilet2 )
    {
        result.push_back({0, -1, Gfx::ENG_OBJTYPE_FIX, "ruin2", glm::vec3(0.0f, -1.5f, 0.0f), glm::vec3(-0.3f, 0.0f, 0.8f)});
        return result;
    }

    if ( type == OBJECT_RUINmobiler1 )
    {
        result.push_back({0, -1, Gfx::ENG_OBJTYPE_FIX, "ruin3", glm::vec3(0.0f, 4.0f, 0.0f), glm::vec3(-Math::PI*0.6f, 0.0f, -0.2f)});
        return result;
    }

    if ( type == OBJECT_RUINmobiler2 )
    {
        result.push_back({0, -1, Gfx::ENG_OBJTYPE_FIX, "ruin3", glm::vec3(0.0f, 2.0f, 0.0f), glm::vec3(-0.1f, 0.0f, -0.3f)});
        return result;
    }

    if ( type == OBJECT_RUINfactory  )
    {
        result.push_back({0, -1, Gfx::ENG_OBJTYPE_FIX, "ruin4"});
        return result;
    }

    if ( type == OBJECT_RUINdoor     )
    {
        result.push_back({0, -1, Gfx::ENG_OBJTYPE_FIX, "ruin5", glm::vec3(0.0f, -0.5f, 0.0f), glm::vec3(0.1f, 0.0f, -0.1f)});
        return result;
    }

    if ( type == OBJECT_RUINsupport  )
    {
        result.push_back({0, -1, Gfx::ENG_OBJTYPE_FIX, "ruin6", glm::vec3(0.0f, 0.5f, 0.0f), glm::vec3(0.1f, 0.0f, 0.1f)});
        return result;
    }

    if ( type == OBJECT_RUINradar    )
    {
        result.push_back({0, -1, Gfx::ENG_OBJTYPE_FIX, "ruin7", glm::vec3(0.0f, -0.5f, 0.0f), glm::vec3(0.15f, 0.0f, 0.1f)});
        return result;
    }

    if ( type == OBJECT_RUINconvert  )
    {
        result.push_back({0, -1, Gfx::ENG_OBJTYPE_FIX, "ruin8"});
        return result;
    }

    if ( type == OBJECT_RUINbase     )
    {
        result.push_back({0, -1, Gfx::ENG_OBJTYPE_FIX, "ruin9", glm::vec3(0.0f, -1.0f, 0.0f), glm::vec3(0.15f, 0.0f, 0.0f)});
        return result;
    }

    if ( type == OBJECT_RUINhead     )
    {
        result.push_back({0, -1, Gfx::ENG_OBJTYPE_FIX, "ruin10", glm::vec3(0.0f, 8.0f, 0.0f), glm::vec3(Math::PI*0.4f, 0.0f, 0.0f)});
        return result;
    }

    if ( type == OBJECT_APOLLO1 )
    {
        result.push_back({0, -1, Gfx::ENG_OBJTYPE_FIX,        "apollol1"});
        for (int i=0 ; i<4 ; i++ )  // creates feet
            result.push_back({i+1,  0, Gfx::ENG_OBJTYPE_DESCENDANT, "apollol2", glm::vec3(),  glm::vec3(0.0f, Math::PI/2.0f*i, 0)});
        result.push_back({5,  0, Gfx::ENG_OBJTYPE_DESCENDANT, "apollol3"}); // ladder
        return result;
    }

    if ( type == OBJECT_APOLLO3 ) name ="apollof"; // flag?
    if ( type == OBJECT_APOLLO4 ) name ="apollom"; // module?
    if ( name.size() > 0 )
    {
        result.push_back({0, -1, Gfx::ENG_OBJTYPE_FIX, name});
        return result;
    }

    if ( type == OBJECT_APOLLO5 )  // antenna?
    {
        result.push_back({0, -1, Gfx::ENG_OBJTYPE_FIX,        "apolloa"});
        result.push_back({1,  0, Gfx::ENG_OBJTYPE_DESCENDANT, "apolloj2", glm::vec3(0.0f, 5.0f, 0.0f),  glm::vec3(0, -120.0f*Math::PI/180.0f, 45.0f*Math::PI/180.0f)});
        return result;
    }

    if ( type == OBJECT_CONTROLLER )
    {
        /*no model*/
        return result;
    }

    if ( type == OBJECT_PORTICO )
    {
        result.push_back({0, -1, Gfx::ENG_OBJTYPE_FIX,        "portico1"});
        result.push_back({1,  0, Gfx::ENG_OBJTYPE_DESCENDANT, "portico2", glm::vec3(0.0f, 67.0f, 0.0f)});
        result.push_back({2,  1, Gfx::ENG_OBJTYPE_DESCENDANT, "portico3", glm::vec3(0.0f, 0.0f, -33.0f), glm::vec3(0.0f,  45.0f*Math::PI/180.0f, 0.0f)});
        result.push_back({3,  2, Gfx::ENG_OBJTYPE_DESCENDANT, "portico4", glm::vec3(50.0f, 0.0f, 0.0f),  glm::vec3(0.0f, -60.0f*Math::PI/180.0f, 0.0f)});
        result.push_back({4,  3, Gfx::ENG_OBJTYPE_DESCENDANT, "portico5", glm::vec3(35.0f, 0.0f, 0.0f),  glm::vec3(0.0f, -55.0f*Math::PI/180.0f, 0.0f)});
        result.push_back({5,  1, Gfx::ENG_OBJTYPE_DESCENDANT, "portico3", glm::vec3(0.0f, 0.0f, 33.0f),  glm::vec3(0.0f, -45.0f*Math::PI/180.0f, 0.0f)});
        result.push_back({6,  5, Gfx::ENG_OBJTYPE_DESCENDANT, "portico4", glm::vec3(50.0f, 0.0f, 0.0f),  glm::vec3(0.0f,  60.0f*Math::PI/180.0f, 0.0f)});
        result.push_back({7,  6, Gfx::ENG_OBJTYPE_DESCENDANT, "portico5", glm::vec3(35.0f, 0.0f, 0.0f),  glm::vec3(0.0f,  55.0f*Math::PI/180.0f, 0.0f)});
        result.push_back({8,  0, Gfx::ENG_OBJTYPE_DESCENDANT, "portico6", glm::vec3(-35.0f, 50.0f, -35.0f), glm::vec3(0.0f, -Math::PI/2.0f, 0.0f), glm::vec3(2.0f, 2.0f, 2.0f)});
        result.push_back({9,  8, Gfx::ENG_OBJTYPE_DESCENDANT, "portico7", glm::vec3(0.0f, 4.5f, 1.9f)});
        result.push_back({10, 0, Gfx::ENG_OBJTYPE_DESCENDANT, "portico6", glm::vec3(-35.0f, 50.0f,  35.0f), glm::vec3(0.0f, -Math::PI/2.0f, 0.0f), glm::vec3(2.0f, 2.0f, 2.0f)});
        result.push_back({11,10, Gfx::ENG_OBJTYPE_DESCENDANT, "portico7", glm::vec3(0.0f, 4.5f, 1.9f)});
        return result;
    }

    if ( type == OBJECT_BASE )
    {
        result.push_back({0, -1, Gfx::ENG_OBJTYPE_FIX,        "base1"});
        for (int i=0 ; i<8 ; i++ )
        {
            glm::vec2 p = Math::RotatePoint(-Math::PI/4.0f*i, 27.8f);
            result.push_back({1+i,   0, Gfx::ENG_OBJTYPE_DESCENDANT, "base2", glm::vec3(p.x, 30.0f, p.y), glm::vec3(0, Math::PI/4.0f*i, Math::PI/2.0f)});
            result.push_back({10+i,1+i, Gfx::ENG_OBJTYPE_DESCENDANT, "base4", glm::vec3(23.5f, 0.0f,  7.0f), glm::vec3(), glm::vec3(1.0f, 1.0f, 1.0f), false});
            result.push_back({18+i,1+i, Gfx::ENG_OBJTYPE_DESCENDANT, "base4", glm::vec3(23.5f, 0.0f, -7.0f), glm::vec3(), glm::vec3(1.0f, 1.0f, 1.0f), true});
        }
        result.push_back({9,  0, Gfx::ENG_OBJTYPE_DESCENDANT, "base3"});
        return result;
    }

    if ( type == OBJECT_DERRICK )
    {
        result.push_back({0, -1, Gfx::ENG_OBJTYPE_FIX,        "derrick1"});
        result.push_back({1,  0, Gfx::ENG_OBJTYPE_DESCENDANT, "derrick2"});
        return result;
    }

    if ( type == OBJECT_RESEARCH )
    {
        result.push_back({0, -1, Gfx::ENG_OBJTYPE_FIX,        "search1"});
        result.push_back({1,  0, Gfx::ENG_OBJTYPE_DESCENDANT, "search2", glm::vec3(0.0f, 13.0f, 0.0f)});
        result.push_back({2,  1, Gfx::ENG_OBJTYPE_DESCENDANT, "search3", glm::vec3(0.0f, 4.0f, 0.0f), glm::vec3(0.0f, 0.0f, 35.0f*Math::PI/180.0f)});
        return result;
    }

    if ( type == OBJECT_RADAR )
    {
        result.push_back({0, -1, Gfx::ENG_OBJTYPE_FIX,        "radar1"});
        result.push_back({1,  0, Gfx::ENG_OBJTYPE_DESCENDANT, "radar2", glm::vec3(0.0f, 5.0f, 0.0f)});
        result.push_back({2,  0, Gfx::ENG_OBJTYPE_DESCENDANT, "radar3", glm::vec3(0.0f, 11.0f, 0.0f), glm::vec3(0.0f, -Math::PI/2.0f, 0.0f)});
        result.push_back({3,  2, Gfx::ENG_OBJTYPE_DESCENDANT, "radar4", glm::vec3(0.0f, 4.5f, 1.9f)});
        return result;
    }

    if ( type == OBJECT_ENERGY )
    {
        result.push_back({0, -1, Gfx::ENG_OBJTYPE_FIX,        "energy"});
        return result;
    }

    if ( type == OBJECT_LABO )
    {
        result.push_back({0, -1, Gfx::ENG_OBJTYPE_FIX,        "labo1"});
        result.push_back({1,  0, Gfx::ENG_OBJTYPE_DESCENDANT, "labo2", glm::vec3(-9.0f, 3.0f, 0.0f), glm::vec3(0.0f, 0.0f, Math::PI/2.0f)});
        result.push_back({2,  1, Gfx::ENG_OBJTYPE_DESCENDANT, "labo3", glm::vec3(9.0f, -1.0f, 0.0f)});
        result.push_back({3,  2, Gfx::ENG_OBJTYPE_DESCENDANT, "labo4", glm::vec3(), glm::vec3(0.0f,                0.0f, 80.0f*Math::PI/180.0f)});
        result.push_back({4,  2, Gfx::ENG_OBJTYPE_DESCENDANT, "labo4", glm::vec3(), glm::vec3(0.0f,  Math::PI*2.0f/3.0f, 80.0f*Math::PI/180.0f)});
        result.push_back({5,  2, Gfx::ENG_OBJTYPE_DESCENDANT, "labo4", glm::vec3(), glm::vec3(0.0f, -Math::PI*2.0f/3.0f, 80.0f*Math::PI/180.0f)});
        return result;
    }

    if ( type == OBJECT_FACTORY )
    {
        result.push_back({0, -1, Gfx::ENG_OBJTYPE_FIX,        "factory1"});

        for (int i=0 ; i<9 ; i++ )
        {
            result.push_back({ 1+i, 0, Gfx::ENG_OBJTYPE_DESCENDANT, "factory2", glm::vec3(10.0f, 2.0f*i,  10.0f), glm::vec3(0.0f,     0.0f,  Math::PI/2.0f), glm::vec3(1.0f, 1.0f, 0.30f)});
            result.push_back({10+i, 0, Gfx::ENG_OBJTYPE_DESCENDANT, "factory2", glm::vec3(10.0f, 2.0f*i, -10.0f), glm::vec3(0.0f, Math::PI, -Math::PI/2.0f), glm::vec3(1.0f, 1.0f, 0.30f)});
        }

        return result;
    }

    if ( type == OBJECT_REPAIR )
    {
        result.push_back({0, -1, Gfx::ENG_OBJTYPE_FIX,        "repair1"});
        result.push_back({1,  0, Gfx::ENG_OBJTYPE_DESCENDANT, "repair2", glm::vec3(-11.0f, 13.5f, 0.0f), glm::vec3(0.0f, 0.0f, Math::PI/2.0f)});
        return result;
    }

    if ( type == OBJECT_DESTROYER )
    {
        result.push_back({0, -1, Gfx::ENG_OBJTYPE_FIX,        "destroy1"});
        result.push_back({1,  0, Gfx::ENG_OBJTYPE_DESCENDANT, "destroy2"});
        return result;
    }

    if ( type == OBJECT_STATION )
    {
        result.push_back({0, -1, Gfx::ENG_OBJTYPE_FIX,        "station"});
        return result;
    }

    if ( type == OBJECT_CONVERT )
    {
        result.push_back({0, -1, Gfx::ENG_OBJTYPE_FIX,        "convert1"});
        result.push_back({1,  0, Gfx::ENG_OBJTYPE_DESCENDANT, "convert2", glm::vec3(0.0f, 14.0f, 0.0f)});
        result.push_back({2,  0, Gfx::ENG_OBJTYPE_DESCENDANT, "convert3", glm::vec3(0.0f, 11.5f, 0.0f), glm::vec3(-Math::PI*0.35f, 0.0f, 0.0f)});
        result.push_back({3,  0, Gfx::ENG_OBJTYPE_DESCENDANT, "convert3", glm::vec3(0.0f, 11.5f, 0.0f), glm::vec3(-Math::PI*0.35f, Math::PI, 0.0f)});
        return result;
    }

    if ( type == OBJECT_TOWER )
    {
        result.push_back({0, -1, Gfx::ENG_OBJTYPE_FIX,        "tower"});
        result.push_back({1,  0, Gfx::ENG_OBJTYPE_DESCENDANT, "roller2c", glm::vec3(0.0f, 20.0f, 0.0f), glm::vec3(0.0f, 0.0f, Math::PI/2.0f)});
        result.push_back({2,  1, Gfx::ENG_OBJTYPE_DESCENDANT, "roller3c", glm::vec3(4.5f, 0.0f, 0.0f)});
        return result;
    }

    if ( type == OBJECT_NUCLEAR )
    {
        result.push_back({0, -1, Gfx::ENG_OBJTYPE_FIX,        "nuclear1"});
        result.push_back({1,  0, Gfx::ENG_OBJTYPE_DESCENDANT, "nuclear2", glm::vec3(20.0f, 10.0f, 0.0f), glm::vec3(0.0f, 0.0f, 135.0f*Math::PI/180.0f)});
        return result;
    }

    if ( type == OBJECT_PARA )
    {
        result.push_back({0, -1, Gfx::ENG_OBJTYPE_FIX,        "para"});
        return result;
    }

    if ( type == OBJECT_SAFE )
    {
        result.push_back({0, -1, Gfx::ENG_OBJTYPE_FIX,        "safe1"});
        result.push_back({1,  0, Gfx::ENG_OBJTYPE_DESCENDANT, "safe2", glm::vec3(), glm::vec3(), glm::vec3(1.05f, 1.05f, 1.05f)});
        result.push_back({2,  0, Gfx::ENG_OBJTYPE_DESCENDANT, "safe3", glm::vec3(), glm::vec3(), glm::vec3(1.05f, 1.05f, 1.05f)});
        return result;
    }

    if ( type == OBJECT_HUSTON )
    {
        result.push_back({0, -1, Gfx::ENG_OBJTYPE_FIX,        "huston1"});
        result.push_back({1,  0, Gfx::ENG_OBJTYPE_DESCENDANT, "huston2", glm::vec3(0.0f, 39.0f, 30.0f), glm::vec3(0.0f, -Math::PI/2.0f, 0.0f), glm::vec3(3.0f, 3.0f, 3.0f)});
        result.push_back({2,  1, Gfx::ENG_OBJTYPE_DESCENDANT, "huston3", glm::vec3(0.0f,  4.5f,  1.9f)});
        return result;
    }

    if ( type == OBJECT_TARGET1 )
    {
        result.push_back({0, -1, Gfx::ENG_OBJTYPE_FIX,        "target1"});
        return result;
    }

    if ( type == OBJECT_TARGET2 )
    {
        result.push_back({0, -1, Gfx::ENG_OBJTYPE_FIX,        "target2", glm::vec3(0.0f, 50.0f*1.5f, 0.0f)});
        return result;
    }

    if ( type == OBJECT_NEST )
    {
        result.push_back({0, -1, Gfx::ENG_OBJTYPE_FIX,        "nest"});
        return result;
    }

    if ( type == OBJECT_START )
    {
        result.push_back({0, -1, Gfx::ENG_OBJTYPE_FIX,        "start"});
        return result;
    }

    if ( type == OBJECT_END )
    {
        result.push_back({0, -1, Gfx::ENG_OBJTYPE_FIX,        "end"});
        return result;
    }

    if ( type == OBJECT_INFO )
    {
        result.push_back({0, -1, Gfx::ENG_OBJTYPE_FIX,        "info1"});
        result.push_back({1,  0, Gfx::ENG_OBJTYPE_DESCENDANT, "info2",  glm::vec3(0.0f, 5.0f, 0.0f)});
        result.push_back({2,  1, Gfx::ENG_OBJTYPE_DESCENDANT, "info3",  glm::vec3(0.0f, 4.5f, 0.0f), glm::vec3(0.0f, 0.0f*Math::PI/3.0f, 0.0f)});
        result.push_back({3,  2, Gfx::ENG_OBJTYPE_DESCENDANT, "radar4", glm::vec3(0.0f, 0.0f, -4.0f)});
        result.push_back({4,  1, Gfx::ENG_OBJTYPE_DESCENDANT, "info3",  glm::vec3(0.0f, 4.5f, 0.0f), glm::vec3(0.0f, 2.0f*Math::PI/3.0f, 0.0f)});
        result.push_back({5,  4, Gfx::ENG_OBJTYPE_DESCENDANT, "radar4", glm::vec3(0.0f, 0.0f, -4.0f)});
        result.push_back({6,  1, Gfx::ENG_OBJTYPE_DESCENDANT, "info3",  glm::vec3(0.0f, 4.5f, 0.0f), glm::vec3(0.0f, 4.0f*Math::PI/3.0f, 0.0f)});
        result.push_back({7,  6, Gfx::ENG_OBJTYPE_DESCENDANT, "radar4", glm::vec3(0.0f, 0.0f, -4.0f)});
        return result;
    }

    if ( type == OBJECT_MOTHER )
    {
        result.push_back({0, -1, Gfx::ENG_OBJTYPE_VEHICLE,    "mother1"});
        result.push_back({1,  0, Gfx::ENG_OBJTYPE_DESCENDANT, "mother2", glm::vec3(16.0f, 3.0f, 0.0f)});
        result.push_back({2,  0, Gfx::ENG_OBJTYPE_DESCENDANT, "mother3", glm::vec3(-5.0f, -1.0f, -12.0f)});
        result.push_back({3,  2, Gfx::ENG_OBJTYPE_DESCENDANT, "mother4", glm::vec3(0.0f, 0.0f, -8.5f)});
        result.push_back({4,  0, Gfx::ENG_OBJTYPE_DESCENDANT, "mother3", glm::vec3(3.5f, -1.0f, -12.0f)});
        result.push_back({5,  4, Gfx::ENG_OBJTYPE_DESCENDANT, "mother4", glm::vec3(0.0f, 0.0f, -8.5f)});
        result.push_back({6,  0, Gfx::ENG_OBJTYPE_DESCENDANT, "mother3", glm::vec3(10.0f, -1.0f, -10.0f)});
        result.push_back({7,  6, Gfx::ENG_OBJTYPE_DESCENDANT, "mother4", glm::vec3(0.0f, 0.0f, -8.5f)});
        result.push_back({8,  0, Gfx::ENG_OBJTYPE_DESCENDANT, "mother3", glm::vec3(-5.0f, -1.0f, 12.0f), {0, Math::PI, 0}});
        result.push_back({9,  8, Gfx::ENG_OBJTYPE_DESCENDANT, "mother4", glm::vec3(0.0f, 0.0f, -8.5f)});
        result.push_back({10, 0, Gfx::ENG_OBJTYPE_DESCENDANT, "mother3", glm::vec3(3.5f, -1.0f, 12.0f), {0, Math::PI, 0}});
        result.push_back({11,10, Gfx::ENG_OBJTYPE_DESCENDANT, "mother4", glm::vec3(0.0f, 0.0f, -8.5f)});
        result.push_back({12, 0, Gfx::ENG_OBJTYPE_DESCENDANT, "mother3", glm::vec3(10.0f, -1.0f, 10.0f), {0, Math::PI, 0}});
        result.push_back({13,12, Gfx::ENG_OBJTYPE_DESCENDANT, "mother4", glm::vec3(0.0f, 0.0f, -8.5f)});
        result.push_back({14, 1, Gfx::ENG_OBJTYPE_DESCENDANT, "mother5", glm::vec3(6.0f, 1.0f, -2.5f)});
        result.push_back({15,14, Gfx::ENG_OBJTYPE_DESCENDANT, "mother6", glm::vec3(8.0f, 0.0f, 0.0f)});
        result.push_back({16, 1, Gfx::ENG_OBJTYPE_DESCENDANT, "mother5", glm::vec3(6.0f, 1.0f, 2.5f)});
        result.push_back({17,16, Gfx::ENG_OBJTYPE_DESCENDANT, "mother6", glm::vec3(8.0f, 0.0f, 0.0f)});
        result.push_back({18, 1, Gfx::ENG_OBJTYPE_DESCENDANT, "mother7", glm::vec3(-4.0f, -3.5f, -8.0f), glm::vec3(), glm::vec3(1.2f, 1.0f, 1.0f)});
        result.push_back({19, 1, Gfx::ENG_OBJTYPE_DESCENDANT, "mother7", glm::vec3(-4.0f, -3.5f, 8.0f), glm::vec3(), glm::vec3(1.2f, 1.0f, 1.0f), true});
        return result;
    }

    if ( type == OBJECT_ANT )
    {
        result.push_back({0, -1, Gfx::ENG_OBJTYPE_VEHICLE,    "ant1"});
        result.push_back({1,  0, Gfx::ENG_OBJTYPE_DESCENDANT, "ant2", glm::vec3(2.0f, 0.0f, 0.0f)});
        result.push_back({2,  0, Gfx::ENG_OBJTYPE_DESCENDANT, "ant3", glm::vec3(-1.0f, 0.0f, 0.0f)});
        result.push_back({3,  0, Gfx::ENG_OBJTYPE_DESCENDANT, "ant4", glm::vec3(-0.4f, -0.1f, -0.3f)});
        result.push_back({4,  3, Gfx::ENG_OBJTYPE_DESCENDANT, "ant5", glm::vec3(0.0f, 0.0f, -1.0f)});
        result.push_back({5,  4, Gfx::ENG_OBJTYPE_DESCENDANT, "ant6", glm::vec3(0.0f, 0.0f, -2.0f)});
        result.push_back({6,  0, Gfx::ENG_OBJTYPE_DESCENDANT, "ant4", glm::vec3(0.1f, -0.1f, -0.4f)});
        result.push_back({7,  6, Gfx::ENG_OBJTYPE_DESCENDANT, "ant5", glm::vec3(0.0f, 0.0f, -1.0f)});
        result.push_back({8,  7, Gfx::ENG_OBJTYPE_DESCENDANT, "ant6", glm::vec3(0.0f, 0.0f, -2.0f)});
        result.push_back({9,  0, Gfx::ENG_OBJTYPE_DESCENDANT, "ant4", glm::vec3(1.4f, -0.1f, -0.6f)});
        result.push_back({10, 9, Gfx::ENG_OBJTYPE_DESCENDANT, "ant5", glm::vec3(0.0f, 0.0f, -1.0f)});
        result.push_back({11,10, Gfx::ENG_OBJTYPE_DESCENDANT, "ant6", glm::vec3(0.0f, 0.0f, -2.0f)});
        result.push_back({12, 0, Gfx::ENG_OBJTYPE_DESCENDANT, "ant4", glm::vec3(-0.4f, -0.1f, 0.3f),{}, {1,1,1}, true});
        result.push_back({13,12, Gfx::ENG_OBJTYPE_DESCENDANT, "ant5", glm::vec3(0.0f, 0.0f, 1.0f),  {}, {1,1,1}, true});
        result.push_back({14,13, Gfx::ENG_OBJTYPE_DESCENDANT, "ant6", glm::vec3(0.0f, 0.0f, 2.0f),  {}, {1,1,1}, true});
        result.push_back({15, 0, Gfx::ENG_OBJTYPE_DESCENDANT, "ant4", glm::vec3(0.1f, -0.1f, 0.4f), {}, {1,1,1}, true});
        result.push_back({16,15, Gfx::ENG_OBJTYPE_DESCENDANT, "ant5", glm::vec3(0.0f, 0.0f, 1.0f),  {}, {1,1,1}, true});
        result.push_back({17,16, Gfx::ENG_OBJTYPE_DESCENDANT, "ant6", glm::vec3(0.0f, 0.0f, 2.0f),  {}, {1,1,1}, true});
        result.push_back({18, 0, Gfx::ENG_OBJTYPE_DESCENDANT, "ant4", glm::vec3(1.4f, -0.1f, 0.6f), {}, {1,1,1}, true});
        result.push_back({19,18, Gfx::ENG_OBJTYPE_DESCENDANT, "ant5", glm::vec3(0.0f, 0.0f, 1.0f),  {}, {1,1,1}, true});
        result.push_back({20,19, Gfx::ENG_OBJTYPE_DESCENDANT, "ant6", glm::vec3(0.0f, 0.0f, 2.0f),  {}, {1,1,1}, true});
        return result;
    }

    if ( type == OBJECT_BEE )
    {
        result.push_back({0, -1, Gfx::ENG_OBJTYPE_VEHICLE,    "bee1"});
        result.push_back({1,  0, Gfx::ENG_OBJTYPE_DESCENDANT, "bee2", glm::vec3(1.6f, 0.3f, 0.0f)});
        result.push_back({2,  0, Gfx::ENG_OBJTYPE_DESCENDANT, "bee3", glm::vec3(-0.8f, 0.0f, 0.0f)});
        result.push_back({3,  0, Gfx::ENG_OBJTYPE_DESCENDANT, "ant4", glm::vec3(-0.3f, -0.1f, -0.2f)});
        result.push_back({4,  3, Gfx::ENG_OBJTYPE_DESCENDANT, "ant5", glm::vec3(0.0f, 0.0f, -1.0f)});
        result.push_back({5,  4, Gfx::ENG_OBJTYPE_DESCENDANT, "ant6", glm::vec3(0.0f, 0.0f, -2.0f)});
        result.push_back({6,  0, Gfx::ENG_OBJTYPE_DESCENDANT, "ant4", glm::vec3(0.3f, -0.1f, -0.4f)});
        result.push_back({7,  6, Gfx::ENG_OBJTYPE_DESCENDANT, "ant5", glm::vec3(0.0f, 0.0f, -1.0f)});
        result.push_back({8,  7, Gfx::ENG_OBJTYPE_DESCENDANT, "ant6", glm::vec3(0.0f, 0.0f, -2.0f)});
        result.push_back({9,  0, Gfx::ENG_OBJTYPE_DESCENDANT, "ant4", glm::vec3(1.0f, -0.1f, -0.7f)});
        result.push_back({10, 9, Gfx::ENG_OBJTYPE_DESCENDANT, "ant5", glm::vec3(0.0f, 0.0f, -1.0f)});
        result.push_back({11,10, Gfx::ENG_OBJTYPE_DESCENDANT, "ant6", glm::vec3(0.0f, 0.0f, -2.0f)});
        result.push_back({12, 0, Gfx::ENG_OBJTYPE_DESCENDANT, "ant4", glm::vec3(-0.3f, -0.1f, 0.2f), {0, Math::PI, 0}});
        result.push_back({13,12, Gfx::ENG_OBJTYPE_DESCENDANT, "ant5", glm::vec3(0.0f, 0.0f, -1.0f)});
        result.push_back({14,13, Gfx::ENG_OBJTYPE_DESCENDANT, "ant6", glm::vec3(0.0f, 0.0f, -2.0f)});
        result.push_back({15, 0, Gfx::ENG_OBJTYPE_DESCENDANT, "ant4", glm::vec3(0.3f, -0.1f, 0.4f), {0, Math::PI, 0}});
        result.push_back({16,15, Gfx::ENG_OBJTYPE_DESCENDANT, "ant5", glm::vec3(0.0f, 0.0f, -1.0f)});
        result.push_back({17,16, Gfx::ENG_OBJTYPE_DESCENDANT, "ant6", glm::vec3(0.0f, 0.0f, -2.0f)});
        result.push_back({18, 0, Gfx::ENG_OBJTYPE_DESCENDANT, "ant4", glm::vec3(1.0f, -0.1f, 0.7f), {0, Math::PI, 0}});
        result.push_back({19,18, Gfx::ENG_OBJTYPE_DESCENDANT, "ant5", glm::vec3(0.0f, 0.0f, -1.0f)});
        result.push_back({20,19, Gfx::ENG_OBJTYPE_DESCENDANT, "ant6", glm::vec3(0.0f, 0.0f, -2.0f)});
        result.push_back({21, 0, Gfx::ENG_OBJTYPE_DESCENDANT, "bee7", glm::vec3(0.8f, 0.4f, -0.5f)});
        result.push_back({22, 0, Gfx::ENG_OBJTYPE_DESCENDANT, "bee7", glm::vec3(0.8f, 0.4f, 0.5f), {}, {1,1,1}, true});
        return result;
    }

    if ( type == OBJECT_TOTO )
    {
        // Creates the head
        result.push_back({0, -1, Gfx::ENG_OBJTYPE_VEHICLE,   "toto1"});
        // Creates mouth.
        result.push_back({1, 0, Gfx::ENG_OBJTYPE_DESCENDANT, "toto2", glm::vec3(1.00f, 0.17f, 0.00f)});
        // Creates the left eye.
        result.push_back({2, 0, Gfx::ENG_OBJTYPE_DESCENDANT, "toto3", glm::vec3(0.85f, 1.04f, 0.25f), {0, -20.0f*Math::PI/180.0f, 0}, {1,1,1}, true});
        // Creates the right eye.
        result.push_back({3, 0, Gfx::ENG_OBJTYPE_DESCENDANT, "toto3", glm::vec3(0.85f, 1.04f, -0.25f), {0, 20.0f*Math::PI/180.0f, 0}});
        // Creates left antenna.
        result.push_back({4, 0, Gfx::ENG_OBJTYPE_DESCENDANT, "toto4", glm::vec3(0.0f,  1.9f, 0.3f), {30.0f*Math::PI/180.0f, 0, 0}});
        result.push_back({5, 4, Gfx::ENG_OBJTYPE_DESCENDANT, "toto4", glm::vec3(0.0f, 0.67f, 0.0f), {30.0f*Math::PI/180.0f, 0, 0}});
        result.push_back({6, 5, Gfx::ENG_OBJTYPE_DESCENDANT, "toto5", glm::vec3(0.0f, 0.70f, 0.0f), {30.0f*Math::PI/180.0f, 0, 0}});
        // Creates right antenna.
        result.push_back({7, 0, Gfx::ENG_OBJTYPE_DESCENDANT, "toto4", glm::vec3(0.0f, 1.9f, -0.3f), {-30.0f*Math::PI/180.0f, 0, 0}});
        result.push_back({8, 7, Gfx::ENG_OBJTYPE_DESCENDANT, "toto4", glm::vec3(0.0f, 0.67f, 0.0f), {-30.0f*Math::PI/180.0f, 0, 0}});
        result.push_back({9, 8, Gfx::ENG_OBJTYPE_DESCENDANT, "toto5", glm::vec3(0.0f, 0.70f, 0.0f), {-30.0f*Math::PI/180.0f, 0, 0}});
        return result;
    }

    if ( type == OBJECT_SPIDER )
    {
    
        // Creates the main base.
        // This is an "empty" object, without triangles
        result.push_back({0, -1, Gfx::ENG_OBJTYPE_VEHICLE});

        // Creates the abdomen.
        result.push_back({1, 0, Gfx::ENG_OBJTYPE_DESCENDANT, "spider1", glm::vec3(1.0f, 0.0f, 0.0f)});

        // Creates the head.
        result.push_back({2, 0, Gfx::ENG_OBJTYPE_DESCENDANT, "spider2", glm::vec3(1.0f, 0.0f, 0.0f)});

        float           table[] =
        {
        //    x       y       z
             0.6f,   0.0f,   0.0f,  // back leg
             0.0f,   0.0f,  -2.0f,
             0.0f,   0.0f,  -2.0f,
             0.0f,   0.0f,  -2.0f,
    
             0.8f,   0.0f,  -0.2f,  // middle-back leg
             0.0f,   0.0f,  -2.0f,
             0.0f,   0.0f,  -2.0f,
             0.0f,   0.0f,  -2.0f,
    
             1.0f,   0.0f,  -0.2f,  // middle-front leg
             0.0f,   0.0f,  -2.0f,
             0.0f,   0.0f,  -2.0f,
             0.0f,   0.0f,  -2.0f,
    
             1.2f,   0.0f,   0.0f,  // front leg
             0.0f,   0.0f,  -2.0f,
             0.0f,   0.0f,  -2.0f,
             0.0f,   0.0f,  -2.0f,
        };

        for (int i=0; i<4; i++)
        {
            // Creates the right leg.
            result.push_back({3+i*4,     0, Gfx::ENG_OBJTYPE_DESCENDANT, "spider3", {table[i*12+0], table[i*12+1], table[i*12+2]}});
            result.push_back({4+i*4, 3+i*4, Gfx::ENG_OBJTYPE_DESCENDANT, "spider4", {table[i*12+3], table[i*12+4], table[i*12+5]}});
            result.push_back({5+i*4, 4+i*4, Gfx::ENG_OBJTYPE_DESCENDANT, "spider5", {table[i*12+6], table[i*12+7], table[i*12+8]}});
            result.push_back({6+i*4, 5+i*4, Gfx::ENG_OBJTYPE_DESCENDANT, "spider6", {table[i*12+9], table[i*12+10], table[i*12+11]}});

            // Creates the left leg.
            result.push_back({19+i*4,      0, Gfx::ENG_OBJTYPE_DESCENDANT, "spider3", {table[i*12+0], table[i*12+1], -table[i*12+2]}, {}, {1,1,1}, true});
            result.push_back({20+i*4, 19+i*4, Gfx::ENG_OBJTYPE_DESCENDANT, "spider4", {table[i*12+3], table[i*12+4], -table[i*12+5]}, {}, {1,1,1}, true});
            result.push_back({21+i*4, 20+i*4, Gfx::ENG_OBJTYPE_DESCENDANT, "spider5", {table[i*12+6], table[i*12+7], -table[i*12+8]}, {}, {1,1,1}, true});
            result.push_back({22+i*4, 21+i*4, Gfx::ENG_OBJTYPE_DESCENDANT, "spider6", {table[i*12+9], table[i*12+10], -table[i*12+11]}, {}, {1,1,1}, true});
        }

        // Creates the right mandible.
        result.push_back({35, 1, Gfx::ENG_OBJTYPE_DESCENDANT, "spider7", glm::vec3(0.0f, 0.0f, -0.3f)});
    
        // Creates the left mandible.
        result.push_back({36, 1, Gfx::ENG_OBJTYPE_DESCENDANT, "spider7", glm::vec3(0.0f, 0.0f, 0.3f), {}, {1,1,1}, true});

        return result;
    }

    if ( type == OBJECT_WORM )
    {
        const int WORM_PART = 7; // number of parts of a worm

        // Creates the main base.
        // This is an "empty" object, without triangles
        result.push_back({0, -1, Gfx::ENG_OBJTYPE_VEHICLE});

        // Creates the head.
        result.push_back({1, 0, Gfx::ENG_OBJTYPE_DESCENDANT, "worm1", glm::vec3(1.0f+WORM_PART/2.0f, 0.0f, 0.0f)});

        // Creates the body.
        for ( int i=0 ; i<WORM_PART ; i++ )
            result.push_back({2+i, 0, Gfx::ENG_OBJTYPE_DESCENDANT, "worm2", glm::vec3(WORM_PART/2.0f-i, 0.0f, 0.0f)});

        // Creates the tail.
        result.push_back({2+WORM_PART, 0, Gfx::ENG_OBJTYPE_DESCENDANT, "worm3", glm::vec3(-WORM_PART/2.0f, 0.0f, 0.0f)});

        return result;
    }

    if ( type == OBJECT_HUMAN || type == OBJECT_TECH )
    {
        // Creates the main base.
        result.push_back({0, -1, Gfx::ENG_OBJTYPE_VEHICLE, "human1c", {}, {}, {1,1,1}, false, false, PART_OPTION_0});
        result.push_back({0, -1, Gfx::ENG_OBJTYPE_VEHICLE, "human1h", {}, {}, {1,1,1}, false, false, PART_OPTION_1});
        result.push_back({0, -1, Gfx::ENG_OBJTYPE_VEHICLE, "human1v", {}, {}, {1,1,1}, false, false, PART_OPTION_2});

        // Creates the head.
        if (type == OBJECT_HUMAN)
        {
            result.push_back({1, 0, Gfx::ENG_OBJTYPE_DESCENDANT, "human2c1", glm::vec3(0.0f, 2.7f, 0.0f), {}, {1, 1.00f, 1}, false, false, PART_OPTION_0});
            result.push_back({1, 0, Gfx::ENG_OBJTYPE_DESCENDANT, "human2h1", glm::vec3(0.0f, 2.7f, 0.0f), {}, {1, 1.05f, 1}, false, false, PART_OPTION_1});
            result.push_back({1, 0, Gfx::ENG_OBJTYPE_DESCENDANT, "human2h1", glm::vec3(0.0f, 2.7f, 0.0f), {}, {1, 1.05f, 1}, false, false, PART_OPTION_2});
        }
        if (type == OBJECT_TECH)
        {
            result.push_back({1, 0, Gfx::ENG_OBJTYPE_DESCENDANT, "human2t", glm::vec3(0.0f, 2.7f, 0.0f), {}, {1, 1.00f, 1}, false, false, PART_OPTION_0});
            result.push_back({1, 0, Gfx::ENG_OBJTYPE_DESCENDANT, "human2t", glm::vec3(0.0f, 2.7f, 0.0f), {}, {1, 1.05f, 1}, false, false, PART_OPTION_1});
            result.push_back({1, 0, Gfx::ENG_OBJTYPE_DESCENDANT, "human2t", glm::vec3(0.0f, 2.7f, 0.0f), {}, {1, 1.05f, 1}, false, false, PART_OPTION_2});
        }

        // Creates the right arm.
        result.push_back({2, 0, Gfx::ENG_OBJTYPE_DESCENDANT, "human3",  glm::vec3(0.0f, 2.3f, -1.2f), glm::vec3(90.0f*Math::PI/180.0f, 90.0f*Math::PI/180.0f, -50.0f*Math::PI/180.0f)});
        // Creates the right forearm.
        result.push_back({3, 2, Gfx::ENG_OBJTYPE_DESCENDANT, "human4r", glm::vec3(1.3f, 0.0f, 0.0f), glm::vec3(0.0f, -20.0f*Math::PI/180.0f, 0.0f)});
        // Creates right hand.
        result.push_back({4, 3, Gfx::ENG_OBJTYPE_DESCENDANT, "human5", glm::vec3(1.2f, 0.0f, 0.0f)});
        // Creates the right thigh.
        result.push_back({5, 0, Gfx::ENG_OBJTYPE_DESCENDANT, "human6", glm::vec3(0.0f, 0.0f, -0.7f), glm::vec3(10.0f*Math::PI/180.0f, 0.0f, 5.0f*Math::PI/180.0f)});
        // Creates the right leg.
        result.push_back({6, 5, Gfx::ENG_OBJTYPE_DESCENDANT, "human7", glm::vec3(0.0f, -1.5f, 0.0f), glm::vec3(0.0f, 0.0f, -10.0f*Math::PI/180.0f)});
        // Creates the right foot.
        result.push_back({7, 6, Gfx::ENG_OBJTYPE_DESCENDANT, "human8", glm::vec3(0.0f, -1.5f, 0.0f), glm::vec3(-10.0f*Math::PI/180.0f, 5.0f*Math::PI/180.0f, 5.0f*Math::PI/180.0f)});

        // Creates the left arm.
        result.push_back({8, 0, Gfx::ENG_OBJTYPE_DESCENDANT, "human3",  glm::vec3(0.0f, 2.3f, 1.2f), glm::vec3(-90.0f*Math::PI/180.0f, -90.0f*Math::PI/180.0f, -50.0f*Math::PI/180.0f), {1,1,1}, true} );
        // Creates the left forearm.
        result.push_back({9, 8, Gfx::ENG_OBJTYPE_DESCENDANT, "human4l", glm::vec3(1.3f, 0.0f, 0.0f), glm::vec3(0.0f, 20.0f*Math::PI/180.0f, 0.0f), {1,1,1}, true});
        // Creates left hand.
        result.push_back({10, 9, Gfx::ENG_OBJTYPE_DESCENDANT, "human5", glm::vec3(1.2f, 0.0f, 0.0f), {}, {1,1,1}, true});
        // Creates the left thigh.
        result.push_back({11, 0, Gfx::ENG_OBJTYPE_DESCENDANT, "human6", glm::vec3(0.0f, 0.0f, 0.7f), glm::vec3(-10.0f*Math::PI/180.0f, 0.0f, 5.0f*Math::PI/180.0f), {1,1,1}, true});
        // Creates the left leg.
        result.push_back({12, 11, Gfx::ENG_OBJTYPE_DESCENDANT, "human7", glm::vec3(0.0f, -1.5f, 0.0f), glm::vec3(0.0f, 0.0f, -10.0f*Math::PI/180.0f), {1,1,1}, true});
        // Creates the left foot.
        result.push_back({13, 12, Gfx::ENG_OBJTYPE_DESCENDANT, "human8", glm::vec3(0.0f, -1.5f, 0.0f), glm::vec3(10.0f*Math::PI/180.0f, -5.0f*Math::PI/180.0f, 5.0f*Math::PI/180.0f), {1,1,1}, true});

        // Creates the neutron gun.
        result.push_back({14, 0, Gfx::ENG_OBJTYPE_DESCENDANT, "human9", glm::vec3(-1.5f, 0.3f, -1.35f), glm::vec3(0, 0, Math::PI), {1,1,1}, false, false, PART_PLUSEXPLORER_FALSE|PART_OPTION_0});
        result.push_back({14, 0, Gfx::ENG_OBJTYPE_DESCENDANT, "human9", glm::vec3(-1.5f, 0.3f, -1.35f), glm::vec3(0, 0, Math::PI), {1,1,1}, false, false, PART_PLUSEXPLORER_FALSE|PART_OPTION_1});

        return result;
    }

    if ( type == OBJECT_MOBILEst )
    {
        result.push_back({0, -1, Gfx::ENG_OBJTYPE_VEHICLE,   "trainers"});
    }
    if ( type == OBJECT_MOBILEsa )
    {
        result.push_back({0, -1, Gfx::ENG_OBJTYPE_VEHICLE,   "trainers", {}, {}, {1,1,1}, false, false, PART_TRAINER_TRUE|PART_OPTION_ANY});
        result.push_back({0, -1, Gfx::ENG_OBJTYPE_VEHICLE,   "subm1",    {}, {}, {1,1,1}, false, false, PART_TRAINER_FALSE|PART_OPTION_ANY});
    }
    if ( type == OBJECT_MOBILErp )
    {
        result.push_back({0, -1, Gfx::ENG_OBJTYPE_VEHICLE,   "trainerr"});
    }
    if (  type == OBJECT_MOBILErt ||
          type == OBJECT_MOBILErc ||
          type == OBJECT_MOBILErr ||
          type == OBJECT_MOBILErs )
    {
        result.push_back({0, -1, Gfx::ENG_OBJTYPE_VEHICLE,   "roller1",  {}, {}, {1,1,1}, false, false, PART_TRAINER_FALSE|PART_OPTION_ANY});
        result.push_back({0, -1, Gfx::ENG_OBJTYPE_VEHICLE,   "trainerr", {}, {}, {1,1,1}, false, false, PART_TRAINER_TRUE|PART_OPTION_ANY});
    }
    if (type == OBJECT_MOBILEtg)
    {
        result.push_back({0, -1, Gfx::ENG_OBJTYPE_VEHICLE,   "target"});
    }
    if (type == OBJECT_MOBILEdr)
    {
        result.push_back({0, -1, Gfx::ENG_OBJTYPE_VEHICLE,   "drawer1"});
    }
    if (type == OBJECT_APOLLO2)
    {
        result.push_back({0, -1, Gfx::ENG_OBJTYPE_VEHICLE,   "apolloj1"});
    }
    if (type == OBJECT_MOBILEwt)
    {
        result.push_back({0, -1, Gfx::ENG_OBJTYPE_VEHICLE,    "trainer"});
        result.push_back({2,  0, Gfx::ENG_OBJTYPE_DESCENDANT, "drawer5", glm::vec3(0.2f, 4.1f, 0.0f), {0, 90.0f*Math::PI/180.0f, 0}, {1,1,1}, false, false, PART_TOY_TRUE|PART_OPTION_ANY});
        result.push_back({28, 0, Gfx::ENG_OBJTYPE_DESCENDANT, "trainerw"});
    }
    if (type == OBJECT_MOBILEft)
    {
        result.push_back({0, -1, Gfx::ENG_OBJTYPE_VEHICLE,    "trainer"});
        result.push_back({2,  0, Gfx::ENG_OBJTYPE_DESCENDANT, "drawer5", glm::vec3(0.2f, 4.1f, 0.0f), {0, 90.0f*Math::PI/180.0f, 0}, {1,1,1}, false, false, PART_TOY_TRUE|PART_OPTION_ANY});
        result.push_back({28, 0, Gfx::ENG_OBJTYPE_DESCENDANT, "trainerf"});
    }
    if (type == OBJECT_MOBILEtt)
    {
        result.push_back({0, -1, Gfx::ENG_OBJTYPE_VEHICLE,    "trainer"});
        result.push_back({2,  0, Gfx::ENG_OBJTYPE_DESCENDANT, "drawer5", glm::vec3(0.2f, 4.1f, 0.0f), {0, 90.0f*Math::PI/180.0f, 0}, {1,1,1}, false, false, PART_TOY_TRUE|PART_OPTION_ANY});
        result.push_back({28, 0, Gfx::ENG_OBJTYPE_DESCENDANT, "trainert"});
    }
    if (type == OBJECT_MOBILEit)
    {
        result.push_back({0, -1, Gfx::ENG_OBJTYPE_VEHICLE,    "trainer"});
        result.push_back({2,  0, Gfx::ENG_OBJTYPE_DESCENDANT, "drawer5", glm::vec3(0.2f, 4.1f, 0.0f), {0, 90.0f*Math::PI/180.0f, 0}, {1,1,1}, false, false, PART_TOY_TRUE|PART_OPTION_ANY});
        result.push_back({28, 0, Gfx::ENG_OBJTYPE_DESCENDANT, "traineri"});
    }
    if ( type == OBJECT_MOBILEfa ||
         type == OBJECT_MOBILEfb ||
         type == OBJECT_MOBILEfc ||
         type == OBJECT_MOBILEfi ||
         type == OBJECT_MOBILEfs)
    {
        result.push_back({0, -1, Gfx::ENG_OBJTYPE_VEHICLE,    "lem1f",  {}, {}, {1,1,1}, false, false, PART_TRAINER_FALSE|PART_OPTION_ANY});
        result.push_back({0, -1, Gfx::ENG_OBJTYPE_VEHICLE,    "trainer",  {}, {}, {1,1,1}, false, false, PART_TRAINER_TRUE|PART_OPTION_ANY});
        result.push_back({28, 0, Gfx::ENG_OBJTYPE_DESCENDANT, "trainerf", {}, {}, {1,1,1}, false, false, PART_TRAINER_TRUE|PART_OPTION_ANY});
        result.push_back({29, 0, Gfx::ENG_OBJTYPE_DESCENDANT, "trainera", {}, {}, {1,1,1}, false, false, PART_TRAINER_TRUE|PART_OPTION_ANY});
    }
    if ( type == OBJECT_MOBILEta ||
         type == OBJECT_MOBILEtb ||
         type == OBJECT_MOBILEtc ||
         type == OBJECT_MOBILEti ||
         type == OBJECT_MOBILEts)
    {
        result.push_back({0, -1, Gfx::ENG_OBJTYPE_VEHICLE,    "lem1t",  {}, {}, {1,1,1}, false, false, PART_TRAINER_FALSE|PART_OPTION_ANY});
        result.push_back({0, -1, Gfx::ENG_OBJTYPE_VEHICLE,    "trainer",  {}, {}, {1,1,1}, false, false, PART_TRAINER_TRUE|PART_OPTION_ANY});
        result.push_back({28, 0, Gfx::ENG_OBJTYPE_DESCENDANT, "trainert", {}, {}, {1,1,1}, false, false, PART_TRAINER_TRUE|PART_OPTION_ANY});
        result.push_back({29, 0, Gfx::ENG_OBJTYPE_DESCENDANT, "trainera", {}, {}, {1,1,1}, false, false, PART_TRAINER_TRUE|PART_OPTION_ANY});
    }
    if ( type == OBJECT_MOBILEwa ||
         type == OBJECT_MOBILEwb ||
         type == OBJECT_MOBILEwc ||
         type == OBJECT_MOBILEwi ||
         type == OBJECT_MOBILEws)
    {
        result.push_back({0, -1, Gfx::ENG_OBJTYPE_VEHICLE,    "lem1w",  {}, {}, {1,1,1}, false, false, PART_TRAINER_FALSE|PART_OPTION_ANY});
        result.push_back({0, -1, Gfx::ENG_OBJTYPE_VEHICLE,    "trainer",  {}, {}, {1,1,1}, false, false, PART_TRAINER_TRUE|PART_OPTION_ANY});
        result.push_back({28, 0, Gfx::ENG_OBJTYPE_DESCENDANT, "trainerw", {}, {}, {1,1,1}, false, false, PART_TRAINER_TRUE|PART_OPTION_ANY});
        result.push_back({29, 0, Gfx::ENG_OBJTYPE_DESCENDANT, "trainera", {}, {}, {1,1,1}, false, false, PART_TRAINER_TRUE|PART_OPTION_ANY});
    }
    if ( type == OBJECT_MOBILEia ||
         type == OBJECT_MOBILEib ||
         type == OBJECT_MOBILEic ||
         type == OBJECT_MOBILEii ||
         type == OBJECT_MOBILEis)
    {
        result.push_back({0, -1, Gfx::ENG_OBJTYPE_VEHICLE,    "lem1i",  {}, {}, {1,1,1}, false, false, PART_TRAINER_FALSE|PART_OPTION_ANY});
        result.push_back({0, -1, Gfx::ENG_OBJTYPE_VEHICLE,    "trainer",  {}, {}, {1,1,1}, false, false, PART_TRAINER_TRUE|PART_OPTION_ANY});
        result.push_back({28, 0, Gfx::ENG_OBJTYPE_DESCENDANT, "traineri", {}, {}, {1,1,1}, false, false, PART_TRAINER_TRUE|PART_OPTION_ANY});
        result.push_back({29, 0, Gfx::ENG_OBJTYPE_DESCENDANT, "trainera", {}, {}, {1,1,1}, false, false, PART_TRAINER_TRUE|PART_OPTION_ANY});
    }


    if (type == OBJECT_MOBILEfa ||
        type == OBJECT_MOBILEta ||
        type == OBJECT_MOBILEwa ||
        type == OBJECT_MOBILEia)
    {
        // Creates the arm.
        result.push_back({1, 0, Gfx::ENG_OBJTYPE_DESCENDANT, "lem2", glm::vec3(0.0f, 5.3f, 0.0f), {0,0, ARM_NEUTRAL_ANGLE1}});
        // Creates the forearm.
        result.push_back({2, 1, Gfx::ENG_OBJTYPE_DESCENDANT, "lem3", glm::vec3(5.0f, 0.0f, 0.0f), {0,0, ARM_NEUTRAL_ANGLE2}});
        // Creates the hand.
        result.push_back({3, 2, Gfx::ENG_OBJTYPE_DESCENDANT, "lem4", glm::vec3(3.5f, 0.0f, 0.0f), {Math::PI/2.0f, 0, ARM_NEUTRAL_ANGLE3}});
        // Creates the close clamp.
        result.push_back({4, 3, Gfx::ENG_OBJTYPE_DESCENDANT, "lem5", glm::vec3(1.5f, 0.0f, 0.0f), {0,0, -Math::PI*0.10f}});
        // Creates the remote clamp.
        result.push_back({5, 3, Gfx::ENG_OBJTYPE_DESCENDANT, "lem6", glm::vec3(1.5f, 0.0f, 0.0f), {0,0, Math::PI*0.10f}});
    }
    if (type == OBJECT_MOBILEfs ||
        type == OBJECT_MOBILEts ||
        type == OBJECT_MOBILEws ||
        type == OBJECT_MOBILEis)
    {
        // Creates the arm.
        result.push_back({1, 0, Gfx::ENG_OBJTYPE_DESCENDANT, "lem2", glm::vec3(0.0f, 5.3f, 0.0f), {0,0, 110.0f*Math::PI/180.0f}});
        // Creates the forearm.
        result.push_back({2, 1, Gfx::ENG_OBJTYPE_DESCENDANT, "lem3", glm::vec3(5.0f, 0.0f, 0.0f), {0,0, -110.0f*Math::PI/180.0f}});
        // Creates the sensor.
        result.push_back({3, 2, Gfx::ENG_OBJTYPE_DESCENDANT, "lem4s", glm::vec3(3.5f, 0.0f, 0.0f), {0,0, -65.0f*Math::PI/180.0f}});
    }
    if (type == OBJECT_MOBILEfc ||
        type == OBJECT_MOBILEtc ||
        type == OBJECT_MOBILEwc ||
        type == OBJECT_MOBILEic)
    {
        // Creates the cannon.
        result.push_back({1, 0, Gfx::ENG_OBJTYPE_DESCENDANT, "canon", glm::vec3(0.0f, 5.3f, 0.0f)});
    }
    if (type == OBJECT_MOBILEfi ||
        type == OBJECT_MOBILEti ||
        type == OBJECT_MOBILEwi ||
        type == OBJECT_MOBILEii)
    {
        // Creates the insect cannon.
        result.push_back({1, 0, Gfx::ENG_OBJTYPE_DESCENDANT, "canoni1", glm::vec3(0.0f, 5.3f, 0.0f)});
        result.push_back({2, 1, Gfx::ENG_OBJTYPE_DESCENDANT, "canoni2", glm::vec3(0.0f, 2.5f, 0.0f)});
    }
    if (type == OBJECT_MOBILEfb ||
        type == OBJECT_MOBILEtb ||
        type == OBJECT_MOBILEwb ||
        type == OBJECT_MOBILEib)
    {
        // Creates the neutron gun.
        result.push_back({1, 0, Gfx::ENG_OBJTYPE_DESCENDANT, "neutron", glm::vec3(0.0f, 5.3f, 0.0f)});
    }

    if (type == OBJECT_MOBILEwa ||
        type == OBJECT_MOBILEwb ||
        type == OBJECT_MOBILEwc ||
        type == OBJECT_MOBILEws ||
        type == OBJECT_MOBILEwi ||
        type == OBJECT_MOBILEwt)
    {
        // Creates the right-back wheel.
        result.push_back({6, 0, Gfx::ENG_OBJTYPE_DESCENDANT, "lem2w", glm::vec3(-3.0f, 1.0f, -3.0f)});
        // Creates the left-back wheel.
        result.push_back({7, 0, Gfx::ENG_OBJTYPE_DESCENDANT, "lem2w", glm::vec3(-3.0f, 1.0f, 3.0f), {0, Math::PI, 0}});
        // Creates the right-front wheel.
        result.push_back({8, 0, Gfx::ENG_OBJTYPE_DESCENDANT, "lem2w", glm::vec3(2.0f, 1.0f, -3.0f)});
        // Creates the left-front wheel.
        result.push_back({9, 0, Gfx::ENG_OBJTYPE_DESCENDANT, "lem2w", glm::vec3(2.0f, 1.0f, 3.0f), {0, Math::PI, 0}});
    }
    if (type == OBJECT_MOBILEtg)
    {
        // Creates the right-back wheel.
        result.push_back({6, 0, Gfx::ENG_OBJTYPE_DESCENDANT, "lem2w", glm::vec3(-2.0f, 1.0f, -3.0f)});
        // Creates the left-back wheel.
        result.push_back({7, 0, Gfx::ENG_OBJTYPE_DESCENDANT, "lem2w", glm::vec3(-2.0f, 1.0f, 3.0f), {0, Math::PI, 0}});
        // Creates the right-front wheel.
        result.push_back({8, 0, Gfx::ENG_OBJTYPE_DESCENDANT, "lem2w", glm::vec3(3.0f, 1.0f, -3.0f)});
        // Creates the left-front wheel.
        result.push_back({9, 0, Gfx::ENG_OBJTYPE_DESCENDANT, "lem2w", glm::vec3(3.0f, 1.0f, 3.0f), {0, Math::PI, 0}});
    }
    if ( type == OBJECT_MOBILEtt )
    {
        // Creates the right caterpillar.
        result.push_back({6, 0, Gfx::ENG_OBJTYPE_DESCENDANT, "lem2t", glm::vec3(0.0f, 2.0f, -3.55f), {}, {1,1,0.725f}, false, true});

        // Creates the left caterpillar.
        result.push_back({7, 0, Gfx::ENG_OBJTYPE_DESCENDANT, "lem3t", glm::vec3(0.0f, 2.0f, 3.55f), {}, {1,1,0.725f}, false, true});
    }
    if (type == OBJECT_MOBILEta ||
        type == OBJECT_MOBILEtb ||
        type == OBJECT_MOBILEtc ||
        type == OBJECT_MOBILEti ||
        type == OBJECT_MOBILEts)  // caterpillars?
    {
        // Creates the right caterpillar.
        result.push_back({6, 0, Gfx::ENG_OBJTYPE_DESCENDANT, "lem2t", glm::vec3(0.0f, 2.0f, -3.55f), {}, {1,1,0.725f}, false, true, PART_TRAINER_TRUE|PART_OPTION_ANY});
        result.push_back({6, 0, Gfx::ENG_OBJTYPE_DESCENDANT, "lem2t", glm::vec3(0.0f, 2.0f, -3.0f),  {}, {1,1,1},      false, true, PART_TRAINER_FALSE|PART_OPTION_ANY});
        // Creates the left caterpillar.
        result.push_back({7, 0, Gfx::ENG_OBJTYPE_DESCENDANT, "lem3t", glm::vec3(0.0f, 2.0f, 3.55f), {}, {1,1,0.725f}, false, true, PART_TRAINER_TRUE|PART_OPTION_ANY});
        result.push_back({7, 0, Gfx::ENG_OBJTYPE_DESCENDANT, "lem3t", glm::vec3(0.0f, 2.0f, 3.0f),  {}, {1,1,1},      false, true, PART_TRAINER_FALSE|PART_OPTION_ANY});
    }
    if (type == OBJECT_MOBILErt ||
        type == OBJECT_MOBILErc ||
        type == OBJECT_MOBILErr ||
        type == OBJECT_MOBILErs ||
        type == OBJECT_MOBILErp)  // large caterpillars?
    {
        // Creates the right caterpillar.
        result.push_back({6, 0, Gfx::ENG_OBJTYPE_DESCENDANT, "roller2", glm::vec3(0.0f, 2.0f, -3.0f),  {}, {1,1,1}, false, true});
        // Creates the left caterpillar.
        result.push_back({7, 0, Gfx::ENG_OBJTYPE_DESCENDANT, "roller3", glm::vec3(0.0f, 2.0f, 3.0f),  {}, {1,1,1}, false, true});
    }
    if (type == OBJECT_MOBILEsa ||
        type == OBJECT_MOBILEst)  // underwater caterpillars?
    {
        // Creates the right caterpillar.
        result.push_back({6, 0, Gfx::ENG_OBJTYPE_DESCENDANT, "subm4", glm::vec3(0.0f, 1.0f, -3.0f),  {}, {1,1,1}, false, true});
        // Creates the left caterpillar.
        result.push_back({7, 0, Gfx::ENG_OBJTYPE_DESCENDANT, "subm5", glm::vec3(0.0f, 1.0f, 3.0f),  {}, {1,1,1}, false, true});
    }
    if (type == OBJECT_MOBILEdr)  // caterpillars?
    {
        // Creates the right caterpillar.
        result.push_back({6, 0, Gfx::ENG_OBJTYPE_DESCENDANT, "drawer2", glm::vec3(0.0f, 1.0f, -3.0f), {}, {1,1,1}, false, true});
        // Creates the left caterpillar.
        result.push_back({7, 0, Gfx::ENG_OBJTYPE_DESCENDANT, "drawer3", glm::vec3(0.0f, 1.0f, 3.0f),  {}, {1,1,1}, false, true});
    }
    if (type == OBJECT_MOBILEfa ||
        type == OBJECT_MOBILEfb ||
        type == OBJECT_MOBILEfc ||
        type == OBJECT_MOBILEfs ||
        type == OBJECT_MOBILEfi ||
        type == OBJECT_MOBILEft)  // flying?
    {
        // Creates the front foot.
        result.push_back({6, 0, Gfx::ENG_OBJTYPE_DESCENDANT, "lem2f", glm::vec3(1.7f, 3.0f, 0.0f)});
        // Creates the right-back foot.
        result.push_back({7, 0, Gfx::ENG_OBJTYPE_DESCENDANT, "lem2f", glm::vec3(-1.8f, 3.0f, -1.5f), {0, 120.0f*Math::PI/180.0f, 0}});
        // Creates the left-back foot.
        result.push_back({8, 0, Gfx::ENG_OBJTYPE_DESCENDANT, "lem2f", glm::vec3(-1.8f, 3.0f, 1.5f), {0, -120.0f*Math::PI/180.0f, 0}});
    }
    if (type == OBJECT_MOBILEia ||
        type == OBJECT_MOBILEib ||
        type == OBJECT_MOBILEic ||
        type == OBJECT_MOBILEis ||
        type == OBJECT_MOBILEii ||
        type == OBJECT_MOBILEit)  // insect legs?
    {
        result.push_back({6,  0, Gfx::ENG_OBJTYPE_DESCENDANT, "ant4", glm::vec3(-1.5f, 1.2f, -0.7f)});
        result.push_back({7,  6, Gfx::ENG_OBJTYPE_DESCENDANT, "ant5", glm::vec3(0.0f, 0.0f, -1.0f)});
        result.push_back({8,  7, Gfx::ENG_OBJTYPE_DESCENDANT, "ant6", glm::vec3(0.0f, 0.0f, -2.0f)});
        result.push_back({9,  0, Gfx::ENG_OBJTYPE_DESCENDANT, "ant4", glm::vec3(0.0f, 1.2f, -0.9f)});
        result.push_back({10, 9, Gfx::ENG_OBJTYPE_DESCENDANT, "ant5", glm::vec3(0.0f, 0.0f, -1.0f)});
        result.push_back({11,10, Gfx::ENG_OBJTYPE_DESCENDANT, "ant6", glm::vec3(0.0f, 0.0f, -2.0f)});
        result.push_back({12, 0, Gfx::ENG_OBJTYPE_DESCENDANT, "ant4", glm::vec3(1.5f, 1.2f, -0.7f)});
        result.push_back({13,12, Gfx::ENG_OBJTYPE_DESCENDANT, "ant5", glm::vec3(0.0f, 0.0f, -1.0f)});
        result.push_back({14,13, Gfx::ENG_OBJTYPE_DESCENDANT, "ant6", glm::vec3(0.0f, 0.0f, -2.0f)});
        result.push_back({15, 0, Gfx::ENG_OBJTYPE_DESCENDANT, "ant4", glm::vec3(-1.5f, 1.2f, 0.7f),{}, {1,1,1}, true});
        result.push_back({16,15, Gfx::ENG_OBJTYPE_DESCENDANT, "ant5", glm::vec3(0.0f, 0.0f, 1.0f), {}, {1,1,1}, true});
        result.push_back({17,16, Gfx::ENG_OBJTYPE_DESCENDANT, "ant6", glm::vec3(0.0f, 0.0f, 2.0f), {}, {1,1,1}, true});
        result.push_back({18, 0, Gfx::ENG_OBJTYPE_DESCENDANT, "ant4", glm::vec3(0.0f, 1.2f, 0.9f), {}, {1,1,1}, true});
        result.push_back({19,18, Gfx::ENG_OBJTYPE_DESCENDANT, "ant5", glm::vec3(0.0f, 0.0f, 1.0f), {}, {1,1,1}, true});
        result.push_back({20,19, Gfx::ENG_OBJTYPE_DESCENDANT, "ant6", glm::vec3(0.0f, 0.0f, 2.0f), {}, {1,1,1}, true});
        result.push_back({21, 0, Gfx::ENG_OBJTYPE_DESCENDANT, "ant4", glm::vec3(1.5f, 1.2f, 0.7f), {}, {1,1,1}, true});
        result.push_back({22,21, Gfx::ENG_OBJTYPE_DESCENDANT, "ant5", glm::vec3(0.0f, 0.0f, 1.0f), {}, {1,1,1}, true});
        result.push_back({23,22, Gfx::ENG_OBJTYPE_DESCENDANT, "ant6", glm::vec3(0.0f, 0.0f, 2.0f), {}, {1,1,1}, true});
    }
    if (type == OBJECT_APOLLO2)
    {
        // antenna
        result.push_back({1, 0, Gfx::ENG_OBJTYPE_DESCENDANT, "apolloj2", glm::vec3(5.5f, 8.8f, 2.0f), {0, -120.0f*Math::PI/180.0f, 45.0f*Math::PI/180.0f}});  
        // camera
        result.push_back({2, 0, Gfx::ENG_OBJTYPE_DESCENDANT, "apolloj3", glm::vec3(5.5f, 2.8f, -2.0f), {0, 30.0f*Math::PI/180.0f, 0}});
        // Creates the wheels.
        result.push_back({6, 0, Gfx::ENG_OBJTYPE_DESCENDANT, "apolloj4", glm::vec3(-5.75f, 1.65f, -5.0f)});
        result.push_back({7, 0, Gfx::ENG_OBJTYPE_DESCENDANT, "apolloj4", glm::vec3(-5.75f, 1.65f, 5.0f)});
        result.push_back({8, 0, Gfx::ENG_OBJTYPE_DESCENDANT, "apolloj4", glm::vec3(5.75f, 1.65f, -5.0f)});
        result.push_back({9, 0, Gfx::ENG_OBJTYPE_DESCENDANT, "apolloj4", glm::vec3(5.75f, 1.65f, 5.00f)});
        // Creates mud guards.
        result.push_back({10, 0, Gfx::ENG_OBJTYPE_DESCENDANT, "apolloj6", glm::vec3(-5.75f, 1.65f, -5.0f)});
        result.push_back({11, 0, Gfx::ENG_OBJTYPE_DESCENDANT, "apolloj6", glm::vec3(-5.75f, 1.65f, 5.0f)});
        result.push_back({12, 0, Gfx::ENG_OBJTYPE_DESCENDANT, "apolloj5", glm::vec3(5.75f, 1.65f, -5.0f)});
        result.push_back({13, 0, Gfx::ENG_OBJTYPE_DESCENDANT, "apolloj5", glm::vec3(5.75f, 1.65f, 5.00f)});
    }

    if (type == OBJECT_MOBILErt)
    {
        // Creates the holder.
        result.push_back({1, 0, Gfx::ENG_OBJTYPE_DESCENDANT, "roller2t", glm::vec3(0.0f, 0.0f, 0.0f)});
        // Creates the pestle.
        result.push_back({2, 0, Gfx::ENG_OBJTYPE_DESCENDANT, "roller3t", glm::vec3(9.0f, 4.0f, 0.0f)});
    }
    if (type == OBJECT_MOBILErc)
    {
        // Creates the holder.
        result.push_back({1, 0, Gfx::ENG_OBJTYPE_DESCENDANT, "roller2c", glm::vec3(3.0f, 4.6f, 0.0f), {0, 0, Math::PI/8.0f}});
        // Creates the cannon.
        result.push_back({2, 0, Gfx::ENG_OBJTYPE_DESCENDANT, "roller3p", glm::vec3(7.0f, 6.5f, 0.0f)});
    }
    if (type == OBJECT_MOBILErr)
    {
        // Creates the holder.
        result.push_back({1, 0, Gfx::ENG_OBJTYPE_DESCENDANT, "recover1", glm::vec3(2.0f, 5.0f, 0.0f)});
        // Creates the right arm.
        result.push_back({2, 1, Gfx::ENG_OBJTYPE_DESCENDANT, "recover2", glm::vec3(0.1f, 0.0f, -5.0f), {0, 0, 126.0f*Math::PI/180.0f}});
        // Creates the right forearm.
        result.push_back({3, 2, Gfx::ENG_OBJTYPE_DESCENDANT, "recover3", glm::vec3(5.0f, 0.0f, -0.5f), {0, 0, -144.0f*Math::PI/180.0f}});
        // Creates the left arm.
        result.push_back({4, 1, Gfx::ENG_OBJTYPE_DESCENDANT, "recover2", glm::vec3(0.1f, 0.0f, 5.0f), {0, 0, 126.0f*Math::PI/180.0f}, {1,1,1}, true});
        // Creates the left forearm.
        result.push_back({5, 4, Gfx::ENG_OBJTYPE_DESCENDANT, "recover3", glm::vec3(5.0f, 0.0f, 0.5f), {0, 0, -144.0f*Math::PI/180.0f}, {1,1,1}, true});
    }
    if (type == OBJECT_MOBILErs)
    {
        // Creates the holder.
        result.push_back({1, 0, Gfx::ENG_OBJTYPE_DESCENDANT, "roller2s", glm::vec3(0.0f, 0.0f, 0.0f)});
        // Creates the intermediate piston.
        result.push_back({2, 1, Gfx::ENG_OBJTYPE_DESCENDANT, "roller3s", glm::vec3(7.0f, 4.5f, 0.0f)});
        // Creates the piston with the sphere.
        result.push_back({3, 2, Gfx::ENG_OBJTYPE_DESCENDANT, "roller4s", glm::vec3(0.0f, 1.0f, 0.0f)});
    }
    if (type == OBJECT_MOBILEsa)
    {
        // Creates the holder.
        result.push_back({1, 0, Gfx::ENG_OBJTYPE_DESCENDANT, "subm2", glm::vec3(4.2f, 3.0f, 0.0f)});
        // Creates the right tong.
        result.push_back({2, 1, Gfx::ENG_OBJTYPE_DESCENDANT, "subm3", glm::vec3(0.5f, 0.0f, -1.5f)});
        // Creates the left tong.
        result.push_back({3, 1, Gfx::ENG_OBJTYPE_DESCENDANT, "subm3", glm::vec3(0.5f, 0.0f, 1.5f), {}, {1,1,1}, true});
        // Flipper
        result.push_back({4, 0, Gfx::ENG_OBJTYPE_DESCENDANT, "trainerg", {}, {}, {1,1,1}, true, false, PART_TRAINER_TRUE|PART_OPTION_ANY});
    }

    if (type == OBJECT_MOBILEdr)
    {
        // Creates the carousel.
        result.push_back({1, 0, Gfx::ENG_OBJTYPE_DESCENDANT, "drawer4", glm::vec3(-3.0f, 3.0f, 0.0f)});

        // Creates the key.
        result.push_back({2, 0, Gfx::ENG_OBJTYPE_DESCENDANT, "drawer5", glm::vec3(3.0f, 5.7f, 0.0f), {0, 90.0f*Math::PI/180.0f, 0}, {1,1,1}, false, false, PART_TOY_TRUE|PART_OPTION_ANY});

        // Creates pencils.
        result.push_back({10, 1, Gfx::ENG_OBJTYPE_DESCENDANT, "drawer10", glm::vec3(0.0f, 0.0f, 0.0f), {0, 45.0f*Math::PI/180.0f*0, 0}});
        result.push_back({11, 1, Gfx::ENG_OBJTYPE_DESCENDANT, "drawer11", glm::vec3(0.0f, 0.0f, 0.0f), {0, 45.0f*Math::PI/180.0f*1, 0}});
        result.push_back({12, 1, Gfx::ENG_OBJTYPE_DESCENDANT, "drawer12", glm::vec3(0.0f, 0.0f, 0.0f), {0, 45.0f*Math::PI/180.0f*2, 0}});
        result.push_back({13, 1, Gfx::ENG_OBJTYPE_DESCENDANT, "drawer13", glm::vec3(0.0f, 0.0f, 0.0f), {0, 45.0f*Math::PI/180.0f*3, 0}});
        result.push_back({14, 1, Gfx::ENG_OBJTYPE_DESCENDANT, "drawer14", glm::vec3(0.0f, 0.0f, 0.0f), {0, 45.0f*Math::PI/180.0f*4, 0}});
        result.push_back({15, 1, Gfx::ENG_OBJTYPE_DESCENDANT, "drawer15", glm::vec3(0.0f, 0.0f, 0.0f), {0, 45.0f*Math::PI/180.0f*5, 0}});
        result.push_back({16, 1, Gfx::ENG_OBJTYPE_DESCENDANT, "drawer16", glm::vec3(0.0f, 0.0f, 0.0f), {0, 45.0f*Math::PI/180.0f*6, 0}});
        result.push_back({17, 1, Gfx::ENG_OBJTYPE_DESCENDANT, "drawer17", glm::vec3(0.0f, 0.0f, 0.0f), {0, 45.0f*Math::PI/180.0f*7, 0}});
    }

    return result;
}

std::vector<CObjectModeledNode> CModeledHardcodeCollection::GetModeledHead(ObjectType type)
{
    std::vector<CObjectModeledNode> result;

    // Creates the head.
    if (type == OBJECT_HUMAN)
    {
        result.push_back({0, -1, Gfx::ENG_OBJTYPE_VEHICLE, "human2h1"});
        result.push_back({1,  0, Gfx::ENG_OBJTYPE_DESCENDANT, "human2g1", {}, {}, {1,1,1}, false, false, PART_ALWAYS, 1});
        result.push_back({1,  0, Gfx::ENG_OBJTYPE_DESCENDANT, "human2g2", {}, {}, {1,1,1}, false, false, PART_ALWAYS, 2});
        result.push_back({1,  0, Gfx::ENG_OBJTYPE_DESCENDANT, "human2g3", {}, {}, {1,1,1}, false, false, PART_ALWAYS, 3});
        result.push_back({1,  0, Gfx::ENG_OBJTYPE_DESCENDANT, "human2g4", {}, {}, {1,1,1}, false, false, PART_ALWAYS, 4});
        result.push_back({1,  0, Gfx::ENG_OBJTYPE_DESCENDANT, "human2g5", {}, {}, {1,1,1}, false, false, PART_ALWAYS, 5});
    }
    if (type == OBJECT_TECH)
    {
        result.push_back({0, -1, Gfx::ENG_OBJTYPE_VEHICLE, "human2t"});
        result.push_back({1,  0, Gfx::ENG_OBJTYPE_DESCENDANT, "human2g1", {}, {}, {1,1,1}, false, false, PART_ALWAYS, 1});
        result.push_back({1,  0, Gfx::ENG_OBJTYPE_DESCENDANT, "human2g2", {}, {}, {1,1,1}, false, false, PART_ALWAYS, 2});
        result.push_back({1,  0, Gfx::ENG_OBJTYPE_DESCENDANT, "human2g3", {}, {}, {1,1,1}, false, false, PART_ALWAYS, 3});
        result.push_back({1,  0, Gfx::ENG_OBJTYPE_DESCENDANT, "human2g4", {}, {}, {1,1,1}, false, false, PART_ALWAYS, 4});
        result.push_back({1,  0, Gfx::ENG_OBJTYPE_DESCENDANT, "human2g5", {}, {}, {1,1,1}, false, false, PART_ALWAYS, 5});
    }
    if ( type == OBJECT_ANT )
    {
        result.push_back({0, -1, Gfx::ENG_OBJTYPE_VEHICLE, "ant2"});
    }
    return result;
}

std::vector<CObjectModeledCrashSphere> CModeledHardcodeCollection::GetModeledCrashSpheres(ObjectType type)
{
    std::vector<CObjectModeledCrashSphere> result;

    if ( type == OBJECT_EGG )
    {
        result.push_back({CrashSphere(glm::vec3(-1.0f, 2.8f, 0.0f), 3.0f, SOUND_BOUMm, 0.45f), PART_ALWAYS});
    }
    else if ( type == OBJECT_BOMB )
    {
        result.push_back({CrashSphere(glm::vec3(0.0f, 0.0f, 0.0f), 3.0f, SOUND_BOUMm, 0.45f), PART_ALWAYS});
    }
    else if ( type == OBJECT_BAG )
    {
        result.push_back({CrashSphere(glm::vec3(0.0f, 0.0f, 0.0f), 4.0f, SOUND_BOUMm, 0.45f), PART_ALWAYS});
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
        result.push_back({CrashSphere(glm::vec3(0.0f, 1.0f, 0.0f), 1.0f, SOUND_BOUMm, 0.45f), PART_ALWAYS});
    }

    if ( type == OBJECT_BARRIER0 )
    {
        result.push_back({CrashSphere(glm::vec3( 3.5f, 3.0f, 0.0f), 0.7f, SOUND_BOUMm, 0.45f), PART_ALWAYS});
        result.push_back({CrashSphere(glm::vec3( 0.0f, 3.0f, 0.0f), 0.7f, SOUND_BOUMm, 0.45f), PART_ALWAYS});
        result.push_back({CrashSphere(glm::vec3(-3.5f, 3.0f, 0.0f), 0.7f, SOUND_BOUMm, 0.45f), PART_ALWAYS});
    }

    if ( type == OBJECT_BARRIER1 )
    {
        result.push_back({CrashSphere(glm::vec3( 8.5f, 3.0f, 0.0f), 0.7f, SOUND_BOUMm, 0.45f), PART_ALWAYS});
        result.push_back({CrashSphere(glm::vec3( 3.5f, 3.0f, 0.0f), 0.7f, SOUND_BOUMm, 0.45f), PART_ALWAYS});
        result.push_back({CrashSphere(glm::vec3( 0.0f, 3.0f, 0.0f), 0.7f, SOUND_BOUMm, 0.45f), PART_ALWAYS});
        result.push_back({CrashSphere(glm::vec3(-3.5f, 3.0f, 0.0f), 0.7f, SOUND_BOUMm, 0.45f), PART_ALWAYS});
        result.push_back({CrashSphere(glm::vec3(-8.5f, 3.0f, 0.0f), 0.7f, SOUND_BOUMm, 0.45f), PART_ALWAYS});
    }

    if ( type == OBJECT_BARRIER2 )  // cardboard?
    {
        result.push_back({CrashSphere(glm::vec3( 8.5f, 3.0f, 0.0f), 0.7f, SOUND_BOUMm, 0.45f), PART_ALWAYS});
        result.push_back({CrashSphere(glm::vec3( 3.5f, 3.0f, 0.0f), 0.7f, SOUND_BOUMm, 0.45f), PART_ALWAYS});
        result.push_back({CrashSphere(glm::vec3( 0.0f, 3.0f, 0.0f), 0.7f, SOUND_BOUMm, 0.45f), PART_ALWAYS});
        result.push_back({CrashSphere(glm::vec3(-3.5f, 3.0f, 0.0f), 0.7f, SOUND_BOUMm, 0.45f), PART_ALWAYS});
        result.push_back({CrashSphere(glm::vec3(-8.5f, 3.0f, 0.0f), 0.7f, SOUND_BOUMm, 0.45f), PART_ALWAYS});
    }

    if ( type == OBJECT_BARRIER3 )  // match + straw?
    {
        result.push_back({CrashSphere(glm::vec3( 8.5f, 3.0f, 0.0f), 0.7f, SOUND_BOUMm, 0.45f), PART_ALWAYS});
        result.push_back({CrashSphere(glm::vec3( 3.5f, 3.0f, 0.0f), 0.7f, SOUND_BOUMm, 0.45f), PART_ALWAYS});
        result.push_back({CrashSphere(glm::vec3( 0.0f, 3.0f, 0.0f), 0.7f, SOUND_BOUMm, 0.45f), PART_ALWAYS});
        result.push_back({CrashSphere(glm::vec3(-3.5f, 3.0f, 0.0f), 0.7f, SOUND_BOUMm, 0.45f), PART_ALWAYS});
        result.push_back({CrashSphere(glm::vec3(-8.5f, 3.0f, 0.0f), 0.7f, SOUND_BOUMm, 0.45f), PART_ALWAYS});
    }

    if ( type == OBJECT_BARRICADE0 )
    {
        result.push_back({CrashSphere(glm::vec3( 3.5f, 3.0f, 0.0f), 0.7f, SOUND_BOUMm, 0.45f), PART_ALWAYS});
        result.push_back({CrashSphere(glm::vec3( 0.0f, 3.0f, 0.0f), 0.7f, SOUND_BOUMm, 0.45f), PART_ALWAYS});
        result.push_back({CrashSphere(glm::vec3(-3.5f, 3.0f, 0.0f), 0.7f, SOUND_BOUMm, 0.45f), PART_ALWAYS});
        result.push_back({CrashSphere(glm::vec3( 3.5f, 6.0f, 0.0f), 0.7f, SOUND_BOUMm, 0.45f), PART_ALWAYS});
        result.push_back({CrashSphere(glm::vec3( 0.0f, 6.0f, 0.0f), 0.7f, SOUND_BOUMm, 0.45f), PART_ALWAYS});
        result.push_back({CrashSphere(glm::vec3(-3.5f, 6.0f, 0.0f), 0.7f, SOUND_BOUMm, 0.45f), PART_ALWAYS});
    }

    if ( type == OBJECT_BARRICADE1 )
    {
        result.push_back({CrashSphere(glm::vec3( 8.5f, 3.0f, 0.0f), 0.7f, SOUND_BOUMm, 0.45f), PART_ALWAYS});
        result.push_back({CrashSphere(glm::vec3( 3.5f, 3.0f, 0.0f), 0.7f, SOUND_BOUMm, 0.45f), PART_ALWAYS});
        result.push_back({CrashSphere(glm::vec3( 0.0f, 3.0f, 0.0f), 0.7f, SOUND_BOUMm, 0.45f), PART_ALWAYS});
        result.push_back({CrashSphere(glm::vec3(-3.5f, 3.0f, 0.0f), 0.7f, SOUND_BOUMm, 0.45f), PART_ALWAYS});
        result.push_back({CrashSphere(glm::vec3(-8.5f, 3.0f, 0.0f), 0.7f, SOUND_BOUMm, 0.45f), PART_ALWAYS});
        result.push_back({CrashSphere(glm::vec3( 8.5f, 6.0f, 0.0f), 0.7f, SOUND_BOUMm, 0.45f), PART_ALWAYS});
        result.push_back({CrashSphere(glm::vec3( 3.5f, 6.0f, 0.0f), 0.7f, SOUND_BOUMm, 0.45f), PART_ALWAYS});
        result.push_back({CrashSphere(glm::vec3( 0.0f, 6.0f, 0.0f), 0.7f, SOUND_BOUMm, 0.45f), PART_ALWAYS});
        result.push_back({CrashSphere(glm::vec3(-3.5f, 6.0f, 0.0f), 0.7f, SOUND_BOUMm, 0.45f), PART_ALWAYS});
        result.push_back({CrashSphere(glm::vec3(-8.5f, 6.0f, 0.0f), 0.7f, SOUND_BOUMm, 0.45f), PART_ALWAYS});
    }

    if ( type == OBJECT_PLANT0 ||
         type == OBJECT_PLANT1 ||
         type == OBJECT_PLANT2 ||
         type == OBJECT_PLANT3 ||
         type == OBJECT_PLANT4 )  // standard?
    {
        result.push_back({CrashSphere(glm::vec3(0.0f, 0.0f, 0.0f), 4.0f, SOUND_BOUM, 0.10f), PART_ALWAYS});
    }

    if ( type == OBJECT_PLANT5 ||
         type == OBJECT_PLANT6 ||
         type == OBJECT_PLANT7 )  // clover?
    {
//?     result.push_back({CrashSphere(glm::vec3(0.0f, 0.0f, 0.0f), 3.0f, SOUND_BOUM, 0.10f), PART_ALWAYS});
    }

    if ( type == OBJECT_PLANT8 ||
         type == OBJECT_PLANT9 )  // squash?
    {
        result.push_back({CrashSphere(glm::vec3(0.0f,  2.0f, 0.0f), 4.0f, SOUND_BOUM, 0.10f), PART_ALWAYS});
        result.push_back({CrashSphere(glm::vec3(0.0f, 10.0f, 0.0f), 4.0f, SOUND_BOUM, 0.10f), PART_ALWAYS});
    }

    if ( type == OBJECT_PLANT10 ||
         type == OBJECT_PLANT11 ||
         type == OBJECT_PLANT12 ||
         type == OBJECT_PLANT13 ||
         type == OBJECT_PLANT14 )  // succulent?
    {
        result.push_back({CrashSphere(glm::vec3(0.0f, 12.0f, 0.0f), 5.0f, SOUND_BOUM, 0.10f), PART_ALWAYS});
    }

    if ( type == OBJECT_PLANT15 ||
         type == OBJECT_PLANT16 ||
         type == OBJECT_PLANT17 ||
         type == OBJECT_PLANT18 )  // fern?
    {
        result.push_back({CrashSphere(glm::vec3(0.0f, 0.0f, 0.0f), 4.0f, SOUND_BOUM, 0.10f), PART_ALWAYS});
    }

    if ( type == OBJECT_PLANT19 )  // fern?
    {
    }

    if ( type == OBJECT_TREE0 )
    {
        result.push_back({CrashSphere(glm::vec3( 0.0f,  3.0f, 2.0f), 3.0f, SOUND_BOUMs, 0.20f), PART_ALWAYS});
        result.push_back({CrashSphere(glm::vec3(-1.0f, 10.0f, 1.0f), 2.0f, SOUND_BOUMs, 0.20f), PART_ALWAYS});
        result.push_back({CrashSphere(glm::vec3( 0.0f, 17.0f, 0.0f), 2.0f, SOUND_BOUMs, 0.20f), PART_ALWAYS});
        result.push_back({CrashSphere(glm::vec3( 1.0f, 27.0f, 0.0f), 2.0f, SOUND_BOUMs, 0.20f), PART_ALWAYS});
    }

    if ( type == OBJECT_TREE1 )
    {
        result.push_back({CrashSphere(glm::vec3( 0.0f,  3.0f, 2.0f), 3.0f, SOUND_BOUMs, 0.20f), PART_ALWAYS});
        result.push_back({CrashSphere(glm::vec3(-2.0f, 11.0f, 1.0f), 2.0f, SOUND_BOUMs, 0.20f), PART_ALWAYS});
        result.push_back({CrashSphere(glm::vec3(-2.0f, 19.0f, 2.0f), 2.0f, SOUND_BOUMs, 0.20f), PART_ALWAYS});
        result.push_back({CrashSphere(glm::vec3( 2.0f, 26.0f, 0.0f), 2.0f, SOUND_BOUMs, 0.20f), PART_ALWAYS});
        result.push_back({CrashSphere(glm::vec3( 2.0f, 34.0f,-2.0f), 2.0f, SOUND_BOUMs, 0.20f), PART_ALWAYS});
    }

    if ( type == OBJECT_TREE2 )
    {
        result.push_back({CrashSphere(glm::vec3( 0.0f,  3.0f, 1.0f), 3.0f, SOUND_BOUMs, 0.20f), PART_ALWAYS});
        result.push_back({CrashSphere(glm::vec3(-2.0f, 10.0f, 1.0f), 2.0f, SOUND_BOUMs, 0.20f), PART_ALWAYS});
        result.push_back({CrashSphere(glm::vec3(-2.0f, 19.0f, 2.0f), 2.0f, SOUND_BOUMs, 0.20f), PART_ALWAYS});
        result.push_back({CrashSphere(glm::vec3( 2.0f, 25.0f, 0.0f), 2.0f, SOUND_BOUMs, 0.20f), PART_ALWAYS});
        result.push_back({CrashSphere(glm::vec3( 3.0f, 32.0f,-2.0f), 2.0f, SOUND_BOUMs, 0.20f), PART_ALWAYS});
    }

    if ( type == OBJECT_TREE3 )
    {
        result.push_back({CrashSphere(glm::vec3(-2.0f,  3.0f, 2.0f), 3.0f, SOUND_BOUMs, 0.20f), PART_ALWAYS});
        result.push_back({CrashSphere(glm::vec3(-3.0f,  9.0f, 1.0f), 2.0f, SOUND_BOUMs, 0.20f), PART_ALWAYS});
        result.push_back({CrashSphere(glm::vec3( 0.0f, 18.0f, 0.0f), 2.0f, SOUND_BOUMs, 0.20f), PART_ALWAYS});
        result.push_back({CrashSphere(glm::vec3( 0.0f, 27.0f, 7.0f), 2.0f, SOUND_BOUMs, 0.20f), PART_ALWAYS});
    }

    if ( type == OBJECT_TREE4 )
    {
        result.push_back({CrashSphere(glm::vec3(0.0f, 10.0f, 0.0f), 10.0f, SOUND_BOUMs, 0.20f), PART_ALWAYS});
        result.push_back({CrashSphere(glm::vec3(0.0f, 21.0f, 0.0f),  8.0f, SOUND_BOUMs, 0.20f), PART_ALWAYS});
        result.push_back({CrashSphere(glm::vec3(0.0f, 32.0f, 0.0f),  7.0f, SOUND_BOUMs, 0.20f), PART_ALWAYS});
    }

    if ( type == OBJECT_TREE5 )  // giant tree (for the world "teen")
    {
        result.push_back({CrashSphere(glm::vec3(  0.0f, 5.0f,-10.0f), 25.0f, SOUND_BOUMs, 0.20f), PART_ALWAYS});
        result.push_back({CrashSphere(glm::vec3(-65.0f, 5.0f, 65.0f), 20.0f, SOUND_BOUMs, 0.20f), PART_ALWAYS});
        result.push_back({CrashSphere(glm::vec3( 38.0f, 5.0f, 21.0f), 18.0f, SOUND_BOUMs, 0.20f), PART_ALWAYS});
    }

    if ( type == OBJECT_MUSHROOM1 )
    {
        result.push_back({CrashSphere(glm::vec3(0.0f, 4.0f, 0.0f), 3.0f, SOUND_BOUM, 0.10f), PART_ALWAYS});
    }

    if ( type == OBJECT_MUSHROOM2 )
    {
        result.push_back({CrashSphere(glm::vec3(0.0f, 5.0f, 0.0f), 3.0f, SOUND_BOUM, 0.10f), PART_ALWAYS});
    }

    if ( type == OBJECT_TEEN0 )  // orange pencil lg=10
    {
        result.push_back({CrashSphere(glm::vec3( 5.0f, 1.0f, 0.0f), 1.0f, SOUND_BOUMm, 0.45f), PART_ALWAYS});
        result.push_back({CrashSphere(glm::vec3( 2.5f, 1.0f, 0.0f), 1.0f, SOUND_BOUMm, 0.45f), PART_ALWAYS});
        result.push_back({CrashSphere(glm::vec3( 0.0f, 1.0f, 0.0f), 1.0f, SOUND_BOUMm, 0.45f), PART_ALWAYS});
        result.push_back({CrashSphere(glm::vec3(-2.5f, 1.0f, 0.0f), 1.0f, SOUND_BOUMm, 0.45f), PART_ALWAYS});
        result.push_back({CrashSphere(glm::vec3(-5.0f, 1.0f, 0.0f), 1.0f, SOUND_BOUMm, 0.45f), PART_ALWAYS});
    }

    if ( type == OBJECT_TEEN1 )  // blue pencil lg=14
    {
        result.push_back({CrashSphere(glm::vec3( 6.0f, 1.0f, 0.0f), 1.0f, SOUND_BOUMm, 0.45f), PART_ALWAYS});
        result.push_back({CrashSphere(glm::vec3( 4.0f, 1.0f, 0.0f), 1.0f, SOUND_BOUMm, 0.45f), PART_ALWAYS});
        result.push_back({CrashSphere(glm::vec3( 2.0f, 1.0f, 0.0f), 1.0f, SOUND_BOUMm, 0.45f), PART_ALWAYS});
        result.push_back({CrashSphere(glm::vec3( 0.0f, 1.0f, 0.0f), 1.0f, SOUND_BOUMm, 0.45f), PART_ALWAYS});
        result.push_back({CrashSphere(glm::vec3(-2.0f, 1.0f, 0.0f), 1.0f, SOUND_BOUMm, 0.45f), PART_ALWAYS});
        result.push_back({CrashSphere(glm::vec3(-4.0f, 1.0f, 0.0f), 1.0f, SOUND_BOUMm, 0.45f), PART_ALWAYS});
        result.push_back({CrashSphere(glm::vec3(-6.0f, 1.0f, 0.0f), 1.0f, SOUND_BOUMm, 0.45f), PART_ALWAYS});
    }

    if ( type == OBJECT_TEEN2 )  // red pencil lg=16
    {
        result.push_back({CrashSphere(glm::vec3( 7.0f, 1.0f, 0.0f), 1.0f, SOUND_BOUMm, 0.45f), PART_ALWAYS});
        result.push_back({CrashSphere(glm::vec3( 4.7f, 1.0f, 0.0f), 1.0f, SOUND_BOUMm, 0.45f), PART_ALWAYS});
        result.push_back({CrashSphere(glm::vec3( 2.3f, 1.0f, 0.0f), 1.0f, SOUND_BOUMm, 0.45f), PART_ALWAYS});
        result.push_back({CrashSphere(glm::vec3( 0.0f, 1.0f, 0.0f), 1.0f, SOUND_BOUMm, 0.45f), PART_ALWAYS});
        result.push_back({CrashSphere(glm::vec3(-2.3f, 1.0f, 0.0f), 1.0f, SOUND_BOUMm, 0.45f), PART_ALWAYS});
        result.push_back({CrashSphere(glm::vec3(-4.7f, 1.0f, 0.0f), 1.0f, SOUND_BOUMm, 0.45f), PART_ALWAYS});
        result.push_back({CrashSphere(glm::vec3(-7.0f, 1.0f, 0.0f), 1.0f, SOUND_BOUMm, 0.45f), PART_ALWAYS});
    }

    if ( type == OBJECT_TEEN3 )  // jar with pencils
    {
        result.push_back({CrashSphere(glm::vec3( 0.0f, 4.0f, 0.0f), 4.0f, SOUND_BOUMm, 0.45f), PART_ALWAYS});
    }

    if ( type == OBJECT_TEEN4 )  // scissors
    {
        result.push_back({CrashSphere(glm::vec3(-9.0f, 1.0f, 0.0f), 1.0f, SOUND_BOUMm, 0.45f), PART_ALWAYS});
        result.push_back({CrashSphere(glm::vec3(-6.0f, 1.0f, 0.0f), 1.1f, SOUND_BOUMm, 0.45f), PART_ALWAYS});
        result.push_back({CrashSphere(glm::vec3(-3.0f, 1.0f, 0.0f), 1.2f, SOUND_BOUMm, 0.45f), PART_ALWAYS});
        result.push_back({CrashSphere(glm::vec3( 0.0f, 1.0f, 0.0f), 1.3f, SOUND_BOUMm, 0.45f), PART_ALWAYS});
        result.push_back({CrashSphere(glm::vec3( 5.1f, 1.0f,-1.3f), 2.6f, SOUND_BOUMm, 0.45f), PART_ALWAYS});
        result.push_back({CrashSphere(glm::vec3( 8.0f, 1.0f, 2.2f), 2.3f, SOUND_BOUMm, 0.45f), PART_ALWAYS});
        result.push_back({CrashSphere(glm::vec3( 9.4f, 1.0f,-2.0f), 2.0f, SOUND_BOUMm, 0.45f), PART_ALWAYS});
    }

    if ( type == OBJECT_TEEN6 )  // book 1
    {
        result.push_back({CrashSphere(glm::vec3(-5.0f, 3.0f, 7.5f), 5.0f, SOUND_BOUMm, 0.45f), PART_ALWAYS});
        result.push_back({CrashSphere(glm::vec3( 4.5f, 3.0f, 7.5f), 5.0f, SOUND_BOUMm, 0.45f), PART_ALWAYS});
        result.push_back({CrashSphere(glm::vec3(-5.0f, 3.0f, 0.0f), 5.0f, SOUND_BOUMm, 0.45f), PART_ALWAYS});
        result.push_back({CrashSphere(glm::vec3( 4.5f, 3.0f, 0.0f), 5.0f, SOUND_BOUMm, 0.45f), PART_ALWAYS});
        result.push_back({CrashSphere(glm::vec3(-5.0f, 3.0f,-7.5f), 5.0f, SOUND_BOUMm, 0.45f), PART_ALWAYS});
        result.push_back({CrashSphere(glm::vec3( 4.5f, 3.0f,-7.5f), 5.0f, SOUND_BOUMm, 0.45f), PART_ALWAYS});
    }

    if ( type == OBJECT_TEEN7 )  // book 2
    {
        result.push_back({CrashSphere(glm::vec3(-5.0f, 3.0f, 7.5f), 5.0f, SOUND_BOUMm, 0.45f), PART_ALWAYS});
        result.push_back({CrashSphere(glm::vec3( 4.5f, 3.0f, 7.5f), 5.0f, SOUND_BOUMm, 0.45f), PART_ALWAYS});
        result.push_back({CrashSphere(glm::vec3(-5.0f, 3.0f, 0.0f), 5.0f, SOUND_BOUMm, 0.45f), PART_ALWAYS});
        result.push_back({CrashSphere(glm::vec3( 4.5f, 3.0f, 0.0f), 5.0f, SOUND_BOUMm, 0.45f), PART_ALWAYS});
        result.push_back({CrashSphere(glm::vec3(-5.0f, 3.0f,-7.5f), 5.0f, SOUND_BOUMm, 0.45f), PART_ALWAYS});
        result.push_back({CrashSphere(glm::vec3( 4.5f, 3.0f,-7.5f), 5.0f, SOUND_BOUMm, 0.45f), PART_ALWAYS});
    }

    if ( type == OBJECT_TEEN8 )  // a stack of books 1
    {
        result.push_back({CrashSphere(glm::vec3(-5.0f, 3.0f, 7.5f), 5.0f, SOUND_BOUMm, 0.45f), PART_ALWAYS});
        result.push_back({CrashSphere(glm::vec3( 4.5f, 3.0f, 7.5f), 5.0f, SOUND_BOUMm, 0.45f), PART_ALWAYS});
        result.push_back({CrashSphere(glm::vec3(-5.0f, 3.0f, 0.0f), 5.0f, SOUND_BOUMm, 0.45f), PART_ALWAYS});
        result.push_back({CrashSphere(glm::vec3( 4.5f, 3.0f, 0.0f), 5.0f, SOUND_BOUMm, 0.45f), PART_ALWAYS});
        result.push_back({CrashSphere(glm::vec3(-5.0f, 3.0f,-7.5f), 5.0f, SOUND_BOUMm, 0.45f), PART_ALWAYS});
        result.push_back({CrashSphere(glm::vec3( 4.5f, 3.0f,-7.5f), 5.0f, SOUND_BOUMm, 0.45f), PART_ALWAYS});
    }

    if ( type == OBJECT_TEEN9 )  // a stack of books 2
    {
        result.push_back({CrashSphere(glm::vec3(-5.0f, 3.0f, 7.5f), 5.0f, SOUND_BOUMm, 0.45f), PART_ALWAYS});
        result.push_back({CrashSphere(glm::vec3( 4.5f, 3.0f, 7.5f), 5.0f, SOUND_BOUMm, 0.45f), PART_ALWAYS});
        result.push_back({CrashSphere(glm::vec3(-5.0f, 3.0f, 0.0f), 5.0f, SOUND_BOUMm, 0.45f), PART_ALWAYS});
        result.push_back({CrashSphere(glm::vec3( 4.5f, 3.0f, 0.0f), 5.0f, SOUND_BOUMm, 0.45f), PART_ALWAYS});
        result.push_back({CrashSphere(glm::vec3(-5.0f, 3.0f,-7.5f), 5.0f, SOUND_BOUMm, 0.45f), PART_ALWAYS});
        result.push_back({CrashSphere(glm::vec3( 4.5f, 3.0f,-7.5f), 5.0f, SOUND_BOUMm, 0.45f), PART_ALWAYS});
    }

    if ( type == OBJECT_TEEN10 )  // bookcase
    {
        result.push_back({CrashSphere(glm::vec3(-26.0f, 3.0f, 0.0f), 6.0f, SOUND_BOUMm, 0.45f), PART_ALWAYS});
        result.push_back({CrashSphere(glm::vec3(-15.0f, 3.0f,-4.0f), 6.0f, SOUND_BOUMm, 0.45f), PART_ALWAYS});
        result.push_back({CrashSphere(glm::vec3(-15.0f, 3.0f, 5.0f), 6.0f, SOUND_BOUMm, 0.45f), PART_ALWAYS});
        result.push_back({CrashSphere(glm::vec3( -4.0f, 3.0f,-4.0f), 6.0f, SOUND_BOUMm, 0.45f), PART_ALWAYS});
        result.push_back({CrashSphere(glm::vec3( -4.0f, 3.0f, 5.0f), 6.0f, SOUND_BOUMm, 0.45f), PART_ALWAYS});
        result.push_back({CrashSphere(glm::vec3(  6.0f, 3.0f,-4.0f), 6.0f, SOUND_BOUMm, 0.45f), PART_ALWAYS});
        result.push_back({CrashSphere(glm::vec3(  6.0f, 3.0f, 4.0f), 6.0f, SOUND_BOUMm, 0.45f), PART_ALWAYS});
        result.push_back({CrashSphere(glm::vec3( 14.0f, 3.0f,-3.0f), 6.0f, SOUND_BOUMm, 0.45f), PART_ALWAYS});
        result.push_back({CrashSphere(glm::vec3( 14.0f, 3.0f, 2.0f), 6.0f, SOUND_BOUMm, 0.45f), PART_ALWAYS});
        result.push_back({CrashSphere(glm::vec3( 24.0f, 3.0f, 5.0f), 6.0f, SOUND_BOUMm, 0.45f), PART_ALWAYS});
    }

    if ( type == OBJECT_TEEN12 )  // coke
    {
        result.push_back({CrashSphere(glm::vec3( 0.0f, 4.0f, 0.0f), 4.0f, SOUND_BOUMm, 0.45f), PART_ALWAYS});
    }

    if ( type == OBJECT_TEEN13 )  // cardboard farm
    {
        result.push_back({CrashSphere(glm::vec3(-10.0f, 4.0f,-7.0f), 5.0f, SOUND_BOUMm, 0.45f), PART_ALWAYS});
        result.push_back({CrashSphere(glm::vec3(  0.0f, 4.0f,-7.0f), 5.0f, SOUND_BOUMm, 0.45f), PART_ALWAYS});
        result.push_back({CrashSphere(glm::vec3( 10.0f, 4.0f,-7.0f), 5.0f, SOUND_BOUMm, 0.45f), PART_ALWAYS});
        result.push_back({CrashSphere(glm::vec3(-10.0f, 4.0f, 0.0f), 5.0f, SOUND_BOUMm, 0.45f), PART_ALWAYS});
        result.push_back({CrashSphere(glm::vec3(  0.0f, 4.0f, 0.0f), 5.0f, SOUND_BOUMm, 0.45f), PART_ALWAYS});
        result.push_back({CrashSphere(glm::vec3( 10.0f, 4.0f, 0.0f), 5.0f, SOUND_BOUMm, 0.45f), PART_ALWAYS});
        result.push_back({CrashSphere(glm::vec3(-10.0f, 4.0f, 7.0f), 5.0f, SOUND_BOUMm, 0.45f), PART_ALWAYS});
        result.push_back({CrashSphere(glm::vec3(  0.0f, 4.0f, 7.0f), 5.0f, SOUND_BOUMm, 0.45f), PART_ALWAYS});
        result.push_back({CrashSphere(glm::vec3( 10.0f, 4.0f, 7.0f), 5.0f, SOUND_BOUMm, 0.45f), PART_ALWAYS});
    }

    if ( type == OBJECT_TEEN14 )  // open box
    {
        result.push_back({CrashSphere(glm::vec3(-10.0f, 4.0f,-7.0f), 5.0f, SOUND_BOUMm, 0.45f), PART_ALWAYS});
        result.push_back({CrashSphere(glm::vec3(  0.0f, 4.0f,-7.0f), 5.0f, SOUND_BOUMm, 0.45f), PART_ALWAYS});
        result.push_back({CrashSphere(glm::vec3( 10.0f, 4.0f,-7.0f), 5.0f, SOUND_BOUMm, 0.45f), PART_ALWAYS});
        result.push_back({CrashSphere(glm::vec3(-10.0f, 4.0f, 0.0f), 5.0f, SOUND_BOUMm, 0.45f), PART_ALWAYS});
        result.push_back({CrashSphere(glm::vec3(  0.0f, 4.0f, 0.0f), 5.0f, SOUND_BOUMm, 0.45f), PART_ALWAYS});
        result.push_back({CrashSphere(glm::vec3( 10.0f, 4.0f, 0.0f), 5.0f, SOUND_BOUMm, 0.45f), PART_ALWAYS});
        result.push_back({CrashSphere(glm::vec3(-10.0f, 4.0f, 7.0f), 5.0f, SOUND_BOUMm, 0.45f), PART_ALWAYS});
        result.push_back({CrashSphere(glm::vec3(  0.0f, 4.0f, 7.0f), 5.0f, SOUND_BOUMm, 0.45f), PART_ALWAYS});
        result.push_back({CrashSphere(glm::vec3( 10.0f, 4.0f, 7.0f), 5.0f, SOUND_BOUMm, 0.45f), PART_ALWAYS});
    }

    if ( type == OBJECT_TEEN15 )  // stack of cartons
    {
        result.push_back({CrashSphere(glm::vec3(-10.0f, 4.0f,-7.0f), 5.0f, SOUND_BOUMm, 0.45f), PART_ALWAYS});
        result.push_back({CrashSphere(glm::vec3(  0.0f, 4.0f,-7.0f), 5.0f, SOUND_BOUMm, 0.45f), PART_ALWAYS});
        result.push_back({CrashSphere(glm::vec3( 10.0f, 4.0f,-7.0f), 5.0f, SOUND_BOUMm, 0.45f), PART_ALWAYS});
        result.push_back({CrashSphere(glm::vec3(-10.0f, 4.0f, 0.0f), 5.0f, SOUND_BOUMm, 0.45f), PART_ALWAYS});
        result.push_back({CrashSphere(glm::vec3(  0.0f, 4.0f, 0.0f), 5.0f, SOUND_BOUMm, 0.45f), PART_ALWAYS});
        result.push_back({CrashSphere(glm::vec3( 10.0f, 4.0f, 0.0f), 5.0f, SOUND_BOUMm, 0.45f), PART_ALWAYS});
        result.push_back({CrashSphere(glm::vec3(-10.0f, 4.0f, 7.0f), 5.0f, SOUND_BOUMm, 0.45f), PART_ALWAYS});
        result.push_back({CrashSphere(glm::vec3(  0.0f, 4.0f, 7.0f), 5.0f, SOUND_BOUMm, 0.45f), PART_ALWAYS});
        result.push_back({CrashSphere(glm::vec3( 10.0f, 4.0f, 7.0f), 5.0f, SOUND_BOUMm, 0.45f), PART_ALWAYS});
    }

    if ( type == OBJECT_TEEN16 )  // watering can
    {
        result.push_back({CrashSphere(glm::vec3(-8.0f, 4.0f, 0.0f), 12.0f, SOUND_BOUMm, 0.45f), PART_ALWAYS});
        result.push_back({CrashSphere(glm::vec3( 8.0f, 4.0f, 0.0f), 12.0f, SOUND_BOUMm, 0.45f), PART_ALWAYS});
    }

    if ( type == OBJECT_TEEN17 )  // wheel |
    {
        result.push_back({CrashSphere(glm::vec3( 0.0f, 31.0f, 0.0f), 31.0f, SOUND_BOUMm, 0.45f), PART_ALWAYS});
    }

    if ( type == OBJECT_TEEN18 )  // wheel /
    {
        result.push_back({CrashSphere(glm::vec3( 0.0f, 31.0f, 0.0f), 31.0f, SOUND_BOUMm, 0.45f), PART_ALWAYS});
    }

    if ( type == OBJECT_TEEN19 )  // wheel =
    {
        result.push_back({CrashSphere(glm::vec3( 0.0f, 10.0f, 0.0f), 32.0f, SOUND_BOUMm, 0.45f), PART_ALWAYS});
    }

    if ( type == OBJECT_TEEN20 )  // wall with shelf
    {
        result.push_back({CrashSphere(glm::vec3(-175.0f, 0.0f,  -5.0f), 4.0f, SOUND_BOUMm, 0.45f), PART_ALWAYS});
        result.push_back({CrashSphere(glm::vec3(-175.0f, 0.0f, -35.0f), 4.0f, SOUND_BOUMm, 0.45f), PART_ALWAYS});
        result.push_back({CrashSphere(glm::vec3( -55.0f, 0.0f,  -5.0f), 4.0f, SOUND_BOUMm, 0.45f), PART_ALWAYS});
        result.push_back({CrashSphere(glm::vec3( -55.0f, 0.0f, -35.0f), 4.0f, SOUND_BOUMm, 0.45f), PART_ALWAYS});
        result.push_back({CrashSphere(glm::vec3( -37.0f, 0.0f,  -5.0f), 4.0f, SOUND_BOUMm, 0.45f), PART_ALWAYS});
        result.push_back({CrashSphere(glm::vec3( -37.0f, 0.0f, -35.0f), 4.0f, SOUND_BOUMm, 0.45f), PART_ALWAYS});
        result.push_back({CrashSphere(glm::vec3(  83.0f, 0.0f,  -5.0f), 4.0f, SOUND_BOUMm, 0.45f), PART_ALWAYS});
        result.push_back({CrashSphere(glm::vec3(  83.0f, 0.0f, -35.0f), 4.0f, SOUND_BOUMm, 0.45f), PART_ALWAYS});
    }

    if ( type == OBJECT_TEEN22 )  // wall with door and shelf
    {
        result.push_back({CrashSphere(glm::vec3(-135.0f, 0.0f,  -5.0f), 4.0f, SOUND_BOUMm, 0.45f), PART_ALWAYS});
        result.push_back({CrashSphere(glm::vec3(-135.0f, 0.0f, -35.0f), 4.0f, SOUND_BOUMm, 0.45f), PART_ALWAYS});
        result.push_back({CrashSphere(glm::vec3( -15.0f, 0.0f,  -5.0f), 4.0f, SOUND_BOUMm, 0.45f), PART_ALWAYS});
        result.push_back({CrashSphere(glm::vec3( -15.0f, 0.0f, -35.0f), 4.0f, SOUND_BOUMm, 0.45f), PART_ALWAYS});
    }

    if ( type == OBJECT_TEEN23 )  // skateboard on wheels
    {
        result.push_back({CrashSphere(glm::vec3(-23.0f, 2.0f, 7.0f), 3.0f, SOUND_BOUMm, 0.45f), PART_ALWAYS});
        result.push_back({CrashSphere(glm::vec3(-23.0f, 2.0f, 0.0f), 3.0f, SOUND_BOUMm, 0.45f), PART_ALWAYS});
        result.push_back({CrashSphere(glm::vec3(-23.0f, 2.0f,-7.0f), 3.0f, SOUND_BOUMm, 0.45f), PART_ALWAYS});
        result.push_back({CrashSphere(glm::vec3( 23.0f, 2.0f, 7.0f), 3.0f, SOUND_BOUMm, 0.45f), PART_ALWAYS});
        result.push_back({CrashSphere(glm::vec3( 23.0f, 2.0f, 0.0f), 3.0f, SOUND_BOUMm, 0.45f), PART_ALWAYS});
        result.push_back({CrashSphere(glm::vec3( 23.0f, 2.0f,-7.0f), 3.0f, SOUND_BOUMm, 0.45f), PART_ALWAYS});
        result.push_back({CrashSphere(glm::vec3(-10.0f, 2.0f, 0.0f), 11.0f, SOUND_BOUMm, 0.45f), PART_OPTION_1});
        result.push_back({CrashSphere(glm::vec3( 10.0f, 2.0f, 0.0f), 11.0f, SOUND_BOUMm, 0.45f), PART_OPTION_1});
    }

    if ( type == OBJECT_TEEN24 )  // skate /
    {
        result.push_back({CrashSphere(glm::vec3(-12.0f, 0.0f, -3.0f), 3.0f, SOUND_BOUMm, 0.45f), PART_ALWAYS});
        result.push_back({CrashSphere(glm::vec3(-12.0f, 0.0f,  3.0f), 3.0f, SOUND_BOUMm, 0.45f), PART_ALWAYS});
    }

    if ( type == OBJECT_TEEN25 )  // skate /
    {
        result.push_back({CrashSphere(glm::vec3(-12.0f, 0.0f, -3.0f), 3.0f, SOUND_BOUMm, 0.45f), PART_ALWAYS});
        result.push_back({CrashSphere(glm::vec3(-12.0f, 0.0f,  3.0f), 3.0f, SOUND_BOUMm, 0.45f), PART_ALWAYS});
    }

    if ( type == OBJECT_TEEN27 )  // large plant?
    {
        result.push_back({CrashSphere(glm::vec3(0.0f, 0.0f, 0.0f), 4.0f, SOUND_BOUM, 0.10f), PART_ALWAYS});
    }

    if ( type == OBJECT_TEEN28 )  // bottle?
    {
        result.push_back({CrashSphere(glm::vec3(0.0f, 2.0f, 0.0f), 5.0f, SOUND_BOUM, 0.10f), PART_ALWAYS});
    }

    if ( type == OBJECT_TEEN30 )  // jump?
    {
        result.push_back({CrashSphere(glm::vec3(0.0f, 4.0f, 0.0f), 15.0f, SOUND_BOUM, 0.10f), PART_ALWAYS});
    }

    if ( type == OBJECT_TEEN31 )  // basket?
    {
        result.push_back({CrashSphere(glm::vec3(-10.0f, 2.0f, 0.0f), 5.0f, SOUND_BOUM, 0.10f), PART_ALWAYS});
        result.push_back({CrashSphere(glm::vec3(  0.0f, 2.0f, 0.0f), 6.0f, SOUND_BOUM, 0.10f), PART_ALWAYS});
        result.push_back({CrashSphere(glm::vec3(  9.0f, 4.0f, 1.0f), 6.0f, SOUND_BOUM, 0.10f), PART_ALWAYS});
    }

    if ( type == OBJECT_TEEN32 )  // chair?
    {
        result.push_back({CrashSphere(glm::vec3( 17.5f, 1.0f,  17.5f), 3.5f, SOUND_BOUM, 0.10f), PART_ALWAYS});
        result.push_back({CrashSphere(glm::vec3( 17.5f, 1.0f, -17.5f), 3.5f, SOUND_BOUM, 0.10f), PART_ALWAYS});
        result.push_back({CrashSphere(glm::vec3(-17.5f, 1.0f,  17.5f), 3.5f, SOUND_BOUM, 0.10f), PART_ALWAYS});
        result.push_back({CrashSphere(glm::vec3(-17.5f, 1.0f, -17.5f), 3.5f, SOUND_BOUM, 0.10f), PART_ALWAYS});
    }

    if ( type == OBJECT_TEEN33 )  // panel?
    {
        result.push_back({CrashSphere(glm::vec3(0.0f, 2.0f, 0.0f), 4.0f, SOUND_BOUM, 0.10f), PART_ALWAYS});
    }

    if ( type == OBJECT_TEEN34 )  // stone?
    {
        result.push_back({CrashSphere(glm::vec3(0.0f, 2.0f, 0.0f), 4.0f, SOUND_BOUM, 0.10f), PART_ALWAYS});
    }

    if ( type == OBJECT_TEEN35 )  // pipe?
    {
        result.push_back({CrashSphere(glm::vec3(-40.0f, 5.0f, 0.0f), 10.0f, SOUND_BOUM, 0.10f), PART_ALWAYS});
        result.push_back({CrashSphere(glm::vec3(-20.0f, 5.0f, 0.0f), 10.0f, SOUND_BOUM, 0.10f), PART_ALWAYS});
        result.push_back({CrashSphere(glm::vec3(  0.0f, 5.0f, 0.0f), 10.0f, SOUND_BOUM, 0.10f), PART_ALWAYS});
        result.push_back({CrashSphere(glm::vec3( 20.0f, 5.0f, 0.0f), 10.0f, SOUND_BOUM, 0.10f), PART_ALWAYS});
        result.push_back({CrashSphere(glm::vec3( 40.0f, 5.0f, 0.0f), 10.0f, SOUND_BOUM, 0.10f), PART_ALWAYS});
    }

    if ( type == OBJECT_TEEN38 )  // fan?
    {
        result.push_back({CrashSphere(glm::vec3(0.0f, 2.0f, 0.0f), 10.0f, SOUND_BOUM, 0.10f), PART_ALWAYS});
    }

    if ( type == OBJECT_TEEN39 )  // potted plant?
    {
        result.push_back({CrashSphere(glm::vec3(0.0f, 2.0f, 0.0f), 8.5f, SOUND_BOUM, 0.10f), PART_ALWAYS});
    }

    if ( type == OBJECT_TEEN40 )  // balloon?
    {
        result.push_back({CrashSphere(glm::vec3(0.0f, 5.0f, 0.0f), 11.0f, SOUND_BOUM, 0.10f), PART_ALWAYS});
    }

    if ( type == OBJECT_TEEN42 )  // clover?
    {
        result.push_back({CrashSphere(glm::vec3(0.0f, 2.0f, 0.0f), 2.0f, SOUND_BOUM, 0.10f), PART_ALWAYS});
    }

    if ( type == OBJECT_TEEN43 )  // clover?
    {
        result.push_back({CrashSphere(glm::vec3(0.0f, 2.0f, 0.0f), 2.0f, SOUND_BOUM, 0.10f), PART_ALWAYS});
    }

    if ( type == OBJECT_TEEN44 )  // car?
    {
        result.push_back({CrashSphere(glm::vec3(0.0f, 10.0f, 0.0f), 55.0f, SOUND_BOUM, 0.10f), PART_ALWAYS});
    }

    if ( type == OBJECT_HOME1 )
    {
        result.push_back({CrashSphere(glm::vec3(0.0f, 5.0f, 0.0f), 10.0f, SOUND_BOUMs, 0.25f), PART_ALWAYS});
    }

    if ( type == OBJECT_QUARTZ0 )
    {
        result.push_back({CrashSphere(glm::vec3(0.0f, 2.0f, 0.0f), 3.5f, SOUND_BOUMm, 0.45f), PART_ALWAYS});
    }
    if ( type == OBJECT_QUARTZ1 )
    {
        result.push_back({CrashSphere(glm::vec3(0.0f, 4.0f, 0.0f), 5.0f, SOUND_BOUMm, 0.45f), PART_ALWAYS});
    }
    if ( type == OBJECT_QUARTZ2 )
    {
        result.push_back({CrashSphere(glm::vec3(0.0f, 6.0f, 0.0f), 6.0f, SOUND_BOUMm, 0.45f), PART_ALWAYS});
    }
    if ( type == OBJECT_QUARTZ3 )
    {
        result.push_back({CrashSphere(glm::vec3(0.0f, 10.0f, 0.0f), 10.0f, SOUND_BOUMm, 0.45f), PART_ALWAYS});
    }

    if ( type == OBJECT_ROOT0 )
    {
        result.push_back({CrashSphere(glm::vec3(-5.0f,  1.0f,  0.0f), 2.0f, SOUND_BOUMv, 0.15f), PART_ALWAYS});
        result.push_back({CrashSphere(glm::vec3( 4.0f,  1.0f,  2.0f), 2.0f, SOUND_BOUMv, 0.15f), PART_ALWAYS});
        result.push_back({CrashSphere(glm::vec3( 4.0f,  1.0f, -3.0f), 2.0f, SOUND_BOUMv, 0.15f), PART_ALWAYS});
        result.push_back({CrashSphere(glm::vec3( 2.0f,  5.0f, -1.0f), 1.5f, SOUND_BOUMv, 0.15f), PART_ALWAYS});
        result.push_back({CrashSphere(glm::vec3(-4.0f,  5.0f, -1.0f), 1.0f, SOUND_BOUMv, 0.15f), PART_ALWAYS});
        result.push_back({CrashSphere(glm::vec3(-2.0f,  8.0f, -0.5f), 1.0f, SOUND_BOUMv, 0.15f), PART_ALWAYS});
        result.push_back({CrashSphere(glm::vec3( 0.0f, 10.0f, -0.5f), 1.0f, SOUND_BOUMv, 0.15f), PART_ALWAYS});
    }
    if ( type == OBJECT_ROOT1 )
    {
        result.push_back({CrashSphere(glm::vec3(-4.0f,  1.0f,  1.0f), 2.0f, SOUND_BOUMv, 0.15f), PART_ALWAYS});
        result.push_back({CrashSphere(glm::vec3( 0.0f,  1.0f,  2.0f), 1.5f, SOUND_BOUMv, 0.15f), PART_ALWAYS});
        result.push_back({CrashSphere(glm::vec3( 3.0f,  1.0f, -2.0f), 2.0f, SOUND_BOUMv, 0.15f), PART_ALWAYS});
        result.push_back({CrashSphere(glm::vec3(-2.0f,  5.0f,  1.0f), 1.0f, SOUND_BOUMv, 0.15f), PART_ALWAYS});
        result.push_back({CrashSphere(glm::vec3( 2.0f,  5.0f,  0.0f), 1.0f, SOUND_BOUMv, 0.15f), PART_ALWAYS});
        result.push_back({CrashSphere(glm::vec3( 0.0f,  8.0f,  1.0f), 1.0f, SOUND_BOUMv, 0.15f), PART_ALWAYS});
        result.push_back({CrashSphere(glm::vec3( 0.0f, 12.0f,  1.0f), 1.0f, SOUND_BOUMv, 0.15f), PART_ALWAYS});
    }
    if ( type == OBJECT_ROOT2 )
    {
        result.push_back({CrashSphere(glm::vec3(-3.0f,  1.0f,  0.5f), 2.0f, SOUND_BOUMv, 0.15f), PART_ALWAYS});
        result.push_back({CrashSphere(glm::vec3( 3.0f,  1.0f, -1.0f), 2.0f, SOUND_BOUMv, 0.15f), PART_ALWAYS});
        result.push_back({CrashSphere(glm::vec3(-1.0f,  4.5f,  0.0f), 1.0f, SOUND_BOUMv, 0.15f), PART_ALWAYS});
        result.push_back({CrashSphere(glm::vec3( 3.0f,  7.0f,  1.0f), 1.0f, SOUND_BOUMv, 0.15f), PART_ALWAYS});
        result.push_back({CrashSphere(glm::vec3( 0.0f,  7.0f, -1.0f), 1.0f, SOUND_BOUMv, 0.15f), PART_ALWAYS});
        result.push_back({CrashSphere(glm::vec3( 4.0f, 11.0f,  1.0f), 1.0f, SOUND_BOUMv, 0.15f), PART_ALWAYS});
    }
    if ( type == OBJECT_ROOT3 )
    {
        result.push_back({CrashSphere(glm::vec3(-4.0f,  1.0f,  1.0f), 3.0f, SOUND_BOUMv, 0.15f), PART_ALWAYS});
        result.push_back({CrashSphere(glm::vec3( 4.0f,  1.0f, -3.0f), 3.0f, SOUND_BOUMv, 0.15f), PART_ALWAYS});
        result.push_back({CrashSphere(glm::vec3( 6.0f,  1.0f,  4.0f), 3.0f, SOUND_BOUMv, 0.15f), PART_ALWAYS});
        result.push_back({CrashSphere(glm::vec3(-2.5f,  7.0f,  2.0f), 2.0f, SOUND_BOUMv, 0.15f), PART_ALWAYS});
        result.push_back({CrashSphere(glm::vec3( 4.0f,  7.0f,  2.0f), 2.0f, SOUND_BOUMv, 0.15f), PART_ALWAYS});
        result.push_back({CrashSphere(glm::vec3( 3.0f,  6.0f, -1.0f), 1.0f, SOUND_BOUMv, 0.15f), PART_ALWAYS});
        result.push_back({CrashSphere(glm::vec3( 0.0f, 12.0f,  0.0f), 2.0f, SOUND_BOUMv, 0.15f), PART_ALWAYS});
        result.push_back({CrashSphere(glm::vec3( 1.0f, 16.0f,  0.0f), 1.0f, SOUND_BOUMv, 0.15f), PART_ALWAYS});
    }
    if ( type == OBJECT_ROOT4 )
    {
        result.push_back({CrashSphere(glm::vec3( -7.0f,  2.0f,  3.0f), 4.0f, SOUND_BOUMv, 0.15f), PART_ALWAYS});
        result.push_back({CrashSphere(glm::vec3(  5.0f,  2.0f, -6.0f), 4.0f, SOUND_BOUMv, 0.15f), PART_ALWAYS});
        result.push_back({CrashSphere(glm::vec3(  6.0f,  2.0f,  6.0f), 3.0f, SOUND_BOUMv, 0.15f), PART_ALWAYS});
        result.push_back({CrashSphere(glm::vec3(-11.0f,  1.0f, -2.0f), 2.0f, SOUND_BOUMv, 0.15f), PART_ALWAYS});
        result.push_back({CrashSphere(glm::vec3(  1.0f,  1.0f, -7.0f), 2.0f, SOUND_BOUMv, 0.15f), PART_ALWAYS});
        result.push_back({CrashSphere(glm::vec3( -4.0f, 10.0f,  3.0f), 2.0f, SOUND_BOUMv, 0.15f), PART_ALWAYS});
        result.push_back({CrashSphere(glm::vec3(  1.0f, 11.0f,  7.0f), 2.0f, SOUND_BOUMv, 0.15f), PART_ALWAYS});
        result.push_back({CrashSphere(glm::vec3(  3.0f, 11.0f, -3.0f), 2.0f, SOUND_BOUMv, 0.15f), PART_ALWAYS});
        result.push_back({CrashSphere(glm::vec3( -3.0f, 17.0f,  1.0f), 2.0f, SOUND_BOUMv, 0.15f), PART_ALWAYS});
        result.push_back({CrashSphere(glm::vec3( -3.0f, 23.0f, -1.0f), 2.0f, SOUND_BOUMv, 0.15f), PART_ALWAYS});
    }
    if ( type == OBJECT_ROOT5 )  // gravity root ?
    {
        result.push_back({CrashSphere(glm::vec3( -7.0f,  2.0f,  3.0f), 4.0f, SOUND_BOUMv, 0.15f), PART_ALWAYS});
        result.push_back({CrashSphere(glm::vec3(  5.0f,  2.0f, -6.0f), 4.0f, SOUND_BOUMv, 0.15f), PART_ALWAYS});
        result.push_back({CrashSphere(glm::vec3(  6.0f,  2.0f,  6.0f), 3.0f, SOUND_BOUMv, 0.15f), PART_ALWAYS});
        result.push_back({CrashSphere(glm::vec3(-11.0f,  1.0f, -2.0f), 2.0f, SOUND_BOUMv, 0.15f), PART_ALWAYS});
        result.push_back({CrashSphere(glm::vec3(  1.0f,  1.0f, -7.0f), 2.0f, SOUND_BOUMv, 0.15f), PART_ALWAYS});
        result.push_back({CrashSphere(glm::vec3( -4.0f, 10.0f,  3.0f), 2.0f, SOUND_BOUMv, 0.15f), PART_ALWAYS});
        result.push_back({CrashSphere(glm::vec3(  1.0f, 11.0f,  7.0f), 2.0f, SOUND_BOUMv, 0.15f), PART_ALWAYS});
        result.push_back({CrashSphere(glm::vec3(  3.0f, 11.0f, -3.0f), 2.0f, SOUND_BOUMv, 0.15f), PART_ALWAYS});
        result.push_back({CrashSphere(glm::vec3( -3.0f, 17.0f,  1.0f), 2.0f, SOUND_BOUMv, 0.15f), PART_ALWAYS});
        result.push_back({CrashSphere(glm::vec3( -3.0f, 23.0f, -1.0f), 2.0f, SOUND_BOUMv, 0.15f), PART_ALWAYS});
    }

    if ( type == OBJECT_RUINmobilew1 )  // vehicle had wheels?
    {
        result.push_back({CrashSphere(glm::vec3(0.0f, 2.8f, 0.0f), 3.0f, SOUND_BOUMm, 0.45f), PART_ALWAYS});
    }

    if ( type == OBJECT_RUINmobilew2 )  // vehicle has wheels?
    {
        result.push_back({CrashSphere(glm::vec3(0.0f, 2.8f, 0.0f), 3.0f, SOUND_BOUMm, 0.45f), PART_ALWAYS});
    }

    if ( type == OBJECT_RUINmobilet1 )  // vehicle have caterpillars?
    {
        result.push_back({CrashSphere(glm::vec3(1.0f, 2.8f, -1.0f), 5.0f, SOUND_BOUMm, 0.45f), PART_ALWAYS});
    }

    if ( type == OBJECT_RUINmobilet2 )  // vehicle have caterpillars?
    {
        result.push_back({CrashSphere(glm::vec3(0.0f, 2.8f, 0.0f), 5.0f, SOUND_BOUMm, 0.45f), PART_ALWAYS});
    }

    if ( type == OBJECT_RUINmobiler1 )  // vehicle skating?
    {
        result.push_back({CrashSphere(glm::vec3(1.0f, 2.8f, -1.0f), 5.0f, SOUND_BOUMm, 0.45f), PART_ALWAYS});
    }

    if ( type == OBJECT_RUINmobiler2 )  // vehicle skating?
    {
        result.push_back({CrashSphere(glm::vec3(0.0f, 1.0f, 0.0f), 5.0f, SOUND_BOUMm, 0.45f), PART_ALWAYS});
    }

    if ( type == OBJECT_RUINfactory )  // factory ?
    {
        result.push_back({CrashSphere(glm::vec3(  9.0f,  1.0f, -11.0f), 5.0f, SOUND_BOUMm, 0.45f), PART_ALWAYS});
        result.push_back({CrashSphere(glm::vec3(  0.0f,  2.0f, -11.0f), 4.0f, SOUND_BOUMm, 0.45f), PART_ALWAYS});
        result.push_back({CrashSphere(glm::vec3(-10.0f,  4.0f, -10.0f), 5.0f, SOUND_BOUMm, 0.45f), PART_ALWAYS});
        result.push_back({CrashSphere(glm::vec3(-12.0f, 11.0f,  -4.0f), 3.0f, SOUND_BOUMm, 0.45f), PART_ALWAYS});
        result.push_back({CrashSphere(glm::vec3(-10.0f,  4.0f,  -2.0f), 3.0f, SOUND_BOUMm, 0.45f), PART_ALWAYS});
        result.push_back({CrashSphere(glm::vec3(-11.0f,  8.0f,   3.0f), 3.0f, SOUND_BOUMm, 0.45f), PART_ALWAYS});
        result.push_back({CrashSphere(glm::vec3(-11.0f,  2.0f,   4.0f), 3.0f, SOUND_BOUMm, 0.45f), PART_ALWAYS});
        result.push_back({CrashSphere(glm::vec3(-11.0f,  2.0f,  10.0f), 3.0f, SOUND_BOUMm, 0.45f), PART_ALWAYS});
        result.push_back({CrashSphere(glm::vec3( -4.0f,  0.0f,  10.0f), 3.0f, SOUND_BOUMm, 0.45f), PART_ALWAYS});
    }

    if ( type == OBJECT_RUINdoor )  // converter holder?
    {
        result.push_back({CrashSphere(glm::vec3(0.0f, 0.0f, 0.0f), 5.0f, SOUND_BOUMm, 0.45f), PART_ALWAYS});
    }

    if ( type == OBJECT_RUINsupport )  // radar holder?
    {
        result.push_back({CrashSphere(glm::vec3(0.0f, 0.0f, 0.0f), 3.0f, SOUND_BOUMm, 0.45f), PART_ALWAYS});
    }

    if ( type == OBJECT_RUINradar )  // radar base?
    {
        result.push_back({CrashSphere(glm::vec3(0.0f, 0.0f, 0.0f), 5.0f, SOUND_BOUMm, 0.45f), PART_ALWAYS});
    }

    if ( type == OBJECT_RUINconvert )  // converter?
    {
        result.push_back({CrashSphere(glm::vec3(-10.0f,  0.0f,  4.0f), 5.0f, SOUND_BOUMm, 0.45f), PART_ALWAYS});
        result.push_back({CrashSphere(glm::vec3(-10.0f,  0.0f, -4.0f), 5.0f, SOUND_BOUMm, 0.45f), PART_ALWAYS});
    }

    if ( type == OBJECT_RUINbase )  // base?
    {
        result.push_back({CrashSphere(glm::vec3(  0.0f, 15.0f,   0.0f),28.0f, SOUND_BOUMm, 0.45f), PART_ALWAYS});
        result.push_back({CrashSphere(glm::vec3( 17.0f,  6.0f,  42.0f), 6.0f, SOUND_BOUMm, 0.45f), PART_ALWAYS});
        result.push_back({CrashSphere(glm::vec3( 17.0f, 17.0f,  42.0f), 4.0f, SOUND_BOUMm, 0.45f), PART_ALWAYS});
        result.push_back({CrashSphere(glm::vec3(-17.0f,  6.0f,  42.0f), 6.0f, SOUND_BOUMm, 0.45f), PART_ALWAYS});
        result.push_back({CrashSphere(glm::vec3(-17.0f, 17.0f,  42.0f), 4.0f, SOUND_BOUMm, 0.45f), PART_ALWAYS});
        result.push_back({CrashSphere(glm::vec3(-42.0f,  6.0f,  17.0f), 6.0f, SOUND_BOUMm, 0.45f), PART_ALWAYS});
        result.push_back({CrashSphere(glm::vec3(-42.0f, 17.0f,  17.0f), 4.0f, SOUND_BOUMm, 0.45f), PART_ALWAYS});
        result.push_back({CrashSphere(glm::vec3(-42.0f,  6.0f, -17.0f), 6.0f, SOUND_BOUMm, 0.45f), PART_ALWAYS});
        result.push_back({CrashSphere(glm::vec3(-42.0f, 17.0f, -17.0f), 4.0f, SOUND_BOUMm, 0.45f), PART_ALWAYS});
        result.push_back({CrashSphere(glm::vec3(-17.0f,  6.0f, -42.0f), 6.0f, SOUND_BOUMm, 0.45f), PART_ALWAYS});
        result.push_back({CrashSphere(glm::vec3(-17.0f, 10.0f, -42.0f), 4.0f, SOUND_BOUMm, 0.45f), PART_ALWAYS});
        result.push_back({CrashSphere(glm::vec3( 15.0f, 13.0f, -34.0f), 3.0f, SOUND_BOUMm, 0.45f), PART_ALWAYS});
        result.push_back({CrashSphere(glm::vec3( 31.0f, 15.0f, -13.0f), 3.0f, SOUND_BOUMm, 0.45f), PART_ALWAYS});
        result.push_back({CrashSphere(glm::vec3( 21.0f,  8.0f, -39.0f), 5.0f, SOUND_BOUMm, 0.45f), PART_ALWAYS});
        result.push_back({CrashSphere(glm::vec3( 26.0f,  8.0f, -33.0f), 5.0f, SOUND_BOUMm, 0.45f), PART_ALWAYS});
    }

    if ( type == OBJECT_RUINhead )  // base cap?
    {
        result.push_back({CrashSphere(glm::vec3(  0.0f, 13.0f,   0.0f),20.0f, SOUND_BOUMm, 0.45f), PART_ALWAYS});
        result.push_back({CrashSphere(glm::vec3(  0.0f, -8.0f,   0.0f), 5.0f, SOUND_BOUMm, 0.45f), PART_ALWAYS});
        result.push_back({CrashSphere(glm::vec3(  0.0f,-16.0f,   0.0f), 3.0f, SOUND_BOUMm, 0.45f), PART_ALWAYS});
        result.push_back({CrashSphere(glm::vec3(  0.0f,-22.0f,   0.0f), 3.0f, SOUND_BOUMm, 0.45f), PART_ALWAYS});
        result.push_back({CrashSphere(glm::vec3(-21.0f,  7.0f,   9.0f), 8.0f, SOUND_BOUMm, 0.45f), PART_ALWAYS});
        result.push_back({CrashSphere(glm::vec3( -9.0f,  7.0f,  21.0f), 8.0f, SOUND_BOUMm, 0.45f), PART_ALWAYS});
        result.push_back({CrashSphere(glm::vec3( 21.0f,  7.0f,   9.0f), 8.0f, SOUND_BOUMm, 0.45f), PART_ALWAYS});
        result.push_back({CrashSphere(glm::vec3(  9.0f,  7.0f,  21.0f), 8.0f, SOUND_BOUMm, 0.45f), PART_ALWAYS});
        result.push_back({CrashSphere(glm::vec3(-21.0f,  7.0f,  -9.0f), 8.0f, SOUND_BOUMm, 0.45f), PART_ALWAYS});
        result.push_back({CrashSphere(glm::vec3( -9.0f,  7.0f, -21.0f), 8.0f, SOUND_BOUMm, 0.45f), PART_ALWAYS});
        result.push_back({CrashSphere(glm::vec3( 21.0f,  7.0f,  -9.0f), 8.0f, SOUND_BOUMm, 0.45f), PART_ALWAYS});
        result.push_back({CrashSphere(glm::vec3(  9.0f,  7.0f, -21.0f), 8.0f, SOUND_BOUMm, 0.45f), PART_ALWAYS});
    }

    if ( type == OBJECT_APOLLO1 )  // LEM ?
    {
        result.push_back({CrashSphere(glm::vec3(  0.0f, 4.0f,   0.0f), 9.0f, SOUND_BOUMm, 0.45f), PART_ALWAYS});
        result.push_back({CrashSphere(glm::vec3( 11.0f, 5.0f,   0.0f), 3.0f, SOUND_BOUMm, 0.45f), PART_ALWAYS});
        result.push_back({CrashSphere(glm::vec3(-11.0f, 5.0f,   0.0f), 3.0f, SOUND_BOUMm, 0.45f), PART_ALWAYS});
        result.push_back({CrashSphere(glm::vec3(  0.0f, 5.0f, -11.0f), 3.0f, SOUND_BOUMm, 0.45f), PART_ALWAYS});
        result.push_back({CrashSphere(glm::vec3(  0.0f, 5.0f,  11.0f), 3.0f, SOUND_BOUMm, 0.45f), PART_ALWAYS});
    }

    if ( type == OBJECT_APOLLO4 )  // module?
    {
        result.push_back({CrashSphere(glm::vec3(0.0f, 2.0f, 0.0f), 2.0f, SOUND_BOUMm, 0.45f), PART_ALWAYS});
    }

    if ( type == OBJECT_APOLLO5 )  // antenna?
    {
        result.push_back({CrashSphere(glm::vec3(0.0f, 4.0f, 0.0f), 3.0f, SOUND_BOUMm, 0.35f), PART_ALWAYS});
    }

    if ( type == OBJECT_PORTICO )
    {
        result.push_back({CrashSphere(glm::vec3(  0.0f, 28.0f,   0.0f), 45.5f, SOUND_BOUMm, 0.45f), PART_ALWAYS});
        result.push_back({CrashSphere(glm::vec3( 27.0f, 10.0f, -42.0f), 15.0f, SOUND_BOUMm, 0.45f), PART_ALWAYS});
        result.push_back({CrashSphere(glm::vec3(  0.0f, 10.0f, -42.0f), 15.0f, SOUND_BOUMm, 0.45f), PART_ALWAYS});
        result.push_back({CrashSphere(glm::vec3(-27.0f, 10.0f, -42.0f), 15.0f, SOUND_BOUMm, 0.45f), PART_ALWAYS});
        result.push_back({CrashSphere(glm::vec3( 27.0f, 10.0f,  42.0f), 15.0f, SOUND_BOUMm, 0.45f), PART_ALWAYS});
        result.push_back({CrashSphere(glm::vec3(  0.0f, 10.0f,  42.0f), 15.0f, SOUND_BOUMm, 0.45f), PART_ALWAYS});
        result.push_back({CrashSphere(glm::vec3(-27.0f, 10.0f,  42.0f), 15.0f, SOUND_BOUMm, 0.45f), PART_ALWAYS});
        result.push_back({CrashSphere(glm::vec3(-32.0f, 45.0f, -32.0f), 10.0f, SOUND_BOUMm, 0.45f), PART_ALWAYS});
        result.push_back({CrashSphere(glm::vec3(-32.0f, 45.0f,  32.0f), 10.0f, SOUND_BOUMm, 0.45f), PART_ALWAYS});
        result.push_back({CrashSphere(glm::vec3( 32.0f, 45.0f, -32.0f), 10.0f, SOUND_BOUMm, 0.45f), PART_ALWAYS});
        result.push_back({CrashSphere(glm::vec3( 32.0f, 45.0f,  32.0f), 10.0f, SOUND_BOUMm, 0.45f), PART_ALWAYS});
    }

    if ( type == OBJECT_BASE )
    {
        result.push_back({CrashSphere(glm::vec3(  0.0f, 33.0f,   0.0f),  2.5f, SOUND_BOUMm, 0.45f), PART_ALWAYS});
        result.push_back({CrashSphere(glm::vec3(  0.0f, 39.0f,   0.0f),  2.5f, SOUND_BOUMm, 0.45f), PART_ALWAYS});
        result.push_back({CrashSphere(glm::vec3(  0.0f, 45.0f,   0.0f),  2.5f, SOUND_BOUMm, 0.45f), PART_ALWAYS});
        result.push_back({CrashSphere(glm::vec3(  0.0f, 51.0f,   0.0f),  2.5f, SOUND_BOUMm, 0.45f), PART_ALWAYS});
        result.push_back({CrashSphere(glm::vec3(  0.0f, 57.0f,   0.0f),  2.5f, SOUND_BOUMm, 0.45f), PART_ALWAYS});
        result.push_back({CrashSphere(glm::vec3(  0.0f, 63.0f,   0.0f),  2.5f, SOUND_BOUMm, 0.45f), PART_ALWAYS});
        result.push_back({CrashSphere(glm::vec3(  0.0f, 69.0f,   0.0f),  2.5f, SOUND_BOUMm, 0.45f), PART_ALWAYS});
        result.push_back({CrashSphere(glm::vec3(  0.0f, 82.0f,   0.0f),  8.0f, SOUND_BOUMm, 0.45f), PART_ALWAYS});
        result.push_back({CrashSphere(glm::vec3( 18.0f, 94.0f,   0.0f), 10.0f, SOUND_BOUMm, 0.45f), PART_ALWAYS});
        result.push_back({CrashSphere(glm::vec3(-18.0f, 94.0f,   0.0f), 10.0f, SOUND_BOUMm, 0.45f), PART_ALWAYS});
        result.push_back({CrashSphere(glm::vec3(  0.0f, 94.0f,  18.0f), 10.0f, SOUND_BOUMm, 0.45f), PART_ALWAYS});
        result.push_back({CrashSphere(glm::vec3(  0.0f, 94.0f, -18.0f), 10.0f, SOUND_BOUMm, 0.45f), PART_ALWAYS});
        result.push_back({CrashSphere(glm::vec3( 13.0f, 94.0f,  13.0f), 10.0f, SOUND_BOUMm, 0.45f), PART_ALWAYS});
        result.push_back({CrashSphere(glm::vec3(-13.0f, 94.0f,  13.0f), 10.0f, SOUND_BOUMm, 0.45f), PART_ALWAYS});
        result.push_back({CrashSphere(glm::vec3( 13.0f, 94.0f, -13.0f), 10.0f, SOUND_BOUMm, 0.45f), PART_ALWAYS});
        result.push_back({CrashSphere(glm::vec3(-13.0f, 94.0f, -13.0f), 10.0f, SOUND_BOUMm, 0.45f), PART_ALWAYS});
        result.push_back({CrashSphere(glm::vec3(  0.0f,104.0f,   0.0f), 14.0f, SOUND_BOUMm, 0.45f), PART_ALWAYS});
    }

    if ( type == OBJECT_DERRICK )
    {
        result.push_back({CrashSphere(glm::vec3(0.0f,  0.0f, 0.0f), 6.0f, SOUND_BOUMm, 0.45f), PART_ALWAYS});
        result.push_back({CrashSphere(glm::vec3(0.0f, 10.0f, 0.0f), 5.0f, SOUND_BOUMm, 0.45f), PART_ALWAYS});
        result.push_back({CrashSphere(glm::vec3(0.0f, 17.0f, 0.0f), 6.0f, SOUND_BOUMm, 0.45f), PART_ALWAYS});
        result.push_back({CrashSphere(glm::vec3(0.0f, 26.0f, 0.0f), 3.0f, SOUND_BOUMm, 0.45f), PART_ALWAYS});
        result.push_back({CrashSphere(glm::vec3(7.0f, 17.0f, 0.0f), 3.0f, SOUND_BOUMm, 0.45f), PART_ALWAYS});
    }

    if ( type == OBJECT_RESEARCH )
    {
        result.push_back({CrashSphere(glm::vec3(0.0f,  0.0f, 0.0f), 9.0f, SOUND_BOUMm, 0.45f), PART_ALWAYS});
        result.push_back({CrashSphere(glm::vec3(0.0f,  6.0f, 0.0f), 9.0f, SOUND_BOUMm, 0.45f), PART_ALWAYS});
        result.push_back({CrashSphere(glm::vec3(0.0f, 14.0f, 0.0f), 7.0f, SOUND_BOUMm, 0.45f), PART_ALWAYS});
    }

    if ( type == OBJECT_RADAR )
    {
        result.push_back({CrashSphere(glm::vec3(0.0f,  3.0f, 0.0f), 6.0f, SOUND_BOUMm, 0.45f), PART_ALWAYS});
        result.push_back({CrashSphere(glm::vec3(0.0f, 11.0f, 0.0f), 6.0f, SOUND_BOUMm, 0.45f), PART_ALWAYS});
    }

    if ( type == OBJECT_ENERGY )
    {
        result.push_back({CrashSphere(glm::vec3(-2.0f, 13.0f, 0.0f), 6.0f, SOUND_BOUMm, 0.45f), PART_ALWAYS});
        result.push_back({CrashSphere(glm::vec3(-7.0f,  3.0f, 0.0f), 5.0f, SOUND_BOUMm, 0.45f), PART_ALWAYS});
        result.push_back({CrashSphere(glm::vec3( 0.0f,  1.0f, 0.0f), 1.5f, SOUND_BOUMm, 0.45f), PART_ALWAYS});
    }

    if ( type == OBJECT_LABO )
    {
        result.push_back({CrashSphere(glm::vec3(  0.0f,  1.0f,  0.0f), 1.5f, SOUND_BOUMm, 0.45f), PART_ALWAYS});
        result.push_back({CrashSphere(glm::vec3(  0.0f, 11.0f,  0.0f), 4.0f, SOUND_BOUMm, 0.45f), PART_ALWAYS});
        result.push_back({CrashSphere(glm::vec3(-10.0f, 10.0f,  0.0f), 4.0f, SOUND_BOUMm, 0.45f), PART_ALWAYS});
        result.push_back({CrashSphere(glm::vec3(-12.0f,  3.0f,  3.0f), 4.0f, SOUND_BOUMm, 0.45f), PART_ALWAYS});
        result.push_back({CrashSphere(glm::vec3(-12.0f,  3.0f, -3.0f), 4.0f, SOUND_BOUMm, 0.45f), PART_ALWAYS});
    }

    if ( type == OBJECT_FACTORY )
    {
        for (int i=0 ; i<2 ; i++ )
        {
            float s = static_cast<float>(i*2-1);
            result.push_back({CrashSphere(glm::vec3(-10.0f,  2.0f, 11.0f*s), 4.0f, SOUND_BOUMm, 0.45f), PART_ALWAYS});
            result.push_back({CrashSphere(glm::vec3( -3.0f,  2.0f, 11.0f*s), 4.0f, SOUND_BOUMm, 0.45f), PART_ALWAYS});
            result.push_back({CrashSphere(glm::vec3(  3.0f,  2.0f, 11.0f*s), 4.0f, SOUND_BOUMm, 0.45f), PART_ALWAYS});
            result.push_back({CrashSphere(glm::vec3( 10.0f,  2.0f, 11.0f*s), 4.0f, SOUND_BOUMm, 0.45f), PART_ALWAYS});
            result.push_back({CrashSphere(glm::vec3(-10.0f,  9.0f, 11.0f*s), 4.0f, SOUND_BOUMm, 0.45f), PART_ALWAYS});
            result.push_back({CrashSphere(glm::vec3( -3.0f,  9.0f, 11.0f*s), 4.0f, SOUND_BOUMm, 0.45f), PART_ALWAYS});
            result.push_back({CrashSphere(glm::vec3(  3.0f,  9.0f, 11.0f*s), 4.0f, SOUND_BOUMm, 0.45f), PART_ALWAYS});
            result.push_back({CrashSphere(glm::vec3( 10.0f,  9.0f, 11.0f*s), 4.0f, SOUND_BOUMm, 0.45f), PART_ALWAYS});
            result.push_back({CrashSphere(glm::vec3(-10.0f, 16.0f, 11.0f*s), 4.0f, SOUND_BOUMm, 0.45f), PART_ALWAYS});
            result.push_back({CrashSphere(glm::vec3( -3.0f, 16.0f, 11.0f*s), 4.0f, SOUND_BOUMm, 0.45f), PART_ALWAYS});
            result.push_back({CrashSphere(glm::vec3(  3.0f, 16.0f, 11.0f*s), 4.0f, SOUND_BOUMm, 0.45f), PART_ALWAYS});
            result.push_back({CrashSphere(glm::vec3( 10.0f, 16.0f, 11.0f*s), 4.0f, SOUND_BOUMm, 0.45f), PART_ALWAYS});
            result.push_back({CrashSphere(glm::vec3(-10.0f, 16.0f,  4.0f*s), 4.0f, SOUND_BOUMm, 0.45f), PART_ALWAYS});
            result.push_back({CrashSphere(glm::vec3( -3.0f, 16.0f,  4.0f*s), 4.0f, SOUND_BOUMm, 0.45f), PART_ALWAYS});
            result.push_back({CrashSphere(glm::vec3(  3.0f, 16.0f,  4.0f*s), 4.0f, SOUND_BOUMm, 0.45f), PART_ALWAYS});
            result.push_back({CrashSphere(glm::vec3( 10.0f, 16.0f,  4.0f*s), 4.0f, SOUND_BOUMm, 0.45f), PART_ALWAYS});
            result.push_back({CrashSphere(glm::vec3(-10.0f,  2.0f,  4.0f*s), 4.0f, SOUND_BOUMm, 0.45f), PART_ALWAYS});
            result.push_back({CrashSphere(glm::vec3(-10.0f,  9.0f,  4.0f*s), 4.0f, SOUND_BOUMm, 0.45f), PART_ALWAYS});
        }
        result.push_back({CrashSphere(glm::vec3(-10.0f, 21.0f, -4.0f), 3.0f, SOUND_BOUMm, 0.45f), PART_ALWAYS});
    }

    if ( type == OBJECT_REPAIR )
    {
        result.push_back({CrashSphere(glm::vec3(-11.0f,  0.0f,  4.0f), 5.0f, SOUND_BOUMm, 0.45f), PART_ALWAYS});
        result.push_back({CrashSphere(glm::vec3(-11.0f,  0.0f,  0.0f), 5.0f, SOUND_BOUMm, 0.45f), PART_ALWAYS});
        result.push_back({CrashSphere(glm::vec3(-11.0f,  0.0f, -4.0f), 5.0f, SOUND_BOUMm, 0.45f), PART_ALWAYS});
        result.push_back({CrashSphere(glm::vec3(-11.0f, 10.0f,  0.0f), 5.0f, SOUND_BOUMm, 0.45f), PART_ALWAYS});
    }

    if ( type == OBJECT_DESTROYER )
    {
        result.push_back({CrashSphere(glm::vec3(-3.5f, 0.0f, -13.5f), 4.0f, SOUND_BOUMm, 0.45f), PART_ALWAYS});
        result.push_back({CrashSphere(glm::vec3( 3.5f, 0.0f, -13.5f), 4.0f, SOUND_BOUMm, 0.45f), PART_ALWAYS});
        result.push_back({CrashSphere(glm::vec3(-3.5f, 0.0f,  13.5f), 4.0f, SOUND_BOUMm, 0.45f), PART_ALWAYS});
        result.push_back({CrashSphere(glm::vec3( 3.5f, 0.0f,  13.5f), 4.0f, SOUND_BOUMm, 0.45f), PART_ALWAYS});
    }

    if ( type == OBJECT_STATION )
    {
        result.push_back({CrashSphere(glm::vec3(-15.0f, 2.0f, 0.0f), 5.0f, SOUND_BOUMm, 0.45f), PART_ALWAYS});
        result.push_back({CrashSphere(glm::vec3(-15.0f, 6.0f, 0.0f), 4.0f, SOUND_BOUMm, 0.45f), PART_ALWAYS});
    }

    if ( type == OBJECT_CONVERT )
    {
        result.push_back({CrashSphere(glm::vec3(-10.0f,  2.0f,  4.0f), 5.0f, SOUND_BOUMm, 0.45f), PART_ALWAYS});
        result.push_back({CrashSphere(glm::vec3(-10.0f,  2.0f, -4.0f), 5.0f, SOUND_BOUMm, 0.45f), PART_ALWAYS});
        result.push_back({CrashSphere(glm::vec3(-10.0f,  9.0f,  0.0f), 6.0f, SOUND_BOUMm, 0.45f), PART_ALWAYS});
        result.push_back({CrashSphere(glm::vec3(  0.0f, 14.0f,  0.0f), 1.5f, SOUND_BOUMm, 0.45f), PART_ALWAYS});
    }

    if ( type == OBJECT_TOWER )
    {
        result.push_back({CrashSphere(glm::vec3(0.0f,  0.0f, 0.0f), 6.5f, SOUND_BOUMm, 0.45f), PART_ALWAYS});
        result.push_back({CrashSphere(glm::vec3(0.0f,  8.0f, 0.0f), 4.0f, SOUND_BOUMm, 0.45f), PART_ALWAYS});
        result.push_back({CrashSphere(glm::vec3(0.0f, 15.0f, 0.0f), 5.0f, SOUND_BOUMm, 0.45f), PART_ALWAYS});
        result.push_back({CrashSphere(glm::vec3(0.0f, 24.0f, 0.0f), 5.0f, SOUND_BOUMm, 0.45f), PART_ALWAYS});
    }

    if ( type == OBJECT_NUCLEAR )
    {
        result.push_back({CrashSphere(glm::vec3( 0.0f,  0.0f, 0.0f), 19.0f, SOUND_BOUMm, 0.45f), PART_ALWAYS});
        result.push_back({CrashSphere(glm::vec3( 0.0f, 24.0f, 0.0f), 15.0f, SOUND_BOUMm, 0.45f), PART_ALWAYS});
        result.push_back({CrashSphere(glm::vec3(22.0f,  1.0f, 0.0f),  1.5f, SOUND_BOUMm, 0.45f), PART_ALWAYS});
    }

    if ( type == OBJECT_PARA )
    {
        result.push_back({CrashSphere(glm::vec3( 13.0f,  3.0f,  13.0f),  3.0f, SOUND_BOUMm, 0.45f), PART_ALWAYS});
        result.push_back({CrashSphere(glm::vec3( 11.0f, 15.0f,  11.0f),  2.0f, SOUND_BOUMm, 0.45f), PART_ALWAYS});
        result.push_back({CrashSphere(glm::vec3(-13.0f,  3.0f,  13.0f),  3.0f, SOUND_BOUMm, 0.45f), PART_ALWAYS});
        result.push_back({CrashSphere(glm::vec3(-11.0f, 15.0f, -11.0f),  2.0f, SOUND_BOUMm, 0.45f), PART_ALWAYS});
        result.push_back({CrashSphere(glm::vec3( 13.0f,  3.0f, -13.0f),  3.0f, SOUND_BOUMm, 0.45f), PART_ALWAYS});
        result.push_back({CrashSphere(glm::vec3( 11.0f, 15.0f, -11.0f),  2.0f, SOUND_BOUMm, 0.45f), PART_ALWAYS});
        result.push_back({CrashSphere(glm::vec3(-13.0f,  3.0f, -13.0f),  3.0f, SOUND_BOUMm, 0.45f), PART_ALWAYS});
        result.push_back({CrashSphere(glm::vec3(-11.0f, 15.0f, -11.0f),  2.0f, SOUND_BOUMm, 0.45f), PART_ALWAYS});
        result.push_back({CrashSphere(glm::vec3(  0.0f, 26.0f,   0.0f),  9.0f, SOUND_BOUMm, 0.45f), PART_ALWAYS});
        result.push_back({CrashSphere(glm::vec3(  0.0f, 54.0f,   0.0f), 14.0f, SOUND_BOUMm, 0.45f), PART_ALWAYS});
    }

    if ( type == OBJECT_SAFE )
    {
        result.push_back({CrashSphere(glm::vec3(0.0f, 1.0f, 0.0f), 13.0f, SOUND_BOUMm, 0.45f), PART_ALWAYS});
    }

    if ( type == OBJECT_HUSTON )
    {
        result.push_back({CrashSphere(glm::vec3( 15.0f,  6.0f, -53.0f), 16.0f, SOUND_BOUMm, 0.45f), PART_ALWAYS});
        result.push_back({CrashSphere(glm::vec3(-15.0f,  6.0f, -53.0f), 16.0f, SOUND_BOUMm, 0.45f), PART_ALWAYS});
        result.push_back({CrashSphere(glm::vec3( 15.0f,  6.0f, -26.0f), 16.0f, SOUND_BOUMm, 0.45f), PART_ALWAYS});
        result.push_back({CrashSphere(glm::vec3(-15.0f,  6.0f, -26.0f), 16.0f, SOUND_BOUMm, 0.45f), PART_ALWAYS});
        result.push_back({CrashSphere(glm::vec3( 15.0f,  6.0f,   0.0f), 16.0f, SOUND_BOUMm, 0.45f), PART_ALWAYS});
        result.push_back({CrashSphere(glm::vec3(-15.0f,  6.0f,   0.0f), 16.0f, SOUND_BOUMm, 0.45f), PART_ALWAYS});
        result.push_back({CrashSphere(glm::vec3( 15.0f,  6.0f,  26.0f), 16.0f, SOUND_BOUMm, 0.45f), PART_ALWAYS});
        result.push_back({CrashSphere(glm::vec3(-15.0f,  6.0f,  26.0f), 16.0f, SOUND_BOUMm, 0.45f), PART_ALWAYS});
        result.push_back({CrashSphere(glm::vec3( 15.0f,  6.0f,  53.0f), 16.0f, SOUND_BOUMm, 0.45f), PART_ALWAYS});
        result.push_back({CrashSphere(glm::vec3(-15.0f,  6.0f,  53.0f), 16.0f, SOUND_BOUMm, 0.45f), PART_ALWAYS});
        result.push_back({CrashSphere(glm::vec3(  0.0f, 27.0f,  30.0f), 12.0f, SOUND_BOUMm, 0.45f), PART_ALWAYS});
        result.push_back({CrashSphere(glm::vec3(  0.0f, 45.0f,  30.0f), 14.0f, SOUND_BOUMm, 0.45f), PART_ALWAYS});
        result.push_back({CrashSphere(glm::vec3( 26.0f,  4.0f, -61.0f),  5.0f, SOUND_BOUMm, 0.45f), PART_ALWAYS});
        result.push_back({CrashSphere(glm::vec3(-26.0f,  4.0f, -61.0f),  5.0f, SOUND_BOUMm, 0.45f), PART_ALWAYS});
        result.push_back({CrashSphere(glm::vec3( 26.0f,  4.0f,  61.0f),  5.0f, SOUND_BOUMm, 0.45f), PART_ALWAYS});
        result.push_back({CrashSphere(glm::vec3(-26.0f,  4.0f,  61.0f),  5.0f, SOUND_BOUMm, 0.45f), PART_ALWAYS});
    }

    if ( type == OBJECT_TARGET1 )
    {
        result.push_back({CrashSphere(glm::vec3(  0.0f, 50.0f+14.0f, 0.0f),  3.0f, SOUND_BOUMm, 0.45f), PART_ALWAYS});
        result.push_back({CrashSphere(glm::vec3( -7.0f, 50.0f+12.0f, 0.0f),  3.0f, SOUND_BOUMm, 0.45f), PART_ALWAYS});
        result.push_back({CrashSphere(glm::vec3(  7.0f, 50.0f+12.0f, 0.0f),  3.0f, SOUND_BOUMm, 0.45f), PART_ALWAYS});
        result.push_back({CrashSphere(glm::vec3(-12.0f, 50.0f+ 7.0f, 0.0f),  3.0f, SOUND_BOUMm, 0.45f), PART_ALWAYS});
        result.push_back({CrashSphere(glm::vec3( 12.0f, 50.0f+ 7.0f, 0.0f),  3.0f, SOUND_BOUMm, 0.45f), PART_ALWAYS});
        result.push_back({CrashSphere(glm::vec3(-14.0f, 50.0f+ 0.0f, 0.0f),  3.0f, SOUND_BOUMm, 0.45f), PART_ALWAYS});
        result.push_back({CrashSphere(glm::vec3( 14.0f, 50.0f+ 0.0f, 0.0f),  3.0f, SOUND_BOUMm, 0.45f), PART_ALWAYS});
        result.push_back({CrashSphere(glm::vec3(-12.0f, 50.0f- 7.0f, 0.0f),  3.0f, SOUND_BOUMm, 0.45f), PART_ALWAYS});
        result.push_back({CrashSphere(glm::vec3( 12.0f, 50.0f- 7.0f, 0.0f),  3.0f, SOUND_BOUMm, 0.45f), PART_ALWAYS});
        result.push_back({CrashSphere(glm::vec3( -7.0f, 50.0f-12.0f, 0.0f),  3.0f, SOUND_BOUMm, 0.45f), PART_ALWAYS});
        result.push_back({CrashSphere(glm::vec3(  7.0f, 50.0f-12.0f, 0.0f),  3.0f, SOUND_BOUMm, 0.45f), PART_ALWAYS});
        result.push_back({CrashSphere(glm::vec3(  0.0f, 50.0f-14.0f, 0.0f),  3.0f, SOUND_BOUMm, 0.45f), PART_ALWAYS});
        result.push_back({CrashSphere(glm::vec3(0.0f, 30.0f, 0.0f), 2.0f, SOUND_BOUMm, 0.45f), PART_ALWAYS});
        result.push_back({CrashSphere(glm::vec3(0.0f, 24.0f, 0.0f), 3.0f, SOUND_BOUMm, 0.45f), PART_ALWAYS});
        result.push_back({CrashSphere(glm::vec3(0.0f, 16.0f, 0.0f), 4.0f, SOUND_BOUMm, 0.45f), PART_ALWAYS});
        result.push_back({CrashSphere(glm::vec3(0.0f,  4.0f, 0.0f), 8.0f, SOUND_BOUMm, 0.45f), PART_ALWAYS});
    }

    if ( type == OBJECT_INFO )
    {
        result.push_back({CrashSphere(glm::vec3(0.0f,  3.0f, 0.0f), 6.0f, SOUND_BOUMm, 0.45f), PART_ALWAYS});
        result.push_back({CrashSphere(glm::vec3(0.0f, 11.0f, 0.0f), 6.0f, SOUND_BOUMm, 0.45f), PART_ALWAYS});
    }

    if ( type == OBJECT_MOTHER )
    {
        result.push_back({CrashSphere(glm::vec3(0.0f, 0.0f, 0.0f), 20.0f, SOUND_BOUM, 0.20f), PART_ALWAYS});
    }
    if ( type == OBJECT_ANT )
    {
        result.push_back({CrashSphere(glm::vec3(0.0f, -2.0f, 0.0f), 4.0f, SOUND_BOUM, 0.20f), PART_ALWAYS});
    }
    if ( type == OBJECT_BEE )
    {
        result.push_back({CrashSphere(glm::vec3(0.0f, 0.0f, 0.0f), 4.0f, SOUND_BOUM, 0.20f), PART_ALWAYS});
    }
    if ( type == OBJECT_SPIDER )
    {
        result.push_back({CrashSphere(glm::vec3(0.0f, -2.0f, 0.0f), 4.0f, SOUND_BOUM, 0.20f), PART_ALWAYS});
    }
    if ( type == OBJECT_WORM )
    {
        result.push_back({CrashSphere(glm::vec3(0.0f, 0.0f, 0.0f), 4.0f, SOUND_BOUM, 0.20f), PART_ALWAYS});
    }

    if ( type == OBJECT_HUMAN || type == OBJECT_TECH )
    {
        result.push_back({CrashSphere(glm::vec3(0.0f, 0.0f, 0.0f), 2.0f, SOUND_AIE, 0.20f), PART_ALWAYS});
    }

    if ( type == OBJECT_MOBILErt ||
         type == OBJECT_MOBILErc ||
         type == OBJECT_MOBILErr ||
         type == OBJECT_MOBILErs ||
         type == OBJECT_MOBILErp )
    {
        result.push_back({CrashSphere(glm::vec3(0.0f, 4.0f, 0.0f), 6.5f, SOUND_BOUMm, 0.45f), PART_ALWAYS});
    }
    if ( type == OBJECT_MOBILEsa ||
         type == OBJECT_MOBILEst )
    {
        result.push_back({CrashSphere(glm::vec3(0.0f, 3.0f, 0.0f), 4.5f, SOUND_BOUMm, 0.45f), PART_ALWAYS});
    }
    if ( type == OBJECT_MOBILEdr )
    {
        result.push_back({CrashSphere(glm::vec3(0.0f, 3.0f, 0.0f), 5.0f, SOUND_BOUMm, 0.45f), PART_ALWAYS});
    }
    if ( type == OBJECT_APOLLO2 )
    {
        result.push_back({CrashSphere(glm::vec3(0.0f, 0.0f, 0.0f), 8.0f, SOUND_BOUMm, 0.45f), PART_ALWAYS});
    }
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
         type == OBJECT_MOBILEtg ||
         type == OBJECT_MOBILEwt ||
         type == OBJECT_MOBILEtt ||
         type == OBJECT_MOBILEft ||
         type == OBJECT_MOBILEit )
    {
        result.push_back({CrashSphere(glm::vec3(0.0f, 3.0f, 0.0f), 4.5f, SOUND_BOUMm, 0.45f), PART_ALWAYS});
    }

    return result;
}

Math::Sphere CModeledHardcodeCollection::GetModeledCameraCollisionSphere(ObjectType type)
{
    if ( type == OBJECT_EGG )
    {
        return (Math::Sphere(glm::vec3(0.0f, 5.0f, 0.0f), 10.0f));
    }
    else if ( type == OBJECT_BOMB )
    {
        return (Math::Sphere(glm::vec3(0.0f, 0.0f, 0.0f), 3.0f));
    }
    else if ( type == OBJECT_BAG )
    {
        return (Math::Sphere(glm::vec3(0.0f, 0.0f, 0.0f), 4.0f));
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
        return (Math::Sphere(glm::vec3(0.0f, 1.0f, 0.0f), 1.5f));
    }

    if ( type == OBJECT_PLANT0 ||
         type == OBJECT_PLANT1 ||
         type == OBJECT_PLANT2 ||
         type == OBJECT_PLANT3 ||
         type == OBJECT_PLANT4 )  // standard?
    {
        return (Math::Sphere(glm::vec3(0.0f, 3.0f, 0.0f), 6.0f));
    }

    if ( type == OBJECT_PLANT10 ||
         type == OBJECT_PLANT11 ||
         type == OBJECT_PLANT12 ||
         type == OBJECT_PLANT13 ||
         type == OBJECT_PLANT14 )  // succulent?
    {
        return (Math::Sphere(glm::vec3(0.0f, 6.0f, 0.0f), 6.0f));
    }

    if ( type == OBJECT_PLANT15 ||
         type == OBJECT_PLANT16 ||
         type == OBJECT_PLANT17 ||
         type == OBJECT_PLANT18 )  // fern?
    {
        return (Math::Sphere(glm::vec3(0.0f, 3.0f, 0.0f), 6.0f));
    }

    if ( type == OBJECT_MUSHROOM1 )
    {
        return (Math::Sphere(glm::vec3(0.0f, 3.0f, 0.0f), 5.5f));
    }

    if ( type == OBJECT_MUSHROOM2 )
    {
        return (Math::Sphere(glm::vec3(0.0f, 4.0f, 0.0f), 5.5f));
    }

    if ( type == OBJECT_TEEN3 )  // jar with pencils
    {
        return (Math::Sphere(glm::vec3(0.0f, 4.0f, 0.0f), 4.0f));
    }

    if ( type == OBJECT_TEEN8 )  // a stack of books 1
    {
        return (Math::Sphere(glm::vec3(0.0f, 10.0f, 0.0f), 12.0f));
    }

    if ( type == OBJECT_TEEN9 )  // a stack of books 2
    {
        return (Math::Sphere(glm::vec3(0.0f, 10.0f, 0.0f), 12.0f));
    }

    if ( type == OBJECT_TEEN10 )  // bookcase
    {
        return (Math::Sphere(glm::vec3(0.0f, 6.0f, 0.0f), 20.0f));
    }

    if ( type == OBJECT_TEEN12 )  // coke
    {
        return (Math::Sphere(glm::vec3(0.0f, 9.0f, 0.0f), 5.0f));
    }

    if ( type == OBJECT_TEEN13 )  // cardboard farm
    {
        return (Math::Sphere(glm::vec3(0.0f, 5.0f, 0.0f), 15.0f));
    }

    if ( type == OBJECT_TEEN14 )  // open box
    {
        return (Math::Sphere(glm::vec3(0.0f, 5.0f, 0.0f), 15.0f));
    }

    if ( type == OBJECT_TEEN15 )  // stack of cartons
    {
        return (Math::Sphere(glm::vec3(0.0f, 5.0f, 0.0f), 15.0f));
    }

    if ( type == OBJECT_TEEN16 )  // watering can
    {
        return (Math::Sphere(glm::vec3(0.0f, 13.0f, 0.0f), 20.0f));
    }

    if ( type == OBJECT_TEEN17 )  // wheel |
    {
        return (Math::Sphere(glm::vec3(0.0f, 31.0f, 0.0f), 31.0f));
    }

    if ( type == OBJECT_TEEN18 )  // wheel /
    {
        return (Math::Sphere(glm::vec3(0.0f, 31.0f, 0.0f), 31.0f));
    }

    if ( type == OBJECT_TEEN19 )  // wheel =
    {
        return (Math::Sphere(glm::vec3(0.0f, 10.0f, 0.0f), 32.0f));
    }

    if ( type == OBJECT_TEEN30 )  // jump?
    {
        return (Math::Sphere(glm::vec3(0.0f, 15.0f, 0.0f), 17.0f));
    }

    if ( type == OBJECT_TEEN31 )  // basket?
    {
        return (Math::Sphere(glm::vec3(0.0f, 0.0f, 0.0f), 10.0f));
    }

    if ( type == OBJECT_TEEN32 )  // chair?
    {
        return (Math::Sphere(glm::vec3(0.0f, 0.0f, 0.0f), 26.0f));
    }


    if ( type == OBJECT_TEEN38 )  // fan?
    {
        return (Math::Sphere(glm::vec3(0.0f, 2.0f, 0.0f), 10.0f));
    }

    if ( type == OBJECT_TEEN39 )  // potted plant?
    {
        return (Math::Sphere(glm::vec3(0.0f, 2.0f, 0.0f), 8.5f));
    }

    if ( type == OBJECT_TEEN40 )  // balloon?
    {
        return (Math::Sphere(glm::vec3(0.0f, 14.0f, 0.0f), 15.0f));
    }

    if ( type == OBJECT_TEEN44 )  // car?
    {
        return (Math::Sphere(glm::vec3(0.0f, 10.0f, 0.0f), 55.0f));
    }

    if ( type == OBJECT_QUARTZ0 )
    {
        return (Math::Sphere(glm::vec3(0.0f, 2.0f, 0.0f), 3.5f));
    }
    if ( type == OBJECT_QUARTZ1 )
    {
        return (Math::Sphere(glm::vec3(0.0f, 4.0f, 0.0f), 5.0f));
    }
    if ( type == OBJECT_QUARTZ2 )
    {
        return (Math::Sphere(glm::vec3(0.0f, 6.0f, 0.0f), 6.0f));
    }
    if ( type == OBJECT_QUARTZ3 )
    {
        return (Math::Sphere(glm::vec3(0.0f, 10.0f, 0.0f), 10.0f));
    }

    if ( type == OBJECT_ROOT0 )
    {
//?     return (Math::Sphere(glm::vec3(0.0f, 6.0f, 0.0f), 11.0f));
    }
    if ( type == OBJECT_ROOT1 )
    {
//?     return (Math::Sphere(glm::vec3(0.0f, 6.0f, 0.0f), 12.0f));
    }
    if ( type == OBJECT_ROOT2 )
    {
//?     return (Math::Sphere(glm::vec3(0.0f, 6.0f, 0.0f), 10.0f));
    }
    if ( type == OBJECT_ROOT3 )
    {
//?     return (Math::Sphere(glm::vec3(0.0f, 10.0f, 0.0f), 14.0f));
    }
    if ( type == OBJECT_ROOT4 )
    {
//?     return (Math::Sphere(glm::vec3(0.0f, 12.0f, 0.0f), 20.0f));
    }
    if ( type == OBJECT_ROOT5 )  // gravity root ?
    {
//?     return (Math::Sphere(glm::vec3(0.0f, 12.0f, 0.0f), 20.0f));
    }

    if ( type == OBJECT_HOME1 )
    {
//?     return (Math::Sphere(glm::vec3(0.0f, 6.0f, 0.0f), 11.0f));
    }

    if ( type == OBJECT_RUINmobilew1 )  // vehicle had wheels?
    {
//?     return (Math::Sphere(glm::vec3(0.0f, 5.0f, 0.0f), 10.0f));
    }

    if ( type == OBJECT_RUINmobilew2 )  // vehicle has wheels?
    {
//?     return (Math::Sphere(glm::vec3(0.0f, 5.0f, 0.0f), 10.0f));
    }

    if ( type == OBJECT_RUINmobilet1 )  // vehicle have caterpillars?
    {
//?     return (Math::Sphere(glm::vec3(1.0f, 5.0f, -1.0f), 10.0f));
    }

    if ( type == OBJECT_RUINmobilet2 )  // vehicle have caterpillars?
    {
//?     return (Math::Sphere(glm::vec3(0.0f, 5.0f, 0.0f), 10.0f));
    }

    if ( type == OBJECT_RUINmobiler1 )  // vehicle skating?
    {
        return (Math::Sphere(glm::vec3(1.0f, 5.0f, -1.0f), 10.0f));
    }

    if ( type == OBJECT_RUINmobiler2 )  // vehicle skating?
    {
        return (Math::Sphere(glm::vec3(0.0f, 5.0f, 0.0f), 10.0f));
    }

    if ( type == OBJECT_RUINfactory )  // factory ?
    {
        return (Math::Sphere(glm::vec3(0.0f, 0.0f, 0.0f), 18.0f));
    }

    if ( type == OBJECT_RUINdoor )  // converter holder?
    {
//?     return (Math::Sphere(glm::vec3(0.0f, 0.0f, 0.0f), 6.0f));
    }

    if ( type == OBJECT_RUINsupport )  // radar holder?
    {
//?     return (Math::Sphere(glm::vec3(0.0f, 0.0f, 0.0f), 4.0f));
    }

    if ( type == OBJECT_RUINradar )  // radar base?
    {
//?     return (Math::Sphere(glm::vec3(0.0f, 0.0f, 0.0f), 6.0f));
    }

    if ( type == OBJECT_RUINconvert )  // converter?
    {
//?     return (Math::Sphere(glm::vec3(-3.0f, 0.0f, 0.0f), 14.0f));
    }

    if ( type == OBJECT_RUINbase )  // base?
    {
        return (Math::Sphere(glm::vec3(0.0f, 0.0f, 0.0f), 48.0f));
    }

    if ( type == OBJECT_RUINhead )  // base cap?
    {
        return (Math::Sphere(glm::vec3(0.0f, 0.0f, 0.0f), 35.0f));
    }

    if ( type == OBJECT_APOLLO1 )  // LEM ?
    {
        return (Math::Sphere(glm::vec3(0.0f, 4.0f, 0.0f), 9.0f));
    }


    if ( type == OBJECT_PORTICO )
    {
        return (Math::Sphere(glm::vec3(0.0f, 35.0f, 0.0f), 50.0f));
    }

    if ( type == OBJECT_BASE )
    {
        return (Math::Sphere(glm::vec3(0.0f, 45.0f, 0.0f), 10.0f));
    }

    if ( type == OBJECT_DERRICK )
    {
        return (Math::Sphere(glm::vec3(0.0f, 10.0f, 0.0f), 10.0f));
    }

    if ( type == OBJECT_RESEARCH )
    {
        return (Math::Sphere(glm::vec3(0.0f, 8.0f, 0.0f), 12.0f));
    }

    if ( type == OBJECT_RADAR )
    {
        return (Math::Sphere(glm::vec3(0.0f, 7.0f, 0.0f), 7.0f));
    }

    if ( type == OBJECT_ENERGY )
    {
        return (Math::Sphere(glm::vec3(-7.0f, 5.0f, 0.0f), 5.0f));
    }

    if ( type == OBJECT_LABO )
    {
        return (Math::Sphere(glm::vec3(-10.0f, 5.0f, 0.0f), 7.0f));
    }

    if ( type == OBJECT_FACTORY )
    {
        return (Math::Sphere(glm::vec3(0.0f, 10.0f, 0.0f), 18.0f));
    }

    if ( type == OBJECT_REPAIR )
    {
        return (Math::Sphere(glm::vec3(-11.0f, 13.0f, 0.0f), 15.0f));
    }

    if ( type == OBJECT_STATION )
    {
        return (Math::Sphere(glm::vec3(-15.0f, 5.0f, 0.0f), 6.0f));
    }

    if ( type == OBJECT_CONVERT )
    {
        return (Math::Sphere(glm::vec3(-3.0f, 8.0f, 0.0f), 14.0f));
    }

    if ( type == OBJECT_TOWER )
    {
        return (Math::Sphere(glm::vec3(0.0f, 5.0f, 0.0f), 7.0f));
    }

    if ( type == OBJECT_NUCLEAR )
    {
        return (Math::Sphere(glm::vec3(0.0f, 17.0f, 0.0f), 26.0f));
    }

    if ( type == OBJECT_PARA )
    {
        return (Math::Sphere(glm::vec3(0.0f, 10.0f, 0.0f), 20.0f));
    }

    if ( type == OBJECT_SAFE )
    {
        return (Math::Sphere(glm::vec3(0.0f, 1.0f, 0.0f), 13.0f));
    }

    if ( type == OBJECT_INFO )
    {
        return (Math::Sphere(glm::vec3(0.0f, 5.0f, 0.0f), 6.0f));
    }

    if ( type == OBJECT_MOTHER )
    {
        return (Math::Sphere(glm::vec3(-2.0f, 10.0f, 0.0f), 25.0f));
    }
    if ( type == OBJECT_ANT )
    {
        return (Math::Sphere(glm::vec3(-0.5f, 1.0f, 0.0f), 4.0f));
    }
    if ( type == OBJECT_BEE )
    {
        return (Math::Sphere(glm::vec3(-1.0f, 1.0f, 0.0f), 5.0f));
    }
    if ( type == OBJECT_SPIDER )
    {
        return (Math::Sphere(glm::vec3(-0.5f, 1.0f, 0.0f), 4.0f));
    }
    if ( type == OBJECT_WORM )
    {
        return (Math::Sphere(glm::vec3(0.0f, 0.0f, 0.0f), 5.0f));
    }

    if ( type == OBJECT_HUMAN || type == OBJECT_TECH )
    {
        return (Math::Sphere(glm::vec3(0.0f, 1.0f, 0.0f), 4.0f));
    }

    if ( type == OBJECT_MOBILErt ||
         type == OBJECT_MOBILErc ||
         type == OBJECT_MOBILErr ||
         type == OBJECT_MOBILErs ||
         type == OBJECT_MOBILErp )
    {
        return (Math::Sphere(glm::vec3(0.0f, 3.0f, 0.0f), 7.0f));
    }
    if ( type == OBJECT_MOBILEsa ||
         type == OBJECT_MOBILEst )
    {
        return (Math::Sphere(glm::vec3(0.0f, 3.0f, 0.0f), 6.0f));
    }
    if ( type == OBJECT_MOBILEdr )
    {
        return (Math::Sphere(glm::vec3(0.0f, 3.0f, 0.0f), 7.0f));
    }
    if ( type == OBJECT_APOLLO2 )
    {
        return Math::Sphere();
    }
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
         type == OBJECT_MOBILEtg ||
         type == OBJECT_MOBILEwt ||
         type == OBJECT_MOBILEtt ||
         type == OBJECT_MOBILEft ||
         type == OBJECT_MOBILEit )
    {
        return (Math::Sphere(glm::vec3(0.0f, 4.0f, 0.0f), 6.0f));
    }

    return Math::Sphere();
}


std::vector<CObjectModeledLevel> CModeledHardcodeCollection::GetModeledLevels(ObjectType type)
{
    std::vector<CObjectModeledLevel> result;

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

    if ( type == OBJECT_BASE )
    {
        result.push_back({28.6f, 73.4f, 30.0f, 0.4f});
    }
    if ( type == OBJECT_REPAIR )
    {
        result.push_back({7.0f, 9.0f, 1.0f, 0.5f});
    }
    if ( type == OBJECT_DESTROYER )
    {
        result.push_back({7.0f, 9.0f, 1.0f, 0.5f});
    }
    if ( type == OBJECT_STATION )
    {
        result.push_back({7.0f, 9.0f, 1.0f, 0.5f});
    }
    if ( type == OBJECT_CONVERT )
    {
        result.push_back({7.0f, 9.0f, 1.0f, 0.5f});
    }
    if ( type == OBJECT_PARA )
    {
        result.push_back({16.0f, 18.0f, 1.0f, 0.5f});
    }
    if ( type == OBJECT_SAFE )
    {
        result.push_back({18.0f, 20.0f, 1.0f, 0.5f});
    }
    if ( type == OBJECT_NEST )
    {
        result.push_back({3.0f, 5.0f, 1.0f, 0.5f});
    }
    if ( type == OBJECT_START )
    {
        result.push_back({7.0f, 9.0f, 1.0f, 0.5f});
    }
    if ( type == OBJECT_END )
    {
        result.push_back({7.0f, 9.0f, 1.0f, 0.5f});
    }

    return result;
}

CObjectModeledShadowCircle CModeledHardcodeCollection::GetModeledShadowCircle(ObjectType type)
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
        return {6.0f, 0.5f, true};
    }

    if ( type == OBJECT_BARRIER1 )
    {
        return {12.0f, 0.5f, true};
    }

    if ( type == OBJECT_BARRIER2 )  // cardboard?
    {
        return {12.0f, 0.8f, true};
    }

    if ( type == OBJECT_BARRIER3 )  // match + straw?
    {
        return {10.0f, 0.5f, true};
    }

    if ( type == OBJECT_BARRICADE0 )
    {
        return {6.0f, 0.5f, true};
    }

    if ( type == OBJECT_BARRICADE1 )
    {
        return {12.0f, 0.5f, true};
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
       return {5.0f, 0.8f, true, true};
    }

    if ( type == OBJECT_TEEN1 )  // blue pencil lg=14
    {
       return {6.0f, 0.8f, true, true};
    }

    if ( type == OBJECT_TEEN2 )  // red pencil lg=16
    {
       return {6.0f, 0.8f, true, true};
    }

    if ( type == OBJECT_TEEN3 )  // jar with pencils
    {
       return {6.0f, 0.5f, false, true};
    }

    if ( type == OBJECT_TEEN4 )  // scissors
    {
       return {10.0f, 0.5f, true, true};
    }

    if ( type == OBJECT_TEEN5 )  // CD
    {
       return {8.0f, 0.2f, false, true};
    }

    if ( type == OBJECT_TEEN6 )  // book 1
    {
       return {20.0f, 0.2f, false, true};
    }

    if ( type == OBJECT_TEEN7 )  // book 2
    {
       return {20.0f, 0.2f, false, true};
    }

    if ( type == OBJECT_TEEN8 )  // a stack of books 1
    {
       return {20.0f, 0.2f, false, true};
    }

    if ( type == OBJECT_TEEN9 )  // a stack of books 2
    {
       return {20.0f, 0.2f, false, true};
    }

    if ( type == OBJECT_TEEN10 )  // bookcase
    {
       return {40.0f, 0.2f, false, true};
    }

    if ( type == OBJECT_TEEN12 )  // coke
    {
       return {4.5f, 1.0f, false, true};
    }

    if ( type == OBJECT_TEEN13 )  // cardboard farm
    {
       return {20.0f, 1.0f, false, true};
    }

    if ( type == OBJECT_TEEN14 )  // open box
    {
       return {20.0f, 1.0f, false, true};
    }

    if ( type == OBJECT_TEEN15 )  // stack of cartons
    {
       return {20.0f, 1.0f, false, true};
    }

    if ( type == OBJECT_TEEN16 )  // watering can
    {
       return {18.0f, 1.0f, false, true};
    }

    if ( type == OBJECT_TEEN17 )  // wheel |
    {
       return {24.0f, 0.5f, false, true};
    }

    if ( type == OBJECT_TEEN18 )  // wheel /
    {
       return {24.0f, 0.5f, false, true};
    }

    if ( type == OBJECT_TEEN19 )  // wheel =
    {
       return {33.0f, 1.0f, false, true};
    }

    if ( type == OBJECT_TEEN23 )  // skateboard on wheels
    {
       return {35.0f, 0.8f, true, true};
    }

    if ( type == OBJECT_TEEN24 )  // skate /
    {
       return {20.0f, 0.2f, false, true};
    }

    if ( type == OBJECT_TEEN25 )  // skate /
    {
       return {20.0f, 0.2f, false, true};
    }

    if ( type == OBJECT_TEEN27 )  // large plant?
    {
       return {40.0f, 0.5f};
    }

    if ( type == OBJECT_TEEN28 )  // bottle?
    {
       return {7.0f, 0.6f, false, true};
    }

    if ( type == OBJECT_TEEN30 )  // jump?
    {
       return {20.0f, 1.0f, false, true};
    }

    if ( type == OBJECT_TEEN31 )  // basket?
    {
       return {16.0f, 0.6f, false, true};
    }

    if ( type == OBJECT_TEEN32 )  // chair?
    {
       return {35.0f, 0.3f, false, true};
    }

    if ( type == OBJECT_TEEN33 )  // panel?
    {
       return {10.0f, 0.3f, false, true};
    }

    if ( type == OBJECT_TEEN34 )  // stone?
    {
       return {3.0f, 1.0f, false, true};
    }

    if ( type == OBJECT_TEEN35 )  // pipe?
    {
       return {40.0f, 0.8f, true, true};
    }

    if ( type == OBJECT_TEEN38 )  // fan?
    {
       return {15.0f, 0.5f, false, true};
    }

    if ( type == OBJECT_TEEN39 )  // potted plant?
    {
       return {10.0f, 1.0f, false, true};
    }

    if ( type == OBJECT_TEEN40 )  // balloon?
    {
       return {15.0f, 0.7f, false, true};
    }

    if ( type == OBJECT_TEEN42 )  // clover?
    {
       return {15.0f, 0.4f, false, true};
    }

    if ( type == OBJECT_TEEN43 )  // clover?
    {
       return {15.0f, 0.4f, false, true};
    }

    if ( type == OBJECT_TEEN44 )  // car?
    {
       return {55.0f, 1.0f, false, true};
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

    if ( type == OBJECT_PORTICO )
    {
        return {50.0f, 1.0f};
    }

    if ( type == OBJECT_BASE )
    {
        return {60.0f, 1.0f};
    }

    if ( type == OBJECT_DERRICK )
    {
        return {10.0f, 0.4f};
    }

    if ( type == OBJECT_RESEARCH )
    {
        return {12.0f, 1.0f};
    }

    if ( type == OBJECT_RADAR )
    {
        return {8.0f, 1.0f};
    }

    if ( type == OBJECT_ENERGY )
    {
        return {6.0f, 0.5f};
    }

    if ( type == OBJECT_LABO )
    {
        return {7.0f, 0.5f};
    }

    if ( type == OBJECT_FACTORY )
    {
        return {24.0f, 0.3f};
    }

    if ( type == OBJECT_DESTROYER )
    {
        return {19.0f, 1.0f};
    }

    if ( type == OBJECT_TOWER )
    {
        return {6.0f, 1.0f};
    }

    if ( type == OBJECT_NUCLEAR )
    {
        return {21.0f, 1.0f};
    }

    if ( type == OBJECT_PARA )
    {
        return {21.0f, 1.0f};
    }

    if ( type == OBJECT_SAFE )
    {
        return {23.0f, 1.0f};
    }

    if ( type == OBJECT_TARGET1 )
    {
        return {15.0f, 1.0f};
    }

    if ( type == OBJECT_NEST )
    {
        return {4.0f, 1.0f};
    }

    if ( type == OBJECT_INFO )
    {
        return {8.0f, 1.0f};
    }

    if ( type == OBJECT_MOTHER )
    {
        return {18.0f, 0.8f};
    }
    if ( type == OBJECT_ANT )
    {
        return {4.0f, 0.5f};
    }
    if ( type == OBJECT_BEE )
    {
        return {6.0f, 0.5f};
    }
    if ( type == OBJECT_SPIDER )
    {
        return {4.0f, 0.5f};
    }
    if ( type == OBJECT_WORM )
    {
        return {0.0f, 1.0f, true};
    }

    if ( type == OBJECT_HUMAN )
    {
        return {2.0f, 0.8f};
    }
    if ( type == OBJECT_TECH )
    {
        return {2.0f, 0.8f};
    }

    if (type == OBJECT_MOBILErt ||
        type == OBJECT_MOBILErc ||
        type == OBJECT_MOBILErr ||
        type == OBJECT_MOBILErs ||
        type == OBJECT_MOBILErp)
    {
        return {6.0f, 1.0f};
    }
    else if (type == OBJECT_MOBILEta ||
             type == OBJECT_MOBILEtb ||
             type == OBJECT_MOBILEtc ||
             type == OBJECT_MOBILEti ||
             type == OBJECT_MOBILEts ||
             type == OBJECT_MOBILEtt ||
             type == OBJECT_MOBILEsa ||
             type == OBJECT_MOBILEst)
    {
        return {5.0f, 1.0f};
    }
    else if (type == OBJECT_MOBILEdr)
    {
        return {4.5f, 1.0f};
    }
    else if (type == OBJECT_APOLLO2)
    {
        return {7.0f, 0.8f};
    }
    else if (type == OBJECT_MOBILEtg ||
             type == OBJECT_MOBILEwa ||
             type == OBJECT_MOBILEfa ||
             type == OBJECT_MOBILEia ||
             type == OBJECT_MOBILEwb ||
             type == OBJECT_MOBILEfb ||
             type == OBJECT_MOBILEib ||
             type == OBJECT_MOBILEwc ||
             type == OBJECT_MOBILEfc ||
             type == OBJECT_MOBILEic ||
             type == OBJECT_MOBILEwi ||
             type == OBJECT_MOBILEfi ||
             type == OBJECT_MOBILEii ||
             type == OBJECT_MOBILEws ||
             type == OBJECT_MOBILEfs ||
             type == OBJECT_MOBILEis ||
             type == OBJECT_MOBILEwt ||
             type == OBJECT_MOBILEft ||
             type == OBJECT_MOBILEit )  // moving vehicle?
    {
        return {4.0f, 1.0f};
    }

    return CObjectModeledShadowCircle();
}

CObjectModeledShadowLight CModeledHardcodeCollection::GetModeledShadowLight(ObjectType type)
{
    if (type == OBJECT_MOBILEfa ||
        type == OBJECT_MOBILEfb ||
        type == OBJECT_MOBILEfc ||
        type == OBJECT_MOBILEfi ||
        type == OBJECT_MOBILEfs ||
        type == OBJECT_MOBILEft)  // flying?
    {
        Gfx::Color color;
//?     color.r = 0.5f-1.0f;
//?     color.g = 0.2f-1.0f;
//?     color.b = 0.0f-1.0f;  // orange
//?     color.r = 0.8f;
//?     color.g = 0.6f;
//?     color.b = 0.0f;  // yellow-orange
        color.r = 0.0f;
        color.g = 0.4f;
        color.b = 0.8f;  // blue
        color.a = 0.0f;
        return {50.0f, color};
    }

    return CObjectModeledShadowLight();
}


float CModeledHardcodeCollection::GetModeledScale(ObjectType type)
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
    if ( type == OBJECT_TARGET1 ) return 1.5f;
    if ( type == OBJECT_TOTO ) return 0.5f;
    return 1.0f;
}

bool CModeledHardcodeCollection::IsModeledForceLoadTextures(ObjectType type)
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
        case OBJECT_INFO:
            return true;

        case OBJECT_FLAGb:
        case OBJECT_FLAGr:
        case OBJECT_FLAGg:
        case OBJECT_FLAGy:
        case OBJECT_FLAGv:
            return true;

        case OBJECT_MOTHER:
        case OBJECT_ANT:
        case OBJECT_BEE:
        case OBJECT_SPIDER:
        case OBJECT_WORM:
            return true;

        case OBJECT_TOTO:
            return true;

        case OBJECT_HUMAN:
        case OBJECT_TECH:
            return true;

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

bool CModeledHardcodeCollection::IsModeledSetFloorHeight(ObjectType type)
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
        case OBJECT_INFO:
            return true;

        case OBJECT_MOTHER:
        case OBJECT_ANT:
        case OBJECT_BEE:
        case OBJECT_SPIDER:
        case OBJECT_WORM:
            return true;

        case OBJECT_TOTO:
            return true;

        case OBJECT_HUMAN:
        case OBJECT_TECH:
            return true;

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

bool CModeledHardcodeCollection::IsModeledFloorAdjust(ObjectType type)
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
            return false;

        default:
            return false;
    }
}

bool CModeledHardcodeCollection::IsModeledFixedPosition(ObjectType type)
{
    return type == OBJECT_SHOW;
}
