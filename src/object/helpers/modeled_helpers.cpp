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

#include "object/object.h"

#include "object/helpers/modeled_helpers.h"

#include "object/interface/modeled_object.h"

glm::vec3 GetPartPosition(CObject* object, int part)
{
    if ( !object->Implements(ObjectInterfaceType::Modeled) ) return {0,0,0};

    CModeledObject* modeled = dynamic_cast<CModeledObject*>(object);
    return modeled->GetPartPosition(part);
}

void SetPartPosition(CObject* object, int part, const glm::vec3 &pos)
{
    if ( !object->Implements(ObjectInterfaceType::Modeled) ) return;

    CModeledObject* modeled = dynamic_cast<CModeledObject*>(object);
    return modeled->SetPartPosition(part, pos);
}

glm::vec3 GetPartRotation(CObject* object, int part)
{
    if ( !object->Implements(ObjectInterfaceType::Modeled) ) return {0,0,0};

    CModeledObject* modeled = dynamic_cast<CModeledObject*>(object);
    return modeled->GetPartRotation(part);
}

float GetPartRotationX(CObject* object, int part)
{
    if ( !object->Implements(ObjectInterfaceType::Modeled) ) return 0.0f;

    CModeledObject* modeled = dynamic_cast<CModeledObject*>(object);
    return modeled->GetPartRotationX(part);
}

float GetPartRotationY(CObject* object, int part)
{
    if ( !object->Implements(ObjectInterfaceType::Modeled) ) return 0.0f;

    CModeledObject* modeled = dynamic_cast<CModeledObject*>(object);
    return modeled->GetPartRotationY(part);
}

float GetPartRotationZ(CObject* object, int part)
{
    if ( !object->Implements(ObjectInterfaceType::Modeled) ) return 0.0f;

    CModeledObject* modeled = dynamic_cast<CModeledObject*>(object);
    return modeled->GetPartRotationZ(part);
}

void SetPartRotation(CObject* object, int part, const glm::vec3 &angle){    if ( !object->Implements(ObjectInterfaceType::Modeled) ) return;    CModeledObject* modeled = dynamic_cast<CModeledObject*>(object);    return modeled->SetPartRotation(part, angle);}
void SetPartRotationX(CObject* object, int part, float angle){    if ( !object->Implements(ObjectInterfaceType::Modeled) ) return;    CModeledObject* modeled = dynamic_cast<CModeledObject*>(object);    return modeled->SetPartRotationX(part, angle);}
void SetPartRotationY(CObject* object, int part, float angle){    if ( !object->Implements(ObjectInterfaceType::Modeled) ) return;    CModeledObject* modeled = dynamic_cast<CModeledObject*>(object);    return modeled->SetPartRotationY(part, angle);}
void SetPartRotationZ(CObject* object, int part, float angle){    if ( !object->Implements(ObjectInterfaceType::Modeled) ) return;    CModeledObject* modeled = dynamic_cast<CModeledObject*>(object);    return modeled->SetPartRotationZ(part, angle);}
glm::vec3 GetPartScale(CObject* object, int part)
{
    if ( !object->Implements(ObjectInterfaceType::Modeled) ) return {1.0f, 1.0f, 1.0f};

    CModeledObject* modeled = dynamic_cast<CModeledObject*>(object);
    return modeled->GetPartScale(part);
}

float GetPartScaleX(CObject* object, int part){    if ( !object->Implements(ObjectInterfaceType::Modeled) ) return 1.0f;    CModeledObject* modeled = dynamic_cast<CModeledObject*>(object);    return modeled->GetPartScaleX(part);}
float GetPartScaleY(CObject* object, int part){    if ( !object->Implements(ObjectInterfaceType::Modeled) ) return 1.0f;    CModeledObject* modeled = dynamic_cast<CModeledObject*>(object);    return modeled->GetPartScaleY(part);}
float GetPartScaleZ(CObject* object, int part){    if ( !object->Implements(ObjectInterfaceType::Modeled) ) return 1.0f;    CModeledObject* modeled = dynamic_cast<CModeledObject*>(object);    return modeled->GetPartScaleZ(part);}
void SetPartScale(CObject* object, int part, float zoom)
{
    if ( !object->Implements(ObjectInterfaceType::Modeled) ) return;

    CModeledObject* modeled = dynamic_cast<CModeledObject*>(object);
    return modeled->SetPartScale(part, zoom);
}

void SetPartScale(CObject* object, int part, glm::vec3 zoom)
{
    if ( !object->Implements(ObjectInterfaceType::Modeled) ) return;

    CModeledObject* modeled = dynamic_cast<CModeledObject*>(object);
    return modeled->SetPartScale(part, zoom);
}

void SetPartScaleX(CObject* object, int part, float zoom)
{
    if ( !object->Implements(ObjectInterfaceType::Modeled) ) return;

    CModeledObject* modeled = dynamic_cast<CModeledObject*>(object);
    return modeled->SetPartScaleX(part, zoom);
}

void SetPartScaleY(CObject* object, int part, float zoom)
{
    if ( !object->Implements(ObjectInterfaceType::Modeled) ) return;

    CModeledObject* modeled = dynamic_cast<CModeledObject*>(object);
    return modeled->SetPartScaleY(part, zoom);
}

void SetPartScaleZ(CObject* object, int part, float zoom)
{
    if ( !object->Implements(ObjectInterfaceType::Modeled) ) return;

    CModeledObject* modeled = dynamic_cast<CModeledObject*>(object);
    return modeled->SetPartScaleZ(part, zoom);
}
