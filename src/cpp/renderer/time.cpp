#include "time.hpp"

void Time::Update(){
    this->currentTime = glfwGetTime(); // get time
    this->deltaTime = this->currentTime - this->lastTime; // calculate delta time
    this->lastTime = this->currentTime; // update last time for next delta time
    this->frameTimeAddition += this->deltaTime; // add to total time since last second
    this->fpscounter += 1;
    // if 1 second has passed, reset and set fps of last second to counter
    if(this->frameTimeAddition > 1.0f){
        this->fps = this->fpscounter;
        this->fpscounter = 0.0f;
        this->frameTimeAddition = 0.0f;
    }
}