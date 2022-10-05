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

#include <boost/lexical_cast.hpp>

#include <unordered_set>

#include "object/object_details.h"
#include "object/details/hardcode.h"

CObjectDetails::CObjectDetails()
{
    Clear();
    LoadHardcode();
    Dump("object_details.std");
    Load("object_details.txt");
    Dump("object_details.tmp");
    Clear();
    Load("object_details.tmp");
    Dump("object_details.sav");
}

void CObjectDetails::Clear()
{
    m_objects.clear();
    m_nameToType.clear();
    m_globals = CObjectGlobalDetails();
}

void CObjectDetails::LoadHardcode()
{
    for ( int i = 0 ; i < OBJECT_MAX ; i++ )
    {
        ObjectType type = static_cast<ObjectType>(i);

        m_objects[type].physics = GetObjectPhysicsDetailsHardcode(type);

        m_objects[type].naming.ReadHardcode(type);
        m_objects[type].assistant.ReadHardcode(type);
        m_objects[type].automation.ReadHardcode(type);
        m_objects[type].creation.ReadHardcode(type);
        m_objects[type].detectable.ReadHardcode(type);
        m_objects[type].scripting.ReadHardcode(type);
        m_objects[type].transportable.ReadHardcode(type);
        m_objects[type].programmable.ReadHardcode(type);
        m_objects[type].task_executor.ReadHardcode(type);
        m_objects[type].josteable.ReadHardcode(type);
        m_objects[type].movable.ReadHardcode(type);
        m_objects[type].flying.ReadHardcode(type);
        m_objects[type].jet_flying.ReadHardcode(type);
        m_objects[type].controllable.ReadHardcode(type);
        m_objects[type].power_container.ReadHardcode(type);
        m_objects[type].ranged.ReadHardcode(type);
        m_objects[type].trace_drawing.ReadHardcode(type);
        m_objects[type].damageable.ReadHardcode(type);
        m_objects[type].destroyable.ReadHardcode(type);
        m_objects[type].fragile.ReadHardcode(type);
        m_objects[type].shielded.ReadHardcode(type);
        m_objects[type].shielded_auto_regen.ReadHardcode(type);
        m_objects[type].slotted.ReadHardcode(type);
        m_objects[type].thumpable.ReadHardcode(type);

        auto levelNaming = m_objects[type].naming;
        if ( levelNaming.name.size() )
            m_nameToType[levelNaming.name] = type;
        if ( levelNaming.alias.size() )
            m_nameToType[levelNaming.alias] = type;
    }
    m_globals.ReadHardcode();
}

void CObjectDetails::Load(const char* fname)
{
    CLevelParser parser(fname);
    if (!parser.Exists())
    {
        assert(false);
        return;
    }

    parser.Load();
    for (auto& line : parser.GetLines())
    {
        if ( line->GetCommand() == "SetObjectNaming" )
        {
            ObjectType type = static_cast<ObjectType>(line->GetParam("value")->AsInt());

            CObjectNamingDetails& naming = m_objects[type].naming;
            naming.Read(line.get());

            m_nameToType[ naming.name] = type;
            if ( naming.alias.size() )
                m_nameToType[ naming.alias] = type;

            continue;
        }

        if ( line.get()->GetParam("type")->IsDefined() )
        {
            ObjectType type = line->GetParam("type")->AsObjectType();

            if (m_objects[type].assistant.Read(line.get()) ||
                m_objects[type].automation.Read(line.get()) ||
                m_objects[type].creation.Read(line.get()) ||
                m_objects[type].detectable.Read(line.get()) ||
                m_objects[type].scripting.Read(line.get()) ||
                m_objects[type].transportable.Read(line.get()) ||
                m_objects[type].programmable.Read(line.get()) ||
                m_objects[type].task_executor.Read(line.get()) ||
                m_objects[type].josteable.Read(line.get()) ||
                m_objects[type].movable.Read(line.get()) ||
                m_objects[type].flying.Read(line.get()) ||
                m_objects[type].jet_flying.Read(line.get()) ||
                m_objects[type].controllable.Read(line.get()) ||
                m_objects[type].power_container.Read(line.get()) ||
                m_objects[type].ranged.Read(line.get()) ||
                m_objects[type].trace_drawing.Read(line.get()) ||
                m_objects[type].damageable.Read(line.get()) ||
                m_objects[type].destroyable.Read(line.get()) ||
                m_objects[type].fragile.Read(line.get()) ||
                m_objects[type].shielded.Read(line.get()) ||
                m_objects[type].shielded_auto_regen.Read(line.get()) ||
                m_objects[type].slotted.Read(line.get()) ||
                m_objects[type].thumpable.Read(line.get()) ) continue;

            auto command    = line.get()->GetCommand();
            auto fileName   = line.get()->GetLevelFilename();
            auto lineNumber = boost::lexical_cast<std::string>(line.get()->GetLineNumber());
            std::string msg = "Unknown command '" + command + "' (in " + fileName + ":" + lineNumber + ")";
            throw std::runtime_error(msg);
        }

        if ( m_globals.Read(line.get()) ) continue;
    }
}

