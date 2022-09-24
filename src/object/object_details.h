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

#include "common/event.h"
#include "common/singleton.h"

#include "graphics/core/color.h"
#include "graphics/engine/engine_types.h"
#include "graphics/engine/pyro_type.h"

#include "level/build_type.h"
#include "level/research_type.h"

#include "math/point.h"
#include "math/vector.h"

#include "object/crash_sphere.h"
#include "object/object.h"
#include "object/object_type.h"




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

enum BaseClass
{
    BASE_CLASS_NONE,
    BASE_CLASS_SIMPLE,
    BASE_CLASS_BUILDING,
    BASE_CLASS_INFO,
    BASE_CLASS_ALIEN,
    BASE_CLASS_ROBOT,
    BASE_CLASS_SHIELDER,
};

struct CObjectCreationModelNode
{
    int                   chunkId   = -1;
    int                   parentId  = -1;
    Gfx::EngineObjectType gfxType   = Gfx::ENG_OBJTYPE_FIX;
    std::string           modFile   = "";
    Math::Vector          position  = Math::Vector();
    Math::Vector          rotation  = Math::Vector();
    bool                  copyModel = false;
};

struct CObjectCreationShadowCircle
{
    float                 radius    = 0.0;
    float                 intensity = 0.0;
    Gfx::EngineShadowType type      = Gfx::ENG_SHADOW_NORM;
    bool                  factored  = false;
};

struct CObjectCreationBuildingLevel
{
    float min    = 0.0;
    float max    = 0.0;
    float height = 0.0;
    float factor = 0.0;
};

struct CObjectButton
{
    ObjectType  type = OBJECT_NULL;
    int         icon = -1;
    std::string text = "";
};

enum ObjectUIWidgetType
{
    WIDGET_ICON_BUTTON  = 0,
    WIDGET_COLOR_BUTTON = 1,
};

union ObjectUIWidgetParams
{
    // for WIDGET_ICON_BUTTON
    int        icon;

    // for WIDGET_COLOR_BUTTON
    Gfx::Color color;
};

struct CObjectUserInterfaceWidget
{
    Math::Point               position               = Math::Point(7.7f, 0.5f);
    Math::Point               size                   = Math::Point(1.0f, 1.0f);
    ObjectUIWidgetType        type                   = WIDGET_ICON_BUTTON;
    ObjectUIWidgetParams      params                 = {-1};
    EventType                 event                  = EVENT_NULL;
    bool                      isDefault              = false;
    bool                      isImmediat             = false;

    bool                      disabledByTrainer      = false;
    bool                      disabledByPlusExplorer = false;
    std::vector<BuildType>    onBuildingsEnabled     = std::vector<BuildType>();
    std::vector<ResearchType> onResearchsDone        = std::vector<ResearchType>();
};



struct CObjectCameraDetails
{
// TODO:
//  * add bool to allow ONBOARD / TOP cameras

// true - could change camera type
// false - only CAM_TYPE_BACK is accessible
    bool isCameraTypeChangable         = false;

// true - remember previous selected camera type for an object
// false - reset camera to CAM_TYPE_BACK on each object selection
    bool isCameraTypePersistent        = false;

// optimal visit camera position
    float visitCameraDistance          = 60.0f;
    float visitCameraHeight            = 15.0f;

// optimal back camera position 
    float backCameraDistance           = 30.0f;
    float backCameraDistanceMin        = 10.0f;
    float backCameraHeight             = 4.0f;
    float backCameraRotationY          = 1.0f;
    float backCameraRotationZ          = 0.0f;

// tweaks for transparency on back camera
    bool disableOtherObjectsTransparencyOnBackCamera = false;
    bool disableObjectTransparencyOnBackCamera       = false;
    bool hasGateTransparencyOnBackCamera             = false;

// never collide with someone's fix camera 
    bool disableCollisionsOnFixCamera  = false;

// remove on-board camera robotic corners 
    bool disableCornersOnOnboardCamera = false;

};



