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

#include "object/details/macro.h"
#include "object/details/movable_details.h"

#include "object/hardcode/movable_hardcode.h"

void CObjectMovableDetails::ReadHardcode(ObjectType type)
{
    

    enabled     = CMovableHardcodeCollection::IsMovable(type);
    motionClass = CMovableHardcodeCollection::GetMotionClass(type);
    sounds      = CMovableHardcodeCollection::GetMotionSounds(type);
    pshhh       = CMovableHardcodeCollection::GetMotionSoundPshhh(type);

    linMotion   = CMovableHardcodeCollection::GetLinMotion(type);
    cirMotion   = CMovableHardcodeCollection::GetCirMotion(type);
    wheels      = CMovableHardcodeCollection::GetWheels(type);

    slowUnderWater = CMovableHardcodeCollection::GetSlowUnderWater(type);
    haveSatCom     = CMovableHardcodeCollection::GetHaveSatCom(type);
    onSlide        = CMovableHardcodeCollection::GetSoundOnSlide(type);

    energyFactor   = CMovableHardcodeCollection::GetMovableEnergyFactor(type);

    tilt.onLandAsHuman           = CMovableHardcodeCollection::IsTiltOnLandAsHuman(type);
    tilt.onLandAsWingedRobot     = CMovableHardcodeCollection::IsTiltOnLandAsWingedRobot(type);
    tilt.onLandAsNormalRobot     = CMovableHardcodeCollection::IsTiltOnLandAsNormalRobot(type);
    tilt.onLandAsApolloRobot     = CMovableHardcodeCollection::IsTiltOnLandAsApolloRobot(type);
    tilt.onFlightAsAlienWasp     = CMovableHardcodeCollection::IsTiltOnFlightAsAlienWasp(type);
    tilt.onFlightAsHuman         = CMovableHardcodeCollection::IsTiltOnFlightAsHuman(type);
    tilt.onFlightAsWingedRobot   = CMovableHardcodeCollection::IsTiltOnFlightAsWingedRobot(type);
    tilt.onSwimAsHuman           = CMovableHardcodeCollection::IsTiltOnSwimAsHuman(type);

    exhaust.bubblesOnEnteringWater   = CMovableHardcodeCollection::IsExhaustBubblesOnEnteringWater(type);
    exhaust.bubblesOnEnteringWaterTime = CMovableHardcodeCollection::IsExhaustBubblesOnEnteringWaterTime(type);
    exhaust.dropsOnLeavingWater     = CMovableHardcodeCollection::IsExhaustDropsOnLeavingWater(type);
    exhaust.onCrashAsHuman          = CMovableHardcodeCollection::IsExhaustOnCrashAsHuman(type);
    exhaust.onCrashAsTrackedRobot   = CMovableHardcodeCollection::IsExhaustOnCrashAsTrackedRobot(type);
    exhaust.onCrashAsHeavyRobot     = CMovableHardcodeCollection::IsExhaustOnCrashAsHeavyRobot(type);
    exhaust.onLandAsHuman           = CMovableHardcodeCollection::IsExhaustOnLandAsHuman(type);
    exhaust.onLandAsWingedRobot     = CMovableHardcodeCollection::IsExhaustOnLandAsWingedRobot(type);
    exhaust.onLandAsHeavyRobot      = CMovableHardcodeCollection::IsExhaustOnLandAsHeavyRobot(type);
    exhaust.onLandAsNormalRobot     = CMovableHardcodeCollection::IsExhaustOnLandAsNormalRobot(type);
    exhaust.onFlightAsHuman         = CMovableHardcodeCollection::IsExhaustOnFlightAsHuman(type);
    exhaust.onFlightAsWingedRobot   = CMovableHardcodeCollection::IsExhaustOnFlightAsWingedRobot(type);
    exhaust.onSwimAsHuman           = CMovableHardcodeCollection::IsExhaustOnSwimAsHuman(type);
    exhaust.onSwimAsAmphibiousRobot = CMovableHardcodeCollection::IsExhaustOnSwimAsAmphibiousRobot(type);

    water.waterLevel                = CMovableHardcodeCollection::GetMaxSafeWaterLevel(type);
    water.splashLevelMin            = CMovableHardcodeCollection::GetWaterSplashLevelMin(type);
    water.splashLevelMax            = CMovableHardcodeCollection::GetWaterSplashLevelMax(type);
    water.splashDiameter            = CMovableHardcodeCollection::GetWaterSplashDiameter(type);
    water.splashForce               = CMovableHardcodeCollection::GetWaterSplashForce(type);

    tracked                         = CMovableHardcodeCollection::GetTrackedDetails(type);
    wheeled                         = CMovableHardcodeCollection::GetWheeledDetails(type);
}

