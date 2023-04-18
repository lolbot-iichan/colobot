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
 * \file object/old_object_interface.h
 * \brief Legacy CObject interface
 */

#pragma once

#include <glm/glm.hpp>

class CAuto;

enum ObjectType : unsigned int;

struct Character
{
    float        wheelFront = 1.0f;     // position X of the front wheels
    float        wheelBack = 1.0f;      // position X of the back wheels
    float        wheelLeft = 1.0f;      // position Z of the left wheels
    float        wheelRight = 1.0f;     // position Z of the right wheels
    float        height = 0.0f;         // normal height on top of ground
};

class COldObjectInterface
{
public:
    virtual ~COldObjectInterface() {}

    virtual void        Simplify();
    virtual void        DeletePart(int part);
    virtual void        SetType(ObjectType type);

    virtual int         GetObjectRank(int part);

    virtual int         GetOption();

    virtual void        SetDrawFront(bool bDraw);

    virtual void        SetFloorHeight(float height);
    virtual void        FloorAdjust();

    virtual void        SetLinVibration(glm::vec3 dir);
    virtual void        SetCirVibration(glm::vec3 dir);

    virtual glm::vec3   GetTilt();

    virtual void        SetMasterParticle(int part, int parti);

    virtual glm::mat4   GetWorldMatrix(int part);

    virtual Character*  GetCharacter();

    virtual void        FlatParent();

    // Not sure. Maybe a separate interface, or maybe CControllableObject (buildings can have viruses too)
    virtual void        SetVirusMode(bool bEnable);
    virtual bool        GetVirusMode();

    // This will be eventually removed after refactoring to subclasses
    virtual CAuto*      GetAuto();
};
