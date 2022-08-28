#include "time.hpp"

double Time::Update(){
    this->currentTime = glfwGetTime();
    this->deltaTime = this->currentTime - this->lastTime;
    this->lastTime = this->currentTime;
    this->frameTimeAddition += this->deltaTime;
    this->fpscounter += 1;
    if(this->frameTimeAddition > 1.0f){
        this->fps = this->fpscounter;
        this->fpscounter = 0.0f;
        this->frameTimeAddition = 0.0f;
    }
}