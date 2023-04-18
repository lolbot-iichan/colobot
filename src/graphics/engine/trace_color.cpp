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

#include "graphics/core/color.h"
#include "graphics/engine/trace_color.h"

#include <cassert>

std::string TraceColorName(TraceColor color)
{
    switch(color)
    {
        case TraceColor::Blue:       return "Blue";
        case TraceColor::Red:        return "Red";
        case TraceColor::Green:      return "Green";
        case TraceColor::Yellow:     return "Yellow";
        case TraceColor::Violet:     return "Violet";
        case TraceColor::White:      return "White";
        case TraceColor::Black:      return "Black";
        case TraceColor::Gray:       return "Gray";
        case TraceColor::LightGray:  return "LightGray";
        case TraceColor::Pink:       return "Pink";
        case TraceColor::Purple:     return "Purple";
        case TraceColor::Orange:     return "Orange";
        case TraceColor::Beige:      return "Beige";
        case TraceColor::Brown:      return "Brown";
        case TraceColor::Skin:       return "Skin";
        case TraceColor::LightGreen: return "LightGreen";
        case TraceColor::LightBlue:  return "LightBlue";
        case TraceColor::RedArrow:   return "RedArrow";
        case TraceColor::BlackArrow: return "BlackArrow";
        default:
            assert(false);
            return "";
    }
}

Gfx::Color TraceColorColor(TraceColor color)
{
    switch(color)
    {
        case TraceColor::Blue:       return Gfx::Color(0.000f, 0.000f, 0.753f, 1.0f);
        case TraceColor::Red:        return Gfx::Color(1.000f, 0.000f, 0.000f, 1.0f);
        case TraceColor::Green:      return Gfx::Color(0.000f, 0.627f, 0.000f, 1.0f);
        case TraceColor::Yellow:     return Gfx::Color(1.000f, 1.000f, 0.000f, 1.0f);
        case TraceColor::Violet:     return Gfx::Color(0.820f, 0.000f, 0.997f, 1.0f);
        case TraceColor::White:      return Gfx::Color(1.000f, 1.000f, 1.000f, 1.0f);
        case TraceColor::Black:      return Gfx::Color(0.000f, 0.000f, 0.000f, 1.0f);
        case TraceColor::Gray:       return Gfx::Color(0.549f, 0.549f, 0.549f, 1.0f);
        case TraceColor::LightGray:  return Gfx::Color(0.753f, 0.753f, 0.753f, 1.0f);
        case TraceColor::Pink:       return Gfx::Color(1.000f, 0.627f, 0.753f, 1.0f);
        case TraceColor::Purple:     return Gfx::Color(0.878f, 0.000f, 0.753f, 1.0f);
        case TraceColor::Orange:     return Gfx::Color(1.000f, 0.627f, 0.000f, 1.0f);
        case TraceColor::Beige:      return Gfx::Color(0.878f, 0.753f, 0.000f, 1.0f);
        case TraceColor::Brown:      return Gfx::Color(0.627f, 0.361f, 0.000f, 1.0f);
        case TraceColor::Skin:       return Gfx::Color(0.961f, 0.839f, 0.714f, 1.0f);
        case TraceColor::LightGreen: return Gfx::Color(0.000f, 1.000f, 0.000f, 1.0f);
        case TraceColor::LightBlue:  return Gfx::Color(0.000f, 0.871f, 1.000f, 1.0f);
        case TraceColor::BlackArrow: return TraceColorColor(TraceColor::Black);
        case TraceColor::RedArrow:   return TraceColorColor(TraceColor::Red); //TODO: We could probably have all the colors available as arrows now

        default:
            assert(false);
            return Gfx::Color();
    }
}
