/*
 * Room Struct -- a representation of an individual level
 *
 *
 * Each element of the array refers to a tilemap index (8 bit int)
 * No metadata for them right now, just the tiles. 
 *
 * square 16x16 for right now, but I'll probably change that eventually.
 * May need to make a new struct or something, not sure. Could also be a bigmap issue.
 *
 */

#ifndef D_ROOM_H
#define D_ROOM_H

/* ----- INCLUDES ----- */
#include <stdint.h>
#include <stddef.h>


/* ----- ROOM STRUCT (AND DEFINITIONS) ----- */
#define D_ROOM_LEN	16

typedef struct {
	uint8_t tiles[D_ROOM_LEN * D_ROOM_LEN];	
} d_room;



#endif
