#ifndef MESH_H
#define MESH_H

#include <vector>
#include "structs.h"
#include "buffers.h"
#include "shaders.h"

class Mesh {
public:
	// mesh data
	VAO* data = new VAO();
	std::vector<Texture> textures;
	
	Mesh(std::vector<Vertex> vertices);
	
	void setIndices(std::vector<unsigned int> indices);
	void setTexture(Texture texture);

	void generateMesh();
	void drawMesh(Shader &shader);
};

#endif