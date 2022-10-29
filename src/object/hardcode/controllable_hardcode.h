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

enum ObjectType : unsigned int;

#include "object/hardcode/controllable_hardcode.h"

struct CControllableHardcodeCollection
{
    static bool IsControllable(ObjectType type);
    static bool IsSelectableByDefault(ObjectType type);
    static bool IsInfectable(ObjectType type);
    static bool IsTrainable(ObjectType type);

    static bool IsShortcutBuilding(ObjectType type);
    static bool IsShortcutMovable(ObjectType type);
    // -1      for objects without icon
    // 0-63    for textures on button1.png 
    // 64-127  for textures on button2.png 
    // 128-191 for textures on button3.png 
    // 192-255 for textures on button4.png 
    static int GetShortcutIcon(ObjectType type);

    static bool HasUserInterfaceProgramUI(ObjectType type);
    static bool HasUserInterfaceProgramUIBlink(ObjectType type);
    static bool HasUserInterfaceBuilderUIHuman(ObjectType type);
    static bool HasUserInterfaceBuilderUIRobot(ObjectType type);
    static bool HasUserInterfaceShielderUIRobot(ObjectType type);
    static bool HasUserInterfaceScribblerUIRobot(ObjectType type);
    static bool HasUserInterfaceDisableFlyWhileGrabbing(ObjectType type);
    static std::vector<Ui::CWidget> GetUserInterfaceWidgetList(ObjectType type);
    static std::vector<CObjectBuilderMenuButtons> GetBuilderMenuButtons(ObjectType type);

    static bool IsCameraTypeChangable(ObjectType type);
    static bool IsCameraTypePersistent(ObjectType type);
    static Gfx::CameraType GetDefaultCameraType(ObjectType type);
    static float GetVisitCameraDistance(ObjectType type);
    static float GetVisitCameraHeight(ObjectType type);
    static bool DisableCollisionsOnFixCamera(ObjectType type);
    static bool DisableOnboardCameraCorners(ObjectType type);
    static bool HasOnboardCameraCrosshair(ObjectType type);
    static glm::vec3 GetOnboardCameraPosition(ObjectType type);
    static float GetBackCameraDistance(ObjectType type);
    static float GetBackCameraDistanceMin(ObjectType type);
    static float GetBackCameraHeight(ObjectType type);
    static float GetBackCameraRotationY(ObjectType type);
    static float GetBackCameraRotationZ(ObjectType type);
    static bool DisableBackCameraCanForceTransparency(ObjectType type);
    static bool DisableBackCameraCanViewAsTransparent(ObjectType type);
    static bool HasGateTransparencyOnBackCamera(ObjectType type);

    static std::vector<CObjectControlLightsDetails> GetControlLights(ObjectType type);
};