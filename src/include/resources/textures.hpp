#ifndef TEXTURES_H
#define TEXTURES_H

#include <glad/gl.h>
#include <iostream>


class Texture {
public:
	int width;
	int height;
	int nrChannels;
	unsigned int textureid;
	Texture(std::string filepath);
	void bind();
	unsigned int generateAndBindTexture2D();
	unsigned char * loadImgData(std::string filepath, bool is_stbi_alpha);
	void setDefaultTextureProperties();
	void setTextureData(unsigned char * data);
};

#endif