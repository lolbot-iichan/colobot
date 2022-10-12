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

#include "level/parser/parserparam.h"

#include "app/app.h"

#include "common/logger.h"
#include "common/make_unique.h"
#include "common/stringutils.h"

#include "common/resources/resourcemanager.h"

#include "graphics/engine/engine_types.h"

#include "level/robotmain.h"
#include "level/scoreboard.h"

#include "level/parser/parser.h"

#include "object/object_details.h"

#include <boost/lexical_cast.hpp>
#include <boost/algorithm/string.hpp>

CLevelParserParam::CLevelParserParam(std::string name, std::string value)
  : m_name(name)
  , m_value(value)
{}

CLevelParserParam::CLevelParserParam(std::string name, bool empty)
  : m_empty(empty)
  , m_name(name)
{
    assert(empty == true); // we need a second argument because we don't want to create param with value "name"
}

CLevelParserParam::CLevelParserParam(int value)
  : m_value(boost::lexical_cast<std::string>(value))
{}

CLevelParserParam::CLevelParserParam(float value)
  : m_value(boost::lexical_cast<std::string>(value))
{}

CLevelParserParam::CLevelParserParam(std::string value)
  : m_value("\""+value+"\"")
{}

CLevelParserParam::CLevelParserParam(bool value)
  : m_value(value ? "1" : "0")
{}

CLevelParserParam::CLevelParserParam(Gfx::Color value)
{
    m_array.push_back(MakeUnique<CLevelParserParam>(value.r));
    m_array.push_back(MakeUnique<CLevelParserParam>(value.g));
    m_array.push_back(MakeUnique<CLevelParserParam>(value.b));
    m_array.push_back(MakeUnique<CLevelParserParam>(value.a));

    LoadArray();
}

CLevelParserParam::CLevelParserParam(Math::Point value)
{
    m_array.push_back(MakeUnique<CLevelParserParam>(value.x));
    m_array.push_back(MakeUnique<CLevelParserParam>(value.y));

    LoadArray();
}

CLevelParserParam::CLevelParserParam(Math::Vector value)
{
    m_array.push_back(MakeUnique<CLevelParserParam>(value.x));
    if(value.y != 0.0f)
        m_array.push_back(MakeUnique<CLevelParserParam>(value.y));
    m_array.push_back(MakeUnique<CLevelParserParam>(value.z));

    LoadArray();
}

CLevelParserParam::CLevelParserParam(ObjectType value)
  : m_value(FromObjectType(value))
{}

CLevelParserParam::CLevelParserParam(DriveType value)
  : m_value(FromDriveType(value))
{}

CLevelParserParam::CLevelParserParam(ToolType value)
  : m_value(FromToolType(value))
{}

CLevelParserParam::CLevelParserParam(Gfx::CameraType value)
  : m_value(FromCameraType(value))
{}

CLevelParserParam::CLevelParserParam(CLevelParserParamVec&& array)
{
    m_array.swap(array);

    LoadArray();
}

void CLevelParserParam::SetLine(CLevelParserLine* line)
{
    m_line = line;
}

CLevelParserLine* CLevelParserParam::GetLine()
{
    return m_line;
}

std::string CLevelParserParam::GetName()
{
    return m_name;
}

std::string CLevelParserParam::GetValue()
{
    return m_value;
}

bool CLevelParserParam::IsDefined()
{
    return !m_empty;
}

template<typename T>
T CLevelParserParam::Cast(std::string value, std::string requestedType)
{
    try
    {
        return boost::lexical_cast<T>(value);
    }
    catch(...)
    {
        throw CLevelParserExceptionBadParam(this, requestedType);
    }
}

template<typename T>
T CLevelParserParam::Cast(std::string requestedType)
{
    return Cast<T>(m_value, requestedType);
}


int CLevelParserParam::AsInt()
{
    if (m_empty)
        throw CLevelParserExceptionMissingParam(this);
    return Cast<int>("int");
}


