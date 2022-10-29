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


#include "object/motion/motion.h"


class CMotionWheeled : public CMotion
{
public:
    CMotionWheeled(COldObject* object);
    ~CMotionWheeled();

    bool        EventProcess(const Event &event) override;

protected:
    bool        EventFrame(const Event &event);

protected:
    float       m_wheelTurn[4];
    glm::vec3   m_wheelLastPos = { 0, 0, 0 };
    glm::vec3   m_wheelLastAngle = { 0, 0, 0 };
};
