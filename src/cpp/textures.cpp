#include "textures.h"
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>
#define UTILS_H
#include "utils.h"

Texture::Texture(unsigned int texturenumber, const char * filePath){
	this->setImageFlip(true);
	glGenTextures(1, &this->texture);
	this->setActiveTexture(texturenumber);
	this->loadImg(filePath);
}

void Texture::setImageFlip(bool isFlipped){
	stbi_set_flip_vertically_on_load(isFlipped);
}

void Texture::setActiveTexture(unsigned int textureNumber){
	glActiveTexture(GL_TEXTURE0 + textureNumber);
	glBindTexture(GL_TEXTURE_2D, this->texture);
}

void Texture::loadImg(const char* filePath){
	unsigned int imgColorFormat = GL_RGB;
	if(splitString(std::string(filePath), ".")[1] == "png"){
		imgColorFormat = GL_RGBA;
	}
	int width, height, nrChannels;
	unsigned char *data = stbi_load(filePath, &width, &height, &nrChannels, 0);
	if (data){
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, imgColorFormat, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	} else{
		std::cout << "Failed to load texture" << std::endl;
	}
	stbi_image_free(data);
}
