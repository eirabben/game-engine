#include "Game.hpp"

#include <iostream>
#include <string>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <selene.h>
#include <memory>

Game::Game() {
    
}

Game::~Game() {
    
}

void Game::run() {
    init();
    
    prepare();
    
    double previousTicks = SDL_GetTicks();
    
    while (!m_quit) {
        // Begin timer frame
//        m_timer.beginFrame();
        
        // Calculate delta time
        currentTicks = SDL_GetTicks();
        deltaTime = currentTicks - previousTicks;
        previousTicks = currentTicks;
        
        handleInput(deltaTime);
        update(deltaTime);
        draw();
        
//        m_timer.endFrame();
        
//        static int frames = 0;
//        if (frames > 100) {
//            frames = 0;
//            std::cout << m_timer.getFps() << "\n";
//        }
//        frames++;
    }
    
    destroy();
}

void Game::init() {
    // Load Lua config
    sel::State configState;
    configState.Load("res/config.lua");
    
    // Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cout << "Could not initialize SDL: " << SDL_GetError() << "\n";
    }
    
    // Tell OpenGL to create a core context
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    
    // TODO: add options to window creation
    m_window.create(configState["screenWidth"], configState["screenHeight"]);
    
    SDL_SetRelativeMouseMode(SDL_TRUE);
    
    SDL_GL_SetSwapInterval(1);
    
    const GLubyte* renderer = glGetString(GL_RENDERER);
    const GLubyte* version = glGetString(GL_VERSION);
    std::cout << "Renderer: " << renderer << "\n";
    std::cout << "OpenGL version supported: " << version << "\n";
    
    glEnable(GL_DEPTH_TEST); // enable depth-testing
    //    glDepthFunc(GL_LESS); // depth-testing interprets a smaller value as "closer"
    
    m_lightingShader.compileShaders("res/Shaders/lighting.vert", "res/Shaders/lighting.frag");
    m_lampShader.compileShaders("res/Shaders/lamp.vert", "res/Shaders/lamp.frag");
    
    double maxFps = configState["maxFps"];
    m_timer.init(static_cast<float>(maxFps));
}

void Game::destroy() {
    m_window.destroy();
    
    SDL_Quit();
}

void Game::prepare() {
    m_cube.init();
    
    m_dirLight.init();
    DirLight dirLight;
    dirLight.direction = glm::vec3(-0.2f, -1.0f, -0.3f);
    dirLight.ambient = glm::vec3(0.05f);
    dirLight.diffuse = glm::vec3(0.4f);
    dirLight.specular = glm::vec3(0.5f);
    m_dirLight.setLight(dirLight);
    
    m_pointLights.push_back(m_pointLight1);
    m_pointLights.push_back(m_pointLight2);
    m_pointLights.push_back(m_pointLight3);
    m_pointLights.push_back(m_pointLight4);
    
    for (int i = 0; i < m_pointLights.size(); i++) {
        m_pointLights[i].init();
        m_pointLights[i].setPosition(pointLightPositions[i]);
        PointLight pointLight = m_pointLights[i].getLight();
        pointLight.position = pointLightPositions[i];
        pointLight.ambient = glm::vec3(0.05f);
        pointLight.diffuse = glm::vec3(0.8f);
        pointLight.specular = glm::vec3(1.0f);
        pointLight.constant = 1.0f;
        pointLight.linear = 0.09f;
        pointLight.quadratic = 0.032f;
        m_pointLights[i].setLight(pointLight);
    }
    
    for (int i = 0; i < 4; i++) {
    }
}

void Game::update(float deltaTime) {

}

void Game::draw() {
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    // Create camera transformations
    glm::mat4 view = m_camera.getViewMatrix();
    glm::mat4 projection = glm::perspective(glm::radians(m_camera.getZoom()), (float)m_window.getWidth() / (float)m_window.getHeight(), 0.1f, 100.0f);
    
    // Use the lighting shader
    m_lightingShader.use();
    
    GLuint viewPosLoc = m_lightingShader.getUniformLocation("viewPos");
    glUniform3fv(viewPosLoc, 1, glm::value_ptr(m_camera.getPosition()));
    
    glUniform3fv(m_lightingShader.getUniformLocation("dirLight.direction"), 1, glm::value_ptr(m_dirLight.getLight().direction));
    glUniform3fv(m_lightingShader.getUniformLocation("dirLight.ambient"), 1, glm::value_ptr(m_dirLight.getLight().ambient));
    glUniform3fv(m_lightingShader.getUniformLocation("dirLight.diffuse"), 1, glm::value_ptr(m_dirLight.getLight().diffuse));
    glUniform3fv(m_lightingShader.getUniformLocation("dirLight.specular"), 1, glm::value_ptr(m_dirLight.getLight().specular));
    
    for (int i = 0; i < m_pointLights.size(); i++) {
        glUniform3fv(m_lightingShader.getUniformLocation("pointLights[" + std::to_string(i) + "].position"), 1, glm::value_ptr(m_pointLights[i].getLight().position));
        glUniform3fv(m_lightingShader.getUniformLocation("pointLights[" + std::to_string(i) + "].ambient"), 1, glm::value_ptr(m_pointLights[i].getLight().ambient));
        glUniform3fv(m_lightingShader.getUniformLocation("pointLights[" + std::to_string(i) + "].diffuse"), 1, glm::value_ptr(m_pointLights[i].getLight().diffuse));
        glUniform3fv(m_lightingShader.getUniformLocation("pointLights[" + std::to_string(i) + "].specular"), 1, glm::value_ptr(m_pointLights[i].getLight().specular));
        glUniform1f(m_lightingShader.getUniformLocation("pointLights[" + std::to_string(i) + "].constant"), m_pointLights[i].getLight().constant);
        glUniform1f(m_lightingShader.getUniformLocation("pointLights[" + std::to_string(i) + "].linear"), m_pointLights[i].getLight().linear);
        glUniform1f(m_lightingShader.getUniformLocation("pointLights[" + std::to_string(i) + "].quadratic"), m_pointLights[i].getLight().quadratic);
    }
    
    // Get uniform locations
    GLuint viewLoc = m_lightingShader.getUniformLocation("view");
    GLuint projectionLoc = m_lightingShader.getUniformLocation("projection");
    // Pass matrices to the shader
    glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
    glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projection));
    
    // Draw the cube
    m_cube.draw(m_lightingShader);
    
    // Use the lamp shader
    m_lampShader.use();
    
    // Get locations
    viewLoc = m_lampShader.getUniformLocation("view");
    projectionLoc = m_lampShader.getUniformLocation("projection");
    // Pass matrices to the shader
    glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
    glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projection));
    
    
    glUseProgram(0);
    
    m_window.swapWindow();
}

void Game::handleInput(float deltaTime) {
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



