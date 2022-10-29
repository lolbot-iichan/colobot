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

#include "object/auto/autoinfo.h"

#include "common/regex_utils.h"

#include "graphics/engine/engine.h"
#include "graphics/engine/particle.h"
#include "graphics/engine/oldmodelmanager.h"

#include "level/parser/parserexceptions.h"
#include "level/parser/parserline.h"
#include "level/parser/parserparam.h"

#include "math/func.h"

#include "object/object.h"

#include "object/helpers/modeled_helpers.h"

#include "object/interface/exchange_post_object.h"

#include "sound/sound.h"

#include "ui/controls/interface.h"
#include "ui/controls/list.h"
#include "ui/controls/window.h"

#include <boost/lexical_cast.hpp>

enum class CAutoInfo::Phase : unsigned int
{
    Wait      = 1,
    Send      = 2,
    Receive   = 3,
    Error     = 4,
};

// Object's constructor.

CAutoInfo::CAutoInfo(CObject* object)
    : CAuto(object),
      m_phase(Phase::Wait),
      m_progress(0.0f),
      m_speed(0.0f),
      m_timeVirus(0.0f),
      m_lastParticle(0.0f),
      m_lastVirus(false)
{
    Init();
}

CAutoInfo::~CAutoInfo()
{
}

void CAutoInfo::DeleteObject(bool all)
{
    CAuto::DeleteObject(all);
}


void CAutoInfo::Init()
{
    m_phase = Phase::Wait;
    m_time = 0.0f;
    m_timeVirus = 0.0f;
    m_lastVirus = false;

    CAuto::Init();
}

void CAutoInfo::Start(int param)
{
    if (param == 0)  // instruction "receive" ?
    {
        m_phase = Phase::Send;
        m_progress = 0.0f;
        m_speed = 1.0f/2.0f;
    }
    else if (param == 2)  // instruction "send" ?
    {
        m_phase = Phase::Receive;
        m_progress = 0.0f;
        m_speed = 1.0f/2.0f;
    }
    else
    {
        m_phase = Phase::Error;
        m_progress = 0.0f;
        m_speed = 1.0f/2.0f;
    }

    m_lastParticle = 0;
    m_goal = m_object->GetPosition();

    glm::vec3    pos, speed;
    glm::vec2       dim;

    if (m_phase == Phase::Send)
    {
        pos = m_goal;
        pos.y += 9.5f;
        speed = glm::vec3(0.0f, 0.0f, 0.0f);
        dim.x = 30.0f;
        dim.y = dim.x;
        m_particle->CreateParticle(pos, speed, dim, Gfx::PARTISPHERE4, 1.5f, 0.0f, 0.0f);

        m_sound->Play(SOUND_LABO, pos, 1.0f, 2.0f);
    }
    if (m_phase == Phase::Receive)
    {
        pos = m_goal;
        pos.y += 9.5f;
        speed = glm::vec3(0.0f, 0.0f, 0.0f);
        dim.x = 50.0f;
        dim.y = dim.x;
        m_particle->CreateParticle(pos, speed, dim, Gfx::PARTISPHERE6, 1.5f, 0.0f, 0.0f);

        m_sound->Play(SOUND_LABO, pos, 1.0f, 2.0f);
    }
    if (m_phase == Phase::Error)
    {
        m_sound->Play(SOUND_GGG, pos, 1.0f, 0.5f);
    }
}

