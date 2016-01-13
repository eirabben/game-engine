#include "Timer.hpp"

#include <SDL2/SDL.h>

void Timer::init() {
    m_maxFps = 60.0f;
}

void Timer::beginFrame() {
    m_startTicks = SDL_GetTicks();
}

float Timer::endFrame() {
    calculateFPS();
    
    float frameTicks = SDL_GetTicks() - m_startTicks;
    
    if (1000.0f / m_maxFps > frameTicks) {
        SDL_Delay(1000.0f/ m_maxFps - frameTicks);
    }
    
    return m_fps;
}

void Timer::calculateFPS() {
    static const int NUM_SAMPLES = 10;
    static float frameTimes[NUM_SAMPLES];
    static int currentFrame = 0;
    static Uint32 prevTicks = SDL_GetTicks();
    
    Uint32 currentTicks = SDL_GetTicks();
    
    m_frameTime = currentTicks - prevTicks;
    frameTimes[currentFrame % NUM_SAMPLES] = m_frameTime;
    
    prevTicks = currentTicks;
    
    int count;
    
    currentFrame++;
    if (currentFrame < NUM_SAMPLES) {
        count = currentFrame;
    } else {
        count = NUM_SAMPLES;
    }
    
    float frameTimeAverage = 0.0f;
    for (int i = 0; i < count; i++) {
        frameTimeAverage += frameTimes[i];
    }
    frameTimeAverage /= count;
    
    if (frameTimeAverage > 0) {
        m_fps = 1000.0f / frameTimeAverage;
    } else {
        m_fps = 60.0f;
    }
}