#include <glad/glad.h>
#include <glfw/glfw3.h>
#include "Shapes.h"
#include <iostream>
#include <random>
#include <vector>
#include "Triangle.h"
#include "shaders.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

void framebufferSizeCallback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
bool isMouseOverBloom(const Circle& bloom, double mouseX, double mouseY, int windowWidth, int windowHeight);

const unsigned int WIDTH = 850;
const unsigned int HEIGHT = 850;

double mouseX, mouseY;
extern Tree tree; // Use the existing tree from shapes.cpp
extern std::vector<Bloom> fallingBlooms;

// Store initial positions of falling blooms
std::vector<glm::vec3> initialPositions;

void renderScene(const std::vector<Triangle>& triangles) {
    glClearColor(0.956f, 0.8f, 0.792f, 1.0f); // Set background color
    glClear(GL_COLOR_BUFFER_BIT);

    for (const auto& triangle : triangles) {
        triangle.draw();
    }
}

void renderBloom(const std::vector<Triangle>& triangles, const glm::mat4& transform) {
    for (const auto& triangle : triangles) {
        triangle.draw(transform);
    }
}

void updateAndRenderFallingBlooms(std::vector<Bloom>& blooms, std::vector<std::vector<Triangle>>& bloomTriangles, std::vector<glm::vec3>& initialPositions, std::uniform_real_distribution<>& dis, std::mt19937& gen) {
    for (size_t i = 0; i < blooms.size(); ++i) {
        Bloom& bloom = blooms[i];
        glm::mat4 transform = glm::mat4(1.0f);

        // Update bloom position
        bloom.cirecleData.center[1] -= dis(gen); // Adjust falling speed as needed

        // Respawn bloom if it goes off the screen
        if (bloom.cirecleData.center[1] < -1.1f) {
            bloom.cirecleData.center[1] = initialPositions[i].y;
            bloom.cirecleData.center[0] = initialPositions[i].x;
        }

        // Apply the final translation to the current position
        transform = glm::translate(transform, glm::vec3(0.0f, bloom.cirecleData.center[1], bloom.cirecleData.center[2]));

        renderBloom(bloomTriangles[i], transform);
    }
}

void updateAndRenderRotatingBlooms(std::vector<Bloom>& blooms, std::vector<std::vector<Triangle>>& bloomTriangles) {
    for (size_t i = 0; i < blooms.size(); ++i) {
        Bloom& bloom = blooms[i];
        glm::mat4 transform = glm::mat4(1.0f);
        if (isMouseOverBloom(bloom.cirecleData, mouseX, mouseY, WIDTH, HEIGHT)) {
            bloom.dynamicRotation += 0.02f;
        }
        transform = glm::translate(transform, glm::vec3(bloom.cirecleData.center[0], bloom.cirecleData.center[1], bloom.cirecleData.center[2]));
        transform = glm::rotate(transform, bloom.dynamicRotation, glm::vec3(0.0f, 0.0f, 1.0f));
        transform = glm::translate(transform, -glm::vec3(bloom.cirecleData.center[0], bloom.cirecleData.center[1], bloom.cirecleData.center[2]));

        renderBloom(bloomTriangles[i], transform);
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
    unsigned int shaderProgram = loadShaders("D:/FH Uni/rtg/Exercise1-Draw2DScene-VBOVAO/src/HW2/transform.vert",
                                             "D:/FH Uni/rtg/Exercise1-Draw2DScene-VBOVAO/src/HW2/transform.frag");
    glUseProgram(shaderProgram);

    // Load cursor image
    int cursorWidth, cursorHeight, cursorChannels;
    unsigned char* cursorImage = stbi_load("D:/FH Uni/rtg/Exercise1-Draw2DScene-VBOVAO/src/HW2/curser.png", &cursorWidth, &cursorHeight, &cursorChannels, 4);
    if (!cursorImage) {
        std::cerr << "Failed to load cursor image" << std::endl;
        return -1;
    }

    // Create GLFW image
    GLFWimage glfwImage;
    glfwImage.width = cursorWidth;
    glfwImage.height = cursorHeight;
    glfwImage.pixels = cursorImage;

    // Create GLFW cursor
    GLFWcursor* cursor = glfwCreateCursor(&glfwImage, 0, 0);
    if (!cursor) {
        std::cerr << "Failed to create GLFW cursor" << std::endl;
        stbi_image_free(cursorImage);
        return -1;
    }

    // Set the cursor for the window
    glfwSetCursor(window, cursor);

    // Create the scene
    std::vector<Triangle> sceneTriangles = createScene();
    std::vector<std::vector<Triangle>> allBloomTriangles = creatBloomsSeperately(tree.blooms);
    std::vector<std::vector<Triangle>> fallingBloomsTriangles = creatBloomsSeperately(fallingBlooms);

    // Store initial positions of falling blooms
    for (const auto& bloom : fallingBlooms) {
        initialPositions.push_back(glm::vec3(bloom.cirecleData.center[0], bloom.cirecleData.center[1], bloom.cirecleData.center[2]));
    }

    // Create a random number generator
    std::random_device rd;  // Obtain a random number from hardware
    std::mt19937 gen(rd()); // Seed the generator

    // Define the range
    std::uniform_real_distribution<> dis(0, 0.002); // Range [-0.02, 0.02]

    // Main Loop
    while (!glfwWindowShouldClose(window)) {
        
        processInput(window);

        // Clear the screen
        glClear(GL_COLOR_BUFFER_BIT);

        // Static scene
        renderScene(sceneTriangles);

        updateAndRenderRotatingBlooms(tree.blooms, allBloomTriangles);

        updateAndRenderFallingBlooms(fallingBlooms, fallingBloomsTriangles, initialPositions, dis, gen);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // Clean up
    glfwDestroyCursor(cursor);
    stbi_image_free(cursorImage);
    glfwTerminate();
    return 0;
}

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
    return (dx * dx + dy * dy) <= (bloom.radius * bloom.radius * 30);
}