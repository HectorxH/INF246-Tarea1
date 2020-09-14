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

    //Lectura de juegos

    cleandir(OBJDIR);
    mkdir(OBJDIR,0700);
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

        char* path = categorize(categories[0], dp->d_name, curr_path);
        Game* g = newGame(name, path, n_categories);
        free((void*)path);

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

    //Ordenamiento de Juegos

    for(int i = 0; i < 5; i++){
        if(all_categories[i] == NULL) break;
        qsort(games_in_category[i]->list, games_in_category[i]->size, sizeof(Game*), compareGame);
    }

    //Inputs de Usuario

    int input;
    int curr_cat;
    int flag = 1;
    while(flag){
        
        if(flag == 1){
            int i;
            for(i = 0; i < 5; i++){
                if(all_categories[i] == NULL) break;
                printf("%d - %s/%s\n", i+1, OBJDIR, all_categories[i]);
            }
            printf("\n");

            printf("Elige una categoria (1-%d): ", i);
            scanf("%d", &input);

            if(input > i || input < 0){
                printf("Numero invalido, intentelo nuevamente...\n");
                continue;
            }

            if(input == 0){
                printf("\nChange Da World…\nMy Final Message.\nGoodbye.\n");
                break;
            }

            curr_cat = input-1;
            flag = 2;
        }
        else if(flag == 2){
            int j;
            for(j = 0; j < games_in_category[curr_cat]->size; j++){
                Game* g = games_in_category[curr_cat]->list[j];
                printf("%d - %s : %s", j+1, g->path, g->name);
            }
            printf("\n");

            printf("Elige una Juego (1-%d): ", j);
            scanf("%d", &input);

            if(input > j || input < 0){
                printf("Numero invalido, intentelo nuevamente...\n");
                continue;
            }

            if(input == 0){
                flag = 1;
                continue;
            }

            printGame(games_in_category[curr_cat]->list[input-1]);
        }
    }

    //Liberar Memoria

    for(int i = 0; i < 5; i++){
        if(all_categories[i] == NULL) break;
        freeList(games_in_category[i]);
        free((void*)all_categories[i]);
    }

    closedir(dir);
    cleandir(SCRDIR);

    return 0;
}
