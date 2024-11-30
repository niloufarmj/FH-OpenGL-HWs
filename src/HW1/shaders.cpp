#include "shaders.h"
#include <glad/glad.h>
#include <iostream>
#include <fstream>
#include <sstream>

std::string loadFile(const char *fname) {
    std::ifstream file(fname);
    if (!file.is_open()) {
        std::cout << "Unable to open file " << fname << std::endl;
        exit(1);
    }

    std::stringstream fileData;
    fileData << file.rdbuf();
    file.close();

    return fileData.str();
}

unsigned int loadShaders(const char* vertexPath, const char* fragmentPath) {
    int vlength, flength;

    std::string vertexShaderString = loadFile(vertexPath);
    std::string fragmentShaderString = loadFile(fragmentPath);
    vlength = vertexShaderString.length();
    flength = fragmentShaderString.length();

    if (vertexShaderString.empty() || fragmentShaderString.empty()) {
        return -1;
    }

    // vertex shader
    const char *vertexShaderCStr = vertexShaderString.c_str();
    unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderCStr, &vlength);
    glCompileShader(vertexShader);

    // check for shader compile errors
    int success;
    char infoLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    // fragment shader
    const char *fragmentShaderCStr = fragmentShaderString.c_str();
    unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderCStr, &flength);
    glCompileShader(fragmentShader);

    // check for shader compile errors
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    // link shaders
    unsigned int shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    // check for linking errors
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
    }

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    return shaderProgram;
}