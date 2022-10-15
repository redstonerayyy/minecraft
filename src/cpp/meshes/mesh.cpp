#include "mesh.hpp"

// store data
Mesh::Mesh(std::vector<Vertex> verts, std::vector<unsigned int> inds){
    this->vertices = verts;
    this->indices = inds;
}

// use vao and shader to draw triangles, unbind vertex array
void Mesh::draw(ShaderProgram &shaderprogram) {
	this->vao->bind();
	shaderprogram.use();
	glDrawElements(GL_TRIANGLES, this->vao->ebo->indices.size(), GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}

//generate VBO and EBO
void Mesh::generateBuffers(bool pos, bool tex, bool normal) {
    this->vao->vbo = new VBO(this->vertices);
    this->vao->ebo = new EBO(this->indices);
	this->vao->fill(pos, tex, normal);
}

//update vertices and indices of VBO and EBO and update buffers
void Mesh::updateBuffers(){
    this->vao->vbo->vertices = this->vertices;
    this->vao->ebo->indices = this->indices;
    this->vao->update();
}
