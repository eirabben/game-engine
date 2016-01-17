#include "Light.hpp"

#include <glm/gtc/matrix_transform.hpp>

Light::Light(glm::vec3 position, glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular) :
m_position(position),
m_ambient(ambient),
m_diffuse(diffuse),
m_specular(specular) {
    
}

void Light::init() {
    m_mesh.setupMesh();
    
    glm::mat4 m = m_mesh.getModelMatrix();
    m = glm::translate(m, m_position);
    m = glm::scale(m, glm::vec3(0.2f));
    m_mesh.setModelMatrix(m);
}

void Light::draw(Shader& shader) {
    m_mesh.draw(shader);
}

glm::vec3 Light::getPosition() const {
    return m_position;
}

glm::vec3 Light::getAmbient() const {
    return m_ambient;
}

glm::vec3 Light::getDiffuse() const {
    return m_diffuse;
}

glm::vec3 Light::getSpecular() const {
    return m_specular;
}