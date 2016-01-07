#pragma once

#include "Camera.hpp"
#include "Shader.hpp"
#include "Window.hpp"

#include <OpenGL/gl3.h>

class Game {
public:
    Game();
    ~Game();
    
    void run();
    
    // Temporary
    void prepare();
    
    void init();
    void destroy();
    
    void update();
    void draw();
    
    void handleInput(float deltaTime);
    
private:
    Window m_window;
    Shader m_shader;
    Camera m_camera = {glm::vec3(0.0f, 0.0f, 3.0f)};
    
    GLuint m_vao;
    GLuint m_vbo;
    GLuint m_ebo;
    
    GLuint m_texture1;
    GLuint m_texture2;
    
    float m_deltaTime = 0.0f;
    float m_lastFrame = 0.0f;
    
    bool m_quit = false;
};