int CLevelParserParam::AsInt(int def)
{
    if (m_empty)
        return def;
    return AsInt();
}


float CLevelParserParam::AsFloat()
{
    if (m_empty)
        throw CLevelParserExceptionMissingParam(this);
    return Cast<float>("float");
}

float CLevelParserParam::AsFloat(float def)
{
    if (m_empty)
        return def;
    return AsFloat();
}


std::string CLevelParserParam::AsString()
{
    if (m_empty)
        throw CLevelParserExceptionMissingParam(this);
    if ((m_value[0] == '\"' && m_value[m_value.length()-1] == '\"') || (m_value[0] == '\'' && m_value[m_value.length()-1] == '\''))
    {
        return m_value.substr(1, m_value.length()-2);
    }
    else
    {
        throw CLevelParserExceptionBadParam(this, "string");
    }
}

std::string CLevelParserParam::AsString(std::string def)
{
    if (m_empty)
        return def;
    return AsString();
}


bool CLevelParserParam::AsBool()
{
    if (m_empty)
        throw CLevelParserExceptionMissingParam(this);
    std::string value = m_value;
    boost::to_lower(value);
    if (value == "true") return true;
    if (value == "false") return false;
    return Cast<bool>("bool");
}

bool CLevelParserParam::AsBool(bool def)
{
    if (m_empty)
        return def;
    return AsBool();
}


std::string CLevelParserParam::ToPath(std::string path, const std::string defaultDir)
{
    if (defaultDir == "" && path.find("%lvl%") != std::string::npos)
        throw CLevelParserException("TODO: Param "+m_name+" does not yet support %lvl%! :(");

    return GetLine()->GetLevel()->InjectLevelPaths(path, defaultDir);
}

std::string CLevelParserParam::AsPath(const std::string defaultDir)
{
    if (m_empty)
        throw CLevelParserExceptionMissingParam(this);

    return ToPath(AsString(), defaultDir);
}

std::string CLevelParserParam::AsPath(const std::string defaultDir, std::string def)
{
    if (m_empty)
        return GetLine()->GetLevel()->InjectLevelPaths(def, defaultDir);

    return ToPath(AsString(def), defaultDir);
}


Gfx::Color CLevelParserParam::AsColor()
{
    if (m_empty)
        throw CLevelParserExceptionMissingParam(this);

    float red, green, blue, alpha;
    if (m_value.length() >= 1 && m_value[0] == '#')
    {
        if (m_value.length() != 7 && m_value.length() != 9)
            throw CLevelParserExceptionBadParam(this, "color");

        try
        {
            red = StrUtils::HexStringToInt(m_value.substr(1, 2));
            green = StrUtils::HexStringToInt(m_value.substr(3, 2));
            blue = StrUtils::HexStringToInt(m_value.substr(5, 2));
            alpha = (m_value.length() == 9) ? StrUtils::HexStringToInt(m_value.substr(7, 2)) : 1.0f;
        }
        catch (...)
        {
            // TODO: Show original exception text
            throw CLevelParserExceptionBadParam(this, "color");
        }
    }
    else
    {
        ParseArray();

        if (m_array.size() != 3 && m_array.size() != 4)
            throw CLevelParserExceptionBadParam(this, "color");

        red = m_array[0]->AsFloat();
        green = m_array[1]->AsFloat();
        blue = m_array[2]->AsFloat();
        alpha = (m_array.size() == 4) ? m_array[3]->AsFloat() : 1.0f;
    }

    if (red > 1.0f || green > 1.0f || blue > 1.0f || alpha > 1.0f)
    {
        red = red / 255.0f;
        green = green / 255.0f;
        blue = blue / 255.0f;
        alpha = alpha / 255.0f;
    }

    return Gfx::Color(red, green, blue, alpha);
}

Gfx::Color CLevelParserParam::AsColor(Gfx::Color def)
{
    if (m_empty)
        return def;
    return AsColor();
}


