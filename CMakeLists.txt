
################################################################################
#
#  Copyright (c) 2020, Perry L Miller IV
#  All rights reserved.
#  MIT License: https://opensource.org/licenses/mit-license.html
#
################################################################################

################################################################################
#
#  Top-level CMake file for the generic_scene_graph project.
#
################################################################################

# We use the add_compile_definitions command.
# https://cmake.org/cmake/help/v3.12/release/3.12.html
cmake_minimum_required ( VERSION 3.12.0 )

# The name of this project.
project ( generic_scene_graph VERSION 0.0.0 LANGUAGES CXX )

# Default to building as a shared library.
if ( NOT DEFINED BUILD_SHARED_LIBS )
  set ( BUILD_SHARED_LIBS ON )
endif()

# Use this C++ standard unless the user specifies otherwise with:
# cmake path/to/source/dir -DCMAKE_CXX_STANDARD=14
if ( NOT DEFINED CMAKE_CXX_STANDARD )
  set ( CMAKE_CXX_STANDARD 17 )
endif()

# Turn off compiler-specific extensions by default.
if ( NOT DEFINED CMAKE_CXX_EXTENSIONS )
  set ( CMAKE_CXX_EXTENSIONS OFF )
endif()

# Make default __attribute__ visibility hidden not public to hide non-exported symbols.
# It is not working on Mac so we disable it.
if ( NOT APPLE )
  set ( CMAKE_CXX_VISIBILITY_PRESET hidden )
  set ( CMAKE_VISIBILITY_INLINES_HIDDEN ON )
endif()

# A convenient variable for telling the compiler to use these header files.
set ( GENERIC_SCENE_GRAPH_CONFIG_DIR_INPUT  ${CMAKE_CURRENT_SOURCE_DIR}/config )
set ( GENERIC_SCENE_GRAPH_CONFIG_DIR_OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/config )

# Set the version.
configure_file (
  ${GENERIC_SCENE_GRAPH_CONFIG_DIR_INPUT}/Version.h.in
  ${GENERIC_SCENE_GRAPH_CONFIG_DIR_OUTPUT}/GSG/Version.h )

# Add options here as needed for config file.

# Now that we have all the configuration options we can write the file.
configure_file (
  ${GENERIC_SCENE_GRAPH_CONFIG_DIR_INPUT}/Config.h.in
  ${GENERIC_SCENE_GRAPH_CONFIG_DIR_OUTPUT}/GSG/Config.h )

# Install generated files wherever the user specified to install things.
install (
  DIRECTORY ${GENERIC_SCENE_GRAPH_CONFIG_DIR_OUTPUT}/GSG
  DESTINATION include
  FILES_MATCHING PATTERN "*.h"
)

# Find and use usul. Set usul_ROOT environment variable to:
# 1) where it is installed, or
# 2) it's build directory.
find_package ( usul REQUIRED )

# Find boost.
find_package ( Boost REQUIRED )

# Does the user want strict warnings?
option ( GENERIC_SCENE_GRAPH_ENABLE_STRICT_WARNINGS "Enable strict warnings" ON )
if ( GENERIC_SCENE_GRAPH_ENABLE_STRICT_WARNINGS )
  message ( "   -- Enabling strict warnings" )
  if ( MSVC ) # Also true for Intel compiler. Means "looks like Visual C++".
    add_compile_options ( /W4 )
  else()
    add_compile_options ( -Wall -Wextra -pedantic -pedantic-errors -Wconversion -Wsign-conversion )
  endif()
endif()

# Does the user want to treat warnings the same as errors?
option ( GENERIC_SCENE_GRAPH_TREAT_WARNINGS_LIKE_ERRORS "Treat warnings like errors" ON )
if ( GENERIC_SCENE_GRAPH_TREAT_WARNINGS_LIKE_ERRORS )
  message ( "   -- Treating warnings like errors" )
  if ( MSVC ) # Also true for Intel compiler. Means "looks like Visual C++".
    add_compile_options ( /WX )
  else()
    add_compile_options ( -Werror )
  endif()
endif()

# Does the user want to build the tests?
option ( GENERIC_SCENE_GRAPH_BUILD_TESTS "Build the tests" OFF )

# Need Catch2 to build the tests
if ( GENERIC_SCENE_GRAPH_BUILD_TESTS )
  find_package ( Catch2 REQUIRED )
endif()

# Set default postfix if none was given on the command line.
if ( NOT DEFINED CMAKE_DEBUG_POSTFIX )
  set ( CMAKE_DEBUG_POSTFIX "_d" )
endif()

# For debug builds we want the _DEBUG preprocessor symbol to be defined.
add_compile_definitions ( $<$<CONFIG:Debug>:_DEBUG> )

# Also process the CMakeLists.txt files found in these directories.
add_subdirectory ( source )
if ( GENERIC_SCENE_GRAPH_BUILD_TESTS )
  add_subdirectory ( tests ) # The tests.
endif()

# Configure how this project gets imported into other cmake projects.
include ( ${CMAKE_CURRENT_SOURCE_DIR}/cmake/export.cmake )
