
#include "ScriptIStereoSound.h"

ScriptIStereoSound::ScriptIStereoSound(lua_State* L) {

  if (ScriptSystem::CheckStackSize(L, "IStereoSound", 1))
    return;

  IStereoSound* s = (IStereoSound*) lua_touserdata(L, -1);
  sound = s;

}

int ScriptIStereoSound::GetLeft(lua_State* L) {

  if (ScriptSystem::CheckStackSize(L, "GetLeft", 1))
    return 0;

  if (!sound) {
    logger.info << "IStereoSound not proberbly initialized. Call aborted."
		<< logger.end;
    return 0;
  }

  IMonoSound* left = sound->GetLeft();
  lua_pushlightuserdata(L, left);
  return 1;

}

int ScriptIStereoSound::GetRight(lua_State* L) {

  if (ScriptSystem::CheckStackSize(L, "GetRight", 1))
    return 0;

  if (!sound) {
    logger.info << "IStereoSound not proberbly initialized. Call aborted."
		<< logger.end;
    return 0;
  }

  IMonoSound* right = sound->GetRight();
  lua_pushlightuserdata(L, right);
  return 1;
  
}

int ScriptIStereoSound::IsStereoSound(lua_State* L) {

  if (ScriptSystem::CheckStackSize(L, "IsStereoSound", 1))
    return 0;

  if (!sound) {
    logger.info << "IStereoSound not proberbly initialized. Call aborted."
		<< logger.end;
    return 0;
  }

  lua_pushboolean(L, true);
  return 1;

}

int ScriptIStereoSound::IsMonoSound(lua_State* L) {

  if (ScriptSystem::CheckStackSize(L, "IsMonoSound", 1))
    return 0;

  if (!sound) {
    logger.info << "IStereoSound not proberbly initialized. Call aborted."
		<< logger.end;
    return 0;
  }

  lua_pushboolean(L, false);
  return 1;

}

