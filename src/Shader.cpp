#include "Shader.hpp"

#include <fstream>
#include <iostream>
#include <sstream>

Shader::Shader() {
    
}

Shader::~Shader() {
    
}

void Shader::compileShaders(const std::string& vertexShaderPath, const std::string& fragmentShaderPath) {
    // Retrieve the source code from the file paths
    std::string vertexShaderSource = loadSourceFromFile(vertexShaderPath);
    std::string fragmentShaderSource = loadSourceFromFile(fragmentShaderPath);
    
    GLuint vertexShader = 0;
    GLuint fragmentShader = 0;
    
    // Create and compile shaders
    
    // Vertex shader
    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    if (vertexShader == 0) {
        std::cout << "Could not create vertex shader\n";
    }
    compileShader(vertexShader, vertexShaderSource.c_str());
    
    // Fragment shader
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    if (fragmentShader == 0) {
        std::cout << "Could not create fragment shader\n";
    }
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
    GLchar infoLog[GL_INFO_LOG_LENGTH];
    glGetShaderiv(shaderID, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(shaderID, GL_INFO_LOG_LENGTH, NULL, infoLog);
        std::cout << "Could not compile shader\n" << infoLog << "\n";
        
        glDeleteShader(shaderID);
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
    GLchar infoLog[GL_INFO_LOG_LENGTH];
    glGetProgramiv(m_program, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(m_program, GL_INFO_LOG_LENGTH, NULL, infoLog);
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

GLint Shader::getUniformLocation(const std::string& uniformName) const {
    GLint location = glGetUniformLocation(m_program, uniformName.c_str());
    if (location == GL_INVALID_INDEX) {
        std::cout << "Uniform " << uniformName << " not found in shader\n";
    }
    return location;
}

void Shader::use() {
    glUseProgram(m_program);
}

void Shader::unuse() {
    glUseProgram(0);
}





