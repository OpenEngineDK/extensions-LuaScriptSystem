
#include "ScriptOpenALSoundSystem.h"

ScriptOpenALSoundSystem::ScriptOpenALSoundSystem(lua_State* L) {

  int nargs = lua_gettop(L);

  //take care of the pointer case
  if (nargs == 1) {
    
    if (ScriptSystem::CheckArgType(L, "OpenALSoundSystem", 'p', 1, -1))
      return;

    sounds = (OpenALSoundSystem*) lua_touserdata(L, -1);
        
  } 
  //the actually new case
  else if (nargs >= 2) {

    if (ScriptSystem::CheckArgType(L, "OpenALSoundSystem", 'p', 1, -2) ||
	ScriptSystem::CheckArgType(L, "OpenALSoundSystem", 'p', 2, -1))
    return;

    if (nargs > 2)
      logger.info << "LuaScriptSystem:: warning OpenALSoundSystem only needs 2 arguments but received" << nargs
		  << " top 2 used" << logger.end;

    ISceneNode* scene = (ISceneNode*) lua_touserdata(L, -2);
    IViewingVolume* vv = (IViewingVolume*) lua_touserdata(L, -1);
    
    sounds = new OpenALSoundSystem(scene, vv);

  }
  else {

    logger.info << "LuaScriptSystem:: OpenALSoundSystem needs 2 arguments (ISceneNode* and IViewingVolume*) but only received"
		<< nargs << logger.end;

  }

}

ScriptOpenALSoundSystem::~ScriptOpenALSoundSystem() {

  delete sounds;

}

int ScriptOpenALSoundSystem::CreateSound(lua_State* L) {

  if (ScriptSystem::CheckStackSize(L, "OpenALSoundSystem", 2) || 
      ScriptSystem::CheckArgType(L, "OpenALSoundSystem", 's', 1, -1))
    return 0;

  if (!sounds) {
    logger.info << "OpenALSoundSystem not proberbly initialized. Call aborted."
		<< logger.end;
    return 0;
  }

  string soundfile = lua_tostring(L, -1);
  ISoundResourcePtr soundrp = ResourceManager<ISoundResource>
    ::Create(soundfile);
  ISound* sound = sounds->CreateSound(soundrp);
  lua_pushlightuserdata(L, sound);
  return 1;

}

int ScriptOpenALSoundSystem::SetRoot(lua_State* L) {

  if (ScriptSystem::CheckStackSize(L, "OpenALSoundSystem", 2) || 
      ScriptSystem::CheckArgType(L, "OpenALSoundSystem", 'p', 1, -1))
    return 0;

  if (!sounds) {
    logger.info << "OpenALSoundSystem not proberbly initialized. Call aborted."
		<< logger.end;
    return 0;
  }

  ISceneNode* newval = (ISceneNode*) lua_touserdata(L, -1);
  sounds->SetRoot(newval);
  return 0;

}

int ScriptOpenALSoundSystem::SetMasterGain(lua_State* L) {

  if (ScriptSystem::CheckStackSize(L, "OpenALSoundSystem", 2) || 
      ScriptSystem::CheckArgType(L, "OpenALSoundSystem", 'd', 1, -1))
    return 0;

  if (!sounds) {
    logger.info << "OpenSoundSystem not proberbly initialized. Call aborted."
		<< logger.end;
    return 0;
  }

  float newval = lua_tonumber(L, -1);
  sounds->SetMasterGain(newval);
  return 0;

}

int ScriptOpenALSoundSystem::GetMasterGain(lua_State* L) {

  if (ScriptSystem::CheckStackSize(L, "OpenSoundSystem", 1))
     return 0;

  if (!sounds) {
    logger.info << "OpenALSoundSystem not proberbly initialized. Call aborted."
		<< logger.end;
    return 0;
  }

  float val = sounds->GetMasterGain();
  lua_pushnumber(L, val);
  return 1;

}

int ScriptOpenALSoundSystem::GetOpenALSoundSystem(lua_State* L) {

  if (!sounds) {
    logger.info << "OpenALSoundSystem not proberbly initialized. Call aborted."
		<< logger.end;
    return 0;
  }

  lua_pushlightuserdata(L, sounds);
  return 1;

}
