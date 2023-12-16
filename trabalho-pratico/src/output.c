#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include "../include/output.h"
#include "../include/statistics.h"


//inteiro que representa a Query q está a ser respondida
static int commandAtual = 0;


//      **** OUTPUTS PARA Q1 ****

#define FREE(ptr) if(ptr){\
    free(ptr);\
    ptr = NULL;\
}

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
        fprintf(outputFile, "%s\n", total_spent);
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
        fprintf(outputFile, "%d\n", delay);
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

    snprintf(fileName, 49, "Resultados/command%d_output.txt", commandAtual);

    FILE * outputFile = fopen(fileName, "a");
    if(!outputFile){
        perror("Query 1 reservation case did not opened the file\n");
        return;
    }

    if(hotel_id == NULL){
        if(outputFile != NULL) fclose(outputFile);
        return;
    }

    if(F == 0){
        fprintf(outputFile, "%s;", hotel_id);
        fprintf(outputFile, "%s;", hotel_name);
        fprintf(outputFile, "%d;", hotel_stars);
        fprintf(outputFile, "%s;", begin_date);
        fprintf(outputFile, "%s;", end_date);
        if(includes_breakfast == 0){
            fprintf(outputFile, "False;");
        }else fprintf(outputFile, "True;");
        //fprintf(outputFile, "%d;", includes_breakfast);
        fprintf(outputFile, "%d;", nights);
        fprintf(outputFile, "%.3f\n", total_price);
    }else{
        fprintf(outputFile, "--- 1 ---\n");
        fprintf(outputFile, "hotel_id: %s\n", hotel_id);
        fprintf(outputFile, "hotel_name: %s\n", hotel_name);
        fprintf(outputFile, "hotel_stars: %d\n", hotel_stars);
        fprintf(outputFile, "begin_date: %s\n", begin_date);
        fprintf(outputFile, "end_date: %s\n", end_date);
        if(includes_breakfast == 0){
            fprintf(outputFile, "includes_breakfast: False\n");
        }else fprintf(outputFile, "includes_breakfast: True\n");
        //fprintf(outputFile, "includes_breakfast: %d\n", includes_breakfast);
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

    snprintf(fileName, 49, "Resultados/command%d_output.txt", commandAtual);

    FILE * outputFile = fopen(fileName, "a");


    if(!r1 && !f2){
        fclose(outputFile);
        return;
    }
    if(f == false){ // Normal Mode
        if(r1 && n1 > 0 && f2 && n2 > 0){ // There is both reservations and flights to be written
            int i = 0,j = 0,count = 0,max = n1 + n2;
            while(count < max){
                if(i < n1 && j < n2){ // Both the arrays have not reached their limit 
                    Time * rTime = getReservBeginDate(r1[i]);
                    Time * fTime = getFlightSDepartureDate(f2[j]);
                    if(compareTimes(rTime,fTime) == true){ // Flight is more recent that the reservation
                        char * time = timeToString(fTime);
                        time[10] = '\0';
                        char * fId = getFlightId(f2[j]);
                        fprintf(outputFile,"%s;%s;flight\n",fId,time);
                        j++;
                        FREE(time);
                        FREE(fId);
                    }
                    else{ // Reservation is more recent that the flight
                        char * time = timeToString(rTime);
                        time[10] = '\0';
                        char * rId = getReservId(r1[i]);
                        fprintf(outputFile,"%s;%s;reservation\n",rId,time);
                        i++;
                        FREE(time);
                        FREE(rId);
                    }
                    destroyTime(rTime);
                    destroyTime(fTime);
                }
                if(i < n1 && j >= n2){ // Flights array have reached his limit
                    Time * rTime = getReservBeginDate(r1[i]);
                    char * time = timeToString(rTime);
                    time[10] = '\0';
                    char * rId = getReservId(r1[i]);
                    fprintf(outputFile,"%s;%s;reservation\n",rId,time);
                    i++;
                    FREE(time);
                    FREE(rId);
                    destroyTime(rTime);
                }
                if(i >= n1 && j < n2){ // Reservations array have reached his limit
                    Time * fTime = getFlightSDepartureDate(f2[j]);
                    char * time = timeToString(fTime);
                    time[10] = '\0';
                    char * fId = getFlightId(f2[j]);
                    fprintf(outputFile,"%s;%s;flight\n",fId,time);
                    j++;
                    FREE(time);
                    FREE(fId);
                    destroyTime(fTime);
                }
                count++;
            }
            fclose(outputFile);
            return;
        }else{
            if(r1 && n1 > 0){ // There only is reservations to be written
                int i = 0;
                while(i < n1){
                    Time * rTime = getReservBeginDate(r1[i]);
                    char * time = timeToString(rTime);
                    time[10] = '\0';
                    char * rId = getReservId(r1[i]);
                    fprintf(outputFile,"%s;%s\n",rId,time);
                    i++;
                    FREE(time);
                    FREE(rId);
                    destroyTime(rTime);
                }
                fclose(outputFile);
                return;
            }
            if(f2 && n2 > 0){ // There only is flights to be written
                int j = 0;
                while(j < n2){
                    Time * fTime = getFlightSDepartureDate(f2[j]);
                    char * time = timeToString(fTime);
                    time[10] = '\0';
                    char * fId = getFlightId(f2[j]);
                    fprintf(outputFile,"%s;%s\n",fId,time);
                    j++;
                    FREE(time);
                    FREE(fId);
                    destroyTime(fTime);
                }
                fclose(outputFile);
                return;
            }
        }
    }else{ // F Mode
        int i = 0,j = 0,count = 0;
        if(r1 && n1 > 0 && f2 && n2 > 0){ // There is both reservations and flights to be written
            
            int max = n1 + n2;

            while(count < max){
                if(count != 0) fprintf(outputFile,"\n");
                if(i < n1 && j < n2){ // Both the arrays have not reached their limit 
                    Time * rTime = getReservBeginDate(r1[i]);
                    Time * fTime = getFlightSDepartureDate(f2[j]);
                    if(compareTimes(rTime,fTime) == true){ // Flight is more recent that the reservation
                        char * time = timeToString(fTime);
                        time[10] = '\0';
                        char * fId = getFlightId(f2[j]);
                        fprintf(outputFile,"--- %d ---\n",count + 1);
                        fprintf(outputFile,"id: %s\ndate: %s\ntype: flight\n",fId,time);
                        j++;
                        FREE(time);
                        FREE(fId);
                    }
                    else{ // Reservation is more recent that the flight
                        char * time = timeToString(rTime);
                        time[10] = '\0';
                        char * rId = getReservId(r1[i]);
                        fprintf(outputFile,"--- %d ---\n",count + 1);
                        fprintf(outputFile,"id: %s\ndate: %s\ntype: reservation\n",rId,time);
                        i++;
                        FREE(time);
                        FREE(rId);
                    }
                    destroyTime(rTime);
                    destroyTime(fTime);
                }
                if(i < n1 && j >= n2){ // Flights array have reached his limit, but the reservations has not
                    count++;
                    while (i < n1)
                    {                
                        Time * rTime = getReservBeginDate(r1[i]);
                        char * time = timeToString(rTime);
                        time[10] = '\0';
                        char * rId = getReservId(r1[i]);
                        fprintf(outputFile,"\n--- %d ---\n",count + 1);
                        fprintf(outputFile,"id: %s\ndate: %s\ntype: reservation\n",rId,time);
                        i++;
                        count++;
                        FREE(time);
                        FREE(rId);
                        destroyTime(rTime);
                    }
                    fclose(outputFile);
                    return;
                }
                if(r1 && f2 && i == n1 && j < n2){ // Reservations array have reached his limit but the flights have not
                    count++;
                    while (j < n2)
                    {
                        Time * fTime = getFlightSDepartureDate(f2[j]);
                        char * time = timeToString(fTime);
                        time[10] = '\0';
                        char * fId = getFlightId(f2[j]);
                        fprintf(outputFile,"\n--- %d ---\n",count + 1);
                        fprintf(outputFile,"id: %s\ndate: %s\ntype: flight\n",fId,time);
                        j++;
                        count++;
                        FREE(time);
                        FREE(fId);
                        destroyTime(fTime);
                    }
                    fclose(outputFile);
                    return;
                }
                count++;
            }
            fclose(outputFile);
            return;


        }else{
            if(r1 && n1 > 0 && !f2){ // There only is reservations to be written
                int r = 0;
                while(r < n1){
                    Time * rTime = getReservBeginDate(r1[r]);
                    char * time = timeToString(rTime);
                    time[10] = '\0';
                    char * rId = getReservId(r1[r]);
                    if(r != 0) fprintf(outputFile,"\n");
                    fprintf(outputFile,"--- %d ---\n",r + 1);
                    fprintf(outputFile,"id: %s\ndate: %s\n",rId,time);
                    r++;
                    FREE(time);
                    FREE(rId);
                    destroyTime(rTime);
                }
                fclose(outputFile);
                return;
            }
            if(f2 && n2 > 0 && !r1){ // There only is flights to be written
                int f = 0;
                while(f < n2){
                    Time * fTime = getFlightSDepartureDate(f2[f]);
                    char * time = timeToString(fTime);
                    time[10] = '\0';
                    char * fId = getFlightId(f2[f]);
                    if(f != 0) fprintf(outputFile,"\n");
                    fprintf(outputFile,"--- %d ---\n",f + 1);
                    fprintf(outputFile,"id: %s\ndate: %s\n",fId,time);
                    f++;
                    FREE(time);
                    FREE(fId);
                    destroyTime(fTime);
                }
                fclose(outputFile);
                return;
            }
        }
    }
    if(outputFile != NULL) fclose(outputFile);
}

