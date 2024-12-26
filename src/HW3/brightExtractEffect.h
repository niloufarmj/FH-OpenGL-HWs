#ifndef BRIGHTEXTRACT_EFFECT_H
#define BRIGHTEXTRACT_EFFECT_H

#include "effect.h"
#include "framebuffer.h"

class BrightExtractEffect : public Effect {
public:
    Framebuffer& framebuffer;
    Shader& shader;

    BrightExtractEffect(Framebuffer& framebuffer, Shader& shader) 
        : framebuffer(framebuffer), shader(shader) {}

    void apply(Shader& shader, unsigned int texture, unsigned int width, unsigned int height, float kernelSize) override {
        glBindFramebuffer(GL_FRAMEBUFFER, framebuffer.pingpongFBO[0]);
        glClear(GL_COLOR_BUFFER_BIT);
        shader.use();
        shader.setFloat("kernelSize", kernelSize / 100);
        glBindTexture(GL_TEXTURE_2D, texture);
        renderQuad();
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
    }
};

#endif // BRIGHTEXTRACT_EFFECT_H