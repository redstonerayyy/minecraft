std::array<float> generateHeightMap(int width, int depth, std::string seed) {
	const siv::PerlinNoise::seed_type seed = seed;
	const siv::PerlinNoise perlin{ seed };

	std::array<float, width * depth> heightmap; //xz

	for (int x = 0; x < width; x++) {
		for (int z = 0; z < depth; z++) {
			const float noise = perlin.octave2D_01((x * 0.01), (z * 0.01), 4);
			heightmap[x + z] = noise;
		}
	}
	return heightmap;
}

Chunk::Chunk(int chunkWidth, int baseHeight) {
	std::array<float> heightMap = generateHeightMap(chunkWidth, chunkWidth, "abc");
	std::array<unsigned int, 16 * 256 * 16> chunkBlocks; //xyz

	//generate blocks
	for (int x = 0; x < 16; x++) {
		for (int y = 0; y < 256; y++) {
			for (int z = 0; z < 16; z++) {
				if (floor(heightMap[x + z] * baseHeight) < y) {
					chunkBlocks[x + y + z] = MC_AIR;
				} else {
					chunkBlocks[x + y + z] = MC_STONE;
				}
			}
		}
	}

	//generate mesh

	for (unsigned int z = 0; z < size - 1; z++)
	{
		for (unsigned int x = 0; x < size - 1; x++)
		{
			unsigned int triangleone[] = { z * size + x, (z + 1) * size + x, (z + 1) * size + x + 1 };
			unsigned int triangletwo[] = { z * size + x, z * size + x + 1, (z + 1) * size + x + 1 };
			mesh_indices.insert(mesh_indices.end(), triangleone, triangleone + 3);
			mesh_indices.insert(mesh_indices.end(), triangletwo, triangletwo + 3);

			//calculate normals
			glm::vec3 vec1_1 = vertices[triangleone[1]].Position - vertices[triangleone[0]].Position;
			glm::vec3 vec2_1 = vertices[triangleone[2]].Position - vertices[triangleone[0]].Position;
			glm::vec3 normal1 = glm::normalize(glm::cross(vec1_1, vec2_1));

			vertices[triangleone[0]].Normal = normal1;
			vertices[triangleone[1]].Normal = normal1;
			vertices[triangleone[2]].Normal = normal1;

			glm::vec3 vec1_2 = vertices[triangletwo[1]].Position - vertices[triangletwo[0]].Position;
			glm::vec3 vec2_2 = vertices[triangletwo[2]].Position - vertices[triangletwo[0]].Position;
			glm::vec3 normal2 = glm::normalize(glm::cross(vec1_2, vec2_2));

			vertices[triangletwo[0]].Normal = normal2;
			vertices[triangletwo[1]].Normal = normal2;
			vertices[triangletwo[2]].Normal = normal2;
		}
	}
}