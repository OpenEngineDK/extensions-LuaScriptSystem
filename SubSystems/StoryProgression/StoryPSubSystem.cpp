
#include "StoryPSubSystem.h"

string MileStone::classname = "MileStone";
CPPToLuaBinder<MileStone>::RegType MileStone::Register[] = {
  {"IsReached", &MileStone::IsReached},
  {"Mark", &MileStone::Mark},
  {"GetData", &MileStone::GetData},
  {"SetData", &MileStone::SetData},
  {"GetMileStone", &MileStone::GetMileStone}
};

string StoryP::classname = "StoryP";
CPPToLuaBinder<StoryP>::RegType StoryP::Register[] = {
  {"AddMileStone", &StoryP::AddMileStone},
  {"DeleteMileStone", &StoryP::DeleteMileStone},
  {"GetMileStone", &StoryP::GetMileStone},
  {"IsReached", &StoryP::IsReached},
  {"GetData", &StoryP::GetData},
  {"Mark", &StoryP::Mark},
  {"GetStoryP", &StoryP::GetStoryP}
};

int ActivateStoryPSubSystem(lua_State* L) {

  if (ScriptSystem::CheckStackSize(L, "ActivateStoryPSubSystem", 0))
    return 0;

  ScriptSystem::RegisterClass<MileStone>();
  ScriptSystem::RegisterClass<StoryP>();

  return 0;

}
