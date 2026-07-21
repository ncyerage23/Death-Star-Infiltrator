/*
 * DEATH STAR INFILTRATOR -- update/draw functions
 *
 */

#include "deathstar.h"


/* ----- UPDATE ----- */
void ds_update()
{
	nyfw_inputPoll();
	if (nyfw_inputKeyPressed(NYFW_KEY_ESC)) {
		running = false;
		return;
	}

	p.y = p.y + GRAVITY;
}


/* ----- DRAW ----- */
void ds_draw_screen()
{
	nyfw_canvasClear(c.scr);
	for (int i = 0; i < 4; i++)
		nyfw_canvasFill(c.scr, WHITE, &c.border_rects[i]);
}



void ds_draw()
{
	/* ----- THE GAME LAYER ----- */
	memcpy(
		c.game_layer.pixels,
		c.level_screen.pixels,
		32768
	);
	
	draw_player();
	

	/* ----- SCALING/COPYING TO SCREEN ----- */
	int gx = c.game_rect.x;
	int gy = c.game_rect.y;
	int scr_stride = c.scr.stride;
	
	
	// do not get this (found online)
	uint16_t row_buf[128*8];
	for (int sy = 0; sy < 128; sy++) {
		uint16_t* src_row = &c.game_layer.pixels[sy*128];

		uint64_t* rb = (uint64_t*)row_buf;
		for (int sx = 0; sx < 128; sx++) {
			uint16_t p = src_row[sx];
			uint64_t quad = (uint64_t)p
				| ((uint64_t)p << 16)
				| ((uint64_t)p << 32)
				| ((uint64_t)p << 48);
			rb[0] = quad;
			rb[1] = quad;
			rb += 2;
		}

		uint16_t* dst_base = &c.scr.pixels[(gy+sy*8) * scr_stride + gx];
		for (int oy = 0; oy < 8; oy++) {
			memcpy(dst_base + oy * scr_stride, row_buf, sizeof(row_buf));
		}
	}




	/*
	// do not get this (found online)
	for (int sy = 0; sy < 128; sy++) {
		uint16_t* src_row = &c.game_layer.pixels[sy*128];

		for (int oy = 0; oy < 8; oy++) {
			uint16_t *dst = &c.scr.pixels[ (gy+sy * 8 + oy) * scr_stride + gx ];
			
			for (int sx = 0; sx < 128; sx++) {
				uint16_t p = src_row[sx];
			
				dst[0] = p;
				dst[1] = p;
				dst[2] = p;
				dst[3] = p;
				dst[4] = p;
				dst[5] = p;
				dst[6] = p;
				dst[7] = p;

				dst += 8;
			}
		}
	}
	*/

}


