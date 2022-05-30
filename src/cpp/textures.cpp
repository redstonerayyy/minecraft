#include "textures.h"
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>
#include "utils.h"

Texture::Texture(unsigned int texturenumber, const char *filePath)
{
	this->setImageFlip(true);
	glGenTextures(1, &this->texture);
	this->loadImg(filePath);
}

void Texture::setImageFlip(bool isFlipped)
{
	stbi_set_flip_vertically_on_load(isFlipped);
}

void Texture::setActiveTexture(unsigned int textureNumber)
{
	glActiveTexture(GL_TEXTURE0 + textureNumber);
}

void Texture::BindTexture()
{
	glBindTexture(GL_TEXTURE_2D, this->texture);
}

void Texture::loadImg(const char *filePath)
{
	this->BindTexture();
	
	// TEXTURE PROPERTIES
	// wrap
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
	// bordercolor
	float borderColor[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, borderColor);
	// filtering
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST_MIPMAP_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_NEAREST);

	int width, height, nrChannels;
	unsigned char *data = stbi_load(filePath, &width, &height, &nrChannels, STBI_rgb);//use STBI_rgb_alpha for images with alpha, shown by strange colors
	if (data)
	{
		if (nrChannels == 3) {
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		}
		else if (nrChannels == 4) {
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
		}
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cout << "Failed to load Image" << std::endl;
	}
	stbi_image_free(data);
}
