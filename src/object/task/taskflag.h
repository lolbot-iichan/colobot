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

#include "object/task/task.h"

#include "object/object_type.h"

#include <glm/glm.hpp>

class CObject;

class CTaskFlag : public CForegroundTask
{
public:
    CTaskFlag(COldObject* object);
    ~CTaskFlag();

    bool        EventProcess(const Event &event) override;

    Error       Start(int rank);
    Error       IsEnded() override;
    bool        Abort() override;

protected:
    Error       CreateFlag(int rank);
    CObject*    SearchNearest(glm::vec3 pos);
    int         CountObject(ObjectType type);

protected:
    float           m_time = 0.0f;
    bool            m_bError = false;
};
