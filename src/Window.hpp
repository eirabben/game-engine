#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>

class Window {
public:
    Window();
    ~Window();
    
    void create(int width, int height);
    void destroy();
    
    void swapWindow();
    
    int getWidth() const;
    int getHeight() const;
    
    // This should be temporary until relative mouse mode works
    SDL_Window* getWindow() const { return m_window; }
    
private:
    SDL_Window* m_window = nullptr;
    SDL_GLContext m_context;
    
    int m_width = 800;
    int m_height = 600;
};
