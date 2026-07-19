/*
 * DEATH STAR INFILTRATOR -- player functions
 *
 */

#include "deathstar.h"

#define MAX(x, y)	(x < y) ? y : x
#define MIN(x, y)	(x < y) ? x : y


int limit_speed(int num, int maximum)
{
	return MAX(-maximum, MIN(num, maximum));	
}


void player_update()
{

}


void player_animate()
{

}


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


