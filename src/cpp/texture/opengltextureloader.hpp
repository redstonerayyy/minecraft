#pragma once

#include <string>
#include <unordered_map>
#include <vector>
#include <glad/glad.h>

namespace OpenGL {

struct Texture {
    GLuint textureid;
    std::string path;
    std::string name;
};

class TextureLoader {
public:
    // default contructor
    TextureLoader(){};
    TextureLoader(std::vector<std::string> directories, std::vector<std::string> paths);
    ~TextureLoader();
private:
    std::vector<std::string> paths;
    std::unordered_map<std::string, Texture> textures;
    void LoadTextureFromFile(std::string path);
    void GetPathsFromDirectory(std::string directory);
};

}
