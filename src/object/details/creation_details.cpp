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
    READ_ARG( "class", AsInt, baseClass );
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
    READ_ARG( "radius",    AsFloat,            shadowCircle.radius     );
    READ_ARG( "intensity", AsFloat,            shadowCircle.intensity  );
    READ_ARG( "shadow",    AsEngineShadowType, shadowCircle.shadowType );
    READ_ARG( "factored",  AsBool,             shadowCircle.factored   );
    READ_END();

    READ_IT_LINE( "AddObjectModelNode", "UpdObjectModelNode", "ClrObjectModelNode", model );
    READ_IT_ARG( "partNum",   AsInt,              chunkId   );
    READ_IT_ARG( "parent",    AsInt,              parentId  );
    READ_IT_ARG( "gfxType",   AsEngineObjectType, gfxType   );
    READ_IT_ARG( "modFile",   AsString,           modFile   );
    READ_IT_ARG( "position",  AsPoint,            position  );
    READ_IT_ARG( "rotation",  AsPoint,            rotation  );
    READ_IT_ARG( "zoom",      AsPoint,            zoom      );
    READ_IT_ARG( "mirrored",  AsBool,             mirrored  );
    READ_IT_ARG( "copyModel", AsBool,             copyModel );
    READ_IT_END();

    READ_IT_LINE( "AddObjectModelCrashSphere", "UpdObjectModelCrashSphere", "ClrObjectModelCrashSphere", crashSpheres );
    READ_IT_ARG( "position",  AsPoint,            sphere.pos    );
    READ_IT_ARG( "radius",    AsFloat,            sphere.radius );
    READ_IT_ARG( "sound",     AsSoundType,        sound         );
    READ_IT_ARG( "hardness",  AsFloat,            hardness      );
    READ_IT_END();

    READ_IT_LINE( "AddObjectModelBuildingLevel", "UpdObjectModelBuildingLevel", "ClrObjectModelBuildingLevel", buildingLevels );
    READ_IT_ARG( "min",       AsFloat,            min    );
    READ_IT_ARG( "max",       AsFloat,            max    );
    READ_IT_ARG( "height",    AsFloat,            height );
    READ_IT_ARG( "factor",    AsFloat,            factor );
    READ_IT_END();

    return false;
}

void CObjectCreationDetails::Write(CLevelParser* parser, ObjectType type)
{
    WRITE_LINE( "SetObjectCreation" );
    WRITE_ARG( "class", AsInt, baseClass );
    WRITE_END();

    WRITE_LINE( "SetObjectModel" );
    WRITE_ARG( "forceTextures", AsBool,   isForceLoadTextures );
    WRITE_ARG( "floorHeight",   AsBool,   isSetFloorHeight    );
    WRITE_ARG( "floorAdjust",   AsBool,   isFloorAdjust       );
    WRITE_ARG( "fixedPos",      AsBool,   isFixedPosition     );
    WRITE_ARG( "zoom",          AsFloat,  zoom                );
    WRITE_ARG( "name",          AsString, displayedName       );
    WRITE_END();

    WRITE_LINE( "SetObjectModelCameraCollisionSphere" );
    WRITE_ARG( "position",  AsPoint,            cameraCollisionSphere.pos    );
    WRITE_ARG( "radius",    AsFloat,            cameraCollisionSphere.radius );
    WRITE_END();

    WRITE_LINE( "SetObjectModelShadowCircle" );
    WRITE_ARG( "radius",    AsFloat,            shadowCircle.radius     );
    WRITE_ARG( "intensity", AsFloat,            shadowCircle.intensity  );
    WRITE_ARG( "shadow",    AsEngineShadowType, shadowCircle.shadowType );
    WRITE_ARG( "factored",  AsBool,             shadowCircle.factored   );
    WRITE_END();

    WRITE_IT_LINE( "AddObjectModelNode", model );
    WRITE_IT_ARG( "partNum",   AsInt,              chunkId   );
    WRITE_IT_ARG( "parent",    AsInt,              parentId  );
    WRITE_IT_ARG( "gfxType",   AsEngineObjectType, gfxType   );
    WRITE_IT_ARG( "modFile",   AsString,           modFile   );
    WRITE_IT_ARG( "position",  AsPoint,            position  );
    WRITE_IT_ARG( "rotation",  AsPoint,            rotation  );
    WRITE_IT_ARG( "zoom",      AsPoint,            zoom      );
    WRITE_IT_ARG( "mirrored",  AsBool,             mirrored  );
    WRITE_IT_ARG( "copyModel", AsBool,             copyModel );
    WRITE_IT_END();

    WRITE_IT_LINE( "AddObjectModelCrashSphere", crashSpheres );
    WRITE_IT_ARG( "position",  AsPoint,            sphere.pos    );
    WRITE_IT_ARG( "radius",    AsFloat,            sphere.radius );
    WRITE_IT_ARG( "sound",     AsSoundType,        sound         );
    WRITE_IT_ARG( "hardness",  AsFloat,            hardness      );
    WRITE_IT_END();

    WRITE_IT_LINE( "AddObjectModelBuildingLevel", buildingLevels );
    WRITE_IT_ARG( "min",       AsFloat,            min    );
    WRITE_IT_ARG( "max",       AsFloat,            max    );
    WRITE_IT_ARG( "height",    AsFloat,            height );
    WRITE_IT_ARG( "factor",    AsFloat,            factor );
    WRITE_IT_END();
}

CObjectCreationDetails GetObjectCreationDetails(CObject* obj)
{
    return CObjectDetails::GetInstance().GetObjectDetails(obj).creation;
}

CObjectCreationDetails GetObjectCreationDetails(ObjectType type)
{
    return CObjectDetails::GetInstance().GetObjectDetails(type).creation;
}