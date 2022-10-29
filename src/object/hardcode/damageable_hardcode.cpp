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

#include "graphics/engine/pyro_type.h"

#include "object/object_type.h"

#include "object/hardcode/damageable_hardcode.h"

/* Macro to mark which texts are translatable by gettext
 * It doesn't do anything at compile-time, as all texts represented here are used later
 * in explicit call to gettext(), but it is used by xgettext executable to filter extracted
 * texts from this file.
 */
#define TR(x) x

/* Please run `cmake --build <path_to_build_folder> --target update-pot`
 * after changing this file in order to update translation files. Thank you.
 */

bool CDamageableHardcodeCollection::IsDamageable(ObjectType type)
{
    // TODO: Hacking some more
    if ( type == OBJECT_MOBILEtg ||
         type == OBJECT_STONE    ||
         type == OBJECT_METAL    ||
         type == OBJECT_URANIUM  ||
         type == OBJECT_POWER    ||
         type == OBJECT_ATOMIC   ||
         type == OBJECT_TNT      ||
         type == OBJECT_BULLET   ||
         type == OBJECT_EGG      ||
         type == OBJECT_BOMB     ||
         type == OBJECT_ANT      ||
         type == OBJECT_WORM     ||
         type == OBJECT_SPIDER   ||
         type == OBJECT_BEE      ||
         type == OBJECT_TEEN28    )
    {
        return true;
    }
    else if (type == OBJECT_HUMAN ||
         type == OBJECT_MOBILEfa ||
         type == OBJECT_MOBILEta ||
         type == OBJECT_MOBILEwa ||
         type == OBJECT_MOBILEia ||
         type == OBJECT_MOBILEfb ||
         type == OBJECT_MOBILEtb ||
         type == OBJECT_MOBILEwb ||
         type == OBJECT_MOBILEib ||
         type == OBJECT_MOBILEfc ||
         type == OBJECT_MOBILEtc ||
         type == OBJECT_MOBILEwc ||
         type == OBJECT_MOBILEic ||
         type == OBJECT_MOBILEfi ||
         type == OBJECT_MOBILEti ||
         type == OBJECT_MOBILEwi ||
         type == OBJECT_MOBILEii ||
         type == OBJECT_MOBILEfs ||
         type == OBJECT_MOBILEts ||
         type == OBJECT_MOBILEws ||
         type == OBJECT_MOBILEis ||
         type == OBJECT_MOBILErt ||
         type == OBJECT_MOBILErc ||
         type == OBJECT_MOBILErr ||
         type == OBJECT_MOBILErs ||
         type == OBJECT_MOBILEsa ||
         type == OBJECT_MOBILEft ||
         type == OBJECT_MOBILEtt ||
         type == OBJECT_MOBILEwt ||
         type == OBJECT_MOBILEit ||
         type == OBJECT_MOBILErp ||
         type == OBJECT_MOBILEst ||
         type == OBJECT_FACTORY  ||
         type == OBJECT_REPAIR   ||
         type == OBJECT_DESTROYER||
         type == OBJECT_DERRICK  ||
         type == OBJECT_STATION  ||
         type == OBJECT_CONVERT  ||
         type == OBJECT_TOWER    ||
         type == OBJECT_RESEARCH ||
         type == OBJECT_RADAR    ||
         type == OBJECT_INFO     ||
         type == OBJECT_ENERGY   ||
         type == OBJECT_LABO     ||
         type == OBJECT_NUCLEAR  ||
         type == OBJECT_SAFE     ||
         type == OBJECT_PARA     ||
         type == OBJECT_MOTHER    )
    {
        return true;
    }
    else if (type == OBJECT_HUSTON ||
             type == OBJECT_BASE    )
    {
        return true;
    }
    else if (type == OBJECT_RUINmobilew1 ||
             type == OBJECT_RUINmobilew2 ||
             type == OBJECT_RUINmobilet1 ||
             type == OBJECT_RUINmobilet2 ||
             type == OBJECT_RUINmobiler1 ||
             type == OBJECT_RUINmobiler2 ||
             type == OBJECT_RUINfactory  ||
             type == OBJECT_RUINdoor     ||
             type == OBJECT_RUINsupport  ||
             type == OBJECT_RUINradar    ||
             type == OBJECT_RUINconvert   )
    {
        return true;
    }
    else if (type == OBJECT_PLANT0  ||
             type == OBJECT_PLANT1  ||
             type == OBJECT_PLANT2  ||
             type == OBJECT_PLANT3  ||
             type == OBJECT_PLANT4  ||
             type == OBJECT_PLANT15 ||
             type == OBJECT_PLANT16 ||
             type == OBJECT_PLANT17 ||
             type == OBJECT_PLANT18 )
    {
        return true;
    }

    return false;
}

