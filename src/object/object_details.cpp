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

#include <unordered_set>

#include "object/object_details.h"
#include "object/object_details_hardcode.h"

/* Macro to mark which texts are translatable by gettext
 * It doesn't do anything at compile-time, as all texts represented here are used later
 * in explicit call to gettext(), but it is used by xgettext executable to filter extracted
 * texts from this file.
 */
#define TR(x) x

/* Please run `cmake --build <path_to_build_folder> --target update-pot`
 * after changing this file in order to update translation files. Thank you.
 */

CObjectDetails::CObjectDetails()
{
    m_builderMenuObjects[0]  = { OBJECT_RESEARCH, 128+35, TR("Build a research center") };
    m_builderMenuObjects[1]  = { OBJECT_FACTORY,  128+32, TR("Build a bot factory") };
    m_builderMenuObjects[2]  = { OBJECT_CONVERT,  128+34, TR("Build a converter") };
    m_builderMenuObjects[3]  = { OBJECT_STATION,  128+36, TR("Build a power station") };
    m_builderMenuObjects[4]  = { OBJECT_RADAR,    128+40, TR("Build a radar station") };
    m_builderMenuObjects[5]  = { OBJECT_REPAIR,   128+41, TR("Build a repair center") };
    m_builderMenuObjects[6]  = { OBJECT_INFO,     128+44, TR("Build a exchange post") };
    m_builderMenuObjects[7]  = { OBJECT_TOWER,    128+37, TR("Build a defense tower") };
    m_builderMenuObjects[8]  = { OBJECT_ENERGY,   128+39, TR("Build a power cell factory") };
    m_builderMenuObjects[9]  = { OBJECT_DERRICK,  128+33, TR("Build a derrick") };
    m_builderMenuObjects[10] = { OBJECT_NUCLEAR,  128+42, TR("Build a nuclear power plant") };
    m_builderMenuObjects[11] = { OBJECT_LABO,     128+38, TR("Build an autolab") };
    m_builderMenuObjects[12] = { OBJECT_PARA,     128+46, TR("Build a lightning conductor") };
    m_builderMenuObjects[13] = { OBJECT_SAFE,     128+47, TR("Build a vault") };

    m_debugMenuObjects[0]  = {OBJECT_HUMAN,    128+8,  ""};
    m_debugMenuObjects[1]  = {OBJECT_MOBILEwa, 128+9,  ""};
    m_debugMenuObjects[2]  = {OBJECT_MOBILEwc, 128+15, ""};
    m_debugMenuObjects[3]  = {OBJECT_MOBILErc, 128+19, ""};
    m_debugMenuObjects[4]  = {OBJECT_FACTORY,  128+32, ""};
    m_debugMenuObjects[5]  = {OBJECT_CONVERT,  128+34, ""};
    m_debugMenuObjects[6]  = {OBJECT_DERRICK,  128+33, ""};
    m_debugMenuObjects[7]  = {OBJECT_STATION,  128+36, ""};
    m_debugMenuObjects[8]  = {OBJECT_METAL,    -1,     "Titanium"};
    m_debugMenuObjects[9]  = {OBJECT_STONE,    -1,     "TitaniumOre"};
    m_debugMenuObjects[10] = {OBJECT_URANIUM,  -1,     "UraniumOre"};
    m_debugMenuObjects[11] = {OBJECT_POWER,    -1,     "PowerCell"};
    m_debugMenuObjects[12] = {OBJECT_ATOMIC,   -1,     "NuclearCell"};

    Clear();
    LoadHardcode();
    Load("object_details.txt");
    Dump("object_details.sav");
}

void CObjectDetails::Clear()
{
    m_objects.clear();
    m_nameToType.clear();
    m_assistant = CObjectAssistantDetails();
}

void CObjectDetails::LoadHardcode()
{
    for ( int i = 0 ; i < OBJECT_MAX ; i++ )
    {
        ObjectType type = static_cast<ObjectType>(i);

        m_objects[type].naming     = GetObjectNamingDetailsHardcode(type);
        m_objects[type].scripting  = GetObjectScriptingDetailsHardcode(type);
        m_objects[type].creation   = GetObjectCreationDetailsHardcode(type);
        m_objects[type].common     = GetObjectCommonInterfaceDetailsHardcode(type);
        m_objects[type].camera     = GetObjectCameraDetailsHardcode(type);
        m_objects[type].physics    = GetObjectPhysicsDetailsHardcode(type);
        m_objects[type].automation = GetObjectAutomationDetailsHardcode(type);
        m_objects[type].icons      = GetObjectIconDetailsHardcode(type);
        m_objects[type].controls   = GetObjectControlsDetailsHardcode(type);

        auto levelNaming = m_objects[type].naming.level;
        if ( levelNaming.name.size() )
            m_nameToType[levelNaming.name] = type;
        if ( levelNaming.alias.size() )
            m_nameToType[levelNaming.alias] = type;
    }
    
    m_assistant = GetObjectAssistantDetailsHardcode();
}

#define CHK_LINE(C)       (line->GetCommand() == C)
#define CACHE_VAL(N,P)    auto N = m_objects[type].P;
#define STORE_VAL(N,P)    m_objects[type].P = N;
#define READ_RAW(K,A,N)   auto N = line->GetParam(K)->A();
#define READ_VAL(K,A,N,O) auto N = line->GetParam(K)->A(O);
#define PUSH_ARR(I,P)     CACHE_VAL(I, P.size()); m_objects[type].P.resize(I+1);

