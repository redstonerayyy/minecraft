#ifndef MESH_H
#define MESH_H

#include <vector>
#include "structs.h"
#include "buffers.h"
#include "shaders.h"

class Mesh {
public:
	// mesh data
	VAO* vao = new VAO();
	
	void addVBO(std::vector<Vertex> vertices);
	void addEBO(std::vector<unsigned int> indices);

	void generateBuffers();
	void drawMesh(ShaderProgram &shaderprogram);
};

#endif