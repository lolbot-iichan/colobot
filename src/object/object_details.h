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
#include "level/parser/parser.h"

#include "math/point.h"
#include "math/vector.h"

#include "object/crash_sphere.h"
#include "object/object.h"
#include "object/object_type.h"

#include "physics/physics.h"

struct CObjectButton
{
    ObjectType  type = OBJECT_NULL;
    int         icon = -1;
    std::string text = "";
};



//////////////////////////////////////////////////////////////////////////////
// Object naming details
//////////////////////////////////////////////////////////////////////////////

struct CObjectLevelNamingDetails
{
// name & alias in level files
    std::string name          = "";
    std::string alias         = "";
};

struct CObjectScriptNamingDetails
{
// name & alias in script files
    std::string name          = "";
    std::string alias         = "";

// help topic name, e.g. "object/base"
    std::string helpTopicPath = "";
};

struct CObjectDisplayedNamingDetails
{
// localizable TR-string
    std::string name          = "";
    bool        usePlayerName = false;
};

struct CObjectNamingDetails
{
    CObjectLevelNamingDetails     level;
    CObjectScriptNamingDetails    script;
    CObjectDisplayedNamingDetails display;
};



//////////////////////////////////////////////////////////////////////////////
// Object scripting details
//////////////////////////////////////////////////////////////////////////////

struct CObjectAllowedScriptingDetails
{
// TODO: move grab & shoot settings into other structs 

// if false, WRONG_BOT error is generated
    bool build                    = false;
    bool flag                     = false;
    bool sniff                    = false;
    bool shield                   = false;
    bool recycle                  = false;
    bool penAsRobot               = false;
    bool grabAsHuman              = false;
    bool grabAsRobot              = false;
    bool shootAsAnt               = false;
    bool shootAsSpider            = false;
    bool shootAsRobot             = false;
};

struct CObjectRadarScriptingDetails
{
    bool       isExplicit         = false;
    std::vector<ObjectType> findableWithThisType = std::vector<ObjectType>();
};

struct CObjectProduceScriptingDetails
{
    bool       isProducable      = false;
    bool       isProducedCharged = false;
    bool       isProducedManual  = false;

    ObjectType container         = OBJECT_NULL;
};

struct CObjectScriptingDetails
{
    CObjectAllowedScriptingDetails allowed;
    
    CObjectRadarScriptingDetails   radar;
    CObjectProduceScriptingDetails produce;
};



//////////////////////////////////////////////////////////////////////////////
// Creation details
//////////////////////////////////////////////////////////////////////////////

