
#include "ScriptISound.h"

ScriptISound::ScriptISound(lua_State* L) {

  if (ScriptSystem::CheckStackSize(L, "ISound", 1) || 
      ScriptSystem::CheckArgType(L, "ISound", "userdata", 1, -1))
    return;

  ISound* s = (ISound*) lua_touserdata(L, -1);
  sound = s;

}

int ScriptISound::IsStereoSound(lua_State* L) {

  if (ScriptSystem::CheckStackSize(L, "IsStereoSound", 1))
    return 0;

  if (!sound) {
    logger.info << "ISound not proberbly initialized. Call aborted."
		<< logger.end;
    return 0;
  }

  bool b = sound->IsStereoSound();
  lua_pushboolean(L, b);
  return 1;

}

int ScriptISound::IsMonoSound(lua_State* L) {

  if (ScriptSystem::CheckStackSize(L, "IsMonoSound", 1))
    return 0;

  if (!sound) {
    logger.info << "ISound not proberbly initialized. Call aborted."
		<< logger.end;
    return 0;
  }
  
  bool b = sound->IsMonoSound();
  lua_pushboolean(L, b);
  return 1;

}

int ScriptISound::IsPlaying(lua_State* L) {

  if (ScriptSystem::CheckStackSize(L, "IsPlaying", 1))
    return 0;

  if (!sound) {
    logger.info << "ISound not proberbly initialized. Call aborted."
		<< logger.end;
    return 0;
  }

  bool b = sound->IsPlaying();
  lua_pushboolean(L, b);
  return 1;

}

int ScriptISound::Play(lua_State* L) {

  if (ScriptSystem::CheckStackSize(L, "Play", 1))
    return 0;

  if (!sound) {
    logger.info << "ISound not proberbly initialized. Call aborted."
		<< logger.end;
    return 0;
  }
  
  sound->Play();
  return 0;

}

int ScriptISound::Stop(lua_State* L) {

  if (ScriptSystem::CheckStackSize(L, "Stop", 1))
    return 0;

  if (!sound) {
    logger.info << "ISound not proberbly initialized. Call aborted."
		<< logger.end;
    return 0;
  }

  sound->Stop();
  return 0;

}

int ScriptISound::Pause(lua_State* L) {

  if (ScriptSystem::CheckStackSize(L, "Pause", 1))
    return 0;

  if (!sound) {
    logger.info << "ISound not proberbly initialized. Call aborted."
		<< logger.end;
    return 0;
  }

  sound->Pause();
  return 0;

}

int ScriptISound::SetLooping(lua_State* L) {

  if (ScriptSystem::CheckStackSize(L, "SetLooping", 2) || 
      ScriptSystem::CheckArgType(L, "SetLooping", "bool", 1, -1))
    return 0;

  if (!sound) {
    logger.info << "ISound not proberbly initialized. Call aborted."
		<< logger.end;
    return 0;
  }

  bool b = lua_toboolean(L, -1);
  sound->SetLooping(b);
  return 0;

}

int ScriptISound::GetLooping(lua_State* L) {

  if (ScriptSystem::CheckStackSize(L, "GetLooping", 1))
    return 0;

  if (!sound) {
    logger.info << "ISound not proberbly initialized. Call aborted."
		<< logger.end;
    return 0;
  }

  bool b = sound->GetLooping();
  lua_pushboolean(L, b);
  return 1;

}

int ScriptISound::SetGain(lua_State* L) {

  if (ScriptSystem::CheckStackSize(L, "SetGain", 2) || 
      ScriptSystem::CheckArgType(L, "SetGain", "float", 1, -1))
    return 0;

  if (!sound) {
    logger.info << "ISound not proberbly initialized. Call aborted."
		<< logger.end;
    return 0;
  }

  float newgain = lua_tonumber(L, -1);
  sound->SetGain(newgain);
  return 0;

}

