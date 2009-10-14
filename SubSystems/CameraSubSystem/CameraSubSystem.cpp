
#include "CameraSubSystem.h"

string ScriptCamera::classname = "Camera";
CPPToLuaBinder<ScriptCamera>::RegType ScriptCamera::Register[] = {
  {"SetDirection", &ScriptCamera::SetDirection},
  {"Move", &ScriptCamera::Move},
  {"LookAt", &ScriptCamera::LookAt},
  {"Rotate", &ScriptCamera::Rotate},
  {"GetCamera", &ScriptCamera::GetCamera}
};

string ScriptFollowCamera::classname = "FollowCamera";
CPPToLuaBinder<ScriptFollowCamera>::RegType ScriptFollowCamera::Register[] = {
  {"Move", &ScriptFollowCamera::Move},
  {"LookAt", &ScriptFollowCamera::LookAt},
  {"Rotate", &ScriptFollowCamera::Rotate},
  {"SetPosition", &ScriptFollowCamera::SetPosition},
  {"SetDirection", &ScriptFollowCamera::SetDirection},
  {"SignalRendering", &ScriptFollowCamera::SignalRendering},
  {"Follow", &ScriptFollowCamera::Follow},
  {"GetFollowCamera", &ScriptFollowCamera::GetFollowCamera}
};

int ActivateCameraSubSystem(lua_State* L) {

  if (ScriptSystem::CheckStackSize(L, "ActivateCameraSubSystem", 0))
    return 0;

  ScriptSystem::RegisterClass<ScriptCamera>();
  ScriptSystem::RegisterClass<ScriptFollowCamera>();

  return 0;

}
