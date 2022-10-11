#include "windowinit.hpp"

//callbacks
//change viewport when window is changed, only works on release of window
void framebuffer_size_callback(GLFWwindow *window, int width, int height)
{
	glViewport(0, 0, width, height);
}

GLFWwindow& WindowInit(){
    // GLWF
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	//MSAA 4x
	glfwWindowHint(GLFW_SAMPLES, 4);

	//create GLFW window
    // Hence we are working with pointers, we should use nullptr instead of NULL to clarify our intent.
	GLFWwindow *window = glfwCreateWindow(800, 600, "LearnOpenGL", nullptr, nullptr);
	if (window == nullptr)
	{
		std::cout << "Failed to create window!" << std::endl;
		glfwTerminate();
		return *window;
	}

	//initialize opengl
	glfwMakeContextCurrent(window);

	if (!gladLoadGL((GLADloadfunc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize glad!" << std::endl;
		return *window;
	}

	//set callbacks
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	// OPENGL
	//set opengl viewport
	glViewport(0, 0, 800, 600);

    return *window;
}