#define READ_LINE(C)      if (CHK_LINE(C)) { READ_RAW("type",AsObjectType,type);
#define READ_ARG(K,A,P)   { CACHE_VAL(x,P); READ_VAL(K,A,y,x); STORE_VAL(y,P); }
#define READ_END()        }


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
        if ( CHK_LINE("NewObject") ) {
            READ_RAW( "type",  GetValue, typeStr );
            READ_RAW( "value", AsInt,    typeInt );

            ObjectType type = static_cast<ObjectType>(typeInt);
            m_objects[type].naming.level.name = typeStr;
            m_nameToType[typeStr] = type;
        }

        READ_LINE( "SetObjectShortcutIcon" );
        READ_ARG( "isBuilding", AsBool, icons.shortcut.isBuilding );
        READ_ARG( "isMovable",  AsBool, icons.shortcut.isMovable );
        READ_ARG( "icon",       AsInt,  icons.shortcut.icon );
        READ_END();

        READ_LINE( "SetObjectTransportable" );
        READ_ARG( "enabled",    AsBool, common.transportable.enabled);
        READ_END();

        READ_LINE( "SetObjectControllable" );
        READ_ARG( "enabled",    AsBool, common.controllable.enabled);
        READ_ARG( "selectable", AsBool, common.controllable.selectable);
        READ_END();

        READ_LINE( "SetObjectMovable" );
        READ_ARG( "enabled",    AsBool, common.movable.enabled);
        READ_END();

        READ_LINE( "SetObjectLinearMotion" );
        READ_ARG( "advanceAccel", AsPoint, common.movable.linMotion.advanceAccel );
        READ_ARG( "recedeAccel",  AsPoint, common.movable.linMotion.recedeAccel  );
        READ_ARG( "stopAccel",    AsPoint, common.movable.linMotion.stopAccel    );
        READ_ARG( "motorAccel",   AsPoint, common.movable.linMotion.motorAccel   );
        READ_ARG( "advanceSpeed", AsPoint, common.movable.linMotion.advanceSpeed );
        READ_ARG( "recedeSpeed",  AsPoint, common.movable.linMotion.recedeSpeed  );
        READ_ARG( "motorSpeed",   AsPoint, common.movable.linMotion.motorSpeed   );
        READ_ARG( "currentSpeed", AsPoint, common.movable.linMotion.currentSpeed );
        READ_ARG( "terrainForce", AsPoint, common.movable.linMotion.terrainForce );
        READ_ARG( "terrainSpeed", AsPoint, common.movable.linMotion.terrainSpeed );
        READ_ARG( "terrainSlide", AsPoint, common.movable.linMotion.terrainSlide );
        READ_ARG( "realSpeed",    AsPoint, common.movable.linMotion.realSpeed    );
        READ_ARG( "finalInclin",  AsPoint, common.movable.linMotion.finalInclin  );
        READ_END();

        READ_LINE( "SetObjectCircularMotion" );
        READ_ARG( "advanceAccel", AsPoint, common.movable.cirMotion.advanceAccel );
        READ_ARG( "recedeAccel",  AsPoint, common.movable.cirMotion.recedeAccel  );
        READ_ARG( "stopAccel",    AsPoint, common.movable.cirMotion.stopAccel    );
        READ_ARG( "motorAccel",   AsPoint, common.movable.cirMotion.motorAccel   );
        READ_ARG( "advanceSpeed", AsPoint, common.movable.cirMotion.advanceSpeed );
        READ_ARG( "recedeSpeed",  AsPoint, common.movable.cirMotion.recedeSpeed  );
        READ_ARG( "motorSpeed",   AsPoint, common.movable.cirMotion.motorSpeed   );
        READ_ARG( "currentSpeed", AsPoint, common.movable.cirMotion.currentSpeed );
        READ_ARG( "terrainForce", AsPoint, common.movable.cirMotion.terrainForce );
        READ_ARG( "terrainSpeed", AsPoint, common.movable.cirMotion.terrainSpeed );
        READ_ARG( "terrainSlide", AsPoint, common.movable.cirMotion.terrainSlide );
        READ_ARG( "realSpeed",    AsPoint, common.movable.cirMotion.realSpeed    );
        READ_ARG( "finalInclin",  AsPoint, common.movable.cirMotion.finalInclin  );
        READ_END();

        READ_LINE( "SetObjectJetFlying" );
        READ_ARG( "enabled",    AsBool, common.jet.enabled);
        READ_END();

        READ_LINE( "SetObjectModel" );
        READ_ARG( "scale",         AsFloat, creation.scale);
        READ_ARG( "forceTextures", AsBool, creation.isForceLoadTextures);
        READ_END();

        READ_LINE( "AddObjectModelNode" );
        PUSH_ARR( id,                         creation.model );
        READ_ARG( "chunkId",   AsInt,         creation.model[id].chunkId   );
        READ_ARG( "parentId",  AsInt,         creation.model[id].parentId  );
        READ_ARG( "gfxType",   AsTerrainType, creation.model[id].gfxType   );
        READ_ARG( "modFile",   AsString,      creation.model[id].modFile   );
        READ_ARG( "position",  AsPoint,       creation.model[id].position  );
        READ_ARG( "rotation",  AsPoint,       creation.model[id].rotation  );
        READ_ARG( "copyModel", AsBool,        creation.model[id].copyModel );
        READ_END();

        READ_LINE( "AddObjectCrashSphere" );
        PUSH_ARR( id,                      creation.crashSpheres );
        READ_ARG( "pos",      AsPoint,     creation.crashSpheres[id].sphere.pos    );
        READ_ARG( "radius",   AsFloat,     creation.crashSpheres[id].sphere.radius    );
//TODO        READ_ARG( "sound",    AsSoundType, creation.crashSpheres[id].sound );
        READ_ARG( "hardness", AsFloat,     creation.crashSpheres[id].hardness );
        READ_END();

        READ_LINE( "AddObjectBuildingLevel" );
        PUSH_ARR( id,                creation.buildingLevels );
        READ_ARG( "min",    AsFloat, creation.buildingLevels[id].min    );
        READ_ARG( "max",    AsFloat, creation.buildingLevels[id].max    );
        READ_ARG( "height", AsFloat, creation.buildingLevels[id].height );
        READ_ARG( "factor", AsFloat, creation.buildingLevels[id].factor );
        READ_END();

        READ_LINE( "AddObjectUILogo" );
        PUSH_ARR( id,                                  controls.widgets );
        READ_ARG( "position",                AsPoint,  controls.widgets[id].position );
        READ_ARG( "size",                    AsPoint,  controls.widgets[id].size );
        READ_ARG( "icon",                    AsInt,    controls.widgets[id].params.icon );
//TODO        READ_ARG( "event",                   AsEventType,    controls.widgets[id].event );
        READ_ARG( "default",                 AsBool,   controls.widgets[id].isDefault );
        READ_ARG( "immediat",                AsBool,   controls.widgets[id].isImmediat );
        READ_ARG( "disabledByTrainer",       AsBool,   controls.widgets[id].disabledByTrainer );
        READ_ARG( "disabledByPlusExplorer",  AsBool,   controls.widgets[id].disabledByPlusExplorer );
        READ_END();

        READ_LINE( "SetObjectAutomationProduction" );
        READ_ARG( "input",  AsObjectType, automation.production.input );
        READ_ARG( "output", AsObjectType, automation.production.output );
        READ_END();

        READ_LINE( "SetAssistant" );
        m_assistant.type = type;
        READ_END();
    }
}

#define NEW_LINE(C)        auto line = MakeUnique<CLevelParserLine>(C);
#define WRITE_VAL(K,V)     line->AddParam((K),MakeUnique<CLevelParserParam>(V));
#define WRITE_FORCE()      bWrite = true;

#define WRITE_LINE(C)      { bool bWrite = false; NEW_LINE(C); WRITE_VAL("type",type);
#define WRITE_ARG(K,O,D,P) if((O.P) != (D.P)) { WRITE_FORCE(); WRITE_VAL((K),(O.P)); }
#define WRITE_END()        if(bWrite) { dumper->AddLine(std::move(line)); } }

