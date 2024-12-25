// #ifndef FOG_EFFECT_H
// #define FOG_EFFECT_H

// #include "effect.h"

// class FogEffect : public Effect {
// public:
//     glm::vec3 fogColor;
//     float fogDensity;

//     FogEffect(const glm::vec3& fogColor = glm::vec3(0.4f, 0.7f, 0.2f), float fogDensity = 0.5f)
//         : fogColor(fogColor), fogDensity(fogDensity) {}

//     bool apply(Shader& shader, unsigned int texture, unsigned int width, unsigned int height) override {
//         shader.use();
//         shader.setVec3("fogColor", fogColor);
//         shader.setFloat("fogDensity", fogDensity);
//         glBindTexture(GL_TEXTURE_2D, texture);
//         renderQuad();
//     }
// };

// #endif // FOG_EFFECT_H