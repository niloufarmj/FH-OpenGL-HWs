#ifndef COMMON_H
#define COMMON_H

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
#include "Framebuffer.h"
#include "BlurEffect.h"
#include "BloomEffect.h"
#include "brightExtractEffect.h"

#endif // COMMON_H