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

#include "object/object_type.h"

#include "object/hardcode/task_executor_hardcode.h"

#include "object/motion/motionant.h"
#include "object/motion/motionspider.h"

/* Macro to mark which texts are translatable by gettext
 * It doesn't do anything at compile-time, as all texts represented here are used later
 * in explicit call to gettext(), but it is used by xgettext executable to filter extracted
 * texts from this file.
 */
#define TR(x) x

/* Please run `cmake --build <path_to_build_folder> --target update-pot`
 * after changing this file in order to update translation files. Thank you.
 */

bool CTaskExecutorHardcodeCollection::IsTaskExecutor(ObjectType type)
{
    return true; // huh!!!
}

CObjectAimTaskExecutorDetails CTaskExecutorHardcodeCollection::GetAimTaskExecutionDetails(ObjectType type)
{
    if ( type == OBJECT_MOBILEfc ||
         type == OBJECT_MOBILEtc ||
         type == OBJECT_MOBILEwc ||
         type == OBJECT_MOBILEic )  // fireball?
    {
        return {true, true, true, true, true, false, 1, -40.0f*Math::PI/180.0f, 40.0f*Math::PI/180.0f, -20.0f*Math::PI/180.0f, 10.0f*Math::PI/180.0f};
    }
    else if ( type == OBJECT_MOBILEfb ||
             type == OBJECT_MOBILEtb ||
             type == OBJECT_MOBILEwb ||
             type == OBJECT_MOBILEib )  // builder?
    {
        return {true, true, true, true, true, false, 1, -40.0f*Math::PI/180.0f, 40.0f*Math::PI/180.0f, -20.0f*Math::PI/180.0f, 10.0f*Math::PI/180.0f};
    }
    else if ( type == OBJECT_MOBILEfi ||
              type == OBJECT_MOBILEti ||
              type == OBJECT_MOBILEwi ||
              type == OBJECT_MOBILEii )  // orgaball?
    {
        return {true, true, true, true, true, false, 1, -40.0f*Math::PI/180.0f, 40.0f*Math::PI/180.0f, -20.0f*Math::PI/180.0f, 20.0f*Math::PI/180.0f};
    }
    else if ( type == OBJECT_MOBILErc )  // phazer?
    {
        return {true, true, true, true, true, false, 2, -40.0f*Math::PI/180.0f, 40.0f*Math::PI/180.0f, -20.0f*Math::PI/180.0f, 45.0f*Math::PI/180.0f};
    }

    return {false};
}

CObjectBuildTaskExecutorDetails CTaskExecutorHardcodeCollection::GetBuildTaskExecutionDetails(ObjectType type)
{
    if ( type == OBJECT_MOBILEtb ||
         type == OBJECT_MOBILEwb ||
         type == OBJECT_MOBILEib )  // builder?
    {
        return {true, false, false, false, false, false, ExecutionAsRobot, false, 1, glm::vec3(0.0f, 2.5f, 0.0f)};
    }
    else if ( type == OBJECT_MOBILEfb )  // flying builder?
    {
        return {true, false, true, false, false, false, ExecutionAsRobot, false, 1, glm::vec3(0.0f, 2.5f, 0.0f)};
    }
    else if ( type == OBJECT_HUMAN )  // me?
    {
        return {true, false, false, false, false, false, ExecutionAsHuman, true, 14, glm::vec3(0.0f, 0.5f, 0.0f)};
    }

    return {false};
}

CObjectDeflagTaskExecutorDetails CTaskExecutorHardcodeCollection::GetDeflagTaskExecutionDetails(ObjectType type)
{
    switch(type)
    {
        case OBJECT_HUMAN:
        case OBJECT_TECH:
            return {true, false, false, false, false, false, ExecutionAsHuman, 0, glm::vec3(0.0f, 0.0f, 0.0f), 10.0f};
        case OBJECT_MOBILEws:
        case OBJECT_MOBILEts:
        case OBJECT_MOBILEfs:
        case OBJECT_MOBILEis:
            return {true, false, false, false, false, false, ExecutionAsRobot, 0, glm::vec3(0.0f, 0.0f, 0.0f), 10.0f};
        default:
            return {false};
    }
}