enum BaseClass
{
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

struct CObjectCreationBuildingLevel
{
    float min    = 0.0;
    float max    = 0.0;
    float height = 0.0;
    float factor = 0.0;
};

struct CObjectCreationShadowCircle
{
    float                 radius    = 0.0;
    float                 intensity = 0.0;
    Gfx::EngineShadowType type      = Gfx::ENG_SHADOW_NORM;
    bool                  factored  = false;
};

struct CObjectCreationDetails
{
// base C++ class for object is switched by this
    BaseClass             baseClass = BASE_CLASS_SIMPLE;

// parts of object model
    std::vector<CObjectCreationModelNode>     model;
    std::vector<CrashSphere>                  crashSpheres;
    std::vector<Math::Sphere>                 cameraCollisionSpheres;
    std::vector<Math::Sphere>                 jostlingSpheres;
    std::vector<CObjectCreationBuildingLevel> buildingLevels;
    CObjectCreationShadowCircle               shadowCircle;

// additional object scale
    float scale                    = 1.0f;

// tweak: should textures be forced to load
    bool isForceLoadTextures       = false;

// tweaks: setting floor level and adjusting is optional
    bool isSetFloorHeight          = false;
    bool isFloorAdjust             = false;
    bool isFixedPosition           = false;
};



//////////////////////////////////////////////////////////////////////////////
// Common interface details
//////////////////////////////////////////////////////////////////////////////

struct CObjectTransportableDetails
{
    bool  enabled             = false;
};

struct CObjectMovableDetails
{
    bool      enabled         = false;
    Motion    linMotion;
    Motion    cirMotion;
    Character wheels;
};

struct CObjectFlyingDetails
{
    bool  enabled             = false;
};

struct CObjectJetFlyingDetails
{
    bool  enabled             = false;
};

struct CObjectControllableDetails
{
    bool  enabled             = false;
    bool  selectable          = true;
};

struct CObjectPowerContainerDetails
{
    bool  enabled             = false;
};

struct CObjectRangedDetails
{
    bool  enabled             = true;
    float radius              = 0.0f;
};

struct CObjectTraceDrawingDetails
{
    bool enabled              = true;
    bool penAnimated          = false;
};

struct CObjectDamageableDetails
{
    bool enabled              = false;

// immunity to some kinds of damage
    bool isImmuneToFireballs  = false;
    bool isImmuneToInsects    = false;
    bool isImmuneToSpiders    = false;
    bool isImmuneToOrgaballs  = false;
    bool isImmuneToPhazers    = false;
    bool isImmuneToTowerRay   = true;  // TODO invert
};

struct CObjectExplosionDestroyableDetails
{
    Gfx::PyroType effect      = Gfx::PT_EXPLOT;
};

struct CObjectWaterDestroyableDetails
{
    bool explodeInWater       = false;
    Gfx::PyroType effect      = Gfx::PT_FRAGW;
};

struct CObjectBurningDestroyableDetails
{
    Gfx::PyroType effect      = Gfx::PT_BURNT;
    bool isKilledByBurning    = true;  // TODO invert
};

struct CObjectDrownedDestroyableDetails
{
    Gfx::PyroType effect      = Gfx::PT_DEADW;
};

struct CObjectWinDestroyableDetails
{
    Gfx::PyroType effect      = Gfx::PT_WPCHECK;
};

struct CObjectSquashDestroyableDetails
{
    bool squashedByHeavy      = false;
    Gfx::PyroType effect      = Gfx::PT_SQUASH;
};

struct CObjectDestroyableDetails
{
    bool enabled              = false;
    bool removeBuildingLevel  = false;

    CObjectExplosionDestroyableDetails explosion;
    CObjectWaterDestroyableDetails     water;
    CObjectBurningDestroyableDetails   burning;
    CObjectDrownedDestroyableDetails   drowned;
    CObjectWinDestroyableDetails       win;
    CObjectSquashDestroyableDetails    squash;
};

struct CObjectFragileDetails
{
    bool enabled              = false;
};

struct CObjectShieldedDetails
{
    bool enabled              = false;
};

struct CObjectShieldedAutoRegenDetails
{
    bool enabled              = false;
    float time                = 0.0f;
};

struct CObjectCargoSlotedDetails
{
    bool         enabled      = false;
    Math::Vector position;
};

struct CObjectPowerSlotedDetails
{
    bool         enabled      = false;
    Math::Vector position;
};

struct CObjectOtherSlotedDetails
{
    bool         enabled      = false;
    Math::Vector position;
};

struct CObjectSlotedDetails
{
    bool enabled              = false;

    CObjectCargoSlotedDetails cargo;
    CObjectPowerSlotedDetails power;
    CObjectOtherSlotedDetails other;
};

struct CObjectCommonInterfaceDetails
{
    CObjectTransportableDetails     transportable;
    CObjectMovableDetails           movable;
    CObjectFlyingDetails            flying;
    CObjectJetFlyingDetails         jet;
    CObjectControllableDetails      controllable;
    CObjectPowerContainerDetails    power;
    CObjectRangedDetails            ranged;
    CObjectTraceDrawingDetails      drawing;
    CObjectDamageableDetails        damageable;
    CObjectDestroyableDetails       destroyable;
    CObjectFragileDetails           fragile;
    CObjectShieldedDetails          shielded;
    CObjectShieldedAutoRegenDetails autoregen;
    CObjectSlotedDetails            sloted;
};



//////////////////////////////////////////////////////////////////////////////
// Camera details
//////////////////////////////////////////////////////////////////////////////

struct CObjectBackCameraDetails
{
// optimal back camera position 
    float distance    = 30.0f;
    float distanceMin = 10.0f;
    float height      = 4.0f;
    float rotationY   = 1.0f;
    float rotationZ   = 0.0f;

// tweaks for transparency on back camera
    bool disableOtherObjectsTransparency = false;
    bool disableObjectTransparency       = false;
    bool hasGateTransparency             = false;
};

struct CObjectFixCameraDetails
{
// never collide with someone's fix camera 
    bool disableCollisions = false;
};

struct CObjectOnboardCameraDetails
{
// remove on-board camera robotic corners 
    bool disableCorners = false;

// has shooting crosshair 
    bool hasCrosshair   = false;
};

struct CObjectVisitCameraDetails
{
// optimal visit camera position
    float distance = 60.0f;
    float height   = 15.0f;
};

struct CObjectCameraDetails
{
// TODO:
//  * add bools to allow camera types

// true - could change camera type
// false - only CAM_TYPE_BACK is accessible
    bool isCameraTypeChangable    = false;

// true - remember previous selected camera type for an object
// false - reset camera to CAM_TYPE_BACK on each object selection
    bool isCameraTypePersistent   = false;

