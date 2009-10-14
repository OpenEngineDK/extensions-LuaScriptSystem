
#ifndef TestFuncs_h
#define TestFuncs_h

#include "../LuaHeader.h"
#include <Logging/Logger.h>
#include "../CPPToLuaBinder.h"
#include <string.h>
using namespace std;

struct Point {
  
  int x;
  int y;

Point(int xv, int yv) : x(xv), y(yv) {}
    
};

int PrintPoint(lua_State* L);
int ChangePoint(lua_State* L);
int CreatePoint(lua_State* L);
int PrintString(lua_State* L);

class Account
{
 private:
   double m_balance;

 public:

   static string classname;
   static CPPToLuaBinder<Account>::RegType Register[];
   
   Account(lua_State* L);   
   int deposit(lua_State* L);
   int withdraw(lua_State* L);
   int balance(lua_State* L);

};

#endif
