#include "mesh.h"

void Mesh::addVBO(std::vector<Vertex> vertices){
	this->vao->vbos.push_back(VBO(vertices));
}

void Mesh::addEBO(std::vector<unsigned int> indices){
	this->vao->ebos.push_back(EBO(indices));
}

void Mesh::generateBuffers() {
	this->vao->fill();
}

void Mesh::drawMesh(ShaderProgram &shaderprogram) {
	this->vao->bind();
	glDrawElements(GL_TRIANGLES, this->vao->eboslength, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}
