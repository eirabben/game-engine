#pragma once

#include <OpenGL/gl3.h>
#include <string>

struct Texture {
    std::string filePath;
    GLuint id = 0;
    int width = 0;
    int height = 0;
};