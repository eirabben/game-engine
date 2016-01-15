#include "CubeMesh.hpp"

#include <glm/gtc/type_ptr.hpp>

void CubeMesh::setupMesh() {
    // Generate array and buffer objects
    glGenVertexArrays(1, &m_vao);
    glGenBuffers(1, &m_vbo);
    
    glBindVertexArray(m_vao);
    
    // Send the buffer data
    glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
    glBufferData(GL_ARRAY_BUFFER, m_vertices.size() * sizeof(GLfloat), &m_vertices[0], GL_STATIC_DRAW);
    
    // Vertex Positions
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)0);
    
    // Unbind buffer and vertex array
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void CubeMesh::draw(Shader& shader) {
    GLuint modelLoc = shader.getUniformLocation("model");
    glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(m_modelMatrix));
    
    glBindVertexArray(m_vao);
    glDrawArrays(GL_TRIANGLES, 0, 36);
    glBindVertexArray(0);
}