
################################################################################
#
#  Copyright (c) 2021, Perry L Miller IV
#  All rights reserved.
#  MIT License: https://opensource.org/licenses/mit-license.html
#
################################################################################

################################################################################
#
#  CMake file for the library.
#
################################################################################

# Define a variable that holds all the source files.
set ( SOURCE_FILES_SCENE
  Nodes/Groups/Group.cpp
  Nodes/Groups/Projection.cpp
  Nodes/Groups/Transform.cpp
  Nodes/Node.cpp
  Nodes/Shapes/Geometry.cpp
  Nodes/Shapes/Shape.cpp
  Primitives/DrawArrays.cpp
  Primitives/DrawElements.cpp
  Primitives/PrimitiveSet.cpp
  State/Container.cpp
  Visitors/Callbacks/Const.cpp
  Visitors/Callbacks/Modify.cpp
  Visitors/Intersection/Intersect.cpp
  Visitors/Visitor.cpp
)

# Set the library names.
set ( LIBRARY_NAME_SCENE ${PROJECT_NAME}_scene )

# Make the libraries using the source files.
add_library ( ${LIBRARY_NAME_SCENE} ${SOURCE_FILES_SCENE} )

# We are compling generic_scene_graph.
target_compile_definitions ( ${LIBRARY_NAME_SCENE} PRIVATE COMPILING_GSG_SCENE )

if ( NOT BUILD_SHARED_LIBS )
  target_compile_definitions ( ${LIBRARY_NAME_SCENE} PUBLIC GSG_SCENE_STATIC_DEFINE )
endif()

# Tell cmake that other projects that use these ones will need our header files.
target_include_directories (
  ${LIBRARY_NAME_SCENE} PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../../>
  $<BUILD_INTERFACE:${GSG_CONFIG_DIR_OUTPUT}>
  $<INSTALL_INTERFACE:include>
)

# CMake will automatically add -I, -L, and -D (etc) appropriately.
target_link_libraries ( ${LIBRARY_NAME_SCENE} PUBLIC
  ${PROJECT_NAME}_base
  usul
  immer
)

# Bake the version into the file name and create symlinks if appropriate.
set_target_properties ( ${LIBRARY_NAME_SCENE} PROPERTIES
  VERSION ${PROJECT_VERSION}
  SOVERSION ${PROJECT_VERSION_MAJOR}
)
