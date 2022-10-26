#include "shaders.hpp"
// util header
#include "utils.hpp"

#include <glad/gl.h>

// advanced calculation stuff
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>

// read shader file and compile opengl shader
Shader::Shader(int shaderType, const char *shaderpath, std::string filename)
{
	// GL_VERTEX_SHADER, GL_FRAGMENT_SHADER
    this->filename = filename; // store name
	this->shaderID = glCreateShader(shaderType); // create opengl shader object
	std::string shaderstring = Utils::readStringFromFile(shaderpath); // read shadersource from file
	const char *shaderSource = shaderstring.c_str();
	glShaderSource(this->shaderID, 1, &shaderSource, NULL); // set source
	glCompileShader(this->shaderID); // compile shader

    // check for compilation errors
	int success_shader;
	char infoLog[512];
	glGetShaderiv(this->shaderID, GL_COMPILE_STATUS, &success_shader);

	if (!success_shader)
	{
		glGetShaderInfoLog(this->shaderID, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::COMPILATION_FAILED\n"
							<< infoLog << std::endl;
	}
}

// link shaders to shader program
ShaderProgram::ShaderProgram(std::vector<Shader> shaders)
{
	this->programID = glCreateProgram(); // create opengl shader program
	for (int i = 0; i < shaders.size(); i++) // attach shaders
	{ // one int is 4 bytes long
		glAttachShader(this->programID, shaders[i].shaderID);
        this->shaderfilenames.push_back(shaders[i].filename);
    }
	glLinkProgram(this->programID); //link

    // check for link errors
	int success_program;
	char infoLog[512];
	glGetProgramiv(this->programID, GL_LINK_STATUS, &success_program);

	if (!success_program)
	{
		glGetProgramInfoLog(this->programID, 512, NULL, infoLog);
		std::cout << "ERROR::PROGRAM::LINKING_FAILED\n"
							<< infoLog << std::endl;
	}
}

// use shader program
void ShaderProgram::use()
{
	glUseProgram(this->programID);
}

// functions for setting various uniforms
void ShaderProgram::setBool(const std::string &name, bool value)
{
	glUniform1i(glGetUniformLocation(this->programID, name.c_str()), (int)value);
}

void ShaderProgram::setInt(const std::string &name, int value)
{
	glUniform1i(glGetUniformLocation(this->programID, name.c_str()), value);
}

void ShaderProgram::setFloat(const std::string &name, float value)
{
	glUniform1f(glGetUniformLocation(this->programID, name.c_str()), value);
}

void ShaderProgram::setVec3(const std::string &name, float x, float y, float z)
{
	float vec3[] = {
			x, y, z};
	glUniform3fv(glGetUniformLocation(this->programID, name.c_str()), 1, vec3);
}

void ShaderProgram::setVec4(const std::string &name, float x, float y, float z, float w)
{
	float vec4[] = {
			x, y, z, w};
	glUniform4fv(glGetUniformLocation(this->programID, name.c_str()), 1, vec4);
}

void ShaderProgram::setMatrix4fv(const std::string &name, glm::mat4 trans)
{
	glUniformMatrix4fv(glGetUniformLocation(this->programID, name.c_str()), 1, GL_FALSE, glm::value_ptr(trans));
}
