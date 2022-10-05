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

#include "level/build_type.h"
#include "level/research_type.h"
#include "level/parser/parser.h"

#include "math/point.h"
#include "math/vector.h"

#include "object/crash_sphere.h"
#include "object/object.h"
#include "object/object_type.h"

#include "object/details/assistant_details.h"
#include "object/details/automation_details.h"
#include "object/details/controllable_details.h"
#include "object/details/creation_details.h"
#include "object/details/damageable_details.h"
#include "object/details/detectable_details.h"
#include "object/details/destroyable_details.h"
#include "object/details/flying_details.h"
#include "object/details/fragile_details.h"
#include "object/details/global_details.h"
#include "object/details/jet_flying_details.h"
#include "object/details/josteable_details.h"
#include "object/details/movable_details.h"
#include "object/details/naming_details.h"
#include "object/details/power_container_details.h"
#include "object/details/programmable_details.h"
#include "object/details/scripting_details.h"
#include "object/details/shielded_details.h"
#include "object/details/shielded_auto_regen_details.h"
#include "object/details/slotted_details.h"
#include "object/details/ranged_details.h"
#include "object/details/task_executor_details.h"
#include "object/details/thumpable_details.h"
#include "object/details/trace_drawing_details.h"
#include "object/details/transportable_details.h"

//////////////////////////////////////////////////////////////////////////////
// Physics details
//////////////////////////////////////////////////////////////////////////////

struct CObjectThumperPhysicsDetails
{
    float         safeRadius      = -1.0f;
    Gfx::PyroType effect          = Gfx::PT_NULL;
    float         explosionDamage = 0.0f;
};

struct CObjectLightningPhysicsDetails
{
    float lightningRodHeight = 0.0f;
};

struct CObjectPhysicsDetails
{
    CObjectThumperPhysicsDetails   thumper;
    CObjectLightningPhysicsDetails lightning;


    float collisionOtherObjectRadiusToIgnore = 0.0f;
    bool  isCollisionDamagable               = false;
    float collisionSoftness                  = 200.0f;
};


//////////////////////////////////////////////////////////////////////////////
// Provider Class
//////////////////////////////////////////////////////////////////////////////

class CObjectDetails : public CSingleton<CObjectDetails>
{

struct CObjectDetail
{
    CObjectNamingDetails          naming;

    CObjectAssistantDetails       assistant;
    CObjectAutomationDetails      automation;
    CObjectCreationDetails        creation;
    CObjectDetectableDetails      detectable;
    CObjectScriptingDetails       scripting;

    CObjectTransportableDetails     transportable;
    CObjectProgrammableDetails      programmable;
    CObjectTaskExecutorDetails      task_executor;
    CObjectJosteableDetails         josteable;
    CObjectMovableDetails           movable;
    CObjectFlyingDetails            flying;
    CObjectJetFlyingDetails         jet_flying;
    CObjectControllableDetails      controllable;
    CObjectPowerContainerDetails    power_container;
    CObjectRangedDetails            ranged;
    CObjectTraceDrawingDetails      trace_drawing;
    CObjectDamageableDetails        damageable;
    CObjectDestroyableDetails       destroyable;
    CObjectFragileDetails           fragile;
    CObjectShieldedDetails          shielded;
    CObjectShieldedAutoRegenDetails shielded_auto_regen;
    CObjectSlottedDetails           slotted;
    CObjectThumpableDetails         thumpable;

    CObjectPhysicsDetails         physics;
};
std::map<ObjectType, CObjectDetail> m_objects;
CObjectGlobalDetails                m_globals;
std::map<std::string, ObjectType>   m_nameToType;

public:
CObjectDetails();

void Clear();
void LoadHardcode();
void Load(const char* fname);
void Dump(const char* fname);

ObjectType CastToObjectType(std::string name);




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

inline CObjectGlobalDetails GetGlobalDetails()
{
    return m_globals;
}

private:
CObjectPhysicsDetails         GetObjectPhysicsDetailsHardcode(ObjectType type);

//////////////////////////////////////////////////////////////////////////////
// Unsorted
//////////////////////////////////////////////////////////////////////////////
public:
ObjectType GetFunctionResearchPerformerObject(ResearchType type);
};



//! Global function to get object details instance
inline CObjectDetails & GetObjectDetails()
{
    return CObjectDetails::GetInstance();
}


//! Global function to parse object name into type

inline ObjectType CastToObjectType(std::string name)
{
    return CObjectDetails::GetInstance().CastToObjectType(name);
}

inline CObjectPhysicsDetails GetObjectPhysicsDetails(ObjectType type)
{
    return CObjectDetails::GetInstance().GetObjectDetails(type).physics;
}


inline CObjectPhysicsDetails GetObjectPhysicsDetails(CObject* obj)
{
    return CObjectDetails::GetInstance().GetObjectDetails(obj).physics;
}
