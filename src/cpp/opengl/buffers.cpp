#include "buffers.hpp"

//VAO
VAO::VAO() {
	glGenVertexArrays(1, &this->vaoID);
}

void VAO::bind(){
	glBindVertexArray(this->vaoID);
}

void VAO::fill(bool pos, bool tex, bool normal) {
	this->bind();
	this->vbo->fillBuffer();
    this->ebo->fillBuffer();
	
    //position, texture, normal
	if(pos) { this->setAttribPointer(0, 3, GL_FLOAT, false, 8, 0); };
	if(tex) { this->setAttribPointer(1, 2, GL_FLOAT, false, 8, 3); };
	if(normal) { this->setAttribPointer(2, 3, GL_FLOAT, false, 8, 5); };
}

void VAO::update(){
	this->bind();
	this->vbo->updateBuffer();
    this->ebo->updateBuffer();
}

void VAO::setAttribPointer(int attribID, int length, int type, bool normalized, int stride, int offset) {
	this->bind();
	glVertexAttribPointer(
		attribID, 
		length, 
		type, 
		normalized, 
		stride * sizeof(float), 
		(void*)(offset * sizeof(float))
	);
	glEnableVertexAttribArray(attribID);
}

//VBO
VBO::VBO(std::vector<Vertex> vertices) {
	glGenBuffers(1, &this->vboID);
	this->vertices = vertices;
}

void VBO::bind(){
    glBindBuffer(GL_ARRAY_BUFFER, this->vboID);
}

void VBO::fillBuffer() {
    this->bind();
	glBufferData(GL_ARRAY_BUFFER, this->vertices.size() * sizeof(this->vertices[0]), &this->vertices[0], GL_DYNAMIC_DRAW);
}

void VBO::updateBuffer(){
    this->bind();
	glBufferSubData(GL_ARRAY_BUFFER, 0, this->vertices.size() * sizeof(this->vertices[0]), &this->vertices[0]);
}

//EBO
EBO::EBO(std::vector<unsigned int> indices) {
	glGenBuffers(1, &this->eboID);
	this->indices = indices;
}

void EBO::bind(){
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->eboID);
}

void EBO::fillBuffer() {
    this->bind();
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, this->indices.size() * sizeof(this->indices[0]), &this->indices[0], GL_DYNAMIC_DRAW);
}

void EBO::updateBuffer(){
    this->bind();
	glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, 0, this->indices.size() * sizeof(this->indices[0]), &this->indices[0]);
}