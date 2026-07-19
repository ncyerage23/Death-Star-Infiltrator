/*
 * DEATH STAR INFILTRATOR -- update/draw functions
 *
 */

#include "deathstar.h"


/* ----- UPDATE ----- */
void player_update()
{
	if (nyfw_inputKeyHeld(NYFW_KEY_LEFT)) {
		p.dx = -5.0f;
	}

	else if (nyfw_inputKeyHeld(NYFW_KEY_RIGHT)) {
		p.dx = 5.0f;
	}

	else
		p.dx = 0;
	
	p.x += p.dx;
	p.y += p.dy;
}


void player_animate()
{

}


void ds_update()
{
	nyfw_inputPoll();
	if (nyfw_inputKeyPressed(NYFW_KEY_ESC)) {
		running = false;
		return;
	}

	player_update();
	// player_animate();

}


/* ----- DRAW ----- */
void draw_player()
{
	int x = c.game_rect.x + p.x;
	int y = c.game_rect.y + p.y;

	for (int i = 0; i < p.w; i++) {
		int spr_x = (p.flip) ? p.w-i : i;
		for (int j = 0; j < p.h; j++) {
			uint16_t spr_col = nyfw_canvGetPixel(c.player_sprite[p.sp], spr_x, j);
			if (spr_col != 0)
				nyfw_canvSetPixel(c.scr, x+i, y+j, spr_col);
		}
	}

}


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


	draw_player();
}



