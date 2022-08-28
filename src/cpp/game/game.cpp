#include "game.hpp"

Game::Game(GLFWwindow * window) {
    this->test = 1;
    glfwSetWindowUserPointer(window, reinterpret_cast<void *>(this));
}

Game * GetGame(GLFWwindow * window){
    Game * gameobject = reinterpret_cast<Game *>(glfwGetWindowUserPointer(window));
    return gameobject;
};