Gfx::PyroType CDamageableHardcodeCollection::GetDamageEffect(ObjectType type)
{
    if ( type == OBJECT_HUMAN )
    {
        return Gfx::PT_SHOTH;
    }
    else if ( type == OBJECT_MOTHER )
    {
        return Gfx::PT_SHOTM;
    }

    return Gfx::PT_SHOTT;
}

bool CDamageableHardcodeCollection::IsImmuneToFireballs(ObjectType type)
{
    if ( type == OBJECT_MOTHER  ) return true; // AlienQueen can be destroyed only by PhazerShooter
    if ((type == OBJECT_BOMB         ||
         type == OBJECT_RUINmobilew1 ||
         type == OBJECT_RUINmobilew2 ||
         type == OBJECT_RUINmobilet1 ||
         type == OBJECT_RUINmobilet2 ||
         type == OBJECT_RUINmobiler1 ||
         type == OBJECT_RUINmobiler2 ||
         type == OBJECT_RUINfactory  ||
         type == OBJECT_RUINdoor     ||
         type == OBJECT_RUINsupport  ||
         type == OBJECT_RUINradar    ||
         type == OBJECT_RUINconvert  )) return true; // Mines and ruins can't be destroyed by shooting

    if ( type == OBJECT_URANIUM ) return true; // UraniumOre is not destroyable by shooting or aliens (see #777)
    if ( type == OBJECT_STONE   ) return true; // TitaniumOre is not destroyable either

    return false;
}

bool CDamageableHardcodeCollection::IsImmuneToInsects(ObjectType type)
{
    if ( type == OBJECT_MOTHER  ) return true; // AlienQueen can be destroyed only by PhazerShooter
    if ((type == OBJECT_BOMB         ||
         type == OBJECT_RUINmobilew1 ||
         type == OBJECT_RUINmobilew2 ||
         type == OBJECT_RUINmobilet1 ||
         type == OBJECT_RUINmobilet2 ||
         type == OBJECT_RUINmobiler1 ||
         type == OBJECT_RUINmobiler2 ||
         type == OBJECT_RUINfactory  ||
         type == OBJECT_RUINdoor     ||
         type == OBJECT_RUINsupport  ||
         type == OBJECT_RUINradar    ||
         type == OBJECT_RUINconvert  )) return true; // Mines and ruins can't be destroyed by shooting

    if ( type == OBJECT_ANT    ||
         type == OBJECT_SPIDER ||
         type == OBJECT_BEE    ||
         type == OBJECT_WORM   ||
         type == OBJECT_NEST   ||
         type == OBJECT_BULLET ||
         type == OBJECT_EGG    ||
         type == OBJECT_TEEN28 ||
         type == OBJECT_TEEN31  ) return true;

    if ( type == OBJECT_URANIUM ) return true; // UraniumOre is not destroyable by shooting or aliens (see #777)
    if ( type == OBJECT_STONE   ) return true; // TitaniumOre is not destroyable either

    return false;
}

bool CDamageableHardcodeCollection::IsImmuneToPhazers(ObjectType type)
{
    if ((type == OBJECT_BOMB         ||
         type == OBJECT_RUINmobilew1 ||
         type == OBJECT_RUINmobilew2 ||
         type == OBJECT_RUINmobilet1 ||
         type == OBJECT_RUINmobilet2 ||
         type == OBJECT_RUINmobiler1 ||
         type == OBJECT_RUINmobiler2 ||
         type == OBJECT_RUINfactory  ||
         type == OBJECT_RUINdoor     ||
         type == OBJECT_RUINsupport  ||
         type == OBJECT_RUINradar    ||
         type == OBJECT_RUINconvert  )) return true; // Mines and ruins can't be destroyed by shooting

    return false;
}

