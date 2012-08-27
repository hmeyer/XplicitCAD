extern "C"
{
        #include "lua.h"
        #include "lualib.h"
        #include "lauxlib.h"
}

#include <luabind/luabind.hpp>
#include <iostream>
#include <string>

// We don't want to write std:: every time we're displaying some debug output
using namespace std;

// --------------------------------------------------------------------------------------------- //

// Put your testing code here...

void luatest() {
  // Create a new lua state
  lua_State *myLuaState = luaL_newstate();
 
  // Connect LuaBind to this lua state
  luabind::open(myLuaState);
 
  // Define a lua function that we can call
  luaL_dostring(
    myLuaState,
    "function add(first, second)\n"
    "  return first + second\n"
    "end\n"
  );
 
  cout << "Lua Test Result: "
       << luabind::call_function<int>(myLuaState, "add", 2, 3)
       << endl;
 
  lua_close(myLuaState);
}
  
