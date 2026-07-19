/* DEATH STAR INFILTRATOR -- Initial Test
 *
 * 
 * This isn't even the prototype. It's just the test to get the game going. A single room, plus some code to sorta 
 * make it work. This is in the games folder right now, but I'll move it to the tests folder, I think. It's a very 
 * basic test, before I start trying to ramp ts up. 
 *
 * Basically, it's just the little PICO-8 platformer tutorial I did, and that's it. Will return tomorrow (or later tonight).
 * Good luck!
 *
 * Progress: 7/13/26, 3:35 pm
 * 	Well, I got the level loader thing working! That's a start, at the very least. It was a bit weird to do, but at this point I don't think there's
 * 	a problem. I don't think it's done perfectly either, but it's not gonna take very much to fix it. I'll make a better system later, using multiple files. 
 * 	But...yeah. All I need to do next is draw the player, do input, and collison. I think. Yeah!
 *
 * Quick break before I do this. Ig.
 *
 * Progress: 7/13/26, 5:27 pm
 * 	I don't think I took the break. Either way, what I currently have works. Not well, but it does work. There was an issue with the whole
 * 	canvasBlit function (slow ash) but I replaced it with a memcpy guy that did work! So...yeah. Now, movement is not as slow. Very cool!
 * 	Next, I think I'll go ham on the pico-8 stuff (collision, acceleration and stuff, jumping, and -- maybe later -- more animations!). That's the next step.
 *
 *
 */

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
Control c;
Player p;

bool running = true;

float gravity = 0.3;
float friction = 0.85;


/* ----- INIT ----- */
int load_level();
int load_sprites();

int ds_init()
{
	/* ----- INITIALIZATION ----- */
	if (!nyfw_windowInit()) return 0;
	if (!nyfw_inputInit(INPUT_KEYS)) return 0;

	/* ----- CONTROL STRUCT ----- */
	c.scr = nyfw_getWindowCanvas();
	nyfw_canvasClear(c.scr);
	
	c.game_rect = (NYFW_Rect){ 448, 28, 1024, 1024 };
	c.border_rects[0] = (NYFW_Rect){ 428, 28, 20, 1024 };		// left
	c.border_rects[1] = (NYFW_Rect){ 1472, 28, 20, 1024 };		// right
	c.border_rects[2] = (NYFW_Rect){ 428, 8, 1064, 20 };		// top
	c.border_rects[3] = (NYFW_Rect){ 428, 1052, 1064, 20 };		// bottom
	
	if (!load_level()) return 0;
	if (!load_sprites()) return 0;

	/* ----- PLAYER STRUCT ----- */
	p.x = 192,	p.y = 192;
	p.sp = 0;
	p.w = 64,	p.h = 64;
	p.flip = false;
	p.dx = 5.0f,		p.dy = 0.0f;
	p.max_dx = 2.0f,	p.max_dy = 3.0f;
	p.acc = 0.5f;
	p.boost = 4;
	p.anim = 0;
	p.running = false;	p.jumping = false;
	p.falling = false;	p.sliding = false;
	p.landed = false;

	return 1;
}


/* ----- UPDATE ----- */
void player_update();
void player_animate();

void ds_update()
{
	nyfw_inputPoll();
	if (nyfw_inputKeyPressed(NYFW_KEY_ESC)) {
		running = false;
		return;
	}

	player_update();
	// player_animate();

}


/* ----- DRAW ----- */
void draw_player();

void ds_draw()
{
	nyfw_canvasClear(c.scr);

	for (int i = 0; i < 4; i++)
		nyfw_canvasFill(c.scr, WHITE, &c.border_rects[i]);
	
	int scr_x = c.game_rect.x;
	int scr_y = c.game_rect.y;
	for (int i = 0; i < c.game_rect.h; i++) {
		memcpy(
			&CANV_PIXEL(c.scr, scr_x, scr_y+i),	// the screen
			&CANV_PIXEL(c.level_screen, 0, i), 	// the level 
			2 * c.game_rect.w
		);
	}


	draw_player();
}


/* ----- CLOSE ----- */
void ds_close()
{
	free(c.level_map.pixels);
	free(c.level_screen.pixels);

	free(c.player_sprite[0].pixels);
	free(c.player_sprite[1].pixels);
	free(c.player_sprite[2].pixels);

	nyfw_inputClose();
	nyfw_windowClose();
}


/* ----- MAIN ----- */
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

}


