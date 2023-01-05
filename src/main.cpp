#include "application.hpp"
#include "openglshaderloader.hpp"
#include "opengltextureloader.hpp"

//glad loads opengl functions, glfw for creating a window and opengl context
#include <glad/glad.h>
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

int main(){
    // create on heap
    Application* game = new Application(200, 200, 0);
	return 0;
}
