CMAKE_MINIMUM_REQUIRED(VERSION 3.22)

project(opengl)

find_package(OpenGL REQUIRED)

if (OPENGL_FOUND)
    message("opengl found")
    message("include dir: ${OPENGL_INCLUDE_DIR}")
    message("link libraries: ${OPENGL_gl_LIBRARY}")
else (OPENGL_FOUND)
    message("opengl not found")
endif()

include_directories(${OPENGL_INCLUDE_DIRS})

set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

add_subdirectory(${CMAKE_SOURCE_DIR}/glfw)

include_directories(glm)
include_directories(glfw/include)
include_directories(glfw/deps)
include_directories(src/include)
include_directories(lib/include)

FILE(GLOB SOURCE_FILES src/cpp/*.cpp)

add_executable(opengl src/main.cpp ${SOURCE_FILES} glfw/deps/glad_gl.c)

target_link_libraries(opengl ${OPENGL_LIBRARIES} glfw)