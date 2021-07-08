
################################################################################
#
#  Copyright (c) 2021, Perry L Miller IV
#  All rights reserved.
#  MIT License: https://opensource.org/licenses/mit-license.html
#
################################################################################

################################################################################
#
#  CMake file for the libraries.
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

# Also process the CMakeLists.txt files found in these directories.
add_subdirectory ( GSG/Base )
add_subdirectory ( GSG/Scene )
add_subdirectory ( GSG/Renderers )

# Tell cmake how to install the headers and binaries if the user types
# "make install" or compiles the Visual C++ INSTALL project. The default
# directory prefix is /usr/local or "C:/Program Files", and can be changed
# on the command line with -DCMAKE_INSTALL_PREFIX=/some/path.
install (
  TARGETS ${LIBRARY_NAME_BASE} ${LIBRARY_NAME_SCENE}
  EXPORT ${PROJECT_NAME}_targets
  ARCHIVE DESTINATION lib
  LIBRARY DESTINATION lib
  RUNTIME DESTINATION bin
)
install (
  DIRECTORY GSG
  DESTINATION include FILES_MATCHING PATTERN "*.h"
)
