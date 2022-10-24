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
 * \file object/details/jostleable_details.h
 * \brief CObjectJostleableDetails - set of tweaks for Jostleable objects
 */

#pragma once

class CObject;
class CLevelParser;
class CLevelParserLine;

#include "math/sphere.h"

//////////////////////////////////////////////////////////////////////////////
// Main struct
//////////////////////////////////////////////////////////////////////////////

struct CObjectJostleableDetails
{
    bool  enabled = false;
    float factor  = 1.0f;
    
    Math::Sphere sphere;

    void ReadHardcode(ObjectType type);
    bool Read(CLevelParserLine* line);
    void Write(CLevelParser* parser, ObjectType type);
};


//////////////////////////////////////////////////////////////////////////////
// Provider
//////////////////////////////////////////////////////////////////////////////

CObjectJostleableDetails GetObjectJostleableDetails(CObject* obj);