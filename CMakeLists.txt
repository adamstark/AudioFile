#===============================================================================
cmake_minimum_required (VERSION 3.12)

project ("AudioFile" VERSION 1.1.1
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
