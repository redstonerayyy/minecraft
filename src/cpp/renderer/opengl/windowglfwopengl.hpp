#pragma once

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

namespace OpenGL {

// abstracted window class
class WindowGLFWOpenGL {
public:
    WindowGLFWOpenGL(int width, int height);

private:
    static void FrameBufferSizeCallback(GLFWwindow *window, int width, int height);
};

}
