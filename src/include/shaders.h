#ifndef SHADERS_H
#define SHADERS_H

#include <glad/gl.h>
#include <string>
#include <iostream>

//advanced calculation stuff
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>

//read from file and compile
unsigned int makeShader(int shaderType, const char *shaderSource);
//link vertex and fragment shader to program
unsigned int makeProgram(unsigned int *shaders);

class Shader {
public:
    // the program ID
    unsigned int programID;
    // constructor reads and builds the shader
    Shader(const char* vertexPath, const char* fragmentPath);
    // use/activate the shader
    void use();
    // utility uniform functions
    void setBool(const std::string &name, bool value);  
    void setInt(const std::string &name, int value);   
    void setFloat(const std::string &name, float value);
    void setMatrix4fv(const std::string& name, glm::mat4 trans);
    void setVec3(const std::string& name, float x, float y, float z);
    void Shader::setVec4(const std::string& name, float x, float y, float z, float w);
};

#endif