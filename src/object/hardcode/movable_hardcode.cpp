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

#include "math/const.h"

#include "object/object_type.h"

#include "object/details/movable_details.h"

#include "object/hardcode/movable_hardcode.h"

bool CMovableHardcodeCollection::IsMovable(ObjectType type)
{
    if ( type == OBJECT_HUMAN ) return true;
    if ( type == OBJECT_TECH ) return true;
    if ( type == OBJECT_MOTHER ) return true;
    if ( type == OBJECT_ANT ) return true;
    if ( type == OBJECT_SPIDER ) return true;
    if ( type == OBJECT_BEE ) return true;
    if ( type == OBJECT_WORM ) return true;
    if ( type == OBJECT_TOTO ) return true;
    if ( type == OBJECT_CONTROLLER ) return true;
    if ( type == OBJECT_APOLLO2 ) return true;
    if ( type == OBJECT_MOBILEdr ) return true;
    if ( type == OBJECT_MOBILEsa ||
         type == OBJECT_MOBILEst ) return true;
    if ( type == OBJECT_MOBILErt ||
         type == OBJECT_MOBILErc ||
         type == OBJECT_MOBILErr ||
         type == OBJECT_MOBILErs ||
         type == OBJECT_MOBILErp) return true;
    if ( type == OBJECT_MOBILEfa ||
         type == OBJECT_MOBILEfb ||
         type == OBJECT_MOBILEfc ||
         type == OBJECT_MOBILEfi ||
         type == OBJECT_MOBILEfs ||
         type == OBJECT_MOBILEft ) return true;
    if ( type == OBJECT_MOBILEia ||
         type == OBJECT_MOBILEib ||
         type == OBJECT_MOBILEic ||
         type == OBJECT_MOBILEii ||
         type == OBJECT_MOBILEis ||
         type == OBJECT_MOBILEit) return true;
    if ( type == OBJECT_MOBILEta ||
         type == OBJECT_MOBILEtb ||
         type == OBJECT_MOBILEtc ||
         type == OBJECT_MOBILEti ||
         type == OBJECT_MOBILEts ||
         type == OBJECT_MOBILEtt ) return true;
    if ( type == OBJECT_MOBILEtg ) return true;
    if ( type == OBJECT_MOBILEwa ||
         type == OBJECT_MOBILEwb ||
         type == OBJECT_MOBILEwc ||
         type == OBJECT_MOBILEwi ||
         type == OBJECT_MOBILEws ||
         type == OBJECT_MOBILEwt ) return true;

    return false;
}

int CMovableHardcodeCollection::GetMotionClass(ObjectType type)
{
    if ( type == OBJECT_HUMAN ) return MOTION_CLASS_HUMAN;
    if ( type == OBJECT_TECH ) return MOTION_CLASS_HUMAN;

    if ( type == OBJECT_MOTHER ) return MOTION_CLASS_MOTHER;
    if ( type == OBJECT_ANT ) return MOTION_CLASS_ANT;
    if ( type == OBJECT_SPIDER ) return MOTION_CLASS_SPIDER;
    if ( type == OBJECT_BEE ) return MOTION_CLASS_BEE;
    if ( type == OBJECT_WORM ) return MOTION_CLASS_WORM;
    if ( type == OBJECT_TOTO ) return MOTION_CLASS_TOTO;
    if ( type == OBJECT_CONTROLLER ) return MOTION_CLASS_SIMPLE;

    if ( type == OBJECT_MOBILEwa ||
         type == OBJECT_MOBILEwb ||
         type == OBJECT_MOBILEwc ||
         type == OBJECT_MOBILEwi ||
         type == OBJECT_MOBILEws ||
         type == OBJECT_MOBILEwt ||
         type == OBJECT_MOBILEtg ||
         type == OBJECT_APOLLO2  )  // wheels
             return MOTION_CLASS_WHEELED;

    if ( type == OBJECT_MOBILEta ||
         type == OBJECT_MOBILEtb ||
         type == OBJECT_MOBILEtc ||
         type == OBJECT_MOBILEti ||
         type == OBJECT_MOBILEts ||
         type == OBJECT_MOBILEtt ||
         type == OBJECT_MOBILEsa ||
         type == OBJECT_MOBILEst ||
         type == OBJECT_MOBILErt ||
         type == OBJECT_MOBILErc ||
         type == OBJECT_MOBILErr ||
         type == OBJECT_MOBILErs ||
         type == OBJECT_MOBILErp ||
         type == OBJECT_MOBILEdr )  // tracks
             return MOTION_CLASS_TRACKED;

    if ( type == OBJECT_MOBILEfa ||
         type == OBJECT_MOBILEfb ||
         type == OBJECT_MOBILEfc ||
         type == OBJECT_MOBILEfi ||
         type == OBJECT_MOBILEfs ||
         type == OBJECT_MOBILEft )  // jet flying
             return MOTION_CLASS_WINGED;

    if ( type == OBJECT_MOBILEia ||
         type == OBJECT_MOBILEib ||
         type == OBJECT_MOBILEic ||
         type == OBJECT_MOBILEii ||
         type == OBJECT_MOBILEis ||
         type == OBJECT_MOBILEit )  // alien legs
             return MOTION_CLASS_LEGGED;

    return MOTION_CLASS_SIMPLE;
}

int CMovableHardcodeCollection::GetMotionSounds(ObjectType type)
{
    if ( type == OBJECT_HUMAN ) return MOTION_SOUND_HUMAN;
    if ( type == OBJECT_TECH ) return MOTION_SOUND_HUMAN;

    if ( type == OBJECT_MOTHER ) return MOTION_SOUND_MOTHER;
    if ( type == OBJECT_ANT ) return MOTION_SOUND_ANT;
    if ( type == OBJECT_SPIDER ) return MOTION_SOUND_SPIDER;
    if ( type == OBJECT_BEE ) return MOTION_SOUND_BEE;
    if ( type == OBJECT_WORM ) return MOTION_SOUND_WORM;

    if ( type == OBJECT_MOBILEwa ||
         type == OBJECT_MOBILEwb ||
         type == OBJECT_MOBILEwc ||
         type == OBJECT_MOBILEwi ||
         type == OBJECT_MOBILEws ||
         type == OBJECT_MOBILEwt ||
         type == OBJECT_MOBILEtg  )  // wheels
             return MOTION_SOUND_WHEELED;

    if ( type == OBJECT_APOLLO2  )  // apollo
             return MOTION_SOUND_APOLLO;

    if ( type == OBJECT_MOBILEta ||
         type == OBJECT_MOBILEtb ||
         type == OBJECT_MOBILEtc ||
         type == OBJECT_MOBILEti ||
         type == OBJECT_MOBILEts ||
         type == OBJECT_MOBILEtt ||
         type == OBJECT_MOBILEdr )  // tracks
             return MOTION_SOUND_TRACKED;

    if ( type == OBJECT_MOBILErt ||
         type == OBJECT_MOBILErc ||
         type == OBJECT_MOBILErr ||
         type == OBJECT_MOBILErs ||
         type == OBJECT_MOBILErp )  // heavy
             return MOTION_SOUND_HEAVY;

    if ( type == OBJECT_MOBILEsa ||
         type == OBJECT_MOBILEst )  // subber
             return MOTION_SOUND_SUBBER;

    if ( type == OBJECT_MOBILEfa ||
         type == OBJECT_MOBILEfb ||
         type == OBJECT_MOBILEfc ||
         type == OBJECT_MOBILEfi ||
         type == OBJECT_MOBILEfs ||
         type == OBJECT_MOBILEft )  // jet flying
             return MOTION_SOUND_WINGED;

    if ( type == OBJECT_MOBILEia ||
         type == OBJECT_MOBILEib ||
         type == OBJECT_MOBILEic ||
         type == OBJECT_MOBILEii ||
         type == OBJECT_MOBILEis ||
         type == OBJECT_MOBILEit )  // alien legs
             return MOTION_SOUND_LEGGED;

    if ( type == OBJECT_TOTO ) return MOTION_SOUND_NONE;
    if ( type == OBJECT_CONTROLLER ) return MOTION_SOUND_NONE;

    return MOTION_SOUND_NONE;
}

bool CMovableHardcodeCollection::GetMotionSoundPshhh(ObjectType type)
{
    if ( type == OBJECT_MOBILErt ||
         type == OBJECT_MOBILErc ||
         type == OBJECT_MOBILErr ||
         type == OBJECT_MOBILErs ||
         type == OBJECT_MOBILErp) return true;

    return false;
}

struct CPhysicsMock
{
    Motion      m_linMotion;        // linear motion
    Motion      m_cirMotion;        // circular motion
    
    void SetLinMotion(PhysicsMode mode, glm::vec3 value)
    {
        if ( mode == MO_ADVACCEL )  m_linMotion.advanceAccel  = value;
        if ( mode == MO_RECACCEL )  m_linMotion.recedeAccel   = value;
        if ( mode == MO_STOACCEL )  m_linMotion.stopAccel     = value;
        if ( mode == MO_TERSPEED )  m_linMotion.terrainSpeed  = value;
        if ( mode == MO_TERSLIDE )  m_linMotion.terrainSlide  = value;
        if ( mode == MO_MOTACCEL )  m_linMotion.motorAccel    = value;
        if ( mode == MO_TERFORCE )  m_linMotion.terrainForce  = value;
        if ( mode == MO_ADVSPEED )  m_linMotion.advanceSpeed  = value;
        if ( mode == MO_RECSPEED )  m_linMotion.recedeSpeed   = value;
        if ( mode == MO_MOTSPEED )  m_linMotion.motorSpeed    = value;
        if ( mode == MO_CURSPEED )  m_linMotion.currentSpeed  = value;
        if ( mode == MO_REASPEED )  m_linMotion.realSpeed     = value;
    }
    
