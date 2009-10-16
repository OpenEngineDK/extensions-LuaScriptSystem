
#include "ScriptIMonoSound.h"

ScriptIMonoSound::ScriptIMonoSound(lua_State* L) {

  if (ScriptSystem::CheckStackSize(L, "IMonoSound", 1) ||
      ScriptSystem::CheckArgType(L, "IMonoSound", 'p', 1, -1))
    return;

  IMonoSound* s = (IMonoSound*) lua_touserdata(L, -1);
  sound = s;

}

int ScriptIMonoSound::IsStereoSound(lua_State* L) {

  if (ScriptSystem::CheckStackSize(L, "IStereoSound", 1))
    return 0;

  if (!sound) {
    logger.info << "IMonoSound not proberbly initialized. Call aborted."
		<< logger.end;
    return 0;
  }

  lua_pushboolean(L, false);
  return 1;

}

int ScriptIMonoSound::IsMonoSound(lua_State* L) {

  if (ScriptSystem::CheckStackSize(L, "IsMonoSound", 1))
    return 0;

  if (!sound) {
    logger.info << "IMonoSound not proberbly initialized. Call aborted."
		<< logger.end;
    return 0;
  }

  lua_pushboolean(L, true);
  return 1;

}

int ScriptIMonoSound::SetMaxDistance(lua_State* L) {

  if (ScriptSystem::CheckStackSize(L, "SetMaxDistanc", 2) ||
      ScriptSystem::CheckArgType(L, "SetMaxDistanc", 'd', 1, -1))
    return 0;

  if (!sound) {
    logger.info << "IMonoSound not proberbly initialized. Call aborted."
		<< logger.end;
    return 0;
  }

  float newdis = lua_tonumber(L, -1);
  sound->SetMaxDistance(newdis);
  return 0;

}

int ScriptIMonoSound::GetMaxDistance(lua_State* L) {

  if (ScriptSystem::CheckStackSize(L, "GetMaxDistance", 1))
    return 0;

  if (!sound) {
    logger.info << "IMonoSound not proberbly initialized. Call aborted."
		<< logger.end;
    return 0;
  }

  float dis = sound->GetMaxDistance();
  lua_pushnumber(L, dis);
  return 1;

}

int ScriptIMonoSound::IsPlaying(lua_State* L) {

  if (ScriptSystem::CheckStackSize(L, "IsPlaying", 1))
    return 0;

  if (!sound) {
    logger.info << "IMonoSound not proberbly initialized. Call aborted."
		<< logger.end;
    return 0;
  }

  bool b = sound->IsPlaying();
  lua_pushboolean(L, b);
  return 1;

}

int ScriptIMonoSound::Play(lua_State* L) {

  if (ScriptSystem::CheckStackSize(L, "Play", 1))
    return 0;

  if (!sound) {
    logger.info << "IMonoSound not proberbly initialized. Call aborted."
		<< logger.end;
    return 0;
  }

  sound->Play();
  return 0;

}

int ScriptIMonoSound::Stop(lua_State* L) {

  if (ScriptSystem::CheckStackSize(L, "Stop", 1))
    return 0;

  if (!sound) {
    logger.info << "IMonoSound not proberbly initialized. Call aborted."
		<< logger.end;
    return 0;
  }

  sound->Stop();
  return 0;

}

int ScriptIMonoSound::Pause(lua_State* L) {

  if (ScriptSystem::CheckStackSize(L, "Pause", 1))
    return 0;

  if (!sound) {
    logger.info << "IMonoSound not proberbly initialized. Call aborted."
		<< logger.end;
    return 0;
  }

  sound->Pause();
  return 0;

}

int ScriptIMonoSound::SetLooping(lua_State* L) {

  if (ScriptSystem::CheckStackSize(L, "SetLooping", 2) ||
      ScriptSystem::CheckArgType(L, "SetLooping", 'b', 1, -1))
    return 0;

  if (!sound) {
    logger.info << "IMonoSound not proberbly initialized. Call aborted."
		<< logger.end;
    return 0;
  }

  bool b = lua_toboolean(L, -1);
  sound->SetLooping(b);
  return 0;

}