    Gfx::CameraType defaultCamera = Gfx::CAM_TYPE_BACK;

    CObjectBackCameraDetails    backCamera;
    CObjectFixCameraDetails     fixCamera;
    CObjectOnboardCameraDetails onboardCamera;
    CObjectVisitCameraDetails   visitCamera;
};



//////////////////////////////////////////////////////////////////////////////
// Physics details
//////////////////////////////////////////////////////////////////////////////

struct CObjectExhaustPhysicsDetails
{
    bool bubblesOnEnteringWater      = true;
    float bubblesOnEnteringWaterTime = 8.0f;

    bool dropsOnLeavingWater     = false;
    bool onCrashAsHuman          = false;
    bool onCrashAsTrackedRobot   = false;
    bool onCrashAsHeavyRobot     = false;
    bool onLandAsHuman           = false;
    bool onLandAsWingedRobot     = false;
    bool onLandAsHeavyRobot      = false;
    bool onLandAsNormalRobot     = false;
    bool onFlightAsHuman         = false;
    bool onFlightAsWingedRobot   = false;
    bool onSwimAsHuman           = false;
    bool onSwimAsAmphibiousRobot = false;
};

struct CObjectThumperPhysicsDetails
{
    float         safeRadius      = -1.0f;
    Gfx::PyroType effect          = Gfx::PT_NULL;
    float         explosionDamage = 0.0f;
    bool          turnOnBack      = false;
};

struct CObjectLightningPhysicsDetails
{
    float lightningRodHeight = 0.0f;
};

struct CObjectWaterPhysicsDetails
{
    float waterLevel         = 0.0f;
    float splashLevelMin     = 0.0f;
    float splashLevelMax     = 9.0f;
    float splashDiameter     = 5.0f;
    float splashForce        = 1.3f;
};

struct CObjectPhysicsDetails
{
    CObjectExhaustPhysicsDetails   exhaust;
    CObjectThumperPhysicsDetails   thumper;
    CObjectLightningPhysicsDetails lightning;
    CObjectWaterPhysicsDetails     water;


    float collisionOtherObjectRadiusToIgnore = 0.0f;
    bool  isCollisionDamagable               = false;
    float collisionSoftness                  = 200.0f;
};



//////////////////////////////////////////////////////////////////////////////
// Automation Details
//////////////////////////////////////////////////////////////////////////////

struct CObjectBlockingAutomationDetails
{
    bool blocksBuilding        = false;
    bool blocksPowerPlant      = false;
    bool blocksNuclearPlant    = false;
    bool blocksFactory         = false;
};

struct CObjectTargetedAutomationDetails
{
    bool attackedByTower       = false;
    bool attackedByMushroom    = false;
    bool chargedByPowerStation = false;
    bool commentedByAssistant  = false;
};

struct CObjectProductionAutomationDetails
{
    ObjectType input           = OBJECT_NULL;
    ObjectType output          = OBJECT_NULL;
};

struct CObjectAutomationDetails
{
    CObjectBlockingAutomationDetails   blocking;
    CObjectTargetedAutomationDetails   targeted;
    CObjectProductionAutomationDetails production;
};



//////////////////////////////////////////////////////////////////////////////
// UI Icon Details
//////////////////////////////////////////////////////////////////////////////

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

struct CObjectMapIconDetails
{
// TODO:
//  * change MapColor to extensible bg & micro-icon selection

// object map options
    MapColor color = MAPCOLOR_NULL;
    int      icon  = -1;

// tweak: showed on map controllable, but non-selectable objects with this property
    bool isForced  = false;
};

struct CObjectShortcutIconDetails
{
// object shortcut options
    bool isBuilding = false;
    bool isMovable  = false;
    int  icon       = -1;
};

struct CObjectIconDetails
{
    CObjectMapIconDetails      map;
    CObjectShortcutIconDetails shortcut;
};



//////////////////////////////////////////////////////////////////////////////
// User Interface Details
//////////////////////////////////////////////////////////////////////////////

enum ObjectUIWidgetType
{
    WIDGET_ICON_BUTTON  = 0,
    WIDGET_COLOR_BUTTON = 1,
    WIDGET_ICON_LOGO    = 2,
};

union ObjectUIWidgetParams
{
    // for WIDGET_ICON_BUTTON
    // for WIDGET_ICON_LOGO
    int        icon;

