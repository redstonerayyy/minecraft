#include "camera.hpp"

// camera object to hold information about a camera
Camera::Camera(
        glm::vec3 cameraposition,
        glm::vec3 camerafront,
        glm::vec3 cameraup,
        float yaw,
        float pitch,
        float fov
    ){
    this->camerapos = cameraposition;
    this->camerafront = camerafront;
    this->cameraup = cameraup;
    this->yaw = yaw;
    this->pitch = pitch;
    this->fov = fov;
}
