#ifndef SETTINGS_H
#define SETTINGS_H

#include <glm/glm.hpp>
#include <util/camera.h>

// settings
extern int SCR_WIDTH = 1024;
extern int SCR_HEIGHT = 720;

// camera
extern glm::vec3 initialPosition(15.3819, -14.9108, -9.41979);
extern float initialYaw = -215.0f;
extern float initialPitch = 3.7f;

extern Camera camera;
extern float lastX;
extern float lastY;
extern bool firstMouse;
extern bool leftButtonDown;
extern bool middleButtonDown;
extern bool rightButtonDown;

extern float deltaTime;
extern float lastFrame;

#endif // SETTINGS_H