#include "Game.hpp"

#include <OpenGL/gl3.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>
#include <selene.h>
#include <iostream>

void Game::run() {
    init();

    unsigned int previousTicks {0};
    unsigned int currentTicks {0};
    float deltaTime {0.0f};

    while (!m_scene.m_quit) {
        currentTicks = SDL_GetTicks();
        deltaTime = (currentTicks - previousTicks);
        previousTicks = currentTicks;

        update(deltaTime);
        draw();
    }

    quit();
}

bool Game::init() {
    // Load Lua config
    sel::State config;
    config.Load("res/config.lua");

    // Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cout << "Could not initialize SDL: " << SDL_GetError() << "\n";
        return false;
    }

    // Tell OpenGL to create a core context
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

    // @TODO: Add settings to window creation
    m_window.create(config["screenWidth"], config["screenHeight"]);

    SDL_SetRelativeMouseMode(SDL_TRUE);
    SDL_GL_SetSwapInterval(1);

    // This is for debugging
    const GLubyte* renderer = glGetString(GL_RENDERER);
    const GLubyte* version = glGetString(GL_VERSION);
    std::cout << "Renderer: " << renderer << "\n";
    std::cout << "OpenGL version supported: " << version << "\n";
    
    glEnable(GL_DEPTH_TEST);

    m_scene.setGame(this);
    m_scene.init();

    return true;
}

void Game::update(float deltaTime) {
    m_scene.update(deltaTime);
}

void Game::draw() {
    m_scene.draw();
    m_window.swapWindow();
}

void Game::quit() {
    m_scene.destroy();
    m_window.destroy();
    SDL_Quit();
}

