
#ifndef ParticleSubSystem_h
#define ParticleSubSystem_h

#include "../../LuaHeader.h"
#include <ParticleSystem/ParticleSystem.h>
#include "../../CPPToLuaBinder.h"
#include <Logging/Logger.h>
class ScriptSystem;

int ActivateParticleSubSystem(lua_State* L);

class ParticleSubSystem {

 public:
  ParticleSubSystem();
  int GetParticleSystem(lua_State* L);

  static string classname;
  static CPPToLuaBinder<ParticleSubSystem>::RegType Register[];

};

#endif
