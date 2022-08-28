#ifndef GAME_HPP
#define GAME_HPP

//GLFW
#include <GLFW/glfw3.h>

class Game {
public:
    int test;
    

    Game(GLFWwindow * window);
};

Game * GetGame(GLFWwindow * window);

#endif