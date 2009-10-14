
#ifndef storyp_h
#define storyp_h

#include "../../LuaHeader.h"
#include "../../ScriptSystem.h"
#include "../../CPPToLuaBinder.h"
class MileStone;

#include <map>
#include <string.h>

using namespace std;

class StoryP {

 private:
  map<string, MileStone*> milestones;
  map<string, MileStone*>::iterator it;

 public:

  //c++ side
  StoryP();
  void AddMileStone(string name, MileStone* s);
  void DeleteMileStone(string name);
  MileStone* GetMileStone(string name);
  bool IsReached(string name);
  void* GetData(string name);
  void Mark(string name);

  //script side
  StoryP(lua_State* L);
  int AddMileStone(lua_State* L);
  int DeleteMileStone(lua_State* L);
  int GetMileStone(lua_State* L);
  int IsReached(lua_State* L);
  int GetData(lua_State* L);
  int Mark(lua_State* L);
  int GetStoryP(lua_State* L);

  static string classname;
  static CPPToLuaBinder<StoryP>::RegType Register[];

};

#endif
