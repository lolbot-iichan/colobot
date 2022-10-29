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

/**
 * \file object/details/programmable_details.cpp
 * \brief CObjectProgrammableDetails - set of tweaks for Programmable objects
 */

#include "level/parser/parser.h"

#include "object/details/macro.h"
#include "object/details/programmable_details.h"

#include "object/hardcode/programmable_hardcode.h"

void CObjectProgrammableDetails::ReadHardcode(ObjectType type)
{
    enabled     = CProgrammableHardcodeCollection::IsProgrammable(type);
    noSaveState = CProgrammableHardcodeCollection::GetNoSaveState(type);

    allowed.build = CProgrammableHardcodeCollection::IsFunctionImplementedBuild(type);
    allowed.deflag = CProgrammableHardcodeCollection::IsFunctionImplementedFlags(type);
    allowed.dropNoParam = CProgrammableHardcodeCollection::IsFunctionImplementedGrabAsHuman(type);
    allowed.dropEnumParam = CProgrammableHardcodeCollection::IsFunctionImplementedGrabAsRobot(type);
    allowed.fireNoParam = CProgrammableHardcodeCollection::IsFunctionImplementedShootAsSpider(type);
    allowed.fireTimeParam = CProgrammableHardcodeCollection::IsFunctionImplementedShootAsRobot(type);
    allowed.firePointParam = CProgrammableHardcodeCollection::IsFunctionImplementedShootAsAnt(type);
    allowed.flag = CProgrammableHardcodeCollection::IsFunctionImplementedFlags(type);
    allowed.grabNoParam = CProgrammableHardcodeCollection::IsFunctionImplementedGrabAsHuman(type);
    allowed.grabEnumParam = CProgrammableHardcodeCollection::IsFunctionImplementedGrabAsRobot(type);
    allowed.recycle = CProgrammableHardcodeCollection::IsFunctionImplementedRecycle(type);
    allowed.sniff = CProgrammableHardcodeCollection::IsFunctionImplementedSniff(type);
    allowed.thump = CProgrammableHardcodeCollection::IsFunctionImplementedThump(type);

    allowed.aim = CProgrammableHardcodeCollection::IsFunctionImplementedShootAsRobot(type);
    allowed.shield = CProgrammableHardcodeCollection::IsFunctionImplementedShield(type);

    allowed.GOTO = CProgrammableHardcodeCollection::IsProgrammable(type);
    allowed.move = CProgrammableHardcodeCollection::IsProgrammable(type);
    allowed.pencolor = CProgrammableHardcodeCollection::IsProgrammable(type);
    allowed.pendown  = CProgrammableHardcodeCollection::IsProgrammable(type);
    allowed.penup    = CProgrammableHardcodeCollection::IsProgrammable(type);
    allowed.receive = CProgrammableHardcodeCollection::IsProgrammable(type);
    allowed.send = CProgrammableHardcodeCollection::IsProgrammable(type);
    allowed.turn = CProgrammableHardcodeCollection::IsProgrammable(type);
    allowed.wait = CProgrammableHardcodeCollection::IsProgrammable(type);

    allowed.destroy = CProgrammableHardcodeCollection::IsProgrammable(type);
    allowed.factory = CProgrammableHardcodeCollection::IsProgrammable(type);
    allowed.research = CProgrammableHardcodeCollection::IsProgrammable(type);
    allowed.takeoff = CProgrammableHardcodeCollection::IsProgrammable(type);

    allowed.abstime = CProgrammableHardcodeCollection::IsProgrammable(type);
    allowed.buildingenabled = CProgrammableHardcodeCollection::IsProgrammable(type);
    allowed.camerafocus = CProgrammableHardcodeCollection::IsProgrammable(type);
    allowed.canbuild = CProgrammableHardcodeCollection::IsProgrammable(type);
    allowed.canresearch = CProgrammableHardcodeCollection::IsProgrammable(type);
    allowed.cmdline = CProgrammableHardcodeCollection::IsProgrammable(type);
    allowed.DELETE = CProgrammableHardcodeCollection::IsProgrammable(type);
    allowed.deleteinfo = CProgrammableHardcodeCollection::IsProgrammable(type);
    allowed.detect = CProgrammableHardcodeCollection::IsProgrammable(type);
    allowed.direction = CProgrammableHardcodeCollection::IsProgrammable(type);
    allowed.distance = CProgrammableHardcodeCollection::IsProgrammable(type);
    allowed.distance2d = CProgrammableHardcodeCollection::IsProgrammable(type);
    allowed.endmission = CProgrammableHardcodeCollection::IsProgrammable(type);
    allowed.errmode = CProgrammableHardcodeCollection::IsProgrammable(type);
    allowed.flatground = CProgrammableHardcodeCollection::IsProgrammable(type);
    allowed.flatspace = CProgrammableHardcodeCollection::IsProgrammable(type);
    allowed.getbuild = CProgrammableHardcodeCollection::IsProgrammable(type);
    allowed.getresearchdone = CProgrammableHardcodeCollection::IsProgrammable(type);
    allowed.getresearchenable = CProgrammableHardcodeCollection::IsProgrammable(type);
    allowed.ipf = CProgrammableHardcodeCollection::IsProgrammable(type);
    allowed.isbusy = CProgrammableHardcodeCollection::IsProgrammable(type);
    allowed.ismovie = CProgrammableHardcodeCollection::IsProgrammable(type);
    allowed.jet = CProgrammableHardcodeCollection::IsProgrammable(type);
    allowed.message = CProgrammableHardcodeCollection::IsProgrammable(type);
    allowed.motor = CProgrammableHardcodeCollection::IsProgrammable(type);
    allowed.penwidth = CProgrammableHardcodeCollection::IsProgrammable(type);
    allowed.playmusic = CProgrammableHardcodeCollection::IsProgrammable(type);
    allowed.produce = CProgrammableHardcodeCollection::IsProgrammable(type);
    allowed.radar = CProgrammableHardcodeCollection::IsProgrammable(type);
    allowed.radarall = CProgrammableHardcodeCollection::IsProgrammable(type);
    allowed.researched = CProgrammableHardcodeCollection::IsProgrammable(type);
    allowed.retobject = CProgrammableHardcodeCollection::IsProgrammable(type);
    allowed.retobjectbyid = CProgrammableHardcodeCollection::IsProgrammable(type);
    allowed.search = CProgrammableHardcodeCollection::IsProgrammable(type);
    allowed.searchall = CProgrammableHardcodeCollection::IsProgrammable(type);
    allowed.setbuild = CProgrammableHardcodeCollection::IsProgrammable(type);
    allowed.setresearchdone = CProgrammableHardcodeCollection::IsProgrammable(type);
    allowed.setresearchenable = CProgrammableHardcodeCollection::IsProgrammable(type);
    allowed.space = CProgrammableHardcodeCollection::IsProgrammable(type);
    allowed.stopmusic = CProgrammableHardcodeCollection::IsProgrammable(type);
    allowed.testinfo = CProgrammableHardcodeCollection::IsProgrammable(type);
    allowed.topo = CProgrammableHardcodeCollection::IsProgrammable(type);
}

