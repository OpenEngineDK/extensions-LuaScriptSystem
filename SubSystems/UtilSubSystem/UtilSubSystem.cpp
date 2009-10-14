
#include "UtilSubSystem.h"

string ScriptTimer::classname = "Timer";
CPPToLuaBinder<ScriptTimer>::RegType ScriptTimer::Register[] = {
  {"Start", &ScriptTimer::Start},
  {"Stop", &ScriptTimer::Stop},
  {"Reset", &ScriptTimer::Reset},
  {"GetElapsedTime", &ScriptTimer::GetElapsedTime},
  {"GetElapsedTimeAndReset", &ScriptTimer::GetElapsedTimeAndReset},
  {"GetElapsedIntervals", &ScriptTimer::GetElapsedIntervals},
  {"GetElapsedIntervalsAndReset", &ScriptTimer::GetElapsedIntervalsAndReset},
  {"IsRunning", &ScriptTimer::IsRunning},
  {"GetTime", &ScriptTimer::GetTime}
};

int ActivateUtilSubSystem(lua_State* L) {

  if (ScriptSystem::CheckStackSize(L, "ActivateUtilsSubSystem", 0))
    return 0;

  ScriptSystem::RegisterClass<ScriptTimer>();

  return 0;

}