void CObjectDetails::Dump(const char* fname)
{
    CLevelParser parser(fname);

    for (int i = 0; i < OBJECT_MAX; i++)
    {
        ObjectType type = static_cast<ObjectType>(i);
        DumpObjectNamingDetails(&parser, type);
        DumpObjectScriptingDetails(&parser, type);
        DumpObjectCreationDetails(&parser, type);
        DumpObjectCommonInterfaceDetails(&parser, type);
        DumpObjectCameraDetails(&parser, type);
        DumpObjectPhysicsDetails(&parser, type);
        DumpObjectAutomationDetails(&parser, type);
        DumpObjectIconDetails(&parser, type);
        DumpObjectControlsDetails(&parser, type);
    }
    DumpObjectAssistantDetails(&parser);

    parser.Save();
}

ObjectType CObjectDetails::ParseObjectTypeFromName(std::string value)
{
    auto it = m_nameToType.find(value);
    if (it != m_nameToType.end())
        return it->second;
    return OBJECT_NULL;
}




//////////////////////////////////////////////////////////////////////////////
// Object naming details
//////////////////////////////////////////////////////////////////////////////

void CObjectDetails::DumpObjectNamingDetails(CLevelParser* dumper, ObjectType type)
{
    CObjectNamingDetails obj = GetObjectDetails(type).naming;
    CObjectNamingDetails def;

    WRITE_LINE( "NewObject" );
    WRITE_VAL( "value", int(type) );
    WRITE_ARG( "type", obj, def, level.name );
    WRITE_ARG( "alias", obj, def, level.alias );
    WRITE_END();

    WRITE_LINE( "SetObjectScriptName" );
    WRITE_VAL( "value", int(type) );
    WRITE_ARG( "name", obj, def, script.name );
    WRITE_ARG( "alias", obj, def, script.alias );
    WRITE_ARG( "help", obj, def, script.helpTopicPath );
    WRITE_END();

    WRITE_LINE( "SetObjectDisplayName" );
    WRITE_ARG( "name", obj, def, display.name );
    WRITE_ARG( "usePlayerName", obj, def, display.usePlayerName );
    WRITE_END();
}

CObjectNamingDetails CObjectDetails::GetObjectNamingDetailsHardcode(ObjectType type)
{
    CObjectNamingDetails result;
    CObjectDetailsHardcodeCollection hardcode;

    result.level.name            = hardcode.GetNameInLevelFiles(type);
    result.level.alias           = hardcode.GetAliasInLevelFiles(type);

    result.script.name           = hardcode.GetNameInScriptFiles(type);
    result.script.alias          = hardcode.GetAliasInScriptFiles(type);
    result.script.helpTopicPath  = hardcode.GetHelpTopicPathName(type);

    result.display.name          = hardcode.GetDisplayedName(type);
    result.display.usePlayerName = hardcode.IsDisplayedNameAsPlayer(type);

    return result;   
}



//////////////////////////////////////////////////////////////////////////////
// Object scripting details
//////////////////////////////////////////////////////////////////////////////

void CObjectDetails::DumpObjectScriptingDetails(CLevelParser* dumper, ObjectType type)
{
    CObjectScriptingDetails obj = GetObjectDetails(type).scripting;
    CObjectScriptingDetails def;

    WRITE_LINE( "SetObjectAllowedScripting" );
    WRITE_ARG( "build", obj, def, allowed.build );
    WRITE_ARG( "flag", obj, def, allowed.flag );
    WRITE_ARG( "sniff", obj, def, allowed.sniff );
    WRITE_ARG( "shield", obj, def, allowed.shield );
    WRITE_ARG( "recycle", obj, def, allowed.recycle );
    WRITE_ARG( "rPen", obj, def, allowed.penAsRobot )
    WRITE_ARG( "hGrab", obj, def, allowed.grabAsHuman );
    WRITE_ARG( "rGrab", obj, def, allowed.grabAsRobot );
    WRITE_ARG( "aShoot", obj, def, allowed.shootAsAnt );
    WRITE_ARG( "sShoot", obj, def, allowed.shootAsSpider );
    WRITE_ARG( "rShoot", obj, def, allowed.shootAsRobot );
    WRITE_END();

    WRITE_LINE( "SetObjectScriptingWithRadar" );
    WRITE_ARG( "explicit", obj, def, radar.isExplicit );
//TODO    WRITE_ARG( "find", obj, def, radar.findableWithThisType );
    WRITE_END();

    WRITE_LINE( "SetObjectScriptingWithProduce" );
    WRITE_ARG( "producable", obj, def, produce.isProducable );
    WRITE_ARG( "charge", obj, def, produce.isProducedCharged );
    WRITE_ARG( "manual", obj, def, produce.isProducedManual );
    WRITE_ARG( "container", obj, def, produce.container );
    WRITE_END();
}

CObjectScriptingDetails CObjectDetails::GetObjectScriptingDetailsHardcode(ObjectType type)
{
    CObjectScriptingDetails result;
    CObjectDetailsHardcodeCollection hardcode;

    result.allowed.build = hardcode.IsFunctionImplementedBuild(type);
    result.allowed.flag = hardcode.IsFunctionImplementedFlags(type);
    result.allowed.sniff = hardcode.IsFunctionImplementedSniff(type);
    result.allowed.shield = hardcode.IsFunctionImplementedShield(type);
    result.allowed.recycle = hardcode.IsFunctionImplementedRecycle(type);
    result.allowed.penAsRobot = hardcode.IsFunctionImplementedDrawAsRobot(type);
    result.allowed.grabAsHuman = hardcode.IsFunctionImplementedGrabAsHuman(type);
    result.allowed.grabAsRobot = hardcode.IsFunctionImplementedGrabAsRobot(type);
    result.allowed.shootAsAnt = hardcode.IsFunctionImplementedShootAsAnt(type);
    result.allowed.shootAsSpider = hardcode.IsFunctionImplementedShootAsSpider(type);
    result.allowed.shootAsRobot = hardcode.IsFunctionImplementedShootAsRobot(type);

    result.radar.isExplicit = hardcode.IsRadarExplicitOnly(type);
    result.radar.findableWithThisType = hardcode.GetObjectsFindableByType(type);

    result.produce.isProducable = hardcode.IsValidObjectTypeId(type);
    result.produce.isProducedCharged = hardcode.IsProduceAlreadyCharged(type);
    result.produce.isProducedManual = hardcode.IsProduceManual(type);
    result.produce.container = hardcode.GetProduceContainer(type);

    return result;   
}



//////////////////////////////////////////////////////////////////////////////
// Creation details
//////////////////////////////////////////////////////////////////////////////