struct CObjectIconDetails
{
// TODO:
//  * change MapColor to extensible bg & micro-icon selection

// object map options
    MapColor mapIconColor              = MAPCOLOR_NULL;
    int mapIcon                        = -1;

// tweak: showed on map controllable, but non-selectable objects with this property
    bool isForcedDisplayOnMap          = false;

// object shortcut options
    bool isShortcutBuilding            = false;
    bool isShortcutMovable             = false;
    int shortcutIcon                   = -1;
};


struct CObjectUserInterfaceDetails
{
// TODO:
//  * add list of actual widgets instead of list of hardcoded UIs

// has program selector interface
    bool hasProgramUI              = false;
// blinks the program selector interface on script execution
    bool hasProgramUIBlink         = false;

// raw widgets list
    std::vector<CObjectUserInterfaceWidget> widgets;

// has very specific interface widgets
    bool hasBuilderUIHuman         = false;
    bool hasBuilderUIRobot         = false;
    bool hasShielderUIRobot        = false;
    bool hasShooterUIRobot         = false;
    bool hasScribblerUIRobot       = false;

// tweak: flight control buttons can be disabled when something is grabbed
    bool disableFlyWhileGrabbing   = false;
};



class CObjectDetails : public CSingleton<CObjectDetails>
{

struct CObjectDetail
{
    std::string                 displayedName;
    CObjectCameraDetails        cameraDetails;
    CObjectIconDetails          iconDetails;
    CObjectUserInterfaceDetails uiDetails;
};


std::map<std::string, ObjectType> m_nameInLevelFilesToObjectType;
std::map<ObjectType, std::vector<ObjectType> > m_aliasToSearchList;

CObjectButton m_builderMenuObjects[14];
CObjectButton m_debugMenuObjects[14];

std::map<ObjectType, CObjectDetail> m_objects;

public:
CObjectDetails();

void Dump();




// [lists] debug menu item (nullptr on error)
CObjectButton GetBuilderMenuItem(int index);

// [lists] debug menu item (nullptr on error)
CObjectButton GetDebugMenuItem(int index);




// [level] object name in level files (default is OBJECT_NULL)
ObjectType ParseNameOrAliasInLevelFiles(std::string name);

// [script] objects that could be find with radar functions by alias (default is vector with given id)
std::vector<ObjectType> GetObjectsFindableByType(ObjectType type);



// [assistant] always moves after camera movement (returns OBJECT_NULL or registered object)
ObjectType GetAssistantType();

// [assistant] react on SatCom pages, etc (default is false)
bool IsAssistantReactingOnDisplayedInfo();

// [assistant] react on errors, warnings, etc (default is false)
bool IsAssistantReactingOnDisplayedText();

// [assistant] always moves after camera movement (default is false)
bool IsAssistantMovesWithCamera();

// [assistant] open SATCOM_HUSTON on click (default is false)
bool IsAssistantIgnoredOnSaveLoad();

// [assistant] open SATCOM_HUSTON on click (default is false)
bool IsAssistantClickable();

// [assistant] ignores collisions, rays, bullets, water, etc (default is false)
bool IsAssistantUndamagable();



// [terrain] limits flat surface (default is false) 
bool IsBlockingBuilding(ObjectType type);




// [immunity] true, if immune to fireballs of Shooters (default is false)
bool IsImmuneToFireballs(ObjectType type);

// [immunity] true, if immune to particle of Ants (default is false)
bool IsImmuneToInsects(ObjectType type);

// [immunity] true, if immune to fireballs (default is false)
bool IsImmuneToSpiders(ObjectType type);

// [immunity] true, if immune to fireballs (default is false)
bool IsImmuneToOrgaballs(ObjectType type);

// [immunity] true, if immune to fireballs (default is false)
bool IsImmuneToPhazers(ObjectType type);

// [immunity] true, if immune to tower rays (default is true)
bool IsImmuneToTowerRays(ObjectType type);




// [auto] can be attacked by tower ray (default is false)
bool IsAutoTargetedByTower(ObjectType type);

// [auto] detected by power station to operate (default is false)
bool IsAutoChargedAtPowerStation(ObjectType type);

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




// [script/autoparams] object that is automaticaly used in function call (returns OBJECT_NULL or registered object)
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
// [script/params]  (default is false)
bool IsRadarExplicitOnly(ObjectType type);



// [script/allowed] functions are binded to C++ implementations (default is false)
bool IsFunctionImplementedBuild(ObjectType type);
bool IsFunctionImplementedFlags(ObjectType type);
bool IsFunctionImplementedShield(ObjectType type);
bool IsFunctionImplementedDrawAsRobot(ObjectType type);
bool IsFunctionImplementedGrabAsHuman(ObjectType type);
bool IsFunctionImplementedGrabAsRobot(ObjectType type);
bool IsFunctionImplementedShootAsAnt(ObjectType type);
bool IsFunctionImplementedShootAsSpider(ObjectType type);
bool IsFunctionImplementedShootAsRobot(ObjectType type);



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
Gfx::PyroType GetThumperPyroType(ObjectType type);
float GetThumperExplosionDamage(ObjectType type);
bool GetThumperTurnOnBack(ObjectType type);


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





// [ui/name] show player name instead of object name (default is false)
bool IsDisplayedNameAsPlayer(ObjectType type);

// [ui/name] localizable string used with gettext (default is "")
std::string GetDisplayedName(ObjectType type);




// [create/model]
BaseClass GetCreationBaseClass(ObjectType type);
std::vector<CObjectCreationModelNode> GetCreationModel(ObjectType type);
std::vector<CrashSphere> GetCreationCrashSpheres(ObjectType type);
std::vector<Math::Sphere> GetCreationCameraCollisionSpheres(ObjectType type);
std::vector<Math::Sphere> GetCreationJostlingSpheres(ObjectType type);
std::vector<CObjectCreationBuildingLevel> GetCreationBuildingLevels(ObjectType type);
CObjectCreationShadowCircle GetCreationShadowCircle(ObjectType type);
float GetCreationScale(ObjectType type);
bool IsCreationForceLoadTextures(ObjectType type);
bool IsCreationSetFloorHeight(ObjectType type);
bool IsCreationFloorAdjust(ObjectType type);
bool IsCreationFixedPosition(ObjectType type);
bool IsDestructionRemoveBuildingLevel(ObjectType type);
Gfx::PyroType GetDestructionByExplosion(ObjectType type);
Gfx::PyroType GetDestructionByWater(ObjectType type);
Gfx::PyroType GetDestructionByBurning(ObjectType type);
Gfx::PyroType GetDestructionByDrowned(ObjectType type);
Gfx::PyroType GetDestructionByWin(ObjectType type);
Gfx::PyroType GetDestructionBySquash(ObjectType type);
bool IsDestructionKilledByBurning(ObjectType type);

public:

CObjectCameraDetails        GetObjectCameraDetails(ObjectType type);
CObjectIconDetails          GetObjectIconDetails(ObjectType type);
CObjectUserInterfaceDetails GetObjectUserInterfaceDetails(ObjectType type);

private:

CObjectCameraDetails        GetObjectCameraDetailsHardcode(ObjectType type);
CObjectIconDetails          GetObjectIconDetailsHardcode(ObjectType type);
CObjectUserInterfaceDetails GetObjectUserInterfaceDetailsHardcode(ObjectType type);
};



//! Global function to get object details instance
inline CObjectDetails & GetObjectDetails()
{
    return CObjectDetails::GetInstance();
}

//! Global function to get object camera details for object
inline CObjectCameraDetails GetObjectCameraDetails(CObject* obj)
{
    ObjectType type = (obj != nullptr) ? obj->GetType() : OBJECT_NULL;
    return CObjectDetails::GetInstance().GetObjectCameraDetails(type);
}

//! Global function to get object camera details for object
inline CObjectIconDetails GetObjectIconDetails(CObject* obj)
{
    ObjectType type = (obj != nullptr) ? obj->GetType() : OBJECT_NULL;
    return CObjectDetails::GetInstance().GetObjectIconDetails(type);
}

//! Global function to get object UI details for object
inline CObjectUserInterfaceDetails GetObjectUserInterfaceDetails(CObject* obj)
{
    ObjectType type = (obj != nullptr) ? obj->GetType() : OBJECT_NULL;
    return CObjectDetails::GetInstance().GetObjectUserInterfaceDetails(type);
} 