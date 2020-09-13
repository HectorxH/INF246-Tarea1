#ifndef _LIST_H_
#define _LIST_H_

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "game.h"

#define INIT_SIZE 32

typedef struct{
    Game** list;
    int size;
    int max_size;
}List;

List* newList();

void pushList(List* l, Game* g);

void fitList(List* l);

void freeList(List* l);

#endif
