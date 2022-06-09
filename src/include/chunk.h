#ifndef CHUNK_H
#define CHUNK_H

#include <array>
#include "blocks.h"

class Chunk {
public:
	Chunk(int chunkWidth, int baseHeight);
};

void generateHeightMap(int width, int depth, std::vector<float> * heightmap, std::string seed);

#endif // !CHUNK_H
