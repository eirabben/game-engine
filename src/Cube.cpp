#include "Cube.hpp"

#include "TextureLoader.hpp"
#include <string>
#include <iostream>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>

Cube::Cube(glm::vec3 position) :
m_position(position) {
    
}

void Cube::init() {
    m_mesh.setupMesh();
    
    glm::mat4 m = m_mesh.getModelMatrix();
    m = glm::translate(m, m_position);
    m_mesh.setModelMatrix(m);
    
    m_material.diffuseMap = TextureLoader::loadTexture("res/Textures/container2.png");
    m_material.specularMap = TextureLoader::loadTexture("res/Textures/container2_specular.png");
    m_material.shininess = 32.0f;
}


void Cube::draw(Shader& shader) {
    GLint matShineLoc = shader.getUniformLocation("material.shininess");
    glUniform1f(matShineLoc, m_material.shininess);
    
    // Use our textures
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, m_material.diffuseMap.id);
    glUniform1i(shader.getUniformLocation("material.diffuse"), 0);
    
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, m_material.specularMap.id);
    glUniform1i(shader.getUniformLocation("material.specular"), 1);
    
    m_mesh.draw(shader);
}

glm::vec3 Cube::getPosition() const {
    return m_position;
}
