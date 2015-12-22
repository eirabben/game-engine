#include "Shader.hpp"

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

Shader::Shader() {
    
}

Shader::~Shader() {
    
}

void Shader::compileShaders(const GLchar* vertexShaderPath, const GLchar* fragmentShaderPath) {
    // Retrieve the source code from the file paths
    std::string vertexShaderCode;
    std::string fragmentShaderCode;
    std::ifstream vertexShaderFile;
    std::ifstream fragmentShaderFile;
    
    // Ensure that ifstream objects can throw exceptions
    vertexShaderFile.exceptions(std::ifstream::badbit);
    fragmentShaderFile.exceptions(std::ifstream::badbit);
    try {
        // Open files
        vertexShaderFile.open(vertexShaderPath);
        fragmentShaderFile.open(fragmentShaderPath);
        std::stringstream vertexShaderStream;
        std::stringstream fragmentShaderStream;
        // Read file buffers into streams
        vertexShaderStream << vertexShaderFile.rdbuf();
        fragmentShaderStream << fragmentShaderFile.rdbuf();
        // Close file handles
        vertexShaderFile.close();
        fragmentShaderFile.close();
        // Convert stream into string
        vertexShaderCode = vertexShaderStream.str();
        fragmentShaderCode = fragmentShaderStream.str();
    } catch (std::ifstream::failure e) {
        std::cout << "Could not read shader file\n";
    }
    
    const GLchar* vertexCode = vertexShaderCode.c_str();
    const GLchar* fragmentCode = fragmentShaderCode.c_str();
    
    GLuint vertexShader;
    GLuint fragmentShader;
    
    // Compile shaders
    GLint success;
    GLchar infoLog[512];
    
    // Vertex shader
    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexCode, NULL);
    glCompileShader(vertexShader);
    // Check for errors
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        std::cout << "Could not compile vertex shader\n" << infoLog << "\n";
    }
    
    // Fragment shader
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentCode, NULL);
    glCompileShader(fragmentShader);
    // Check for errors
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
        std::cout << "Could not compile fragment shader\n" << infoLog << "\n";
    }
    
    // Shader program
    m_program = glCreateProgram();
    glAttachShader(m_program, vertexShader);
    glAttachShader(m_program, fragmentShader);
    glLinkProgram(m_program);
    // Check for errors
    glGetProgramiv(m_program, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(m_program, 512, NULL, infoLog);
        std::cout << "Could not link program\n" << infoLog << "\n";
    }
    // Shaders are no longer needed, delete them
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
    
}

void Shader::use() {
    glUseProgram(m_program);
}



