#ifndef _GAME_H_
#define _GAME_H_

#include <string.h>
#include <stdlib.h>

#define MAX_NAME 64
#define MAX_PATH 256

typedef struct{
    char name[MAX_NAME];
    char path[MAX_PATH];
    int n_categories;
}Game;

Game* newGame(char* path);

int compareGame(Game* g1, Game* g2);

void freeGame(Game* g);

void printGame(Game* g)

#endif
