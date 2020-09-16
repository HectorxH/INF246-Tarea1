#ifndef _UTIL_H_
#define _UTIL_H_

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include "util.h"
#include <sys/stat.h>
#include <dirent.h>

#define MAX_STR_SIZE 256
#define SCRDIR "./games"
#define OBJDIR "./Steam"

char** category_list(char* str, int* N);

char* categorize(char* category, char* filename, char* source);

void cleandir(char* path);

#endif
