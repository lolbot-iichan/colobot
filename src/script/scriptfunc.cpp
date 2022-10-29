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

#include "script/scriptfunc.h"

#include "CBot/CBot.h"

#include "app/app.h"

#include "common/global.h"
#include "common/logger.h"

#include "common/resources/inputstream.h"
#include "common/resources/outputstream.h"
#include "common/resources/resourcemanager.h"

#include "graphics/engine/engine.h"
#include "graphics/engine/terrain.h"
#include "graphics/engine/water.h"

#include "level/robotmain.h"

#include "level/parser/parser.h"
#include "level/parser/path_inject.h"

#include "math/all.h"

#include "object/object.h"
#include "object/object_details.h"
#include "object/object_manager.h"
#include "object/old_object.h"

#include "object/auto/auto.h"
#include "object/auto/autobase.h"
#include "object/auto/autofactory.h"

#include "object/details/details_provider.h"
#include "object/details/global_details.h"
#include "object/details/trace_drawing_details.h"

#include "object/helpers/cargo_helpers.h"
#include "object/helpers/programmable_helpers.h"

#include "object/interface/destroyable_object.h"
#include "object/interface/exchange_post_object.h"
#include "object/interface/programmable_object.h"
#include "object/interface/shielder_object.h"
#include "object/interface/task_executor_object.h"
#include "object/interface/thumpable_object.h"
#include "object/interface/trace_drawing_object.h"

#include "object/task/taskinfo.h"

#include "physics/physics.h"

#include "script/cbottoken.h"
#include "script/script.h"

#include "sound/sound.h"

#include "ui/displaytext.h"

#include <cmath>

using namespace CBot;

template<class T> inline T PopSimple(CBot::CBotVar* &var, T def, T(*getter)(CBot::CBotVar* &var))
{
    T result = def;
    if ( var != nullptr )
    {
        result = getter(var);
        var = var->GetNext();
    }
    return result;
}

inline int PopType(CBot::CBotVar* &var, int def=CBot::CBotTypMAX)
{
    return PopSimple<int>(var, def, [](CBot::CBotVar* &var){return static_cast<int>(var->GetType());});
}

inline int PopValInt(CBot::CBotVar* &var, int def=0)
{
    return PopSimple<int>(var, def, [](CBot::CBotVar* &var){return var->GetValInt();});
}

inline float PopValFloat(CBot::CBotVar* &var, float def=0.0f)
{
    return PopSimple<float>(var, def, [](CBot::CBotVar* &var){return var->GetValFloat();});
}

inline std::string PopValString(CBot::CBotVar* &var, std::string def="")
{
    return PopSimple<std::string>(var, def, [](CBot::CBotVar* &var){return var->GetValString();});
}

inline CObject* PopValObject(CBot::CBotVar* &var, CObject* def=nullptr)
{
    return PopSimple<CObject*>(var, def, [](CBot::CBotVar* &var){return static_cast<CObject*>(var->GetUserPtr());});
}

inline glm::vec3 PopValPoint(CBot::CBotVar* &var, glm::vec3 def = {0,0,0})
{
    glm::vec3 result = def;
    if ( var != nullptr )
    {
        if ( var->GetType() <= CBot::CBotTypDouble )
        {
            result.x = PopValFloat(var)*g_unit;
            result.y = 0.0f;
            result.z = PopValFloat(var)*g_unit;
        }
        else
        {
            CBot::CBotVar *pX = var->GetItem("x");
            CBot::CBotVar *pY = var->GetItem("y");
            CBot::CBotVar *pZ = var->GetItem("z");
            var = var->GetNext();

            result.x = PopValFloat(pX)*g_unit;
            result.y = PopValFloat(pZ)*g_unit;  // attention y -> z !
            result.z = PopValFloat(pY)*g_unit;  // attention y -> z !
        }
    }
    return result;
}

inline std::vector<ObjectType> PopValObjectList(CBot::CBotVar* &var)
{
    std::vector<int> tmp;
    std::vector<ObjectType> result;

    if ( var != nullptr )
    {
        if ( var->GetType() == CBot::CBotTypArrayPointer )
        {
            CBot::CBotVar* array = var->GetItemList();
            var = var->GetNext();
            while ( array != nullptr )
                tmp.push_back( PopValInt(array) );
        }
        else
            tmp.push_back( PopValInt(var) );
    }

    for ( int type : tmp )
    {
        ObjectType t = static_cast<ObjectType>(type);
        result.push_back(t);
        for (auto it: GetObjectScriptingDetails(t).findableByRadar)
            result.push_back(it.value);
    }

    return result;
}

// Compile a parameter of type "point".

inline CBot::CBotTypResult cPoint(CBot::CBotVar* &var, void* user)
{
    if ( var == nullptr )  return CBot::CBotTypResult(CBot::CBotErrLowParam);

    if ( var->GetType() <= CBot::CBotTypDouble )
    {
        if ( PopType(var) > CBot::CBotTypDouble )  return CBot::CBotTypResult(CBot::CBotErrBadNum);
        if ( var == nullptr )  return CBot::CBotTypResult(CBot::CBotErrLowParam);
        if ( PopType(var) > CBot::CBotTypDouble )  return CBot::CBotTypResult(CBot::CBotErrBadNum);
        return CBot::CBotTypResult(0);
    }

    if ( var->GetType() == CBot::CBotTypClass )
    {
        if ( !var->IsElemOfClass("point") )  return CBot::CBotTypResult(CBot::CBotErrBadParam);
        var = var->GetNext();
        return CBot::CBotTypResult(0);
    }

    return CBot::CBotTypResult(CBot::CBotErrBadParam);
}

// Compile a parameter of type "object or an array of objects".

inline CBot::CBotTypResult cObjectList(CBot::CBotVar* &var)
{
    if ( var == nullptr )  return CBot::CBotTypResult(CBot::CBotErrLowParam);

    if ( var->GetType() <= CBot::CBotTypDouble )
    {
        if ( PopType(var) > CBot::CBotTypDouble )  return CBot::CBotTypResult(CBot::CBotErrBadNum);
        return CBot::CBotTypResult(0);
    }

    if ( var->GetType() == CBot::CBotTypArrayPointer )
    {
        CBot::CBotTypResult type = var->GetTypResult().GetTypElem();
        if ( type.GetType() > CBot::CBotTypDouble )  return CBot::CBotTypResult(CBot::CBotErrBadParam);  // type
        return CBot::CBotTypResult(0);
    }

    return CBot::CBotTypResult(CBot::CBotErrBadNum);
}

// Compiling a procedure with a single "point".

CBotTypResult CScriptFunctions::cOnePoint(CBotVar* &var, void* user)
{
    CBotTypResult   ret;

    ret = cPoint(var, user); if ( ret.GetType() != 0 )  return ret;
    if ( var == nullptr )  return CBotTypResult(CBotTypFloat);
    return CBotTypResult(CBotErrOverParam);
}

// Compilation of the instruction "endmission(result, delay)"

CBotTypResult CScriptFunctions::cEndMission(CBotVar* &var, void* user)
{
    if ( var == nullptr )  return CBotTypResult(CBotErrLowParam);
    if ( PopType(var) > CBotTypDouble )  return CBotTypResult(CBotErrBadNum);
    if ( var == nullptr )  return CBotTypResult(CBotErrLowParam);
    if ( PopType(var) > CBotTypDouble )  return CBotTypResult(CBotErrBadNum);
    if ( var == nullptr )  return CBotTypResult(CBotTypFloat);
    return CBotTypResult(CBotErrOverParam);
}

// Instruction "endmission(result, delay)"

bool CScriptFunctions::rEndMission(CBotVar* var, CBotVar* result, int& exception, void* user)
{
    CScript*    script = static_cast<CScript*>(user);
    CObject*    pThis = script->m_object;
    Error       err = ERR_WRONG_BOT;

    if ( IsFunctionAllowed(pThis, FUNCTION_endmission) )
    {
        Error ended = static_cast<Error>(PopValInt(var));
        float delay = PopValFloat(var);
    
        script->m_main->SetMissionResultFromScript(ended, delay);
        err = ERR_OK;
    }

    return ReturnErr(err, script, result, exception);
}

// Compilation of the instruction "playmusic(filename, repeat)"

CBotTypResult CScriptFunctions::cPlayMusic(CBotVar* &var, void* user)
{
    if ( var == nullptr )  return CBotTypResult(CBotErrLowParam);
    if ( PopType(var) != CBotTypString )  return CBotTypResult(CBotErrBadString);
    if ( var == nullptr )  return CBotTypResult(CBotErrLowParam);
    if ( PopType(var) > CBotTypDouble )  return CBotTypResult(CBotErrBadNum);
    if ( var == nullptr )  return CBotTypResult(CBotTypFloat);
    return CBotTypResult(CBotErrOverParam);
}

// Instruction "playmusic(filename, repeat)"

bool CScriptFunctions::rPlayMusic(CBotVar* var, CBotVar* result, int& exception, void* user)
{
    CScript*    script = static_cast<CScript*>(user);
    CObject*    pThis = script->m_object;
    Error       err = ERR_WRONG_BOT;

    if ( IsFunctionAllowed(pThis, FUNCTION_playmusic) )
    {
        std::string filename = PopValString(var);
        bool repeat = PopValInt(var);
    
        CApplication::GetInstancePointer()->GetSound()->StopMusic();
        CApplication::GetInstancePointer()->GetSound()->PlayMusic(filename, repeat);
        err = ERR_OK;
    }

    return ReturnErr(err, script, result, exception);
}

// Instruction "stopmusic()"

bool CScriptFunctions::rStopMusic(CBotVar* var, CBotVar* result, int& exception, void* user)
{
    CScript*    script = static_cast<CScript*>(user);
    CObject*    pThis = script->m_object;
    Error       err = ERR_WRONG_BOT;

    if ( IsFunctionAllowed(pThis, FUNCTION_stopmusic) )
    {
        CApplication::GetInstancePointer()->GetSound()->StopMusic();
        err = ERR_OK;
    }

    return ReturnErr(err, script, result, exception);
}

// Instruction "getbuild()"

bool CScriptFunctions::rGetBuild(CBotVar* var, CBotVar* result, int& exception, void* user)
{
    CScript*    script = static_cast<CScript*>(user);
    CObject*    pThis = script->m_object;
    Error       err = ERR_WRONG_BOT;
    int         ret = 0;

    if ( IsFunctionAllowed(pThis, FUNCTION_getbuild) )
    {
        ret = script->m_main->GetEnableBuild();
        err = ERR_OK;
    }

    return ReturnInt(ret, err, script, result, exception);
}

// Instruction "getresearchenable()"

bool CScriptFunctions::rGetResearchEnable(CBotVar* var, CBotVar* result, int& exception, void* user)
{
    CScript*    script = static_cast<CScript*>(user);
    CObject*    pThis = script->m_object;
    Error       err = ERR_WRONG_BOT;
    int         ret = 0;

    if ( IsFunctionAllowed(pThis, FUNCTION_getresearchenable) )
    {
        ret = script->m_main->GetEnableResearch();
        err = ERR_OK;
    }

    return ReturnInt(ret, err, script, result, exception);
}

// Instruction "getresearchdone()"

bool CScriptFunctions::rGetResearchDone(CBotVar* var, CBotVar* result, int& exception, void* user)
{
    CScript*    script = static_cast<CScript*>(user);
    CObject*    pThis = script->m_object;
    Error       err = ERR_WRONG_BOT;
    int         ret = 0;

    if ( IsFunctionAllowed(pThis, FUNCTION_getresearchdone) )
    {
        ret = script->m_main->GetDoneResearch(pThis->GetTeam());
        err = ERR_OK;
    }

    return ReturnInt(ret, err, script, result, exception);
}

// Instruction "setbuild(mask)"

bool CScriptFunctions::rSetBuild(CBotVar* var, CBotVar* result, int& exception, void* user)
{
    CScript*    script = static_cast<CScript*>(user);
    CObject*    pThis = script->m_object;
    Error       err = ERR_WRONG_BOT;

    if ( IsFunctionAllowed(pThis, FUNCTION_setbuild) )
    {
        int mask = PopValInt(var);

        script->m_main->SetEnableBuild(mask);
        CApplication::GetInstancePointer()->GetEventQueue()->AddEvent(Event(EVENT_UPDINTERFACE));
        err = ERR_OK;
    }

    return ReturnErr(err, script, result, exception);
}

// Instruction "setresearchenable()"

bool CScriptFunctions::rSetResearchEnable(CBotVar* var, CBotVar* result, int& exception, void* user)
{
    CScript*    script = static_cast<CScript*>(user);
    CObject*    pThis = script->m_object;
    Error       err = ERR_WRONG_BOT;

    if ( IsFunctionAllowed(pThis, FUNCTION_setresearchenable) )
    {
        int mask = PopValInt(var);

        script->m_main->SetEnableResearch(mask);
        CApplication::GetInstancePointer()->GetEventQueue()->AddEvent(Event(EVENT_UPDINTERFACE));
        err = ERR_OK;
    }

    return ReturnErr(err, script, result, exception);
}

// Instruction "setresearchdone()"

bool CScriptFunctions::rSetResearchDone(CBotVar* var, CBotVar* result, int& exception, void* user)
{
    CScript*    script = static_cast<CScript*>(user);
    CObject*    pThis = script->m_object;
    Error       err = ERR_WRONG_BOT;

    if ( IsFunctionAllowed(pThis, FUNCTION_setresearchdone) )
    {
        int mask = PopValInt(var);

        script->m_main->SetDoneResearch(mask, pThis->GetTeam());
        CApplication::GetInstancePointer()->GetEventQueue()->AddEvent(Event(EVENT_UPDINTERFACE));
        err = ERR_OK;
    }

    return ReturnErr(err, script, result, exception);
}

// Compilation of the instruction "retobject(rank)".

CBotTypResult CScriptFunctions::cGetObject(CBotVar* &var, void* user)
{
    if ( var == nullptr )  return CBotTypResult(CBotErrLowParam);
    if ( PopType(var) > CBotTypDouble )  return CBotTypResult(CBotErrBadNum);
    if ( var == nullptr )  return CBotTypResult(CBotTypPointer, "object");
    return CBotTypResult(CBotErrOverParam);
}

// Instruction "retobjectbyid(rank)".

bool CScriptFunctions::rGetObjectById(CBotVar* var, CBotVar* result, int& exception, void* user)
{
    CScript*    script = static_cast<CScript*>(user);
    CObject*    pThis = script->m_object;
    Error       err = ERR_WRONG_BOT;
    CObject*    ret = nullptr;

    if ( IsFunctionAllowed(pThis, FUNCTION_retobjectbyid) )
    {
        int id = PopValInt(var);

        ret = CObjectManager::GetInstancePointer()->GetObjectById(id);
        err = ERR_OK;
    }

    return ReturnPointer(ret, err, script, result, exception);
}

// Instruction "retobject(rank)".

