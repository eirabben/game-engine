#pragma once

#include "Shader.hpp"

#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>
#include <OpenGL/gl3.h>

class Game {
public:
    Game();
    ~Game();
    
    void run();
    
    void prepare();
    
    void init();
    void destroy();
    
    void update();
    void draw();
    
private:
    SDL_Window* m_window = nullptr;
    SDL_GLContext m_context;
    
    Shader m_shader;
    
    GLuint m_vao;
    GLuint m_vbo;
    GLuint m_ebo;
    
    const int m_windowWidth = 800;
    const int m_windowHeight = 600;
    
};
