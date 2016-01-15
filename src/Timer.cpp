#include "Timer.hpp"

#include <SDL2/SDL.h>

void Timer::init(float maxFps) {
    setMaxFps(maxFps);
}

void Timer::setMaxFps(float maxFps) {
    m_maxFps = maxFps;
}

void Timer::beginFrame() {
    m_startTicks = SDL_GetTicks();
}

void Timer::endFrame() {
    calculateFps();
    
    float frameTicks = SDL_GetTicks() - m_startTicks;
    
    if (1000.0f / m_maxFps > frameTicks) {
        SDL_Delay(1000.0f/ m_maxFps - frameTicks);
    }
}

float Timer::getFps() const {
    return m_fps;
}

float Timer::getDeltaTime() const {
    return m_deltaTime;
}

void Timer::calculateFps() {
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