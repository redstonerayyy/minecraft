#include "mesh.h"

Mesh::Mesh(std::vector<Vertex> verts, std::vector<unsigned int> inds){
    this->vertices = verts;
    this->indices = inds;
}

void Mesh::draw(ShaderProgram &shaderprogram) {
	this->vao->bind();
	shaderprogram.use();
	glDrawElements(GL_TRIANGLES, this->vao->eboslength, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}

void Mesh::generateBuffers(bool pos, bool tex, bool normal) {
    this->vao->vbos = { VBO(this->vertices) };
    this->vao->ebos = { EBO(this->indices) };
	this->vao->fill(pos, tex, normal);
}
