
#ifndef LuaListener_h
#define LuaListener_h

#include "ScriptSystem.h"

#include <string>
#include <vector>

#include <Core/IListener.h>

using std::string;
using OpenEngine::Core::IListener;

class ILuaListener {
 public:
  virtual void AddScript(string stackid, string scriptname,
			 string funcname = "") = 0;
};

template <typename EventArg>
class LuaListener : public IListener<EventArg>, public ILuaListener {
 private:

  class CallInfo {
  public:
    string scriptname, funcname, stackid;    
  CallInfo(string sn, string fn, string st) :
    scriptname(sn), funcname(fn), stackid(st) {}; 
  };

  vector<CallInfo*> hookedupscripts;
  static LuaListener<EventArg>* lis;
 
  LuaListener() {}

 public:
  ~LuaListener() {
    for (unsigned int i = 0; i < hookedupscripts.size(); i++) {
      delete hookedupscripts[i];
    }
  }

  static LuaListener<EventArg>* GetListener() {
    if (lis == NULL)
      lis = new LuaListener<EventArg>();
    return lis;
  }

  void Handle(EventArg arg) {
    for (unsigned int i = 0; i < hookedupscripts.size(); i++) {
      CallInfo* currentinfo = hookedupscripts[i];
      string scriptname = currentinfo->scriptname;
      string funcname = currentinfo->funcname;
      string stackid = currentinfo->stackid;
      
      if (funcname.compare("")) { 
	ScriptSystem::RunScriptFunc(scriptname, 
				    funcname, stackid, "u", 
				    "", &arg, sizeof(arg));	 
      }
      else
	ScriptSystem::RunScript(scriptname, stackid);
    }
  }

  void AddScript(string scriptname, string funcname, string stackid) {
    CallInfo* info = new CallInfo(scriptname, funcname, stackid);
    hookedupscripts.push_back(info);
  }
};

template <typename EventArg> LuaListener<EventArg>* LuaListener<EventArg>::lis;

#endif