    glm::vec3 GetLinMotion(PhysicsMode mode)
    {
        if ( mode == MO_ADVACCEL )  return m_linMotion.advanceAccel;
        if ( mode == MO_RECACCEL )  return m_linMotion.recedeAccel;
        if ( mode == MO_STOACCEL )  return m_linMotion.stopAccel;
        if ( mode == MO_TERSPEED )  return m_linMotion.terrainSpeed;
        if ( mode == MO_TERSLIDE )  return m_linMotion.terrainSlide;
        if ( mode == MO_MOTACCEL )  return m_linMotion.motorAccel;
        if ( mode == MO_TERFORCE )  return m_linMotion.terrainForce;
        if ( mode == MO_ADVSPEED )  return m_linMotion.advanceSpeed;
        if ( mode == MO_RECSPEED )  return m_linMotion.recedeSpeed;
        if ( mode == MO_MOTSPEED )  return m_linMotion.motorSpeed;
        if ( mode == MO_CURSPEED )  return m_linMotion.currentSpeed;
        if ( mode == MO_REASPEED )  return m_linMotion.realSpeed;
        return glm::vec3(0.0f, 0.0f, 0.0f);
    }
    
    void SetLinMotionX(PhysicsMode mode, float value)
    {
        if ( mode == MO_ADVACCEL )  m_linMotion.advanceAccel.x  = value;
        if ( mode == MO_RECACCEL )  m_linMotion.recedeAccel.x   = value;
        if ( mode == MO_STOACCEL )  m_linMotion.stopAccel.x     = value;
        if ( mode == MO_TERSPEED )  m_linMotion.terrainSpeed.x  = value;
        if ( mode == MO_TERSLIDE )  m_linMotion.terrainSlide.x  = value;
        if ( mode == MO_MOTACCEL )  m_linMotion.motorAccel.x    = value;
        if ( mode == MO_TERFORCE )  m_linMotion.terrainForce.x  = value;
        if ( mode == MO_ADVSPEED )  m_linMotion.advanceSpeed.x  = value;
        if ( mode == MO_RECSPEED )  m_linMotion.recedeSpeed.x   = value;
        if ( mode == MO_MOTSPEED )  m_linMotion.motorSpeed.x    = value;
        if ( mode == MO_CURSPEED )  m_linMotion.currentSpeed.x  = value;
        if ( mode == MO_REASPEED )  m_linMotion.realSpeed.x     = value;
    }
    
    float GetLinMotionX(PhysicsMode mode)
    {
        if ( mode == MO_ADVACCEL )  return m_linMotion.advanceAccel.x;
        if ( mode == MO_RECACCEL )  return m_linMotion.recedeAccel.x;
        if ( mode == MO_STOACCEL )  return m_linMotion.stopAccel.x;
        if ( mode == MO_TERSPEED )  return m_linMotion.terrainSpeed.x;
        if ( mode == MO_TERSLIDE )  return m_linMotion.terrainSlide.x;
        if ( mode == MO_MOTACCEL )  return m_linMotion.motorAccel.x;
        if ( mode == MO_TERFORCE )  return m_linMotion.terrainForce.x;
        if ( mode == MO_ADVSPEED )  return m_linMotion.advanceSpeed.x;
        if ( mode == MO_RECSPEED )  return m_linMotion.recedeSpeed.x;
        if ( mode == MO_MOTSPEED )  return m_linMotion.motorSpeed.x;
        if ( mode == MO_CURSPEED )  return m_linMotion.currentSpeed.x;
        if ( mode == MO_REASPEED )  return m_linMotion.realSpeed.x;
        return 0.0f;
    }
    
    // Specifies the speed of elevation.
    
    void SetLinMotionY(PhysicsMode mode, float value)
    {
        if ( mode == MO_ADVACCEL )  m_linMotion.advanceAccel.y  = value;
        if ( mode == MO_RECACCEL )  m_linMotion.recedeAccel.y   = value;
        if ( mode == MO_STOACCEL )  m_linMotion.stopAccel.y     = value;
        if ( mode == MO_TERSPEED )  m_linMotion.terrainSpeed.y  = value;
        if ( mode == MO_TERSLIDE )  m_linMotion.terrainSlide.y  = value;
        if ( mode == MO_MOTACCEL )  m_linMotion.motorAccel.y    = value;
        if ( mode == MO_TERFORCE )  m_linMotion.terrainForce.y  = value;
        if ( mode == MO_ADVSPEED )  m_linMotion.advanceSpeed.y  = value;
        if ( mode == MO_RECSPEED )  m_linMotion.recedeSpeed.y   = value;
        if ( mode == MO_MOTSPEED )  m_linMotion.motorSpeed.y    = value;
        if ( mode == MO_CURSPEED )  m_linMotion.currentSpeed.y  = value;
        if ( mode == MO_REASPEED )  m_linMotion.realSpeed.y     = value;
    }
    
    float GetLinMotionY(PhysicsMode mode)
    {
        if ( mode == MO_ADVACCEL )  return m_linMotion.advanceAccel.y;
        if ( mode == MO_RECACCEL )  return m_linMotion.recedeAccel.y;
        if ( mode == MO_STOACCEL )  return m_linMotion.stopAccel.y;
        if ( mode == MO_TERSPEED )  return m_linMotion.terrainSpeed.y;
        if ( mode == MO_TERSLIDE )  return m_linMotion.terrainSlide.y;
        if ( mode == MO_MOTACCEL )  return m_linMotion.motorAccel.y;
        if ( mode == MO_TERFORCE )  return m_linMotion.terrainForce.y;
        if ( mode == MO_ADVSPEED )  return m_linMotion.advanceSpeed.y;
        if ( mode == MO_RECSPEED )  return m_linMotion.recedeSpeed.y;
        if ( mode == MO_MOTSPEED )  return m_linMotion.motorSpeed.y;
        if ( mode == MO_CURSPEED )  return m_linMotion.currentSpeed.y;
        if ( mode == MO_REASPEED )  return m_linMotion.realSpeed.y;
        return 0.0f;
    }
    
    // Specifies the velocity perpendicular to the direction of travel.
    
    void SetLinMotionZ(PhysicsMode mode, float value)
    {
        if ( mode == MO_ADVACCEL )  m_linMotion.advanceAccel.z  = value;
        if ( mode == MO_RECACCEL )  m_linMotion.recedeAccel.z   = value;
        if ( mode == MO_STOACCEL )  m_linMotion.stopAccel.z     = value;
        if ( mode == MO_TERSPEED )  m_linMotion.terrainSpeed.z  = value;
        if ( mode == MO_TERSLIDE )  m_linMotion.terrainSlide.z  = value;
        if ( mode == MO_MOTACCEL )  m_linMotion.motorAccel.z    = value;
        if ( mode == MO_TERFORCE )  m_linMotion.terrainForce.z  = value;
        if ( mode == MO_ADVSPEED )  m_linMotion.advanceSpeed.z  = value;
        if ( mode == MO_RECSPEED )  m_linMotion.recedeSpeed.z   = value;
        if ( mode == MO_MOTSPEED )  m_linMotion.motorSpeed.z    = value;
        if ( mode == MO_CURSPEED )  m_linMotion.currentSpeed.z  = value;
        if ( mode == MO_REASPEED )  m_linMotion.realSpeed.z     = value;
    }
    
    float GetLinMotionZ(PhysicsMode mode)
    {
        if ( mode == MO_ADVACCEL )  return m_linMotion.advanceAccel.z;
        if ( mode == MO_RECACCEL )  return m_linMotion.recedeAccel.z;
        if ( mode == MO_STOACCEL )  return m_linMotion.stopAccel.z;
        if ( mode == MO_TERSPEED )  return m_linMotion.terrainSpeed.z;
        if ( mode == MO_TERSLIDE )  return m_linMotion.terrainSlide.z;
        if ( mode == MO_MOTACCEL )  return m_linMotion.motorAccel.z;
        if ( mode == MO_TERFORCE )  return m_linMotion.terrainForce.z;
        if ( mode == MO_ADVSPEED )  return m_linMotion.advanceSpeed.z;
        if ( mode == MO_RECSPEED )  return m_linMotion.recedeSpeed.z;
        if ( mode == MO_MOTSPEED )  return m_linMotion.motorSpeed.z;
        if ( mode == MO_CURSPEED )  return m_linMotion.currentSpeed.z;
        if ( mode == MO_REASPEED )  return m_linMotion.realSpeed.z;
        return 0.0f;
    }
    
    // Specifies the rotation around the axis of walk.
    
    void SetCirMotion(PhysicsMode mode, glm::vec3 value)
    {
        if ( mode == MO_ADVACCEL )  m_cirMotion.advanceAccel  = value;
        if ( mode == MO_RECACCEL )  m_cirMotion.recedeAccel   = value;
        if ( mode == MO_STOACCEL )  m_cirMotion.stopAccel     = value;
        if ( mode == MO_TERSPEED )  m_cirMotion.terrainSpeed  = value;
        if ( mode == MO_TERSLIDE )  m_cirMotion.terrainSlide  = value;
        if ( mode == MO_MOTACCEL )  m_cirMotion.motorAccel    = value;
        if ( mode == MO_TERFORCE )  m_cirMotion.terrainForce  = value;
        if ( mode == MO_ADVSPEED )  m_cirMotion.advanceSpeed  = value;
        if ( mode == MO_RECSPEED )  m_cirMotion.recedeSpeed   = value;
        if ( mode == MO_MOTSPEED )  m_cirMotion.motorSpeed    = value;
        if ( mode == MO_CURSPEED )  m_cirMotion.currentSpeed  = value;
        if ( mode == MO_REASPEED )  m_cirMotion.realSpeed     = value;
    }
    
