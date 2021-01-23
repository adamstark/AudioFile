#===============================================================================
cmake_minimum_required (VERSION 3.12)

project ("AudioFile" VERSION 1.0.9
                     DESCRIPTION "A simple C++ library for reading and writing audio files."
                     HOMEPAGE_URL "https://github.com/adamstark/AudioFile")

#===============================================================================
include (GNUInstallDirs)

#===============================================================================
add_library (${PROJECT_NAME} INTERFACE)

#===============================================================================
target_include_directories (
  ${PROJECT_NAME}
  INTERFACE $<BUILD_INTERFACE:${${PROJECT_NAME}_SOURCE_DIR}>
            $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>)

#===============================================================================
target_compile_features (${PROJECT_NAME} INTERFACE cxx_std_11)

#===============================================================================
add_subdirectory (examples)

enable_testing()
add_subdirectory (tests)

#===============================================================================
set (CMAKE_SUPPRESS_REGENERATION true)