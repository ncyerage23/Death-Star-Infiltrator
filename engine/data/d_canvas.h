/*
 * Canvas Struct -- 16bpp image
 *
 *
 * Moved from canvas module, because I'm doing a thing. 
 * Canvas module one is still there, and I'll fix that later on. 
 *
 */

#ifndef D_CANVAS_H
#define D_CANVAS_H

/* ----- INCLUDES ----- */
#include <stdint.h>
#include <stddef.h>


/* ----- CANVAS STRUCT ----- */
typedef struct {
	uint16_t* pixels;
	size_t width;
	size_t height;
	size_t stride;
	int original;
} d_canvas;

#define CANV_NULL	((d_canvas){0})

// should I put rect somewhere too? Here? Idek. No functions, obviously, but yeah.


#endif