Math::Vector CLevelParserParam::AsPoint()
{
    if (m_empty)
        throw CLevelParserExceptionMissingParam(this);

    ParseArray();

    if (m_array.size() == 2) //XZ
    {
        return Math::Vector(m_array[0]->AsFloat(), 0.0f, m_array[1]->AsFloat());
    }
    else if (m_array.size() == 3) //XYZ
    {
        return Math::Vector(m_array[0]->AsFloat(), m_array[1]->AsFloat(), m_array[2]->AsFloat());
    }
    else
    {
        throw CLevelParserExceptionBadParam(this, "point");
    }
}

Math::Vector CLevelParserParam::AsPoint(Math::Vector def)
{
    if (m_empty)
        return def;
    return AsPoint();
}

Math::Point CLevelParserParam::AsPoint(Math::Point def)
{
    if (m_empty)
        return def;

    ParseArray();
    if (m_array.size() == 2)
    {
        return Math::Point(m_array[0]->AsFloat(), m_array[1]->AsFloat());
    }
    else
    {
        throw CLevelParserExceptionBadParam(this, "point");
    }
}

ObjectType CLevelParserParam::ToObjectType(std::string value)
{
    if (value == "All"               ) return OBJECT_NULL; // For use in NewScript
    if (value == "Any"               ) return OBJECT_NULL; // For use in type= in ending conditions

    ObjectType type = CastToObjectType(value);
    if ( type != OBJECT_NULL ) return type;

    return static_cast<ObjectType>(Cast<int>(value, "object"));
}

const std::string CLevelParserParam::FromObjectType(ObjectType value)
{
    std::string name = GetObjectNamingDetails(value).name;
    if ( name.size() ) return name;

    return boost::lexical_cast<std::string>(static_cast<int>(value));
}

ObjectType CLevelParserParam::AsObjectType()
{
    if (m_empty)
        throw CLevelParserExceptionMissingParam(this);
    return ToObjectType(m_value);
}

ObjectType CLevelParserParam::AsObjectType(ObjectType def)
{
    if (m_empty)
        return def;
    return AsObjectType();
}


DriveType CLevelParserParam::ToDriveType(std::string value)
{
    if (value == "Wheeled"   ) return DriveType::Wheeled;
    if (value == "Tracked"   ) return DriveType::Tracked;
    if (value == "Winged"    ) return DriveType::Winged;
    if (value == "Legged"    ) return DriveType::Legged;
    if (value == "Heavy"     ) return DriveType::Heavy;
    if (value == "Amphibious") return DriveType::Amphibious;
    if (value == "Other"     ) return DriveType::Other;
    return static_cast<DriveType>(Cast<int>(value, "drive"));
}

const std::string CLevelParserParam::FromDriveType(DriveType value)
{
    if (value == DriveType::Wheeled   ) return "Wheeled";
    if (value == DriveType::Tracked   ) return "Tracked";
    if (value == DriveType::Winged    ) return "Winged";
    if (value == DriveType::Legged    ) return "Legged";
    if (value == DriveType::Heavy     ) return "Heavy";
    if (value == DriveType::Amphibious) return "Amphibious";
    if (value == DriveType::Other     ) return "Other";

    return boost::lexical_cast<std::string>(static_cast<int>(value));
}

DriveType CLevelParserParam::AsDriveType()
{
    if (m_empty)
        throw CLevelParserExceptionMissingParam(this);
    return ToDriveType(m_value);
}

DriveType CLevelParserParam::AsDriveType(DriveType def)
{
    if (m_empty)
        return def;
    return AsDriveType();
}


ToolType CLevelParserParam::ToToolType(std::string value)
{
    if (value == "Grabber"    ) return ToolType::Grabber;
    if (value == "Sniffer"    ) return ToolType::Sniffer;
    if (value == "Shooter"    ) return ToolType::Shooter;
    if (value == "OrgaShooter") return ToolType::OrganicShooter;
    if (value == "Builder"    ) return ToolType::Builder;
    if (value == "Other"      ) return ToolType::Other;

    return static_cast<ToolType>(Cast<int>(value, "tool"));
}

