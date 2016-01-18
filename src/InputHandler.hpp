#pragma once

#include "Command.hpp"
#include <glm/glm.hpp>
#include <unordered_map>
#include <memory>

using KeyID = unsigned int;

class InputHandler {
public:
    InputHandler();
    
    void update();
    
    void keyPressed(KeyID id);
    void keyReleased(KeyID id);
    void mouseMoved(float newX, float newY, float xRel, float yRel);
    
    bool isKeyDown(KeyID id);
    bool wasKeyPressed(KeyID id);
    
    glm::vec2 getMouseCoords() const;
    
private:
    bool wasKeyDown(KeyID id);
    
    std::unordered_map<KeyID, bool> m_keyMap;
    std::unordered_map<KeyID, bool> m_previousKeyMap;
    
    glm::vec2 m_mouseCoords = glm::vec2(0.0f, 0.0f);
};