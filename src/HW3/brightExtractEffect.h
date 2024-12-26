#ifndef BRIGHTEXTRACT_EFFECT_H
#define BRIGHTEXTRACT_EFFECT_H

#include "effect.h"
#include "framebuffer.h"

class BrightExtractEffect : public Effect {
public:
    Framebuffer& framebuffer;
    unsigned int amount;

    BrightExtractEffect(Framebuffer& framebuffer, unsigned int amount = 10) : framebuffer(framebuffer), amount(amount) {}

    void apply(Shader& shader, unsigned int texture, unsigned int width, unsigned int height) override {
        glBindFramebuffer(GL_FRAMEBUFFER, framebuffer.pingpongFBO[0]);
        glClear(GL_COLOR_BUFFER_BIT);
        shader.use();
        glBindTexture(GL_TEXTURE_2D, framebuffer.colorBuffers[0]);
        renderQuad();
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
    }
};

#endif // BRIGHTEXTRACT_H