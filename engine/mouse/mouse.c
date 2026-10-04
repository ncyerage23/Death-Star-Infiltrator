/*
 * Mouse source
 *
 * Yeah. Only handles mouse movement, not clicking right now. 
 *
 */


/* ----- INCLUDES ----- */
#include "canvas/allcanvas.h"
#include "core/input.h"
#include <stdint.h>
#include <stdlib.h>


/* ----- MOUSE STRUCT ----- */
static struct {
	NYFW_Canvas icon;
	int scale;

	float x_sens;
	float y_sens;

	int x, y;
	int dx, dy;

	NYFW_Canvas scr;
} mouse;


/* ----- INIT/CLOSE ----- */
int mouse_init(const char* icon_path, int scale, NYFW_Canvas scr)
{
	NYFW_Canvas loaded_icon;
	if (!nyfw_loadNYMG(&loaded_icon, icon_path)) return 0;

	if (scale > 1) 
		mouse.icon = nyfw_canvasScaleUp(loaded_icon, scale);
	else
		mouse.icon = loaded_icon;

	mouse.x_sens = 1.5;
	mouse.y_sens = 2.0;

	mouse.x = 10;
	mouse.y = 10;

	mouse.dx = 0;
	mouse.dy = 0;

	mouse.scr = scr;

	return 1;
}


void mouse_close()
{
	free(mouse.icon.pixels);
}


/* ----- MORE FUNCTIONS! ----- */
void mouse_setSensitivity(float xs, float ys)
{
	mouse.x_sens = xs;
	mouse.y_sens = ys;
}

int mouse_getX() { return mouse.x; }
int mouse_getY() { return mouse.y; }

int mouse_getFutX() { return mouse.x + mouse.dx; }
int mouse_getFutY() { return mouse.y + mouse.dy; }




/* ----- Update stuff ----- */
void mouse_getDelta()
{
	mouse.dx = (float)nyfw_inputMouseDX() * mouse.x_sens;
	mouse.dy = (float)nyfw_inputMouseDY() * mouse.y_sens;
}

void mouse_update()
{
	mouse.x += mouse.dx;
	mouse.y += mouse.dy;
}


void mouse_draw(int realdraw)
{
	int icnw = mouse.icon.width;
	int icnh = mouse.icon.height;
	
	uint16_t c = (realdraw) ? 0xffff : 0x0000;

	for (int j = 0; j < icnh; j++)
		for (int i = 0; i < icnw; i++)
			if (CANV_PIXEL(mouse.icon, i, j) != 0)
				nyfw_canvSetPixel(mouse.scr, mouse.x + i, mouse.y + j, c);

}