bool CScriptFunctions::rGetObject(CBotVar* var, CBotVar* result, int& exception, void* user)
{
    CScript*    script = static_cast<CScript*>(user);
    CObject*    pThis = script->m_object;
    Error       err = ERR_WRONG_BOT;
    CObject*    ret = nullptr;

    if ( IsFunctionAllowed(pThis, FUNCTION_retobject) )
    {
        int rank = PopValInt(var);

        ret = CObjectManager::GetInstancePointer()->GetObjectByRank(rank);
        err = ERR_OK;
    }

    return ReturnPointer(ret, err, script, result, exception);
}

// Compilation of instruction "isbusy( object )"

CBotTypResult CScriptFunctions::cIsBusy(CBot::CBotVar* &var, void* user)
{
    if ( var == nullptr )  return CBotTypResult(CBotErrLowParam);
    return CBotTypResult(CBotTypBoolean);
}

// Instruction "isbusy( object )"

bool CScriptFunctions::rIsBusy(CBotVar* var, CBotVar* result, int& exception, void* user)
{
    CScript*    script = static_cast<CScript*>(user);
    CObject*    pThis = script->m_object;
    Error       err = ERR_WRONG_BOT;
    int         ret = 0;

    if ( IsFunctionAllowed(pThis, FUNCTION_isbusy) )
    {
        CObject* obj = PopValObject(var);

        if (obj == nullptr || GetObjectAutomatedDetails(obj).autoClass == AUTO_CLASS_NONE || obj->GetAuto() == nullptr ) // TODO: use an interface
            err = ERR_WRONG_OBJ;
        else if ( pThis->GetTeam() != obj->GetTeam() && obj->GetTeam() != 0 )
            err = ERR_ENEMY_OBJECT;
        else
        {
            ret = obj->GetAuto()->GetBusy();
            err = ERR_OK;
        }
    }

    return ReturnInt(ret, err, script, result, exception);
}

// Instruction "destroy( object )"

bool CScriptFunctions::rDestroy(CBotVar* var, CBotVar* result, int& exception, void* user)
{
    CScript*    script = static_cast<CScript*>(user);
    CObject*    pThis = script->m_object;
    Error       err = ERR_WRONG_BOT;

    if ( IsFunctionAllowed(pThis, FUNCTION_destroy) )
    {
        CObject* obj = PopValObject(var);

        if (obj == nullptr)
        {
            ObjectType  fType = GetObjectGlobalDetails().defaults.destroyPerformer;
            obj = CObjectManager::GetInstancePointer()->FindNearest(pThis, fType);
        }

        if (obj == nullptr || GetObjectAutomatedDetails(obj).autoClass != AUTO_CLASS_DESTROYER || obj->GetAuto() == nullptr )
            err = ERR_WRONG_OBJ;
        else if ( pThis->GetTeam() != obj->GetTeam() && obj->GetTeam() != 0 )
            err = ERR_ENEMY_OBJECT;
        else
            err = obj->GetAuto()->StartAction(0);
    }

    return ReturnErr(err, script, result, exception);
}

// Compilation of instruction "factory(cat[, program , object])"

CBotTypResult CScriptFunctions::cFactory(CBotVar* &var, void* user)
{
    if ( var == nullptr )  return CBotTypResult(CBotErrLowParam);
    if ( PopType(var) > CBotTypDouble )  return CBotTypResult(CBotErrBadNum);
    if ( var == nullptr )  return CBotTypResult(CBotTypFloat);
    if ( PopType(var) != CBotTypString )  return CBotTypResult(CBotErrBadString);
    if ( var == nullptr )  return CBotTypResult(CBotTypFloat);
    if ( PopType(var) != CBotTypPointer )  return CBotTypResult(CBotErrBadParam);
    if ( var == nullptr )  return CBotTypResult(CBotTypFloat);
    return CBotTypResult(CBotErrOverParam);
}

// Instruction "factory(cat[, program , object])"

bool CScriptFunctions::rFactory(CBotVar* var, CBotVar* result, int& exception, void* user)
{
    CScript*    script = static_cast<CScript*>(user);
    CObject*    pThis = script->m_object;
    Error       err = ERR_WRONG_BOT;

    if ( IsFunctionAllowed(pThis, FUNCTION_factory) )
    {
        ObjectType  type    = static_cast<ObjectType>(PopValInt(var));
        std::string program = PopValString(var);
        CObject*    obj     = PopValObject(var);

        if (obj == nullptr)
        {
            ObjectType  fType = GetObjectGlobalDetails().defaults.factoryPerformer;
            obj = CObjectManager::GetInstancePointer()->FindNearest(pThis, fType);
        }

        if (obj == nullptr || GetObjectAutomatedDetails(obj).autoClass != AUTO_CLASS_FACTORY || obj->GetAuto() == nullptr )
            err = ERR_WRONG_OBJ;
        else if ( pThis->GetTeam() != obj->GetTeam() && obj->GetTeam() != 0 )
            err = ERR_ENEMY_OBJECT;
        else
            err = obj->GetAuto()->StartAction(type);

        if ( err == ERR_OK )
        {
            static_cast<CAutoFactory*>(obj->GetAuto())->SetProgram(program);
        }
    }

    return ReturnErr(err, script, result, exception);
}

// Compilation of instruction "research(type[, object])"

CBotTypResult CScriptFunctions::cResearch(CBotVar* &var, void* user)
{
    if ( var == nullptr )  return CBotTypResult(CBotErrLowParam);
    if ( PopType(var) > CBotTypDouble )  return CBotTypResult(CBotErrBadNum);
    if ( var == nullptr )  return CBotTypResult(CBotTypFloat);
    if ( PopType(var) != CBotTypPointer )  return CBotTypResult(CBotErrBadParam);
    if ( var == nullptr )  return CBotTypResult(CBotTypFloat);
    return CBotTypResult(CBotErrOverParam);
}
// Instruction "research(type[, object])"

bool CScriptFunctions::rResearch(CBotVar* var, CBotVar* result, int& exception, void* user)
{
    CScript*    script = static_cast<CScript*>(user);
    CObject*    pThis = script->m_object;
    Error       err = ERR_WRONG_BOT;

    if ( IsFunctionAllowed(pThis, FUNCTION_research) )
    {
        ResearchType type = static_cast<ResearchType>(PopValInt(var));
        CObject* obj = PopValObject(var);

        if (obj == nullptr)
        {
            ObjectType  fType = GetObjectDetails()->GetFunctionResearchPerformerObject(type);
            obj = CObjectManager::GetInstancePointer()->FindNearest(pThis, fType);
        }

        if (obj == nullptr || ( GetObjectAutomatedDetails(obj).autoClass != AUTO_CLASS_LABO    &&
                                GetObjectAutomatedDetails(obj).autoClass != AUTO_CLASS_RESEARCH ) || obj->GetAuto() == nullptr )
            err = ERR_WRONG_OBJ;
        else if ( pThis->GetTeam() != obj->GetTeam() && obj->GetTeam() != 0 )
            err = ERR_ENEMY_OBJECT;
        else
            err = obj->GetAuto()->StartAction(type);
    }

    return ReturnErr(err, script, result, exception);
}

// Instruction "takeoff(object)"

bool CScriptFunctions::rTakeOff(CBotVar* var, CBotVar* result, int& exception, void* user)
{
    CScript*    script = static_cast<CScript*>(user);
    CObject*    pThis = script->m_object;
    Error       err = ERR_WRONG_BOT;

    if ( IsFunctionAllowed(pThis, FUNCTION_takeoff) )
    {
        CObject* obj = PopValObject(var);
        if (obj == nullptr)
        {
            ObjectType  fType = GetObjectGlobalDetails().defaults.takeoffPerformer;
            obj = CObjectManager::GetInstancePointer()->FindNearest(pThis, fType);
        }

        if (obj == nullptr || GetObjectAutomatedDetails(obj).autoClass != AUTO_CLASS_BASE || obj->GetAuto() == nullptr )
            err = ERR_WRONG_OBJ;
        else if ( pThis->GetTeam() != obj->GetTeam() && obj->GetTeam() != 0 )
            err = ERR_ENEMY_OBJECT;
        else
            err = obj->GetAuto()->StartAction(0);
    }

    return ReturnErr(err, script, result, exception);
}

// Compilation of the instruction "delete(rank[, exploType])".

CBotTypResult CScriptFunctions::cDelete(CBotVar* &var, void* user)
{
    if ( var == nullptr )  return CBotTypResult(CBotErrLowParam);
    if ( PopType(var) > CBotTypDouble )  return CBotTypResult(CBotErrBadNum);
    if ( var == nullptr )  return CBotTypResult(CBotTypFloat);
    if ( PopType(var) > CBotTypDouble )  return CBotTypResult(CBotErrBadNum);
    if ( var == nullptr )  return CBotTypResult(CBotTypFloat);
    return CBotTypResult(CBotErrOverParam);
}

// Instruction "delete(rank[, exploType])".

bool CScriptFunctions::rDelete(CBotVar* var, CBotVar* result, int& exception, void* user)
{
    CScript*    script = static_cast<CScript*>(user);
    CObject*    pThis = script->m_object;

    if ( !IsFunctionAllowed(pThis, FUNCTION_DELETE) )
        return ReturnErr(ERR_WRONG_BOT, script, result, exception);

    int rank = PopValInt(var);
    DestructionType exploType = static_cast<DestructionType>(PopValInt(var, int(DestructionType::Explosion)));

    CObject* obj = CObjectManager::GetInstancePointer()->GetObjectById(rank);
    if ( obj == nullptr || (obj->Implements(ObjectInterfaceType::Old) && dynamic_cast<COldObject&>(*obj).IsDying()) )
    {
        return ReturnErr(ERR_OK, script, result, exception);
    }

    bool deleteSelf = (obj == pThis);

    if ( exploType != DestructionType::NoEffect && obj->Implements(ObjectInterfaceType::Destroyable) )
    {
        dynamic_cast<CDestroyableObject&>(*obj).DestroyObject(static_cast<DestructionType>(exploType));
    }
    else
    {
        for (int slotNum = GetNumSlots(obj) - 1; slotNum >= 0; slotNum--)
        {
            CObjectManager::GetInstancePointer()->DeleteObjectInSlot(obj, slotNum);
        }
        CObjectManager::GetInstancePointer()->DeleteObject(obj);
    }
    // Returning "false" here makes sure the program doesn't try to keep executing
    // if the robot just destroyed itself using delete(this.id)
    // See issue #925
    return !deleteSelf ? ReturnErr(ERR_OK, script, result, exception) : false;
}

static CBotTypResult compileSearch(CBotVar* &var, void* user, CBotTypResult returnValue)
{
    CBotTypResult ret;

    if ( var == nullptr )  return CBotTypResult(CBotErrLowParam);
    ret = cObjectList(var);  if ( ret.GetType() != 0 ) return ret;             // type
    if ( var == nullptr )  return returnValue;
    ret = cPoint(var, user); if ( ret.GetType() != 0 ) return ret;             // pos
    if ( var == nullptr )  return returnValue;
    if ( PopType(var) > CBotTypDouble )  return CBotTypResult(CBotErrBadNum);  // min
    if ( var == nullptr )  return returnValue;
    if ( PopType(var) > CBotTypDouble )  return CBotTypResult(CBotErrBadNum);  // max
    if ( var == nullptr )  return returnValue;
    if ( PopType(var) > CBotTypDouble )  return CBotTypResult(CBotErrBadNum);  // sense
    if ( var == nullptr )  return returnValue;
    if ( PopType(var) > CBotTypDouble )  return CBotTypResult(CBotErrBadNum);  // filter
    if ( var == nullptr )  return returnValue;
    return CBotTypResult(CBotErrOverParam);
}

// Compilation of "search(type, pos, min, max, sens, filter)".

CBotTypResult CScriptFunctions::cSearch(CBotVar* &var, void* user)
{
    return compileSearch(var, user, CBotTypResult(CBotTypPointer, "object"));
}

CBotTypResult CScriptFunctions::cSearchAll(CBotVar* &var, void* user)
{
    return compileSearch(var, user, CBotTypResult(CBotTypArrayPointer, CBotTypResult(CBotTypPointer, "object")));
}

bool CScriptFunctions::rSearch(CBotVar* var, CBotVar* result, int& exception, void* user)
{
    CScript*    script = static_cast<CScript*>(user);
    CObject*    pThis = script->m_object;
    Error       err = ERR_WRONG_BOT;
    CObject*    ret = nullptr;

    if ( IsFunctionAllowed(pThis, FUNCTION_searchall) )
    {
        std::vector<ObjectType> types = PopValObjectList(var);
        glm::vec3 pos = PopValPoint(var, pThis->GetPosition());
        float min     = PopValFloat(var, 0.0f*g_unit);
        float max     = PopValFloat(var, 1000.0f*g_unit);
        float sens    = PopValFloat(var, 1.0f);
        RadarFilter filter = static_cast<RadarFilter>(PopValInt(var, FILTER_NONE));

        ret = CObjectManager::GetInstancePointer()->Radar(pThis, pos, 0.0f, types, 0.0f, Math::PI*2.0f, min, max, sens < 0, filter, true);
        err = ERR_OK;
    }

    return ReturnPointer(ret, err, script, result, exception);
}

bool CScriptFunctions::rSearchAll(CBotVar* var, CBotVar* result, int& exception, void* user)
{
    CScript*    script = static_cast<CScript*>(user);
    CObject*    pThis = script->m_object;
    Error       err = ERR_WRONG_BOT;
    std::vector<CObject*> ret;

    if ( IsFunctionAllowed(pThis, FUNCTION_searchall) )
    {
        std::vector<ObjectType> types = PopValObjectList(var);
        glm::vec3 pos = PopValPoint(var, pThis->GetPosition());
        float min     = PopValFloat(var, 0.0f*g_unit);
        float max     = PopValFloat(var, 1000.0f*g_unit);
        float sens    = PopValFloat(var, 1.0f);
        RadarFilter filter = static_cast<RadarFilter>(PopValInt(var, FILTER_NONE));

        ret = CObjectManager::GetInstancePointer()->RadarAll(pThis, pos, 0.0f, types, 0.0f, Math::PI*2.0f, min, max, sens < 0, filter, true);
        err = ERR_OK;
    }

    return ReturnPointerList(ret, err, script, result, exception);
}


static CBotTypResult compileRadar(CBotVar* &var, void* user, CBotTypResult returnValue)
{
    CBotTypResult   ret;

    if ( var == nullptr )  return returnValue;
    ret = cObjectList(var);  if ( ret.GetType() != 0 ) return ret;             // type
    if ( var == nullptr )  return returnValue;
    if ( PopType(var) > CBotTypDouble )  return CBotTypResult(CBotErrBadNum);  // angle
    if ( var == nullptr )  return returnValue;
    if ( PopType(var) > CBotTypDouble )  return CBotTypResult(CBotErrBadNum);  // focus
    if ( var == nullptr )  return returnValue;
    if ( PopType(var) > CBotTypDouble )  return CBotTypResult(CBotErrBadNum);  // min
    if ( var == nullptr )  return returnValue;
    if ( PopType(var) > CBotTypDouble )  return CBotTypResult(CBotErrBadNum);  // max
    if ( var == nullptr )  return returnValue;
    if ( PopType(var) > CBotTypDouble )  return CBotTypResult(CBotErrBadNum);  // sense
    if ( var == nullptr )  return returnValue;
    if ( PopType(var) > CBotTypDouble )  return CBotTypResult(CBotErrBadNum);  // filter
    if ( var == nullptr )  return returnValue;
    return CBotTypResult(CBotErrOverParam);
}

