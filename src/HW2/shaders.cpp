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

void checkCompileErrors(unsigned int shader, std::string type) {
    int success;
    char infoLog[1024];
    if (type != "PROGRAM") {
        glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
        if (!success) {
            glGetShaderInfoLog(shader, 1024, NULL, infoLog);
            std::cerr << "ERROR::SHADER_COMPILATION_ERROR of type: " << type << "\n" << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
        }
    } else {
        glGetProgramiv(shader, GL_LINK_STATUS, &success);
        if (!success) {
            glGetProgramInfoLog(shader, 1024, NULL, infoLog);
            std::cerr << "ERROR::PROGRAM_LINKING_ERROR of type: " << type << "\n" << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
        }
    }
}

unsigned int loadShaders(const char* vertexPath, const char* fragmentPath) {
    std::string vertexShaderString = loadFile(vertexPath);
    std::string fragmentShaderString = loadFile(fragmentPath);

    if (vertexShaderString.empty() || fragmentShaderString.empty()) {
        return -1;
    }

    // vertex shader
    const char *vertexShaderCStr = vertexShaderString.c_str();
    unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderCStr, NULL);
    glCompileShader(vertexShader);
    checkCompileErrors(vertexShader, "VERTEX");

    // fragment shader
    const char *fragmentShaderCStr = fragmentShaderString.c_str();
    unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderCStr, NULL);
    glCompileShader(fragmentShader);
    checkCompileErrors(fragmentShader, "FRAGMENT");

    // link shaders
    unsigned int shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);
    checkCompileErrors(shaderProgram, "PROGRAM");

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    return shaderProgram;
}