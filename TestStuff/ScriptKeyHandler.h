// Key handler.
// -------------------------------------------------------------------
// Copyright (C) 2007 OpenEngine.dk (See AUTHORS) 
// 
// This program is free software; It is covered by the GNU General 
// Public License version 2 or any later version. 
// See the GNU General Public License for more details (see LICENSE). 
//--------------------------------------------------------------------

#ifndef script_key_handler_h
#define script_key_handler_h

// inherits from
#include <Core/IListener.h>
#include <ScriptSystem.h>

#include <Devices/IKeyboard.h>
#include <list>

using namespace OpenEngine::Core;
using namespace OpenEngine::Devices;
using std::list;

class ScriptKeyHandler : public IListener<KeyboardEventArg> {
private:
    list<Key> keysPressed;

public:
    ScriptKeyHandler();
    ~ScriptKeyHandler();

    void Handle(KeyboardEventArg arg);
    void HandleUp(Key key);

};

#endif 
