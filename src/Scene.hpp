#pragma once

#include "Camera.hpp"
#include "InputHandler.hpp"
#include "Shader.hpp"
#include "EcsSettings.hpp"

#include <OpenGL/gl3.h>
#include <glm/glm.hpp>
#include <vector>
#include "Texture.hpp"

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

    Shader m_lightingShader;
    Shader m_lampShader;
    Manager mgr;
    
    Camera m_camera = {glm::vec3(0.0f, 0.0f, 3.0f)};

    // Positions all containers
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

    // Positions of the point lights
    std::vector<glm::vec3> pointLightPositions = {
        glm::vec3( 0.7f,  0.2f,  2.0f),
        glm::vec3( 2.3f, -3.3f, -4.0f),
        glm::vec3(-4.0f,  2.0f, -12.0f),
        glm::vec3( 0.0f,  0.0f, -3.0f)
    };
};
