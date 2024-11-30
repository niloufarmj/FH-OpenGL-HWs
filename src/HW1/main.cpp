#include <glad/glad.h>
#include <glfw/glfw3.h>
#include <iostream>
#include <vector>

void framebufferSizeCallback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);

const unsigned int WIDTH = 800;
const unsigned int HEIGHT = 600;

class Triangle {
public:
    Triangle(GLfloat* vertices) {
        this->vertices = vertices;
        initBuffers();
    }

    void draw() const {
        glBindVertexArray(vao);
        glDrawArrays(GL_TRIANGLES, 0, 3);
    }

private:
    GLfloat* vertices;
    unsigned int vbo, vao;

    void initBuffers() {
        glGenVertexArrays(1, &vao);
        glBindVertexArray(vao);

        glGenBuffers(1, &vbo);
        glBindBuffer(GL_ARRAY_BUFFER, vbo);
        glBufferData(GL_ARRAY_BUFFER, 9 * sizeof(GLfloat), vertices, GL_STATIC_DRAW);

        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);

        glBindVertexArray(0); // disable VBO
    }
};

void renderScene(const std::vector<Triangle>& triangles) {
    glClearColor(1.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    glColor3f(0.0f, 1.0f, 0.0f); // green
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

    // Define vertices for three triangles
    GLfloat vertices1[] = {
        -0.9f, -0.9f, 0.0f,  // bottom left
        -0.5f, -0.9f, 0.0f,  // bottom right
        -0.7f, -0.5f, 0.0f   // top
    };

    GLfloat vertices2[] = {
        0.5f, -0.9f, 0.0f,   // bottom left
        0.9f, -0.9f, 0.0f,   // bottom right
        0.7f, -0.5f, 0.0f    // top
    };

    GLfloat vertices3[] = {
        -0.2f, 0.5f, 0.0f,   // bottom left
        0.2f, 0.5f, 0.0f,    // bottom right
        0.0f, 0.9f, 0.0f     // top
    };

    std::vector<Triangle> triangles;
    triangles.emplace_back(vertices1);
    triangles.emplace_back(vertices2);
    triangles.emplace_back(vertices3);

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