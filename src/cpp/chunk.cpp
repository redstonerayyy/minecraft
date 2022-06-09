
void generateHeightMap(int width, int depth, std::vector<float> * heightmap, std::string seed) {
	const siv::PerlinNoise::seed_type seed = seed;
	const siv::PerlinNoise perlin{ seed };

	for (int x = 0; x < width; x++) {
		for (int z = 0; z < depth; z++) {
			const float noise = perlin.octave2D_01((x * 0.01), (z * 0.01), 4);
			heightmap.push_back(noise);
		}
	}
	
}

Chunk::Chunk(int chunkWidth, int baseHeight) {
	std::vector<float> heightMap;
	generateHeightMap(chunkWidth, chunkWidth, &heightMap, "abc");
	std::array<unsigned int, 16 * 256 * 16> chunkBlocks; //xyz

	//generate blocks
	for (int x = 0; x < 16; x++) {
		for (int y = 0; y < 256; y++) {
			for (int z = 0; z < 16; z++) {
				if (floor(heightMap[x * 16 + z] * baseHeight) < y) {
					chunkBlocks[x * 16 + y * 256 + z] = MC_AIR;
				} else {
					chunkBlocks[x * 16 + y * 256 + z] = MC_STONE;
				}
			}
		}
	}

	//generate mesh
	for (int x = 0; x < 16; x++) {
		for (int y = 0; y < 256; y++) {
			for (int z = 0; z < 16; z++) {
				if (chunkBlocks[x * 16 + y * 256 + z] == MC_AIR) {
				} else {
					//is MC_STONE check which sides are air
					if(y + 1 <= 256){//check if out of bounds
						if(chunkBlocks[x * 16 + (y + 1) * 256 + z] == MC_AIR){//y + 1
							
						}
					}
					if(y - 1 >= 0){//check if out of bounds
						if(chunkBlocks[x * 16 + (y - 1) * 256 + z] == MC_AIR){//y - 1

						}
					}
					if(x + 1 <= 16){//check if out of bounds
						if(chunkBlocks[(x + 1) * 16 + y * 256 + z] == MC_AIR){//x + 1

						}
					}
					if(x - 1 >= 0){//check if out of bounds
						if(chunkBlocks[(x - 1) * 16 + y * 256 + z] == MC_AIR){//x - 1

						}
					}
					if(z + 1 <= 16){//check if out of bounds
						if(chunkBlocks[x * 16 + y * 256 + z + 1] == MC_AIR){//z + 1

						}
					}
					if(z - 1 >= 0){//check if out of bounds
						if(chunkBlocks[x * 16 + y * 256 + z - 1] == MC_AIR){//z - 1

						}
					}
				}
			}
		}
	}


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