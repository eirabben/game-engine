#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>

class Window {
public:
    Window();
    ~Window();
    
    void create();
    void destroy();
    
    void swapWindow();
    
    int getWidth() const { return m_width; }
    int getHeight() const { return m_height; }
    
private:
    SDL_Window* m_window = nullptr;
    SDL_GLContext m_context;
    
    int m_width = 800;
    int m_height = 600;
};
