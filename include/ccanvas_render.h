#ifndef CCANVAS_RENDER_H
#define CCANVAS_RENDER_H

#include "ccanvas_context.h"
#include "ccanvas_colours.h"

void ccanvas_update(ccanvas_context_t* ctx);
void ccanvas_clear(ccanvas_context_t* ctx, ccanvas_colour_t colour);

void ccanvas_set_pixel(ccanvas_context_t* ctx, int x, int y, ccanvas_colour_t colour);
#endif //CCANVAS_RENDER_H
