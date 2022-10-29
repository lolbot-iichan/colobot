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
 * \file object/details/macro.h
 * \brief collection of macro definitions used in Read()/Write() methods
 */

#pragma once

#include <boost/lexical_cast.hpp>

#include "level/parser/parser.h"

#include "object/details/macro.h"

void ThrowUnusedCmd(CLevelParserLine* line)
{
    auto command    = line->GetCommand();
    auto fileName   = line->GetLevelFilename();
    auto lineNumber = boost::lexical_cast<std::string>(line->GetLineNumber());
    std::string msg = "Unknown command '" + command + "' (in " + fileName + ":" + lineNumber + ")";
    throw std::runtime_error(msg);
}

void ThrowUnusedArg(CLevelParserLine* line, std::string arg, std::string matcherPath, int matcherLine)
{
    auto command    = line->GetCommand();
    auto fileName   = line->GetLevelFilename();
    auto lineNumber = boost::lexical_cast<std::string>(line->GetLineNumber());
    std::string msg = "Unknown argument '" + arg  + "' for command '" + command + "' (in " + fileName + ":" + lineNumber + ")\n" + "See supported arguments at " + basename(matcherPath.data()) + ":" + boost::lexical_cast<std::string>(matcherLine);
    throw std::runtime_error(msg);
}