
#include <glad/glad.h>
#include <glfw/glfw3.h>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>

void framebufferSizeCallback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);

const unsigned int WIDTH = 800;
const unsigned int HEIGHT = 600;

class Triangle {
public:
    Triangle(GLfloat* vertices, GLfloat* color) {
        this->vertices = vertices;
        this->color = color;
        initBuffers();
    }

    void draw() const {
        glBindVertexArray(vao);
        glDrawArrays(GL_TRIANGLES, 0, 3);
    }

private:
    GLfloat* vertices;
    GLfloat* color;
    unsigned int vbo[2], vao;

    void initBuffers() {
        glGenVertexArrays(1, &vao);
        glBindVertexArray(vao);

        glGenBuffers(2, vbo);

        // Vertex buffer
        glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
        glBufferData(GL_ARRAY_BUFFER, 9 * sizeof(GLfloat), vertices, GL_STATIC_DRAW);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);

        // Color buffer
        GLfloat colors[9] = { color[0], color[1], color[2], color[0], color[1], color[2], color[0], color[1], color[2] };
        glBindBuffer(GL_ARRAY_BUFFER, vbo[1]);
        glBufferData(GL_ARRAY_BUFFER, 9 * sizeof(GLfloat), colors, GL_STATIC_DRAW);
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, NULL);

        glBindVertexArray(0); // disable VBO
    }
};

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

unsigned int loadShaders() {
    int vlength, flength;

    std::string vertexShaderString = loadFile("D:/FH Uni/rtg/Exercise1-Draw2DScene-VBOVAO/src/HW1/colorShader.vert");
    std::string fragmentShaderString = loadFile("D:/FH Uni/rtg/Exercise1-Draw2DScene-VBOVAO/src/HW1/colorShader.frag");
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

void renderScene(const std::vector<Triangle>& triangles) {
    glClearColor(1.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    for (const auto& triangle : triangles) {
        triangle.draw();
    }
}

int main() {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_COMPAT_PROFILE);

    // GLFW Window
    GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "Triangle Example", NULL, NULL);
    if (window == NULL) {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebufferSizeCallback);

    // Initialize GLAD
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    // Load shaders
    unsigned int shaderProgram = loadShaders();
    glUseProgram(shaderProgram);

    // Define vertices and colors for three triangles
    GLfloat vertices1[] = {
        -0.9f, -0.9f, 0.0f,  // bottom left
        -0.5f, -0.9f, 0.0f,  // bottom right
        -0.7f, -0.5f, 0.0f   // top
    };
    GLfloat color1[] = { 0.7f, 0.3f, 0.1f };  // red

    GLfloat vertices2[] = {
        0.5f, -0.9f, 0.0f,   // bottom left
        0.9f, -0.9f, 0.0f,   // bottom right
        0.7f, -0.5f, 0.0f    // top
    };
    GLfloat color2[] = { 1.0f, 1.0f, 0.0f };  // yellow

    GLfloat vertices3[] = {
        -0.2f, 0.5f, 0.0f,   // bottom left
        0.2f, 0.5f, 0.0f,    // bottom right
        0.0f, 0.9f, 0.0f     // top
    };
    GLfloat color3[] = { 0.5f, 0.5f, 0.5f };  // gray

    std::vector<Triangle> triangles;
    triangles.emplace_back(vertices1, color1);
    triangles.emplace_back(vertices2, color2);
    triangles.emplace_back(vertices3, color3);

    // Main Loop
    while (!glfwWindowShouldClose(window)) {
        processInput(window);
        renderScene(triangles);
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}

// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow* window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

void framebufferSizeCallback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}