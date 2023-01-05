#include "opengltextureloader.hpp"
#include "utils.hpp"

#include <string>
#include <vector>
#include <fstream>
#include <filesystem>
#include <algorithm>
#include <iostream>
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>
#include <glad/glad.h>

namespace OpenGL {

TextureLoader::TextureLoader(std::vector<std::string> directories, std::vector<std::string> paths){
    glEnable(GL_TEXTURE_2D);
    this->paths = paths;
    // get all filepaths from each directory
    for( std::string directory : directories ){
        this->GetPathsFromDirectory(directory);        
    };
    // load all shaders
    for( std::string path : this->paths ){
        this->LoadTextureFromFile(path);
    };
}

TextureLoader::~TextureLoader(){
    // free all memory
    std::vector<GLuint> textureids;
    for( const auto & [ key, value ] : this->textures ){
        textureids.emplace_back(value.textureid);
    }
    glDeleteTextures(textureids.size(), &textureids[0]);
}

void TextureLoader::LoadTextureFromFile(std::string path){
    // try to open file
    std::ifstream file(path);
    // abort and return on error
    if( ! file.is_open() ) return;
    // read file
    std::string content( (std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>() );
    // create texture
    // find out which type of image file and name
    std::string name = std::filesystem::path(path).filename();
    std::vector<std::string> nameparts = Utils::SplitString(name, ".");
    std::string imgfiletype = nameparts.at(nameparts.size() - 1);
    // load img data
    stbi_set_flip_vertically_on_load(true); // load normally and not flipped
	unsigned char *data;
    int width, height, nrChannels;
	if(imgfiletype == "png"){
		data = stbi_load(path.c_str(), &width, &height, &nrChannels, STBI_rgb_alpha);//use STBI_rgb_alpha for images with alpha, shown by strange colors
	}
    if(imgfiletype == "jpg"){
        data = stbi_load(path.c_str(), &width, &height, &nrChannels, STBI_rgb);
    }

	if(!data){
		std::cout << "Failed to load Image" << std::endl;
	}
    // create texture
    GLuint textureid;
	glGenTextures(1, &textureid);
	glBindTexture(GL_TEXTURE_2D, textureid);
    // set default parameters
    // wrap
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	// bordercolor
	float borderColor[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, borderColor);
	// filtering
    // use nearest to prevent blurring when rendering pixel blocks
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    // set img data for the texture
    // differentiate between channel count, either with or wihtout alpha
    if (nrChannels == 3){ // without alpha
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
	}
	else if (nrChannels == 4){ // with alpha
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
	}
    // generate mipmap
	glGenerateMipmap(GL_TEXTURE_2D);
    // free data
	stbi_image_free(data);
    // add into hashmap
    this->textures[name] = Texture{textureid, path, name};
}

void TextureLoader::GetPathsFromDirectory(std::string directory){
    // for each file in the directory add it to the global paths list if the path is not present yet
    for( const auto & entry : std::filesystem::directory_iterator(directory) ){
        std::string path = entry.path();
        if( ! std::any_of( this->paths.begin(), this->paths.end(), [path](std::string existingpath){ return existingpath == path;} ) ){
            this->paths.emplace_back(path);
        }
    }
}

}
