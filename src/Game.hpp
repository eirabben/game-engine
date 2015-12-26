#pragma once

#include "Shader.hpp"
#include "Window.hpp"

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
    Window m_window;
    Shader m_shader;
    
    GLuint m_vao;
    GLuint m_vbo;
};
