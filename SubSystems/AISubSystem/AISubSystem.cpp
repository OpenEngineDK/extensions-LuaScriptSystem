
#include "AISubSystem.h"

string StateMashine::classname = "StateMashine";
CPPToLuaBinder<StateMashine>::RegType StateMashine::Register[] = {
  {"AddState", &StateMashine::AddState},
  {"GotoState", &StateMashine::GotoState},
  {"CurrentState", &StateMashine::CurrentState},
  {"GetData", &StateMashine::GetData},
  {"GetStateMashine", &StateMashine::GetStateMashine}
};

int ActivateAISubSystem(lua_State* L) {

  ScriptSystem::RegisterClass<StateMashine>();

  return 0;

}
