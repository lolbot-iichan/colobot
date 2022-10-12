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
 * \file object/details/creation_details.cpp
 * \brief CObjectCreationDetails - set of tweaks for Creation objects
 */

#include "level/parser/parser.h"

#include "object/details/details_provider.h"
#include "object/details/hardcode.h"
#include "object/details/macro.h"
#include "object/details/creation_details.h"

void CObjectCreationDetails::ReadHardcode(ObjectType type)
{
    CHardcodeCollection hardcode;

    baseClass              = hardcode.GetCreationBaseClass(type);
    autoClass              = hardcode.GetCreationAutoClass(type);

    isForceLoadTextures    = hardcode.IsCreationForceLoadTextures(type);
    isSetFloorHeight       = hardcode.IsCreationSetFloorHeight(type);
    isFloorAdjust          = hardcode.IsCreationFloorAdjust(type);
    isFixedPosition        = hardcode.IsCreationFixedPosition(type);
    zoom                   = hardcode.GetCreationScale(type);

    cameraCollisionSphere  = hardcode.GetCreationCameraCollisionSphere(type);
    shadowCircle           = hardcode.GetCreationShadowCircle(type);

    model                  = hardcode.GetCreationModel(type);
    crashSpheres           = hardcode.GetCreationCrashSpheres(type);
    buildingLevels         = hardcode.GetCreationBuildingLevels(type);

    displayedName          = hardcode.GetDisplayedName(type);
}

bool CObjectCreationDetails::Read(CLevelParserLine* line)
{
    READ_LINE( "SetObjectCreation" );
    READ_ARG( "baseClass",     AsInt,    baseClass           );
    READ_ARG( "autoClass",     AsInt,    autoClass           );
    READ_END();

    READ_LINE( "SetObjectModel" );
    READ_ARG( "forceTextures", AsBool,   isForceLoadTextures );
    READ_ARG( "floorHeight",   AsBool,   isSetFloorHeight    );
    READ_ARG( "floorAdjust",   AsBool,   isFloorAdjust       );
    READ_ARG( "fixedPos",      AsBool,   isFixedPosition     );
    READ_ARG( "zoom",          AsFloat,  zoom                );
    READ_ARG( "name",          AsString, displayedName       );
    READ_END();

    READ_LINE( "SetObjectModelCameraCollisionSphere" );
    READ_ARG( "position",  AsPoint,            cameraCollisionSphere.pos    );
    READ_ARG( "radius",    AsFloat,            cameraCollisionSphere.radius );
    READ_END();

    READ_LINE( "SetObjectModelShadowCircle" );
    READ_ARG( "radius",    AsFloat,            shadowCircle.radius    );
    READ_ARG( "intensity", AsFloat,            shadowCircle.intensity );
    READ_ARG( "shadow",    AsEngineShadowType, shadowCircle.shadowType    );
    READ_ARG( "factored",  AsBool,             shadowCircle.factored  );
    READ_END();

    READ_LINE( "AddObjectModelNode" );
    READ_NEW( id,                              model);
    READ_ARG( "partNum",   AsInt,              model[id].chunkId   );
    READ_ARG( "parent",    AsInt,              model[id].parentId  );
    READ_ARG( "gfxType",   AsEngineObjectType, model[id].gfxType );
    READ_ARG( "modFile",   AsString,           model[id].modFile   );
    READ_ARG( "position",  AsPoint,            model[id].position  );
    READ_ARG( "rotation",  AsPoint,            model[id].rotation  );
    READ_ARG( "zoom",      AsPoint,            model[id].zoom      );
    READ_ARG( "mirrored",  AsBool,             model[id].mirrored  );
    READ_ARG( "copyModel", AsBool,             model[id].copyModel );
    READ_END();

    READ_LINE( "AddObjectModelCrashSphere" );
    READ_NEW( id,                              crashSpheres);
    READ_ARG( "pos",       AsPoint,            crashSpheres[id].sphere.pos    );
    READ_ARG( "radius",    AsFloat,            crashSpheres[id].sphere.radius );
    READ_ARG( "sound",     AsSoundType,        crashSpheres[id].sound         );
    READ_ARG( "hardness",  AsFloat,            crashSpheres[id].hardness      );
    READ_END();

    READ_LINE( "AddObjectModelBuildingLevel" );
    READ_NEW( id,                              buildingLevels);
    READ_ARG( "min",       AsFloat,            buildingLevels[id].min    );
    READ_ARG( "max",       AsFloat,            buildingLevels[id].max    );
    READ_ARG( "height",    AsFloat,            buildingLevels[id].height );
    READ_ARG( "factor",    AsFloat,            buildingLevels[id].factor );
    READ_END();

    READ_LINE( "UpdObjectModelCrashSphere" );
    READ_IDX( id );
    READ_ARG( "pos",       AsPoint,            crashSpheres[id].sphere.pos    );
    READ_ARG( "radius",    AsFloat,            crashSpheres[id].sphere.radius );
    READ_ARG( "sound",     AsSoundType,        crashSpheres[id].sound         );
    READ_ARG( "hardness",  AsFloat,            crashSpheres[id].hardness      );
    READ_END();

    return false;
}

