#pragma once

#include "CubeMesh.hpp"
#include "Shader.hpp"
#include <glm/glm.hpp>

class Light {
public:
    Light(glm::vec3 position, glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular);
    
    void init();
    void draw(Shader& shader);
    
    glm::vec3 getPosition() const;
    glm::vec3 getAmbient() const;
    glm::vec3 getDiffuse() const;
    glm::vec3 getSpecular() const;
    
private:
    glm::vec3 m_position;
    
    glm::vec3 m_ambient;
    glm::vec3 m_diffuse;
    glm::vec3 m_specular;
    
    CubeMesh m_mesh;
};