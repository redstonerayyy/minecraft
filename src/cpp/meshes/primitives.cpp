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
	vertices.push_back(createVertex(triangle[1], 1.0f, 1.0f, 1.0f, 1.0f, 1.0f));
	vertices.push_back(createVertex(triangle[2], 1.0f, 1.0f, 1.0f, 1.0f, 1.0f));
	indices.push_back(verticeslength);
	indices.push_back(verticeslength + 1);
	indices.push_back(verticeslength + 2);
}

void generateSquare(std::vector<Vertex> &vertices, std::vector<unsigned int> &indices, const float squarecords[4][3], const float cordshift[3]){
	int verticeslength = vertices.size();
	float squarecordsnew[4][3];
	for(int i = 0; i < 4; i++){
		for(int j = 0; j < 3; j++){
			squarecordsnew[i][j] = squarecords[i][j] + cordshift[j];
		}
	}
	vertices.push_back(createVertex(squarecordsnew[0], 1.0f, 1.0f, 1.0f, 1.0f, 1.0f));
	vertices.push_back(createVertex(squarecordsnew[1], 1.0f, 1.0f, 1.0f, 1.0f, 1.0f));
	vertices.push_back(createVertex(squarecordsnew[2], 1.0f, 1.0f, 1.0f, 1.0f, 1.0f));
	vertices.push_back(createVertex(squarecordsnew[3], 1.0f, 1.0f, 1.0f, 1.0f, 1.0f));
	//first triangle
	indices.push_back(verticeslength);
	indices.push_back(verticeslength + 1);
	indices.push_back(verticeslength + 3);
	//seconds triangle
	indices.push_back(verticeslength + 1);
	indices.push_back(verticeslength + 2);
	indices.push_back(verticeslength + 3);
}
