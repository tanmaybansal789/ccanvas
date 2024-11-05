#ifndef CCANVAS_WINDOW_H
#define CCANVAS_WINDOW_H

#include "ccanvas_defines.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

GLFWwindow* ccanvas_window_new(const char* title, int width, int height);

#endif //CCANVAS_WINDOW_H