/* ----- HELPERS ----- */
NYFW_Canvas load_tiles()
{
	FILE* fp;
	fp = fopen("assets/tile_list.txt", "r");
	char line[256];

	uint16_t* pixels = malloc(2 * 32 * 32);
	NYFW_Canvas out = nyfw_canvas(pixels, 32, 32, 32);

	int count = 0;
	if (fp != NULL) {
		while(fgets(line, sizeof(line), fp) && count < 16) {
			line[strcspn(line, "\n")] = '\0';

			NYFW_Canvas tile;
			nyfw_loadNYMG(&tile, line);
		
			NYFW_Rect tile_rect = { 8 * (count % 4), 8 * (count / 4), 8, 8 };
			nyfw_canvasBlit(tile, NULL, out, &tile_rect);	
			
			free(tile.pixels);
			count++;
		}
		fclose(fp);
	}
	return out;
}


int load_level()
{
	/* ----- LEVEL MAP ----- */
	if (!nyfw_loadNYMG(&c.level_map, "assets/proto.nymap")) return 0;

	/* ----- LEVEL LAYER ALLOCATION ----- */
	uint16_t* level_layer_pixels = malloc(2 * 1024 * 1024);
	if (!level_layer_pixels) return 0;
	c.level_screen = nyfw_canvas(level_layer_pixels, 1024, 1024, 1024);
	nyfw_canvasClear(c.level_screen);

	/* ----- THE TILE PALETTE ----- */
	NYFW_Canvas tiles = load_tiles();
	uint16_t* test_pixels = tiles.pixels;
	tiles = nyfw_canvasScaleUp(tiles, 8);
	free(test_pixels);

	/* ----- DRAWING THE FULL LEVEL ----- */
	for (int j = 0; j < 16; j++) {
		for (int i = 0; i < 16; i++) {
			int ti = c.level_map.pixels[j * 16 + i];
			if (ti == 0) continue;

			NYFW_Rect srcr = { 64 * (ti%4), 64 * (ti/4), 64, 64 };
			NYFW_Rect dstr = { i*64, j*64, 64, 64 };
			nyfw_canvasBlit(tiles, &srcr, c.level_screen, &dstr);
		}
	}

	return 1;
}


int load_sprites()
{
	NYFW_Canvas s1, s2, s3;
	nyfw_loadNYMG(&s1, "assets/sprites/player_1.nymg");
	nyfw_loadNYMG(&s2, "assets/sprites/player_2.nymg");
	nyfw_loadNYMG(&s3, "assets/sprites/player_3.nymg");

	c.player_sprite[0] = nyfw_canvasScaleUp(s1, 8);
	c.player_sprite[1] = nyfw_canvasScaleUp(s2, 8);
	c.player_sprite[2] = nyfw_canvasScaleUp(s3, 8);

	free(s1.pixels);
	free(s2.pixels);
	free(s3.pixels);

	return 1;
}


void draw_player()
{
	int x = c.game_rect.x + p.x;
	int y = c.game_rect.y + p.y;

	for (int i = 0; i < p.w; i++) {
		int spr_x = (p.flip) ? p.w-i : i;
		for (int j = 0; j < p.h; j++) {
			uint16_t spr_col = nyfw_canvGetPixel(c.player_sprite[p.sp], spr_x, j);
			if (spr_col != 0)
				nyfw_canvSetPixel(c.scr, x+i, y+j, spr_col);
		}
	}

}


int limit_speed(int num, int maximum)
{
	return MAX(-maximum, MIN(num, maximum));
}


typedef enum {
	LEFT,
	RIGHT,
	UP,
	DOWN
} Aim;


void collide_map(int x, int y, int w, int h, Aim a, int flag)
{
	int x1, y1, x2, y2;

	if (a == LEFT) {
		x1 = x-1;
		y1 = y;
		x2 = x;
		y2 = y+h-1;
	}
	else if (a == RIGHT) {
		x1 = x+w;
		y1 = y;
		x2 = x+w+1;
		y2 = y+h-1;
	}
	else if (a == UP) {
		x1 = x+1;
		y1 = y-1;
		x2 = x+w-1;
		y2 = y;
	}
	else if (a == DOWN) {
		x1 = x;
		y1 = y+h;
		x2 = x+w;
		y2 = y+h;
	}

	// pixels to tiles
	x1 /= 8;
	y1 /= 8;
	x2 /= 8;
	y2 /= 8;

	// something about flag (which is a param that I didn't put yet) idk what it is
}


void player_update()
{
	if (nyfw_inputKeyHeld(NYFW_KEY_LEFT)) {
		p.dx = -5.0f;
	}

	else if (nyfw_inputKeyHeld(NYFW_KEY_RIGHT)) {
		p.dx = 5.0f;
	}

	else
		p.dx = 0;
	
	p.x += p.dx;
	p.y += p.dy;
}


void player_animate()
{

}


