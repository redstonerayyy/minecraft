#ifndef CHUNK_H
#define CHUNK_H

#include <array>
#include "blocks.h"

class Chunk {
public:
	Chunk(int chunkWidth, int baseHeight);


};

std::array<float> generateHeightMap(int width, int depth, std::string seed);

#endif // !CHUNK_H
