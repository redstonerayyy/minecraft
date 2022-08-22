#ifndef CAMERA_H
#define CAMERA_H

#include <glm.hpp>

class Camera{
public:
    glm::vec3 camerapos;
    glm::vec3 camerafront;
    glm::vec3 cameraup;
    float yaw;
    float pitch;
    float fov;

    Camera(
        glm::vec3 cameraposition = glm::vec3(5.0f, 5.0f, 5.0f),
        glm::vec3 camerafront = glm::vec3(1.0f, 0.0f, 0.0f),
        glm::vec3 cameraup = glm::vec3(0.0f, 1.0f, 0.0f),
        float yaw = -90.0f,
        float pitch = 0.0f,
        float fov = 45.0f
    );
};

#endif