if (NOT GLFW_FOUND)

find_path(GLFW_INCLUDE_DIR GLFW/glfw3.h
  PATHS
    ${PROJECT_SOURCE_DIR}/../deps
    ${PROJECT_SOURCE_DIR}/../deps/include
  NO_DEFAULT_PATH
)
  
find_library(GLFW_LIBRARIES NAMES glfw glfw3
  PATHS
    ${PROJECT_SOURCE_DIR}/../deps
    ${PROJECT_SOURCE_DIR}/../deps/lib
  PATH_SUFFIXES
    a
    lib
    dylib
  NO_DEFAULT_PATH
)

set(GLFW_FOUND "NO")

if(GLFW_INCLUDE_DIR AND GLFW_LIBRARIES)
  set(GLFW_FOUND "YES")
endif()

if(GLFW_FOUND)
  message(STATUS "Found GLFW: ${GLFW_INCLUDE_DIR}")
else()
  if (NOT GLFW_FIND_QUIETLY)
    message(FATAL ERROR "could NOT find GLFW")
  endif()
endif()

endif()