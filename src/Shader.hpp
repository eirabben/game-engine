#pragma once

#include <OpenGL/gl3.h>
#include <string>

class Shader {
public:
    
    Shader();
    Shader(const std::string& vertexShaderPath, const std::string& fragmentShaderPath);
    ~Shader();
    
    void compileShaders(const std::string& vertexShaderPath, const std::string& fragmentShaderPath);
    void compileShader(const GLchar* shaderSource, GLuint shaderID, const std::string& shaderName);
    void linkShaders();
    const GLchar* loadSourceFromFile(const std::string shaderPath);
    
    void use();
    
private:
    
    
    GLuint m_program;
    GLuint m_vertexShader;
    GLuint m_fragmentShader;
    
};