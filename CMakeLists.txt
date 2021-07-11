
################################################################################
#
#  Copyright (c) 2021, Perry L Miller IV
#  All rights reserved.
#  MIT License: https://opensource.org/licenses/mit-license.html
#
################################################################################

################################################################################
#
#  Top-level CMake file for the generic_scene_graph project.
#
################################################################################

# Without this version or greater we get this error in Azure Pipelines:
# "make: *** No rule to make target 'test'.  Stop."
cmake_minimum_required ( VERSION 3.13.0 )

# Get the version from this file.
file ( STRINGS ${CMAKE_CURRENT_LIST_DIR}/version.txt PROJECT_VERSION )

# The name of this project.
project ( gsg VERSION ${PROJECT_VERSION} LANGUAGES CXX )

# Changes to the version file should trigger a re-configuration.
set_property ( DIRECTORY APPEND PROPERTY CMAKE_CONFIGURE_DEPENDS ${CMAKE_CURRENT_LIST_DIR}/version.txt )

# Default to building as a shared library
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

# Make VC++ more standard compliant.
if ( MSVC )
  add_compile_options ( /permissive- /Zc:__cplusplus )
endif()

# Make default __attribute__ visibility hidden not public to hide non-exported symbols.
# It is not working on Mac so we disable it.
if ( NOT APPLE )
  set ( CMAKE_CXX_VISIBILITY_PRESET hidden )
  set ( CMAKE_VISIBILITY_INLINES_HIDDEN ON )
endif()

# A convenient variable for telling the compiler to use these header files.
set ( GSG_CONFIG_DIR_INPUT  ${CMAKE_CURRENT_SOURCE_DIR}/config )
set ( GSG_CONFIG_DIR_OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/config )

# Tell CMake to not skip using rpath.
set ( CMAKE_SKIP_RPATH OFF )

# Tell the linkers to write their output files here.
set ( CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin )
set ( CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib )
set ( CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib )

# Does the user want to ignore these warning?
if ( MSVC ) # Also true for Intel compiler. Means "looks like Visual C++".
  option ( GSG_IGNORE_VCPP_WARNING_4251
    "Use a pragma to ignore Visual C++ warning 4251" ON )
  option ( GSG_IGNORE_VCPP_WARNING_4275
    "Use a pragma to ignore Visual C++ warning 4275" ON )
endif()

# Does the user want to be able to install this project.
if ( "${CMAKE_PROJECT_NAME}" STREQUAL "${PROJECT_NAME}" )
  set ( ${PROJECT_NAME}_INSTALL_DEFAULT ON )
else()
  set ( ${PROJECT_NAME}_INSTALL_DEFAULT OFF )
endif()
option ( ${PROJECT_NAME}_INSTALL "Able to install ${PROJECT_NAME}" ${${PROJECT_NAME}_INSTALL_DEFAULT} )

# Install generated files wherever the user specified to install things.
if ( ${PROJECT_NAME}_INSTALL )
  install (
    DIRECTORY ${GSG_CONFIG_DIR_OUTPUT}/GSG
    DESTINATION include
    FILES_MATCHING PATTERN "*.h"
  )
endif()

# Append to the cmake module path to help it find some packages.
list ( APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake )
if ( DEFINED ENV{DEVELOPMENT_DEPENDENCIES_DIR} )
  list ( APPEND CMAKE_MODULE_PATH $ENV{DEVELOPMENT_DEPENDENCIES_DIR} )
endif()

# Find usul.
find_package ( usul REQUIRED )
message ( "-- Found usul ${usul_VERSION}" )

# Find immer.
find_package ( Immer REQUIRED )

# Find boost.
find_package ( Boost REQUIRED )

# Does the user want strict warnings?
option ( GSG_ENABLE_STRICT_WARNINGS "Enable strict warnings" ON )
if ( GSG_ENABLE_STRICT_WARNINGS )
  message ( "   -- Enabling strict warnings" )
  if ( MSVC ) # Also true for Intel compiler. Means "looks like Visual C++".
    add_compile_options ( /W4 )
  else()
    add_compile_options ( -Wall -Wextra -pedantic -pedantic-errors -Wconversion -Wsign-conversion )
  endif()
endif()

# Does the user want to treat warnings the same as errors?
option ( GSG_TREAT_WARNINGS_LIKE_ERRORS "Treat warnings like errors" ON )
if ( GSG_TREAT_WARNINGS_LIKE_ERRORS )
  message ( "   -- Treating warnings like errors" )
  if ( MSVC ) # Also true for Intel compiler. Means "looks like Visual C++".
    add_compile_options ( /WX )
  else()
    add_compile_options ( -Werror )
  endif()
endif()

# Does the user want to build the tests?
option ( GSG_BUILD_TESTS "Build the tests" OFF )

# Need Catch2 to build the tests
if ( GSG_BUILD_TESTS )
  find_package ( Catch2 REQUIRED )
endif()

# Set default postfix if none was given on the command line.
if ( NOT DEFINED CMAKE_DEBUG_POSTFIX )
  set ( CMAKE_DEBUG_POSTFIX "_d" )
endif()

# Now that we have all the configuration options we can write these files.
configure_file (
  ${GSG_CONFIG_DIR_INPUT}/Version.h.in
  ${GSG_CONFIG_DIR_OUTPUT}/GSG/Version.h )
configure_file (
  ${GSG_CONFIG_DIR_INPUT}/Config.h.in
  ${GSG_CONFIG_DIR_OUTPUT}/GSG/Config.h )

# For debug builds we want the _DEBUG preprocessor symbol to be defined.
add_compile_definitions ( $<$<CONFIG:Debug>:_DEBUG> )

# Also process the CMakeLists.txt files found in these directories.
add_subdirectory ( source )
if ( GSG_BUILD_TESTS )
  enable_testing()
  add_subdirectory ( tests ) # The tests.
endif()

# Configure how this project gets imported into other cmake projects.
# include ( ${CMAKE_CURRENT_SOURCE_DIR}/cmake/export.cmake )
