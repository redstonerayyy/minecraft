#ifndef BUFFERS_H
#define BUFFERS_H

#include <glad/gl.h>
#include <string>
#include <iostream>
#include <vector>
#include "structs.h"

class VBO;
class EBO;

class VAO {
public:
	unsigned int vaoID;
	unsigned int vboslength;
	unsigned int eboslength;
	std::vector<VBO> vbos;
	std::vector<EBO> ebos;
	
	VAO();

	void bind();
	void fill();
	void setAttribPointer(int attribID, int length, int type, bool normalized, int stride, int offset);

private:
	unsigned int vboallid;
	unsigned int eboallid;
};

class VBO {
public:
	unsigned int vboID;
	std::vector<Vertex> vertices;

	VBO(std::vector<Vertex> vertices);

	void fillBuffer();
};

class EBO {
public:
	unsigned int eboID;
	std::vector<unsigned int> indices;

	EBO(std::vector<unsigned int> indices);

	void fillBuffer();
};

#endif