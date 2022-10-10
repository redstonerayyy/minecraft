#ifndef MESH_H
#define MESH_H

#include <vector>
#include "structs.hpp"
#include "buffers.hpp"
#include "shaders.hpp"

class Mesh {
public:
    //MESH DATA, vertices and indices
    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;

    VAO* vao = new VAO();

    void generateBuffers(bool pos = true, bool tex  = true, bool normal  = true);
    void draw(ShaderProgram &shaderprogram);

    Mesh(std::vector<Vertex> verts, std::vector<unsigned int> inds);
};

#endif