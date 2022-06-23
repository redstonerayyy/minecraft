#include "shaders.h"
//util header
#include "utils.h"

//advanced calculation stuff
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>

unsigned int makeShader(int shaderType, const char *shaderSource){
	unsigned int shader;
	shader = glCreateShader(shaderType);
	glShaderSource(shader, 1, &shaderSource, NULL);
	glCompileShader(shader);

	int  success_shader;
	char infoLog[512];
	glGetShaderiv(shader, GL_COMPILE_STATUS, &success_shader);

	if(!success_shader)
	{
		glGetShaderInfoLog(shader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::COMPILATION_FAILED\n" << infoLog << std::endl;
	}
	return shader;
}

unsigned int makeProgram(unsigned int *shaders){
	unsigned int program;
	program = glCreateProgram();
	for(int i = 0; i < sizeof(shaders)/4; i++){ //one int is 4 bytes long
		glAttachShader(program, shaders[i]);
	}
	glLinkProgram(program);

	int succes_program;
	char infoLog[512];
	glGetProgramiv(program, GL_LINK_STATUS, &succes_program);
	
	if(!succes_program) {
		glGetProgramInfoLog(program, 512, NULL, infoLog);
		std::cout << "ERROR::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
	}
	return program;
}


Shader::Shader(const char* vertexPath, const char* fragmentPath)
{
	std::string vertexShaderSource = readStringFromFile(vertexPath);
	std::string fragmentShaderSource = readStringFromFile(fragmentPath);
	
	unsigned int shaders[2];
	shaders[0] = makeShader(GL_VERTEX_SHADER, vertexShaderSource.c_str());
	shaders[1] = makeShader(GL_FRAGMENT_SHADER, fragmentShaderSource.c_str());
	unsigned int program = makeProgram(shaders);
	glDeleteShader(shaders[0]);
	glDeleteShader(shaders[1]);
	this->programID = program;
}

void Shader::use() 
{ 
    glUseProgram(this->programID);
}

void Shader::setBool(const std::string &name, bool value)
{         
    glUniform1i(glGetUniformLocation(this->programID, name.c_str()), (int)value); 
}

void Shader::setInt(const std::string &name, int value)
{ 
    glUniform1i(glGetUniformLocation(this->programID, name.c_str()), value); 
}

void Shader::setFloat(const std::string &name, float value)
{ 
    glUniform1f(glGetUniformLocation(this->programID, name.c_str()), value); 
}

void Shader::setMatrix4fv(const std::string& name, glm::mat4 trans) {
	glUniformMatrix4fv(glGetUniformLocation(this->programID, name.c_str()), 1, GL_FALSE, glm::value_ptr(trans));
}

void Shader::setVec3(const std::string& name, float x, float y, float z) {
	float vec3[] = {
		x, y, z
	};
	glUniform3fv(glGetUniformLocation(this->programID, name.c_str()), 1, vec3);
}

void Shader::setVec4(const std::string& name, float x, float y, float z, float w) {
	float vec4[] = {
		x, y, z, w
	};
	glUniform3fv(glGetUniformLocation(this->programID, name.c_str()), 1, vec4);
}