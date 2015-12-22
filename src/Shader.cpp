#include "Shader.hpp"

#include <OpenGL/gl.h>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

Shader::Shader() {
    
}

Shader::Shader(const std::string& vertexShaderPath, const std::string& fragmentShaderPath) {
    compileShaders(vertexShaderPath, fragmentShaderPath);
}

Shader::~Shader() {
    
}

void Shader::compileShaders(const std::string& vertexShaderPath, const std::string& fragmentShaderPath) {
    // Load the shaders into a char buffer
    const GLchar* vertexShaderSource = loadSourceFromFile(vertexShaderPath);
    const GLchar* fragmentShaderSource = loadSourceFromFile(fragmentShaderPath);
    
    // Create and compile vertex shader
    m_vertexShader = glCreateShader(GL_VERTEX_SHADER);
    compileShader(vertexShaderSource, m_vertexShader, "Vertex shader");
    
    // Create and compile fragment shader
    m_fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    compileShader(fragmentShaderSource, m_fragmentShader, "Fragment shader");
    
    // Link the program
    linkShaders();
}

void Shader::compileShader(const GLchar* shaderSource, GLuint shaderID, const std::string& shaderName) {
    GLint success;
    GLchar infoLog[GL_INFO_LOG_LENGTH];
    
    // Compile the shader
    glShaderSource(shaderID, 1, &shaderSource, NULL);
    glCompileShader(shaderID);
    
    // Check for compilation errors
    glGetShaderiv(shaderID, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(shaderID, GL_INFO_LOG_LENGTH, NULL, infoLog);
        std::cout << shaderName << " failed to compile: " << infoLog << "\n";
    }
}

void Shader::linkShaders() {
    GLint success;
    GLchar infoLog[GL_INFO_LOG_LENGTH];
    
    // Create the program
    m_program = glCreateProgram();
    
    // Attach shaders to program
    glAttachShader(m_program, m_vertexShader);
    glAttachShader(m_program, m_fragmentShader);
    
    // Link the program
    glLinkProgram(m_program);
    
    // Check if linking succeeded
    glGetProgramiv(m_program, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(m_program, GL_INFO_LOG_LENGTH, NULL, infoLog);
        std::cout << "Shader program failed to link: " << infoLog << "\n";
    }
    
    // Delete shaders after linking
    glDeleteShader(m_vertexShader);
    glDeleteShader(m_fragmentShader);
}

const GLchar* Shader::loadSourceFromFile(const std::string shaderPath) {
    std::string shaderCode;
    
    // Open the file for reading
    std::ifstream shaderFile;
    shaderFile.open(shaderPath);
    std::stringstream shaderStream;
    
    // Read the file's buffer content into the stream
    shaderStream << shaderFile.rdbuf();
    
    // Close the file
    shaderFile.close();
    
    // Convert the stream to GLchar array
    shaderCode = shaderStream.str();
    const GLchar* code = shaderCode.c_str();
    
    return code;
}

void Shader::use() {
    glUseProgram(m_program);
}