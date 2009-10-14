
#ifndef scriptfollowcamera_h
#define scriptfollowcamera_h

#include "../../LuaHeader.h"
#include "../../CPPToLuaBinder.h"
#include "../../ScriptSystem.h"

#include <Display/FollowCamera.h>
#include <Display/IViewingVolume.h>
#include <Math/Quaternion.h>
#include <Math/Vector.h>

using namespace OpenEngine::Display;
using namespace OpenEngine::Math;

class ScriptFollowCamera {

 private:
  FollowCamera* cam;

 public:

  ScriptFollowCamera(lua_State* L);
  int Move(lua_State* L);
  int LookAt(lua_State* L);
  int Rotate(lua_State* L);
  int SetPosition(lua_State* L);
  int SetDirection(lua_State* L);
  int SignalRendering(lua_State* L);
  int Follow(lua_State* L);
  int GetFollowCamera(lua_State* L);

  static string classname;
  static CPPToLuaBinder<ScriptFollowCamera>::RegType Register[];

};

#endif
