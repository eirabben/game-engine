#pragma once

#include <OpenGL/gl3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

enum CameraMovement {
    FORWARD,
    BACKWARD,
    LEFT,
    RIGHT
};

// Default values
const GLfloat YAW = -90.0f;
const GLfloat PITCH = 0.0f;
const GLfloat SPEED = 3.0f;
const GLfloat SENSITIVITY = 0.25f;
const GLfloat ZOOM = 45.0f;

class Camera {
public:
    Camera(glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f), GLfloat yaw = YAW, GLfloat pitch = PITCH);
    Camera(GLfloat posX, GLfloat posY, GLfloat posZ, GLfloat upX, GLfloat upY, GLfloat upZ, GLfloat yaw, GLfloat pitch);
    
    glm::mat4 getViewMatrix() const;
    GLfloat getZoom() const;
    
    void processKeyboard(CameraMovement direction, GLfloat deltaTime);
    void processMouseMovement(GLfloat xOffset, GLfloat yOffset, GLboolean constrainPitch = true);
    void processMouseScroll(GLfloat yOffset);
    
private:
    void updateCameraVectors();
    
    // Camera attributes
    glm::vec3 m_position = glm::vec3(0.0f, 0.0f, 0.0f);
    glm::vec3 m_front = glm::vec3(0.0f, 0.0f, -1.0f);
    glm::vec3 m_up;
    glm::vec3 m_right;
    glm::vec3 m_worldUp;
    
    // Euler angles
    GLfloat m_yaw;
    GLfloat m_pitch;
    
    // Camera options
    GLfloat m_movementSpeed = SPEED;
    GLfloat m_mouseSensitivity = SENSITIVITY;
    GLfloat m_zoom = ZOOM;
    
};