bool CObjectProgrammableDetails::Read(CLevelParserLine* line)
{
    READ_LINE( "SetObjectProgrammable" );
    READ_ARG( "enabled",     AsBool, enabled     );
    READ_ARG( "noSaveState", AsBool, noSaveState );
    READ_END();

    READ_LINE( "SetObjectProgrammableAllow" );
    // with foreground tasks
    READ_ARG( "build",             AsBool, allowed.build             );
    READ_ARG( "deflag",            AsBool, allowed.deflag            );
    READ_ARG( "drop0",             AsBool, allowed.dropNoParam       );
    READ_ARG( "dropE",             AsBool, allowed.dropEnumParam     );
    READ_ARG( "fire0",             AsBool, allowed.fireNoParam       );
    READ_ARG( "fireT",             AsBool, allowed.fireTimeParam     );
    READ_ARG( "fireP",             AsBool, allowed.firePointParam    );
    READ_ARG( "flag",              AsBool, allowed.flag              );
    READ_ARG( "goto",              AsBool, allowed.GOTO              );
    READ_ARG( "grab0",             AsBool, allowed.grabNoParam       );
    READ_ARG( "grabE",             AsBool, allowed.grabEnumParam     );
    READ_ARG( "move",              AsBool, allowed.move              );
    READ_ARG( "pencolor",          AsBool, allowed.pencolor          );
    READ_ARG( "pendown",           AsBool, allowed.pendown           );
    READ_ARG( "penup",             AsBool, allowed.penup             );
    READ_ARG( "receive",           AsBool, allowed.receive           );
    READ_ARG( "recycle",           AsBool, allowed.recycle           );
    READ_ARG( "send",              AsBool, allowed.send              );
    READ_ARG( "sniff",             AsBool, allowed.sniff             );
    READ_ARG( "thump",             AsBool, allowed.thump             );
    READ_ARG( "turn",              AsBool, allowed.turn              );
    READ_ARG( "wait",              AsBool, allowed.wait              );
    // with background tasks
    READ_ARG( "aim",               AsBool, allowed.aim               );
    READ_ARG( "shield",            AsBool, allowed.shield            );
    // with automated buildings
    READ_ARG( "destroy",           AsBool, allowed.destroy           );
    READ_ARG( "factory",           AsBool, allowed.factory           );
    READ_ARG( "research",          AsBool, allowed.research          );
    READ_ARG( "takeoff",           AsBool, allowed.takeoff           );
    // with no tasks
    READ_ARG( "abstime",           AsBool, allowed.abstime           );
    READ_ARG( "buildingenabled",   AsBool, allowed.buildingenabled   );
    READ_ARG( "camerafocus",       AsBool, allowed.camerafocus       );
    READ_ARG( "canbuild",          AsBool, allowed.canbuild          );
    READ_ARG( "canresearch",       AsBool, allowed.canresearch       );
    READ_ARG( "cmdline",           AsBool, allowed.cmdline           );
    READ_ARG( "delete",            AsBool, allowed.DELETE            );
    READ_ARG( "deleteinfo",        AsBool, allowed.deleteinfo        );
    READ_ARG( "detect",            AsBool, allowed.detect            );
    READ_ARG( "direction",         AsBool, allowed.direction         );
    READ_ARG( "distance",          AsBool, allowed.distance          );
    READ_ARG( "distance2d",        AsBool, allowed.distance2d        );
    READ_ARG( "endmission",        AsBool, allowed.endmission        );
    READ_ARG( "errmode",           AsBool, allowed.errmode           );
    READ_ARG( "flatground",        AsBool, allowed.flatground        );
    READ_ARG( "flatspace",         AsBool, allowed.flatspace         );
    READ_ARG( "getbuild",          AsBool, allowed.getbuild          );
    READ_ARG( "getresearchdone",   AsBool, allowed.getresearchdone   );
    READ_ARG( "getresearchenable", AsBool, allowed.getresearchenable );
    READ_ARG( "ipf",               AsBool, allowed.ipf               );
    READ_ARG( "isbusy",            AsBool, allowed.isbusy            );
    READ_ARG( "ismovie",           AsBool, allowed.ismovie           );
    READ_ARG( "jet",               AsBool, allowed.jet               );
    READ_ARG( "message",           AsBool, allowed.message           );
    READ_ARG( "motor",             AsBool, allowed.motor             );
    READ_ARG( "penwidth",          AsBool, allowed.penwidth          );
    READ_ARG( "playmusic",         AsBool, allowed.playmusic         );
    READ_ARG( "produce",           AsBool, allowed.produce           );
    READ_ARG( "radar",             AsBool, allowed.radar             );
    READ_ARG( "radarall",          AsBool, allowed.radarall          );
    READ_ARG( "researched",        AsBool, allowed.researched        );
    READ_ARG( "retobject",         AsBool, allowed.retobject         );
    READ_ARG( "retobjectbyid",     AsBool, allowed.retobjectbyid     );
    READ_ARG( "search",            AsBool, allowed.search            );
    READ_ARG( "searchall",         AsBool, allowed.searchall         );
    READ_ARG( "setbuild",          AsBool, allowed.setbuild          );
    READ_ARG( "setresearchdone",   AsBool, allowed.setresearchdone   );
    READ_ARG( "setresearchenable", AsBool, allowed.setresearchenable );
    READ_ARG( "space",             AsBool, allowed.space             );
    READ_ARG( "stopmusic",         AsBool, allowed.stopmusic         );
    READ_ARG( "testinfo",          AsBool, allowed.testinfo          );
    READ_ARG( "topo",              AsBool, allowed.topo              );
    READ_END();

    return false;
}

