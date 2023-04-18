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


#include "object/auto/autonest.h"

#include "graphics/engine/engine.h"
#include "graphics/engine/terrain.h"

#include "level/robotmain.h"

#include "level/parser/parserline.h"
#include "level/parser/parserparam.h"

#include "math/geometry.h"

#include "object/object.h"
#include "object/object_manager.h"

#include "object/details/details_provider.h"
#include "object/details/automated_details.h"

#include "object/helpers/cargo_helpers.h"

// Object's constructor.

CAutoNest::CAutoNest(CObject* object) : CAuto(object)
{
    Init();
}

// Object's destructor.

CAutoNest::~CAutoNest()
{
}


// Destroys the object.

void CAutoNest::DeleteObject(bool all)
{
    if ( !all )
    {
        CObject* cargo = SearchCargo();
        if ( cargo != nullptr )
        {
            CObjectManager::GetInstancePointer()->DeleteObject(cargo);
        }
    }

    CAuto::DeleteObject(all);
}


// Initialize the object.

void CAutoNest::Init()
{
    m_phase    = ANP_WAIT;
    m_progress = 0.0f;
    m_speed    = 1.0f/4.0f;

    m_time     = 0.0f;
    m_lastParticle = 0.0f;

    m_cargoPos = GetCargoPos();
}


// Management of an event.

bool CAutoNest::EventProcess(const Event &event)
{
    CAuto::EventProcess(event);

    if ( m_engine->GetPause() )  return true;
    if ( event.type != EVENT_FRAME )  return true;

    m_progress += event.rTime*m_speed;

    if ( m_phase == ANP_WAIT )
    {
        if ( m_progress >= 1.0f )
            FindSomethingToDig();
    }

    if ( m_phase == ANP_BIRTH )
    {
        CObject* cargo = SearchCargo();

        if ( m_progress < 1.0f )
        {
            if ( cargo != nullptr )
            {
                cargo->SetScale(m_progress);
            }
        }
        else
        {
            if ( cargo != nullptr )
            {
                cargo->SetScale(1.0f);
                cargo->SetLock(false);
            }
            m_main->DisplayText(m_onCompleted, m_object, Ui::TT_INFO);

            m_phase    = ANP_WAIT;
            m_progress = 0.0f;
            m_speed    = 1.0f/5.0f;
        }
    }

    return true;
}

void CAutoNest::FindSomethingToDig()
{
    auto digging = GetObjectAutomatedDetails(m_object).digging;

    Gfx::TerrainRes res = m_terrain->GetResource(m_object->GetPosition());

    std::vector<CObjectDiggingAutomated> matched;
    for ( auto it: digging.objects )
    {
        if (it.soil != Gfx::TR_ANY && it.soil != res)    continue;
        if (it.maxCount != -1)
        {
            size_t maxCount = static_cast<size_t>(it.maxCount);
            size_t count    = CObjectManager::GetInstancePointer()->RadarAll(nullptr, it.output).size();
            if ( count >= maxCount ) continue;
        }
        matched.push_back(it);
    }

    if ( matched.size() > 0 && SearchFree(GetCargoPos()) )
    {
        CObjectDiggingAutomated matchedFinal = matched[ std::rand() % matched.size() ];
        m_type        = matchedFinal.output;
        m_onCompleted = matchedFinal.message;
        m_cargoPos    = GetCargoPos();

        if (matchedFinal.output != OBJECT_NULL)
            CreateCargo(m_cargoPos, 0.0f);

        m_phase    = ANP_BIRTH;
        m_progress = 0.0f;
        m_speed    = 1.0f/matchedFinal.duration;
    }
    else
    {
        m_phase    = ANP_WAIT;
        m_progress = 0.0f;
        m_speed    = 1.0f/4.0f;
    }
}

glm::vec3 CAutoNest::GetCargoPos()
{
    auto digging = GetObjectAutomatedDetails(m_object).digging;
    glm::mat4 mat = m_object->GetWorldMatrix(digging.partNum);
    glm::vec3 pos = Math::Transform(mat, digging.position);
    m_terrain->AdjustToFloor(pos);
    return pos;
}

// Seeks if a site is free.

bool CAutoNest::SearchFree(glm::vec3 pos)
{
    if (IsObjectBeingTransported(m_object)) return false;    

    for (CObject* obj : CObjectManager::GetInstancePointer()->GetAllObjects())
    {
        ObjectType type = obj->GetType();
        if ( type == m_object->GetType() )  continue;

        for (const auto& crashSphere : obj->GetAllCrashSpheres())
        {
            glm::vec3 sPos = crashSphere.sphere.pos;
            float sRadius = crashSphere.sphere.radius;

            float distance = glm::distance(sPos, pos);
            distance -= sRadius;
            if ( distance < 2.0f )  return false;  // location occupied
        }
    }

    return true;  // free location
}

// Create a transportable object.

void CAutoNest::CreateCargo(glm::vec3 pos, float angle)
{
    if (m_type == OBJECT_NULL) return; 

    CObject* cargo = CObjectManager::GetInstancePointer()->CreateObject(pos, angle, m_type);
    cargo->SetLock(true);  // not usable
    cargo->SetScale(0.0f);
}

// Looking for the ball during manufacture.

CObject* CAutoNest::SearchCargo()
{
    for (CObject* obj : CObjectManager::GetInstancePointer()->GetAllObjects())
    {
        if ( !obj->GetLock() )  continue;

        for ( auto it: GetObjectAutomatedDetails(m_object).digging.objects )
        {
            if ( obj->GetType() != m_type ) continue;

            glm::vec3 oPos = obj->GetPosition();
            if ( oPos.x == m_cargoPos.x && oPos.z == m_cargoPos.z )
            {
                return obj;
            }
        }
    }

    return nullptr;
}

// Saves all parameters of the controller.

bool CAutoNest::Write(CLevelParserLine* line)
{
    if ( m_phase == ANP_WAIT )  return false;

    line->AddParam("aExist", std::make_unique<CLevelParserParam>(true));
    CAuto::Write(line);
    line->AddParam("aPhase", std::make_unique<CLevelParserParam>(static_cast<int>(m_phase)));
    line->AddParam("aProgress", std::make_unique<CLevelParserParam>(m_progress));
    line->AddParam("aSpeed", std::make_unique<CLevelParserParam>(m_speed));

    return true;
}

// Restores all parameters of the controller.

bool CAutoNest::Read(CLevelParserLine* line)
{
    if ( !line->GetParam("aExist")->AsBool(false) )  return false;

    CAuto::Read(line);
    m_phase = static_cast< AutoNestPhase >(line->GetParam("aPhase")->AsInt(ANP_WAIT));
    m_progress = line->GetParam("aProgress")->AsFloat(0.0f);
    m_speed = line->GetParam("aSpeed")->AsFloat(1.0f);

    m_lastParticle = 0.0f;

    return true;
}