void outputQ3(bool f,double rating){

    commandAtual++;

    char fileName[50];

    memset(fileName,'\0',50);

    snprintf(fileName, 49, "Resultados/command%d_output.txt", commandAtual);

    FILE * outputFile = fopen(fileName, "a");
    if(!outputFile){
        perror("Query 3 command line did not open, probably file name wrong.\n");
        return;
    }

    if(f == true){
        fprintf(outputFile,"--- 1 ---\nrating: %0.3f\n",rating);
    }else{
        fprintf(outputFile,"%0.3f\n",rating);
    }
    fclose(outputFile);
}

void outputQ4(bool f,Reservation ** rList,int max){
    commandAtual++;

    char fileName[50];

    memset(fileName,'\0',50);

    snprintf(fileName, 49 , "Resultados/command%d_output.txt", commandAtual);

    FILE * outputFile = fopen(fileName, "a");
    if(!outputFile){
        perror("Query 4 command line did not open, probably file name wrong.\n");
        return;
    }

    if(f == true){
        for(int i = 0; i < max;i++){
            if(rList[i]){
                char * id = getReservId(rList[i]);
                Time * bTime = getReservBeginDate(rList[i]);
                Time * eTime = getReservEndDate(rList[i]);
                char * stringBTime = timeToString(bTime);
                char * stringETime = timeToString(eTime);
                char * uId = getReservUserId(rList[i]);
                int rating = getReservRating(rList[i]);
                int n = numberOfDays(bTime,eTime);

                if(i != 0) fprintf(outputFile,"\n");
                fprintf(outputFile,"--- %d ---\n",i + 1);
                fprintf(outputFile,"id: %s\n",id);
                fprintf(outputFile,"begin_date: %s\n",stringBTime);
                fprintf(outputFile,"end_date: %s\n",stringETime);
                fprintf(outputFile,"user_id: %s\n",uId);
                fprintf(outputFile,"rating: %d\n",rating);
                fprintf(outputFile,"total_price: %0.3f\n",getTotalSpentOnReserv(rList[i],n));
                FREE(id);
                FREE(stringBTime);
                FREE(stringETime);
                FREE(uId);
                destroyTime(bTime);
                destroyTime(eTime);
            }else{
                break;
            }
        }
    }else{
        for(int i = 0;i < max;i++){
            if(rList[i]){
                char * id = getReservId(rList[i]);
                Time * bTime = getReservBeginDate(rList[i]);
                Time * eTime = getReservEndDate(rList[i]);
                char * stringBTime = timeToString(bTime);
                char * stringETime = timeToString(eTime);
                char * uId = getReservUserId(rList[i]);
                int rating = getReservRating(rList[i]);
                int n = numberOfDays(bTime,eTime);

                fprintf(outputFile,"%s;%s;%s;%s;%d;%0.3f\n",id,stringBTime,stringETime,uId,rating,getTotalSpentOnReserv(rList[i],n));

                FREE(id);
                FREE(stringBTime);
                FREE(stringETime);
                FREE(uId);
                destroyTime(bTime);
                destroyTime(eTime);
            }else{
                break;
            }
        }
    }
    fclose(outputFile);
    
}