void CObjectCreationDetails::Write(CLevelParser* parser, ObjectType type)
{
    CObjectCreationDetails def;

    WRITE_LINE( "SetObjectCreation" );
    WRITE_ARG( "baseClass",     def, baseClass           );
    WRITE_ARG( "autoClass",     def, autoClass           );
    WRITE_END();

    WRITE_LINE( "SetObjectModel" );
    WRITE_ARG( "forceTextures", def, isForceLoadTextures );
    WRITE_ARG( "floorHeight",   def, isSetFloorHeight    );
    WRITE_ARG( "floorAdjust",   def, isFloorAdjust       );
    WRITE_ARG( "fixedPos",      def, isFixedPosition     );
    WRITE_ARG( "zoom",          def, zoom                );
    WRITE_ARG( "name",          def, displayedName       );
    WRITE_END();

    WRITE_LINE( "SetObjectModelCameraCollisionSphere" );
    WRITE_ARG( "position",      def, cameraCollisionSphere.pos    );
    WRITE_ARG( "radius",        def, cameraCollisionSphere.radius );
    WRITE_END();

    WRITE_LINE( "SetObjectModelShadowCircle" );
    WRITE_ARG( "radius",        def, shadowCircle.radius     );
    WRITE_ARG( "intensity",     def, shadowCircle.intensity  );
    WRITE_ARG( "shadow",        def, shadowCircle.shadowType );
    WRITE_ARG( "factored",      def, shadowCircle.factored   );
    WRITE_END();

    CObjectCreationModelNode defM;
    for ( auto it : model )
    {
        WRITE_LINE( "AddObjectModelNode" );
        WRITE_IT( "partNum",  defM, chunkId   );
        WRITE_IT( "parent",   defM, parentId  );
        WRITE_IT( "gfxType",  defM, gfxType   );
        WRITE_IT( "modFile",  defM, modFile   );
        WRITE_IT( "position", defM, position  );
        WRITE_IT( "rotation", defM, rotation  );
        WRITE_IT( "zoom",     defM, zoom      );
        WRITE_IT( "mirrored", defM, mirrored  );
        WRITE_IT( "copyModel",defM, copyModel );
        WRITE_END();
    }

    CrashSphere defC;
    for ( auto it : crashSpheres )
    {
        WRITE_LINE( "AddObjectModelCrashSphere" );
        WRITE_IT( "pos",      defC, sphere.pos    );
        WRITE_IT( "radius",   defC, sphere.radius );
        WRITE_IT( "sound",    defC, sound         );
        WRITE_IT( "hardness", defC, hardness      );
        WRITE_END();
    }

    CObjectCreationBuildingLevel defB;
    for ( auto it : buildingLevels )
    {
        WRITE_LINE( "AddObjectModelBuildingLevel" );
        WRITE_IT( "min",      defB, min    );
        WRITE_IT( "max",      defB, max    );
        WRITE_IT( "height",   defB, height );
        WRITE_IT( "factor",   defB, factor );
        WRITE_END();
    }
}

CObjectCreationDetails GetObjectCreationDetails(CObject* obj)
{
    return CObjectDetails::GetInstance().GetObjectDetails(obj).creation;
}

CObjectCreationDetails GetObjectCreationDetails(ObjectType type)
{
    return CObjectDetails::GetInstance().GetObjectDetails(type).creation;
}