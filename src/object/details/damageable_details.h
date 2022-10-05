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
 * \file object/details/damageable_details.h
 * \brief CObjectDamageableDetails - set of tweaks for Damageable objects
 */

#pragma once

class CObject;
class CLevelParser;
class CLevelParserLine;

//////////////////////////////////////////////////////////////////////////////
// Child structs
//////////////////////////////////////////////////////////////////////////////

struct CObjectFireDamageDetails
{
    bool enabled = true;
};

struct CObjectOrganicDamageDetails
{
    bool enabled = true;
};

struct CObjectPhazerDamageDetails
{
    bool enabled = true;
};

struct CObjectTowerDamageDetails
{
    bool enabled = false;
};

struct CObjectFallingObjectDamageDetails
{
    bool enabled = true;
};

struct CObjectExplosiveDamageDetails
{
    bool enabled = true;
};

struct CObjectCollisionDamageDetails
{
    bool enabled = true;
};

struct CObjectLightningDamageDetails
{
    bool enabled = true;
};

struct CObjectFallDamageDetails
{
    bool enabled = true;
};

struct CObjectSpiderDamageDetails
{
    bool enabled = true;
};

//////////////////////////////////////////////////////////////////////////////
// Main struct
//////////////////////////////////////////////////////////////////////////////

struct CObjectDamageableDetails
{
    bool enabled = false;

    CObjectFireDamageDetails          fire;
    CObjectOrganicDamageDetails       organic;
    CObjectPhazerDamageDetails        phazer;
    CObjectTowerDamageDetails         tower;
    CObjectFallingObjectDamageDetails fallingObject;
    CObjectExplosiveDamageDetails     explosive;
    CObjectCollisionDamageDetails     collision;
    CObjectLightningDamageDetails     lightning;
    CObjectFallDamageDetails          fall;
    CObjectSpiderDamageDetails        spider;

    void ReadHardcode(ObjectType type);
    bool Read(CLevelParserLine* line);
    void Write(CLevelParser* parser, ObjectType type);
};

//////////////////////////////////////////////////////////////////////////////
// Provider
//////////////////////////////////////////////////////////////////////////////

CObjectDamageableDetails GetObjectDamageableDetails(CObject* obj);
