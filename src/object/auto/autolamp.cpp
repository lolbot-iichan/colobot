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

#include "object/auto/autolamp.h"

#include "graphics/engine/particle.h"

#include "level/robotmain.h"

#include "math/geometry.h"

#include "object/object.h"

#include "object/details/details_provider.h"
#include "object/details/automated_details.h"

// Object's constructor.

CAutoLamp::CAutoLamp(CObject* object) : CAuto(object)
{
    m_lens = -1;
    m_spot = -1;

    Init();
}

// Object's destructor.

CAutoLamp::~CAutoLamp()
{
}


// Initialize the object.

void CAutoLamp::Init()
{
    auto lamp = GetObjectAutomatedDetails(m_object).lamp;

    {
        glm::mat4 mat = m_object->GetWorldMatrix(lamp.particle.partNum);
        glm::vec3 pos = Math::Transform(mat, lamp.particle.position);
        glm::vec2 dim = {lamp.particle.size, lamp.particle.size};
        m_lens = m_particle->CreateParticle(pos, glm::vec3(0.0f, 0.0f, 0.0f), dim, Gfx::PARTISELY, 1.0f, 0.0f, 0.0f);
    }

    {
        glm::mat4 mat = m_object->GetWorldMatrix(lamp.spot.partNum);
        glm::vec3 pos = Math::Transform(mat, lamp.spot.position);
        Gfx::Color color = lamp.spot.color;
        m_spot = m_main->CreateSpot(pos, color);
    }
}