int ScriptISound::GetGain(lua_State* L) {

  if (ScriptSystem::CheckStackSize(L, "GetGain", 1))
    return 0;

  if (!sound) {
    logger.info << "ISound not proberbly initialized. Call aborted."
		<< logger.end;
    return 0;
  }

  float gain = sound->GetGain();
  lua_pushnumber(L, gain);
  return 1;

}

int ScriptISound::GetLengthInSamples(lua_State* L) {

  if (ScriptSystem::CheckStackSize(L, "GetLengthInSamples", 1))
    return 0;

  if (!sound) {
    logger.info << "ISound not proberbly initialized. Call aborted."
		<< logger.end;
    return 0;
  }

  unsigned int length = sound->GetLengthInSamples();
  lua_pushinteger(L, length);
  return 1;

}

int ScriptISound::GetLength(lua_State* L) {

  if (ScriptSystem::CheckStackSize(L, "GetLength", 1))
    return 0;

  if (!sound) {
    logger.info << "ISound not proberbly initialized. Call aborted."
		<< logger.end;
    return 0;
  }

  Time t = sound->GetLength();
  lua_pushlightuserdata(L, &t);
  return 1;

}

int ScriptISound::SetElapsedSamples(lua_State* L) {

  if (ScriptSystem::CheckStackSize(L, "SetElapsedSamples", 2) || 
      ScriptSystem::CheckArgType(L, "SetElapsedSamples", "int", 1, -1))
    return 0;

  if (!sound) {
    logger.info << "ISound not proberbly initialized. Call aborted."
		<< logger.end;
    return 0;
  }

  unsigned int i = lua_tointeger(L, -1);
  sound->SetElapsedSamples(i);
  return 0;

}

int ScriptISound::GetElapsedSamples(lua_State* L) {

  if (ScriptSystem::CheckStackSize(L, "GetElapsedSamples", 1))
    return 0;

  if (!sound) {
    logger.info << "ISound not proberbly initialized. Call aborted."
		<< logger.end;
    return 0;
  }

  unsigned int i = sound->GetElapsedSamples();
  lua_pushinteger(L, i);
  return 1;

}

int ScriptISound::SetElapsedTime(lua_State* L) {

  if (ScriptSystem::CheckStackSize(L, "SetElapsedTime", 2) || 
      ScriptSystem::CheckArgType(L, "SetElapsedTime", "userdata", 1, -1))
    return 0;

  if (!sound) {
    logger.info << "ISound not proberbly initialized. Call aborted."
		<< logger.end;
    return 0;
  }

  Time* t = (Time*) lua_touserdata(L, -1);
  sound->SetElapsedTime(*t);
  return 0;

}

int ScriptISound::GetElapsedTime(lua_State* L) {

  if (ScriptSystem::CheckStackSize(L, "GetElapsedTime", 1))
    return 0;

  if (!sound) {
    logger.info << "ISound not proberbly initialized. Call aborted."
		<< logger.end;
    return 0;
  }

  Time t = sound->GetElapsedTime();
  lua_pushlightuserdata(L, &t);
  return 1;

}

int ScriptISound::GetTimeLeft(lua_State* L) {

  if (ScriptSystem::CheckStackSize(L, "GetTimeLeft", 1))
    return 0;

  if (!sound) {
    logger.info << "ISound not proberbly initialized. Call aborted."
		<< logger.end;
    return 0;
  }

  Time t = sound->GetTimeLeft();
  lua_pushlightuserdata(L, &t);
  return 1;

}

int ScriptISound::IsAtEnd(lua_State* L) {

  if (ScriptSystem::CheckStackSize(L, "IsAtEnd", 1))
    return 0;

  if (!sound) {
    logger.info << "ISound not proberbly initialized. Call aborted."
		<< logger.end;
    return 0;
  }

  bool b = sound->IsAtEnd();
  lua_pushboolean(L, b);
  return 1;

}
