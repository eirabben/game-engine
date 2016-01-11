#include "Game.hpp"

#define STB_IMAGE_IMPLEMENTATION // Required for stb_image.h
#include <stb_image.h>
#include <iostream>
#include <string>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

Game::Game() {
    
}

Game::~Game() {
    
}

void Game::run() {
    init();
    
    prepare();
    
    update();
    
    destroy();
}

void Game::prepare() {
    m_shader.compileShaders("res/Shaders/simple.vert", "res/Shaders/simple.frag");
    
//    GLfloat vertices[] = {
//        // Positions         // Colors
//        -0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f,  // Bottom right
//         0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,  // Bottom left
//         0.0f,  0.5f, 0.0f,  0.0f, 0.0f, 1.0f   // Top
//    };
//    
//    // Texture coordinates
//    GLfloat texCoords[] = {
//        0.0f, 0.0f,  // lower left
//        1.0f, 0.0f,  // lower right
//        0.5f, 1.0f   // top center
//    };
    
    GLfloat vertices[] = {
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
        0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
        0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
        
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
        0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
        0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
        -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        
        -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        
        0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
        0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
        0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
        0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f
    };
    
//    GLfloat vertices[] = {
//        // Positions          // Colors           // Texture Coords
//         0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,   // Top Right
//         0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,   // Bottom Right
//        -0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,   // Bottom Left
//        -0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f    // Top Left
//    };
    
//    GLuint indices[] = {
//        0, 1, 3,  // First triangle
//        1, 2, 3   // Second triangle
//    };
    
    // Set mipmap filtering options
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    
    glGenVertexArrays(1, &m_vao);
    glGenBuffers(1, &m_vbo);
//    glGenBuffers(1, &m_ebo);
    
    glBindVertexArray(m_vao);
    
    glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    
//    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ebo);
//    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
    
    // Position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)0);
    glEnableVertexAttribArray(0);
    
    // Color attribute
//    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
//    glEnableVertexAttribArray(1);
    
    // Texture attribute
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
    glEnableVertexAttribArray(1);
    
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    
    glBindVertexArray(0);
    
    // Load texture images
    
    // Texture 1
    glGenTextures(1, &m_texture1);
    glBindTexture(GL_TEXTURE_2D, m_texture1);
    
    // Set texture wrapping options
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    
    // Set texture filtering options
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    
    int width;
    int height;
    std::string filename = "res/Textures/container.jpg";
    unsigned char* imageData = stbi_load(filename.c_str(), &width, &height, 0, 3);
    
    // Check if image was loaded
    if (imageData == NULL) {
        std::cout << "Image data not found\n";
    }
    
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, imageData);
    glGenerateMipmap(GL_TEXTURE_2D);
    stbi_image_free(imageData);
    glBindTexture(GL_TEXTURE_2D, 0);
    

    // Texture 2
    glGenTextures(1, &m_texture2);
    glBindTexture(GL_TEXTURE_2D, m_texture2);
    
    // Set texture wrapping options
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    
    // Set texture filtering options
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    
    filename = "res/Textures/awesomeface.png";
    imageData = stbi_load(filename.c_str(), &width, &height, 0, 3);
    
    // Check if image was loaded
    if (imageData == NULL) {
        std::cout << "Image data not found\n";
    }
    
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, imageData);
    glGenerateMipmap(GL_TEXTURE_2D);
    stbi_image_free(imageData);
    glBindTexture(GL_TEXTURE_2D, 0);
}

void Game::init() {
    // Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cout << "Could not initialize SDL: " << SDL_GetError() << "\n";
    }
    
    // Tell OpenGL to create a core context
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    
    // TODO: add options to window creation
    m_window.create();
    
    SDL_SetRelativeMouseMode(SDL_TRUE);
    
    SDL_GL_SetSwapInterval(1);
    
    const GLubyte* renderer = glGetString(GL_RENDERER);
    const GLubyte* version = glGetString(GL_VERSION);
    std::cout << "Renderer: " << renderer << "\n";
    std::cout << "OpenGL version supported: " << version << "\n";
    
    glEnable(GL_DEPTH_TEST); // enable depth-testing
//    glDepthFunc(GL_LESS); // depth-testing interprets a smaller value as "closer"
}

void Game::destroy() {
    glDeleteVertexArrays(1, &m_vao);
    glDeleteBuffers(1, &m_vbo);
    
    m_window.destroy();
    
    SDL_Quit();
}

void Game::update() {
    while (!m_quit) {
        currentTime = SDL_GetTicks();
        deltaTime = currentTime - prevTime;
        
        handleInput(deltaTime);
        // update(deltaTime);
        draw();
        
        prevTime = currentTime;
    }
}

void Game::draw() {
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    m_shader.use();
    
    // Use our textures
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, m_texture1);
    glUniform1i(m_shader.getUniformLocation("ourTexture1"), 0);
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, m_texture2);
    glUniform1i(m_shader.getUniformLocation("ourTexture2"), 1);
    
    glm::mat4 view;
    view = m_camera.getViewMatrix();
    
    glm::mat4 projection;
    projection = glm::perspective(glm::radians(m_camera.getZoom()), (float)m_window.getWidth() / (float)m_window.getHeight(), 0.1f, 1000.0f);
    
    GLuint modelLoc = m_shader.getUniformLocation("model");
    GLuint viewLoc = m_shader.getUniformLocation("view");
    GLuint projectionLoc = m_shader.getUniformLocation("projection");
    
    glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
    glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projection));
    
    glBindVertexArray(m_vao);
    for (GLuint i = 0; i < 10; i++) {
        glm::mat4 model;
        model = glm::translate(model, cubePositions[i]);
        GLfloat angle = 20.0f * i;
        model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        
        glDrawArrays(GL_TRIANGLES, 0, 36);
    }
    
    glBindVertexArray(0);
    
    glUseProgram(0);
    
    m_window.swapWindow();
}

void Game::handleInput(float deltaTime) {
    m_inputHandler.update();
    
    SDL_Event e;
    
    if (SDL_PollEvent(&e)) {
        
        switch (e.type) {
            case SDL_QUIT:
                m_quit = true;
                break;
            case SDL_KEYDOWN:
                m_inputHandler.pressKey(e.key.keysym.sym);
                break;
            case SDL_KEYUP:
                m_inputHandler.releaseKey(e.key.keysym.sym);
                break;
            case SDL_MOUSEMOTION:
                m_inputHandler.setMouseCoords(e.motion.x, e.motion.y);
                m_camera.processMouseMovement(e.motion.xrel, -e.motion.yrel);
                break;
            case SDL_MOUSEBUTTONDOWN:
                m_inputHandler.pressKey(e.button.button);
                break;
            case SDL_MOUSEBUTTONUP:
                m_inputHandler.releaseKey(e.button.button);
                break;
            case SDL_MOUSEWHEEL:
                m_camera.processMouseScroll(e.wheel.y);
                break;
            default:
                break;
        }
    }
    
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



