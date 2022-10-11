#pragma once

#include <string>
#include <iostream>
#include <vector>

//advanced calculation stuff
#include <glm.hpp>

class Shader {
public:
    unsigned int shaderID;
    std::string filename;
    Shader(int shaderType, const char * shaderpath, std::string filename);
};

class ShaderProgram {
public:
    unsigned int programID;
    std::vector<std::string> shaderfilenames;
    ShaderProgram(std::vector<Shader> shaders);
    
    void use();
    // utility uniform functions
    void setInt(const std::string &name, int value);   
    void setBool(const std::string &name, bool value); 
    void setFloat(const std::string &name, float value);

    void setVec3(const std::string& name, float x, float y, float z);
    void setVec4(const std::string& name, float x, float y, float z, float w);
    void setMatrix4fv(const std::string& name, glm::mat4 trans);
};
