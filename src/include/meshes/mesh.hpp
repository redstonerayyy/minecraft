#pragma once

#include <vector>
#include "structs.hpp" // vertex struct
#include "buffers.hpp" // VAO, VBO, EBO
#include "shaders.hpp" // shader to draw with

class Mesh {
public:
    //MESH DATA, vertices and indices
    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;

    // construct vao for mesh
    VAO* vao = new VAO();

    // modify and build buffers
    void generateBuffers(bool pos = true, bool tex  = true, bool normal  = true);
    void updateBuffers();
    void draw(ShaderProgram &shaderprogram);

    // initialize with values, need to generate afterwards
    Mesh(std::vector<Vertex> verts, std::vector<unsigned int> inds);
};
