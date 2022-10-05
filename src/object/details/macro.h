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
 * \file object/details/macro.h
 * \brief collection of macro definitions used in Read()/Write() methods
 */

#pragma once

#define WRITE_NEW(C)       auto line = MakeUnique<CLevelParserLine>(C);
#define WRITE_VAL(K,V)     line->AddParam((K),MakeUnique<CLevelParserParam>(V));

#define WRITE_GLOB(C)      { bool bWrite = false; WRITE_NEW(C);
#define WRITE_LINE(C)      { bool bWrite = false; WRITE_NEW(C); WRITE_VAL("type",type);
#define WRITE_VAR(K,D,P)   if((P) != (D))   { bWrite = true; WRITE_VAL((K),(P)); }
#define WRITE_ARG(K,D,P)   if((P) != (D.P)) { bWrite = true; WRITE_VAL((K),(P)); }
#define WRITE_IT(K,D,P)    if((it.P) != (D.P)) { bWrite = true; WRITE_VAL((K),(it.P)); }
#define WRITE_END()        if(bWrite) { parser->AddLine(std::move(line)); } }

#define READ_LINE(C)      if (line->GetCommand() == (C)) {
#define READ_NEW(I,P)     auto I = P.size(); P.resize(I+1);
#define READ_IDX(N)       auto N = line->GetParam("id")->AsInt();
#define READ_ARG(K,A,P)   P = line->GetParam(K)->A(P);
#define READ_RAW(K,P)     P = line->GetParam(K)->GetValue();
#define READ_END()        return true; }
