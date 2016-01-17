#pragma once

#include "Texture.hpp"
#include <glm/glm.hpp>

struct Material {
    Texture diffuseMap;
    Texture specularMap;
    float shininess;
};