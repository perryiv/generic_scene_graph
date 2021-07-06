
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
set ( SOURCE_FILES_BASE
  GSG/Base/Containers/TypedArrays.cpp
  GSG/Base/Objects/Object.cpp
)
set ( SOURCE_FILES_SCENE
  GSG/Scene/Nodes/Groups/Group.cpp
  GSG/Scene/Nodes/Groups/Projection.cpp
  GSG/Scene/Nodes/Groups/Transform.cpp
  GSG/Scene/Nodes/Node.cpp
  GSG/Scene/Nodes/Shapes/Geometry.cpp
  GSG/Scene/Nodes/Shapes/Shape.cpp
  GSG/Scene/Primitives/DrawArrays.cpp
  GSG/Scene/Primitives/DrawElements.cpp
  GSG/Scene/Primitives/PrimitiveSet.cpp
  GSG/Scene/State/Container.cpp
  GSG/Scene/Visitors/Callbacks/Const.cpp
  GSG/Scene/Visitors/Callbacks/Modify.cpp
  GSG/Scene/Visitors/Intersection/Intersect.cpp
  GSG/Scene/Visitors/Visitor.cpp
)

# Set the library names.
set (  BASE_LIBRARY_NAME ${PROJECT_NAME}_base  )
set ( SCENE_LIBRARY_NAME ${PROJECT_NAME}_scene )

# Make the libraries using the source files.
add_library (  ${BASE_LIBRARY_NAME} ${SOURCE_FILES_BASE}  )
add_library ( ${SCENE_LIBRARY_NAME} ${SOURCE_FILES_SCENE} )

# We are compling generic_scene_graph.
target_compile_definitions (  ${BASE_LIBRARY_NAME} PRIVATE COMPILING_GSG_BASE  )
target_compile_definitions ( ${SCENE_LIBRARY_NAME} PRIVATE COMPILING_GSG_SCENE )

if ( NOT BUILD_SHARED_LIBS )
  target_compile_definitions (  ${BASE_LIBRARY_NAME} PUBLIC GSG_BASE_STATIC_DEFINE  )
  target_compile_definitions ( ${SCENE_LIBRARY_NAME} PUBLIC GSG_SCENE_STATIC_DEFINE )
endif()

# Tell cmake that other projects that use these ones will need our header files.
target_include_directories (
  ${BASE_LIBRARY_NAME} PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
  $<BUILD_INTERFACE:${GSG_CONFIG_DIR_OUTPUT}>
  $<INSTALL_INTERFACE:include>
)
target_include_directories (
  ${SCENE_LIBRARY_NAME} PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
  $<BUILD_INTERFACE:${GSG_CONFIG_DIR_OUTPUT}>
  $<INSTALL_INTERFACE:include>
)

# CMake will automatically add -I, -L, and -D (etc) appropriately.
target_link_libraries ( ${BASE_LIBRARY_NAME} PUBLIC
  usul
)
target_link_libraries ( ${SCENE_LIBRARY_NAME} PUBLIC
  ${BASE_LIBRARY_NAME}
  usul
  immer
)

# Bake the version into the file name and create symlinks if appropriate.
set_target_properties ( ${BASE_LIBRARY_NAME} PROPERTIES
  VERSION ${PROJECT_VERSION}
  SOVERSION ${PROJECT_VERSION_MAJOR}
)
set_target_properties ( ${SCENE_LIBRARY_NAME} PROPERTIES
  VERSION ${PROJECT_VERSION}
  SOVERSION ${PROJECT_VERSION_MAJOR}
)

# Tell cmake how to install the headers and binaries if the user types
# "make install" or compiles the Visual C++ INSTALL project. The default
# directory prefix is /usr/local or "C:/Program Files", and can be changed
# on the command line with -DCMAKE_INSTALL_PREFIX=/some/path.
install (
  TARGETS ${BASE_LIBRARY_NAME} ${SCENE_LIBRARY_NAME}
  EXPORT ${PROJECT_NAME}_targets
  ARCHIVE DESTINATION lib
  LIBRARY DESTINATION lib
  RUNTIME DESTINATION bin
)
install (
  DIRECTORY GSG
  DESTINATION include FILES_MATCHING PATTERN "*.h"
)
