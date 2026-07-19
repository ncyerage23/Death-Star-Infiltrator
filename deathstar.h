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


/* ----- STRUCTS ----- */
typedef struct {
	NYFW_Canvas scr;
	NYFW_Rect game_rect;
	NYFW_Rect border_rects[4];
	
	NYFW_Canvas level_map;		// compressed map form (for collision & stuff, loaded from .nymap)
	NYFW_Canvas level_screen;	// version for copying to the screen
	NYFW_Canvas player_sprite[3];
} Control;

typedef struct {
	int x, y;
	int sp;
	int w, h;
	bool flip;
	float dx, dy;
	float max_dx, max_dy;
	float acc;
	int boost;
	int anim;
	bool running, jumping, falling, sliding;
	bool landed;
} Player;


/* ----- VARIABLES ----- */
extern Control c;
extern Player p;
extern bool running;


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
void ds_draw();








#endif
