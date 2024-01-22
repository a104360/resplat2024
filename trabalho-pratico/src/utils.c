#include "../include/utils.h"
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <stdio.h>


void ffree(void ** ptr){
    if(*ptr){
        free(*ptr);
        *ptr = NULL;
    }
}




void initArrays(void *** ptr, int max){
    *ptr = (void **)malloc(sizeof(void *) * max);
    for(int i = 0;i < max;(*ptr)[i] = NULL,i++);
}


int extendArray(void ***ptr, int old, int new) {
    *ptr = realloc(*ptr, sizeof(void *) * new);

    if (*ptr == NULL)
        return 0;
    for (int i = old; i < new; (*ptr)[i++] = NULL);

    return 1;
}
