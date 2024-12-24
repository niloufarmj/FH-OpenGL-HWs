#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <util/shader.h>
#include <util/camera.h>
#include <util/model.h>
#include <util/assets.h>
#include <util/window.h>

#include <iostream>
#include "callbacks.h"
#include "rendering.h"
#include "settings.h"
#include "input.h"

Camera camera(initialPosition, glm::vec3(0.0f, -1.0f, 0.0f), initialYaw, initialPitch);
float lastX = (float)SCR_WIDTH / 2.0f;
float lastY = (float)SCR_HEIGHT / 2.0f;
bool firstMouse = true;
bool leftButtonDown = false;
bool middleButtonDown = false;
bool rightButtonDown = false;

float deltaTime = 0.0f;
float lastFrame = 0.0f;

const char *APP_NAME = "postprocessing";
int effectIndex = 0; // 0 for None, 1 for Bloom

int main()
{
    glm::vec4 bgColor = {0.1, 0.1, 0.1, 1.0};
    bool showWireframe = false;
    bool rotateModel = false;

    InitWindowAndGUI(SCR_WIDTH, SCR_HEIGHT, APP_NAME, false);
    glViewport(0, 0, SCR_WIDTH, SCR_HEIGHT);

    std::cout << SCR_WIDTH << " " << SCR_HEIGHT << std::endl;

    SetCursorPosCallback(mouse_callback);
    SetMouseButtonCallback(mouse_button_callback);
    SetScrollCallback(scroll_callback);
    SetFramebufferSizeCallback(framebuffer_size_callback);

    glEnable(GL_DEPTH_TEST);

    const std::string SRC = "../src/HW3/";

    Shader modelShader(SRC + "model.vs.glsl", SRC + "model.fs.glsl");
    Shader brightExtractShader(SRC + "shader.vs.glsl", SRC + "brightExtract.fs.glsl");
    Shader blurShader(SRC + "shader.vs.glsl", SRC + "blur.fs.glsl");
    Shader bloomShader(SRC + "shader.vs.glsl", SRC + "bloom.fs.glsl");
    Shader screenShader(SRC + "shader.vs.glsl", SRC + "screenshader.fs.glsl");

    Shader *activeShader = &screenShader;

    Model myModel("../resources/objects/jesus/scene.gltf", true);

    modelShader.use();
    modelShader.setInt("texture1", 0);

    activeShader->use();
    activeShader->setInt("screenTexture", 0);

    // Create framebuffer for HDR rendering
    unsigned int hdrFBO;
    glGenFramebuffers(1, &hdrFBO);
    glBindFramebuffer(GL_FRAMEBUFFER, hdrFBO);

    unsigned int colorBuffers[2];
    glGenTextures(2, colorBuffers);
    for (unsigned int i = 0; i < 2; i++) {
        glBindTexture(GL_TEXTURE_2D, colorBuffers[i]);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB16F, SCR_WIDTH, SCR_HEIGHT, 0, GL_RGB, GL_FLOAT, NULL);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + i, GL_TEXTURE_2D, colorBuffers[i], 0);
    }
    unsigned int rboDepth;
    glGenRenderbuffers(1, &rboDepth);
    glBindRenderbuffer(GL_RENDERBUFFER, rboDepth);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, SCR_WIDTH, SCR_HEIGHT);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, rboDepth);

    unsigned int attachments[2] = { GL_COLOR_ATTACHMENT0, GL_COLOR_ATTACHMENT1 };
    glDrawBuffers(2, attachments);

    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
        std::cout << "Framebuffer not complete!" << std::endl;
    glBindFramebuffer(GL_FRAMEBUFFER, 0);

    // Ping-pong framebuffers for blurring
    unsigned int pingpongFBO[2];
    unsigned int pingpongColorbuffers[2];
    glGenFramebuffers(2, pingpongFBO);
    glGenTextures(2, pingpongColorbuffers);
    for (unsigned int i = 0; i < 2; i++) {
        glBindFramebuffer(GL_FRAMEBUFFER, pingpongFBO[i]);
        glBindTexture(GL_TEXTURE_2D, pingpongColorbuffers[i]);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB16F, SCR_WIDTH, SCR_HEIGHT, 0, GL_RGB, GL_FLOAT, NULL);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, pingpongColorbuffers[i], 0);

        if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
            std::cout << "Framebuffer not complete!" << std::endl;
    }

    while (!glfwWindowShouldClose(window))
    {
        float currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        glfwPollEvents();
        processInput(window);

        if (gui)
        {
            ImGui_ImplOpenGL3_NewFrame();
            ImGui_ImplGlfw_NewFrame();
            ImGui::NewFrame();

            ImGui::Begin(APP_NAME);
            ImGui::Text("FPS: %.1f", ImGui::GetIO().Framerate);
            ImGui::ColorEdit3("clear color", (float *)&bgColor.x);
            ImGui::Checkbox("rotate model", &rotateModel);
            ImGui::Checkbox("show wireframe", &showWireframe);

            if (ImGui::Button("reload shaders"))
            {
                modelShader.reload();
                modelShader.use();
                modelShader.setInt("texture1", 0);
                activeShader->reload();
                activeShader->use();
                activeShader->setInt("screenTexture", 0);
            }

            ImGui::Text("Effects");
            ImGui::SameLine();
            const char* effects[] = { "None", "Bloom" };
            ImGui::Combo(" ", &effectIndex, effects, IM_ARRAYSIZE(effects));

            ImGui::End();
            ImGui::Render();
        }

        // 1. Render scene into floating point framebuffer
        glBindFramebuffer(GL_FRAMEBUFFER, hdrFBO);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        modelShader.use();
        glm::mat4 model = glm::mat4(1.0f);
        if (rotateModel)
            model = glm::rotate(model, currentFrame, glm::vec3(0, 1, 0));
        glm::mat4 view = camera.GetViewMatrix();
        glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
        modelShader.setMat4("model", model);
        modelShader.setMat4("view", view);
        modelShader.setMat4("projection", projection);
        myModel.Draw(modelShader);
        glBindFramebuffer(GL_FRAMEBUFFER, 0);

        if (effectIndex == 1) // Bloom effect
        {
            // 2. Extract bright areas
            glBindFramebuffer(GL_FRAMEBUFFER, pingpongFBO[0]);
            glClear(GL_COLOR_BUFFER_BIT);
            brightExtractShader.use();
            glBindTexture(GL_TEXTURE_2D, colorBuffers[0]);
            renderQuad();
            glBindFramebuffer(GL_FRAMEBUFFER, 0);

            // 3. Blur bright areas
            bool horizontal = true, first_iteration = true;
            unsigned int amount = 10;
            blurShader.use();
            for (unsigned int i = 0; i < amount; i++) {
                glBindFramebuffer(GL_FRAMEBUFFER, pingpongFBO[horizontal]);
                blurShader.setInt("horizontal", horizontal);
                glBindTexture(GL_TEXTURE_2D, first_iteration ? colorBuffers[1] : pingpongColorbuffers[!horizontal]);
                renderQuad();
                horizontal = !horizontal;
                if (first_iteration)
                    first_iteration = false;
            }
            glBindFramebuffer(GL_FRAMEBUFFER, 0);

            // 4. Render to screen with bloom
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
            bloomShader.use();
            glBindTexture(GL_TEXTURE_2D, colorBuffers[0]);
            glActiveTexture(GL_TEXTURE1);
            glBindTexture(GL_TEXTURE_2D, pingpongColorbuffers[!horizontal]);
            renderQuad();
        }
        else // Normal effect
        {
            // Render to screen without bloom
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
            activeShader->use();
            glBindTexture(GL_TEXTURE_2D, colorBuffers[0]);
            renderQuad();
        }

        if (showWireframe)
            glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

        if (gui)
            ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        glfwSwapBuffers(window);
    }

    glfwTerminate();
    return 0;
}