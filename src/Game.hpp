#pragma once

#include "InputHandler.hpp"
#include "Scene.hpp"
#include "Window.hpp"

class Game {
public:
    void run();
    bool init();

    void update(float deltaTime);
    void draw();

    void onSdlEvent(SDL_Event& e);

    void quit();
    
    Window window;
    InputHandler inputHandler;
    
private:
    Scene scene;

};
