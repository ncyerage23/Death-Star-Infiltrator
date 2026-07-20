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
	NYFW_Rect player_rect = { (int)p.x, (int)p.y, p.w, p.h };
	if (!p.flip) {
		nyfw_canvasBlit(
			c.player_sprite[p.sp],
			NULL,
			c.game_layer,
			&player_rect
		);
	}
	else {
		for (int i = 0; i < p.w; i++) {
			int spr_x = p.w-i;
			for (int j = 0; j < p.h; j++) {
				uint16_t spr_col = nyfw_canvGetPixel(c.player_sprite[p.sp], spr_x, j);
				if (spr_col != 0)
					nyfw_canvSetPixel(c.game_layer, p.x+i, p.y+j, spr_col);
			}
		}
	}

}


