
#include "MileStone.h"

MileStone::MileStone(void* d) {

  reached = false;
  if (d != NULL)
    data = d;

}

bool MileStone::IsReached() {
  
  return reached;

}

void MileStone::Mark() {

  reached = true;

}

void* MileStone::GetData() {

  return data;

}

void MileStone::SetData(void* d) {
  
  data = d;

}

//---------------------------------------------

MileStone::MileStone(lua_State* L) {

  reached = false;

  int args = lua_gettop(L);

  //ok there is a data pointer 
  if (args == 1) 
    data = lua_touserdata(L, -1);
  else if (args > 1)
    logger.info << "Warning MileStone given more arguments than needed."
		<< logger.end;

}

int MileStone::IsReached(lua_State* L) {

  if (ScriptSystem::CheckStackSize(L, "IsReached", 1))
    return 0;

  lua_pushboolean(L, reached);
  return 1;

}

int MileStone::Mark(lua_State* L) {

  if (ScriptSystem::CheckStackSize(L, "Mark", 1))
    return 0;

  reached = true;
  return 0;

}

int MileStone::GetData(lua_State* L) {

  if (ScriptSystem::CheckStackSize(L, "GetData", 1))
    return 0;

  lua_pushlightuserdata(L, data);
  return 1;

}

int MileStone::SetData(lua_State* L) {

  if (ScriptSystem::CheckStackSize(L, "SetData", 2) ||
      ScriptSystem::CheckArgType(L, "SetData", 'p', 1, -1))
    return 0;

  data = lua_touserdata(L, -1);
  return 0;

}

int MileStone::GetMileStone(lua_State* L) {

  if (ScriptSystem::CheckStackSize(L, "GetMileStone", 1))
    return 0;

  lua_pushlightuserdata(L, this);
  return 1;

}
