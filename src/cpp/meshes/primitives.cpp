#include "primitives.h"

Vertex createVertex(const float * position, float tex1, float tex2, float nvecx, float nvecy, float nvecz){
	Vertex vert;
	vert.Position = glm::vec3(position[0], position[1], position[2]);
	vert.TexCoords = glm::vec2(tex1, tex2);
	vert.Normal = glm::vec3(nvecx, nvecy, nvecz);
	return vert;
}

void generateSquare(std::vector<Vertex> &vertices, std::vector<unsigned int> &indices, const float squarecords[4][3], const float cordshift[3], float pvector[3], const float normal[3]){
	int verticeslength = vertices.size();
	glm::mat4 transmat = glm::translate(glm::mat4(1.0f), glm::vec3(pvector[0], pvector[1], pvector[2]));
	float squarecordsnew[4][3];
	for(int i = 0; i < 4; i++){
		for(int j = 0; j < 3; j++){
			squarecordsnew[i][j] = squarecords[i][j] + cordshift[j];
		}
		glm::vec4 temp = transmat * glm::vec4(squarecordsnew[i][0], squarecordsnew[i][1], squarecordsnew[i][2], 1.0f);
		squarecordsnew[i][0] = temp.x;
		squarecordsnew[i][1] = temp.y;
		squarecordsnew[i][2] = temp.z;
	}
	//create vertices
	vertices.push_back(createVertex(squarecordsnew[0], defaulttexcoords[0][0], defaulttexcoords[0][1], normal[0], normal[1], normal[2]));
	vertices.push_back(createVertex(squarecordsnew[1], defaulttexcoords[1][0], defaulttexcoords[1][1], normal[0], normal[1], normal[2]));
	vertices.push_back(createVertex(squarecordsnew[2], defaulttexcoords[2][0], defaulttexcoords[2][1], normal[0], normal[1], normal[2]));
	vertices.push_back(createVertex(squarecordsnew[3], defaulttexcoords[3][0], defaulttexcoords[3][1], normal[0], normal[1], normal[2]));
	//first triangle
	indices.push_back(verticeslength);
	indices.push_back(verticeslength + 1);
	indices.push_back(verticeslength + 2);
	//second triangle
	indices.push_back(verticeslength + 1);
	indices.push_back(verticeslength + 2);
	indices.push_back(verticeslength + 3);
}

void generateCube(std::vector<Vertex> &vertices, std::vector<unsigned int> &mesh_indices, float pvector[3], int sides[6]){
	const float shiftzero[3] = {0.0f, 0.0f, 0.0f};
	const float shiftx[3] = {-1.0f, 0.0f, 0.0f};
	const float shifty[3] = {0.0f, 1.0f, 0.0f};
	const float shiftz[3] = {0.0f, 0.0f, -1.0f};
	if(sides[0]){//left
		generateSquare(vertices, mesh_indices, squarex, shiftzero, pvector, normals[0]);
	}
	if(sides[1]){//bottom
		generateSquare(vertices, mesh_indices, squarey, shiftzero, pvector, normals[1]);
	}
	if(sides[2]){//front
		generateSquare(vertices, mesh_indices, squarez, shiftzero, pvector, normals[2]);
	}
	if(sides[3]){//left
		generateSquare(vertices, mesh_indices, squarex, shiftx, pvector, normalsreverse[0]);
	}
	if(sides[4]){//top
		generateSquare(vertices, mesh_indices, squarey, shifty, pvector, normalsreverse[1]);
	}
	if(sides[5]){//back
		generateSquare(vertices, mesh_indices, squarez, shiftz, pvector, normalsreverse[2]);
	}
}