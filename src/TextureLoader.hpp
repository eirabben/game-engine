#pragma once

#include "Texture.hpp"
#include <string>

class TextureLoader {
public:
    static Texture loadTexture(std::string filePath);
};