cmake_minimum_required(VERSION 2.6)
project(GameEngine)

# Set the output directory for the build
# https://stackoverflow.com/questions/6594796/how-do-i-make-cmake-output-into-a-bin-dir
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)

# Set directory for the source
set(PROJECT_SOURCE_DIR ${CMAKE_SOURCE_DIR}/src)

# Include GLFW
#add_subdirectory(${CMAKE_SOURCE_DIR}/deps/glfw)
#include_directories(${CMAKE_SOURCE_DIR}/deps/glfw/include)

add_subdirectory(src)

