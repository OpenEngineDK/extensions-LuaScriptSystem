// Key handler.
// -------------------------------------------------------------------
// Copyright (C) 2007 OpenEngine.dk (See AUTHORS) 
// 
// This program is free software; It is covered by the GNU General 
// Public License version 2 or any later version. 
// See the GNU General Public License for more details (see LICENSE). 
//--------------------------------------------------------------------

#include "ScriptKeyHandler.h"

ScriptKeyHandler::ScriptKeyHandler() {
}

ScriptKeyHandler::~ScriptKeyHandler() {
}

// set state of keys on up/down events
void ScriptKeyHandler::Handle(KeyboardEventArg arg) {
    if(arg.type == EVENT_PRESS)
      keysPressed.push_back(arg.sym);
    else {
      keysPressed.remove(arg.sym);
      HandleUp(arg.sym);
    }
}

void ScriptKeyHandler::HandleUp(Key key) {

    switch (key) {
    case KEY_F2:
      ScriptSystem::RunScriptFunc("sound.lua", "TestScream", "", "", "");
      break;
    case KEY_F3:
      ScriptSystem::RunScriptFunc("sound.lua", "Next", "", "", "");
      break;
    case KEY_F4:
      //      ScriptSystem::RunScriptFunc("/home/jakob/Skrivebord/openengine/projects/test.lua", "Print", "", "", "");
      //      ScriptSystem::RunScriptFunc("test.lua", "Print", "", "", "");
      ScriptSystem::RunScript("tests/test.lua");
      break;
    default:
      break;
    }
}



