#include "util.h"
#include "game.h"
#include "list.h"
#include <stdio.h>
#include <dirent.h>

#define MAX_NAME 256
#define MAX_PATH 512
#define MAX_STR_SIZE 256
#define SCRDIR "./games"
#define OBJDIR "./Steam"

int main(){
    DIR* dir = opendir(SCRDIR);
    if(dir == NULL){
        printf("Error: No se encuentra la carpeta ./games\n");
        return 0;
    }
    struct dirent* dp;

    char* all_categories[5] = {NULL, NULL, NULL, NULL, NULL};
    List* games_in_category[5];

    while((dp = readdir(dir)) != NULL){
        if(!strcmp(dp->d_name, ".") || !strcmp(dp->d_name, "..")) continue;

        char curr_path[MAX_PATH];
        snprintf(curr_path, sizeof(curr_path), "%s/%s", SCRDIR, dp->d_name);

        FILE* fp = fopen(curr_path, "r");
        if(fp == NULL){
            printf("Error: Problema al abrir el archivo %s\n", curr_path);
            exit(0);
        }

        char name[MAX_NAME];
        fgets(name, MAX_NAME-1, fp);

        char str_categories[MAX_STR_SIZE];
        fgets(str_categories, MAX_STR_SIZE-1, fp);

        fclose(fp);

        int n_categories;
        char** categories = category_list(str_categories, &n_categories);

        Game* g = newGame(name, curr_path, n_categories);


        // char* path = categorize(categories[0], dp->d_name, curr_path);

        for(int i = 0; i < 5; i++){
            if(all_categories[i] == NULL){
                all_categories[i] = (char*)malloc(sizeof(char)*MAX_STR_SIZE);
                strncpy(all_categories[i], categories[0], MAX_STR_SIZE);
                games_in_category[i] = newList();
                pushList(games_in_category[i], g);
                break;
            }
            else if(!strcmp(categories[0], all_categories[i])){
                pushList(games_in_category[i], g);
                break;
            }
        }

        for(int i = 0; i < n_categories; i++) free(categories[i]);
        free((void*)categories);
    }

    for(int i = 0; i < 5; i++){
        if(all_categories[i] == NULL) break;
        printf("\n\n\n\n-------------------------------------------------------------------------------\n");
        printf("\t\tCategoria: %s\n", all_categories[i]);
        printf("-------------------------------------------------------------------------------\n\n");
        qsort(games_in_category[i]->list, games_in_category[i]->size, sizeof(Game*), compareGame);
        for(int j = 0; j < games_in_category[i]->size; j++){
            printGame(games_in_category[i]->list[j]);
        }
        freeList(games_in_category[i]);
    }

    closedir(dir);


    return 0;
}