bool CAutoInfo::EventProcess(const Event &event)
{
    CAuto::EventProcess(event);

    if (m_engine->GetPause())  return true;
    if (event.type != EVENT_FRAME)  return true;

    m_timeVirus -= event.rTime;

    if (m_object->GetVirusMode())  // contaminated by a virus?
    {
        if (m_timeVirus <= 0.0f)
        {
            m_timeVirus = 0.1f+Math::Rand()*0.3f;

            float angle = GetPartRotationY(m_object, 1);
            angle += Math::Rand()*0.3f;
            SetPartRotationY(m_object, 1, angle);

            SetPartRotationX(m_object, 2, (Math::Rand()-0.5f)*0.3f);
            SetPartRotationX(m_object, 4, (Math::Rand()-0.5f)*0.3f);
            SetPartRotationX(m_object, 6, (Math::Rand()-0.5f)*0.3f);

            SetPartRotationZ(m_object, 2, (Math::Rand()-0.5f)*0.3f);
            SetPartRotationZ(m_object, 4, (Math::Rand()-0.5f)*0.3f);
            SetPartRotationZ(m_object, 6, (Math::Rand()-0.5f)*0.3f);

            UpdateListVirus();
        }
        m_lastVirus = true;
        return true;
    }
    else
    {
        if (m_lastVirus)
        {
            m_lastVirus = false;
            UpdateList();  // normally returns the list
        }
        else if (m_object->Implements(ObjectInterfaceType::ExchangePost))
        {
            if (dynamic_cast<CExchangePostObject*>(m_object)->GetInfoUpdate())
            {
                UpdateList();  // updates the list
            }
        }
    }

    UpdateInterface(event.rTime);

    float rTime = event.rTime;

    if (m_phase == Phase::Send)  // instruction "receive" ?
    {
        if (m_progress < 0.5f &&
            m_lastParticle+m_engine->ParticleAdapt(0.05f) <= m_time)
        {
            m_lastParticle = m_time;

            for (int i = 0; i < 4; i++)
            {
                glm::vec3 pos = m_goal;
                pos.y += 9.5f;
                glm::vec3 speed;
                speed.x = (Math::Rand()-0.5f)*50.0f;
                speed.z = (Math::Rand()-0.5f)*50.0f;
                speed.y = (Math::Rand()-0.5f)*50.0f;
                speed *= 0.5f+m_progress*0.5f;
                glm::vec2 dim(0.6f, 0.6f);
                float duration = Math::Rand()*0.5f+0.5f;
                m_particle->CreateTrack(pos, speed, dim, Gfx::PARTITRACK6,
                                         duration, 0.0f,
                                         duration*0.9f, 0.7f);
            }
        }

        if (m_progress < 1.0f)
        {
            m_progress += rTime*m_speed;

            SetPartRotationZ(m_object, 2, m_progress*2.0f*Math::PI);
            SetPartRotationZ(m_object, 4, m_progress*2.0f*Math::PI);
            SetPartRotationZ(m_object, 6, m_progress*2.0f*Math::PI);
        }
        else
        {
            m_phase = Phase::Wait;

            SetPartRotationX(m_object, 2, 0.0f);
            SetPartRotationX(m_object, 4, 0.0f);
            SetPartRotationX(m_object, 6, 0.0f);

            SetPartRotationZ(m_object, 2, 0.0f);
            SetPartRotationZ(m_object, 4, 0.0f);
            SetPartRotationZ(m_object, 6, 0.0f);
        }
    }

    if (m_phase == Phase::Receive)  // instruction "send" ?
    {
        if (m_progress < 0.5f &&
            m_lastParticle+m_engine->ParticleAdapt(0.05f) <= m_time)
        {
            m_lastParticle = m_time;

            for (int i = 0; i < 4; i++)
            {
                glm::vec3 pos = m_goal;
                pos.y += 9.5f;
                glm::vec3 speed = pos;
                pos.x += (Math::Rand()-0.5f)*40.0f;
                pos.y += (Math::Rand()-0.5f)*40.0f;
                pos.z += (Math::Rand()-0.5f)*40.0f;
                speed = (speed-pos)*1.0f;
//?             speed *= 0.5f+m_progress*0.5f;
                glm::vec2 dim(0.6f, 0.6f);
                float duration = Math::Rand()*0.5f+0.5f;
                m_particle->CreateTrack(pos, speed, dim, Gfx::PARTITRACK6,
                                         duration, 0.0f,
                                         duration*0.9f, 0.7f);
            }
        }

        if (m_progress < 1.0f)
        {
            m_progress += rTime*m_speed;

            SetPartRotationZ(m_object, 2, m_progress*2.0f*Math::PI);
            SetPartRotationZ(m_object, 4, m_progress*2.0f*Math::PI);
            SetPartRotationZ(m_object, 6, m_progress*2.0f*Math::PI);
        }
        else
        {
            m_phase = Phase::Wait;

            SetPartRotationX(m_object, 2, 0.0f);
            SetPartRotationX(m_object, 4, 0.0f);
            SetPartRotationX(m_object, 6, 0.0f);

            SetPartRotationZ(m_object, 2, 0.0f);
            SetPartRotationZ(m_object, 4, 0.0f);
            SetPartRotationZ(m_object, 6, 0.0f);
        }
    }

    if ( m_phase == Phase::Error )
    {
        if (m_progress < 0.5f &&
            m_lastParticle+m_engine->ParticleAdapt(0.05f) <= m_time)
        {
            m_lastParticle = m_time;

            glm::vec3 pos = m_goal;
            glm::vec3 speed;
            speed.x = (Math::Rand()-0.5f)*5.0f;
            speed.z = (Math::Rand()-0.5f)*5.0f;
            speed.y = 5.0f+Math::Rand()*5.0f;
            glm::vec2 dim;
            dim.x = 5.0f+Math::Rand()*5.0f;
            dim.y = dim.x;
            float duration = 4.0f;
            m_particle->CreateParticle(pos, speed, dim, Gfx::PARTISMOKE1, duration);
        }

        if (m_progress < 1.0f)
        {
            m_progress += rTime*m_speed;
            rTime = 0.0f;  // stops the rotation

            float angle = 0.0f;
            if ( m_progress < 0.5f )
            {
                angle = m_progress/0.5f;
            }
            else
            {
                angle = 1.0f-(m_progress-0.5f)/0.5f;
            }
            SetPartRotationX(m_object, 2, angle*0.5f);
            SetPartRotationX(m_object, 4, angle*0.5f);
            SetPartRotationX(m_object, 6, angle*0.5f);

            SetPartRotationZ(m_object, 2, (Math::Rand()-0.5f)*0.2f);
            SetPartRotationZ(m_object, 4, (Math::Rand()-0.5f)*0.2f);
            SetPartRotationZ(m_object, 6, (Math::Rand()-0.5f)*0.2f);
        }
        else
        {
            m_phase = Phase::Wait;

            SetPartRotationX(m_object, 2, 0.0f);
            SetPartRotationX(m_object, 4, 0.0f);
            SetPartRotationX(m_object, 6, 0.0f);

            SetPartRotationZ(m_object, 2, 0.0f);
            SetPartRotationZ(m_object, 4, 0.0f);
            SetPartRotationZ(m_object, 6, 0.0f);
        }
    }

    float angle = GetPartRotationY(m_object, 1);
    angle += rTime*0.5f;
    SetPartRotationY(m_object, 1, angle);

    SetPartRotationX(m_object, 3, sinf(m_time*6.0f+Math::PI*0.0f/3.0f)*0.3f);
    SetPartRotationX(m_object, 5, sinf(m_time*6.0f+Math::PI*2.0f/3.0f)*0.3f);
    SetPartRotationX(m_object, 7, sinf(m_time*6.0f+Math::PI*4.0f/3.0f)*0.3f);

    return true;
}

