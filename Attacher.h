
#ifndef Attacher_h
#define Attacher_h

#include <Core/IListener.h>
#include <Core/IEvent.h>
#include <Logging/Logger.h>
using OpenEngine::Core::IListener;
using OpenEngine::Core::IEvent;

class ILuaListener;
template <typename EventArg>
class LuaListener;

class IAttacher {
 public:
  virtual void Attach(void* lis) = 0;
  virtual ILuaListener* GetListener() = 0;
};

template <typename EventArg>
class Attacher : IAttacher {
 private:
  IEvent<EventArg>& e;

 public:
 Attacher(IEvent<EventArg>& event): e(event) {}

  void Attach(void* lis) {

    IListener<EventArg>* tlis = (IListener<EventArg>*) lis;
    e.Attach(*tlis);

  }
  
  ILuaListener* GetListener() {
    LuaListener<EventArg>* lis =
      LuaListener<EventArg>::GetListener();
    static bool isAttached = false;
    if (!isAttached) {
      Attach(lis);
      isAttached = true;
    }
    return lis;
  }
  
};

#endif
