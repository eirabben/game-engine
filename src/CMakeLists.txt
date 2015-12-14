file(GLOB_RECURSE ENGINE_SRC "*.hpp" "*.cpp")

add_executable(GameEngine ${ENGINE_SRC})
install(TARGETS GameEngine RUNTIME DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})
