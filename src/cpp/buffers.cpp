#include "buffers.h"

struct VertexAttribPointer {
	int attribID;
	int length;
	int type;
	bool normalized;
	int stride;
	int offset;
};

//VAO
VAO::VAO() {
	glGenVertexArrays(1, &this->vaoID);
}

void VAO::bind(){
	glBindVertexArray(this->vaoID);
}

void VAO::fillFirst() {
	this->bind();
	this->vbos[0].fillBuffer();
	this->setAttribPointer(0, 3, GL_FLOAT, false, 8, 0);
	this->setAttribPointer(1, 2, GL_FLOAT, false, 8, 3);
	this->setAttribPointer(2, 3, GL_FLOAT, false, 8, 5);
	this->vbos[1].fillBuffer();
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

void VBO::fillBuffer() {
	glBindBuffer(GL_ARRAY_BUFFER, this->vboID);
	glBufferData(GL_ARRAY_BUFFER, this->vertices.size() * sizeof(this->vertices[0]), &this->vertices[0], GL_STATIC_DRAW);
}

//EBO
EBO::EBO(std::vector<unsigned int> indices) {
	glGenBuffers(1, &this->eboID);
	this->indices = indices;
}

void EBO::fillBuffer() {
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->eboID);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, this->indices.size() * sizeof(this->indices[0]), &this->indices[0], GL_STATIC_DRAW);
}
