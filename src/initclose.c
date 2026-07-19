/* 
 * DEATH STAR INFILTRATOR -- init/close functions
 *
 */

#include "deathstar.h"

Control c;
Player p;


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