std::vector<CObjectDeflagTaskExecutorObject> CTaskExecutorHardcodeCollection::GetDeflagTaskExecutionObjects(ObjectType type)
{
    std::vector<CObjectDeflagTaskExecutorObject> result;

    switch(type)
    {
        case OBJECT_HUMAN:
        case OBJECT_TECH:
        case OBJECT_MOBILEws:
        case OBJECT_MOBILEts:
        case OBJECT_MOBILEfs:
        case OBJECT_MOBILEis:
            return {
                {OBJECT_FLAGb,OBJECT_NULL,"", Gfx::PT_FLDELETE},
                {OBJECT_FLAGr,OBJECT_NULL,"", Gfx::PT_FLDELETE},
                {OBJECT_FLAGg,OBJECT_NULL,"", Gfx::PT_FLDELETE},
                {OBJECT_FLAGy,OBJECT_NULL,"", Gfx::PT_FLDELETE},
                {OBJECT_FLAGv,OBJECT_NULL,"", Gfx::PT_FLDELETE},
            };
        default:
            return result;
    }
}

CObjectDemarkTaskExecutorDetails CTaskExecutorHardcodeCollection::GetDemarkTaskExecutionDetails(ObjectType type)
{
    switch(type)
    {
        case OBJECT_MOBILEws:
        case OBJECT_MOBILEts:
        case OBJECT_MOBILEfs:
        case OBJECT_MOBILEis:
            return {true, false, false, false, false, false, 8.0f};
        default:
            return {false};
    }
}

std::vector<CObjectDemarkTaskExecutorObject> CTaskExecutorHardcodeCollection::GetDemarkTaskExecutionObjects(ObjectType type)
{
    std::vector<CObjectDemarkTaskExecutorObject> result;

    if ( (type == OBJECT_MOBILEfs ||
          type == OBJECT_MOBILEts ||
          type == OBJECT_MOBILEws ||
          type == OBJECT_MOBILEis ) )
    {
        result.push_back({OBJECT_MARKPOWER});
        result.push_back({OBJECT_MARKSTONE});
        result.push_back({OBJECT_MARKURANIUM});
        result.push_back({OBJECT_MARKKEYa});
        result.push_back({OBJECT_MARKKEYb});
        result.push_back({OBJECT_MARKKEYc});
        result.push_back({OBJECT_MARKKEYd});
    }
          
    return result;
}

CObjectExplodeTaskExecutorDetails CTaskExecutorHardcodeCollection::GetExplodeTaskExecutionDetails(ObjectType type)
{
    switch(type)
    {
        case OBJECT_SPIDER:
            return {true, true, false, true, false, false};
        default:
            return {false};
    }
}

CObjectFireTaskExecutorDetails CTaskExecutorHardcodeCollection::GetFireTaskExecutionDetails(ObjectType type)
{
    switch(type)
    {
        case OBJECT_MOBILErc:
            return {true, false, false, true, false, false, 2, {4.0f, 0.0f, 0.0f}, FIRE_PHAZER, Gfx::PARTITRACK11, 1.2f, (0.25f/1.5f)};
        case OBJECT_MOBILEtc:
        case OBJECT_MOBILEwc:
        case OBJECT_MOBILEic:
            return {true, false, false, true, false, false, 1, {3.0f, 1.0f, 0.0f}, FIRE_CANNON, Gfx::PARTIGUN1, 2.0f, (0.25f/2.5f)};
        case OBJECT_MOBILEfc:
            return {true, false, true,  true, false, false, 1, {3.0f, 1.0f, 0.0f}, FIRE_CANNON, Gfx::PARTIGUN1, 2.0f, (0.25f/2.5f)};
        case OBJECT_MOBILEti:
        case OBJECT_MOBILEwi:
        case OBJECT_MOBILEii:
            return {true, false, false, true, false, false, 1, {0.0f, 2.5f, 0.0f}, FIRE_ORGA, Gfx::PARTIGUN4, 2.0f, (0.10f/2.5f)};
        case OBJECT_MOBILEfi:
            return {true, false, true,  true, false, false, 1, {0.0f, 2.5f, 0.0f}, FIRE_ORGA, Gfx::PARTIGUN4, 2.0f, (0.10f/2.5f)};
        default:
            return {false};
    }
}

