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


#include "object/auto/autofan.h"

#include "object/old_object.h"

#include "sound/sound.h"

#include <stdio.h>


// Object's constructor.

CAutoFan::CAutoFan(COldObject* object) : CAuto(object)
{
    m_soundChannel = -1;
    Init();
}

// Object's constructor.

CAutoFan::~CAutoFan()
{
    if ( m_soundChannel != -1 )
    {
        m_sound->FlushEnvelope(m_soundChannel);
        m_sound->AddEnvelope(m_soundChannel, 0.0f, 1.0f, 1.0f, SOPER_STOP);
        m_soundChannel = -1;
    }
}


// Initialize the object.

void CAutoFan::Init()
{
    m_speed = 1.0f/1.0f;
    m_progress = 0.0f;

    if ( m_soundChannel == -1 )
    {
//?     m_soundChannel = m_sound->Play(SOUND_MANIP, m_object->GetPosition(0), 1.0f, 0.5f, true);
        m_silent = false;
    }
}


// Management of an event.

bool CAutoFan::EventProcess(const Event &event)
{
    CAuto::EventProcess(event);

    if ( m_soundChannel != -1 )
    {
        if ( m_engine->GetPause() )
        {
            if ( !m_silent )
            {
                m_sound->AddEnvelope(m_soundChannel, 0.0f, 0.5f, 0.1f, SOPER_CONTINUE);
                m_silent = true;
            }
        }
        else
        {
            if ( m_silent )
            {
                m_sound->AddEnvelope(m_soundChannel, 1.0f, 0.5f, 0.1f, SOPER_CONTINUE);
                m_silent = false;
            }
        }
    }

    if ( m_engine->GetPause() )  return true;
    if ( event.type != EVENT_FRAME )  return true;

    m_progress += event.rTime*m_speed;

    m_object->SetPartRotationY(1, sinf(m_progress*0.6f)*0.4f);
    m_object->SetPartRotationX(2, m_progress*5.0f);

    return true;
}
