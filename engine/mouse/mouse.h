/*
 * MOUSE MODULE
 *
 * This is an abstraction for the mouse. For now, at least,
 * I'll use a mouse .nymg for the icon. So yeah. Pretty simple stuff.
 *
 */


#ifndef MOUSE_H
#define MOUSE_H

#include "canvas/canvas.h"
#include <stdint.h>


int mouse_init(const char* icon_path, int scale, NYFW_Canvas scr);
void mouse_close();

void mouse_setSensitivity(float xs, float ys);
void mouse_getDelta();
int mouse_getX();
int mouse_getY();
int mouse_getFutX();
int mouse_getFutY();


void mouse_update();
void mouse_draw(int realdraw);





#endif

