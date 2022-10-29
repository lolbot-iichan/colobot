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


#include "object/task/taskbuild.h"

#include "graphics/core/color.h"
#include "graphics/core/light.h"

#include "graphics/engine/engine.h"
#include "graphics/engine/lightman.h"
#include "graphics/engine/terrain.h"
#include "graphics/engine/water.h"

#include "level/robotmain.h"

#include "math/geometry.h"

#include "object/object_manager.h"
#include "object/old_object.h"

#include "object/auto/auto.h"

#include "object/details/details_provider.h"
#include "object/details/physical_details.h"
#include "object/details/task_executor_details.h"

#include "object/helpers/cargo_helpers.h"

#include "object/motion/motionhuman.h"

#include "physics/physics.h"

#include "sound/sound.h"

// Object's constructor.

CTaskBuild::CTaskBuild(COldObject* object) : CForegroundTask(object)
{
    int     i;

    m_type = OBJECT_NULL;
    m_time = 0.0f;
    m_soundChannel = -1;

    for ( i=0 ; i<TBMAXLIGHT ; i++ )
    {
        m_lightRank[i] = -1;
    }
}

// Object's destructor.

CTaskBuild::~CTaskBuild()
{
    int     i;

    if ( m_soundChannel != -1 )
    {
        m_sound->FlushEnvelope(m_soundChannel);
        m_sound->AddEnvelope(m_soundChannel, 0.0f, 1.0f, 1.0f, SOPER_STOP);
        m_soundChannel = -1;
    }

    for ( i=0 ; i<TBMAXLIGHT ; i++ )
    {
        if ( m_lightRank[i] == -1 )  continue;
        m_lightMan->DeleteLight(m_lightRank[i]);
    }
}


// Creates a building.

void CTaskBuild::CreateBuilding(glm::vec3 pos, float angle, bool trainer)
{
    ObjectCreateParams params;
    params.pos = pos;
    params.angle = angle;
    params.type = m_type;
    params.power = 0.0f;
    params.team = m_object->GetTeam();
    params.trainer = trainer;
    m_building = CObjectManager::GetInstancePointer()->CreateObject(params);
    m_building->SetLock(true);  // not yet usable

    m_buildingHeight = GetObjectPhysicalDetails(m_building).height;
    m_buildingHeight *= 0.25f;

    m_buildingPos = m_building->GetPosition();
    m_buildingPos.y -= m_buildingHeight;
    m_building->SetPosition(m_buildingPos);
}

// Creates lights for the effects.

void CTaskBuild::CreateLight()
{
    Gfx::Color   color;
    glm::vec3 center, pos, dir;
    glm::vec2    c, p;
    float        angle;
    int          i;

    if ( !m_engine->GetLightMode() )  return;

    center = m_metal->GetPosition();

    angle = 0;
    for ( i=0 ; i<TBMAXLIGHT ; i++ )
    {
        m_lightRank[i] = m_lightMan->CreateLight();
        if ( m_lightRank[i] == -1 )  continue;

        c.x = center.x;
        c.y = center.z;
        p.x = center.x+40.0f;
        p.y = center.z;
        p = Math::RotatePoint(c, angle, p);
        pos.x = p.x;
        pos.z = p.y;
        pos.y = center.y+40.0f;
        dir = center-pos;

        Gfx::Light light;
        light.type       = Gfx::LIGHT_SPOT;
        light.ambient    = Gfx::Color(0.0f, 0.0f, 0.0f);
        light.diffuse    = Gfx::Color(0.0f, 0.0f, 0.0f); // invisible
        light.position   = pos;
        light.direction  = dir;
        light.spotIntensity = 128;
        light.attenuation0 = 1.0f;
        light.attenuation1 = 0.0f;
        light.attenuation2 = 0.0f;
        light.spotAngle = 90.0f*Math::PI/180.0f;
        m_lightMan->SetLight(m_lightRank[i], light);

        color.r = -1.0f;
        color.g = -1.0f;
        color.b = -0.5f;  // violet
        color.a =  0.0f;
        m_lightMan->SetLightColor(m_lightRank[i], color);
        m_lightMan->SetLightColorSpeed(m_lightRank[i], 1.0f/((1.0f/m_speed)*0.25f));

        angle += (Math::PI*2.0f)/TBMAXLIGHT;
    }

    m_bBlack = false;
}

