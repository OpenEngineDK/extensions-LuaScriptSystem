
#ifndef ScriptOpenALSoundSystem_h
#define ScriptOpenALSoundSystem_h

#include "../../LuaHeader.h"
#include "../../CPPToLuaBinder.h"
#include "../../ScriptSystem.h"
#include <Sound/OpenALSoundSystem.h>
#include <Sound/ISound.h>
#include <Scene/ISceneNode.h>
#include <Display/FollowCamera.h>
#include <Resources/ResourceManager.h>
#include <Resources/ISoundResource.h>

using namespace OpenEngine::Display;
using namespace OpenEngine::Sound;
using namespace OpenEngine::Resources;

class ScriptOpenALSoundSystem {

 private:
  OpenALSoundSystem* sounds;

 public:

  ScriptOpenALSoundSystem(lua_State* L);
  ~ScriptOpenALSoundSystem();
  int CreateSound(lua_State* L);
  int SetRoot(lua_State* L);
  int SetMasterGain(lua_State* L);
  int GetMasterGain(lua_State* L);
  int GetOpenALSoundSystem(lua_State* L);

  static string classname;
  static CPPToLuaBinder<ScriptOpenALSoundSystem>::RegType Register[];

};

#endif
