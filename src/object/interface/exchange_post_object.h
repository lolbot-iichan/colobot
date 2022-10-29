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

#include "object/object_interface_type.h"

#include <string>
#include <vector>

#include <boost/optional.hpp> 

struct ExchangePostInfo
{
    std::string name;       //!< name of the information
    float value = 0.0f;     //!< value of the information
};

/**
 * \class CExchangePostObject
 * \brief Interface for objects that can act as information servers
 */
class CExchangePostObject
{
public:
    explicit CExchangePostObject(ObjectInterfaceTypes& types)
    {
        types[static_cast<int>(ObjectInterfaceType::ExchangePost)] = true;
    }
    virtual ~CExchangePostObject()
    {}

    //! Management of ExchangePostInfo list
    //@{
    virtual bool SetInfo(const std::string& name, float value) = 0;
    virtual const std::vector<ExchangePostInfo>& GetInfoList() = 0;
    virtual boost::optional<float> GetInfoValue(const std::string& name) = 0;
    virtual bool HasInfo(const std::string& name) = 0;
    virtual bool DeleteInfo(const std::string& name) = 0;
    virtual void SetInfoUpdate(bool update) = 0;
    virtual bool GetInfoUpdate() = 0; 
    //@}
};
