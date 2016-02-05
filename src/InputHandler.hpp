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
    
    bool isKeyDown(KeyID id) const;
    bool wasKeyPressed(KeyID id) const;
    bool hasMouseMoved() const;
    
    glm::vec2 getMouseCoords() const;
    glm::vec2 getMouseRel() const;
    
private:
    bool wasKeyDown(KeyID id) const;
    
    std::unordered_map<KeyID, bool> m_keyMap;
    std::unordered_map<KeyID, bool> m_previousKeyMap;
    
    bool m_mouseMoved {false};
    glm::vec2 m_mouseCoords {0.0f, 0.0f};
    glm::vec2 m_mouseRel {0.0f, 0.0f};
};
