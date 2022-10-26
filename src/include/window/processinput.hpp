#pragma once

#include "GLFW/glfw3.h"
#include "game.hpp"
#include "structs.hpp"
#include "worldgen.hpp"
#include "utils.hpp"
#include "primitives.hpp"
#include <time.h>
#include <iostream>

// handle key presses, verts and inds to change world on u press
void processInput(GLFWwindow* window, std::vector<Vertex> &verts, std::vector<unsigned int> &inds);
