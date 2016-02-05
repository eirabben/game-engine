#include "Game.hpp"

#include <iostream>
#include <string>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <selene.h>
#include <memory>
#include "TextureLoader.hpp"
#include "Processors/PDirLight.hpp"
#include "Processors/PMeshRenderer.hpp"
#include "Processors/PPointLight.hpp"

void Scene::init() {
    m_lightingShader.compileShaders("res/Shaders/lighting.vert", "res/Shaders/lighting.frag");
    m_lampShader.compileShaders("res/Shaders/lamp.vert", "res/Shaders/lamp.frag");

    // Create the cube
    auto& cube = mgr.createEntity();
    cube.name = "Cube";

    CPosition cubePos;
    cubePos.position = {0.0f, 0.0f, 0.0f};
    mgr.addComponent<CPosition>(cube.id, cubePos);

    CMesh cubeMesh;
    cubeMesh.init();
    cubeMesh.modelMatrix = glm::translate(cubeMesh.modelMatrix, cubePos.position);
    std::cout << &cubeMesh.modelMatrix << "\n";
    mgr.addComponent<CMesh>(cube.id, cubeMesh);

    CMaterial material;
    material.diffuseMap = TextureLoader::loadTexture("res/Textures/container2.png");
    material.specularMap = TextureLoader::loadTexture("res/Textures/container2_specular.png");
    material.shininess = 32.0f;
    mgr.addComponent<CMaterial>(cube.id, material);

    // Create the directional light
    auto& dirLight = mgr.createEntity();

    CDirLight dLight;
    dLight.direction = glm::vec3(-0.2f, -1.0f, -0.3f);
    dLight.ambient = glm::vec3(0.05f);
    dLight.diffuse = glm::vec3(0.4f);
    dLight.specular = glm::vec3(0.5f);
    mgr.addComponent<CDirLight>(dirLight.id, dLight);

    auto& pointLight = mgr.createEntity();

    CPointLight pLight;
    pLight.position = glm::vec3(0.7f, 0.2f, 2.0f);
    pLight.ambient = glm::vec3(0.05f);
    pLight.diffuse = glm::vec3(0.8f);
    pLight.specular = glm::vec3(1.0f);
    pLight.constant = 1.0f;
    pLight.linear = 0.09f;
    pLight.quadratic = 0.032f;
    mgr.addComponent<CPointLight>(pointLight.id, pLight);
    
    /* m_pointLights.push_back(m_pointLight1); */
    /* m_pointLights.push_back(m_pointLight2); */
    /* m_pointLights.push_back(m_pointLight3); */
    /* m_pointLights.push_back(m_pointLight4); */
    
    /* for (int i = 0; i < m_pointLights.size(); i++) { */
    /*     m_pointLights[i].init(); */
    /*     m_pointLights[i].setPosition(pointLightPositions[i]); */
    /*     PointLight pointLight = m_pointLights[i].getLight(); */
    /*     pointLight.position = pointLightPositions[i]; */
    /*     pointLight.ambient = glm::vec3(0.05f); */
    /*     pointLight.diffuse = glm::vec3(0.8f); */
    /*     pointLight.specular = glm::vec3(1.0f); */
    /*     pointLight.constant = 1.0f; */
    /*     pointLight.linear = 0.09f; */
    /*     pointLight.quadratic = 0.032f; */
    /*     m_pointLights[i].setLight(pointLight); */
    /* } */
}

void Scene::destroy() {

}

void Scene::update(float deltaTime) {
    handleInput(deltaTime);
}

void Scene::draw() {
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    // Create camera transformations
    glm::mat4 view = m_camera.getViewMatrix();
    glm::mat4 projection = glm::perspective(glm::radians(m_camera.getZoom()), (float)m_game->m_window.getWidth() / (float)m_game->m_window.getHeight(), 0.1f, 100.0f);
    
    // Use the lighting shader
    m_lightingShader.use();
    
    GLuint viewPosLoc = m_lightingShader.getUniformLocation("viewPos");
    glUniform3fv(viewPosLoc, 1, glm::value_ptr(m_camera.getPosition()));

    PDirLight dlp;
    dlp.update(mgr, m_lightingShader);

    PPointLight plp;
    plp.update(mgr, m_lightingShader);
    
    // Get uniform locations
    GLuint viewLoc = m_lightingShader.getUniformLocation("view");
    GLuint projectionLoc = m_lightingShader.getUniformLocation("projection");
    // Pass matrices to the shader
    glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
    glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projection));

    PMeshRenderer mrp;
    mrp.update(mgr, m_lightingShader);
    
    // Use the lamp shader
    m_lampShader.use();
    
    // Get locations
    viewLoc = m_lampShader.getUniformLocation("view");
    projectionLoc = m_lampShader.getUniformLocation("projection");
    // Pass matrices to the shader
    glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
    glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projection));
    
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
                break;
            case SDL_KEYUP:
                m_inputHandler.keyReleased(e.key.keysym.sym);
                break;
            case SDL_MOUSEMOTION:
                m_inputHandler.mouseMoved(e.motion.x, e.motion.y, e.motion.xrel, e.motion.yrel);
                m_camera.processMouseMovement(e.motion.xrel, -e.motion.yrel);
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

