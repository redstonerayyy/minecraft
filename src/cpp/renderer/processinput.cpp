#include "processinput.hpp"

//react to input
void processInput(GLFWwindow* window, std::vector<Vertex> &verts, std::vector<unsigned int> &inds)
{
    // get game
	Game * game = GetGame(window);
    // std::cout << game->time.fps << "\n";

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
}
