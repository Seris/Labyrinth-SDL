#ifndef LABYRINTH_H
#define LABYRINTH_H

#include <SDL.h>
#include "map.h"

#define WIN_WIDTH 300
#define WIN_HEIGHT 300

void labyrinth(struct Map*);
void onKeyPressed(SDL_Scancode, struct Map*);
int canPlayerMove(struct Coordinate* newPosition, struct Map* map);
void movePlayerTo(struct Coordinate*, struct Map*);
void IAshortestPath(struct Map *map);

#endif