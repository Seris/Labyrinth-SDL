#ifndef OBJECTS_H
#define OBJECTS_H

#define OBJECTS_COUNT 3

int initObjects(SDL_Renderer* renderer);
void freeObjects(void);

SDL_Texture* getTextureFromID(int);

#endif