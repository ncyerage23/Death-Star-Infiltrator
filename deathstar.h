/*
 * DEATH STAR INFILTRATOR!
 *
 * I'm just doing a test/prototype right now, but this is gonna be the main game header. I guess. 
 * The plan is to adapt that whole PICO-8 Platformer tutorial to NYFW and C. Which has been difficult so far,
 * but I think splitting it into multiple files will help (a bit, at least). Plus, I will need multiple files 
 * anyway, so yeah. 
 *
 * Besides doing the tutorial from the videos, I think I'll also try to fix the backend parts just a bit. 
 * Possibly by scaling the game screen each frame? I'm not actually sure. Lol. I'll think about that before
 * I do it. 
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
