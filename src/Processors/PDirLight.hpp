#pragma once

#include "../EcsSettings.hpp"
#include <OpenGL/gl3.h>
#include <glm/gtc/type_ptr.hpp>

class PDirLight {
    using Signature = ecs::Signature<CDirLight>;
    
public:
    void update(Manager& mgr, Shader& shader) {
        mgr.forEntitiesMatching<Signature>(
        [&shader](auto&, auto& light) {
            glUniform3fv(shader.getUniformLocation("dirLight.direction"), 1, glm::value_ptr(light.direction));
            glUniform3fv(shader.getUniformLocation("dirLight.ambient"), 1, glm::value_ptr(light.ambient));
            glUniform3fv(shader.getUniformLocation("dirLight.diffuse"), 1, glm::value_ptr(light.diffuse));
            glUniform3fv(shader.getUniformLocation("dirLight.specular"), 1, glm::value_ptr(light.specular));
        });
    }
};
