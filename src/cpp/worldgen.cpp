#include "worldgen.h"

void smoothWorld(std::vector<Vertex> &vertices, std::vector<unsigned int> &indices) {

	const siv::PerlinNoise::seed_type seed = 123456u;

	const siv::PerlinNoise perlin{ seed };

	for (float z = 0.0f; z < 20; z++)
	{
		for (float x = 0.0f; x < 20; x++)
		{
			const double noise = perlin.octave2D_01((x * 0.01), (z * 0.01), 4);
			Vertex vert;
			vert.Position = glm::vec3(x, floor(noise * 20), z);
			vert.TexCoords = glm::vec2(1.0f, 1.0f);
			vert.Normal = glm::vec3(1.0f, 1.0f, 1.0f);
			vertices.push_back(vert);
			std::cout << vertices.size() << "." << vert.Position.x << ":" << vert.Position.y << ":" << vert.Position.z << std::endl;
		}
	}

	for (unsigned int z = 0; z < 19; z++)
	{
		for (unsigned int x = 0; x < 19; x++)
		{
			indices.insert(indices.end(), { z, z + 20, z + 21});
			indices.insert(indices.end(), { z, z + 1, z + 21});
			std::cout << indices.size() << "." << z << ":" << z + 20 << ":" << z + 21 << "::" << z << ":" << z + 1 << ":" << z + 21 << std::endl;
		}
	}
};