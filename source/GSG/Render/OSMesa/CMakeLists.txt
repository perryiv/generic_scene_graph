
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
set ( SOURCE_FILES_RENDERER_OSMESA
  Renderer.cpp
)

# Set the library names.
set ( LIBRARY_NAME_RENDERER_OSMESA ${PROJECT_NAME}_renderer_osmesa )

# Make the libraries using the source files.
add_library ( ${LIBRARY_NAME_RENDERER_OSMESA} ${SOURCE_FILES_RENDERER_OSMESA} )

# We are compling generic_scene_graph.
target_compile_definitions ( ${LIBRARY_NAME_RENDERER_OSMESA} PRIVATE COMPILING_GSG_RENDERER_OSMESA )

if ( NOT BUILD_SHARED_LIBS )
  target_compile_definitions ( ${LIBRARY_NAME_RENDERER_OSMESA} PUBLIC GSG_RENDERER_OSMESA_STATIC_DEFINE )
endif()

# Tell cmake that other projects that use these ones will need our header files.
target_include_directories (
  ${LIBRARY_NAME_RENDERER_OSMESA} PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../../../>
  $<BUILD_INTERFACE:${GSG_CONFIG_DIR_OUTPUT}>
  $<INSTALL_INTERFACE:include>
)

# Find OSMesa.
find_package ( OSMesa REQUIRED )

# CMake will automatically add -I, -L, and -D (etc) appropriately.
target_link_libraries ( ${LIBRARY_NAME_RENDERER_OSMESA} PUBLIC
  ${PROJECT_NAME}_scene
  ${PROJECT_NAME}_base
  usul
  OSMesa::OSMesa
)

# Bake the version into the file name and create symlinks if appropriate.
set_target_properties ( ${LIBRARY_NAME_RENDERER_OSMESA} PROPERTIES
  VERSION ${PROJECT_VERSION}
  SOVERSION ${PROJECT_VERSION_MAJOR}
)