CBotTypResult CScriptFunctions::cRadarAll(CBotVar* &var, void* user)
{
    return compileRadar(var, user, CBotTypResult(CBotTypArrayPointer, CBotTypResult(CBotTypPointer, "object")));
}

// Compilation of instruction "radar(type, angle, focus, min, max, sens)".

CBotTypResult CScriptFunctions::cRadar(CBotVar* &var, void* user)
{
    return compileRadar(var, user, CBotTypResult(CBotTypPointer, "object"));
}

// Instruction "radar(type, angle, focus, min, max, sens, filter)".

bool CScriptFunctions::rRadar(CBotVar* var, CBotVar* result, int& exception, void* user)
{
    CScript*    script = static_cast<CScript*>(user);
    CObject*    pThis = script->m_object;
    Error       err = ERR_WRONG_BOT;
    CObject*    ret = nullptr;

    if ( IsFunctionAllowed(pThis, FUNCTION_radar) )
    {
        std::vector<ObjectType> types = PopValObjectList(var);
        float angle = -PopValFloat(var)*Math::PI/180.0f;
        float focus = PopValFloat(var, Math::PI*2.0f);
        float min   = PopValFloat(var, 0.0f)*g_unit;
        float max   = PopValFloat(var, 1000.0f)*g_unit;
        float sens  = PopValFloat(var, 1.0f);
        RadarFilter filter = static_cast<RadarFilter>(PopValInt(var, FILTER_NONE));
    
        ret = CObjectManager::GetInstancePointer()->Radar(pThis, types, angle, focus, min, max, sens < 0, filter, true);
        err = ERR_OK;
    }

    return ReturnPointer(ret, err, script, result, exception);
}

// Instruction "radarall(type, angle, focus, min, max, sens, filter)".

bool CScriptFunctions::rRadarAll(CBotVar* var, CBotVar* result, int& exception, void* user)
{
    CScript*    script = static_cast<CScript*>(user);
    CObject*    pThis = script->m_object;
    Error       err = ERR_WRONG_BOT;
    std::vector<CObject*> ret;

    if ( IsFunctionAllowed(pThis, FUNCTION_radarall) )
    {
        std::vector<ObjectType> types = PopValObjectList(var);
        float angle = -PopValFloat(var)*Math::PI/180.0f;
        float focus = PopValFloat(var, Math::PI*2.0f);
        float min   = PopValFloat(var, 0.0f)*g_unit;
        float max   = PopValFloat(var, 1000.0f)*g_unit;
        float sens  = PopValFloat(var, 1.0f);
        RadarFilter filter = static_cast<RadarFilter>(PopValInt(var, FILTER_NONE));
    
        ret = CObjectManager::GetInstancePointer()->RadarAll(pThis, types, angle, focus, min, max, sens < 0, filter, true);
        err = ERR_OK;
    }

    return ReturnPointerList(ret, err, script, result, exception);
}


// Monitoring a task.

bool CScriptFunctions::WaitForForegroundTask(CScript* script, CBotVar* result, int &exception)
{
    assert(script->m_taskExecutor->IsForegroundTask());
    Error err = script->m_taskExecutor->GetForegroundTask()->IsEnded();
    if ( err != ERR_CONTINUE )  // task terminated?
    {
        script->m_taskExecutor->StopForegroundTask();

        script->m_bContinue = false;

        if ( err == ERR_STOP )  err = ERR_OK;
        result->SetValInt(err);  // indicates the error or ok
        if ( ShouldTaskStop(err, script->m_errMode) )
        {
            exception = err;
            return false;
        }
        return true;  // it's all over
    }

    script->m_bContinue = true;
    return false;  // not done
}

bool CScriptFunctions::WaitForBackgroundTask(CScript* script, CBotVar* result, int &exception)
{
    assert(script->m_taskExecutor->IsBackgroundTask());
    Error err = script->m_taskExecutor->GetBackgroundTask()->IsEnded();
    if ( err != ERR_CONTINUE )  // task terminated?
    {
        script->m_taskExecutor->StopBackgroundTask();

        script->m_bContinue = false;

        if ( err == ERR_STOP )  err = ERR_OK;
        result->SetValInt(err);  // indicates the error or ok
        if ( ShouldTaskStop(err, script->m_errMode) )
        {
            exception = err;
            return false;
        }
        return true;  // it's all over
    }

    script->m_bContinue = true;
    return false;  // not done
}


// Returns true if error code means real error and exception must be thrown

bool CScriptFunctions::ShouldTaskStop(Error err, int errMode)
{
    // aim impossible  - not a real error
    if ( err == ERR_AIM_IMPOSSIBLE )
        return false;

    if ( err != ERR_OK && errMode == ERM_STOP )
        return true;

    return false;
}


// Compilation of the instruction "detect(type)".

CBotTypResult CScriptFunctions::cDetect(CBotVar* &var, void* user)
{
    if ( var == nullptr )  return CBotTypResult(CBotErrLowParam);
    if ( PopType(var) > CBotTypDouble )  return CBotTypResult(CBotErrBadNum);
    if ( var == nullptr )  return CBotTypResult(CBotTypBoolean);
    return CBotTypResult(CBotErrOverParam);
}

// Instruction "detect(type)".

bool CScriptFunctions::rDetect(CBotVar* var, CBotVar* result, int& exception, void* user)
{
    CScript*    script = static_cast<CScript*>(user);
    CObject*    pThis = script->m_object;
    Error       err = ERR_WRONG_BOT;
    float       ret = 0;

    if ( IsFunctionAllowed(pThis, FUNCTION_detect) )
    {
        if ( !script->m_taskExecutor->IsForegroundTask() )  // no task in progress?
        {
            std::vector<ObjectType> types = PopValObjectList(var);
    
            CObject* pBest = CObjectManager::GetInstancePointer()->Radar(pThis, types, 0.0f, 45.0f*Math::PI/180.0f, 0.0f, 20.0f, false, FILTER_NONE, true);
    
            if (pThis->Implements(ObjectInterfaceType::Old))
            {
                script->m_main->StartDetectEffect(dynamic_cast<COldObject*>(pThis), pBest);
            }
    
            script->m_returnValue = (pBest != nullptr) ? 1.0f : 0.0f;
    
            err = script->m_taskExecutor->StartTaskWait(0.3f);
            if ( err != ERR_OK )
            {
                script->m_taskExecutor->StopForegroundTask();
                return ReturnFloat(ret, err, script, result, exception);
            }
        }
        if ( !WaitForForegroundTask(script, result, exception) )  return false;  // not finished
        ret = *script->m_returnValue;
    }

    return ReturnFloat(ret, err, script, result, exception);
}


// Compilation of the instruction "direction(pos)".

CBotTypResult CScriptFunctions::cDirection(CBotVar* &var, void* user)
{
    CBotTypResult   ret;

    if ( var == nullptr )  return CBotTypResult(CBotErrLowParam);
    ret = cPoint(var, user); if ( ret.GetType() != 0 )  return ret;
    if ( var == nullptr )  return CBotTypResult(CBotTypFloat);
    return CBotTypResult(CBotErrOverParam);
}

// Instruction "direction(pos)".

bool CScriptFunctions::rDirection(CBotVar* var, CBotVar* result, int& exception, void* user)
{
    CScript*    script = static_cast<CScript*>(user);
    CObject*    pThis = script->m_object;
    Error       err = ERR_WRONG_BOT;
    float       ret = 0.0f;

    if ( IsFunctionAllowed(pThis, FUNCTION_direction) )
    {
        glm::vec3 oPos = PopValPoint(var);
    
        glm::vec3 iPos = pThis->GetPosition();
        float a = pThis->GetRotationY();
        float g = Math::RotateAngle(oPos.x-iPos.x, iPos.z-oPos.z);  // CW !
    
        ret = -Math::Direction(a, g)*180.0f/Math::PI;
        err = ERR_OK;
    }

    return ReturnFloat(ret, err, script, result, exception);
}

// Instruction "canbuild ( category );"
// returns true if this building can be built

bool CScriptFunctions::rCanBuild(CBotVar* var, CBotVar* result, int& exception, void* user)
{
    CScript*    script = static_cast<CScript*>(user);
    CObject*    pThis = script->m_object;
    Error       err = ERR_WRONG_BOT;
    int         ret = 0;

    if ( IsFunctionAllowed(pThis, FUNCTION_canbuild) )
    {
        ObjectType category = static_cast<ObjectType>(PopValInt(var));

        ret = script->m_main->CanBuild(category, pThis->GetTeam());
        err = ERR_OK;
    }

    return ReturnInt(ret, err, script, result, exception);
}

// Instruction "canresearch ( category );"

bool CScriptFunctions::rCanResearch(CBotVar* var, CBotVar* result, int& exception, void* user)
{
    CScript*    script = static_cast<CScript*>(user);
    CObject*    pThis = script->m_object;
    Error       err = ERR_WRONG_BOT;
    int         ret = 0;

    if ( IsFunctionAllowed(pThis, FUNCTION_canresearch) )
    {
        ResearchType research = static_cast<ResearchType>(PopValInt(var));

        ret = script->m_main->IsResearchEnabled(research);
        err = ERR_OK;
    }

    return ReturnInt(ret, err, script, result, exception);
}

// Instruction "researched ( category );"

bool CScriptFunctions::rResearched(CBotVar* var, CBotVar* result, int& exception, void* user)
{
    CScript*    script = static_cast<CScript*>(user);
    CObject*    pThis = script->m_object;
    Error       err = ERR_WRONG_BOT;
    int         ret = 0;

    if ( IsFunctionAllowed(pThis, FUNCTION_researched) )
    {
        ResearchType research = static_cast<ResearchType>(PopValInt(var));

        ret = script->m_main->IsResearchDone(research, pThis->GetTeam());
        err = ERR_OK;
    }

    return ReturnInt(ret, err, script, result, exception);
}

// Instruction "buildingenabled ( category );"

bool CScriptFunctions::rBuildingEnabled(CBotVar* var, CBotVar* result, int& exception, void* user)
{
    CScript*    script = static_cast<CScript*>(user);
    CObject*    pThis = script->m_object;
    Error       err = ERR_WRONG_BOT;
    int         ret = 0;

    if ( IsFunctionAllowed(pThis, FUNCTION_buildingenabled) )
    {
        ObjectType category = static_cast<ObjectType>(PopValInt(var));

        ret = script->m_main->IsBuildingEnabled(category);
        err = ERR_OK;
    }

    return ReturnInt(ret, err, script, result, exception);
}

// Instruction "build(type)"
// draws error if can not build (wher errormode stop), otherwise 0 <- error

bool CScriptFunctions::rBuild(CBotVar* var, CBotVar* result, int& exception, void* user)
{
    CScript*    script = static_cast<CScript*>(user);
    CObject*    pThis = script->m_object;
    Error       err = ERR_WRONG_BOT;

    if ( script->m_taskExecutor->IsForegroundTask() )
        return WaitForForegroundTask(script, result, exception);

    if ( IsFunctionAllowed(pThis, FUNCTION_build) )
    {
        ObjectType category = static_cast<ObjectType>(PopValInt(var));

        err = script->m_taskExecutor->StartTaskBuild(category);
    }

    return ReturnErrOrForegroundTask(err, script, result, exception);
}

// Instruction "flag(color)"

bool CScriptFunctions::rFlag(CBotVar* var, CBotVar* result, int& exception, void* user)
{
    CScript*    script = static_cast<CScript*>(user);
    CObject*    pThis = script->m_object;
    Error       err = ERR_WRONG_BOT;

    if ( script->m_taskExecutor->IsForegroundTask() )
        return WaitForForegroundTask(script, result, exception);

    if ( IsFunctionAllowed(pThis, FUNCTION_flag) )
    {
        int value = PopValInt(var);

        err = script->m_taskExecutor->StartTaskFlag(value);
    }

    return ReturnErrOrForegroundTask(err, script, result, exception);
}

// Instruction "deflag()"

bool CScriptFunctions::rDeflag(CBotVar* var, CBotVar* result, int& exception, void* user)
{
    CScript*    script = static_cast<CScript*>(user);
    CObject*    pThis = script->m_object;
    Error       err = ERR_WRONG_BOT;

    if ( script->m_taskExecutor->IsForegroundTask() )
        return WaitForForegroundTask(script, result, exception);

    if ( IsFunctionAllowed(pThis, FUNCTION_deflag) )
    {
        err = script->m_taskExecutor->StartTaskDeflag();
    }

    return ReturnErrOrForegroundTask(err, script, result, exception);
}

// Compilation of the instruction "produce(pos, angle, type[, scriptName[, power[, team]]])"
// or "produce(type[, power])".

CBotTypResult CScriptFunctions::cProduce(CBotVar* &var, void* user)
{
    CBotTypResult   ret;

    if ( var == nullptr )  return CBotTypResult(CBotErrLowParam);

    if ( var->GetType() <= CBotTypDouble )
    {
        if ( PopType(var) > CBotTypDouble )  return CBotTypResult(CBotErrBadNum);
        if ( var == nullptr ) return CBotTypResult(CBotTypFloat);
        if ( PopType(var) > CBotTypDouble )  return CBotTypResult(CBotErrBadNum);
        if ( var == nullptr )  return CBotTypResult(CBotTypFloat);
        return CBotTypResult(CBotErrOverParam);
    }
    else
    {
        ret = cPoint(var, user); if ( ret.GetType() != 0 )  return ret;
        if ( var == nullptr )  return CBotTypResult(CBotErrLowParam);
        if ( PopType(var) > CBotTypDouble )  return CBotTypResult(CBotErrBadNum);
        if ( var == nullptr )  return CBotTypResult(CBotErrLowParam);
        if ( PopType(var) > CBotTypDouble )  return CBotTypResult(CBotErrBadNum);
        if ( var == nullptr )  return CBotTypResult(CBotTypFloat);
        if ( PopType(var) != CBotTypString )  return CBotTypResult(CBotErrBadString);
        if ( var == nullptr )  return CBotTypResult(CBotTypFloat);
        if ( PopType(var) > CBotTypDouble )  return CBotTypResult(CBotErrBadNum);
        if ( var == nullptr )  return CBotTypResult(CBotTypFloat);
        if ( PopType(var) > CBotTypDouble )  return CBotTypResult(CBotErrBadNum);
        if ( var == nullptr )  return CBotTypResult(CBotTypFloat);
        return CBotTypResult(CBotErrOverParam);
    }
}

