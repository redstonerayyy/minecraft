#include "mesh.h"

void Mesh::addVerticeArray(std::vector<Vertex> vertices){
    this->verticesarrays->push_back(vertices);
}

void Mesh::addIndiceArray(std::vector<unsigned int> indices){
    this->indicesarrays->push_back(indices);
}




void Mesh::drawVAO(ShaderProgram &shaderprogram) {
	this->vao->bind();
	shaderprogram.use();
	glDrawElements(GL_TRIANGLES, this->vao->eboslength, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}











void Mesh::addVBO(std::vector<Vertex> vertices){
	this->vao->vbos.push_back(VBO(vertices));
}

void Mesh::addEBO(std::vector<unsigned int> indices){
	this->vao->ebos.push_back(EBO(indices));
}

void Mesh::generateBuffers(bool pos, bool tex, bool normal) {
	this->vao->fill(pos, tex, normal);
}


std::vector<VBO> Mesh::getVbos(){
    return this->vao->vbos;
}

std::vector<EBO> Mesh::getEbos(){
    return this->vao->ebos;
}