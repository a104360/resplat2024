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
}