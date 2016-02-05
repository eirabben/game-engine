#pragma once

#include "../EcsSettings.hpp"

#include <iostream>

#include <glm/gtc/type_ptr.hpp>

class PLightRenderer {
    using Signature = ecs::Signature<CPosition, CMesh, CMaterial>;
    
public:
    void update(Manager& mgr, Shader& shader) {
        mgr.forEntitiesMatching<Signature>(
        [&shader](auto& entity, auto& pos, auto& mesh, auto& mat) {

            /* std::cout << "Entity name: " << entity.name << "\n"; */

            GLint matShineLoc = shader.getUniformLocation("material.shininess");
            glUniform1f(matShineLoc, mat.shininess);
            
            // Use our textures
            glActiveTexture(GL_TEXTURE0);
            glBindTexture(GL_TEXTURE_2D, mat.diffuseMap.id);
            glUniform1i(shader.getUniformLocation("material.diffuse"), 0);
            
            glActiveTexture(GL_TEXTURE1);
            glBindTexture(GL_TEXTURE_2D, mat.specularMap.id);
            glUniform1i(shader.getUniformLocation("material.specular"), 1);

            GLuint modelLoc = shader.getUniformLocation("model");
            glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(mesh.modelMatrix));
            
            glBindVertexArray(mesh.vao);
            glDrawArrays(GL_TRIANGLES, 0, 36);
            glBindVertexArray(0);
        });
    }
};
