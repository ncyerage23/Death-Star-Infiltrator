/*
 * Palette Struct -- a system for quick color lookup
 *
 * For right now, up to 255 colors (0 is no color)
 * For reference in tile images, so they store 8bit ints
 *
 * Also, won't be doing this in files yet probably. I'll just make one
 * somewhere. 
 *
 */

#ifndef D_PALETTE_H
#define D_PALETTE_H

/* ----- INCLUDES ----- */
#include <stdint.h>


/* ----- PALETTE STRUCT ----- */
typedef struct {
	uint8_t count;		// up to 255
	uint16_t colors[256];
} d_palette;


// like tile, there are functions I should put with this. 
// But they shouldn't be here. Idk where they should be, but yeah. 


#endif

