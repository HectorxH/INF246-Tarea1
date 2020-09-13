#include "util.h"

char** category_list(char* str, int* N){
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
