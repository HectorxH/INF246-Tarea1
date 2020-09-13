#include "game.h"


Game* newGame(char* name, char* path, int n_categories){
    Game* g = (Game*)malloc(sizeof(Game));

    strncpy(g->name, name, MAX_NAME);
    strncpy(g->path, path, MAX_PATH);
    g->n_categories = n_categories;

    return g;
}

int compareGame(Game* g1, Game* g2){
    return g1->n_categories - g2->n_categories;
}

void freeGame(Game* g){
    free((void*)g);
}

void printGame(Game* g){
    printf("WIP\n");
    return;
}