void CObjectDetails::DumpObjectCreationDetails(CLevelParser* dumper, ObjectType type)
{
    CObjectCreationDetails obj = GetObjectDetails(type).creation;
    CObjectCreationDetails def;

    WRITE_LINE( "SetObjectModel" );
    WRITE_ARG( "scale", obj, def, scale );
    WRITE_ARG( "forceTextures", obj, def, isForceLoadTextures );
    WRITE_END();

    CObjectCreationModelNode defM;
    for ( auto it : obj.model )
    {
        WRITE_LINE( "AddObjectModelNode" );
        WRITE_ARG( "chunkId",  it, defM, chunkId   );
        WRITE_ARG( "parentId", it, defM, parentId  );
        WRITE_ARG( "gfxType",  it, defM, gfxType   );
        WRITE_ARG( "modFile",  it, defM, modFile   );
        WRITE_ARG( "position", it, defM, position  );
        WRITE_ARG( "rotation", it, defM, rotation  );
        WRITE_ARG( "copyModel",it, defM, copyModel );
        WRITE_END();
    }

    CrashSphere defC;
    for ( auto it : obj.crashSpheres )
    {
        WRITE_LINE( "AddObjectCrashSphere" );
        WRITE_ARG( "pos",      it, defC, sphere.pos    );
        WRITE_ARG( "radius",   it, defC, sphere.radius );
        WRITE_ARG( "sound",    it, defC, sound         );
        WRITE_ARG( "hardness", it, defC, hardness      );
        WRITE_END();
    }

    CObjectCreationBuildingLevel defB;
    for ( auto it : obj.buildingLevels )
    {
        WRITE_LINE( "AddObjectBuildingLevel" );
        WRITE_ARG( "min",    it, defB, min    );
        WRITE_ARG( "max",    it, defB, max    );
        WRITE_ARG( "height", it, defB, height );
        WRITE_ARG( "factor", it, defB, factor );
        WRITE_END();
    }
}

CObjectCreationDetails CObjectDetails::GetObjectCreationDetailsHardcode(ObjectType type)
{
    CObjectCreationDetails result;
    CObjectDetailsHardcodeCollection hardcode;

    result.baseClass = hardcode.GetCreationBaseClass(type);
    
    result.model = hardcode.GetCreationModel(type);
    result.crashSpheres = hardcode.GetCreationCrashSpheres(type);
    result.cameraCollisionSpheres= hardcode.GetCreationCameraCollisionSpheres(type);
    result.jostlingSpheres = hardcode.GetCreationJostlingSpheres(type);
    result.buildingLevels = hardcode.GetCreationBuildingLevels(type);
    result.shadowCircle = hardcode.GetCreationShadowCircle(type);

    result.scale = hardcode.GetCreationScale(type);

    result.isForceLoadTextures = hardcode.IsCreationForceLoadTextures(type);

    result.isSetFloorHeight = hardcode.IsCreationSetFloorHeight(type);
    result.isFloorAdjust = hardcode.IsCreationFloorAdjust(type);
    result.isFixedPosition = hardcode.IsCreationFixedPosition(type);

    return result;   
}



//////////////////////////////////////////////////////////////////////////////
// Common interface details
//////////////////////////////////////////////////////////////////////////////

