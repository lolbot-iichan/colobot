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
 * \file object/details/programmable_details.h
 * \brief CObjectProgrammableDetails - set of tweaks for Programmable objects
 */

#pragma once

class CObject;
class CLevelParser;
class CLevelParserLine;

//////////////////////////////////////////////////////////////////////////////
// Child structs
//////////////////////////////////////////////////////////////////////////////

struct CObjectAllowedScriptingDetails
{
// if false, WRONG_BOT error is generated
    bool build                    = false;
    bool flag                     = false;
    bool sniff                    = false;
    bool shield                   = false;
    bool recycle                  = false;
    bool pen                      = false;
    bool grabNoParam              = false;
    bool grabEnumParam            = false;
    bool shootNoParam             = false;
    bool shootTimeParam           = false;
    bool shootPointParam          = false;
};

//////////////////////////////////////////////////////////////////////////////
// Main struct
//////////////////////////////////////////////////////////////////////////////

struct CObjectProgrammableDetails
{
    bool enabled = false;

    CObjectAllowedScriptingDetails allowed;

    void ReadHardcode(ObjectType type);
    bool Read(CLevelParserLine* line);
    void Write(CLevelParser* parser, ObjectType type);
};

//////////////////////////////////////////////////////////////////////////////
// Provider
//////////////////////////////////////////////////////////////////////////////

CObjectProgrammableDetails GetObjectProgrammableDetails(CObject* obj);
