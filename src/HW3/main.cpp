#include "common.h"


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
int effectIndex = 0; // 0 for None, 1 for Blur, 2 for BrightExtract, 3 for Bloom
float kernelSize = 1.0f; // Initial value

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

    // Create framebuffer object
    Framebuffer framebuffer(SCR_WIDTH, SCR_HEIGHT);

    // Create effect objects
    BlurEffect blurEffect(framebuffer, blurShader);
    BrightExtractEffect brightExtractEffect(framebuffer, brightExtractShader);
    BloomEffect bloomEffect(framebuffer, brightExtractEffect, blurEffect, bloomShader);

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
            const char* effects[] = { "None", "Blur", "BrightExtract", "Bloom" };
            ImGui::Combo(" ", &effectIndex, effects, IM_ARRAYSIZE(effects));

            ImGui::SliderFloat("Kernel Size", &kernelSize, 1.0f, 10.0f);

            ImGui::End();
            ImGui::Render();
        }

        // 1. Render scene into floating point framebuffer
        glBindFramebuffer(GL_FRAMEBUFFER, framebuffer.FBO);
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

        if (effectIndex == 1) // Blur effect
        {
            blurEffect.apply(blurShader, framebuffer.colorBuffers[0], SCR_WIDTH, SCR_HEIGHT, kernelSize);

            // Render to screen with blur
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
            activeShader->use();
            glBindTexture(GL_TEXTURE_2D, framebuffer.pingpongColorbuffers[0]);
            renderQuad();
        }
        else if (effectIndex == 2) // Bright Extract effect
        {
            brightExtractEffect.apply(brightExtractShader, framebuffer.colorBuffers[0], SCR_WIDTH, SCR_HEIGHT, kernelSize);

            // Render the bright extract output to the screen for debugging
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
            activeShader->use();
            glBindTexture(GL_TEXTURE_2D, framebuffer.pingpongColorbuffers[0]);
            renderQuad();
        }
        else if (effectIndex == 3) // Bloom effect
        {
            bloomEffect.apply(bloomShader, framebuffer.colorBuffers[0], SCR_WIDTH, SCR_HEIGHT, kernelSize);

            
        }
        else // Normal effect
        {
            // Render to screen without blur, bloom, or fog
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
            activeShader->use();
            glBindTexture(GL_TEXTURE_2D, framebuffer.colorBuffers[0]);
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