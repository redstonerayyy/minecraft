#pragma once

#include <glad/gl.h>
#include <string>
#include <iostream>
#include <vector>
#include "structs.hpp"

// class EBO;
// hold indices and fill a buffer or
// update a buffer with the current indices
class EBO {
public:
	unsigned int eboID;
	std::vector<unsigned int> indices;

	EBO(std::vector<unsigned int> indices);

    void bind();
	void fillBuffer();
    void updateBuffer();
};

// class VBO;
// hold vertices and fill a buffer or
// update a buffer with the current vertices
class VBO {
public:
    unsigned int vboID;
    std::vector<Vertex> vertices;

    VBO(std::vector<Vertex> vertices);

    void bind();
    void fillBuffer();
    void updateBuffer();
};

// hold an ebo and vbo
// fill or update both and set
// the attribute pointers for
// this vao
class VAO {
public:
	unsigned int vaoID;
	VBO* vbo;
	EBO* ebo;

	VAO();

	void bind();
	void fill(bool pos, bool tex, bool normal);
    void update();
	void setAttribPointer(int attribID, int length, int type, bool normalized, int stride, int offset);
};
