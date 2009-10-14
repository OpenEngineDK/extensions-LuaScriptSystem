
#ifndef MusikSubSystem_h
#define MusikSubSystem_h

#include "../../LuaHeader.h"
#include "../../CPPToLuaBinder.h"
#include <Logging/Logger.h>
class ScriptSystem;

#include "ScriptISound.h"
#include "ScriptIMonoSound.h"
#include "ScriptIStereoSound.h"
#include "ScriptISoundSystem.h"
#include "ScriptOpenALSoundSystem.h"
#include "ScriptITransitionMode.h"
#include "ScriptBruteTransitionMode.h"
#include "ScriptMusicPlayer.h"

int ActivateMusicSubSystem(lua_State* L);

#endif
