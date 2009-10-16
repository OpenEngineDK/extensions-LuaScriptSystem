
#include "StateMashine.h"

StateMashine::StateMashine() {
  
  state.first = "";
  state.second = NULL;

}

void StateMashine::AddState(string name, void* data) {
 
  it = states.find(name);
 
  if (it == states.end()) 
    states.insert(pair<string, void*>(name, data));
  else
    (*it).second = data;

}

void StateMashine::GotoState(string name) {

  it = states.find(name);

  if (it != states.end()) 
    state = (*it);
  else
    logger.info << "cannot change to state: " << name << " cause it does"
		<< " not exist" << logger.end;

}

string StateMashine::CurrentState() {

  return state.first;

}

void* StateMashine::GetData() {

  return state.second;

}

//-----------------------------------------------------------

StateMashine::StateMashine(lua_State* L) {

  state.first = "";
  state.second = NULL;

}

int StateMashine::AddState(lua_State* L) {

  int nargs = lua_gettop(L);

  string name;
  void* data = NULL;

  if (nargs == 3) {
    name = lua_tostring(L, -2);
    data = lua_touserdata(L, -1);   
  }
  else if (nargs == 2) {
    name = lua_tostring(L, -1);
  }
  else if (nargs < 2) {
    logger.info << "AddState needs aleast one argument but got zero. "
		<< "Signature is:"
		<< " AddState(string name, optional void* data)." 
		<< " Call terminated." << logger.end;
    return 0;
  }
  else {
    logger.info << "Warning: AddState received " << nargs - 1 
		<< " but only needs 2" << logger.end;
    name = lua_tostring(L, -2);
    data = lua_touserdata(L, -1); 
  }

  AddState(name, data);
  return 0;

}

int StateMashine::GotoState(lua_State* L) {

  if (ScriptSystem::CheckStackSize(L, "GotoState", 2) ||
      ScriptSystem::CheckArgType(L, "GotoState", 's', 1, -1))
    return 0;

  string name = lua_tostring(L, -1);
  
  GotoState(name);
  return 0;

}

int StateMashine::CurrentState(lua_State* L) {

  if (ScriptSystem::CheckStackSize(L, "CurrentState", 1))
    return 0;
  
  lua_pushstring(L, CurrentState().c_str());
  return 1;

}

int StateMashine::GetData(lua_State* L) {

  if (ScriptSystem::CheckStackSize(L, "CurrentState", 1))
    return 0;

  lua_pushlightuserdata(L, GetData());
  return 1;

}

int StateMashine::GetStateMashine(lua_State* L) {

   if (ScriptSystem::CheckStackSize(L, "GetStateMashine", 1))
    return 0;

   lua_pushlightuserdata(L, this);
   return 1;
}
