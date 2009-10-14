
/*

  This file is only there to give users a chance to get the needed lua
  includes for the functions they make. It is needed because lua requires
  the functions that are registered to have a certain form for which these
  includes are needed.

 */

#ifndef LuaHeader_h
#define LuaHeader_h

extern "C"
{
  #include "lua.h"
  #include "lualib.h"
  #include "lauxlib.h"
}

#endif
