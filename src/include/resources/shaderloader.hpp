#pragma once

#include <vector>
#include <string>  
#include "shaders.hpp"
#include "utils.hpp"

class ShaderLoader {
public:
	std::vector<Shader> shaders;
	std::vector<ShaderProgram> shaderprograms;

	ShaderLoader(std::vector<std::string> directories = {}, std::vector<std::string> paths = {});
	ShaderProgram MakeProgram(std::vector<std::string> shadernames);
};
