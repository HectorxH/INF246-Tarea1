#include <stdio.h>
#include <unistd.h>
#include "util.h"
#include <sys/stat.h>

char** category_list(char* str, int* N){
    int len = 1;
    for(int i = 0; str[i] != '\0'; i++){
        if(str[i] == ',') len++;
    }

    *N = len;
    char** categories = (char**)malloc(sizeof(char*)*len);

    int i = 0;
    char* token = strtok(str, ", ");
    char* category = (char*)malloc(sizeof(char)*MAX_STR_SIZE);
    strncpy(category, token, MAX_STR_SIZE);
    categories[i] = category;
    i++;
    token = strtok(NULL, ",");
    while(token != NULL) {
        category = (char*)malloc(sizeof(char)*MAX_STR_SIZE);
        strncpy(category, token+1, MAX_STR_SIZE);
        categories[i] = category;
        i++;
        token = strtok(NULL, ",");
    }

    return categories;
}


char* categorize(char* category, char* filename){
    int result;
    char* newdir = malloc(512);
    strcat(newdir, OBJDIR);
    strcat(newdir, "/");
    strcat(newdir, category);
    mkdir(newdir, 0700);
    strcat(newdir, "/");
    strcat(newdir, filename);
    result = rename(filename, newdir);
    return newdir;
}

