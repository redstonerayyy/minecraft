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
	if(0 < this->vbos.size() && this->vbos.size() < 2){
		this->vboslength = vbos[0].vertices.size();
		this->vbos[0].fillBuffer();
	} else {
		std::vector<Vertex> all_vertices;
		for(int i = 0; i < this->vbos.size(); i++){
			all_vertices.insert(all_vertices.end(), vbos[i].vertices.begin(), vbos[i].vertices.end());
		};
		this->vboslength = all_vertices.size();
		glGenBuffers(1, &this->vboallid);
		glBindBuffer(GL_ARRAY_BUFFER, this->vboallid);
		glBufferData(GL_ARRAY_BUFFER, all_vertices.size() * sizeof(all_vertices[0]), &all_vertices[0], GL_DYNAMIC_DRAW);
	}
	if(0 < this->ebos.size() && this->ebos.size() < 2){
		this->eboslength = ebos[0].indices.size();
		this->ebos[0].fillBuffer();
	} else {
		std::vector<unsigned int> all_indices;
		for(int i = 0; i < this->ebos.size(); i++){
			all_indices.insert(all_indices.end(), ebos[i].indices.begin(), ebos[i].indices.end());
		};
		this->eboslength = all_indices.size();
		glGenBuffers(1, &this->eboallid);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->eboallid);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, all_indices.size() * sizeof(all_indices[0]), &all_indices[0], GL_DYNAMIC_DRAW);
	}

	//position, texture, normal
	if(pos) { this->setAttribPointer(0, 3, GL_FLOAT, false, 8, 0); };
	if(tex) { this->setAttribPointer(1, 2, GL_FLOAT, false, 8, 3); };
	if(normal) { this->setAttribPointer(2, 3, GL_FLOAT, false, 8, 5); };
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
	glBufferData(GL_ARRAY_BUFFER, this->vertices.size() * sizeof(this->vertices[0]), &this->vertices[0], GL_DYNAMIC_DRAW);
}

//EBO
EBO::EBO(std::vector<unsigned int> indices) {
	glGenBuffers(1, &this->eboID);
	this->indices = indices;
}

void EBO::fillBuffer() {
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->eboID);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, this->indices.size() * sizeof(this->indices[0]), &this->indices[0], GL_DYNAMIC_DRAW);
}
