#include "game.h"

/*
 * Function: newGame
 * ----------------------------
 *   Crea un struct de tipo juego y inicializa sus campos.
 *
 *   char* name: string con nombre de juego.
 *   char* path: string con direccion completa de juego.
 *   int n: la cantidad de categorias del juego.
 *
 *   Returns: Game*, retorna el juego creado.
 */
Game* newGame(char* name, char* path, int n_categories){
    Game* g = (Game*)malloc(sizeof(Game));

    strncpy(g->name, name, MAX_NAME);
    strncpy(g->path, path, MAX_PATH);
    g->n_categories = n_categories;

    return g;
}

/*
 * Function: compareGame
 * ----------------------------
 *   Función que permite comparar las cantidades de categorias de dos juegos.
 *
 *   const void* g1: primer juego
 *   const void* g2: segundo juego
 *
 *   Returns: int, diferencia entre las cantidades decategorias de dos juegos.
 */
int compareGame(const void* g1, const void* g2){
    return (*(Game**)g1)->n_categories - (*(Game**)g2)->n_categories;
}

/*
 * Function: freeGame
 * ----------------------------
 *   Libera la memoria asignada al struct de juego, pasado como parametro.
 *
 *   Game* g: el juego a liberar.
 *
 *   Returns: void, no retorna nada.
 */
void freeGame(Game* g){
    free((void*)g);
}

/*
 * Function: printGame
 * ----------------------------
 *   Muestra por pantalla los datos de campos de struct, según el formato dado.
 *
 *   Game* g: el juego cuyos datos se desea mostrar por pantalla.
 *
 *   Returns: void, no retorna nada.
 */
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
    printf("Categorias(%d):\n\t%s", g->n_categories, buffer);

    fgets(buffer, MAX_PATH-1, fp);
    printf("Desarrollador:\n\t%s", buffer);

    fgets(buffer, MAX_PATH-1, fp);
    printf("Descripción:\n\t%s", buffer);
    printf("----------------------------------------\n\n");

    fclose(fp);
    
    return;
}
