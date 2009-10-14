
#ifndef Scripttimer_h
#define Scripttimer_h

#include <Utils/Timer.h>
#include "../../ScriptSystem.h"
#include "../../LuaHeader.h"
#include "../../CPPToLuaBinder.h"

using OpenEngine::Utils::Timer;

class ScriptTimer {

 private:
  Timer t;

 public:
  ScriptTimer(lua_State* L);
  ~ScriptTimer();
  int Start(lua_State* L);
  int Stop(lua_State* L);
  int Reset(lua_State* L);
  int GetElapsedTime(lua_State* L);
  int GetElapsedTimeAndReset(lua_State* L);
  int GetElapsedIntervals(lua_State* L);
  int GetElapsedIntervalsAndReset(lua_State* L);
  int IsRunning(lua_State* L);
  int GetTime(lua_State* L);

  static string classname;
  static CPPToLuaBinder<ScriptTimer>::RegType Register[];

};

#endif
