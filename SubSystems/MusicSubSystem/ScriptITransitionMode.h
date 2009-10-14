
#ifndef scriptitransitionmode_h
#define scriptitransitionmode_h

#include <Sound/ITransitionMode.h>
#include <Sound/ISound.h>
#include <Utils/Timer.h>
#include "../../LuaHeader.h"
#include "../../CPPToLuaBinder.h"
#include "../../ScriptSystem.h"

using namespace OpenEngine::Sound;
using OpenEngine::Utils::Time;

class ScriptITransitionMode {

 private:
  ITransitionMode* trans;

 public:
  ScriptITransitionMode(lua_State* L);
  int InitFade(lua_State* L);
  int GetInTime(lua_State* L);
  int GetOutTime(lua_State* L);
  int Process(lua_State* L);
  int IsDone(lua_State* L);
  int Start(lua_State* L);

  static string classname;
  static CPPToLuaBinder<ScriptITransitionMode>::RegType Register[];

};

#endif