void CObjectDetails::DumpObjectCommonInterfaceDetails(CLevelParser* dumper, ObjectType type)
{
    CObjectCommonInterfaceDetails obj = GetObjectDetails(type).common;
    CObjectCommonInterfaceDetails def;

    WRITE_LINE( "SetObjectTransportable" );
    WRITE_ARG( "enabled", obj, def, transportable.enabled );
    WRITE_END();

    WRITE_LINE( "SetObjectMovable" );
    WRITE_ARG( "enabled", obj, def, movable.enabled );
    WRITE_END();

    WRITE_LINE( "SetObjectLinearMotion" );
    WRITE_ARG( "advanceAccel", obj, def, movable.linMotion.advanceAccel );
    WRITE_ARG( "recedeAccel",  obj, def, movable.linMotion.recedeAccel  );
    WRITE_ARG( "stopAccel",    obj, def, movable.linMotion.stopAccel    );
    WRITE_ARG( "motorAccel",   obj, def, movable.linMotion.motorAccel   );
    WRITE_ARG( "advanceSpeed", obj, def, movable.linMotion.advanceSpeed );
    WRITE_ARG( "recedeSpeed",  obj, def, movable.linMotion.recedeSpeed  );
    WRITE_ARG( "motorSpeed",   obj, def, movable.linMotion.motorSpeed   );
    WRITE_ARG( "currentSpeed", obj, def, movable.linMotion.currentSpeed );
    WRITE_ARG( "terrainForce", obj, def, movable.linMotion.terrainForce );
    WRITE_ARG( "terrainSpeed", obj, def, movable.linMotion.terrainSpeed );
    WRITE_ARG( "terrainSlide", obj, def, movable.linMotion.terrainSlide );
    WRITE_ARG( "realSpeed",    obj, def, movable.linMotion.realSpeed    );
    WRITE_ARG( "finalInclin",  obj, def, movable.linMotion.finalInclin  );
    WRITE_END();

    WRITE_LINE( "SetObjectCircularMotion" );
    WRITE_ARG( "advanceAccel", obj, def, movable.cirMotion.advanceAccel );
    WRITE_ARG( "recedeAccel",  obj, def, movable.cirMotion.recedeAccel  );
    WRITE_ARG( "stopAccel",    obj, def, movable.cirMotion.stopAccel    );
    WRITE_ARG( "motorAccel",   obj, def, movable.cirMotion.motorAccel   );
    WRITE_ARG( "advanceSpeed", obj, def, movable.cirMotion.advanceSpeed );
    WRITE_ARG( "recedeSpeed",  obj, def, movable.cirMotion.recedeSpeed  );
    WRITE_ARG( "motorSpeed",   obj, def, movable.cirMotion.motorSpeed   );
    WRITE_ARG( "currentSpeed", obj, def, movable.cirMotion.currentSpeed );
    WRITE_ARG( "terrainForce", obj, def, movable.cirMotion.terrainForce );
    WRITE_ARG( "terrainSpeed", obj, def, movable.cirMotion.terrainSpeed );
    WRITE_ARG( "terrainSlide", obj, def, movable.cirMotion.terrainSlide );
    WRITE_ARG( "realSpeed",    obj, def, movable.cirMotion.realSpeed    );
    WRITE_ARG( "finalInclin",  obj, def, movable.cirMotion.finalInclin  );
    WRITE_END();

    WRITE_LINE( "SetObjectWheels" );
    WRITE_ARG( "front",  obj, def, movable.wheels.wheelFront );
    WRITE_ARG( "back",   obj, def, movable.wheels.wheelBack  );
    WRITE_ARG( "left",   obj, def, movable.wheels.wheelLeft  );
    WRITE_ARG( "right",  obj, def, movable.wheels.wheelRight );
    WRITE_ARG( "height", obj, def, movable.wheels.height     );
    WRITE_END();

    WRITE_LINE( "SetObjectFlying" );
    WRITE_ARG( "enabled", obj, def, flying.enabled );
    WRITE_END();

    WRITE_LINE( "SetObjectJetFlying" );
    WRITE_ARG( "enabled", obj, def, jet.enabled );
    WRITE_END();

    WRITE_LINE( "SetObjectControllable" );
    WRITE_ARG( "enabled", obj, def, controllable.enabled );
    WRITE_ARG( "selectable", obj, def, controllable.selectable );
    WRITE_END();

    WRITE_LINE( "SetObjectPowerContainer" );
    WRITE_ARG( "enabled", obj, def, power.enabled );
    WRITE_END();

    WRITE_LINE( "SetObjectRanged" );
    WRITE_ARG( "enabled", obj, def, ranged.enabled );
    WRITE_ARG( "radius", obj, def, ranged.radius );
    WRITE_END();

    WRITE_LINE( "SetObjectTraceDrawing" );
    WRITE_ARG( "enabled", obj, def, drawing.enabled );
    WRITE_ARG( "penAnimated", obj, def, drawing.penAnimated );
    WRITE_END();

    WRITE_LINE( "SetObjectDamagable" );
    WRITE_ARG( "enabled", obj, def, damageable.enabled );
    WRITE_ARG( "fImmune", obj, def, damageable.isImmuneToFireballs );
    WRITE_ARG( "iImmune", obj, def, damageable.isImmuneToInsects );
    WRITE_ARG( "sImmune", obj, def, damageable.isImmuneToSpiders );
    WRITE_ARG( "wImmune", obj, def, damageable.isImmuneToOrgaballs );
    WRITE_ARG( "pImmune", obj, def, damageable.isImmuneToPhazers );
    WRITE_ARG( "rImmune", obj, def, damageable.isImmuneToTowerRay );
    WRITE_END();

    WRITE_LINE( "SetObjectDestroyable" );
    WRITE_ARG( "enabled", obj, def, destroyable.enabled );
    WRITE_ARG( "removeBuildingLevel", obj, def, destroyable.removeBuildingLevel );
    WRITE_ARG( "eEffect", obj, def, destroyable.explosion.effect );
    WRITE_ARG( "wEffect", obj, def, destroyable.water.effect );
    WRITE_ARG( "wExplode", obj, def, destroyable.water.explodeInWater );
    WRITE_ARG( "bEffect", obj, def, destroyable.burning.effect );
    WRITE_ARG( "bKills", obj, def, destroyable.burning.isKilledByBurning );
    WRITE_ARG( "dEffect", obj, def, destroyable.drowned.effect );
    WRITE_ARG( "xEffect", obj, def, destroyable.win.effect );
    WRITE_ARG( "sEffect", obj, def, destroyable.squash.effect );
    WRITE_ARG( "sByHeavy", obj, def, destroyable.squash.squashedByHeavy );
    WRITE_END();

    WRITE_LINE( "SetObjectFragile" );
    WRITE_ARG( "enabled", obj, def, fragile.enabled );
    WRITE_END();

    WRITE_LINE( "SetObjectShielded" );
    WRITE_ARG( "enabled", obj, def, shielded.enabled );
    WRITE_END();

    WRITE_LINE( "SetObjectShieldedAutoRegen" );
    WRITE_ARG( "enabled", obj, def, autoregen.enabled );
    WRITE_ARG( "time", obj, def, autoregen.time );
    WRITE_END();

    WRITE_LINE( "SetObjectSloted" );
    WRITE_ARG( "enabled", obj, def, sloted.enabled );
    WRITE_ARG( "cSlot",   obj, def, sloted.cargo.enabled );
    WRITE_ARG( "cPos",    obj, def, sloted.cargo.position );
    WRITE_ARG( "pSlot",   obj, def, sloted.power.enabled );
    WRITE_ARG( "pPos",    obj, def, sloted.power.position );
    WRITE_ARG( "oSlot",   obj, def, sloted.other.enabled );
    WRITE_ARG( "oPos",    obj, def, sloted.other.position );
    WRITE_END();
}

CObjectCommonInterfaceDetails CObjectDetails::GetObjectCommonInterfaceDetailsHardcode(ObjectType type)
{
    CObjectCommonInterfaceDetails result;
    CObjectDetailsHardcodeCollection hardcode;

    result.transportable.enabled = hardcode.IsTransportable(type);

    result.movable.enabled = hardcode.IsMovable(type);
    result.movable.linMotion = hardcode.GetLinMotion(type);
    result.movable.cirMotion = hardcode.GetCirMotion(type);
    result.movable.wheels = hardcode.GetWheels(type);

    result.flying.enabled = hardcode.IsFlying(type);

    result.jet.enabled = hardcode.IsJetFlying(type);

    result.controllable.enabled = hardcode.IsControllable(type);
    result.controllable.selectable = hardcode.IsSelectableByDefault(type);

    result.power.enabled = hardcode.IsPowerContainer(type);

    result.ranged.enabled = hardcode.IsRanged(type);;
    result.ranged.radius = hardcode.GetRangedRadius(type);

    result.drawing.enabled = hardcode.IsTraceDrawing(type);
    result.drawing.penAnimated = hardcode.IsFunctionImplementedDrawAsRobot(type);

    result.damageable.enabled = hardcode.IsDamageable(type);
    result.damageable.isImmuneToFireballs = hardcode.IsImmuneToFireballs(type);
    result.damageable.isImmuneToInsects = hardcode.IsImmuneToInsects(type);
    result.damageable.isImmuneToSpiders = hardcode.IsImmuneToSpiders(type);
    result.damageable.isImmuneToOrgaballs = hardcode.IsImmuneToOrgaballs(type);
    result.damageable.isImmuneToPhazers = hardcode.IsImmuneToPhazers(type);
    result.damageable.isImmuneToTowerRay = hardcode.IsImmuneToTowerRays(type);

    result.destroyable.enabled = hardcode.IsDestroyable(type);
    result.destroyable.removeBuildingLevel = hardcode.IsDestructionRemoveBuildingLevel(type);
    result.destroyable.explosion.effect = hardcode.GetDestructionByExplosion(type);
    result.destroyable.water.effect = hardcode.GetDestructionByWater(type);
    result.destroyable.water.explodeInWater = hardcode.IsExplodesInWater(type);
    result.destroyable.burning.effect = hardcode.GetDestructionByBurning(type);
    result.destroyable.burning.isKilledByBurning = hardcode.IsDestructionKilledByBurning(type);
    result.destroyable.drowned.effect = hardcode.GetDestructionByDrowned(type);
    result.destroyable.win.effect = hardcode.GetDestructionByWin(type);
    result.destroyable.squash.effect = hardcode.GetDestructionBySquash(type);
    result.destroyable.squash.squashedByHeavy = hardcode.IsSquashedByHeavy(type);

    result.fragile.enabled = hardcode.IsFragile(type);

    result.shielded.enabled = hardcode.IsShielded(type);

    result.autoregen.enabled = hardcode.IsShieldAutoregen(type);
    result.autoregen.time = hardcode.GetShieldAutoregenTime(type);
    
    result.sloted.enabled         = hardcode.IsSloted(type);
    result.sloted.cargo.enabled   = hardcode.HasCargoSlot(type);
//TODO    result.sloted.cargo.position = hardcode.xxxxxx(type);
    result.sloted.power.enabled   = hardcode.HasPowerSlot(type);
    result.sloted.power.position  = hardcode.GetPowerSlotPosition(type);
    result.sloted.other.enabled   = hardcode.HasOtherSlot(type);
    result.sloted.other.position  = hardcode.GetOtherSlotPosition(type);

    return result;   
}



