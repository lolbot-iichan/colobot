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
 * \file object/details/slotted_details.h
 * \brief CObjectSlottedDetails - set of tweaks for Slotted objects
 */

#pragma once

class CObject;
class CLevelParser;
class CLevelParserLine;

#include <vector>
#include <glm/fwd.hpp>

//////////////////////////////////////////////////////////////////////////////
// Child structs
//////////////////////////////////////////////////////////////////////////////

enum SlotType
{
    SLOT_POWER = 0,
    SLOT_CARGO = 1,
    SLOT_OTHER = 2,
};

struct CObjectSlotDetails
{
    int       category = SLOT_OTHER;
    int       partNum  = 0;
    glm::vec3 position = {0,0,0};
    glm::vec3 rotation = {0,0,0};
    
    //TODO: rename
    // object can be taken from [angle-acceptanceAngle; angle+acceptanceAngle] angle interval only
    float     angle           = 0; 
    float     acceptanceAngle = 0;
};

//////////////////////////////////////////////////////////////////////////////
// Main struct
//////////////////////////////////////////////////////////////////////////////

struct CObjectSlottedDetails
{
    bool enabled = false;
    bool createWithBattery = false;

    std::vector<CObjectSlotDetails> slots;

    void ReadHardcode(ObjectType type);
    bool Read(CLevelParserLine* line);
    void Write(CLevelParser* parser, ObjectType type);
};
