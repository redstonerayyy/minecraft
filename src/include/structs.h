#ifndef STRUCTS_H
#define STRUCTS_H

#include <glm.hpp>

struct Vertex {
	glm::vec3 Position;
	glm::vec3 Normal;
	glm::vec2 TexCoords;
};

struct Texture {
	unsigned int id;
	std::string type;
	std::string name;
};

#endif