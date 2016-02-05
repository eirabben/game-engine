#pragma once

#include "../EcsSettings.hpp"
#include <OpenGL/gl3.h>
#include <glm/gtc/type_ptr.hpp>

class PPointLight {
    using Signature = ecs::Signature<CPointLight>;
    
public:
    void update(Manager& mgr, Shader& shader) {
        mgr.forEntitiesMatching<Signature>(
        [&shader](auto& entity, auto& light) {
            glUniform3fv(shader.getUniformLocation("pointLights[" + std::to_string(light.id) + "].position"), 1, glm::value_ptr(light.position));
            glUniform3fv(shader.getUniformLocation("pointLights[" + std::to_string(light.id) + "].ambient"), 1, glm::value_ptr(light.ambient));
            glUniform3fv(shader.getUniformLocation("pointLights[" + std::to_string(light.id) + "].diffuse"), 1, glm::value_ptr(light.diffuse));
            glUniform3fv(shader.getUniformLocation("pointLights[" + std::to_string(light.id) + "].specular"), 1, glm::value_ptr(light.specular));
            glUniform1f(shader.getUniformLocation("pointLights[" + std::to_string(light.id) + "].constant"), light.constant);
            glUniform1f(shader.getUniformLocation("pointLights[" + std::to_string(light.id) + "].linear"), light.linear);
            glUniform1f(shader.getUniformLocation("pointLights[" + std::to_string(light.id) + "].quadratic"), light.quadratic);
        });
    }
};
