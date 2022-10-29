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
 * \file object/object_part_filter.cpp
 * \brief MatchObjectPartFilter - implementation of optional parts filter
 */

#include "object/object.h"
#include "object/object_part_filter.h"
#include "object/old_object.h"

#define MATCH_BOOL_FILTERS(T,F,C) {bool t=(filter&T),f=(filter&F);if(!t!=!f){bool c=(C);if(!c!=!t) return false;}}

bool MatchObjectPartFilter(CObject* obj, int filter)
{
    if ( obj == nullptr )
        return false;

    if ( filter == PART_ALWAYS )
        return true;

    if ( obj->Implements(ObjectInterfaceType::Old) )
    {
        COldObject* old = dynamic_cast<COldObject*>(obj);

        int option = filter & PART_OPTION_ANY;
        if (option != PART_OPTION_ANY && option != old->GetOption())
            return false;
    
        MATCH_BOOL_FILTERS(PART_TOY_TRUE, PART_TOY_FALSE, old->GetToy());
        MATCH_BOOL_FILTERS(PART_TRAINER_TRUE, PART_TRAINER_FALSE, old->GetTrainer() || old->GetPlusTrainer());
        MATCH_BOOL_FILTERS(PART_PLUSEXPLORER_TRUE, PART_PLUSEXPLORER_FALSE, old->GetPlusExplorer());
    }

    return true;
}
