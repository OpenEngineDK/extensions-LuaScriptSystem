
#include "ScriptISoundSystem.h"

ScriptISoundSystem::ScriptISoundSystem(lua_State* L) {

  if (ScriptSystem::CheckStackSize(L, "ISoundSystem", 1) || 
      ScriptSystem::CheckArgType(L, "ISoundSystem", "userdata", 1, -1))
    return;

  ISoundSystem* newsys = (ISoundSystem*) lua_touserdata(L, -1);
  sys = newsys;

}

int ScriptISoundSystem::CreateSound(lua_State* L) {

  if (ScriptSystem::CheckStackSize(L, "ISoundSystem", 2) || 
      ScriptSystem::CheckArgType(L, "ISoundSystem", "string", 1, -1))
    return 0;

  if (!sys) {
    logger.info << "ISoundSystem not proberbly initialized. Call aborted."
		<< logger.end;
    return 0;
  }

  string soundfile = lua_tostring(L, -1);
  ISoundResourcePtr soundrp = ResourceManager<ISoundResource>
    ::Create(soundfile);
  ISound* sound = sys->CreateSound(soundrp);
  lua_pushlightuserdata(L, sound);
  return 1;

}

int ScriptISoundSystem::SetRoot(lua_State* L) {

  if (ScriptSystem::CheckStackSize(L, "ISoundSystem", 2) || 
      ScriptSystem::CheckArgType(L, "ISoundSystem", "userdata", 1, -1))
    return 0;

  if (!sys) {
    logger.info << "ISoundSystem not proberbly initialized. Call aborted."
		<< logger.end;
    return 0;
  }

  ISceneNode* scene = (ISceneNode*) lua_touserdata(L, -1);
  sys->SetRoot(scene);
  return 0;

}

int ScriptISoundSystem::SetMasterGain(lua_State* L) {

  if (ScriptSystem::CheckStackSize(L, "ISoundSystem", 2) || 
      ScriptSystem::CheckArgType(L, "ISoundSystem", "float", 1, -1))
    return 0;

  if (!sys) {
    logger.info << "ISoundSystem not proberbly initialized. Call aborted."
		<< logger.end;
    return 0;
  }

  float gain = lua_tonumber(L, -1);
  sys->SetMasterGain(gain);
  return 0;

}

int ScriptISoundSystem::GetMasterGain(lua_State* L) {

  if (ScriptSystem::CheckStackSize(L, "ISoundSystem", 1))
     return 0;

  if (!sys) {
    logger.info << "ISoundSystem not proberbly initialized. Call aborted."
		<< logger.end;
    return 0;
  }

  float gain = sys->GetMasterGain();
  lua_pushnumber(L, gain);
  return 1;

}
