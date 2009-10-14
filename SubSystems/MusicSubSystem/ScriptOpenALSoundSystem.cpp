
#include "ScriptOpenALSoundSystem.h"

ScriptOpenALSoundSystem::ScriptOpenALSoundSystem(lua_State* L) {

  if (ScriptSystem::CheckStackSize(L, "OpenALSoundSystem", 2) || 
      ScriptSystem::CheckArgType(L, "OpenALSoundSystem", "userdata", 1, -2) ||
      ScriptSystem::CheckArgType(L, "OpenALSoundSystem", "userdata", 2, -1))
    return;

  ISceneNode* scene = (ISceneNode*) lua_touserdata(L, -2);
  FollowCamera* cam = (FollowCamera*) lua_touserdata(L, -1);

  sounds = new OpenALSoundSystem(scene, cam);

}

ScriptOpenALSoundSystem::~ScriptOpenALSoundSystem() {

  delete sounds;

}

int ScriptOpenALSoundSystem::CreateSound(lua_State* L) {

  if (ScriptSystem::CheckStackSize(L, "OpenALSoundSystem", 2) || 
      ScriptSystem::CheckArgType(L, "OpenALSoundSystem", "string", 1, -1))
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
      ScriptSystem::CheckArgType(L, "OpenALSoundSystem", "userdata", 1, -1))
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
      ScriptSystem::CheckArgType(L, "OpenALSoundSystem", "float", 1, -1))
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
