
#ifndef ScriptISound_h
#define ScriptISound_h

#include <Sound/ISound.h>
#include <Utils/Timer.h>
#include "../../LuaHeader.h"
#include "../../CPPToLuaBinder.h"
#include "../../ScriptSystem.h"

using namespace OpenEngine::Sound;
using OpenEngine::Utils::Time;

class ScriptISound {

 private:
  ISound* sound;

 public:

  ScriptISound(lua_State* L);
  int IsStereoSound(lua_State* L);
  int IsMonoSound(lua_State* L);
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
  int GetTimeLeft(lua_State* L);
  int IsAtEnd(lua_State* L);

  static string classname;
  static CPPToLuaBinder<ScriptISound>::RegType Register[];

};

#endif
