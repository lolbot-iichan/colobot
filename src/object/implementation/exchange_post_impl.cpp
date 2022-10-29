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

#include "object/implementation/exchange_post_impl.h"

#include "common/regex_utils.h"

#include "graphics/engine/engine.h"
#include "graphics/engine/oldmodelmanager.h"

#include "level/parser/parserexceptions.h"
#include "level/parser/parserline.h"
#include "level/parser/parserparam.h"

#include "math/func.h"

#include "object/object.h"

#include "sound/sound.h"

#include "ui/controls/interface.h"
#include "ui/controls/list.h"
#include "ui/controls/window.h"

#include <boost/lexical_cast.hpp>

static int GetMaximumInfoListSize()
{
    return 10;
}

CExchangePostObjectImpl::CExchangePostObjectImpl(ObjectInterfaceTypes& types)
    : CExchangePostObject(types)
    , m_infoUpdate(false)
{
}

CExchangePostObjectImpl::~CExchangePostObjectImpl()
{}

bool CExchangePostObjectImpl::SetInfo(const std::string& name, float value)
{
    for (auto& info : m_infoList)
    {
        if (info.name == name)
        {
            info.value = value;
            m_infoUpdate = true;
            return true;
        }
    }

    if (static_cast<int>(m_infoList.size()) == GetMaximumInfoListSize())
    {
        return false;
    }

    ExchangePostInfo info;
    info.name = name;
    info.value = value;
    m_infoList.push_back(info);
    m_infoUpdate = true;
    return true;
}

const std::vector<ExchangePostInfo>& CExchangePostObjectImpl::GetInfoList()
{
    return m_infoList;
}

boost::optional<float> CExchangePostObjectImpl::GetInfoValue(const std::string& name)
{
    for (auto& info : m_infoList)
    {
        if (info.name == name)
        {
            return info.value;
        }
    }
    return boost::none;
}

bool CExchangePostObjectImpl::HasInfo(const std::string& name)
{
    for (auto& info : m_infoList)
    {
        if (info.name == name)
        {
            return true;
        }
    }
    return false;
}

bool CExchangePostObjectImpl::DeleteInfo(const std::string& name)
{
    for (auto it = m_infoList.begin(); it != m_infoList.end(); ++it)
    {
        if (it->name == name)
        {
            m_infoList.erase(it);
            m_infoUpdate = true;
            return true;
        }
    }
    return false;
}

bool CExchangePostObjectImpl::GetInfoUpdate()
{
    return m_infoUpdate;
}

void CExchangePostObjectImpl::SetInfoUpdate(bool update)
{
    m_infoUpdate = update;
}

void CExchangePostObjectImpl::WriteInfo(CLevelParserLine* line)
{
    int i = 0;
    for (const auto& info : m_infoList)
    {
        ++i;
        if (!info.name.empty())
        {
            auto key = "info" + boost::lexical_cast<std::string>(i);
            auto paramValue = info.name + "=" + boost::lexical_cast<std::string>(info.value);
            line->AddParam(key, std::make_unique<CLevelParserParam>(paramValue));
        }
    }
}

void CExchangePostObjectImpl::ReadInfo(CLevelParserLine* line)
{
    for (int i = 1; i <= GetMaximumInfoListSize(); i++)
    {
        std::string op = std::string("info") + boost::lexical_cast<std::string>(i);

        if (!line->GetParam(op)->IsDefined())
            break;

        std::string text = line->GetParam(op)->AsString();

        ExchangePostInfo info;

        try
        {
            auto matches = RegexUtils::AssertRegexMatch(text, "([^=]+)=(.*)");
            info.name = matches[1];
            info.value = boost::lexical_cast<float>(matches[2]);
        }
        catch (...)
        {
            throw CLevelParserExceptionBadParam(line->GetParam(op), op);
        }


        m_infoList.push_back(info);
    }
}
