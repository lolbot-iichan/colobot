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

#include "object/auto/autoquarz.h"

#include "graphics/engine/particle.h"

#include "math/geometry.h"

#include "object/object.h"

#include "object/details/details_provider.h"
#include "object/details/automated_details.h"

// Object's constructor.

CAutoQuarz::CAutoQuarz(CObject* object) : CAuto(object)
{
    for (int i = 0; i < QUARZMAXLENS; i++)
    {
        m_lens[i] = -1;
    }

    Init();
}

// Object's destructor.

CAutoQuarz::~CAutoQuarz()
{
}


// Initialize the object.

void CAutoQuarz::Init()
{
    auto quarz = GetObjectAutomatedDetails(m_object).quarz;

    int n = quarz.numLights > QUARZMAXLENS ? QUARZMAXLENS : quarz.numLights;

    glm::mat4 mat = m_object->GetWorldMatrix(quarz.partNum);
    glm::vec3 pos = Math::Transform(mat, quarz.position); 

    for (int i = 0; i < n; i++ )
    {
        m_lens[i] = m_particle->CreateParticle(pos, pos, glm::vec2(2.0f, 2.0f), Gfx::PARTIQUARTZ, 0.7f+Math::Rand()*0.7f, quarz.radius, 0.0f);
    }
}
