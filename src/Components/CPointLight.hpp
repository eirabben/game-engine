#pragma once

#include <glm/glm.hpp>

struct CPointLight {
    glm::vec3 ambient;
    glm::vec3 diffuse;
    glm::vec3 specular;

    glm::vec3 position;
    
    GLfloat constant;
    GLfloat linear;
    GLfloat quadratic;
};
