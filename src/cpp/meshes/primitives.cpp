#include "primitives.h"

Vertex createVertex(float[3] position, float tex1,float tex2, float nvecx, float nvecy, float nvecz){
	Vertex vert;
	vert.Position = glm::vec3(position[0], position[1], position[2]);
	vert.TexCoords = glm::vec2(tex1, tex2);
	vert.Normal = glm::vec3(nvecx, nvecy, nvecz);
	return vert;
}


void generateTriangle(std::vector<Vertex> &vertices, std::vector<unsigned int> &indices, glm::vec3 origin, int MESH_DIRECTION){
	vertices.push_back(createVertex(triangle[0], 1.0f, 1.0f, 1.0f, 1.0f, 1.0f));
	vertices.push_back(createVertex(triangle[1], 1.0f, 1.0f, 1.0f, 1.0f, 1.0f));
	vertices.push_back(createVertex(triangle[2], 1.0f, 1.0f, 1.0f, 1.0f, 1.0f));
	if (MESH_DIRECTION == MESH_UP){

	} else if (MESH_DIRECTION == MESH_LEFT){

	} else if (MESH_DIRECTION == MESH_FRONT){

	} else {}
}
