#include "mesh.h"

void Mesh::addVBO(std::vector<Vertex> vertices){
	this->vao->vbos.push_back(VBO(vertices));
}

void Mesh::addEBO(std::vector<unsigned int> indices){
	this->vao->ebos.push_back(EBO(indices));
}

void Mesh::generateBuffers(bool pos, bool tex, bool normal) {
	this->vao->fill(pos, tex, normal);
}

void Mesh::drawMesh(ShaderProgram &shaderprogram) {
	this->vao->bind();
	shaderprogram.use();
	glDrawElements(GL_TRIANGLES, this->vao->eboslength, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}

std::vector<VBO> Mesh::getVbos(){
    return this->vao->vbos;
}

std::vector<EBO> Mesh::getEbos(){
    return this->vao->ebos;
}