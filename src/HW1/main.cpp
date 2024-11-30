#include <glad/glad.h>
#include <glfw/glfw3.h>
#include <iostream>
#include <vector>
#include "Triangle.h"
#include "shaders.h"

void framebufferSizeCallback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);

const unsigned int WIDTH = 800;
const unsigned int HEIGHT = 600;

void renderScene(const std::vector<Triangle>& triangles) {
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // Set background color to black
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
    unsigned int shaderProgram = loadShaders("D:/FH Uni/rtg/Exercise1-Draw2DScene-VBOVAO/src/HW1/colorShader.vert",
                                             "D:/FH Uni/rtg/Exercise1-Draw2DScene-VBOVAO/src/HW1/colorShader.frag");
    glUseProgram(shaderProgram);

    // Define vertices and colors for three triangles
    GLfloat vertices1[] = {
        -0.9f, -0.9f, 0.0f,  // bottom left
        -0.5f, -0.9f, 0.0f,  // bottom right
        -0.7f, -0.5f, 0.0f   // top
    };
    GLfloat color1[] = { 1.0f, 0.0f, 0.0f };  // red

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