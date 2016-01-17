#pragma once

#include "Camera.hpp"
#include "InputHandler.hpp"
#include "Shader.hpp"
#include "Window.hpp"
#include "Timer.hpp"
#include "Cube.hpp"
#include "Light.hpp"

#include <OpenGL/gl3.h>
#include <glm/glm.hpp>
#include <vector>

class Game {
public:
    Game();
    ~Game();
    
    void run();
    
    void init();
    void destroy();
    
    // Temporary
    void prepare();
    
    void update(float deltaTime);
    void draw();
    
    void handleInput(float deltaTime);
    
private:
    Window m_window;
    Timer m_timer;
    InputHandler m_inputHandler;
    
    Shader m_lightingShader;
    Shader m_lampShader;
    
    Camera m_camera = {glm::vec3(0.0f, 0.0f, 3.0f)};
    Cube m_cube = {glm::vec3(0.0f, 0.0f, 0.0f)};
    Light m_light = {glm::vec3(1.2f, 1.0f, 2.0f), glm::vec3(0.2f, 0.2f, 0.2f), glm::vec3(0.5f, 0.5f, 0.5f), glm::vec3(1.0f, 1.0f, 1.0f)};
    
    GLuint m_vao;
    GLuint m_vbo;
    
    int prevTicks = 0;
    int currentTicks = 0;
    float deltaTime = 0.0f;
    
    std::vector<glm::vec3> cubePositions = {
        glm::vec3( 0.0f,  0.0f,  0.0f),
        glm::vec3( 2.0f,  5.0f, -15.0f),
        glm::vec3(-1.5f, -2.2f, -2.5f),
        glm::vec3(-3.8f, -2.0f, -12.3f),
        glm::vec3( 2.4f, -0.4f, -3.5f),
        glm::vec3(-1.7f,  3.0f, -7.5f),
        glm::vec3( 1.3f, -2.0f, -2.5f),
        glm::vec3( 1.5f,  2.0f, -2.5f),
        glm::vec3( 1.5f,  0.2f, -1.5f),
        glm::vec3(-1.3f,  1.0f, -1.5f)
    };
    
    bool m_quit = false;
};