CObjectFireAntTaskExecutorDetails CTaskExecutorHardcodeCollection::GetFireAntTaskExecutionDetails(ObjectType type)
{
    switch(type)
    {
        case OBJECT_ANT:
            return {true, false, false, true, true, false};
        default:
            return {false};
    }
}

CObjectFlagTaskExecutorDetails CTaskExecutorHardcodeCollection::GetFlagTaskExecutionDetails(ObjectType type)
{
    switch(type)
    {
        case OBJECT_HUMAN:
        case OBJECT_TECH:
            return {true, false, false, false, false, false, ExecutionAsHuman, 0, glm::vec3(4.0f, 0.0f, 0.0f)};
        case OBJECT_MOBILEws:
        case OBJECT_MOBILEts:
        case OBJECT_MOBILEfs:
        case OBJECT_MOBILEis:
            return {true, false, false, false, false, false, ExecutionAsRobot, 0, glm::vec3(6.0f, 0.0f, 0.0f)};
        default:
            return {false};
    }
}

std::vector<CObjectFlagTaskExecutorObject> CTaskExecutorHardcodeCollection::GetFlagTaskExecutionObjects(ObjectType type)
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
            return {{OBJECT_FLAGb,"",5}, {OBJECT_FLAGr,"",5}, {OBJECT_FLAGg,"",5}, {OBJECT_FLAGy,"",5}, {OBJECT_FLAGv,"",5}};
        default:
            return result;
    }
}

CObjectRecycleTaskExecutorDetails CTaskExecutorHardcodeCollection::GetRecycleTaskExecutionDetails(ObjectType type)
{
    switch(type)
    {
        case OBJECT_MOBILErr:
            return {true, false, false, false, false, false, ExecutionAsRobot, 0, glm::vec3(11.8f, 3.3f, 0.0f), 11.8f};
        default:
            return {false};
    }
}

