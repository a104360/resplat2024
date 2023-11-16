#include "../include/parser.h"
#include "../include/interpreter.h"
#include "../include/dataTypes.h"
#include "../include/output.h"
#include <stdio.h>

int main(int argc,char **argv){
    
    
    char * filePath = malloc(sizeof(char) * 50);

    strcpy(filePath,argv[1]);
    strncat(filePath,"/",2);

    // Create Users Database
    strncat(filePath,"users.csv",10);

    FILE * file = fopen(filePath,"r");

    fclose(file);

    // Create Reservations Database

    //Create Flights Database

    // Create Passangers Database 

    free(filePath);

    // Read and execute commands, freeing after used


    // Free everything used

    return 0;
}