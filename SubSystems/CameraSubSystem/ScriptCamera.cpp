
#include "ScriptCamera.h"

ScriptCamera::ScriptCamera(lua_State* L) {

  if (ScriptSystem::CheckStackSize(L, "Camera", 1) ||
      ScriptSystem::CheckArgType(L, "Camera", 'p', 1, -1))
    return;

  IViewingVolume* vol = (IViewingVolume*) lua_touserdata(L, -1); 
  cam = new Camera(*vol);

}

int ScriptCamera::SetDirection(lua_State* L) {

  if (!cam) {
 
    logger.info << "Camera not initialized. Call Aborted." << logger.end;
    return 0;

  }

  int nargs = lua_gettop(L);

  //find out what specific direction function is being called
  //and deal with it
  if (nargs == 1 || 
      ScriptSystem::CheckArgType(L, "SetDirection", 'p', 1, -1)) {
    
    Quaternion<float>* qua = (Quaternion<float>*) lua_touserdata(L, -1);
    cam->SetDirection(*qua);

  }
  else if (nargs == 2 ||
	   ScriptSystem::CheckArgType(L, "SetDirection", 'p', 1, -2) ||
	   ScriptSystem::CheckArgType(L, "SetDirection", 'p', 2, -1)) {
    
    Vector<3, float>* dir = (Vector<3, float>*) lua_touserdata(L, -2);
    Vector<3, float>* up = (Vector<3, float>*) lua_touserdata(L, -1);
    cam->SetDirection(*dir, *up);

  }
  else 
    logger.info << "Wrong number or types of arguments. Possible uses are: "
		<< "SetDirection(Quaternion<float>*) and "
		<< "SetDirection(Vecter<3, float>*, Vector<3, float>*)."
		<< " Call aborted." << logger.end;

  return 0;

}

int ScriptCamera::Move(lua_State* L) {

  if (!cam) {

    logger.info << "Camera not initialized. Call Aborted." << logger.end;
    return 0;

  }

  int nargs = lua_gettop(L);

  if (nargs == 1 ||
      ScriptSystem::CheckArgType(L, "Move", 'p', 1, -1)) {

    Vector<3, float>* pos = (Vector<3, float>*) lua_touserdata(L, -1);
    cam->Move(*pos);

  }
  else if (nargs == 3 || 
	   ScriptSystem::CheckArgType(L, "Move", 'd', 1, -3) ||
	   ScriptSystem::CheckArgType(L, "Move", 'd', 2, -2) ||
	   ScriptSystem::CheckArgType(L, "Move", 'd', 3, -1)) {

    float l = lua_tonumber(L, -3);
    float t = lua_tonumber(L, -2);
    float v = lua_tonumber(L, -1);
    cam->Move(l, t, v);

  }
  else
    logger.info << "Wrong number or types of arguments. Possible uses are: "
		<< "Move(Vector<3, float>*) and "
		<< "Move(float, float, float)."
		<< " Call aborted." << logger.end;

  return 0;

}

int ScriptCamera::LookAt(lua_State* L) {

  if (!cam) {

    logger.info << "Camera not initialized. Call Aborted." << logger.end;
    return 0;

  }
  
  int nargs = lua_gettop(L);

  if (nargs == 1 ||
      ScriptSystem::CheckArgType(L, "LookAt", 'p', 1, -1)) {

    Vector<3, float>* point = (Vector<3, float>*) lua_touserdata(L, -1);
    cam->LookAt(*point);

  }
  else if (nargs == 3 || 
	   ScriptSystem::CheckArgType(L, "LookAt", 'd', 1, -3) ||
	   ScriptSystem::CheckArgType(L, "LookAt", 'd', 2, -2) ||
	   ScriptSystem::CheckArgType(L, "LookAt", 'd', 3, -1)) {

    float x = lua_tonumber(L, -3);
    float y = lua_tonumber(L, -2);
    float z = lua_tonumber(L, -1);
    cam->LookAt(x, y, z);

  }
  else
    logger.info << "Wrong number or types of arguments. Possible uses are: "
		<< "LookAt(Vector<3, float>*) and "
		<< "LookAt(float, float, float)."
		<< " Call aborted." << logger.end;

  return 0;

}

int ScriptCamera::Rotate(lua_State* L) {

  if (!cam) {

    logger.info << "Camera not initialized. Call Aborted." << logger.end;
    return 0;

  }

  int nargs = lua_gettop(L);

  if (nargs == 1 ||
      ScriptSystem::CheckArgType(L, "Rotate", 'p', 1, -1)) {
    
    Quaternion<float>* qua = (Quaternion<float>*) lua_touserdata(L, -1);
    cam->Rotate(*qua);

  }
  else if (nargs == 2 ||
	   ScriptSystem::CheckArgType(L, "Rotate", 'd', 1, -2) ||
	   ScriptSystem::CheckArgType(L, "Rotate", 'p', 2, -1)) {

    float angle = lua_tonumber(L, -2);
    Vector<3, float>* axis = (Vector<3, float>*) lua_touserdata(L, -1);
    cam->Rotate(angle, *axis);

  }
  else if (nargs == 3 || 
	   ScriptSystem::CheckArgType(L, "Rotate", 'd', 1, -3) ||
	   ScriptSystem::CheckArgType(L, "Rotate", 'd', 2, -2) ||
	   ScriptSystem::CheckArgType(L, "Rotate", 'd', 3, -1)) {

    float roll = lua_tonumber(L, -3);
    float pitch = lua_tonumber(L, -2);
    float yaw = lua_tonumber(L, -1);
    cam->Rotate(roll, pitch, yaw);

  }
  else
    logger.info << "Wrong number or types of arguments. Possible uses are: "
		<< "Rotate(Quaternion<float>*) and "
		<< "Rotate(float, Vector<3, float>*)"
		<< "Rotate(float, float, float)."
		<< " Call aborted." << logger.end;
 
  return 0;

}

int ScriptCamera::GetCamera(lua_State* L) {

  if (!cam) {

    logger.info << "Camera not initialized. Call Aborted." << logger.end;
    return 0;

  }

  if (ScriptSystem::CheckStackSize(L, "GetFollowCamera", 1))
    return 0;
  
  lua_pushlightuserdata(L, cam);
  return 1;

}
