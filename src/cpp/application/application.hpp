#pragma once

// define namespace for this header
#include "openglshaderloader.hpp"
#include "opengltextureloader.hpp"
namespace gl = OpenGL;

class Application {
public:
    Application(int windowwidth, int windowheight, int runmode);
    ~Application();
    gl::ShaderLoader shaderloader;
    gl::TextureLoader textureloader;
    static const int test = 1;
// game
// renderer
// resources
// window
// eventsystem
private:
    void PreRunChecks();
    void PrepareRun();
    void Window();
    void LoadShaders();
    void LoadTextures();
};

