#include "InputHandler.hpp"

#include <SDL2/SDL.h>

InputHandler::InputHandler() {
}

void InputHandler::update() {
    for (auto it : m_keyMap) {
        m_previousKeyMap[it.first] = it.second;
    }
    m_mouseRel = glm::vec2(0.0f);
    m_mouseMoved = false;
}

void InputHandler::keyPressed(KeyID id) {
    m_keyMap[id] = true;
}

void InputHandler::keyReleased(KeyID id) {
    m_keyMap[id] = false;
}

void InputHandler::mouseMoved(float newX, float newY, float xRel, float yRel) {
    m_mouseCoords = glm::vec2(newX, newY);
    m_mouseRel = glm::vec2(xRel, yRel);
    m_mouseMoved = true;
}

bool InputHandler::isKeyDown(KeyID id) const {
    // Using iterator method to avoid creating the key if it does not exist.
    auto it = m_keyMap.find(id);
    if (it != m_keyMap.end()) {
        return it->second;
    }
    
    return false;
}

bool InputHandler::wasKeyPressed(KeyID id) const {
    if (isKeyDown(id) && !wasKeyDown(id)) {
        return true;
    }
    
    return false;
}

bool InputHandler::hasMouseMoved() const {
    return m_mouseMoved;
}

glm::vec2 InputHandler::getMouseCoords() const {
    return m_mouseCoords;
}

glm::vec2 InputHandler::getMouseRel() const {
    return m_mouseRel;
}

bool InputHandler::wasKeyDown(KeyID id) const {
    auto it = m_previousKeyMap.find(id);
    if (it != m_previousKeyMap.end()) {
        return it->second;
    }
    
    return false;
}
