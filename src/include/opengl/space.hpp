#pragma once

#include "camera.hpp"
#include "shaders.hpp"

//advanced calculation stuff
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>

class Space {
public:
    glm::mat4 view;
    glm::mat4 projection;
    glm::mat4 model;

    void Update(Camera &camera, ShaderProgram &shaderprogram);
};