bool CDamageableHardcodeCollection::IsImmuneToTowerRays(ObjectType type)
{
    if ( type == OBJECT_MOTHER  ) return true; // AlienQueen can be destroyed only by PhazerShooter
    if ((type == OBJECT_BOMB         ||
         type == OBJECT_RUINmobilew1 ||
         type == OBJECT_RUINmobilew2 ||
         type == OBJECT_RUINmobilet1 ||
         type == OBJECT_RUINmobilet2 ||
         type == OBJECT_RUINmobiler1 ||
         type == OBJECT_RUINmobiler2 ||
         type == OBJECT_RUINfactory  ||
         type == OBJECT_RUINdoor     ||
         type == OBJECT_RUINsupport  ||
         type == OBJECT_RUINradar    ||
         type == OBJECT_RUINconvert  )) return true; // Mines and ruins can't be destroyed by shooting

    if (type == OBJECT_MOBILEtg ||
     type == OBJECT_TEEN28   ||
     type == OBJECT_TEEN31   ||
     type == OBJECT_ANT      ||
     type == OBJECT_SPIDER   ||
     type == OBJECT_BEE      ||
     type == OBJECT_WORM     ||
     type == OBJECT_NEST) return false;

     return true;
}

bool CDamageableHardcodeCollection::IsImmuneToOrgashooters(ObjectType type)
{
    if ( type == OBJECT_MOTHER )  return true; // AlienQueen can be destroyed only by PhazerShooter
    if ((type == OBJECT_BOMB         ||
         type == OBJECT_RUINmobilew1 ||
         type == OBJECT_RUINmobilew2 ||
         type == OBJECT_RUINmobilet1 ||
         type == OBJECT_RUINmobilet2 ||
         type == OBJECT_RUINmobiler1 ||
         type == OBJECT_RUINmobiler2 ||
         type == OBJECT_RUINfactory  ||
         type == OBJECT_RUINdoor     ||
         type == OBJECT_RUINsupport  ||
         type == OBJECT_RUINradar    ||
         type == OBJECT_RUINconvert  )) return true; // Mines and ruins can't be destroyed by shooting

    if ( type == OBJECT_URANIUM ) return true; // UraniumOre is not destroyable by shooting or aliens (see #777)
    if ( type == OBJECT_STONE   ) return true; // TitaniumOre is not destroyable either

    return false;
}

bool CDamageableHardcodeCollection::IsImmuneToOrgaballs(ObjectType type)
{
    if ( type == OBJECT_MOTHER )  return true; // AlienQueen can be destroyed only by PhazerShooter
    if ((type == OBJECT_BOMB         ||
         type == OBJECT_RUINmobilew1 ||
         type == OBJECT_RUINmobilew2 ||
         type == OBJECT_RUINmobilet1 ||
         type == OBJECT_RUINmobilet2 ||
         type == OBJECT_RUINmobiler1 ||
         type == OBJECT_RUINmobiler2 ||
         type == OBJECT_RUINfactory  ||
         type == OBJECT_RUINdoor     ||
         type == OBJECT_RUINsupport  ||
         type == OBJECT_RUINradar    ||
         type == OBJECT_RUINconvert  )) return true; // Mines and ruins can't be destroyed by shooting

    if ( type == OBJECT_URANIUM ) return true; // UraniumOre is not destroyable by shooting or aliens (see #777)
    if ( type == OBJECT_STONE   ) return true; // TitaniumOre is not destroyable either

    return false;
}

bool CDamageableHardcodeCollection::IsImmuneToExplosive(ObjectType type)
{
    if ( type == OBJECT_MOTHER )  return true; // AlienQueen can be destroyed only by PhazerShooter

    return false;
}

