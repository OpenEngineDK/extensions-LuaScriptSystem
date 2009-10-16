
//xmacro, pattern

#ifndef LuaScriptSystem_h
#define LuaScriptSystem_h

#include <Logging/Logger.h>

#include <stdarg.h>
#include <string.h>
#include <map>
#include <Core/EngineEvents.h>
#include <Core/Engine.h>
#include <Math/RandomGenerator.h>
#include "LuaHeader.h"
template <typename EventArg>
class LuaListener;
#include "CPPToLuaBinder.h"
#include "TestStuff/TestFuncs.h"
#include "Attacher.h"
#include "InotifyStuff/definitions.h"

#ifdef _OnLinux_
#include "InotifyStuff/inotify-cxx.h"
#endif

#include "SubSystems/ParticleSubSystem/ParticleSubSystem.h"
#include "SubSystems/MusicSubSystem/MusicSubSystem.h"
#include "SubSystems/StoryProgression/StoryPSubSystem.h"
#include "SubSystems/AISubSystem/AISubSystem.h"
#include "SubSystems/CameraSubSystem/CameraSubSystem.h"
#include "SubSystems/UtilSubSystem/UtilSubSystem.h"

using namespace std;
using namespace OpenEngine::Core;
using OpenEngine::Math::RandomGenerator;

class ScriptSystem {

 private:
  static string libpath;
  static bool initialized;
  static Engine* en;
  static RandomGenerator randgen;
  static map<string, lua_State*> stacks;
  static map<string, bool> watchstatus;

  #ifdef _OnLinux_
  static Inotify notify;
  #endif

  //debug method
  static void ReportErrors(lua_State* L, int status);
  //function to separate init code from register code
  static void RegistreCore(string stackid = "default");

  //helper functions
  static string GetScriptName(string usergivenname);
  static bool CheckIfInit(string name);
  static lua_State* GetStack(string name);
  static void WatchDir(string path);
  static bool CheckFile(string name);
  static void WatchScript(string name);

  //core functions e.g the functions that will be 
  //registered
  static int GetInitAttacher(lua_State* L);
  static int GetDeinitAttacher(lua_State* L);
  static int GetProcessAttacher(lua_State* L);
  static int Attach(lua_State* L);
  static int ListenOnEvent(lua_State* L);
  static int RunScript(lua_State* L);
  static int RunScriptFunc(lua_State* L);
  static int GetRandomInt(lua_State* L);

  //hide the constructor to make sure this class cannot be
  //instanciated
  ScriptSystem();

 public:
  //super level functions e.a the backbone of the
  //scriptsystem
  static bool CheckArgType(lua_State* L, string name, char type, int number, int index);
  static bool CheckStackSize(lua_State* L, string name, int count);
  static void InitScriptSystem(string path, Engine* engine);
  static void DeinitScriptSystem();
  static void RunScript(string scriptname, string stackid = "default");
  static void RunScriptFunc(string scriptname, string funcname, string stackid,
			    string argtypes, string returntypes, 
			    ...);
  static void GetGlobal(string scriptname, string name, char type, void* rval, string stackid = "default");
  static void ChangeScriptDir(string newpath);
  static void RemoveStack(string name);
  static void RemoveStack(lua_State* L);
  static void RegisterNonClassFunc(string name, lua_CFunction func, string stackid = "default");

  template <typename T>
    static void RegisterClass(string stackid = "default") {
    
    if (CheckIfInit("RegisterClass"))
      return;

    //get the stack
    lua_State* L = GetStack(stackid);
    
    CPPToLuaBinder<T>::Register(L);

  }

  template <typename T>
    static void RegisterClassFunc(T* obj, string stackid = "default") {

    if (CheckIfInit("RegisterClassFunc"))
      return;    

    //get the stack
    lua_State* L = GetStack(stackid);

    CPPToLuaBinder<T>::Register(L, obj);
  }

};

#endif
