#pragma once

#include "Camera.hpp"

class Command {
public:
    virtual ~Command() {}
    virtual void execute(Camera& camera) = 0;
};

class MoveForwardCommand : public Command {
public:
    virtual void execute(Camera& camera) {
        
    }
};