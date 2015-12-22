#pragma once

#include <OpenGL/gl3.h>
#include <string>

class Shader {
public:
    
    Shader();
    ~Shader();
    
    void compileShaders(const GLchar* vertexShaderPath, const GLchar* fragmentShaderPath);
//    void compileShader(const GLchar* shaderSource, GLuint shaderID, const std::string& shaderName);
//    void linkShaders();
//    const GLchar* loadSourceFromFile(const std::string shaderPath);
    
    void use();
    
private:
    GLuint m_program;
    
};