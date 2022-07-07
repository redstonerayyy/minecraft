#include "meshtransform.h"
#include <iostream>

#define PI 3.14159265


//rotation not really working
void RotateVertices(std::vector<Vertex> &vertices, glm::mat4 matrix){
	for (int i = 0; i < vertices.size(); i++) {
		std::cout << vertices[i].Position.x << ":" << vertices[i].Position.y << ":" << vertices[i].Position.z << std::endl;
		glm::vec4 modified = matrix * glm::vec4(vertices[i].Position, 1.0f);
		std::cout << modified[0] << ":" << modified[1] << ":" << modified[2] << std::endl;
		vertices[i].Position = glm::vec3(modified[0], modified[1], modified[1]);
	}
};

glm::mat4 RotationMatrixZ(double angle){
	std::cout << "Radians" << glm::radians((float)angle) << std::endl;
	glm::mat4 rotationMatrix = glm::rotate(glm::mat4(1.0f), glm::radians((float)angle), glm::vec3(1.0f, 0.0f, 0.0f));
	// angle = angle * PI / 180; //convert to radians
	// glm::mat4 rotationMatrix = {
	// 	{ std::cos(angle), -std::sin(angle), 0 , 0 },
	// 	{ std::sin(angle), std::cos(angle), 0, 0 },
	// 	{ 0, 0, 1, 0 },
	// 	{ 0, 0, 0, 1 }, 
	// };
	return rotationMatrix;
};

glm::mat4 RotateVerticesQuaternion(glm::vec4 rotation){
	float normalization = sqrt(rotation.w * 2 + rotation.x * 2 + rotation.y * 2 + rotation.z * 2);
	rotation.w /= normalization;
	rotation.x /= normalization;
	rotation.y /= normalization;
	rotation.z /= normalization;
	glm::quat quaternion = glm::quat(rotation.w, rotation.x, rotation.y, rotation.z);
	glm::mat4 rotationmatrix = glm::toMat4(quaternion);
	return rotationmatrix;
}