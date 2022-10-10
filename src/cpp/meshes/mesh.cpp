#include "mesh.hpp"

Mesh::Mesh(std::vector<Vertex> verts, std::vector<unsigned int> inds){
    this->vertices = verts;
    this->indices = inds;
}

void Mesh::draw(ShaderProgram &shaderprogram) {
	this->vao->bind();
	shaderprogram.use();
	glDrawElements(GL_TRIANGLES, this->vao->ebo->indices.size(), GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}

void Mesh::generateBuffers(bool pos, bool tex, bool normal) {
    this->vao->vbo = new VBO(this->vertices);
    this->vao->ebo = new EBO(this->indices);
	this->vao->fill(pos, tex, normal);
}

void Mesh::updateBuffers(){
    this->vao->vbo->vertices = this->vertices;
    this->vao->ebo->indices = this->indices;
    this->vao->update();
}