const std::string CLevelParserParam::FromToolType(ToolType value)
{
    if (value == ToolType::Grabber       ) return "Grabber";
    if (value == ToolType::Sniffer       ) return "Sniffer";
    if (value == ToolType::Shooter       ) return "Shooter";
    if (value == ToolType::OrganicShooter) return "OrgaShooter";
    if (value == ToolType::Builder       ) return "Builder";
    if (value == ToolType::Other         ) return "Other";
    return boost::lexical_cast<std::string>(static_cast<int>(value));
}

ToolType CLevelParserParam::AsToolType()
{
    if (m_empty)
        throw CLevelParserExceptionMissingParam(this);
    return ToToolType(m_value);
}

ToolType CLevelParserParam::AsToolType(ToolType def)
{
    if (m_empty)
        return def;
    return AsToolType();
}


Gfx::WaterType CLevelParserParam::ToWaterType(std::string value)
{
    if (value == "nullptr") return Gfx::WATER_NULL;
    if (value == "TT"  ) return Gfx::WATER_TT;
    if (value == "TO"  ) return Gfx::WATER_TO;
    if (value == "CT"  ) return Gfx::WATER_CT;
    if (value == "CO"  ) return Gfx::WATER_CO;
    return static_cast<Gfx::WaterType>(Cast<int>(value, "watertype"));
}

Gfx::WaterType CLevelParserParam::AsWaterType()
{
    if (m_empty)
        throw CLevelParserExceptionMissingParam(this);
    return ToWaterType(m_value);
}

Gfx::WaterType CLevelParserParam::AsWaterType(Gfx::WaterType def)
{
    if (m_empty)
        return def;
    return AsWaterType();
}


Gfx::EngineObjectType CLevelParserParam::ToTerrainType(std::string value)
{
    if (value == "Terrain") return Gfx::ENG_OBJTYPE_TERRAIN;
    if (value == "Object" ) return Gfx::ENG_OBJTYPE_FIX;
    if (value == "Quartz" ) return Gfx::ENG_OBJTYPE_QUARTZ;
    if (value == "Metal"  ) return Gfx::ENG_OBJTYPE_METAL;
    return static_cast<Gfx::EngineObjectType>(Cast<int>(value, "terraintype"));
}

Gfx::EngineObjectType CLevelParserParam::AsTerrainType()
{
    if (m_empty)
        throw CLevelParserExceptionMissingParam(this);
    return ToTerrainType(m_value);
}

Gfx::EngineObjectType CLevelParserParam::AsTerrainType(Gfx::EngineObjectType def)
{
    if (m_empty)
        return def;
    return AsTerrainType();
}


int CLevelParserParam::ToBuildFlag(std::string value)
{
    if (value == "BotFactory"    ) return BUILD_FACTORY;
    if (value == "Derrick"       ) return BUILD_DERRICK;
    if (value == "Converter"     ) return BUILD_CONVERT;
    if (value == "RadarStation"  ) return BUILD_RADAR;
    if (value == "PowerPlant"    ) return BUILD_ENERGY;
    if (value == "NuclearPlant"  ) return BUILD_NUCLEAR;
    if (value == "FuelCellPlant" ) return BUILD_NUCLEAR;
    if (value == "PowerStation"  ) return BUILD_STATION;
    if (value == "RepairCenter"  ) return BUILD_REPAIR;
    if (value == "DefenseTower"  ) return BUILD_TOWER;
    if (value == "ResearchCenter") return BUILD_RESEARCH;
    if (value == "AutoLab"       ) return BUILD_LABO;
    if (value == "PowerCaptor"   ) return BUILD_PARA;
    if (value == "ExchangePost"  ) return BUILD_INFO;
    if (value == "Vault"         ) return BUILD_SAFE;
    if (value == "Destroyer"     ) return BUILD_DESTROYER;
    if (value == "FlatGround"    ) return BUILD_GFLAT;
    if (value == "Flag"          ) return BUILD_FLAG;
    return Cast<int>(value, "buildflag");
}

