cmake_minimum_required(VERSION 2.8)
 
PROJECT(xplicit)
 
find_package(VTK REQUIRED)
include(${VTK_USE_FILE})

find_package(Lua51 REQUIRED)
include_directories(${LUA_INCLUDE_DIR})
 
if (APPLE)
  add_executable(xplicit MACOSX_BUNDLE Xplicit.cxx luabridge.cxx)
else()
  add_executable(xplicit Xplicit.cxx luabridge.cxx)
endif()
 
if(VTK_LIBRARIES)
  target_link_libraries(xplicit ${VTK_LIBRARIES} ${LUA_LIBRARIES} luabind)
else()
  target_link_libraries(xplicit vtkHybrid ${LUA_LIBRARIES} luabind)
endif()
