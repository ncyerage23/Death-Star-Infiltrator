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
	p.dy += GRAVITY;
	p.dx *= FRICTION;
 
	if (nyfw_inputKeyHeld(NYFW_KEY_LEFT)) {
		p.dx -= p.acc;
		p.running = true;
		p.flip = true;
	}

	if (nyfw_inputKeyHeld(NYFW_KEY_RIGHT)) {
		p.dx += p.acc;
		p.running = true;
		p.flip = false;
	}

	// jump
	if (nyfw_inputKeyPressed(NYFW_KEY_X) && p.landed) {
		p.dy -= p.boost;
		p.landed = false;
	}

	// check collision
	if (p.dy > 0) {
		p.falling = true;
		p.landed = false;
		p.jumping = false;

		if (collide_map( (int)p.x, (int)p.y, p.w, p.h, DOWN) ) {
			p.landed = true;
			p.falling = false;
			p.dy = 0;
			p.y-= (int)(p.y + p.h) % 8;
		}
	}
	else if (p.dy < 0) {
		p.jumping = true;
		if (collide_map( (int)p.x, (int)p.y, p.w, p.h, UP)) {
			p.dy = 0;
		}
	}

	// left and right
	if (p.dx < 0) {
		if (collide_map((int)p.x, (int)p.y, p.w, p.h, LEFT)) {
			p.dx = 0;
		}
	}
	else if (p.dx > 0) {
		if (collide_map((int)p.x, (int)p.y, p.w, p.h, RIGHT)) {
			p.dx = 0;
		}
	}

	p.x += p.dx;
	p.y += p.dy;
}


void player_animate()
{

}


void draw_player()
{
	if (p.flip) {
		for (int i = 0; i < p.w; i++) {
			int spr_x = p.w-i;
			for (int j = 0; j < p.h; j++) {
				uint16_t spr_col = CANV_PIXEL(c.player_sprite[p.sp], spr_x, j);
				if (spr_col != 0)
					CANV_PIXEL(c.game_layer, (int)(p.x+i), (int)(p.y+j)) = spr_col;
			}
		}
	}
	else {
		for (int i = 0; i < p.w; i++) {
			for (int j = 0; j < p.h; j++) {
				uint16_t spr_col = CANV_PIXEL(c.player_sprite[p.sp], i, j);
				if (spr_col != 0)
					CANV_PIXEL(c.game_layer, (int)(p.x+i), (int)(p.y+j)) = spr_col;
			}
		}
		
	}

}