// Switches the lights from black to white.

void CTaskBuild::BlackLight()
{
    Gfx::Color color;
    int        i;

    for ( i=0 ; i<TBMAXLIGHT ; i++ )
    {
        if ( m_lightRank[i] == -1 )  continue;

        color.r = 0.0f;
        color.g = 0.0f;
        color.b = 0.0f;  // white (invisible)
        color.a = 0.0f;
        m_lightMan->SetLightColor(m_lightRank[i], color);
        m_lightMan->SetLightColorSpeed(m_lightRank[i], 1.0f/((1.0f/m_speed)*0.75f));
    }

    m_bBlack = true;
}

// Management of an event.

bool CTaskBuild::EventProcess(const Event &event)
{
    glm::vec3        pos, dir, speed, pv, pm, tilt;
    glm::vec2           dim;
    float           a, g, cirSpeed, dist, linSpeed, diff;

    if ( m_engine->GetPause() )  return true;
    if ( event.type != EVENT_FRAME )  return true;
    if ( m_bError )  return false;

    m_time += event.rTime;

    m_progress += event.rTime*m_speed;  // other advance

    auto build = GetObjectTaskExecutorDetails(m_object).build;

    // Cancel if the player tries to move
    float axeX = event.motionInput.x;
    float axeY = event.motionInput.y;
    float axeZ = event.motionInput.z;
    if ( build.cancelOnMotion && m_object->GetSelect() &&
         (axeX != 0.0f || axeY != 0.0f || axeZ != 0.0f) &&
         (m_phase == TBP_TURN || m_phase == TBP_MOVE || m_phase == TBP_TAKE || m_phase == TBP_PREP) )
    {
        m_phase = TBP_STOP;
    }

    if ( m_phase == TBP_STOP )  // stops?
    {
        return true;
    }

    if ( m_phase == TBP_TURN )  // preliminary rotation?
    {
        a = m_object->GetRotationY();
        g = m_angleY;
        cirSpeed = Math::Direction(a, g)*1.0f;
        if ( cirSpeed >  1.0f )  cirSpeed =  1.0f;
        if ( cirSpeed < -1.0f )  cirSpeed = -1.0f;

        m_physics->SetMotorSpeedZ(cirSpeed);  // turns left/right
        return true;
    }

    if ( m_phase == TBP_MOVE )  // preliminary forward/backward?
    {
        dist = glm::distance(m_object->GetPosition(), m_metal->GetPosition());
        linSpeed = 0.0f;
        if ( m_physics->GetLand() )
        {
            if ( dist > 30.0f )  linSpeed =  1.0f;
            if ( dist < 30.0f )  linSpeed = -1.0f;
        }
        else
        {
            if ( dist > 55.0f )  linSpeed =  0.5f;
            if ( dist < 35.0f )  linSpeed = -0.5f;
        }
        m_physics->SetMotorSpeedX(linSpeed);  // forward/backward
        return true;
    }

    if ( m_phase == TBP_RECEDE )  // terminal back?
    {
        m_physics->SetMotorSpeedX(-1.0f);  // back
        return true;
    }

    if ( m_phase == TBP_TAKE )  // takes gun?
    {
        return true;
    }

    if ( m_phase == TBP_PREP )  // prepares?
    {
        return true;
    }

    if ( m_phase == TBP_TERM )  // ends?
    {
        return true;
    }

    if ( !m_bBuild )  // building to build?
    {
        m_bBuild = true;

        pos = m_metal->GetPosition();
        a   = m_object->GetRotationY();
        CreateBuilding(pos, a+Math::PI, m_object->GetTrainer());
        CreateLight();
    }

    pos = m_buildingPos;
    pos.y += m_buildingHeight*m_progress;
    m_building->SetPosition(pos);  // the building rises

    m_building->SetScale(m_progress*0.75f+0.25f);
    m_metal->SetScale(1.0f-m_progress);

    a = (2.0f-2.0f*m_progress);
    if ( a > 1.0f )  a = 1.0f;
    dir.x = (Math::Rand()-0.5f)*a*0.1f;
    dir.z = (Math::Rand()-0.5f)*a*0.1f;
    dir.y = (Math::Rand()-0.5f)*a*0.1f;
    m_building->SetCirVibration(dir);

    if ( !m_bBlack && m_progress >= 0.25f )
    {
        BlackLight();
    }

    if ( m_lastParticle+m_engine->ParticleAdapt(0.05f) <= m_time )
    {
        m_lastParticle = m_time;

        pos = m_metal->GetPosition();
        speed.x = (Math::Rand()-0.5f)*20.0f;
        speed.z = (Math::Rand()-0.5f)*20.0f;
        speed.y = Math::Rand()*10.0f;
        dim.x = Math::Rand()*6.0f+4.0f;
        dim.y = dim.x;
        m_particle->CreateParticle(pos, speed, dim, Gfx::PARTIFIRE);

        glm::mat4 mat = m_object->GetWorldMatrix(build.partNum);
        pos = Math::Transform(mat, build.particlePos);

        speed = m_metal->GetPosition();
        speed.x += (Math::Rand()-0.5f)*5.0f;
        speed.z += (Math::Rand()-0.5f)*5.0f;
        speed -= pos;
        dim.x = 2.0f;
        dim.y = dim.x;
        m_particle->CreateParticle(pos, speed, dim, Gfx::PARTIFIREZ);

        if ( Math::Rand() < 0.3f )
        {
            m_sound->Play(SOUND_BUILD, m_object->GetPosition(), 0.5f, 1.0f*Math::Rand()*1.5f);
        }
    }

    if ( build.execution == ExecutionAsRobot )
    {
        if(m_object->Implements(ObjectInterfaceType::JetFlying) && m_object->GetReactorRange()<0.2f && m_phase != TBP_MOVE)
        {
            pv = m_object->GetPosition();
            pm = m_metal->GetPosition();
            dist = glm::distance(pv, pm);
            diff = pm.y - 8.0f - pv.y;
            tilt = m_object->GetRotation();
            m_object->StartTaskGunGoal(asin(diff/dist)-tilt.z, 0.0f);
        }
    }

    return true;
}


