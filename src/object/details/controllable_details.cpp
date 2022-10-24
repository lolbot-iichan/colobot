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
 * \file object/details/controllable_details.cpp
 * \brief CObjectControllableDetails - set of tweaks for Controllable objects
 */

#include "level/parser/parser.h"

#include "object/details/details_provider.h"
#include "object/details/hardcode.h"
#include "object/details/macro.h"
#include "object/details/controllable_details.h"

void CObjectControllableDetails::ReadHardcode(ObjectType type)
{
    CHardcodeCollection hardcode;

    enabled    = hardcode.IsControllable(type);
    selectable = hardcode.IsSelectableByDefault(type);
    infectable = hardcode.IsInfectable(type);
    
    shortcut.icon                               = hardcode.GetShortcutIcon(type);
    shortcut.isBuilding                         = hardcode.IsShortcutBuilding(type);
    shortcut.isMovable                          = hardcode.IsShortcutMovable(type);
    controls.hasProgramUI                       = hardcode.HasUserInterfaceProgramUI(type);
    controls.hasProgramUIBlink                  = hardcode.HasUserInterfaceProgramUIBlink(type);
    controls.hasBuilderUIHuman                  = hardcode.HasUserInterfaceBuilderUIHuman(type);
    controls.hasBuilderUIRobot                  = hardcode.HasUserInterfaceBuilderUIRobot(type);
    controls.hasShielderUIRobot                 = hardcode.HasUserInterfaceShielderUIRobot(type);
    controls.hasScribblerUIRobot                = hardcode.HasUserInterfaceScribblerUIRobot(type);
    controls.disableFlyWhileGrabbing            = hardcode.HasUserInterfaceDisableFlyWhileGrabbing(type);
    controls.widgets                            = hardcode.GetUserInterfaceWidgetList(type);

    camera.isCameraTypeChangable                = hardcode.IsCameraTypeChangable(type);
    camera.isCameraTypePersistent               = hardcode.IsCameraTypePersistent(type);
    camera.defaultCamera                        = hardcode.GetDefaultCameraType(type);
    camera.visit.distance                       = hardcode.GetVisitCameraDistance(type);
    camera.visit.height                         = hardcode.GetVisitCameraHeight(type);
    camera.fixed.disableCollisions              = hardcode.DisableCollisionsOnFixCamera(type);
    camera.onboard.disableCorners               = hardcode.DisableOnboardCameraCorners(type);
    camera.onboard.hasCrosshair                 = hardcode.HasOnboardCameraCrosshair(type);
    camera.onboard.partNum                      = 0;
    camera.onboard.position                     = hardcode.GetOnboardCameraPosition(type);
    camera.back.distance                        = hardcode.GetBackCameraDistance(type);
    camera.back.distanceMin                     = hardcode.GetBackCameraDistanceMin(type);
    camera.back.height                          = hardcode.GetBackCameraHeight(type);
    camera.back.rotationY                       = hardcode.GetBackCameraRotationY(type);
    camera.back.rotationZ                       = hardcode.GetBackCameraRotationZ(type);
    camera.back.disableOtherObjectsTransparency = hardcode.DisableBackCameraCanForceTransparency(type);
    camera.back.disableObjectTransparency       = hardcode.DisableBackCameraCanViewAsTransparent(type);
    camera.back.hasGateTransparency             = hardcode.HasGateTransparencyOnBackCamera(type);

    lights = hardcode.GetControlLights(type);
}

