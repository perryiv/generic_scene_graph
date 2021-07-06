
################################################################################
#
#  Copyright (c) 2020, Perry L Miller IV
#  All rights reserved.
#  MIT License: https://opensource.org/licenses/mit-license.html
#
################################################################################

################################################################################
#
#  CMake file for the test program.
#
################################################################################

# Need to include files from this directory.
include_directories ( ${CMAKE_CURRENT_SOURCE_DIR} )

# Define a variable that holds all the source files.
set ( SOURCE_FILES_BASE
  ./GSG/Base/Containers/Array.cpp
  ./GSG/Base/Containers/TypedArrays.cpp
  ./GSG/Main.cpp
  ./GSG/Version.cpp
)
set ( SOURCE_FILES_SCENE
  ./GSG/Scene/Nodes/Groups/Group.cpp
  ./GSG/Scene/Nodes/Groups/Transform.cpp
  ./GSG/Scene/Nodes/Shapes/Geometry.cpp
  ./GSG/Scene/Primitives/DrawElements.cpp
  ./GSG/Scene/State/Container.cpp
  ./GSG/Scene/Visitors/Callbacks.cpp
  ./GSG/Main.cpp
  ./GSG/Version.cpp
)

# Make an executable.
add_executable ( ${PROJECT_NAME}_base_test  ${SOURCE_FILES_BASE}  )
add_executable ( ${PROJECT_NAME}_scene_test ${SOURCE_FILES_SCENE} )

# Append a "d" to the file name if this is a debug build.
# Unlike with the library files, this does not happen automatically.
# if ( ( DEFINED CMAKE_DEBUG_POSTFIX ) AND ( NOT ${CMAKE_DEBUG_POSTFIX} STREQUAL "" ) )
if ( CMAKE_BUILD_TYPE STREQUAL "Debug" )
  set_target_properties ( ${PROJECT_NAME}_base_test  PROPERTIES DEBUG_POSTFIX ${CMAKE_DEBUG_POSTFIX} )
  set_target_properties ( ${PROJECT_NAME}_scene_test PROPERTIES DEBUG_POSTFIX ${CMAKE_DEBUG_POSTFIX} )
endif()

# Tell cmake we are going to use these libraries.
# It will automatically add -I, -L, and -D (etc) appropriately.
target_link_libraries ( ${PROJECT_NAME}_base_test PRIVATE
  ${PROJECT_NAME}_base
  Catch2::Catch2
)
target_link_libraries ( ${PROJECT_NAME}_scene_test PRIVATE
  ${PROJECT_NAME}_scene
  Catch2::Catch2
)

# Run a custom command to delete all the stale code-coverage files.
# https://stackoverflow.com/questions/47393377/annoying-error-message-cannot-merge-previous-gcda-file
# This has to come after the target is declared above.
if ( GSG_ENABLE_CODE_COVERAGE )
  if ( "${CMAKE_CXX_COMPILER_ID}" MATCHES "Clang" )
    add_custom_command ( TARGET ${PROJECT_NAME}_base_test
      PRE_LINK COMMAND find . -name "*.gcda" -print0 | xargs -0 rm
    )
    add_custom_command ( TARGET ${PROJECT_NAME}_scene_test
      PRE_LINK COMMAND find . -name "*.gcda" -print0 | xargs -0 rm
    )
  endif()
endif()
