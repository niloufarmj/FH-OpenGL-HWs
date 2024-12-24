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
    Shader screenShader(SRC + "screenshader.vs.glsl", SRC + "screenshader.fs.glsl");

    Shader *activeShader = &screenShader;

    Model myModel("../resources/objects/jesus/scene.gltf", true);

    modelShader.use();
    modelShader.setInt("texture1", 0);

    activeShader->use();
    activeShader->setInt("screenTexture", 0);

    unsigned int framebuffer;
    glGenFramebuffers(1, &framebuffer);
    glBindFramebuffer(GL_FRAMEBUFFER, framebuffer);
    unsigned int textureColorbuffer;
    glGenTextures(1, &textureColorbuffer);
    glBindTexture(GL_TEXTURE_2D, textureColorbuffer);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, SCR_WIDTH, SCR_HEIGHT, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, textureColorbuffer, 0);
    unsigned int rbo;
    glGenRenderbuffers(1, &rbo);
    glBindRenderbuffer(GL_RENDERBUFFER, rbo);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, SCR_WIDTH, SCR_HEIGHT);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, rbo);
    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
        std::cout << "ERROR::FRAMEBUFFER:: Framebuffer is not complete!" << std::endl;
    glBindFramebuffer(GL_FRAMEBUFFER, 0);

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

            ImGui::End();
            ImGui::Render();
        }

        glBindFramebuffer(GL_FRAMEBUFFER, framebuffer);
        glEnable(GL_DEPTH_TEST);

        glClearColor(bgColor.r, bgColor.g, bgColor.b, bgColor.a);
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
        glDisable(GL_DEPTH_TEST);
        glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        if (showWireframe)
            glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

        activeShader->use();
        auto randomNumber = ((double)rand() / (RAND_MAX));
        activeShader->setFloat("randomNumber", randomNumber);
        activeShader->setFloat("timer", currentFrame);
        glBindTexture(GL_TEXTURE_2D, textureColorbuffer);
        renderQuad();

        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        if (gui)
            ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        glfwSwapBuffers(window);
    }

    glfwTerminate();
    return 0;
}