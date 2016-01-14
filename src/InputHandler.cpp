#include "InputHandler.hpp"

#include <SDL2/SDL.h>

void InputHandler::update() {
    for (auto it : m_keyMap) {
        m_previousKeyMap[it.first] = it.second;
    }
}

//void InputHandler::handleInput() {
//    
//}

void InputHandler::keyPressed(KeyID id) {
    m_keyMap[id] = true;
}

void InputHandler::keyReleased(KeyID id) {
    m_keyMap[id] = false;
}

void InputHandler::setMouseCoords(float x, float y) {
    m_mouseCoords = glm::vec2(x, y);
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
