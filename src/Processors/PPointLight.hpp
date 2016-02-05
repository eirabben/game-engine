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
            glUniform3fv(shader.getUniformLocation("pointLights[0].position"), 1, glm::value_ptr(light.position));
            glUniform3fv(shader.getUniformLocation("pointLights[0].ambient"), 1, glm::value_ptr(light.ambient));
            glUniform3fv(shader.getUniformLocation("pointLights[0].diffuse"), 1, glm::value_ptr(light.diffuse));
            glUniform3fv(shader.getUniformLocation("pointLights[0].specular"), 1, glm::value_ptr(light.specular));
            glUniform1f(shader.getUniformLocation("pointLights[0].constant"), light.constant);
            glUniform1f(shader.getUniformLocation("pointLights[0].linear"), light.linear);
            glUniform1f(shader.getUniformLocation("pointLights[0].quadratic"), light.quadratic);
        });
    }
};
