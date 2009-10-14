
#ifndef LuaListener_h
#define LuaListener_h

#include <Core/IListener.h>
#include <string>
#include <vector>
using namespace std;
using OpenEngine::Core::IListener;

#include "ScriptSystem.h"

struct CallInfo {

  string scriptname;
  string funcname;
  string stackid;
  
  CallInfo(string sn, string fn, string st): scriptname(sn), 
    funcname(fn), stackid(st) {}; 

};

class ILuaListener {

 public:
  virtual void AddScript(string scriptname, string funcname, string stackid) = 0;
  virtual void AddScript(string scriptname, string stackid) = 0;
  virtual bool IsAttached() = 0;
  virtual void Mark() = 0;

};

template <typename EventArg>
class LuaListener : public IListener<EventArg>, public ILuaListener {

 private:
  vector<CallInfo*> hookedupscripts;
  static LuaListener<EventArg>* lis;
  bool isatt;
 
  LuaListener() {
    isatt = false;
  }

 public:
  ~LuaListener() {
    
    for (unsigned int i = 0; i < hookedupscripts.size(); i++) {

      delete hookedupscripts[i]; 

    }

  }

  static LuaListener<EventArg>* GetListener() {

    if (lis == NULL) {
      lis = new LuaListener<EventArg>();
    }
   
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
      else {
	ScriptSystem::RunScript(scriptname, stackid);
      }
      
    }
    
  }

  void AddScript(string scriptname, string funcname, string stackid) {
    
    //make the info struct
    CallInfo* info = new CallInfo(scriptname, funcname, stackid);

    hookedupscripts.push_back(info);

  }

  void AddScript(string scriptname, string stackid) {

    //make the info struct
    CallInfo* info = new CallInfo(scriptname, "", stackid);

    hookedupscripts.push_back(info);

  }

  bool IsAttached() {
    
    return isatt;

  }

  void Mark() {

    isatt = true;

  }
};

template <typename EventArg> LuaListener<EventArg>* LuaListener<EventArg>::lis;

#endif
