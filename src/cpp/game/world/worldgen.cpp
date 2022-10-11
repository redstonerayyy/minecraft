#include "worldgen.hpp"

std::vector<std::vector<float>> generateNoiseMap(int width, int depth, int octaves, long unsigned int heightmapseed) {
    //set seed
	const siv::PerlinNoise::seed_type seed = heightmapseed;
	const siv::PerlinNoise perlin{ seed };

    //2 dimensional vector
	std::vector<std::vector<float>> noisemap;
	//scale and octaves as parameters
	for (int x = 0; x < width; x++) {
        // fill vector with noise floats between 0 and 1
		noisemap.push_back(std::vector<float>{});
        for (int z = 0; z < depth; z++) {
            // smaple noise at given position, 0.01 as scale
			const float noise = perlin.octave2D_01((x * 0.01), (z * 0.01), octaves);
			noisemap[x].push_back(noise);
		}
	}

    //return vector
	return noisemap;
};
