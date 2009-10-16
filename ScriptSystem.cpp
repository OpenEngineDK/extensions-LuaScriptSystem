
#include "ScriptSystem.h"
#include "LuaListener.h"
#include "CPPToLuaBinder.h"

//cpp magic
string ScriptSystem::libpath;
bool ScriptSystem::initialized;
Engine* ScriptSystem::en;
RandomGenerator ScriptSystem::randgen;
map<string, lua_State*> ScriptSystem::stacks;
map<string, bool> ScriptSystem::watchstatus;

#ifdef _OnLinux_
Inotify ScriptSystem::notify;
#endif

string Account::classname = "Account";
CPPToLuaBinder<Account>::RegType Account::Register[] = {
     {"deposit",  &Account::deposit},
     {"withdraw", &Account::withdraw},
     {"balance",  &Account::balance}
};

//the functions
//-------------------------------------------------------

void ScriptSystem::ReportErrors(lua_State* L, int status)
{

  //should make sure system is initialized but it is private
  //and I know what I am doing :))

  if ( status != 0 ) {
    logger.info << "LuaScriptSystem: " << lua_tostring(L, -1) << logger.end;
    lua_pop(L, 1); // remove error message
  }
}

void ScriptSystem::RegistreCore(string stackid) {

  //  RegisterNonClassFunc("PrintPoint", PrintPoint);
  //  RegisterNonClassFunc("ChangePoint", ChangePoint);
  //  RegisterNonClassFunc("CreatePoint", CreatePoint);
  //  RegisterNonClassFunc("PrintString", PrintString);
  RegisterNonClassFunc("ActivateParticleSubSystem",
		       ActivateParticleSubSystem, stackid);
  RegisterNonClassFunc("ActivateMusicSubSystem",
		       ActivateMusicSubSystem, stackid);
  RegisterNonClassFunc("ActivateStoryProgressionSubSystem",
		       ActivateStoryPSubSystem, stackid);
  RegisterNonClassFunc("ActivateAISubSystem",
		       ActivateAISubSystem, stackid);
  RegisterNonClassFunc("ActivateCameraSubSystem",
		       ActivateCameraSubSystem, stackid);
  RegisterNonClassFunc("ActivateUtilSubSystem",
		       ActivateUtilSubSystem, stackid);
  
  //register the scriptsystem core functions
  RegisterNonClassFunc("GetInitAttacher", GetInitAttacher, stackid);
  RegisterNonClassFunc("GetDeinitAttacher", GetDeinitAttacher, stackid);
  RegisterNonClassFunc("GetProcessAttacher", GetProcessAttacher, stackid);
  RegisterNonClassFunc("Attach", Attach, stackid);
  RegisterNonClassFunc("ListenOnEvent",  ListenOnEvent, stackid);  
  RegisterNonClassFunc("RunScript", RunScript, stackid);
  RegisterNonClassFunc("RunScriptFunc", RunScriptFunc, stackid);
  RegisterNonClassFunc("GetRandomInt", GetRandomInt, stackid);

}

string ScriptSystem::GetScriptName(string usergivenname) {

  //should make sure system is initialized but it is private
  //and I know what I am doing :))

  //check to see if we are dealing with a complete
  //path or a relative. Complete path will have a :
  //in the second position
  if (usergivenname.at(0) == '/')
    return usergivenname;
  else
    //concat scriptname to standard library path
    return libpath + usergivenname;

}

bool ScriptSystem::CheckIfInit(string name) {

  //make sure system is initialized
  if (!initialized) {
    logger.info << "ScriptSystem not initialized. "
		<< name << " call aborted." 
		<< logger.end;
    return true;
  }

  return false;

}

lua_State* ScriptSystem::GetStack(string name) {

  map<string, lua_State*>::iterator it;

  it = stacks.find(name);

  //not here so make a new one
  if (it == stacks.end()) {
    lua_State* L = lua_open();
    luaL_openlibs(L);
    stacks.insert(pair<string, lua_State*>(name, L));
    RegistreCore(name);
    return L;
  }
  //return the stored one
  else
    return (*it).second; 

}

void ScriptSystem::WatchDir(string path) {

  #ifdef _OnLinux_
  try {

    InotifyWatch watch(path, IN_CLOSE_WRITE);

    if (notify.FindWatch(watch.GetPath()) == NULL) {
      notify.Add(watch);
    }

  }
  catch (InotifyException &e) {
    //activate if debug information is needed
    //logger.info << "Inotify exception occured: " << e.GetMessage() << logger.end;
  }
  #else
  
  #endif

}

