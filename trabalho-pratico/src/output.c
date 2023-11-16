#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include "../include/output.h"

//inteiro que representa a Query q está a ser respondida
int commandAtual = 0;


//      **** OUTPUTS PARA Q1 ****


//user
void outputQ1User(int F, char * name, char sex, int age, char * country_code , char * passport , char * number_of_flights, char * number_of_reservations, char * total_spent){

    commandAtual++;

    char fileName[50];

    snprintf(fileName, sizeof(fileName), "../Resultados/command%d_output.txt", commandAtual);

    FILE * outputFile = fopen(fileName, "a");

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
}


//flight
void outputQ1Flight(int F, char * airline, char * plane_model , char * origin, char * destination , char * schedule_departure_date , char * schedule_arrival_date, int passengers, int delay){

    commandAtual++;

    char fileName[50];

    snprintf(fileName, sizeof(fileName), "../Resultados/command%d_output.txt", commandAtual);

    FILE * outputFile = fopen(fileName, "a");

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
}


//reservation
void outputQ1Reservation(int F, char * hotel_id, char * hotel_name , int hotel_stars, char * begin_date , char * end_date , bool includes_breakfast, int nights, int total_price){

    commandAtual++;

    char fileName[50];

    snprintf(fileName, sizeof(fileName), "../Resultados/command%d_output.txt", commandAtual);

    FILE * outputFile = fopen(fileName, "a");

    if(F == 0){
        fprintf(outputFile, "%s;", hotel_id);
        fprintf(outputFile, "%s;", hotel_name);
        fprintf(outputFile, "%d;", hotel_stars);
        fprintf(outputFile, "%s;", begin_date);
        fprintf(outputFile, "%s;", end_date);
        fprintf(outputFile, "%d;", includes_breakfast);
        fprintf(outputFile, "%d;", nights);
        fprintf(outputFile, "%d;", total_price);
    }else{
        fprintf(outputFile, "--- 1 ---\n");
        fprintf(outputFile, "hotel_id: %s\n", hotel_id);
        fprintf(outputFile, "hotel_name: %s\n", hotel_name);
        fprintf(outputFile, "hotel_stars: %d\n", hotel_stars);
        fprintf(outputFile, "begin_date: %s\n", begin_date);
        fprintf(outputFile, "end_date: %s\n", end_date);
        fprintf(outputFile, "includes_breakfast: %d\n", includes_breakfast);
        fprintf(outputFile, "nights: %d\n", nights);
        fprintf(outputFile, "total_price: %d\n", total_price);
    }
}



//      **** OUTPUTS PARA Q1 ****


void outputQ2(Reservation ** reservation, Flight ** flight){}