int ScriptIMonoSound::GetLooping(lua_State* L) {

  if (ScriptSystem::CheckStackSize(L, "GetLooping", 1))
    return 0;

  if (!sound) {
    logger.info << "IMonoSound not proberbly initialized. Call aborted."
		<< logger.end;
    return 0;
  }

  bool b = sound->GetLooping();
  lua_pushboolean(L, b);
  return 1;

}

int ScriptIMonoSound::SetGain(lua_State* L) {

  if (ScriptSystem::CheckStackSize(L, "SetGain", 2) ||
      ScriptSystem::CheckArgType(L, "SetGain", 'd', 1, -1))
    return 0;

  if (!sound) {
    logger.info << "IMonoSound not proberbly initialized. Call aborted."
		<< logger.end;
    return 0;
  }

  float newgain = lua_tonumber(L, -1);
  sound->SetGain(newgain);
  return 0;

}

int ScriptIMonoSound::GetGain(lua_State* L) {

  if (ScriptSystem::CheckStackSize(L, "GetGain", 1))
    return 0;

  if (!sound) {
    logger.info << "IMonoSound not proberbly initialized. Call aborted."
		<< logger.end;
    return 0;
  }

  float gain = sound->GetGain();
  lua_pushnumber(L, gain);
  return 1;

}

int ScriptIMonoSound::GetLengthInSamples(lua_State* L) {

  if (ScriptSystem::CheckStackSize(L, "GetLengthInSamples", 1))
    return 0;

  if (!sound) {
    logger.info << "IMonoSound not proberbly initialized. Call aborted."
		<< logger.end;
    return 0;
  }

  unsigned int length = sound->GetLengthInSamples();
  lua_pushinteger(L, length);
  return 1;

}

int ScriptIMonoSound::GetLength(lua_State* L) {

  if (ScriptSystem::CheckStackSize(L, "GetLength", 1))
    return 0;

  if (!sound) {
    logger.info << "IMonoSound not proberbly initialized. Call aborted."
		<< logger.end;
    return 0;
  }

  Time t = sound->GetLength();
  lua_pushlightuserdata(L, &t);
  return 1;

}

int ScriptIMonoSound::SetElapsedSamples(lua_State* L) {

  if (ScriptSystem::CheckStackSize(L, "SetElapsedSamples", 2) ||
      ScriptSystem::CheckArgType(L, "SetElapsedSamples", 'i', 1, -1))
    return 0;

  if (!sound) {
    logger.info << "IMonoSound not proberbly initialized. Call aborted."
		<< logger.end;
    return 0;
  }

  unsigned int i = lua_tointeger(L, -1);
  sound->SetElapsedSamples(i);
  return 0;

}

int ScriptIMonoSound::GetElapsedSamples(lua_State* L) {

  if (ScriptSystem::CheckStackSize(L, "GetElapsedSamples", 1))
    return 0;

  if (!sound) {
    logger.info << "IMonoSound not proberbly initialized. Call aborted."
		<< logger.end;
    return 0;
  }

  unsigned int i = sound->GetElapsedSamples();
  lua_pushinteger(L, i);
  return 1;

}

int ScriptIMonoSound::SetElapsedTime(lua_State* L) {

  if (ScriptSystem::CheckStackSize(L, "SetElapsedTime", 2) ||
      ScriptSystem::CheckArgType(L, "SetElapsedTime", 'p', 1, -1))
    return 0;

  if (!sound) {
    logger.info << "IMonoSound not proberbly initialized. Call aborted."
		<< logger.end;
    return 0;
  }

  Time* t = (Time*) lua_touserdata(L, -1);
  sound->SetElapsedTime(*t);
  return 0;

}

