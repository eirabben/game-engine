#include "Window.hpp"

#include <iostream>

Window::Window() {
    
}

Window::~Window() {
    
}

void Window::create(int width, int height) {
    m_width = width;
    m_height = height;
    
    // Create the window with SDL
    m_window = SDL_CreateWindow("OpenGL", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, m_width, m_height, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);
    
    // Check for errors
    if (m_window == nullptr) {
        std::cout << "Window could not be created: " << SDL_GetError() << "\n";
    }
    
    // Create the OpenGL context
    m_context = SDL_GL_CreateContext(m_window);
    if (m_context == NULL) {
        std::cout << "Could not create context: " << SDL_GetError() << "\n";
    }
    
    // Tell OpenGL the viewport size
    glViewport(0, 0, m_width, m_height);
}

void Window::destroy() {
    // Delete the context
    SDL_GL_DeleteContext(m_context);
    
    // Destroy the window
    SDL_DestroyWindow(m_window);
    m_window = nullptr;
}

void Window::swapWindow() {
    SDL_GL_SwapWindow(m_window);
}

int Window::getWidth() const {
    return m_width;
}

int Window::getHeight() const {
    return m_height;
}