bool CObjectControllableDetails::Read(CLevelParserLine* line)
{
    READ_LINE( "SetObjectControllable" );
    READ_ARG( "enabled",        AsBool, enabled                          );
    READ_ARG( "selectable",     AsBool, selectable                       );
    READ_ARG( "infectable",     AsBool, infectable                       );
    READ_ARG( "icon",           AsInt,  shortcut.icon                    );
    READ_ARG( "isBuilding",     AsBool, shortcut.isBuilding              );
    READ_ARG( "isMovable",      AsBool, shortcut.isMovable               );
    READ_ARG( "programs",       AsBool, controls.hasProgramUI            );
    READ_ARG( "bPrograms",      AsBool, controls.hasProgramUIBlink       );
    READ_ARG( "hBuilder",       AsBool, controls.hasBuilderUIHuman       );
    READ_ARG( "rBuilder",       AsBool, controls.hasBuilderUIRobot       );
    READ_ARG( "rShielder",      AsBool, controls.hasShielderUIRobot      );
    READ_ARG( "rScribbler",     AsBool, controls.hasScribblerUIRobot     );
    READ_ARG( "noFlyWhileGrab", AsBool, controls.disableFlyWhileGrabbing );
    READ_END();

    READ_LINE( "SetObjectControllableCamera" );
    READ_ARG( "changable",                 AsBool,       camera.isCameraTypeChangable                );
    READ_ARG( "persistent",                AsBool,       camera.isCameraTypePersistent               );
    READ_ARG( "default",                   AsCameraType, camera.defaultCamera                        );
    READ_ARG( "visitDist",                 AsFloat,      camera.visit.distance                       );
    READ_ARG( "visitHeight",               AsFloat,      camera.visit.height                         );
    READ_ARG( "fixedNoCollision",          AsBool,       camera.fixed.disableCollisions              );
    READ_ARG( "onboardNoCorners",          AsBool,       camera.onboard.disableCorners               );
    READ_ARG( "onboardCrosshair",          AsBool,       camera.onboard.hasCrosshair                 );
    READ_ARG( "partNum",                   AsInt,        camera.onboard.partNum                      );
    READ_ARG( "position",                  AsPoint,      camera.onboard.position                     );
    READ_ARG( "backDistance",              AsFloat,      camera.back.distance                        );
    READ_ARG( "backMinimum",               AsFloat,      camera.back.distanceMin                     );
    READ_ARG( "backHeight",                AsFloat,      camera.back.height                          );
    READ_ARG( "backRotationY",             AsFloat,      camera.back.rotationY                       );
    READ_ARG( "backRotationZ",             AsFloat,      camera.back.rotationZ                       );
    READ_ARG( "transparencyDisableOthers", AsBool,       camera.back.disableOtherObjectsTransparency );
    READ_ARG( "transparencyDisable",       AsBool,       camera.back.disableObjectTransparency       );
    READ_ARG( "transparencyGateHack",      AsBool,       camera.back.hasGateTransparency             );
    READ_END();

    READ_IT_LINE( "AddObjectControllableWidget", "UpdObjectControllableWidget", "ClrObjectControllableWidget", controls.widgets );
    READ_IT_ARG( "position",               AsPoint,        position               );
    READ_IT_ARG( "size",                   AsPoint,        size                   );
    READ_IT_ARG( "widget",                 AsWidgetType,   widgetType             );
    if ( it.widgetType == Ui::WIDGET_COLOR_BUTTON )
        { READ_IT_ARG( "color",            AsColor,        params.color           ); }
    else
        { READ_IT_ARG( "icon",             AsInt,          params.icon            ); }
    READ_IT_ARG( "event",                  AsEventType,    event                  );
    READ_IT_ARG( "default",                AsBool,         isDefault              );
    READ_IT_ARG( "immediat",               AsBool,         isImmediat             );
    READ_IT_ARG( "disabledByTrainer",      AsBool,         disabledByTrainer      );
    READ_IT_ARG( "disabledByPlusExplorer", AsBool,         disabledByPlusExplorer );
    READ_IT_ARG( "onBuildingEnabled",      AsBuildFlag,    onBuildingEnabled      );
    READ_IT_ARG( "onResearchDone",         AsResearchFlag, onResearchDone         );
    READ_IT_END();

    READ_IT_LINE( "AddObjectControllableLight", "UpdObjectControllableLight", "ClrObjectControllableLight", lights );
    READ_IT_ARG( "color",    AsParticleType, color          );
    READ_IT_ARG( "position", AsPoint,        position       );
    READ_IT_ARG( "partNum",  AsInt,          partNum        );
    READ_IT_ARG( "zoom",     AsFloat,        zoom           );
    READ_IT_ARG( "trainer",  AsInt,          trainerMatcher );
    READ_IT_END();

    return false;
}

