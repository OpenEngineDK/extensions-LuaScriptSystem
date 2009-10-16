
#include "ScriptBruteTransitionMode.h"

ScriptBruteTransitionMode::ScriptBruteTransitionMode(lua_State* L) {

  if (ScriptSystem::CheckStackSize(L, "BruteTransitionMode", 2) ||
      ScriptSystem::CheckArgType(L, "BruteTransitionMode", 'p', 1, -2) ||
      ScriptSystem::CheckArgType(L, "BruteTransitionMode", 'p', 2, -1))
    return;

  Time* intime = (Time*) lua_touserdata(L, -2);
  Time* outtime = (Time*) lua_touserdata(L, -1);
  trans = new BruteTransitionMode(*intime, *outtime);

}

int ScriptBruteTransitionMode::InitFade(lua_State* L) {

  if (ScriptSystem::CheckStackSize(L, "InitFade", 3) ||
      ScriptSystem::CheckArgType(L, "InitFade", 'p', 1, -2) ||
      ScriptSystem::CheckArgType(L, "InitFade", 'p', 2, -1))
    return 0;

  if (!trans) {
    logger.info << "BruteTransitionMode is not proberbly initialized" 
		<< ". Call aborted." << logger.end;
    return 0;
  }  

  ISound* from = (ISound*) lua_touserdata(L, -2);
  ISound* to = (ISound*) lua_touserdata(L, -1);
  trans->InitFade(from, to);

  return 0;

}

int ScriptBruteTransitionMode::GetInTime(lua_State* L) {

  if (ScriptSystem::CheckStackSize(L, "GetInTime", 1))
    return 0;

  if (!trans) {
    logger.info << "BruteTransitionMode is not proberbly initialized" 
		<< ". Call aborted." << logger.end;
    return 0;
  } 

  Time t = trans->GetInTime();
  lua_pushlightuserdata(L, &t);
  return 1;

}

int ScriptBruteTransitionMode::GetOutTime(lua_State* L) {

  if (ScriptSystem::CheckStackSize(L, "GetOutTime", 1))
    return 0;

  if (!trans) {
    logger.info << "BruteTransitionMode is not proberbly initialized" 
		<< ". Call aborted." << logger.end;
    return 0;
  } 

  Time t = trans->GetOutTime();
  lua_pushlightuserdata(L, &t);
  return 1;

}

int ScriptBruteTransitionMode::Process(lua_State* L) {

  if (ScriptSystem::CheckStackSize(L, "Proces", 1))
    return 0;

  if (!trans) {
    logger.info << "BruteTransitionMode is not proberbly initialized" 
		<< ". Call aborted." << logger.end;
    return 0;
  } 

  trans->Process();
  return 0;

}

int ScriptBruteTransitionMode::IsDone(lua_State* L) {

  if (ScriptSystem::CheckStackSize(L, "IsDone", 1))
    return 0;

  if (!trans) {
    logger.info << "BruteTransitionMode is not proberbly initialized" 
		<< ". Call aborted." << logger.end;
    return 0;
  } 

  bool b = trans->IsDone();
  lua_pushboolean(L, b);
  return 1;

}

int ScriptBruteTransitionMode::Start(lua_State* L) {

  if (ScriptSystem::CheckStackSize(L, "Start", 1))
    return 0;

  if (!trans) {
    logger.info << "BruteTransitionMode is not proberbly initialized" 
		<< ". Call aborted." << logger.end;
    return 0;
  } 

  trans->Start();
  return 0;

}

int ScriptBruteTransitionMode::GetBruteTransitionMode(lua_State* L) {

  if (ScriptSystem::CheckStackSize(L, "GetBruteTransitionMode", 1))
    return 0;

  if (!trans) {
    logger.info << "BruteTransitionMode is not proberbly initialized" 
		<< ". Call aborted." << logger.end;
    return 0;
  } 

  lua_pushlightuserdata(L, trans);
  return 1;

}


