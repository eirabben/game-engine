#pragma once

#include <OpenGL/gl3.h>
#include <glm/glm.hpp>

struct Light {
    glm::vec3 ambient;
    glm::vec3 diffuse;
    glm::vec3 specular;
};

struct DirLight : public Light {
    glm::vec3 direction;
};

struct PointLight : public Light {
    glm::vec3 position;
    
    GLfloat constant;
    GLfloat linear;
    GLfloat quadratic;
};