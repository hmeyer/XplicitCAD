cmake_minimum_required(VERSION 2.8)
 
PROJECT(xplicitCAD)

SET( xplicitSrc 
	main/Xplicit.cpp
	main/main.cpp
	main/mainwindow.cpp
	main/implicitwidget.cpp
	primitives/primitive.cpp
	primitives/sphere.cpp
	primitives/boolean.cpp
	primitives/boundingBox.cpp
	lua/luabridge.cpp
)

SET( HeaderDirs
	main
	lua
	primitives
)

SET( UIS 
	ui/MainWindow.ui 
)

SET ( QVTKMocHeaders
	main/mainwindow.h
)
 
find_package(VTK REQUIRED)
include(${VTK_USE_FILE})

find_package(Lua51 REQUIRED)
include_directories(${LUA_INCLUDE_DIR})

SET(QT_MOC_EXECUTABLE ${VTK_QT_MOC_EXECUTABLE} CACHE FILEPATH "")
SET(QT_UIC_EXECUTABLE ${VTK_QT_UIC_EXECUTABLE} CACHE FILEPATH "")
SET(QT_QMAKE_EXECUTABLE ${VTK_QT_QMAKE_EXECUTABLE} CACHE FILEPATH "")
SET(DESIRED_QT_VERSION ${VTK_DESIRED_QT_VERSION} CACHE FILEPATH "")
FIND_PACKAGE(Qt)
IF(QT_USE_FILE)
  INCLUDE(${QT_USE_FILE})
ELSE(QT_USE_FILE)
  SET(QT_LIBRARIES   ${QT_QT_LIBRARY})
ENDIF(QT_USE_FILE)

IF(NOT DESIRED_QT_VERSION MATCHES 4)
	MESSAGE(FATAL_ERROR "Need QT Version >= 4 build into VTK")
ENDIF(NOT DESIRED_QT_VERSION MATCHES 4)

ADD_DEFINITIONS(-ftemplate-depth-100)

INCLUDE_DIRECTORIES(
	${HeaderDirs}
  	${QT_INCLUDE_DIR} ${QT_QTGUI_INCLUDE_DIR} ${QT_QTCORE_INCLUDE_DIR}
	${CMAKE_CURRENT_BINARY_DIR} ${CMAKE_CURRENT_SOURCE_DIR}
	${QWT_INCLUDE_DIR}
)

QT4_WRAP_UI( xplicitSrc ${UIS} )
QT4_WRAP_CPP( xplicitSrc ${QVTKMocHeaders} )

SET( fullSrc ${xplicitSrc} ${MOCSrcs})
 
if (APPLE)
  add_executable(xplicitCAD MACOSX_BUNDLE ${fullSrc})
else()
  add_executable(xplicitCAD ${fullSrc})
endif()
 
SET( fullLib  ${LUA_LIBRARIES} QVTK luabind qscintilla2 ${QT_LIBRARIES})

if(VTK_LIBRARIES)
  target_link_libraries(xplicitCAD ${VTK_LIBRARIES} ${fullLib})
else()
  target_link_libraries(xplicitCAD vtkHybrid ${fullLib})
endif()
