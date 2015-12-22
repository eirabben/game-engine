#include "Game.hpp"
#include <iostream>
#include <fstream>
#include <vector>
#include <string>

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
    
    float vertices[] = {
         0.0f,  0.5f, // v1 (x,y)
         0.5f, -0.5f, // v2 (x,y)
        -0.5f, -0.5f  // v3 (x,y)
    };
    
    GLuint vbo;
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
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
    m_window = SDL_CreateWindow("OpenGL", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);
    if (m_window == nullptr) {
        std::cout << "Window could not be created: " << SDL_GetError() << "\n";
    }
    
    // Create the OpenGL context
    m_context = SDL_GL_CreateContext(m_window);
    if (m_context == NULL) {
        std::cout << "Could not create context: " << SDL_GetError() << "\n";
    }
}

void Game::destroy() {
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
    SDL_GL_SwapWindow(m_window);
}