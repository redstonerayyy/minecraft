//glad loads opengl functions, glfw for creating a window and opengl context
#include <glad/gl.h>
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

//cout, calculations for opengl
#include <iostream>
#include <math.h>

//self-defined management classes for opengl
#include "shaders.h"
#include "buffers.h"
#include "textures.h"

//advanced calculation stuff
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>


// GLOBALs
//camera position
glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);
glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);

//camera rotation
float yaw = -90.0f;	// yaw is initialized to -90.0 degrees since a yaw of 0.0 results in a direction vector pointing to the right so we initially rotate a bit to the left.
float pitch = 0.0f;
//camera field of view
float fov = 45.0f;

//matrices
glm::mat4 model;
glm::mat4 view;
glm::mat4 projection;

//time, fps
float deltaTime = 0.0f;	// Time between current frame and last frame
float lastFrame = 0.0f; // Time of last frame
float fps = 0.0f;
float frameTimeAddition = 0.0f;

//input
bool firstMouse = true; //set to false if mouse enters the window
float lastX = 800.0f / 2.0f;
float lastY = 600.0f / 2.0f;

//callbacks
//change viewport when window is changed, only works on release of window
void framebuffer_size_callback(GLFWwindow *window, int width, int height)
{
	glViewport(0, 0, width, height);
};

//make turning with mouse
//not really an idea what happens, just copied from learnopengl
void mouse_callback(GLFWwindow* window, double xposIn, double yposIn)
{
	float xpos = static_cast<float>(xposIn);
	float ypos = static_cast<float>(yposIn);

	if (firstMouse)
	{
		lastX = xpos;
		lastY = ypos;
		firstMouse = false;
	}

	float xoffset = xpos - lastX;
	float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top
	lastX = xpos;
	lastY = ypos;

	float sensitivity = 0.1f; // change this value to your liking
	xoffset *= sensitivity;
	yoffset *= sensitivity;

	yaw += xoffset;
	pitch += yoffset;

	// make sure that when pitch is out of bounds, screen doesn't get flipped
	if (pitch > 89.0f)
		pitch = 89.0f;
	if (pitch < -89.0f)
		pitch = -89.0f;

	glm::vec3 front;
	front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
	front.y = sin(glm::radians(pitch));
	front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
	cameraFront = glm::normalize(front);
}

//zoom by changing fov
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	fov -= (float)yoffset;
	if (fov < 1.0f)
		fov = 1.0f;
	if (fov > 45.0f)
		fov = 45.0f;
	projection = glm::perspective(glm::radians(fov), 800.0f / 600.0f, 0.1f, 100.0f);
}

//react to input
void processInput(GLFWwindow* window)
{
	//close
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);

	//log fps
	float currentFrame = glfwGetTime();
	deltaTime = currentFrame - lastFrame;
	lastFrame = currentFrame;
	frameTimeAddition += deltaTime;
	fps += 1.0f;
	if (frameTimeAddition > 1.0f) {
		std::cout << fps << std::endl;
		fps = 0.0f;
		frameTimeAddition = 0.0f;
	}

	//move camera
	const float cameraSpeed = 2.5f * deltaTime; // adjust accordingly
	//forward, backward, left, right
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		cameraPos += cameraSpeed * cameraFront;
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		cameraPos -= cameraSpeed * cameraFront;
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
	//up, down
	if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
		cameraPos += cameraUp * cameraSpeed;
	if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
		cameraPos -= cameraUp * cameraSpeed;
}


int main()
{
	// GLWF
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	//MSAA 4x
	glfwWindowHint(GLFW_SAMPLES, 4);

	GLFWwindow *window = glfwCreateWindow(800, 600, "LearnOpenGL", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create window!" << std::endl;
		glfwTerminate();
		return -1;
	};

	glfwMakeContextCurrent(window);

	if (!gladLoadGL((GLADloadfunc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize glad!" << std::endl;
		return -1;
	};

	//set callbacks
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	glfwSetCursorPosCallback(window, mouse_callback);
	glfwSetScrollCallback(window, scroll_callback);

	// OPENGL
	//set opengl viewport
	glViewport(0, 0, 800, 600);
	
	// SHADERS
	//TODO implement relative resource searching
	Shader defaultShader("C:\\Users\\paul\\source\\repos\\minecraft\\src\\shaders\\vertex.glsl", "C:\\Users\\paul\\source\\repos\\minecraft\\src\\shaders\\fragment.glsl");
	
	Shader lightshader("C:\\Users\\paul\\source\\repos\\minecraft\\src\\shaders\\lightvertex.glsl", "C:\\Users\\paul\\source\\repos\\minecraft\\src\\shaders\\light.glsl");
	// VERTEX DATA
	// vertices, indices, cube position -> moved to other file
	
	#include "vertexdata.h"

	VAO* cube = new VAO();
	cube->fillVBO(cube_vertices, sizeof(cube_vertices));
	//vertex cordinate
	cube->setAttrib(0, 3, GL_FLOAT, false, 5, 0);
	//texture cordinte
	cube->setAttrib(1, 2, GL_FLOAT, false, 5, 3);
	cube->fillEBO(indices, sizeof(indices));


	VAO* light = new VAO();
	light->fillVBO(light_vertices, sizeof(light_vertices));
	light->setAttrib(0, 3, GL_FLOAT, false, 3, 0);
	light->fillEBO(indices, sizeof(indices));

	// TEXTURES
	unsigned int texture = makeTexture("C:\\Users\\paul\\source\\repos\\minecraft\\src\\textures\\diamond_ore.png");

	// RENDER OPTIONS
	// Wireframes
	// glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	//avoid random drawing, not continous geometry
	glEnable(GL_DEPTH_TEST);

	//MSAA
	glEnable(GL_MULTISAMPLE);

	// RENDER LOOP
	while (!glfwWindowShouldClose(window))
	{
		// INPUT
		//keysboard input, mouse input
		processInput(window);

		defaultShader.use();
		// CAMERA
		// model matrix set further down, dynamically for each object
		//view matrix, transform world space to camera space
		glm::mat4 view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
		defaultShader.setMatrix4fv("view", view);

		//projection matrix, view space to device cordinates
		glm::mat4 projection = glm::perspective(glm::radians(fov), 800.0f / 600.0f, 0.1f, 100.0f);
		defaultShader.setMatrix4fv("projection", projection);

		// DRAWING
		//clear color and depth buffer
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		//vertex data, shaders
		cube->use();
		defaultShader.setVec3("lightColor", 1.0f, 1.0f, 1.0f);
		
		int cubesize = 30;
		//draw cubes
		for (float i = 0.0f; i < cubesize; i++) {
			for (float j = 0.0f; j < cubesize; j++) {
				for (float k = 0.0f; k < cubesize; k++) {
					glm::mat4 model = glm::mat4(1.0f);
					model = glm::translate(model, glm::vec3(i, j, k));
					defaultShader.setMatrix4fv("model", model);
					glDrawArrays(GL_TRIANGLES, 0, 36);
				}
			}
		}


		//DRAW LIGHT

		light->use();
		lightshader.use();
		lightshader.setMatrix4fv("view", view);
		lightshader.setMatrix4fv("projection", projection);
		glm::mat4 model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(-1.0f, -1.0f, -1.0f));
		lightshader.setMatrix4fv("model", model);
		glDrawArrays(GL_TRIANGLES, 0, 36);

		//GLFW updating the window
		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	glfwTerminate();
	return 0;
}
