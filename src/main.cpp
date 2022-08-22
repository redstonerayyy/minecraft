//glad loads opengl functions, glfw for creating a window and opengl context
#include <glad/gl.h>
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

//STL
#include <iostream>
#include <math.h>
#include <array>

//self-defined management classes for opengl, game classes
#include "shaders.h"
#include "buffers.h"
#include "textures.h"
#include "camera.hpp"
#include "windowinit.hpp"


#include "structs.h"
#include "fileslist.h"

#include "mesh.h"
#include "primitives.h"

#include "worldgen.h"

#include "utils.h"

//advanced calculation stuff
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>

Camera maincam = Camera();


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

	maincam.yaw += xoffset;
	maincam.pitch += yoffset;

	// make sure that when pitch is out of bounds, screen doesn't get flipped
	if (maincam.pitch > 89.0f)
		maincam.pitch = 89.0f;
	if (maincam.pitch < -89.0f)
		maincam.pitch = -89.0f;

	glm::vec3 front;
	front.x = cos(glm::radians(maincam.yaw)) * cos(glm::radians(maincam.pitch));
	front.y = sin(glm::radians(maincam.pitch));
	front.z = sin(glm::radians(maincam.yaw)) * cos(glm::radians(maincam.pitch));
	maincam.camerafront = glm::normalize(front);
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
		maincam.camerapos += cameraSpeed * maincam.camerafront;
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		maincam.camerapos -= cameraSpeed * maincam.camerafront;
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		maincam.camerapos -= glm::normalize(glm::cross(maincam.camerafront, maincam.cameraup)) * cameraSpeed;
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		maincam.camerapos += glm::normalize(glm::cross(maincam.camerafront, maincam.cameraup)) * cameraSpeed;
	//up, down
	if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
		maincam.camerapos += maincam.cameraup * cameraSpeed;
	if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
		maincam.camerapos -= maincam.cameraup * cameraSpeed;
}


int main()
{
	GLFWwindow *window = WindowInit();
	
	// SHADERS
	//TODO implement relative resource searching
	//std::string shaderDir = "C:\\Users\\paul\\source\\repos\\minecraft\\src\\shaders\\";
	std::string shaderDir = "/home/anton/Github/minecraft/src/shaders/";
	std::string vertexpath = shaderDir + "vertex.glsl";
	std::string fragmentpath = shaderDir + "light_new.glsl";
	std::vector<Shader> shaders;
	shaders.push_back(Shader(GL_VERTEX_SHADER, vertexpath.c_str()));
	shaders.push_back(Shader(GL_FRAGMENT_SHADER, fragmentpath.c_str()));
	ShaderProgram defaultShader(shaders);
	
	std::string lightvertexpath = shaderDir + "light_vertex.glsl";
	std::string lightfragmentpath = shaderDir + "light.glsl";
	std::vector<Shader> lightshaders;
	lightshaders.push_back(Shader(GL_VERTEX_SHADER, lightvertexpath.c_str()));
	lightshaders.push_back(Shader(GL_FRAGMENT_SHADER, lightfragmentpath.c_str()));
	ShaderProgram lightShader(lightshaders);
	// TEXTURES

	//std::string textureDir = "C:\\Users\\paul\\source\\repos\\minecraft\\src\\textures\\";
	glEnable(GL_TEXTURE_2D);
	glActiveTexture(GL_TEXTURE0);
	Texture texture1 = Texture(texturedir + "diamond_ore.png");
	glActiveTexture(GL_TEXTURE0 + 1);
	Texture texture2 = Texture(texturedir + "white.png");

	// VERTEX DATA

	std::vector<Vertex> vertices;
	std::vector<unsigned int> indices;

	//smoothWorld(vertices, mesh_indices);
	float size = 200.0f;
	std::vector<float> noisemap = generateNoiseMap(size, size, 111);
	for(float i = 0; i < size; i++){
		for(float j = 0; j < size; j++){
			float transvec[3] = {i, froundf(0.0f * noisemap[i * size + j]), j};
			int cubesides[6] = { 1, 1, 1, 1, 1, 1};
			generateCube(vertices, indices, transvec, cubesides);
		}
	}

	Mesh world;
	world.addVBO(vertices);
	world.addEBO(indices);
	world.generateBuffers(true, true, true);

	std::vector<Vertex> lightvertices;
	std::vector<unsigned int> lightindices;
	float lightpos[3] = {5.0f, 5.0f, 5.0f};
	int cubesides[6] = { 1, 1, 1, 1, 1, 1};
	generateCube(lightvertices, lightindices, lightpos, cubesides);
	Mesh light;
	light.addVBO(lightvertices);
	light.addEBO(lightindices);
	light.generateBuffers(true, true, true);


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
		glm::mat4 view = glm::lookAt(maincam.camerapos, maincam.camerapos + maincam.camerafront, maincam.cameraup);
		defaultShader.setMatrix4fv("view", view);

		//projection matrix, view space to device cordinates
		glm::mat4 projection = glm::perspective(glm::radians(maincam.fov), 800.0f / 600.0f, 0.1f, 400.0f);
		defaultShader.setMatrix4fv("projection", projection);

		// DRAWING
		//clear color and depth buffer
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		////vertex data, shaders
		
		defaultShader.setInt("tex_sampler1", 0);
		defaultShader.setVec3("lightPos", -5.0f, -5.0f, -5.0f);
		defaultShader.setVec3("viewPos", maincam.camerapos.x, maincam.camerapos.y, maincam.camerapos.z);

		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(-1.0, -1.0, -1.0));
		defaultShader.setMatrix4fv("model", model);
		// glEnable(GL_TEXTURE_2D);
		// glActiveTexture(GL_TEXTURE0);
		//glDrawArrays(GL_TRIANGLES, 0, 36);
		world.drawMesh(defaultShader);

		lightShader.use();
		lightShader.setMatrix4fv("view", view);
		lightShader.setMatrix4fv("projection", projection);
		lightShader.setMatrix4fv("model", model);
		light.drawMesh(lightShader);
		//GLFW updating the window
		//std::cout << glGetError() << std::endl;
		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	glfwTerminate();
	return 0;
}
