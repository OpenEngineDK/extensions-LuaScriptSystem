
#ifndef ScriptIMonoSound_h
#define ScriptIMonoSound_h

#include <Sound/IMonoSound.h>
#include "../../LuaHeader.h" 
#include <Utils/Timer.h>
#include <Resources/ISoundResource.h>
#include <Math/Vector.h>
#include "../../CPPToLuaBinder.h"
#include "../../ScriptSystem.h"

using namespace OpenEngine::Sound;
using OpenEngine::Utils::Time;

class ScriptIMonoSound {

 private:
  
  IMonoSound* sound;

 public:

  ScriptIMonoSound(lua_State* L);
  int IsStereoSound(lua_State* L);
  int IsMonoSound(lua_State* L);
  int SetMaxDistance(lua_State* L);
  int GetMaxDistance(lua_State* L);
  int IsPlaying(lua_State* L);  
  int Play(lua_State* L);
  int Stop(lua_State* L);
  int Pause(lua_State* L);
  int SetLooping(lua_State* L);
  int GetLooping(lua_State* L);     
  int SetGain(lua_State* L);
  int GetGain(lua_State* L);
  int GetLengthInSamples(lua_State* L);
  int GetLength(lua_State* L);
  int SetElapsedSamples(lua_State* L);
  int GetElapsedSamples(lua_State* L);
  int SetElapsedTime(lua_State* L);
  int GetElapsedTime(lua_State* L);        
  int SetVelocity(lua_State* L);
  int GetVelocity(lua_State* L);
  int GetPosition(lua_State* L);
  int SetPosition(lua_State* L);
  int SetRelativePosition(lua_State* L);        
  int GetResource(lua_State* L);
  int GetTimeLeft(lua_State* L);
  int IsAtEnd(lua_State* L);
  
  static string classname;
  static CPPToLuaBinder<ScriptIMonoSound>::RegType Register[];
  
};

#endif