    glm::vec3 GetCirMotion(PhysicsMode mode)
    {
        if ( mode == MO_ADVACCEL )  return m_cirMotion.advanceAccel;
        if ( mode == MO_RECACCEL )  return m_cirMotion.recedeAccel;
        if ( mode == MO_STOACCEL )  return m_cirMotion.stopAccel;
        if ( mode == MO_TERSPEED )  return m_cirMotion.terrainSpeed;
        if ( mode == MO_TERSLIDE )  return m_cirMotion.terrainSlide;
        if ( mode == MO_MOTACCEL )  return m_cirMotion.motorAccel;
        if ( mode == MO_TERFORCE )  return m_cirMotion.terrainForce;
        if ( mode == MO_ADVSPEED )  return m_cirMotion.advanceSpeed;
        if ( mode == MO_RECSPEED )  return m_cirMotion.recedeSpeed;
        if ( mode == MO_MOTSPEED )  return m_cirMotion.motorSpeed;
        if ( mode == MO_CURSPEED )  return m_cirMotion.currentSpeed;
        if ( mode == MO_REASPEED )  return m_cirMotion.realSpeed;
        return glm::vec3(0.0f, 0.0f, 0.0f);
    }
    
    void SetCirMotionX(PhysicsMode mode, float value)
    {
        if ( mode == MO_ADVACCEL )  m_cirMotion.advanceAccel.x  = value;
        if ( mode == MO_RECACCEL )  m_cirMotion.recedeAccel.x   = value;
        if ( mode == MO_STOACCEL )  m_cirMotion.stopAccel.x     = value;
        if ( mode == MO_TERSPEED )  m_cirMotion.terrainSpeed.x  = value;
        if ( mode == MO_TERSLIDE )  m_cirMotion.terrainSlide.x  = value;
        if ( mode == MO_MOTACCEL )  m_cirMotion.motorAccel.x    = value;
        if ( mode == MO_TERFORCE )  m_cirMotion.terrainForce.x  = value;
        if ( mode == MO_ADVSPEED )  m_cirMotion.advanceSpeed.x  = value;
        if ( mode == MO_RECSPEED )  m_cirMotion.recedeSpeed.x   = value;
        if ( mode == MO_MOTSPEED )  m_cirMotion.motorSpeed.x    = value;
        if ( mode == MO_CURSPEED )  m_cirMotion.currentSpeed.x  = value;
        if ( mode == MO_REASPEED )  m_cirMotion.realSpeed.x     = value;
    }
    
    float GetCirMotionX(PhysicsMode mode)
    {
        if ( mode == MO_ADVACCEL )  return m_cirMotion.advanceAccel.x;
        if ( mode == MO_RECACCEL )  return m_cirMotion.recedeAccel.x;
        if ( mode == MO_STOACCEL )  return m_cirMotion.stopAccel.x;
        if ( mode == MO_TERSPEED )  return m_cirMotion.terrainSpeed.x;
        if ( mode == MO_TERSLIDE )  return m_cirMotion.terrainSlide.x;
        if ( mode == MO_MOTACCEL )  return m_cirMotion.motorAccel.x;
        if ( mode == MO_TERFORCE )  return m_cirMotion.terrainForce.x;
        if ( mode == MO_ADVSPEED )  return m_cirMotion.advanceSpeed.x;
        if ( mode == MO_RECSPEED )  return m_cirMotion.recedeSpeed.x;
        if ( mode == MO_MOTSPEED )  return m_cirMotion.motorSpeed.x;
        if ( mode == MO_CURSPEED )  return m_cirMotion.currentSpeed.x;
        if ( mode == MO_REASPEED )  return m_cirMotion.realSpeed.x;
        return 0.0f;
    }
    
    // Specifies the rotation direction.
    
    void SetCirMotionY(PhysicsMode mode, float value)
    {
        if ( mode == MO_ADVACCEL )  m_cirMotion.advanceAccel.y  = value;
        if ( mode == MO_RECACCEL )  m_cirMotion.recedeAccel.y   = value;
        if ( mode == MO_STOACCEL )  m_cirMotion.stopAccel.y     = value;
        if ( mode == MO_TERSPEED )  m_cirMotion.terrainSpeed.y  = value;
        if ( mode == MO_TERSLIDE )  m_cirMotion.terrainSlide.y  = value;
        if ( mode == MO_MOTACCEL )  m_cirMotion.motorAccel.y    = value;
        if ( mode == MO_TERFORCE )  m_cirMotion.terrainForce.y  = value;
        if ( mode == MO_ADVSPEED )  m_cirMotion.advanceSpeed.y  = value;
        if ( mode == MO_RECSPEED )  m_cirMotion.recedeSpeed.y   = value;
        if ( mode == MO_MOTSPEED )  m_cirMotion.motorSpeed.y    = value;
        if ( mode == MO_CURSPEED )  m_cirMotion.currentSpeed.y  = value;
        if ( mode == MO_REASPEED )  m_cirMotion.realSpeed.y     = value;
    }
    
    float GetCirMotionY(PhysicsMode mode)
    {
        if ( mode == MO_ADVACCEL )  return m_cirMotion.advanceAccel.y;
        if ( mode == MO_RECACCEL )  return m_cirMotion.recedeAccel.y;
        if ( mode == MO_STOACCEL )  return m_cirMotion.stopAccel.y;
        if ( mode == MO_TERSPEED )  return m_cirMotion.terrainSpeed.y;
        if ( mode == MO_TERSLIDE )  return m_cirMotion.terrainSlide.y;
        if ( mode == MO_MOTACCEL )  return m_cirMotion.motorAccel.y;
        if ( mode == MO_TERFORCE )  return m_cirMotion.terrainForce.y;
        if ( mode == MO_ADVSPEED )  return m_cirMotion.advanceSpeed.y;
        if ( mode == MO_RECSPEED )  return m_cirMotion.recedeSpeed.y;
        if ( mode == MO_MOTSPEED )  return m_cirMotion.motorSpeed.y;
        if ( mode == MO_CURSPEED )  return m_cirMotion.currentSpeed.y;
        if ( mode == MO_REASPEED )  return m_cirMotion.realSpeed.y;
        return 0.0f;
    }
    
    // Specifies the rotation up/down.
    
    void SetCirMotionZ(PhysicsMode mode, float value)
    {
        if ( mode == MO_ADVACCEL )  m_cirMotion.advanceAccel.z  = value;
        if ( mode == MO_RECACCEL )  m_cirMotion.recedeAccel.z   = value;
        if ( mode == MO_STOACCEL )  m_cirMotion.stopAccel.z     = value;
        if ( mode == MO_TERSPEED )  m_cirMotion.terrainSpeed.z  = value;
        if ( mode == MO_TERSLIDE )  m_cirMotion.terrainSlide.z  = value;
        if ( mode == MO_MOTACCEL )  m_cirMotion.motorAccel.z    = value;
        if ( mode == MO_TERFORCE )  m_cirMotion.terrainForce.z  = value;
        if ( mode == MO_ADVSPEED )  m_cirMotion.advanceSpeed.z  = value;
        if ( mode == MO_RECSPEED )  m_cirMotion.recedeSpeed.z   = value;
        if ( mode == MO_MOTSPEED )  m_cirMotion.motorSpeed.z    = value;
        if ( mode == MO_CURSPEED )  m_cirMotion.currentSpeed.z  = value;
        if ( mode == MO_REASPEED )  m_cirMotion.realSpeed.z     = value;
    }
    
    float GetCirMotionZ(PhysicsMode mode)
    {
        if ( mode == MO_ADVACCEL )  return m_cirMotion.advanceAccel.z;
        if ( mode == MO_RECACCEL )  return m_cirMotion.recedeAccel.z;
        if ( mode == MO_STOACCEL )  return m_cirMotion.stopAccel.z;
        if ( mode == MO_TERSPEED )  return m_cirMotion.terrainSpeed.z;
        if ( mode == MO_TERSLIDE )  return m_cirMotion.terrainSlide.z;
        if ( mode == MO_MOTACCEL )  return m_cirMotion.motorAccel.z;
        if ( mode == MO_TERFORCE )  return m_cirMotion.terrainForce.z;
        if ( mode == MO_ADVSPEED )  return m_cirMotion.advanceSpeed.z;
        if ( mode == MO_RECSPEED )  return m_cirMotion.recedeSpeed.z;
        if ( mode == MO_MOTSPEED )  return m_cirMotion.motorSpeed.z;
        if ( mode == MO_CURSPEED )  return m_cirMotion.currentSpeed.z;
        if ( mode == MO_REASPEED )  return m_cirMotion.realSpeed.z;
        return 0.0f;
    }
};

