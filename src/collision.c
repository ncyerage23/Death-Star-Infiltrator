/* 
 * DEATH STAR INFILTRATOR -- collision testing
 *
 */

#include "deathstar.h"

bool collide_map(int x, int y, int w, int h, Aim a)
{
	int x1=0, x2=0, y1=0, y2=0;

	if (a == LEFT) {
		x1 = x-1;	y1 = y;
		x2 = x;		y2 = y+h-1;
	}
	else if (a == RIGHT) {
		x1 = x+w;	y1 = y;
		x2 = x+w+1;	y2 = y+h-1;
	}
	else if (a == UP) {
		x1 = x+1;	y1 = y-1;
		x2 = x+w-1;	y2 = y;
	}
	else {
		x1 = x;		y1 = y+h;
		x2 = x+w;	y2 = y+h;
	}

	// convert pixels to tiles
	x1 /= 8;	y1 /= 8;
	x2 /= 8;	y2 /= 8;
	
	if ( 
		CANV_PIXEL(c.level, x1, y1) != 0 ||
		CANV_PIXEL(c.level, x1, y2) != 0 ||
		CANV_PIXEL(c.level, x2, y1) != 0 ||
		CANV_PIXEL(c.level, x2, y2) != 0
	) return true;
	
	return false;
}
