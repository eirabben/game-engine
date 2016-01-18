#pragma once

#include "../CubeMesh.hpp"
#include "../Light.hpp"
#include "../Shader.hpp"
#include <glm/glm.hpp>
#include <memory>

class LightEntity {
public:
    LightEntity();
    
    void init();
    void draw(Shader& shader);
    
    glm::vec3 getPosition() const {
        return m_position;
    }
    
    void setPosition(glm::vec3 position) {
        m_position = position;
    }
    
private:
    glm::vec3 m_position;
    CubeMesh m_mesh;
};

class DirLightEntity : public LightEntity {
public:
    DirLight& getLight() {
        return m_light;
    }
    
    void setLight(DirLight light) {
        m_light = light;
    }
    
private:
    DirLight m_light;
};

class PointLightEntity : public LightEntity {
public:
    PointLight& getLight() {
        return m_light;
    }
    
    void setLight(PointLight light) {
        m_light = light;
    }
    
private:
    PointLight m_light;
};