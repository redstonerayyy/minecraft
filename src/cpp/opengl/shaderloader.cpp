#include "shaderloader.hpp"

ShaderLoader::ShaderLoader(std::vector<std::string> directories, std::vector<std::string> paths){
	
	
	
	
	//std::string shaderDir = "C:\\Users\\paul\\source\\repos\\minecraft\\src\\shaders\\";
	std::string shaderDir = "/home/anton/Github/minecraft/src/shaders/";
	std::string vertexpath = shaderDir + "vertex.glsl";
	std::string fragmentpath = shaderDir + "light_new.glsl";
	std::vector<Shader> shaders;
	shaders.emplace_back(Shader(GL_VERTEX_SHADER, vertexpath.c_str()));
	shaders.emplace_back(Shader(GL_FRAGMENT_SHADER, fragmentpath.c_str()));

	std::string lightvertexpath = shaderDir + "light_vertex.glsl";
	std::string lightfragmentpath = shaderDir + "light.glsl";
	std::vector<Shader> lightshaders;
	lightshaders.emplace_back(Shader(GL_VERTEX_SHADER, lightvertexpath.c_str()));
	lightshaders.emplace_back(Shader(GL_FRAGMENT_SHADER, lightfragmentpath.c_str()));
	ShaderProgram lightShader(lightshaders);
}