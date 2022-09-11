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


#include "script/cbottoken.h"

#include "app/app.h"

#include "object/object_type.h"
#include "object/object_details.h"

#include <string.h>


// Seeking the name of an object.

std::string GetObjectName(ObjectType type)
{
    return GetObjectDetails().GetNameInScriptFiles(type);
}

// Seeking the name of a secondary object.
// (because Otto thinks that Germans do not like nuclear power)

std::string GetObjectAlias(ObjectType type)
{
    return GetObjectDetails().GetAliasInScriptFiles(type);
}


// Returns the help file to use for the object.

std::string GetHelpFilename(ObjectType type)
{
    std::string helpfile = GetObjectDetails().GetHelpTopicPathName(type);
    if (helpfile.empty())
        return "";

    return std::string("help/") + CApplication::GetInstancePointer()->GetLanguageChar() + "/" + helpfile + ".txt";
}


// Returns the help file to use for instruction.

std::string GetHelpFilename(const char *token)
{
    std::string helpfile = "";

    if ( strcmp(token, "if"            ) == 0 )  helpfile = "cbot/if";
    if ( strcmp(token, "else"          ) == 0 )  helpfile = "cbot/if";
    if ( strcmp(token, "repeat"        ) == 0 )  helpfile = "cbot/repeat";
    if ( strcmp(token, "for"           ) == 0 )  helpfile = "cbot/for";
    if ( strcmp(token, "while"         ) == 0 )  helpfile = "cbot/while";
    if ( strcmp(token, "do"            ) == 0 )  helpfile = "cbot/do";
    if ( strcmp(token, "break"         ) == 0 )  helpfile = "cbot/break";
    if ( strcmp(token, "continue"      ) == 0 )  helpfile = "cbot/continue";
    if ( strcmp(token, "return"        ) == 0 )  helpfile = "cbot/return";
    if ( strcmp(token, "sizeof"        ) == 0 )  helpfile = "cbot/sizeof";
    if ( strcmp(token, "byte"          ) == 0 )  helpfile = "cbot/byte";
    if ( strcmp(token, "short"         ) == 0 )  helpfile = "cbot/short";
    if ( strcmp(token, "char"          ) == 0 )  helpfile = "cbot/char";
    if ( strcmp(token, "int"           ) == 0 )  helpfile = "cbot/int";
    if ( strcmp(token, "long"          ) == 0 )  helpfile = "cbot/long";
    if ( strcmp(token, "float"         ) == 0 )  helpfile = "cbot/float";
    if ( strcmp(token, "double"        ) == 0 )  helpfile = "cbot/double";
    if ( strcmp(token, "bool"          ) == 0 )  helpfile = "cbot/bool";
    if ( strcmp(token, "string"        ) == 0 )  helpfile = "cbot/string";
    if ( strcmp(token, "point"         ) == 0 )  helpfile = "cbot/point";
    if ( strcmp(token, "object"        ) == 0 )  helpfile = "cbot/object";
    if ( strcmp(token, "file"          ) == 0 )  helpfile = "cbot/file";
    if ( strcmp(token, "void"          ) == 0 )  helpfile = "cbot/void";
    if ( strcmp(token, "null"          ) == 0 )  helpfile = "cbot/null";
    if ( strcmp(token, "nan"           ) == 0 )  helpfile = "cbot/nan";
    if ( strcmp(token, "true"          ) == 0 )  helpfile = "cbot/true";
    if ( strcmp(token, "false"         ) == 0 )  helpfile = "cbot/false";
    if ( strcmp(token, "sin"           ) == 0 )  helpfile = "cbot/sin";
    if ( strcmp(token, "cos"           ) == 0 )  helpfile = "cbot/cos";
    if ( strcmp(token, "tan"           ) == 0 )  helpfile = "cbot/tan";
    if ( strcmp(token, "asin"          ) == 0 )  helpfile = "cbot/asin";
    if ( strcmp(token, "acos"          ) == 0 )  helpfile = "cbot/acos";
    if ( strcmp(token, "atan"          ) == 0 )  helpfile = "cbot/atan";
    if ( strcmp(token, "atan2"         ) == 0 )  helpfile = "cbot/atan2";
    if ( strcmp(token, "sqrt"          ) == 0 )  helpfile = "cbot/sqrt";
    if ( strcmp(token, "pow"           ) == 0 )  helpfile = "cbot/pow";
    if ( strcmp(token, "rand"          ) == 0 )  helpfile = "cbot/rand";
    if ( strcmp(token, "abs"           ) == 0 )  helpfile = "cbot/abs";
    if ( strcmp(token, "floor"         ) == 0 )  helpfile = "cbot/floor";
    if ( strcmp(token, "ceil"          ) == 0 )  helpfile = "cbot/ceil";
    if ( strcmp(token, "round"         ) == 0 )  helpfile = "cbot/round";
    if ( strcmp(token, "trunc"         ) == 0 )  helpfile = "cbot/trunc";
    if ( strcmp(token, "retobject"     ) == 0 )  helpfile = "cbot/retobj";
    if ( strcmp(token, "errmode"       ) == 0 )  helpfile = "cbot/errmode";
    if ( strcmp(token, "isbusy"          ) == 0 )  helpfile = "cbot/isbusy";
    if ( strcmp(token, "takeoff"       ) == 0 )  helpfile = "cbot/takeoff";
    if ( strcmp(token, "research"      ) == 0 )  helpfile = "cbot/research";
    if ( strcmp(token, "factory"       ) == 0 )  helpfile = "cbot/factory";
    if ( strcmp(token, "destroy"       ) == 0 )  helpfile = "cbot/destroy";
    if ( strcmp(token, "search"        ) == 0 )  helpfile = "cbot/search";
    if ( strcmp(token, "searchall"     ) == 0 )  helpfile = "cbot/searchall";
    if ( strcmp(token, "radar"         ) == 0 )  helpfile = "cbot/radar";
    if ( strcmp(token, "radarall"      ) == 0 )  helpfile = "cbot/radarall";
    if ( strcmp(token, "direction"     ) == 0 )  helpfile = "cbot/direct";
    if ( strcmp(token, "distance"      ) == 0 )  helpfile = "cbot/dist";
    if ( strcmp(token, "distance2d"    ) == 0 )  helpfile = "cbot/dist2d";
    if ( strcmp(token, "space"         ) == 0 )  helpfile = "cbot/space";
    if ( strcmp(token, "flatspace"     ) == 0 )  helpfile = "cbot/flatspace";
    if ( strcmp(token, "flatground"    ) == 0 )  helpfile = "cbot/flatgrnd";
    if ( strcmp(token, "canbuild"       ) == 0 )  helpfile = "cbot/canbuild";
    if ( strcmp(token, "canresearch"    ) == 0 )  helpfile = "cbot/canresearch";
    if ( strcmp(token, "researched"     ) == 0 )  helpfile = "cbot/researched";
    if ( strcmp(token, "buildingenabled") == 0 )  helpfile = "cbot/buildingenabled";
    if ( strcmp(token, "build"         ) == 0 )  helpfile = "cbot/build";
    if ( strcmp(token, "flag"          ) == 0 )  helpfile = "cbot/flag";
    if ( strcmp(token, "deflag"        ) == 0 )  helpfile = "cbot/deflag";
    if ( strcmp(token, "wait"          ) == 0 )  helpfile = "cbot/wait";
    if ( strcmp(token, "move"          ) == 0 )  helpfile = "cbot/move";
    if ( strcmp(token, "turn"          ) == 0 )  helpfile = "cbot/turn";
    if ( strcmp(token, "goto"          ) == 0 )  helpfile = "cbot/goto";
    if ( strcmp(token, "grab"          ) == 0 )  helpfile = "cbot/grab";
    if ( strcmp(token, "drop"          ) == 0 )  helpfile = "cbot/drop";
    if ( strcmp(token, "sniff"         ) == 0 )  helpfile = "cbot/sniff";
    if ( strcmp(token, "receive"       ) == 0 )  helpfile = "cbot/receive";
    if ( strcmp(token, "send"          ) == 0 )  helpfile = "cbot/send";
    if ( strcmp(token, "deleteinfo"    ) == 0 )  helpfile = "cbot/delinfo";
    if ( strcmp(token, "testinfo"      ) == 0 )  helpfile = "cbot/testinfo";
    if ( strcmp(token, "thump"         ) == 0 )  helpfile = "cbot/thump";
    if ( strcmp(token, "recycle"       ) == 0 )  helpfile = "cbot/recycle";
    if ( strcmp(token, "shield"        ) == 0 )  helpfile = "cbot/shield";
    if ( strcmp(token, "fire"          ) == 0 )  helpfile = "cbot/fire";
    if ( strcmp(token, "antfire"       ) == 0 )  helpfile = "cbot/antfire";
    if ( strcmp(token, "aim"           ) == 0 )  helpfile = "cbot/aim";
    if ( strcmp(token, "motor"         ) == 0 )  helpfile = "cbot/motor";
    if ( strcmp(token, "jet"           ) == 0 )  helpfile = "cbot/jet";
    if ( strcmp(token, "topo"          ) == 0 )  helpfile = "cbot/topo";
    if ( strcmp(token, "message"       ) == 0 )  helpfile = "cbot/message";
    if ( strcmp(token, "abstime"       ) == 0 )  helpfile = "cbot/abstime";
    if ( strcmp(token, "Blue"          ) == 0 )  helpfile = "cbot/flag";
    if ( strcmp(token, "Red"           ) == 0 )  helpfile = "cbot/flag";
    if ( strcmp(token, "Green"         ) == 0 )  helpfile = "cbot/flag";
    if ( strcmp(token, "Yellow"        ) == 0 )  helpfile = "cbot/flag";
    if ( strcmp(token, "Violet"        ) == 0 )  helpfile = "cbot/flag";
    if ( strcmp(token, "BlackArrow"    ) == 0 )  helpfile = "cbot/pendown";
    if ( strcmp(token, "RedArrow"      ) == 0 )  helpfile = "cbot/pendown";
    if ( strcmp(token, "White"         ) == 0 )  helpfile = "cbot/pendown";
    if ( strcmp(token, "Black"         ) == 0 )  helpfile = "cbot/pendown";
    if ( strcmp(token, "Gray"          ) == 0 )  helpfile = "cbot/pendown";
    if ( strcmp(token, "LightGray"     ) == 0 )  helpfile = "cbot/pendown";
    if ( strcmp(token, "Pink"          ) == 0 )  helpfile = "cbot/pendown";
    if ( strcmp(token, "Purple"        ) == 0 )  helpfile = "cbot/pendown";
    if ( strcmp(token, "Orange"        ) == 0 )  helpfile = "cbot/pendown";
    if ( strcmp(token, "Beige"         ) == 0 )  helpfile = "cbot/pendown";
    if ( strcmp(token, "Brown"         ) == 0 )  helpfile = "cbot/pendown";
    if ( strcmp(token, "Skin"          ) == 0 )  helpfile = "cbot/pendown";
    if ( strcmp(token, "LightGreen"    ) == 0 )  helpfile = "cbot/pendown";
    if ( strcmp(token, "LightBlue"     ) == 0 )  helpfile = "cbot/pendown";
    if ( strcmp(token, "InFront"       ) == 0 )  helpfile = "cbot/grab";
    if ( strcmp(token, "Behind"        ) == 0 )  helpfile = "cbot/grab";
    if ( strcmp(token, "EnergyCell"    ) == 0 )  helpfile = "cbot/grab";
    if ( strcmp(token, "DisplayError"  ) == 0 )  helpfile = "cbot/message";
    if ( strcmp(token, "DisplayWarning") == 0 )  helpfile = "cbot/message";
    if ( strcmp(token, "DisplayInfo"   ) == 0 )  helpfile = "cbot/message";
    if ( strcmp(token, "DisplayMessage") == 0 )  helpfile = "cbot/message";
    if ( strcmp(token, "ResearchTracked"       ) == 0 )  helpfile = "cbot/researches";
    if ( strcmp(token, "ResearchWinged"        ) == 0 )  helpfile = "cbot/researches";
    if ( strcmp(token, "ResearchShooter"       ) == 0 )  helpfile = "cbot/researches";
    if ( strcmp(token, "ResearchDefenseTower"  ) == 0 )  helpfile = "cbot/researches";
    if ( strcmp(token, "ResearchNuclearPlant"  ) == 0 )  helpfile = "cbot/researches";
    if ( strcmp(token, "ResearchThumper"       ) == 0 )  helpfile = "cbot/researches";
    if ( strcmp(token, "ResearchShielder"      ) == 0 )  helpfile = "cbot/researches";
    if ( strcmp(token, "ResearchPhazerShooter" ) == 0 )  helpfile = "cbot/researches";
    if ( strcmp(token, "ResearchLegged"        ) == 0 )  helpfile = "cbot/researches";
    if ( strcmp(token, "ResearchOrgaShooter"   ) == 0 )  helpfile = "cbot/researches";
    if ( strcmp(token, "ResearchRecycler"      ) == 0 )  helpfile = "cbot/researches";
    if ( strcmp(token, "ResearchSubber"        ) == 0 )  helpfile = "cbot/researches";
    if ( strcmp(token, "ResearchSniffer"       ) == 0 )  helpfile = "cbot/researches";
    if ( strcmp(token, "strlen"        ) == 0 )  helpfile = "cbot/string";
    if ( strcmp(token, "strleft"       ) == 0 )  helpfile = "cbot/string";
    if ( strcmp(token, "strright"      ) == 0 )  helpfile = "cbot/string";
    if ( strcmp(token, "strmid"        ) == 0 )  helpfile = "cbot/string";
    if ( strcmp(token, "strval"        ) == 0 )  helpfile = "cbot/string";
    if ( strcmp(token, "strfind"       ) == 0 )  helpfile = "cbot/string";
    if ( strcmp(token, "strlower"      ) == 0 )  helpfile = "cbot/string";
    if ( strcmp(token, "strupper"      ) == 0 )  helpfile = "cbot/string";
    if ( strcmp(token, "open"          ) == 0 )  helpfile = "cbot/open";
    if ( strcmp(token, "close"         ) == 0 )  helpfile = "cbot/close";
    if ( strcmp(token, "writeln"       ) == 0 )  helpfile = "cbot/writeln";
    if ( strcmp(token, "readln"        ) == 0 )  helpfile = "cbot/readln";
    if ( strcmp(token, "eof"           ) == 0 )  helpfile = "cbot/eof";
    if ( strcmp(token, "deletefile"    ) == 0 )  helpfile = "cbot/deletef";
    if ( strcmp(token, "openfile"      ) == 0 )  helpfile = "cbot/openfile";
    if ( strcmp(token, "pendown"       ) == 0 )  helpfile = "cbot/pendown";
    if ( strcmp(token, "penup"         ) == 0 )  helpfile = "cbot/penup";
    if ( strcmp(token, "pencolor"      ) == 0 )  helpfile = "cbot/pencolor";
    if ( strcmp(token, "penwidth"      ) == 0 )  helpfile = "cbot/penwidth";
    if ( strcmp(token, "extern"        ) == 0 )  helpfile = "cbot/extern";
    if ( strcmp(token, "class"         ) == 0 )  helpfile = "cbot/class";
    if ( strcmp(token, "static"        ) == 0 )  helpfile = "cbot/static";
    if ( strcmp(token, "public"        ) == 0 )  helpfile = "cbot/public";
    if ( strcmp(token, "private"       ) == 0 )  helpfile = "cbot/private";
    if ( strcmp(token, "synchronized"  ) == 0 )  helpfile = "cbot/synchro";
    if ( strcmp(token, "new"           ) == 0 )  helpfile = "cbot/new";
    if ( strcmp(token, "this"          ) == 0 )  helpfile = "cbot/this";
    if ( strcmp(token, "switch"        ) == 0 ||
         strcmp(token, "case"          ) == 0 ||
         strcmp(token, "default"       ) == 0 )  helpfile = "cbot/switch";

    if (helpfile.empty())
        return "";

    return std::string("help/") + CApplication::GetInstancePointer()->GetLanguageChar() + "/" + helpfile + ".txt";
}