bool CDamageableHardcodeCollection::IsImmuneToCollisionsByOthers(ObjectType type)
{
    if ( type == OBJECT_MOTHER )  return true; // AlienQueen can be destroyed only by PhazerShooter
    if ((type == OBJECT_BOMB         ||
         type == OBJECT_RUINmobilew1 ||
         type == OBJECT_RUINmobilew2 ||
         type == OBJECT_RUINmobilet1 ||
         type == OBJECT_RUINmobilet2 ||
         type == OBJECT_RUINmobiler1 ||
         type == OBJECT_RUINmobiler2 ||
         type == OBJECT_RUINfactory  ||
         type == OBJECT_RUINdoor     ||
         type == OBJECT_RUINsupport  ||
         type == OBJECT_RUINradar    ||
         type == OBJECT_RUINconvert  )) return true; // Mines and ruins can't be destroyed by shooting

    if ( type == OBJECT_METAL ) return true;
    if ( type == OBJECT_POWER ) return true;
    if ( type == OBJECT_NUCLEAR ) return true;

    if ( type == OBJECT_HUMAN    ||
         type == OBJECT_MOBILEwa ||
         type == OBJECT_MOBILEta ||
         type == OBJECT_MOBILEfa ||
         type == OBJECT_MOBILEia ||
         type == OBJECT_MOBILEwb ||
         type == OBJECT_MOBILEtb ||
         type == OBJECT_MOBILEfb ||
         type == OBJECT_MOBILEib ||
         type == OBJECT_MOBILEwc ||
         type == OBJECT_MOBILEtc ||
         type == OBJECT_MOBILEfc ||
         type == OBJECT_MOBILEic ||
         type == OBJECT_MOBILEwi ||
         type == OBJECT_MOBILEti ||
         type == OBJECT_MOBILEfi ||
         type == OBJECT_MOBILEii ||
         type == OBJECT_MOBILEws ||
         type == OBJECT_MOBILEts ||
         type == OBJECT_MOBILEfs ||
         type == OBJECT_MOBILEis ||
         type == OBJECT_MOBILErt ||
         type == OBJECT_MOBILErc ||
         type == OBJECT_MOBILErr ||
         type == OBJECT_MOBILErs ||
         type == OBJECT_MOBILEsa ||
         type == OBJECT_MOBILEwt ||
         type == OBJECT_MOBILEtt ||
         type == OBJECT_MOBILEft ||
         type == OBJECT_MOBILEit ||
         type == OBJECT_MOBILErp ||
         type == OBJECT_MOBILEst ||
         type == OBJECT_MOBILEdr ||
         type == OBJECT_APOLLO2  ) return false;

    return false;
}

bool CDamageableHardcodeCollection::IsImmuneToCollisionsByItself(ObjectType type)
{
    if ( type == OBJECT_HUMAN    ||
         type == OBJECT_MOBILEwa ||
         type == OBJECT_MOBILEta ||
         type == OBJECT_MOBILEfa ||
         type == OBJECT_MOBILEia ||
         type == OBJECT_MOBILEwb ||
         type == OBJECT_MOBILEtb ||
         type == OBJECT_MOBILEfb ||
         type == OBJECT_MOBILEib ||
         type == OBJECT_MOBILEwc ||
         type == OBJECT_MOBILEtc ||
         type == OBJECT_MOBILEfc ||
         type == OBJECT_MOBILEic ||
         type == OBJECT_MOBILEwi ||
         type == OBJECT_MOBILEti ||
         type == OBJECT_MOBILEfi ||
         type == OBJECT_MOBILEii ||
         type == OBJECT_MOBILEws ||
         type == OBJECT_MOBILEts ||
         type == OBJECT_MOBILEfs ||
         type == OBJECT_MOBILEis ||
         type == OBJECT_MOBILErt ||
         type == OBJECT_MOBILErc ||
         type == OBJECT_MOBILErr ||
         type == OBJECT_MOBILErs ||
         type == OBJECT_MOBILEsa ||
         type == OBJECT_MOBILEwt ||
         type == OBJECT_MOBILEtt ||
         type == OBJECT_MOBILEft ||
         type == OBJECT_MOBILEit ||
         type == OBJECT_MOBILErp ||
         type == OBJECT_MOBILEst ||
         type == OBJECT_MOBILEdr ||
         type == OBJECT_APOLLO2  ) return false;

    return true;
}

