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

//////////////////////////////////////////////////////////////////////////////
// Child structs
//////////////////////////////////////////////////////////////////////////////

struct CObjectCargoSlottedDetails
{
    bool         enabled = false;

    int          partNum = 0;
    Math::Vector position;
};

struct CObjectPowerSlottedDetails
{
    bool         enabled = false;

    Math::Vector position;
};

struct CObjectOtherSlottedDetails
{
    bool         enabled = false;

    Math::Vector position;
};

//////////////////////////////////////////////////////////////////////////////
// Main struct
//////////////////////////////////////////////////////////////////////////////

struct CObjectSlottedDetails
{
    bool enabled = false;

    CObjectCargoSlottedDetails cargo;
    CObjectPowerSlottedDetails power;
    CObjectOtherSlottedDetails other;

    void ReadHardcode(ObjectType type);
    bool Read(CLevelParserLine* line);
    void Write(CLevelParser* parser, ObjectType type);
};


//////////////////////////////////////////////////////////////////////////////
// Provider
//////////////////////////////////////////////////////////////////////////////

CObjectSlottedDetails GetObjectSlottedDetails(CObject* obj);
