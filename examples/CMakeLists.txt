include_directories (${AudioFile_SOURCE_DIR})

add_definitions (-DPROJECT_BINARY_DIR="${CMAKE_CURRENT_BINARY_DIR}")
file (COPY test-audio.wav DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

add_executable (Examples examples.cpp)
target_link_libraries (Examples AudioFile)
