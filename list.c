#include "list.h"

List* newList(){
    List* l = (List*)malloc(sizeof(List));
    l->list = (Game**)malloc(sizeof(Game*)*INIT_SIZE);
    l->size = 0;
    l->max_size = INIT_SIZE;
    return l;
}

void pushList(List* l, Game* g){
    if(l->size >= l->max_size){
        l->max_size *= 2;
        l->list = realloc(l->list, l->max_size);
    }
    l->list[l->size++] = g;
}

void fitList(List* l){
    l->max_size = l->size;
    l->list = realloc(l->list, l->max_size);
}

void freeList(List* l){
    for(int i = 0; i < l->size; i++) freeGame(l->list[i]);
    free((void*)l->list);
    free((void*)l);
}