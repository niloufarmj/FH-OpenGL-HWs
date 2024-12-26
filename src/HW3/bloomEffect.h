#ifndef BLOOM_EFFECT_H
#define BLOOM_EFFECT_H

#include "Effect.h"
#include "Framebuffer.h"

class BloomEffect : public Effect {
public:
    Framebuffer& framebuffer;
    Shader& brightExtractShader;
    Shader& blurShader;
    Shader& bloomShader;
    unsigned int amount;

    BloomEffect(Framebuffer& framebuffer, Shader& brightExtractShader, Shader& blurShader, Shader& bloomShader, unsigned int amount = 10)
        : framebuffer(framebuffer), brightExtractShader(brightExtractShader), blurShader(blurShader), bloomShader(bloomShader), amount(amount) {}

    void apply(Shader& shader, unsigned int texture, unsigned int width, unsigned int height) override {
        // 1. Extract bright areas
        glBindFramebuffer(GL_FRAMEBUFFER, framebuffer.pingpongFBO[0]);
        glClear(GL_COLOR_BUFFER_BIT);
        brightExtractShader.use();
        glBindTexture(GL_TEXTURE_2D, texture);
        renderQuad();
        glBindFramebuffer(GL_FRAMEBUFFER, 0);


        // 2. Blur bright areas
        bool horizontal = true, first_iteration = true;
        blurShader.use();
        blurShader.setVec2("pixelSize", glm::vec2(1.0f / width, 1.0f / height));
        for (unsigned int i = 0; i < amount; i++) {
            glBindFramebuffer(GL_FRAMEBUFFER, framebuffer.pingpongFBO[horizontal]);
            blurShader.setInt("horizontal", horizontal);
            glBindTexture(GL_TEXTURE_2D, first_iteration ? framebuffer.pingpongColorbuffers[0] : framebuffer.pingpongColorbuffers[!horizontal]);
            renderQuad();
            horizontal = !horizontal;
            if (first_iteration)
                first_iteration = false;
        }
        glBindFramebuffer(GL_FRAMEBUFFER, 0);


        // 3. Render to screen with bloom
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        bloomShader.use();
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, framebuffer.colorBuffers[0]);
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, framebuffer.pingpongColorbuffers[!horizontal]);
        bloomShader.setInt("scene", 0);
        bloomShader.setInt("bloomBlur", 1);
        renderQuad();
        }
};

#endif // BLOOM_EFFECT_H