void outputQ5(bool f, Flight ** fList,int max){
    commandAtual++;

    char fileName[50];

    memset(fileName,'\0',50);

    snprintf(fileName, 49, "Resultados/command%d_output.txt", commandAtual);

    FILE * outputFile = fopen(fileName, "a");
    if(!outputFile){
        perror("Query 5 command line did not open, probably file name wrong.\n");
        return;
    }
    if(f == true){
        for(int i = 0;i < max;i++){
            char * fId = getFlightId(fList[i]);
            Time * sDD = getFlightSDepartureDate(fList[i]);
            char * sDepDate = timeToString(sDD);
            char * destination = getFlightDestination(fList[i]);
            char * airline = getFlightAirline(fList[i]);
            char * planeModel = getFlightPlaneModel(fList[i]);
            if(i != 0) fprintf(outputFile,"\n");
            fprintf(outputFile,"--- %d ---\n",i + 1);
            fprintf(outputFile,"id: %s\n",fId);
            fprintf(outputFile,"schedule_departure_date: %s\n",sDepDate);
            fprintf(outputFile,"destination: %s\n",destination);
            fprintf(outputFile,"airline: %s\n",airline);
            fprintf(outputFile,"plane_model: %s\n",planeModel);
            destroyTime(sDD);
            FREE(fId);
            FREE(sDepDate);
            FREE(destination);
            FREE(airline);
            FREE(planeModel);
        }
    }else{
        for(int i = 0;i < max;i++){
            char * fId = getFlightId(fList[i]);
            Time * sDD = getFlightSDepartureDate(fList[i]);
            char * sDepDate = timeToString(sDD);
            char * destination = getFlightDestination(fList[i]);
            char * airline = getFlightAirline(fList[i]);
            char * planeModel = getFlightPlaneModel(fList[i]);
            fprintf(outputFile,"%s;%s;%s;%s;%s\n",
            fId,
            sDepDate,
            destination,
            airline,
            planeModel);
            destroyTime(sDD);
            FREE(fId);
            FREE(sDepDate);
            FREE(destination);
            FREE(airline);
            FREE(planeModel);
        }
    }
    fclose(outputFile);
}

void outputQ8(double revenue, bool f){
    commandAtual++;

    char fileName[50];

    memset(fileName,'\0',50);

    snprintf(fileName, 49, "Resultados/command%d_output.txt", commandAtual);

    FILE * outputFile = fopen(fileName, "a");
    if(!outputFile){
        perror("Query 8 command line did not open, probably file name wrong.\n");
        return;
    }

    if(f== true){
        fprintf(outputFile,"--- 1 ---\n");
        fprintf(outputFile,"revenue: %0.3f\n",revenue);
    }else{
        fprintf(outputFile,"%0.3f\n",revenue);
    }
    fclose(outputFile);
}