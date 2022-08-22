#ifndef WINDOWINIT_HPP
#define WINDOWINIT_HPP

#include <glad/gl.h>
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

void framebuffer_size_callback(GLFWwindow *window, int width, int height);
GLFWwindow WindowInit();

#endif