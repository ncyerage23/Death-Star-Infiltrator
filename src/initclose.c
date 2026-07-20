/* 
 * DEATH STAR INFILTRATOR -- init/close functions
 *
 */

#include "deathstar.h"

Control c;
Player p;


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
	/* ----- LEVEL ----- */
	if (!nyfw_loadNYMG(&c.level, "assets/proto.nymap")) return 0;

	/* ----- LEVEL SCREEN ----- */	
	uint16_t* level_scr_pixels = malloc(2 * 128 * 128);	// 128x128 pixels: 16x16 tiles at normal resolution
	if (!level_scr_pixels) return 0;
	c.level_screen = nyfw_canvas(level_scr_pixels, 128, 128, 128);
	nyfw_canvasClear(c.level_screen);

	/* ----- DRAWING TO LEVEL SCREEN ----- */
	NYFW_Canvas tiles = load_tiles();
	for (int j = 0; j < 16; j++) {
		for (int i = 0; i < 16; i++) {
			int ti = c.level.pixels[j * 16 + i];
			if (ti == 0) continue;

			NYFW_Rect srcr = { 8 * (ti%4), 8 * (ti/4), 8, 8 };
			NYFW_Rect dstr = { i*8, j*8, 8, 8 };
			nyfw_canvasBlit(tiles, &srcr, c.level_screen, &dstr);
		}
	}

	return 1;
}


int load_sprites()
{
	nyfw_loadNYMG(&c.player_sprite[0], "assets/sprites/player_1.nymg");
	nyfw_loadNYMG(&c.player_sprite[1], "assets/sprites/player_2.nymg");
	nyfw_loadNYMG(&c.player_sprite[2], "assets/sprites/player_3.nymg");

	return 1;
}


/* ----- MAIN INIT/CLOSE ----- */
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
	
	uint16_t* game_pixels = malloc(2 * 128 * 128);
	c.game_layer = nyfw_canvas(game_pixels, 128, 128, 128);
	nyfw_canvasClear(c.game_layer);
	
	/* ----- PLAYER STRUCT ----- */
	p = (Player){
		.sp = 0,
		.x = 59.0f,	.y = 59.0f,
		.w = 8,		.h = 8,
		.flip = false,

		.dx = 0.0f,	.dy = 0.0f,
		.max_dx = 2.0f,	.max_dy = 3.0f,
		.acc = 0.5f,
		.boost = 4.0f,
		
		.anim = 0,
		.running = false,
		.jumping = false,
		.falling = false,
		.sliding = false,
		.landed = false,
	};


	return 1;
}


void ds_close()
{
	free(c.level.pixels);
	free(c.level_screen.pixels);

	free(c.player_sprite[0].pixels);
	free(c.player_sprite[1].pixels);
	free(c.player_sprite[2].pixels);

	nyfw_inputClose();
	nyfw_windowClose();
}
