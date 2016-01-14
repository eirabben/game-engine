#pragma once

#include <glm/glm.hpp>
#include <unordered_map>

using KeyID = unsigned int;

class InputHandler {
public:
    void update();
    
    void keyPressed(KeyID id);
    void keyReleased(KeyID id);
    void mouseMoved(float newX, float newY, float xRel, float yRel);
    
    void setMouseCoords(float x, float y);
    
    bool isKeyDown(KeyID id);
    bool wasKeyPressed(KeyID id); // @TODO: Change the name to reflect what it does
    
    glm::vec2 getMouseCoords() const;
    
private:
    bool wasKeyDown(KeyID id);
    
    std::unordered_map<KeyID, bool> m_keyMap;
    std::unordered_map<KeyID, bool> m_previousKeyMap;
    
    glm::vec2 m_mouseCoords = glm::vec2(0.0f, 0.0f);
    
};