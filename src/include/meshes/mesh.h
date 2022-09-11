#ifndef MESH_H
#define MESH_H

#include <vector>
#include "structs.h"
#include "buffers.h"
#include "shaders.h"

class Mesh {
public:
    //MESH DATA, vertices and indices
    std::vector<std::vector<Vertex>> verticesarrays;
    std::vector<std::vector<unsigned int> indicesarrays;
    
    void addVerticeArray(std::vector<Vertex> vertices);
    void addIndiceArray(std::vector<unsigned int> indices);

    std::vector<Vertex> ConcatVerticeArrays(std::vector<int> indices);
    std::vector<unsigned int> ConcatIndiceArrays(std::vector<int> indices);
    
    //VAOS
    std::vector<VAO> vaos;
    
    void addVAO(std::vector<int> varrays, std::vector<int> iarrays, std::string name);
    void deleteVAO(std::string name);
    void bindVAO(std::string name);
    void drawVAO(ShaderProgram &shaderprogram);

    Mesh();
};

#endif