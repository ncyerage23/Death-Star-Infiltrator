/*
 * Bigmap Struct -- stores all rooms (up to 256) for the game
 *
 * Same as tilemap, but for rooms.
 *
 */

#ifndef D_BIGMAP_H
#define D_BIGMAP_H

/* ----- INCLUDES ----- */
#include <stdint.h>
#include "data/d_room.h"


/* ----- BIGMAP STRUCT ----- */
#define D_ROOMCOUNT_MAX		256
#define D_BIGMAP_SIZE		D_ROOM_LEN * D_ROOM_LEN * D_ROOMCOUNT_MAX

typedef struct {
	int count;
	uint8_t room_tiles[D_BIGMAP_SIZE];
} d_bigmap;


#endif
