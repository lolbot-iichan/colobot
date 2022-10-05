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
 * \file object/details/movable_details.cpp
 * \brief CObjectMovableDetails - set of tweaks for Movable objects
 */

#include "level/parser/parser.h"

#include "object/details/details_provider.h"
#include "object/details/hardcode.h"
#include "object/details/macro.h"
#include "object/details/movable_details.h"

void CObjectMovableDetails::ReadHardcode(ObjectType type)
{
    CHardcodeCollection hardcode;

    enabled   = hardcode.IsMovable(type);
    drive     = hardcode.GetDriveType(type);
    linMotion = hardcode.GetLinMotion(type);
    cirMotion = hardcode.GetCirMotion(type);
    wheels    = hardcode.GetWheels(type);

    exhaust.bubblesOnEnteringWater   = hardcode.IsExhaustBubblesOnEnteringWater(type);
    exhaust.bubblesOnEnteringWaterTime = hardcode.IsExhaustBubblesOnEnteringWaterTime(type);
    exhaust.dropsOnLeavingWater     = hardcode.IsExhaustDropsOnLeavingWater(type);
    exhaust.onCrashAsHuman          = hardcode.IsExhaustOnCrashAsHuman(type);
    exhaust.onCrashAsTrackedRobot   = hardcode.IsExhaustOnCrashAsTrackedRobot(type);
    exhaust.onCrashAsHeavyRobot     = hardcode.IsExhaustOnCrashAsHeavyRobot(type);
    exhaust.onLandAsHuman           = hardcode.IsExhaustOnLandAsHuman(type);
    exhaust.onLandAsWingedRobot     = hardcode.IsExhaustOnLandAsWingedRobot(type);
    exhaust.onLandAsHeavyRobot      = hardcode.IsExhaustOnLandAsHeavyRobot      (type);
    exhaust.onLandAsNormalRobot     = hardcode.IsExhaustOnLandAsNormalRobot(type);
    exhaust.onFlightAsHuman         = hardcode.IsExhaustOnFlightAsHuman(type);
    exhaust.onFlightAsWingedRobot   = hardcode.IsExhaustOnFlightAsWingedRobot   (type);
    exhaust.onSwimAsHuman           = hardcode.IsExhaustOnSwimAsHuman(type);
    exhaust.onSwimAsAmphibiousRobot = hardcode.IsExhaustOnSwimAsAmphibiousRobot(type);

    water.waterLevel                = hardcode.GetMaxSafeWaterLevel(type);
    water.splashLevelMin            = hardcode.GetWaterSplashLevelMin(type);
    water.splashLevelMax            = hardcode.GetWaterSplashLevelMax(type);
    water.splashDiameter            = hardcode.GetWaterSplashDiameter(type);
    water.splashForce               = hardcode.GetWaterSplashForce(type);
}

