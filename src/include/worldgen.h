#ifndef WORLDGEN_H
#define WORLDGEN_H

#include <iostream>
#include "PerlinNoise.hpp"
#include "structs.h"

void smoothWorld(std::vector<Vertex> &vertices, std::vector<unsigned int> &indices);

#endif
