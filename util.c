#include <stdio.h>
#include <unistd.h>
#include "util.h"
#include <sys/stat.h>
#include <dirent.h>

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

char* categorize(char* category, char* filename, char* source){
    int result;
    char* newdir = malloc(512);
    strcat(newdir, OBJDIR);
    strcat(newdir, "/");
    strcat(newdir, category);
    // crea categoria nueva, si ya existe no hace nada
    mkdir(newdir, 0700);
    strcat(newdir, "/");
    strcat(newdir, filename);
    // mueve el txt desde source a objective
    result = rename(source, newdir);
    if(!result){
        printf("Error al crear la carpeta de categorización");
    }
    return newdir;
}

// REVISAR MEMORIA (posible fuga?)
void cleandir(char* path){
    DIR *dir;
    struct dirent *entry;
    if(!(dir = opendir(path))){
        return;
    }
    while ((entry = readdir(dir)) != NULL) {
        // ignora nombres con . y ..
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0)
            continue;
        // borra cualquier archivo que puede estar en carpeta
        if(entry->d_type == DT_REG){
            char *filepath = (char *) malloc(strlen(path) + strlen(entry->d_name) + 2);
            strcpy(filepath , path);
            strcat(filepath , "/");
            strcat(filepath , entry->d_name);
            remove(filepath);
            free(filepath);
        }
        // borrar carpeta, llamada recursiva
        else if(entry->d_type == DT_DIR){
            char *newpath = (char *) malloc(strlen(path) + strlen(entry->d_name) + 2);
            strcpy(newpath, path);
            strcat(newpath, "/");
            strcat(newpath, entry->d_name);
            uninstall(newpath);
            rmdir(newpath);
            free(newpath);
        }
    }
    rmdir(path);
    closedir(dir);
}