int CLevelParserParam::AsBuildFlag()
{
    if (m_empty)
        throw CLevelParserExceptionMissingParam(this);
    return ToBuildFlag(m_value);
}

int CLevelParserParam::AsBuildFlag(int def)
{
    if (m_empty)
        return def;
    return AsBuildFlag();
}


int CLevelParserParam::ToResearchFlag(std::string value)
{
    if (value == "TRACKER" ) return RESEARCH_TANK;
    if (value == "WINGER"  ) return RESEARCH_FLY;
    if (value == "THUMPER" ) return RESEARCH_THUMP;
    if (value == "SHOOTER" ) return RESEARCH_CANON;
    if (value == "TOWER"   ) return RESEARCH_TOWER;
    if (value == "PHAZER"  ) return RESEARCH_PHAZER;
    if (value == "SHIELDER") return RESEARCH_SHIELD;
    if (value == "ATOMIC"  ) return RESEARCH_ATOMIC;
    if (value == "iPAW"    ) return RESEARCH_iPAW;
    if (value == "iGUN"    ) return RESEARCH_iGUN;
    if (value == "RECYCLER") return RESEARCH_RECYCLER;
    if (value == "SUBBER"  ) return RESEARCH_SUBM;
    if (value == "SNIFFER" ) return RESEARCH_SNIFFER;
    if (value == "BUILDER" ) return RESEARCH_BUILDER;
    if (value == "TARGET"  ) return RESEARCH_TARGET;

    /* /9j/4AAQSkZJRgABAQEAYABgAAD//gATQ3JlYXRlZCB3aXRoIEdJTVD/2wBDACAWGBwYFCAcGhwk
     * IiAmMFA0MCwsMGJGSjpQdGZ6eHJmcG6AkLicgIiuim5woNqirr7EztDOfJri8uDI8LjKzsb/2wBD
     * ASIkJDAqMF40NF7GhHCExsbGxsbGxsbGxsbGxsbGxsbGxsbGxsbGxsbGxsbGxsbGxsbGxsbGxsbG
     * xsbGxsbGxsb/wgARCAAgAWwDAREAAhEBAxEB/8QAGQABAQEBAQEAAAAAAAAAAAAAAAECAwQF/8QA
     * FwEBAQEBAAAAAAAAAAAAAAAAAAECA//aAAwDAQACEAMQAAAB+gZTKdGsmiAhSghDnL2sAAAAAAAA
     * AAAAAAAh4Zw5t+yRrrgAApAWXhN+7XPJQbAAAAAAAAAAAAAIfPzx5Xp7ZjtrrAQgAOhgFMGiFIDR
     * oyCmSlIQpDQIUgBAaNgHNOR6CKAABQZKAAACggAAABCgyaAAAKU//8QAIRAAAwACAwACAwEAAAAA
     * AAAAAAERAhIDECEgQSIxQFD/2gAIAQEAAQUCG4brqpfBO/FuLHkWX+Dk6fs42Z4ttrI1yNch4NDx
     * yJka5muSM8W+Pi43fv09Pv8Asy8E/eL0bhsbGxv7sbO7dLI2NjZlYm2beVysWVbfmxi6U3NhOmxs
     * bfi8oXxuGxTY2NjY2E78MsVkLhx6hEREIREROtUREIQiIiE7hCEREQiIiERCGqIRERERERF3/8QA
     * HxEAAQMEAwEAAAAAAAAAAAAAAQACEQMhMFAQEiJg/9oACAEDAQE/AeOwyRoQZcneblU3TiCMRoRT
     * cTZGm4iAmNj5n//EABsRAQACAgMAAAAAAAAAAAAAAAEAETFQAiFg/9oACAECAQE/Adfliwb1mGcu
     * 4FeZ/8QAHRAAAQMFAQAAAAAAAAAAAAAAEQAQIQEgMDFQYf/aAAgBAQAGPwJt3RyQosh9qq94QY3j
     * HXzGWOWeb//EACMQAAMAAgICAwADAQAAAAAAAAABESExUWEQQXGBkSBAUPH/2gAIAQEAAT8hEJW4
     * Jvg2I2l5birEJWpVZ5TT0Is9DuJ5/wAFz0SeCUGZb6PiQpbzOKe/3OSydbkcVEW9e8mE03c+zfl/
     * pg2/Rew96I+8hBXGoOhqGNM9+hJ7f3Wu06jadNnqVHxz2Twx8cMWBOF8f9MHD8G6Txn0XM6EtabJ
     * vR8GbmtGaYXGBEsrVEzZ8IwnVvg6v0IC/SDNej4M9rcHN6I4ZHBwmTLBY5NiJ4Xs+941X0TwxWTi
     * +z4E8MeOFmUnhif4E+Am7liUUQ0brOo6iOCODo7G52ETRBIR1EcCRKQhOwsljR1EQm0hsi6IJOrx
     * JEdRL0RJMHUQNHtDtSJIdR1HUdR1HUJTx//aAAwDAQACAAMAAAAQFggkgAFwAAAAAAAAAAAAAAAl
     * aAkgACwggAAAAAAAAAAAAAlyAAAAEkkkkAkEggAgEAAkAFdAEkAEEkAgkgAEAkkkAAAg/8QAGxEB
     * AAIDAQEAAAAAAAAAAAAAAQARMDFQQVH/2gAIAQMBAT8QihuCe4wVoiwt4OyYAbJQpxKmI1OCxYqB
     * HbfMSU/YFcv/xAAcEQEAAwACAwAAAAAAAAAAAAABABEhMFAxUWD/2gAIAQIBAT8Q5r6EcPUMPEqb
     * xMBvoQbYgZKm/M//xAAnEAEBAAICAgAGAQUAAAAAAAABEQAhMVFBYRBxgZGhscEgQFDR8P/aAAgB
     * AQABPxDIZD3iUAL3r4GFjwLz8KWXeAiAG1chAOxuIBILwd/GhQxjMePBiWLo+f8AAOjGS2PB0YUE
     * nytypVAqw88Bnz3xhQAcAK8n8ZBhan13x9sibBeAvA94FtczST5YvWKm+HgOsvYDFOzdGbVRJO3d
     * wZqBorh8fPBxTdF/GIwrqusPFZPGKAo/PHCQeHvChVJP7xKJhqJwJ+85rp1N5TgkQvnDMa3gDERi
     * Is0ynDblmrZliFp5L5xNeXSefX/e8nKdCKfh+P1jtAtrT1/vNNpX0Qz95lRwtoerm5qwSb5cnXm1
     * iyERxrxLzgjrRaq5rJWjPxzkBBt+u8ZXYDbOfrm+GuBW9d4gBrj0esgyvYybNxzrjIwEg+sNhGcm
     * kwUHQl+kuanajJ5wakDzOc8ggV9ZyRG8zxZjYk0Ac4Ok8HvWsQACjwd5PEZtiSCC+HCvSIWOAE3o
     * 94btYQQ87c3zyT8z+MMVOAOfe5Z7mcaJod/0TF+nyZTj0LgEABwGcqNTPwJgDcBti4raNtc1Om2v
     * nlA27M2CI4h35kuEgOCXPUzj6YsAB5MJgXEAiCHrFH5J9MDiat25tRt53zkWzjEAiUcXrlgaISdY
     * qqnLec0SdAfbjFmzfdxJQl5zg6YUQbwNkVpM38MXAmhpHEzZCYg7U4wNDR05uFpO8U5HEyhJkT75
     * sWN6zZY5ueh1gCBPPw//2Q==
     */
    if (value == "\x6a\x65\x73\x74\x65\x6d\x50\x41\x57\x49\x45\x4d"                ) return RESEARCH_iPAW;
    if (value == "\x6a\x65\x73\x74\x65\x6d\x50\x49\x53\x54\x4f\x4c\x45\x54\x45\x4d") return RESEARCH_iGUN;

    return Cast<int>(value, "researchflag");
}

