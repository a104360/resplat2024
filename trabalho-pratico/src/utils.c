#include "../include/utils.h"
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <stdio.h>


void ffree(void * ptr){
    if(ptr){
        free(ptr);
        ptr = NULL;
    }
}



void initArrays(void *** ptr, int max){
    *ptr = (void **)malloc(sizeof(void *) * max);
    for(int i = 0;i < max;(*ptr)[i] = NULL,i++);
}


int extendArray(void *** ptr,int old,int new){
    void ** nPtr = realloc(*ptr,sizeof(void *) * new);
    if(nPtr == NULL) return 0;
    *ptr = nPtr;
    for(int i = old;i < new;(*ptr)[i] = NULL,i++);
    return 1;
}