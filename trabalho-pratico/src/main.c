#include "../include/parser.h"
#include "../include/interpreter.h"
#include "../include/dataTypes.h"
#include "../include/catalogs.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define BUFFERSIZE 1000

int main(int argc,char **argv){
    if (argc < 2) {
        perror("Nao existe argumentos");
        return 1;
    }
    size_t argSize = 0;
    argSize = strlen(argv[1]);
    char * filePath = NULL;
    filePath = malloc(strlen(argv[1]) + 20); // malloc
    memset(filePath,'\0',argSize + 20);
    strncpy(filePath,argv[1],argSize);


    // Create Users Database
    strncat(filePath,"/users.csv",12); // ?
    filePath[argSize + 1 + 10 + 1] = '\0';

    FILE * userFile = NULL;
    userFile = fopen(filePath,"r"); // open

    FILE * userErrors = NULL;
    char * filePathUErrors = NULL;
    filePathUErrors = malloc(strlen(argv[1]) + 20); // malloc
    strncpy(filePathUErrors,"Resultados",14);
    strncat(filePathUErrors,"/users_errors.csv",18); // ?
    userErrors = fopen(filePathUErrors,"a"); // open
    if(userErrors == NULL) {perror("Users errors file did not open\n"); return 1;}

    char * userData = malloc(sizeof(char) * BUFFERSIZE); // malloc

    if(userData == NULL) { perror("Erro a alocar memoria na main"); return 1;}

    memset(userData, '\0', BUFFERSIZE);

    fseek(userFile,115,SEEK_SET);

    UsersDatabase uDatabase = initUsers(); // initDatabase

    while(fgets(userData,BUFFERSIZE,userFile)){

        User * uBuffer = NULL;

        int tamanhoUserData = verTamanhoLinha(userData);

        char * userDataClean = malloc(sizeof(char) * (tamanhoUserData +1)); // malloc

        strncpy(userDataClean,userData,tamanhoUserData);

        userDataClean[tamanhoUserData] = '\0';


        uBuffer = userCheck(userDataClean); // malloc

        if(uBuffer != NULL){
            char * idBuffer = getUserId(uBuffer); // malloc

            g_hash_table_insert(uDatabase,idBuffer,uBuffer);

            free(idBuffer); // free

            free(uBuffer); // free

        }else{ 
            fprintf(userErrors,"%s",userDataClean);
        }
        
        uBuffer = NULL;
        free(userDataClean);// free
    }
    
    fclose(userFile); // close
    free(filePathUErrors);  // free
    free(userData); // free
    fclose(userErrors); // close
    free(filePath); // free

    
    // Create Reservations Database
    strncpy(filePath,argv[1],argSize);
    strncat(filePath,"/reservations.csv",19);

    filePath[argSize + 1 + 17 + 1] = '\0';

    FILE * reservationsFile = NULL;
    reservationsFile = fopen(filePath,"r");

    FILE * reservationsErrors = NULL;
    char * filePathRErrors = NULL;
    filePathRErrors = malloc(argSize + 27);
    strncpy(filePathRErrors,"Resultados",14);
    strncat(filePathRErrors,"/reservations_errors.csv",25);
    reservationsErrors = fopen(filePathRErrors,"a+");
    if(!reservationsErrors) {perror("Reservations errors file did not open\n"); return 1;}

    char * reservationData = malloc(sizeof(char) * BUFFERSIZE);

    if(!reservationData) { perror("Erro a alocar memoria na main"); return 1;}

    memset(reservationData, '\0', BUFFERSIZE);

    ReservationsDatabase rDatabase = initReservations();

    while(fgets(reservationData,strlen(reservationData),reservationsFile)){

        Reservation * rBuffer = NULL;

        int tamanhoReservationData = verTamanhoLinha(reservationData);

        char reservationDataClean[tamanhoReservationData +1];

        strncpy(reservationDataClean,reservationData,tamanhoReservationData);

        reservationDataClean[tamanhoReservationData] = '\0';

        rBuffer = reservationCheck(reservationDataClean);

        reservationCheck(reservationDataClean);

    if(rBuffer != NULL){
            char * idBuffer = getReservId(rBuffer);

            g_hash_table_insert(rDatabase,idBuffer,rBuffer);

            free(idBuffer);

        }else{ 
            fprintf(reservationsErrors,"%s",reservationDataClean);
        }
        
            rBuffer = NULL;
    }
    
    fclose(reservationsFile);
    free(reservationData);
    free(filePath);


/*
    //Create Flights Database
    strcpy(filePath,argv[1]);
    strncat(filePath,"/",2);

    strcat(filePath,"flights.csv");

    FILE * flightFile = fopen(filePath,"r");

    char * flightData = malloc(sizeof(char) * BUFFERSIZE);

    if(!flightData) { perror("Erro a alocar memoria na main"); return 1;}

    memset(flightData, '\0', strlen(flightData));

    while(fgets(flightData,strlen(flightData),flightFile)){

        int tamanhoFlightData = verTamanhoLinha(flightData);

        char flightDataClean[tamanhoFlightData +1];

        strncpy(flightDataClean,flightData,tamanhoFlightData);

        flightDataClean[tamanhoFlightData] = '\0';

        fligthCheck(flightDataClean);

    }

    fclose(flightFile);

    // Create Passangers Database 

    strcpy(filePath,argv[1]);
    strncat(filePath,"/",2);

    strcat(filePath,"flights.csv");

    FILE * passangersFile = fopen(filePath,"r");

    char * passangersData = malloc(sizeof(char) * BUFFERSIZE);

    if(!passangersData) { perror("Erro a alocar memoria na main"); return 1;}

    memset(passangersData, '\0', strlen(passangersData));

    while(fgets(passangersData,strlen(passangersData),passangersFile)){

        int tamanhoPassangersData = verTamanhoLinha(passangersData);

        char passangersDataClean[tamanhoPassangersData +1];

        strncpy(passangersDataClean,passangersData,tamanhoPassangersData);

        passangersDataClean[tamanhoPassangersData] = '\0';

        passangerCheck(passangersDataClean);

    }

    fclose(passangersFile);


    // Read and execute commands, freeing after used
    
    //readEntryFile();

    // Free everything used
*/  destroyUsers(uDatabase); // destroy
    return 0;
}