#ifndef TEXTURES_H
#define TEXTURES_H

#include <glad/gl.h>
#include <iostream>

class Texture {
public:
	unsigned int texture;
	Texture(unsigned int texturenumber, const char *filePath);
	void loadImg(const char *filePath);
	void Texture::BindTexture();
	void setActiveTexture(unsigned int textureNumber);
	void setImageFlip(bool isFlipped);
};

#endif