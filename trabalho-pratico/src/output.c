#include "../include/output.h"
#include <stdio.h>

FILE *createFile (const char* nome) {
    FILE *file = fopen(nome, "w");
    if (file == NULL) {
        perror("ERRO\n");
        exit(1);
    }
    return file;
}

void writeDataFile (FILE *file,const char *data){
    if (file != NULL) {
        fprintf(file, "%s", data);
    } else {
    fprintf(stderr, "ERRO\n");
    }
}