Motion CMovableHardcodeCollection::GetLinMotion(ObjectType type)
{
    CPhysicsMock physics;

    if ( type == OBJECT_MOTHER )
    {
        physics.SetLinMotionX(MO_ADVSPEED,   8.0f);
        physics.SetLinMotionX(MO_RECSPEED,   8.0f);
        physics.SetLinMotionX(MO_ADVACCEL,  10.0f);
        physics.SetLinMotionX(MO_RECACCEL,  10.0f);
        physics.SetLinMotionX(MO_STOACCEL,  40.0f);
        physics.SetLinMotionX(MO_TERSLIDE,   5.0f);
        physics.SetLinMotionZ(MO_TERSLIDE,   5.0f);
        physics.SetLinMotionX(MO_TERFORCE,  30.0f);
        physics.SetLinMotionZ(MO_TERFORCE,  20.0f);
        physics.SetLinMotionZ(MO_MOTACCEL,  40.0f);
    }
    if ( type == OBJECT_ANT )
    {
        physics.SetLinMotionX(MO_ADVSPEED,  12.0f);
        physics.SetLinMotionX(MO_RECSPEED,  12.0f);
        physics.SetLinMotionX(MO_ADVACCEL,  15.0f);
        physics.SetLinMotionX(MO_RECACCEL,  15.0f);
        physics.SetLinMotionX(MO_STOACCEL,  40.0f);
        physics.SetLinMotionX(MO_TERSLIDE,   5.0f);
        physics.SetLinMotionZ(MO_TERSLIDE,   5.0f);
        physics.SetLinMotionX(MO_TERFORCE,   5.0f);
        physics.SetLinMotionZ(MO_TERFORCE,   5.0f);
        physics.SetLinMotionZ(MO_MOTACCEL,  10.0f);
    }
    if ( type == OBJECT_SPIDER )
    {
        physics.SetLinMotionX(MO_ADVSPEED,  12.0f);
        physics.SetLinMotionX(MO_RECSPEED,  12.0f);
        physics.SetLinMotionX(MO_ADVACCEL,  15.0f);
        physics.SetLinMotionX(MO_RECACCEL,  15.0f);
        physics.SetLinMotionX(MO_STOACCEL,  40.0f);
        physics.SetLinMotionX(MO_TERSLIDE,   5.0f);
        physics.SetLinMotionZ(MO_TERSLIDE,   5.0f);
        physics.SetLinMotionX(MO_TERFORCE,   5.0f);
        physics.SetLinMotionZ(MO_TERFORCE,   5.0f);
        physics.SetLinMotionZ(MO_MOTACCEL,  10.0f);
    }
    if ( type == OBJECT_BEE )
    {
        physics.SetLinMotionX(MO_ADVSPEED,  50.0f);
        physics.SetLinMotionX(MO_RECSPEED,  50.0f);
        physics.SetLinMotionX(MO_ADVACCEL,  20.0f);
        physics.SetLinMotionX(MO_RECACCEL,  20.0f);
        physics.SetLinMotionX(MO_STOACCEL,  20.0f);
        physics.SetLinMotionX(MO_TERSLIDE,   5.0f);
        physics.SetLinMotionZ(MO_TERSLIDE,   5.0f);
        physics.SetLinMotionX(MO_TERFORCE,  10.0f);
        physics.SetLinMotionZ(MO_TERFORCE,  10.0f);
        physics.SetLinMotionZ(MO_MOTACCEL,  40.0f);
        physics.SetLinMotionY(MO_ADVSPEED,  60.0f);
        physics.SetLinMotionY(MO_RECSPEED,  60.0f);
        physics.SetLinMotionY(MO_ADVACCEL,  20.0f);
        physics.SetLinMotionY(MO_RECACCEL,  50.0f);
        physics.SetLinMotionY(MO_STOACCEL,  50.0f);
    }
    if ( type == OBJECT_WORM )
    {
        physics.SetLinMotionX(MO_ADVSPEED,   3.0f);
        physics.SetLinMotionX(MO_RECSPEED,   3.0f);
        physics.SetLinMotionX(MO_ADVACCEL,  10.0f);
        physics.SetLinMotionX(MO_RECACCEL,  10.0f);
        physics.SetLinMotionX(MO_STOACCEL,  40.0f);
        physics.SetLinMotionX(MO_TERSLIDE,   5.0f);
        physics.SetLinMotionZ(MO_TERSLIDE,   5.0f);
        physics.SetLinMotionX(MO_TERFORCE,   5.0f);
        physics.SetLinMotionZ(MO_TERFORCE,   5.0f);
        physics.SetLinMotionZ(MO_MOTACCEL,  40.0f);
    }
    if ( type == OBJECT_HUMAN )
    {
        physics.SetLinMotionX(MO_ADVSPEED, 50.0f);
        physics.SetLinMotionX(MO_RECSPEED, 35.0f);
        physics.SetLinMotionX(MO_ADVACCEL, 20.0f);
        physics.SetLinMotionX(MO_RECACCEL, 20.0f);
        physics.SetLinMotionX(MO_STOACCEL, 20.0f);
        physics.SetLinMotionX(MO_TERSLIDE,  5.0f);
        physics.SetLinMotionZ(MO_TERSLIDE,  5.0f);
        physics.SetLinMotionX(MO_TERFORCE, 70.0f);
        physics.SetLinMotionZ(MO_TERFORCE, 40.0f);
        physics.SetLinMotionZ(MO_MOTACCEL, 40.0f);
        physics.SetLinMotionY(MO_ADVSPEED, 60.0f);
        physics.SetLinMotionY(MO_RECSPEED, 60.0f);
        physics.SetLinMotionY(MO_ADVACCEL, 20.0f);
        physics.SetLinMotionY(MO_RECACCEL, 50.0f);
        physics.SetLinMotionY(MO_STOACCEL, 50.0f);
    }
    if ( type == OBJECT_TECH )
    {
        physics.SetLinMotionX(MO_ADVSPEED, 40.0f);
        physics.SetLinMotionX(MO_RECSPEED, 15.0f);
        physics.SetLinMotionX(MO_ADVACCEL,  8.0f);
        physics.SetLinMotionX(MO_RECACCEL,  8.0f);
        physics.SetLinMotionX(MO_STOACCEL,  8.0f);
        physics.SetLinMotionX(MO_TERSLIDE,  5.0f);
        physics.SetLinMotionZ(MO_TERSLIDE,  5.0f);
        physics.SetLinMotionX(MO_TERFORCE, 50.0f);
        physics.SetLinMotionZ(MO_TERFORCE, 50.0f);
        physics.SetLinMotionZ(MO_MOTACCEL, 40.0f);
        physics.SetLinMotionY(MO_ADVSPEED, 60.0f);
        physics.SetLinMotionY(MO_RECSPEED, 60.0f);
        physics.SetLinMotionY(MO_ADVACCEL, 20.0f);
        physics.SetLinMotionY(MO_RECACCEL, 50.0f);
        physics.SetLinMotionY(MO_STOACCEL, 50.0f);
    }
    if ( type == OBJECT_CONTROLLER )
    {
        physics.SetLinMotionX(MO_ADVSPEED, 50.0f);
        physics.SetLinMotionX(MO_RECSPEED, 50.0f);
        physics.SetLinMotionX(MO_ADVACCEL, 20.0f);
        physics.SetLinMotionX(MO_RECACCEL, 20.0f);
        physics.SetLinMotionX(MO_STOACCEL, 20.0f);
        physics.SetLinMotionX(MO_TERSLIDE,  0.0f);
        physics.SetLinMotionZ(MO_TERSLIDE,  0.0f);
        physics.SetLinMotionX(MO_TERFORCE,  0.0f);
        physics.SetLinMotionZ(MO_TERFORCE,  0.0f);
        physics.SetLinMotionZ(MO_MOTACCEL, 40.0f);
        physics.SetLinMotionY(MO_ADVSPEED, 60.0f);
        physics.SetLinMotionY(MO_RECSPEED, 60.0f);
        physics.SetLinMotionY(MO_ADVACCEL, 20.0f);
        physics.SetLinMotionY(MO_RECACCEL, 50.0f);
        physics.SetLinMotionY(MO_STOACCEL, 50.0f);
    }
    if ( type == OBJECT_APOLLO2 )  // jeep?
    {
        physics.SetLinMotionX(MO_ADVSPEED, 15.0f);
        physics.SetLinMotionX(MO_RECSPEED, 10.0f);
        physics.SetLinMotionX(MO_ADVACCEL, 20.0f);
        physics.SetLinMotionX(MO_RECACCEL, 20.0f);
        physics.SetLinMotionX(MO_STOACCEL, 40.0f);
        physics.SetLinMotionX(MO_TERSLIDE,  2.0f);
        physics.SetLinMotionZ(MO_TERSLIDE,  2.0f);
        physics.SetLinMotionX(MO_TERFORCE, 30.0f);
        physics.SetLinMotionZ(MO_TERFORCE, 10.0f);
        physics.SetLinMotionZ(MO_MOTACCEL, 20.0f);
    }
    if ( type == OBJECT_MOBILEdr )
    {
        physics.SetLinMotionX(MO_ADVSPEED, 15.0f);
        physics.SetLinMotionX(MO_RECSPEED, 10.0f);
        physics.SetLinMotionX(MO_ADVACCEL, 20.0f);
        physics.SetLinMotionX(MO_RECACCEL, 10.0f);
        physics.SetLinMotionX(MO_STOACCEL, 40.0f);
        physics.SetLinMotionX(MO_TERSLIDE,  5.0f);
        physics.SetLinMotionZ(MO_TERSLIDE,  5.0f);
        physics.SetLinMotionX(MO_TERFORCE, 20.0f);
        physics.SetLinMotionZ(MO_TERFORCE, 10.0f);
        physics.SetLinMotionZ(MO_MOTACCEL, 40.0f);
    }
    if ( type == OBJECT_MOBILEsa ||
         type == OBJECT_MOBILEst )
    {
        physics.SetLinMotionX(MO_ADVSPEED, 15.0f);
        physics.SetLinMotionX(MO_RECSPEED, 10.0f);
        physics.SetLinMotionX(MO_ADVACCEL, 20.0f);
        physics.SetLinMotionX(MO_RECACCEL, 10.0f);
        physics.SetLinMotionX(MO_STOACCEL, 40.0f);
        physics.SetLinMotionX(MO_TERSLIDE,  5.0f);
        physics.SetLinMotionZ(MO_TERSLIDE,  5.0f);
        physics.SetLinMotionX(MO_TERFORCE, 20.0f);
        physics.SetLinMotionZ(MO_TERFORCE, 10.0f);
        physics.SetLinMotionZ(MO_MOTACCEL, 40.0f);
    }
    if ( type == OBJECT_MOBILErt ||
         type == OBJECT_MOBILErc ||
         type == OBJECT_MOBILErr ||
         type == OBJECT_MOBILErs ||
         type == OBJECT_MOBILErp)  // large caterpillars?
    {
        physics.SetLinMotionX(MO_ADVSPEED, 10.0f);
        physics.SetLinMotionX(MO_RECSPEED,  5.0f);
        physics.SetLinMotionX(MO_ADVACCEL, 10.0f);
        physics.SetLinMotionX(MO_RECACCEL,  5.0f);
        physics.SetLinMotionX(MO_STOACCEL, 40.0f);
        physics.SetLinMotionX(MO_TERSLIDE,  5.0f);
        physics.SetLinMotionZ(MO_TERSLIDE,  5.0f);
        physics.SetLinMotionX(MO_TERFORCE, 20.0f);
        physics.SetLinMotionZ(MO_TERFORCE, 10.0f);
        physics.SetLinMotionZ(MO_MOTACCEL, 40.0f);
    }
    if ( type == OBJECT_MOBILEfa ||
         type == OBJECT_MOBILEfb ||
         type == OBJECT_MOBILEfc ||
         type == OBJECT_MOBILEfi ||
         type == OBJECT_MOBILEfs ||
         type == OBJECT_MOBILEft )  // flying?
    {

        physics.SetLinMotionX(MO_ADVSPEED, 50.0f);
        physics.SetLinMotionX(MO_RECSPEED, 50.0f);
        physics.SetLinMotionX(MO_ADVACCEL, 20.0f);
        physics.SetLinMotionX(MO_RECACCEL, 20.0f);
        physics.SetLinMotionX(MO_STOACCEL, 20.0f);
        physics.SetLinMotionX(MO_TERSLIDE,  5.0f);
        physics.SetLinMotionZ(MO_TERSLIDE,  5.0f);
        physics.SetLinMotionX(MO_TERFORCE, 50.0f);
        physics.SetLinMotionZ(MO_TERFORCE, 50.0f);
        physics.SetLinMotionZ(MO_MOTACCEL, 40.0f);
        physics.SetLinMotionY(MO_ADVSPEED, 60.0f);
        physics.SetLinMotionY(MO_RECSPEED, 60.0f);
        physics.SetLinMotionY(MO_ADVACCEL, 20.0f);
        physics.SetLinMotionY(MO_RECACCEL, 50.0f);
        physics.SetLinMotionY(MO_STOACCEL, 50.0f);
    }
    if ( type == OBJECT_MOBILEia ||
         type == OBJECT_MOBILEib ||
         type == OBJECT_MOBILEic ||
         type == OBJECT_MOBILEii ||
         type == OBJECT_MOBILEis ||
         type == OBJECT_MOBILEit)  // legs?
    {

        physics.SetLinMotionX(MO_ADVSPEED, 15.0f);
        physics.SetLinMotionX(MO_RECSPEED,  8.0f);
        physics.SetLinMotionX(MO_ADVACCEL, 40.0f);
        physics.SetLinMotionX(MO_RECACCEL, 20.0f);
        physics.SetLinMotionX(MO_STOACCEL, 40.0f);
        physics.SetLinMotionX(MO_TERSLIDE,  5.0f);
        physics.SetLinMotionZ(MO_TERSLIDE,  5.0f);
        physics.SetLinMotionX(MO_TERFORCE, 10.0f);
//?     physics.SetLinMotionX(MO_TERFORCE, 15.0f);
        physics.SetLinMotionZ(MO_TERFORCE, 10.0f);
        physics.SetLinMotionZ(MO_MOTACCEL, 40.0f);
    }
    if ( type == OBJECT_MOBILEta ||
         type == OBJECT_MOBILEtb ||
         type == OBJECT_MOBILEtc ||
         type == OBJECT_MOBILEti ||
         type == OBJECT_MOBILEts ||
         type == OBJECT_MOBILEtt )  // caterpillars?
    {

        physics.SetLinMotionX(MO_ADVSPEED, 15.0f);
        physics.SetLinMotionX(MO_RECSPEED,  8.0f);
        physics.SetLinMotionX(MO_ADVACCEL, 15.0f);
        physics.SetLinMotionX(MO_RECACCEL,  8.0f);
        physics.SetLinMotionX(MO_STOACCEL, 40.0f);
        physics.SetLinMotionX(MO_TERSLIDE,  5.0f);
        physics.SetLinMotionZ(MO_TERSLIDE,  5.0f);
        physics.SetLinMotionX(MO_TERFORCE, 20.0f);
        physics.SetLinMotionZ(MO_TERFORCE, 10.0f);
        physics.SetLinMotionZ(MO_MOTACCEL, 40.0f);
    }
    if ( type == OBJECT_MOBILEtg )
    {

        physics.SetLinMotionX(MO_ADVSPEED, 20.0f);
        physics.SetLinMotionX(MO_RECSPEED, 10.0f);
        physics.SetLinMotionX(MO_ADVACCEL, 40.0f);
        physics.SetLinMotionX(MO_RECACCEL, 20.0f);
        physics.SetLinMotionX(MO_STOACCEL, 40.0f);
        physics.SetLinMotionX(MO_TERSLIDE,  5.0f);
        physics.SetLinMotionZ(MO_TERSLIDE,  5.0f);
        physics.SetLinMotionX(MO_TERFORCE, 50.0f);
        physics.SetLinMotionZ(MO_TERFORCE, 20.0f);
        physics.SetLinMotionZ(MO_MOTACCEL, 20.0f);
    }
    if ( type == OBJECT_MOBILEwa ||
         type == OBJECT_MOBILEwb ||
         type == OBJECT_MOBILEwc ||
         type == OBJECT_MOBILEwi ||
         type == OBJECT_MOBILEws ||
         type == OBJECT_MOBILEwt )  // wheels?
    {
        physics.SetLinMotionX(MO_ADVSPEED, 20.0f);
        physics.SetLinMotionX(MO_RECSPEED, 10.0f);
        physics.SetLinMotionX(MO_ADVACCEL, 40.0f);
        physics.SetLinMotionX(MO_RECACCEL, 20.0f);
        physics.SetLinMotionX(MO_STOACCEL, 40.0f);
        physics.SetLinMotionX(MO_TERSLIDE,  5.0f);
        physics.SetLinMotionZ(MO_TERSLIDE,  5.0f);
        physics.SetLinMotionX(MO_TERFORCE, 50.0f);
        physics.SetLinMotionZ(MO_TERFORCE, 30.0f);
        physics.SetLinMotionZ(MO_MOTACCEL, 20.0f);
    }

    Motion result;
    result.advanceAccel = physics.GetLinMotion(MO_ADVACCEL);
    result.recedeAccel  = physics.GetLinMotion(MO_RECACCEL);
    result.stopAccel    = physics.GetLinMotion(MO_STOACCEL);
    result.terrainSpeed = physics.GetLinMotion(MO_TERSPEED);
    result.terrainSlide = physics.GetLinMotion(MO_TERSLIDE);
    result.motorAccel   = physics.GetLinMotion(MO_MOTACCEL);
    result.terrainForce = physics.GetLinMotion(MO_TERFORCE);
    result.advanceSpeed = physics.GetLinMotion(MO_ADVSPEED);
    result.recedeSpeed  = physics.GetLinMotion(MO_RECSPEED);
    result.motorSpeed   = physics.GetLinMotion(MO_MOTSPEED);
    result.currentSpeed = physics.GetLinMotion(MO_CURSPEED);
    result.realSpeed    = physics.GetLinMotion(MO_REASPEED);
    return result;
}

