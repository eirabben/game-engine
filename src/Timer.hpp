#pragma once

class Timer {
public:
    void init();
    
    void beginFrame();
    float endFrame();
    
private:
    void calculateFPS();
    
    float m_fps;
    float m_maxFps;
    float m_frameTime;
    unsigned int m_startTicks;
};