#pragma once

#include "CubeMesh.hpp"
#include "Shader.hpp"
#include <glm/glm.hpp>

class Light {
public:
    Light(glm::vec3 position, glm::vec3 color);
    
    void init();
    void draw(Shader& shader);
    
    glm::vec3 getPosition() const;
    glm::vec3 getColor() const;
    
private:
    glm::vec3 m_position;
    glm::vec3 m_color;
    
    CubeMesh m_mesh;
};