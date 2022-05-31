#ifndef BUFFERS_H
#define BUFFERS_H

#include <glad/gl.h>
#include <string>
#include <iostream>

class VAO {
public:
	//IDs
	unsigned int vaoID;
	unsigned int vboID;
	unsigned int eboID;
	void use();
	void fillVBO(float *vertices, size_t array_length);
	void fillEBO(unsigned int *indices, size_t array_length);
	void setAttrib(int attribID, int length, int type, bool normalized, int stride, int offset);
	VAO();
};

#endif