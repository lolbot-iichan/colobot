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
 * \file object/object_part_filter.h
 * \brief ObjectPartFilter - enum for filtering out optional model and UI pieces
 */

#pragma once

class CObject;

// +---------+---------+---------+---------+-------------------+
// |Lightning|PlusExplo| Trainer |   Toy   |      Option       |
// +----+----+----+----+----+----+----+----+----+----+----+----+
// |    |    |    |    |    |    |    |    |    |    |    |    |
// +----+----+----+----+----+----+----+----+----+----+----+----+
// |00b : ANY|00b : ANY|00b : ANY|00b : ANY|  0-14   :  value  |
// |01b : ==0|01b : ==0|01b : ==0|01b : ==0|  1111b  :  ANY    |
// |10b : ==1|10b : ==1|10b : ==1|10b : ==1|         :         |
// |11b : ANY|11b : ANY|11b : ANY|11b : ANY|         :         |
// +---------+---------+---------+---------+-------------------+

#define OBJ_PART_OPTION_BITS 4

enum ObjectPartFilter
{
    PART_ALWAYS        = 0xFFFF,

    PART_OPTION_0      = 0,
    PART_OPTION_1      = 1,
    PART_OPTION_2      = 2,
    PART_OPTION_3      = 3,
    PART_OPTION_4      = 4,
    PART_OPTION_5      = 5,
    PART_OPTION_6      = 6,
    PART_OPTION_7      = 7,
    PART_OPTION_8      = 8,
    PART_OPTION_9      = 9,
    PART_OPTION_10     = 10,
    PART_OPTION_11     = 11,
    PART_OPTION_12     = 12,
    PART_OPTION_13     = 13,
    PART_OPTION_14     = 14,
    PART_OPTION_ANY    = 15,

    PART_TOY_FALSE          = 1 << OBJ_PART_OPTION_BITS << 0,
    PART_TOY_TRUE           = 1 << OBJ_PART_OPTION_BITS << 1,

    PART_TRAINER_FALSE      = 1 << OBJ_PART_OPTION_BITS << 2,
    PART_TRAINER_TRUE       = 1 << OBJ_PART_OPTION_BITS << 3,

    PART_PLUSEXPLORER_FALSE = 1 << OBJ_PART_OPTION_BITS << 4,
    PART_PLUSEXPLORER_TRUE  = 1 << OBJ_PART_OPTION_BITS << 5,

    PART_LIGHTNING_FALSE    = 1 << OBJ_PART_OPTION_BITS << 6,
    PART_LIGHTNING_TRUE     = 1 << OBJ_PART_OPTION_BITS << 7,
};

bool MatchObjectPartFilter(CObject* obj, int filter);
