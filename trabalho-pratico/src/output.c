#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include "../include/output.h"
#include "../include/statistics.h"


//inteiro que representa a Query q está a ser respondida
static int commandAtual = 0;


//      **** OUTPUTS PARA Q1 ****


//user
void outputQ1User(int F, char * name, char sex, int age, char * country_code , char * passport , char * number_of_flights, char * number_of_reservations, char * total_spent){

    commandAtual++;

    char fileName[50];

    memset(fileName,'\0',50);

    snprintf(fileName, 49, "Resultados/command%d_output.txt", commandAtual);

    FILE * outputFile = fopen(fileName, "a");
    if(outputFile == NULL){
        perror("!!!File did not opened!!!\n");
        return;
    }

    if(name == NULL){
        if(outputFile != NULL) fclose(outputFile);
        return;
    }

    if(F == 0){
        fprintf(outputFile, "%s;", name);
        fprintf(outputFile, "%c;", sex);
        fprintf(outputFile, "%d;", age);
        fprintf(outputFile, "%s;", country_code);
        fprintf(outputFile, "%s;", passport);
        fprintf(outputFile, "%s;", number_of_flights);
        fprintf(outputFile, "%s;", number_of_reservations);
        fprintf(outputFile, "%s;", total_spent);
    }else{
        fprintf(outputFile, "--- 1 ---\n");
        fprintf(outputFile, "name: %s\n", name);
        fprintf(outputFile, "sex: %c\n", sex);
        fprintf(outputFile, "age: %d\n", age);
        fprintf(outputFile, "country_code: %s\n", country_code);
        fprintf(outputFile, "passport: %s\n", passport);
        fprintf(outputFile, "number_of_flights: %s\n", number_of_flights);
        fprintf(outputFile, "number_of_reservations: %s\n", number_of_reservations);
        fprintf(outputFile, "total_spent: %s\n", total_spent);
    }
    fclose(outputFile);
}


//flight
void outputQ1Flight(int F, char * airline, char * plane_model , char * origin, char * destination , char * schedule_departure_date , char * schedule_arrival_date, int passengers, int delay){

    commandAtual++;

    char fileName[50];

    memset(fileName,'\0',50);
    
    snprintf(fileName, 50, "Resultados/command%d_output.txt", commandAtual);

    FILE * outputFile = fopen(fileName, "a");
    if(outputFile == NULL){ 
        return;
    }
    
    if(airline == NULL){
        if(outputFile != NULL){ 
        fclose(outputFile);
        return;
    }   
    }

    if(F == 0){
        fprintf(outputFile, "%s;", airline);
        fprintf(outputFile, "%s;", plane_model);
        fprintf(outputFile, "%s;", origin);
        fprintf(outputFile, "%s;", destination);
        fprintf(outputFile, "%s;", schedule_departure_date);
        fprintf(outputFile, "%s;", schedule_arrival_date);
        fprintf(outputFile, "%d;", passengers);
        fprintf(outputFile, "%d;", delay);
    }else{
        fprintf(outputFile, "--- 1 ---\n");
        fprintf(outputFile, "airline: %s\n", airline);
        fprintf(outputFile, "plane_model: %s\n", plane_model);
        fprintf(outputFile, "origin: %s\n", origin);
        fprintf(outputFile, "destination: %s\n", destination);
        fprintf(outputFile, "schedule_departure_date: %s\n", schedule_departure_date);
        fprintf(outputFile, "schedule_arrival_date: %s\n", schedule_arrival_date);
        fprintf(outputFile, "passengers: %d\n", passengers);
        fprintf(outputFile, "delay: %d\n", delay);
    }
    fclose(outputFile);
}


//reservation
void outputQ1Reservation(int F, char * hotel_id, char * hotel_name , int hotel_stars, char * begin_date , char * end_date , bool includes_breakfast, int nights, double total_price){

    commandAtual++;

    char fileName[50];

    memset(fileName,'\0',50);

    snprintf(fileName, strlen(fileName), "../Resultados/command%d_output.txt", commandAtual);

    FILE * outputFile = fopen(fileName, "a");

    if(hotel_id == NULL){
        if(outputFile == NULL) fclose(outputFile);
        return;
    }

    if(F == 0){
        fprintf(outputFile, "%s;", hotel_id);
        fprintf(outputFile, "%s;", hotel_name);
        fprintf(outputFile, "%d;", hotel_stars);
        fprintf(outputFile, "%s;", begin_date);
        fprintf(outputFile, "%s;", end_date);
        fprintf(outputFile, "%d;", includes_breakfast);
        fprintf(outputFile, "%d;", nights);
        fprintf(outputFile, "%.3f;", total_price);
    }else{
        fprintf(outputFile, "--- 1 ---\n");
        fprintf(outputFile, "hotel_id: %s\n", hotel_id);
        fprintf(outputFile, "hotel_name: %s\n", hotel_name);
        fprintf(outputFile, "hotel_stars: %d\n", hotel_stars);
        fprintf(outputFile, "begin_date: %s\n", begin_date);
        fprintf(outputFile, "end_date: %s\n", end_date);
        fprintf(outputFile, "includes_breakfast: %d\n", includes_breakfast);
        fprintf(outputFile, "nights: %d\n", nights);
        fprintf(outputFile, "total_price: %.3f\n", total_price);
    }
    fclose(outputFile);
}





