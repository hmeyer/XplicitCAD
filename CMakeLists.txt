cmake_minimum_required(VERSION 2.8)
 
PROJECT(ImplicitSphere)
 
find_package(VTK REQUIRED)
include(${VTK_USE_FILE})
 
if (APPLE)
  add_executable(ImplicitTest MACOSX_BUNDLE ImplicitTest.cxx)
else()
  add_executable(ImplicitTest ImplicitTest.cxx)
endif()
 
if(VTK_LIBRARIES)
  target_link_libraries(ImplicitTest ${VTK_LIBRARIES})
else()
  target_link_libraries(ImplicitTest vtkHybrid )
endif()
