include_directories (doctest)
include_directories (${AudioFile_SOURCE_DIR})

add_definitions(-DPROJECT_BINARY_DIR="${CMAKE_CURRENT_BINARY_DIR}")

file (COPY test-audio DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
file (MAKE_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/audio-write-tests)

add_executable (Tests main.cpp GeneralTests.cpp WavLoadingTests.cpp AiffLoadingTests.cpp FileWritingTests.cpp)
target_compile_features (Tests PRIVATE cxx_std_17)
add_test (NAME Tests COMMAND Tests)

# add_executable (LoadingTests main.cpp WavLoadingTests.cpp AiffLoadingTests.cpp)
# target_compile_features (LoadingTests PRIVATE cxx_std_17)
# add_test (NAME LoadingTests COMMAND LoadingTests)