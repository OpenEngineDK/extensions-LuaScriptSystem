
#include "MusicSubSystem.h"
#include "../../ScriptSystem.h"

string ScriptISound::classname = "ISound";
CPPToLuaBinder<ScriptISound>::RegType ScriptISound::Register[] = {
  {"IsStereoSound", &ScriptISound::IsStereoSound},
  {"IsMonoSound", &ScriptISound::IsMonoSound},
  {"IsPlaying", &ScriptISound::IsPlaying},
  {"Play", &ScriptISound::Play},
  {"Stop", &ScriptISound::Stop},
  {"Pause", &ScriptISound::Pause},
  {"SetLooping", &ScriptISound::SetLooping},
  {"GetLooping", &ScriptISound::GetLooping},
  {"SetGain", &ScriptISound::SetGain},
  {"GetGain", &ScriptISound::GetGain},
  {"GetLengthInSamples", &ScriptISound::GetLengthInSamples},
  {"GetLength", &ScriptISound::GetLength},
  {"SetElapsedSamples", &ScriptISound::SetElapsedSamples},
  {"GetElapsedSamples", &ScriptISound::GetElapsedSamples},
  {"SetElapsedTime", &ScriptISound::SetElapsedTime},
  {"GetElapsedTime", &ScriptISound::GetElapsedTime},
  {"GetTimeLeft", &ScriptISound::GetTimeLeft},
  {"IsAtEnd", &ScriptISound::IsAtEnd}
};

string ScriptIMonoSound::classname = "IMonoSound";
CPPToLuaBinder<ScriptIMonoSound>::RegType ScriptIMonoSound::Register[] = {
  {"IsStereoSound", &ScriptIMonoSound::IsStereoSound},
  {"IsMonoSound", &ScriptIMonoSound::IsMonoSound},
  {"SetMaxDistance", &ScriptIMonoSound::SetMaxDistance},
  {"GetMaxDistance", &ScriptIMonoSound::GetMaxDistance},
  {"IsPlaying", &ScriptIMonoSound::IsPlaying},
  {"Play", &ScriptIMonoSound::Play},
  {"Stop", &ScriptIMonoSound::Stop},
  {"Pause", &ScriptIMonoSound::Pause},
  {"SetLooping", &ScriptIMonoSound::SetLooping},
  {"GetLooping", &ScriptIMonoSound::GetLooping},
  {"SetGain", &ScriptIMonoSound::SetGain},
  {"GetGain", &ScriptIMonoSound::GetGain},
  {"GetLengthInSamples", &ScriptIMonoSound::GetLengthInSamples},
  {"GetLength", &ScriptIMonoSound::GetLength},
  {"SetElapsedSamples", &ScriptIMonoSound::SetElapsedSamples},
  {"GetElapsedSamples", &ScriptIMonoSound::GetElapsedSamples},
  {"SetElapsedTime", &ScriptIMonoSound::SetElapsedTime},
  {"GetElapsedTime", &ScriptIMonoSound::GetElapsedTime},
  {"SetVelocity", &ScriptIMonoSound::SetVelocity},
  {"GetVelocity", &ScriptIMonoSound::GetVelocity},
  {"GetPosition", &ScriptIMonoSound::GetPosition},
  {"SetPosition", &ScriptIMonoSound::SetPosition},
  {"SetRelativePosition", &ScriptIMonoSound::SetRelativePosition},
  {"GetResource", &ScriptIMonoSound::GetResource},
  {"GetTimeLeft", &ScriptIMonoSound::GetTimeLeft},
  {"IsAtEnd", &ScriptIMonoSound::IsAtEnd}
};

string ScriptIStereoSound::classname = "IStereoSound";
CPPToLuaBinder<ScriptIStereoSound>::RegType ScriptIStereoSound::Register[] = {
  {"GetLeft", &ScriptIStereoSound::GetLeft},
  {"GetRight", &ScriptIStereoSound::GetRight},
  {"IsStereoSound", &ScriptIStereoSound::IsStereoSound},
  {"IsMonoSound", &ScriptIStereoSound::IsMonoSound}
};

string ScriptISoundSystem::classname = "ISoundSystem";
CPPToLuaBinder<ScriptISoundSystem>::RegType ScriptISoundSystem::Register[] = {
  {"CreateSound",  &ScriptISoundSystem::CreateSound},
  {"SetRoot",  &ScriptISoundSystem::SetRoot},
  {"SetMasterGain",  &ScriptISoundSystem::SetMasterGain},
  {"GetMasterGain",  &ScriptISoundSystem::GetMasterGain}
};

