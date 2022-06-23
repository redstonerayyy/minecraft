#ifndef MESHTRANSFORM_H
#define MESHTRANSFORM_H

#include "meshtransform.h"
#include "structs.h"

#include <vector>

//advanced calculation stuff
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>


void RotateVertices(std::vector<Vertex> &vertices, glm::mat4 matrix);

#endif