#include "mesh.h"

Mesh::Mesh(std::vector<Vertex> vertices) {
	VBO verts(vertices);
	this->data->vbos.push_back(verts);
	generateMesh();
}

void Mesh::setIndices(std::vector<unsigned int> indices) {
	EBO inds(indices);
	this->data->ebos.push_back(inds);
	generateMesh();
}

void Mesh::setTexture(Texture texture) {
	this->textures.push_back(texture);
}

void Mesh::generateMesh() {
	this->data->fillFirst();
}

void Mesh::drawMesh(Shader &shader) {
	this->data->bind();
	glDrawElements(GL_TRIANGLES, this->data->ebos[0].indices.size(), GL_UNSIGNED_INT, 0);
	//glBindVertexArray(0);
}