void CObjectControllableDetails::Write(CLevelParser* parser, ObjectType type)
{
    WRITE_LINE( "SetObjectControllable" );
    WRITE_ARG( "enabled",        AsBool, enabled                          );
    WRITE_ARG( "selectable",     AsBool, selectable                       );
    WRITE_ARG( "infectable",     AsBool, infectable                       );
    WRITE_ARG( "icon",           AsInt,  shortcut.icon                    );
    WRITE_ARG( "isBuilding",     AsBool, shortcut.isBuilding              );
    WRITE_ARG( "isMovable",      AsBool, shortcut.isMovable               );
    WRITE_ARG( "programs",       AsBool, controls.hasProgramUI            );
    WRITE_ARG( "bPrograms",      AsBool, controls.hasProgramUIBlink       );
    WRITE_ARG( "hBuilder",       AsBool, controls.hasBuilderUIHuman       );
    WRITE_ARG( "rBuilder",       AsBool, controls.hasBuilderUIRobot       );
    WRITE_ARG( "rShielder",      AsBool, controls.hasShielderUIRobot      );
    WRITE_ARG( "rScribbler",     AsBool, controls.hasScribblerUIRobot     );
    WRITE_ARG( "noFlyWhileGrab", AsBool, controls.disableFlyWhileGrabbing );
    WRITE_END();

    WRITE_LINE( "SetObjectControllableCamera" );
    WRITE_ARG( "changable",                 AsBool,       camera.isCameraTypeChangable                );
    WRITE_ARG( "persistent",                AsBool,       camera.isCameraTypePersistent               );
    WRITE_ARG( "default",                   AsCameraType, camera.defaultCamera                        );
    WRITE_ARG( "visitDist",                 AsFloat,      camera.visit.distance                       );
    WRITE_ARG( "visitHeight",               AsFloat,      camera.visit.height                         );
    WRITE_ARG( "fixedNoCollision",          AsBool,       camera.fixed.disableCollisions              );
    WRITE_ARG( "onboardNoCorners",          AsBool,       camera.onboard.disableCorners               );
    WRITE_ARG( "onboardCrosshair",          AsBool,       camera.onboard.hasCrosshair                 );
    WRITE_ARG( "partNum",                   AsInt,        camera.onboard.partNum                      );
    WRITE_ARG( "position",                  AsPoint,      camera.onboard.position                     );
    WRITE_ARG( "backDistance",              AsFloat,      camera.back.distance                        );
    WRITE_ARG( "backMinimum",               AsFloat,      camera.back.distanceMin                     );
    WRITE_ARG( "backHeight",                AsFloat,      camera.back.height                          );
    WRITE_ARG( "backRotationY",             AsFloat,      camera.back.rotationY                       );
    WRITE_ARG( "backRotationZ",             AsFloat,      camera.back.rotationZ                       );
    WRITE_ARG( "transparencyDisableOthers", AsBool,       camera.back.disableOtherObjectsTransparency );
    WRITE_ARG( "transparencyDisable",       AsBool,       camera.back.disableObjectTransparency       );
    WRITE_ARG( "transparencyGateHack",      AsBool,       camera.back.hasGateTransparency             );
    WRITE_END();

    WRITE_IT_LINE( "AddObjectControllableWidget", controls.widgets );
    WRITE_IT_ARG( "position",               AsPoint,        position               );
    WRITE_IT_ARG( "size",                   AsPoint,        size                   );
    WRITE_IT_ARG( "widget",                 AsWidgetType,   widgetType             );
    if ( it.widgetType == Ui::WIDGET_COLOR_BUTTON )
        { WRITE_IT_ARG( "color",            AsColor,        params.color           ); }
    else
        { WRITE_IT_ARG( "icon",             AsInt,          params.icon            ); }
    WRITE_IT_ARG( "event",                  AsEventType,    event                  );
    WRITE_IT_ARG( "default",                AsBool,         isDefault              );
    WRITE_IT_ARG( "immediat",               AsBool,         isImmediat             );
    WRITE_IT_ARG( "disabledByTrainer",      AsBool,         disabledByTrainer      );
    WRITE_IT_ARG( "disabledByPlusExplorer", AsBool,         disabledByPlusExplorer );
    WRITE_IT_ARG( "onBuildingEnabled",      AsBuildFlag,    onBuildingEnabled      );
    WRITE_IT_ARG( "onResearchDone",         AsResearchFlag, onResearchDone         );
    WRITE_IT_END();

    WRITE_IT_LINE( "AddObjectControllableLight", lights );
    WRITE_IT_ARG( "color",    AsParticleType, color          );
    WRITE_IT_ARG( "position", AsPoint,        position       );
    WRITE_IT_ARG( "partNum",  AsInt,          partNum        );
    WRITE_IT_ARG( "zoom",     AsFloat,        zoom           );
    WRITE_IT_ARG( "trainer",  AsInt,          trainerMatcher );
    WRITE_IT_END();
}

CObjectControllableDetails GetObjectControllableDetails(CObject* obj)
{
    return CObjectDetails::GetInstance().GetObjectDetails(obj).controllable;
}