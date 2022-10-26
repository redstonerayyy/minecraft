#pragma once

#include <glad/gl.h>
#include <iostream>


class Texture {
public:
	int width;
	int height;
	int nrChannels;
	unsigned int textureid;

    Texture(std::string filepath);
    // bind texture
    void bind();
    // functions to generate texture
	unsigned int generateAndBindTexture2D();
	unsigned char * loadImgData(std::string filepath, bool is_stbi_alpha);
	void setDefaultTextureProperties();
	void setTextureData(unsigned char * data);
};
