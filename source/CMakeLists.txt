
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

# Does the user want to generate code coverage?
option ( GSG_ENABLE_CODE_COVERAGE
  "Generate test code coverage in supported configurations" OFF )
if ( GSG_ENABLE_CODE_COVERAGE )
  if ( UNIX ) # True for Linux, Mac, and Cygwin.
    message ( "   -- Generating test code coverage data" )
    add_compile_options ( -fprofile-arcs -ftest-coverage )
    if ( "${CMAKE_CXX_COMPILER_ID}" MATCHES "Clang" )
      add_link_options ( --coverage )
    else() # GCC
      link_libraries ( gcov )
    endif()
  else()
    message ( WARNING "Test code coverage data not supported with current compiler" )
  endif()
endif()

# We want position independent code.
set ( CMAKE_POSITION_INDEPENDENT_CODE ON )

# Define a variable that holds all the source files.
set ( SOURCE_FILES
  GSG/Base/Containers/TypedArrays.cpp
  GSG/Base/Objects/Object.cpp
  GSG/Scene/Nodes/Groups/Group.cpp
  GSG/Scene/Nodes/Groups/Transform.cpp
  GSG/Scene/Nodes/Node.cpp
  GSG/Scene/Nodes/Shapes/Geometry.cpp
  GSG/Scene/Nodes/Shapes/Shape.cpp
  GSG/Scene/Primitives/DrawArrays.cpp
  GSG/Scene/Primitives/DrawElements.cpp
  GSG/Scene/Primitives/PrimitiveSet.cpp
  GSG/Scene/Visitors/Intersection/Intersect.cpp
  GSG/Scene/Visitors/Visitor.cpp
)

set ( THIS_LIBRARY_NAME ${PROJECT_NAME} )

# Make the library using the source files.
# Hey CMake, here is a library and all the stuff you need to know about it.
add_library ( ${THIS_LIBRARY_NAME} ${SOURCE_FILES} )

# We are compling generic_scene_graph.
target_compile_definitions ( ${THIS_LIBRARY_NAME} PRIVATE COMPILING_GSG )

if ( NOT BUILD_SHARED_LIBS )
  target_compile_definitions ( ${THIS_LIBRARY_NAME} PUBLIC GSG_STATIC_DEFINE )
endif()

# Tell cmake that other projects that use this one will need our header files.
target_include_directories (
  ${THIS_LIBRARY_NAME} PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
  $<BUILD_INTERFACE:${GSG_CONFIG_DIR_OUTPUT}>
  $<INSTALL_INTERFACE:include>
)

# CMake will automatically add -I, -L, and -D (etc) appropriately.
target_link_libraries ( ${THIS_LIBRARY_NAME} PUBLIC
  usul
  immer
)

# Bake the version into the file name and create symlinks if appropriate.
set_target_properties ( ${THIS_LIBRARY_NAME} PROPERTIES
  VERSION ${PROJECT_VERSION}
  SOVERSION ${PROJECT_VERSION_MAJOR}
)

# Tell cmake how to install the headers and binaries if the user types
# "make install" or compiles the Visual C++ INSTALL project. The default
# directory prefix is /usr/local or "C:/Program Files", and can be changed
# on the command line with -DCMAKE_INSTALL_PREFIX=/some/path.
install (
  TARGETS ${THIS_LIBRARY_NAME}
  EXPORT ${THIS_LIBRARY_NAME}_targets
  ARCHIVE DESTINATION lib
  LIBRARY DESTINATION lib
  RUNTIME DESTINATION bin
)
install (
  DIRECTORY GSG
  DESTINATION include FILES_MATCHING PATTERN "*.h"
)
