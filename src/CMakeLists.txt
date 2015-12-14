# Find GLFW library
find_package(GLFW REQUIRED)
if (GLFW_FOUND)
    include_directories(${GLFW_INCLUDE_DIR})
    link_libraries(${GLFW_LIBRARIES})
endif()

# Add all files to the build
file(GLOB_RECURSE ENGINE_SRC "*.hpp" "*.cpp")

# Add the executable from the source
add_executable(GameEngine ${ENGINE_SRC})

# Link with libraries
target_link_libraries(GameEngine ${GLFW_LIBRARIES})

# Install the product to the bin folder
install(TARGETS GameEngine RUNTIME DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})
