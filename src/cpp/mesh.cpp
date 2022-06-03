#include "mesh.h"

Mesh::Mesh(std::vector<Vertex> vertices) {
	this->data.vbos.push_back(new VBO(vertices));
	generateMesh();
}

void Mesh::setIndices(std::vector<unsigned int> indices) {
	this->data.ebos.push_back(new EBO(indices));
	generateMesh();
}

void Mesh::setTexture(Texture texture) {
	this->textures.push_back(texture);
}

void Mesh::generateMesh() {
	this->data.fillFirst();
}

void Mesh::drawMesh(Shader &shader) {
	this->data.bint();
	glDrawElements(GL_TRIANGLES, this->data->ebos[0].indices.size(), GL_UNSIGNED_INT, 0);
	//glBindVertexArray(0);
}