bool CObjectMovableDetails::Read(CLevelParserLine* line)
{
    READ_LINE( "SetObjectMovable" );
    READ_ARG( "enabled",        AsBool,      enabled        );
    READ_ARG( "class",          AsInt,       motionClass    );
    READ_ARG( "sounds",         AsInt,       sounds         );
    READ_ARG( "pshhh",          AsBool,      pshhh          );
    READ_ARG( "slowUnderWater", AsBool,      slowUnderWater );
    READ_ARG( "haveSatCom",     AsBool,      haveSatCom     );
    READ_ARG( "onSlide",        AsSoundType, onSlide        );
    READ_ARG( "energyFactor",   AsFloat,     energyFactor   );
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

    READ_LINE( "SetObjectMovableTilt" );
    READ_ARG( "onLandAsHuman",              AsBool,  tilt.onLandAsHuman              );
    READ_ARG( "onLandAsWingedRobot",        AsBool,  tilt.onLandAsWingedRobot        );
    READ_ARG( "onLandAsNormalRobot",        AsBool,  tilt.onLandAsNormalRobot        );
    READ_ARG( "onLandAsApolloRobot",        AsBool,  tilt.onLandAsApolloRobot        );
    READ_ARG( "onFlightAsAlienWasp",        AsBool,  tilt.onFlightAsAlienWasp        );
    READ_ARG( "onFlightAsHuman",            AsBool,  tilt.onFlightAsHuman            );
    READ_ARG( "onFlightAsWingedRobot",      AsBool,  tilt.onFlightAsWingedRobot      );
    READ_ARG( "onSwimAsHuman",              AsBool,  tilt.onSwimAsHuman              );
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

    READ_LINE( "SetObjectMovableTracked" );
    READ_ARG( "rotationMin", AsFloat, tracked.rotationMin );
    READ_ARG( "rotationMax", AsFloat, tracked.rotationMax );
    READ_END();

    READ_LINE( "SetObjectMovableWheeled" );
    READ_ARG( "back",          AsFloat, wheeled.back          );
    READ_ARG( "front",         AsFloat, wheeled.front         );
    READ_ARG( "dist",          AsFloat, wheeled.dist          );
    READ_ARG( "radius",        AsFloat, wheeled.radius        );
    READ_ARG( "rotationSpeed", AsFloat, wheeled.rotationSpeed );
    READ_ARG( "hasMudCovers",  AsBool,  wheeled.hasMudCovers  );
    READ_END();

    return false;
}

