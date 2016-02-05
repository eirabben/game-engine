#include "Game.hpp"

#include <iostream>
#include <string>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <selene.h>
#include <memory>
#include "TextureLoader.hpp"

#include "Processors/PLightRenderer.hpp"
#include "Processors/PLampRenderer.hpp"
#include "Processors/PDirLight.hpp"
#include "Processors/PPointLight.hpp"


void Scene::init() {
    m_lightingShader.compileShaders("res/Shaders/lighting.vert", "res/Shaders/lighting.frag");
    m_lampShader.compileShaders("res/Shaders/lamp.vert", "res/Shaders/lamp.frag");

    // Create the cubes
    for (GLuint i = 0; i < 10; i++)
    {
        auto& cube = mgr.createEntity();

        mgr.addComponent<CPosition>(cube.id, {cubePositions[i]});

        mgr.addComponent<CMesh>(cube.id, {});
        auto& mesh = mgr.getComponent<CMesh>(cube.id);
        mesh.init();
        mesh.modelMatrix = glm::translate(mesh.modelMatrix, cubePositions[i]);
        GLfloat angle = 20.0f * i;
        mesh.modelMatrix = glm::rotate(mesh.modelMatrix, angle, glm::vec3(1.0f, 0.3f, 0.5f));

        CMaterial material;
        material.diffuseMap = TextureLoader::loadTexture("res/Textures/container2.png");
        material.specularMap = TextureLoader::loadTexture("res/Textures/container2_specular.png");
        material.shininess = 32.0f;
        mgr.addComponent<CMaterial>(cube.id, material);
    }

    // Create the directional light
    auto& dirLight = mgr.createEntity();

    CDirLight dLight;
    dLight.direction = glm::vec3(-0.2f, -1.0f, -0.3f);
    dLight.ambient = glm::vec3(0.05f);
    dLight.diffuse = glm::vec3(0.4f);
    dLight.specular = glm::vec3(0.5f);
    mgr.addComponent<CDirLight>(dirLight.id, dLight);

    // Create point lights
    for (auto i = 0; i < 4; i++) {
        auto& pointLight = mgr.createEntity();

        CPointLight pLight;
        pLight.position = pointLightPositions[i];
        pLight.ambient = glm::vec3(0.05f);
        pLight.diffuse = glm::vec3(0.8f);
        pLight.specular = glm::vec3(1.0f);
        pLight.constant = 1.0f;
        pLight.linear = 0.09f;
        pLight.quadratic = 0.032f;
        pLight.id = i;
        mgr.addComponent<CPointLight>(pointLight.id, pLight);

        mgr.addComponent<CMesh>(pointLight.id, {});
        auto& mesh = mgr.getComponent<CMesh>(pointLight.id);
        mesh.init();
        mesh.modelMatrix = glm::translate(mesh.modelMatrix, pointLightPositions[i]);
        mesh.modelMatrix = glm::scale(mesh.modelMatrix, glm::vec3(0.2f));
    }

}

void Scene::destroy() {

}

void Scene::update(float deltaTime) {
    handleInput(deltaTime);
}

void Scene::draw() {
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    // Use the lighting shader
    m_lightingShader.use();
    
    glUniform3fv(m_lightingShader.getUniformLocation("viewPos"), 1, glm::value_ptr(m_camera.getPosition()));

    PDirLight dlp;
    dlp.update(mgr, m_lightingShader);

    PPointLight plp;
    plp.update(mgr, m_lightingShader);
    
    // Create camera transformations
    glm::mat4 view = m_camera.getViewMatrix();
    glm::mat4 projection = glm::perspective(glm::radians(m_camera.getZoom()), (float)m_game->m_window.getWidth() / (float)m_game->m_window.getHeight(), 0.1f, 100.0f);

    // Pass view matrix to shader
    GLuint viewLoc = m_lightingShader.getUniformLocation("view");
    glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));

    // Pass projection matrix to shader
    GLuint projectionLoc = m_lightingShader.getUniformLocation("projection");
    glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projection));

    PLightRenderer lightRenderer;
    lightRenderer.update(mgr, m_lightingShader);

    // Use the lamp shader
    m_lampShader.use();
    
    // Pass view matrix to shader
    viewLoc = m_lampShader.getUniformLocation("view");
    glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));

    // Pass projection matrix to shader
    projectionLoc = m_lampShader.getUniformLocation("projection");
    glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projection));

    PLampRenderer lampRenderer;
    lampRenderer.update(mgr, m_lampShader);
    
    glUseProgram(0);
    
}

void Scene::handleInput(float deltaTime) {
    m_inputHandler.update();
    
    SDL_Event e;
    
    while (SDL_PollEvent(&e)) {
        
        switch (e.type) {
            case SDL_QUIT:
                m_quit = true;
                break;
            case SDL_KEYDOWN:
                m_inputHandler.keyPressed(e.key.keysym.sym);
                std::cout << "key pressed\n";
                break;
            case SDL_KEYUP:
                m_inputHandler.keyReleased(e.key.keysym.sym);
                break;
            case SDL_MOUSEMOTION:
                m_inputHandler.mouseMoved(e.motion.x, e.motion.y, e.motion.xrel, e.motion.yrel);
                m_camera.processMouseMovement(e.motion.xrel, -e.motion.yrel);
                std::cout << "Mouse moved\n";
                break;
            case SDL_MOUSEBUTTONDOWN:
                m_inputHandler.keyPressed(e.button.button);
                break;
            case SDL_MOUSEBUTTONUP:
                m_inputHandler.keyReleased(e.button.button);
                break;
            case SDL_MOUSEWHEEL:
                m_camera.processMouseScroll(e.wheel.y);
                break;
            default:
                break;
        }
    }
    
//    Command* c = m_inputHandler.handleInput();
//    if (c != nullptr) {
//        c->execute(m_camera);
//    }
    
    if (m_inputHandler.isKeyDown(SDLK_w)) {
        m_camera.processKeyboard(CameraMovement::FORWARD, deltaTime);
    }
    if (m_inputHandler.isKeyDown(SDLK_a)) {
        m_camera.processKeyboard(CameraMovement::LEFT, deltaTime);
    }
    if (m_inputHandler.isKeyDown(SDLK_s)) {
        m_camera.processKeyboard(CameraMovement::BACKWARD, deltaTime);
    }
    if (m_inputHandler.isKeyDown(SDLK_d)) {
        m_camera.processKeyboard(CameraMovement::RIGHT, deltaTime);
    }
    if (m_inputHandler.isKeyDown(SDLK_ESCAPE)) {
        m_quit = true;
    }
}

