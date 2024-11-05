#include "ccanvas_context.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

static const GLfloat ccanvas_quad_vertices[] = {
    -1.0f,  1.0f,
    -1.0f, -1.0f,
     1.0f, -1.0f,
     1.0f,  1.0f
};

static const GLuint ccanvas_quad_indices[] = { 0, 1, 2, 0, 2, 3 };


ccanvas_context_t ccanvas_context_create(const char* title, int width, int height) {
    GLFWwindow* window = ccanvas_window_new(title, width, height);

    GLuint shader = ccanvas_shader_program_create("../assets/vertex_shader.glsl",
                                                "../assets/fragment_shader.glsl");

    ccanvas_context_t ctx = {
        .screen = calloc(width * height, sizeof(ccanvas_colour_t)),
        .window = window,
        .shader = shader,
        .texture = 0,
        .vao = 0,
        .width = width,
        .height = height
    };

    GLuint vbo, ebo;
    glGenVertexArrays(1, &ctx.vao);
    glGenBuffers(1, &vbo);
    glGenBuffers(1, &ebo);

    glBindVertexArray(ctx.vao);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(ccanvas_quad_vertices), ccanvas_quad_vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(ccanvas_quad_indices), ccanvas_quad_indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glGenTextures(1, &ctx.texture);
    glBindTexture(GL_TEXTURE_2D, ctx.texture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, ctx.screen);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    glUseProgram(ctx.shader);
    glUniform1i(glGetUniformLocation(ctx.shader, "screenTexture"), 0);

    ccanvas_context_make_current(&ctx);

    return ctx;
}

ccanvas_context_t* ccanvas_context_new(const char* title, int width, int height) {
    ccanvas_context_t* ctx = malloc(sizeof(ccanvas_context_t));
    if (ctx == NULL) {
        CCANVAS_ERR("Failed to allocate memory for ccanvas_context_t");
        return NULL;
    }

    *ctx = ccanvas_context_create(title, width, height);
    return ctx;
}

errno_t ccanvas_context_free(ccanvas_context_t* ctx, bool free_ctx) {
    glDeleteVertexArrays(1, &ctx->vao);
    glDeleteTextures(1, &ctx->texture);
    glDeleteProgram(ctx->shader);
    glfwDestroyWindow(ctx->window);

    free(ctx->screen);

    if (free_ctx) {
        free(ctx);
    }

    return 0;
}

errno_t ccanvas_context_make_current(ccanvas_context_t* ctx) {
    glfwMakeContextCurrent(ctx->window);
    return 0;
}
