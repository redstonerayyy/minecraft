//glad loads opengl functions, glfw for creating a window and opengl context
#include <glad/gl.h>
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

//cout, calculations for opengl
#include <iostream>
#include <math.h>

//self-defined management classes for opengl
#include "shaders.h"
#include "textures.h"
#include "buffers.h"
#include "structs.h"
#include "mesh.h"
#include "primitives.h"
// #include "PerlinNoise.hpp"
#include "worldgen.h"
#include "chunk.h"
#include "utils.h"

//advanced calculation stuff
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>


// GLOBALs
//camera position
glm::vec3 cameraPos = glm::vec3(5.0f, 5.0f, 5.0f);
glm::vec3 cameraFront = glm::vec3(1.0f, 0.0f, 0.0f);
glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);

//camera rotation
float yaw = -90.0f;	// yaw is initialized to -90.0 degrees since a yaw of 0.0 results in a direction vector pointing to the right so we initially rotate a bit to the left.
float pitch = 0.0f;
//camera field of view
float fov = 45.0f;


//light
float lighty = 1.0f;
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
		//std::cout << fps << std::endl;
		fps = 0.0f;
		frameTimeAddition = 0.0f;
	}

	//move camera
	const float cameraSpeed = 10.0f * deltaTime; // adjust accordingly
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
	glfwWindowHint(GLFW_SAMPLES, 8);

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
	//std::string shaderDir = "C:\\Users\\paul\\source\\repos\\minecraft\\src\\shaders\\";
	std::string shaderDir = "/home/anton/Github/minecraft/src/shaders/";
	std::string vertexpath = shaderDir + "vertex.glsl";
	std::string fragmentpath = shaderDir + "light_proto.glsl";
	Shader defaultShader(vertexpath.c_str(), fragmentpath.c_str());
	
	std::string lightvertexpath = shaderDir + "lightvertex.glsl";
	std::string lightfragmentpath = shaderDir + "light.glsl";
	Shader lightshader(lightvertexpath.c_str(), lightfragmentpath.c_str());
	
	// TEXTURES
	//std::string textureDir = "C:\\Users\\paul\\source\\repos\\minecraft\\src\\textures\\";
	std::string textureDir = "/home/anton/Github/minecraft/src/textures/";
	glEnable(GL_TEXTURE_2D);
	glActiveTexture(GL_TEXTURE0);
	unsigned int texture = makeTexture(textureDir + "diamond_ore.png");

	// VERTEX DATA
	// vertices, indices, cube position -> moved to other file
	
	#include "vertexdata.h"

	std::vector<Vertex> vertices;
	std::vector<unsigned int> mesh_indices;

	//smoothWorld(vertices, mesh_indices);
	float size = 200.0f;
	std::vector<float> noisemap = generateNoiseMap(size, size, 111);
	for(float i = 0; i < size; i++){
		for(float j = 0; j < size; j++){
			float transvec[3] = {i, froundf(100 * noisemap[i * size + j]), j};
			int cubesides[6] = { 0, 0, 0, 0, 1, 0};
			generateCube(vertices, mesh_indices, transvec, cubesides);
		}
	}


	//Chunk* world = new Chunk(16, 100, vertices, mesh_indices);
	

	Mesh wall(vertices);

	//std::vector<unsigned int> inds;
	// for (int i = 0; i < sizeof(indices)/sizeof(unsigned int); i++) {
	// 	inds.push_back(indices[i]);
	// }
	wall.setIndices(mesh_indices);

	//VAO* test = new VAO();
	//VBO verts(cubevert);
	//test->vbos.push_back(verts);
	//test->fillFirst();
	

	// RENDER OPTIONS
	// Wireframes
	// glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	//avoid random drawing and not continous geometry
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
		glm::mat4 projection = glm::perspective(glm::radians(fov), 800.0f / 600.0f, 0.1f, 200.0f);
		defaultShader.setMatrix4fv("projection", projection);

		// DRAWING
		//clear color and depth buffer
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		////vertex data, shaders
		
		defaultShader.setVec3("viewPos", cameraPos.x, cameraPos.y, cameraPos.z);
		
		defaultShader.setInt("tex_sampler", 0);
		defaultShader.setVec3("material.specular", 1.0f, 0.0f, 0.0f);
		defaultShader.setFloat("material.shininess", 32.0f);
		
		defaultShader.setVec3("dirLight.direction", 0.0f, -1.0f, 0.0f);
		defaultShader.setVec3("dirLight.ambient",  0.4f, 0.4f, 0.4f);
		defaultShader.setVec3("dirLight.diffuse",  0.6f, 0.6f, 0.6f); // darken diffuse light a bit
		defaultShader.setVec3("dirLight.specular", 1.0f, 1.0f, 1.0f);

		defaultShader.setVec3("pointLights[0].position", -1.0f, -1.0f, -1.0f);
		defaultShader.setVec3("pointLights[0].ambient", 0.2f, 0.2f, 0.2f);
		defaultShader.setVec3("pointLights[0].diffuse", 0.4f, 0.4f, 0.4f); // darken diffuse light a bit
		defaultShader.setVec3("pointLights[0].specular", 1.0f, 0.0f, 0.0f);
		defaultShader.setFloat("pointLights[0].constant", 1.0f);
		defaultShader.setFloat("pointLights[0].linear", 0.045f);
		defaultShader.setFloat("pointLights[0].quadratic", 0.0075f);

		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(-1.0, -1.0, -1.0));
		defaultShader.setMatrix4fv("model", model);
		glEnable(GL_TEXTURE_2D);
		glActiveTexture(GL_TEXTURE0);
		//glDrawArrays(GL_TRIANGLES, 0, 36);
		wall.drawMesh(defaultShader);
		
		//GLFW updating the window
		//std::cout << glGetError() << std::endl;
		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	glfwTerminate();
	return 0;
}
