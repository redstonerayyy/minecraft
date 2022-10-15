#pragma once

#include <GLFW/glfw3.h>

//object for holding time information
// like delta time or fps
class Time {
public:
    double deltaTime = 0.0f;
    double currentTime = 0.0f;
    double lastTime = 0.0f;
    double frameTimeAddition = 0.0f;
    double fps = 0.0f;
    double fpscounter = 0.0f;

    void Update();
};
