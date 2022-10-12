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


#include "object/auto/autoboat.h"

#include "graphics/engine/particle.h"
#include "graphics/engine/water.h"

#include "object/old_object.h"

#include <stdio.h>


// Object's constructor.

CAutoBoat::CAutoBoat(COldObject* object) : CAuto(object)
{
    Init();
}

// Object's constructor.

CAutoBoat::~CAutoBoat()
{
}


// Initialize the object.

void CAutoBoat::Init()
{
    m_speed = 1.0f/1.0f;
    m_progress = 0.0f;
    m_lastParticle = 0.0f;

    Math::Vector pos = m_object->GetPosition();
    m_speed = 1.0f/(1.0f+(Math::Mod(pos.x/10.0f-0.5f, 1.0f)*0.2f))*2.5f;
    m_progress = Math::Mod(pos.x/10.0f, 1.0f);
}


// Management of an event.

bool CAutoBoat::EventProcess(const Event &event)
{
    CAuto::EventProcess(event);

    if ( m_engine->GetPause() )  return true;
    if ( event.type != EVENT_FRAME )  return true;

    m_progress += event.rTime*m_speed;

    Math::Vector vib;
    vib.x = 0.0f;
    vib.y = sinf(m_progress)*1.0f;
    vib.z = 0.0f;
    m_object->SetLinVibration(vib);

    vib.x = 0.0f;
    vib.y = 0.0f;
    vib.z = sinf(m_progress*0.5f)*0.15f;
    m_object->SetCirVibration(vib);

    if ( m_lastParticle+m_engine->ParticleAdapt(0.15f) <= m_time )
    {
        m_lastParticle = m_time;

        Math::Vector pos;
        pos = m_object->GetPosition();
        pos.y = m_water->GetLevel()+1.0f;
        pos.x += (Math::Rand()-0.5f)*20.0f;
        pos.z += (Math::Rand()-0.5f)*20.0f;
        Math::Vector speed;
        speed.y = 0.0f;
        speed.x = 0.0f;
        speed.z = 0.0f;
        Math::Point dim;
        dim.x = 20.0f;
        dim.y = dim.x;
        m_particle->CreateParticle(pos, speed, dim, Gfx::PARTIFLIC, 3.0f, 0.0f, 0.0f);
    }

    return true;
}