void CObjectProgrammableDetails::Write(CLevelParser* parser, ObjectType type)
{
    WRITE_LINE( "SetObjectProgrammable" );
    WRITE_ARG( "enabled",     AsBool, enabled     );
    WRITE_ARG( "noSaveState", AsBool, noSaveState );
    WRITE_END();

    WRITE_LINE( "SetObjectProgrammableAllow" );
    // with foreground tasks
    WRITE_ARG( "build",             AsBool, allowed.build             );
    WRITE_ARG( "deflag",            AsBool, allowed.deflag            );
    WRITE_ARG( "drop0",             AsBool, allowed.dropNoParam       );
    WRITE_ARG( "dropE",             AsBool, allowed.dropEnumParam     );
    WRITE_ARG( "fire0",             AsBool, allowed.fireNoParam       );
    WRITE_ARG( "fireT",             AsBool, allowed.fireTimeParam     );
    WRITE_ARG( "fireP",             AsBool, allowed.firePointParam    );
    WRITE_ARG( "flag",              AsBool, allowed.flag              );
    WRITE_ARG( "goto",              AsBool, allowed.GOTO              );
    WRITE_ARG( "grab0",             AsBool, allowed.grabNoParam       );
    WRITE_ARG( "grabE",             AsBool, allowed.grabEnumParam     );
    WRITE_ARG( "move",              AsBool, allowed.move              );
    WRITE_ARG( "pencolor",          AsBool, allowed.pencolor          );
    WRITE_ARG( "pendown",           AsBool, allowed.pendown           );
    WRITE_ARG( "penup",             AsBool, allowed.penup             );
    WRITE_ARG( "receive",           AsBool, allowed.receive           );
    WRITE_ARG( "recycle",           AsBool, allowed.recycle           );
    WRITE_ARG( "send",              AsBool, allowed.send              );
    WRITE_ARG( "sniff",             AsBool, allowed.sniff             );
    WRITE_ARG( "thump",             AsBool, allowed.thump             );
    WRITE_ARG( "turn",              AsBool, allowed.turn              );
    WRITE_ARG( "wait",              AsBool, allowed.wait              );
    // with background tasks
    WRITE_ARG( "aim",               AsBool, allowed.aim               );
    WRITE_ARG( "shield",            AsBool, allowed.shield            );
    // with automated buildings
    WRITE_ARG( "destroy",           AsBool, allowed.destroy           );
    WRITE_ARG( "factory",           AsBool, allowed.factory           );
    WRITE_ARG( "research",          AsBool, allowed.research          );
    WRITE_ARG( "takeoff",           AsBool, allowed.takeoff           );
    // with no tasks
    WRITE_ARG( "abstime",           AsBool, allowed.abstime           );
    WRITE_ARG( "buildingenabled",   AsBool, allowed.buildingenabled   );
    WRITE_ARG( "camerafocus",       AsBool, allowed.camerafocus       );
    WRITE_ARG( "canbuild",          AsBool, allowed.canbuild          );
    WRITE_ARG( "canresearch",       AsBool, allowed.canresearch       );
    WRITE_ARG( "cmdline",           AsBool, allowed.cmdline           );
    WRITE_ARG( "delete",            AsBool, allowed.DELETE            );
    WRITE_ARG( "deleteinfo",        AsBool, allowed.deleteinfo        );
    WRITE_ARG( "detect",            AsBool, allowed.detect            );
    WRITE_ARG( "direction",         AsBool, allowed.direction         );
    WRITE_ARG( "distance",          AsBool, allowed.distance          );
    WRITE_ARG( "distance2d",        AsBool, allowed.distance2d        );
    WRITE_ARG( "endmission",        AsBool, allowed.endmission        );
    WRITE_ARG( "errmode",           AsBool, allowed.errmode           );
    WRITE_ARG( "flatground",        AsBool, allowed.flatground        );
    WRITE_ARG( "flatspace",         AsBool, allowed.flatspace         );
    WRITE_ARG( "getbuild",          AsBool, allowed.getbuild          );
    WRITE_ARG( "getresearchdone",   AsBool, allowed.getresearchdone   );
    WRITE_ARG( "getresearchenable", AsBool, allowed.getresearchenable );
    WRITE_ARG( "ipf",               AsBool, allowed.ipf               );
    WRITE_ARG( "isbusy",            AsBool, allowed.isbusy            );
    WRITE_ARG( "ismovie",           AsBool, allowed.ismovie           );
    WRITE_ARG( "jet",               AsBool, allowed.jet               );
    WRITE_ARG( "message",           AsBool, allowed.message           );
    WRITE_ARG( "motor",             AsBool, allowed.motor             );
    WRITE_ARG( "penwidth",          AsBool, allowed.penwidth          );
    WRITE_ARG( "playmusic",         AsBool, allowed.playmusic         );
    WRITE_ARG( "produce",           AsBool, allowed.produce           );
    WRITE_ARG( "radar",             AsBool, allowed.radar             );
    WRITE_ARG( "radarall",          AsBool, allowed.radarall          );
    WRITE_ARG( "researched",        AsBool, allowed.researched        );
    WRITE_ARG( "retobject",         AsBool, allowed.retobject         );
    WRITE_ARG( "retobjectbyid",     AsBool, allowed.retobjectbyid     );
    WRITE_ARG( "search",            AsBool, allowed.search            );
    WRITE_ARG( "searchall",         AsBool, allowed.searchall         );
    WRITE_ARG( "setbuild",          AsBool, allowed.setbuild          );
    WRITE_ARG( "setresearchdone",   AsBool, allowed.setresearchdone   );
    WRITE_ARG( "setresearchenable", AsBool, allowed.setresearchenable );
    WRITE_ARG( "space",             AsBool, allowed.space             );
    WRITE_ARG( "stopmusic",         AsBool, allowed.stopmusic         );
    WRITE_ARG( "testinfo",          AsBool, allowed.testinfo          );
    WRITE_ARG( "topo",              AsBool, allowed.topo              );
    WRITE_END();
}
