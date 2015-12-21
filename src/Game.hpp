#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>

class Game {
public:
    Game();
    ~Game();
    
    void run();
    
    void prepare();
    
    void init();
    void destroy();
    
    void update();
    void draw();
    
private:
    SDL_Window* m_window = nullptr;
    SDL_GLContext m_context;
    
};