// Instruction "produce(pos, angle, type[, scriptName[, power[, team]]])"
// or "produce(type[, power])".

bool CScriptFunctions::rProduce(CBotVar* var, CBotVar* result, int& exception, void* user)
{
    CScript*    script = static_cast<CScript*>(user);
    CObject*    pThis = script->m_object;

    if ( !IsFunctionAllowed(pThis, FUNCTION_produce) )
        return ReturnErr(ERR_WRONG_BOT, script, result, exception);

    std::string name = "";

    ObjectCreateParams params;
    if ( var->GetType() <= CBotTypDouble )
    {
        params.type  = static_cast<ObjectType>(PopValInt(var));
        params.power = PopValFloat(var, -1.0f);

        params.pos   = pThis->GetPosition();
        params.angle = (pThis->GetRotation() + pThis->GetTilt()).y;
    }
    else
    {
        params.pos   = PopValPoint(var);
        params.angle = PopValFloat(var)*Math::PI/180.0f;
        params.type  = static_cast<ObjectType>(PopValInt(var));
        name         = PopValString(var);
        params.power = PopValFloat(var, -1.0f);
        params.team  = PopValInt(var);
    }

    CObject* object = nullptr;

    auto produceDetails = GetObjectScriptingDetails(params.type).produce;
    if (produceDetails.isProducedCharged && params.power == -1.0f)
    {
        params.power = 1.0f;
    }

    if (produceDetails.isProducable)
    {
        object = CObjectManager::GetInstancePointer()->CreateObject(params);
    }
    if (object == nullptr)
    {
        return ReturnErr(ERR_UNKNOWN, script, result, exception);
    }

    if (produceDetails.container != OBJECT_NULL)
    {
        params.type = produceDetails.container;
        CObjectManager::GetInstancePointer()->CreateObject(params);
        if (object->Implements(ObjectInterfaceType::Programmable))
        {
            dynamic_cast<CProgrammableObject&>(*object).SetActivity(false);
        }
    }

    if (produceDetails.isProducedManual)
    {
        assert(object->Implements(ObjectInterfaceType::Old)); // TODO: temporary hack
        dynamic_cast<COldObject&>(*object).SetManual(true);
    }

    script->m_main->CreateShortcuts();

    if (!name.empty())
    {
        std::string name2 = InjectLevelPathsForCurrentLevel(name, "ai");
        if (object->Implements(ObjectInterfaceType::Programmable))
        {
            CProgramStorageObject* programStorage = dynamic_cast<CProgramStorageObject*>(object);
            Program* program = programStorage->AddProgram();
            programStorage->ReadProgram(program, name2.c_str());
            program->readOnly = true;
            program->filename = name;
            dynamic_cast<CProgrammableObject&>(*object).RunProgram(program);
        }
    }

    return ReturnErr(ERR_OK, script, result, exception);
}


// Compilation of the instruction "distance(p1, p2)".

CBotTypResult CScriptFunctions::cDistance(CBotVar* &var, void* user)
{
    CBotTypResult   ret;

    if ( var == nullptr )  return CBotTypResult(CBotErrLowParam);
    ret = cPoint(var, user); if ( ret.GetType() != 0 )  return ret;
    if ( var == nullptr )  return CBotTypResult(CBotErrLowParam);
    ret = cPoint(var, user); if ( ret.GetType() != 0 )  return ret;
    if ( var == nullptr )  return CBotTypResult(CBotTypFloat);
    return CBotTypResult(CBotErrOverParam);
}

// Instruction "distance(p1, p2)".

bool CScriptFunctions::rDistance(CBotVar* var, CBotVar* result, int& exception, void* user)
{
    CScript*    script = static_cast<CScript*>(user);
    CObject*    pThis = script->m_object;
    Error       err = ERR_WRONG_BOT;
    float       ret = 0.0f;

    if ( IsFunctionAllowed(pThis, FUNCTION_distance) )
    {
        glm::vec3 p1 = PopValPoint(var);
        glm::vec3 p2 = PopValPoint(var);
    
        ret = glm::distance(p1, p2)/g_unit;
        err = ERR_OK;
    }

    return ReturnFloat(ret, err, script, result, exception);
}

// Instruction "distance2d(p1, p2)".

bool CScriptFunctions::rDistance2d(CBotVar* var, CBotVar* result, int& exception, void* user)
{
    CScript*    script = static_cast<CScript*>(user);
    CObject*    pThis = script->m_object;
    Error       err = ERR_WRONG_BOT;
    float       ret = 0.0f;

    if ( IsFunctionAllowed(pThis, FUNCTION_distance2d) )
    {
        glm::vec3 p1 = PopValPoint(var);
        glm::vec3 p2 = PopValPoint(var);
    
        ret = Math::DistanceProjected(p1, p2)/g_unit;
        err = ERR_OK;
    }

    return ReturnFloat(ret, err, script, result, exception);
}


// Compilation of the instruction "space(center, rMin, rMax, dist)".

CBotTypResult CScriptFunctions::cSpace(CBotVar* &var, void* user)
{
    CBotTypResult   ret;

    if ( var == nullptr )  return CBotTypResult(CBotTypIntrinsic, "point");
    ret = cPoint(var, user); if ( ret.GetType() != 0 )  return ret;
    if ( var == nullptr )  return CBotTypResult(CBotTypIntrinsic, "point");
    if ( PopType(var) > CBotTypDouble )  return CBotTypResult(CBotErrBadNum);
    if ( var == nullptr )  return CBotTypResult(CBotTypIntrinsic, "point");
    if ( PopType(var) > CBotTypDouble )  return CBotTypResult(CBotErrBadNum);
    if ( var == nullptr )  return CBotTypResult(CBotTypIntrinsic, "point");
    if ( PopType(var) > CBotTypDouble )  return CBotTypResult(CBotErrBadNum);
    if ( var == nullptr )  return CBotTypResult(CBotTypIntrinsic, "point");
    return CBotTypResult(CBotErrOverParam);
}

// Instruction "space(center, rMin, rMax, dist)".

bool CScriptFunctions::rSpace(CBotVar* var, CBotVar* result, int& exception, void* user)
{
    CScript*    script = static_cast<CScript*>(user);
    CObject*    pThis = script->m_object;
    Error       err = ERR_WRONG_BOT;
    glm::vec3   ret = {};

    if ( IsFunctionAllowed(pThis, FUNCTION_space) )
    {
        glm::vec3 center = PopValPoint(var, pThis->GetPosition());
        float     rMin   = PopValFloat(var, 10.0f)*g_unit;
        float     rMax   = PopValFloat(var, 50.0f)*g_unit;
        float     dist   = PopValFloat(var, 4.0f)*g_unit;

        bool success = script->m_main->FreeSpace(center, rMin, rMax, dist, pThis);
        if (success)
            ret = {center.x/g_unit, center.y/g_unit, center.z/g_unit};
        else
            ret = {center.x, center.z, center.y};
        err = ERR_OK;
    }
    return ReturnPoint(ret, err, script, result, exception);
}

CBotTypResult CScriptFunctions::cFlatSpace(CBotVar* &var, void* user)
{
    CBotTypResult   ret;

    if ( var == nullptr )  return CBotTypResult(CBotErrLowParam);
    ret = cPoint(var, user); if ( ret.GetType() != 0 )  return ret;
    if ( var == nullptr )  return CBotTypResult(CBotErrLowParam);
    if ( PopType(var) > CBotTypDouble )  return CBotTypResult(CBotErrBadNum);
    if ( var == nullptr )  return CBotTypResult(CBotTypIntrinsic, "point");
    if ( PopType(var) > CBotTypDouble )  return CBotTypResult(CBotErrBadNum);
    if ( var == nullptr )  return CBotTypResult(CBotTypIntrinsic, "point");
    if ( PopType(var) > CBotTypDouble )  return CBotTypResult(CBotErrBadNum);
    if ( var == nullptr )  return CBotTypResult(CBotTypIntrinsic, "point");
    if ( PopType(var) > CBotTypDouble )  return CBotTypResult(CBotErrBadNum);
    if ( var == nullptr )  return CBotTypResult(CBotTypIntrinsic, "point");
    return CBotTypResult(CBotErrOverParam);
}

// Instruction "flatspace(center, flatMin, rMin, rMax, dist)".

bool CScriptFunctions::rFlatSpace(CBotVar* var, CBotVar* result, int& exception, void* user)
{
    CScript*    script = static_cast<CScript*>(user);
    CObject*    pThis = script->m_object;
    Error       err = ERR_WRONG_BOT;
    glm::vec3   ret = {};

    if ( IsFunctionAllowed(pThis, FUNCTION_flatspace) )
    {
        glm::vec3 center = PopValPoint(var);
        float flatMin = PopValFloat(var)*g_unit;
        float rMin = PopValFloat(var, 10.0f)*g_unit;
        float rMax = PopValFloat(var, 50.0f)*g_unit;
        float dist = PopValFloat(var, 4.0f)*g_unit;

        script->m_main->FlatFreeSpace(center, flatMin, rMin, rMax, dist, pThis);
        ret = {center.x/g_unit, center.y/g_unit, center.z/g_unit};
        err = ERR_OK;
    }

    return ReturnPoint(ret, err, script, result, exception);
}


// Compilation of the instruction "flatground(center, rMax)".

CBotTypResult CScriptFunctions::cFlatGround(CBotVar* &var, void* user)
{
    CBotTypResult   ret;

    if ( var == nullptr )  return CBotTypResult(CBotErrLowParam);
    ret = cPoint(var, user); if ( ret.GetType() != 0 )  return ret;
    if ( var == nullptr )  return CBotTypResult(CBotErrLowParam);
    if ( PopType(var) > CBotTypDouble )  return CBotTypResult(CBotErrBadNum);
    if ( var == nullptr )  return CBotTypResult(CBotTypFloat);
    return CBotTypResult(CBotErrOverParam);
}

// Instruction "flatground(center, rMax)".

bool CScriptFunctions::rFlatGround(CBotVar* var, CBotVar* result, int& exception, void* user)
{
    CScript*    script = static_cast<CScript*>(user);
    CObject*    pThis = script->m_object;
    Error       err = ERR_WRONG_BOT;
    float       ret = 0;

    if ( IsFunctionAllowed(pThis, FUNCTION_flatground) )
    {
        glm::vec3 center = PopValPoint(var);
        float rMax = PopValFloat(var)*g_unit;

        ret = script->m_main->GetFlatZoneRadius(center, rMax, pThis)/g_unit;
        err = ERR_OK;
    }

    return ReturnFloat(ret, err, script, result, exception);
}


// Instruction "wait(time)".

bool CScriptFunctions::rWait(CBotVar* var, CBotVar* result, int& exception, void* user)
{
    CScript*    script = static_cast<CScript*>(user);
    CObject*    pThis = script->m_object;
    Error       err = ERR_WRONG_BOT;

    if ( script->m_taskExecutor->IsForegroundTask() )
        return WaitForForegroundTask(script, result, exception);

    if ( IsFunctionAllowed(pThis, FUNCTION_wait) )
    {
        float value = PopValFloat(var);

        err = script->m_taskExecutor->StartTaskWait(value);
    }

    return ReturnErrOrForegroundTask(err, script, result, exception);
}

// Instruction "move(dist)".

bool CScriptFunctions::rMove(CBotVar* var, CBotVar* result, int& exception, void* user)
{
    CScript*    script = static_cast<CScript*>(user);
    CObject*    pThis = script->m_object;
    Error       err = ERR_WRONG_BOT;

    if ( script->m_taskExecutor->IsForegroundTask() )
        return WaitForForegroundTask(script, result, exception);

    if ( IsFunctionAllowed(pThis, FUNCTION_move) )
    {
        float value = PopValFloat(var)*g_unit;

        err = script->m_taskExecutor->StartTaskAdvance(value);
    }

    return ReturnErrOrForegroundTask(err, script, result, exception);
}

// Instruction "turn(angle)".

bool CScriptFunctions::rTurn(CBotVar* var, CBotVar* result, int& exception, void* user)
{
    CScript*    script = static_cast<CScript*>(user);
    CObject*    pThis = script->m_object;
    Error       err = ERR_WRONG_BOT;

    if ( script->m_taskExecutor->IsForegroundTask() )
        return WaitForForegroundTask(script, result, exception);

    if ( IsFunctionAllowed(pThis, FUNCTION_turn) )
    {
        float value = PopValFloat(var);
        value = -value*Math::PI/180.0f;

        err = script->m_taskExecutor->StartTaskTurn(value);
    }

    return ReturnErrOrForegroundTask(err, script, result, exception);
}

// Compilation of the instruction "goto(pos, altitude, crash, goal)".

CBotTypResult CScriptFunctions::cGoto(CBotVar* &var, void* user)
{
    CBotTypResult   ret;

    if ( var == nullptr )  return CBotTypResult(CBotErrLowParam);
    ret = cPoint(var, user); if ( ret.GetType() != 0 )  return ret;
    if ( var == nullptr )  return CBotTypResult(CBotTypFloat);
    if ( PopType(var) > CBotTypDouble )  return CBotTypResult(CBotErrBadNum);
    if ( var == nullptr )  return CBotTypResult(CBotTypFloat);
    if ( PopType(var) > CBotTypDouble )  return CBotTypResult(CBotErrBadNum);
    if ( var == nullptr )  return CBotTypResult(CBotTypFloat);
    if ( PopType(var) > CBotTypDouble )  return CBotTypResult(CBotErrBadNum);
    if ( var == nullptr )  return CBotTypResult(CBotTypFloat);
    return CBotTypResult(CBotErrOverParam);
}

// Instruction "goto(pos, altitude, mode)".

bool CScriptFunctions::rGoto(CBotVar* var, CBotVar* result, int& exception, void* user)
{
    CScript*    script = static_cast<CScript*>(user);
    CObject*    pThis = script->m_object;
    Error       err = ERR_WRONG_BOT;

    if ( script->m_taskExecutor->IsForegroundTask() )
        return WaitForForegroundTask(script, result, exception);

    if ( IsFunctionAllowed(pThis, FUNCTION_GOTO) )
    {
        glm::vec3 pos = PopValPoint(var);
        float altitude = PopValFloat(var)*g_unit;
        TaskGotoGoal  goal  = static_cast<TaskGotoGoal>(PopValInt(var, TGG_DEFAULT));
        TaskGotoCrash crash = static_cast<TaskGotoCrash>(PopValInt(var, TGC_DEFAULT));

        err = script->m_taskExecutor->StartTaskGoto(pos, altitude, goal, crash);
    }

    return ReturnErrOrForegroundTask(err, script, result, exception);
}

// Compilation "grab/drop(oper)".

CBotTypResult CScriptFunctions::cGrabDrop(CBotVar* &var, void* user)
{
    if ( var == nullptr )  return CBotTypResult(CBotTypFloat);
    if ( PopType(var) > CBotTypDouble )  return CBotTypResult(CBotErrBadNum);
    if ( var == nullptr )  return CBotTypResult(CBotTypFloat);
    return CBotTypResult(CBotErrOverParam);
}

