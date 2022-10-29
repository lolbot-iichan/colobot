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

#include "math/sphere.h"

#include "object/object_type.h"

#include "object/hardcode/jostleable_hardcode.h"

bool CJostleableHardcodeCollection::IsJostleable(ObjectType type)
{
    if ( type == OBJECT_FLAGb ||
         type == OBJECT_FLAGr ||
         type == OBJECT_FLAGg ||
         type == OBJECT_FLAGy ||
         type == OBJECT_FLAGv ) return true;
    if ( type == OBJECT_PLANT0 ||
         type == OBJECT_PLANT1 ||
         type == OBJECT_PLANT2 ||
         type == OBJECT_PLANT3 ||
         type == OBJECT_PLANT4 ) return true;
    if ( type == OBJECT_PLANT5 ||
         type == OBJECT_PLANT6 ||
         type == OBJECT_PLANT7 ) return true;
    if ( type == OBJECT_PLANT10 ||
         type == OBJECT_PLANT11 ||
         type == OBJECT_PLANT12 ||
         type == OBJECT_PLANT13 ||
         type == OBJECT_PLANT14 ) return true;
    if ( type == OBJECT_PLANT15 ||
         type == OBJECT_PLANT16 ||
         type == OBJECT_PLANT17 ||
         type == OBJECT_PLANT18 ) return true;
    if ( type == OBJECT_PLANT19 ) return true;
    if ( type == OBJECT_MUSHROOM1 ) return true;
    if ( type == OBJECT_MUSHROOM2 ) return true;
    if ( type == OBJECT_APOLLO3 ) return true;

    return false;
}

bool CJostleableHardcodeCollection::IsJostleableSpecial(ObjectType type)
{
    if ( type == OBJECT_FLAGb ||
         type == OBJECT_FLAGr ||
         type == OBJECT_FLAGg ||
         type == OBJECT_FLAGy ||
         type == OBJECT_FLAGv ) return true;
    return false;
}

float CJostleableHardcodeCollection::GetJostleFactor(ObjectType type)
{
    if ( type >= OBJECT_PLANT5 &&
         type <= OBJECT_PLANT7 )  // clover?
    {
        return 3.0f;
    }
    return 1.0f;
}

Math::Sphere CJostleableHardcodeCollection::GetJostlingSphere(ObjectType type)
{
    if ( type == OBJECT_FLAGb ||
         type == OBJECT_FLAGr ||
         type == OBJECT_FLAGg ||
         type == OBJECT_FLAGy ||
         type == OBJECT_FLAGv )
    {
        return (Math::Sphere(glm::vec3(0.0f, 4.0f, 0.0f), 1.0f));
    }

    if ( type == OBJECT_PLANT0 ||
         type == OBJECT_PLANT1 ||
         type == OBJECT_PLANT2 ||
         type == OBJECT_PLANT3 ||
         type == OBJECT_PLANT4 )  // standard?
    {
        return (Math::Sphere(glm::vec3(0.0f, 0.0f, 0.0f), 8.0f));
    }

    if ( type == OBJECT_PLANT5 ||
         type == OBJECT_PLANT6 ||
         type == OBJECT_PLANT7 )  // clover?
    {
        return (Math::Sphere(glm::vec3(0.0f, 0.0f, 0.0f), 4.0f));
    }

    if ( type == OBJECT_PLANT10 ||
         type == OBJECT_PLANT11 ||
         type == OBJECT_PLANT12 ||
         type == OBJECT_PLANT13 ||
         type == OBJECT_PLANT14 )  // succulent?
    {
        return (Math::Sphere(glm::vec3(0.0f, 4.0f, 0.0f), 8.0f));
    }

    if ( type == OBJECT_PLANT15 ||
         type == OBJECT_PLANT16 ||
         type == OBJECT_PLANT17 ||
         type == OBJECT_PLANT18 )  // fern?
    {
        return (Math::Sphere(glm::vec3(0.0f, 0.0f, 0.0f), 8.0f));
    }

    if ( type == OBJECT_PLANT19 )  // fern?
    {
        return (Math::Sphere(glm::vec3(0.0f, 0.0f, 0.0f), 8.0f));
    }

    if ( type == OBJECT_MUSHROOM1 )
    {
        return (Math::Sphere(glm::vec3(0.0f, 3.0f, 0.0f), 5.5f));
    }

    if ( type == OBJECT_MUSHROOM2 )
    {
        return (Math::Sphere(glm::vec3(0.0f, 4.0f, 0.0f), 5.5f));
    }

    if ( type == OBJECT_APOLLO3 )  // flag?
    {
        return (Math::Sphere(glm::vec3(0.0f, 4.0f, 0.0f), 1.0f));
    }

    return Math::Sphere();
}
