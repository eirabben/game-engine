# Add all files to the build
file(GLOB_RECURSE ENGINE_SRC "*.hpp" "*.cpp")

# Add the executable from the source
add_executable(GameEngine ${ENGINE_SRC})

target_link_libraries(GameEngine ${SDL2_LIBRARY})
target_link_libraries(GameEngine ${OPENGL_LIBRARY})
set_property(TARGET GameEngine PROPERTY CXX_STANDARD 14)

# Install the product to the bin folder
install(TARGETS GameEngine RUNTIME DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})
