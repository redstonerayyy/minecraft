#include "game.hpp"

// set glfw window pointer to this object
// no other functionality as this is purely a reference wrapper and
// all functionality is in the contained objects
Game::Game(GLFWwindow * window) {
    glfwSetWindowUserPointer(window, reinterpret_cast<void *>(this));
}

// retrun reference to this object
Game * GetGame(GLFWwindow * window){
    Game * gameobject = reinterpret_cast<Game *>(glfwGetWindowUserPointer(window));
    return gameobject;
};
