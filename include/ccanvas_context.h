#ifndef CCANVAS_CONTEXT_H
#define CCANVAS_CONTEXT_H

#include "ccanvas_defines.h"
#include "ccanvas_colours.h"
#include "ccanvas_window.h"
#include "ccanvas_shader.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

typedef struct {
    ccanvas_colour_t* screen;
    GLFWwindow* window;
    GLuint shader, texture, vao;
    int width, height;
} ccanvas_context_t;

ccanvas_context_t ccanvas_context_create(const char* title, int width, int height);
ccanvas_context_t* ccanvas_context_new(const char* title, int width, int height);
errno_t ccanvas_context_free(ccanvas_context_t* ctx, bool free_ctx);

errno_t ccanvas_context_make_current(ccanvas_context_t* ctx);

#endif //CCANVAS_CONTEXT_H
