#===============================================================================
cmake_minimum_required (VERSION 3.12)

project ("AudioFile" VERSION 1.1.3
                     DESCRIPTION "A simple C++ library for reading and writing audio files."
                     HOMEPAGE_URL "https://github.com/adamstark/AudioFile")

#===============================================================================
include (GNUInstallDirs)

#===============================================================================
option (BUILD_TESTS "Build tests" ON)
option (BUILD_EXAMPLES "Build examples" ON)

#===============================================================================
set (AUDIOFILE_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/AudioFile.h)
source_group (TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${AUDIOFILE_SOURCES})

add_library (${PROJECT_NAME} INTERFACE ${AUDIOFILE_SOURCES})

#===============================================================================
target_include_directories (${PROJECT_NAME} INTERFACE
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
  $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>)

#===============================================================================
target_compile_features (${PROJECT_NAME} INTERFACE cxx_std_17)

#===============================================================================
if (BUILD_EXAMPLES)
  add_subdirectory (examples)
endif ()

if (BUILD_TESTS)
  enable_testing()
  add_subdirectory (tests)
endif ()

#===============================================================================
set (CMAKE_SUPPRESS_REGENERATION true)

#===============================================================================
include (CMakePackageConfigHelpers)

install (TARGETS ${PROJECT_NAME}
  EXPORT ${PROJECT_NAME}Targets
  LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
  RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
  ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
  INCLUDES DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)

install (FILES ${PROJECT_SOURCE_DIR}/AudioFile.h
  DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/${PROJECT_NAME}
)

install (EXPORT ${PROJECT_NAME}Targets
  FILE ${PROJECT_NAME}Targets.cmake
  NAMESPACE ${PROJECT_NAME}::
  DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/${PROJECT_NAME}
)

file (WRITE ${PROJECT_BINARY_DIR}/Config.cmake.in
  "@PACKAGE_INIT@\n\ninclude(\"\${CMAKE_CURRENT_LIST_DIR}/@PROJECT_NAME@Targets.cmake\")\n\ncheck_required_components(@PROJECT_NAME@)\n"
)

configure_package_config_file (
  ${PROJECT_BINARY_DIR}/Config.cmake.in
  ${PROJECT_BINARY_DIR}/${PROJECT_NAME}Config.cmake
  INSTALL_DESTINATION
  ${CMAKE_INSTALL_LIBDIR}/cmake/${PROJECT_NAME}
)

write_basic_package_version_file (
  ${PROJECT_BINARY_DIR}/${PROJECT_NAME}ConfigVersion.cmake
  VERSION ${PROJECT_VERSION}
  COMPATIBILITY SameMajorVersion
  ARCH_INDEPENDENT
)

install (FILES
  ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}Config.cmake
  ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}ConfigVersion.cmake
  DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/${PROJECT_NAME}
)
