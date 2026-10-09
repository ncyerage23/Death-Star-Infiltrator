/*
 * Tile Struct -- a representation of a single tile and its metadata
 *
 *
 * Won't really be for use in the actual games, only for making individual tiles,
 * and compiling them to tilemaps. But yeah, it's a good place to start. 
 *
 */

#ifndef D_TILE_H
#define D_TILE_H

/* ----- INCLUDES ----- */
#include <stdint.h>
#include <stddef.h>


/* ----- DEFAULT TILE LENGTH ----- */
#ifndef D_TILE_LEN
#define D_TILE_LEN	8
#endif

// size of tile.pixels in bytes
#define D_TILE_SIZE	D_TILE_LEN * D_TILE_LEN * 2 + 2


/*
 * This allows the user to overwrite the tile length and define their own
 * sized tiles. Just for future use, I guess, if I want to move up to 16x16.
 * If I do, I'll eventually just overwrite it here, but for now, this is good.
 *
 * Also: if I'm overwriting it, I have to define the new tile length before I include
 * this header. Just an fyi. 
 *
 * Also, if I don't define the macro in all files including D_TILE_H, it'll be different for
 * each one. I can make a header shared by all source files, though, and do it there. That'd work.
 *
 */



/* ----- TILE STRUCT ----- */
typedef struct {
	uint8_t flags;					// user-defined metadata flags
	uint8_t pixels[D_TILE_LEN * D_TILE_LEN];	// represented as palette indices
} d_tile;




#endif
