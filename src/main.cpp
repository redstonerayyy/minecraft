//glad loads opengl functions, glfw for creating a window and opengl context
#include <glad/gl.h>
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

//STL
#include <iostream>
#include <cmath>
#include <array>
#include <time.h>

//advanced calculation stuff
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>

//self-defined management classes for opengl, game classes
#include "shaders.hpp"
#include "buffers.hpp"
#include "textures.hpp"
#include "camera.hpp"
#include "windowinit.hpp"
#include "processinput.hpp"
#include "mousecallback.hpp"

#include "shaderloader.hpp"

#include "structs.hpp"
#include "fileslist.hpp"

#include "mesh.hpp"
#include "primitives.hpp"

#include "worldgen.hpp"
#include "game.hpp"
#include "space.hpp"

#include "utils.hpp"
#include "world.hpp"


//matrices
glm::mat4 model;

int main()
{
    //INITIALIZE WINDOW AND GLOBALS
	//WINDOW
    GLFWwindow& window = WindowInit();
	glfwSetInputMode(&window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	glfwSetCursorPosCallback(&window, mouse_callback);

    //GLOBALS
	Game gameinfo = Game(&window);
	Game * game = GetGame(&window);
	game->time = Time();
	game->maincam = Camera();
	game->input = Input();
    game->space = Space();

	// SHADERS
    ShaderLoader shaderloader({"run/shaders"});

    ShaderProgram defaultShader = shaderloader.MakeProgram({"vertex.glsl", "light_new.glsl"});
    ShaderProgram lightShader = shaderloader.MakeProgram({"vertex_light.glsl", "light.glsl"});
	
	// TEXTURES
	glEnable(GL_TEXTURE_2D);
	glActiveTexture(GL_TEXTURE0);
	Texture texture1 = Texture(texturedir + "diamond_ore.png");
	glActiveTexture(GL_TEXTURE0 + 1);
	Texture texture2 = Texture(texturedir + "white.png");

	//SEED
	std::srand(time(NULL));
	int seed = std::rand();

	std::cout << seed << "\n";

	// VERTEX DATA
	std::vector<Vertex> vertices;
	std::vector<unsigned int> indices;

	World worldgen = World( seed );
	Chunk chunkone = worldgen.GetChunk(0, 0);

	int size = 200.0f;
	std::vector<std::vector<float>> noisemap = generateNoiseMap(size, size, 4, seed);
	for(int i = 0; i < size; i++){
		for(int j = 0; j < size; j++){
			float transvec[3] = {i*1.0f, Utils::froundf(100.0f * noisemap[i][j]), j*1.0f};
			std::array<int, 6> cubesides = { 1, 1, 1, 1, 1, 1};
			generateCube(vertices, indices, transvec, cubesides);
		}
	}

    //MESH
	Mesh world = Mesh(chunkone.vertices, chunkone.indices);
	world.generateBuffers(true, true, true);

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
        //TIME, MATRIZES
		game->time.Update();
        game->space.Update(game->maincam, defaultShader);
		

        //UPDATES VERTS
        //move world
        // for(int i = 0; i < world.vertices.size(); ++i){
        //     world.vertices[i].Position.x += -1;
        // }

        // world.updateBuffers();

        // INPUT
		//keysboard input, mouse input
		processInput(&window, vertices, indices);
        world.vertices = vertices;
        world.indices = indices;
        world.updateBuffers();
		defaultShader.use();

		// DRAWING
		//clear color and depth buffer
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		
        //SHADER
		defaultShader.setInt("tex_sampler1", 0);
		defaultShader.setVec3("lightPos", -5.0f, -5.0f, -5.0f);
		defaultShader.setVec3("viewPos", game->maincam.camerapos.x, game->maincam.camerapos.y, game->maincam.camerapos.z);

        //MESHES
        world.draw(defaultShader);

		//GLFW updating the window
		//std::cout << glGetError() << std::endl;
		glfwSwapBuffers(&window);
		glfwPollEvents();
	}
	glfwTerminate();
	return 0;
}
