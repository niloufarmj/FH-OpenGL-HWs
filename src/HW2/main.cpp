#include <glad/glad.h>
#include <glfw/glfw3.h>
#include "Shapes.h"
#include <iostream>
#include <vector>
#include "Triangle.h"
#include "shaders.h"


void framebufferSizeCallback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
bool isMouseOverBloom(const Circle& bloom, double mouseX, double mouseY, int windowWidth, int windowHeight);

const unsigned int WIDTH = 850;
const unsigned int HEIGHT = 850;

double mouseX, mouseY;
extern Tree tree; // Use the existing tree from shapes.cpp

void renderScene(const std::vector<Triangle>& triangles) {
    glClearColor(0.956f, 0.8f, 0.792f, 1.0f); // Set background color
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
    GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "Sakura", NULL, NULL);
    if (window == NULL) {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebufferSizeCallback);
    glfwSetCursorPosCallback(window, mouse_callback);

    // Initialize GLAD
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    // Load shaders
    unsigned int shaderProgram = loadShaders("D:/FH Uni/rtg/Exercise1-Draw2DScene-VBOVAO/src/HW1/colorShader.vert",
                                             "D:/FH Uni/rtg/Exercise1-Draw2DScene-VBOVAO/src/HW1/colorShader.frag");
    glUseProgram(shaderProgram);

    // Create the scene
    std::vector<Triangle> sceneTriangles = createScene();
    std::vector<Triangle> bloomTriangles = creatBloomsSeperately(tree);
    std::vector<Triangle> triangles;

    // Main Loop
    while (!glfwWindowShouldClose(window)) {
        processInput(window);

        // Clear the screen
        glClear(GL_COLOR_BUFFER_BIT);

        // Update and draw the single bloom
        Bloom& bloom = tree.blooms[30];
        if (isMouseOverBloom(bloom.cirecleData, mouseX, mouseY, WIDTH, HEIGHT)) {
            bloom.dynamicRotation += 0.01f; // Adjust rotation speed as needed

            // Clear and reuse the bloomTriangles vector
            bloomTriangles.clear();
            bloomTriangles = creatBloomsSeperately(tree);
        }

        // Render the static parts of the scene
        triangles = sceneTriangles;
        triangles.insert(triangles.end(), bloomTriangles.begin(), bloomTriangles.end());

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

void mouse_callback(GLFWwindow* window, double xpos, double ypos) {
    mouseX = xpos;
    mouseY = ypos;
}

bool isMouseOverBloom(const Circle& bloom, double mouseX, double mouseY, int windowWidth, int windowHeight) {
    // Convert mouse coordinates to normalized device coordinates (NDC)
    float x = static_cast<float>((2.0 * mouseX) / windowWidth - 1.0);
    float y = static_cast<float>(1.0 - (2.0 * mouseY) / windowHeight);

    // Check if the mouse is within the bloom's radius
    float dx = x - bloom.center[0];
    float dy = y - bloom.center[1];
    return (dx * dx + dy * dy) <= (bloom.radius * bloom.radius);
}