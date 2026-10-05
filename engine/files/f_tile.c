/*
 * f_tile implementation
 *
 * Read/write tile binary file
 * 
 * TODO: I currently don't read the f_header. Not sure if that's good, but it will work. 
 * It'll be more annoying to open files, but for now, I don't really care. Just fix it when needed. 
 *
 */


/* ----- INCLUDES ----- */
#include "files/f_tile.h"


/* ----- TILE DATA STRUCT ----- */
typedef struct {
	uint8_t format;		// format number, 1 is the regular one (8x8, 8 bpp)
} f_tileinfo;


/* ----- READ/WRITE ----- */
int f_readTile(FILE* fp, d_tile* tile, int requested_format)
{
	if (!fp) {
		printf("File is null?\n");
		return 0;
	}

	f_tileinfo info;
	if (!fread(&info, sizeof(f_tileinfo), 1, fp)) {
		printf("Failed to read tile info header.\n");
		return 0;
	}

	if (info.format != requested_format) {
		printf("Mismatch: file does not match requested format. Req: %d File: %d.\n", 
				requested_format, info.format);
		return 0;
	}
	
	if (!fread(tile, sizeof(d_tile), 1, fp)) {
		printf("Failed to read tile data.\n");
		return 0;
	}

	return 1;
}


int f_writeTile(FILE* fp, d_tile* tile, int tile_format)
{
	if (!fp) {
		printf("File is null?\n");
		return 0;
	}

	if (!tile) {
		printf("Tile is null.\n");
		return 0;
	}

	
	f_tileinfo info = {
		.format = tile_format,
	};
	fwrite(&info, sizeof(f_tileinfo), 1, fp);

	fwrite(tile, sizeof(d_tile), 1, fp);

	return 1;
}




