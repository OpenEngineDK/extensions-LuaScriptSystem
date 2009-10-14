
#ifndef CPPToLuaBinder_h
#define CPPToLuaBinder_h

#include "LuaHeader.h"
#include <Logging/Logger.h>
#include <string>
#include <string.h>
using namespace std;

template <typename T>
class CPPToLuaBinder
{

  //hide away the constructor. This class is not 
  //suppose to be constructored in any way and since
  //c++ will insert a public constructor if none is
  //present this unaccessable constructor is declared.
 protected: 
  CPPToLuaBinder(); 
  
 private:
  
  //this function is the one called by lua and it is 
  //its job to call the right member function on the
  //object
  static int MFuncDispatcher(lua_State* L) {
    
    /* stack looks like = 
       
       2: arguments to the func in c++
       1: table
     */
    int i = lua_tonumber(L, lua_upvalueindex(1));
    
    //get hold of the object in the table
    lua_pushnumber(L, 0); 
    lua_gettable(L, 1);
    T* obj = static_cast<T*>(lua_touserdata(L,-1));
    //pop off the object to leave the arguments on top
    lua_pop(L, 1); 
    return (obj->*(T::Register[i].mfunc))(L);
    
  }

//this function is the one called by lua and it is 
  //its job to call the right member function on the
  //object
  static int FuncDispatcher(lua_State* L) {
   
    /* stack looks like = 
       
       2: arguments to the func in c++
     */
    int i = lua_tonumber(L, lua_upvalueindex(1));
    T* obj = static_cast<T*>(lua_touserdata(L,lua_upvalueindex(2)));

    return (obj->*(T::Register[i].mfunc))(L);
    
  }

  //this function makes the table and set up all the 
  //fields of the table. Also allocates the object that 
  //will be called.
  static int Constructor(lua_State* L) {

    //make the new object
    T* obj= new T(L); 
    
    //clear the stack
    lua_settop(L,0);
    
    //make the new table and put obj at index 0
    lua_newtable(L); 
    lua_pushnumber(L, 0); 
    lua_pushlightuserdata(L, obj);
    lua_settable(L, -3);
    
    //set the garbage collector to the one defined
    //in this obj (the one in the gc global) by
    //assigning the gc closure to the gc field of the 
    //table
    lua_pushstring(L, "gc");
    lua_getglobal(L, "gc");
    lua_settable(L, -3);
    
    //figure out how many arguments are in the array
    //defined in the Register on the class T
    int size = sizeof(T::Register) / sizeof (*T::Register);
    
    //register the member functions
    for (int i = 0; i < size; i++) {
      lua_pushstring(L, (T::Register[i].name).c_str());
      lua_pushnumber(L, i);
      lua_pushcclosure(L, &CPPToLuaBinder<T>::MFuncDispatcher, 1);
      lua_settable(L, -3);
    }

    //by now only the table which is what we return is 
    //on the stack and so everything is fine
    return 1; 
  }
  
  //garbage collect function
  static int gc_obj(lua_State* L) {
    T* obj = static_cast<T*>(lua_touserdata(L, -1));
    delete obj;
    return 0;
  }
  
 public:

  //the functionmap struct
  struct RegType { 
    string name; 
    int(T::*mfunc)(lua_State*);
  };      

  /*the types of things that can be registered

    1) classes. Means full construction with table
       and globals - the works
    2) functions. Means you deliver an of the class
       type and the function you register

   */

  //the register function for classes
  static void Register(lua_State* L) {
    //bind the class constructor to the global classname
    lua_pushcfunction(L, &CPPToLuaBinder<T>::Constructor);
    lua_setglobal(L, T::classname.c_str());
    
    //bind the garbage function to the global gc
    lua_pushcfunction(L, &CPPToLuaBinder<T>::gc_obj);
    lua_setglobal(L, "gc");
    
  }

  //the register function for functions
  static void Register(lua_State* L, T* obj) {

    //figure out how many arguments are in the array
    //defined in the Register on the class T
    int size = sizeof(T::Register) / sizeof (*T::Register);

    //register the member functions
    for (int i = 0; i < size; i++) {
      //store the obj as in the closure
      lua_pushnumber(L, i);
      lua_pushlightuserdata(L, obj);
      lua_pushcclosure(L, &CPPToLuaBinder<T>::FuncDispatcher, 2);
      lua_setglobal(L, (T::Register[i].name).c_str());
    }
    
  }
 
};

#endif
