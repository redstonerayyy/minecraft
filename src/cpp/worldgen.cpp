#include "worldgen.h"

std::vector<Vertex> smoothWorld() {
	std::vector<Vertex> vertices;
	std::vector<unsigned int> indices;

	const siv::PerlinNoise::seed_type seed = 123456u;

	const siv::PerlinNoise perlin{ seed };

	for (int y = 0; y < 5; ++y)
	{
		for (int x = 0; x < 5; ++x)
		{
			const double noise = perlin.octave2D_01((x * 0.01), (y * 0.01), 4);

			std::cout << noise << '\t';
		}

		std::cout << '\n';
	}

	return vertices;
};