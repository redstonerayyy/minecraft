#include "application.hpp"
// define namespace for this headers
#include "openglshaderloader.hpp"
#include "opengltextureloader.hpp"
#include "windowglfwopengl.hpp"
namespace gl = OpenGL;

Application::Application(int windowwidth, int windowheight, int runmode){
    this->Window();
    // shaders. textures need an active opengl context
    this->LoadShaders();
    this->LoadTextures();
}

void Application::LoadShaders(){
    this->shaderloader = gl::ShaderLoader({"run/shaders"}, {});
}

void Application::LoadTextures(){
    this->textureloader = gl::TextureLoader({"run/textures"}, {});
}

void Application::Window(){
    gl::WindowGLFWOpenGL* window = new gl::WindowGLFWOpenGL(800, 600);
}
