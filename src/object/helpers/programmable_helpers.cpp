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

#include "object/object.h"

#include "object/helpers/programmable_helpers.h"

#include "object/details/details_provider.h"
#include "object/details/programmable_details.h"

bool IsFunctionAllowed(CObject* object, FunctionId id)
{
    auto allowed = GetObjectProgrammableDetails(object).allowed;

    switch(id)
    {
        case FUNCTION_build:             return allowed.build;
        case FUNCTION_deflag:            return allowed.deflag;
        case FUNCTION_dropNoParam:       return allowed.dropNoParam;
        case FUNCTION_dropEnumParam:     return allowed.dropEnumParam;
        case FUNCTION_fireNoParam:       return allowed.fireNoParam;
        case FUNCTION_fireTimeParam:     return allowed.fireTimeParam;
        case FUNCTION_firePointParam:    return allowed.firePointParam;
        case FUNCTION_flag:              return allowed.flag;
        case FUNCTION_GOTO:              return allowed.GOTO;
        case FUNCTION_grabNoParam:       return allowed.grabNoParam;
        case FUNCTION_grabEnumParam:     return allowed.grabEnumParam;
        case FUNCTION_move:              return allowed.move;
        case FUNCTION_pencolor:          return allowed.pencolor;
        case FUNCTION_pendown:           return allowed.pendown;
        case FUNCTION_penup:             return allowed.penup;
        case FUNCTION_receive:           return allowed.receive;
        case FUNCTION_recycle:           return allowed.recycle;
        case FUNCTION_send:              return allowed.send;
        case FUNCTION_sniff:             return allowed.sniff;
        case FUNCTION_thump:             return allowed.thump;
        case FUNCTION_turn:              return allowed.turn;
        case FUNCTION_wait:              return allowed.wait;
        case FUNCTION_aim:               return allowed.aim;
        case FUNCTION_shield:            return allowed.shield;
        case FUNCTION_destroy:           return allowed.destroy;
        case FUNCTION_factory:           return allowed.factory;
        case FUNCTION_research:          return allowed.research;
        case FUNCTION_takeoff:           return allowed.takeoff;
        case FUNCTION_abstime:           return allowed.abstime;
        case FUNCTION_buildingenabled:   return allowed.buildingenabled;
        case FUNCTION_camerafocus:       return allowed.camerafocus;
        case FUNCTION_canbuild:          return allowed.canbuild;
        case FUNCTION_canresearch:       return allowed.canresearch;
        case FUNCTION_cmdline:           return allowed.cmdline;
        case FUNCTION_DELETE:            return allowed.DELETE;
        case FUNCTION_deleteinfo:        return allowed.deleteinfo;
        case FUNCTION_detect:            return allowed.detect;
        case FUNCTION_direction:         return allowed.direction;
        case FUNCTION_distance:          return allowed.distance;
        case FUNCTION_distance2d:        return allowed.distance2d;
        case FUNCTION_endmission:        return allowed.endmission;
        case FUNCTION_errmode:           return allowed.errmode;
        case FUNCTION_flatground:        return allowed.flatground;
        case FUNCTION_flatspace:         return allowed.flatspace;
        case FUNCTION_getbuild:          return allowed.getbuild;
        case FUNCTION_getresearchdone:   return allowed.getresearchdone;
        case FUNCTION_getresearchenable: return allowed.getresearchenable;
        case FUNCTION_ipf:               return allowed.ipf;
        case FUNCTION_isbusy:            return allowed.isbusy;
        case FUNCTION_ismovie:           return allowed.ismovie;
        case FUNCTION_jet:               return allowed.jet;
        case FUNCTION_message:           return allowed.message;
        case FUNCTION_motor:             return allowed.motor;
        case FUNCTION_penwidth:          return allowed.penwidth;
        case FUNCTION_playmusic:         return allowed.playmusic;
        case FUNCTION_produce:           return allowed.produce;
        case FUNCTION_radar:             return allowed.radar;
        case FUNCTION_radarall:          return allowed.radarall;
        case FUNCTION_researched:        return allowed.researched;
        case FUNCTION_retobject:         return allowed.retobject;
        case FUNCTION_retobjectbyid:     return allowed.retobjectbyid;
        case FUNCTION_search:            return allowed.search;
        case FUNCTION_searchall:         return allowed.searchall;
        case FUNCTION_setbuild:          return allowed.setbuild;
        case FUNCTION_setresearchdone:   return allowed.setresearchdone;
        case FUNCTION_setresearchenable: return allowed.setresearchenable;
        case FUNCTION_space:             return allowed.space;
        case FUNCTION_stopmusic:         return allowed.stopmusic;
        case FUNCTION_testinfo:          return allowed.testinfo;
        case FUNCTION_topo:              return allowed.topo;
        default:                         return false;
    }
}
