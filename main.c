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

    // Se borra la carpeta Steam si ya existe y se crea una vacia.
    cleandir(OBJDIR);
    mkdir(OBJDIR,0700);
    
    // Se inicia la lectura de archivos .txt desde la carpeta ./games
    // Esta carpeta debe estar en el directorio en el cual se ubica el ejecutable.
    DIR* dir = opendir(SCRDIR);
    if(dir == NULL){
        printf("Error: No se encuentra la carpeta ./games\n");
        return 0;
    }
    struct dirent* dp;

    char* all_categories[5] = {NULL, NULL, NULL, NULL, NULL};
    List* games_in_category[5];

    while((dp = readdir(dir)) != NULL){
        // Se ignoran los directorios . y ..
        if(!strcmp(dp->d_name, ".") || !strcmp(dp->d_name, "..")) continue;

        char curr_path[MAX_PATH];
        snprintf(curr_path, sizeof(curr_path), "%s/%s", SCRDIR, dp->d_name);

        FILE* fp = fopen(curr_path, "r");
        if(fp == NULL){
            printf("Error: Problema al abrir el archivo %s\n", curr_path);
            exit(0);
        }

        // Se guarda el nombre de juego
        char name[MAX_NAME];
        fgets(name, MAX_NAME-1, fp);

        // Se guarda el string de categorias de juego
        char str_categories[MAX_STR_SIZE];
        fgets(str_categories, MAX_STR_SIZE-1, fp);

        fclose(fp);

        int n_categories;
        // Se obtiene la lista de categorias. Se mueve el juego a la carpeta
        // que corresponde a su primera categoria de la lista antes obtenida.
        char** categories = category_list(str_categories, &n_categories);
        char* path = categorize(categories[0], dp->d_name, curr_path);

        // Se inicializa el struct de juego.
        Game* g = newGame(name, path, n_categories);
        free((void*)path);


        // Se guarda la categoria en la lista de categorias para marcar su existencia.
        // Se inserta el juego en la lista correspondiente a su categoria para posterior ordenamiento.
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

        // Liberación de memoria ocupada
        for(int i = 0; i < n_categories; i++) free(categories[i]);
        free((void*)categories);
    }

    // Utilizando el quicksort, se ordenan los juegos en base a la cantidad de categorias.
    // El proceso se repite para las 5 categorias.
    for(int i = 0; i < 5; i++){
        if(all_categories[i] == NULL) break;
        qsort(games_in_category[i]->list, games_in_category[i]->size, sizeof(Game*), compareGame);
    }

    // Parte de la aplicación standalone de consola. Funciona en base al input de usuario.
    int input;
    int curr_cat;
    int flag = 1;
    while(flag){
        // Si flag es 1, el usuario debe ver la lista de categorias.
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
            // Al ingresar 0, se cierra la aplicación.
            if(input == 0){
                printf("\nChange Da World…\nMy Final Message.\nGoodbye.\n");
                break;
            }
            curr_cat = input-1;
            flag = 2;
        }
        // Si flag es 2, el usuario debe ver juegos ordenados de la categoria elegida.
        else if(flag == 2){
            int j;
            // Se muestran los juegos según la categoría actual elegida.
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
            // Al ingresar 0, el usuario vuelve a ver la lista de categorias.
            if(input == 0){
                flag = 1;
                continue;
            }
            // Se muestra la información de juego elegido.
            printGame(games_in_category[curr_cat]->list[input-1]);
        }
    }

    // Se libera la memoria de heap utilizada.
    for(int i = 0; i < 5; i++){
        if(all_categories[i] == NULL) break;
        freeList(games_in_category[i]);
        free((void*)all_categories[i]);
    }

    // Se cierra el directorio y se borra la carpeta ./games pues esta ya está vacia.
    closedir(dir);
    cleandir(SCRDIR);

    return 0;
}
