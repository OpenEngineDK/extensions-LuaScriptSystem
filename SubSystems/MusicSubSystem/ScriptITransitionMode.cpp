
#include "ScriptITransitionMode.h"

ScriptITransitionMode::ScriptITransitionMode(lua_State* L) {

  if (ScriptSystem::CheckStackSize(L, "ITransitionMode", 1) ||
      ScriptSystem::CheckArgType(L, "ITransitionMode", "userdata", 1, -1))
    return;

  trans = (ITransitionMode*) lua_touserdata(L, -1);

}

int ScriptITransitionMode::InitFade(lua_State* L) {

  if (ScriptSystem::CheckStackSize(L, "InitFade", 3) ||
      ScriptSystem::CheckArgType(L, "InitFade", "userdata", 1, -2) ||
      ScriptSystem::CheckArgType(L, "InitFade", "userdata", 2, -1))
    return 0;

  if (!trans) {
    logger.info << "ITransitionMode is not proberbly initialized" 
		<< ". Call aborted." << logger.end;
    return 0;
  } 

  ISound* from = (ISound*) lua_touserdata(L, -2);
  ISound* to = (ISound*) lua_touserdata(L, -1);
  trans->InitFade(from, to);

  return 0;

}

int ScriptITransitionMode::GetInTime(lua_State* L) {

  if (ScriptSystem::CheckStackSize(L, "GetInTime", 1))
    return 0;

  if (!trans) {
    logger.info << "ITransitionMode is not proberbly initialized" 
		<< ". Call aborted." << logger.end;
    return 0;
  } 

  Time t = trans->GetInTime();
  lua_pushlightuserdata(L, &t);
  return 1;

}

int ScriptITransitionMode::GetOutTime(lua_State* L) {

  if (ScriptSystem::CheckStackSize(L, "GetOutTime", 1))
    return 0;

  if (!trans) {
    logger.info << "ITransitionMode is not proberbly initialized" 
		<< ". Call aborted." << logger.end;
    return 0;
  } 

  Time t = trans->GetOutTime();
  lua_pushlightuserdata(L, &t);
  return 1;

}

int ScriptITransitionMode::Process(lua_State* L) {

  if (ScriptSystem::CheckStackSize(L, "Proces", 1))
    return 0;

  if (!trans) {
    logger.info << "ITransitionMode is not proberbly initialized" 
		<< ". Call aborted." << logger.end;
    return 0;
  } 

  trans->Process();
  return 0;

}

int ScriptITransitionMode::IsDone(lua_State* L) {

  if (ScriptSystem::CheckStackSize(L, "IsDone", 1))
    return 0;

  if (!trans) {
    logger.info << "ITransitionMode is not proberbly initialized" 
		<< ". Call aborted." << logger.end;
    return 0;
  } 

  bool b = trans->IsDone();
  lua_pushboolean(L, b);
  return 1;

}

int ScriptITransitionMode::Start(lua_State* L) {

  if (ScriptSystem::CheckStackSize(L, "Start", 1))
    return 0;

  if (!trans) {
    logger.info << "ITransitionMode is not proberbly initialized" 
		<< ". Call aborted." << logger.end;
    return 0;
  } 

  trans->Start();
  return 0;

}

