#ifndef MESHTRANSFORM_H
#define MESHTRANSFORM_H

#include "meshtransform.h"
#include "structs.h"

#include <vector>
#include <math.h>

//advanced calculation stuff
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>
//#include <gtc/quaternion.hpp>
#include <gtx/quaternion.hpp>

void RotateVertices(std::vector<Vertex> &vertices, glm::mat4 matrix);
glm::mat4 RotationMatrixZ(double angle);
glm::mat4 RotateVerticesQuaternion(glm::vec4 rotation);

#endif