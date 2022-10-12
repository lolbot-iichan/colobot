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

    READ_LINE( "AddObjectControllableWidget" );
    READ_NEW( id,                                       controls.widgets                            );
    READ_ARG( "position",               AsPoint,        controls.widgets[id].position               );
    READ_ARG( "size",                   AsPoint,        controls.widgets[id].size                   );
    READ_ARG( "widget",                 AsWidgetType,   controls.widgets[id].widgetType             );
    if ( controls.widgets[id].widgetType == Ui::WIDGET_COLOR_BUTTON )
        { READ_ARG( "color",            AsColor,        controls.widgets[id].params.color           ); }
    else
        { READ_ARG( "icon",             AsInt,          controls.widgets[id].params.icon            ); }
    READ_ARG( "event",                  AsEventType,    controls.widgets[id].event                  );
    READ_ARG( "default",                AsBool,         controls.widgets[id].isDefault              );
    READ_ARG( "immediat",               AsBool,         controls.widgets[id].isImmediat             );
    READ_ARG( "disabledByTrainer",      AsBool,         controls.widgets[id].disabledByTrainer      );
    READ_ARG( "disabledByPlusExplorer", AsBool,         controls.widgets[id].disabledByPlusExplorer );
    READ_ARG( "onBuildingEnabled",      AsBuildFlag,    controls.widgets[id].onBuildingEnabled      );
    READ_ARG( "onResearchDone",         AsResearchFlag, controls.widgets[id].onResearchDone         );
    READ_END();

    READ_LINE( "AddObjectControllableLight" );
    READ_NEW( id,                         lights                    );
    READ_ARG( "color",    AsParticleType, lights[id].color          );
    READ_ARG( "position", AsPoint,        lights[id].position       );
    READ_ARG( "partNum",  AsInt,          lights[id].partNum        );
    READ_ARG( "zoom",     AsFloat,        lights[id].zoom           );
    READ_ARG( "trainer",  AsInt,          lights[id].trainerMatcher );
    READ_END();

    return false;
}

void CObjectControllableDetails::Write(CLevelParser* parser, ObjectType type)
{
    CObjectControllableDetails def;

    WRITE_LINE( "SetObjectControllable" );
    WRITE_ARG( "enabled",        def, enabled                          );
    WRITE_ARG( "selectable",     def, selectable                       );
    WRITE_ARG( "infectable",     def, infectable                       );
    WRITE_ARG( "icon",           def, shortcut.icon                    );
    WRITE_ARG( "isBuilding",     def, shortcut.isBuilding              );
    WRITE_ARG( "isMovable",      def, shortcut.isMovable               );
    WRITE_ARG( "programs",       def, controls.hasProgramUI            );
    WRITE_ARG( "bPrograms",      def, controls.hasProgramUIBlink       );
    WRITE_ARG( "hBuilder",       def, controls.hasBuilderUIHuman       );
    WRITE_ARG( "rBuilder",       def, controls.hasBuilderUIRobot       );
    WRITE_ARG( "rShielder",      def, controls.hasShielderUIRobot      );
    WRITE_ARG( "rScribbler",     def, controls.hasScribblerUIRobot     );
    WRITE_ARG( "noFlyWhileGrab", def, controls.disableFlyWhileGrabbing );
    WRITE_END();

    WRITE_LINE( "SetObjectControllableCamera" );
    WRITE_ARG( "changable",                 def, camera.isCameraTypeChangable                );
    WRITE_ARG( "persistent",                def, camera.isCameraTypePersistent               );
    WRITE_ARG( "default",                   def, camera.defaultCamera                        );
    WRITE_ARG( "visitDist",                 def, camera.visit.distance                       );
    WRITE_ARG( "visitHeight",               def, camera.visit.height                         );
    WRITE_ARG( "fixedNoCollision",          def, camera.fixed.disableCollisions              );
    WRITE_ARG( "onboardNoCorners",          def, camera.onboard.disableCorners               );
    WRITE_ARG( "onboardCrosshair",          def, camera.onboard.hasCrosshair                 );
    WRITE_ARG( "partNum",                   def, camera.onboard.partNum                      );
    WRITE_ARG( "position",                  def, camera.onboard.position                     );
    WRITE_ARG( "backDistance",              def, camera.back.distance                        );
    WRITE_ARG( "backMinimum",               def, camera.back.distanceMin                     );
    WRITE_ARG( "backHeight",                def, camera.back.height                          );
    WRITE_ARG( "backRotationY",             def, camera.back.rotationY                       );
    WRITE_ARG( "backRotationZ",             def, camera.back.rotationZ                       );
    WRITE_ARG( "transparencyDisableOthers", def, camera.back.disableOtherObjectsTransparency );
    WRITE_ARG( "transparencyDisable",       def, camera.back.disableObjectTransparency       );
    WRITE_ARG( "transparencyGateHack",      def, camera.back.hasGateTransparency             );
    WRITE_END();

    for ( auto it: controls.widgets )
    {
        Ui::CWidget defW;

        WRITE_LINE( "AddObjectControllableWidget" );
        WRITE_IT( "position",               defW, position               );
        WRITE_IT( "size",                   defW, size                   );
        WRITE_IT( "widget",                 defW, widgetType             );
        if ( it.widgetType == Ui::WIDGET_COLOR_BUTTON )
            { WRITE_IT( "color",            defW, params.color           ); }
        else
            { WRITE_IT( "icon",             defW, params.icon            ); }
        WRITE_IT( "event",                  defW, event                  );
        WRITE_IT( "default",                defW, isDefault              );
        WRITE_IT( "immediat",               defW, isImmediat             );
        WRITE_IT( "disabledByTrainer",      defW, disabledByTrainer      );
        WRITE_IT( "disabledByPlusExplorer", defW, disabledByPlusExplorer );
        WRITE_IT( "onBuildingEnabled",      defW, onBuildingEnabled      );
        WRITE_IT( "onResearchDone",         defW, onResearchDone         );
        WRITE_END();
    }

    for ( auto it: lights )
    {
        CObjectControlLightsDetails defL;
        WRITE_LINE( "AddObjectControllableLight" );
        WRITE_IT( "color",    defL, color          );
        WRITE_IT( "position", defL, position       );
        WRITE_IT( "partNum",  defL, partNum        );
        WRITE_IT( "zoom",     defL, zoom           );
        WRITE_IT( "trainer",  defL, trainerMatcher );
        WRITE_END();
    }
}

CObjectControllableDetails GetObjectControllableDetails(CObject* obj)
{
    return CObjectDetails::GetInstance().GetObjectDetails(obj).controllable;
}