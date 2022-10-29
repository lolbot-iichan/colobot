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

#include "object/details/physical_details.h"

#include "object/hardcode/physical_hardcode.h"

bool  CPhysicalHardcodeCollection::GetSquashing(ObjectType type)
{
    if ( type == OBJECT_MOBILErt ||
         type == OBJECT_MOBILErc ||
         type == OBJECT_MOBILErr ||
         type == OBJECT_MOBILErs ||
         type == OBJECT_MOBILErp  )   return true;

    return false;
}

float  CPhysicalHardcodeCollection::GetCollisionSoftness(ObjectType type)
{
   if (  type == OBJECT_DERRICK  ||
         type == OBJECT_FACTORY  ||
         type == OBJECT_STATION  ||
         type == OBJECT_CONVERT  ||
         type == OBJECT_REPAIR   ||
         type == OBJECT_DESTROYER||
         type == OBJECT_TOWER    ||
         type == OBJECT_RESEARCH ||
         type == OBJECT_RADAR    ||
         type == OBJECT_INFO     ||
         type == OBJECT_ENERGY   ||
         type == OBJECT_LABO     ||
         type == OBJECT_NUCLEAR  ||
         type == OBJECT_PARA     ||
         type == OBJECT_SAFE     ||
         type == OBJECT_HUSTON   )  // building?
    {
        return 200.0f;
    }
    else if ( type == OBJECT_MOTHER ||
              type == OBJECT_ANT    ||
              type == OBJECT_SPIDER ||
              type == OBJECT_BEE    ||
              type == OBJECT_WORM   )  // insect?
    {
        return 400.0f;
    }
    else
    if ( type == OBJECT_STONE ||
         type == OBJECT_METAL )
    {
        return 500.0f;
    }
    else
    if ( type == OBJECT_URANIUM ||
         type == OBJECT_POWER   ||
         type == OBJECT_ATOMIC  )
    {
        return 100.0f;
    }
    else
    {
        return 200.0f;
    }
}

CObjectExplosivePhysicalDetails  CPhysicalHardcodeCollection::GetExlosive(ObjectType type)
{
    CObjectExplosivePhysicalDetails result;

    if ( type == OBJECT_TNT      ) return {true, 10.0f}; // TNT
    if ( type == OBJECT_MOBILEtg ) return {true, 10.0f}; // TargetBot (something running into it)
    if ( type == OBJECT_BOMB     ) return {true,  0.0f}; // Mine
    
    return result;
}

CObjectHotPointPhysicalDetails  CPhysicalHardcodeCollection::GetHotPoint(ObjectType type)
{
    CObjectHotPointPhysicalDetails result = {false};

    if ( type == OBJECT_DERRICK )
        result = {true, 0, {8.0f, 0.0f, 0.0f}, 4.0f, true, false, true, true};

    if ( type == OBJECT_CONVERT )
        result = {true, 0, {0.0f, 0.0f, 0.0f}, 4.0f, true, false, true, true};

    if ( type == OBJECT_RESEARCH )
        result = {true, 0, {10.0f, 0.0f, 0.0f}, 2.5f, true, true, true, true};

    if ( type == OBJECT_ENERGY )
        result = {true, 0, {6.0f, 0.0f, 0.0f}, 6.0f, true, true, true, false};

    if ( type == OBJECT_TOWER )
        result = {true, 0, {5.0f, 0.0f, 0.0f}, 4.0f, true, true, true, true};

    if ( type == OBJECT_LABO )
        result = {true, 0, {6.0f, 0.0f, 0.0f}, 6.0f, true, true, true, false};

    if ( type == OBJECT_NUCLEAR )
        result = {true, 0, {22.0f, 0.0f, 0.0f}, 4.0f, true, true, true, true};

    if ( type == OBJECT_FACTORY )
        result = {true, 0, {4.0f, 0.0f, 0.0f}, 6.0f, true, false, true, true};

    if ( type == OBJECT_STATION )
        result = {true, 0, {4.0f, 0.0f, 0.0f}, 4.0f, true, false, false, false};

    if ( type == OBJECT_REPAIR )
        result = {true, 0, {4.0f, 0.0f, 0.0f}, 4.0f, true, false, false, false};

    if ( type == OBJECT_PARA )
        result = {true, 0, {0.0f, 0.0f, 0.0f}, 20.0f, true, false, false, true, true};

    return result;
}

