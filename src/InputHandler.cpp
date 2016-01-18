#include "InputHandler.hpp"

#include <SDL2/SDL.h>

InputHandler::InputHandler() {
}

void InputHandler::update() {
    for (auto it : m_keyMap) {
        m_previousKeyMap[it.first] = it.second;
    }
}

void InputHandler::keyPressed(KeyID id) {
    m_keyMap[id] = true;
}

void InputHandler::keyReleased(KeyID id) {
    m_keyMap[id] = false;
}

void InputHandler::mouseMoved(float newX, float newY, float xRel, float yRel) {
    m_mouseCoords = glm::vec2(newX, newY);
}

bool InputHandler::isKeyDown(KeyID id) {
    // Using iterator method to avoid creating the key if it does not exist.
    auto it = m_keyMap.find(id);
    if (it != m_keyMap.end()) {
        return it->second;
    }
    
    return false;
}

bool InputHandler::wasKeyPressed(KeyID id) {
    if (isKeyDown(id) && !wasKeyDown(id)) {
        return true;
    }
    
    return false;
}

glm::vec2 InputHandler::getMouseCoords() const {
    return m_mouseCoords;
}

bool InputHandler::wasKeyDown(KeyID id) {
    auto it = m_previousKeyMap.find(id);
    if (it != m_previousKeyMap.end()) {
        return it->second;
    }
    
    return false;
}