// Assigns the goal was achieved.

Error CTaskBuild::Start(ObjectType type)
{
    float iAngle, oAngle;

    m_type = type;
    m_lastParticle = 0.0f;
    m_progress = 0.0f;

    iAngle = m_object->GetRotationY();
    iAngle = Math::NormAngle(iAngle);  // 0..2*Math::PI
    oAngle = iAngle;

    auto task = GetObjectTaskExecutorDetails(m_object).build;

    m_bError = true;  // operation impossible
    {
        Error err = CanStartTask(&task);
        if ( err != ERR_OK )  return err;

        err = CRobotMain::GetInstancePointer()->CanBuildError(type, m_object->GetTeam());
        if ( err != ERR_OK )  return err;

        err = SearchMetalObject(oAngle, 2.0f, 100.0f, Math::PI*0.25f);
        if ( err != ERR_OK )  return err;
    
        glm::vec3 pv = m_object->GetPosition();
        glm::vec3 pm = m_metal->GetPosition();
        if(!m_physics->GetLand() && fabs(pm.y-pv.y)>8.0f) return ERR_BUILD_METALAWAY;
    
        m_metal->SetLock(true);  // not usable
        m_camera->StartCentering(m_object, Math::PI*0.15f, 99.9f, 0.0f, 1.0f);
    
        m_phase = TBP_TURN;  // rotation necessary preliminary
        m_angleY = oAngle;  // angle was reached
    
        pv.y += 8.3f;
        m_angleZ = Math::RotateAngle(Math::DistanceProjected(pv, pm), fabs(pv.y-pm.y));
    
        m_physics->SetFreeze(true);  // it does not move
    }
    m_bBuild = false;  // not yet built
    m_bError = false;  // ok
    return ERR_OK;
}

