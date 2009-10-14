
#ifndef scriptbrutetransitionmode_h
#define scriptbrutetransitionmode_h

#include <Sound/BruteTransitionMode.h>
#include <Sound/ISound.h>
#include <Utils/Timer.h>
#include "../../LuaHeader.h"
#include "../../CPPToLuaBinder.h"
#include "../../ScriptSystem.h"
#include <Logging/Logger.h>

using namespace OpenEngine::Sound;
using OpenEngine::Utils::Time;

class ScriptBruteTransitionMode {

 private:
  BruteTransitionMode* trans;

 public:
  ScriptBruteTransitionMode(lua_State* L);
  int InitFade(lua_State* L);
  int GetInTime(lua_State* L);
  int GetOutTime(lua_State* L);
  int Process(lua_State* L);
  int IsDone(lua_State* L);
  int Start(lua_State* L);
  int GetBruteTransitionMode(lua_State* L);

  static string classname;
  static CPPToLuaBinder<ScriptBruteTransitionMode>::RegType Register[];

};

#endif
