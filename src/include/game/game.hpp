#pragma once

//GLFW
#include <GLFW/glfw3.h>

//GAME CLASSES
#include "camera.hpp"
#include "time.hpp"
#include "input.hpp"
#include "space.hpp"

//global object referenced by glfws window pointer,
//holds instances of import classes
//lock into instance headers and source files for more informatoin
class Game {
public:
    Camera maincam;
    Time time;
    Input input;
    Space space;

    Game(GLFWwindow * window);
};

//return reference to this object using the window pointer
Game * GetGame(GLFWwindow * window);