// Indicates whether the action is finished.

Error CTaskBuild::IsEnded()
{
    CAuto*      automat;
    float       angle, dist, time, diff;
    glm::vec3       pv,   pm,   tilt;

    if ( m_engine->GetPause() )  return ERR_CONTINUE;
    if ( m_bError )  return ERR_STOP;

    if ( m_phase == TBP_TURN )  // preliminary rotation?
    {
        angle = m_object->GetRotationY();
        angle = Math::NormAngle(angle);  // 0..2*Math::PI

        if ( Math::TestAngle(angle, m_angleY-Math::PI*0.01f, m_angleY+Math::PI*0.01f) )
        {
            m_physics->SetMotorSpeedZ(0.0f);

            dist = glm::distance(m_object->GetPosition(), m_metal->GetPosition());
            if ( dist > 30.0f )
            {
                time = m_physics->GetLinTimeLength(dist-30.0f, 1.0f);
                m_speed = 1.0f/time;
            }
            else
            {
                time = m_physics->GetLinTimeLength(30.0f-dist, -1.0f);
                m_speed = 1.0f/time;
            }
            m_phase = TBP_MOVE;
            m_progress = 0.0f;
        }
        return ERR_CONTINUE;
    }

    if ( m_phase == TBP_MOVE )  // preliminary forward/backward?
    {
        dist = glm::distance(m_object->GetPosition(), m_metal->GetPosition());

        if ( (!m_physics->GetLand() && (dist >= 35.0f && dist <= 55.0f)) ||
             ( dist >= 25.0f && dist <= 35.0f) )
        {
            m_physics->SetMotorSpeedX(0.0f);

            auto build = GetObjectTaskExecutorDetails(m_object).build;
            if ( build.execution == ExecutionAsHuman )
            {
                m_motion->SetAction(MHS_GUN);  // takes gun
            }

            m_phase = TBP_TAKE;
            m_speed = 1.0f/1.0f;
            m_progress = 0.0f;
        }
        else
        {
            if ( m_progress > 1.0f )  // timeout?
            {
                m_metal->SetLock(false);  // usable again
                if ( dist < 30.0f )  return ERR_BUILD_METALNEAR;
                else                 return ERR_BUILD_METALAWAY;
            }
        }
        return ERR_CONTINUE;
    }

    if ( m_phase == TBP_TAKE )  // takes gun
    {
        if ( m_progress < 1.0f )  return ERR_CONTINUE;

        auto build = GetObjectTaskExecutorDetails(m_object).build;
        if ( build.execution == ExecutionAsHuman )
        {
            m_motion->SetAction(MHS_FIRE);  // shooting position
            m_object->SetObjectParent(14, 4);
            m_object->SetPartPosition(14, glm::vec3(0.6f, 0.1f, 0.3f));
            m_object->SetPartRotationZ(14, 0.0f);
        }
        if ( build.execution == ExecutionAsRobot )
        {
            m_object->SetObjectParent(1, 0);
            pv = m_object->GetPosition();
            pm = m_metal->GetPosition();
            dist = glm::distance(pv, pm);
            diff = pm.y - 8.0f - pv.y;
            tilt = m_object->GetRotation();
            if(dist) m_object->StartTaskGunGoal(asin(diff/dist)-tilt.z, 0.0f);
        }

        m_phase = TBP_PREP;
        m_speed = 1.0f/1.0f;
        m_progress = 0.0f;
    }

    if ( m_phase == TBP_PREP )  // prepares?
    {
        if ( m_progress < 1.0f )  return ERR_CONTINUE;

        m_soundChannel = m_sound->Play(SOUND_TREMBLE, m_object->GetPosition(), 0.0f, 1.0f, true);
        m_sound->AddEnvelope(m_soundChannel, 0.7f, 1.0f, 1.0f, SOPER_CONTINUE);
        m_sound->AddEnvelope(m_soundChannel, 0.7f, 1.5f, 7.0f, SOPER_CONTINUE);
        m_sound->AddEnvelope(m_soundChannel, 0.0f, 1.5f, 2.0f, SOPER_STOP);

        m_camera->StartEffect(Gfx::CAM_EFFECT_VIBRATION, m_metal->GetPosition(), 1.0f);

        m_phase = TBP_BUILD;
        m_speed = 1.0f/10.f;  // duration of 10s
        m_progress = 0.0f;
    }

    if ( m_phase == TBP_BUILD )  // construction?
    {
        if ( m_progress < 1.0f )  return ERR_CONTINUE;

        DeleteMark(m_metal->GetPosition(), 20.0f);

        CObjectManager::GetInstancePointer()->DeleteObject(m_metal);
        m_metal = nullptr;

        m_building->SetScale(1.0f);
        m_building->SetCirVibration(glm::vec3(0.0f, 0.0f, 0.0f));
        m_building->SetLock(false);  // building usable
        m_main->CreateShortcuts();
        m_main->DisplayText(m_onCompleted, m_building, Ui::TT_INFO, 10.0f, 50.0f);

        automat = m_building->GetAuto();
        if ( automat != nullptr )
        {
            automat->Init();
        }

        auto build = GetObjectTaskExecutorDetails(m_object).build;
        if ( build.execution == ExecutionAsHuman )
        {
            m_motion->SetAction(MHS_GUN);  // hands gun
        }

        m_phase = TBP_TERM;
        m_speed = 1.0f/1.0f;
        m_progress = 0.0f;
    }

    if ( m_phase == TBP_TERM )  // rotation terminale ?
    {
        if ( m_progress < 1.0f )  return ERR_CONTINUE;

        auto build = GetObjectTaskExecutorDetails(m_object).build;
        if ( build.execution == ExecutionAsHuman )
        {
            m_motion->SetAction(-1);
            m_object->SetObjectParent(14, 0);
            m_object->SetPartPosition(14, glm::vec3(-1.5f, 0.3f, -1.35f));
            m_object->SetPartRotationZ(14, Math::PI);
        }
        if ( build.execution == ExecutionAsRobot )
        {
            m_object->StartTaskGunGoal(0.0f, 0.0f);
        }

        if ( m_bNeedRecede )
        {
            m_phase = TBP_RECEDE;
            m_speed = 1.0f/1.5f;
            m_progress = 0.0f;
        }
    }

    if ( m_phase == TBP_RECEDE )  // back?
    {
        if ( m_progress < 1.0f )  return ERR_CONTINUE;

        m_physics->SetMotorSpeedX(0.0f);
    }

    if ( m_phase == TBP_STOP ) // canceled?
    {
        auto build = GetObjectTaskExecutorDetails(m_object).build;
        if ( build.execution == ExecutionAsHuman )
        {
            if ( m_progress < 1.0f && m_motion->GetAction() == MHS_GUN )  return ERR_CONTINUE;
    
            if ( m_motion->GetAction() == MHS_FIRE )
            {
                m_motion->SetAction(MHS_GUN);
                m_speed = 1.0f/1.0f;
                m_progress = 0.0f;
                return ERR_CONTINUE;
            }
    
            m_motion->SetAction(-1);

            // Place gun back
            m_object->SetObjectParent(14, 0);
            m_object->SetPartPosition(14, glm::vec3(-1.5f, 0.3f, -1.35f));
            m_object->SetPartRotationZ(14, Math::PI);
        }

        m_physics->SetMotorSpeedX(0.0f);
        m_physics->SetMotorSpeedZ(0.0f);

        m_metal->SetLock(false); // make titanium usable
    }

    Abort();
    return ERR_STOP;
}