bool ScriptSystem::CheckFile(string name) {

#ifdef _OnLinux_

  map<string, bool>::iterator it; 

  //update status map
  try {

    notify.WaitForEvents();
    InotifyEvent event;      
    bool got_event = notify.GetEvent(&event);
    
    while (got_event) {
      
      string filename = event.GetName();
      
      //make sure it is a script file that has changed
      string extension = filename.substr(filename.length()-4);
      
      if (extension.compare(".lua") == 0) {
	
	it = watchstatus.find(filename);
	(*it).second = true;
	
      }
      
      got_event = notify.GetEvent(&event);
      
    }
  } catch (InotifyException &e) {
    logger.info << "Inotify exception!!! occured: " << e.GetMessage() << logger.end;
  }
  
  //check if it is a absolute path and if so extract script name
  if (name.at(0) == '/') {
    int i = name.rfind("/");
    name = name.substr(i + 1);
  }
  
  //check status map
  it = watchstatus.find(name);
  
  if (it == watchstatus.end()) {
    return false;
  }
  else {
    
    if ((*it).second) {
      (*it).second = false;
      return true;
    }
    else {
      return false;
    }
    
  }
  
#else
  return false;
#endif

}

void ScriptSystem::WatchScript(string name) {

  #ifdef _OnLinux_

  map<string, bool>::iterator it;

  //  logger.info << "argstr is: " << name << logger.end;

  //this is a absolute path so cut off scriptname to watch dir
  //and add a entry in watchstatus
  if (name.at(0) == '/') {
   
    int i = name.rfind("/");
    string lib = name.substr(0, i + 1);
    string scriptname = name.substr(i + 1);
    WatchDir(lib);
    
    it = watchstatus.find(scriptname);

    if (it == watchstatus.end()) {
      watchstatus.insert(pair<string, bool>(scriptname, false));
    }

  }
  //just add to inotify and catch exception e.a let it handle multiple
  //additions
  else {

    WatchDir(libpath);
    
    it = watchstatus.find(name);

    if (it == watchstatus.end())
      watchstatus.insert(pair<string, bool>(name, false));

  }

  #endif
}

int ScriptSystem::GetInitAttacher(lua_State* L) {

  //check the stack size
  if (CheckStackSize(L, "GetInitAttacher", 0))
    return 0;

  //create the new attacher
  IEvent<InitializeEventArg>& e = en->InitializeEvent();
  Attacher<InitializeEventArg>* a = 
    new Attacher<InitializeEventArg>(e);
  
  lua_pushlightuserdata(L, a);

  return 1;
}

int ScriptSystem::GetDeinitAttacher(lua_State* L) {

  //check the stack size
  if (CheckStackSize(L, "GetDeinitAttacher", 0))
    return 0;

  //create the new attacher
  IEvent<DeinitializeEventArg>& e = en->DeinitializeEvent();
  Attacher<DeinitializeEventArg>* a = 
    new Attacher<DeinitializeEventArg>(e);

  lua_pushlightuserdata(L, a);

  return 1;
}

int ScriptSystem::GetProcessAttacher(lua_State* L) {

  //check the stack size
  if (CheckStackSize(L, "GetProcessAttacher", 0))
    return 0;

  //create the new attacher
  IEvent<ProcessEventArg>& e = en->ProcessEvent();
  Attacher<ProcessEventArg>* a = 
    new Attacher<ProcessEventArg>(e);

  lua_pushlightuserdata(L, a);

  return 1;
}

int ScriptSystem::Attach(lua_State* L) {

  //check the stack size and types
  if (CheckStackSize(L, "Attach", 2) || CheckArgType(L, "Attach", 'p', 1, -2)
      || CheckArgType(L, "Attach", 'p', 2, -1))
    return 0;

  IAttacher* a = (IAttacher*) lua_touserdata(L, -2);
  void* lis = lua_touserdata(L, -1);

  a->Attach(lis);

  lua_pop(L, 2);

  return 0;
}

