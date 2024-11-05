#ifndef CCANVAS_DEFINES_H
#define CCANVAS_DEFINES_H

#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
#include <math.h>
#include <errno.h>

#ifndef CCANVAS_VERTEX_PATH
#define CCANVAS_VERTEX_PATH "../assets/vertex_shader.glsl"
#endif //CCANVAS_VERTEX_PATH

#ifndef CCANVAS_FRAGMENT_PATH
#define CCANVAS_FRAGMENT_PATH "../assets/fragment_shader.glsl"
#endif //CCANVAS_FRAGMENT_PATH

#ifndef CCANVAS_LOG
#define CCANVAS_LOG(fmt, ...) printf("[CCANVAS] " fmt "\n", ##__VA_ARGS__)
#endif //CCANVAS_LOG

#ifndef CCANVAS_ERR
#define CCANVAS_ERR(fmt, ...) fprintf(stderr, "[CCANVAS] " fmt "\n", ##__VA_ARGS__)
#endif //CCANVAS_ERR

#endif //CCANVAS_DEFINES_H