// Instruction "grab(oper)".

bool CScriptFunctions::rGrab(CBotVar* var, CBotVar* result, int& exception, void* user)
{
    CScript*    script = static_cast<CScript*>(user);
    CObject*    pThis = script->m_object;
    Error       err = ERR_WRONG_BOT;

    if ( script->m_taskExecutor->IsForegroundTask() )
        return WaitForForegroundTask(script, result, exception);

    if ( IsFunctionAllowed(pThis, FUNCTION_grabNoParam) )
    {
        err = script->m_taskExecutor->StartTaskTake();
    }
    if ( IsFunctionAllowed(pThis, FUNCTION_grabEnumParam) )
    {
        TaskManipArm type = static_cast<TaskManipArm>(PopValInt(var, TMA_FFRONT));
        err = script->m_taskExecutor->StartTaskManip(TMO_GRAB, type);
    }

    return ReturnErrOrForegroundTask(err, script, result, exception);
}

// Instruction "drop(oper)".

bool CScriptFunctions::rDrop(CBotVar* var, CBotVar* result, int& exception, void* user)
{
    CScript*    script = static_cast<CScript*>(user);
    CObject*    pThis = script->m_object;
    Error       err = ERR_WRONG_BOT;

    if ( script->m_taskExecutor->IsForegroundTask() )
        return WaitForForegroundTask(script, result, exception);

    if ( IsFunctionAllowed(pThis, FUNCTION_dropNoParam) )
    {
        err = script->m_taskExecutor->StartTaskTake();
    }
    if ( IsFunctionAllowed(pThis, FUNCTION_dropEnumParam) )
    {
        TaskManipArm type = static_cast<TaskManipArm>(PopValInt(var, TMA_FFRONT));
        err = script->m_taskExecutor->StartTaskManip(TMO_DROP, type);
    }

    return ReturnErrOrForegroundTask(err, script, result, exception);
}

// Instruction "sniff()".

bool CScriptFunctions::rSniff(CBotVar* var, CBotVar* result, int& exception, void* user)
{
    CScript*    script = static_cast<CScript*>(user);
    CObject*    pThis = script->m_object;
    Error       err = ERR_WRONG_BOT;

    if ( script->m_taskExecutor->IsForegroundTask() )
        return WaitForForegroundTask(script, result, exception);

    if ( IsFunctionAllowed(pThis, FUNCTION_sniff) )
    {
        err = script->m_taskExecutor->StartTaskSearch();
    }

    return ReturnErrOrForegroundTask(err, script, result, exception);
}

// Compilation of the instruction "receive(nom, power)".

CBotTypResult CScriptFunctions::cReceive(CBotVar* &var, void* user)
{
    if ( var == nullptr )  return CBotTypResult(CBotErrLowParam);
    if ( PopType(var) != CBotTypString )  return CBotTypResult(CBotErrBadString);
    if ( var == nullptr )  return CBotTypResult(CBotTypFloat);
    if ( PopType(var) > CBotTypDouble )  return CBotTypResult(CBotErrBadNum);
    if ( var == nullptr )  return CBotTypResult(CBotTypFloat);
    return CBotTypResult(CBotErrOverParam);
}

// Instruction "receive(nom, power)".

bool CScriptFunctions::rReceive(CBotVar* var, CBotVar* result, int& exception, void* user)
{
    CScript*    script = static_cast<CScript*>(user);
    CObject*    pThis = script->m_object;

    if ( !IsFunctionAllowed(pThis, FUNCTION_receive) )
        return ReturnNan(ERR_WRONG_BOT, script, result, exception);

    if ( !script->m_taskExecutor->IsForegroundTask() )  // no task in progress?
    {
        std::string infoName = PopValString(var);
        float power = PopValFloat(var, 10.0f)*g_unit;

        Error err = script->m_taskExecutor->StartTaskInfo(infoName.c_str(), 0.0f, power, false);

        if ( err != ERR_OK )
        {
            script->m_taskExecutor->StopForegroundTask();
            return ReturnNan(err, script, result, exception);
        }

        CExchangePostObject* exchangePost = FindExchangePost(pThis, power);
        script->m_returnValue = exchangePost->GetInfoValue(infoName);
    }
    if ( !WaitForForegroundTask(script, result, exception) )  return false;  // not finished

    if ( script->m_returnValue == boost::none )
    {
        result->SetValFloat(nanf(""));
    }
    else
    {
        result->SetValFloat(*script->m_returnValue);
    }
    return true;
}

// Compilation of the instruction "send(nom, value, power)".

CBotTypResult CScriptFunctions::cSend(CBotVar* &var, void* user)
{
    if ( var == nullptr )  return CBotTypResult(CBotErrLowParam);
    if ( PopType(var) != CBotTypString )  return CBotTypResult(CBotErrBadString);
    if ( var == nullptr )  return CBotTypResult(CBotErrLowParam);
    if ( PopType(var) > CBotTypDouble )  return CBotTypResult(CBotErrBadNum);
    if ( var == nullptr )  return CBotTypResult(CBotTypFloat);
    if ( PopType(var) > CBotTypDouble )  return CBotTypResult(CBotErrBadNum);
    if ( var == nullptr )  return CBotTypResult(CBotTypFloat);
    return CBotTypResult(CBotErrOverParam);
}

// Instruction "send(nom, value, power)".

bool CScriptFunctions::rSend(CBotVar* var, CBotVar* result, int& exception, void* user)
{
    CScript*    script = static_cast<CScript*>(user);
    CObject*    pThis = script->m_object;
    Error       err = ERR_WRONG_BOT;

    if ( script->m_taskExecutor->IsForegroundTask() )
        return WaitForForegroundTask(script, result, exception);

    if ( IsFunctionAllowed(pThis, FUNCTION_send) )
    {
        std::string infoName = PopValString(var);
        float value = PopValFloat(var);
        float power = PopValFloat(var, 10.0f)*g_unit;

        err = script->m_taskExecutor->StartTaskInfo(infoName.c_str(), value, power, true);
    }

    return ReturnErrOrForegroundTask(err, script, result, exception);
}

// Seeks the nearest information terminal.

CExchangePostObject* CScriptFunctions::FindExchangePost(CObject* object, float power)
{
    ObjectType  fType = GetObjectGlobalDetails().defaults.receivePerformer;
    CObject* exchangePost = CObjectManager::GetInstancePointer()->FindNearest(object, fType, power/g_unit);
    return dynamic_cast<CExchangePostObject*>(exchangePost);
}

// Compilation of the instruction "deleteinfo/testinfo(name, power)".

CBotTypResult CScriptFunctions::cDeleteTestInfo(CBotVar* &var, void* user)
{
    if ( var == nullptr )  return CBotTypResult(CBotErrLowParam);
    if ( PopType(var) != CBotTypString )  return CBotTypResult(CBotErrBadString);
    if ( var == nullptr )  return CBotTypResult(CBotTypBoolean);
    if ( PopType(var) > CBotTypDouble )  return CBotTypResult(CBotErrBadNum);
    if ( var == nullptr )  return CBotTypResult(CBotTypBoolean);
    return CBotTypResult(CBotErrOverParam);
}

// Instruction "deleteinfo(name, power)".

bool CScriptFunctions::rDeleteInfo(CBotVar* var, CBotVar* result, int& exception, void* user)
{
    CScript*    script = static_cast<CScript*>(user);
    CObject*    pThis = script->m_object;
    Error       err = ERR_WRONG_BOT;
    int         ret = 0;

    if ( IsFunctionAllowed(pThis, FUNCTION_deleteinfo) )
    {
        std::string infoName = PopValString(var);
        float power = PopValFloat(var, 10.0f)*g_unit;
    
        CExchangePostObject* exchangePost = FindExchangePost(pThis, power);
    
        ret = (exchangePost != nullptr) ? exchangePost->DeleteInfo(infoName) : false;
        err = ERR_OK;
    }

    return ReturnInt(ret, err, script, result, exception);
}

// Instruction "testinfo(name, power)".

bool CScriptFunctions::rTestInfo(CBotVar* var, CBotVar* result, int& exception, void* user)
{
    CScript*    script = static_cast<CScript*>(user);
    CObject*    pThis = script->m_object;
    Error       err = ERR_WRONG_BOT;
    int         ret = 0;

    if ( IsFunctionAllowed(pThis, FUNCTION_testinfo) )
    {
        std::string infoName = PopValString(var);
        float power = PopValFloat(var, 10.0f)*g_unit;
    
        CExchangePostObject* exchangePost = FindExchangePost(pThis, power);
    
        ret = (exchangePost != nullptr) ? exchangePost->HasInfo(infoName) : false;
        err = ERR_OK;
    }

    return ReturnInt(ret, err, script, result, exception);
}

// Instruction "thump()".

bool CScriptFunctions::rThump(CBotVar* var, CBotVar* result, int& exception, void* user)
{
    CScript*    script = static_cast<CScript*>(user);
    CObject*    pThis = script->m_object;
    Error       err = ERR_WRONG_BOT;

    if ( script->m_taskExecutor->IsForegroundTask() )
        return WaitForForegroundTask(script, result, exception);

    if ( IsFunctionAllowed(pThis, FUNCTION_thump) )
    {
        err = script->m_taskExecutor->StartTaskTerraform();
    }

    return ReturnErrOrForegroundTask(err, script, result, exception);
}

// Instruction "recycle()".

bool CScriptFunctions::rRecycle(CBotVar* var, CBotVar* result, int& exception, void* user)
{
    CScript*    script = static_cast<CScript*>(user);
    CObject*    pThis = script->m_object;
    Error       err = ERR_WRONG_BOT;

    if ( script->m_taskExecutor->IsForegroundTask() )
        return WaitForForegroundTask(script, result, exception);

    if ( IsFunctionAllowed(pThis, FUNCTION_recycle) )
    {
        err = script->m_taskExecutor->StartTaskRecover();
    }

    return ReturnErrOrForegroundTask(err, script, result, exception);
}

// Compilation "shield(oper, radius)".

CBotTypResult CScriptFunctions::cShield(CBotVar* &var, void* user)
{
    if ( var == nullptr )  return CBotTypResult(CBotErrLowParam);
    if ( PopType(var) > CBotTypDouble )  return CBotTypResult(CBotErrBadNum);
    if ( var == nullptr )  return CBotTypResult(CBotErrLowParam);
    if ( PopType(var) > CBotTypDouble )  return CBotTypResult(CBotErrBadNum);
    if ( var == nullptr )  return CBotTypResult(CBotTypFloat);
    return CBotTypResult(CBotErrOverParam);
}

// Instruction "shield(oper, radius)".

bool CScriptFunctions::rShield(CBotVar* var, CBotVar* result, int& exception, void* user)
{
    CScript*    script = static_cast<CScript*>(user);
    CObject*    pThis = script->m_object;
    Error       err = ERR_WRONG_BOT;

    if ( IsFunctionAllowed(pThis, FUNCTION_shield) )
    {
        float oper   = PopValFloat(var);  // 0=down, 1=up
        float radius = PopValFloat(var);
        if ( radius < 10.0f )  radius = 10.0f;
        if ( radius > 25.0f )  radius = 25.0f;
        radius = (radius-10.0f)/15.0f;
    
        if ( !script->m_taskExecutor->IsBackgroundTask() )  // shield folds?
        {
            if ( oper == 0.0f ) // down?
            {
                err = ERR_OBJ_BUSY;  // shows the error
            }
            else if ( pThis->Implements(ObjectInterfaceType::Shielder) )
            {
                dynamic_cast<CShielderObject&>(*pThis).SetShieldRadius(radius);
                err = script->m_taskExecutor->StartTaskShield(TSM_UP, 1000.0f);
            }
        }
        else    // shield deployed?
        {
            if ( oper == 0.0f )  // down?
            {
                err = script->m_taskExecutor->StartTaskShield(TSM_DOWN, 0.0f);
            }
            else if ( pThis->Implements(ObjectInterfaceType::Shielder) )
            {
                dynamic_cast<CShielderObject&>(*pThis).SetShieldRadius(radius);
                err = script->m_taskExecutor->StartTaskShield(TSM_UPDATE, 0.0f);
            }
        }
    }

    return ReturnErrOrBackgroundTask(err, script, result, exception);
}

// Compilation "fire(delay)".

CBotTypResult CScriptFunctions::cFire(CBotVar* &var, void* user)
{
    CObject*    pThis = static_cast<CScript*>(user)->m_object;

    if ( IsFunctionAllowed(pThis, FUNCTION_fireNoParam) )
    {
        if ( var == nullptr )  return CBotTypResult(CBotTypFloat);
        return CBotTypResult(CBotErrOverParam);
    }

    if ( IsFunctionAllowed(pThis, FUNCTION_firePointParam) )
    {
        CBotTypResult ret;

        if ( var == nullptr )  return CBotTypResult(CBotErrLowParam);
        ret = cPoint(var, user); if ( ret.GetType() != 0 )  return ret;
        if ( var == nullptr )  return CBotTypResult(CBotTypFloat);
        return CBotTypResult(CBotErrOverParam);
    }

    if ( IsFunctionAllowed(pThis, FUNCTION_fireTimeParam) )
    {
        if ( var != nullptr )
        {
            if ( PopType(var) > CBotTypDouble )  return CBotTypResult(CBotErrBadNum);
            if ( var == nullptr )  return CBotTypResult(CBotTypFloat);
            return CBotTypResult(CBotErrOverParam);
        }
        return CBotTypResult(CBotTypFloat);
    }

    return CBotTypResult(CBotErrNoFunc);
}

// Instruction "fire(delay)".

bool CScriptFunctions::rFire(CBotVar* var, CBotVar* result, int& exception, void* user)
{
    CScript*    script = static_cast<CScript*>(user);
    CObject*    pThis = script->m_object;
    Error       err = ERR_WRONG_BOT;

    if ( script->m_taskExecutor->IsForegroundTask() )
        return WaitForForegroundTask(script, result, exception);

    if ( IsFunctionAllowed(pThis, FUNCTION_fireNoParam) )
    {
        err = script->m_taskExecutor->StartTaskSpiderExplo();
    }
    if ( IsFunctionAllowed(pThis, FUNCTION_firePointParam) )
    {
        glm::vec3 impact = PopValPoint(var);
        float waterLevel = Gfx::CEngine::GetInstancePointer()->GetWater()->GetLevel();
        impact.y += waterLevel;

        err = script->m_taskExecutor->StartTaskFireAnt(impact);
    }
    if ( IsFunctionAllowed(pThis, FUNCTION_fireTimeParam) )
    {
        float delay = fabs(PopValFloat(var));

        err = script->m_taskExecutor->StartTaskFire(delay);
    }

    return ReturnErrOrForegroundTask(err, script, result, exception);
}

// Compilation of the instruction "aim(x, y)".

