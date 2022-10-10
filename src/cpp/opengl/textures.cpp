#include "textures.hpp"
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>
#include "fileslist.hpp"

//TEXTURE CLASS
Texture::Texture(std::string filepath){
	this->textureid = this->generateAndBindTexture2D();
	unsigned char * imgdata = this->loadImgData(filepath, false);
	this->setDefaultTextureProperties();
	this->setTextureData(imgdata);
}

void Texture::bind(){
	glBindTexture(GL_TEXTURE_2D, this->textureid);
}

unsigned int Texture::generateAndBindTexture2D(){
	//generate texture
	unsigned int texture;
	glEnable(GL_TEXTURE_2D);
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	return texture;
}

unsigned char * Texture::loadImgData(std::string filepath, bool is_stbi_alpha){
	stbi_set_flip_vertically_on_load(true);
	unsigned char *data;
	if(is_stbi_alpha){
		data = stbi_load(filepath.c_str(), &this->width, &this->height, &this->nrChannels, STBI_rgb_alpha);//use STBI_rgb_alpha for images with alpha, shown by strange colors
	} else {
		data = stbi_load(filepath.c_str(), &this->width, &this->height, &this->nrChannels, STBI_rgb);
	}

	if(!data){
		std::cout << "Failed to load Image" << std::endl;
	}

	return data;
}

void Texture::setDefaultTextureProperties(){
	// TEXTURE PROPERTIES
	// wrap
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	
	// bordercolor
	float borderColor[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, borderColor);
	
	// filtering
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
}

void Texture::setTextureData(unsigned char * data){
	if (nrChannels == 3) {
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, this->width, this->height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
	}
	else if (nrChannels == 4) {
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, this->width, this->height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
	}
	glGenerateMipmap(GL_TEXTURE_2D);
	stbi_image_free(data);
}
