#ifndef STRUCTS_H
#define STRUCTS_H

#include <glm.hpp>
#include <string>

struct Vertex {
	glm::vec3 Position;
	glm::vec2 TexCoords;
	glm::vec3 Normal;
};

struct TextureStruct {
	unsigned int id;
	std::string type;
	std::string name;
};

#endif