// Suddenly ends the current action.

bool CTaskBuild::Abort()
{
    if ( m_soundChannel != -1 )
    {
        m_sound->FlushEnvelope(m_soundChannel);
        m_sound->AddEnvelope(m_soundChannel, 0.0f, 1.0f, 1.0f, SOPER_STOP);
        m_soundChannel = -1;
    }

    m_camera->StopCentering(m_object, 2.0f);
    m_physics->SetFreeze(false);  // is moving again
    return true;
}


// Checks whether the terrain is fairly flat
// and if there is not too close to another object.

Error CTaskBuild::FlatFloor(float reqRadius)
{
    glm::vec3    center, bPos;
    float       radius, max, bRadius = 0.0f, angle, dist;
    bool        bLittleFlat, bBase;

    radius = reqRadius;
    //if ( radius == 0.0f )  return ERR_UNKNOWN;

    center = m_metal->GetPosition();
    angle = m_terrain->GetFineSlope(center);
    bLittleFlat = ( angle < Gfx::TERRAIN_FLATLIMIT);

    max = m_terrain->GetFlatZoneRadius(center, radius);
    if ( max < radius )  // area too small?
    {
        if ( bLittleFlat )
        {
            m_main->SetShowLimit(1, Gfx::PARTILIMIT3, m_metal, center, max, 10.0f);
        }
        return bLittleFlat?ERR_BUILD_FLATLIT:ERR_BUILD_FLAT;
    }

    max = 100000.0f;
    bBase = false;
    for (CObject* pObj : CObjectManager::GetInstancePointer()->GetAllObjects())
    {
        if ( !pObj->GetActive() )  continue;  // inactive?
        if (IsObjectBeingTransported(pObj))  continue;
        if ( pObj == m_metal )  continue;
        if ( pObj == m_object )  continue;

        float r = GetObjectPhysicalDetails(pObj).noBuildRadius;
        if ( r > 0 )
        {
            glm::vec3 oPos = pObj->GetPosition();
            dist = glm::distance(center, oPos) - r;
            if ( dist < max )
            {
                max = dist;
                bPos = oPos;
                bRadius = 0.0f;
                bBase = true;
            }
        }
        else
        {
            for (const auto& crashSphere : pObj->GetAllCrashSpheres())
            {
                glm::vec3 oPos = crashSphere.sphere.pos;
                float oRadius = crashSphere.sphere.radius;

                dist = glm::distance(center, oPos)-oRadius;
                if ( dist < max )
                {
                    max = dist;
                    bPos = oPos;
                    bRadius = oRadius;
                    bBase = false;
                }
            }
        }
    }
    if ( max < radius )
    {
        m_main->SetShowLimit(1, Gfx::PARTILIMIT2, m_metal, center, max, 10.0f);
        if ( bRadius < 2.0f )  bRadius = 2.0f;
        m_main->SetShowLimit(2, Gfx::PARTILIMIT3, m_metal, bPos, bRadius, 10.0f);
        return bBase?ERR_BUILD_BASE:ERR_BUILD_BUSY;
    }

    max = 100000.0f;
    for (CObject* pObj : CObjectManager::GetInstancePointer()->GetAllObjects())
    {
        if ( !pObj->GetActive() )  continue;  // inactive?
        if (IsObjectBeingTransported(pObj))  continue;
        if ( pObj == m_metal )  continue;
        if ( pObj == m_object )  continue;

        if ( GetObjectPhysicalDetails(pObj).hasBuildMargin )
        {
            for (const auto& crashSphere : pObj->GetAllCrashSpheres())
            {
                glm::vec3 oPos = crashSphere.sphere.pos;
                float oRadius = crashSphere.sphere.radius;

                dist = glm::distance(center, oPos)-oRadius;
                if ( dist < max )
                {
                    max = dist;
                    bPos = oPos;
                    bRadius = oRadius;
                }
            }
        }
    }
    if ( max-BUILDMARGIN < radius )
    {
        m_main->SetShowLimit(1, Gfx::PARTILIMIT2, m_metal, center, max-BUILDMARGIN, 10.0f);
        m_main->SetShowLimit(2, Gfx::PARTILIMIT3, m_metal, bPos, bRadius+BUILDMARGIN, 10.0f);
        return bBase?ERR_BUILD_BASE:ERR_BUILD_NARROW;
    }

    return ERR_OK;
}

