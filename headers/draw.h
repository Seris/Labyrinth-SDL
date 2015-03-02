#ifndef DRAW_H
#define DRAW_H

#include <SDL.h>
#include "map.h"

void drawMap(struct Map*);
void cleanRenderer(int red, int green, int blue, int alpha, SDL_Renderer* renderer);

#endif