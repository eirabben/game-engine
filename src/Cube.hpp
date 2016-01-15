#pragma once

#include "Entity.hpp"
#include <OpenGL/gl3.h>
#include <vector>
#include <glm/glm.hpp>
#include "Shader.hpp"
#include "CubeMesh.hpp"

class Cube {
public:
    Cube(glm::vec3 position, glm::vec3 color);
    
    void init();
    void draw(Shader& shader);
    
    glm::vec3 getPosition() const;
    glm::vec3 getColor() const;
    
private:
    glm::vec3 m_position;
    glm::vec3 m_color;
    
    CubeMesh m_mesh;
};