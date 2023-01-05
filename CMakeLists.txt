#project and settings
CMAKE_MINIMUM_REQUIRED(VERSION 3.22)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS "-Wall")

project(minecraft)

#build glfw
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

add_subdirectory(${CMAKE_SOURCE_DIR}/glfw)

#build minecraft
#source files
FILE(GLOB SF_APPLICATION src/cpp/application/*.cpp)
FILE(GLOB SF_SHADER src/cpp/shader/*.cpp)
FILE(GLOB SF_TEXTURE src/cpp/texture/*.cpp)
FILE(GLOB SF_UTILS src/cpp/utils/*.cpp)
FILE(GLOB SF_RENDERER src/cpp/renderer/opengl/*.cpp)

#add target
add_executable(minecraft src/main.cpp glad/src/glad.c ${SF_APPLICATION} ${SF_SHADER} ${SF_TEXTURE} ${SF_UTILS} ${SF_RENDERER})

#library headers
target_include_directories(minecraft PRIVATE glm/glm)
target_include_directories(minecraft PRIVATE glfw/include)
target_include_directories(minecraft PRIVATE lib/include)
target_include_directories(minecraft PRIVATE glad/include)

#source headers
target_include_directories(minecraft PRIVATE src/cpp/application)
target_include_directories(minecraft PRIVATE src/cpp/texture)
target_include_directories(minecraft PRIVATE src/cpp/shader)
target_include_directories(minecraft PRIVATE src/cpp/utils)
target_include_directories(minecraft PRIVATE src/cpp/renderer/opengl)

#link libraries
target_link_libraries(minecraft OpenGL glfw)