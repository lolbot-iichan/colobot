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
 * \file object/object_properties.h
 * \brief CObjectDetails - set of methods with various info about all the objects in one place
 */

#pragma once

#include <map>
#include <string>
#include <vector>

#include "common/singleton.h"

#include "object/object_type.h"

#include "level/research_type.h"

enum MapColor
{
    MAPCOLOR_NULL,
    MAPCOLOR_BASE,
    MAPCOLOR_FIX,
    MAPCOLOR_MOVE,
    MAPCOLOR_ALIEN,
    MAPCOLOR_WAYPOINTb,
    MAPCOLOR_WAYPOINTr,
    MAPCOLOR_WAYPOINTg,
    MAPCOLOR_WAYPOINTy,
    MAPCOLOR_WAYPOINTv,
    MAPCOLOR_BBOX,
};

struct CObjectButton
{
    ObjectType  type = OBJECT_NULL;
    int         icon = -1;
    std::string text = "";
};

class CObjectDetails : public CSingleton<CObjectDetails>
{

struct CObjectDetail
{
    std::string displayedName;
};


std::map<std::string, ObjectType> m_nameToObjectType;
std::map<ObjectType, std::vector<ObjectType> > m_aliasToSearchList;

CObjectButton m_builderMenuObjects[14];
CObjectButton m_debugMenuObjects[14];

std::map<ObjectType, CObjectDetail> m_objects;

public:
    CObjectDetails();



// [lists] debug menu item (nullptr on error)
CObjectButton GetBuilderMenuItem(int index);

// [lists] debug menu item (nullptr on error)
CObjectButton GetDebugMenuItem(int index);




// [level] object name in level files (default is OBJECT_NULL)
ObjectType ParseNameOrAliasInLevelFiles(std::string name);

// [script] objects that could be find with radar functions by alias (default is vector with given id)
std::vector<ObjectType> GetObjectsFindableByType(ObjectType type);



// [terrain] limits flat surface (default is false) 
bool IsBlockingBuilding(ObjectType type);




// [camera/types] could change camera type (default is false) 
bool IsCameraTypeChangable(ObjectType type);

// [camera/types] remember camera mode or  (default is false)
// true - remember object camera type while switching between objects
// false - reset camera to CAM_TYPE_BACK on each selection
bool IsCameraTypePersistent(ObjectType type);



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

// [camera/back] can make other objects transparent when they overlap the back camera (default is true) 
bool GetBackCameraCanForceTransparency(ObjectType type);

// [camera/back] can be transparent when overlaps someone's back camera (default is true) 
bool GetBackCameraCanViewAsTransparent(ObjectType type);




// [camera/fix] can collide with someone's fix camera (default is true) 
bool GetFixCameraCanCollide(ObjectType type);




// [camera/onboard] on-board camera has robotic corners (default is true) 
bool GetOnboardCameraCorners(ObjectType type);




// [camera/visit] radius of ideal visit (default is 60.0f)
float GetVisitCameraDistance(ObjectType type);

// [camera/visit] height of ideal visit (default is 15.0f)
float GetVisitCameraHeight(ObjectType type);




// [immunity] true, if immune to fireballs of Shooters (default is false)
bool GetImmuneToFireballs(ObjectType type);

// [immunity] true, if immune to particle of Ants (default is false)
bool GetImmuneToInsects(ObjectType type);

// [immunity] true, if immune to fireballs (default is false)
bool GetImmuneToSpiders(ObjectType type);

// [immunity] true, if immune to fireballs (default is false)
bool GetImmuneToOrgaballs(ObjectType type);

// [immunity] true, if immune to fireballs (default is false)
bool GetImmuneToPhazers(ObjectType type);

// [immunity] true, if immune to tower rays (default is true)
bool GetImmuneToTowerRays(ObjectType type);




// [auto] can be attacked by tower ray (default is false)
bool IsAutoTargetedByTower(ObjectType type);

// [auto] required to walk back from power station to operate (default is false)
bool IsAutoBlockingPowerStation(ObjectType type);

// [auto] required to walk back from power plant to operate (default is false)
bool IsAutoBlockingPowerPlant(ObjectType type);

// [auto] required to walk back from nuclear plant to operate (default is false)
bool IsAutoBlockingNuclearPlant(ObjectType type);

// [auto] required to walk back from factory to operate (default is false)
bool IsAutoBlockingFactory(ObjectType type);



// [level/code] object name in level files (default is "")
std::string GetNameInLevelFiles(ObjectType type);

// [level/code] object asias in level files (default is "")
std::string GetAliasInLevelFiles(ObjectType type);



// [script/code] object name in script files (default is "")
std::string GetNameInScriptFiles(ObjectType type);

// [script/code] object asias in script files (default is "")
std::string GetAliasInScriptFiles(ObjectType type);

// [script/code] help topic name, e.g. "object/base" (default is "")
std::string GetHelpTopicPathName(ObjectType type);



// [script/autoparams] object that is automaticaly used in function call
ObjectType GetFunctionDestroyPerformerObject();
ObjectType GetFunctionFactoryPerformerObject();
ObjectType GetFunctionResearchPerformerObject(ResearchType type);
ObjectType GetFunctionTakeOffPerformerObject();
ObjectType GetFunctionReceivePerformerObject();

// [script/params] can object be used at produce() call (default is false)
bool IsValidObjectTypeId(ObjectType type);
// [script/params] object that should also be created at produce() call (default is OBJECT_NULL)
ObjectType GetProduceContainer(ObjectType type);
// [script/params] should be charged at produce() with -1 power (default is false)
bool IsProduceAlreadyCharged(ObjectType type);
// [script/params] force manual mode for produced item (default is false)
bool IsProduceManual(ObjectType type);


// [script/allowed] drawer functions are binded to C++ implementations (default is false)
bool IsFunctionImplementedBuild(ObjectType type);
bool IsFunctionImplementedFlags(ObjectType type);
bool IsFunctionImplementedShield(ObjectType type);
bool IsFunctionImplementedDrawAsRobot(ObjectType type);
bool IsFunctionImplementedGrabAsHuman(ObjectType type);
bool IsFunctionImplementedGrabAsRobot(ObjectType type);
bool IsFunctionImplementedShootAsAnt(ObjectType type);
bool IsFunctionImplementedShootAsSpider(ObjectType type);
bool IsFunctionImplementedShootAsRobot(ObjectType type);



// [physics/assistant] can be ignored by any kinds of rays, bullets (default is false)
bool IsNotPhysicalObject(ObjectType type);




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




// [physics/water] explodes when going underwater (default is false)
bool IsExplodesInWater(ObjectType type);

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




// [ui/iface] has program selector interface (default is false)
bool GetInterfaceProgram(ObjectType type);

// [ui/iface] blinks the program selector interface on script execution (default is false)
bool GetInterfaceProgramBlink(ObjectType type);

// [ui/iface] has human grabber interface (default is false)
bool GetInterfaceGrabberHuman(ObjectType type);

// [ui/iface] has human flag planting interface (default is false)
bool GetInterfaceFlaggerHuman(ObjectType type);

// [ui/iface] has human builder interface (default is false)
bool GetInterfaceBuilderHuman(ObjectType type);

// [ui/iface] has machine multi-mode grabber interface (default is false)
bool GetInterfaceGrabberRobotArm(ObjectType type);

// [ui/iface] has machine simple grabber interface (default is false)
bool GetInterfaceGrabberRobotSimple(ObjectType type);

// [ui/iface] has machine builder interface (default is false)
bool GetInterfaceBuilderRobot(ObjectType type);

// [ui/iface] has machine sniffer interface (default is false)
bool GetInterfaceSnifferRobot(ObjectType type);

// [ui/iface] has machine flag planting interface (default is false)
bool GetInterfaceFlaggerRobot(ObjectType type);

// [ui/iface] has machine thumper interface (default is false)
bool GetInterfaceThumperRobot(ObjectType type);

// [ui/iface] has machine recycler interface (default is false)
bool GetInterfaceRecyclerRobot(ObjectType type);

// [ui/iface] has machine shielder interface (default is false)
bool GetInterfaceShielderRobot(ObjectType type);

// [ui/iface] has machine shooter interface (default is false)
bool GetInterfaceShooterRobot(ObjectType type);

// [ui/iface] has machine scribbler interface (default is false)
bool GetInterfaceScribblerRobot(ObjectType type);

// [ui/iface] has alien expoder interface (default is false)
bool GetInterfaceExploderAlien(ObjectType type);

// [ui/iface] fly buttons are disabled when something is grabbed (default is false)
bool IsInterfaceDisableFlyWhileGrabbing(ObjectType type);




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




// [ui/name] show player name instead of object name (default is false)
bool IsDisplayedNameAsPlayer(ObjectType type);

// [ui/name] localizable string used with gettext (default is "")
std::string GetDisplayedName(ObjectType type);
};



//! Global function to get object details instance
inline CObjectDetails & GetObjectDetails()
{
    return CObjectDetails::GetInstance();
} 