int ScriptSystem::ListenOnEvent(lua_State* L) {

  int nargs = lua_gettop(L);
  int index;

  //check size and types
  if (nargs >= 4) {
    //check top 4 arguments
    if (CheckArgType(L, "ListenOnEvent", 'p', 1, -4) 
	|| CheckArgType(L, "ListenOnEvent", 's', 2, -3)
	|| CheckArgType(L, "ListenOnEvent", 's', 3, -2)
	|| CheckArgType(L, "ListenOnEvent", 's', 4, -1))
      return 0;

    //check if there are too many arguments on the stack and if so
    //warn
    if (nargs > 4)
      logger.info << "Warning ListenOnEvent called with too many arguments"
		  << " but top 4 arguments used" << logger.end;
    
    //set index
    index = -4;
  }
  else if (nargs == 3) {
    //check that top 3 arguments are ok
    if (CheckArgType(L, "ListenOnEvent", 'p', 1, -3) 
	|| CheckArgType(L, "ListenOnEvent", 's', 2, -2)
	|| CheckArgType(L, "ListenOnEvent", 's', 3, -1))
      return 0;

    //set index
    index = -3;
  }
  //ok we know we have 2 or fewer arguments
  else { 
    //check if there are too few arguments
    if (nargs < 2) {
      logger.info << "ListenOnEvent called with only: " << nargs 
		  << " arguments. The function looks like this:\n"
		  << "ListenOnEvent(attacher, scriptname, opt funcname, opt stackid)."
		  << " Call aborted." << logger.end;
      return 0;
    }
    //check types
    if (CheckArgType(L, "ListenOnEvent", 'p', 1, -2) 
	|| CheckArgType(L, "ListenOnEvent", 's', 2, -1))
      return 0;
    index = -2;
  }
 
  IAttacher* att = (IAttacher*) lua_touserdata(L, index);
  ILuaListener* lis = att->GetListener();

  string scriptname = lua_tostring(L, index + 1);

  if (nargs >= 4) {
    string funcname = lua_tostring(L, index + 2);
    string stackid = lua_tostring(L, index + 3);
    lis->AddScript(scriptname, funcname, stackid);    
  }
  else if (nargs == 3) {
    string funcname = lua_tostring(L, index + 2);
    lis->AddScript(scriptname, funcname, "default");
  }
  else
    lis->AddScript(scriptname, "default"); 

  //take off the args - clean up
  lua_pop(L, nargs);

  return 0;
  
}

int ScriptSystem::RunScript(lua_State* L) {

  int nargs = lua_gettop(L);

  if (nargs >= 2) {

    //check arguments
    if (CheckArgType(L, "Runscript", 's', 1, -2) ||
	CheckArgType(L, "Runscript", 's', 2, -1))
      return 0;

    if (nargs > 2)
      logger.info << "Warning: Runscript called with " << nargs 
		  << " arguments but only needs max 2." << logger.end;

    string name = lua_tostring(L, -2);
    string stack = lua_tostring(L, -1);

    RunScript(name, stack);

  }
  else if (nargs == 1) {

    //check stack and size
    if (CheckArgType(L, "Runscript", 's', 1, -1))
      return 0;

    string name = lua_tostring(L, -1);
    
    RunScript(name);

  }

  //cleanup
  lua_settop(L, 0);

  return 0;

}

int ScriptSystem::RunScriptFunc(lua_State* L) {

  //check args and types
  if (CheckArgType(L, "RunScriptFunc", 's', 1, -3) ||
      CheckArgType(L, "RunScriptFunc", 's', 2, -2) ||
      CheckArgType(L, "RunScriptFunc", 'i', 3, -1))
    return 0;

  string name = lua_tostring(L, -3);
  string funcname = lua_tostring(L, -2);
  int rvals = lua_tointeger(L, -1);

  //pop the name and funcname
  lua_pop(L, 3);

  //get the script name
  string path = GetScriptName(name);

  //load the script and catch errors  
  int s = luaL_loadfile(L, path.c_str());

  if (s == 0) {
    
    //try to find the function in question
    lua_getglobal(L, funcname.c_str());

    //script has not been run and so function
    //is not located jet. Therefore we have to
    //run the script.
    if (lua_isnil(L, lua_gettop(L)) || CheckFile(name)) {

      //remove the nil argument
      lua_pop(L, 1);
      //run script
      s = lua_pcall(L, 0, LUA_MULTRET, 0);
      //now try function again
      lua_getglobal(L, funcname.c_str());

      //watch script
      WatchScript(name);

    }
  }

  //now move the function pointer to the bottom
  lua_insert(L, 1);

  //call the function
  s = lua_pcall(L, lua_gettop(L) - 1, LUA_MULTRET, 0);

  //report errors and cancel call
  ReportErrors(L, s);
  if (s != 0) {
	logger.info << "Call to " << funcname << " in " << path << " aborted" << logger.end;
	lua_settop(L, 0);
	return 0;
  }

  return rvals;

}

int ScriptSystem::GetRandomInt(lua_State* L) {

  int range = lua_tointeger(L, -1);
  int res = randgen.UniformInt(0, range);
  lua_pushinteger(L, res);
  return 1;

}

