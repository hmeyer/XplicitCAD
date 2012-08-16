cmake_minimum_required(VERSION 2.8)
 
PROJECT(MarchingCubes)
 
find_package(VTK REQUIRED)
include(${VTK_USE_FILE})
 
if (APPLE)
  add_executable(MarchingCubes MACOSX_BUNDLE MarchingCubes.cxx)
else()
  add_executable(MarchingCubes MarchingCubes.cxx)
endif()
 
if(VTK_LIBRARIES)
  target_link_libraries(MarchingCubes ${VTK_LIBRARIES})
else()
  target_link_libraries(MarchingCubes vtkHybrid )
endif()

