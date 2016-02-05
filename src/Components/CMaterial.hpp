#pragma once

#include "../Texture.hpp"

struct CMaterial {
    Texture diffuseMap;
    Texture specularMap;
    float shininess;
};
