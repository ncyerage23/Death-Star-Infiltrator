/*
 * Tilemap Struct -- storing all tiles (up to 255) for the game
 *
 * 
 * All tiles are stored as one big map. 
 * Tile 0 is held for null tile. 
 *
 */

#ifndef D_TILEMAP_H
#define D_TILEMAP_H

/* ----- INCLUDES ----- */
#include <stdint.h>
#include "data/d_tile.h"	// for D_TILE_LEN


/* ----- TILEMAP STRUCT ----- */
#define D_TILECOUNT_MAX		256
#define D_TILEMAP_SIZE		D_TILE_LEN * D_TILE_LEN * D_TILECOUNT_MAX

typedef struct {
	int count;				// number of tiles actually in map
	uint8_t tile_pixels[D_TILEMAP_SIZE];	// tile pixel data
	uint8_t tile_flags[D_TILECOUNT_MAX];	// flag metadata for each tile, indexed to same order as tile_pixels
} d_tilemap;



#endif
