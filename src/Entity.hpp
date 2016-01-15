#pragma once

class Entity {
public:
    virtual ~Entity() {}
    
    virtual void moveForward() {}
    virtual void moveBackward() {}
    virtual void moveLeft() {}
    virtual void moveRight() {}
};