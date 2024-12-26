#ifndef BLUR_EFFECT_H
#define BLUR_EFFECT_H

#include "effect.h"
#include "framebuffer.h"

class BlurEffect : public Effect {
public:
    Framebuffer& framebuffer;
    Shader& shader;
    unsigned int amount;

    BlurEffect(Framebuffer& framebuffer, Shader& shader, unsigned int amount = 10) 
        : framebuffer(framebuffer), shader(shader), amount(amount) {}

    void apply(Shader& shader, unsigned int texture, unsigned int width, unsigned int height, float kernelSize) override {
        bool horizontal = true, first_iteration = true;
        shader.use();
        shader.setVec2("pixelSize", glm::vec2(1.0f / width, 1.0f / height));
        shader.setFloat("kernelSize", kernelSize / 5); // Pass kernel size to shader
        for (unsigned int i = 0; i < amount; i++) {
            glBindFramebuffer(GL_FRAMEBUFFER, framebuffer.pingpongFBO[horizontal]);
            shader.setInt("horizontal", horizontal);
            glBindTexture(GL_TEXTURE_2D, first_iteration ? texture : framebuffer.pingpongColorbuffers[!horizontal]);
            renderQuad();
            horizontal = !horizontal;
            if (first_iteration)
                first_iteration = false;
        }
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
    }
};

#endif // BLUR_EFFECT_H