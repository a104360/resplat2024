#include "../include/parser.h"
#include "../include/interpreter.h"
#include "../include/user.h"
#include "../include/reservation.h"
#include "../include/flight.h"
#include "../include/passengers.h"
#include "../include/statistics.h"
#include "../include/testes.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define BUFFERSIZE 1000

void print(gpointer key,gpointer value,gpointer data){
    Reservation * r = (Reservation *) value;
    if(!strcoll("HTL1002",key)) 
        printf("%d\n",getReservRating(r));
}


int main(int argc,char **argv){
    if(argc == 3){
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


        Users * uDatabase = createDatabase(&destroyUser); // initDatabase

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
                insertOnDatabase(uDatabase,getUserId(uBuffer),uBuffer);

            }else{ 
                fprintf(userErrors,"%s",userDataClean);
            }
            
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

        Reservations * rDatabase = createDatabase(&destroyReservation);

        fgets(reservationData,BUFFERSIZE,reservationsFile);

        fprintf(reservationsErrors,"%s",reservationData);

        while(fgets(reservationData,BUFFERSIZE,reservationsFile)){

            Reservation * rBuffer = NULL;

            int tamanhoReservationData = verTamanhoLinha(reservationData);

            char * reservationDataClean = malloc(sizeof(char) * (tamanhoReservationData +1));

            strncpy(reservationDataClean,reservationData,tamanhoReservationData);

            reservationDataClean[tamanhoReservationData] = '\0';

            rBuffer = reservationCheck(reservationDataClean,uDatabase);

        if(rBuffer != NULL){
                insertOnDatabase(rDatabase,getReservId(rBuffer),rBuffer);
            }else{ 
                fprintf(reservationsErrors,"%s",reservationDataClean);
            }
                
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
        if(!flightsErrors) {
            perror("Flights errors file did not open\n");
            if(filePath){
                free(filePath);
                filePath = NULL;
            } 
            if(filePathFErrors){
                free(filePathFErrors);
                filePathFErrors = NULL;
            }
            if(flightFile){
                fclose(flightFile);
                flightFile = NULL;
            }
            return 1;
        }

        char * flightData = malloc(sizeof(char) * BUFFERSIZE);

        if(!flightData) { 
            perror("Erro a alocar memoria na main"); 
            if(filePath){
                free(filePath);
                filePath = NULL;
            } 
            if(filePathFErrors){
                free(filePathFErrors);
                filePathFErrors = NULL;
            }
            if(flightFile){
                fclose(flightFile);
                flightFile = NULL;
            }
            fclose(flightsErrors);
            flightsErrors = NULL;
            return 1;
        }

        memset(flightData, '\0', BUFFERSIZE);

        Flights * fDatabase = createDatabase(&destroyFlight);

        while(fgets(flightData,BUFFERSIZE,flightFile)){

            Flight * fBuffer = NULL;

            int tamanhoFlightData = verTamanhoLinha(flightData);

            char flightDataClean[tamanhoFlightData +1];

            strncpy(flightDataClean,flightData,tamanhoFlightData);

            flightDataClean[tamanhoFlightData] = '\0';

            fBuffer = fligthCheck(flightDataClean);

            //fligthCheck(flightDataClean);

            if(fBuffer != NULL){

                insertOnDatabase(fDatabase,getFlightId(fBuffer),fBuffer);

            }else{ 
                fprintf(flightsErrors,"%s",flightDataClean);
            }

        }

        fclose(flightFile); // close
        flightFile = NULL;
        free(filePathFErrors);  // free
        filePathFErrors = NULL;
        free(flightData); // free
        flightData = NULL;
        fclose(flightsErrors); // close
        flightsErrors = NULL;


        // Create Passengers Database 

        memset(filePath,'\0',argSize + 20);

        strncpy(filePath,argv[1],argSize);
        strncat(filePath,"/passengers.csv",17);

        FILE * passengersFile = NULL;
        passengersFile = fopen(filePath,"r");
        if(passengersFile == NULL){
            perror("Did not opened the file correctly");
            return 10;
        }

        FILE * passengersErrors = NULL;
        char * filePathPErrors = NULL;
        filePathPErrors = malloc(argSize + 27);
        strncpy(filePathPErrors,"Resultados",14);
        strncat(filePathPErrors,"/passengers_errors.csv",25);
        passengersErrors = fopen(filePathPErrors,"a+");
        if(!passengersErrors) {perror("Passengers errors file did not open\n"); return 1;}

        char * passengersData = malloc(sizeof(char) * BUFFERSIZE);

        if(!passengersData) { perror("Erro a alocar memoria na main"); return 1;}

        memset(passengersData, '\0', BUFFERSIZE);

        Passengers * pDatabase = createPassengerDatabase();
        
        fgets(passengersData,BUFFERSIZE,passengersFile);

        fprintf(passengersErrors,"%s",passengersData);

        while(fgets(passengersData,BUFFERSIZE,passengersFile)){

            Passenger * pBuffer = NULL;

            int tamanhoPassengersData = verTamanhoLinha(passengersData);

            char passengersDataClean[tamanhoPassengersData +1];

            strncpy(passengersDataClean,passengersData,tamanhoPassengersData);

            passengersDataClean[tamanhoPassengersData] = '\0';

            pBuffer = passengerCheck(passengersDataClean,uDatabase,fDatabase);

            if(pBuffer != NULL){
                insertPassenger(pDatabase,pBuffer);

            }else{ 
                fprintf(passengersErrors,"%s",passengersDataClean);
            }
        }

        fclose(passengersFile); // close
        passengersFile = NULL;
        free(filePathPErrors);  // free
        filePathPErrors = NULL;
        free(passengersData); // free
        passengersData = NULL;
        fclose(passengersErrors); // close
        passengersErrors = NULL;
        free(filePath); // free
        filePath = NULL;

        // Read and execute commands, freeing after used

        readEntryFile((const Users *) uDatabase,(const Reservations *) rDatabase,(const Flights *) fDatabase,(const Passengers *) pDatabase,argc,argv);

        // Free everything used
        destroyPassengers(pDatabase);
        destroyDatabase(uDatabase);
        destroyDatabase(fDatabase);
        destroyDatabase(rDatabase);
    }
    if(argc == 2){
        confirmar(argc,argv);
    }
    return 0;
}