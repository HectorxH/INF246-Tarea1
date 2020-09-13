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
    FILE* fp = fopen(g->path, "r");
    if(fp == NULL){
        printf("Error: Problema al abrir el archivo %s\n", g->path);
        exit(0);
    }

    printf("----------------------------------------\n");
    char buffer[MAX_PATH];
    fgets(buffer, MAX_PATH-1, fp);
    printf("Nombre:\n\t%s", buffer);

    fgets(buffer, MAX_PATH-1, fp);
    printf("Categorias:\n\t%s", buffer);

    fgets(buffer, MAX_PATH-1, fp);
    printf("Desarrollador:\n\t%s", buffer);

    fgets(buffer, MAX_PATH-1, fp);
    printf("Descripcion:\n\t%s", buffer);
    printf("----------------------------------------\n\n");

    fclose(fp);
    
    return;
}
