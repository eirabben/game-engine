#pragma once

#include <OpenGL/gl3.h>
#include <string>

class Shader {
public:
    
    Shader();
    ~Shader();
    
    void compileShaders(const std::string& vertexShaderPath, const std::string& fragmentShaderPath);
    void compileShader(GLuint shaderID, const GLchar* shaderSource);
//    void linkShaders();
//    const GLchar* loadSourceFromFile(const std::string shaderPath);
    
    void use();
    
private:
    GLuint m_program;
    
};