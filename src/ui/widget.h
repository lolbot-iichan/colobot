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

#pragma once

#include "common/event.h"

#include "graphics/core/color.h"

#include "level/build_type.h"
#include "level/research_type.h"

#include "math/point.h"

#include "object/object_type.h"

#include <vector>

namespace Ui
{

enum WidgetType
{
    WIDGET_ICON_BUTTON  = 0,
    WIDGET_ICON_LOGO    = 1,
    WIDGET_COLOR_BUTTON = 2,
};

union CWidgetParams
{
    // for WIDGET_ICON_BUTTON
    // for WIDGET_ICON_LOGO
    int        icon;

    // for WIDGET_COLOR_BUTTON
    Gfx::Color color;
};

struct CWidget
{
    Math::Point   position               = Math::Point(7.7f, 0.5f);
    Math::Point   size                   = Math::Point(1.0f, 1.0f);
    WidgetType    widgetType             = WIDGET_ICON_BUTTON;
    CWidgetParams params                 = {-1};
    EventType     event                  = EVENT_NULL;

    bool          isDefault              = false;
    bool          isImmediat             = false;

    bool          disabledByTrainer      = false;
    bool          disabledByPlusExplorer = false;

    int           onBuildingEnabled      = 0;
    int           onResearchDone         = 0;
};

} // namespace Ui
