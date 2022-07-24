#include "worldgen.h"
#include <array>

void smoothWorld(std::vector<Vertex> &vertices, std::vector<unsigned int> &mesh_indices) {

	const siv::PerlinNoise::seed_type seed = 123456u;

	const siv::PerlinNoise perlin{ seed };

	int size = 100;

	for (double z = 0.0f; z < size; z++)
	{
		for (double x = 0.0f; x < size; x++)
		{
			const double noise = perlin.octave2D_01((x * 0.01), (z * 0.01), 4);
			Vertex vert;
			vert.Position = glm::vec3(x, floor((float)noise * 20), z);
		}
	}
};
