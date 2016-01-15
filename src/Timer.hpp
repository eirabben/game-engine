#pragma once

class Timer {
public:
    void init(float maxFps);
    
    void setMaxFps(float maxFps);
    
    void beginFrame();
    void endFrame();
    
    float getFps() const;
    float getDeltaTime() const;
    
private:
    void calculateFps();
    
    float m_fps = 0.0f;
    float m_maxFps = 0.0f;
    
    float m_deltaTime = 0.0f;
    
    float m_frameTime = 0.0f;
    unsigned int m_startTicks = 0;
};