    // for WIDGET_COLOR_BUTTON
    Gfx::Color color;
};

struct CObjectControlsWidget
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

struct CObjectControlsDetails
{
// TODO:
//  * add list of actual widgets for: builders, shielder, scribbler

// has program selector interface
    bool hasProgramUI              = false;
// blinks the program selector interface on script execution
    bool hasProgramUIBlink         = false;

// raw widgets list
    std::vector<CObjectControlsWidget> widgets;

// has very specific interface widgets
    bool hasBuilderUIHuman         = false;
    bool hasBuilderUIRobot         = false;
    bool hasShielderUIRobot        = false;
    bool hasScribblerUIRobot       = false;

// tweak: flight control buttons can be disabled when something is grabbed
    bool disableFlyWhileGrabbing   = false;
};



//////////////////////////////////////////////////////////////////////////////
// Assistant global details
//////////////////////////////////////////////////////////////////////////////

struct CObjectAssistantDetails
{
    ObjectType type       = OBJECT_NULL;
    bool reactOnSatcom    = false;
    bool reactOnMessages  = false;
    bool moveWithCamera   = false;
    bool ignoreOnSaveLoad = false;
    bool clickable        = false;
    bool undamageable     = false;
    bool unpausable       = false;
};



//////////////////////////////////////////////////////////////////////////////
// Provider Class
//////////////////////////////////////////////////////////////////////////////

class CObjectDetails : public CSingleton<CObjectDetails>
{

struct CObjectDetail
{
    CObjectNamingDetails          naming;
    CObjectScriptingDetails       scripting;
    CObjectCreationDetails        creation;
    CObjectCommonInterfaceDetails common;
    CObjectCameraDetails          camera;
    CObjectPhysicsDetails         physics;
    CObjectAutomationDetails      automation;
    CObjectIconDetails            icons;
    CObjectControlsDetails        controls;
};
std::map<ObjectType, CObjectDetail> m_objects;
std::map<std::string, ObjectType> m_nameToType;

CObjectAssistantDetails m_assistant;

public:
CObjectDetails();

void Clear();
void LoadHardcode();
void Load(const char* fname);
void Dump(const char* fname);
ObjectType ParseObjectTypeFromName(std::string name);




public:


inline CObjectDetail GetObjectDetails(ObjectType type)
{
    auto it = m_objects.find(type);
    return it != m_objects.end() ? it->second : CObjectDetail();
}

inline CObjectDetail GetObjectDetails(CObject* obj)
{
    ObjectType type = (obj != nullptr) ? obj->GetType() : OBJECT_NULL;
    return GetObjectDetails(type);
}

inline CObjectAssistantDetails GetObjectAssistantDetails()
{
    return m_assistant;
};

private:

void DumpObjectNamingDetails(CLevelParser* dumper, ObjectType type);
void DumpObjectScriptingDetails(CLevelParser* dumper, ObjectType type);
void DumpObjectCreationDetails(CLevelParser* dumper, ObjectType type);
void DumpObjectCommonInterfaceDetails(CLevelParser* dumper, ObjectType type);
void DumpObjectCameraDetails(CLevelParser* dumper, ObjectType type);
void DumpObjectPhysicsDetails(CLevelParser* dumper, ObjectType type);
void DumpObjectAutomationDetails(CLevelParser* dumper, ObjectType type);
void DumpObjectIconDetails(CLevelParser* dumper, ObjectType type);
void DumpObjectControlsDetails(CLevelParser* dumper, ObjectType type);
void DumpObjectAssistantDetails(CLevelParser* dumper);

CObjectNamingDetails          GetObjectNamingDetailsHardcode(ObjectType type);
CObjectScriptingDetails       GetObjectScriptingDetailsHardcode(ObjectType type);
CObjectCreationDetails        GetObjectCreationDetailsHardcode(ObjectType type);
CObjectCommonInterfaceDetails GetObjectCommonInterfaceDetailsHardcode(ObjectType type);
CObjectCameraDetails          GetObjectCameraDetailsHardcode(ObjectType type);
CObjectPhysicsDetails         GetObjectPhysicsDetailsHardcode(ObjectType type);
CObjectAutomationDetails      GetObjectAutomationDetailsHardcode(ObjectType type);
CObjectIconDetails            GetObjectIconDetailsHardcode(ObjectType type);
CObjectControlsDetails        GetObjectControlsDetailsHardcode(ObjectType type);
CObjectAssistantDetails       GetObjectAssistantDetailsHardcode();

//////////////////////////////////////////////////////////////////////////////
// Unsorted
//////////////////////////////////////////////////////////////////////////////
private:
CObjectButton m_builderMenuObjects[14];
CObjectButton m_debugMenuObjects[14];
public:
CObjectButton GetBuilderMenuItem(int index);
CObjectButton GetDebugMenuItem(int index);
// [script/autoparams] object that is automaticaly used in function call (returns OBJECT_NULL or registered object)
ObjectType GetFunctionDestroyPerformerObject();
ObjectType GetFunctionFactoryPerformerObject();
ObjectType GetFunctionResearchPerformerObject(ResearchType type);
ObjectType GetFunctionTakeOffPerformerObject();
ObjectType GetFunctionReceivePerformerObject();
};



//! Global function to get object details instance
inline CObjectDetails & GetObjectDetails()
{
    return CObjectDetails::GetInstance();
}


//! Global function to parse object name into type

inline ObjectType ParseObjectTypeFromName(std::string name)
{
    return CObjectDetails::GetInstance().ParseObjectTypeFromName(name);
}



//! Global functions to get details for an object type

inline CObjectNamingDetails GetObjectNamingDetails(ObjectType type)
{
    return CObjectDetails::GetInstance().GetObjectDetails(type).naming;
}

inline CObjectCommonInterfaceDetails GetObjectCommonInterfaceDetails(ObjectType type)
{
    return CObjectDetails::GetInstance().GetObjectDetails(type).common;
}

inline CObjectScriptingDetails GetObjectScriptingDetails(ObjectType type)
{
    return CObjectDetails::GetInstance().GetObjectDetails(type).scripting;
}

inline CObjectCreationDetails GetObjectCreationDetails(ObjectType type)
{
    return CObjectDetails::GetInstance().GetObjectDetails(type).creation;
}

inline CObjectPhysicsDetails GetObjectPhysicsDetails(ObjectType type)
{
    return CObjectDetails::GetInstance().GetObjectDetails(type).physics;
}



//! Global functions to get details for an object

inline CObjectScriptingDetails GetObjectScriptingDetails(CObject* obj)
{
    return CObjectDetails::GetInstance().GetObjectDetails(obj).scripting;
}

inline CObjectCommonInterfaceDetails GetObjectCommonInterfaceDetails(CObject* obj)
{
    return CObjectDetails::GetInstance().GetObjectDetails(obj).common;
}

inline CObjectCameraDetails GetObjectCameraDetails(CObject* obj)
{
    return CObjectDetails::GetInstance().GetObjectDetails(obj).camera;
}

inline CObjectPhysicsDetails GetObjectPhysicsDetails(CObject* obj)
{
    return CObjectDetails::GetInstance().GetObjectDetails(obj).physics;
}

inline CObjectAutomationDetails GetObjectAutomationDetails(CObject* obj)
{
    return CObjectDetails::GetInstance().GetObjectDetails(obj).automation;
}

inline CObjectIconDetails GetObjectIconDetails(CObject* obj)
{
    return CObjectDetails::GetInstance().GetObjectDetails(obj).icons;
}

inline CObjectControlsDetails GetObjectControlsDetails(CObject* obj)
{
    return CObjectDetails::GetInstance().GetObjectDetails(obj).controls;
}



//! Global functions to get global details

inline CObjectAssistantDetails GetObjectAssistantDetails()
{
    return CObjectDetails::GetInstance().GetObjectAssistantDetails();
}
