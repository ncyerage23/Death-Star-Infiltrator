/*
 * DEATH STAR INFILTRATOR -- update/draw functions
 *
 */

#include "deathstar.h"


double get_time()
{
	struct timespec ts;
	clock_gettime(CLOCK_MONOTONIC, &ts);
	return ts.tv_sec + ts.tv_nsec / 1e9;
}



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
void ds_draw()
{
	static int call = 0;
	double start = get_time();

	/* ----- CLEARING + BORDER ----- */
	nyfw_canvasClear(c.scr);
	for (int i = 0; i < 4; i++)
		nyfw_canvasFill(c.scr, WHITE, &c.border_rects[i]);
	
	double border = get_time();


	/* ----- THE GAME LAYER ----- */
	nyfw_canvasClear(c.game_layer);		// copying the level layer to the game layer
	memcpy(
		c.game_layer.pixels,
		c.level_screen.pixels,
		2 * 128 * 128
	);
	double level = get_time();
	
	draw_player();
	double player = get_time();

	NYFW_Canvas game_scaled = nyfw_canvasScaleUp(c.game_layer, 8);
	double scale = get_time();


	/* ----- COPYING TO SCREEN ----- */
	int scr_x = c.game_rect.x;
	int scr_y = c.game_rect.y;
	for (int i = 0; i < c.game_rect.h; i++) {
		memcpy(
			&CANV_PIXEL(c.scr, scr_x, scr_y+i),	// the screen
			&CANV_PIXEL(game_scaled, 0, i), 	// the game layer (scaled to screen resolution)
			2 * c.game_rect.w
		);
	}
	
	free(game_scaled.pixels);
	double end = get_time();


	printf(
		"Draw %d:\n"
		"\ttotal: %.2f ms\n"
		"\tborder: %.2f ms\n"
		"\tlevel: %.2f ms\n"
		"\tplayer: %.2f ms\n"
		"\tscale: %.2f ms\n"
		"\tblit: %.2f ms\n"
		"\n",
		call,
		(end-start)*1000,
		(border-start)*1000,
		(level-border)*1000,
		(player-level)*1000,
		(scale-player)*1000,
		(end-scale)*1000
	);
	call++;
}