int CLevelParserParam::AsResearchFlag()
{
    if (m_empty)
        throw CLevelParserExceptionMissingParam(this);
    return ToResearchFlag(m_value);
}

int CLevelParserParam::AsResearchFlag(int def)
{
    if (m_empty)
        return def;
    return AsResearchFlag();
}

CScoreboard::SortType CLevelParserParam::ToSortType(std::string value)
{
    if (value == "Points") return CScoreboard::SortType::SORT_POINTS;
    if (value == "Name"  ) return CScoreboard::SortType::SORT_ID;
    return CScoreboard::SortType::SORT_ID;
}

CScoreboard::SortType CLevelParserParam::AsSortType()
{
    if (m_empty)
        throw CLevelParserExceptionMissingParam(this);
    return ToSortType(m_value);
}

CScoreboard::SortType CLevelParserParam::AsSortType(CScoreboard::SortType def)
{
    if (m_empty)
        return def;
    return AsSortType();
}

Gfx::PyroType CLevelParserParam::ToPyroType(std::string value)
{
    if (value == "FRAGt" ) return Gfx::PT_FRAGT;
    if (value == "FRAGo" ) return Gfx::PT_FRAGO;
    if (value == "FRAGw" ) return Gfx::PT_FRAGW;
    if (value == "EXPLOt") return Gfx::PT_EXPLOT;
    if (value == "EXPLOo") return Gfx::PT_EXPLOO;
    if (value == "EXPLOw") return Gfx::PT_EXPLOW;
    if (value == "SHOTt" ) return Gfx::PT_SHOTT;
    if (value == "SHOTh" ) return Gfx::PT_SHOTH;
    if (value == "SHOTm" ) return Gfx::PT_SHOTM;
    if (value == "SHOTw" ) return Gfx::PT_SHOTW;
    if (value == "EGG"   ) return Gfx::PT_EGG;
    if (value == "BURNt" ) return Gfx::PT_BURNT;
    if (value == "BURNo" ) return Gfx::PT_BURNO;
    if (value == "SPIDER") return Gfx::PT_SPIDER;
    if (value == "FALL"  ) return Gfx::PT_FALL;
    if (value == "RESET" ) return Gfx::PT_RESET;
    if (value == "WIN"   ) return Gfx::PT_WIN;
    if (value == "LOST"  ) return Gfx::PT_LOST;
    return static_cast<Gfx::PyroType>(Cast<int>(value, "pyrotype"));
}

