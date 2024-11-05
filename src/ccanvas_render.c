#include "ccanvas_render.h"

void ccanvas_update(ccanvas_context_t* ctx) {
    glBindTexture(GL_TEXTURE_2D, ctx->texture);

    glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, ctx->width, ctx->height, GL_RGBA, GL_UNSIGNED_BYTE, ctx->screen);

    glClear(GL_COLOR_BUFFER_BIT);
    glBindVertexArray(ctx->vao);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

    glfwSwapBuffers(ctx->window);
    glfwPollEvents();
}

// ----------------------------------------------------------------

void ccanvas_clear(ccanvas_context_t* ctx, ccanvas_colour_t colour) {
    for (int i = 0; i < ctx->width * ctx->height; ++i) {
        ctx->screen[i] = colour;
    }
}

void ccanvas_set_pixel(ccanvas_context_t* ctx, int x, int y, ccanvas_colour_t colour) {
    if (x < 0 || x >= ctx->width || y < 0 || y >= ctx->height) {
        return;
    }

    ctx->screen[y * ctx->width + x] = colour;
}