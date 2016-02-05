#pragma once

#include "../EcsSettings.hpp"

#include <iostream>

#include <glm/gtc/type_ptr.hpp>

class PLampRenderer {
    using Signature = ecs::Signature<CPointLight, CMesh>;
    
public:
    void update(Manager& mgr, Shader& shader) {
        mgr.forEntitiesMatching<Signature>(
        [&shader](auto& entity, auto& light, auto& mesh) {

            GLuint modelLoc = shader.getUniformLocation("model");
            glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(mesh.modelMatrix));
            
            glBindVertexArray(mesh.vao);
            glDrawArrays(GL_TRIANGLES, 0, 36);
            glBindVertexArray(0);
        });
    }
};