CBotTypResult CScriptFunctions::cAim(CBotVar* &var, void* user)
{
    if ( var == nullptr )  return CBotTypResult(CBotErrLowParam);
    if ( PopType(var) > CBotTypDouble )  return CBotTypResult(CBotErrBadNum);
    if ( var == nullptr )  return CBotTypResult(CBotTypFloat);
    if ( PopType(var) > CBotTypDouble )  return CBotTypResult(CBotErrBadNum);
    if ( var == nullptr )  return CBotTypResult(CBotTypFloat);
    return CBotTypResult(CBotErrOverParam);
}

// Instruction "aim(dir)".

bool CScriptFunctions::rAim(CBotVar* var, CBotVar* result, int& exception, void* user)
{
    CScript*    script = static_cast<CScript*>(user);
    CObject*    pThis = script->m_object;
    Error       err = ERR_WRONG_BOT;

    if ( script->m_taskExecutor->IsBackgroundTask() )
        return WaitForBackgroundTask(script, result, exception);

    if ( IsFunctionAllowed(pThis, FUNCTION_aim) )
    {
        float x = PopValFloat(var)*Math::PI/180.0f;
        float y = PopValFloat(var)*Math::PI/180.0f;

        err = script->m_taskExecutor->StartTaskGunGoal(x, y);
        if ( err == ERR_AIM_IMPOSSIBLE )
        {
            result->SetValInt(err);  // shows the error
            err = ERR_OK;
        }
    }

    return ReturnErrOrBackgroundTask(err, script, result, exception);
}

// Compilation of the instruction "motor(left, right)".

CBotTypResult CScriptFunctions::cMotor(CBotVar* &var, void* user)
{
    if ( var == nullptr )  return CBotTypResult(CBotErrLowParam);
    if ( PopType(var) > CBotTypDouble )  return CBotTypResult(CBotErrBadNum);
    if ( var == nullptr )  return CBotTypResult(CBotErrLowParam);
    if ( PopType(var) > CBotTypDouble )  return CBotTypResult(CBotErrBadNum);
    if ( var == nullptr )  return CBotTypResult(CBotTypFloat);
    return CBotTypResult(CBotErrOverParam);
}

// Instruction "motor(left, right)".

bool CScriptFunctions::rMotor(CBotVar* var, CBotVar* result, int& exception, void* user)
{
    CScript*    script = static_cast<CScript*>(user);
    CObject*    pThis = script->m_object;
    Error       err = ERR_WRONG_BOT;

    if ( IsFunctionAllowed(pThis, FUNCTION_motor) )
    {
        float left = PopValFloat(var);
        float right = PopValFloat(var);

        float speed = (left+right)/2.0f;
        if ( speed < -1.0f )  speed = -1.0f;
        if ( speed >  1.0f )  speed =  1.0f;

        float turn = left-right;
        if ( turn < -1.0f )  turn = -1.0f;
        if ( turn >  1.0f )  turn =  1.0f;

        // TODO: Why do we set the speed? Maybe should just return an error?
        if (pThis->Implements(ObjectInterfaceType::Thumpable) &&
            dynamic_cast<CThumpableObject*>(pThis)->GetFixed() )
        {
            speed = 0.0f;
            turn  = 0.0f;
        }

        if (pThis->Implements(ObjectInterfaceType::Movable))
        {
            CPhysics* physics = dynamic_cast<CMovableObject*>(pThis)->GetPhysics();
            physics->SetMotorSpeedX(speed);  // forward/backward
            physics->SetMotorSpeedZ(turn);  // turns
            err = ERR_OK;
        }
    }

    return ReturnErr(err, script, result, exception);
}

// Instruction "jet(power)".

bool CScriptFunctions::rJet(CBotVar* var, CBotVar* result, int& exception, void* user)
{
    CScript*    script = static_cast<CScript*>(user);
    CObject*    pThis = script->m_object;
    Error       err = ERR_WRONG_BOT;

    if ( IsFunctionAllowed(pThis, FUNCTION_jet) )
    {
        float value = PopValFloat(var);
        if ( value > 1.0f ) value = 1.0f;

        if (pThis->Implements(ObjectInterfaceType::Movable))
        {
            CPhysics* physics = dynamic_cast<CMovableObject*>(pThis)->GetPhysics();
            physics->SetMotorSpeedY(value);
            err = ERR_OK;
        }
    }

    return ReturnErr(err, script, result, exception);
}

// Compilation of the instruction "topo(pos)".

CBotTypResult CScriptFunctions::cTopo(CBotVar* &var, void* user)
{
    CBotTypResult   ret;

    if ( var == nullptr )  return CBotTypResult(CBotErrLowParam);
    ret = cPoint(var, user); if ( ret.GetType() != 0 )  return ret;
    if ( var == nullptr )  return CBotTypResult(CBotTypFloat);
    return CBotTypResult(CBotErrOverParam);
}

// Instruction "topo(pos)".

bool CScriptFunctions::rTopo(CBotVar* var, CBotVar* result, int& exception, void* user)
{
    CScript*    script = static_cast<CScript*>(user);
    CObject*    pThis = script->m_object;
    Error       err = ERR_WRONG_BOT;
    float       ret = 0.0f;

    if ( IsFunctionAllowed(pThis, FUNCTION_topo) )
    {
        glm::vec3 pos = PopValPoint(var);

        float level = script->m_terrain->GetFloorLevel(pos) - script->m_water->GetLevel();

        ret = level/g_unit;
        err = ERR_OK;
    }

    return ReturnFloat(ret, err, script, result, exception);
}

// Compilation of the instruction "message(string, type)".

CBotTypResult CScriptFunctions::cMessage(CBotVar* &var, void* user)
{
    if ( var == nullptr )  return CBotTypResult(CBotErrLowParam);
    int varType = PopType(var);
    if ( varType != CBotTypString && varType != CBotTypBoolean && varType > CBotTypDouble )  return CBotTypResult(CBotErrBadNum);
    if ( var == nullptr )  return CBotTypResult(CBotTypFloat);
    if ( PopType(var) > CBotTypDouble )  return CBotTypResult(CBotErrBadNum);
    if ( var == nullptr )  return CBotTypResult(CBotTypFloat);
    return CBotTypResult(CBotErrOverParam);
}

// Instruction "message(string, type)".

bool CScriptFunctions::rMessage(CBotVar* var, CBotVar* result, int& exception, void* user)
{
    CScript*    script = static_cast<CScript*>(user);
    CObject*    pThis = script->m_object;
    Error       err = ERR_WRONG_BOT;

    if ( IsFunctionAllowed(pThis, FUNCTION_message) )
    {
        std::string msg = PopValString(var);
        Ui::TextType type = static_cast<Ui::TextType>(PopValInt(var, Ui::TT_MESSAGE));
    
        script->m_main->GetDisplayText()->DisplayText(msg.c_str(), script->m_object, 10.0f, type);
        err = ERR_OK;
    }

    return ReturnErr(err, script, result, exception);
}

// Instruction "cmdline(rank)".

bool CScriptFunctions::rCmdline(CBotVar* var, CBotVar* result, int& exception, void* user)
{
    CScript*    script = static_cast<CScript*>(user);
    CObject*    pThis = script->m_object;
    Error       err = ERR_WRONG_BOT;
    float       ret = 0.0f;

    if ( IsFunctionAllowed(pThis, FUNCTION_cmdline) )
    {
        int rank = PopValInt(var);
        
        if ( pThis->Implements(ObjectInterfaceType::Programmable) )
        {
            ret = dynamic_cast<CProgrammableObject&>(*pThis).GetCmdLine(rank);
            err = ERR_OK;
        }
    }

    return ReturnFloat(ret, err, script, result, exception);
}

// Instruction "ismovie()".

bool CScriptFunctions::rIsMovie(CBotVar* var, CBotVar* result, int& exception, void* user)
{
    CScript*    script = static_cast<CScript*>(user);
    CObject*    pThis = script->m_object;
    Error       err = ERR_WRONG_BOT;
    float       ret = 0.0f;

    if ( IsFunctionAllowed(pThis, FUNCTION_ismovie) )
    {
        ret = script->m_main->GetMovieLock() ? 1.0f : 0.0f;
        err = ERR_OK;
    }

    return ReturnFloat(ret, err, script, result, exception);
}

// Instruction "errmode(mode)".

bool CScriptFunctions::rErrMode(CBotVar* var, CBotVar* result, int& exception, void* user)
{
    CScript*    script = static_cast<CScript*>(user);
    CObject*    pThis = script->m_object;
    Error       err = ERR_WRONG_BOT;

    if ( IsFunctionAllowed(pThis, FUNCTION_errmode) )
    {
        int value = PopValInt(var);

        if ( value < 0 )  value = 0;
        if ( value > 1 )  value = 1;
        script->m_errMode = value;

        err = ERR_OK;
    }

    return ReturnErr(err, script, result, exception);
}

// Instruction "ipf(num)".

bool CScriptFunctions::rIPF(CBotVar* var, CBotVar* result, int& exception, void* user)
{
    CScript*    script = static_cast<CScript*>(user);
    CObject*    pThis = script->m_object;
    Error       err = ERR_WRONG_BOT;

    if ( IsFunctionAllowed(pThis, FUNCTION_ipf) )
    {
        int value = PopValInt(var);

        if ( value <     1 )  value =     1;
        if ( value > 10000 )  value = 10000;
        script->m_ipf = value;

        err = ERR_OK;
    }

    return ReturnErr(err, script, result, exception);
}

// Instruction "abstime()".

bool CScriptFunctions::rAbsTime(CBotVar* var, CBotVar* result, int& exception, void* user)
{
    CScript*    script = static_cast<CScript*>(user);
    CObject*    pThis = script->m_object;
    Error       err = ERR_WRONG_BOT;
    float       ret = 0.0f;

    if ( IsFunctionAllowed(pThis, FUNCTION_abstime) )
    {
        ret = script->m_main->GetGameTime();
        err = ERR_OK;
    }

    return ReturnFloat(ret, err, script, result, exception);
}

// Compilation of the instruction "pendown(color, width)".

CBotTypResult CScriptFunctions::cPenDown(CBotVar* &var, void* user)
{
    if ( var == nullptr )  return CBotTypResult(CBotTypFloat);
    if ( PopType(var) > CBotTypDouble )  return CBotTypResult(CBotErrBadNum);
    if ( var == nullptr )  return CBotTypResult(CBotTypFloat);
    if ( PopType(var) > CBotTypDouble )  return CBotTypResult(CBotErrBadNum);
    if ( var == nullptr )  return CBotTypResult(CBotTypFloat);
    return CBotTypResult(CBotErrOverParam);
}

// Instruction "pendown(color, width)".

bool CScriptFunctions::rPenDown(CBotVar* var, CBotVar* result, int& exception, void* user)
{
    CScript*    script = static_cast<CScript*>(user);
    CObject*    pThis = script->m_object;
    Error       err = ERR_WRONG_BOT;

    if ( script->m_taskExecutor->IsForegroundTask() )
        return WaitForForegroundTask(script, result, exception);

    if ( IsFunctionAllowed(pThis, FUNCTION_pendown) )
    {
        int color = PopValInt(var);
        if ( color <  0 )  color = 0;
        if ( color >= static_cast<int>(TraceColor::Max) )  color = static_cast<int>(TraceColor::Max) - 1;

        float width = PopValFloat(var);
        if ( width < 0.1f )  width = 0.1f;
        if ( width > 1.0f )  width = 1.0f;

        if (pThis->Implements(ObjectInterfaceType::TraceDrawing))
        {
            CTraceDrawingObject* traceDrawing = dynamic_cast<CTraceDrawingObject*>(pThis);
            if ( color != -1 )   traceDrawing->SetTraceColor(static_cast<TraceColor>(color));
            if ( width != 0.0f ) traceDrawing->SetTraceWidth(width);
            traceDrawing->SetTraceDown(true);

            err = ERR_OK;
            if ( GetObjectTraceDrawingDetails(pThis).penAnimated )
            {
                err = script->m_taskExecutor->StartTaskPen(true, static_cast<TraceColor>(color));
            }
        }
    }

    return ReturnErrOrForegroundTask(err, script, result, exception);
}

// Instruction "penup()".

bool CScriptFunctions::rPenUp(CBotVar* var, CBotVar* result, int& exception, void* user)
{
    CScript*    script = static_cast<CScript*>(user);
    CObject*    pThis = script->m_object;
    Error       err = ERR_WRONG_BOT;

    if ( script->m_taskExecutor->IsForegroundTask() )
        return WaitForForegroundTask(script, result, exception);

    if ( IsFunctionAllowed(pThis, FUNCTION_penup) )
    {
        if (pThis->Implements(ObjectInterfaceType::TraceDrawing))
        {
            CTraceDrawingObject* traceDrawing = dynamic_cast<CTraceDrawingObject*>(pThis);
            traceDrawing->SetTraceDown(false);

            err = ERR_OK;
            if ( GetObjectTraceDrawingDetails(pThis).penAnimated )
            {
                err = script->m_taskExecutor->StartTaskPen(false);
            }
        }
    }

    return ReturnErrOrForegroundTask(err, script, result, exception);
}

// Instruction "pencolor(color)".

bool CScriptFunctions::rPenColor(CBotVar* var, CBotVar* result, int& exception, void* user)
{
    CScript*    script = static_cast<CScript*>(user);
    CObject*    pThis = script->m_object;
    Error       err = ERR_WRONG_BOT;

    if ( script->m_taskExecutor->IsForegroundTask() )
        return WaitForForegroundTask(script, result, exception);

    if ( IsFunctionAllowed(pThis, FUNCTION_pencolor) )
    {
        int color = PopValInt(var);
        if ( color <  0 )  color = 0;
        if ( color >= static_cast<int>(TraceColor::Max) )  color = static_cast<int>(TraceColor::Max) - 1;

        if (pThis->Implements(ObjectInterfaceType::TraceDrawing))
        {
            CTraceDrawingObject* traceDrawing = dynamic_cast<CTraceDrawingObject*>(pThis);
            traceDrawing->SetTraceColor(static_cast<TraceColor>(color));

            err = ERR_OK;
            if ( GetObjectTraceDrawingDetails(pThis).penAnimated )
            {
                err = script->m_taskExecutor->StartTaskPen(traceDrawing->GetTraceDown(), traceDrawing->GetTraceColor());
            }
        }
    }

    return ReturnErrOrForegroundTask(err, script, result, exception);
}

// Instruction "penwidth( width )".

bool CScriptFunctions::rPenWidth(CBotVar* var, CBotVar* result, int& exception, void* user)
{
    CScript*    script = static_cast<CScript*>(user);
    CObject*    pThis = script->m_object;
    Error       err = ERR_WRONG_BOT;

    if ( IsFunctionAllowed(pThis, FUNCTION_penwidth) )
    {
        float width = PopValFloat(var);
        if ( width < 0.1f )  width = 0.1f;
        if ( width > 1.0f )  width = 1.0f;

        if (pThis->Implements(ObjectInterfaceType::TraceDrawing))
        {
            dynamic_cast<CTraceDrawingObject*>(pThis)->SetTraceWidth(width);
            err = ERR_OK;
        }
    }

    return ReturnErr(err, script, result, exception);
}

