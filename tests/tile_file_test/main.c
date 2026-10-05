/*
 * Tile file test!
 *
 * Testing saving/loading a tile file...and maybe a little rendering.
 * Also the first step for making a thing to convert my .nymg tiles to .tile files.
 * 
 * Start by displaying the tile to the screen
 *
 * Okay!! I displayed the tile to the screen! I'm gonna make a smaller screen and do it there, then scale, I think. Just so it's easier to see. 
 * 
 *
 * Well, I did everything! I made a tile, drew it to the screen, saved it as a binary file, loaded the same binary file,
 * and drew that to the screen! And, of course, it worked!
 *
 *
 */


#include "data/d_tile.h"
#include <string.h>
#include "canvas/colors.h"
#include "core/core.h"
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include "files/f_header.h"
#include "files/f_tile.h"


d_tile make_tile()
{
	d_tile test;
	test.flags = 0;
	for (int i = 0; i < 64; i++)
		test.pixels[i] = 14;	// 14 == pink

	test.pixels[2] = 12;		// 12 == LBLUE

	return test;
}


void draw_tile(NYFW_Canvas c, d_tile tile, int x, int y)
{
	for (int j = 0; j < D_TILE_LEN; j++)
		for (int i = 0; i < D_TILE_LEN; i++)
			CANV_PIXEL(c, x+i, y+j) = NYFW_Palette[tile.pixels[j * D_TILE_LEN + i]];
}


int main()
{
	if (!nyfw_windowInit(1)) return 0;
	NYFW_Canvas scr = nyfw_getWindowCanvas();

	uint16_t viewpixels[D_TILE_LEN * D_TILE_LEN * 16 * 16];
	NYFW_Canvas view = nyfw_canvas(viewpixels, 128, 128, 128);
	nyfw_canvasClear(view);

	nyfw_canvasClear(scr);
	
	d_tile tile = make_tile();
	draw_tile(view, tile, 0, 0);


	FILE* fp = fopen("assets/new_tiles/test.tile", "wb");
	
	f_header head = {
		.magic = "NY",
		.version = 1,
		.type = "TL",
		.size = 2*8*8 + 2
	};
	f_writeHeader(fp, &head);
	f_writeTile(fp, &tile, TILE_FORMAT_888);
	
	fclose(fp);			

	
	FILE* fp2 = fopen("assets/new_tiles/test.tile", "rb");
	f_header head2;
	f_readHeader(fp2, &head2);
	d_tile tile2;
	f_readTile(fp2, &tile2, TILE_FORMAT_888);
	fclose(fp2);

	draw_tile(view, tile2, 16, 16);



	
	NYFW_Canvas viewscale = nyfw_canvasScaleUp(view, 8); 
	nyfw_canvasBlit(viewscale, NULL, scr, NULL);

	nyfw_windowPresent();
	sleep(2);

	free(viewscale.pixels);
	nyfw_windowClose();
	return 0;
}

