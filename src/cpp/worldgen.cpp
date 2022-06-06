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
			vert.TexCoords = glm::vec2(1.0f, 1.0f);
			vert.Normal = glm::vec3(0.0f, 0.0f, 0.0f);
			vertices.push_back(vert);
			// std::cout << vertices.size() << "." << vert.Position.x << ":" << vert.Position.y << ":" << vert.Position.z << std::endl;
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
};

//void blockWorld(std::vector<Vertex> &vertices, std::vector<unsigned int> &mesh_indices) {
//
//	const siv::PerlinNoise::seed_type seed = 123456u;
//
//	const siv::PerlinNoise perlin{ seed };
//
//	const int size = 16;
//	std::array<double, size * size> heightmap;
//
//	for (int z = 0; z < size; z++)
//	{
//		for (int x = 0; x < size; x++)
//		{
//			const double noise = perlin.octave2D_01((x * 0.01), (z * 0.01), 4);
//			heightmap[z + x] = noise;
//		}
//	}
//
//	//chunks are 16 by 16 by 256
//	std::array<unsigned int, 16 * 16 * 256> chunk;
//
//
//	for (unsigned int z = 0; z < size - 1; z++)
//	{
//		for (unsigned int x = 0; x < size - 1; x++)
//		{
//			unsigned int triangleone[] = { z * size + x, (z + 1) * size + x, (z + 1) * size + x + 1 };
//			unsigned int triangletwo[] = { z * size + x, z * size + x + 1, (z + 1) * size + x + 1 };
//			mesh_indices.insert(mesh_indices.end(), triangleone, triangleone + 3);
//			mesh_indices.insert(mesh_indices.end(), triangletwo, triangletwo + 3);
//			
//			//calculate normals
//			glm::vec3 vec1_1 = vertices[triangleone[1]].Position - vertices[triangleone[0]].Position;
//			glm::vec3 vec2_1 = vertices[triangleone[2]].Position - vertices[triangleone[0]].Position;
//			glm::vec3 normal1 = glm::normalize(glm::cross(vec1_1, vec2_1));
//
//			vertices[triangleone[0]].Normal = normal1;
//			vertices[triangleone[1]].Normal = normal1;
//			vertices[triangleone[2]].Normal = normal1;
//
//			glm::vec3 vec1_2 = vertices[triangletwo[1]].Position - vertices[triangletwo[0]].Position;
//			glm::vec3 vec2_2 = vertices[triangletwo[2]].Position - vertices[triangletwo[0]].Position;
//			glm::vec3 normal2 = glm::normalize(glm::cross(vec1_2, vec2_2));
//
//			vertices[triangletwo[0]].Normal = normal2;
//			vertices[triangletwo[1]].Normal = normal2;
//			vertices[triangletwo[2]].Normal = normal2;
//		}
//	}
//};
