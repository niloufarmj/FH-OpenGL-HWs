#ifndef EFFECT_H
#define EFFECT_H

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <util/shader.h>
#include "rendering.h"

class Effect {
public:
    virtual void apply(Shader& shader, unsigned int texture, unsigned int width, unsigned int height, float kernelSize) = 0;
};

#endif // EFFECT_H