Motion CMovableHardcodeCollection::GetCirMotion(ObjectType type)
{
    CPhysicsMock physics;

    if ( type == OBJECT_MOTHER )
    {
        physics.SetCirMotionY(MO_ADVSPEED,   0.1f*Math::PI);
        physics.SetCirMotionY(MO_RECSPEED,   0.1f*Math::PI);
        physics.SetCirMotionY(MO_ADVACCEL,  10.0f);
        physics.SetCirMotionY(MO_RECACCEL,  10.0f);
        physics.SetCirMotionY(MO_STOACCEL,  20.0f);
    }
    if ( type == OBJECT_ANT )
    {
        physics.SetCirMotionY(MO_ADVSPEED,   1.0f*Math::PI);
        physics.SetCirMotionY(MO_RECSPEED,   1.0f*Math::PI);
        physics.SetCirMotionY(MO_ADVACCEL,  20.0f);
        physics.SetCirMotionY(MO_RECACCEL,  20.0f);
        physics.SetCirMotionY(MO_STOACCEL,  40.0f);
    }
    if ( type == OBJECT_SPIDER )
    {    
        physics.SetCirMotionY(MO_ADVSPEED,   1.0f*Math::PI);
        physics.SetCirMotionY(MO_RECSPEED,   1.0f*Math::PI);
        physics.SetCirMotionY(MO_ADVACCEL,  20.0f);
        physics.SetCirMotionY(MO_RECACCEL,  20.0f);
        physics.SetCirMotionY(MO_STOACCEL,  40.0f);

    }
    if ( type == OBJECT_BEE )
    {
        physics.SetCirMotionY(MO_ADVSPEED,   1.0f*Math::PI);
        physics.SetCirMotionY(MO_RECSPEED,   1.0f*Math::PI);
        physics.SetCirMotionY(MO_ADVACCEL,  20.0f);
        physics.SetCirMotionY(MO_RECACCEL,  20.0f);
        physics.SetCirMotionY(MO_STOACCEL,  40.0f);
    }
    if ( type == OBJECT_WORM )
    {
        physics.SetCirMotionY(MO_ADVSPEED,   0.2f*Math::PI);
        physics.SetCirMotionY(MO_RECSPEED,   0.2f*Math::PI);
        physics.SetCirMotionY(MO_ADVACCEL,  10.0f);
        physics.SetCirMotionY(MO_RECACCEL,  10.0f);
        physics.SetCirMotionY(MO_STOACCEL,  20.0f);
    }
    if ( type == OBJECT_HUMAN )
    {
        physics.SetCirMotionY(MO_ADVSPEED,  0.8f*Math::PI);
        physics.SetCirMotionY(MO_RECSPEED,  0.8f*Math::PI);
        physics.SetCirMotionY(MO_ADVACCEL,  6.0f);
        physics.SetCirMotionY(MO_RECACCEL,  6.0f);
        physics.SetCirMotionY(MO_STOACCEL,  4.0f);
    }
    if ( type == OBJECT_TECH )
    {
        physics.SetCirMotionY(MO_ADVSPEED,  0.6f*Math::PI);
        physics.SetCirMotionY(MO_RECSPEED,  0.6f*Math::PI);
        physics.SetCirMotionY(MO_ADVACCEL,  4.0f);
        physics.SetCirMotionY(MO_RECACCEL,  4.0f);
        physics.SetCirMotionY(MO_STOACCEL,  3.0f);
    }
    if ( type == OBJECT_CONTROLLER )
    {
        physics.SetCirMotionY(MO_ADVSPEED,  0.4f*Math::PI);
        physics.SetCirMotionY(MO_RECSPEED,  0.4f*Math::PI);
        physics.SetCirMotionY(MO_ADVACCEL,  2.0f);
        physics.SetCirMotionY(MO_RECACCEL,  2.0f);
        physics.SetCirMotionY(MO_STOACCEL,  2.0f);
    }
    if ( type == OBJECT_APOLLO2 )  // jeep?
    {
        physics.SetCirMotionY(MO_ADVSPEED,  0.4f*Math::PI);
        physics.SetCirMotionY(MO_RECSPEED,  0.4f*Math::PI);
        physics.SetCirMotionY(MO_ADVACCEL,  2.0f);
        physics.SetCirMotionY(MO_RECACCEL,  2.0f);
        physics.SetCirMotionY(MO_STOACCEL,  4.0f);
    }
    if ( type == OBJECT_MOBILEdr )
    {
        physics.SetCirMotionY(MO_ADVSPEED,  0.5f*Math::PI);
        physics.SetCirMotionY(MO_RECSPEED,  0.5f*Math::PI);
        physics.SetCirMotionY(MO_ADVACCEL,  5.0f);
        physics.SetCirMotionY(MO_RECACCEL,  5.0f);
        physics.SetCirMotionY(MO_STOACCEL, 10.0f);
    }
    if ( type == OBJECT_MOBILEsa ||
         type == OBJECT_MOBILEst )
    {
        physics.SetCirMotionY(MO_ADVSPEED,  0.5f*Math::PI);
        physics.SetCirMotionY(MO_RECSPEED,  0.5f*Math::PI);
        physics.SetCirMotionY(MO_ADVACCEL,  5.0f);
        physics.SetCirMotionY(MO_RECACCEL,  5.0f);
        physics.SetCirMotionY(MO_STOACCEL, 10.0f);
    }
    if ( type == OBJECT_MOBILErt ||
         type == OBJECT_MOBILErc ||
         type == OBJECT_MOBILErr ||
         type == OBJECT_MOBILErs ||
         type == OBJECT_MOBILErp)  // large caterpillars?
    {
        physics.SetCirMotionY(MO_ADVSPEED,  0.3f*Math::PI);
        physics.SetCirMotionY(MO_RECSPEED,  0.3f*Math::PI);
        physics.SetCirMotionY(MO_ADVACCEL,  2.0f);
        physics.SetCirMotionY(MO_RECACCEL,  2.0f);
        physics.SetCirMotionY(MO_STOACCEL,  4.0f);
    }
    if ( type == OBJECT_MOBILEfa ||
         type == OBJECT_MOBILEfb ||
         type == OBJECT_MOBILEfc ||
         type == OBJECT_MOBILEfi ||
         type == OBJECT_MOBILEfs ||
         type == OBJECT_MOBILEft )  // flying?
    {

        physics.SetCirMotionY(MO_ADVSPEED,  0.4f*Math::PI);
        physics.SetCirMotionY(MO_RECSPEED,  0.4f*Math::PI);
        physics.SetCirMotionY(MO_ADVACCEL,  2.0f);
        physics.SetCirMotionY(MO_RECACCEL,  2.0f);
        physics.SetCirMotionY(MO_STOACCEL,  2.0f);
    }
    if ( type == OBJECT_MOBILEia ||
         type == OBJECT_MOBILEib ||
         type == OBJECT_MOBILEic ||
         type == OBJECT_MOBILEii ||
         type == OBJECT_MOBILEis ||
         type == OBJECT_MOBILEit)  // legs?
    {

        physics.SetCirMotionY(MO_ADVSPEED,  0.5f*Math::PI);
        physics.SetCirMotionY(MO_RECSPEED,  0.5f*Math::PI);
        physics.SetCirMotionY(MO_ADVACCEL, 10.0f);
        physics.SetCirMotionY(MO_RECACCEL, 10.0f);
        physics.SetCirMotionY(MO_STOACCEL, 15.0f);
    }
    if ( type == OBJECT_MOBILEta ||
         type == OBJECT_MOBILEtb ||
         type == OBJECT_MOBILEtc ||
         type == OBJECT_MOBILEti ||
         type == OBJECT_MOBILEts ||
         type == OBJECT_MOBILEtt )  // caterpillars?
    {

        physics.SetCirMotionY(MO_ADVSPEED,  0.5f*Math::PI);
        physics.SetCirMotionY(MO_RECSPEED,  0.5f*Math::PI);
        physics.SetCirMotionY(MO_ADVACCEL, 10.0f);
        physics.SetCirMotionY(MO_RECACCEL, 10.0f);
        physics.SetCirMotionY(MO_STOACCEL,  6.0f);
    }
    if ( type == OBJECT_MOBILEtg )
    {

        physics.SetCirMotionY(MO_ADVSPEED,  0.8f*Math::PI);
        physics.SetCirMotionY(MO_RECSPEED,  0.8f*Math::PI);
        physics.SetCirMotionY(MO_ADVACCEL, 10.0f);
        physics.SetCirMotionY(MO_RECACCEL, 10.0f);
        physics.SetCirMotionY(MO_STOACCEL, 15.0f);
    }
    if ( type == OBJECT_MOBILEwa ||
         type == OBJECT_MOBILEwb ||
         type == OBJECT_MOBILEwc ||
         type == OBJECT_MOBILEwi ||
         type == OBJECT_MOBILEws ||
         type == OBJECT_MOBILEwt )  // wheels?
    {
        physics.SetCirMotionY(MO_ADVSPEED,  0.8f*Math::PI);
        physics.SetCirMotionY(MO_RECSPEED,  0.8f*Math::PI);
        physics.SetCirMotionY(MO_ADVACCEL,  8.0f);
        physics.SetCirMotionY(MO_RECACCEL,  8.0f);
        physics.SetCirMotionY(MO_STOACCEL, 12.0f);
    }

    Motion result;
    result.advanceAccel = physics.GetCirMotion(MO_ADVACCEL);
    result.recedeAccel  = physics.GetCirMotion(MO_RECACCEL);
    result.stopAccel    = physics.GetCirMotion(MO_STOACCEL);
    result.terrainSpeed = physics.GetCirMotion(MO_TERSPEED);
    result.terrainSlide = physics.GetCirMotion(MO_TERSLIDE);
    result.motorAccel   = physics.GetCirMotion(MO_MOTACCEL);
    result.terrainForce = physics.GetCirMotion(MO_TERFORCE);
    result.advanceSpeed = physics.GetCirMotion(MO_ADVSPEED);
    result.recedeSpeed  = physics.GetCirMotion(MO_RECSPEED);
    result.motorSpeed   = physics.GetCirMotion(MO_MOTSPEED);
    result.currentSpeed = physics.GetCirMotion(MO_CURSPEED);
    result.realSpeed    = physics.GetCirMotion(MO_REASPEED);
    return result;
}

