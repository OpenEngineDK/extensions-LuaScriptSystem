
#ifndef ScriptMusicPlayer_h
#define ScriptMusicPlayer_h

#include "../../LuaHeader.h"
#include "../../ScriptSystem.h"
#include "../../CPPToLuaBinder.h"
#include <Sound/MusicPlayer.h>
#include <Display/Camera.h>
#include <Sound/ITransitionMode.h>
#include <Logging/Logger.h>

using namespace OpenEngine::Display;
using namespace OpenEngine::Sound;

class ScriptMusicPlayer {

 private:
  MusicPlayer* player;

 public:

  ScriptMusicPlayer(lua_State* L);
  int AddSound(lua_State* L);
  int Previous(lua_State* L);
  int Next(lua_State* L);
  int SwitchTo(lua_State* L);
  int NumberOfTracks(lua_State* L);
  int Play(lua_State* L);
  int Stop(lua_State* L);
  int Pause(lua_State* L);
  int Shuffle(lua_State* L);
  int SetTransitionMode(lua_State* L);	
  int SetGain(lua_State* L);
  int GetGain(lua_State* L);
  int GetMusicPlayer(lua_State* L);

  static string classname;
  static CPPToLuaBinder<ScriptMusicPlayer>::RegType Register[];

};

#endif
