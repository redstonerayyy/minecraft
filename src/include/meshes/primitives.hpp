#pragma once

#include "structs.hpp"
#include "primitivedata.hpp"
//#include "enums.h"
//#include "meshtransform.h"

#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>

#include <vector>
#include <array>

//add primitive shapes to a meshes buffer data
//take a vertex array pointer and a indice array pointer
Vertex createVertex(float x, float y, float z, float tex1, float tex2, float nvecx, float nvecz, float nvecy);
void generateSquare(std::vector<Vertex> &vertices, std::vector<unsigned int> &indices, const float squarecords[4][3], const float cordshift[3], float pvector[3], const float normal[3]);
void generateCube(std::vector<Vertex> &vertices, std::vector<unsigned int> &mesh_indices, float pvector[3], std::array<int, 6> sides);
