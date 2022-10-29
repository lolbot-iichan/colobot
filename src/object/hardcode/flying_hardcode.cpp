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

#include "object/object_type.h"

#include "object/details/flying_details.h"

#include "object/hardcode/flying_hardcode.h"

bool CFlyingHardcodeCollection::IsFlying(ObjectType type)
{
    // TODO: Temporary hack
    if ( type == OBJECT_MOBILEfa || // WingedGrabber
         type == OBJECT_MOBILEfb || // WingedBuilder
         type == OBJECT_MOBILEfs || // WingedSniffer
         type == OBJECT_MOBILEfc || // WingedShooter
         type == OBJECT_MOBILEfi || // WingedOrgaShooter
         type == OBJECT_MOBILEft || // WingedTrainer
         type == OBJECT_HUMAN    || // Me
         type == OBJECT_TECH     || // Tech
         type == OBJECT_BEE      ||
         type == OBJECT_CONTROLLER) return true;
    return false;
}

bool CFlyingHardcodeCollection::GetNoFlyWithCargo(ObjectType type)
{
    if ( type == OBJECT_HUMAN ||
         type == OBJECT_TECH  ) return true;

    return false;
}

float CFlyingHardcodeCollection::GetLandingAccel(ObjectType type)
{
    if ( type == OBJECT_HUMAN ||
         type == OBJECT_TECH  )
    {
        return LANDING_ACCELh;
    }
    else
    {
        return LANDING_ACCEL;
    }
}

float CFlyingHardcodeCollection::GetFlyingEnergyFactor(ObjectType type)
{
    return 0.01f;
}

