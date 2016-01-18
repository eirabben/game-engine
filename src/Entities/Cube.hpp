#pragma once

#include "../Shader.hpp"
#include "../CubeMesh.hpp"
#include "../Material.hpp"
#include <OpenGL/gl3.h>
#include <glm/glm.hpp>
#include <vector>


class Cube {
public:
    Cube(glm::vec3 position);
    
    void init();
    void draw(Shader& shader);
    
    glm::vec3 getPosition() const;
    
private:
    glm::vec3 m_position;
    
    CubeMesh m_mesh;
    Material m_material;
};