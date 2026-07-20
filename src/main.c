/*
 * DEATH STAR INFILTRATOR -- main
 *
 */

#include "deathstar.h"

bool running = true;


int main()
{
	ds_init();

	while (running) {
		ds_update();
		if (!running) break;

		ds_draw();
		nyfw_windowPresent();
	}
	
	ds_close();
	return 1;
}




