#include "mousecallback.hpp"

//make turning with mouse
//not really an idea what happens, just copied from learnopengl
void mouse_callback(GLFWwindow* window, double xposIn, double yposIn)
{
    // get pointer to game object
	Game * game = GetGame(window);
    // convert
	auto xpos = static_cast<float>(xposIn);
	auto ypos = static_cast<float>(yposIn);

    // if mouse enters window first, set previous position
    // to current
	if (game->input.mouseoutside)
	{
		game->input.mouselastx = xpos;
		game->input.mouselasty = ypos;
		game->input.mouseoutside = false;
	}

    // calculate offset from current and last mouse position
	float xoffset = xpos - game->input.mouselastx;
	float yoffset = game->input.mouselasty - ypos; // reversed since y-coordinates go from bottom to top
	game->input.mouselastx = xpos;
	game->input.mouselasty = ypos;

	float sensitivity = 0.1f; // change this value to your liking
	xoffset *= sensitivity;
	yoffset *= sensitivity;

    // add offset to yaw and pitch of camera
    // to make it turn
	game->maincam.yaw += xoffset;
	game->maincam.pitch += yoffset;

	// make sure that when pitch is out of bounds, screen doesn't get flipped
	if (game->maincam.pitch > 89.0f)
		game->maincam.pitch = 89.0f;
	if (game->maincam.pitch < -89.0f)
		game->maincam.pitch = -89.0f;

    // set camera front to reflect the change of yaw and pitch
	glm::vec3 front;
	front.x = cos(glm::radians(game->maincam.yaw)) * cos(glm::radians(game->maincam.pitch));
	front.y = sin(glm::radians(game->maincam.pitch));
	front.z = sin(glm::radians(game->maincam.yaw)) * cos(glm::radians(game->maincam.pitch));
	game->maincam.camerafront = glm::normalize(front);
}
