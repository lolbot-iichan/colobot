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
 * \file object/details/transportable_details.h
 * \brief CObjectTransportableDetails - set of tweaks for Transportable objects
 */

#pragma once

#include "object/object_details.h"

#include "object/details/details_provider.h"

CObjectAutomatedDetails GetObjectAutomatedDetails(CObject* obj)
{
    return CObjectDetails::GetInstance().GetObjectDetails(obj).automated;
}

CObjectAssistantDetails GetObjectAssistantDetails(CObject* obj)
{
    return CObjectDetails::GetInstance().GetObjectDetails(obj).assistant;
}

CObjectControllableDetails GetObjectControllableDetails(CObject* obj)
{
    return CObjectDetails::GetInstance().GetObjectDetails(obj).controllable;
}

CObjectDamageableDetails GetObjectDamageableDetails(CObject* obj)
{
    return CObjectDetails::GetInstance().GetObjectDetails(obj).damageable;
}

CObjectDestroyableDetails GetObjectDestroyableDetails(CObject* obj)
{
    return CObjectDetails::GetInstance().GetObjectDetails(obj).destroyable;
}

CObjectDetectableDetails GetObjectDetectableDetails(CObject* obj)
{
    return CObjectDetails::GetInstance().GetObjectDetails(obj).detectable;
}

CObjectExchangePostDetails GetObjectExchangePostDetails(CObject* obj)
{
    return CObjectDetails::GetInstance().GetObjectDetails(obj).exchange_post;
}

CObjectFlyingDetails GetObjectFlyingDetails(CObject* obj)
{
    return CObjectDetails::GetInstance().GetObjectDetails(obj).flying;
}

CObjectFragileDetails GetObjectFragileDetails(CObject* obj)
{
    return CObjectDetails::GetInstance().GetObjectDetails(obj).fragile;
}

CObjectGlobalDetails GetObjectGlobalDetails()
{
    return CObjectDetails::GetInstance().GetGlobalDetails();
}

CObjectJetFlyingDetails GetObjectJetFlyingDetails(CObject* obj)
{
    return CObjectDetails::GetInstance().GetObjectDetails(obj).jet_flying;
}

CObjectJostleableDetails GetObjectJostleableDetails(CObject* obj)
{
    return CObjectDetails::GetInstance().GetObjectDetails(obj).jostleable;
}

CObjectLevelDetails GetObjectLevelDetails(ObjectType type)
{
    return CObjectDetails::GetInstance().GetObjectDetails(type).level;
}

CObjectModeledDetails GetObjectModeledDetails(CObject* obj)
{
    return CObjectDetails::GetInstance().GetObjectDetails(obj).modeled;
}

CObjectMovableDetails GetObjectMovableDetails(CObject* obj)
{
    return CObjectDetails::GetInstance().GetObjectDetails(obj).movable;
}

CObjectNamingDetails GetObjectNamingDetails(ObjectType type)
{
    return CObjectDetails::GetInstance().GetObjectDetails(type).naming;
}

CObjectPhysicalDetails GetObjectPhysicalDetails(CObject* obj)
{
    return CObjectDetails::GetInstance().GetObjectDetails(obj).physical;
}

CObjectPowerContainerDetails GetObjectPowerContainerDetails(CObject* obj)
{
    return CObjectDetails::GetInstance().GetObjectDetails(obj).power_container;
}

CObjectRangedDetails GetObjectRangedDetails(CObject* obj)
{
    return CObjectDetails::GetInstance().GetObjectDetails(obj).ranged;
}

CObjectProgrammableDetails GetObjectProgrammableDetails(CObject* obj)
{
    return CObjectDetails::GetInstance().GetObjectDetails(obj).programmable;
}

CObjectScriptingDetails GetObjectScriptingDetails(ObjectType type)
{
    return CObjectDetails::GetInstance().GetObjectDetails(type).scripting;
}

CObjectShieldedDetails GetObjectShieldedDetails(CObject* obj)
{
    return CObjectDetails::GetInstance().GetObjectDetails(obj).shielded;
}

CObjectShieldedAutoRegenDetails GetObjectShieldedAutoRegenDetails(CObject* obj)
{
    return CObjectDetails::GetInstance().GetObjectDetails(obj).shielded_auto_regen;
}

CObjectShielderDetails GetObjectShielderDetails(CObject* obj)
{
    return CObjectDetails::GetInstance().GetObjectDetails(obj).shielder;
}

CObjectSlottedDetails GetObjectSlottedDetails(CObject* obj)
{
    return CObjectDetails::GetInstance().GetObjectDetails(obj).slotted;
}

CObjectTaskExecutorDetails GetObjectTaskExecutorDetails(CObject* obj)
{
    return CObjectDetails::GetInstance().GetObjectDetails(obj).task_executor;
}

CObjectThumpableDetails GetObjectThumpableDetails(CObject* obj)
{
    return CObjectDetails::GetInstance().GetObjectDetails(obj).thumpable;
}

CObjectTraceDrawingDetails GetObjectTraceDrawingDetails(CObject* obj)
{
    return CObjectDetails::GetInstance().GetObjectDetails(obj).trace_drawing;
}

CObjectTransportableDetails GetObjectTransportableDetails(CObject* obj)
{
    return CObjectDetails::GetInstance().GetObjectDetails(obj).transportable;
}