Error CAutoInfo::GetError()
{
    if (m_object->GetVirusMode())
    {
        return ERR_BAT_VIRUS;
    }

    return ERR_OK;
}

bool CAutoInfo::CreateInterface(bool select)
{
    CAuto::CreateInterface(select);

    if (!select)  return true;

    Ui::CWindow* pw = static_cast< Ui::CWindow* >(m_interface->SearchControl(EVENT_WINDOW0));
    if (pw == nullptr)  return false;

    float ox = 3.0f/640.0f;
    float oy = 3.0f/480.0f;
    float sx = 33.0f/640.0f;
    float sy = 33.0f/480.0f;

    glm::vec2 pos, ddim;

    pos.x = ox+sx*7.0f;
    pos.y = oy+sy*0.0f;
    ddim.x = 160.0f/640.0f;
    ddim.y =  66.0f/480.0f;
    Ui::CList* pl = pw->CreateList(pos, ddim, 1, EVENT_OBJECT_GINFO, 1.10f);
    pl->SetSelectCap(false);

    UpdateList();
    return true;
}

void CAutoInfo::UpdateInterface(float rTime)
{
    CAuto::UpdateInterface(rTime);
}

void CAutoInfo::UpdateList()
{
    if (!m_object->Implements(ObjectInterfaceType::ExchangePost)) return;
    CExchangePostObject* object = dynamic_cast<CExchangePostObject*>(m_object);

    Ui::CWindow* pw = static_cast< Ui::CWindow* >(m_interface->SearchControl(EVENT_WINDOW0));
    if (pw == nullptr)  return;

    Ui::CList* pl = static_cast< Ui::CList* >(pw->SearchControl(EVENT_OBJECT_GINFO));
    if (pl == nullptr)  return;

    pl->Flush();
    const auto& infoList = object->GetInfoList();
    if (infoList.empty())
    {
        pl->ClearState(Ui::STATE_ENABLE);
    }
    else
    {
        pl->SetState(Ui::STATE_ENABLE);

        for (int i = 0; i < static_cast<int>(infoList.size()); i++)
        {
            char text[100];
            sprintf(text, "%s = %.2f", infoList[i].name.c_str(), infoList[i].value);
            pl->SetItemName(i, text);
        }
    }

    object->SetInfoUpdate(false);
}

