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

}


/* ----- DRAW ----- */
void ds_draw()
{
	nyfw_canvasClear(c.scr);

	for (int i = 0; i < 4; i++)
		nyfw_canvasFill(c.scr, WHITE, &c.border_rects[i]);
	
	int scr_x = c.game_rect.x;
	int scr_y = c.game_rect.y;
	for (int i = 0; i < c.game_rect.h; i++) {
		memcpy(
			&CANV_PIXEL(c.scr, scr_x, scr_y+i),	// the screen
			&CANV_PIXEL(c.level_screen, 0, i), 	// the level 
			2 * c.game_rect.w
		);
	}

}



