#include "../include/parser.h"
#include "../include/interpreter.h"
#include "../include/dataTypes.h"
#include <stdio.h>

#define BUFFERSIZE 1000

int main(int argc,char **argv){
    
    char * folder_path = argv[1];
    char * filePath = malloc(sizeof(char) * 50);

    strcpy(filePath,folder_path);
    strncat(filePath,"/",2);



    // Create Users Database
    strcat(filePath,"users.csv");

    FILE * userFile = fopen(filePath,"r");

    char * userData = malloc(sizeof(char) * BUFFERSIZE);

    if(!userData) { perror("Erro a alocar memoria na main"); return;}

    memset(userData, '\0', strlen(userData));

    while(fgets(userData,strlen(userData),userFile)){

        int tamanhoUserData = verTamanhoLinha(userData);

        char userDataClean[tamanhoUserData +1];

        strncpy(userDataClean,userData,tamanhoUserData);

        userDataClean[tamanhoUserData] = '\0';

        userCheck(userDataClean);

    }

    fclose(userFile);



    // Create Reservations Database
    strcpy(filePath,folder_path);
    strncat(filePath,"/",2);

    strcat(filePath,"reservations.csv");

    FILE * reservationFile = fopen(filePath,"r");

    char * reservationData = malloc(sizeof(char) * BUFFERSIZE);

    if(!reservationData) { perror("Erro a alocar memoria na main"); return;}

    memset(reservationData, '\0', strlen(reservationData));

    while(fgets(reservationData,strlen(reservationData),reservationFile)){

        int tamanhoReservationData = verTamanhoLinha(reservationData);

        char reservationDataClean[tamanhoReservationData +1];

        strncpy(reservationDataClean,reservationData,tamanhoReservationData);

        reservationDataClean[tamanhoReservationData] = '\0';

        reservationCheck(reservationDataClean);

    }

    fclose(reservationFile);



    //Create Flights Database
    strcpy(filePath,folder_path);
    strncat(filePath,"/",2);

    strcat(filePath,"flights.csv");

    FILE * flightFile = fopen(filePath,"r");

    char * flightData = malloc(sizeof(char) * BUFFERSIZE);

    if(!flightData) { perror("Erro a alocar memoria na main"); return;}

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

    strcpy(filePath,folder_path);
    strncat(filePath,"/",2);

    strcat(filePath,"flights.csv");

    FILE * passangersFile = fopen(filePath,"r");

    char * passangersData = malloc(sizeof(char) * BUFFERSIZE);

    if(!passangersData) { perror("Erro a alocar memoria na main"); return;}

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
    
    readEntryFile();

    // Free everything used

    return 0;
}