std::vector<CObjectRecycleTaskExecutorObject> CTaskExecutorHardcodeCollection::GetRecycleTaskExecutionObjects(ObjectType type)
{
    std::vector<CObjectRecycleTaskExecutorObject> result;

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

CObjectShieldTaskExecutorDetails CTaskExecutorHardcodeCollection::GetShieldTaskExecutionDetails(ObjectType type)
{
    switch(type)
    {
        case OBJECT_MOBILErs:
            return {true, true, true, true, false, false};
        default:
            return {false};
    }
}

CObjectSniffTaskExecutorDetails CTaskExecutorHardcodeCollection::GetSniffTaskExecutionDetails(ObjectType type)
{
    switch(type)
    {
        case OBJECT_MOBILEws:
        case OBJECT_MOBILEts:
        case OBJECT_MOBILEfs:
        case OBJECT_MOBILEis:
            return {true, false, false, false, false, false, ExecutionAsRobot, 0, glm::vec3(7.5f, 0.0f, 0.0f)};
        default:
            return {false};
    }
}

std::vector<CObjectSniffTaskExecutorObject> CTaskExecutorHardcodeCollection::GetSniffTaskExecutionObjects(ObjectType type)
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

CObjectTakeTaskExecutorDetails CTaskExecutorHardcodeCollection::GetTakeTaskExecutionDetails(ObjectType type)
{
    switch(type)
    {
        case OBJECT_HUMAN:
        case OBJECT_TECH:
            return {true, true, false, true, true, false};
        default:
            return {false};
    }
}

CObjectManipTaskExecutorDetails CTaskExecutorHardcodeCollection::GetManipTaskExecutionDetails(ObjectType type)
{
    switch(type)
    {
        case OBJECT_BEE:
            return {true, true, true, true, true, false, ExecutionNoMotion};
        case OBJECT_MOBILEsa:
            return {true, true, false, true, true, false, ExecutionAsSubber};
        case OBJECT_MOBILEfa:
        case OBJECT_MOBILEta:
        case OBJECT_MOBILEwa:
        case OBJECT_MOBILEia:
            return {true, false, false, true, true, false, ExecutionAsRobot};
        case OBJECT_HUMAN:
        case OBJECT_TECH:
            // for TMO_GRAB
            return {false, false, false, false, false, false, ExecutionAsHuman};
        default:
            return {false};
    }
}

CObjectThumpTaskExecutorDetails CTaskExecutorHardcodeCollection::GetThumpTaskExecutionDetails(ObjectType type)
{
    switch(type)
    {
        case OBJECT_MOBILErt:
            return {true, false, false, false, false, false, ExecutionAsRobot, 0, glm::vec3(9.0f, 0.0f, 0.0f), 400.0f};
        default:
            return {false};
    }
}

bool IsProgrammable(ObjectType type)
{
    if ( type == OBJECT_HUMAN ) return true;
    if ( type == OBJECT_TECH ) return true;
    if ( type == OBJECT_MOTHER ) return true;
    if ( type == OBJECT_ANT ) return true;
    if ( type == OBJECT_SPIDER ) return true;
    if ( type == OBJECT_BEE ) return true;
    if ( type == OBJECT_WORM ) return true;
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

CTaskConditions CTaskExecutorHardcodeCollection::GetUniversalTaskExecutionDetails(ObjectType type)
{
    if ( IsProgrammable(type) )
        return {true, true, true, true, true, true};

    return {false};
}

CObjectGotoTaskExecutorDetails CTaskExecutorHardcodeCollection::GetGotoTaskExecutionDetails(ObjectType type)
{
    if ( !IsProgrammable(type) )
        return {false};

    CObjectGotoTaskExecutorDetails result;
    result.enabled = IsProgrammable(type);
    
    result.onWater  = true;
    result.onFlying = true;
    result.onMoving = true;
    result.onCarrying = true;
    result.onCarried = false;

    result.defaultGoal = TGG_STOP;
    if ( type == OBJECT_MOTHER ||
         type == OBJECT_ANT    ||
         type == OBJECT_SPIDER ||
         type == OBJECT_WORM   )
    {
        result.defaultGoal = TGG_EXPRESS;
    }

//? result.defaultCrash = TGC_RIGHTLEFT;
    result.defaultCrash = TGC_BEAM;
    if ( type == OBJECT_MOTHER ||
         type == OBJECT_ANT    ||
         type == OBJECT_SPIDER ||
         type == OBJECT_WORM   ||
         type == OBJECT_BEE    )
    {
        result.defaultCrash = TGC_HALT;
    }


    result.approximate = false;
    if ( type == OBJECT_HUMAN    ||
         type == OBJECT_TECH     ||
         type == OBJECT_MOTHER   ||
         type == OBJECT_ANT      ||
         type == OBJECT_SPIDER   ||
         type == OBJECT_BEE      ||
         type == OBJECT_WORM     ||
         type == OBJECT_MOBILErt ||
         type == OBJECT_MOBILErc ||
         type == OBJECT_MOBILErr ||
         type == OBJECT_MOBILErs ||
         type == OBJECT_MOBILErp )
    {
        result.approximate = true;
    }

    result.noAdjusting = false;
    if ( type == OBJECT_BEE  ||
         type == OBJECT_WORM )
    {
        result.noAdjusting = true;
    }

    result.acceptWater = false;
    result.acceptFlying = false;
    result.angleLimit = 20.0f*Math::PI/180.0f;

    if ( type == OBJECT_MOBILEwa ||
         type == OBJECT_MOBILEwb ||
         type == OBJECT_MOBILEwc ||
         type == OBJECT_MOBILEws ||
         type == OBJECT_MOBILEwi ||
         type == OBJECT_MOBILEwt ||
         type == OBJECT_MOBILEtg )  // wheels?
    {
        result.angleLimit = 20.0f*Math::PI/180.0f;
    }

    if ( type == OBJECT_MOBILEta ||
         type == OBJECT_MOBILEtb ||
         type == OBJECT_MOBILEtc ||
         type == OBJECT_MOBILEti ||
         type == OBJECT_MOBILEts )  // caterpillars?
    {
        result.angleLimit = 35.0f*Math::PI/180.0f;
    }

    if ( type == OBJECT_MOBILErt ||
         type == OBJECT_MOBILErc ||
         type == OBJECT_MOBILErr ||
         type == OBJECT_MOBILErs ||
         type == OBJECT_MOBILErp )  // large caterpillars?
    {
        result.angleLimit = 35.0f*Math::PI/180.0f;
    }

    if ( type == OBJECT_MOBILEsa ||
         type == OBJECT_MOBILEst )  // submarine caterpillars?
    {
        result.angleLimit = 35.0f*Math::PI/180.0f;
        result.acceptWater = true;
    }

    if ( type == OBJECT_MOBILEdr )  // designer caterpillars?
    {
        result.angleLimit = 35.0f*Math::PI/180.0f;
    }

    if ( type == OBJECT_MOBILEfa ||
         type == OBJECT_MOBILEfb ||
         type == OBJECT_MOBILEfc ||
         type == OBJECT_MOBILEfs ||
         type == OBJECT_MOBILEfi ||
         type == OBJECT_MOBILEft )  // flying?
    {
        result.angleLimit = 15.0f*Math::PI/180.0f;
        result.acceptFlying = true;
    }

    if ( type == OBJECT_MOBILEia ||
         type == OBJECT_MOBILEib ||
         type == OBJECT_MOBILEic ||
         type == OBJECT_MOBILEis ||
         type == OBJECT_MOBILEii )  // insect legs?
    {
        result.angleLimit = 60.0f*Math::PI/180.0f;
    }

    result.repulseEnabled = true;
    if ( type == OBJECT_WORM ||
         type == OBJECT_CONTROLLER )
    {
        result.repulseEnabled = false;
    }

    result.repulseCustom = false;
    result.repulseLand   = 0.0f;
    result.repulseNoLand = 0.0f;
    result.repulseFactor = 2.0f;

    if ( type == OBJECT_MOBILEwa ||
         type == OBJECT_MOBILEwb ||
         type == OBJECT_MOBILEwc ||
         type == OBJECT_MOBILEwi ||
         type == OBJECT_MOBILEws ||
         type == OBJECT_MOBILEwt )  // wheels?
    {
        result.repulseCustom = true;
        result.repulseLand   = 5.0f;
        result.repulseNoLand = 5.0f;
        result.repulseFactor = 1.5f;
    }
    if ( type == OBJECT_MOBILEta ||
         type == OBJECT_MOBILEtb ||
         type == OBJECT_MOBILEtc ||
         type == OBJECT_MOBILEti ||
         type == OBJECT_MOBILEts ||
         type == OBJECT_MOBILEtt ||
         type == OBJECT_MOBILEdr )  // caterpillars?
    {
        result.repulseCustom = true;
        result.repulseLand   = 4.0f;
        result.repulseNoLand = 4.0f;
        result.repulseFactor = 1.5f;
    }
    if ( type == OBJECT_MOBILEfa ||
         type == OBJECT_MOBILEfb ||
         type == OBJECT_MOBILEfc ||
         type == OBJECT_MOBILEfi ||
         type == OBJECT_MOBILEfs ||
         type == OBJECT_MOBILEft )  // flying?
    {
        result.repulseCustom = true;
        result.repulseLand   = 5.0f;
        result.repulseNoLand = 10.0f;
        result.repulseFactor = 1.5f;
    }
    if ( type == OBJECT_MOBILEia ||
         type == OBJECT_MOBILEib ||
         type == OBJECT_MOBILEic ||
         type == OBJECT_MOBILEii ||
         type == OBJECT_MOBILEis ||
         type == OBJECT_MOBILEit )  // legs?
    {
        result.repulseCustom = true;
        result.repulseLand   = 4.0f;
        result.repulseNoLand = 4.0f;
        result.repulseFactor = 1.5f;
    }
    if ( type == OBJECT_BEE )  // wasp?
    {
        result.repulseCustom = true;
        result.repulseLand   = 3.0f;
        result.repulseNoLand = 5.0f;
        result.repulseFactor = 1.5f;
    }

    return result;
}

std::vector<CObjectThumpTaskExecutorObject> CTaskExecutorHardcodeCollection::GetThumpTaskExecutionObjects(ObjectType type)
{
    std::vector<CObjectThumpTaskExecutorObject> result;

    if ( type == OBJECT_MOBILErt)
    {
        result.push_back({OBJECT_ANT,    MAS_BACK1});
        result.push_back({OBJECT_SPIDER, MSS_BACK1});
    }

    return result;
}


std::vector<CObjectBuildTaskExecutorObject> CTaskExecutorHardcodeCollection::GetBuildTaskExecutionObjects(ObjectType type)
{
    std::vector<CObjectBuildTaskExecutorObject> result;

    if (type == OBJECT_HUMAN    ||
        type == OBJECT_MOBILEwb ||
        type == OBJECT_MOBILEfb ||
        type == OBJECT_MOBILEib ||
        type == OBJECT_MOBILEtb  )
    {
        result.push_back({ OBJECT_METAL, OBJECT_RESEARCH, TR("Building completed"), 10.0f,  true });
        result.push_back({ OBJECT_METAL, OBJECT_FACTORY,  TR("Building completed"), 15.0f,  true });
        result.push_back({ OBJECT_METAL, OBJECT_CONVERT,  TR("Building completed"), 12.0f, false });
        result.push_back({ OBJECT_METAL, OBJECT_STATION,  TR("Building completed"), 12.0f, false });
        result.push_back({ OBJECT_METAL, OBJECT_RADAR,    TR("Building completed"),  5.0f, false });
        result.push_back({ OBJECT_METAL, OBJECT_REPAIR,   TR("Building completed"), 12.0f, false });
        result.push_back({ OBJECT_METAL, OBJECT_INFO,     TR("Building completed"),  5.0f, false });
        result.push_back({ OBJECT_METAL, OBJECT_TOWER,    TR("Building completed"),  7.0f, false });
        result.push_back({ OBJECT_METAL, OBJECT_ENERGY,   TR("Building completed"),  8.0f, false });
        result.push_back({ OBJECT_METAL, OBJECT_DERRICK,  TR("Building completed"),  5.0f, false });
        result.push_back({ OBJECT_METAL, OBJECT_NUCLEAR,  TR("Building completed"), 20.0f,  true });
        result.push_back({ OBJECT_METAL, OBJECT_LABO,     TR("Building completed"), 12.0f, false });
        result.push_back({ OBJECT_METAL, OBJECT_PARA,     TR("Building completed"), 20.0f, false });
        result.push_back({ OBJECT_METAL, OBJECT_SAFE,     TR("Building completed"), 20.0f, false });
        result.push_back({ OBJECT_METAL, OBJECT_DESTROYER,TR("Building completed"), 20.0f, false });
    }
    return result;
}

std::vector<CObjectDemarkTaskExecutorObject> CTaskExecutorHardcodeCollection::GetBuildTaskExecutionRemove(ObjectType type)
{
    std::vector<CObjectDemarkTaskExecutorObject> result;

    if (type == OBJECT_HUMAN    ||
        type == OBJECT_MOBILEwb ||
        type == OBJECT_MOBILEfb ||
        type == OBJECT_MOBILEib ||
        type == OBJECT_MOBILEtb  )
    {
        result.push_back({ OBJECT_MARKSTONE   });
        result.push_back({ OBJECT_MARKURANIUM });
        result.push_back({ OBJECT_MARKPOWER   });
        result.push_back({ OBJECT_MARKKEYa    });
        result.push_back({ OBJECT_MARKKEYb    });
        result.push_back({ OBJECT_MARKKEYc    });
        result.push_back({ OBJECT_MARKKEYd    });
    }
    return result;
}
