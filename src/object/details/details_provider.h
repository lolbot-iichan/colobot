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

class CObject;
class CObjectAssistantDetails;
class CObjectAutomatedDetails;
class CObjectControllableDetails;
class CObjectDamageableDetails;
class CObjectDestroyableDetails;
class CObjectDetectableDetails;
class CObjectExchangePostDetails;
class CObjectFlyingDetails;
class CObjectFragileDetails;
class CObjectGlobalDetails;
class CObjectJetFlyingDetails;
class CObjectJostleableDetails;
class CObjectLevelDetails;
class CObjectMovableDetails;
class CObjectModeledDetails;
class CObjectNamingDetails;
class CObjectPhysicalDetails;
class CObjectPowerContainerDetails;
class CObjectProgrammableDetails;
class CObjectRangedDetails;
class CObjectScriptingDetails;
class CObjectShieldedAutoRegenDetails;
class CObjectShieldedDetails;
class CObjectShielderDetails;
class CObjectSlottedDetails;
class CObjectTaskExecutorDetails;
class CObjectThumpableDetails;
class CObjectTraceDrawingDetails;
class CObjectTransportableDetails;

enum ObjectType : unsigned int;

CObjectAssistantDetails GetObjectAssistantDetails(CObject* obj);
CObjectAutomatedDetails GetObjectAutomatedDetails(CObject* obj);
CObjectControllableDetails GetObjectControllableDetails(CObject* obj);
CObjectDamageableDetails GetObjectDamageableDetails(CObject* obj);
CObjectDestroyableDetails GetObjectDestroyableDetails(CObject* obj);
CObjectDetectableDetails GetObjectDetectableDetails(CObject* obj);
CObjectExchangePostDetails GetObjectExchangePostDetails(CObject* obj);
CObjectFlyingDetails GetObjectFlyingDetails(CObject* obj);
CObjectFragileDetails GetObjectFragileDetails(CObject* obj);
CObjectGlobalDetails GetObjectGlobalDetails();
CObjectJetFlyingDetails GetObjectJetFlyingDetails(CObject* obj);
CObjectJostleableDetails GetObjectJostleableDetails(CObject* obj);
CObjectLevelDetails GetObjectLevelDetails(ObjectType type);
CObjectModeledDetails GetObjectModeledDetails(CObject* obj);
CObjectMovableDetails GetObjectMovableDetails(CObject* obj);
CObjectNamingDetails GetObjectNamingDetails(ObjectType type);
CObjectPhysicalDetails GetObjectPhysicalDetails(CObject* obj);
CObjectPowerContainerDetails GetObjectPowerContainerDetails(CObject* obj);
CObjectProgrammableDetails GetObjectProgrammableDetails(CObject* obj);
CObjectRangedDetails GetObjectRangedDetails(CObject* obj);
CObjectScriptingDetails GetObjectScriptingDetails(ObjectType type);
CObjectShieldedAutoRegenDetails GetObjectShieldedAutoRegenDetails(CObject* obj);
CObjectShieldedDetails GetObjectShieldedDetails(CObject* obj);
CObjectShielderDetails GetObjectShielderDetails(CObject* obj);
CObjectSlottedDetails GetObjectSlottedDetails(CObject* obj);
CObjectTaskExecutorDetails GetObjectTaskExecutorDetails(CObject* obj);
CObjectThumpableDetails GetObjectThumpableDetails(CObject* obj);
CObjectTraceDrawingDetails GetObjectTraceDrawingDetails(CObject* obj);
CObjectTransportableDetails GetObjectTransportableDetails(CObject* obj);
