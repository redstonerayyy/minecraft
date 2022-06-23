#include "meshtransform.h"

void RotateVertices(std::vector<Vertex> &vertices, glm::mat4 matrix){
	for (int i = 0; i < vertices.size(); i++) {
		glm::vec4 modified = glm::vec4(vertices[i].Position, 1.0f) * matrix;
		vertices[i].Position = glm::vec3(modified[0], modified[1], modified[1]);
	}
}
