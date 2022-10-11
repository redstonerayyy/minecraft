#pragma once

#include "GLFW/glfw3.h"
#include "game.hpp"
#include "structs.hpp"
#include "worldgen.hpp"
#include "utils.hpp"
#include "primitives.hpp"
#include <time.h>
#include <iostream>

void processInput(GLFWwindow* window, std::vector<Vertex> &verts, std::vector<unsigned int> &inds);
