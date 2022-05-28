#ifndef SHADERS_H
#define SHADERS_H

#include <glad/gl.h>
#include <string>
#include <sstream>
#include <fstream>
#include <iostream>

//advanced calculation stuff
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>

unsigned int makeShader(int shaderType, const char *shaderSource);
unsigned int makeProgram(unsigned int *shaders);
std::string readStringFromFile(const char *filePath);

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
    void Shader::setMatrix4fv(const std::string& name, glm::mat4 trans);
};

#endif