#pragma once

#include "Camera.hpp"
#include <functional>

class Command {
public:
    virtual ~Command() {}
    virtual void execute(Camera& camera) = 0;
};

class QuitCommand : public Command {
public:
    QuitCommand(std::function<void(Camera& camera)> func) : func(func) {
        
    }
    
    virtual void execute(Camera& camera) {
        func(camera);
    }
    
private:
    std::function<void(Camera& camera)> func;
};