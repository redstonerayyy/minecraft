#ifndef CHUNK_H
#define CHUNK_H

#include <array>
#include <vector>
#include "PerlinNoise.hpp"
#include "blocks.h"
#include "structs.h"

class Chunk {
public:
	Chunk(int chunkWidth, int baseHeight, std::vector<Vertex> &vertices, std::vector<unsigned int> &indices);
};

void generateHeightMap(int width, int depth, std::vector<float> * heightmap, std::string seed);

#endif // !CHUNK_H
