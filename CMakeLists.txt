cmake_minimum_required(VERSION 2.8)
 
PROJECT(xplicit)
 
find_package(VTK REQUIRED)
include(${VTK_USE_FILE})
 
if (APPLE)
  add_executable(xplicit MACOSX_BUNDLE Xplicit.cxx)
else()
  add_executable(xplicit Xplicit.cxx)
endif()
 
if(VTK_LIBRARIES)
  target_link_libraries(xplicit ${VTK_LIBRARIES})
else()
  target_link_libraries(xplicit vtkHybrid )
endif()
