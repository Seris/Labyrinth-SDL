#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>

#include <SDL.h>
#include <SDL_image.h>
#include "labyrinth.h"
#include "map.h"

struct Map* loadMap(const char* src, SDL_Renderer *renderer){
    int fd = open(src, O_RDONLY);
    if(fd == -1){
        perror("open");
        exit(EXIT_FAILURE);
    }

    struct stat stat;
    if(fstat(fd, &stat) == -1){
        perror("stat");
        exit(EXIT_FAILURE);
    }

    if(stat.st_size < 14){
        fprintf(stderr, "Corrupted map file");
        exit(EXIT_FAILURE);
    }

    int16_t version, lines, columns;

    read(fd, &version, 2);
    if(version != 1){
        fprintf(stderr, "Incompatible/Corrupted map file");
        exit(EXIT_FAILURE);
    }

    struct Map *map;
    map = malloc(sizeof(struct Map));

    read(fd, &map->columns, 2);
    read(fd, &map->lines, 2);

    read(fd, &map->player.column, 2);
    read(fd, &map->player.line, 2);
    read(fd, &map->exit.column, 2);
    read(fd, &map->exit.line, 2);

    map->size = map->columns * map->lines;
    map->renderer = renderer;

    if(stat.st_size < (14 + map->size)){
        fprintf(stderr, "Corrupted map file");
        exit(EXIT_FAILURE);
    }

    int8_t* rawMap = calloc(map->size, sizeof(int8_t));
    read(fd, rawMap, map->size);

    map->map = calloc(map->columns, sizeof(int8_t*));

    int column, line;
    for(column = 0; column < map->columns; column++){
        map->map[column] = (int8_t*) calloc(map->lines, sizeof(int8_t));
        for(line = 0; line < map->lines; line++){
            map->map[column][line] = rawMap[(map->lines * column + line)];
        }
    }

    free(rawMap);

    return map;
}

void freeMap(struct Map* map){
    int i;
    for(i = 0; i < map->columns; i++){
        free(map->map[i]);
    }

    SDL_DestroyRenderer(map->renderer);

    free(map->map);
    free(map);
}

int main(int argc, char* argv[]){
    SDL_Window* window;
    SDL_Renderer* renderer;    

    int img_flags = IMG_INIT_PNG;

    SDL_Init(SDL_INIT_VIDEO);
    if(IMG_Init(img_flags) & img_flags != img_flags){
        fprintf(stderr, "IMG_Init: Failed to load PNG Support\n%s\n", IMG_GetError());
        return 1;
    }

    if(SDL_CreateWindowAndRenderer(WIN_WIDTH, WIN_HEIGHT, 0, &window, &renderer) == 1){
        fprintf(stderr, "SDL Error: %s\n", SDL_GetError());
        exit(EXIT_FAILURE);
    } else {
        SDL_ClearError();
    }

    int playerPos[2] = {1, 1}, exitPos[2] = {8, 8};
    struct Map *map = loadMap("./map", renderer);

    labyrinth(map);

    SDL_DestroyWindow(window);
    SDL_Quit();

    freeMap(map);

    return EXIT_SUCCESS;
}
