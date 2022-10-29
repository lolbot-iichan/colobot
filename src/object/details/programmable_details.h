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

    // with foreground tasks
    bool build                    = false;
    bool deflag                   = false;
    bool dropNoParam              = false;
    bool dropEnumParam            = false;
    bool fireNoParam              = false;
    bool fireTimeParam            = false;
    bool firePointParam           = false;
    bool flag                     = false;
    bool GOTO                     = false;
    bool grabNoParam              = false;
    bool grabEnumParam            = false;
    bool move                     = false;
    bool pencolor                 = false;
    bool pendown                  = false;
    bool penup                    = false;
    bool receive                  = false;
    bool recycle                  = false;
    bool send                     = false;
    bool sniff                    = false;
    bool thump                    = false;
    bool turn                     = false;
    bool wait                     = false;

    // with background tasks
    bool aim                      = false;
    bool shield                   = false;

    // with automated buildings
    bool destroy                  = false;
    bool factory                  = false;
    bool research                 = false;
    bool takeoff                  = false;

    // with no tasks
    bool abstime                  = false;
    bool buildingenabled          = false;
    bool camerafocus              = false;
    bool canbuild                 = false;
    bool canresearch              = false;
    bool cmdline                  = false;
    bool DELETE                   = false;
    bool deleteinfo               = false;
    bool detect                   = false;
    bool direction                = false;
    bool distance                 = false;
    bool distance2d               = false;
    bool endmission               = false;
    bool errmode                  = false;
    bool flatground               = false;
    bool flatspace                = false;
    bool getbuild                 = false;
    bool getresearchdone          = false;
    bool getresearchenable        = false;
    bool ipf                      = false;
    bool isbusy                   = false;
    bool ismovie                  = false;
    bool jet                      = false;
    bool message                  = false;
    bool motor                    = false;
    bool penwidth                 = false;
    bool playmusic                = false;
    bool produce                  = false;
    bool radar                    = false;
    bool radarall                 = false;
    bool researched               = false;
    bool retobject                = false;
    bool retobjectbyid            = false;
    bool search                   = false;
    bool searchall                = false;
    bool setbuild                 = false;
    bool setresearchdone          = false;
    bool setresearchenable        = false;
    bool space                    = false;
    bool stopmusic                = false;
    bool testinfo                 = false;
    bool topo                     = false;
};

//////////////////////////////////////////////////////////////////////////////
// Main struct
//////////////////////////////////////////////////////////////////////////////

struct CObjectProgrammableDetails
{
    bool enabled     = false;
    bool noSaveState = false;

    CObjectAllowedScriptingDetails allowed;

    void ReadHardcode(ObjectType type);
    bool Read(CLevelParserLine* line);
    void Write(CLevelParser* parser, ObjectType type);
};
