
################################################################################
#
#  Copyright (c) 2020, Perry L Miller IV
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
set ( SOURCE_FILES_BASE
  Containers/TypedArrays.cpp
  Objects/Object.cpp
)

# Set the library names.
set (  BASE_LIBRARY_NAME ${PROJECT_NAME}_base  )

# Make the libraries using the source files.
add_library (  ${BASE_LIBRARY_NAME} ${SOURCE_FILES_BASE}  )

# We are compling generic_scene_graph.
target_compile_definitions (  ${BASE_LIBRARY_NAME} PRIVATE COMPILING_GSG_BASE  )

if ( NOT BUILD_SHARED_LIBS )
  target_compile_definitions (  ${BASE_LIBRARY_NAME} PUBLIC GSG_BASE_STATIC_DEFINE  )
endif()

# Tell cmake that other projects that use these ones will need our header files.
target_include_directories (
  ${BASE_LIBRARY_NAME} PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../../>
  $<BUILD_INTERFACE:${GSG_CONFIG_DIR_OUTPUT}>
  $<INSTALL_INTERFACE:include>
)

# CMake will automatically add -I, -L, and -D (etc) appropriately.
target_link_libraries ( ${BASE_LIBRARY_NAME} PUBLIC
  usul
)

# Bake the version into the file name and create symlinks if appropriate.
set_target_properties ( ${BASE_LIBRARY_NAME} PROPERTIES
  VERSION ${PROJECT_VERSION}
  SOVERSION ${PROJECT_VERSION_MAJOR}
)