// Seeks the nearest metal object.

Error CTaskBuild::SearchMetalObject(float &angle, float dMin, float dMax,
                                       float aLimit)
{
    CObject     *pBest;
    glm::vec3   iPos, oPos;
    float       min, iAngle, a, aa, aBest, distance, magic;
    bool        bMetal;
    float       reqRadius = 0.0f;

    auto build = GetObjectTaskExecutorDetails(m_object).build;

    iPos   = m_object->GetPosition();
    iAngle = m_object->GetRotationY();
    iAngle = Math::NormAngle(iAngle);  // 0..2*Math::PI

    min = 1000000.0f;
    pBest = nullptr;
    bMetal = false;
    for (CObject* pObj : CObjectManager::GetInstancePointer()->GetAllObjects())
    {
        if ( !pObj->GetActive() )  continue;  // objet inactive?
        if (IsObjectBeingTransported(pObj))  continue;

        bool bMatched = false;
        for ( auto it: build.objects )
        {
            if (pObj->GetType() == it.input && m_type == it.output)
            {
                m_onCompleted = it.message;
                m_bNeedRecede = it.needRecede;
                reqRadius = it.reqRadius;
                bMatched = true;
            }
        }
        if ( !bMatched )  continue;

        bMetal = true;  // metal exists

        oPos = pObj->GetPosition();
        distance = glm::distance(oPos, iPos);
        a = Math::RotateAngle(oPos.x-iPos.x, iPos.z-oPos.z);  // CW!

        if ( distance > dMax )  continue;
        if ( !Math::TestAngle(a, iAngle-aLimit, iAngle+aLimit) )  continue;

        if ( distance < dMin )
        {
            Error err = FlatFloor(reqRadius);
            return err == ERR_OK ? ERR_BUILD_METALNEAR : err;
        }

        aa = fabs(a-iAngle);
        if ( aa > Math::PI )  aa = Math::PI*2.0f-aa;
        magic = distance*aa;

        if ( magic < min )
        {
            min = magic;
            aBest = a;
            pBest = pObj;
        }
    }

    angle = aBest;
    m_metal = pBest;

    if ( pBest == nullptr )
    {
        if ( bMetal )  return ERR_BUILD_METALAWAY;  // too far
        else           return ERR_BUILD_METALINEX;  // non-existent
    }

    return FlatFloor(reqRadius);
}

// Destroys all the close marks.

void CTaskBuild::DeleteMark(glm::vec3 pos, float radius)
{
    std::vector<CObject*> objectsToDelete;

    auto typesToRemove = GetObjectTaskExecutorDetails(m_object).build.remove;

    for (CObject* obj : CObjectManager::GetInstancePointer()->GetAllObjects())
    {
        for ( auto it: typesToRemove )
        {
            if ( it.input != obj->GetType() )  continue;

            glm::vec3 oPos = obj->GetPosition();
            float distance = glm::distance(oPos, pos);
            if ( distance <= radius )
            {
                objectsToDelete.push_back(obj);
                break;
            }
        }
    }

    for (CObject* obj : objectsToDelete)
    {
        CObjectManager::GetInstancePointer()->DeleteObject(obj);
    }
}
