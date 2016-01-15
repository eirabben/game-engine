#pragma once

#include "Entity.hpp"
#include <functional>
#include <iostream>

class Command {
public:
    virtual ~Command() {}
    virtual void execute(Entity& entity) = 0;
};

class MoveForwardCommand : public Command {
public:
    virtual void execute(Entity& entity) override {
        entity.moveForward();
    }
};

class MoveBackwardCommand : public Command {
public:
    virtual void execute(Entity& entity) override {
        entity.moveBackward();
    }
};

class MoveLeftCommand : public Command {
public:
    virtual void execute(Entity& entity) override {
        entity.moveLeft();
    }
};

class MoveRightCommand : public Command {
public:
    virtual void execute(Entity& entity) override {
        entity.moveRight();
    }
};