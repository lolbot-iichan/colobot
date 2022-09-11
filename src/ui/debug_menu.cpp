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

#include "ui/debug_menu.h"

#include "app/app.h"

#include "common/event.h"
#include "common/stringutils.h"

#include "graphics/engine/lightning.h"
#include "graphics/engine/terrain.h"

#include "level/robotmain.h"

#include "object/object.h"
#include "object/object_details.h"
#include "object/object_manager.h"

#include "sound/sound.h"

#include "ui/controls/button.h"
#include "ui/controls/check.h"
#include "ui/controls/interface.h"
#include "ui/controls/label.h"
#include "ui/controls/window.h"

#include <SDL_clipboard.h>

namespace Ui
{

CDebugMenu::CDebugMenu(CRobotMain* main, Gfx::CEngine* engine, CObjectManager* objMan, CSoundInterface* sound)
{
    m_main = main;
    m_interface = m_main->GetInterface();
    m_engine = engine;
    m_objMan = objMan;
    m_sound = sound;
}

CDebugMenu::~CDebugMenu()
{

}

void CDebugMenu::ToggleInterface()
{
    if (!IsActive())
    {
        CreateInterface();
        CLabel* pl = m_interface->CreateLabel(Math::Point(0.0f, 0.9f), Math::Point(1.0f, 0.1f), -1, EVENT_LABEL19, "??");
        pl->SetFontType(Gfx::FONT_STUDIO);
    }
    else
    {
        m_interface->DeleteControl(EVENT_LABEL19);
        DestroyInterface();
    }
}

const Math::Point dim = Math::Point(33.0f/640.0f, 33.0f/480.0f);
const float ox = 3.0f/640.0f, oy = 3.0f/480.0f;
const float /*sx = 33.0f/640.0f,*/ sy = 33.0f/480.0f;

void CDebugMenu::CreateInterface()
{
    CWindow* pw = m_interface->CreateWindows(Math::Point(), Math::Point(), 0, EVENT_WINDOW7);
    Math::Point pos, ddim;
    CCheck* pc;
    CButton* pb;

    ddim.x = 4*dim.x+4*ox;
    ddim.y = 222.0f/480.0f;
    pos.x = 1.0f-ddim.x;
    pos.y = oy+sy*3.0f;
    pw->CreateGroup(pos, ddim, 6, EVENT_WINDOW7);

    ddim.x = ddim.x - 4*ox;
    ddim.y = dim.y*0.5f;
    pos.x += 2*ox;
    pos.y = oy+sy*9.0f;
    pb = pw->CreateButton(pos, ddim, -1, EVENT_DBG_SPAWN_OBJ);
    pb->SetName("Spawn object");
    pos.y -= ddim.y;
    pb = pw->CreateButton(pos, ddim, -1, EVENT_DBG_TELEPORT);
    pb->SetName("Teleport");
    pos.y -= ddim.y;
    pb = pw->CreateButton(pos, ddim, -1, EVENT_DBG_LIGHTNING);
    pb->SetName("Lightning");
    pos.y -= 0.048f;
    pc = pw->CreateCheck(pos, ddim, -1, EVENT_DBG_STATS);
    pc->SetName("Display stats");
    pos.y -= 0.048f;
    pos.y -= 0.048f;
    pc = pw->CreateCheck(pos, ddim, -1, EVENT_DBG_RESOURCES);
    pc->SetName("Underground resources");
    pos.y -= 0.048f;
    pc = pw->CreateCheck(pos, ddim, -1, EVENT_DBG_GOTO);
    pc->SetName("Render goto() path");
    pos.y -= 0.048f;
    pc = pw->CreateCheck(pos, ddim, -1, EVENT_DBG_CRASHSPHERES);
    pc->SetName("Render crash spheres");
    pos.y -= 0.048f;
    pc = pw->CreateCheck(pos, ddim, -1, EVENT_DBG_LIGHTS);
    pc->SetName("Render dynamic lights");
    pos.y -= 0.048f;
    pb = pw->CreateButton(pos, ddim, -1, EVENT_DBG_LIGHTS_DUMP);
    pb->SetName("Dump lights to log");

    UpdateInterface();
}

void CDebugMenu::CreateSpawnInterface()
{
    CWindow* pw = m_interface->CreateWindows(Math::Point(), Math::Point(), 0, EVENT_WINDOW7);
    Math::Point pos, ddim;
    CButton* pb;

    ddim.x = 4*dim.x+4*ox;
    ddim.y = 222.0f/480.0f;
    pos.x = 1.0f-ddim.x;
    pos.y = oy+sy*3.0f;
    pw->CreateGroup(pos, ddim, 6, EVENT_WINDOW7);

    ddim.x = ddim.x - 4*ox;
    ddim.y = dim.y*0.5f;
    pos.x += 2*ox;
    pos.y = oy+sy*9.0f;
    pb = pw->CreateButton(pos, ddim, -1, EVENT_DBG_SPAWN_CANCEL);
    pb->SetName("Cancel");
    pos.y -= ddim.y;
    float startX = pos.x;

    int n = 0;
    for (int i = 0; i <= EVENT_DBG_SPAWN_14 - EVENT_DBG_SPAWN_01; i++)
    {
        auto item = GetObjectDetails().GetDebugMenuItem(i);
        if (item.icon == -1) continue;

        if (n % 4 == 0)
        {
            pos.x = startX;
            pos.y -= dim.y;
        }

        EventType ev = static_cast<EventType>(EVENT_DBG_SPAWN_01 + i);
        pw->CreateButton(pos, dim, item.icon, ev);
        pos.x += dim.x;
        n++;
    }

    pos.x = startX;
    for (int i = 0; i <= EVENT_DBG_SPAWN_14 - EVENT_DBG_SPAWN_01; i++)
    {
        auto item = GetObjectDetails().GetDebugMenuItem(i);
        if (item.icon != -1) continue;
        if (item.type == OBJECT_NULL) continue;

        pos.y -= ddim.y;
        EventType ev = static_cast<EventType>(EVENT_DBG_SPAWN_01 + i);
        pb = pw->CreateButton(pos, ddim, -1, ev);
        pb->SetName(item.text);
    }
}

void CDebugMenu::UpdateInterface()
{
    CCheck* pc;
    CButton* pb;

    CWindow* pw = static_cast<CWindow*>(m_interface->SearchControl(EVENT_WINDOW7));
    if (pw == nullptr) return;


    pb = static_cast<CButton*>(pw->SearchControl(EVENT_DBG_LIGHTNING));
    if (pb != nullptr)
    {
        pb->SetName(m_lightningActive ? "Disable lightning" : "Lightning");
    }

    pb = static_cast<CButton*>(pw->SearchControl(EVENT_DBG_TELEPORT));
    if (pb != nullptr)
    {
        pb->SetName(m_teleportActive ? "Abort teleport" : "Teleport");
    }

    pc = static_cast<CCheck*>(pw->SearchControl(EVENT_DBG_STATS));
    if (pc != nullptr)
    {
        pc->SetState(STATE_CHECK, m_engine->GetShowStats());
    }

    pc = static_cast<CCheck*>(pw->SearchControl(EVENT_DBG_RESOURCES));
    if (pc != nullptr)
    {
        pc->SetState(STATE_CHECK, m_engine->GetDebugResources());
    }

    pc = static_cast<CCheck*>(pw->SearchControl(EVENT_DBG_GOTO));
    if (pc != nullptr)
    {
        pc->SetState(STATE_CHECK, m_engine->GetDebugGoto());
    }

    pc = static_cast<CCheck*>(pw->SearchControl(EVENT_DBG_CRASHSPHERES));
    if (pc != nullptr)
    {
        pc->SetState(STATE_CHECK, m_main->GetDebugCrashSpheres());
    }

    pc = static_cast<CCheck*>(pw->SearchControl(EVENT_DBG_LIGHTS));
    if (pc != nullptr)
    {
        pc->SetState(STATE_CHECK, m_engine->GetDebugLights());
    }

    for (int idx = 0; idx <= EVENT_DBG_SPAWN_14 - EVENT_DBG_SPAWN_01; idx++)
    {
        EventType ev = static_cast<EventType>(EVENT_DBG_SPAWN_01 + idx);
        pb = static_cast<CButton*>(pw->SearchControl(ev));
        if (pb != nullptr)
        {
            auto item = GetObjectDetails().GetDebugMenuItem(idx);
            pb->SetState(STATE_ENABLE, item.type != m_spawningType);
        }
    }
}

void CDebugMenu::DestroyInterface()
{
    m_interface->DeleteControl(EVENT_WINDOW7);
    m_spawningType = OBJECT_NULL;
}

bool CDebugMenu::EventProcess(const Event &event)
{
    switch (event.type)
    {
        case EVENT_DBG_STATS:
            m_engine->SetShowStats(!m_engine->GetShowStats());
            UpdateInterface();
            break;

        case EVENT_DBG_SPAWN_OBJ:
            DestroyInterface();
            CreateSpawnInterface();
            break;

        case EVENT_DBG_TELEPORT:
            if (!m_teleportActive)
            {
                if (m_main->GetSelect() != nullptr)
                    m_teleportActive = true;
                else
                    m_sound->Play(SOUND_CLICK);
            }
            else
            {
                m_teleportActive = false;
            }
            UpdateInterface();
            break;

        case EVENT_DBG_LIGHTNING:
            m_lightningActive = !m_lightningActive;
            UpdateInterface();
            break;

        case EVENT_DBG_RESOURCES:
            m_engine->SetDebugResources(!m_engine->GetDebugResources());
            UpdateInterface();
            break;

        case EVENT_DBG_GOTO:
            m_engine->SetDebugGoto(!m_engine->GetDebugGoto());
            UpdateInterface();
            break;

        case EVENT_DBG_CRASHSPHERES:
            m_main->SetDebugCrashSpheres(!m_main->GetDebugCrashSpheres());
            UpdateInterface();
            break;

        case EVENT_DBG_LIGHTS:
            m_engine->SetDebugLights(!m_engine->GetDebugLights());
            UpdateInterface();
            break;

        case EVENT_DBG_LIGHTS_DUMP:
            m_engine->DebugDumpLights();
            break;


        case EVENT_DBG_SPAWN_CANCEL:
            DestroyInterface();
            CreateInterface();
            break;

        case EVENT_DBG_SPAWN_01:
        case EVENT_DBG_SPAWN_02:
        case EVENT_DBG_SPAWN_03:
        case EVENT_DBG_SPAWN_04:
        case EVENT_DBG_SPAWN_05:
        case EVENT_DBG_SPAWN_06:
        case EVENT_DBG_SPAWN_07:
        case EVENT_DBG_SPAWN_08:
        case EVENT_DBG_SPAWN_09:
        case EVENT_DBG_SPAWN_10:
        case EVENT_DBG_SPAWN_11:
        case EVENT_DBG_SPAWN_12:
        case EVENT_DBG_SPAWN_13:
        case EVENT_DBG_SPAWN_14:
            {
                int idx = event.type - EVENT_DBG_SPAWN_01;
                auto item = GetObjectDetails().GetDebugMenuItem(idx);
                m_spawningType = item.type;
                UpdateInterface();
            }
            break;

        case EVENT_MOUSE_BUTTON_DOWN:
            if (event.GetData<MouseButtonEventData>()->button == MOUSE_BUTTON_LEFT)
            {
                if (m_lightningActive)
                {
                    return !HandleLightning(event.mousePos);
                }

                if (m_teleportActive)
                {
                    return !HandleTeleport(event.mousePos);
                }

                if (m_spawningType != OBJECT_NULL)
                {
                    return !HandleSpawnObject(m_spawningType, event.mousePos);
                }
            }
            break;

        case EVENT_MOUSE_MOVE:
            if (m_spawningType != OBJECT_NULL || m_teleportActive || m_lightningActive)
            {
                return false;
            }
            break;

        case EVENT_FRAME:
            HandleFrameUpdate(event);
            break;

        case EVENT_KEY_DOWN:
            if (event.GetData<KeyEventData>()->key == KEY(c) && (event.kmodState & KMOD_CTRL) != 0)
            {
                if (IsActive())
                {
                    return !HandleCopy(event.mousePos);
                }
            }

        default:
            break;
    }
    return true;
}

bool CDebugMenu::HandleSpawnObject(ObjectType type, Math::Point mousePos)
{
    Math::Vector pos;
    if (m_engine->DetectObject(mousePos, pos, true) == -1)
    {
        m_sound->Play(SOUND_CLICK, 1.0f, 0.5f);
        return false;
    }

    ObjectCreateParams params;
    params.pos = pos;
    params.type = type;
    params.power = 100.0f;
    m_objMan->CreateObject(params);

    // Update shortcuts in the upper-left corner
    m_main->CreateShortcuts();

    m_sound->Play(SOUND_RADAR, 2.0f, 1.5f);

    return true;
}

bool CDebugMenu::HandleLightning(Math::Point mousePos)
{
    Math::Vector pos;
    if (m_engine->DetectObject(mousePos, pos, true) == -1)
    {
        m_sound->Play(SOUND_CLICK, 1.0f, 0.5f);
        return false;
    }

    m_engine->GetLightning()->StrikeAtPos(pos);

    return true;
}

bool CDebugMenu::HandleTeleport(Math::Point mousePos)
{
    CObject* select = m_main->GetSelect();

    Math::Vector pos;
    if (m_engine->DetectObject(mousePos, pos, true) == -1 || !m_engine->GetTerrain()->AdjustToFloor(pos) || select == nullptr)
    {
        m_sound->Play(SOUND_CLICK, 1.0f, 0.5f);
        m_teleportActive = false;
        UpdateInterface();
        return false;
    }

    select->SetPosition(pos);

    m_sound->Play(SOUND_BUILD, 4.0f, 0.75f);
    m_sound->Play(SOUND_BUILD, pos, 4.0f, 0.75f);

    m_teleportActive = false;
    UpdateInterface();

    return true;
}

void CDebugMenu::HandleFrameUpdate(const Event &event)
{
    std::string str = "-";
    Math::Vector pos;
    int obj;
    if ((obj = m_engine->DetectObject(event.mousePos, pos, true)) != -1)
        str = StrUtils::Format("pos=% 3.2f; % 3.2f    height=% 3.2f    objId=% 4d", pos.x, pos.z, pos.y, obj);

    CLabel* pl = static_cast<CLabel*>(m_interface->SearchControl(EVENT_LABEL19));
    if (pl == nullptr) return;
    pl->SetName(str.c_str());
}

bool CDebugMenu::HandleCopy(Math::Point mousePos)
{
    Math::Vector pos;
    if (m_engine->DetectObject(mousePos, pos, true) == -1)
    {
        m_sound->Play(SOUND_CLICK, 1.0f, 0.5f);
        return false;
    }

    std::string str = StrUtils::Format("pos=%.2f;%.2f", pos.x, pos.z);

    GetLogger()->Debug("%s\n", str.c_str());
    SDL_SetClipboardText(str.c_str());
    return true;
}

bool CDebugMenu::IsActive()
{
    return m_interface->SearchControl(EVENT_WINDOW7) != nullptr;
}

}
