#include "list.h"

/*
 * Function: newList
 * ----------------------------
 *   Crea una lista de structs para contener los juegos.
 *
 *   No tiene parametros.
 *
 *   Returns: List*, nueva lista de structs creada.
 */
List* newList(){
    List* l = (List*)malloc(sizeof(List));
    l->list = (Game**)malloc(sizeof(Game*)*INIT_SIZE);
    l->size = 0;
    l->max_size = INIT_SIZE;
    return l;
}

/*
 * Function: pushList
 * ----------------------------
 *   Permite insertar un struct de juego en la lista.
 *
 *   List* l: lista de structs.
 *
 *   Returns: void, no retorna nada.
 */

void pushList(List* l, Game* g){
    if(l->size >= l->max_size){
        l->max_size *= 2;
        l->list = realloc(l->list, l->max_size);
    }
    l->list[l->size++] = g;
}

/*
 * Function: fitList
 * ----------------------------
 *   Ajusta el tamaño de la lista según su tamaño real.
 *
 *   List* l: lista de structs.
 *
 *   Returns: void, no retorna nada.
 */
void fitList(List* l){
    l->max_size = l->size;
    l->list = realloc(l->list, l->max_size);
}

/*
 * Function: freeList
 * ----------------------------
 *   Libera la memoria ocupada por la lista.
 *
 *   List* l: lista de structs.
 *
 *   Returns: void, no retorna nada.
 */
void freeList(List* l){
    for(int i = 0; i < l->size; i++) freeGame(l->list[i]);
    free((void*)l->list);
    free((void*)l);
}