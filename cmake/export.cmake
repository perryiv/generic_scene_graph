
################################################################################
#
#  Copyright (c) 2021, Perry L Miller IV
#  All rights reserved.
#  MIT License: https://opensource.org/licenses/mit-license.html
#
################################################################################

################################################################################
#
#  Configure how this project gets imported into other cmake projects.
#
################################################################################

# Define how things are installed.
if ( WIN32 AND NOT CYGWIN )
  set ( INSTALL_CMAKE_DIR cmake )
else()
  set ( INSTALL_CMAKE_DIR lib/cmake/${PROJECT_NAME} )
endif()

# Specify how things are exported.
export ( TARGETS ${PROJECT_NAME}_base
  FILE ${PROJECT_BINARY_DIR}/${PROJECT_NAME}_targets.cmake
)
export ( TARGETS ${PROJECT_NAME}_scene
  FILE ${PROJECT_BINARY_DIR}/${PROJECT_NAME}_targets.cmake
)

# Export the package.
export ( PACKAGE ${PROJECT_NAME}_base ${PROJECT_NAME}_scene )

# Compute relative path from cmake export files to the include directory.
file ( RELATIVE_PATH REL_INCLUDE_DIR /${INSTALL_CMAKE_DIR} /include )

# Create export configuration file for the build tree.
set ( CONFIG_INCLUDE_DIRS ${PROJECT_SOURCE_DIR} ${PROJECT_BINARY_DIR} )
configure_file (
  ${CMAKE_CURRENT_LIST_DIR}/${PROJECT_NAME}_base-config.cmake.in
  ${PROJECT_BINARY_DIR}/${PROJECT_NAME}_base-config.cmake @ONLY
)
configure_file (
  ${CMAKE_CURRENT_LIST_DIR}/${PROJECT_NAME}_scene-config.cmake.in
  ${PROJECT_BINARY_DIR}/${PROJECT_NAME}_scene-config.cmake @ONLY
)

# Create export configuration file for the install tree.
set ( CONFIG_INCLUDE_DIRS \${GSG_CMAKE_DIR}/${REL_INCLUDE_DIR} )
configure_file (
  ${CMAKE_CURRENT_LIST_DIR}/${PROJECT_NAME}_base-config.cmake.in
  ${PROJECT_BINARY_DIR}${CMAKE_FILES_DIRECTORY}/${PROJECT_NAME}_base-config.cmake @ONLY
)
configure_file (
  ${CMAKE_CURRENT_LIST_DIR}/${PROJECT_NAME}_scene-config.cmake.in
  ${PROJECT_BINARY_DIR}${CMAKE_FILES_DIRECTORY}/${PROJECT_NAME}_scene-config.cmake @ONLY
)

# Create export version file for both the build and install tree.
configure_file (
  ${CMAKE_CURRENT_LIST_DIR}/${PROJECT_NAME}_base-config-version.cmake.in
  ${PROJECT_BINARY_DIR}/${PROJECT_NAME}_base-config-version.cmake @ONLY
)
configure_file (
  ${CMAKE_CURRENT_LIST_DIR}/${PROJECT_NAME}_scene-config-version.cmake.in
  ${PROJECT_BINARY_DIR}/${PROJECT_NAME}_scene-config-version.cmake @ONLY
)

# Install the config files that cmake will use when another project uses this one.
install ( FILES
  ${PROJECT_BINARY_DIR}${CMAKE_FILES_DIRECTORY}/${PROJECT_NAME}_base-config.cmake
  ${PROJECT_BINARY_DIR}/${PROJECT_NAME}_base-config-version.cmake
  DESTINATION ${INSTALL_CMAKE_DIR}
)
install ( FILES
  ${PROJECT_BINARY_DIR}${CMAKE_FILES_DIRECTORY}/${PROJECT_NAME}_scene-config.cmake
  ${PROJECT_BINARY_DIR}/${PROJECT_NAME}_scene-config-version.cmake
  DESTINATION ${INSTALL_CMAKE_DIR}
)

# Install the export target files that cmake will use when another project uses this one.
install (
  EXPORT ${PROJECT_NAME}_targets
  DESTINATION ${INSTALL_CMAKE_DIR}
)
