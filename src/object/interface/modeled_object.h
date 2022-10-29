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

#include "object/object_interface_type.h"

class CModeledObject
{
public:
    explicit CModeledObject(ObjectInterfaceTypes& types)
    {
        types[static_cast<int>(ObjectInterfaceType::Modeled)] = true;
    }
    virtual ~CModeledObject()
    {}

    virtual void        SetPartPosition(int part, const glm::vec3 &pos) = 0;
    virtual glm::vec3   GetPartPosition(int part) const = 0;

    virtual void        SetPartRotation(int part, const glm::vec3 &angle) = 0;
    virtual glm::vec3   GetPartRotation(int part) const = 0;
    virtual void        SetPartRotationY(int part, float angle) = 0;
    virtual void        SetPartRotationX(int part, float angle) = 0;
    virtual void        SetPartRotationZ(int part, float angle) = 0;
    virtual float       GetPartRotationY(int part) = 0;
    virtual float       GetPartRotationX(int part) = 0;
    virtual float       GetPartRotationZ(int part) = 0;

    virtual void        SetPartScale(int part, float zoom) = 0;
    virtual void        SetPartScale(int part, glm::vec3 zoom) = 0;
    virtual glm::vec3   GetPartScale(int part) const = 0;
    virtual void        SetPartScaleX(int part, float zoom) = 0;
    virtual float       GetPartScaleX(int part) = 0;
    virtual void        SetPartScaleY(int part, float zoom) = 0;
    virtual float       GetPartScaleY(int part) = 0;
    virtual void        SetPartScaleZ(int part, float zoom) = 0;
    virtual float       GetPartScaleZ(int part) = 0;
};