Character CMovableHardcodeCollection::GetWheels(ObjectType type)
{
    Character character;
    if ( type == OBJECT_MOTHER )
    {
        character.wheelFront = 10.0f;
        character.wheelBack  = 10.0f;
        character.wheelLeft  = 20.0f;
        character.wheelRight = 20.0f;
        character.height     =  3.0f;
    }
    if ( type == OBJECT_ANT )
    {
        character.wheelFront = 3.0f;
        character.wheelBack  = 3.0f;
        character.wheelLeft  = 5.0f;
        character.wheelRight = 5.0f;
        character.height     = 1.2f;
    }
    if ( type == OBJECT_SPIDER )
    {    
        character.wheelFront = 4.0f;
        character.wheelBack  = 4.0f;
        character.wheelLeft  = 6.0f;
        character.wheelRight = 6.0f;
        character.height     = 0.6f;
    }
    if ( type == OBJECT_BEE )
    {
        character.wheelFront = 3.0f;
        character.wheelBack  = 3.0f;
        character.wheelLeft  = 5.0f;
        character.wheelRight = 5.0f;
        character.height     = 2.5f;
    }
    if ( type == OBJECT_WORM )
    {
        character.wheelFront = 10.0f;
        character.wheelBack  = 10.0f;
        character.wheelLeft  =  2.0f;
        character.wheelRight =  2.0f;
        character.height     = -0.2f;
    }
    if ( type == OBJECT_HUMAN )
    {
        character.wheelFront = 4.0f;
        character.wheelBack  = 4.0f;
        character.wheelLeft  = 4.0f;
        character.wheelRight = 4.0f;
        character.height     = 3.5f;
    }
    if ( type == OBJECT_TECH )
    {
        character.wheelFront = 4.0f;
        character.wheelBack  = 4.0f;
        character.wheelLeft  = 4.0f;
        character.wheelRight = 4.0f;
        character.height     = 3.5f;
    }
    if ( type == OBJECT_CONTROLLER )
    {
        // default
    }
    if ( type == OBJECT_APOLLO2 )  // jeep?
    {
        character.wheelFront = 6.0f;
        character.wheelBack  = 6.0f;
        character.wheelLeft  = 5.0f;
        character.wheelRight = 5.0f;
    }
    if ( type == OBJECT_MOBILEdr )
    {
        character.wheelFront = 4.0f;
        character.wheelBack  = 4.0f;
        character.wheelLeft  = 4.0f;
        character.wheelRight = 4.0f;
    }
    if ( type == OBJECT_MOBILEsa ||
         type == OBJECT_MOBILEst )
    {
        character.wheelFront = 4.0f;
        character.wheelBack  = 4.0f;
        character.wheelLeft  = 4.0f;
        character.wheelRight = 4.0f;
    }
    if ( type == OBJECT_MOBILErt ||
         type == OBJECT_MOBILErc ||
         type == OBJECT_MOBILErr ||
         type == OBJECT_MOBILErs ||
         type == OBJECT_MOBILErp)  // large caterpillars?
    {
        character.wheelFront = 5.0f;
        character.wheelBack  = 5.0f;
        character.wheelLeft  = 6.0f;
        character.wheelRight = 6.0f;
    }
    if ( type == OBJECT_MOBILEfa ||
         type == OBJECT_MOBILEfb ||
         type == OBJECT_MOBILEfc ||
         type == OBJECT_MOBILEfi ||
         type == OBJECT_MOBILEfs ||
         type == OBJECT_MOBILEft )  // flying?
    {
        character.wheelFront = 5.0f;
        character.wheelBack  = 4.0f;
        character.wheelLeft  = 4.5f;
        character.wheelRight = 4.5f;
    }
    if ( type == OBJECT_MOBILEia ||
         type == OBJECT_MOBILEib ||
         type == OBJECT_MOBILEic ||
         type == OBJECT_MOBILEii ||
         type == OBJECT_MOBILEis ||
         type == OBJECT_MOBILEit)  // legs?
    {
        character.wheelFront = 4.0f;
        character.wheelBack  = 4.0f;
        character.wheelLeft  = 5.0f;
        character.wheelRight = 5.0f;
    }
    if ( type == OBJECT_MOBILEta ||
         type == OBJECT_MOBILEtb ||
         type == OBJECT_MOBILEtc ||
         type == OBJECT_MOBILEti ||
         type == OBJECT_MOBILEts ||
         type == OBJECT_MOBILEtt )  // caterpillars?
    {
        character.wheelFront = 4.0f;
        character.wheelBack  = 4.0f;
        character.wheelLeft  = 4.8f;
        character.wheelRight = 4.8f;
    }
    if ( type == OBJECT_MOBILEtg )
    {
        character.wheelFront = 4.0f;
        character.wheelBack  = 3.0f;
        character.wheelLeft  = 4.0f;
        character.wheelRight = 4.0f;
    }
    if ( type == OBJECT_MOBILEwa ||
         type == OBJECT_MOBILEwb ||
         type == OBJECT_MOBILEwc ||
         type == OBJECT_MOBILEwi ||
         type == OBJECT_MOBILEws ||
         type == OBJECT_MOBILEwt )  // wheels?
    {
        character.wheelFront = 3.0f;
        character.wheelBack  = 4.0f;
        character.wheelLeft  = 4.0f;
        character.wheelRight = 4.0f;
    }

    return character;
}

