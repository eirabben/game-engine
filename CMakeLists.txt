cmake_minimum_required(VERSION 2.6)
project(GameEngine)

# Set the output directory for the build
# https://stackoverflow.com/questions/6594796/how-do-i-make-cmake-output-into-a-bin-dir
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_SOURCE_DIR}/cmake/)

# Set directory for the source
set(PROJECT_SOURCE_DIR ${CMAKE_SOURCE_DIR}/src)

# Include SDL2
find_package(SDL2 REQUIRED)
if(SDL2_FOUND)
    include_directories(${SDL2_INCLUDE_DIR})
    link_libraries(${SDL2_LIBRARIES})
endif()

# Include OpenGL
find_package(OpenGL REQUIRED)
if (OPENGL_FOUND)
    include_directories(${OPENGL_INCLUDE_DIR})
    link_libraries(${OPENGL_LIBRARY})
endif()

# Add our source code directory
add_subdirectory(src)
