#include "TextureLoader.hpp"

#define STB_IMAGE_IMPLEMENTATION // Required for stb_image.h
#include <stb_image.h>
#include <iostream>
#include <OpenGL/gl3.h>

Texture TextureLoader::loadTexture(std::string filePath) {
    Texture texture;
    
    // Load the image with stbi
    int width;
    int height;
    unsigned char* imageData = stbi_load(filePath.c_str(), &width, &height, 0, 3);
    
    // Check if image was loaded
    if (imageData == NULL) {
        std::cout << "Image data not found.\n";
    }
    
    // Generate and bind textures
    glGenTextures(1, &texture.id);
    glBindTexture(GL_TEXTURE_2D, texture.id);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, imageData);
    
    // Free the image data after upload
    stbi_image_free(imageData);
    
    // Set texture wrapping options
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    
    // Set texture filtering options
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    
    // Generate mipmap
    glGenerateMipmap(GL_TEXTURE_2D);
    
    // Unbind texture target
    glBindTexture(GL_TEXTURE_2D, 0);
    
    // Set other texture params
    texture.filePath = filePath;
    texture.width = width;
    texture.height = height;
    
    return texture;
}