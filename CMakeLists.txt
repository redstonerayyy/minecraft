#project and settings
CMAKE_MINIMUM_REQUIRED(VERSION 3.22)
set (CMAKE_CXX_STANDARD 17)

project(opengl)

#find opengl
find_package(OpenGL REQUIRED)

if (OPENGL_FOUND)
    message("opengl found")
    message("include dir: ${OPENGL_INCLUDE_DIR}")
else (OPENGL_FOUND)
    message("opengl not found")
endif()


#build glfw
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

add_subdirectory(${CMAKE_SOURCE_DIR}/glfw)

#build minecraft
#source files
FILE(GLOB SOURCE_FILES_SUB0 src/cpp/*.cpp)
FILE(GLOB SOURCE_FILES_SUB1 src/cpp/**/*.cpp)
FILE(GLOB SOURCE_FILES_SUB2 src/cpp/**/**/*.cpp)

#add target
add_executable(opengl src/main.cpp ${SOURCE_FILES_SUB0} ${SOURCE_FILES_SUB1} ${SOURCE_FILES_SUB2} glfw/deps/glad_gl.c)

#include dirs

#libraries
target_include_directories(opengl PRIVATE ${OPENGL_INCLUDE_DIRS})
target_include_directories(opengl PRIVATE glm/glm)
target_include_directories(opengl PRIVATE glfw/include)
target_include_directories(opengl PRIVATE glfw/deps)
target_include_directories(opengl PRIVATE lib/include)

#source headers
target_include_directories(opengl PRIVATE src/include/game)
target_include_directories(opengl PRIVATE src/include/game/world)
target_include_directories(opengl PRIVATE src/include/general)
target_include_directories(opengl PRIVATE src/include/meshes)
target_include_directories(opengl PRIVATE src/include/renderer)
target_include_directories(opengl PRIVATE src/include/resources)
target_include_directories(opengl PRIVATE src/include/util)
target_include_directories(opengl PRIVATE src/include/window)

#link libraries
target_link_libraries(opengl ${OPENGL_LIBRARIES} glfw)