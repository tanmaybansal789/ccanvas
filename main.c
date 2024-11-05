#include "ccanvas.h"

#include <math.h>
#include <time.h>

#define FOV 256.0              
#define CUBE_SIZE 50           
#define ROTATION_SPEED 0.05    

typedef struct {
    float x, y, z;
} Vec3;

void draw_border(ccanvas_context_t* ctx, ccanvas_colour_t color) {
    for (int x = 0; x < ctx->width; ++x) {
        ccanvas_set_pixel(ctx, x, 0, color);
        ccanvas_set_pixel(ctx, x, ctx->height - 1, color);
    }
    for (int y = 0; y < ctx->height; ++y) {
        ccanvas_set_pixel(ctx, 0, y, color);
        ccanvas_set_pixel(ctx, ctx->width - 1, y, color);
    }
}

void draw_line(ccanvas_context_t* ctx, int x0, int y0, int x1, int y1, ccanvas_colour_t colour) {
    int dx = abs(x1 - x0);
    int dy = abs(y1 - y0);
    int sx = (x0 < x1) ? 1 : -1;
    int sy = (y0 < y1) ? 1 : -1;
    int err = dx - dy;

    while (true) {
        ccanvas_set_pixel(ctx, x0, y0, colour);

        if (x0 == x1 && y0 == y1) break;
        int e2 = 2 * err;
        if (e2 > -dy) {
            err -= dy;
            x0 += sx;
        }
        if (e2 < dx) {
            err += dx;
            y0 += sy;
        }
    }
}

void rotate_x(Vec3* point, float angle) {
    float y = point->y * cos(angle) - point->z * sin(angle);
    float z = point->y * sin(angle) + point->z * cos(angle);
    point->y = y;
    point->z = z;
}

void rotate_y(Vec3* point, float angle) {
    float x = point->x * cos(angle) + point->z * sin(angle);
    float z = -point->x * sin(angle) + point->z * cos(angle);
    point->x = x;
    point->z = z;
}

void rotate_z(Vec3* point, float angle) {
    float x = point->x * cos(angle) - point->y * sin(angle);
    float y = point->x * sin(angle) + point->y * cos(angle);
    point->x = x;
    point->y = y;
}

int main(void) {
    ccanvas_context_t* ctx = ccanvas_context_new("Colorful Rotating Cube with Border", 800, 600);

    printf("ctx->window: %p\n", ctx->window);

    Vec3 cubeVertices[8] = {
        {-CUBE_SIZE, -CUBE_SIZE, -CUBE_SIZE},
        { CUBE_SIZE, -CUBE_SIZE, -CUBE_SIZE},
        { CUBE_SIZE,  CUBE_SIZE, -CUBE_SIZE},
        {-CUBE_SIZE,  CUBE_SIZE, -CUBE_SIZE},
        {-CUBE_SIZE, -CUBE_SIZE,  CUBE_SIZE},
        { CUBE_SIZE, -CUBE_SIZE,  CUBE_SIZE},
        { CUBE_SIZE,  CUBE_SIZE,  CUBE_SIZE},
        {-CUBE_SIZE,  CUBE_SIZE,  CUBE_SIZE}
    };
    int edges[12][2] = {
        {0, 1}, {1, 2}, {2, 3}, {3, 0},
        {4, 5}, {5, 6}, {6, 7}, {7, 4},
        {0, 4}, {1, 5}, {2, 6}, {3, 7}
    };

    float angle = 0;

    while (!glfwWindowShouldClose(ctx->window)) {
        
        for (int i = 0; i < ctx->width * ctx->height; ++i) {
            ctx->screen[i] = CCANVAS_BLACK(255);  
        }

        
        ccanvas_colour_t borderColor = ccanvas_hsva_to_rgba(CCANVAS_HSVA_COLOUR(fmodf(angle * 0.1f, 1.0f), 1.0f, 1.0f, 1.0f));
        draw_border(ctx, borderColor);

        
        Vec3 transformedVertices[8];
        for (int i = 0; i < 8; i++) {
            transformedVertices[i] = cubeVertices[i];
            
            rotate_x(&transformedVertices[i], angle);
            rotate_y(&transformedVertices[i], angle);
            rotate_z(&transformedVertices[i], angle);
            
            float distance = 4 * CUBE_SIZE;
            float z = transformedVertices[i].z + distance;
            transformedVertices[i].x = (transformedVertices[i].x * FOV) / z + ctx->width / 2;
            transformedVertices[i].y = (transformedVertices[i].y * FOV) / z + ctx->height / 2;
        }

        
        for (int i = 0; i < 12; i++) {
            int start = edges[i][0];
            int end = edges[i][1];
            
            float hue = fmodf(angle * 0.1f + (i * 0.05f), 1.0f);
            ccanvas_colour_t edgeColor = ccanvas_hsva_to_rgba(CCANVAS_HSVA_COLOUR(hue, 1.0f, 1.0f, 1.0f));
            draw_line(ctx,
                      (int)transformedVertices[start].x, (int)transformedVertices[start].y,
                      (int)transformedVertices[end].x, (int)transformedVertices[end].y,
                      edgeColor);
        }

        
        ccanvas_update(ctx);
        angle += ROTATION_SPEED;

        
        struct timespec req = {0, 30000000L};  
        nanosleep(&req, NULL);
    }

    ccanvas_context_free(ctx, true);

    return 0;
}