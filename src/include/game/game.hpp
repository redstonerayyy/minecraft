#ifndef GAME_HPP
#define GAME_HPP

//GLFW
#include <GLFW/glfw3.h>

//GAME CLASSES
#include "camera.hpp"
#include "time.hpp"
#include "input.hpp"

class Game {
public:
    int test;
    Camera maincam;
    Time time;
    Input input;

    Game(GLFWwindow * window);
};

Game * GetGame(GLFWwindow * window);

#endif