#include "GUI.h"

GUI::GUI(const char* appName, glm::vec4& bgColor, bool& rotateModel, bool& showWireframe, int& effectIndex, Shader& modelShader, Shader*& activeShader, GLFWwindow* window)
    : appName(appName), bgColor(bgColor), rotateModel(rotateModel), showWireframe(showWireframe), effectIndex(effectIndex), modelShader(modelShader), activeShader(activeShader), window(window) {}

void GUI::Init() {
    if (!initialized) {
        ImGui::CreateContext();
        ImGui_ImplGlfw_InitForOpenGL(window, true);
        ImGui_ImplOpenGL3_Init("#version 330");
        ImGui::StyleColorsDark();
        initialized = true;
    }
}

void GUI::Render() {
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    ImGui::Begin(appName);
    ImGui::Text("FPS: %.1f", ImGui::GetIO().Framerate);
    ImGui::ColorEdit3("clear color", (float*)&bgColor.x);
    ImGui::Checkbox("rotate model", &rotateModel);
    ImGui::Checkbox("show wireframe", &showWireframe);

    if (ImGui::Button("reload shaders")) {
        modelShader.reload();
        modelShader.use();
        modelShader.setInt("texture1", 0);
        activeShader->reload();
        activeShader->use();
        activeShader->setInt("screenTexture", 0);
    }

    ImGui::Text("Effects");
    ImGui::SameLine();
    const char* effects[] = { "None", "Blur", "Bloom" };
    ImGui::Combo(" ", &effectIndex, effects, IM_ARRAYSIZE(effects));

    ImGui::End();
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void GUI::Cleanup() {
    if (initialized) {
        ImGui_ImplOpenGL3_Shutdown();
        ImGui_ImplGlfw_Shutdown();
        ImGui::DestroyContext();
        initialized = false;
    }
}