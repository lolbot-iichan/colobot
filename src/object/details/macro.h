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

#include <boost/lexical_cast.hpp>

#include <libgen.h>

#include <set>

#define DO_DEF_THIS()            std::remove_reference<decltype(*this)>::type def;
#define DO_DEF_IT(P)             decltype(P)::value_type def;

#define DO_WRITE_NEW(C)          auto line = MakeUnique<CLevelParserLine>(C);
#define DO_WRITE_VAL(K,V)        line->AddParam((K),MakeUnique<CLevelParserParam>(V));
#define DO_WRITE_LINE(C)         { bool bWrite = false; DO_WRITE_NEW(C);
#define DO_WRITE_ARG(K,D,P)      if((P) != (D)) { bWrite = true; DO_WRITE_VAL((K),(P)); }
#define DO_WRITE_END()           if(bWrite) { parser->AddLine(std::move(line)); } } }

#define DO_CHK_LINE(C)           if (line->GetCommand() == C) {
#define DO_CHK_LINE2(C1,C2)      if (line->GetCommand() == C1 || line->GetCommand() == C2) {
#define DO_TST_INIT()            std::set<std::string> keys={"type"};
#define DO_TST_UNMATCHED()       for (auto k: line->GetKeys()) if (!keys.count(k)) {UnusedArg(line, k, __FILE__, __LINE__);}

#define DO_READ_ARG(K,A,P)       P = line->GetParam(K)->A(P); keys.insert(K);
#define DO_READ_END()            DO_TST_UNMATCHED(); return true; }
#define DO_READ_ADD(CA,P)        DO_CHK_LINE(CA); id = P.size(); P.resize(id+1); }
#define DO_READ_UPD(CU)          DO_CHK_LINE(CU); DO_READ_ARG("id",AsInt,id); }
#define DO_READ_CRL(CC,P)        DO_CHK_LINE(CC); DO_TST_INIT(); P.clear(); DO_READ_END();
#define DO_READ_IDX(CA,CU,P)     DO_CHK_LINE2(CA,CU); size_t id=0; DO_TST_INIT(); DO_READ_ADD(CA,P); DO_READ_UPD(CU);

#define WRITE_GLOB(C)            { DO_DEF_THIS(); DO_WRITE_LINE(C);
#define WRITE_LINE(C)            { DO_DEF_THIS(); DO_WRITE_LINE(C); DO_WRITE_VAL("type",type);
#define WRITE_ARG(K,A,P)         DO_WRITE_ARG(K, def.P, P);
#define WRITE_END()              DO_WRITE_END()

#define WRITE_IT_GLOB(C,P)       { DO_DEF_IT(P); for(auto it:P) { DO_WRITE_LINE(C);
#define WRITE_IT_LINE(C,P)       { DO_DEF_IT(P); for(auto it:P) { DO_WRITE_LINE(C); DO_WRITE_VAL("type",type);
#define WRITE_IT_ARG(K,A,P)      DO_WRITE_ARG(K, def.P, it.P);
#define WRITE_IT_END()           DO_WRITE_END() }

#define READ_LINE(C)             DO_CHK_LINE(C); DO_TST_INIT();
#define READ_ARG(K,A,P)          DO_READ_ARG(K, A, P);
#define READ_END()               DO_READ_END()

#define READ_IT_LINE(CA,CU,CC,P) DO_READ_CRL(CC,P); DO_READ_IDX(CA,CU,P); auto &it = P[id];
#define READ_IT_ARG(K,A,P)       DO_READ_ARG(K, A, it.P);
#define READ_IT_END()            DO_READ_END()

void inline UnusedCmd(CLevelParserLine* line)
{
    auto command    = line->GetCommand();
    auto fileName   = line->GetLevelFilename();
    auto lineNumber = boost::lexical_cast<std::string>(line->GetLineNumber());
    std::string msg = "Unknown command '" + command + "' (in " + fileName + ":" + lineNumber + ")";
    throw std::runtime_error(msg);
}

void inline UnusedArg(CLevelParserLine* line, std::string arg, std::string matcherPath, int matcherLine)
{
    auto command    = line->GetCommand();
    auto fileName   = line->GetLevelFilename();
    auto lineNumber = boost::lexical_cast<std::string>(line->GetLineNumber());
    std::string msg = "Unknown argument '" + arg  + "' for command '" + command + "' (in " + fileName + ":" + lineNumber + ")\n" + "See supported arguments at " + basename(matcherPath.data()) + ":" + boost::lexical_cast<std::string>(matcherLine);
    throw std::runtime_error(msg);
}