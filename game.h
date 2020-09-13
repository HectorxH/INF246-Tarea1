#ifndef _GAME_H_
#define _GAME_H_

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <dirent.h>

#define MAX_NAME 256
#define MAX_PATH 512

typedef struct{
    char name[MAX_NAME];
    char path[MAX_PATH];
    int n_categories;
}Game;

Game* newGame(char* name, char* path, int n_categories);

int compareGame(const void* g1, const void* g2);

void freeGame(Game* g);

void printGame(Game* g);

#endif
