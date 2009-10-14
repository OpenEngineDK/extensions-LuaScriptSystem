
#include "TestFuncs.h"

Account::Account(lua_State* L) {
  lua_pushstring(L, "balance");
  lua_gettable(L, -2);
  m_balance = lua_tonumber(L, -1);
  lua_pop(L, 2); 
}

int Account::deposit(lua_State* L) {
  m_balance += lua_tonumber(L, -1);
  lua_pop(L, 1);
  return 0; 
}

int Account::withdraw(lua_State* L) {
  m_balance -= lua_tonumber(L, -1);
  lua_pop(L, 1);
  return 0;
}

int Account::balance(lua_State* L) {
  lua_pushnumber(L, m_balance);
  return 1;  
}

int PrintPoint(lua_State* L) {

  Point* p = (Point *) lua_touserdata(L, 1);

  logger.info << "Point: x is " << p->x << " and y is " 
	      << p->y << logger.end;

  //clean up
  lua_pop(L, 1);

  //it only prints so no need to return anything
  return 0;
}

int ChangePoint(lua_State* L) {

  Point* p = (Point *) lua_touserdata(L, 1);
  int x = lua_tointeger(L, 2);
  int y = lua_tointeger(L, 3);

  p->x = x;
  p->y = y;

  //clean up
  lua_pop(L, 3);

  //it only prints so no need to return anything
  return 0;
}

int CreatePoint(lua_State* L) {

  //make a point
  Point* p = new Point(4, 6);
  
  lua_pushlightuserdata(L, p);

  return 1;

}

int PrintString(lua_State* L) {

  string s = lua_tostring(L, -1);

  logger.info << s << logger.end;
  
  return 0;

}