// Test if a keyword is a type of variable.

bool IsType(const char *token)
{
    if ( strcmp(token, "void"   ) == 0 )  return true;
    if ( strcmp(token, "byte"   ) == 0 )  return true;
    if ( strcmp(token, "short"  ) == 0 )  return true;
    if ( strcmp(token, "char"   ) == 0 )  return true;
    if ( strcmp(token, "int"    ) == 0 )  return true;
    if ( strcmp(token, "long"   ) == 0 )  return true;
    if ( strcmp(token, "float"  ) == 0 )  return true;
    if ( strcmp(token, "double" ) == 0 )  return true;
    if ( strcmp(token, "bool"   ) == 0 )  return true;
    if ( strcmp(token, "string" ) == 0 )  return true;
    if ( strcmp(token, "point"  ) == 0 )  return true;
    if ( strcmp(token, "object" ) == 0 )  return true;
    if ( strcmp(token, "file"   ) == 0 )  return true;
    return false;
}

// Test if a keyword is a function.

bool IsFunction(const char *token)
{
    if ( strcmp(token, "sin"          ) == 0 )  return true;
    if ( strcmp(token, "cos"          ) == 0 )  return true;
    if ( strcmp(token, "tan"          ) == 0 )  return true;
    if ( strcmp(token, "asin"         ) == 0 )  return true;
    if ( strcmp(token, "acos"         ) == 0 )  return true;
    if ( strcmp(token, "atan"         ) == 0 )  return true;
    if ( strcmp(token, "atan2"        ) == 0 )  return true;
    if ( strcmp(token, "sqrt"         ) == 0 )  return true;
    if ( strcmp(token, "pow"          ) == 0 )  return true;
    if ( strcmp(token, "rand"         ) == 0 )  return true;
    if ( strcmp(token, "abs"          ) == 0 )  return true;
    if ( strcmp(token, "floor"        ) == 0 )  return true;
    if ( strcmp(token, "ceil"         ) == 0 )  return true;
    if ( strcmp(token, "round"        ) == 0 )  return true;
    if ( strcmp(token, "trunc"        ) == 0 )  return true;
    if ( strcmp(token, "retobjectbyid") == 0 )  return true;
    if ( strcmp(token, "retobject"    ) == 0 )  return true;
    if ( strcmp(token, "isbusy"         ) == 0 )  return true;
    if ( strcmp(token, "factory"      ) == 0 )  return true;
    if ( strcmp(token, "research"     ) == 0 )  return true;
    if ( strcmp(token, "takeoff"      ) == 0 )  return true;
    if ( strcmp(token, "destroy"      ) == 0 )  return true;
    if ( strcmp(token, "search"       ) == 0 )  return true;
    if ( strcmp(token, "searchall"    ) == 0 )  return true;
    if ( strcmp(token, "radar"        ) == 0 )  return true;
    if ( strcmp(token, "radarall"     ) == 0 )  return true;
    if ( strcmp(token, "detect"       ) == 0 )  return true;
    if ( strcmp(token, "direction"    ) == 0 )  return true;
    if ( strcmp(token, "distance"     ) == 0 )  return true;
    if ( strcmp(token, "distance2d"   ) == 0 )  return true;
    if ( strcmp(token, "space"        ) == 0 )  return true;
    if ( strcmp(token, "flatspace"    ) == 0 )  return true;
    if ( strcmp(token, "flatground"   ) == 0 )  return true;
    if ( strcmp(token, "canbuild"       ) == 0 )  return true;
    if ( strcmp(token, "canresearch"    ) == 0 )  return true;
    if ( strcmp(token, "researched"     ) == 0 )  return true;
    if ( strcmp(token, "buildingenabled") == 0 )  return true;
    if ( strcmp(token, "build"        ) == 0 )  return true;
    if ( strcmp(token, "flag"         ) == 0 )  return true;
    if ( strcmp(token, "deflag"       ) == 0 )  return true;
    if ( strcmp(token, "wait"         ) == 0 )  return true;
    if ( strcmp(token, "move"         ) == 0 )  return true;
    if ( strcmp(token, "turn"         ) == 0 )  return true;
    if ( strcmp(token, "goto"         ) == 0 )  return true;
    if ( strcmp(token, "grab"         ) == 0 )  return true;
    if ( strcmp(token, "drop"         ) == 0 )  return true;
    if ( strcmp(token, "sniff"        ) == 0 )  return true;
    if ( strcmp(token, "receive"      ) == 0 )  return true;
    if ( strcmp(token, "send"         ) == 0 )  return true;
    if ( strcmp(token, "deleteinfo"   ) == 0 )  return true;
    if ( strcmp(token, "testinfo"     ) == 0 )  return true;
    if ( strcmp(token, "thump"        ) == 0 )  return true;
    if ( strcmp(token, "recycle"      ) == 0 )  return true;
    if ( strcmp(token, "shield"       ) == 0 )  return true;
    if ( strcmp(token, "fire"         ) == 0 )  return true;
    if ( strcmp(token, "antfire"      ) == 0 )  return true;
    if ( strcmp(token, "aim"          ) == 0 )  return true;
    if ( strcmp(token, "motor"        ) == 0 )  return true;
    if ( strcmp(token, "jet"          ) == 0 )  return true;
    if ( strcmp(token, "topo"         ) == 0 )  return true;
    if ( strcmp(token, "message"      ) == 0 )  return true;
    if ( strcmp(token, "abstime"      ) == 0 )  return true;
    if ( strcmp(token, "ismovie"      ) == 0 )  return true;
    if ( strcmp(token, "errmode"      ) == 0 )  return true;
    if ( strcmp(token, "ipf"          ) == 0 )  return true;
    if ( strcmp(token, "strlen"       ) == 0 )  return true;
    if ( strcmp(token, "strleft"      ) == 0 )  return true;
    if ( strcmp(token, "strright"     ) == 0 )  return true;
    if ( strcmp(token, "strmid"       ) == 0 )  return true;
    if ( strcmp(token, "strval"       ) == 0 )  return true;
    if ( strcmp(token, "strfind"      ) == 0 )  return true;
    if ( strcmp(token, "strlower"     ) == 0 )  return true;
    if ( strcmp(token, "strupper"     ) == 0 )  return true;
    if ( strcmp(token, "open"         ) == 0 )  return true;
    if ( strcmp(token, "close"        ) == 0 )  return true;
    if ( strcmp(token, "writeln"      ) == 0 )  return true;
    if ( strcmp(token, "readln"       ) == 0 )  return true;
    if ( strcmp(token, "eof"          ) == 0 )  return true;
    if ( strcmp(token, "deletefile"   ) == 0 )  return true;
    if ( strcmp(token, "openfile"     ) == 0 )  return true;
    if ( strcmp(token, "pendown"      ) == 0 )  return true;
    if ( strcmp(token, "penup"        ) == 0 )  return true;
    if ( strcmp(token, "pencolor"     ) == 0 )  return true;
    if ( strcmp(token, "penwidth"     ) == 0 )  return true;
    if ( strcmp(token, "camerafocus"  ) == 0 )  return true;
    if ( strcmp(token, "sizeof"       ) == 0 )  return true;
    return false;
}


