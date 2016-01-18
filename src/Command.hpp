#pragma once

#include <functional>

class Command {
public:
    virtual ~Command() {}
    virtual void execute() = 0;
};