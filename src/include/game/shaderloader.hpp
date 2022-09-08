#pragma once

#include <vector>
#include <string>  
#include "shaders.h"
#include "utils.h"

class ShaderLoader {
public:
	std::vector<Shader> shaders;
	std::vector<ShaderProgram> shaderprograms;

	ShaderLoader(std::vector<std::string> directories = {}, std::vector<std::string> paths = {});
	// ReadSource();
};
