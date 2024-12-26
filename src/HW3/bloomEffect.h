#ifndef BLOOM_EFFECT_H
#define BLOOM_EFFECT_H

#include "Effect.h"
#include "Framebuffer.h"
#include "BrightExtractEffect.h"
#include "BlurEffect.h"

class BloomEffect : public Effect {
public:
    Framebuffer& framebuffer;
    BrightExtractEffect& brightExtractEffect;
    BlurEffect& blurEffect;
    Shader& bloomShader;
    unsigned int amount;

    BloomEffect(Framebuffer& framebuffer, BrightExtractEffect& brightExtractEffect, BlurEffect& blurEffect, Shader& bloomShader, unsigned int amount = 10)
        : framebuffer(framebuffer), brightExtractEffect(brightExtractEffect), blurEffect(blurEffect), bloomShader(bloomShader), amount(amount) {}

    void apply(Shader& shader, unsigned int texture, unsigned int width, unsigned int height, float kernelSize) override {
        // 1. Extract bright areas
        brightExtractEffect.apply(brightExtractEffect.shader, texture, width, height, kernelSize);

        // 2. Blur bright areas
        blurEffect.apply(blurEffect.shader, framebuffer.pingpongColorbuffers[0], width, height, kernelSize);

        // 3. Render to screen with bloom
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        bloomShader.use();
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, framebuffer.colorBuffers[0]);
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, framebuffer.pingpongColorbuffers[0]);
        bloomShader.setInt("scene", 0);
        bloomShader.setInt("bloomBlur", 1);
        renderQuad();
    }
};

#endif // BLOOM_EFFECT_H