// Compilation of the instruction with one object parameter

CBotTypResult CScriptFunctions::cOneObject(CBotVar* &var, void* user)
{
    if ( var == nullptr )  return CBotTypResult(CBotTypFloat);
    var = var->GetNext();                                      // TODO: huh? no verification?!
    if ( var == nullptr )  return CBotTypResult(CBotTypFloat);
    return CBotTypResult(CBotErrOverParam);
}

// Instruction "camerafocus(object)".

bool CScriptFunctions::rCameraFocus(CBotVar* var, CBotVar* result, int& exception, void* user)
{
    CScript*    script = static_cast<CScript*>(user);
    CObject*    pThis = script->m_object;
    Error       err = ERR_WRONG_BOT;

    if ( IsFunctionAllowed(pThis, FUNCTION_camerafocus) )
    {
        CObject* object = PopValObject(var, pThis);

        script->m_main->SelectObject(object, false);
        err = ERR_OK;
    }

    return ReturnErr(err, script, result, exception);
}


// Compilation of class "point".

CBotTypResult CScriptFunctions::cPointConstructor(CBotVar* pThis, CBotVar* &var)
{
    if ( !pThis->IsElemOfClass("point") )  return CBotTypResult(CBotErrBadNum);

    if ( var == nullptr )  return CBotTypResult(0);  // ok if no parameter
    if ( PopType(var) > CBotTypDouble )  return CBotTypResult(CBotErrBadNum);
    if ( var == nullptr )  return CBotTypResult(CBotErrLowParam);
    if ( PopType(var) > CBotTypDouble )  return CBotTypResult(CBotErrBadNum);
    if ( var == nullptr )  return CBotTypResult(0);  // this function returns void
    if ( PopType(var) > CBotTypDouble )  return CBotTypResult(CBotErrBadNum);
    if ( var == nullptr )  return CBotTypResult(0);  // this function returns void
    return CBotTypResult(CBotErrOverParam);
}

//Execution of the class "point".

bool CScriptFunctions::rPointConstructor(CBotVar* pThis, CBotVar* var, CBotVar* pResult, int& Exception, void* user)
{
    CBotVar     *pX, *pY, *pZ;

    if ( var == nullptr )  return true;  // constructor with no parameters is ok

    pX = pThis->GetItem("x");
    if ( pX == nullptr ) { Exception = CBotErrUndefItem;  return false; }
    if ( var->GetType() > CBotTypDouble ) { Exception = CBotErrBadNum;  return false; }
    pX->SetValFloat( PopValFloat(var) );
    if ( var == nullptr ) { Exception = CBotErrLowParam;  return false; }

    pY = pThis->GetItem("y");
    if ( pY == nullptr )  { Exception = CBotErrUndefItem;  return false; }
    if ( var->GetType() > CBotTypDouble ) { Exception = CBotErrBadNum;  return false; }
    pY->SetValFloat( PopValFloat(var) );
    if ( var == nullptr )  return true;  // ok with only two parameters

    pZ = pThis->GetItem("z");
    if ( pZ == nullptr )  { Exception = CBotErrUndefItem;  return false; }
    if ( var->GetType() > CBotTypDouble ) { Exception = CBotErrBadNum;  return false; }
    pZ->SetValFloat( PopValFloat(var) );
    if ( var == nullptr )  return  true;  // no interruption

    { Exception = CBotErrOverParam;  return false; }
}

class CBotFileColobot : public CBotFile
{
public:
    static int m_numFilesOpen;

    CBotFileColobot(const std::string& filename, CBotFileAccessHandler::OpenMode mode)
    {
        if (mode == CBotFileAccessHandler::OpenMode::Read)
        {
            auto is = std::make_unique<CInputStream>(filename);
            if (is->is_open())
            {
                m_file = std::move(is);
            }
        }
        else if (mode == CBotFileAccessHandler::OpenMode::Write)
        {
            auto os = std::make_unique<COutputStream>(filename);
            if (os->is_open())
            {
                m_file = std::move(os);
            }
        }
        else if (mode == CBotFileAccessHandler::OpenMode::Append)
        {
            auto os = std::make_unique<COutputStream>(filename, std::ios_base::app);
            if (os->is_open())
            {
                m_file = std::move(os);
            }
        }

        if (Opened())
        {
            GetLogger()->Info("CBot open file '%s', mode '%c'\n", filename.c_str(), mode);
            m_numFilesOpen++;
        }
    }

    ~CBotFileColobot() override
    {
        if (Opened())
        {
            GetLogger()->Info("CBot close file\n");
            m_numFilesOpen--;
        }

        std::ios* file = m_file.get();
        CInputStream* is = dynamic_cast<CInputStream*>(file);
        if(is != nullptr) is->close();
        COutputStream* os = dynamic_cast<COutputStream*>(file);
        if(os != nullptr) os->close();
    }

    virtual bool Opened() override
    {
        return m_file != nullptr;
    }

    virtual bool Errored() override
    {
        return m_file->bad();
    }

    virtual bool IsEOF() override
    {
        return m_file->eof();
    }

    virtual std::string ReadLine() override
    {
        CInputStream* is = dynamic_cast<CInputStream*>(m_file.get());
        assert(is != nullptr);

        std::string line;
        std::getline(*is, line);
        return line;
    }

    virtual void Write(const std::string& s) override
    {
        COutputStream* os = dynamic_cast<COutputStream*>(m_file.get());
        assert(os != nullptr);

        *os << s;
    }

private:
    std::unique_ptr<std::ios> m_file;
};
int CBotFileColobot::m_numFilesOpen = 0;

class CBotFileAccessHandlerColobot : public CBotFileAccessHandler
{
public:
    virtual std::unique_ptr<CBotFile> OpenFile(const std::string& filename, OpenMode mode) override
    {
        return std::make_unique<CBotFileColobot>(PrepareFilename(filename), mode);
    }

    virtual bool DeleteFile(const std::string& filename) override
    {
        std::string fname = PrepareFilename(filename);
        GetLogger()->Info("CBot delete file '%s'\n", fname.c_str());
        return CResourceManager::Remove(fname);
    }

private:
    static std::string PrepareFilename(const std::string& filename)
    {
        CResourceManager::CreateNewDirectory("files");
        return "files/" + filename;
    }
};



// Initializes all functions for module CBOT.

void CScriptFunctions::Init()
{
    CBotProgram::Init();

    for (int i = 0; i < OBJECT_MAX; i++)
    {
        ObjectType type = static_cast<ObjectType>(i);
        std::string token = GetObjectName(type);
        if (token.size())
            CBotProgram::DefineNum(token, type);

        token = GetObjectAlias(type);
        if (token.size())
            CBotProgram::DefineNum(token, type);
    }
    CBotProgram::DefineNum("Any", OBJECT_NULL);

    for (int i = 0; i < static_cast<int>(TraceColor::Max); i++)
    {
        TraceColor color = static_cast<TraceColor>(i);
        CBotProgram::DefineNum(TraceColorName(color).c_str(), static_cast<int>(color));
    }

    CBotProgram::DefineNum("InFront",    TMA_FFRONT);
    CBotProgram::DefineNum("Behind",     TMA_FBACK);
    CBotProgram::DefineNum("EnergyCell", TMA_POWER);

    CBotProgram::DefineNum("DisplayError",   Ui::TT_ERROR);
    CBotProgram::DefineNum("DisplayWarning", Ui::TT_WARNING);
    CBotProgram::DefineNum("DisplayInfo",    Ui::TT_INFO);
    CBotProgram::DefineNum("DisplayMessage", Ui::TT_MESSAGE);

    CBotProgram::DefineNum("FilterNone",        FILTER_NONE);
    CBotProgram::DefineNum("FilterOnlyLanding", FILTER_ONLYLANDING);
    CBotProgram::DefineNum("FilterOnlyFlying",  FILTER_ONLYFLYING);
    CBotProgram::DefineNum("FilterFriendly",    FILTER_FRIENDLY);
    CBotProgram::DefineNum("FilterEnemy",       FILTER_ENEMY);
    CBotProgram::DefineNum("FilterNeutral",     FILTER_NEUTRAL);

    CBotProgram::DefineNum("DestructionNone",           static_cast<int>(DestructionType::NoEffect));
    CBotProgram::DefineNum("DestructionExplosion",      static_cast<int>(DestructionType::Explosion));
    CBotProgram::DefineNum("DestructionExplosionWater", static_cast<int>(DestructionType::ExplosionWater));
    CBotProgram::DefineNum("DestructionBurn",           static_cast<int>(DestructionType::Burn));
    CBotProgram::DefineNum("DestructionDrowned",        static_cast<int>(DestructionType::Drowned));

    CBotProgram::DefineNum("ResultNotEnded",  ERR_MISSION_NOTERM);
    CBotProgram::DefineNum("ResultLost",      INFO_LOST);
    CBotProgram::DefineNum("ResultLostQuick", INFO_LOSTq);
    CBotProgram::DefineNum("ResultWin",       ERR_OK);

    // NOTE: The Build___ constants are for use only with getbuild() and setbuild() for MissionController, not for normal players
    CBotProgram::DefineNum("BuildBotFactory",       BUILD_FACTORY);
    CBotProgram::DefineNum("BuildDerrick",          BUILD_DERRICK);
    CBotProgram::DefineNum("BuildConverter",        BUILD_CONVERT);
    CBotProgram::DefineNum("BuildRadarStation",     BUILD_RADAR);
    CBotProgram::DefineNum("BuildPowerPlant",       BUILD_ENERGY);
    CBotProgram::DefineNum("BuildNuclearPlant",     BUILD_NUCLEAR);
    CBotProgram::DefineNum("BuildPowerStation",     BUILD_STATION);
    CBotProgram::DefineNum("BuildRepairCenter",     BUILD_REPAIR);
    CBotProgram::DefineNum("BuildDefenseTower",     BUILD_TOWER);
    CBotProgram::DefineNum("BuildResearchCenter",   BUILD_RESEARCH);
    CBotProgram::DefineNum("BuildAutoLab",          BUILD_LABO);
    CBotProgram::DefineNum("BuildPowerCaptor",      BUILD_PARA);
    CBotProgram::DefineNum("BuildExchangePost",     BUILD_INFO);
    CBotProgram::DefineNum("BuildVault",            BUILD_SAFE);
    CBotProgram::DefineNum("BuildDestroyer",        BUILD_DESTROYER);
    CBotProgram::DefineNum("FlatGround",            BUILD_GFLAT);
    CBotProgram::DefineNum("UseFlags",              BUILD_FLAG);

    CBotProgram::DefineNum("ResearchTracked",       RESEARCH_TANK);
    CBotProgram::DefineNum("ResearchWinged",        RESEARCH_FLY);
    CBotProgram::DefineNum("ResearchShooter",       RESEARCH_CANON);
    CBotProgram::DefineNum("ResearchDefenseTower",  RESEARCH_TOWER);
    CBotProgram::DefineNum("ResearchNuclearPlant",  RESEARCH_ATOMIC);
    CBotProgram::DefineNum("ResearchThumper",       RESEARCH_THUMP);
    CBotProgram::DefineNum("ResearchShielder",      RESEARCH_SHIELD);
    CBotProgram::DefineNum("ResearchPhazerShooter", RESEARCH_PHAZER);
    CBotProgram::DefineNum("ResearchLegged",        RESEARCH_iPAW);
    CBotProgram::DefineNum("ResearchOrgaShooter",   RESEARCH_iGUN);
    CBotProgram::DefineNum("ResearchRecycler",      RESEARCH_RECYCLER);
    CBotProgram::DefineNum("ResearchSubber",        RESEARCH_SUBM);
    CBotProgram::DefineNum("ResearchSniffer",       RESEARCH_SNIFFER);
    CBotProgram::DefineNum("ResearchBuilder",       RESEARCH_BUILDER);
    CBotProgram::DefineNum("ResearchTarget",        RESEARCH_TARGET);

    CBotProgram::DefineNum("PolskiPortalColobota", 1337);

    CBotClass* bc;

    // Add the class Point.
    bc = CBotClass::Create("point", nullptr, true);  // intrinsic class
    bc->AddItem("x", CBotTypFloat);
    bc->AddItem("y", CBotTypFloat);
    bc->AddItem("z", CBotTypFloat);
    bc->AddFunction("point", rPointConstructor, cPointConstructor);

    // Adds the class Object.
    bc = CBotClass::Create("object", nullptr);
    bc->AddItem("category",    CBotTypResult(CBotTypInt), CBotVar::ProtectionLevel::ReadOnly);
    bc->AddItem("position",    CBotTypResult(CBotTypClass, "point"), CBotVar::ProtectionLevel::ReadOnly);
    bc->AddItem("orientation", CBotTypResult(CBotTypFloat), CBotVar::ProtectionLevel::ReadOnly);
    bc->AddItem("pitch",       CBotTypResult(CBotTypFloat), CBotVar::ProtectionLevel::ReadOnly);
    bc->AddItem("roll",        CBotTypResult(CBotTypFloat), CBotVar::ProtectionLevel::ReadOnly);
    bc->AddItem("energyLevel", CBotTypResult(CBotTypFloat), CBotVar::ProtectionLevel::ReadOnly);
    bc->AddItem("shieldLevel", CBotTypResult(CBotTypFloat), CBotVar::ProtectionLevel::ReadOnly);
    bc->AddItem("temperature", CBotTypResult(CBotTypFloat), CBotVar::ProtectionLevel::ReadOnly);
    bc->AddItem("altitude",    CBotTypResult(CBotTypFloat), CBotVar::ProtectionLevel::ReadOnly);
    bc->AddItem("lifeTime",    CBotTypResult(CBotTypFloat), CBotVar::ProtectionLevel::ReadOnly);
    bc->AddItem("energyCell",  CBotTypResult(CBotTypPointer, "object"), CBotVar::ProtectionLevel::ReadOnly);
    bc->AddItem("load",        CBotTypResult(CBotTypPointer, "object"), CBotVar::ProtectionLevel::ReadOnly);
    bc->AddItem("id",          CBotTypResult(CBotTypInt), CBotVar::ProtectionLevel::ReadOnly);
    bc->AddItem("team",        CBotTypResult(CBotTypInt), CBotVar::ProtectionLevel::ReadOnly);
    bc->AddItem("dead",        CBotTypResult(CBotTypBoolean), CBotVar::ProtectionLevel::ReadOnly);
    bc->AddItem("velocity",    CBotTypResult(CBotTypClass, "point"), CBotVar::ProtectionLevel::ReadOnly);

    CBotProgram::AddFunction("endmission",rEndMission,cEndMission);
    CBotProgram::AddFunction("playmusic", rPlayMusic ,cPlayMusic);
    CBotProgram::AddFunction("stopmusic", rStopMusic ,cNull);

    CBotProgram::AddFunction("getbuild",          rGetBuild,          cNull);
    CBotProgram::AddFunction("getresearchenable", rGetResearchEnable, cNull);
    CBotProgram::AddFunction("getresearchdone",   rGetResearchDone,   cNull);
    CBotProgram::AddFunction("setbuild",          rSetBuild,          cOneInt);
    CBotProgram::AddFunction("setresearchenable", rSetResearchEnable, cOneInt);
    CBotProgram::AddFunction("setresearchdone",   rSetResearchDone,   cOneInt);

    CBotProgram::AddFunction("canbuild",        rCanBuild,        cOneIntReturnBool);
    CBotProgram::AddFunction("canresearch",     rCanResearch,     cOneIntReturnBool);
    CBotProgram::AddFunction("researched",      rResearched,      cOneIntReturnBool);
    CBotProgram::AddFunction("buildingenabled", rBuildingEnabled, cOneIntReturnBool);

    CBotProgram::AddFunction("build",           rBuild,           cOneInt);
    CBotProgram::AddFunction("flag",            rFlag,            cGrabDrop);
    CBotProgram::AddFunction("deflag",          rDeflag,          cNull);

    CBotProgram::AddFunction("retobject", rGetObject, cGetObject);
    CBotProgram::AddFunction("retobjectbyid", rGetObjectById, cGetObject);
    CBotProgram::AddFunction("delete",    rDelete,    cDelete);
    CBotProgram::AddFunction("search",    rSearch,    cSearch);
    CBotProgram::AddFunction("searchall", rSearchAll, cSearchAll);
    CBotProgram::AddFunction("radar",     rRadar,     cRadar);
    CBotProgram::AddFunction("radarall",  rRadarAll,  cRadarAll);
    CBotProgram::AddFunction("detect",    rDetect,    cDetect);
    CBotProgram::AddFunction("direction", rDirection, cDirection);
    CBotProgram::AddFunction("produce",   rProduce,   cProduce);
    CBotProgram::AddFunction("distance",  rDistance,  cDistance);
    CBotProgram::AddFunction("distance2d",rDistance2d,cDistance);
    CBotProgram::AddFunction("space",     rSpace,     cSpace);
    CBotProgram::AddFunction("flatspace", rFlatSpace, cFlatSpace);
    CBotProgram::AddFunction("flatground",rFlatGround,cFlatGround);
    CBotProgram::AddFunction("wait",      rWait,      cOneFloat);
    CBotProgram::AddFunction("move",      rMove,      cOneFloat);
    CBotProgram::AddFunction("turn",      rTurn,      cOneFloat);
    CBotProgram::AddFunction("goto",      rGoto,      cGoto);
    CBotProgram::AddFunction("grab",      rGrab,      cGrabDrop);
    CBotProgram::AddFunction("drop",      rDrop,      cGrabDrop);
    CBotProgram::AddFunction("sniff",     rSniff,     cNull);
    CBotProgram::AddFunction("receive",   rReceive,   cReceive);
    CBotProgram::AddFunction("send",      rSend,      cSend);
    CBotProgram::AddFunction("deleteinfo",rDeleteInfo,cDeleteTestInfo);
    CBotProgram::AddFunction("testinfo",  rTestInfo,  cDeleteTestInfo);
    CBotProgram::AddFunction("thump",     rThump,     cNull);
    CBotProgram::AddFunction("recycle",   rRecycle,   cNull);
    CBotProgram::AddFunction("shield",    rShield,    cShield);
    CBotProgram::AddFunction("fire",      rFire,      cFire);
    CBotProgram::AddFunction("aim",       rAim,       cAim);
    CBotProgram::AddFunction("motor",     rMotor,     cMotor);
    CBotProgram::AddFunction("jet",       rJet,       cOneFloat);
    CBotProgram::AddFunction("topo",      rTopo,      cTopo);
    CBotProgram::AddFunction("message",   rMessage,   cMessage);
    CBotProgram::AddFunction("cmdline",   rCmdline,   cOneFloat);
    CBotProgram::AddFunction("ismovie",   rIsMovie,   cNull);
    CBotProgram::AddFunction("errmode",   rErrMode,   cOneFloat);
    CBotProgram::AddFunction("ipf",       rIPF,       cOneFloat);
    CBotProgram::AddFunction("abstime",   rAbsTime,   cNull);
    CBotProgram::AddFunction("pendown",   rPenDown,   cPenDown);
    CBotProgram::AddFunction("penup",     rPenUp,     cNull);
    CBotProgram::AddFunction("pencolor",  rPenColor,  cOneFloat);
    CBotProgram::AddFunction("penwidth",  rPenWidth,  cOneFloat);
    CBotProgram::AddFunction("factory",   rFactory,   cFactory);
    CBotProgram::AddFunction("camerafocus", rCameraFocus, cOneObject);
    CBotProgram::AddFunction("takeoff",   rTakeOff,   cOneObject);
    CBotProgram::AddFunction("isbusy",    rIsBusy,    cIsBusy);
    CBotProgram::AddFunction("research",  rResearch,  cResearch);
    CBotProgram::AddFunction("destroy",   rDestroy,   cOneObject);

    SetFileAccessHandler(std::make_unique<CBotFileAccessHandlerColobot>());
}


