#include "Shader.hpp"

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

Shader::Shader() {
    
}

Shader::~Shader() {
    
}

void Shader::compileShaders(const std::string& vertexShaderPath, const std::string& fragmentShaderPath) {
    // Retrieve the source code from the file paths
    std::string vertexShaderSource = loadSourceFromFile(vertexShaderPath);
    std::string fragmentShaderSource = loadSourceFromFile(fragmentShaderPath);
    
    GLuint vertexShader;
    GLuint fragmentShader;
    
    // Compile shaders
    
    // Vertex shader
    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    compileShader(vertexShader, vertexShaderSource.c_str());
    
    // Fragment shader
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    compileShader(fragmentShader, fragmentShaderSource.c_str());
    
    // Shader program
    linkShaders(vertexShader, fragmentShader);

    // Shaders are no longer needed, delete them
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
    
}

void Shader::compileShader(GLuint shaderID, const GLchar* shaderSource) {
    // Compile the shader
    glShaderSource(shaderID, 1, &shaderSource, NULL);
    glCompileShader(shaderID);
    
    // Check for errors
    GLint success;
    GLchar infoLog[512];
    glGetShaderiv(shaderID, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(shaderID, 512, NULL, infoLog);
        std::cout << "Could not compile shader\n" << infoLog << "\n";
    }
}

void Shader::linkShaders(GLuint vertexShaderID, GLuint fragmentShaderID) {
    // Create shader program
    m_program = glCreateProgram();
    
    // Attach shaders
    glAttachShader(m_program, vertexShaderID);
    glAttachShader(m_program, fragmentShaderID);
    
    // Link the program
    glLinkProgram(m_program);
    
    // Check for errors
    GLint success;
    GLchar infoLog[512];
    glGetProgramiv(m_program, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(m_program, 512, NULL, infoLog);
        std::cout << "Could not link program\n" << infoLog << "\n";
    }
}

std::string Shader::loadSourceFromFile(const std::string& shaderPath) {
    // Retrieve the source code from the file paths
    std::string shaderSource;
    std::ifstream shaderFile;
    
    // Ensure that ifstream objects can throw exceptions
    shaderFile.exceptions(std::ifstream::badbit);
    try {
        // Open files
        shaderFile.open(shaderPath);
        std::stringstream shaderStream;
        // Read file buffers into streams
        shaderStream << shaderFile.rdbuf();
        // Close file handles
        shaderFile.close();
        // Convert stream into string
        shaderSource = shaderStream.str();
    } catch (std::ifstream::failure e) {
        std::cout << "Could not read shader file: " << shaderPath << "\n";
    }
    
    return shaderSource;
}

void Shader::use() {
    glUseProgram(m_program);
}





