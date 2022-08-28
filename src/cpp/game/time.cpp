#include "time.hpp"

double Time::Update(){
    this->currentTime = glfwGetTime();
    this->deltaTime = this->currentTime - this->lastTime;
    this->frameTimeAddition += this->deltaTime;
    this->lastfps = 0;
    this->fps += 1;
    if(this->frameTimeAddition > 1.0f){
        this->lastfps = this->fps;
        this->fps = 0.0f;
        this->frameTimeAddition = 0.0f
    }
}