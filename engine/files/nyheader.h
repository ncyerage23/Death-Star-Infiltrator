/*
 * NYHeader -- a common header for game data
 *
 *
 * Described in detail in docs/files.md, but I'll put another one here. 
 * 
 * Anyway, this is the basis of all game data saved to binary files. For this
 * module (engine/files), I'm gonna use the prefix "nyfile_" for any functions. 
 *
 */

#ifndef NYHEADER_H
#define NYHEADER_H


/* ----- INCLUDES ----- */
#include <stdint.h>
#include <stdio.h>


/* ----- TYPE DEFINITIONS ----- */
#define FTYPE_PALETTE	0x504c		// PL: palette
#define FTYPE_TILE	0x544c		// TL: tile
#define FTYPE_ROOM	0x524d		// RM: room layout
#define FTYPE_TILEMAP	0x544d		// TM: tilemap
#define FTYPE_BIGMAP	0x424d		// BM: bigmap
#define FTYPE_IMAGE	0x4d47		// MG: regular ole image


/* ----- NYHEADER STRUCT (8 BYTES) ----- */
typedef struct {
	char magic[2];		// always 'NY'
	uint8_t version;	// version of file
	char type[2];		// data type in file (see docs)
	uint32_t size;		// size (in bytes) of remaining file
} NYHeader;


/* ----- READ/WRITE ----- */
int nyfile_readHeader(FILE* f, NYHeader* head);
int nyfile_writeHeader(FILE* f, NYHeader* head);

// return 1 on success, 0 on fail




#endif


