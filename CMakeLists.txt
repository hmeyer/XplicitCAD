cmake_minimum_required(VERSION 2.8)
 
PROJECT(ImplicitSphere)
 
find_package(VTK REQUIRED)
include(${VTK_USE_FILE})
 
if (APPLE)
  add_executable(ImplicitSphere MACOSX_BUNDLE ImplicitSphere.cxx)
else()
  add_executable(ImplicitSphere ImplicitSphere.cxx)
endif()
 
if(VTK_LIBRARIES)
  target_link_libraries(ImplicitSphere ${VTK_LIBRARIES})
else()
  target_link_libraries(ImplicitSphere vtkHybrid )
endif()
