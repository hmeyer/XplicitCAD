/*
    This file is part of Xplicit.
    Copyright 2012 Henning Meyer

    Xplicit is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    Xplicit is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with Xplicit.  If not, see <http://www.gnu.org/licenses/>.
*/

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
  
