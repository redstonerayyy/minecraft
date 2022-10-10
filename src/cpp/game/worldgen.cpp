#include "worldgen.hpp"

std::vector<float> generateNoiseMap(int width, int depth, int octaves, long unsigned int heightmapseed) {
	const siv::PerlinNoise::seed_type seed = heightmapseed;
	const siv::PerlinNoise perlin{ seed };

	std::vector<float> noisemap;
	//scale and octaves as parameters
	for (int x = 0; x < width; x++) {
		for (int z = 0; z < depth; z++) {
			const float noise = perlin.octave2D_01((x * 0.01), (z * 0.01), octaves);
			noisemap.push_back(noise);
		}
	}

	return noisemap;
};
