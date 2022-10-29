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


#include "object/auto/autoorgacannon.h"

#include "graphics/engine/camera.h"
#include "graphics/engine/engine.h"

#include "math/const.h"

#include "object/object.h"

#include "object/helpers/common_helpers.h"
#include "object/helpers/modeled_helpers.h"
#include "object/helpers/power_helpers.h"

#include "sound/sound.h"

#include <stdio.h>


// Object's constructor.

CAutoOrgaCannon::CAutoOrgaCannon(CObject* object) : CAuto(object)
{
    Init();
}

// Object's constructor.

CAutoOrgaCannon::~CAutoOrgaCannon()
{
}


// Initialize the object.

void CAutoOrgaCannon::Init()
{
    m_speed = 1.0f/1.0f;
    m_progress = 0.0f;

}


// Management of an event.

bool CAutoOrgaCannon::EventProcess(const Event &event)
{
    CAuto::EventProcess(event);

    if ( m_engine->GetPause() )  return true;
    if ( event.type != EVENT_FRAME )  return true;

    m_progress += event.rTime*m_speed;

    float       zoom, angle, factor;
    bool        bOnBoard = false;

    if ( IsObjectSelected(m_object) && m_camera->GetType() == Gfx::CAM_TYPE_ONBOARD )
    {
        bOnBoard = true;
    }

    float energy = GetObjectEnergyLevel(m_object);
    if (energy == 0.0f)  return true;
    if (energy > 1.0f) energy = 1.0f; //fix issue with cheated cells, see issue #1009

    factor = 0.5f+energy*0.5f;
    if ( bOnBoard )  factor *= 0.8f;

    zoom = 1.3f+
           sinf(m_progress*Math::PI*0.31f)*0.10f+
           sinf(m_progress*Math::PI*0.52f)*0.08f+
           sinf(m_progress*Math::PI*1.53f)*0.05f;
    zoom *= factor;
    SetPartScaleY(m_object, 2, zoom);

    zoom = 1.0f+
           sinf(m_progress*Math::PI*0.27f)*0.07f+
           sinf(m_progress*Math::PI*0.62f)*0.06f+
           sinf(m_progress*Math::PI*1.73f)*0.03f;
    zoom *= factor;
    SetPartScaleZ(m_object, 2, zoom);

    angle = sinf(m_progress*1.0f)*0.10f+
            sinf(m_progress*1.3f)*0.15f+
            sinf(m_progress*2.7f)*0.05f;
    SetPartRotationX(m_object, 2, angle);

    return true;
    return true;
}
