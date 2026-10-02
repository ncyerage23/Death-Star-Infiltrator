/*
 * DEATH STAR INFILTRATOR!
 *
 *
 */

#ifndef DEATHSTAR_H
#define DEATHSTAR_H


/* ----- INCLUDES ----- */
#include "core/core.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <unistd.h>
#include <stdint.h>
#include <time.h>

#include "canvas/canvas.h"
#include "canvas/nymg.h"
#include "canvas/colors.h"


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
#define FRICTION	0.75f


/* ----- COLLISION ----- */
typedef enum {
	LEFT,
	RIGHT,
	UP,
	DOWN
} Aim;

bool collide_map(int x, int y, int w, int h, Aim a);


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