ScriptSystem::ScriptSystem() {
}

bool ScriptSystem::CheckArgType(lua_State* L, string name, char type, int number, int index) {

  if (type == 'p' && !lua_islightuserdata(L, index)) {
    logger.info << "Function " << name << " wants some userdata as argument " 
		<< number << ". Call aborted." << logger.end;
    return true;
  }
  else if (type == 's' && !lua_isstring(L, index)) {
    logger.info << "Function " << name << " wants a string as argument " 
		<< number << ". Call aborted." << logger.end;
    return true;
  }
  else if (type == 'b' && !lua_isboolean(L, index)) {
    logger.info << "Function " << name << " wants a bool as argument " 
		<< number << ". Call aborted." << logger.end;
    return true;
  }
  else if (type == 'd' && !lua_isnumber(L, index)) {
    logger.info << "Function " << name << " wants a float/double as argument " 
		<< number << ". Call aborted." << logger.end;
    return true;
  }
  else if (type == 'i' && !lua_isnumber(L, index)) {
    logger.info << "Function " << name << " wants a integer as argument " 
		<< number << ". Call aborted." << logger.end;
    return true;
  }

  return false;

}

bool ScriptSystem::CheckStackSize(lua_State* L, string name, int count) {

  int stacksize = lua_gettop(L);

  //too few arguments so call has to be stopped
  if (stacksize < count) {
    
    logger.info << "Function " << name << " needs " << count 
		<< " argument/arguments but there is only " 
		<< stacksize << " argument/arguments on the stack."
		<< " Call aborted." << logger.end;
    return true;

  }
  //too many arguments
  else if (stacksize > count) {

    logger.info << "Warning function " << name << " is getting "
		<< stacksize << " argument/arguments but only needs "
		<< count << " argument/arguments" << logger.end;
    return false;

  }
  //arguments match so no problem
  else
    return false;
  
}

void ScriptSystem::InitScriptSystem(string path, Engine* engine) {

  //set initialized
  initialized = true;

  lua_State* L = lua_open();

  stacks.insert(pair<string, lua_State*>("default", L));

  //open the libs
  luaL_openlibs(L);

  //set standard library path
  libpath = path;

  en = engine;
  randgen.SeedWithTime();

  //register core functions
  RegistreCore();

  #ifdef _OnLinux_
  //remember to make nonblocking
  notify.SetNonBlock(true);
  #endif

}

void ScriptSystem::DeinitScriptSystem() {
  
  map<string, lua_State*>::iterator it;

  it = stacks.begin();

  while (it != stacks.end()) { 
    lua_close((*it).second);
    ++it;
  }

};

void ScriptSystem::RunScript(string scriptname, string stackid) {

  //make sure system is initialized
  if (CheckIfInit("RunScript"))
    return;

  //get the stack
  lua_State* L = GetStack(stackid);

  //get the script name
  string path = GetScriptName(scriptname);

  //load the script and catch errors
  int s = luaL_loadfile(L, path.c_str());

  if (s==0) {
    // execute Lua program
    s = lua_pcall(L, 0, LUA_MULTRET, 0);

    //watch script
    WatchScript(scriptname);
  }

  ReportErrors(L, s);

}