void CObjectMovableDetails::Write(CLevelParser* parser, ObjectType type)
{
    WRITE_LINE( "SetObjectMovable" );
    WRITE_ARG( "enabled",        AsBool,      enabled        );
    WRITE_ARG( "class",          AsInt,       motionClass    );
    WRITE_ARG( "sounds",         AsInt,       sounds         );
    WRITE_ARG( "pshhh",          AsBool,      pshhh          );
    WRITE_ARG( "slowUnderWater", AsBool,      slowUnderWater );
    WRITE_ARG( "haveSatCom",     AsBool,      haveSatCom     );
    WRITE_ARG( "onSlide",        AsSoundType, onSlide        );
    WRITE_ARG( "energyFactor",   AsFloat,     energyFactor   );
    WRITE_END();

    WRITE_LINE( "SetObjectMovableLinear" );
    WRITE_ARG( "advanceAccel", AsPoint, linMotion.advanceAccel );
    WRITE_ARG( "recedeAccel",  AsPoint, linMotion.recedeAccel  );
    WRITE_ARG( "stopAccel",    AsPoint, linMotion.stopAccel    );
    WRITE_ARG( "motorAccel",   AsPoint, linMotion.motorAccel   );
    WRITE_ARG( "advanceSpeed", AsPoint, linMotion.advanceSpeed );
    WRITE_ARG( "recedeSpeed",  AsPoint, linMotion.recedeSpeed  );
    WRITE_ARG( "motorSpeed",   AsPoint, linMotion.motorSpeed   );
    WRITE_ARG( "currentSpeed", AsPoint, linMotion.currentSpeed );
    WRITE_ARG( "terrainForce", AsPoint, linMotion.terrainForce );
    WRITE_ARG( "terrainSpeed", AsPoint, linMotion.terrainSpeed );
    WRITE_ARG( "terrainSlide", AsPoint, linMotion.terrainSlide );
    WRITE_ARG( "realSpeed",    AsPoint, linMotion.realSpeed    );
    WRITE_ARG( "finalInclin",  AsPoint, linMotion.finalInclin  );
    WRITE_END();

    WRITE_LINE( "SetObjectMovableCircular" );
    WRITE_ARG( "advanceAccel", AsPoint, cirMotion.advanceAccel );
    WRITE_ARG( "recedeAccel",  AsPoint, cirMotion.recedeAccel  );
    WRITE_ARG( "stopAccel",    AsPoint, cirMotion.stopAccel    );
    WRITE_ARG( "motorAccel",   AsPoint, cirMotion.motorAccel   );
    WRITE_ARG( "advanceSpeed", AsPoint, cirMotion.advanceSpeed );
    WRITE_ARG( "recedeSpeed",  AsPoint, cirMotion.recedeSpeed  );
    WRITE_ARG( "motorSpeed",   AsPoint, cirMotion.motorSpeed   );
    WRITE_ARG( "currentSpeed", AsPoint, cirMotion.currentSpeed );
    WRITE_ARG( "terrainForce", AsPoint, cirMotion.terrainForce );
    WRITE_ARG( "terrainSpeed", AsPoint, cirMotion.terrainSpeed );
    WRITE_ARG( "terrainSlide", AsPoint, cirMotion.terrainSlide );
    WRITE_ARG( "realSpeed",    AsPoint, cirMotion.realSpeed    );
    WRITE_ARG( "finalInclin",  AsPoint, cirMotion.finalInclin  );
    WRITE_END();

    WRITE_LINE( "SetObjectMovableWheels" );
    WRITE_ARG( "front",        AsFloat, wheels.wheelFront      );
    WRITE_ARG( "back",         AsFloat, wheels.wheelBack       );
    WRITE_ARG( "left",         AsFloat, wheels.wheelLeft       );
    WRITE_ARG( "right",        AsFloat, wheels.wheelRight      );
    WRITE_ARG( "height",       AsFloat, wheels.height          );
    WRITE_END();

    WRITE_LINE( "SetObjectMovableTilt" );
    WRITE_ARG( "onLandAsHuman",              AsBool,  tilt.onLandAsHuman              );
    WRITE_ARG( "onLandAsWingedRobot",        AsBool,  tilt.onLandAsWingedRobot        );
    WRITE_ARG( "onLandAsNormalRobot",        AsBool,  tilt.onLandAsNormalRobot        );
    WRITE_ARG( "onLandAsApolloRobot",        AsBool,  tilt.onLandAsApolloRobot        );
    WRITE_ARG( "onFlightAsAlienWasp",        AsBool,  tilt.onFlightAsAlienWasp        );
    WRITE_ARG( "onFlightAsHuman",            AsBool,  tilt.onFlightAsHuman            );
    WRITE_ARG( "onFlightAsWingedRobot",      AsBool,  tilt.onFlightAsWingedRobot      );
    WRITE_ARG( "onSwimAsHuman",              AsBool,  tilt.onSwimAsHuman              );
    WRITE_END();

    WRITE_LINE( "SetObjectMovableExhaust" );
    WRITE_ARG( "bubblesOnEnteringWater",     AsBool,  exhaust.bubblesOnEnteringWater     );
    WRITE_ARG( "bubblesOnEnteringWaterTime", AsFloat, exhaust.bubblesOnEnteringWaterTime );
    WRITE_ARG( "dropsOnLeavingWater",        AsBool,  exhaust.dropsOnLeavingWater        );
    WRITE_ARG( "onCrashAsHuman",             AsBool,  exhaust.onCrashAsHuman             );
    WRITE_ARG( "onCrashAsTrackedRobot",      AsBool,  exhaust.onCrashAsTrackedRobot      );
    WRITE_ARG( "onCrashAsHeavyRobot",        AsBool,  exhaust.onCrashAsHeavyRobot        );
    WRITE_ARG( "onLandAsHuman",              AsBool,  exhaust.onLandAsHuman              );
    WRITE_ARG( "onLandAsWingedRobot",        AsBool,  exhaust.onLandAsWingedRobot        );
    WRITE_ARG( "onLandAsHeavyRobot",         AsBool,  exhaust.onLandAsHeavyRobot         );
    WRITE_ARG( "onLandAsNormalRobot",        AsBool,  exhaust.onLandAsNormalRobot        );
    WRITE_ARG( "onFlightAsHuman",            AsBool,  exhaust.onFlightAsHuman            );
    WRITE_ARG( "onFlightAsWingedRobot",      AsBool,  exhaust.onFlightAsWingedRobot      );
    WRITE_ARG( "onSwimAsHuman",              AsBool,  exhaust.onSwimAsHuman              );
    WRITE_ARG( "onSwimAsAmphibiousRobot",    AsBool,  exhaust.onSwimAsAmphibiousRobot    );
    WRITE_END();

    WRITE_LINE( "SetObjectMovableWater" );
    WRITE_ARG( "waterLevel",     AsFloat, water.waterLevel      );
    WRITE_ARG( "splashLevelMin", AsFloat, water.splashLevelMin  );
    WRITE_ARG( "splashLevelMax", AsFloat, water.splashLevelMax  );
    WRITE_ARG( "splashDiameter", AsFloat, water.splashDiameter  );
    WRITE_ARG( "splashForce",    AsFloat, water.splashForce     );
    WRITE_END();

    WRITE_LINE( "SetObjectMovableTracked" );
    WRITE_ARG( "rotationMin", AsFloat, tracked.rotationMin );
    WRITE_ARG( "rotationMax", AsFloat, tracked.rotationMax );
    WRITE_END();

    WRITE_LINE( "SetObjectMovableWheeled" );
    WRITE_ARG( "back",          AsFloat, wheeled.back          );
    WRITE_ARG( "front",         AsFloat, wheeled.front         );
    WRITE_ARG( "dist",          AsFloat, wheeled.dist          );
    WRITE_ARG( "radius",        AsFloat, wheeled.radius        );
    WRITE_ARG( "rotationSpeed", AsFloat, wheeled.rotationSpeed );
    WRITE_ARG( "hasMudCovers",  AsBool,  wheeled.hasMudCovers  );
    WRITE_END();
}
