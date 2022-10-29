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

#include "graphics/engine/engine.h"
#include "graphics/engine/lightning.h"
#include "graphics/engine/terrain.h"

#include "level/robotmain.h"

#include "object/object.h"
#include "object/object_manager.h"

#include "object/details/details_provider.h"
#include "object/details/global_details.h"

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
        CLabel* pl = m_interface->CreateLabel({ 0.0f, 0.9f }, { 1.0f, 0.1f }, -1, EVENT_LABEL19, "??");
        pl->SetFontType(Gfx::FONT_STUDIO);
    }
    else
    {
        m_interface->DeleteControl(EVENT_LABEL19);
        DestroyInterface();
    }
}

constexpr glm::vec2 dim = { 33.0f / 640.0f, 33.0f / 480.0f };
constexpr float ox = 3.0f/640.0f, oy = 3.0f/480.0f;
constexpr float /*sx = 33.0f/640.0f,*/ sy = 33.0f/480.0f;

void CDebugMenu::CreateInterface()
{
    CWindow* pw = m_interface->CreateWindows({ 0, 0 }, { 0, 0 }, 0, EVENT_WINDOW7);
    glm::vec2 pos, ddim;
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
    CWindow* pw = m_interface->CreateWindows({ 0, 0 }, { 0, 0 }, 0, EVENT_WINDOW7);
    glm::vec2 pos, ddim;
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


    size_t n = 0;

    size_t len = EVENT_DBG_SPAWN_MAX - EVENT_DBG_SPAWN_01 + 1;
    auto debugMenu = GetObjectGlobalDetails().debugMenu;
    len = debugMenu.size() > len ? len : debugMenu.size();
    for (size_t i = 0; i < len; i++)
    {
        if (debugMenu[i].icon == -1) continue;

        if (n % 4 == 0)
        {
            pos.x = startX;
            pos.y -= dim.y;
        }

        EventType ev = static_cast<EventType>(EVENT_DBG_SPAWN_01 + i);
        pw->CreateButton(pos, dim, debugMenu[i].icon, ev)->SetTooltip(debugMenu[i].text);
        pos.x += dim.x;
        n++;
    }

    pos.x = startX;
    for (size_t i = 0; i < len; i++)
    {
        if (debugMenu[i].icon != -1) continue;
        if (debugMenu[i].type == OBJECT_NULL) continue;

        pos.y -= ddim.y;
        EventType ev = static_cast<EventType>(EVENT_DBG_SPAWN_01 + i);
        pb = pw->CreateButton(pos, ddim, -1, ev);
        pb->SetName(debugMenu[i].text);
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

    size_t len = EVENT_DBG_SPAWN_MAX - EVENT_DBG_SPAWN_01 + 1;
    auto debugMenu = GetObjectGlobalDetails().debugMenu;
    len = debugMenu.size() > len ? len : debugMenu.size();
    for (size_t i = 0; i <= len; i++)
    {
        EventType ev = static_cast<EventType>(EVENT_DBG_SPAWN_01 + i);
        pb = static_cast<CButton*>(pw->SearchControl(ev));
        if (pb != nullptr)
        {
            pb->SetState(STATE_ENABLE, debugMenu[i].type != m_spawningType);
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
    if (event.type == EVENT_DBG_STATS)
    {
        m_engine->SetShowStats(!m_engine->GetShowStats());
        UpdateInterface();
    }
    else if (event.type == EVENT_DBG_SPAWN_OBJ)
    {
        DestroyInterface();
        CreateSpawnInterface();
    }
    else if (event.type == EVENT_DBG_TELEPORT)
    {
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
    }
    else if (event.type == EVENT_DBG_LIGHTNING)
    {
        m_lightningActive = !m_lightningActive;
        UpdateInterface();
    }
    else if (event.type == EVENT_DBG_RESOURCES)
    {
        m_engine->SetDebugResources(!m_engine->GetDebugResources());
        UpdateInterface();
    }
    else if (event.type == EVENT_DBG_GOTO)
    {
        m_engine->SetDebugGoto(!m_engine->GetDebugGoto());
        UpdateInterface();
    }
    else if (event.type == EVENT_DBG_CRASHSPHERES)
    {
        m_main->SetDebugCrashSpheres(!m_main->GetDebugCrashSpheres());
        UpdateInterface();
    }
    else if (event.type == EVENT_DBG_LIGHTS)
    {
        m_engine->SetDebugLights(!m_engine->GetDebugLights());
        UpdateInterface();
    }
    else if (event.type == EVENT_DBG_LIGHTS_DUMP)
    {
        m_engine->DebugDumpLights();
    }
    else if (event.type == EVENT_DBG_SPAWN_CANCEL)
    {
        DestroyInterface();
        CreateInterface();
    }
    else if (event.type >= EVENT_DBG_SPAWN_01 && event.type <= EVENT_DBG_SPAWN_MAX)
    {
        size_t idx = event.type - EVENT_DBG_SPAWN_01;
        assert(idx < GetObjectGlobalDetails().debugMenu.size());
        auto item = GetObjectGlobalDetails().debugMenu[idx];
        m_spawningType = item.type;
        UpdateInterface();
    }
    else if (event.type == EVENT_MOUSE_BUTTON_DOWN)
    {
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
    }
    else if (event.type == EVENT_MOUSE_MOVE)
    {
        if (m_spawningType != OBJECT_NULL || m_teleportActive || m_lightningActive)
        {
            return false;
        }
    }
    else if (event.type == EVENT_FRAME)
    {
        HandleFrameUpdate(event);
    }
    else if (event.type == EVENT_KEY_DOWN)
    {
        if (event.GetData<KeyEventData>()->key == KEY(c) && (event.kmodState & KMOD_CTRL) != 0)
        {
            if (IsActive())
            {
                return !HandleCopy(event.mousePos);
            }
        }
    }
    return true;
}

bool CDebugMenu::HandleSpawnObject(ObjectType type, const glm::vec2& mousePos)
{
    glm::vec3 pos;
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

bool CDebugMenu::HandleLightning(const glm::vec2& mousePos)
{
    glm::vec3 pos;
    if (m_engine->DetectObject(mousePos, pos, true) == -1)
    {
        m_sound->Play(SOUND_CLICK, 1.0f, 0.5f);
        return false;
    }

    m_engine->GetLightning()->StrikeAtPos(pos);

    return true;
}

bool CDebugMenu::HandleTeleport(const glm::vec2& mousePos)
{
    CObject* select = m_main->GetSelect();

    glm::vec3 pos;
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
    glm::vec3 pos;
    int obj;
    if ((obj = m_engine->DetectObject(event.mousePos, pos, true)) != -1)
        str = StrUtils::Format("pos=% 3.2f; % 3.2f    height=% 3.2f    objId=% 4d", pos.x, pos.z, pos.y, obj);

    CLabel* pl = static_cast<CLabel*>(m_interface->SearchControl(EVENT_LABEL19));
    if (pl == nullptr) return;
    pl->SetName(str.c_str());
}

bool CDebugMenu::HandleCopy(const glm::vec2& mousePos)
{
    glm::vec3 pos;
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
