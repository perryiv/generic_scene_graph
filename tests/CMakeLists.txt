
################################################################################
#
#  Copyright (c) 2021, Perry L Miller IV
#  All rights reserved.
#  MIT License: https://opensource.org/licenses/mit-license.html
#
################################################################################

################################################################################
#
#  CMake file for the test programs.
#
################################################################################

# Turn on testing.
enable_testing()

# The arguments passed to the test programs.
set ( TEST_ARGUMENTS --abort --use-colour=yes --durations=no )

# Need to include files from this directory.
include_directories ( ${CMAKE_CURRENT_SOURCE_DIR} )

# Process the CMakeLists.txt files found in these directories.
add_subdirectory ( GSG/Base )
add_subdirectory ( GSG/Scene )
add_subdirectory ( GSG/Renderers )