Gfx::PyroType CLevelParserParam::AsPyroType()
{
    if (m_empty)
        throw CLevelParserExceptionMissingParam(this);
    return ToPyroType(m_value);
}

Gfx::PyroType CLevelParserParam::AsPyroType(Gfx::PyroType def)
{
    if (m_empty)
        return def;
    return AsPyroType();
}


Gfx::CameraType CLevelParserParam::ToCameraType(std::string value)
{
    if (value == "BACK"   ) return Gfx::CAM_TYPE_BACK;
    if (value == "PLANE"  ) return Gfx::CAM_TYPE_PLANE;
    if (value == "ONBOARD") return Gfx::CAM_TYPE_ONBOARD;
    if (value == "FIX"    ) return Gfx::CAM_TYPE_FIX;
    return static_cast<Gfx::CameraType>(Cast<int>(value, "camera"));
}

const std::string CLevelParserParam::FromCameraType(Gfx::CameraType value)
{
    if (value == Gfx::CAM_TYPE_ONBOARD) return "ONBOARD";
    if (value == Gfx::CAM_TYPE_FIX    ) return "FIX";
    return boost::lexical_cast<std::string>(static_cast<int>(value));
}

Gfx::CameraType CLevelParserParam::AsCameraType()
{
    if (m_empty)
        throw CLevelParserExceptionMissingParam(this);
    return ToCameraType(m_value);
}

