#include "windowglfwopengl.hpp"

#include <iostream>
#include <glad/glad.h>
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

namespace OpenGL {

WindowGLFWOpenGL::WindowGLFWOpenGL(int width, int height){
    // GLWF
	if(glfwInit() != GLFW_TRUE){
        std::cout << "ERROR initializing glfw\n";
        exit(EXIT_FAILURE);
    }
    // set opengl version and profile
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	//MSAA 4x
	glfwWindowHint(GLFW_SAMPLES, 4);

	//create GLFW window
    // Hence we are working with pointers, we should use nullptr instead of NULL to clarify our intent.
	GLFWwindow *window = glfwCreateWindow(width, height, "Minecraft", nullptr, nullptr);
	if (window == nullptr){
		std::cout << "ERROR Failed to create window!" << std::endl;
		glfwTerminate();
		exit(EXIT_FAILURE);
	}

	//initialize opengl
	glfwMakeContextCurrent(window);

	if (!gladLoadGL()){
		std::cout << "Failed to initialize glad!" << std::endl;
	}

	//set callbacks
	glfwSetFramebufferSizeCallback(window, WindowGLFWOpenGL::FrameBufferSizeCallback);

	// OPENGL
	//set opengl viewport
	glViewport(0, 0, width, height);
}

//callbacks
//change viewport when window is changed, only works on release of window
void WindowGLFWOpenGL::FrameBufferSizeCallback(GLFWwindow *window, int width, int height){
	glViewport(0, 0, width, height);
}

}
