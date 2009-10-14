SET( EXTENSION_NAME "Extensions_LuaScriptSystem")

ADD_LIBRARY( ${EXTENSION_NAME}
  ScriptSystem.cpp

  TestStuff/TestFuncs.cpp
  TestStuff/ScriptKeyHandler.cpp

  SubSystems/ParticleSubSystem/ParticleSubSystem.cpp

  SubSystems/AISubSystem/StateMashine.cpp
  SubSystems/AISubSystem/AISubSystem.cpp

  SubSystems/MusicSubSystem/MusicSubSystem.cpp
  SubSystems/MusicSubSystem/ScriptOpenALSoundSystem.cpp
  SubSystems/MusicSubSystem/ScriptMusicPlayer.cpp
  SubSystems/MusicSubSystem/ScriptIMonoSound.cpp  
  SubSystems/MusicSubSystem/ScriptISound.cpp
  SubSystems/MusicSubSystem/ScriptIStereoSound.cpp
  SubSystems/MusicSubSystem/ScriptISoundSystem.cpp
  SubSystems/MusicSubSystem/ScriptITransitionMode.cpp
  SubSystems/MusicSubSystem/ScriptBruteTransitionMode.cpp

  SubSystems/StoryProgression/MileStone.cpp
  SubSystems/StoryProgression/StoryP.cpp
  SubSystems/StoryProgression/StoryPSubSystem.cpp

  SubSystems/CameraSubSystem/ScriptCamera.cpp
  SubSystems/CameraSubSystem/ScriptFollowCamera.cpp
  SubSystems/CameraSubSystem/CameraSubSystem.cpp

  SubSystems/UtilSubSystem/ScriptTimer.cpp
  SubSystems/UtilSubSystem/UtilSubSystem.cpp

  InotifyStuff/inotify-cxx.cpp
)

TARGET_LINK_LIBRARIES( ${EXTENSION_NAME}
  ${LUA_LIBRARY}
  OpenEngine_Core
)
