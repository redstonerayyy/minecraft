#include "space.hpp"

void Space::Update(Camera &camera, ShaderProgram &shaderprogram){
    shaderprogram.use();
    //view matrix, transform world space to camera space
    glm::mat4 view = glm::lookAt(camera.camerapos, camera.camerapos + camera.camerafront, camera.cameraup);
    shaderprogram.setMatrix4fv("view", view);

    //projection matrix, view space to device cordinates
    glm::mat4 projection = glm::perspective(glm::radians(camera.fov), 800.0f / 600.0f, 0.1f, 400.0f);
    shaderprogram.setMatrix4fv("projection", projection);

    //make model matrix
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(-1.0, -1.0, -1.0));
    shaderprogram.setMatrix4fv("model", model);
}