void CAutoInfo::UpdateListVirus()
{
    Ui::CWindow* pw = static_cast< Ui::CWindow* >(m_interface->SearchControl(EVENT_WINDOW0));
    if (pw == nullptr)  return;

    Ui::CList* pl = static_cast< Ui::CList* >(pw->SearchControl(EVENT_OBJECT_GINFO));
    if (pl == nullptr)  return;

    pl->SetState(Ui::STATE_ENABLE);

    pl->Flush();
    for (int i = 0; i < 4; ++i)
    {
        char text[100];
        int max = static_cast< int >(2.0f+Math::Rand()*10.0f);
        for (int j = 0; j < max; ++j)
        {
            do
            {
                text[j] = ' '+static_cast<int>(Math::Rand()*94.0f);
            }
            while (text[j] == '\\');
        }
        text[max] = 0;

        pl->SetItemName(i, text);
    }
}

bool CAutoInfo::Write(CLevelParserLine* line)
{
    if (m_phase == Phase::Wait)
        return false;

    line->AddParam("aExist", std::make_unique<CLevelParserParam>(true));
    CAuto::Write(line);
    line->AddParam("aPhase", std::make_unique<CLevelParserParam>(static_cast<int>(m_phase)));
    line->AddParam("aProgress", std::make_unique<CLevelParserParam>(m_progress));
    line->AddParam("aSpeed", std::make_unique<CLevelParserParam>(m_speed));

    return true;
}

bool CAutoInfo::Read(CLevelParserLine* line)
{
    if (!line->GetParam("aExist")->AsBool(false))
        return false;

    CAuto::Read(line);
    m_phase = static_cast<Phase>(line->GetParam("aPhase")->AsInt(static_cast<int>(Phase::Wait)));
    m_progress = line->GetParam("aProgress")->AsFloat(0.0f);
    m_speed = line->GetParam("aSpeed")->AsFloat(1.0f);

    m_lastParticle = 0.0f;

    return true;
}
