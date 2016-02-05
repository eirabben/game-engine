#pragma once

#include "Scene.hpp"
#include "Window.hpp"

class Game {
public:
    void run();
    bool init();

    void update(float deltaTime);
    void draw();

    void quit();
    
    Window m_window;
    
private:
    bool m_quit {false};
    
    Scene m_scene;
};
