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

#include "math/geometry.h"

#include "object/object_manager.h"
#include "object/old_object.h"

#include "object/auto/autoworm.h"

#include "object/details/controllable_details.h"

#include <stdio.h>


// Object's constructor.

CAutoWorm::CAutoWorm(COldObject* object) : CAuto(object)
{
    Init();
}


// Object's constructor.

CAutoWorm::~CAutoWorm()
{
}


// Initialize the object.

void CAutoWorm::Init()
{
    m_wormLastTime = 0.0f;
}


// Management of an event.

bool CAutoWorm::EventProcess(const Event &event)
{
    CAuto::EventProcess(event);

    if ( m_engine->GetPause() )  return true;
    if ( event.type != EVENT_FRAME )  return true;

    WormFrame(event.rTime);

    return true;
}


// Sought a target for the worm.

CObject* CAutoWorm::WormSearch(Math::Vector &impact)
{
    Math::Vector iPos = m_object->GetPosition();
    float min = 1000000.0f;

    CObject* best = nullptr;
    for (CObject* obj : CObjectManager::GetInstancePointer()->GetAllObjects())
    {
        auto controllable = GetObjectControllableDetails(obj);
        if (!controllable.infectable) continue;
        if ( obj->GetVirusMode() )  continue;

        //TODO: Why not just use GetPosition() since we use DistanceProjected anyway?

        if (obj->GetCrashSphereCount() == 0) continue;
        Math::Vector oPos = obj->GetFirstCrashSphere().sphere.pos;
        float distance = Math::DistanceProjected(oPos, iPos);
        if (distance < min)
        {
            min = distance;
            best = obj;
        }
    }
    if ( best == nullptr )  return nullptr;

    impact = best->GetPosition();
    return best;
}


// Contaminate objects near the worm.

void CAutoWorm::WormFrame(float rTime)
{
    Math::Vector impact;

    m_wormLastTime += rTime;
    if ( m_wormLastTime >= 0.5f )
    {
        m_wormLastTime = 0.0f;

        CObject* pObj = WormSearch(impact);
        if ( pObj == nullptr ) return;

        if ( Math::Distance(m_object->GetPosition(), impact) <= 15.0f )
        {
            pObj->SetVirusMode(true);  // bam, infected!
        }
    }
}
