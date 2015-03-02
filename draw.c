#include <stdio.h>
#include <SDL.h>
#include "map.h"
#include "draw.h"
#include "objects.h"
#include "labyrinth.h"

void cleanRenderer(int red, int green, int blue, int alpha, SDL_Renderer* renderer){
    SDL_SetRenderDrawColor(renderer, red, green, blue, alpha);
    SDL_RenderClear(renderer);
}

void drawAllMap(struct Map* map){
    cleanRenderer(0x5F, 0x38, 0x0D, 255, map->renderer);

    SDL_Rect srcrect;
    srcrect.w = WIN_WIDTH / map->columns;
    srcrect.h = WIN_HEIGHT / map->lines;

    int column, line, object;
    for (column = 0; column < map->columns; ++column){
        srcrect.x = column * srcrect.w;

        for(line = 0; line < map->lines; ++line){
            srcrect.y = line * srcrect.h;

            object = map->map[column][line];
            if(object != -1){
                if(SDL_RenderCopy(map->renderer, getTextureFromID(object), NULL, &srcrect) < 0){
                    printf("SDL RenderCopy Error: %s\n", SDL_GetError());
                }
            }
        }
    }
    
    srcrect.x = map->exit.column * srcrect.w;
    srcrect.y = map->exit.line * srcrect.h;
    SDL_RenderCopy(map->renderer, getTextureFromID(2), NULL, &srcrect);

    srcrect.x = map->player.column * srcrect.w;
    srcrect.y = map->player.line * srcrect.h;
    SDL_RenderCopy(map->renderer, getTextureFromID(1), NULL, &srcrect);

}