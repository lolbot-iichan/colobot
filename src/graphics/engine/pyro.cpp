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


#include "graphics/engine/pyro.h"

#include "app/app.h"

#include "common/logger.h"

#include "graphics/core/triangle.h"

#include "graphics/engine/engine.h"
#include "graphics/engine/lightman.h"
#include "graphics/engine/particle.h"
#include "graphics/engine/terrain.h"

#include "level/robotmain.h"

#include "math/geometry.h"

#include "object/object_manager.h"
#include "object/old_object.h"

#include "object/details/details_provider.h"
#include "object/details/destroyable_details.h"

#include "object/helpers/cargo_helpers.h"

#include "object/interface/shielder_object.h"

#include "object/motion/motionhuman.h"

#include "sound/sound.h"


// Graphics module namespace
namespace Gfx
{


CPyro::CPyro()
{
    m_engine      = CEngine::GetInstancePointer();
    m_main        = CRobotMain::GetInstancePointer();
    m_terrain     = m_main->GetTerrain();
    m_camera      = m_main->GetCamera();
    m_particle    = m_engine->GetParticle();
    m_lightMan    = m_engine->GetLightManager();
    m_sound       = CApplication::GetInstancePointer()->GetSound();
}

CPyro::~CPyro()
{
}

void CPyro::DeleteObject()
{
    if ( m_lightRank != -1 )
    {
        m_lightMan->DeleteLight(m_lightRank);
        m_lightRank = -1;
    }
}

bool CPyro::Create(PyroType type, CObject* obj, float force)
{
    m_object = obj;
    m_force = force;

    ObjectType oType = obj->GetType();
    int objRank = obj->GetObjectRank(0);
    if (objRank == -1) return false;

    glm::vec3 min{}, max{};
    m_engine->GetObjectBBox(objRank, min, max);
    glm::vec3 pos = obj->GetPosition();

    DisplayError(type, obj);  // displays eventual messages

    for (const auto& crashSphere : obj->GetAllCrashSpheres())
    {
        m_crashSpheres.push_back(crashSphere.sphere);
    }

    // Calculates the size of the effect.
    if ( oType == OBJECT_ANT    ||
         oType == OBJECT_BEE    ||
         oType == OBJECT_WORM   ||
         oType == OBJECT_SPIDER )
    {
        m_size = 40.0f;
    }
    else
    {
        m_size = glm::distance(min, max)*2.0f;
        if ( m_size <  4.0f )  m_size =  4.0f;
        if ( m_size > 80.0f )  m_size = 80.0f;
    }
    if ( oType == OBJECT_TNT  ||
         oType == OBJECT_BOMB )
    {
        m_size *= 2.0f;
    }

    m_pos = pos+(min+max)/2.0f;
    m_type = type;
    m_progress = 0.0f;
    m_speed = 1.0f/20.0f;    m_time = 0.0f;
    m_lastParticle = 0.0f;
    m_lastParticleSmoke = 0.0f;
    m_lightRank = -1;

    if ( oType == OBJECT_TEEN28 ||
         oType == OBJECT_TEEN31 )
    {
        m_pos.y = pos.y+1.0f;
    }

    // Seeking the position of the battery.

    CObject* power = GetObjectInPowerCellSlot(obj);

    if (power == nullptr)
    {
        m_power = false;
    }
    else
    {
        m_power = true;
        pos = power->GetPosition();
        pos.y += 1.0f;
        glm::mat4 mat = obj->GetWorldMatrix(0);
        m_posPower = Math::Transform(mat, pos);
    }

    if ( oType == OBJECT_POWER   ||
         oType == OBJECT_ATOMIC  ||
         oType == OBJECT_URANIUM ||
         oType == OBJECT_TNT     ||
         oType == OBJECT_BOMB    )
    {
        m_power = true;
        glm::mat4 mat = obj->GetWorldMatrix(0);
        m_posPower = Math::Transform(mat, glm::vec3(0.0f, 1.0f, 0.0f));
        m_pos = m_posPower;
    }
    if ( oType == OBJECT_STATION )
    {
        m_power = true;
        glm::mat4 mat = obj->GetWorldMatrix(0);
        m_posPower = Math::Transform(mat, glm::vec3(-15.0f, 7.0f, 0.0f));
        m_pos = m_posPower;
    }
    if ( oType == OBJECT_ENERGY )
    {
        m_power = true;
        glm::mat4 mat = obj->GetWorldMatrix(0);
        m_posPower = Math::Transform(mat, glm::vec3(-7.0f, 6.0f, 0.0f));
        m_pos = m_posPower;
    }
    if ( oType == OBJECT_NUCLEAR )
    {
        m_power = true;
        glm::mat4 mat = obj->GetWorldMatrix(0);
        m_posPower = Math::Transform(mat, glm::vec3(0.0f, 0.0f, 0.0f));
        assert(m_pos == m_posPower);
        m_pos = m_posPower;
    }
    if ( oType == OBJECT_PARA )
    {
        m_power = true;
        glm::mat4 mat = obj->GetWorldMatrix(0);
        m_posPower = Math::Transform(mat, glm::vec3(0.0f, 0.0f, 0.0f));
        assert(m_pos == m_posPower);
        m_pos = m_posPower;
    }

    // Plays the sound of a pyrotechnic effect.
    if ( type == PT_FRAGT  ||
         type == PT_FRAGW  ||
         type == PT_EXPLOT ||
         type == PT_EXPLOW )
    {
        SoundType sound;
        if ( m_power )
        {
            sound = SOUND_EXPLOp;
        }
        else
        {
            sound = SOUND_EXPLO;
        }
        if ( oType == OBJECT_STONE   ||
             oType == OBJECT_METAL   ||
             oType == OBJECT_BULLET  ||
             oType == OBJECT_BBOX    ||
             oType == OBJECT_KEYa    ||
             oType == OBJECT_KEYb    ||
             oType == OBJECT_KEYc    ||
             oType == OBJECT_KEYd    )
        {
            sound = SOUND_EXPLOl;
        }
        if ( oType == OBJECT_URANIUM ||
             oType == OBJECT_POWER   ||
             oType == OBJECT_ATOMIC  ||
             oType == OBJECT_TNT     ||
             oType == OBJECT_BOMB    )
        {
            sound = SOUND_EXPLOlp;
        }
        m_sound->Play(sound, m_pos);
    }
    if ( type == PT_FRAGO  ||
         type == PT_EXPLOO ||
         type == PT_SPIDER ||
         type == PT_SHOTM  )
    {
        m_sound->Play(SOUND_EXPLOi, m_pos);
    }
    if ( type == PT_FRAGV )
    {
        m_sound->Play(SOUND_BOUMv, m_pos);
    }
    if ( type == PT_BURNT ||
         type == PT_BURNO )
    {
        m_soundChannel = m_sound->Play(SOUND_BURN, m_pos, 1.0f, 1.0f, true);
        m_sound->AddEnvelope(m_soundChannel, 1.0f, 1.0f, 12.0f, SOPER_CONTINUE);
        m_sound->AddEnvelope(m_soundChannel, 0.0f, 1.0f,  5.0f, SOPER_STOP);
    }
    if ( type == PT_BURNO )
    {
        m_sound->Play(SOUND_DEADi, m_pos);
        m_sound->Play(SOUND_DEADi, m_engine->GetEyePt());
    }
    if ( type == PT_EGG )
    {
        m_sound->Play(SOUND_EGG, m_pos);
    }
    if ( type == PT_WPCHECK  ||
         type == PT_FLCREATE ||
         type == PT_FLDELETE )
    {
        m_sound->Play(SOUND_WAYPOINT, m_pos);
    }
    if ( oType == OBJECT_HUMAN )
    {
        if ( type == PT_DEADG )
        {
            m_sound->Play(SOUND_DEADg, m_pos);
        }
        if ( type == PT_DEADW )
        {
            m_sound->Play(SOUND_DEADw, m_pos);
        }
        assert(m_object->Implements(ObjectInterfaceType::Controllable));
        if ( type == PT_SHOTH && dynamic_cast<CControllableObject&>(*m_object).GetSelect() )
        {
            m_sound->Play(SOUND_AIE, m_pos);
            m_sound->Play(SOUND_AIE, m_engine->GetEyePt());
        }
    }

    if ( m_type == PT_FRAGT ||
         m_type == PT_FRAGO ||
         m_type == PT_FRAGW ||
         m_type == PT_FRAGV )
    {
        m_engine->DeleteShadowSpot(m_object->GetObjectRank(0));
    }

    if ( m_type == PT_DEADG )
    {
        assert(m_object->Implements(ObjectInterfaceType::Destroyable));
        dynamic_cast<CDestroyableObject&>(*m_object).SetDying(DeathType::Dead);

        assert(obj->Implements(ObjectInterfaceType::Movable));
        dynamic_cast<CMovableObject&>(*obj).GetMotion()->SetAction(MHS_DEADg, 1.0f);

        m_camera->StartCentering(m_object, Math::PI*0.5f, 99.9f, 0.0f, 1.5f);
        m_camera->StartOver(CAM_OVER_EFFECT_FADEOUT_WHITE, m_pos, 1.0f);
        m_speed = 1.0f/10.0f;
        return true;
    }
    if ( m_type == PT_DEADW )
    {
        assert(m_object->Implements(ObjectInterfaceType::Destroyable));
        dynamic_cast<CDestroyableObject&>(*m_object).SetDying(DeathType::Dead);

        assert(obj->Implements(ObjectInterfaceType::Movable));
        dynamic_cast<CMovableObject&>(*obj).GetMotion()->SetAction(MHS_DEADw, 1.0f);

        m_camera->StartCentering(m_object, Math::PI*0.5f, 99.9f, 0.0f, 3.0f);
        m_camera->StartOver(CAM_OVER_EFFECT_FADEOUT_BLACK, m_pos, 1.0f);
        m_speed = 1.0f/10.0f;
        return true;
    }

    if ( m_type == PT_SHOTT ||
         m_type == PT_SHOTM )
    {
        m_camera->StartEffect(CAM_EFFECT_SHOT, m_pos, force);
        m_speed = 1.0f/1.0f;
        return true;
    }
    if ( m_type == PT_SHOTH )
    {
        assert(m_object->Implements(ObjectInterfaceType::Controllable));
        if ( m_camera->GetBlood() && dynamic_cast<CControllableObject&>(*m_object).GetSelect() )
        {
            m_camera->StartOver(CAM_OVER_EFFECT_BLOOD, m_pos, force);
        }
        m_speed = 1.0f/0.2f;
        return true;
    }

    if ( m_type == PT_SHOTW )
    {
        m_speed = 1.0f/1.0f;
    }

    if ( m_type == PT_BURNT )
    {
        BurnStart();
    }

    if ( m_type == PT_WPCHECK )
    {
        m_speed = 1.0f/8.0f;
        m_object->SetLock(true);  // object more functional
    }
    if ( m_type == PT_FLCREATE )
    {
        m_speed = 1.0f/2.0f;
    }
    if ( m_type == PT_FLDELETE )
    {
        m_speed = 1.0f/2.0f;
        m_object->SetLock(true);  // object more functional
    }
    if ( m_type == PT_RESET )
    {
        m_speed = 1.0f/2.0f;
        m_resetAngle = m_object->GetRotationY();
    }
    if ( m_type == PT_FINDING )
    {
        float limit = (m_size-1.0f)/4.0f;
        if (limit > 8.0f) limit = 8.0f;
        if (oType == OBJECT_APOLLO2) limit = 2.0f;
        m_speed = 1.0f/limit;
    }
    if ( m_type == PT_SQUASH )
    {
        m_speed = 1.0f/2.0f;
        m_object->SetLock(true);
    }


    if ( m_type == PT_EXPLOT ||
         m_type == PT_EXPLOO ||
         m_type == PT_EXPLOW )
    {
        CreateTriangle(obj, oType, 0);
        m_engine->DeleteShadowSpot(m_object->GetObjectRank(0));
        ExploStart();
    }

    if ( m_type == PT_FALL )
    {
        FallStart();
        return true;
    }

    if ( m_type == PT_BURNT ||
         m_type == PT_BURNO )
    {
        m_speed = 1.0f/15.0f;

        LightOperAdd(0.00f, 0.0f,  2.0f,  1.0f,  0.0f);  // red-orange
        LightOperAdd(0.30f, 1.0f, -0.8f, -0.8f, -0.8f);  // dark gray
        LightOperAdd(0.80f, 1.0f, -0.8f, -0.8f, -0.8f);  // dark gray
        LightOperAdd(1.00f, 0.0f, -0.8f, -0.8f, -0.8f);  // dark gray
        CreateLight(m_pos, 40.0f);
        return true;
    }

    if ( m_type == PT_SPIDER )
    {
        m_speed = 1.0f/15.0f;

        pos = glm::vec3(-3.0f, 2.0f, 0.0f);
        glm::mat4 mat = obj->GetWorldMatrix(0);
        m_pos = Math::Transform(mat, pos);

        m_engine->DeleteShadowSpot(m_object->GetObjectRank(0));
    }

    if ( m_type != PT_FRAGV &&
         m_type != PT_EGG   &&
         m_type != PT_WIN   &&
         m_type != PT_LOST  &&
         m_type != PT_SQUASH)
    {
        float h = 40.0f;
        if ( m_type == PT_FRAGO  ||
             m_type == PT_EXPLOO )
        {
            LightOperAdd(0.00f, 0.0f, -1.0f, -0.5f, -1.0f);  // dark green
            LightOperAdd(0.05f, 1.0f, -1.0f, -0.5f, -1.0f);  // dark green
            LightOperAdd(1.00f, 0.0f, -1.0f, -0.5f, -1.0f);  // dark green
        }
        else if ( m_type == PT_FRAGT  ||
                  m_type == PT_EXPLOT )
        {
            LightOperAdd(0.00f, 1.0f,  4.0f,  4.0f,  2.0f);  // yellow
            LightOperAdd(0.02f, 1.0f,  4.0f,  2.0f,  0.0f);  // red-orange
            LightOperAdd(0.16f, 1.0f, -0.8f, -0.8f, -0.8f);  // dark gray
            LightOperAdd(1.00f, 0.0f, -0.8f, -0.8f, -0.8f);  // dark gray
            h = m_size*2.0f;
        }
        else if ( m_type == PT_SPIDER )
        {
            LightOperAdd(0.00f, 0.0f, -0.5f, -1.0f, -1.0f);  // dark red
            LightOperAdd(0.05f, 1.0f, -0.5f, -1.0f, -1.0f);  // dark red
            LightOperAdd(1.00f, 0.0f, -0.5f, -1.0f, -1.0f);  // dark red
        }
        else if ( m_type == PT_FRAGW  ||
                  m_type == PT_EXPLOW ||
                  m_type == PT_SHOTW  )
        {
            LightOperAdd(0.00f, 0.0f, -0.5f, -0.5f, -1.0f);  // dark yellow
            LightOperAdd(0.05f, 1.0f, -0.5f, -0.5f, -1.0f);  // dark yellow
            LightOperAdd(1.00f, 0.0f, -0.5f, -0.5f, -1.0f);  // dark yellow
        }
        else if ( m_type == PT_WPCHECK  ||
                  m_type == PT_FLCREATE ||
                  m_type == PT_FLDELETE ||
                  m_type == PT_RESET    ||
                  m_type == PT_FINDING  )
        {
            LightOperAdd(0.00f, 1.0f,  4.0f,  4.0f,  2.0f);  // yellow
            LightOperAdd(1.00f, 0.0f,  4.0f,  4.0f,  2.0f);  // yellow
        }
        else
        {
            LightOperAdd(0.00f, 0.0f, -0.8f, -0.8f, -0.8f);  // dark gray
            LightOperAdd(0.05f, 1.0f, -0.8f, -0.8f, -0.8f);  // dark gray
            LightOperAdd(1.00f, 0.0f, -0.8f, -0.8f, -0.8f);  // dark gray
        }
        CreateLight(m_pos, h);

        if ( m_type != PT_SHOTW    &&
             m_type != PT_WPCHECK  &&
             m_type != PT_FLCREATE &&
             m_type != PT_FLDELETE &&
             m_type != PT_RESET    &&
             m_type != PT_FINDING  &&
             m_type != PT_SQUASH   )
        {
            m_camera->StartEffect(CAM_EFFECT_EXPLO, m_pos, force);
        }
    }

    if ( m_type == PT_SHOTW )  return true;

    // Generates the triangles of the explosion.
    if ( m_type == PT_FRAGT  ||
         m_type == PT_FRAGO  ||
         m_type == PT_FRAGW  ||
         m_type == PT_FRAGV  ||
         m_type == PT_SPIDER ||
         m_type == PT_EGG    ||
        (m_type == PT_EXPLOT && oType == OBJECT_MOBILEtg) ||
        (m_type == PT_EXPLOT && oType == OBJECT_TEEN28  ) ||
        (m_type == PT_EXPLOT && oType == OBJECT_TEEN31  ) )
    {
        for (int part = 0; part < OBJECTMAXPART; part++)
        {
            CreateTriangle(obj, oType, part);
        }
    }

    if ( m_type == PT_FRAGT  ||
         m_type == PT_EXPLOT )
    {
        if ( m_power )
        {
            int total = static_cast<int>(10.0f*m_engine->GetParticleDensity());
            if ( oType == OBJECT_TNT  ||
                 oType == OBJECT_BOMB )  total *= 3;
            for (int i = 0; i < total; i++)
            {
                pos = m_posPower;
                glm::vec3 speed{};
                speed.x = (Math::Rand()-0.5f)*30.0f;
                speed.z = (Math::Rand()-0.5f)*30.0f;
                speed.y = Math::Rand()*30.0f;
                glm::vec2 dim;
                dim.x = 1.0f;
                dim.y = dim.x;
                float duration = Math::Rand()*3.0f+2.0f;
                float mass = Math::Rand()*10.0f+15.0f;
                m_particle->CreateTrack(pos, speed, dim, PARTITRACK1,
                                         duration, mass, Math::Rand()+0.7f, 1.0f);
            }
        }

        if (m_size > 10.0f)  // large enough (freight excluded)?
        {
            if (m_power)
            {
                pos = m_posPower;
            }
            else
            {
                pos = m_pos;
                m_terrain->AdjustToFloor(pos);
                pos.y += 1.0f;
            }
            glm::vec2 dim;
            dim.x = m_size*0.4f;
            dim.y = dim.x;
            m_particle->CreateParticle(pos, glm::vec3(0.0f,0.0f,0.0f), dim, PARTISPHERE0, 2.0f, 0.0f, 0.0f);
        }
    }

    if ( m_type == PT_FRAGO  ||
         m_type == PT_EXPLOO )
    {
        int total = static_cast<int>(10.0f*m_engine->GetParticleDensity());
        for (int i = 0; i < total; i++)
        {
            pos = m_pos;
            glm::vec3 speed{};
            speed.x = (Math::Rand()-0.5f)*30.0f;
            speed.z = (Math::Rand()-0.5f)*30.0f;
            speed.y = Math::Rand()*50.0f;
            glm::vec2 dim;
            dim.x = 1.0f;
            dim.y = dim.x;
            float duration = Math::Rand()*1.0f+0.8f;
            float mass = Math::Rand()*10.0f+15.0f;
            m_particle->CreateParticle(pos, speed, dim, PARTIORGANIC1,
                                         duration, mass);
        }
        total = static_cast<int>(5.0f*m_engine->GetParticleDensity());
        for (int i = 0; i < total; i++)
        {
            pos = m_pos;
            glm::vec3 speed{};
            speed.x = (Math::Rand()-0.5f)*30.0f;
            speed.z = (Math::Rand()-0.5f)*30.0f;
            speed.y = Math::Rand()*50.0f;
            glm::vec2 dim;
            dim.x = 1.0f;
            dim.y = dim.x;
            float duration = Math::Rand()*2.0f+1.4f;
            float mass = Math::Rand()*10.0f+15.0f;
            m_particle->CreateTrack(pos, speed, dim, PARTITRACK4,
                                     duration, mass, duration*0.5f, dim.x*2.0f);
        }
    }

    if ( m_type == PT_SPIDER )
    {
        for (int i = 0; i < 50; i++)
        {
            pos = m_pos;
            pos.x += (Math::Rand()-0.5f)*3.0f;
            pos.z += (Math::Rand()-0.5f)*3.0f;
            pos.y += (Math::Rand()-0.5f)*2.0f;
            glm::vec3 speed{};
            speed.x = (Math::Rand()-0.5f)*24.0f;
            speed.z = (Math::Rand()-0.5f)*24.0f;
            speed.y = 10.0f+Math::Rand()*10.0f;
            glm::vec2 dim;
            dim.x = 1.0f;
            dim.y = dim.x;
            int channel = m_particle->CreateParticle(pos, speed, dim, PARTIGUN3, 2.0f+Math::Rand()*2.0f, 10.0f);
            m_particle->SetObjectFather(channel, obj);
        }
        int total = static_cast<int>(10.0f*m_engine->GetParticleDensity());
        for (int i = 0; i < total; i++)
        {
            pos = m_pos;
            pos.x += (Math::Rand()-0.5f)*3.0f;
            pos.z += (Math::Rand()-0.5f)*3.0f;
            pos.y += (Math::Rand()-0.5f)*2.0f;
            glm::vec3 speed{};
            speed.x = (Math::Rand()-0.5f)*24.0f;
            speed.z = (Math::Rand()-0.5f)*24.0f;
            speed.y = 7.0f+Math::Rand()*7.0f;
            glm::vec2 dim{};
            dim.x = 1.0f;
            dim.y = dim.x;
            m_particle->CreateTrack(pos, speed, dim, PARTITRACK3,
                                    2.0f+Math::Rand()*2.0f, 10.0f, 2.0f, 0.6f);
        }
    }

    if ( type == PT_FRAGT  ||
         type == PT_FRAGW  ||
         type == PT_EXPLOT ||
         type == PT_EXPLOW )
    {
        if (m_size > 10.0f || m_power)
        {
            pos = m_pos;
            glm::vec3 speed(0.0f, 0.0f, 0.0f);
            glm::vec2 dim;
            dim.x = m_size;
            dim.y = dim.x;
            m_particle->CreateParticle(pos, speed, dim, PARTICHOC, 2.0f);
        }
    }

    return true;
}

bool CPyro::EventProcess(const Event &event)
{
    if (event.type != EVENT_FRAME) return true;
    if (m_engine->GetPause()) return true;

    m_time += event.rTime;
    m_progress += event.rTime*m_speed;

    if (m_soundChannel != -1 && m_object != nullptr)
    {
        glm::vec3 pos = m_object->GetPosition();
        m_sound->Position(m_soundChannel, pos);

        if (m_lightRank != -1)
        {
            pos.y += m_lightHeight;
            m_lightMan->SetLightPos(m_lightRank, pos);
        }
    }

    if ( m_type == PT_SHOTT &&
         m_lastParticle+m_engine->ParticleAdapt(0.05f) <= m_time )
    {
        m_lastParticle = m_time;

        if (m_crashSpheres.size() > 0)
        {
            int i = rand() % m_crashSpheres.size();
            glm::vec3 pos = m_crashSpheres[i].pos;
            float radius = m_crashSpheres[i].radius;
            pos.x += (Math::Rand()-0.5f)*radius*2.0f;
            pos.z += (Math::Rand()-0.5f)*radius*2.0f;
            glm::vec3 speed{};
            speed.x = (Math::Rand()-0.5f)*radius*0.5f;
            speed.z = (Math::Rand()-0.5f)*radius*0.5f;
            speed.y = Math::Rand()*radius*1.0f;
            glm::vec2 dim{};
            dim.x = Math::Rand()*radius*0.5f+radius*0.75f*m_force;
            dim.y = dim.x;
            m_particle->CreateParticle(pos, speed, dim, PARTISMOKE1, 3.0f);
        }
        else
        {
            glm::vec3 pos = m_pos;
            pos.x += (Math::Rand()-0.5f)*m_size*0.3f;
            pos.z += (Math::Rand()-0.5f)*m_size*0.3f;
            glm::vec3 speed{};
            speed.x = (Math::Rand()-0.5f)*m_size*0.1f;
            speed.z = (Math::Rand()-0.5f)*m_size*0.1f;
            speed.y = Math::Rand()*m_size*0.2f;
            glm::vec2 dim;
            dim.x = Math::Rand()*m_size/10.0f+m_size/10.0f*m_force;
            dim.y = dim.x;
            m_particle->CreateParticle(pos, speed, dim, PARTISMOKE1, 3.0f);
        }
    }

    if ( m_camera->GetBlood() && m_type == PT_SHOTH &&
         m_lastParticle+m_engine->ParticleAdapt(0.05f) <= m_time )
    {
        m_lastParticle = m_time;

        for (int i = 0; i < 10; i++)
        {
            glm::vec3 pos = m_pos;
            pos.x += (Math::Rand()-0.5f)*m_size*0.2f;
            pos.z += (Math::Rand()-0.5f)*m_size*0.2f;
            pos.y += (Math::Rand()-0.5f)*m_size*0.5f;
            glm::vec3 speed{};
            speed.x = (Math::Rand()-0.5f)*5.0f;
            speed.z = (Math::Rand()-0.5f)*5.0f;
            speed.y = Math::Rand()*1.0f;
            glm::vec2 dim;
            dim.x = 1.0f;
            dim.y = dim.x;
            m_particle->CreateParticle(pos, speed, dim, PARTIBLOOD, Math::Rand()*3.0f+3.0f, Math::Rand()*10.0f+15.0f, 0.5f);
        }
    }

    if ( m_camera->GetBlood() && m_type == PT_SHOTM &&
         m_lastParticle+m_engine->ParticleAdapt(0.05f) <= m_time )
    {
        m_lastParticle = m_time;

        int r = static_cast<int>(10.0f*m_engine->GetParticleDensity());
        for (int i = 0; i < r; i++)
        {
            glm::vec3 pos = m_pos;
            pos.x += (Math::Rand()-0.5f)*20.0f;
            pos.z += (Math::Rand()-0.5f)*20.0f;
            pos.y += 8.0f;
            glm::vec3 speed{};
            speed.x = (Math::Rand()-0.5f)*40.0f;
            speed.z = (Math::Rand()-0.5f)*40.0f;
            speed.y = Math::Rand()*40.0f;
            glm::vec2 dim;
            dim.x = Math::Rand()*8.0f+8.0f*m_force;
            dim.y = dim.x;

            m_particle->CreateParticle(pos, speed, dim, PARTIBLOODM, 2.0f, 50.0f, 0.0f);
        }
    }

    if ( m_type == PT_SHOTW &&
         m_lastParticle+m_engine->ParticleAdapt(0.05f) <= m_time )
    {
        m_lastParticle = m_time;

        if (m_crashSpheres.size() > 0)
        {
            int i = rand() % m_crashSpheres.size();
            glm::vec3 pos = m_crashSpheres[i].pos;
            float radius = m_crashSpheres[i].radius;
            pos.x += (Math::Rand()-0.5f)*radius*2.0f;
            pos.z += (Math::Rand()-0.5f)*radius*2.0f;
            glm::vec3 speed{};
            speed.x = (Math::Rand()-0.5f)*radius*0.5f;
            speed.z = (Math::Rand()-0.5f)*radius*0.5f;
            speed.y = Math::Rand()*radius*1.0f;
            glm::vec2 dim;
            dim.x = 1.0f*m_force;
            dim.y = dim.x;
            m_particle->CreateParticle(pos, speed, dim, PARTIBLITZ, 0.5f, 0.0f, 0.0f);
        }
        else
        {
            glm::vec3 pos = m_pos;
            pos.x += (Math::Rand()-0.5f)*m_size*0.3f;
            pos.z += (Math::Rand()-0.5f)*m_size*0.3f;
            glm::vec3 speed{};
            speed.x = (Math::Rand()-0.5f)*m_size*0.1f;
            speed.z = (Math::Rand()-0.5f)*m_size*0.1f;
            speed.y = Math::Rand()*m_size*0.2f;
            glm::vec2 dim;
            dim.x = 1.0f*m_force;
            dim.y = dim.x;
            m_particle->CreateParticle(pos, speed, dim, PARTIBLITZ, 0.5f, 0.0f, 0.0f);
        }
    }

    if ( m_type == PT_SHOTW &&
         m_lastParticleSmoke+m_engine->ParticleAdapt(0.10f) <= m_time )
    {
        m_lastParticleSmoke = m_time;

        glm::vec3 pos = m_pos;
        pos.y -= 2.0f;
        pos.x += (Math::Rand()-0.5f)*4.0f;
        pos.z += (Math::Rand()-0.5f)*4.0f;
        glm::vec3 speed{};
        speed.x = 0.0f;
        speed.z = 0.0f;
        speed.y = 10.0f+Math::Rand()*10.0f;
        glm::vec2 dim;
        dim.x = Math::Rand()*2.5f+2.0f*m_force;
        dim.y = dim.x;
        m_particle->CreateParticle(pos, speed, dim, PARTICRASH, 4.0f);
    }

    if ( (m_type == PT_FRAGT || m_type == PT_EXPLOT) &&
         m_progress < 0.05f &&
         m_lastParticle+m_engine->ParticleAdapt(0.05f) <= m_time )
    {
        m_lastParticle = m_time;

        glm::vec3 pos = m_pos;
        glm::vec3 speed{};
        speed.x = (Math::Rand()-0.5f)*m_size*1.0f;
        speed.z = (Math::Rand()-0.5f)*m_size*1.0f;
        speed.y = Math::Rand()*m_size*0.50f;
        glm::vec2 dim;
        dim.x = Math::Rand()*m_size/5.0f+m_size/5.0f;
        dim.y = dim.x;

        m_particle->CreateParticle(pos, speed, dim, PARTIEXPLOT);
    }

    if ( (m_type == PT_FRAGT || m_type == PT_EXPLOT) &&
         m_progress < 0.10f &&
         m_lastParticleSmoke+m_engine->ParticleAdapt(0.10f) <= m_time )
    {
        m_lastParticleSmoke = m_time;

        glm::vec2 dim;
        dim.x = Math::Rand()*m_size/3.0f+m_size/3.0f;
        dim.y = dim.x;
        glm::vec3 pos = m_pos;
        pos.x += (Math::Rand()-0.5f)*m_size*0.5f;
        pos.z += (Math::Rand()-0.5f)*m_size*0.5f;
        m_terrain->AdjustToFloor(pos);
        glm::vec3 speed{};
        speed.x = 0.0f;
        speed.z = 0.0f;
        speed.y = -dim.x/2.0f/4.0f;
        pos.y += dim.x/2.0f;

        ParticleType type;
        int r = rand()%2;
        if (r == 0) type = PARTISMOKE1;
        if (r == 1) type = PARTISMOKE2;
        m_particle->CreateParticle(pos, speed, dim, type, 6.0f);
    }

    if ( (m_type == PT_FRAGO || m_type == PT_EXPLOO) &&
         m_progress < 0.03f &&
         m_lastParticle+m_engine->ParticleAdapt(0.1f) <= m_time )
    {
        m_lastParticle = m_time;

        glm::vec3 pos = m_pos;
        glm::vec3 speed{};
        speed.x = (Math::Rand()-0.5f)*m_size*2.0f;
        speed.z = (Math::Rand()-0.5f)*m_size*2.0f;
        speed.y = Math::Rand()*m_size*1.0f;
        glm::vec2 dim;
        dim.x = Math::Rand()*m_size/2.0f+m_size/2.0f;
        dim.y = dim.x;

        m_particle->CreateParticle(pos, speed, dim, PARTIEXPLOO);
    }

    if ( (m_type == PT_FRAGW || m_type == PT_EXPLOW) &&
         m_progress < 0.05f &&
         m_lastParticle+m_engine->ParticleAdapt(0.05f) <= m_time )
    {
        m_lastParticle = m_time;

        glm::vec3 pos = m_pos;
        glm::vec3 speed{};
        speed.x = (Math::Rand()-0.5f)*m_size*1.0f;
        speed.z = (Math::Rand()-0.5f)*m_size*1.0f;
        speed.y = Math::Rand()*m_size*0.50f;
        glm::vec2 dim;
        dim.x = 1.0f;
        dim.y = dim.x;

        m_particle->CreateParticle(pos, speed, dim, PARTIBLITZ, 0.5f, 0.0f, 0.0f);
    }

    if ( (m_type == PT_FRAGW || m_type == PT_EXPLOW) &&
         m_progress < 0.25f &&
         m_lastParticleSmoke+m_engine->ParticleAdapt(0.05f) <= m_time )
    {
        m_lastParticleSmoke = m_time;

        glm::vec3 pos = m_pos;
        pos.y -= 2.0f;
        pos.x += (Math::Rand()-0.5f)*4.0f;
        pos.z += (Math::Rand()-0.5f)*4.0f;
        glm::vec3 speed{};
        speed.x = 0.0f;
        speed.z = 0.0f;
        speed.y = 4.0f+Math::Rand()*4.0f;
        glm::vec2 dim;
        dim.x = Math::Rand()*2.5f+2.0f;
        dim.y = dim.x;
        m_particle->CreateParticle(pos, speed, dim, PARTICRASH, 4.0f);
    }

    if ( m_type == PT_WPCHECK )
    {
        float factor;
        if (m_progress < 0.25f)
            factor = 0.0f;
        else
            factor = powf((m_progress-0.25f)/0.75f, 2.0f)*30.0f;

        if ( m_progress < 0.85f &&
             m_lastParticle+m_engine->ParticleAdapt(0.10f) <= m_time )
        {
            m_lastParticle = m_time;

            glm::vec3 pos = m_pos;
            pos.y += factor;
            pos.x += (Math::Rand()-0.5f)*3.0f;
            pos.z += (Math::Rand()-0.5f)*3.0f;
            glm::vec3 speed;
            speed.x = 0.0f;
            speed.z = 0.0f;
            speed.y = 5.0f+Math::Rand()*5.0f;
            glm::vec2 dim;
            dim.x = Math::Rand()*1.5f+1.5f;
            dim.y = dim.x;
            m_particle->CreateParticle(pos, speed, dim, PARTIGLINT, 2.0f);
        }

        if(m_object != nullptr)
        {
            glm::vec3 angle = m_object->GetRotation();
            angle.y = m_progress*20.0f;
            angle.x = sinf(m_progress*49.0f)*0.3f;
            angle.z = sinf(m_progress*47.0f)*0.2f;
            m_object->SetRotation(angle);

            glm::vec3 pos = m_pos;
            pos.y += factor;
            m_object->SetPosition(pos);

            if ( m_progress > 0.85f )
            {
                m_object->SetScale(1.0f-(m_progress-0.85f)/0.15f);
            }
        }
    }

    if ( m_type == PT_FLCREATE )
    {
        if ( m_lastParticle+m_engine->ParticleAdapt(0.05f) <= m_time )
        {
            m_lastParticle = m_time;

            glm::vec3 pos = m_pos;
            m_terrain->AdjustToFloor(pos);
            pos.x += (Math::Rand()-0.5f)*1.0f;
            pos.z += (Math::Rand()-0.5f)*1.0f;
            glm::vec3 speed;
            speed.x = (Math::Rand()-0.5f)*2.0f;
            speed.z = (Math::Rand()-0.5f)*2.0f;
            speed.y = 2.0f+Math::Rand()*2.0f;
            glm::vec2 dim;
            dim.x = (Math::Rand()*1.0f+1.0f)*(0.2f+m_progress*0.8f);
            dim.y = dim.x;
            m_particle->CreateParticle(pos, speed, dim, PARTIGLINT, 2.0f, 0.0f, 0.0f);
        }

        if(m_object != nullptr)
        {
            glm::vec3 angle = m_object->GetRotation();
            angle.x = sinf(m_progress*49.0f)*0.3f*(1.0f-m_progress);
            angle.z = sinf(m_progress*47.0f)*0.2f*(1.0f-m_progress);
            m_object->SetRotation(angle);

            m_object->SetScale(m_progress);
        }
    }

    if ( m_type == PT_FLDELETE )
    {
        if ( m_lastParticle+m_engine->ParticleAdapt(0.05f) <= m_time )
        {
            m_lastParticle = m_time;

            glm::vec3 pos = m_pos;
            m_terrain->AdjustToFloor(pos);
            pos.x += (Math::Rand()-0.5f)*1.0f;
            pos.z += (Math::Rand()-0.5f)*1.0f;
            glm::vec3 speed;
            speed.x = (Math::Rand()-0.5f)*2.0f;
            speed.z = (Math::Rand()-0.5f)*2.0f;
            speed.y = 2.0f+Math::Rand()*2.0f;
            glm::vec2 dim;
            dim.x = (Math::Rand()*1.0f+1.0f)*(0.2f+m_progress*0.8f);
            dim.y = dim.x;
            m_particle->CreateParticle(pos, speed, dim, PARTIGLINT, 2.0f, 0.0f, 0.5f);
        }

        if(m_object != nullptr)
        {
            glm::vec3 angle = m_object->GetRotation();
            angle.y = m_progress*20.0f;
            angle.x = sinf(m_progress*49.0f)*0.3f;
            angle.z = sinf(m_progress*47.0f)*0.2f;
            m_object->SetRotation(angle);

            m_object->SetScale(1.0f-m_progress);
        }
    }

    if ( m_type == PT_RESET )
    {
        if ( m_lastParticle+m_engine->ParticleAdapt(0.05f) <= m_time )
        {
            m_lastParticle = m_time;

            glm::vec3 pos = m_pos;
            pos.x += (Math::Rand()-0.5f)*5.0f;
            pos.z += (Math::Rand()-0.5f)*5.0f;
            glm::vec3 speed;
            speed.x = 0.0f;
            speed.z = 0.0f;
            speed.y = 5.0f+Math::Rand()*5.0f;
            glm::vec2 dim;
            dim.x = Math::Rand()*2.0f+2.0f;
            dim.y = dim.x;
            m_particle->CreateParticle(pos, speed, dim, PARTIGLINTb, 2.0f);

            pos = m_pos;
            speed.x = (Math::Rand()-0.5f)*20.0f;
            speed.z = (Math::Rand()-0.5f)*20.0f;
            speed.y = Math::Rand()*10.0f;
            speed *= 0.5f+m_progress*0.5f;
            dim.x = 0.6f;
            dim.y = dim.x;
            pos.y += dim.y;
            float duration = Math::Rand()*1.5f+1.5f;
            m_particle->CreateTrack(pos, speed, dim, PARTITRACK6,
                                     duration, 0.0f,
                                     duration*0.9f, 0.7f);
        }

        if(m_object != nullptr)
        {
            float angle = m_resetAngle;
            m_object->SetRotationY(angle-powf((1.0f-m_progress)*5.0f, 2.0f));
            m_object->SetScale(m_progress);
        }
    }

    if ( m_type == PT_FINDING )
    {
        if ( m_object != nullptr &&
             m_lastParticle+m_engine->ParticleAdapt(0.05f) <= m_time )
        {
            m_lastParticle = m_time;

            float factor = m_size*0.3f;
            if (m_object->GetType() == OBJECT_SAFE) factor *= 1.3f;
            if (factor > 40.0f) factor = 40.0f;
            glm::vec3 pos = m_pos;
            m_terrain->AdjustToFloor(pos);
            pos.x += (Math::Rand()-0.5f)*factor;
            pos.z += (Math::Rand()-0.5f)*factor;
            glm::vec3 speed;
            speed.x = (Math::Rand()-0.5f)*2.0f;
            speed.z = (Math::Rand()-0.5f)*2.0f;
            speed.y = 4.0f+Math::Rand()*4.0f;
            glm::vec2 dim;
            dim.x = (Math::Rand()*3.0f+3.0f)*(1.0f-m_progress*0.9f);
            dim.y = dim.x;
            m_particle->CreateParticle(pos, speed, dim, PARTIGLINT, 2.0f, 0.0f, 0.5f);
        }
    }

    if ( m_type == PT_SQUASH && m_object != nullptr )
    {
        m_object->SetScaleY(1.0f-sinf(m_progress)*0.5f);
    }

    if ( (m_type == PT_BURNT || m_type == PT_BURNO) &&
         m_object != nullptr )
    {
        if ( m_lastParticle+m_engine->ParticleAdapt(0.05f) <= m_time )
        {
            m_lastParticle = m_time;

            float factor = m_size/25.0f;  // 1 = standard size

            glm::vec3 pos = m_object->GetPosition();
            pos.y -= m_object->GetCharacter()->height;
            pos.x += (Math::Rand()-0.5f)*(4.0f+8.0f*m_progress)*factor;
            pos.z += (Math::Rand()-0.5f)*(4.0f+8.0f*m_progress)*factor;
            glm::vec3 speed;
            speed.x = 0.0f;
            speed.z = 0.0f;
            speed.y = 0.0f;
            glm::vec2 dim;
            dim.x = (Math::Rand()*2.5f+1.0f)*factor;
            dim.y = dim.x;
            m_particle->CreateParticle(pos, speed, dim, PARTIFLAME, 2.0f, 0.0f, 0.2f);

            pos = m_object->GetPosition();
            pos.y -= m_object->GetCharacter()->height;
            pos.x += (Math::Rand()-0.5f)*(2.0f+4.0f*m_progress)*factor;
            pos.z += (Math::Rand()-0.5f)*(2.0f+4.0f*m_progress)*factor;
            speed.x = 0.0f;
            speed.z = 0.0f;
            speed.y = (Math::Rand()*5.0f*m_progress+3.0f)*factor;
            dim.x = (Math::Rand()*2.0f+1.0f)*factor;
            dim.y = dim.x;
            m_particle->CreateParticle(pos, speed, dim, PARTIFLAME, 2.0f, 0.0f, 0.2f);

            pos = m_object->GetPosition();
            pos.y -= 2.0f;
            pos.x += (Math::Rand()-0.5f)*5.0f*factor;
            pos.z += (Math::Rand()-0.5f)*5.0f*factor;
            speed.x = 0.0f;
            speed.z = 0.0f;
            speed.y = (6.0f+Math::Rand()*6.0f+m_progress*6.0f)*factor;
            dim.x = (Math::Rand()*1.5f+1.0f+m_progress*3.0f)*factor;
            dim.y = dim.x;
            m_particle->CreateParticle(pos, speed, dim, PARTISMOKE3, 4.0f);
        }

        if ( m_type == PT_BURNT )
        {
            BurnProgress();
        }
        else
        {
            glm::vec3 speed;
            speed.y = 0.0f;
            speed.x = (Math::Rand()-0.5f)*m_progress*1.0f;
            speed.z = (Math::Rand()-0.5f)*m_progress*1.0f;
            if ( m_progress > 0.8f )
            {
                float prog = (m_progress-0.8f)/0.2f;  // 0..1
                speed.y = -prog*6.0f;  // sinks into the ground
                m_object->SetScale(1.0f-prog*0.5f);
            }
            m_object->SetLinVibration(speed);
        }
    }

    if ( m_type == PT_WIN &&
         m_object != nullptr )
    {
        if ( m_lastParticle+m_engine->ParticleAdapt(0.05f) <= m_time )
        {
            m_lastParticle = m_time;

            glm::vec3 pos = m_object->GetPosition();
            pos.y += 1.5f;
            glm::vec3 speed;
            speed.x = (Math::Rand()-0.5f)*10.0f;
            speed.z = (Math::Rand()-0.5f)*10.0f;
            speed.y = 8.0f+Math::Rand()*8.0f;
            glm::vec2 dim;
            dim.x = Math::Rand()*0.2f+0.2f;
            dim.y = dim.x;
            m_particle->CreateTrack(pos, speed, dim,
                                     static_cast<ParticleType>(PARTITRACK7+rand()%4),
                                     3.0f, 20.0f, 1.0f, 0.4f);
        }
    }

    if ( m_type == PT_LOST &&
         m_object != nullptr )
    {
        if ( m_lastParticle+m_engine->ParticleAdapt(0.10f) <= m_time )
        {
            m_lastParticle = m_time;

            glm::vec3 pos = m_object->GetPosition();
            pos.y -= 2.0f;
            pos.x += (Math::Rand()-0.5f)*10.0f;
            pos.z += (Math::Rand()-0.5f)*10.0f;
            glm::vec3 speed;
            speed.x = 0.0f;
            speed.z = 0.0f;
            speed.y = 1.0f+Math::Rand()*1.0f;
            glm::vec2 dim;
            dim.x = Math::Rand()*1.0f+1.0f;
            dim.y = dim.x;
            m_particle->CreateParticle(pos, speed, dim, PARTISMOKE1, 8.0f, 0.0f, 0.0f);
        }
    }

    if (m_type == PT_FALL)
        FallProgress(event.rTime);

    if (m_lightRank != -1)
        LightOperFrame(event.rTime);

    return true;
}

Error CPyro::IsEnded()
{
    // Destroys the object that exploded.
    //It should not be destroyed at the end of the Create,
    //because it is sometimes the object itself that makes the Create:
    //  pyro->Create(PT_FRAGT, this);
    if ( m_type == PT_FRAGT  ||
         m_type == PT_FRAGO  ||
         m_type == PT_FRAGW  ||
         m_type == PT_FRAGV  ||
         m_type == PT_SPIDER ||
         m_type == PT_EGG    )
    {
        DeleteObject(true, true);
    }

    if ( m_type == PT_FALL )  // freight which grave?
    {
        return FallIsEnded();
    }

    if ( m_type == PT_WIN  ||
         m_type == PT_LOST )
    {
        return ERR_CONTINUE;
    }

    // End of the pyrotechnic effect?
    if ( m_progress < 1.0f )  return ERR_CONTINUE;

    if ( m_type == PT_EXPLOT ||
         m_type == PT_EXPLOO ||
         m_type == PT_EXPLOW )  // explosion?
    {
        ExploTerminate();
    }

    if ( m_type == PT_BURNT ||
         m_type == PT_BURNO )  // burning?
    {
        BurnTerminate();
    }

    if ( m_type == PT_WPCHECK  ||
         m_type == PT_FLDELETE )
    {
        DeleteObject(true, true);
    }

    if ( m_type == PT_FLCREATE )
    {
        m_object->SetRotationX(0.0f);
        m_object->SetRotationZ(0.0f);
        m_object->SetScale(1.0f);
    }

    if ( m_type == PT_RESET )
    {
        m_object->SetRotationY(m_resetAngle);
        m_object->SetScale(1.0f);
    }

    if ( m_type == PT_SQUASH )
    {
        m_object->SetType(OBJECT_PLANT19);
    }

    if ( m_lightRank != -1 )
    {
        m_lightMan->DeleteLight(m_lightRank);
        m_lightRank = -1;
    }

    return ERR_STOP;
}

void CPyro::CutObjectLink(CObject* obj)
{
    if (m_object == obj)
        m_object = nullptr;
}

void CPyro::DisplayError(PyroType type, CObject* obj)
{
    if ( type == PT_FRAGT  ||
         type == PT_FRAGO  ||
         type == PT_FRAGW  ||
         type == PT_EXPLOT ||
         type == PT_EXPLOO ||
         type == PT_EXPLOW ||
         type == PT_BURNT  ||
         type == PT_BURNO  )
    {
        m_main->DisplayText(GetObjectDestroyableDetails(obj).message, obj, Ui::TT_INFO, 5.0f);
    }
}

void CPyro::CreateLight(glm::vec3 pos, float height)
{
    if (!m_engine->GetLightMode()) return;

    m_lightHeight = height;

    Gfx::Light light;
    light.type        = LIGHT_SPOT;
    light.ambient     = Gfx::Color(0.0f, 0.0f, 0.0f);
    light.position    = glm::vec3(pos.x, pos.y+height, pos.z);
    light.direction   = glm::vec3(0.0f, -1.0f, 0.0f);  // against the bottom
    light.spotIntensity = 1.0f;
    light.attenuation0 = 1.0f;
    light.attenuation1 = 0.0f;
    light.attenuation2 = 0.0f;
    light.spotAngle = Math::PI/4.0f;

    m_lightRank = m_lightMan->CreateLight();

    m_lightMan->SetLight(m_lightRank, light);
    m_lightMan->SetLightIntensity(m_lightRank, 0.0f);

    // Only illuminates the objects on the ground.
    m_lightMan->SetLightIncludeType(m_lightRank, ENG_OBJTYPE_TERRAIN);
}

void CPyro::DeleteObject(bool primary, bool secondary)
{
    if (m_object == nullptr) return;

    ObjectType type = m_object->GetType();
    if ( secondary              &&
         type != OBJECT_FACTORY &&
         type != OBJECT_NUCLEAR &&
         type != OBJECT_ENERGY )
    {
        for (int slot = GetNumSlots(m_object) - 1; slot >= 0; slot--)
        {
            CObjectManager::GetInstancePointer()->DeleteObjectInSlot(m_object, slot);
        }
    }

    if (primary)
    {
        // TODO: this should be handled in the object's destructor
        if (CObject* transporter = GetObjectTransporter(m_object))
        {
            assert(transporter->Implements(ObjectInterfaceType::Slotted));
            for (int slotNum = GetNumSlots(transporter) - 1; slotNum >= 0; slotNum--)
            {
                if (GetObjectInSlot(transporter, slotNum) == m_object)
                {
                    CObjectManager::GetInstancePointer()->DeleteObjectInSlot(transporter, slotNum);
                    m_object = nullptr;
                    return;
                }
            }
        }

        CObjectManager::GetInstancePointer()->DeleteObject(m_object);
        m_object = nullptr;
    }
}

void CPyro::CreateTriangle(CObject* obj, ObjectType oType, int part)
{
    int objRank = obj->GetObjectRank(part);
    if (objRank == -1) return;


    int total = m_engine->GetObjectTotalTriangles(objRank);

    float percent = 0.10f;
    if (total < 50) percent = 0.25f;
    if (total < 20) percent = 0.50f;

    if ( m_type == PT_FRAGV || m_type == PT_EGG )
    {
        percent = 0.30f;
    }

    if (oType == OBJECT_POWER    ||
        oType == OBJECT_ATOMIC   ||
        oType == OBJECT_URANIUM  ||
        oType == OBJECT_TNT      ||
        oType == OBJECT_BOMB     ||
        oType == OBJECT_TEEN28)
    {
        percent = 0.75f;
    }
    else if (oType == OBJECT_MOBILEtg)
    {
        percent = 0.50f;
    }

    std::vector<EngineTriangle> buffer;
    total = m_engine->GetPartialTriangles(objRank, percent, 100, buffer);

    for (int i = 0; i < total; i++)
    {
        glm::vec3 p1, p2, p3;

        p1.x = buffer[i].triangle[0].position.x;
        p1.y = buffer[i].triangle[0].position.y;
        p1.z = buffer[i].triangle[0].position.z;
        p2.x = buffer[i].triangle[1].position.x;
        p2.y = buffer[i].triangle[1].position.y;
        p2.z = buffer[i].triangle[1].position.z;
        p3.x = buffer[i].triangle[2].position.x;
        p3.y = buffer[i].triangle[2].position.y;
        p3.z = buffer[i].triangle[2].position.z;

        float h;

        h = glm::distance(p1, p2);
        if ( h > 5.0f )
        {
            p2.x = p1.x+((p2.x-p1.x)*5.0f/h);
            p2.y = p1.y+((p2.y-p1.y)*5.0f/h);
            p2.z = p1.z+((p2.z-p1.z)*5.0f/h);
        }

        h = glm::distance(p2, p3);
        if ( h > 5.0f )
        {
            p3.x = p2.x+((p3.x-p2.x)*5.0f/h);
            p3.y = p2.y+((p3.y-p2.y)*5.0f/h);
            p3.z = p2.z+((p3.z-p2.z)*5.0f/h);
        }

        h = glm::distance(p3, p1);
        if ( h > 5.0f )
        {
            p1.x = p3.x+((p1.x-p3.x)*5.0f/h);
            p1.y = p3.y+((p1.y-p3.y)*5.0f/h);
            p1.z = p3.z+((p1.z-p3.z)*5.0f/h);
        }

        buffer[i].triangle[0].position.x = p1.x;
        buffer[i].triangle[0].position.y = p1.y;
        buffer[i].triangle[0].position.z = p1.z;
        buffer[i].triangle[1].position.x = p2.x;
        buffer[i].triangle[1].position.y = p2.y;
        buffer[i].triangle[1].position.z = p2.z;
        buffer[i].triangle[2].position.x = p3.x;
        buffer[i].triangle[2].position.y = p3.y;
        buffer[i].triangle[2].position.z = p3.z;

        glm::vec3 offset;
        offset.x = (buffer[i].triangle[0].position.x+buffer[i].triangle[1].position.x+buffer[i].triangle[2].position.x)/3.0f;
        offset.y = (buffer[i].triangle[0].position.y+buffer[i].triangle[1].position.y+buffer[i].triangle[2].position.y)/3.0f;
        offset.z = (buffer[i].triangle[0].position.z+buffer[i].triangle[1].position.z+buffer[i].triangle[2].position.z)/3.0f;

        buffer[i].triangle[0].position.x -= offset.x;
        buffer[i].triangle[1].position.x -= offset.x;
        buffer[i].triangle[2].position.x -= offset.x;

        buffer[i].triangle[0].position.y -= offset.y;
        buffer[i].triangle[1].position.y -= offset.y;
        buffer[i].triangle[2].position.y -= offset.y;

        buffer[i].triangle[0].position.z -= offset.z;
        buffer[i].triangle[1].position.z -= offset.z;
        buffer[i].triangle[2].position.z -= offset.z;

        glm::vec3 speed;
        float mass;

        glm::mat4 mat = obj->GetWorldMatrix(part);
        glm::vec3 pos = Math::Transform(mat, offset);
        if ( m_type == PT_FRAGV || m_type == PT_EGG )
        {
            speed.x = (Math::Rand()-0.5f)*10.0f;
            speed.z = (Math::Rand()-0.5f)*10.0f;
            speed.y = Math::Rand()*15.0f;
            mass = Math::Rand()*20.0f+20.0f;
        }
        else if ( m_type == PT_SPIDER )
        {
            speed.x = (Math::Rand()-0.5f)*10.0f;
            speed.z = (Math::Rand()-0.5f)*10.0f;
            speed.y = Math::Rand()*20.0f;
            mass = Math::Rand()*10.0f+15.0f;
        }
        else
        {
            speed.x = (Math::Rand()-0.5f)*30.0f;
            speed.z = (Math::Rand()-0.5f)*30.0f;
            speed.y = Math::Rand()*30.0f;
            mass = Math::Rand()*10.0f+15.0f;
        }
        if ( oType == OBJECT_STONE   )  speed *= 0.5f;
        if ( oType == OBJECT_URANIUM )  speed *= 0.4f;
        float duration = Math::Rand()*3.0f+3.0f;
        m_particle->CreateFrag(pos, speed, &buffer[i], PARTIFRAG,
                               duration, mass, 0.5f);
    }
}

void CPyro::ExploStart()
{
    m_burnType = m_object->GetType();

    glm::vec3 oPos = m_object->GetPosition();
    m_burnFall = m_terrain->GetHeightToFloor(oPos, true);

    m_object->Simplify();
    m_object->SetLock(true);  // ruin not usable yet
    assert(m_object->Implements(ObjectInterfaceType::Destroyable));
    dynamic_cast<CDestroyableObject&>(*m_object).SetDying(DeathType::Exploding);  // being destroyed
    m_object->FlatParent();

    if ( m_object->Implements(ObjectInterfaceType::Controllable) && dynamic_cast<CControllableObject&>(*m_object).GetSelect() )
    {
        dynamic_cast<CControllableObject&>(*m_object).SetSelect(false);  // deselects the object
        m_camera->SetType(CAM_TYPE_EXPLO);
        m_main->DeselectAll();
    }
    m_main->RemoveFromSelectionHistory(m_object);

    for (int i = 0; i < OBJECTMAXPART; i++)
    {
        int objRank = m_object->GetObjectRank(i);
        if (objRank == -1) continue;

        // TODO: refactor later to material change
        int oldBaseObjRank = m_engine->GetObjectBaseRank(objRank);
        if (oldBaseObjRank != -1)
        {
            int newBaseObjRank = m_engine->CreateBaseObject();
            m_engine->CopyBaseObject(oldBaseObjRank, newBaseObjRank);
            m_engine->SetObjectBaseRank(objRank, newBaseObjRank);

            m_engine->ChangeSecondTexture(objRank, "dirty04.png");
        }

        // TODO: temporary hack (hopefully)
        assert(m_object->Implements(ObjectInterfaceType::Old));
        glm::vec3 pos = dynamic_cast<COldObject&>(*m_object).GetPartPosition(i);

        glm::vec3 speed;
        float weight;

        if (i == 0)  // main part?
        {
            weight = 0.0f;

            speed.y = -1.0f;
            speed.x = 0.0f;
            speed.z = 0.0f;
        }
        else
        {
            glm::vec3 min, max;
            m_engine->GetObjectBBox(objRank, min, max);
            weight = glm::distance(min, max);  // weight according to size!

            speed.y = 10.0f+Math::Rand()*20.0f;
            speed.x = (Math::Rand()-0.5f)*20.0f;
            speed.z = (Math::Rand()-0.5f)*20.0f;
        }

        int channel = m_particle->CreatePart(pos, speed, PARTIPART, 10.0f, 20.0f, weight, 0.5f);
        if (channel != -1)
            m_object->SetMasterParticle(i, channel);
    }
    m_engine->LoadTexture("textures/dirty04.png");

    DeleteObject(false, true);  // destroys the object transported + the battery
}
void CPyro::ExploTerminate()
{
    DeleteObject(true, false);  // removes the main object
}

void CPyro::BurnStart()
{
    m_burnType = m_object->GetType();

    glm::vec3 oPos = m_object->GetPosition();
    m_burnFall = m_terrain->GetHeightToFloor(oPos, true);

    m_object->Simplify();
    m_object->SetLock(true);  // ruin not usable yet

    if ( m_object->Implements(ObjectInterfaceType::Controllable) && dynamic_cast<CControllableObject&>(*m_object).GetSelect() )
    {
        dynamic_cast<CControllableObject&>(*m_object).SetSelect(false);  // deselects the object
        m_camera->SetType(CAM_TYPE_EXPLO);
        m_main->DeselectAll();
    }
    m_main->RemoveFromSelectionHistory(m_object);

    for (int i = 0; i < OBJECTMAXPART; i++)
    {
        int objRank = m_object->GetObjectRank(i);
        if (objRank == -1) continue;

        // TODO: refactor later to material change
        int oldBaseObjRank = m_engine->GetObjectBaseRank(objRank);
        if (oldBaseObjRank != -1)
        {
            int newBaseObjRank = m_engine->CreateBaseObject();
            m_engine->CopyBaseObject(oldBaseObjRank, newBaseObjRank);
            m_engine->SetObjectBaseRank(objRank, newBaseObjRank);

            m_engine->ChangeSecondTexture(objRank, "dirty04.png");
        }
    }
    m_engine->LoadTexture("textures/dirty04.png");

    m_burnPartTotal = 0;

    glm::vec3 pos, angle;

    auto burningParts = GetObjectDestroyableDetails(m_object).burning.parts;
    for ( auto it : burningParts )
    {
        pos.x = it.position.x + it.posRandom.x * Math::Rand();
        pos.y = it.position.y + it.posRandom.y * Math::Rand();
        pos.z = it.position.z + it.posRandom.z * Math::Rand();
        angle.x = it.angle.x + it.angleRandom.x * Math::Rand();
        angle.y = it.angle.y + it.angleRandom.y * Math::Rand();
        angle.z = it.angle.z + it.angleRandom.z * Math::Rand();

        BurnAddPart(it.partNum, pos, angle);

        if ( it.keep )
            m_burnKeepParts.push_back(it.partNum);
    }
}

void CPyro::BurnAddPart(int part, glm::vec3 pos, glm::vec3 angle)
{
    // TODO: temporary hack (hopefully)
    assert(m_object->Implements(ObjectInterfaceType::Old));
    COldObject* oldObj = dynamic_cast<COldObject*>(m_object);

    int i = m_burnPartTotal;
    m_burnPart[i].part = part;
    m_burnPart[i].initialPos = oldObj->GetPartPosition(part);
    m_burnPart[i].finalPos = m_burnPart[i].initialPos+pos;
    m_burnPart[i].initialAngle = oldObj->GetPartRotation(part);
    m_burnPart[i].finalAngle = m_burnPart[i].initialAngle+angle;

    m_burnPartTotal++;
}

void CPyro::BurnProgress()
{
    if ( m_burnType == OBJECT_TEEN31 )  // basket?
    {
        m_object->SetScaleY(1.0f-m_progress*0.5f);  // slight flattening
    }

    for (int i = 0; i < m_burnPartTotal; i++)
    {
        glm::vec3 pos = m_burnPart[i].initialPos + m_progress*(m_burnPart[i].finalPos-m_burnPart[i].initialPos);
        if ( i == 0 && m_burnFall > 0.0f )
        {
            float h = powf(m_progress, 2.0f)*1000.0f;
            if ( h > m_burnFall )  h = m_burnFall;
            pos.y -= h;
        }

        // TODO: temporary hack (hopefully)
        assert(m_object->Implements(ObjectInterfaceType::Old));
        COldObject* oldObj = dynamic_cast<COldObject*>(m_object);

        oldObj->SetPartPosition(m_burnPart[i].part, pos);

        pos = m_burnPart[i].initialAngle + m_progress*(m_burnPart[i].finalAngle-m_burnPart[i].initialAngle);
        oldObj->SetPartRotation(m_burnPart[i].part, pos);
    }

    // TODO: should this apply to every slot?
    if (CObject* sub = GetObjectInPowerCellSlot(m_object)) // is there a battery?
    {
        sub->SetScaleY(1.0f - m_progress);  // complete flattening
    }
}

bool CPyro::BurnIsKeepPart(int part)
{
    for ( auto it : m_burnKeepParts )
    {
        if (part == it) return true;  // must keep
    }
    return false;  // must destroy
}

void CPyro::BurnTerminate()
{
    if (m_object == nullptr)
        return;

    if (m_type == PT_BURNO)  // organic object is burning?
    {
        DeleteObject(true, true);  // removes the insect
        return;
    }

    for (int i = 1; i < OBJECTMAXPART; i++)
    {
        int objRank = m_object->GetObjectRank(i);
        if (objRank == -1) continue;
        if (BurnIsKeepPart(i)) continue;

        m_object->DeletePart(i);
    }

    DeleteObject(false, true);  // destroys the object transported + the battery

    ObjectType type = GetObjectDestroyableDetails(m_object).burning.ruins;
    m_object->SetType(type); // Ruin or Wreck (recoverable by Recycler)

    dynamic_cast<CDestroyableObject*>(m_object)->SetDying(DeathType::Alive);
    m_object->SetLock(false);
}

void CPyro::FallStart()
{
    m_object->SetLock(true);  // usable

    glm::vec3 pos = m_object->GetPosition();
    m_fallFloor = m_terrain->GetFloorLevel(pos);
    m_fallSpeed = 0.0f;
    m_fallBulletTime = 0.0f;
    m_fallEnding = false;
}

CObject* CPyro::FallSearchBeeExplo()
{
    auto bulletCrashSphere = m_object->GetFirstCrashSphere();

    for (CObject* obj : CObjectManager::GetInstancePointer()->GetAllObjects())
    {
        if (obj == m_object) continue;
        if (obj->GetType() == OBJECT_BEE) continue;
        if ( !obj->Implements(ObjectInterfaceType::Destroyable) )  continue;

        if (IsObjectBeingTransported(obj)) continue;

        glm::vec3 oPos = obj->GetPosition();

        if (obj->Implements(ObjectInterfaceType::Shielder))
        {
            float shieldRadius = dynamic_cast<CShielderObject&>(*obj).GetActiveShieldRadius();
            if ( shieldRadius > 0.0f )
            {
                float distance = glm::distance(oPos, bulletCrashSphere.sphere.pos);
                if (distance <= shieldRadius)
                    return obj;
            }
        }

        if ( obj->GetType() == OBJECT_BASE )
        {
            float distance = glm::distance(oPos, bulletCrashSphere.sphere.pos);
            if (distance < 25.0f)
                return obj;
        }

        // Test the center of the object, which is necessary for objects
        // that have no sphere in the center (station).
        float distance = glm::distance(oPos, bulletCrashSphere.sphere.pos)-4.0f;
        if (distance < 5.0f)
            return obj;

        // Test with all spheres of the object.
        for (const auto& objCrashSphere : obj->GetAllCrashSpheres())
        {
            if (Math::DistanceBetweenSpheres(objCrashSphere.sphere, bulletCrashSphere.sphere) <= 0.0f)
            {
                return obj;
            }
        }
    }

    return nullptr;
}

void CPyro::FallProgress(float rTime)
{
    if (m_object == nullptr) return;

    m_fallSpeed += rTime*50.0f;  // v2 = v1 + a*dt
    glm::vec3 pos;
    pos = m_object->GetPosition();
    pos.y -= m_fallSpeed*rTime;  // dd -= v2*dt

    bool floor = false;

    if (pos.y <= m_fallFloor)  // below the ground level?
    {
        pos.y = m_fallFloor;
        floor = true;
    }
    m_object->SetPosition(pos);

    if (m_object->GetType() == OBJECT_BULLET)
    {
        m_fallBulletTime += rTime;

        if (m_fallBulletTime > 0.2f || floor)
        {
            m_fallBulletTime = 0.0f;

            CObject* obj = FallSearchBeeExplo();
            if (obj == nullptr)
            {
                if (floor)  // reaches the ground?
                {
                    assert(m_object->Implements(ObjectInterfaceType::Destroyable));
                    // TODO: implement "killer"?
                    dynamic_cast<CDestroyableObject&>(*m_object).DestroyObject(DestructionType::Explosion);
                }
            }
            else
            {
                if (obj->Implements(ObjectInterfaceType::Shielder) && dynamic_cast<CShielderObject&>(*obj).GetActiveShieldRadius() > 0.0f)  // protected by shield?
                {
                    m_particle->CreateParticle(pos, glm::vec3(0.0f, 0.0f, 0.0f),
                                               { 6.0f, 6.0f }, PARTIGUNDEL, 2.0f, 0.0f, 0.0f);
                    m_sound->Play(SOUND_GUNDEL);

                    DeleteObject(true, true);  // removes the ball
                }
                else
                {
                    assert(obj->Implements(ObjectInterfaceType::Damageable));
                    if (dynamic_cast<CDamageableObject&>(*obj).DamageObject(DamageType::FallingObject))
                    {
                        DeleteObject(true, true);  // removes the ball
                    }
                    else
                    {
                        assert(m_object->Implements(ObjectInterfaceType::Destroyable));
                        // TODO: implement "killer"?
                        dynamic_cast<CDestroyableObject&>(*m_object).DestroyObject(DestructionType::Explosion);
                    }
                }
            }

            if (floor || obj != nullptr)
            {
                m_fallEnding = true;
            }
        }
    }
}

Error CPyro::FallIsEnded()
{
    if (m_fallEnding || m_object == nullptr) return ERR_STOP;

    glm::vec3 pos = m_object->GetPosition();
    if (pos.y > m_fallFloor) return ERR_CONTINUE;

    m_sound->Play(SOUND_BOUM, pos);
    m_object->SetLock(false);  // usable again

    return ERR_STOP;
}

void CPyro::LightOperFlush()
{
    m_lightOper.clear();
}

void CPyro::LightOperAdd(float progress, float intensity, float r, float g, float b)
{
    PyroLightOper lightOper;

    lightOper.progress  = progress;
    lightOper.intensity = intensity;
    lightOper.color.r   = r;
    lightOper.color.g   = g;
    lightOper.color.b   = b;

    m_lightOper.push_back(lightOper);
}

void CPyro::LightOperFrame(float rTime)
{
    for (std::size_t i = 1; i < m_lightOper.size(); i++)
    {
        if ( m_progress < m_lightOper[i].progress )
        {
            float progress = (m_progress-m_lightOper[i-1].progress) / (m_lightOper[i].progress-m_lightOper[i-1].progress);

            float intensity = m_lightOper[i-1].intensity + (m_lightOper[i].intensity-m_lightOper[i-1].intensity)*progress;
            Gfx::Color color;
            color.r = m_lightOper[i-1].color.r + (m_lightOper[i].color.r-m_lightOper[i-1].color.r)*progress;
            color.g = m_lightOper[i-1].color.g + (m_lightOper[i].color.g-m_lightOper[i-1].color.g)*progress;
            color.b = m_lightOper[i-1].color.b + (m_lightOper[i].color.b-m_lightOper[i-1].color.b)*progress;

            m_lightMan->SetLightIntensity(m_lightRank, intensity);
            m_lightMan->SetLightColor(m_lightRank, color);
            break;
        }
    }
}


} // namespace Gfx
