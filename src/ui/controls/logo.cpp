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


#include "ui/controls/logo.h"

#include "common/event.h"
#include "common/restext.h"

#include "graphics/engine/engine.h"


#include <stdio.h>
#include <string.h>


namespace Ui
{
// Object's constructor.

CLogo::CLogo() : CControl()
{
}

// Object's destructor.

CLogo::~CLogo()
{
}


// Creates a new button.

bool CLogo::Create(Math::Point pos, Math::Point dim, int icon, EventType eventType)
{
    if ( eventType == EVENT_NULL )  eventType = GetUniqueEventType();

    CControl::Create(pos, dim, icon, eventType);

    if ( icon == -1 )
    {
        std::string name = GetResourceName(eventType);
        SetName(name);
    }

    return true;
}


// Management of an event.

bool CLogo::EventProcess(const Event &event)
{
    return true;
}


// Draw button.

void CLogo::Draw()
{
    Math::Point     uv1,uv2, corner, pos, dim;
    float       dp;
    int         icon;

    if ( (m_state & STATE_VISIBLE) == 0 )  return;

    if ( m_state & STATE_SHADOW )
    {
        DrawShadow(m_pos, m_dim);
    }

    dp = 0.5f / 256.0f;

    pos = m_pos;
    dim = m_dim;

    m_engine->SetTexture("textures/interface/button2.png");
    m_engine->SetState(Gfx::ENG_RSTATE_NORMAL);
    uv1.x = 32.0f / 256.0f;
    uv1.y = 32.0f / 256.0f;
    uv2.x = uv1.x+32.0f/256.0f;
    uv2.y = uv1.y+32.0f/256.0f;
    uv1.x += dp;
    uv1.y += dp;
    uv2.x -= dp;
    uv2.y -= dp;
    DrawIcon(pos, dim, uv1, uv2);

    m_engine->SetTexture("textures/interface/button3.png");
    m_engine->SetState(Gfx::ENG_RSTATE_NORMAL);
    pos.x +=  8.0f / 640.0f;
    pos.y +=  8.0f / 480.0f;
    dim.x -= 16.0f / 640.0f;
    dim.y -= 16.0f / 480.0f;
    uv1.x = 32.0f / 256.0f;
    uv1.y =  0.0f / 256.0f;
    uv2.x = uv1.x+32.0f/256.0f;
    uv2.y = uv1.y+32.0f/256.0f;
    uv1.x += dp;
    uv1.y += dp;
    uv2.x -= dp;
    uv2.y -= dp;
    DrawIcon(pos, dim, uv1, uv2);

    m_engine->SetState(Gfx::ENG_RSTATE_NORMAL);
    pos.x += 2.0f / 640.0f;
    pos.y += 2.0f / 480.0f;
    dim.x -= 4.0f / 640.0f;
    dim.y -= 4.0f / 480.0f;
    uv1.x = 0.0f / 256.0f;
    uv1.y = 0.0f / 256.0f;
    uv2.x = uv1.x+32.0f/256.0f;
    uv2.y = uv1.y+32.0f/256.0f;
    uv1.x += dp;
    uv1.y += dp;
    uv2.x -= dp;
    uv2.y -= dp;
    DrawIcon(pos, dim, uv1, uv2);

    switch ( m_icon << 6 )
    {
        case 0:
            m_engine->SetTexture("textures/interface/button1.png"); break;
        case 1:
            m_engine->SetTexture("textures/interface/button2.png"); break;
        case 3:
            m_engine->SetTexture("textures/interface/button4.png"); break;
        default: ; // button3.png
    }
    icon = m_icon % 64;

    m_engine->SetState(Gfx::ENG_RSTATE_TTEXTURE_BLACK);
    pos.x +=  8.0f / 640.0f;
    pos.y +=  8.0f / 480.0f;
    dim.x -= 16.0f / 640.0f;
    dim.y -= 16.0f / 480.0f;
    uv1.x = (32.0f/256.0f)*(icon%8);
    uv1.y = (32.0f/256.0f)*(icon/8);  // uv texture
    uv2.x = uv1.x+32.0f/256.0f;
    uv2.y = uv1.y+32.0f/256.0f;
    uv1.x += dp;
    uv1.y += dp;
    uv2.x -= dp;
    uv2.y -= dp;
    DrawIcon(pos, dim, uv1, uv2);
}


}

