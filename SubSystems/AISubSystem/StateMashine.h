
#ifndef statemashine_h
#define statemashine_h

#include "../../LuaHeader.h"
#include "../../CPPToLuaBinder.h"
#include "../../ScriptSystem.h"

#include <map>
#include <string.h>

using namespace std;

class StateMashine {

 private:
  map<string, void*> states;
  map<string, void*>::iterator it;
  pair<string, void*> state;

 public:
  
  //c++ side
  StateMashine();
  void AddState(string name, void* data);
  void GotoState(string name);
  string CurrentState();
  void* GetData();

  //script
  StateMashine(lua_State* L);
  int AddState(lua_State* L);
  int GotoState(lua_State* L);
  int CurrentState(lua_State* L);
  int GetData(lua_State* L);
  int GetStateMashine(lua_State* L);

  static string classname;
  static CPPToLuaBinder<StateMashine>::RegType Register[];

};

#endif
