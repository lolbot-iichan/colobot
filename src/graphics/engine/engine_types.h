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

/**
 * \file graphics/engine/engine.h
 * \brief Main graphics engine - CEngine class
 */

#pragma once

// Graphics module namespace
namespace Gfx
{

/**
  \enum EngineObjectType
  \brief Class of graphics engine object */
enum EngineObjectType
{
    //! Object doesn't exist
    ENG_OBJTYPE_NULL        = 0,
    //! Terrain
    ENG_OBJTYPE_TERRAIN     = 1,
    //! Fixed object
    ENG_OBJTYPE_FIX         = 2,
    //! Moving object
    ENG_OBJTYPE_VEHICLE    = 3,
    //! Part of a moving object
    ENG_OBJTYPE_DESCENDANT  = 4,
    //! Fixed object type quartz
    ENG_OBJTYPE_QUARTZ      = 5,
    //! Fixed object type metal
    ENG_OBJTYPE_METAL       = 6
};

/**
 * \struct EngineShadowType
 * \brief Type of shadow drawn by the graphics engine
 */
enum EngineShadowType
{
    //! Normal shadow
    ENG_SHADOW_NORM = 0,
    //! TODO: ?
    ENG_SHADOW_WORM = 1
};

} // namespace Gfx