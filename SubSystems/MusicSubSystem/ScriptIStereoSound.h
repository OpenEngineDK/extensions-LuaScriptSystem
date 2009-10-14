
#ifndef ScriptIStereoSound_h
#define ScriptIStereoSound_h

#include "../../LuaHeader.h"
#include <Sound/IStereoSound.h>
#include <string.h>
#include "../../CPPToLuaBinder.h"
#include "../../ScriptSystem.h"

using namespace std;
using namespace OpenEngine::Sound;

class ScriptIStereoSound {

 private:
  IStereoSound* sound;

 public:  
  ScriptIStereoSound(lua_State* L);
  int GetLeft(lua_State* L);
  int GetRight(lua_State* L);
  int IsStereoSound(lua_State* L);
  int IsMonoSound(lua_State* L);

  static string classname;
  static CPPToLuaBinder<ScriptIStereoSound>::RegType Register[];

};

#endif
