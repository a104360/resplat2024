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
    filePath = malloc(argSize + 20); // malloc
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


    UsersDatabase uDatabase = initUsers(); // initDatabase

    fgets(userData,BUFFERSIZE,userFile);

    fprintf(userErrors,"%s",userData);

    while(fgets(userData,BUFFERSIZE,userFile)){

        User * uBuffer = NULL;

        int tamanhoUserData = verTamanhoLinha(userData);

        char * userDataClean = malloc(sizeof(char) * (tamanhoUserData +1)); // malloc

        strncpy(userDataClean,userData,tamanhoUserData);

        userDataClean[tamanhoUserData] = '\0';


        uBuffer = userCheck(userDataClean); // malloc

        if(uBuffer != NULL){
            char * idBuffer = getUserId(uBuffer); // malloc

            //g_hash_table_insert(uDatabase,idBuffer,uBuffer);
            insertUser(uDatabase,uBuffer);

            free(idBuffer); // free
            idBuffer = NULL;

            free(uBuffer); // free

        }else{ 
            fprintf(userErrors,"%s",userDataClean);
        }
        
        uBuffer = NULL;
        free(userDataClean);// free
        userDataClean = NULL;
    }
    
    fclose(userFile); // close
    userFile = NULL;
    free(filePathUErrors);  // free
    filePathUErrors = NULL;
    free(userData); // free
    userData = NULL;
    fclose(userErrors); // close
    userErrors = NULL;

    memset(filePath,'\0',argSize + 20);
  
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

    fgets(reservationData,BUFFERSIZE,reservationsFile);

    fprintf(reservationsErrors,"%s",reservationData);

    while(fgets(reservationData,BUFFERSIZE,reservationsFile)){

        Reservation * rBuffer = NULL;

        int tamanhoReservationData = verTamanhoLinha(reservationData);

        char * reservationDataClean = malloc(sizeof(char) * (tamanhoReservationData +1));

        strncpy(reservationDataClean,reservationData,tamanhoReservationData);

        reservationDataClean[tamanhoReservationData] = '\0';

        rBuffer = reservationCheck(reservationDataClean);

        //reservationCheck(reservationDataClean);

    if(rBuffer != NULL){
            char * idBuffer = NULL;
            if(rBuffer != NULL) getReservId(rBuffer);

            //g_hash_table_insert(rDatabase,idBuffer,rBuffer);
            insertReserv(rDatabase,rBuffer);

            free(idBuffer);
            idBuffer = NULL;
            free(rBuffer);
            rBuffer = NULL;

        }else{ 
            fprintf(reservationsErrors,"%s",reservationDataClean);
        }
        
            rBuffer = NULL;
            free(reservationDataClean);
            reservationDataClean = NULL;
    }
    
    fclose(reservationsFile); // close
    reservationsFile = NULL;
    free(filePathRErrors);  // free
    filePathRErrors = NULL;
    free(reservationData); // free
    reservationData = NULL;
    fclose(reservationsErrors); // close
    reservationsErrors = NULL;
    //free(filePath); // free

    memset(filePath,'\0',argSize + 20);
  

    //Create Flights Database
    strncpy(filePath,argv[1],argSize);
    strncat(filePath,"/flights.csv",14);

    FILE * flightFile = NULL;
    flightFile = fopen(filePath,"r");

    FILE * flightsErrors = NULL;
    char * filePathFErrors = NULL;
    filePathFErrors = malloc(argSize + 27);
    strncpy(filePathFErrors,"Resultados",14);
    strncat(filePathFErrors,"/flights_errors.csv",25);
    flightsErrors = fopen(filePathFErrors,"a+");
    if(!flightsErrors) {perror("Flights errors file did not open\n"); return 1;}

    char * flightData = malloc(sizeof(char) * BUFFERSIZE);

    if(!flightData) { perror("Erro a alocar memoria na main"); return 1;}

    memset(flightData, '\0', BUFFERSIZE);

    FlightsDatabase fDatabase = initFlights();

    while(fgets(flightData,BUFFERSIZE,flightFile)){

        Flight * fBuffer = NULL;

        int tamanhoFlightData = verTamanhoLinha(flightData);

        char flightDataClean[tamanhoFlightData +1];

        strncpy(flightDataClean,flightData,tamanhoFlightData);

        flightDataClean[tamanhoFlightData] = '\0';

        fBuffer = fligthCheck(flightDataClean);

        //fligthCheck(flightDataClean);

        if(fBuffer != NULL){
            char * idBuffer = getFlightId(fBuffer);

            //g_hash_table_insert(fDatabase,idBuffer,fBuffer);
            insertFlight(fDatabase,fBuffer);

            free(idBuffer);
            idBuffer = NULL;

            free(fBuffer);
            fBuffer = NULL;

        }else{ 
            fprintf(flightsErrors,"%s",flightDataClean);
        }
        
            fBuffer = NULL;

    }

    fclose(flightFile); // close
    flightFile = NULL;
    free(filePathFErrors);  // free
    filePathFErrors = NULL;
    free(flightData); // free
    flightData = NULL;
    fclose(flightsErrors); // close
    flightsErrors = NULL;
    free(filePath); // free
    filePath = NULL;

    // Create Passangers Database 
/*
    strncpy(filePath,argv[1],argSize);
    strncat(filePath,"/passangers.csv",17);

    FILE * passangersFile = NULL;
    passangersFile = fopen(filePath,"r");

    FILE * passangersErrors = NULL;
    char * filePathPErrors = NULL;
    filePathPErrors = malloc(argSize + 27);
    strncpy(filePathPErrors,"Resultados",14);
    strncat(filePathPErrors,"/passangers_errors.csv",25);
    passangersErrors = fopen(filePathPErrors,"a+");
    if(!passangersErrors) {perror("Passangers errors file did not open\n"); return 1;}

    char * passangersData = malloc(sizeof(char) * BUFFERSIZE);

    if(!passangersData) { perror("Erro a alocar memoria na main"); return 1;}

    memset(passangersData, '\0', strlen(passangersData));

    PassangersDatabase * pDatabase = initPassangers();

    while(fgets(passangersData,strlen(passangersData),passangersFile)){

        int tamanhoPassangersData = verTamanhoLinha(passangersData);

        char passangersDataClean[tamanhoPassangersData +1];

        strncpy(passangersDataClean,passangersData,tamanhoPassangersData);

        passangersDataClean[tamanhoPassangersData] = '\0';

        passangerCheck(passangersDataClean);

    }

    fclose(passangersFile);
*/

    // Read and execute commands, freeing after used
    
    //readEntryFile();

    // Free everything used
    //free(filePath); // free
    destroyUsers(uDatabase); // destroy
    destroyFlights(fDatabase);
    destroyReservs(rDatabase);
    return 0;
}