// Returns using a compact instruction.

const char* GetHelpText(const char *token)
{
    if ( strcmp(token, "if"        ) == 0 )  return "if ( condition ) { code }";
    if ( strcmp(token, "else"      ) == 0 )  return "else { code }";
    if ( strcmp(token, "repeat"    ) == 0 )  return "repeat ( number )";
    if ( strcmp(token, "for"       ) == 0 )  return "for ( before ; condition ; end )";
    if ( strcmp(token, "while"     ) == 0 )  return "while ( condition ) { code }";
    if ( strcmp(token, "do"        ) == 0 )  return "do { code } while ( condition );";
    if ( strcmp(token, "switch"    ) == 0 )  return "switch ( value ) { code }";
    if ( strcmp(token, "case"      ) == 0 )  return "case label: { code }";
    if ( strcmp(token, "default"   ) == 0 )  return "default: { code } ";
    if ( strcmp(token, "break"     ) == 0 )  return "break;";
    if ( strcmp(token, "continue"  ) == 0 )  return "continue;";
    if ( strcmp(token, "return"    ) == 0 )  return "return;";
    if ( strcmp(token, "sizeof"    ) == 0 )  return "sizeof( array );";
    if ( strcmp(token, "int"       ) == 0 )  return "int";
    if ( strcmp(token, "sin"       ) == 0 )  return "sin ( angle );";
    if ( strcmp(token, "cos"       ) == 0 )  return "cos ( angle );";
    if ( strcmp(token, "tan"       ) == 0 )  return "tan ( angle );";
    if ( strcmp(token, "asin"      ) == 0 )  return "asin ( value );";
    if ( strcmp(token, "acos"      ) == 0 )  return "acos ( value );";
    if ( strcmp(token, "atan"      ) == 0 )  return "atan ( value );";
    if ( strcmp(token, "atan2"     ) == 0 )  return "atan2 ( y, x );";
    if ( strcmp(token, "sqrt"      ) == 0 )  return "sqrt ( value );";
    if ( strcmp(token, "pow"       ) == 0 )  return "pow ( x, y );";
    if ( strcmp(token, "rand"      ) == 0 )  return "rand ( );";
    if ( strcmp(token, "abs"       ) == 0 )  return "abs ( value );";
    if ( strcmp(token, "floor"     ) == 0 )  return "floor ( value );";
    if ( strcmp(token, "ceil"      ) == 0 )  return "ceil ( value );";
    if ( strcmp(token, "round"     ) == 0 )  return "round ( value );";
    if ( strcmp(token, "trunc"     ) == 0 )  return "trunc ( value );";
    if ( strcmp(token, "retobject"    ) == 0 )  return "retobject ( rank );";
    if ( strcmp(token, "retobjectbyid") == 0 )  return "retobjectbyid ( rank );";
    if ( strcmp(token, "progfunc"  ) == 0 )  return "progfunc ( funcname );";
    if ( strcmp(token, "isbusy"      ) == 0 )  return "isbusy ( object );";
    if ( strcmp(token, "factory"   ) == 0 )  return "factory ( cat, program, object );";
    if ( strcmp(token, "research"  ) == 0 )  return "research ( type, object );";
    if ( strcmp(token, "takeoff"   ) == 0 )  return "takeoff ( object );";
    if ( strcmp(token, "destroy"   ) == 0 )  return "destroy ( object );";
    if ( strcmp(token, "search"    ) == 0 )  return "search ( cat, pos, min, max, sens, filter );";
    if ( strcmp(token, "searchall" ) == 0 )  return "searchall ( cat, pos, min, max, sens, filter );";
    if ( strcmp(token, "radar"     ) == 0 )  return "radar ( cat, angle, focus, min, max, sens, filter );";
    if ( strcmp(token, "radarall"  ) == 0 )  return "radarall ( cat, angle, focus, min, max, sens, filter );";
    if ( strcmp(token, "detect"    ) == 0 )  return "detect ( cat );";
    if ( strcmp(token, "direction" ) == 0 )  return "direction ( position );";
    if ( strcmp(token, "distance2d") == 0 )  return "distance2d ( p1, p2 );";
    if ( strcmp(token, "distance"  ) == 0 )  return "distance ( p1, p2 );";
    if ( strcmp(token, "flatspace" ) == 0 )  return "flatspace ( center, flatmin, rmin, rmax, dist );";
    if ( strcmp(token, "space"     ) == 0 )  return "space ( center, rmin, rmax, dist );";
    if ( strcmp(token, "flatground") == 0 )  return "flatground ( center, rmax );";
    if ( strcmp(token, "canbuild"       ) == 0 )  return "canbuild ( category );";
    if ( strcmp(token, "canresearch"    ) == 0 )  return "canresearch ( research );";
    if ( strcmp(token, "researched"     ) == 0 )  return "researched ( research );";
    if ( strcmp(token, "buildingenabled") == 0 )  return "buildingenabled ( category );";
    if ( strcmp(token, "build"     ) == 0 )  return "build ( category );";
    if ( strcmp(token, "flag"      ) == 0 )  return "flag ( color );";
    if ( strcmp(token, "deflag"    ) == 0 )  return "deflag ( );";
    if ( strcmp(token, "wait"      ) == 0 )  return "wait ( time );";
    if ( strcmp(token, "move"      ) == 0 )  return "move ( distance );";
    if ( strcmp(token, "turn"      ) == 0 )  return "turn ( angle );";
    if ( strcmp(token, "goto"      ) == 0 )  return "goto ( position, altitude );";
    if ( strcmp(token, "grab"      ) == 0 )  return "grab ( order );";
    if ( strcmp(token, "drop"      ) == 0 )  return "drop ( order );";
    if ( strcmp(token, "sniff"     ) == 0 )  return "sniff ( );";
    if ( strcmp(token, "receive"   ) == 0 )  return "receive ( name, power );";
    if ( strcmp(token, "send"      ) == 0 )  return "send ( name, value, power );";
    if ( strcmp(token, "deleteinfo") == 0 )  return "deleteinfo ( name, power );";
    if ( strcmp(token, "testinfo"  ) == 0 )  return "testinfo ( name, power );";
    if ( strcmp(token, "thump"     ) == 0 )  return "thump ( );";
    if ( strcmp(token, "recycle"   ) == 0 )  return "recycle ( );";
    if ( strcmp(token, "shield"    ) == 0 )  return "shield ( oper, radius );";
    if ( strcmp(token, "fire"      ) == 0 )  return "fire ( time );";
    if ( strcmp(token, "aim"       ) == 0 )  return "aim ( y, x );";
    if ( strcmp(token, "motor"     ) == 0 )  return "motor ( left, right );";
    if ( strcmp(token, "jet"       ) == 0 )  return "jet ( power );";
    if ( strcmp(token, "topo"      ) == 0 )  return "topo ( position );";
    if ( strcmp(token, "message"   ) == 0 )  return "message ( string, type );";
    if ( strcmp(token, "abstime"   ) == 0 )  return "abstime ( );";
    if ( strcmp(token, "ismovie"   ) == 0 )  return "ismovie ( );";
    if ( strcmp(token, "errmode"   ) == 0 )  return "errmode ( mode );";
    if ( strcmp(token, "ipf"       ) == 0 )  return "ipf ( number );";
    if ( strcmp(token, "strlen"    ) == 0 )  return "strlen ( string );";
    if ( strcmp(token, "strleft"   ) == 0 )  return "strleft ( string, len );";
    if ( strcmp(token, "strright"  ) == 0 )  return "strright ( string, len );";
    if ( strcmp(token, "strmid"    ) == 0 )  return "strmid ( string, pos, len );";
    if ( strcmp(token, "strval"    ) == 0 )  return "strval ( string );";
    if ( strcmp(token, "strfind"   ) == 0 )  return "strfind ( string, substring );";
    if ( strcmp(token, "strlower"  ) == 0 )  return "strlower ( string );";
    if ( strcmp(token, "strupper"  ) == 0 )  return "strupper ( string );";
    if ( strcmp(token, "open"      ) == 0 )  return "file.open ( filename, mode );";
    if ( strcmp(token, "close"     ) == 0 )  return "file.close ( );";
    if ( strcmp(token, "writeln"   ) == 0 )  return "file.writeln ( string );";
    if ( strcmp(token, "readln"    ) == 0 )  return "file.readln ( );";
    if ( strcmp(token, "eof"       ) == 0 )  return "eof ( );";
    if ( strcmp(token, "deletefile") == 0 )  return "deletefile ( filename );";
    if ( strcmp(token, "openfile"  ) == 0 )  return "openfile ( filename, mode );";
    if ( strcmp(token, "pendown"   ) == 0 )  return "pendown ( color, width );";
    if ( strcmp(token, "penup"     ) == 0 )  return "penup ( );";
    if ( strcmp(token, "pencolor"  ) == 0 )  return "pencolor ( color );";
    if ( strcmp(token, "penwidth"  ) == 0 )  return "penwidth ( width );";
    if ( strcmp(token, "camerafocus") == 0 )  return "camerafocus ( object );";
    return "";
}
