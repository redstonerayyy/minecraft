#include "openglshaderprogramuniforms.hpp"

#include <string>
#include <glad/glad.h>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include <glm/mat4x4.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace OpenGL {

void SetBoolUniform(GLuint programid, std::string name, bool value){
    GLint location = glGetUniformLocation(programid, name.c_str());
    glUniform1i(location, value);
}

void SetIntegerUniform(GLuint programid, std::string name, int value){
    GLint location = glGetUniformLocation(programid, name.c_str());
    glUniform1i(location, value);
}

void SetFloatUniform(GLuint programid, std::string name, float value){
    GLint location = glGetUniformLocation(programid, name.c_str());
    glUniform1f(location, value);
}

void SetVec3Uniform(GLuint programid, std::string name, glm::vec3 value){
    GLint location = glGetUniformLocation(programid, name.c_str());
    glUniform3fv(location, 1, glm::value_ptr(value));
}

void SetVec4Uniform(GLuint programid, std::string name, glm::vec4 value){
    GLint location = glGetUniformLocation(programid, name.c_str());
    glUniform4fv(location, 1, glm::value_ptr(value));
}

void SetMat4x4Uniform(GLuint programid, std::string name, glm::mat4 value){
    GLint location = glGetUniformLocation(programid, name.c_str());
    glUniformMatrix4fv(location, 1, false, glm::value_ptr(value));
}

}
