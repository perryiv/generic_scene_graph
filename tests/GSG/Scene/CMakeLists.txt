
################################################################################
#
#  Copyright (c) 2021, Perry L Miller IV
#  All rights reserved.
#  MIT License: https://opensource.org/licenses/mit-license.html
#
################################################################################

################################################################################
#
#  CMake file for the test program.
#
################################################################################

# Define a variable that holds all the source files.
set ( SOURCE_FILES_SCENE
  Nodes/Groups/Group.cpp
  Nodes/Groups/Transform.cpp
  Nodes/Shapes/Geometry.cpp
  Primitives/DrawElements.cpp
  State/Container.cpp
  Visitors/Callbacks.cpp
  ../Main.cpp
  ../Version.cpp
)

# Make an executable.
add_executable ( ${PROJECT_NAME}_scene_test ${SOURCE_FILES_SCENE} )

# Append a "d" to the file name if this is a debug build.
# Unlike with the library files, this does not happen automatically.
# if ( ( DEFINED CMAKE_DEBUG_POSTFIX ) AND ( NOT ${CMAKE_DEBUG_POSTFIX} STREQUAL "" ) )
if ( CMAKE_BUILD_TYPE STREQUAL "Debug" )
  set_target_properties ( ${PROJECT_NAME}_scene_test PROPERTIES DEBUG_POSTFIX ${CMAKE_DEBUG_POSTFIX} )
endif()

# Tell cmake we are going to use these libraries.
# It will automatically add -I, -L, and -D (etc) appropriately.
target_link_libraries ( ${PROJECT_NAME}_scene_test PRIVATE
  ${PROJECT_NAME}_scene
  ${PROJECT_NAME}_base
  Catch2::Catch2
)

# Run a custom command to delete all the stale code-coverage files.
# https://stackoverflow.com/questions/47393377/annoying-error-message-cannot-merge-previous-gcda-file
# This has to come after the target is declared above.
if ( GSG_ENABLE_CODE_COVERAGE )
  if ( "${CMAKE_CXX_COMPILER_ID}" MATCHES "Clang" )
    add_custom_command ( TARGET ${PROJECT_NAME}_scene_test
      PRE_LINK COMMAND find . -name "*.gcda" -print0 | xargs -0 rm
    )
  endif()
endif()

# Add a test.
add_test (
  NAME ${PROJECT_NAME}_scene_test
  COMMAND ${PROJECT_NAME}_scene_test ${TEST_ARGUMENTS}
)
