//glad loads opengl functions, glfw for creating a window and opengl context
#include <glad/gl.h>
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

//STL
#include <iostream>
#include <cmath>
#include <array>

//self-defined management classes for opengl, game classes
#include "shaders.h"
#include "buffers.h"
#include "textures.h"
#include "camera.hpp"
#include "windowinit.hpp"
#include "processinput.hpp"
#include "mousecallback.hpp"

#include "shaderloader.hpp"

#include "structs.h"
#include "fileslist.h"

#include "mesh.h"
#include "primitives.h"

#include "worldgen.h"
#include "game.hpp"

#include "utils.h"

//advanced calculation stuff
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>

//matrices
glm::mat4 model;

int main()
{
	GLFWwindow& window = WindowInit();
	Game gameinfo = Game(&window);
	Game * game = GetGame(&window);
	game->time = Time();
	game->maincam = Camera();
	game->input = Input();

	glfwSetInputMode(&window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	glfwSetCursorPosCallback(&window, mouse_callback);

	// SHADERS
    ShaderLoader shaderloader({"run/shaders"});

    ShaderProgram defaultShader = shaderloader.MakeProgram({"vertex.glsl", "light_new.glsl"});
    ShaderProgram lightShader = shaderloader.MakeProgram({"vertex_light.glsl", "light.glsl"});
	
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

	int size = 200.0f;
	std::vector<float> noisemap = generateNoiseMap(size, size, 111);
	for(int i = 0; i < size; i++){
		for(int j = 0; j < size; j++){
			float transvec[3] = {i*1.0f, Utils::froundf(0.0f * noisemap[i * size + j]), j*1.0f};
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
	while (!glfwWindowShouldClose(&window))
	{
		game->time.Update();

		// INPUT
		//keysboard input, mouse input
		processInput(&window);

		defaultShader.use();
		// CAMERA
		// model matrix set further down, dynamically for each object
		//view matrix, transform world space to camera space
		glm::mat4 view = glm::lookAt(game->maincam.camerapos, game->maincam.camerapos + game->maincam.camerafront, game->maincam.cameraup);
		defaultShader.setMatrix4fv("view", view);

		//projection matrix, view space to device cordinates
		glm::mat4 projection = glm::perspective(glm::radians(game->maincam.fov), 800.0f / 600.0f, 0.1f, 400.0f);
		defaultShader.setMatrix4fv("projection", projection);

		// DRAWING
		//clear color and depth buffer
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		////vertex data, shaders
		
		defaultShader.setInt("tex_sampler1", 0);
		defaultShader.setVec3("lightPos", -5.0f, -5.0f, -5.0f);
		defaultShader.setVec3("viewPos", game->maincam.camerapos.x, game->maincam.camerapos.y, game->maincam.camerapos.z);

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
		glfwSwapBuffers(&window);
		glfwPollEvents();
	}
	glfwTerminate();
	return 0;
}
