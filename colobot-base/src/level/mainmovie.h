/*
 * This file is part of the Colobot: Gold Edition source code
 * Copyright (C) 2001-2023, Daniel Roux, EPSITEC SA & TerranovaTeam
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
 * \file level/mainmovie.h
 * \brief CMainMovie - control over movie sequences
 */

#pragma once

#include <glm/glm.hpp>


class CRobotMain;
class CSoundInterface;
struct Event;

namespace Gfx
{
class CCamera;
class CEngine;
} // namespace Gfx

enum MainMovieType : unsigned char
{
    MM_NONE,
    MM_SATCOMopen,
    MM_SATCOMclose,
};



class CMainMovie
{
public:
    CMainMovie();
    ~CMainMovie();

    void            Flush();
    bool            Start(MainMovieType type, float time);
    bool            Stop();
    bool            IsExist();
    bool            EventProcess(const Event &event);
    MainMovieType   GetType();
    MainMovieType   GetStopType();

protected:
    Gfx::CEngine*       m_engine;
    CRobotMain*         m_main;
    Gfx::CCamera*       m_camera;
    CSoundInterface*    m_sound;

    MainMovieType       m_type;
    MainMovieType       m_stopType;
    float               m_speed;
    float               m_progress;
    glm::vec3           m_initialEye;
    glm::vec3           m_initialLookat;
    glm::vec3           m_finalEye[2];
    glm::vec3           m_finalLookat[2];
};

