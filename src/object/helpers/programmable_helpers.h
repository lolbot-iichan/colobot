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

#pragma once

class CObject;

enum FunctionId : unsigned int
{
    FUNCTION_build,
    FUNCTION_deflag,
    FUNCTION_dropNoParam,
    FUNCTION_dropEnumParam,
    FUNCTION_fireNoParam,
    FUNCTION_fireTimeParam,
    FUNCTION_firePointParam,
    FUNCTION_flag,
    FUNCTION_GOTO,
    FUNCTION_grabNoParam,
    FUNCTION_grabEnumParam,
    FUNCTION_move,
    FUNCTION_pencolor,
    FUNCTION_pendown,
    FUNCTION_penup,
    FUNCTION_receive,
    FUNCTION_recycle,
    FUNCTION_send,
    FUNCTION_sniff,
    FUNCTION_thump,
    FUNCTION_turn,
    FUNCTION_wait,

    // with background tasks
    FUNCTION_aim,
    FUNCTION_shield,

    // with automated buildings
    FUNCTION_destroy,
    FUNCTION_factory,
    FUNCTION_research,
    FUNCTION_takeoff,

    // with no tasks
    FUNCTION_abstime,
    FUNCTION_buildingenabled,
    FUNCTION_camerafocus,
    FUNCTION_canbuild,
    FUNCTION_canresearch,
    FUNCTION_cmdline,
    FUNCTION_DELETE,
    FUNCTION_deleteinfo,
    FUNCTION_detect,
    FUNCTION_direction,
    FUNCTION_distance,
    FUNCTION_distance2d,
    FUNCTION_endmission,
    FUNCTION_errmode,
    FUNCTION_flatground,
    FUNCTION_flatspace,
    FUNCTION_getbuild,
    FUNCTION_getresearchdone,
    FUNCTION_getresearchenable,
    FUNCTION_ipf,
    FUNCTION_isbusy,
    FUNCTION_ismovie,
    FUNCTION_jet,
    FUNCTION_message,
    FUNCTION_motor,
    FUNCTION_penwidth,
    FUNCTION_playmusic,
    FUNCTION_produce,
    FUNCTION_radar,
    FUNCTION_radarall,
    FUNCTION_researched,
    FUNCTION_retobject,
    FUNCTION_retobjectbyid,
    FUNCTION_search,
    FUNCTION_searchall,
    FUNCTION_setbuild,
    FUNCTION_setresearchdone,
    FUNCTION_setresearchenable,
    FUNCTION_space,
    FUNCTION_stopmusic,
    FUNCTION_testinfo,
    FUNCTION_topo
};

bool IsFunctionAllowed(CObject* object, FunctionId id);
