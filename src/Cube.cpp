#include "Cube.hpp"

#define STB_IMAGE_IMPLEMENTATION // Required for stb_image.h
#include <stb_image.h>
#include <string>
#include <iostream>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>

Cube::Cube(glm::vec3 position, glm::vec3 color) :
m_position(position),
m_color(color) {
    
}

void Cube::init() {
    m_mesh.setupMesh();
    
    glm::mat4 m = m_mesh.getModelMatrix();
    m = glm::translate(m, m_position);
    m_mesh.setModelMatrix(m);
    
//    // Load textures
//    // Texture 1
//    glGenTextures(1, &m_texture1);
//    glBindTexture(GL_TEXTURE_2D, m_texture1);
//    
//    // Set texture wrapping options
//    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
//    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
//    
//    // Set texture filtering options
//    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
//    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
//    
//    int width;
//    int height;
//    std::string filename = "res/Textures/container.jpg";
//    unsigned char* imageData = stbi_load(filename.c_str(), &width, &height, 0, 3);
//    
//    // Check if image was loaded
//    if (imageData == NULL) {
//        std::cout << "Image data not found\n";
//    }
//    
//    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, imageData);
//    glGenerateMipmap(GL_TEXTURE_2D);
//    stbi_image_free(imageData);
//    glBindTexture(GL_TEXTURE_2D, 0);
//    
//    
//    // Texture 2
//    glGenTextures(1, &m_texture2);
//    glBindTexture(GL_TEXTURE_2D, m_texture2);
//    
//    // Set texture wrapping options
//    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
//    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
//    
//    // Set texture filtering options
//    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
//    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
//    
//    filename = "res/Textures/awesomeface.png";
//    imageData = stbi_load(filename.c_str(), &width, &height, 0, 3);
//    
//    // Check if image was loaded
//    if (imageData == NULL) {
//        std::cout << "Image data not found\n";
//    }
//    
//    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, imageData);
//    glGenerateMipmap(GL_TEXTURE_2D);
//    stbi_image_free(imageData);
//    glBindTexture(GL_TEXTURE_2D, 0);
}


void Cube::draw(Shader& shader) {
    m_mesh.draw(shader);
    
    // Use our textures
//    glActiveTexture(GL_TEXTURE0);
//    glBindTexture(GL_TEXTURE_2D, m_texture1);
//    glUniform1i(shader.getUniformLocation("ourTexture1"), 0);
//    glActiveTexture(GL_TEXTURE1);
//    glBindTexture(GL_TEXTURE_2D, m_texture2);
//    glUniform1i(shader.getUniformLocation("ourTexture2"), 1);
}

glm::vec3 Cube::getPosition() const {
    return m_position;
}
glm::vec3 Cube::getColor() const {
    return m_color;
}