bool CObjectMovableDetails::Read(CLevelParserLine* line)
{
    READ_LINE( "SetObjectMovable" );
    READ_ARG( "enabled",      AsBool,      enabled );
    READ_ARG( "drive",        AsDriveType, drive   );
    READ_END();

    READ_LINE( "SetObjectMovableLinear" );
    READ_ARG( "advanceAccel", AsPoint, linMotion.advanceAccel );
    READ_ARG( "recedeAccel",  AsPoint, linMotion.recedeAccel  );
    READ_ARG( "stopAccel",    AsPoint, linMotion.stopAccel    );
    READ_ARG( "motorAccel",   AsPoint, linMotion.motorAccel   );
    READ_ARG( "advanceSpeed", AsPoint, linMotion.advanceSpeed );
    READ_ARG( "recedeSpeed",  AsPoint, linMotion.recedeSpeed  );
    READ_ARG( "motorSpeed",   AsPoint, linMotion.motorSpeed   );
    READ_ARG( "currentSpeed", AsPoint, linMotion.currentSpeed );
    READ_ARG( "terrainForce", AsPoint, linMotion.terrainForce );
    READ_ARG( "terrainSpeed", AsPoint, linMotion.terrainSpeed );
    READ_ARG( "terrainSlide", AsPoint, linMotion.terrainSlide );
    READ_ARG( "realSpeed",    AsPoint, linMotion.realSpeed    );
    READ_ARG( "finalInclin",  AsPoint, linMotion.finalInclin  );
    READ_END();

    READ_LINE( "SetObjectMovableCircular" );
    READ_ARG( "advanceAccel", AsPoint, cirMotion.advanceAccel );
    READ_ARG( "recedeAccel",  AsPoint, cirMotion.recedeAccel  );
    READ_ARG( "stopAccel",    AsPoint, cirMotion.stopAccel    );
    READ_ARG( "motorAccel",   AsPoint, cirMotion.motorAccel   );
    READ_ARG( "advanceSpeed", AsPoint, cirMotion.advanceSpeed );
    READ_ARG( "recedeSpeed",  AsPoint, cirMotion.recedeSpeed  );
    READ_ARG( "motorSpeed",   AsPoint, cirMotion.motorSpeed   );
    READ_ARG( "currentSpeed", AsPoint, cirMotion.currentSpeed );
    READ_ARG( "terrainForce", AsPoint, cirMotion.terrainForce );
    READ_ARG( "terrainSpeed", AsPoint, cirMotion.terrainSpeed );
    READ_ARG( "terrainSlide", AsPoint, cirMotion.terrainSlide );
    READ_ARG( "realSpeed",    AsPoint, cirMotion.realSpeed    );
    READ_ARG( "finalInclin",  AsPoint, cirMotion.finalInclin  );
    READ_END();

    READ_LINE( "SetObjectMovableWheels" );
    READ_ARG( "front",        AsFloat, wheels.wheelFront      );
    READ_ARG( "back",         AsFloat, wheels.wheelBack       );
    READ_ARG( "left",         AsFloat, wheels.wheelLeft       );
    READ_ARG( "right",        AsFloat, wheels.wheelRight      );
    READ_ARG( "height",       AsFloat, wheels.height          );
    READ_END();

    READ_LINE( "SetObjectMovableExhaust" );
    READ_ARG( "bubblesOnEnteringWater",     AsBool,  exhaust.bubblesOnEnteringWater     );
    READ_ARG( "bubblesOnEnteringWaterTime", AsFloat, exhaust.bubblesOnEnteringWaterTime );
    READ_ARG( "dropsOnLeavingWater",        AsBool,  exhaust.dropsOnLeavingWater        );
    READ_ARG( "onCrashAsHuman",             AsBool,  exhaust.onCrashAsHuman             );
    READ_ARG( "onCrashAsTrackedRobot",      AsBool,  exhaust.onCrashAsTrackedRobot      );
    READ_ARG( "onCrashAsHeavyRobot",        AsBool,  exhaust.onCrashAsHeavyRobot        );
    READ_ARG( "onLandAsHuman",              AsBool,  exhaust.onLandAsHuman              );
    READ_ARG( "onLandAsWingedRobot",        AsBool,  exhaust.onLandAsWingedRobot        );
    READ_ARG( "onLandAsHeavyRobot",         AsBool,  exhaust.onLandAsHeavyRobot         );
    READ_ARG( "onLandAsNormalRobot",        AsBool,  exhaust.onLandAsNormalRobot        );
    READ_ARG( "onFlightAsHuman",            AsBool,  exhaust.onFlightAsHuman            );
    READ_ARG( "onFlightAsWingedRobot",      AsBool,  exhaust.onFlightAsWingedRobot      );
    READ_ARG( "onSwimAsHuman",              AsBool,  exhaust.onSwimAsHuman              );
    READ_ARG( "onSwimAsAmphibiousRobot",    AsBool,  exhaust.onSwimAsAmphibiousRobot    );
    READ_END();

    READ_LINE( "SetObjectMovableWater" );
    READ_ARG( "waterLevel",     AsFloat, water.waterLevel      );
    READ_ARG( "splashLevelMin", AsFloat, water.splashLevelMin  );
    READ_ARG( "splashLevelMax", AsFloat, water.splashLevelMax  );
    READ_ARG( "splashDiameter", AsFloat, water.splashDiameter  );
    READ_ARG( "splashForce",    AsFloat, water.splashForce     );
    READ_END();

    return false;
}