bool CDamageableHardcodeCollection::IsImmuneToLightning(ObjectType type)
{
    if ( type == OBJECT_MOTHER )  return true;
    if ((type == OBJECT_BOMB         ||
         type == OBJECT_RUINmobilew1 ||
         type == OBJECT_RUINmobilew2 ||
         type == OBJECT_RUINmobilet1 ||
         type == OBJECT_RUINmobilet2 ||
         type == OBJECT_RUINmobiler1 ||
         type == OBJECT_RUINmobiler2 ||
         type == OBJECT_RUINfactory  ||
         type == OBJECT_RUINdoor     ||
         type == OBJECT_RUINsupport  ||
         type == OBJECT_RUINradar    ||
         type == OBJECT_RUINconvert  )) return true; // Mines and ruins can't be destroyed by shooting

    return GetLightningRodHeight(type) != 0.0f;
}

bool CDamageableHardcodeCollection::IsImmuneToFall(ObjectType type)
{
    if ( type == OBJECT_MOTHER )  return true;
    if ((type == OBJECT_BOMB         ||
         type == OBJECT_RUINmobilew1 ||
         type == OBJECT_RUINmobilew2 ||
         type == OBJECT_RUINmobilet1 ||
         type == OBJECT_RUINmobilet2 ||
         type == OBJECT_RUINmobiler1 ||
         type == OBJECT_RUINmobiler2 ||
         type == OBJECT_RUINfactory  ||
         type == OBJECT_RUINdoor     ||
         type == OBJECT_RUINsupport  ||
         type == OBJECT_RUINradar    ||
         type == OBJECT_RUINconvert  )) return true; // Mines and ruins can't be destroyed by shooting

    return false;
}

bool CDamageableHardcodeCollection::IsImmuneToSpiders(ObjectType type)
{
    if ( type == OBJECT_MOTHER )  return true;
    if ((type == OBJECT_BOMB         ||
         type == OBJECT_RUINmobilew1 ||
         type == OBJECT_RUINmobilew2 ||
         type == OBJECT_RUINmobilet1 ||
         type == OBJECT_RUINmobilet2 ||
         type == OBJECT_RUINmobiler1 ||
         type == OBJECT_RUINmobiler2 ||
         type == OBJECT_RUINfactory  ||
         type == OBJECT_RUINdoor     ||
         type == OBJECT_RUINsupport  ||
         type == OBJECT_RUINradar    ||
         type == OBJECT_RUINconvert  )) return true; // Mines and ruins can't be destroyed by shooting

    if ( type == OBJECT_ANT    ||
         type == OBJECT_SPIDER ||
         type == OBJECT_BEE    ||
         type == OBJECT_WORM   ||
         type == OBJECT_NEST   ||
         type == OBJECT_BULLET ||
         type == OBJECT_EGG    ||
         type == OBJECT_TEEN28 ||
         type == OBJECT_TEEN31  ) return true;

    return false;
}

SoundType CDamageableHardcodeCollection::GetInsectDamageSound(ObjectType type)
{
    if ( type == OBJECT_HUMAN ) return SOUND_NONE;

    return SOUND_TOUCH;
}

float CDamageableHardcodeCollection::GetCollisionOtherObjectRadiusToIgnore(ObjectType type)
{
    if ( type == OBJECT_MOTHER ) return 1.2f;
    if ( type == OBJECT_ANT    ) return 1.2f;
    if ( type == OBJECT_SPIDER ) return 1.2f;
    if ( type == OBJECT_BEE    ) return 1.2f;
    if ( type == OBJECT_WORM   ) return 1.2f;

    return 0.0f;
}