int ScriptIMonoSound::GetElapsedTime(lua_State* L) {

  if (ScriptSystem::CheckStackSize(L, "GetElapsedTime", 1))
    return 0;

  if (!sound) {
    logger.info << "IMonoSound not proberbly initialized. Call aborted."
		<< logger.end;
    return 0;
  }

  Time t = sound->GetElapsedTime();
  lua_pushlightuserdata(L, &t);
  return 1;

}

int ScriptIMonoSound::SetVelocity(lua_State* L) {

  if (ScriptSystem::CheckStackSize(L, "SetVelocity", 2) ||
      ScriptSystem::CheckArgType(L, "SetVelocity", 'p', 1, -1))
    return 0;

  if (!sound) {
    logger.info << "IMonoSound not proberbly initialized. Call aborted."
		<< logger.end;
    return 0;
  }

  Vector<3,float>* vec = (Vector<3,float>*) lua_touserdata(L, -1);
  sound->SetVelocity(*vec);
  return 0;

}

int ScriptIMonoSound::GetVelocity(lua_State* L) {

  if (ScriptSystem::CheckStackSize(L, "GetVelocity", 1))
    return 0;

  if (!sound) {
    logger.info << "IMonoSound not proberbly initialized. Call aborted."
		<< logger.end;
    return 0;
  }

  Vector<3, float> vec = sound->GetVelocity();
  lua_pushlightuserdata(L, &vec);
  return 1;

}

int ScriptIMonoSound::GetPosition(lua_State* L) {

  if (ScriptSystem::CheckStackSize(L, "GetPosition", 1))
    return 0;

  if (!sound) {
    logger.info << "IMonoSound not proberbly initialized. Call aborted."
		<< logger.end;
    return 0;
  }

  Vector<3, float> vec = sound->GetPosition();
  lua_pushlightuserdata(L, &vec);
  return 1;

}

int ScriptIMonoSound::SetPosition(lua_State* L) {

  if (ScriptSystem::CheckStackSize(L, "SetPosition", 2) ||
      ScriptSystem::CheckArgType(L, "SetPosition", 'p', 1, -1))
    return 0;

  if (!sound) {
    logger.info << "IMonoSound not proberbly initialized. Call aborted."
		<< logger.end;
    return 0;
  }

  Vector<3, float>* vec = (Vector<3, float>*) lua_touserdata(L, -1);
  sound->SetPosition(*vec);
  return 0;

}

int ScriptIMonoSound::SetRelativePosition(lua_State* L) {

  if (ScriptSystem::CheckStackSize(L, "SetRelativePosition", 2) ||
      ScriptSystem::CheckArgType(L, "SetRelativePosition", 'b', 1, -1))
    return 0;

  if (!sound) {
    logger.info << "IMonoSound not proberbly initialized. Call aborted."
		<< logger.end;
    return 0;
  }

  bool b = lua_toboolean(L, -1);
  sound->SetRelativePosition(b);
  return 0;

}

int ScriptIMonoSound::GetResource(lua_State* L) {

  if (ScriptSystem::CheckStackSize(L, "GetResource", 1))
    return 0;

  if (!sound) {
    logger.info << "IMonoSound not proberbly initialized. Call aborted."
		<< logger.end;
    return 0;
  }

  ISoundResourcePtr p = sound->GetResource();
  lua_pushlightuserdata(L, &p);
  return 1;

}

int ScriptIMonoSound::GetTimeLeft(lua_State* L) {

  if (ScriptSystem::CheckStackSize(L, "GetTimeLeft", 1))
    return 0;

  if (!sound) {
    logger.info << "IMonoSound not proberbly initialized. Call aborted."
		<< logger.end;
    return 0;
  }

  Time t = sound->GetTimeLeft();
  lua_pushlightuserdata(L, &t);
  return 1;

}

int ScriptIMonoSound::IsAtEnd(lua_State* L) {

  if (ScriptSystem::CheckStackSize(L, "IsAtEnd", 1))
    return 0;

  if (!sound) {
    logger.info << "IMonoSound not proberbly initialized. Call aborted."
		<< logger.end;
    return 0;
  }

  bool b = sound->IsAtEnd();
  lua_pushboolean(L, b);
  return 1;

}
