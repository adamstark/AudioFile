#===============================================================================
cmake_minimum_required (VERSION 3.19)

project ("AudioFile" VERSION 1.1.0
                     DESCRIPTION "A simple C++ library for reading and writing audio files."
                     HOMEPAGE_URL "https://github.com/adamstark/AudioFile")

#===============================================================================
include (CMakePackageConfigHelpers)
include (GNUInstallDirs)

#===============================================================================
option (BUILD_TESTS "Build tests" ON)
option (BUILD_EXAMPLES "Build examples" ON)

#===============================================================================
add_library (${PROJECT_NAME} INTERFACE)
target_sources (${PROJECT_NAME} PRIVATE AudioFile.h)

#===============================================================================
if(MSVC)
  # needed for M_PI macro
  add_definitions(-D_USE_MATH_DEFINES)
endif()

#===============================================================================
target_include_directories (
  ${PROJECT_NAME}
  INTERFACE $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}>
            $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>)

#===============================================================================
target_compile_features (${PROJECT_NAME} INTERFACE cxx_std_11)

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
install (TARGETS ${PROJECT_NAME}
  EXPORT ${PROJECT_NAME}Targets
  LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
  RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
  ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
  INCLUDES DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)

install (FILES ${PROJECT_SOURCE_DIR}/AudioFile.h
  DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/AudioFile
)

install(EXPORT ${PROJECT_NAME}Targets
    FILE ${PROJECT_NAME}Targets.cmake
    NAMESPACE ${PROJECT_NAME}::
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/${PROJECT_NAME}
)

configure_package_config_file (
  ${PROJECT_SOURCE_DIR}/cmake/${PROJECT_NAME}Config.cmake.in
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
