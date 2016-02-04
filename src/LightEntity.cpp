#include "LightEntity.hpp"

#include <glm/gtc/matrix_transform.hpp>

LightEntity::LightEntity() {
    
}

void LightEntity::init() {
    m_mesh.setupMesh();
    
    glm::mat4 m = m_mesh.getModelMatrix();
    m = glm::translate(m, m_position);
    m = glm::scale(m, glm::vec3(0.2f));
    m_mesh.setModelMatrix(m);
}

void LightEntity::draw(Shader& shader) {
    m_mesh.draw(shader);
}