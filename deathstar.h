/*
 * DEATH STAR INFILTRATOR!
 *
 * I'm just doing a test/prototype right now, but this is gonna be the main game header. I guess. 
 *
 * Progress 7/19/26 4:15 pm:
 * 	I decided I'm too lazy to fix up the backend like I planned (at least right now) and just
 * 	want to move forward with the tutorial. So, I guess that's what I'm gonna do. I think
 * 	I'll take a short break first, maybe circling back here later. Though I have other things
 * 	I need to do. But yeah, pretty good work so far. 
 *
 * Progress 7/20/26 2:51 pm:
 * 	A few things. I decided I'm not too lazy to fix up the backend, so I did that. I now have
 * 	a 128x128 game layer which I draw everything to, then I scale it up and copy it to the 
 * 	screen every frame. Makes more sense (somewhat). Unfortunately, it's ridiculously slow,
 * 	running (doing pretty much nothing but a simple update) at around 2 FPS. From some time checks
 * 	I've discovered the main culprit is the scale function I need to call every frame (drawing the
 * 	border and blitting also take longer, but like 1% of the scale call). 
 * 	So, the next step is to speed up scaling. I'll probably just do it in this instead of fixing
 * 	the NYFW scale function -- for now -- but idk what I can do really. So...yeah. 
 *
 */

#ifndef DEATHSTAR_H
#define DEATHSTAR_H


/* ----- INCLUDES ----- */
#include "NYFW/nyfw.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <unistd.h>
#include <stdint.h>
#include <time.h>


/* ----- STRUCTS ----- */
typedef struct {
	NYFW_Canvas scr;
	NYFW_Rect game_rect;			// space where game will be displayed on scr
	NYFW_Rect border_rects[4];		// border around game on scr
	
	NYFW_Canvas level;			// map loaded from .nymap file, 16x16 (1px = 1 tile index)
	NYFW_Canvas player_sprite[3];		// player sprites, 8x8 pixels (equivalent to 1 tile in size)
	NYFW_Canvas level_screen;		// level upscaled to 128x128 pixels (tiles pasted here. for quick copying to final game screen)

	NYFW_Canvas game_layer;			// 128x128 game layer (draw sprites + level to this, then scale and paste)
} Control;

typedef struct {
	float x, y;
	int sp;
	int w, h;
	bool flip;

	float dx, dy;
	float max_dx, max_dy;
	float acc;
	float boost;

	int anim;
	bool running, jumping, falling, sliding, landed;
} Player;


/* ----- VARIABLES ----- */
extern Control c;
extern Player p;
extern bool running;

#define GRAVITY		0.3f
#define FRICTION	0.85f


/* ----- COLLISION ----- */
typedef enum {
	LEFT,
	RIGHT,
	UP,
	DOWN
} Aim;

bool collide_map(int x, int y, int w, int h, Aim a, int flag);


/* ----- PLAYER ----- */
void player_update();
void player_animate();
void draw_player();


/* ----- INIT/CLOSE ----- */
int ds_init();
void ds_close();


/* ----- UPDATE/DRAW ----- */
void ds_update();
void ds_draw_screen();
void ds_draw();








#endif