string ScriptOpenALSoundSystem::classname = "OpenALSoundSystem";
CPPToLuaBinder<ScriptOpenALSoundSystem>::RegType ScriptOpenALSoundSystem::Register[] = {
  {"CreateSound",  &ScriptOpenALSoundSystem::CreateSound},
  {"SetRoot",  &ScriptOpenALSoundSystem::SetRoot},
  {"SetMasterGain",  &ScriptOpenALSoundSystem::SetMasterGain},
  {"GetMasterGain",  &ScriptOpenALSoundSystem::GetMasterGain},
  {"GetOpenALSoundSystem",  &ScriptOpenALSoundSystem::GetOpenALSoundSystem}
};

string ScriptITransitionMode::classname = "ITransitionMode";
CPPToLuaBinder<ScriptITransitionMode>::RegType ScriptITransitionMode::Register[] = {
  {"InitFade", &ScriptITransitionMode::InitFade},
  {"GetInTime", &ScriptITransitionMode::GetInTime},
  {"GetOutTime", &ScriptITransitionMode::GetOutTime},
  {"Process", &ScriptITransitionMode::Process},
  {"IsDone", &ScriptITransitionMode::IsDone},
  {"Start", &ScriptITransitionMode::Start}
};

string ScriptBruteTransitionMode::classname = "BruteTransitionMode";
CPPToLuaBinder<ScriptBruteTransitionMode>::RegType ScriptBruteTransitionMode::Register[] = {
  {"InitFade", &ScriptBruteTransitionMode::InitFade},
  {"GetInTime", &ScriptBruteTransitionMode::GetInTime},
  {"GetOutTime", &ScriptBruteTransitionMode::GetOutTime},
  {"Process", &ScriptBruteTransitionMode::Process},
  {"IsDone", &ScriptBruteTransitionMode::IsDone},
  {"Start", &ScriptBruteTransitionMode::Start}
};

string ScriptMusicPlayer::classname = "MusicPlayer";
CPPToLuaBinder<ScriptMusicPlayer>::RegType ScriptMusicPlayer::Register[] = {
  {"AddSound",  &ScriptMusicPlayer::AddSound},
  {"Previous",  &ScriptMusicPlayer::Previous},
  {"Next",  &ScriptMusicPlayer::Next},
  {"SwitchTo",  &ScriptMusicPlayer::SwitchTo},
  {"NumberOfTracks",  &ScriptMusicPlayer::NumberOfTracks},
  {"Play",  &ScriptMusicPlayer::Play},
  {"Stop",  &ScriptMusicPlayer::Stop},
  {"Pause",  &ScriptMusicPlayer::Pause},
  {"Shuffle",  &ScriptMusicPlayer::Shuffle},
  {"SetTransitionMode",  &ScriptMusicPlayer::SetTransitionMode},
  {"SetGain",  &ScriptMusicPlayer::SetGain},
  {"GetGain",  &ScriptMusicPlayer::GetGain},
  {"GetMusicPlayer", &ScriptMusicPlayer::GetMusicPlayer}
};

int ActivateMusicSubSystem(lua_State* L) {

  if (ScriptSystem::CheckStackSize(L, "ActivateMusicSubSystem", 0))
    return 0;

  //IMPORTANT NOTE TO THOSE WONDERING ABOUT THE STACK COUNT
  //IN THE CHECKS IN ALL THESE FILES. IT IS ONE HIGHER THAN 
  //ONE SHOULD THINK AND THAT IS BECAUSE THE TABLE RESPRESENTING 
  //THE CLASS IS ALSO ON THE STACK AT INDEX 0 (BOTTOM)
  ScriptSystem::RegisterClass<ScriptISound>();
  ScriptSystem::RegisterClass<ScriptIStereoSound>();
  ScriptSystem::RegisterClass<ScriptIMonoSound>();
  ScriptSystem::RegisterClass<ScriptISoundSystem>();
  ScriptSystem::RegisterClass<ScriptOpenALSoundSystem>();
  ScriptSystem::RegisterClass<ScriptITransitionMode>();
  ScriptSystem::RegisterClass<ScriptBruteTransitionMode>();
  ScriptSystem::RegisterClass<ScriptMusicPlayer>();

  return 0;

} 




