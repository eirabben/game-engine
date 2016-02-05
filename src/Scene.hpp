#pragma once

#include "Camera.hpp"
#include "InputHandler.hpp"
#include "Shader.hpp"
#include "EcsSettings.hpp"

#include <OpenGL/gl3.h>
#include <glm/glm.hpp>
#include <vector>

class Game;

class Scene {
public:
    void init();
    void destroy();
    
    void update(float deltaTime);
    void draw();
    
    void handleInput(float deltaTime);
    
    void setGame(Game* game) { m_game = game; }

    bool m_quit {false};
    
private:
    Game* m_game {nullptr};
    InputHandler m_inputHandler;
    Shader m_lightingShader;
    Shader m_lampShader;
    Manager mgr;
    
    Camera m_camera = {glm::vec3(0.0f, 0.0f, 3.0f)};
};