//////////////////////////////////////////////////////////////////////////////
// Camera details
//////////////////////////////////////////////////////////////////////////////

void CObjectDetails::DumpObjectCameraDetails(CLevelParser* dumper, ObjectType type)
{
    CObjectCameraDetails obj = GetObjectDetails(type).camera;
    CObjectCameraDetails def;

    WRITE_LINE( "SetObjectCamera" );
    WRITE_ARG( "changable",  obj, def, isCameraTypeChangable );
    WRITE_ARG( "persistent", obj, def, isCameraTypePersistent );
    WRITE_ARG( "default", obj, def, defaultCamera );
    WRITE_END();

    WRITE_LINE( "SetObjectCameraVisit" );
    WRITE_ARG( "dist", obj, def, visitCamera.distance );
    WRITE_ARG( "height", obj, def, visitCamera.height );
    WRITE_END();

    WRITE_LINE( "SetObjectCameraFixed" );
    WRITE_ARG( "noCollision", obj, def, fixCamera.disableCollisions );
    WRITE_END();

    WRITE_LINE( "SetObjectCameraOnboard" );
    WRITE_ARG( "noCorners", obj, def, onboardCamera.disableCorners );
    WRITE_ARG( "hasCrosshair", obj, def, onboardCamera.hasCrosshair );
    WRITE_END();

    WRITE_LINE( "SetObjectCameraBack" );
    WRITE_ARG( "dist", obj, def, backCamera.distance );
    WRITE_ARG( "min", obj, def, backCamera.distanceMin );
    WRITE_ARG( "height", obj, def, backCamera.height );
    WRITE_ARG( "yRot", obj, def, backCamera.rotationY );
    WRITE_ARG( "zRot", obj, def, backCamera.rotationZ );
    WRITE_END();

    WRITE_LINE( "SetObjectCameraBackTransparency" );
    WRITE_ARG( "disableForOthers", obj, def, backCamera.disableOtherObjectsTransparency );
    WRITE_ARG( "disableForThis", obj, def, backCamera.disableObjectTransparency );
    WRITE_ARG( "gateHack", obj, def, backCamera.hasGateTransparency );
    WRITE_END();
}

CObjectCameraDetails CObjectDetails::GetObjectCameraDetailsHardcode(ObjectType type)
{
    CObjectCameraDetails result;
    CObjectDetailsHardcodeCollection hardcode;

    result.isCameraTypeChangable         = hardcode.IsCameraTypeChangable(type);
    result.isCameraTypePersistent        = hardcode.IsCameraTypePersistent(type);
    result.defaultCamera                 = hardcode.GetDefaultCameraType(type);

    result.visitCamera.distance          = hardcode.GetVisitCameraDistance(type);
    result.visitCamera.height            = hardcode.GetVisitCameraHeight(type);

    result.backCamera.distance           = hardcode.GetBackCameraDistance(type);
    result.backCamera.distanceMin        = hardcode.GetBackCameraDistanceMin(type);
    result.backCamera.height             = hardcode.GetBackCameraHeight(type);
    result.backCamera.rotationY          = hardcode.GetBackCameraRotationY(type);
    result.backCamera.rotationZ          = hardcode.GetBackCameraRotationZ(type);

    result.backCamera.disableOtherObjectsTransparency = hardcode.DisableBackCameraCanForceTransparency(type);
    result.backCamera.disableObjectTransparency       = hardcode.DisableBackCameraCanViewAsTransparent(type);
    result.backCamera.hasGateTransparency             = hardcode.HasGateTransparencyOnBackCamera(type);

    result.fixCamera.disableCollisions   = hardcode.DisableCollisionsOnFixCamera(type);

    result.onboardCamera.disableCorners  = hardcode.DisableOnboardCameraCorners(type);
    result.onboardCamera.hasCrosshair    = hardcode.HasOnboardCameraCrosshair(type);

    return result;   
}



//////////////////////////////////////////////////////////////////////////////
// Physics details
//////////////////////////////////////////////////////////////////////////////

void CObjectDetails::DumpObjectPhysicsDetails(CLevelParser* dumper, ObjectType type)
{
    CObjectPhysicsDetails obj = GetObjectDetails(type).physics;
    CObjectPhysicsDetails def;

    WRITE_LINE( "SetObjectExhaustPhysics" );
    WRITE_ARG( "bubblesOnEnteringWater",  obj, def, exhaust.bubblesOnEnteringWater );
    WRITE_ARG( "bubblesOnEnteringWaterTime",  obj, def, exhaust.bubblesOnEnteringWaterTime );
//TODO
    WRITE_END();
}

