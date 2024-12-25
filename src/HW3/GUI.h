#ifndef GUI_H
#define GUI_H

#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>
#include <glm/glm.hpp>
#include <util/shader.h>
#include <GLFW/glfw3.h>

class GUI {
public:
    GUI(const char* appName, glm::vec4& bgColor, bool& rotateModel, bool& showWireframe, int& effectIndex, Shader& modelShader, Shader*& activeShader, GLFWwindow* window);
    void Init();
    void Render();
    void Cleanup();

private:
    const char* appName;
    glm::vec4& bgColor;
    bool& rotateModel;
    bool& showWireframe;
    int& effectIndex;
    Shader& modelShader;
    Shader*& activeShader;
    GLFWwindow* window;
    bool initialized = false; // Flag to check if ImGui is initialized
};

#endif // GUI_H