
#ifndef scriptcamera_h
#define scriptcamera_h

#include "../../LuaHeader.h"
#include "../../CPPToLuaBinder.h"
#include "../../ScriptSystem.h"

#include <Display/IViewingVolume.h>
#include <Display/Camera.h>
#include <Math/Quaternion.h>
#include <Math/Vector.h>

using namespace OpenEngine::Display;
using namespace OpenEngine::Math;

class ScriptCamera {

 private:
  Camera* cam;

 public:
  ScriptCamera(lua_State* L);
  int SetDirection(lua_State* L);
  int Move(lua_State* L);
  int LookAt(lua_State* L);
  int Rotate(lua_State* L);
  int GetCamera(lua_State* L);

  static string classname;
  static CPPToLuaBinder<ScriptCamera>::RegType Register[];

};

#endif