CObjectPhysicsDetails CObjectDetails::GetObjectPhysicsDetailsHardcode(ObjectType type)
{
    CObjectPhysicsDetails result;
    CObjectDetailsHardcodeCollection hardcode;

    result.exhaust.bubblesOnEnteringWater   = hardcode.IsExhaustBubblesOnEnteringWater(type);
    result.exhaust.bubblesOnEnteringWaterTime = hardcode.IsExhaustBubblesOnEnteringWaterTime(type);
    result.exhaust.dropsOnLeavingWater     = hardcode.IsExhaustDropsOnLeavingWater(type);
    result.exhaust.onCrashAsHuman          = hardcode.IsExhaustOnCrashAsHuman(type);
    result.exhaust.onCrashAsTrackedRobot   = hardcode.IsExhaustOnCrashAsTrackedRobot(type);
    result.exhaust.onCrashAsHeavyRobot     = hardcode.IsExhaustOnCrashAsHeavyRobot(type);
    result.exhaust.onLandAsHuman           = hardcode.IsExhaustOnLandAsHuman(type);
    result.exhaust.onLandAsWingedRobot     = hardcode.IsExhaustOnLandAsWingedRobot(type);
    result.exhaust.onLandAsHeavyRobot      = hardcode.IsExhaustOnLandAsHeavyRobot      (type);
    result.exhaust.onLandAsNormalRobot     = hardcode.IsExhaustOnLandAsNormalRobot(type);
    result.exhaust.onFlightAsHuman         = hardcode.IsExhaustOnFlightAsHuman(type);
    result.exhaust.onFlightAsWingedRobot   = hardcode.IsExhaustOnFlightAsWingedRobot   (type);
    result.exhaust.onSwimAsHuman           = hardcode.IsExhaustOnSwimAsHuman(type);
    result.exhaust.onSwimAsAmphibiousRobot = hardcode.IsExhaustOnSwimAsAmphibiousRobot(type);

    result.thumper.safeRadius              = hardcode.GetThumperSafeRadius(type);
    result.thumper.effect                  = hardcode.GetThumperPyroType(type);
    result.thumper.explosionDamage         = hardcode.GetThumperExplosionDamage(type);
    result.thumper.turnOnBack              = hardcode.GetThumperTurnOnBack(type);

    result.lightning.lightningRodHeight    = hardcode.GetLightningRodHeight(type);

    result.water.waterLevel                = hardcode.GetMaxSafeWaterLevel(type);
    result.water.splashLevelMin            = hardcode.GetWaterSplashLevelMin(type);
    result.water.splashLevelMax            = hardcode.GetWaterSplashLevelMax(type);
    result.water.splashDiameter            = hardcode.GetWaterSplashDiameter(type);
    result.water.splashForce               = hardcode.GetWaterSplashForce(type);

    result.collisionOtherObjectRadiusToIgnore = hardcode.GetCollisionOtherObjectRadiusToIgnore(type);
    result.isCollisionDamagable            = hardcode.IsCollisionDamagable(type);
    result.collisionSoftness               = hardcode.GetCollisionSoftness(type);

    return result;
}




//////////////////////////////////////////////////////////////////////////////
// Automation Details
//////////////////////////////////////////////////////////////////////////////

void CObjectDetails::DumpObjectAutomationDetails(CLevelParser* dumper, ObjectType type)
{
    CObjectAutomationDetails obj = GetObjectDetails(type).automation;
    CObjectAutomationDetails def;

    WRITE_LINE( "SetObjectAutomationBlock" );
    WRITE_ARG( "building",   obj, def, blocking.blocksBuilding    );
    WRITE_ARG( "powerplant", obj, def, blocking.blocksPowerPlant  );
    WRITE_ARG( "nuclear",    obj, def, blocking.blocksNuclearPlant);
    WRITE_ARG( "factory",    obj, def, blocking.blocksFactory     );
    WRITE_END();

    WRITE_LINE( "SetObjectAutomationTarget" );
    WRITE_ARG( "byTower",        obj, def, targeted.attackedByTower       );
    WRITE_ARG( "byMushroom",     obj, def, targeted.attackedByMushroom    );
    WRITE_ARG( "byPowerStation", obj, def, targeted.chargedByPowerStation );
    WRITE_ARG( "byAssistant",    obj, def, targeted.commentedByAssistant  );
    WRITE_END();

    WRITE_LINE( "SetObjectAutomationProduction" );
    WRITE_ARG( "input", obj, def, production.input );
    WRITE_ARG( "output", obj, def, production.output );
    WRITE_END();
}

CObjectAutomationDetails CObjectDetails::GetObjectAutomationDetailsHardcode(ObjectType type)
{
    CObjectAutomationDetails result;
    CObjectDetailsHardcodeCollection hardcode;

    result.blocking.blocksBuilding        = hardcode.IsBlockingBuilding(type);
    result.blocking.blocksPowerPlant      = hardcode.IsAutoBlockingPowerPlant(type);
    result.blocking.blocksNuclearPlant    = hardcode.IsAutoBlockingNuclearPlant(type);
    result.blocking.blocksFactory         = hardcode.IsAutoBlockingFactory(type);

    result.targeted.attackedByTower       = hardcode.IsAutoTargetedByTower(type);
    result.targeted.attackedByMushroom    = hardcode.IsAutoTargetedByMushroom(type);
    result.targeted.chargedByPowerStation = hardcode.IsAutoChargedAtPowerStation(type);
    result.targeted.commentedByAssistant  = hardcode.IsAutoCommentedByAssistant(type);

    result.production.input               = hardcode.GetProductionInput(type);
    result.production.output              = hardcode.GetProductionOutput(type);

    return result;   
}



//////////////////////////////////////////////////////////////////////////////
// UI Icon details
//////////////////////////////////////////////////////////////////////////////

void CObjectDetails::DumpObjectIconDetails(CLevelParser* dumper, ObjectType type)
{
    CObjectIconDetails obj = GetObjectDetails(type).icons;
    CObjectIconDetails def;

    WRITE_LINE( "SetObjectMapIcon" );
    WRITE_ARG( "color", obj, def, map.color );
    WRITE_ARG( "icon", obj, def, map.icon );
    WRITE_ARG( "forced", obj, def, map.isForced );
    WRITE_END();

    WRITE_LINE( "SetObjectShortcutIcon" );
    WRITE_ARG( "isBuilding", obj, def, shortcut.isBuilding );
    WRITE_ARG( "isMovable", obj, def, shortcut.isMovable );
    WRITE_ARG( "icon", obj, def, shortcut.icon );
    WRITE_END();
}

CObjectIconDetails CObjectDetails::GetObjectIconDetailsHardcode(ObjectType type)
{
    CObjectIconDetails result;
    CObjectDetailsHardcodeCollection hardcode;

    result.map.color           = hardcode.GetMapIconColor(type);
    result.map.icon            = hardcode.GetMapIcon(type);
    result.map.isForced        = hardcode.GetMapShowEvenUnselectable(type);

    result.shortcut.isBuilding = hardcode.IsShortcutBuilding(type);
    result.shortcut.isMovable  = hardcode.IsShortcutMovable(type);
    result.shortcut.icon       = hardcode.GetShortcutIcon(type);

    return result;   
}

//////////////////////////////////////////////////////////////////////////////
// User Interface Details
//////////////////////////////////////////////////////////////////////////////

