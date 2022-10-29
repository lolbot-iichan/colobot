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
 * \file object/details/controllable_details.h
 * \brief CObjectControllableDetails - set of tweaks for Controllable objects
 */

#pragma once

class CObject;
class CLevelParser;
class CLevelParserLine;

enum EventType : unsigned int;

#include <vector>

#include "graphics/engine/camera.h"
#include "graphics/engine/particle.h"

#include "object/object_part_filter.h"

#include "ui/widget.h"

//////////////////////////////////////////////////////////////////////////////
// Camera child structs
//////////////////////////////////////////////////////////////////////////////

struct CObjectBackCameraDetails
{
// optimal back camera position 
    float distance    = 30.0f;
    float distanceMin = 10.0f;
    float height      = 4.0f;
    float rotationY   = 1.0f;
    float rotationZ   = 0.0f;

// tweaks for transparency on back camera
    bool disableOtherObjectsTransparency = false;
    bool disableObjectTransparency       = false;
    bool hasGateTransparency             = false;
};

struct CObjectFixCameraDetails
{
// never collide with someone's fix camera 
    bool disableCollisions = false;
};

struct CObjectOnboardCameraDetails
{
    bool         disableCorners = false;
    bool         hasCrosshair   = false;
    int          partNum        = 0;
    glm::vec3    position       = {0.7f, 4.8f, 0.0f};
};

struct CObjectVisitCameraDetails
{
// optimal visit camera position
    float distance = 60.0f;
    float height   = 15.0f;
};

struct CObjectCameraDetails
{
// TODO:
//  * add bools to allow camera types

// true - could change camera type
// false - only CAM_TYPE_BACK is accessible
    bool isCameraTypeChangable    = false;

// true - remember previous selected camera type for an object
// false - reset camera to CAM_TYPE_BACK on each object selection
    bool isCameraTypePersistent   = false;

    Gfx::CameraType defaultCamera = Gfx::CAM_TYPE_BACK;

    CObjectBackCameraDetails    back;
    CObjectFixCameraDetails     fixed;
    CObjectOnboardCameraDetails onboard;
    CObjectVisitCameraDetails   visit;
};

//////////////////////////////////////////////////////////////////////////////
// Controls child struct
//////////////////////////////////////////////////////////////////////////////

struct CObjectBuilderMenuButtons
{
    ObjectType  output  = OBJECT_NULL;
    int         icon    = -1;
    std::string text    = "";
};

struct CObjectControlsDetails
{
// TODO:
//  * add list of actual widgets for: builders, shielder, scribbler

// has program selector interface
    bool hasProgramUI              = false;
// blinks the program selector interface on script execution
    bool hasProgramUIBlink         = false;

// has very specific interface widgets
    bool hasBuilderUIHuman         = false;
    bool hasBuilderUIRobot         = false;
    bool hasShielderUIRobot        = false;
    bool hasScribblerUIRobot       = false;

// tweak: flight control buttons can be disabled when something is grabbed
    bool disableFlyWhileGrabbing   = false;

    std::vector<Ui::CWidget> widgets;
    std::vector<CObjectBuilderMenuButtons> build;
};

//////////////////////////////////////////////////////////////////////////////
// Shortcut child struct
//////////////////////////////////////////////////////////////////////////////

struct CObjectShortcutDetails
{
// object shortcut options
    bool isBuilding = false;
    bool isMovable  = false;
    int  icon       = -1;
};

//////////////////////////////////////////////////////////////////////////////
// Controls child struct
//////////////////////////////////////////////////////////////////////////////

struct CObjectControlLightsDetails
{
    Gfx::ParticleType color    = static_cast<Gfx::ParticleType>(0);
    glm::vec3         position = glm::vec3();
    int               partNum  = 0;
    float             zoom     = 1.0f;
    int               filter   = PART_ALWAYS;
};

//////////////////////////////////////////////////////////////////////////////
// Main struct
//////////////////////////////////////////////////////////////////////////////

struct CObjectControllableDetails
{
    bool  enabled    = false;

    bool  selectable = true;
    bool  infectable = false;
    bool  trainable  = true;

    CObjectCameraDetails                     camera;
    CObjectControlsDetails                   controls;
    CObjectShortcutDetails                   shortcut;
    std::vector<CObjectControlLightsDetails> lights;

    void ReadHardcode(ObjectType type);
    bool Read(CLevelParserLine* line);
    void Write(CLevelParser* parser, ObjectType type);
};