void CObjectMovableDetails::Write(CLevelParser* parser, ObjectType type)
{
    CObjectMovableDetails def;

    WRITE_LINE( "SetObjectMovable" );
    WRITE_ARG( "enabled", def, enabled );
    WRITE_ARG( "drive",   def, drive   );
    WRITE_END();

    WRITE_LINE( "SetObjectMovableLinear" );
    WRITE_ARG( "advanceAccel", def, linMotion.advanceAccel );
    WRITE_ARG( "recedeAccel",  def, linMotion.recedeAccel  );
    WRITE_ARG( "stopAccel",    def, linMotion.stopAccel    );
    WRITE_ARG( "motorAccel",   def, linMotion.motorAccel   );
    WRITE_ARG( "advanceSpeed", def, linMotion.advanceSpeed );
    WRITE_ARG( "recedeSpeed",  def, linMotion.recedeSpeed  );
    WRITE_ARG( "motorSpeed",   def, linMotion.motorSpeed   );
    WRITE_ARG( "currentSpeed", def, linMotion.currentSpeed );
    WRITE_ARG( "terrainForce", def, linMotion.terrainForce );
    WRITE_ARG( "terrainSpeed", def, linMotion.terrainSpeed );
    WRITE_ARG( "terrainSlide", def, linMotion.terrainSlide );
    WRITE_ARG( "realSpeed",    def, linMotion.realSpeed    );
    WRITE_ARG( "finalInclin",  def, linMotion.finalInclin  );
    WRITE_END();

    WRITE_LINE( "SetObjectMovableCircular" );
    WRITE_ARG( "advanceAccel", def, cirMotion.advanceAccel );
    WRITE_ARG( "recedeAccel",  def, cirMotion.recedeAccel  );
    WRITE_ARG( "stopAccel",    def, cirMotion.stopAccel    );
    WRITE_ARG( "motorAccel",   def, cirMotion.motorAccel   );
    WRITE_ARG( "advanceSpeed", def, cirMotion.advanceSpeed );
    WRITE_ARG( "recedeSpeed",  def, cirMotion.recedeSpeed  );
    WRITE_ARG( "motorSpeed",   def, cirMotion.motorSpeed   );
    WRITE_ARG( "currentSpeed", def, cirMotion.currentSpeed );
    WRITE_ARG( "terrainForce", def, cirMotion.terrainForce );
    WRITE_ARG( "terrainSpeed", def, cirMotion.terrainSpeed );
    WRITE_ARG( "terrainSlide", def, cirMotion.terrainSlide );
    WRITE_ARG( "realSpeed",    def, cirMotion.realSpeed    );
    WRITE_ARG( "finalInclin",  def, cirMotion.finalInclin  );
    WRITE_END();

    WRITE_LINE( "SetObjectMovableWheels" );
    WRITE_ARG( "front",        def, wheels.wheelFront      );
    WRITE_ARG( "back",         def, wheels.wheelBack       );
    WRITE_ARG( "left",         def, wheels.wheelLeft       );
    WRITE_ARG( "right",        def, wheels.wheelRight      );
    WRITE_ARG( "height",       def, wheels.height          );
    WRITE_END();

    WRITE_LINE( "SetObjectMovableExhaust" );
    WRITE_ARG( "bubblesOnEnteringWater",     def,  exhaust.bubblesOnEnteringWater     );
    WRITE_ARG( "bubblesOnEnteringWaterTime", def, exhaust.bubblesOnEnteringWaterTime );
    WRITE_ARG( "dropsOnLeavingWater",        def,  exhaust.dropsOnLeavingWater        );
    WRITE_ARG( "onCrashAsHuman",             def,  exhaust.onCrashAsHuman             );
    WRITE_ARG( "onCrashAsTrackedRobot",      def,  exhaust.onCrashAsTrackedRobot      );
    WRITE_ARG( "onCrashAsHeavyRobot",        def,  exhaust.onCrashAsHeavyRobot        );
    WRITE_ARG( "onLandAsHuman",              def,  exhaust.onLandAsHuman              );
    WRITE_ARG( "onLandAsWingedRobot",        def,  exhaust.onLandAsWingedRobot        );
    WRITE_ARG( "onLandAsHeavyRobot",         def,  exhaust.onLandAsHeavyRobot         );
    WRITE_ARG( "onLandAsNormalRobot",        def,  exhaust.onLandAsNormalRobot        );
    WRITE_ARG( "onFlightAsHuman",            def,  exhaust.onFlightAsHuman            );
    WRITE_ARG( "onFlightAsWingedRobot",      def,  exhaust.onFlightAsWingedRobot      );
    WRITE_ARG( "onSwimAsHuman",              def,  exhaust.onSwimAsHuman              );
    WRITE_ARG( "onSwimAsAmphibiousRobot",    def,  exhaust.onSwimAsAmphibiousRobot    );
    WRITE_END();

    WRITE_LINE( "SetObjectMovableWater" );
    WRITE_ARG( "waterLevel",     def, water.waterLevel      );
    WRITE_ARG( "splashLevelMin", def, water.splashLevelMin  );
    WRITE_ARG( "splashLevelMax", def, water.splashLevelMax  );
    WRITE_ARG( "splashDiameter", def, water.splashDiameter  );
    WRITE_ARG( "splashForce",    def, water.splashForce     );
    WRITE_END();
}

CObjectMovableDetails GetObjectMovableDetails(CObject* obj)
{
    return CObjectDetails::GetInstance().GetObjectDetails(obj).movable;
}

CObjectMovableDetails GetObjectMovableDetails(ObjectType type)
{
    return CObjectDetails::GetInstance().GetObjectDetails(type).movable;
}