// Updates the class Object.

void CScriptFunctions::uObject(CBotVar* botThis, void* user)
{
    CPhysics*   physics;
    CBotVar     *pVar, *pSub;
    ObjectType  type;
    glm::vec3    pos;
    float       value;

    if ( user == nullptr )  return;

    CObject* obj = static_cast<CObject*>(user);
    assert(obj->Implements(ObjectInterfaceType::Old));
    COldObject* object = static_cast<COldObject*>(obj);

    physics = object->GetPhysics();

    // Updates the object's type.
    pVar = botThis->GetItemList();  // "category"
    type = object->GetType();
    pVar->SetValInt(type, object->GetName());

    // Updates the position of the object.
    pVar = pVar->GetNext();  // "position"
    if (IsObjectBeingTransported(object))
    {
        pSub = pVar->GetItemList();  // "x"
        pSub->SetValFloat(nanf(""));
        pSub = pSub->GetNext();  // "y"
        pSub->SetValFloat(nanf(""));
        pSub = pSub->GetNext();  // "z"
        pSub->SetValFloat(nanf(""));
    }
    else
    {
        pos = object->GetPosition();
        float waterLevel = Gfx::CEngine::GetInstancePointer()->GetWater()->GetLevel();
        pos.y -= waterLevel;  // relative to sea level!
        pSub = pVar->GetItemList();  // "x"
        pSub->SetValFloat(pos.x/g_unit);
        pSub = pSub->GetNext();  // "y"
        pSub->SetValFloat(pos.z/g_unit);
        pSub = pSub->GetNext();  // "z"
        pSub->SetValFloat(pos.y/g_unit);
    }

    // Updates the angle.
    pos = object->GetRotation();
    pos += object->GetTilt();
    pVar = pVar->GetNext();  // "orientation"
    pVar->SetValFloat(Math::NormAngle(2*Math::PI - pos.y)*180.0f/Math::PI);
    pVar = pVar->GetNext();  // "pitch"
    pVar->SetValFloat((Math::NormAngle(pos.z + Math::PI) - Math::PI)*180.0f/Math::PI);
    pVar = pVar->GetNext();  // "roll"
    pVar->SetValFloat((Math::NormAngle(pos.x + Math::PI) - Math::PI)*180.0f/Math::PI);

    // Updates the energy level of the object.
    pVar = pVar->GetNext();  // "energyLevel"
    value = object->GetEnergyLevel();
    pVar->SetValFloat(value);

    // Updates the shield level of the object.
    pVar = pVar->GetNext();  // "shieldLevel"
    if ( !obj->Implements(ObjectInterfaceType::Shielded) ) value = 1.0f;
    else value = dynamic_cast<CShieldedObject*>(object)->GetShield();
    pVar->SetValFloat(value);

    // Updates the temperature of the reactor.
    pVar = pVar->GetNext();  // "temperature"
    if ( !obj->Implements(ObjectInterfaceType::JetFlying) )  value = 0.0f;
    else value = 1.0f-dynamic_cast<CJetFlyingObject*>(object)->GetReactorRange();
    pVar->SetValFloat(value);

    // Updates the height above the ground.
    pVar = pVar->GetNext();  // "altitude"
    if ( physics == nullptr )  value = 0.0f;
    else                 value = physics->GetFloorHeight();
    pVar->SetValFloat(value/g_unit);

    // Updates the lifetime of the object.
    pVar = pVar->GetNext();  // "lifeTime"
    value = object->GetAbsTime();
    pVar->SetValFloat(value);

    // Updates the type of battery.
    pVar = pVar->GetNext();  // "energyCell"
    if (HasPowerCellSlot(object))
    {
        CObject *power = GetObjectInPowerCellSlot(object);
        if (power == nullptr)
        {
            pVar->SetPointer(nullptr);
        }
        else if (power->Implements(ObjectInterfaceType::Old))
        {
            pVar->SetPointer(power->GetBotVar());
        }
    }

    // Updates the transported object's type.
    pVar = pVar->GetNext();  // "load"
    if (HasCargoSlot(object))
    {
        CObject* cargo = GetObjectInCargoSlot(object);
        if (cargo == nullptr)
        {
            pVar->SetPointer(nullptr);
        }
        else if (cargo->Implements(ObjectInterfaceType::Old))
        {
            pVar->SetPointer(cargo->GetBotVar());
        }
    }

    pVar = pVar->GetNext();  // "id"
    value = object->GetID();
    pVar->SetValInt(value);

    pVar = pVar->GetNext();  // "team"
    value = object->GetTeam();
    pVar->SetValInt(value);

    pVar = pVar->GetNext();  // "dead"
    value = object->IsDying();
    pVar->SetValInt(value);

    // Updates the velocity of the object.
    pVar = pVar->GetNext();  // "velocity"
    if (IsObjectBeingTransported(object) || physics == nullptr)
    {
        pSub = pVar->GetItemList();  // "x"
        pSub->SetValFloat(nanf(""));
        pSub = pSub->GetNext();  // "y"
        pSub->SetValFloat(nanf(""));
        pSub = pSub->GetNext();  // "z"
        pSub->SetValFloat(nanf(""));
    }
    else
    {
        glm::mat4 matRotate;
        Math::LoadRotationZXYMatrix(matRotate, object->GetRotation());
        pos = physics->GetLinMotion(MO_CURSPEED);
        pos = Math::Transform(matRotate, pos);

        pSub = pVar->GetItemList();  // "x"
        pSub->SetValFloat(pos.x/g_unit);
        pSub = pSub->GetNext();  // "y"
        pSub->SetValFloat(pos.z/g_unit);
        pSub = pSub->GetNext();  // "z"
        pSub->SetValFloat(pos.y/g_unit);
    }
}

CBotVar* CScriptFunctions::CreateObjectVar(CObject* obj)
{
    CBotClass* bc = CBotClass::Find("object");
    if ( bc != nullptr )
    {
        bc->SetUpdateFunc(CScriptFunctions::uObject);
    }

    CBotVar* botVar = CBotVar::Create("", CBotTypResult(CBotTypClass, "object"));
    botVar->SetUserPtr(obj);
    botVar->SetIdent(obj->GetID());
    return botVar;
}

void CScriptFunctions::DestroyObjectVar(CBotVar* botVar, bool permanent)
{
    if ( botVar == nullptr ) return;

    botVar->SetUserPtr(OBJECTDELETED);
    if (permanent)
        CBotVar::Destroy(botVar);
}

bool CScriptFunctions::CheckOpenFiles()
{
    return CBotFileColobot::m_numFilesOpen > 0;
}

bool CScriptFunctions::ReturnInt(int ret, Error err, CScript* script, CBot::CBotVar* result, int &exception)
{
    result->SetValInt(ret);
    return ExitWithExceptionIfNeeded(err, script, exception);
}

bool CScriptFunctions::ReturnFloat(float ret, Error err, CScript* script, CBot::CBotVar* result, int &exception)
{
    result->SetValFloat(ret);
    return ExitWithExceptionIfNeeded(err, script, exception);
}

bool CScriptFunctions::ReturnPoint(glm::vec3& ret, Error err, CScript* script, CBot::CBotVar* result, int &exception)
{
    CBotVar* pSub = result->GetItemList();
    if ( pSub != nullptr )
    {
        pSub->SetValFloat(ret.x);
        pSub = pSub->GetNext();
        pSub->SetValFloat(ret.z);
        pSub = pSub->GetNext();
        pSub->SetValFloat(ret.y);
    }
    return ExitWithExceptionIfNeeded(err, script, exception);
}

bool CScriptFunctions::ReturnPointer(CObject* ret, Error err, CScript* script, CBot::CBotVar* result, int &exception)
{
    CBotVar* ptr = (ret != nullptr) ? ret->GetBotVar() : nullptr;
    result->SetPointer(ptr);
    return ExitWithExceptionIfNeeded(err, script, exception);
}

bool CScriptFunctions::ReturnPointerList(std::vector<CObject*> ret, Error err, CScript* script, CBot::CBotVar* result, int &exception)
{
    result->SetInit(CBotVar::InitType::DEF);

    int i = 0;
    for (CObject* obj : ret)
        result->GetItem(i++, true)->SetPointer(obj->GetBotVar());

    return ExitWithExceptionIfNeeded(err, script, exception);
}

bool CScriptFunctions::ReturnNan(Error err, CScript* script, CBot::CBotVar* result, int &exception)
{
    result->SetValFloat(nanf(""));
    return ExitWithExceptionIfNeeded(err, script, exception);
}

bool CScriptFunctions::ReturnErr(Error err, CScript* script, CBot::CBotVar* result, int &exception)
{
    result->SetValInt(err);
    return ExitWithExceptionIfNeeded(err, script, exception);
}

bool CScriptFunctions::ReturnErrOrForegroundTask(Error err, CScript* script, CBot::CBotVar* result, int &exception)
{
    result->SetValInt(err);
    if ( err != ERR_OK )
    {
        script->m_taskExecutor->StopForegroundTask();
        return ExitWithExceptionIfNeeded(err, script, exception);
    }
    return WaitForForegroundTask(script, result, exception);
}

bool CScriptFunctions::ReturnErrOrBackgroundTask(Error err, CScript* script, CBot::CBotVar* result, int &exception)
{
    result->SetValInt(err);
    if ( err != ERR_OK )
    {
        script->m_taskExecutor->StopBackgroundTask();
        return ExitWithExceptionIfNeeded(err, script, exception);
    }
    return WaitForBackgroundTask(script, result, exception);
}

bool CScriptFunctions::ExitWithExceptionIfNeeded(Error err, CScript* script, int &exception)
{
    if ( err != 0 && script->m_errMode == ERM_STOP )
    {
        exception = err;
        return false;
    }
    else
    {
        exception = 0;
        return true;
    }
}
