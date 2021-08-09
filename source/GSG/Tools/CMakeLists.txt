
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
set ( SOURCE_FILES
  Tree/Layer.cpp
  Tree/Root.cpp
  Visitors/Callbacks/Const.cpp
  Visitors/Callbacks/Modify.cpp
  Visitors/Cull/Visitor.cpp
  Visitors/Intersection/Intersect.cpp
  Visitors/Update/Visitor.cpp
)

# Set the library names.
set ( LIBRARY_NAME ${PROJECT_NAME}_tools )

# Make the libraries using the source files.
add_library ( ${LIBRARY_NAME} ${SOURCE_FILES} )

# We are compling this library.
target_compile_definitions ( ${LIBRARY_NAME} PRIVATE COMPILING_GSG_TOOLS )

if ( NOT BUILD_SHARED_LIBS )
  target_compile_definitions ( ${LIBRARY_NAME} PUBLIC GSG_TOOLS_STATIC_DEFINE )
endif()

# Tell cmake that other projects that use these ones will need our header files.
target_include_directories (
  ${LIBRARY_NAME} PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../../>
  $<BUILD_INTERFACE:${GSG_CONFIG_DIR_OUTPUT}>
  $<INSTALL_INTERFACE:include>
)

# CMake will automatically add -I, -L, and -D (etc) appropriately.
target_link_libraries ( ${LIBRARY_NAME} PUBLIC
  ${PROJECT_NAME}_scene
)

# Bake the version into the file name and create symlinks if appropriate.
set_target_properties ( ${LIBRARY_NAME} PROPERTIES
  VERSION ${PROJECT_VERSION}
  SOVERSION ${PROJECT_VERSION_MAJOR}
)
