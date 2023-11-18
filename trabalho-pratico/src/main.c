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
    filePath = malloc(argSize + 20);

    strncpy(filePath,argv[1],argSize);


    // Create Users Database
    strncat(filePath,"/users.csv",12);
    filePath[argSize + 1 + 10 + 1] = '\0';

    FILE * userFile = NULL;
    userFile = fopen(filePath,"r");

    FILE * userErrors = NULL;
    char * filePathUErrors = NULL;
    filePathUErrors = malloc(argSize + 20);
    strncpy(filePathUErrors,"Resultados",14);
    strncat(filePathUErrors,"/users_errors.csv",18);
    userErrors = fopen(filePathUErrors,"a+");
    if(!userErrors) {perror("Users errors file did not open\n"); return 1;}

    char * userData = malloc(sizeof(char) * BUFFERSIZE);

    if(!userData) { perror("Erro a alocar memoria na main"); return 1;}

    memset(userData, '\0', BUFFERSIZE);

    //rewind(userFile);
    fseek(userFile,115,SEEK_SET);
    //fgets(userData,BUFFERSIZE,userFile);

    //fgets(userData,BUFFERSIZE,userFile);
    //fgets(userData,BUFFERSIZE,userFile);
    //fgets(userData,BUFFERSIZE,userFile);
    //fgets(userData,BUFFERSIZE,userFile);
    //fgets(userData,BUFFERSIZE,userFile);

    UsersDatabase uDatabase = initUsers();

    while(fgets(userData,BUFFERSIZE,userFile)){

        User * uBuffer = NULL;

        int tamanhoUserData = verTamanhoLinha(userData);

        char userDataClean[tamanhoUserData +1];

        strncpy(userDataClean,userData,tamanhoUserData);

        userDataClean[tamanhoUserData] = '\0';


        uBuffer = userCheck(userDataClean);

        if(uBuffer != NULL){
            char * idBuffer = getUserId(uBuffer);

            g_hash_table_insert(uDatabase,idBuffer,uBuffer);

            free(idBuffer);

        }else{ 
            fprintf(userErrors,"%s",userDataClean);
        }
        
            uBuffer = NULL;
    }
    
    fclose(userFile);
    free(userData);
    free(filePath);

    /*
    // Create Reservations Database
    strcpy(filePath,argv[1]);
    strncat(filePath,"/",2);

    strcat(filePath,"reservations.csv");

    FILE * reservationFile = fopen(filePath,"r");

    char * reservationData = malloc(sizeof(char) * BUFFERSIZE);

    if(!reservationData) { perror("Erro a alocar memoria na main"); return 1;}

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
*/
    return 0;
}