#pragma once

#include <string>
#include <glad/glad.h>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include <glm/mat4x4.hpp>

namespace OpenGL {

void SetBoolUniform(GLuint programid, std::string name, bool value);
void SetIntegerUniform(GLuint programid, std::string name, int value);
void SetFloatUniform(GLuint programid, std::string name, float value);
void SetVec3Uniform(GLuint programid, std::string name, glm::vec3 value);
void SetVec4Uniform(GLuint programid, std::string name, glm::vec4 value);
void SetMat4x4Uniform(GLuint programid, std::string name, glm::mat4 value);

}
