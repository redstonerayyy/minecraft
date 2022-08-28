#include "game.hpp"

Game::Game(GLFWwindow * window) {
    this->test = 1;
    glfwSetWindowUserPointer(window, reinterpret_cast<void *>(this));
}