void CObjectDetails::Dump(const char* fname)
{
    CLevelParser parser(fname);

    for (int i = 0; i < OBJECT_MAX; i++)
    {
        ObjectType type = static_cast<ObjectType>(i);
        m_objects[type].naming.Write(&parser, type);
    }

    for (int i = 0; i < OBJECT_MAX; i++)
    {
        ObjectType type = static_cast<ObjectType>(i);
        m_objects[type].assistant.Write(&parser, type);
        m_objects[type].automation.Write(&parser, type);
        m_objects[type].creation.Write(&parser, type);
        m_objects[type].detectable.Write(&parser, type);
        m_objects[type].scripting.Write(&parser, type);
        m_objects[type].transportable.Write(&parser, type);
        m_objects[type].programmable.Write(&parser, type);
        m_objects[type].task_executor.Write(&parser, type);
        m_objects[type].josteable.Write(&parser, type);
        m_objects[type].movable.Write(&parser, type);
        m_objects[type].flying.Write(&parser, type);
        m_objects[type].jet_flying.Write(&parser, type);
        m_objects[type].controllable.Write(&parser, type);
        m_objects[type].power_container.Write(&parser, type);
        m_objects[type].ranged.Write(&parser, type);
        m_objects[type].trace_drawing.Write(&parser, type);
        m_objects[type].damageable.Write(&parser, type);
        m_objects[type].destroyable.Write(&parser, type);
        m_objects[type].fragile.Write(&parser, type);
        m_objects[type].shielded.Write(&parser, type);
        m_objects[type].shielded_auto_regen.Write(&parser, type);
        m_objects[type].slotted.Write(&parser, type);
        m_objects[type].thumpable.Write(&parser, type);
    }

    m_globals.Write(&parser);

    parser.Save();
}

ObjectType CObjectDetails::CastToObjectType(std::string value)
{
    auto it = m_nameToType.find(value);
    if (it != m_nameToType.end())
        return it->second;
    return OBJECT_NULL;
}




//////////////////////////////////////////////////////////////////////////////
// Unsorted
//////////////////////////////////////////////////////////////////////////////

CObjectPhysicsDetails CObjectDetails::GetObjectPhysicsDetailsHardcode(ObjectType type)
{
    CObjectPhysicsDetails result;
    CHardcodeCollection hardcode;

    result.thumper.safeRadius                 = hardcode.GetThumperSafeRadius(type);
    result.thumper.effect                     = hardcode.GetThumperPyroType(type);
    result.thumper.explosionDamage            = hardcode.GetThumperExplosionDamage(type);

    result.lightning.lightningRodHeight       = hardcode.GetLightningRodHeight(type);

    result.collisionOtherObjectRadiusToIgnore = hardcode.GetCollisionOtherObjectRadiusToIgnore(type);
    result.isCollisionDamagable               = hardcode.IsCollisionDamagable(type);
    result.collisionSoftness                  = hardcode.GetCollisionSoftness(type);

    return result;
}

ObjectType CObjectDetails::GetFunctionResearchPerformerObject(ResearchType type)
{
    if ( type == RESEARCH_iPAW       ||
         type == RESEARCH_iGUN       ||
         type == RESEARCH_TARGET      ) return OBJECT_LABO;
    return OBJECT_RESEARCH;
}

