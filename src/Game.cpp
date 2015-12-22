#include "Game.hpp"
#include <iostream>
#include <fstream>
#include <vector>
#include <string>

#include <cmath>

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
    m_shader.compileShaders("Shaders/simple.vert", "Shaders/simple.frag");
    
    GLfloat vertices[] = {
        // Positions         // Colors
        -0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f,  // Bottom right
         0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,  // Bottom left
         0.0f,  0.5f, 0.0f,  0.0f, 0.0f, 1.0f   // Top
    };
    
    glGenVertexArrays(1, &m_vao);
    glGenBuffers(1, &m_vbo);
    
    glBindVertexArray(m_vao);
    
    glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    
    // Position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)0);
    glEnableVertexAttribArray(0);
    
    // Color attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
    glEnableVertexAttribArray(1);
    
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    
    glBindVertexArray(0);
    
//    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
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
    
    // Create the window
    m_window = SDL_CreateWindow("OpenGL", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, m_windowWidth, m_windowHeight, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);
    if (m_window == nullptr) {
        std::cout << "Window could not be created: " << SDL_GetError() << "\n";
    }
    
    // Create the OpenGL context
    m_context = SDL_GL_CreateContext(m_window);
    if (m_context == NULL) {
        std::cout << "Could not create context: " << SDL_GetError() << "\n";
    }
    
    glViewport(0, 0, m_windowWidth, m_windowHeight);
    
    const GLubyte* renderer = glGetString(GL_RENDERER);
    const GLubyte* version = glGetString(GL_VERSION);
    std::cout << "Renderer: " << renderer << "\n";
    std::cout << "OpenGL version supported: " << version << "\n";
    
//    glEnable(GL_DEPTH_TEST); // enable depth-testing
//    glDepthFunc(GL_LESS); // depth-testing interprets a smaller value as "closer"
    
}

void Game::destroy() {
    glDeleteVertexArrays(1, &m_vao);
    glDeleteBuffers(1, &m_vbo);
    
    SDL_GL_DeleteContext(m_context);
    SDL_DestroyWindow(m_window);
    m_window = nullptr;
    SDL_Quit();
}

void Game::update() {
    bool run = true;
    
    SDL_Event windowEvent;
    
    while (run) {
        if (SDL_PollEvent(&windowEvent)) {
            if (windowEvent.type == SDL_QUIT) {
                run = false;
            }
        }
        
        draw();
    }
}

void Game::draw() {
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    
    m_shader.use();
    
    glBindVertexArray(m_vao);
    glDrawArrays(GL_TRIANGLES, 0, 3);
    glBindVertexArray(0);
    
    glUseProgram(0);
    
    SDL_GL_SwapWindow(m_window);
}



