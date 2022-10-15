#pragma once

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include "glm.hpp"

// hold mouse properties
class Input {
public:
    float mouseoutside;
    float mouselastx;
    float mouselasty;

    Input();
};
