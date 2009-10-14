# The OE_CURRENT_EXTENSION_DIR is the full filesystem path to this extension
INCLUDE(${CMAKE_ROOT}/Modules/FindLua51.cmake)
#INCLUDE(${OE_CURRENT_EXTENSION_DIR}/cmake/FindLuaLibs.cmake)

IF(LUA51_FOUND)

  INCLUDE_DIRECTORIES(${LUA_INCLUDE_DIR})
  
  # Extra debug info
  IF(OE_DEBUG_CMAKE)
    MESSAGE("-- Looking for LUA_INCLUDE_PATH - found ${LUA_INCLUDE_PATH}")
    MESSAGE("-- Looking for LUA_LIBRARIES - found ${LUA_LIBRARY}")
  ENDIF(OE_DEBUG_CMAKE)

ELSE (LUA51_FOUND)

  MESSAGE ("WARNING: Could not find Lua Libraries - depending targets will be disabled.")

ENDIF(LUA51_FOUND)
