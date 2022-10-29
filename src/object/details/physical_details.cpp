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
 * \file object/details/physical_details.cpp
 * \brief CObjectPhysicalDetails - set of tweaks for Physical objects
 */

#include "level/parser/parser.h"

#include "object/details/macro.h"
#include "object/details/physical_details.h"

#include "object/hardcode/physical_hardcode.h"

void CObjectPhysicalDetails::ReadHardcode(ObjectType type)
{
    squashing         = CPhysicalHardcodeCollection::GetSquashing(type);
    collisionSoftness = CPhysicalHardcodeCollection::GetCollisionSoftness(type);
    height            = CPhysicalHardcodeCollection::GetHeight(type);
    noBuildRadius     = CPhysicalHardcodeCollection::GetNoBuildRadius(type);
    hasBuildMargin    = CPhysicalHardcodeCollection::GetBuildMargin(type);
    isBulletWall      = CPhysicalHardcodeCollection::GetBulletWall(type);

    explosive         = CPhysicalHardcodeCollection::GetExlosive(type);
    hotpoint          = CPhysicalHardcodeCollection::GetHotPoint(type);
    approaching       = CPhysicalHardcodeCollection::GetApproaching(type);
}

bool CObjectPhysicalDetails::Read(CLevelParserLine* line)
{
    READ_LINE( "SetObjectPhysical" );
    READ_ARG( "squashing",         AsBool,  squashing         );
    READ_ARG( "collisionSoftness", AsFloat, collisionSoftness );
    READ_ARG( "height",            AsFloat, height            );
    READ_ARG( "noBuildRadius",     AsFloat, noBuildRadius     );
    READ_ARG( "hasBuildMargin",    AsBool,  hasBuildMargin    );
    READ_ARG( "isBulletWall",      AsBool,  isBulletWall      );
    READ_ARG( "gotoSmallDistance", AsBool,  approaching.gotoSmallDistance );
    READ_ARG( "gotoPowerCell",     AsBool,  approaching.gotoPowerCell     );
    READ_END();

    READ_LINE( "SetObjectPhysicalExplosive" );
    READ_ARG( "enabled",        AsBool,  explosive.enabled        );
    READ_ARG( "collisionForce", AsFloat, explosive.collisionForce );
    READ_END();

    READ_LINE( "SetObjectPhysicalHotPoint" );
    READ_ARG( "enabled",    AsBool,  hotpoint.enabled    );
    READ_ARG( "partNum",    AsInt,   hotpoint.partNum    );
    READ_ARG( "position",   AsPoint, hotpoint.position   );
    READ_ARG( "suppl",      AsFloat, hotpoint.suppl      );
    READ_ARG( "dxTake",     AsBool,  hotpoint.dxTake     );
    READ_ARG( "dxOther",    AsBool,  hotpoint.dxOther    );
    READ_ARG( "dxDistance", AsBool,  hotpoint.dxDistance );
    READ_ARG( "dxSuppl",    AsBool,  hotpoint.dxSuppl    );
    READ_ARG( "flyingOnly", AsBool,  hotpoint.flyingOnly );
    READ_END();

    return false;
}

void CObjectPhysicalDetails::Write(CLevelParser* parser, ObjectType type)
{
    WRITE_LINE( "SetObjectPhysical" );
    WRITE_ARG( "squashing",         AsBool,  squashing         );
    WRITE_ARG( "collisionSoftness", AsFloat, collisionSoftness );
    WRITE_ARG( "height",            AsFloat, height            );
    WRITE_ARG( "noBuildRadius",     AsFloat, noBuildRadius     );
    WRITE_ARG( "hasBuildMargin",    AsBool,  hasBuildMargin    );
    WRITE_ARG( "isBulletWall",      AsBool,  isBulletWall      );
    WRITE_ARG( "gotoSmallDistance", AsBool,  approaching.gotoSmallDistance );
    WRITE_ARG( "gotoPowerCell",     AsBool,  approaching.gotoPowerCell     );
    WRITE_END();

    WRITE_LINE( "SetObjectPhysicalExplosive" );
    WRITE_ARG( "enabled",        AsBool,  explosive.enabled        );
    WRITE_ARG( "collisionForce", AsFloat, explosive.collisionForce );
    WRITE_END();

    WRITE_LINE( "SetObjectPhysicalHotPoint" );
    WRITE_ARG( "enabled",    AsBool,  hotpoint.enabled    );
    WRITE_ARG( "partNum",    AsInt,   hotpoint.partNum    );
    WRITE_ARG( "position",   AsPoint, hotpoint.position   );
    WRITE_ARG( "suppl",      AsFloat, hotpoint.suppl      );
    WRITE_ARG( "dxTake",     AsBool,  hotpoint.dxTake     );
    WRITE_ARG( "dxOther",    AsBool,  hotpoint.dxOther    );
    WRITE_ARG( "dxDistance", AsBool,  hotpoint.dxDistance );
    WRITE_ARG( "dxSuppl",    AsBool,  hotpoint.dxSuppl    );
    WRITE_ARG( "flyingOnly", AsBool,  hotpoint.flyingOnly );
    WRITE_END();
}
