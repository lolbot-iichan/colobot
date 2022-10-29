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


#pragma once

#include "object/interface/exchange_post_object.h"

#include "object/auto/auto.h"

#include <string>
#include <vector>

#include <boost/optional.hpp>

struct ExchangePostInfo;

namespace Gfx
{
class COldModelManager;
class CEngine;
}

class CExchangePostObjectImpl : public CExchangePostObject
{
public:
    explicit CExchangePostObjectImpl(ObjectInterfaceTypes& types);
    virtual ~CExchangePostObjectImpl();

    bool SetInfo(const std::string& name, float value) override;
    const std::vector<ExchangePostInfo>& GetInfoList() override;
    boost::optional<float> GetInfoValue(const std::string& name) override;
    bool HasInfo(const std::string& name) override;
    bool DeleteInfo(const std::string& name) override;
    void SetInfoUpdate(bool update) override;
    bool GetInfoUpdate() override;

    void ReadInfo(CLevelParserLine* line);
    void WriteInfo(CLevelParserLine* line);

private:
    std::vector<ExchangePostInfo> m_infoList;
    bool m_infoUpdate;
};