void CObjectDetails::DumpObjectControlsDetails(CLevelParser* dumper, ObjectType type)
{
    CObjectControlsDetails obj = GetObjectDetails(type).controls;
    CObjectControlsDetails def;

    WRITE_LINE( "SetObjectUIProgram" );
    WRITE_ARG( "enable", obj, def, hasProgramUI );
    WRITE_ARG( "blink", obj, def, hasProgramUIBlink );
    WRITE_END();

    for ( auto it: obj.widgets )
    {
        CObjectControlsWidget defW;
        if ( it.type == WIDGET_ICON_BUTTON )
        {
            WRITE_LINE( "AddObjectUIButton" );
            WRITE_ARG( "icon", it, defW, params.icon );
            WRITE_ARG( "position", it, defW, position );
            WRITE_ARG( "size", it, defW, size );
            WRITE_ARG( "event", it, defW, event );
            WRITE_ARG( "default", it, defW, isDefault );
            WRITE_ARG( "immediat", it, defW, isImmediat );
            WRITE_ARG( "disabledByTrainer", it, defW, disabledByTrainer );
            WRITE_ARG( "disabledByPlusExplorer", it, defW, disabledByPlusExplorer );
            WRITE_END();
        }
        else if ( it.type == WIDGET_COLOR_BUTTON )
        {
            WRITE_LINE( "AddObjectUIColor" );
            WRITE_ARG( "color", it, defW, params.color );
            WRITE_ARG( "position", it, defW, position );
            WRITE_ARG( "size", it, defW, size );
            WRITE_ARG( "event", it, defW, event );
            WRITE_ARG( "default", it, defW, isDefault );
            WRITE_ARG( "disabledByTrainer", it, defW, disabledByTrainer );
            WRITE_ARG( "disabledByPlusExplorer", it, defW, disabledByPlusExplorer );
            WRITE_END();
        }
        else if ( it.type == WIDGET_ICON_LOGO )
        {
            WRITE_LINE( "AddObjectUILogo" );
            WRITE_ARG( "icon", it, defW, params.icon );
            WRITE_ARG( "position", it, defW, position );
            WRITE_ARG( "size", it, defW, size );
            WRITE_ARG( "event", it, defW, event );
            WRITE_ARG( "default", it, defW, isDefault );
            WRITE_ARG( "immediat", it, defW, isImmediat );
            WRITE_ARG( "disabledByTrainer", it, defW, disabledByTrainer );
            WRITE_ARG( "disabledByPlusExplorer", it, defW, disabledByPlusExplorer );
            WRITE_END();
        }
    }

    WRITE_LINE( "SetObjectUISpecial" );
    WRITE_ARG( "hBuilder", obj, def, hasBuilderUIHuman );
    WRITE_ARG( "rBuilder", obj, def, hasBuilderUIRobot );
    WRITE_ARG( "rShielder", obj, def, hasShielderUIRobot );
    WRITE_ARG( "rScribbler", obj, def, hasScribblerUIRobot );
    WRITE_ARG( "noFlyWhileGrab", obj, def, disableFlyWhileGrabbing );
    WRITE_END();
}

CObjectControlsDetails CObjectDetails::GetObjectControlsDetailsHardcode(ObjectType type)
{
    CObjectControlsDetails result;
    CObjectDetailsHardcodeCollection hardcode;

    result.hasProgramUI            = hardcode.HasUserInterfaceProgramUI(type);
    result.hasProgramUIBlink       = hardcode.HasUserInterfaceProgramUIBlink(type);

    result.widgets                 = hardcode.GetUserInterfaceWidgetList(type);

    result.hasBuilderUIHuman       = hardcode.HasUserInterfaceBuilderUIHuman(type);
    result.hasBuilderUIRobot       = hardcode.HasUserInterfaceBuilderUIRobot(type);
    result.hasShielderUIRobot      = hardcode.HasUserInterfaceShielderUIRobot(type);
    result.hasScribblerUIRobot     = hardcode.HasUserInterfaceScribblerUIRobot(type);

    result.disableFlyWhileGrabbing = hardcode.HasUserInterfaceDisableFlyWhileGrabbing(type);

    return result;   
}

//////////////////////////////////////////////////////////////////////////////
// Assistant global details
//////////////////////////////////////////////////////////////////////////////

void CObjectDetails::DumpObjectAssistantDetails(CLevelParser* dumper)
{
    CObjectAssistantDetails obj = m_assistant;
    CObjectAssistantDetails def;

    ObjectType type = obj.type;
    if ( type != OBJECT_NULL )
    {
        WRITE_LINE( "SetAssistant" );
        WRITE_ARG( "reactOnSatcom", obj, def, reactOnSatcom );
        WRITE_ARG( "reactOnMessages", obj, def, reactOnMessages );
        WRITE_ARG( "moveWithCamera", obj, def, moveWithCamera );
        WRITE_ARG( "ignoreOnSaveLoad", obj, def, ignoreOnSaveLoad );
        WRITE_ARG( "clickable", obj, def, clickable );
        WRITE_ARG( "undamageable", obj, def, undamageable );
        WRITE_ARG( "unpausable", obj, def, unpausable );
        WRITE_FORCE();
        WRITE_END();
    }
}

CObjectAssistantDetails CObjectDetails::GetObjectAssistantDetailsHardcode()
{
    CObjectAssistantDetails result;
    CObjectDetailsHardcodeCollection hardcode;

    result.type = hardcode.GetAssistantType();
    result.reactOnSatcom = hardcode.IsAssistantReactingOnDisplayedInfo();
    result.reactOnMessages = hardcode.IsAssistantReactingOnDisplayedText();
    result.moveWithCamera = hardcode.IsAssistantIgnoredOnSaveLoad();
    result.ignoreOnSaveLoad = hardcode.IsAssistantMovesWithCamera();
    result.clickable = hardcode.IsAssistantClickable();
    result.undamageable = hardcode.IsAssistantUndamagable();
    result.unpausable = hardcode.IsAssistantUnpausable();

    return result;   
}



//////////////////////////////////////////////////////////////////////////////
// Unsorted
//////////////////////////////////////////////////////////////////////////////

CObjectButton CObjectDetails::GetBuilderMenuItem(int index)
{
    if (index < 0 || index >= 14) return CObjectButton();
    return m_builderMenuObjects[index];
}

CObjectButton CObjectDetails::GetDebugMenuItem(int index)
{
    if (index < 0 || index >= 14) return CObjectButton();
    return m_debugMenuObjects[index];
}

ObjectType CObjectDetails::GetFunctionDestroyPerformerObject()
{
    return OBJECT_DESTROYER;
}

ObjectType CObjectDetails::GetFunctionFactoryPerformerObject()
{
    return OBJECT_FACTORY;
}

ObjectType CObjectDetails::GetFunctionResearchPerformerObject(ResearchType type)
{
    if ( type == RESEARCH_iPAW       ||
         type == RESEARCH_iGUN       ||
         type == RESEARCH_TARGET      ) return OBJECT_LABO;
    return OBJECT_RESEARCH;
}

ObjectType CObjectDetails::GetFunctionTakeOffPerformerObject()
{
    return OBJECT_BASE;
}

ObjectType CObjectDetails::GetFunctionReceivePerformerObject()
{
    return OBJECT_INFO;
}