Gfx::CameraType CLevelParserParam::AsCameraType(Gfx::CameraType def)
{
    if (m_empty)
        return def;
    return AsCameraType();
}

MissionType CLevelParserParam::ToMissionType(std::string value)
{
    if (value == "NORMAL"     ) return MISSION_NORMAL;
    if (value == "RETRO"      ) return MISSION_RETRO;
    if (value == "CODE_BATTLE") return MISSION_CODE_BATTLE;
    return static_cast<MissionType>(Cast<int>(value, "MissionType"));
}

MissionType CLevelParserParam::AsMissionType()
{
    if (m_empty)
        throw CLevelParserExceptionMissingParam(this);
    return ToMissionType(m_value);
}

MissionType CLevelParserParam::AsMissionType(MissionType def)
{
    if (m_empty)
        return def;
    return AsMissionType();
}

EventType CLevelParserParam::AsEventType(EventType def)
{
    if (m_empty)
        return def;
    return static_cast<EventType>(Cast<int>(m_value, "AsEventType"));
}

Ui::WidgetType CLevelParserParam::AsWidgetType(Ui::WidgetType def)
{
    if (m_empty)
        return def;
    return static_cast<Ui::WidgetType>(Cast<int>(m_value, "WidgetType"));
}

Gfx::EngineObjectType CLevelParserParam::AsEngineObjectType(Gfx::EngineObjectType def)
{
    if (m_empty)
        return def;
    return static_cast<Gfx::EngineObjectType>(Cast<int>(m_value, "EngineObjectType"));
}

Gfx::EngineShadowType CLevelParserParam::AsEngineShadowType(Gfx::EngineShadowType def)
{
    if (m_empty)
        return def;
    return static_cast<Gfx::EngineShadowType>(Cast<int>(m_value, "EngineShadowType"));
}

Gfx::ParticleType CLevelParserParam::AsParticleType(Gfx::ParticleType def)
{
    if (m_empty)
        return def;
    return static_cast<Gfx::ParticleType>(Cast<int>(m_value, "ParticleType"));
}

SoundType CLevelParserParam::AsSoundType(SoundType def)
{
    if (m_empty)
        return def;
    return static_cast<SoundType>(Cast<int>(m_value, "SoundType"));
}

TaskExecutionType CLevelParserParam::AsTaskExecutionType(TaskExecutionType def)
{
    if (m_empty)
        return def;
    return static_cast<TaskExecutionType>(Cast<int>(m_value, "TaskExecutionType"));
}

Gfx::TerrainRes CLevelParserParam::AsTerrainRes(Gfx::TerrainRes def)
{
    if (m_empty)
        return def;
    return static_cast<Gfx::TerrainRes>(Cast<int>(m_value, "TerrainRes"));
}

Gfx::PlanetType CLevelParserParam::AsPlanetType()
{
    Gfx::PlanetType planetType{};

    if (m_value == "0")
        planetType = Gfx::PlanetType::Sky;
    else if (m_value == "1")
        planetType = Gfx::PlanetType::OuterSpace;

    return planetType;
}

void CLevelParserParam::ParseArray()
{
    if (m_array.size() != 0)
        return;

    std::vector<std::string> values;
    boost::split(values, m_value, boost::is_any_of(";"));
    int i = 0;
    for (auto& value : values)
    {
        boost::algorithm::trim(value);
        if (value.empty()) continue;
        auto param = MakeUnique<CLevelParserParam>(m_name + "[" + boost::lexical_cast<std::string>(i) + "]", value);
        param->SetLine(m_line);
        m_array.push_back(std::move(param));
        i++;
    }
}

void CLevelParserParam::LoadArray()
{
    m_value = "";
    bool first = true;
    for (auto& value : m_array)
    {
        if (!first)
            m_value += ";";
        m_value += value->GetValue();
        first = false;
    }
}

const CLevelParserParamVec& CLevelParserParam::AsArray()
{
    if (m_empty)
        throw CLevelParserExceptionMissingParam(this);

    ParseArray();

    return m_array;
}
