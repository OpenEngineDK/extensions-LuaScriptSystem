
#include "ScriptMusicPlayer.h"

ScriptMusicPlayer::ScriptMusicPlayer(lua_State* L) {

  if (ScriptSystem::CheckStackSize(L, "MusicPlayer", 2) ||
      ScriptSystem::CheckArgType(L, "MusicPlayer", 'p', 1, -2) ||
      ScriptSystem::CheckArgType(L, "MusicPlayer", 'p', 2, -1))
    return;

  Camera* cam = (Camera*) lua_touserdata(L, -2);
  ISoundSystem* sounds = (ISoundSystem*) lua_touserdata(L, -1);

  player = new MusicPlayer(cam, sounds);

}

int ScriptMusicPlayer::AddSound(lua_State* L) {

  if (ScriptSystem::CheckStackSize(L, "MusicPlayer", 2) ||
      ScriptSystem::CheckArgType(L, "MusicPlayer", 's', 1, -1))
    return 0;

  if (!player) {
    logger.info << "MusicPlayer is not proberbly initialized. Call Aborted."
		<< logger.end;
  }

  string file = lua_tostring(L, -1);
  player->AddSound(file);
  return 0;

}

int ScriptMusicPlayer::Previous(lua_State* L) {

  if (ScriptSystem::CheckStackSize(L, "Previous", 1))
    return 0;

  if (!player) {
    logger.info << "MusicPlayer is not proberbly initialized. Call Aborted."
		<< logger.end;
  }

  player->Previous();
  return 0;

}

int ScriptMusicPlayer::Next(lua_State* L) {

  if (ScriptSystem::CheckStackSize(L, "Next", 1))
    return 0;

  if (!player) {
    logger.info << "MusicPlayer is not proberbly initialized. Call Aborted."
		<< logger.end;
  }

  player->Next();
  return 0;

}

int ScriptMusicPlayer::SwitchTo(lua_State* L) {

  if (ScriptSystem::CheckStackSize(L, "SwitchTo", 2) ||
      ScriptSystem::CheckArgType(L, "SwitchTo", 'i', 1, -1))
    return 0;

  if (!player) {
    logger.info << "MusicPlayer is not proberbly initialized. Call Aborted."
		<< logger.end;
  }

  unsigned int index = (unsigned int) lua_tointeger(L, -1);
  player->SwitchTo(index);
  return 0;

}

int ScriptMusicPlayer::NumberOfTracks(lua_State* L) {

  if (ScriptSystem::CheckStackSize(L, "NumberOfTracks", 1))
    return 0;

  if (!player) {
    logger.info << "MusicPlayer is not proberbly initialized. Call Aborted."
		<< logger.end;
  }

  unsigned int num = player->NumberOfTracks();
  lua_pushnumber(L, num);
  return 1;

}

int ScriptMusicPlayer::Play(lua_State* L) {

  if (ScriptSystem::CheckStackSize(L, "Play", 1))
    return 0;

  if (!player) {
    logger.info << "MusicPlayer is not proberbly initialized. Call Aborted."
		<< logger.end;
  }

  player->Play();
  return 0;

}

int ScriptMusicPlayer::Stop(lua_State* L) {

  if (!player) {
    logger.info << "MusicPlayer is not proberbly initialized. Call Aborted."
		<< logger.end;
  }

  player->Stop();
  return 0;

}

int ScriptMusicPlayer::Pause(lua_State* L) {

  if (ScriptSystem::CheckStackSize(L, "Pause", 1))
    return 0;

  if (!player) {
    logger.info << "MusicPlayer is not proberbly initialized. Call Aborted."
		<< logger.end;
  }

  player->Pause();
  return 0;

}

int ScriptMusicPlayer::Shuffle(lua_State* L) {

  if (ScriptSystem::CheckStackSize(L, "Shuffle", 2) ||
      ScriptSystem::CheckArgType(L, "Shuffle", 'b', 1, -1))
    return 0;

  if (!player) {
    logger.info << "MusicPlayer is not proberbly initialized. Call Aborted."
		<< logger.end;
  }

  bool con = lua_toboolean(L, -1);
  player->Shuffle(con);
  return 0;

}

int ScriptMusicPlayer::SetTransitionMode(lua_State* L) {

  if (ScriptSystem::CheckStackSize(L, "SetTransitionMode", 2) ||
      ScriptSystem::CheckArgType(L, "SetTransitionMode", 'p', 1, -1))
    return 0;

  if (!player) {
    logger.info << "MusicPlayer is not proberbly initialized. Call Aborted."
		<< logger.end;
  }

  ITransitionMode* mode = (ITransitionMode*) lua_touserdata(L, -1);
  player->SetTransitionMode(mode);
  return 0;

}	

int ScriptMusicPlayer::SetGain(lua_State* L) {

  if (ScriptSystem::CheckStackSize(L, "SetGain", 2) ||
      ScriptSystem::CheckArgType(L, "SetGain", 'd', 1, -1))
    return 0;

  if (!player) {
    logger.info << "MusicPlayer is not proberbly initialized. Call Aborted."
		<< logger.end;
  }

  float newval = lua_tonumber(L, -1);
  player->SetGain(newval);
  return 0;

}

int ScriptMusicPlayer::GetGain(lua_State* L) {

  if (ScriptSystem::CheckStackSize(L, "GetGain", 1))
    return 0;

  if (!player) {
    logger.info << "MusicPlayer is not proberbly initialized. Call Aborted."
		<< logger.end;
  }

  float val = player->GetGain();
  lua_pushnumber(L, val);
  return 1;

}

int ScriptMusicPlayer::GetMusicPlayer(lua_State* L) {

  if (ScriptSystem::CheckStackSize(L, "GetGain", 1))
    return 0;

  if (!player) {
    logger.info << "MusicPlayer is not proberbly initialized. Call Aborted."
		<< logger.end;
  }

  lua_pushlightuserdata(L, player);
  return 1;

}
