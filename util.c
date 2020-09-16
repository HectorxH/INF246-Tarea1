#include "util.h"

/*
 * Function: category_list
 * ----------------------------
 *   Funcion analogo de .split(",") de Python. Separa el string 
 *	 original que contiene las categorias separadas por comas.
 *
 *   char* str: string con categorias separadas por comas.
 *   int* N: parametro para guardar la cantidad de categorias del juego.
 *
 *   Returns: char**, retorna lista de strings de categorias.
 */
char** category_list(char* str, int* N){
    str[strlen(str)-1] = '\0';

    int len = 1;
    for(int i = 0; str[i] != '\0'; i++){
        if(str[i] == ',') len++;
    }

    *N = len;
    char** categories = (char**)malloc(sizeof(char*)*len);

    int i = 0;
    char* token = strtok(str, ",");
    categories[i] = (char*)malloc(sizeof(char)*MAX_STR_SIZE);
    strncpy(categories[i], token, MAX_STR_SIZE);
    i++;
    token = strtok(NULL, ",");
    while(token != NULL) {
        categories[i] = (char*)malloc(sizeof(char)*MAX_STR_SIZE);
        strncpy(categories[i], token+1, MAX_STR_SIZE);
        i++;
        token = strtok(NULL, ",");
    }

    return categories;
}

/*
 * Function: categorize
 * ----------------------------
 *   Borra las carpetas y sus contenidos. Funciona recursivamente para
 *	 borrar carpetas anidadas.
 *
 *   char* category: string con la categoria a que pertenece el juego.
 *   char* filename: nombre de archivo a mover, corresponde a nombre de juego.
 *   char* source: direccion completa donde se encuentra el juego originalamente.
 *
 *   Returns: char*, retorna la nueva direccion completa al archivo categorizado.
 */
char* categorize(char* category, char* filename, char* source){
    int result;
    char* newdir = malloc(sizeof(char)*512);
    strncpy(newdir, OBJDIR, 511);
    strcat(newdir, "/");
    strcat(newdir, category);
    // Crea categoria nueva, si ya existe no hace nada
    mkdir(newdir, 0700);
    strcat(newdir, "/");
    strcat(newdir, filename);
    // Mueve el .txt desde source a objective
    result = rename(source, newdir);
    if(result != 0){
        printf("Error al crear la carpeta de categorización\n");
    }
    return newdir;
}

/*
 * Function: cleandir
 * ----------------------------
 *   Borra las carpetas y sus contenidos. Funciona recursivamente para
 *	 borrar carpetas anidadas.
 *
 *   char* path: direccion completa a la carpeta a borrar.
 *
 *   Returns: void, no retorna nada. 
 */
void cleandir(char* path){
    DIR *dir;
    struct dirent *entry;
    if(!(dir = opendir(path))){
        return;
    }
    while ((entry = readdir(dir)) != NULL) {
        // Ignora nombres de directorios con . y ..
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0)
            continue;
        // Borra cualquier archivo que puede estar en carpeta
        if(entry->d_type == DT_REG){
            char *filepath = (char*) malloc(strlen(path)+strlen(entry->d_name)+2);
            strcpy(filepath , path);
            strcat(filepath , "/");
            strcat(filepath , entry->d_name);
            remove(filepath);
            free(filepath);
        }
        // Llamada recursiva para borrar las subcarpetas y la carpeta contenedora
        else if(entry->d_type == DT_DIR){
            char *newpath = (char*) malloc(strlen(path)+strlen(entry->d_name)+2);
            strcpy(newpath, path);
            strcat(newpath, "/");
            strcat(newpath, entry->d_name);
            cleandir(newpath);
            rmdir(newpath);
            free(newpath);
        }
    }
    rmdir(path);
    closedir(dir);
}

