#include "buffers.h"

void VAO::use(){
	glBindVertexArray(this->vaoID);
}

void VAO::fillVBO(float *vertices, size_t array_length){
	this->use();
	glBindBuffer(GL_ARRAY_BUFFER, this->vboID);
	glBufferData(GL_ARRAY_BUFFER, array_length, vertices, GL_STATIC_DRAW);
}

void VAO::fillEBO(unsigned int *indices, size_t array_length){
	this->use();
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->eboID);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, array_length, indices, GL_STATIC_DRAW);
}

void VAO::setAttrib(int attribID, int length, int type, bool normalized, int stride, int offset){
	this->use();
	glVertexAttribPointer(attribID, length, type, normalized, stride * sizeof(float), (void*)(offset * sizeof(float)));
	glEnableVertexAttribArray(attribID);
}

VAO::VAO(float *vertices, size_t varray_length, unsigned int *indices, size_t iarray_length){
	glGenVertexArrays(1, &this->vaoID);
	glGenBuffers(1, &this->vboID);
	glGenBuffers(1, &this->eboID);
	this->fillVBO(vertices, varray_length);
	this->fillEBO(indices, iarray_length);
	//vertex cordinate
	this->setAttrib(0, 3, GL_FLOAT, false, 5, 0);
	//texture cordinte
	this->setAttrib(1, 2, GL_FLOAT, false, 5, 3);
}