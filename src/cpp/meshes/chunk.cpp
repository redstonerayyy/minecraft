
#include "chunk.h"

void generateHeightMap(int width, int depth, std::vector<float> * heightmap, long unsigned int heightmapseed) {
	const siv::PerlinNoise::seed_type seed = heightmapseed;
	const siv::PerlinNoise perlin{ seed };

	for (int x = 0; x < width; x++) {
		for (int z = 0; z < depth; z++) {
			const float noise = perlin.octave2D_01((x * 0.01), (z * 0.01), 4);
			heightmap->push_back(noise);
		}
	}
}

Chunk::Chunk(int chunkWidth, int baseHeight, std::vector<Vertex> &vertices, std::vector<unsigned int> &mesh_indices) {
	std::vector<float> heightMap;
	generateHeightMap(chunkWidth, chunkWidth, &heightMap, 123456u);
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
	
	// std::vector<Vertex> vertices;
	// std::vector<unsigned int> indices;

	int addindexindices = 0;
	//generate mesh
	for (float x = 0; x < 16; x++) {
		for (float y = 0; y < 256; y++) {
			for (float z = 0; z < 16; z++) {
				if (chunkBlocks[x * 16 + y * 256 + z] == MC_AIR) {
					//nothing to render if it is air
				} else {
					//is MC_STONE check which sides are air
					//TOP
					if(y + 1 < 256){//check if out of bounds
						if(chunkBlocks[x * 16 + (y + 1) * 256 + z] == MC_AIR){//y + 1
							//4 vertices
							vertices.push_back({
								glm::vec3(x, y + 1, z),//Position 
								glm::vec2(0.0f, 0.0f),//TexCoords
								glm::vec3(0.0f, 0.0f, 0.0f),//Normal
							});
							
							//top
							vertices.push_back({
								glm::vec3(x, y + 1, z + 1),//Position 
								glm::vec2(0.0f, 1.0f),//TexCoords
								glm::vec3(0.0f, 0.0f, 0.0f),//Normal
							});

							vertices.push_back({
								glm::vec3(x + 1, y + 1, z + 1),//Position 
								glm::vec2(1.0f, 1.0f),//TexCoords
								glm::vec3(0.0f, 0.0f, 0.0f),//Normal
							});

							vertices.push_back({
								glm::vec3(x + 1, y + 1, z),//Position 
								glm::vec2(1.0f, 0.0f),//TexCoords
								glm::vec3(0.0f, 0.0f, 0.0f),//Normal
							});

							unsigned int triangleone[] = { addindexindices, addindexindices + 1, addindexindices + 2};
							unsigned int triangletwo[] = { addindexindices, addindexindices + 3, addindexindices + 2};
							mesh_indices.insert(mesh_indices.end(), triangleone, triangleone + 3);
							mesh_indices.insert(mesh_indices.end(), triangletwo, triangletwo + 3);
							addindexindices += 6;
						}
					}
					//BOTTOM
					if(y - 1 >= 0){//check if out of bounds
						if(chunkBlocks[x * 16 + (y - 1) * 256 + z] == MC_AIR){//y - 1
							//4 vertices
							vertices.push_back({
								glm::vec3(x, y - 1, z),//Position 
								glm::vec2(0.0f, 0.0f),//TexCoords
								glm::vec3(0.0f, 0.0f, 0.0f),//Normal
							});
							
							vertices.push_back({
								glm::vec3(x, y - 1, z + 1),//Position 
								glm::vec2(0.0f, 1.0f),//TexCoords
								glm::vec3(0.0f, 0.0f, 0.0f),//Normal
							});

							vertices.push_back({
								glm::vec3(x + 1, y - 1, z + 1),//Position 
								glm::vec2(1.0f, 1.0f),//TexCoords
								glm::vec3(0.0f, 0.0f, 0.0f),//Normal
							});

							vertices.push_back({
								glm::vec3(x + 1, y - 1, z),//Position 
								glm::vec2(1.0f, 0.0f),//TexCoords
								glm::vec3(0.0f, 0.0f, 0.0f),//Normal
							});

							unsigned int triangleone[] = { addindexindices, addindexindices + 1, addindexindices + 2};
							unsigned int triangletwo[] = { addindexindices, addindexindices + 3, addindexindices + 2};
							mesh_indices.insert(mesh_indices.end(), triangleone, triangleone + 3);
							mesh_indices.insert(mesh_indices.end(), triangletwo, triangletwo + 3);
							addindexindices += 6;
						}
					}
					//RIGHT
					if(x + 1 < 16){//check if out of bounds
						if(chunkBlocks[(x + 1) * 16 + y * 256 + z] == MC_AIR){//x + 1
							//4 vertices
							vertices.push_back({
								glm::vec3(x + 1, y + 1, z),//Position 
								glm::vec2(0.0f, 0.0f),//TexCoords
								glm::vec3(0.0f, 0.0f, 0.0f),//Normal
							});
							
							vertices.push_back({
								glm::vec3(x + 1, y + 1, z + 1),//Position 
								glm::vec2(0.0f, 1.0f),//TexCoords
								glm::vec3(0.0f, 0.0f, 0.0f),//Normal
							});

							vertices.push_back({
								glm::vec3(x + 1, y, z + 1),//Position 
								glm::vec2(1.0f, 1.0f),//TexCoords
								glm::vec3(0.0f, 0.0f, 0.0f),//Normal
							});

							vertices.push_back({
								glm::vec3(x + 1, y, z),//Position 
								glm::vec2(1.0f, 0.0f),//TexCoords
								glm::vec3(0.0f, 0.0f, 0.0f),//Normal
							});

							unsigned int triangleone[] = { addindexindices, addindexindices + 1, addindexindices + 2};
							unsigned int triangletwo[] = { addindexindices, addindexindices + 3, addindexindices + 2};
							mesh_indices.insert(mesh_indices.end(), triangleone, triangleone + 3);
							mesh_indices.insert(mesh_indices.end(), triangletwo, triangletwo + 3);
							addindexindices += 6;
						}
					}
					//LEFT
					if(x - 1 >= 0){//check if out of bounds
						if(chunkBlocks[(x - 1) * 16 + y * 256 + z] == MC_AIR){//x - 1
							//4 vertices
							vertices.push_back({
								glm::vec3(x - 1, y + 1, z),//Position 
								glm::vec2(0.0f, 0.0f),//TexCoords
								glm::vec3(0.0f, 0.0f, 0.0f),//Normal
							});
							
							vertices.push_back({
								glm::vec3(x - 1, y + 1, z + 1),//Position 
								glm::vec2(0.0f, 1.0f),//TexCoords
								glm::vec3(0.0f, 0.0f, 0.0f),//Normal
							});

							vertices.push_back({
								glm::vec3(x - 1, y, z + 1),//Position 
								glm::vec2(1.0f, 1.0f),//TexCoords
								glm::vec3(0.0f, 0.0f, 0.0f),//Normal
							});

							vertices.push_back({
								glm::vec3(x - 1, y, z),//Position 
								glm::vec2(1.0f, 0.0f),//TexCoords
								glm::vec3(0.0f, 0.0f, 0.0f),//Normal
							});

							unsigned int triangleone[] = { addindexindices, addindexindices + 1, addindexindices + 2};
							unsigned int triangletwo[] = { addindexindices, addindexindices + 3, addindexindices + 2};
							mesh_indices.insert(mesh_indices.end(), triangleone, triangleone + 3);
							mesh_indices.insert(mesh_indices.end(), triangletwo, triangletwo + 3);
							addindexindices += 6;
						}
					}
					//BACK
					if(z + 1 < 16){//check if out of bounds
						if(chunkBlocks[x * 16 + y * 256 + z + 1] == MC_AIR){//z + 1
							//4 vertices
							vertices.push_back({
								glm::vec3(x, y, z + 1),//Position 
								glm::vec2(0.0f, 0.0f),//TexCoords
								glm::vec3(0.0f, 0.0f, 0.0f),//Normal
							});
							
							vertices.push_back({
								glm::vec3(x, y + 1, z + 1),//Position 
								glm::vec2(0.0f, 1.0f),//TexCoords
								glm::vec3(0.0f, 0.0f, 0.0f),//Normal
							});

							vertices.push_back({
								glm::vec3(x + 1, y + 1, z + 1),//Position 
								glm::vec2(1.0f, 1.0f),//TexCoords
								glm::vec3(0.0f, 0.0f, 0.0f),//Normal
							});

							vertices.push_back({
								glm::vec3(x + 1, y, z + 1),//Position 
								glm::vec2(1.0f, 0.0f),//TexCoords
								glm::vec3(0.0f, 0.0f, 0.0f),//Normal
							});

							unsigned int triangleone[] = { addindexindices, addindexindices + 1, addindexindices + 2};
							unsigned int triangletwo[] = { addindexindices, addindexindices + 3, addindexindices + 2};
							mesh_indices.insert(mesh_indices.end(), triangleone, triangleone + 3);
							mesh_indices.insert(mesh_indices.end(), triangletwo, triangletwo + 3);
							addindexindices += 6;
						}
					}
					//FRONT
					if(z - 1 >= 0){//check if out of bounds
						if(chunkBlocks[x * 16 + y * 256 + z - 1] == MC_AIR){//z - 1
							//4 vertices
							vertices.push_back({
								glm::vec3(x, y, z - 1),//Position 
								glm::vec2(0.0f, 0.0f),//TexCoords
								glm::vec3(0.0f, 0.0f, 0.0f),//Normal
							});
							
							vertices.push_back({
								glm::vec3(x, y + 1, z - 1),//Position 
								glm::vec2(0.0f, 1.0f),//TexCoords
								glm::vec3(0.0f, 0.0f, 0.0f),//Normal
							});

							vertices.push_back({
								glm::vec3(x + 1, y + 1, z - 1),//Position 
								glm::vec2(1.0f, 1.0f),//TexCoords
								glm::vec3(0.0f, 0.0f, 0.0f),//Normal
							});

							vertices.push_back({
								glm::vec3(x + 1, y, z - 1),//Position 
								glm::vec2(1.0f, 0.0f),//TexCoords
								glm::vec3(0.0f, 0.0f, 0.0f),//Normal
							});

							unsigned int triangleone[] = { addindexindices, addindexindices + 1, addindexindices + 2};
							unsigned int triangletwo[] = { addindexindices, addindexindices + 3, addindexindices + 2};
							mesh_indices.insert(mesh_indices.end(), triangleone, triangleone + 3);
							mesh_indices.insert(mesh_indices.end(), triangletwo, triangletwo + 3);
							addindexindices += 6;
						}
					}
				}
			}
		}
	}
}