void ScriptSystem::RunScriptFunc(string scriptname, 
				 string funcname,
				 string stackid,
				 string argtypes,
				 string returntypes,				 
				 ...) {

  //make sure system is initialized
  if (CheckIfInit("RunScriptFunc"))
    return;

  //get the stack
  lua_State* L;

  if (stackid.compare("") == 0)
    //get the stack
    L = GetStack("default");
  else
    L = GetStack(stackid);

  //make the variable lenght list and initialize it.
  va_list vl;
  va_start(vl, returntypes);

  //get the script name
  string path = GetScriptName(scriptname);

  //load the script and catch errors  
  int s = luaL_loadfile(L, path.c_str());

  if (s==0) {
    
    //try to find the function in question
    lua_getglobal(L, funcname.c_str());

    //script has not been run and so function
    //is not located jet. Therefore we have to
    //run the script.
    if (lua_isnil(L, lua_gettop(L)) || CheckFile(scriptname)) {

       //remove the nil argument
      lua_pop(L, 1);
      //run script
      s = lua_pcall(L, 0, LUA_MULTRET, 0);
      //now try function again
      lua_getglobal(L, funcname.c_str());

      //watch script
      WatchScript(scriptname);

    }

    //get the arguments on the stack
    for (unsigned int i = 0; i < argtypes.length(); i++) {
      switch (argtypes.at(i)) {
      
      case 'b': {
	lua_pushboolean(L, va_arg(vl, int));
	break;
      }
      case 'i': {
	lua_pushinteger(L, va_arg(vl, int));
	break;
      }
      case 'd': {
	lua_pushnumber(L, va_arg(vl, double));
	break;
      }
      case 's': {
	lua_pushstring(L, va_arg(vl, char*));
	break;
      }
      case 'u': {
	void* data = va_arg(vl, void*);
	int size = va_arg(vl, int);
	void* ldata = lua_newuserdata(L, size);
	memcpy(ldata, data, size);
	break;
      }
      case 'p': {
	void* p = va_arg(vl, void*);
	lua_pushlightuserdata(L, p);
	break;
      }
      default:
	logger.info << "unrecognized argument: " 
		    << argtypes.at(i) << logger.end;
	break;

      }
    }

    //call the function
    s = lua_pcall(L, argtypes.length(), LUA_MULTRET, 0);

    unsigned int rrv = returntypes.length();
    unsigned int trv = lua_gettop(L);

    //if returnvalues are requested make sure there
    //is enough
    if (rrv > trv)
      logger.info << rrv << " return values requested" 
		  << ". Only " << trv 
		  << " return values present"
		  << logger.end;
    else {

      //get the returvalues
      for (unsigned int i = 0; i < rrv; i++) {

	int nextindex = trv - rrv + 1 - i;

	switch (returntypes.at(i)) {
	
	case 'b': {
	  bool* bp = (bool*) va_arg(vl, int*);
	  *bp = lua_toboolean(L, nextindex);
	  break;
	}
	case 'i': {
	  int* ip = va_arg(vl, int*);
	  *ip = lua_tointeger(L, nextindex);
	  break;
	}
	case 'd': {
	  double* fp = va_arg(vl, double*);
	  *fp = lua_tonumber(L, nextindex);
	  break;
	}
	case 's': {
	  string* cp = (string*) va_arg(vl, char*);
	  *cp = lua_tostring(L, nextindex);
	  break;
	}
	case 'u': {
	  void* dest = va_arg(vl, void*);
	  int size = va_arg(vl, int);
	  void* sour = lua_touserdata(L, nextindex);
	  memcpy(dest, sour, size);
	  break;
	}
	case 'p': {
	  void** p = va_arg(vl, void**);
	  *p = lua_touserdata(L, nextindex);
	  break;
	}
	default:
	  logger.info << "unrecognized argument: " 
		      << returntypes.at(i) << logger.end;
	  break;
	}  

      }    
    }

    ReportErrors(L, s);
    lua_pop(L, trv - 1);
  }

  va_end(vl);

}

void ScriptSystem::GetGlobal(string scriptname, string name, char type, void* rval, string stackid) {

  lua_State* L = GetStack(stackid);

  lua_getglobal(L, name.c_str());

  //check that there is something on the stack and it is not nil
  //if this check fails it means the global could not be found so stop
  if (lua_gettop(L) != 1 || lua_isnil(L, -1)) {
    logger.info << "Global " << name << " could not be found" << logger.end;
    return;
  }

  switch (type) {

  case 'b': {
    bool* bp = (bool*) rval;
    *bp = lua_toboolean(L, -1);
    break;
  }
  case 'i': {
    int* ip = (int*) rval;
    *ip = lua_tointeger(L, -1);
    break;
  } 
  case 'd': {
    double* dp = (double*) rval;
    *dp = lua_tonumber(L, -1);
    break;
  }
  case 's': {
    string* sp = (string*) rval;
    *sp = lua_tostring(L, -1);
    break;
  }
  case 'p': {
    void** p = (void**) rval;
    *p = lua_touserdata(L, -1);
    break;
  }
  default:
    logger.info << "requested type is not available: " << type << logger.end;
    break;
  }

  lua_pop(L, 1);
}

void ScriptSystem::ChangeScriptDir(string newpath) {

  if (CheckIfInit("ChangeScriptDir"))
    return;

  libpath = newpath;

}

void ScriptSystem::RemoveStack(string name) {

  lua_State* L = GetStack(name);
  lua_close(L);
  stacks.erase(name);

}

void ScriptSystem::RemoveStack(lua_State* L) {
  lua_close(L);
}

void ScriptSystem::RegisterNonClassFunc(string name, lua_CFunction func, string stackid) {

  if (CheckIfInit("RegisterNonClassFunc"))
    return;

  //get the stack
  lua_State* L = GetStack(stackid);

  lua_register(L, name.c_str(), func);

} 






