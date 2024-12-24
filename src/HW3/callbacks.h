#ifndef CALLBACKS_H
#define CALLBACKS_H

#include <GLFW/glfw3.h>
#include <iostream>
#include "settings.h"

extern Camera camera;
extern float lastX, lastY;
extern bool firstMouse, leftButtonDown, middleButtonDown, rightButtonDown;

void framebuffer_size_callback(GLFWwindow *window, int width, int height)
{
    glViewport(0, 0, width, height);
    std::cout << "size_callback: " << width << " " << height << std::endl;
}

void mouse_callback(GLFWwindow *window, double xpos, double ypos)
{
    if (firstMouse)
    {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos;

    lastX = xpos;
    lastY = ypos;

    if (leftButtonDown)
        camera.ProcessMouseMovement(xoffset, yoffset);
}

void scroll_callback(GLFWwindow *window, double xoffset, double yoffset)
{
    camera.ProcessMouseScroll(yoffset);
}

void mouse_button_callback(GLFWwindow *window, int button, int action, int mods)
{
    if (action == GLFW_PRESS)
    {
        if (button == GLFW_MOUSE_BUTTON_LEFT)
            leftButtonDown = true;
        if (button == GLFW_MOUSE_BUTTON_MIDDLE)
            middleButtonDown = true;
        if (button == GLFW_MOUSE_BUTTON_RIGHT)
            rightButtonDown = true;
    }
    else if (action == GLFW_RELEASE)
    {
        if (button == GLFW_MOUSE_BUTTON_LEFT)
            leftButtonDown = false;
        if (button == GLFW_MOUSE_BUTTON_MIDDLE)
            middleButtonDown = false;
        if (button == GLFW_MOUSE_BUTTON_RIGHT)
            rightButtonDown = false;
    }
}

#endif // CALLBACKS_H