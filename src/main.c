/*
 * DEATH STAR INFILTRATOR -- main
 *
 */

#include "deathstar.h"

bool running = true;


void mainloop()
{
	ds_update();
	if (!running) return;

	ds_draw();
	nyfw_windowPresent();
}


int main()
{
	ds_init();

	while (running) {
		mainloop();
	}
	
	ds_close();
	return 1;
}




