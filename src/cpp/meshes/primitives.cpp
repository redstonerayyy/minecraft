#include "primitives.h"

Vertex createVertex(const float * position, float tex1, float tex2, float nvecx, float nvecy, float nvecz){
	Vertex vert;
	vert.Position = glm::vec3(position[0], position[1], position[2]);
	vert.TexCoords = glm::vec2(tex1, tex2);
	vert.Normal = glm::vec3(nvecx, nvecy, nvecz);
	return vert;
}


void generateTriangle(std::vector<Vertex> &vertices, std::vector<unsigned int> &indices){
	int verticeslength = vertices.size();
	vertices.push_back(createVertex(triangle[0], 1.0f, 1.0f, 1.0f, 1.0f, 1.0f));
	indices.push_back(verticeslength);
	vertices.push_back(createVertex(triangle[1], 1.0f, 1.0f, 1.0f, 1.0f, 1.0f));
	indices.push_back(verticeslength + 1);
	vertices.push_back(createVertex(triangle[2], 1.0f, 1.0f, 1.0f, 1.0f, 1.0f));
	indices.push_back(verticeslength + 2);
}