bool CMovableHardcodeCollection::GetSlowUnderWater(ObjectType type)
{
    if ( type == OBJECT_HUMAN ||
         type == OBJECT_TECH  ) return true;

    return false;
}

bool CMovableHardcodeCollection::GetHaveSatCom(ObjectType type)
{
    if ( type == OBJECT_HUMAN ) return true;

    return false;
}

SoundType CMovableHardcodeCollection::GetSoundOnSlide(ObjectType type)
{
    if ( type == OBJECT_HUMAN ||
         type == OBJECT_TECH  )
    {
        return SOUND_NONE;
    }

    return SOUND_SLIDE;
}

float CMovableHardcodeCollection::GetMovableEnergyFactor(ObjectType type)
{
    float factor = 1.0f;
    if ( type == OBJECT_MOBILEia ||
         type == OBJECT_MOBILEib ||
         type == OBJECT_MOBILEis ||
         type == OBJECT_MOBILEic ||
         type == OBJECT_MOBILEii ||
         type == OBJECT_MOBILEit )  factor = 0.5f;

    return 0.005f * factor;
}

bool CMovableHardcodeCollection::IsTiltOnLandAsHuman(ObjectType type)
{
    if ( type == OBJECT_HUMAN ||
         type == OBJECT_TECH  )  return true;

    return false;
}

bool CMovableHardcodeCollection::IsTiltOnLandAsWingedRobot(ObjectType type)
{
    if ( type == OBJECT_MOBILEfa ||
         type == OBJECT_MOBILEfb ||
         type == OBJECT_MOBILEfc ||
         type == OBJECT_MOBILEfi ||
         type == OBJECT_MOBILEfs ||
         type == OBJECT_MOBILEft )  return true;

    return false;
}

bool CMovableHardcodeCollection::IsTiltOnLandAsNormalRobot(ObjectType type)
{
    if ( type == OBJECT_MOBILEwa ||
         type == OBJECT_MOBILEwb ||
         type == OBJECT_MOBILEwc ||
         type == OBJECT_MOBILEwi ||
         type == OBJECT_MOBILEws ||
         type == OBJECT_MOBILEwt ||
         type == OBJECT_MOBILEtg )  return true;

    return false;
}

bool CMovableHardcodeCollection::IsTiltOnLandAsApolloRobot(ObjectType type)
{
    if ( type == OBJECT_APOLLO2  )  return true;

    return false;
}

bool CMovableHardcodeCollection::IsTiltOnFlightAsAlienWasp(ObjectType type)
{
    if ( type == OBJECT_BEE  )  return true;

    return false;
}

bool CMovableHardcodeCollection::IsTiltOnFlightAsHuman(ObjectType type)
{
    if ( type == OBJECT_HUMAN ||
         type == OBJECT_TECH  )  return true;

    return false;
}

bool CMovableHardcodeCollection::IsTiltOnFlightAsWingedRobot(ObjectType type)
{
    if ( type == OBJECT_MOBILEfa ||
         type == OBJECT_MOBILEfb ||
         type == OBJECT_MOBILEfc ||
         type == OBJECT_MOBILEfi ||
         type == OBJECT_MOBILEfs ||
         type == OBJECT_MOBILEft )  return true;

    return false;
}

bool CMovableHardcodeCollection::IsTiltOnSwimAsHuman(ObjectType type)
{
    if ( type == OBJECT_HUMAN ||
         type == OBJECT_TECH  )  return true;

    return false;
}

bool CMovableHardcodeCollection::IsExhaustBubblesOnEnteringWater(ObjectType type)
{
    if ( type == OBJECT_MOBILEia ||
         type == OBJECT_MOBILEib ||
         type == OBJECT_MOBILEic ||
         type == OBJECT_MOBILEii ||
         type == OBJECT_MOBILEis ||
         type == OBJECT_MOBILEit ||  // legs?
         type == OBJECT_MOBILEdr ||
         type == OBJECT_MOTHER   ||
         type == OBJECT_ANT      ||
         type == OBJECT_SPIDER   ||
         type == OBJECT_BEE      ||
         type == OBJECT_WORM     ||
         type == OBJECT_APOLLO2  )  return false;

    return true;
}

float CMovableHardcodeCollection::IsExhaustBubblesOnEnteringWaterTime(ObjectType type)
{
    if ( type == OBJECT_HUMAN )  return 3.0f;
    return 8.0f;
}

