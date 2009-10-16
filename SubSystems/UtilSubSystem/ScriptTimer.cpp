
#include "ScriptTimer.h"

ScriptTimer::ScriptTimer(lua_State* L) {
}

ScriptTimer::~ScriptTimer() {
}

int ScriptTimer::Start(lua_State* L) {

  if (ScriptSystem::CheckStackSize(L, "Start", 1))
    return 0;

  t.Start();
  return 0;

}

int ScriptTimer::Stop(lua_State* L) {

  if (ScriptSystem::CheckStackSize(L, "Stop", 1))
    return 0;

  t.Stop();
  return 0;

}

int ScriptTimer::Reset(lua_State* L) {

  if (ScriptSystem::CheckStackSize(L, "Reset", 1))
    return 0;

  t.Reset();
  return 0;

}

int ScriptTimer::GetElapsedTime(lua_State* L) {

  if (ScriptSystem::CheckStackSize(L, "GetElapsedTime", 1))
    return 0;

  Time time = t.GetElapsedTime();
  lua_pushlightuserdata(L, &time);
  return 1;

}

int ScriptTimer::GetElapsedTimeAndReset(lua_State* L) {

  if (ScriptSystem::CheckStackSize(L, "GetElapsedTimeAndReset", 1))
    return 0;

  Time time = t.GetElapsedTimeAndReset();
  lua_pushlightuserdata(L, &time);
  return 1;

}

int ScriptTimer::GetElapsedIntervals(lua_State* L) {

  if (ScriptSystem::CheckStackSize(L, "GetElapsedIntervals", 2) ||
      ScriptSystem::CheckArgType(L, "GetElapsedIntervals", 'i', 1, -1))
    return 0;

  int arg = lua_tointeger(L, -1);
  unsigned int time = t.GetElapsedIntervals(arg);
  lua_pushinteger(L, time);
  return 1;

}

int ScriptTimer::GetElapsedIntervalsAndReset(lua_State* L) {

  if (ScriptSystem::CheckStackSize(L, "GetElapsedIntervalsAndReset", 2) ||
      ScriptSystem::CheckArgType(L, "GetElapsedIntervalsAndReset", 'i', 1, -1))
    return 0;

  int arg = lua_tointeger(L, -1);
  unsigned int time = t.GetElapsedIntervalsAndReset(arg);
  lua_pushinteger(L, time);
  return 1;

}

int ScriptTimer::IsRunning(lua_State* L) {

  if (ScriptSystem::CheckStackSize(L, "IsRunning", 1))
    return 0;

  bool running = t.IsRunning();
  lua_pushboolean(L, running);
  return 1;

}

int ScriptTimer::GetTime(lua_State* L) {

  if (ScriptSystem::CheckStackSize(L, "IsRunning", 1))
    return 0;

  Time time = Timer::GetTime();
  lua_pushlightuserdata(L, &time);
  return 1;

}
