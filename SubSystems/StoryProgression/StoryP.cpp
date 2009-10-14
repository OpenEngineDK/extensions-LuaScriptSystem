
#include "StoryP.h"
#include "MileStone.h"

StoryP::StoryP() {
}

void StoryP::AddMileStone(string name, MileStone* s) {

  //is it already there?
  it = milestones.find(name);

  //it is not here so add
  if (it == milestones.end())     
    milestones.insert(pair<string, MileStone*>(name, s));
  //it is already here so best that can be done is give new value
  else
    (*it).second = s;
  
}

void StoryP::DeleteMileStone(string name) {

  milestones.erase(name);

}

MileStone* StoryP::GetMileStone(string name) {

  it = milestones.find(name);

  if (it == milestones.end())
    return NULL;
  else
    return (*it).second;

}

bool StoryP::IsReached(string name) {

  it = milestones.find(name);

  if (it == milestones.end())
    return false;
  else
    return ((*it).second)->IsReached();

}

void* StoryP::GetData(string name) {

  it = milestones.find(name);

  if (it == milestones.end())
    return false;
  else
    return ((*it).second)->GetData();
  
}

void StoryP::Mark(string name) {

  it = milestones.find(name);

  if (it != milestones.end())
    ((*it).second)->Mark();  

}

//-----------------------------------------------

StoryP::StoryP(lua_State* L) {
}

int StoryP::AddMileStone(lua_State* L) {

  if (ScriptSystem::CheckStackSize(L, "AddMileStone", 3) ||
      ScriptSystem::CheckArgType(L, "AddMileStone", "string", 1, -2) ||
      ScriptSystem::CheckArgType(L, "AddMileStone", "userdata", 2, -1))
    return 0;

  string name = lua_tostring(L, -2);
  MileStone* s = (MileStone*) lua_touserdata(L, -1);
  AddMileStone(name, s);
  return 0;

}

int StoryP::DeleteMileStone(lua_State* L) {

  if (ScriptSystem::CheckStackSize(L, "DeleteMileStone", 2) ||
      ScriptSystem::CheckArgType(L, "DeleteMileStone", "string", 1, -1))
    return 0;

  string name = lua_tostring(L, -1);
  DeleteMileStone(name);
  return 0;

}

int StoryP::GetMileStone(lua_State* L) {

  if (ScriptSystem::CheckStackSize(L, "GetMileStone", 2) ||
      ScriptSystem::CheckArgType(L, "GetMileStone", "string", 1, -1))
    return 0;

  string name = lua_tostring(L, -1);
  lua_pushlightuserdata(L, GetMileStone(name));
  return 1;

}

int StoryP::IsReached(lua_State* L) {

  if (ScriptSystem::CheckStackSize(L, "IsReached", 2) ||
      ScriptSystem::CheckArgType(L, "IsReached", "string", 1, -1))
    return 0;

  string name = lua_tostring(L, -1);
  lua_pushboolean(L, IsReached(name));
  return 1;

}

int StoryP::GetData(lua_State* L) {

  if (ScriptSystem::CheckStackSize(L, "GetData", 2) ||
      ScriptSystem::CheckArgType(L, "GetData", "string", 1, -1))
    return 0;

  string name = lua_tostring(L, -1);
  lua_pushlightuserdata(L, GetData(name));
  return 1;

}

int StoryP::Mark(lua_State* L) {

  if (ScriptSystem::CheckStackSize(L, "Mark", 2) ||
      ScriptSystem::CheckArgType(L, "Mark", "string", 1, -1))
    return 0;

  string name = lua_tostring(L, -1);
  Mark(name);
  return 0;

}

int StoryP::GetStoryP(lua_State* L) {

  if (ScriptSystem::CheckStackSize(L, "GetStoryP", 1)) 
    return 0;

  lua_pushlightuserdata(L, this);
  return 1;

}
