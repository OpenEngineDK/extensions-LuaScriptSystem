
#include "ParticleSubSystem.h"
#include "../../ScriptSystem.h"

string ParticleSubSystem::classname = "ParticleSubSystem";
CPPToLuaBinder<ParticleSubSystem>::RegType ParticleSubSystem::Register[] = {
  {"GetParticleSystem",  &ParticleSubSystem::GetParticleSystem}
  };

int ActivateParticleSubSystem(lua_State* L) {

  if (ScriptSystem::CheckStackSize(L, "ActivateParticleSubSystem", 0))
    return 0;

  ScriptSystem::RegisterClassFunc<ParticleSubSystem>(new ParticleSubSystem());
  
  return 0;
}

ParticleSubSystem::ParticleSubSystem() {
}

int ParticleSubSystem::GetParticleSystem(lua_State* L) {

  if (ScriptSystem::CheckStackSize(L, "GetParticleSystem", 0))
    return 0;

  //create the particlesystem
  OpenEngine::ParticleSystem::ParticleSystem* ps = new OpenEngine::ParticleSystem::ParticleSystem();

  //return it
  lua_pushlightuserdata(L, ps);

  return 1;
}
