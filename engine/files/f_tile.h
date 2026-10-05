/*
 * Tile File -- loading/saving
 *
 * 
 * Uses the tile data struct (in engine/data) and reads
 * the binary file of it, or writes it to a binary file. 
 *
 * Should I have it already have the file open, or should I do it like f_header
 * and pass the file to this? Probably the latter. 
 *
 */

#ifndef F_TILE_H
#define F_TILE_H


/* ----- INCLUDES ----- */
#include <stdint.h>
#include <stdio.h>
#include "data/d_tile.h"


/* ----- TILE FORMAT SPECIFIER ----- */
#define TILE_FORMAT_888		1


/* ----- READ/WRITE ----- */
int f_readTile(FILE* fp, d_tile* tile, int requested_format);
int f_writeTile(FILE* fp, d_tile* tile, int tile_format);


#endif
