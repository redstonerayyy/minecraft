#include "processinput.hpp"

//react to input
void processInput(GLFWwindow* window, std::vector<Vertex> &verts, std::vector<unsigned int> &inds)
{
    // get game
	Game * game = GetGame(window);
    std::cout << game->time.fps << "\n";

	//close
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);

	//move camera
	const float cameraSpeed = 10.0f * game->time.deltaTime; // adjust accordingly
	//forward, backward, left, right
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		game->maincam.camerapos += cameraSpeed * game->maincam.camerafront;
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		game->maincam.camerapos -= cameraSpeed * game->maincam.camerafront;
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		game->maincam.camerapos -= glm::normalize(glm::cross(game->maincam.camerafront, game->maincam.cameraup)) * cameraSpeed;
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		game->maincam.camerapos += glm::normalize(glm::cross(game->maincam.camerafront, game->maincam.cameraup)) * cameraSpeed;
	//up, down
	if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
		game->maincam.camerapos += game->maincam.cameraup * cameraSpeed;
	if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
		game->maincam.camerapos -= game->maincam.cameraup * cameraSpeed;
    
    //update world
    if (glfwGetKey(window, GLFW_KEY_U) == GLFW_PRESS){
        std::vector<Vertex> vtemp;
        std::vector<unsigned int> itemp;
        std::srand(time(NULL));
	    int seed = std::rand();
        int size = 200.0f;
        std::vector<std::vector<float>> noisemap = generateNoiseMap(size, size, 4, seed);
        for(int i = 0; i < size; i++){
            for(int j = 0; j < size; j++){
                float transvec[3] = {i*1.0f, Utils::froundf(100.0f * noisemap[i][j]), j*1.0f};
                std::array<int, 6> cubesides = { 1, 1, 1, 1, 1, 1};
                generateCube(vtemp, itemp, transvec, cubesides);
            }
        }
        verts = vtemp;
        inds = itemp;
    }
}
