#pragma once

#include <glm/glm.hpp>

struct CPosition {
    glm::vec3 position;

    CPosition() {}
    CPosition(glm::vec3 position) : position(position) {}
};
