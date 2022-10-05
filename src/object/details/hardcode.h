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
 * \file object/details/hardcode.h
 * \brief CHardcodeCollection - set of methods with various hardcoded info about all the objects in one place
 */

#pragma once

#include <map>
#include <string>
#include <vector>

#include "common/singleton.h"

#include "graphics/engine/engine_types.h"
#include "graphics/engine/pyro_type.h"

#include "level/research_type.h"

#include "math/vector.h"

#include "object/crash_sphere.h"
#include "object/object_type.h"

#include "object/details/automation_details.h"
#include "object/details/detectable_details.h"
#include "object/details/destroyable_details.h"
#include "object/details/controllable_details.h"
#include "object/details/creation_details.h"
#include "object/details/global_details.h"
#include "object/details/movable_details.h"
#include "object/details/task_executor_details.h"
#include "object/details/trace_drawing_details.h"


class CHardcodeCollection
{
public:

//////////////////////////////////////////////////////////////////////////////
// Object naming details
//////////////////////////////////////////////////////////////////////////////

// [naming/level] object name in level files (default is "")
std::string GetNameInLevelFiles(ObjectType type);
// [naming/level] object asias in level files (default is "")
std::string GetAliasInLevelFiles(ObjectType type);

// [naming/script] object name in script files (default is "")
std::string GetNameInScriptFiles(ObjectType type);
// [naming/script] object asias in script files (default is "")
std::string GetAliasInScriptFiles(ObjectType type);
// [naming/script] help topic name, e.g. "object/base" (default is "")
std::string GetHelpTopicPathName(ObjectType type);

// [naming/ui] localizable string used with gettext (default is "")
std::string GetDisplayedName(ObjectType type);
// [naming/ui] show player name instead of object name (default is false)
bool IsDisplayedNameAsPlayer(ObjectType type);



//////////////////////////////////////////////////////////////////////////////
// Object scripting details
//////////////////////////////////////////////////////////////////////////////

// [script/allowed] functions are binded to C++ implementations (default is false)
bool IsFunctionImplementedBuild(ObjectType type);
bool IsFunctionImplementedFlags(ObjectType type);
bool IsFunctionImplementedSniff(ObjectType type);
bool IsFunctionImplementedShield(ObjectType type);
bool IsFunctionImplementedRecycle(ObjectType type);
bool IsFunctionImplementedGrabAsHuman(ObjectType type);
bool IsFunctionImplementedGrabAsRobot(ObjectType type);
bool IsFunctionImplementedShootAsAnt(ObjectType type);
bool IsFunctionImplementedShootAsSpider(ObjectType type);
bool IsFunctionImplementedShootAsRobot(ObjectType type);

// [script/radar]  (default is false)
bool IsRadarExplicitOnly(ObjectType type);

ObjectType GetBaseType(ObjectType type);

// [script/radar] objects that could be find with radar functions by alias (default is vector with given id)
std::vector<ObjectType> GetObjectsFindableByType(ObjectType type);

// [script/produce] can object be used at produce() call (default is false)
bool IsValidObjectTypeId(ObjectType type);
// [script/produce] object that should also be created at produce() call (default is OBJECT_NULL)
ObjectType GetProduceContainer(ObjectType type);
// [script/produce] should be charged at produce() with -1 power (default is false)
bool IsProduceAlreadyCharged(ObjectType type);
// [script/produce] force manual mode for produced item (default is false)
bool IsProduceManual(ObjectType type);



//////////////////////////////////////////////////////////////////////////////
// Creation details
//////////////////////////////////////////////////////////////////////////////

// [create/model] base C++ class for object is switched by this (default is BASE_CLASS_NONE)
BaseClass GetCreationBaseClass(ObjectType type);
AutoClass GetCreationAutoClass(ObjectType type);

// [create/model] list of nodes of object model
std::vector<CObjectCreationModelNode> GetCreationModel(ObjectType type);
// [create/model] list of crash spheres of object model
std::vector<CrashSphere> GetCreationCrashSpheres(ObjectType type);
// [create/model] camera collision sphere of object model
Math::Sphere GetCreationCameraCollisionSphere(ObjectType type);
// [create/model] list of building levels platforms of object model
std::vector<CObjectCreationBuildingLevel> GetCreationBuildingLevels(ObjectType type);
// [create/model] details on object shadow circle
CObjectCreationShadowCircle GetCreationShadowCircle(ObjectType type);

// [create/model] additional object scale (default is 1.0f)
float GetCreationScale(ObjectType type);

// [create/model] should textures be forced to load (default is false)
bool IsCreationForceLoadTextures(ObjectType type);

// [create/model] should floor be adjusted (default is false)
bool IsCreationSetFloorHeight(ObjectType type);
// [create/model] should floor be adjusted x2 (default is false)
bool IsCreationFloorAdjust(ObjectType type);
// [create/model] should ignore gravity and hand in the air (default is false)
bool IsCreationFixedPosition(ObjectType type);



//////////////////////////////////////////////////////////////////////////////
// Common interface details
//////////////////////////////////////////////////////////////////////////////

DriveType GetDriveType(ObjectType type);
ToolType GetToolType(ObjectType type);

bool IsProgrammable(ObjectType type);
bool IsTaskExecutor(ObjectType type);
CObjectFlagTaskExecutorDetails GetFlagTaskExecutionDetails(ObjectType type);
CObjectSniffTaskExecutorDetails GetSniffTaskExecutionDetails(ObjectType type);
std::vector<CObjectFlagTaskExecutorObject>  GetFlagTaskExecutionObjects(ObjectType type);
std::vector<CObjectSniffTaskExecutorObject> GetSniffTaskExecutionObjects(ObjectType type);

bool IsTransportable(ObjectType type);
bool IsDropZoneShownOnPut(ObjectType type);

bool IsJosteable(ObjectType type);
Math::Sphere GetJostlingSphere(ObjectType type);
float GetJosteFactor(ObjectType type);

bool IsMovable(ObjectType type);
Motion GetLinMotion(ObjectType type);
Motion GetCirMotion(ObjectType type);
Character GetWheels(ObjectType type);
    
bool IsFlying(ObjectType type);
bool IsJetFlying(ObjectType type);

bool IsControllable(ObjectType type);
bool IsSelectableByDefault(ObjectType type);

bool IsPowerContainer(ObjectType type);

bool IsTraceDrawing(ObjectType type);
bool IsFunctionImplementedDrawAsRobot(ObjectType type);

bool IsRanged(ObjectType type);
float GetRangedRadius(ObjectType type);

// [damageble] implements interface (default is false)
bool IsDamageable(ObjectType type);

// [damageble/immunity] true, if immune to fireballs of Shooters (default is false)
bool IsImmuneToFireballs(ObjectType type);
// [damageble/immunity] true, if immune to particle of Ants (default is false)
bool IsImmuneToInsects(ObjectType type);
// [damageble/immunity] true, if immune to fireballs (default is false)
bool IsImmuneToSpiders(ObjectType type);
// [damageble/immunity] true, if immune to fireballs (default is false)
bool IsImmuneToOrgaballs(ObjectType type);
// [damageble/immunity] true, if immune to fireballs (default is false)
bool IsImmuneToPhazers(ObjectType type);
// [damagable/immunity] true, if immune to tower rays (default is true)
bool IsImmuneToTowerRays(ObjectType type);

// [destroyable] implements interface (default is false)
bool IsDestroyable(ObjectType type);
bool IsExplodesInWater(ObjectType type);
bool IsSquashedByHeavy(ObjectType type);

// [destroyable/pyro]
bool IsDestructionRemoveBuildingLevel(ObjectType type);
Gfx::PyroType GetDestructionByExplosion(ObjectType type);
Gfx::PyroType GetDestructionByWater(ObjectType type);
Gfx::PyroType GetDestructionByBurning(ObjectType type);
Gfx::PyroType GetDestructionByDrowned(ObjectType type);
Gfx::PyroType GetDestructionByWin(ObjectType type);
Gfx::PyroType GetDestructionBySquash(ObjectType type);
bool IsDestructionKilledByBurning(ObjectType type);
std::vector<CPyroBurnPartDetails> GetBurnParts(ObjectType type);
ObjectType GetTypeAfterBurn(ObjectType);

// [fragile] implements interface (default is false)
bool IsFragile(ObjectType type);
bool IsFragileBurnable(ObjectType type);

// [shielded] implements interface (default is false)
bool IsShielded(ObjectType type);
bool IsShieldAutoregen(ObjectType type);
float GetShieldAutoregenTime(ObjectType type);

// [sloted] implements interface (default is false)
bool IsSloted(ObjectType type);
bool HasCargoSlot(ObjectType type);
bool HasPowerSlot(ObjectType type);
bool HasOtherSlot(ObjectType type);
int GetCargoSlotPartNumber(ObjectType type);
Math::Vector GetCargoSlotPosition(ObjectType type);
Math::Vector GetPowerSlotPosition(ObjectType type);
Math::Vector GetOtherSlotPosition(ObjectType type);

bool IsThumpable(ObjectType type);

//////////////////////////////////////////////////////////////////////////////
// Camera details
//////////////////////////////////////////////////////////////////////////////

// [camera/types] could change camera type (default is false) 
bool IsCameraTypeChangable(ObjectType type);
// [camera/types] remember camera mode or  (default is false)
// true - remember object camera type while switching between objects
// false - reset camera to CAM_TYPE_BACK on each selection
bool IsCameraTypePersistent(ObjectType type);

// [camera/types] camera type on object selection (default is CAM_TYPE_BACK)
Gfx::CameraType GetDefaultCameraType(ObjectType type);

// [camera/visit] radius of ideal visit (default is 60.0f)
float GetVisitCameraDistance(ObjectType type);
// [camera/visit] height of ideal visit (default is 15.0f)
float GetVisitCameraHeight(ObjectType type);

// [camera/back] minimal distance for back camera (default is 30.0f) 
float GetBackCameraDistance(ObjectType type);
// [camera/back] minimal distance for back camera (default is 10.0f) 
float GetBackCameraDistanceMin(ObjectType type);
// [camera/back] height for back camera (default is 4.0f) 
float GetBackCameraHeight(ObjectType type);
// [camera/back] angle for back camera devided by M_PI (default is 1.0f)
float GetBackCameraRotationY(ObjectType type);
// [camera/back] angle for back camera devided by M_PI (default is 0.0f)
float GetBackCameraRotationZ(ObjectType type);

// [camera/back/transparency] can make other objects transparent when they overlap the back camera (default is false) 
bool DisableBackCameraCanForceTransparency(ObjectType type);
// [camera/back/transparency] can be transparent when overlaps someone's back camera (default is false) 
bool DisableBackCameraCanViewAsTransparent(ObjectType type);
// [camera/back/transparency] can be transparent or not depending on angles - hack for Factory Building (default is false) 
bool HasGateTransparencyOnBackCamera(ObjectType type);

// [camera/fix] can collide with someone's fix camera (default is false) 
bool DisableCollisionsOnFixCamera(ObjectType type);

// [camera/onboard] on-board camera has robotic corners (default is false) 
bool DisableOnboardCameraCorners(ObjectType type);
// [camera/onboard] on-board camera has crosshair to target (default is false) 
bool HasOnboardCameraCrosshair(ObjectType type);



//////////////////////////////////////////////////////////////////////////////
// Physics Details
//////////////////////////////////////////////////////////////////////////////

// [physics/collision] max radius of collision spheres to ignore (default is 0.0f)
float GetCollisionOtherObjectRadiusToIgnore(ObjectType type);
// [physics/collision] gets damage when collides with something (default is false)
bool IsCollisionDamagable(ObjectType type);
// [physics/collision] force of collision is devided by this (default is 200.0f)
float GetCollisionSoftness(ObjectType type);

// [physics/exhaust] bubbles around just after entering water (default is true)
bool IsExhaustBubblesOnEnteringWater(ObjectType type);
// [physics/exhaust] delay before underwater bubbles (default is 8.0f)
float IsExhaustBubblesOnEnteringWaterTime(ObjectType type);
// [physics/exhaust] drops on coming into water and coming out of water (default is true)
bool IsExhaustDropsOnLeavingWater(ObjectType type);
// [physics/exhaust] exhaust physics for dust: human type (default is false)
bool IsExhaustOnCrashAsHuman(ObjectType type);
// [physics/exhaust] exhaust physics for dust: tracked type (default is false)
bool IsExhaustOnCrashAsTrackedRobot(ObjectType type);
// [physics/exhaust] exhaust physics for dust: heavy type (default is false)
bool IsExhaustOnCrashAsHeavyRobot(ObjectType type);
// [physics/exhaust] motor exhaust physics for land movement: human type (default is false)
bool IsExhaustOnLandAsHuman(ObjectType type);
// [physics/exhaust] motor exhaust physics for land movement: winged type (default is false)
bool IsExhaustOnLandAsWingedRobot(ObjectType type);
// [physics/exhaust] motor exhaust physics for land movement: heavy type (default is false)
bool IsExhaustOnLandAsHeavyRobot(ObjectType type);
// [physics/exhaust] motor exhaust physics for land movement: other robots (default is false)
bool IsExhaustOnLandAsNormalRobot(ObjectType type);
// [physics/exhaust] motor exhaust physics for flight: human type (default is false)
bool IsExhaustOnFlightAsHuman(ObjectType type);
// [physics/exhaust] motor exhaust physics for flight: human type (default is false)
bool IsExhaustOnFlightAsWingedRobot(ObjectType type);
// [physics/exhaust] motor exhaust physics for swimming: human type (default is false)
bool IsExhaustOnSwimAsHuman(ObjectType type);
// [physics/exhaust] motor exhaust physics for swimming: subber type (default is false)
bool IsExhaustOnSwimAsAmphibiousRobot(ObjectType type);

// [physics/thumper] 
float GetThumperSafeRadius(ObjectType type);
// [physics/thumper] 
Gfx::PyroType GetThumperPyroType(ObjectType type);
// [physics/thumper] 
float GetThumperExplosionDamage(ObjectType type);
// [physics/thumper] 
bool GetThumperTurnOnBack(ObjectType type);

// [physics/water] maximum safe depth of water (default is 0.0f)
float GetMaxSafeWaterLevel(ObjectType type);
// [physics/water] minimum level of water for splash (default is 0.0f)
float GetWaterSplashLevelMin(ObjectType type);
// [physics/water] minimum level of water for splash (default is 9.0f)
float GetWaterSplashLevelMax(ObjectType type);
// [physics/water] radius of water splash (default is 5.0f)
float GetWaterSplashDiameter(ObjectType type);
// [physics/water] radius of water splash (default is 1.3f)
float GetWaterSplashForce(ObjectType type);

// [physics/lightning] height of lightning rod, if any (default is 0.0f)
//  0 for objects destroyable by lightning
// >0 for objects that have a lightning rod on some height
float GetLightningRodHeight(ObjectType type);



//////////////////////////////////////////////////////////////////////////////
// Automation Details
//////////////////////////////////////////////////////////////////////////////

// [auto] limits flat surface (default is false) 
bool IsBlockingBuilding(ObjectType type);
// [auto] can be attacked by tower ray (default is false)
bool IsAutoTargetedByTower(ObjectType type);
// [auto] can be attacked by mushroom (default is false)
bool IsAutoTargetedByMushroom(ObjectType type);
// [auto] detected by power station to operate (default is false)
bool IsAutoChargedAtPowerStation(ObjectType type);
// [auto] commented by Toto (default is false)
bool IsAutoCommentedByAssistant(ObjectType type);
// [auto] required to walk back from power plant to operate (default is false)
bool IsAutoBlockingPowerPlant(ObjectType type);
// [auto] required to walk back from nuclear plant to operate (default is false)
bool IsAutoBlockingNuclearPlant(ObjectType type);
// [auto] required to walk back from factory to operate (default is false)
bool IsAutoBlockingFactory(ObjectType type);

std::vector<CObjectProductionAutomationDetails> GetProduction(ObjectType type);



//////////////////////////////////////////////////////////////////////////////
// UI Icon Details
//////////////////////////////////////////////////////////////////////////////

// [ui/map] even non-selectable units should be displayed on map (default is false)
bool GetMapShowEvenUnselectable(ObjectType type);
// [ui/map] color of map icon (default is MAPCOLOR_NULL)
MapColor GetMapIconColor(ObjectType type);
// [ui/map] #id of map icon (default is -1)
// -1      for objects with empty icon
// 0-63    for textures on button1.png 
// 64-127  for textures on button2.png 
// 128-191 for textures on button3.png 
// 192-255 for textures on button4.png 
int GetMapIcon(ObjectType type);

// [ui/shortcut] a contollable building object with a shortcut (default is false)
bool IsShortcutBuilding(ObjectType type);
// [ui/shortcut] a contollable moving object with a shortcut (default is false)
bool IsShortcutMovable(ObjectType type);
// [ui/shortcut] #id of shortcut icon (default is -1)
// -1      for objects without icon
// 0-63    for textures on button1.png 
// 64-127  for textures on button2.png 
// 128-191 for textures on button3.png 
// 192-255 for textures on button4.png 
int GetShortcutIcon(ObjectType type);



//////////////////////////////////////////////////////////////////////////////
// User Interface Details
//////////////////////////////////////////////////////////////////////////////

// [ui/iface] has program selector interface (default is false)
bool HasUserInterfaceProgramUI(ObjectType type);
// [ui/iface] blinks the program selector interface on script execution (default is false)
bool HasUserInterfaceProgramUIBlink(ObjectType type);

// [ui/iface] raw widget list
std::vector<Ui::CWidget> GetUserInterfaceWidgetList(ObjectType type);

// [ui/iface] has human builder interface (default is false)
bool HasUserInterfaceBuilderUIHuman(ObjectType type);
// [ui/iface] has machine builder interface (default is false)
bool HasUserInterfaceBuilderUIRobot(ObjectType type);
// [ui/iface] has machine shielder interface (default is false)
bool HasUserInterfaceShielderUIRobot(ObjectType type);
// [ui/iface] has machine scribbler interface (default is false)
bool HasUserInterfaceScribblerUIRobot(ObjectType type);

// [ui/iface] fly buttons are disabled when something is grabbed (default is false)
bool HasUserInterfaceDisableFlyWhileGrabbing(ObjectType type);



//////////////////////////////////////////////////////////////////////////////
// Global details
//////////////////////////////////////////////////////////////////////////////

// [assistant] always moves after camera movement (returns OBJECT_NULL or registered object)
ObjectType GetPlayerType();
ObjectType GetBaseType();
ObjectType GetAssistantType();
ObjectType GetFunctionDestroyPerformerObject();
ObjectType GetFunctionFactoryPerformerObject();
ObjectType GetFunctionTakeOffPerformerObject();
ObjectType GetFunctionReceivePerformerObject();
std::vector<CObjectButton> GetBuilderMenuButtons();
std::vector<CObjectButton> GetDebugMenuButtons();
};
