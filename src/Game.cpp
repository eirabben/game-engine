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

    while (!scene.m_quit) {
        currentTicks = SDL_GetTicks();
        deltaTime = (currentTicks - previousTicks);
        previousTicks = currentTicks;

        inputHandler.update();

        update(deltaTime);
        draw();
    }

    quit();
}

bool Game::init() {
    // Load Lua config
    sel::State config;
    config.Load("res/config.lua");
    
    // These must apparently be set before SDL_Init
    SDL_SetRelativeMouseMode(SDL_TRUE);
    SDL_GL_SetSwapInterval(1);

    // Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cout << "Could not initialize SDL: " << SDL_GetError() << "\n";
        return false;
    }

    // Tell OpenGL to create a core context
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

    // @TODO: Add settings to window creation
    window.create(config["screenWidth"], config["screenHeight"]);


    glEnable(GL_DEPTH_TEST);

    scene.setGame(this);
    scene.init();

    return true;
}

void Game::update(float deltaTime) {
    scene.update(deltaTime);
}

void Game::draw() {
    scene.draw();
    window.swapWindow();
}

void Game::onSdlEvent(SDL_Event& e) {
    switch (e.type) {
        case SDL_QUIT:
            break;
        case SDL_MOUSEMOTION:
            std::cout << "Mouse movement\n";
            inputHandler.mouseMoved(e.motion.x, e.motion.y, e.motion.xrel, e.motion.yrel);
            SDL_WarpMouseInWindow(window.getWindow(), window.getWidth() / 2, window.getHeight() / 2);
            break;
        case SDL_KEYDOWN:
            inputHandler.keyPressed(e.key.keysym.sym);
            break;
        case SDL_KEYUP:
            inputHandler.keyReleased(e.key.keysym.sym);
            break;
        case SDL_MOUSEBUTTONDOWN:
            std::cout << "Mouse pressed\n";
            inputHandler.keyPressed(e.button.button);
            break;
        case SDL_MOUSEBUTTONUP:
            inputHandler.keyReleased(e.button.button);
            break;
        case SDL_MOUSEWHEEL:
            break;
        default:
            break;
    }
}

void Game::quit() {
    scene.destroy();
    window.destroy();
    SDL_Quit();
}

