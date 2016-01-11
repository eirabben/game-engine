#include "Camera.hpp"

Camera::Camera(glm::vec3 position, glm::vec3 up, GLfloat yaw, GLfloat pitch) :
m_position(position),
m_worldUp(up),
m_yaw(yaw),
m_pitch(pitch) {
    updateCameraVectors();
}

Camera::Camera(GLfloat posX, GLfloat posY, GLfloat posZ, GLfloat upX, GLfloat upY, GLfloat upZ, GLfloat yaw, GLfloat pitch) :
m_position(glm::vec3(posX, posY, posZ)),
m_worldUp(glm::vec3(upX, upY, upZ)),
m_yaw(yaw),
m_pitch(pitch) {
    
    updateCameraVectors();
}

glm::mat4 Camera::getViewMatrix() const {
    return glm::lookAt(m_position, m_position + m_front, m_up);
}

GLfloat Camera::getZoom() const {
    return m_zoom;
}

void Camera::processKeyboard(CameraMovement direction, GLfloat deltaTime) {
    GLfloat velocity = m_movementSpeed * deltaTime / 1000;
    if (direction == CameraMovement::FORWARD) {
        m_position += m_front * velocity;
    }
    if (direction == CameraMovement::BACKWARD) {
        m_position -= m_front * velocity;
    }
    if (direction == CameraMovement::LEFT) {
        m_position -= m_right * velocity;
    }
    if (direction == CameraMovement::RIGHT) {
        m_position += m_right * velocity;
    }
}

void Camera::processMouseMovement(GLfloat xOffset, GLfloat yOffset, GLboolean constrainPitch) {
    xOffset *= m_mouseSensitivity;
    yOffset *= m_mouseSensitivity;
    
    m_yaw += xOffset;
    m_pitch += yOffset;
    
    if (constrainPitch) {
        if (m_pitch > 89.0f) {
            m_pitch = 89.0f;
        }
        if (m_pitch < -89.0f) {
            m_pitch = -89.0f;
        }
    }
    
    updateCameraVectors();
}

void Camera::processMouseScroll(GLfloat yOffset) {
    // @TODO: Change this to be more readable
    if (m_zoom >= 1.0f && m_zoom <= 45.0f) {
        m_zoom -= yOffset;
    }
    if (m_zoom <= 1.0f) {
        m_zoom = 1.0f;
    }
    if (m_zoom >= 45.0f) {
        m_zoom = 45.0f;
    }
}

void Camera::updateCameraVectors() {
    // Calculate new front vector
    glm::vec3 front;
    front.x = cos(glm::radians(m_yaw)) * cos(glm::radians(m_pitch));
    front.y = sin(glm::radians(m_pitch));
    front.z = sin(glm::radians(m_yaw)) * cos(glm::radians(m_pitch));
    m_front = glm::normalize(front);
    
    // Re-calculate the right and up vectors
    m_right = glm::normalize(glm::cross(m_front, m_worldUp));
    m_up = glm::normalize(glm::cross(m_right, m_front));
}
