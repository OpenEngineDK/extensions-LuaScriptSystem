
#ifndef milestone_h
#define milestone_h

#include "../../LuaHeader.h"
#include "../../ScriptSystem.h"
#include "../../CPPToLuaBinder.h"

class MileStone {

 private:
  bool reached;
  void* data;

 public:
  
  //c++ side
  MileStone(void* d = NULL);
  bool IsReached();
  void Mark();
  void* GetData();
  void SetData(void* d);

  //script side
  MileStone(lua_State* L);
  int IsReached(lua_State* L);
  int Mark(lua_State* L);
  int GetData(lua_State* L);
  int SetData(lua_State* L);
  int GetMileStone(lua_State* L);

  static string classname;
  static CPPToLuaBinder<MileStone>::RegType Register[];

};

#endif
