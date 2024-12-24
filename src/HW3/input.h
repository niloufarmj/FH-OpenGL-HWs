#ifndef INPUT_H
#define INPUT_H

#include <GLFW/glfw3.h>
#include "settings.h"

extern Camera camera;
extern float deltaTime;

void PrintCameraPositionAndOrientation(const Camera& camera)
{
    std::cout << "Camera Position: (" << camera.Position.x << ", " << camera.Position.y << ", " << camera.Position.z << ")\n";
    std::cout << "Camera Yaw: " << camera.Yaw << "\n";
    std::cout << "Camera Pitch: " << camera.Pitch << "\n";
}


void processInput(GLFWwindow *window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        camera.ProcessKeyboard(FORWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        camera.ProcessKeyboard(BACKWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        camera.ProcessKeyboard(LEFT, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        camera.ProcessKeyboard(RIGHT, deltaTime);

    if (glfwGetKey(window, GLFW_KEY_P) == GLFW_PRESS)
    {
        PrintCameraPositionAndOrientation(camera);
    }
}

#endif // INPUT_H