bool CMovableHardcodeCollection::IsExhaustDropsOnLeavingWater(ObjectType type)
{
    if ( type == OBJECT_MOBILEia ||
         type == OBJECT_MOBILEib ||
         type == OBJECT_MOBILEic ||
         type == OBJECT_MOBILEii ||
         type == OBJECT_MOBILEis ||
         type == OBJECT_MOBILEit ||  // legs?
         type == OBJECT_MOBILEdr ||
         type == OBJECT_MOTHER   ||
         type == OBJECT_ANT      ||
         type == OBJECT_SPIDER   ||
         type == OBJECT_BEE      ||
         type == OBJECT_WORM     ||
         type == OBJECT_APOLLO2  )  return false;

    return true;
}

bool CMovableHardcodeCollection::IsExhaustOnCrashAsHuman(ObjectType type)
{
    if ( (type == OBJECT_HUMAN ||
          type == OBJECT_TECH  ) )   return true;
    return false;
}

bool CMovableHardcodeCollection::IsExhaustOnCrashAsTrackedRobot(ObjectType type)
{
    if ((type == OBJECT_MOBILEta ||
         type == OBJECT_MOBILEtb ||
         type == OBJECT_MOBILEtc ||
         type == OBJECT_MOBILEti ||
         type == OBJECT_MOBILEts ||
         type == OBJECT_MOBILEtt  ) )   return true;
    return false;
}

bool CMovableHardcodeCollection::IsExhaustOnCrashAsHeavyRobot(ObjectType type)
{
    if ((type == OBJECT_MOBILErt ||
         type == OBJECT_MOBILErc ||
         type == OBJECT_MOBILErr ||
         type == OBJECT_MOBILErs ||
         type == OBJECT_MOBILErp  ) )   return true;
    return false;
}

bool CMovableHardcodeCollection::IsExhaustOnLandAsHuman(ObjectType type)
{
    if ( (type == OBJECT_HUMAN ||
          type == OBJECT_TECH  ) )   return true;
    return false;
}

bool CMovableHardcodeCollection::IsExhaustOnLandAsWingedRobot(ObjectType type)
{
    if ((type == OBJECT_MOBILEfa ||
         type == OBJECT_MOBILEfb ||
         type == OBJECT_MOBILEfc ||
         type == OBJECT_MOBILEfi ||
         type == OBJECT_MOBILEfs ||
         type == OBJECT_MOBILEft  ) )   return true;
    return false;
}

bool CMovableHardcodeCollection::IsExhaustOnFlightAsHuman(ObjectType type)
{
    if ( (type == OBJECT_HUMAN ||
          type == OBJECT_TECH  ) )   return true;
    return false;
}

bool  CMovableHardcodeCollection::IsExhaustOnLandAsHeavyRobot(ObjectType type)
{
    if ((type == OBJECT_MOBILErt ||
         type == OBJECT_MOBILErc ||
         type == OBJECT_MOBILErr ||
         type == OBJECT_MOBILErs ||
         type == OBJECT_MOBILErp  ) )   return true;
    return false;
}

bool  CMovableHardcodeCollection::IsExhaustOnLandAsNormalRobot(ObjectType type)
{
    if ((type == OBJECT_MOBILEta ||
         type == OBJECT_MOBILEtb ||
         type == OBJECT_MOBILEtc ||
         type == OBJECT_MOBILEti ||
         type == OBJECT_MOBILEts ||
         type == OBJECT_MOBILEtt ||
         type == OBJECT_MOBILEtg ||
         type == OBJECT_MOBILEwa ||
         type == OBJECT_MOBILEwb ||
         type == OBJECT_MOBILEwc ||
         type == OBJECT_MOBILEwi ||
         type == OBJECT_MOBILEws ||
         type == OBJECT_MOBILEwt ||
         type == OBJECT_MOBILEsa ||
         type == OBJECT_MOBILEst  ) )   return true;
    return false;
}

bool CMovableHardcodeCollection::IsExhaustOnFlightAsWingedRobot(ObjectType type)
{
    if ((type == OBJECT_MOBILEfa ||
         type == OBJECT_MOBILEfb ||
         type == OBJECT_MOBILEfc ||
         type == OBJECT_MOBILEfi ||
         type == OBJECT_MOBILEfs ||
         type == OBJECT_MOBILEft  ) )   return true;
    return false;
}

bool CMovableHardcodeCollection::IsExhaustOnSwimAsHuman(ObjectType type)
{
    if ( (type == OBJECT_HUMAN ||
          type == OBJECT_TECH  ) )   return true;
    return false;
}

bool CMovableHardcodeCollection::IsExhaustOnSwimAsAmphibiousRobot(ObjectType type)
{
    if ( (type == OBJECT_MOBILEst ||
          type == OBJECT_MOBILEsa  ) )   return true;
    return false;
}

float CMovableHardcodeCollection::GetMaxSafeWaterLevel(ObjectType type)
{
    if ( type == OBJECT_HUMAN ||
         type == OBJECT_TECH  )
    {
        return 3.0f;
    }

    if ( type == OBJECT_MOBILEfa ||
         type == OBJECT_MOBILEta ||
         type == OBJECT_MOBILEwa ||
         type == OBJECT_MOBILEia ||
         type == OBJECT_MOBILEfb ||
         type == OBJECT_MOBILEtb ||
         type == OBJECT_MOBILEwb ||
         type == OBJECT_MOBILEib ||
         type == OBJECT_MOBILEfc ||
         type == OBJECT_MOBILEtc ||
         type == OBJECT_MOBILEwc ||
         type == OBJECT_MOBILEic ||
         type == OBJECT_MOBILEfi ||
         type == OBJECT_MOBILEti ||
         type == OBJECT_MOBILEwi ||
         type == OBJECT_MOBILEii ||
         type == OBJECT_MOBILEfs ||
         type == OBJECT_MOBILEts ||
         type == OBJECT_MOBILEws ||
         type == OBJECT_MOBILEis ||
         type == OBJECT_MOBILErt ||
         type == OBJECT_MOBILErc ||
         type == OBJECT_MOBILErr ||
         type == OBJECT_MOBILErs ||
         type == OBJECT_MOBILEsa ||
         type == OBJECT_MOBILEtg ||
         type == OBJECT_MOBILEft ||
         type == OBJECT_MOBILEtt ||
         type == OBJECT_MOBILEwt ||
         type == OBJECT_MOBILEit ||
         type == OBJECT_MOBILErp ||
         type == OBJECT_MOBILEst ||
         type == OBJECT_MOBILEdr )
    {
        return 2.0f;
    }

    return 0.0f; 
}

float CMovableHardcodeCollection::GetWaterSplashLevelMin(ObjectType type)
{
    if ( (type == OBJECT_HUMAN ||
          type == OBJECT_TECH  ) )   return 3.0f;

    return 0.0f;
}

float CMovableHardcodeCollection::GetWaterSplashLevelMax(ObjectType type)
{
    if ( (type == OBJECT_HUMAN ||
          type == OBJECT_TECH  ) )   return 3.0f;

    return 9.0f;
}

float CMovableHardcodeCollection::GetWaterSplashDiameter(ObjectType type)
{
    if ( (type == OBJECT_HUMAN ||
          type == OBJECT_TECH  ) )   return 5.0f;

    return 2.5f;
}

float CMovableHardcodeCollection::GetWaterSplashForce(ObjectType type)
{
    if ( (type == OBJECT_HUMAN ||
          type == OBJECT_TECH  ) )   return 1.0f;

    return 1.3f;
}

CObjectTrackedMovableDetails CMovableHardcodeCollection::GetTrackedDetails(ObjectType type)
{
    if ( type == OBJECT_MOBILEta ||
         type == OBJECT_MOBILEtb ||
         type == OBJECT_MOBILEtc ||
         type == OBJECT_MOBILEti ||
         type == OBJECT_MOBILEts ||
         type == OBJECT_MOBILEtt )
    {
        return {-12.0f*Math::PI/180.0f, 8.0f*Math::PI/180.0f};
    }
    else if ( type == OBJECT_MOBILEsa ||
              type == OBJECT_MOBILEst )
    {
        return {-15.0f*Math::PI/180.0f, 15.0f*Math::PI/180.0f};
    }
    else if ( type == OBJECT_MOBILEdr )
    {
        return {-10.0f*Math::PI/180.0f, 10.0f*Math::PI/180.0f};
    }
    else if ( type == OBJECT_MOBILErt ||
              type == OBJECT_MOBILErc ||
              type == OBJECT_MOBILErr ||
              type == OBJECT_MOBILErs ||
              type == OBJECT_MOBILErp )
    {
        return {-10.0f*Math::PI/180.0f, 15.0f*Math::PI/180.0f};
    }

    return CObjectTrackedMovableDetails();
}

CObjectWheeledMovableDetails CMovableHardcodeCollection::GetWheeledDetails(ObjectType type)
{
    float       back, front, dist, radius;

    if ( type == OBJECT_MOBILEtg )
    {
        back   = -2.0f;  // back wheels position
        front  =  3.0f;  // front wheels position
        dist   =  3.0f;  // distancing wheels Z
        radius =  1.0f;
        return {back, front, dist, radius, 1.0, false};
    }
    else if ( type == OBJECT_APOLLO2 )
    {
        back   = -5.75f;  // back wheels position
        front  =  5.75f;  // front wheels position
        dist   =  5.00f;  // distancing wheels Z
        radius =  1.65f;
        return {back, front, dist, radius, 0.5, true};
    }
    else if ( type == OBJECT_APOLLO2 )
    {
        back   = -3.0f;  // back wheels position
        front  =  2.0f;  // front wheels position
        dist   =  3.0f;  // distancing wheels Z
        radius =  1.0f;
        return {back, front, dist, radius, 1.0, false};
    }

    return CObjectWheeledMovableDetails();
}