float CDamageableHardcodeCollection::GetCollisionResistance(ObjectType type)
{
    if (type == OBJECT_DERRICK  ||
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
        type == OBJECT_HUSTON    )  // building?
    {
        return 400.0f;
    }

    
    if (type == OBJECT_MOBILEwa ||
        type == OBJECT_MOBILEta ||
        type == OBJECT_MOBILEfa ||
        type == OBJECT_MOBILEia ||
        type == OBJECT_MOBILEwb ||
        type == OBJECT_MOBILEtb ||
        type == OBJECT_MOBILEfb ||
        type == OBJECT_MOBILEib ||
        type == OBJECT_MOBILEwc ||
        type == OBJECT_MOBILEtc ||
        type == OBJECT_MOBILEfc ||
        type == OBJECT_MOBILEic ||
        type == OBJECT_MOBILEwi ||
        type == OBJECT_MOBILEti ||
        type == OBJECT_MOBILEfi ||
        type == OBJECT_MOBILEii ||
        type == OBJECT_MOBILEws ||
        type == OBJECT_MOBILEts ||
        type == OBJECT_MOBILEfs ||
        type == OBJECT_MOBILEis ||
        type == OBJECT_MOBILErt ||
        type == OBJECT_MOBILErc ||
        type == OBJECT_MOBILErr ||
        type == OBJECT_MOBILErs ||
        type == OBJECT_MOBILEsa ||
        type == OBJECT_MOBILEwt ||
        type == OBJECT_MOBILEtt ||
        type == OBJECT_MOBILEft ||
        type == OBJECT_MOBILEit ||
        type == OBJECT_MOBILErp ||
        type == OBJECT_MOBILEst  )  // vehicle?
    {
        // TODO: implement "killer"?
        return 200.0f;
    }

    if (type == OBJECT_STONE   ||
        type == OBJECT_URANIUM )
    {
        return 0.0f;
    }

    return -1.0f;
}

float CDamageableHardcodeCollection::GetLightningRodHeight(ObjectType type)
{
    if (type == OBJECT_BASE)
    {
        return 120.0f;
    }
    if (type == OBJECT_PARA)
    {
        return 67.0f;
    }

    return 0.0f; 
}

float CDamageableHardcodeCollection::GetLightningHitProbability(ObjectType type)
{
    if ( type == OBJECT_BASE     ||
         type == OBJECT_DERRICK  ||
         type == OBJECT_FACTORY  ||
         type == OBJECT_REPAIR   ||
         type == OBJECT_DESTROYER||
         type == OBJECT_STATION  ||
         type == OBJECT_CONVERT  ||
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
        return 1.0f;
    }
    if ( type == OBJECT_METAL    ||
         type == OBJECT_POWER    ||
         type == OBJECT_ATOMIC   ) // resource?
    {
        return 0.3f;
    }
    if ( type == OBJECT_MOBILEfa ||
         type == OBJECT_MOBILEta ||
         type == OBJECT_MOBILEwa ||
         type == OBJECT_MOBILEia ||
         type == OBJECT_MOBILEfb ||
         type == OBJECT_MOBILEtb ||
         type == OBJECT_MOBILEwb ||
         type == OBJECT_MOBILEib ||
         type == OBJECT_MOBILEfc ||
         type == OBJECT_MOBILEtc ||
         type == OBJECT_MOBILEwc ||
         type == OBJECT_MOBILEic ||
         type == OBJECT_MOBILEfi ||
         type == OBJECT_MOBILEti ||
         type == OBJECT_MOBILEwi ||
         type == OBJECT_MOBILEii ||
         type == OBJECT_MOBILEfs ||
         type == OBJECT_MOBILEts ||
         type == OBJECT_MOBILEws ||
         type == OBJECT_MOBILEis ||
         type == OBJECT_MOBILErt ||
         type == OBJECT_MOBILErc ||
         type == OBJECT_MOBILErr ||
         type == OBJECT_MOBILErs ||
         type == OBJECT_MOBILEsa ||
         type == OBJECT_MOBILEft ||
         type == OBJECT_MOBILEtt ||
         type == OBJECT_MOBILEwt ||
         type == OBJECT_MOBILEit ||
         type == OBJECT_MOBILErp ||
         type == OBJECT_MOBILEst ||
         type == OBJECT_MOBILEtg ||
         type == OBJECT_MOBILEdr )  // robot?
    {
        return 0.5f;
    }
    return 0.0f;
}
