
#ifndef ScriptISoundSystem_h
#define ScriptISoundSystem_h

#include "../../LuaHeader.h"
#include "../../CPPToLuaBinder.h"
#include "../../ScriptSystem.h"
#include <Sound/ISoundSystem.h>
#include <Scene/ISceneNode.h>
#include <Sound/ISound.h>
#include <Resources/ResourceManager.h>
#include <Resources/ISoundResource.h>
#include <string.h>

using namespace std;
using namespace OpenEngine::Sound;
using OpenEngine::Scene::ISceneNode;
using namespace OpenEngine::Resources;

class ScriptISoundSystem {

 private:
  ISoundSystem* sys;

 public:

  ScriptISoundSystem(lua_State* L);
  int CreateSound(lua_State* L);
  int SetRoot(lua_State* L);
  int SetMasterGain(lua_State* L);
  int GetMasterGain(lua_State* L);

  static string classname;
  static CPPToLuaBinder<ScriptISoundSystem>::RegType Register[];

};

#endif