//*OUTPUTS PARA Q2
void outputQ2(bool f,Reservation ** r1,int n1, Flight ** f2,int n2){
    
    commandAtual++;

    char fileName[50];

    memset(fileName,'\0',50);

    snprintf(fileName, strlen(fileName), "../Resultados/command%d_output.txt", commandAtual);

    FILE * outputFile = fopen(fileName, "a");


    if(!r1 && !f2){
        fclose(outputFile);
        return;
    }
    if(f == true){
        if(r1 && n1 > 0 && f2 && n2 > 0){
        int i = 0,j = 0,count = 0,max = n1 + n2;
        while(count < max){
            if(compareTimes(getReservBeginDate(r1[i]),getFlightSDepartureDate(f2[j])) == true){ 
                fprintf(outputFile,"%s;%sflight\n",getFlightId(f2[j]),timeToString(getFlightSDepartureDate(f2[j])));
                j++;
            }
            else{
                fprintf(outputFile,"%s;%sreservation\n",getReservId(r1[i]),timeToString(getReservBeginDate(r1[i])));
                i++;
            }
            count++;
        }
        fclose(outputFile);
        return;
        }
        if(r1 && n1 > 0){
            int i = 0;
            while(i < n1){
                fprintf(outputFile,"%s;%s\n",getReservId(r1[i]),timeToString(getReservBeginDate(r1[i])));
                i++;
            }
            fclose(outputFile);
            return;
        }
        if(f2 && n2 > 0){
            int j = 0;
            while(j < n2){
                fprintf(outputFile,"%s;%s\n",getFlightId(f2[j]),timeToString(getFlightSDepartureDate(f2[j])));
                j++;
            }
            fclose(outputFile);
            return;
        }
    }
    if(outputFile != NULL) fclose(outputFile);
}

void outputQ3(bool f,double rating){

    commandAtual++;

    char fileName[50];

    memset(fileName,'\0',50);

    snprintf(fileName, strlen(fileName), "../Resultados/command%d_output.txt", commandAtual);

    FILE * outputFile = fopen(fileName, "a");


    if(f == true){
        fprintf(outputFile,"--- 1 ---\n%.3f\n",rating);
    }else{
        fprintf(outputFile,"%.3f\n",rating);
    }
    fclose(outputFile);
}

void outputQ4(bool f,Reservation ** rList,int max){
    commandAtual++;

    char fileName[50];

    memset(fileName,'\0',50);

    snprintf(fileName, strlen(fileName), "../Resultados/command%d_output.txt", commandAtual);

    FILE * outputFile = fopen(fileName, "a");

    if(f == true){
        for(int i = 0; i < max;i++){
            fprintf(outputFile,"--- %d ---\n",i);
            fprintf(outputFile,"id : %s\n",getReservId(rList[i]));
            fprintf(outputFile,"begin_date : %s\n",timeToString(getReservBeginDate(rList[i])));
            fprintf(outputFile,"end_date : %s\n",timeToString(getReservEndDate(rList[i])));
            fprintf(outputFile,"user_id : %s\n",getReservUserId(rList[i]));
            fprintf(outputFile,"rating : %d\n",getReservRating(rList[i]));
            fprintf(outputFile,"total_price : %.3f\n",getTotalSpentOnReserv(rList[i],-1));
        }
    }else{
        for(int i = 0;i < max;i++){
            fprintf(outputFile,"%s;%s;%s;%s;%d;%.3f\n",getReservId(rList[i]),timeToString(getReservBeginDate(rList[i])),
            timeToString(getReservEndDate(rList[i])),getReservUserId(rList[i]),
            getReservRating(rList[i]),getTotalSpentOnReserv(rList[i],-1));
        }
    }
    fclose(outputFile);
    
}

void outputQ5(bool f, Flight ** fList,int max){
    commandAtual++;

    char fileName[50];

    memset(fileName,'\0',50);

    snprintf(fileName, strlen(fileName), "../Resultados/command%d_output.txt", commandAtual);

    FILE * outputFile = fopen(fileName, "a");
    if(f == true){
        for(int i = 0;i < max;i++){
            fprintf(outputFile,"--- %d ---\n",i);
            fprintf(outputFile,"id : %s\n",getFlightId(fList[i]));
            fprintf(outputFile,"schedule_departure_date : %s\n",timeToString(getFlightSDepartureDate(fList[i])));
            fprintf(outputFile,"destination : %s\n",getFlightDestination(fList[i]));
            fprintf(outputFile,"airline : %s\n",getFlightAirline(fList[i]));
            fprintf(outputFile,"plane_model : %s\n",getFlightPlaneModel(fList[i]));
        }
    }else{
        for(int i = 0;i < max;i++){
            fprintf(outputFile,"%s;%s;%s;%s;%s",
            getFlightId(fList[i]),
            timeToString(getFlightSDepartureDate(fList[i])),
            getFlightDestination(fList[i]),
            getFlightAirline(fList[i]),
            getFlightPlaneModel(fList[i]));
        }
    }
    fclose(outputFile);
}

void outputQ8(double revenue, bool f){
    commandAtual++;

    char fileName[50];

    memset(fileName,'\0',50);

    snprintf(fileName, strlen(fileName), "../Resultados/command%d_output.txt", commandAtual);

    FILE * outputFile = fopen(fileName, "a");
    if(f== true){
        fprintf(outputFile,"--- 1 ---\n");
        fprintf(outputFile,"revenue: %.3f\n",revenue);
    }else{
        fprintf(outputFile,"%.3f\n",revenue);
    }
    fclose(outputFile);
}