CObjectApproachingPhysicalDetails  CPhysicalHardcodeCollection::GetApproaching(ObjectType type)
{
    CObjectApproachingPhysicalDetails result = {false, false};

    if ( type == OBJECT_STONE   || // IsTransportable
         type == OBJECT_URANIUM ||
         type == OBJECT_BULLET  ||
         type == OBJECT_METAL   ||
         type == OBJECT_POWER   ||
         type == OBJECT_ATOMIC  ||
         type == OBJECT_BBOX    ||
         type == OBJECT_KEYa    ||
         type == OBJECT_KEYb    ||
         type == OBJECT_KEYc    ||
         type == OBJECT_KEYd    ||
         type == OBJECT_TNT     ||
         type == OBJECT_RUINmobilew1 || // TODO: CRecoverableObject?
         type == OBJECT_RUINmobilew2 ||
         type == OBJECT_RUINmobilet1 ||
         type == OBJECT_RUINmobilet2 ||
         type == OBJECT_RUINmobiler1 ||
         type == OBJECT_RUINmobiler2 ||
         type == OBJECT_BASE         )
    {
        result = {true, false};
    }

    if ( type == OBJECT_MOBILEfa ||
         type == OBJECT_MOBILEta ||
         type == OBJECT_MOBILEwa ||
         type == OBJECT_MOBILEia ||
         type == OBJECT_MOBILEfb ||
         type == OBJECT_MOBILEtb ||
         type == OBJECT_MOBILEwb ||
         type == OBJECT_MOBILEib ||
         type == OBJECT_MOBILEfs ||
         type == OBJECT_MOBILEts ||
         type == OBJECT_MOBILEws ||
         type == OBJECT_MOBILEis ||
         type == OBJECT_MOBILEfc ||
         type == OBJECT_MOBILEtc ||
         type == OBJECT_MOBILEwc ||
         type == OBJECT_MOBILEic ||
         type == OBJECT_MOBILEfi ||
         type == OBJECT_MOBILEti ||
         type == OBJECT_MOBILEwi ||
         type == OBJECT_MOBILEii ||
         type == OBJECT_MOBILErt ||
         type == OBJECT_MOBILErc ||
         type == OBJECT_MOBILErr ||
         type == OBJECT_MOBILErs ||
         type == OBJECT_MOBILEsa ||
         type == OBJECT_MOBILEtg ||
         type == OBJECT_MOBILEft ||
         type == OBJECT_MOBILEtt ||
         type == OBJECT_MOBILEwt ||
         type == OBJECT_MOBILEit ||
         type == OBJECT_MOBILErp ||
         type == OBJECT_MOBILEst ||
         type == OBJECT_MOBILEdr )
    {
        result = {false, true};
    }

    return result;
}

float  CPhysicalHardcodeCollection::GetHeight(ObjectType type)
{
    if ( type == OBJECT_DERRICK  )  return 35.0f;
    if ( type == OBJECT_FACTORY  )  return 28.0f;
    if ( type == OBJECT_REPAIR   )  return 30.0f;
    if ( type == OBJECT_STATION  )  return 13.0f;
    if ( type == OBJECT_CONVERT  )  return 20.0f;
    if ( type == OBJECT_TOWER    )  return 30.0f;
    if ( type == OBJECT_RESEARCH )  return 22.0f;
    if ( type == OBJECT_RADAR    )  return 19.0f;
    if ( type == OBJECT_ENERGY   )  return 20.0f;
    if ( type == OBJECT_LABO     )  return 16.0f;
    if ( type == OBJECT_NUCLEAR  )  return 40.0f;
    if ( type == OBJECT_PARA     )  return 68.0f;
    if ( type == OBJECT_INFO     )  return 19.0f;
    if ( type == OBJECT_SAFE     )  return 16.0f;
    if ( type == OBJECT_DESTROYER)  return 35.0f;
    if ( type == OBJECT_HUSTON   )  return 45.0f;

    return 0.0f;
}

float  CPhysicalHardcodeCollection::GetNoBuildRadius(ObjectType type)
{
    if ( type == OBJECT_BASE ) return 80.0f;

    return 0.0f;
}

bool  CPhysicalHardcodeCollection::GetBuildMargin(ObjectType type)
{
    if ( type == OBJECT_DERRICK  ||
         type == OBJECT_FACTORY  ||
         type == OBJECT_STATION  ||
         type == OBJECT_CONVERT  ||
         type == OBJECT_REPAIR   ||
         type == OBJECT_TOWER    ||
         type == OBJECT_RESEARCH ||
         type == OBJECT_RADAR    ||
         type == OBJECT_ENERGY   ||
         type == OBJECT_LABO     ||
         type == OBJECT_NUCLEAR  ||
         type == OBJECT_DESTROYER||
         type == OBJECT_START    ||
         type == OBJECT_END      ||
         type == OBJECT_INFO     ||
         type == OBJECT_PARA     ||
         type == OBJECT_SAFE     ||
         type == OBJECT_HUSTON   ) return true;

    return false;
}

bool  CPhysicalHardcodeCollection::GetBulletWall(ObjectType type)
{
    if ( type == OBJECT_BARRICADE0 ||
         type == OBJECT_BARRICADE1 )
    {
        return true;
    }
    return false;
}
