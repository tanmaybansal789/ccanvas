#ifndef CCANVAS_COLOURS_H
#define CCANVAS_COLOURS_H

#include "ccanvas_defines.h"

#include <stdint.h>

typedef uint32_t ccanvas_colour_t;

typedef struct {
    float h, s, v, a;
} ccanvas_hsva_t;

#define CCANVAS_RGBA_COLOUR(red, green, blue, alpha) \
    ((ccanvas_colour_t)(((uint8_t)(alpha) << 24) | ((uint8_t)(red) << 16) | ((uint8_t)(green) << 8) | (uint8_t)(blue)))

#define CCANVAS_RGB_COLOUR(r, g, b) CCANVAS_RGBA_COLOUR(r, g, b, 255)
#define CCANVAS_HEX_COLOUR(hex) ((ccanvas_colour_t)(hex))
#define CCANVAS_HSVA_COLOUR(hue, saturation, value, alpha) ((ccanvas_hsva_t) { .h = hue, .s = saturation, .v = value, .a = alpha })
#define CCANVAS_HSV_COLOUR(h, s, v) CCANVAS_HSVA_COLOUR(h, s, v, 1.0f)

// Macros to extract RGBA components from ccanvas_colour_t
#define CCANVAS_GET_R(colour) ((uint8_t)((colour) >> 16) & 0xFF)
#define CCANVAS_GET_G(colour) ((uint8_t)((colour) >> 8) & 0xFF)
#define CCANVAS_GET_B(colour) ((uint8_t)(colour) & 0xFF)
#define CCANVAS_GET_A(colour) ((uint8_t)((colour) >> 24) & 0xFF)

static ccanvas_colour_t ccanvas_hsva_to_rgba(ccanvas_hsva_t hsva) {
    float r, g, b;
    float h = hsva.h, s = hsva.s, v = hsva.v, a = hsva.a;

    int i = (int)(h * 6);
    float f = h * 6 - i;
    float p = v * (1 - s);
    float q = v * (1 - f * s);
    float t = v * (1 - (1 - f) * s);

    switch (i % 6) {
        case 0: r = v, g = t, b = p; break;
        case 1: r = q, g = v, b = p; break;
        case 2: r = p, g = v, b = t; break;
        case 3: r = p, g = q, b = v; break;
        case 4: r = t, g = p, b = v; break;
        case 5: r = v, g = p, b = q; break;
    }

    return CCANVAS_RGBA_COLOUR((uint8_t)(r * 255), (uint8_t)(g * 255), (uint8_t)(b * 255), (uint8_t)(a * 255));
}

static ccanvas_hsva_t ccanvas_rgba_to_hsva(ccanvas_colour_t colour) {
    float rf = CCANVAS_GET_R(colour) / 255.0f;
    float gf = CCANVAS_GET_G(colour) / 255.0f;
    float bf = CCANVAS_GET_B(colour) / 255.0f;
    float af = CCANVAS_GET_A(colour) / 255.0f;

    float max = fmaxf(rf, fmaxf(gf, bf));
    float min = fminf(rf, fminf(gf, bf));
    float delta = max - min;

    float h, s, v = max;

    if (delta < 0.00001f) {
        h = 0;
        s = 0;
    } else {
        s = (max > 0.0f) ? (delta / max) : 0.0f;

        if (rf >= max)
            h = (gf - bf) / delta;
        else if (gf >= max)
            h = 2.0f + (bf - rf) / delta;
        else
            h = 4.0f + (rf - gf) / delta;

        h /= 6.0f;
        if (h < 0.0f)
            h += 1.0f;
    }

    return (ccanvas_hsva_t){h, s, v, af};
}

// Common color macros with opacity
#define CCANVAS_BLACK(a) CCANVAS_RGBA_COLOUR(0, 0, 0, a)
#define CCANVAS_WHITE(a) CCANVAS_RGBA_COLOUR(255, 255, 255, a)
#define CCANVAS_RED(a) CCANVAS_RGBA_COLOUR(255, 0, 0, a)
#define CCANVAS_GREEN(a) CCANVAS_RGBA_COLOUR(0, 255, 0, a)
#define CCANVAS_BLUE(a) CCANVAS_RGBA_COLOUR(0, 0, 255, a)
#define CCANVAS_YELLOW(a) CCANVAS_RGBA_COLOUR(255, 255, 0, a)
#define CCANVAS_CYAN(a) CCANVAS_RGBA_COLOUR(0, 255, 255, a)
#define CCANVAS_MAGENTA(a) CCANVAS_RGBA_COLOUR(255, 0, 255, a)

#endif //CCANVAS_COLOURS_H