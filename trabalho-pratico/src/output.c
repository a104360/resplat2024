#include "../include/flight.h"
#include "../include/reservation.h"
#include "../include/output.h"
#include "../include/statistics.h"
#include "../include/time.h"
#include "../include/ui.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#define DOWN -1

#define UP 1

//inteiro que representa a Query q está a ser respondida
static int commandAtual = 0;

extern bool interactive;

//user
void outputQ1User(int F, char * name, char sex, int age, char * country_code , char * passport , int number_of_flights, int number_of_reservations, double total_spent){

    commandAtual++;

    if(interactive == false){

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
            fprintf(outputFile, "%d;", number_of_flights);
            fprintf(outputFile, "%d;", number_of_reservations);
            fprintf(outputFile, "%.3f\n", total_spent);
        }else{
            fprintf(outputFile, "--- 1 ---\n");
            fprintf(outputFile, "name: %s\n", name);
            fprintf(outputFile, "sex: %c\n", sex);
            fprintf(outputFile, "age: %d\n", age);
            fprintf(outputFile, "country_code: %s\n", country_code);
            fprintf(outputFile, "passport: %s\n", passport);
            fprintf(outputFile, "number_of_flights: %d\n", number_of_flights);
            fprintf(outputFile, "number_of_reservations: %d\n", number_of_reservations);
            fprintf(outputFile, "total_spent: %.3f\n", total_spent);
        }
        fclose(outputFile);
        return;
    }
    cursorOff();
    printQ1User(F,name,sex,age,country_code,passport,number_of_flights,number_of_reservations,total_spent);
    dontWriteOnScreen();
    int input = getInput();
    while(input != 0){
        input = getInput();
    }
    writeOnScreen();
    cursorOn();
    return;
}


//flight
void outputQ1Flight(int F, char * airline, char * plane_model , char * origin, char * destination , char * schedule_departure_date , char * schedule_arrival_date, int passengers, int delay){

    if(interactive == false){
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
        return;
    }
    cursorOff();
    printQ1Flight(F,airline,plane_model,origin,destination,schedule_departure_date,schedule_arrival_date,passengers,delay);
    dontWriteOnScreen();
    int input = getInput();
    while(input != 0) input = getInput();
    writeOnScreen();
    cursorOn();
}


//reservation
void outputQ1Reservation(int F, char * hotel_id, char * hotel_name , int hotel_stars, char * begin_date , char * end_date , bool includes_breakfast, int nights, double total_price){

    if(interactive == false){

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
            fprintf(outputFile, "nights: %d\n", nights);
            fprintf(outputFile, "total_price: %.3f\n", total_price);
        }
        fclose(outputFile);
        return;
    }
    cursorOff();
    printQ1Reservation(F,hotel_id,hotel_name,hotel_stars,begin_date,end_date,includes_breakfast,nights,total_price);
    dontWriteOnScreen();
    int input = getInput();
    while(input != 0) input = getInput();
    writeOnScreen();
    cursorOn();
}





//*OUTPUTS PARA Q2
void outputQ2(bool f,Reservation ** reservations,int n1, Flight ** flights,int n2){
    
    if(interactive == false){

        commandAtual++;

        char fileName[50];

        memset(fileName,'\0',50);

        snprintf(fileName, 49, "Resultados/command%d_output.txt", commandAtual);

        FILE * outputFile = fopen(fileName, "a");


        if(!reservations && !flights){
            fclose(outputFile);
            return;
        }
        if(f == false){ // Normal Mode
            if(reservations && n1 > 0 && flights && n2 > 0){ // There is both reservations and flights to be written
                int i = 0,j = 0,count = 0,max = n1 + n2;
                while(count < max){
                    if(i < n1 && j < n2){ // Both the arrays have not reached their limit 
                        Time * rTime = getReservBeginDate(reservations[i]);
                        Time * fTime = getFlightSDepartureDate(flights[j]);
                        if(compareTimes(rTime,fTime) == true){ // Flight is more recent that the reservation
                            char * time = timeToString(fTime);
                            time[10] = '\0';
                            char * fId = getFlightId(flights[j]);
                            fprintf(outputFile,"%s;%s;flight\n",fId,time);
                            j++;
                            ffree((void **) &time);
                            ffree((void **) &fId);
                        }
                        else{ // Reservation is more recent that the flight
                            char * time = timeToString(rTime);
                            time[10] = '\0';
                            char * rId = getReservId(reservations[i]);
                            fprintf(outputFile,"%s;%s;reservation\n",rId,time);
                            i++;
                            ffree((void **) &time);
                            ffree((void **) &rId);
                        }
                        destroyTime(rTime);
                        destroyTime(fTime);
                    }
                    if(i < n1 && j >= n2){ // Flights array have reached his limit
                        Time * rTime = getReservBeginDate(reservations[i]);
                        char * time = timeToString(rTime);
                        time[10] = '\0';
                        char * rId = getReservId(reservations[i]);
                        fprintf(outputFile,"%s;%s;reservation\n",rId,time);
                        i++;
                        ffree((void **) &time);
                        ffree((void **) &rId);
                        destroyTime(rTime);
                    }
                    if(i >= n1 && j < n2){ // Reservations array have reached his limit
                        Time * fTime = getFlightSDepartureDate(flights[j]);
                        char * time = timeToString(fTime);
                        time[10] = '\0';
                        char * fId = getFlightId(flights[j]);
                        fprintf(outputFile,"%s;%s;flight\n",fId,time);
                        j++;
                        ffree((void **) &time);
                        ffree((void **) &fId);
                        destroyTime(fTime);
                    }
                    count++;
                }
                fclose(outputFile);
                return;
            }else{
                if(reservations && n1 > 0){ // There only is reservations to be written
                    int i = 0;
                    while(i < n1){
                        Time * rTime = getReservBeginDate(reservations[i]);
                        char * time = timeToString(rTime);
                        time[10] = '\0';
                        char * rId = getReservId(reservations[i]);
                        fprintf(outputFile,"%s;%s\n",rId,time);
                        i++;
                        ffree((void **) &time);
                        ffree((void **) &rId);
                        destroyTime(rTime);
                    }
                    fclose(outputFile);
                    return;
                }
                if(flights && n2 > 0){ // There only is flights to be written
                    int j = 0;
                    while(j < n2){
                        Time * fTime = getFlightSDepartureDate(flights[j]);
                        char * time = timeToString(fTime);
                        time[10] = '\0';
                        char * fId = getFlightId(flights[j]);
                        fprintf(outputFile,"%s;%s\n",fId,time);
                        j++;
                        ffree((void **) &time);
                        ffree((void **) &fId);
                        destroyTime(fTime);
                    }
                    fclose(outputFile);
                    return;
                }
            }
        }else{ // F Mode
            int i = 0,j = 0,count = 0;
            if(reservations && n1 > 0 && flights && n2 > 0){ // There is both reservations and flights to be written
                
                int max = n1 + n2;

                while(count < max){
                    if(count != 0) fprintf(outputFile,"\n");
                    if(i < n1 && j < n2){ // Both the arrays have not reached their limit 
                        Time * rTime = getReservBeginDate(reservations[i]);
                        Time * fTime = getFlightSDepartureDate(flights[j]);
                        if(compareTimes(rTime,fTime) == true){ // Flight is more recent that the reservation
                            char * time = timeToString(fTime);
                            time[10] = '\0';
                            char * fId = getFlightId(flights[j]);
                            fprintf(outputFile,"--- %d ---\n",count + 1);
                            fprintf(outputFile,"id: %s\ndate: %s\ntype: flight\n",fId,time);
                            j++;
                            ffree((void **) &time);
                            ffree((void **) &fId);
                        }
                        else{ // Reservation is more recent that the flight
                            char * time = timeToString(rTime);
                            time[10] = '\0';
                            char * rId = getReservId(reservations[i]);
                            fprintf(outputFile,"--- %d ---\n",count + 1);
                            fprintf(outputFile,"id: %s\ndate: %s\ntype: reservation\n",rId,time);
                            i++;
                            ffree((void **) &time);
                            ffree((void **) &rId);
                        }
                        destroyTime(rTime);
                        destroyTime(fTime);
                    }
                    if(i < n1 && j >= n2){ // Flights array have reached his limit, but the reservations has not
                        count++;
                        while (i < n1)
                        {                
                            Time * rTime = getReservBeginDate(reservations[i]);
                            char * time = timeToString(rTime);
                            time[10] = '\0';
                            char * rId = getReservId(reservations[i]);
                            fprintf(outputFile,"\n--- %d ---\n",count + 1);
                            fprintf(outputFile,"id: %s\ndate: %s\ntype: reservation\n",rId,time);
                            i++;
                            count++;
                            ffree((void **) &time);
                            ffree((void **) &rId);
                            destroyTime(rTime);
                        }
                        fclose(outputFile);
                        return;
                    }
                    if(reservations && flights && i == n1 && j < n2){ // Reservations array have reached his limit but the flights have not
                        count++;
                        while (j < n2)
                        {
                            Time * fTime = getFlightSDepartureDate(flights[j]);
                            char * time = timeToString(fTime);
                            time[10] = '\0';
                            char * fId = getFlightId(flights[j]);
                            fprintf(outputFile,"\n--- %d ---\n",count + 1);
                            fprintf(outputFile,"id: %s\ndate: %s\ntype: flight\n",fId,time);
                            j++;
                            count++;
                            ffree((void **) &time);
                            ffree((void **) &fId);
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
                if(reservations && n1 > 0 && !flights){ // There only is reservations to be written
                    int r = 0;
                    while(r < n1){
                        Time * rTime = getReservBeginDate(reservations[r]);
                        char * time = timeToString(rTime);
                        time[10] = '\0';
                        char * rId = getReservId(reservations[r]);
                        if(r != 0) fprintf(outputFile,"\n");
                        fprintf(outputFile,"--- %d ---\n",r + 1);
                        fprintf(outputFile,"id: %s\ndate: %s\n",rId,time);
                        r++;
                        ffree((void **) &time);
                        ffree((void **) &rId);
                        destroyTime(rTime);
                    }
                    fclose(outputFile);
                    return;
                }
                if(flights && n2 > 0 && !reservations){ // There only is flights to be written
                    int f = 0;
                    while(f < n2){
                        Time * fTime = getFlightSDepartureDate(flights[f]);
                        char * time = timeToString(fTime);
                        time[10] = '\0';
                        char * fId = getFlightId(flights[f]);
                        if(f != 0) fprintf(outputFile,"\n");
                        fprintf(outputFile,"--- %d ---\n",f + 1);
                        fprintf(outputFile,"id: %s\ndate: %s\n",fId,time);
                        f++;
                        ffree((void **) &time);
                        ffree((void **) &fId);
                        destroyTime(fTime);
                    }
                    fclose(outputFile);
                    return;
                }
            }
        }
        if(outputFile != NULL) fclose(outputFile);
    }
    cursorOff();
    int command = 0;
    int rCount = 0;
    int fCount = 0;
    int max = n1 + n2;
    printQ2(f,&command,5,reservations,n1,&rCount,flights,n2,&fCount);
    dontWriteOnScreen();
    int input = getInput();
    while(input != 0){
        if(input == DOWN && command < max){
            printQ2(f,&command,5,reservations,n1,&rCount,flights,n2,&fCount);
            input = getInput();
            continue;
        }
        if(input == UP){
            int temp = 0;
            fCount -= 1;
            rCount -= 1;
            while(temp < 2){
                if(command % 5 == 0){
                    if(rCount > 0 && fCount > 0){
                        Time * r = getReservBeginDate(reservations[rCount]);
                        Time * f = getFlightSDepartureDate(flights[fCount]);
                        if(compareTimes(r,f) == true){
                            rCount--;
                        }else{
                            fCount--;
                        } 
                        destroyTime(r);
                        destroyTime(f);
                        command--;
                    }else{
                        if(rCount > 0){
                            rCount--;
                            command--;
                        }
                        if(fCount > 0){
                            fCount--;
                            command--;
                        }
                    }
                }

                while((command % 5) != 0 && command >= 0){
                    if(rCount > 0 && fCount > 0){
                        Time * r = getReservBeginDate(reservations[rCount]);
                        Time * f = getFlightSDepartureDate(flights[fCount]);
                        if(compareTimes(r,f) == true){
                            rCount--;
                        }else{
                            fCount--;
                        } 
                        destroyTime(r);
                        destroyTime(f);
                        command--;
                        continue;
                    }else{
                        if(rCount > 0){
                            rCount--;
                            command--;
                            continue;
                        }
                        if(fCount > 0){
                            fCount--;
                            command--;
                            continue;
                        }
                    }
                    break;
                }
                temp++;

            }
            if(rCount != 0 && fCount != 0){
                rCount += 1;
                fCount += 1;
            }else{
                command = 0;
            }
            printQ2(f,&command,5,reservations,n1,&rCount,flights,n2,&fCount);
        }
        input = getInput();
    }
    cursorOn();
    writeOnScreen();
}

void outputQ3(bool f,double rating){

    if(interactive == false){
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
        return;
    }
    cursorOff();
    printQ3(f,rating);
    dontWriteOnScreen();
    int input = getInput();
    while(input != 0){
        input = getInput();
    }
    writeOnScreen();
    cursorOn();
}

void outputQ4(bool f,Reservation ** rList,int max){
    if(interactive == false){
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
                    ffree((void **) &id);
                    ffree((void **) &stringBTime);
                    ffree((void **) &stringETime);
                    ffree((void **) &uId);
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

                    ffree((void **) &id);
                    ffree((void **) &stringBTime);
                    ffree((void **) &stringETime);
                    ffree((void **) &uId);
                    destroyTime(bTime);
                    destroyTime(eTime);
                }else{
                    break;
                }
            }
        }
        fclose(outputFile);
        return;
    }
    int index = 0;
    printQ4(f,5,&index,rList,max);
    dontWriteOnScreen();
    cursorOff();
    int input = getInput();
    while(input != 0){
        if(input == DOWN){
            if(index >= max){
                input = getInput();
                continue;
            }
            printQ4(f,5,&index,rList,max);
            input = getInput();
            continue;
        }
        if(input == UP){
            int rewinder = 0;
            while(rewinder < 2){
                if(index > 0) index -= 1;
                while(index > 0 && (index % 5) != 0) index -= 1;
                rewinder++;
            }
            printQ4(f,5,&index,rList,max);
            input = getInput();
            continue;
        }
        input = getInput();
    }
    writeOnScreen();
    cursorOn();
}

void outputQ5(bool f, Flight ** fList,int max){
    if(interactive == false){
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
                ffree((void **) &fId);
                ffree((void **) &sDepDate);
                ffree((void **) &destination);
                ffree((void **) &airline);
                ffree((void **) &planeModel);
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
                ffree((void **) &fId);
                ffree((void **) &sDepDate);
                ffree((void **) &destination);
                ffree((void **) &airline);
                ffree((void **) &planeModel);
            }
        }
        fclose(outputFile);
        return;
    }
    cursorOff();
    int index = 0;
    printQ5(f,5,&index,fList,max);
    dontWriteOnScreen();
    int input = getInput();
    while(input != 0){
        if(input == DOWN){
            if(index >= max){
                input = getInput();
                continue;
            }
            printQ5(f,5,&index,fList,max);
            input = getInput();
            continue;
        }
        if(input == UP){
            int rewinder = 0;
            while(rewinder < 2){
                if(index > 0) index -= 1;
                while(index > 0 && (index % 5) != 0) index -= 1;
                rewinder++;
            }
            printQ5(f,5,&index,fList,max);
            input = getInput();
            continue;
        }
        input = getInput();
    }
    writeOnScreen();
    cursorOn();
}


void outputQ6(bool f,int n, char ** names, int * number,int exists){
    if(interactive == false){
        commandAtual++;
        
        char fileName[50];

        memset(fileName,'\0',50);

        snprintf(fileName, 49, "Resultados/command%d_output.txt", commandAtual);

        FILE * outputFile = fopen(fileName, "a");

        if(!outputFile){
            perror("Query 6 command line did not open, probably file name wrong.\n");
            return;
        }
        int maxIndex = n;
        if(exists < n) maxIndex = exists;
        if(f == true){
            for(int j=0; j < maxIndex; j++){
                if(j!=0) fprintf(outputFile,"\n");
                fprintf(outputFile,"--- %d ---\n",j + 1);
                fprintf(outputFile,"name: %s\n",names[j]);
                fprintf(outputFile,"passengers: %d\n",number[j]);
            }
        }else{
            for(int k=0; k < maxIndex; k++){
            fprintf(outputFile,"%s;%d\n",names[k],number[k]);
            }
        }
        
        fclose(outputFile);
        return;
    }
    cursorOff();
    int index = 0;
    printQ6(f,5,&index,n,names,number);
    dontWriteOnScreen();
    int input = getInput();
    while(input != 0){
        if(input == DOWN){
            if(index >= n){
                input = getInput();
                continue;
            }
            printQ6(f,5,&index,n,names,number);
            input = getInput();
            continue;
        }
        if(input == UP){
            int rewinder = 0;
            while(rewinder < 2){
                if(index > 0) index -= 1;
                while(index > 0 && (index % 5) != 0) index -= 1;
                rewinder++;
            }
            printQ6(f,5,&index,n,names,number);
            input = getInput();
            continue;
        }
        input = getInput();
    }     
    writeOnScreen();
    cursorOn();
}

void outputQ7(bool f,SingularRecord * temp,int max){
    if(interactive == false){

        commandAtual++;
        
        
        char fileName[50];

        memset(fileName,'\0',50);

        snprintf(fileName, 49, "Resultados/command%d_output.txt", commandAtual);

        FILE * outputFile = fopen(fileName, "a");
        if(!outputFile){
            perror("Query 7 command line did not open, probably file name wrong.\n");
            return;
        }

        if(f == true){
            for(int i = 0;i < max && i < getSRecordSize(temp);i++){
                if(i != 0) fprintf(outputFile,"\n");
                char * airport = getSRecordName(temp,i);
                int delay = getSRecordListElement(temp,i);
                fprintf(outputFile,"--- %d ---\n",i + 1);
                fprintf(outputFile,"name: %s\n",airport);
                fprintf(outputFile,"median: %d\n",delay);
                ffree((void **) &airport);
            }
        }else{
            for(int i = 0;i < max && i < getSRecordSize(temp);i++){
                char * airport = getSRecordName(temp,i);
                int delay = getSRecordListElement(temp,i);
                fprintf(outputFile,"%s;%d\n",airport,delay);
                ffree((void **) &airport);
            }
        }
        fclose(outputFile);
        return;
    }
    cursorOff();
    int index = 0;
    printQ7(f,5,&index,temp,max);
    dontWriteOnScreen();
    int input = getInput();
    while(input != 0){
        if(input == DOWN){
            if(index >= max){
                input = getInput();
                continue;
            }
            printQ7(f,5,&index,temp,max);
            input = getInput();
            continue;
        }
        if(input == UP){
            int rewinder = 0;
            while(rewinder < 2){
                if(index > 0) index -= 1;
                while(index > 0 && (index % 5) != 0) index -= 1;
                rewinder++;
            }
            printQ7(f,5,&index,temp,max);
            input = getInput();
            continue;
        }
        input = getInput();
    }
    cursorOn();
    writeOnScreen();
}


void outputQ8(bool f, int revenue){
    if(interactive == false){
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
            fprintf(outputFile,"revenue: %d\n",revenue);
        }else{
            fprintf(outputFile,"%d\n",revenue);
        }
        fclose(outputFile);
        return;
    }
    printQ8(f,revenue);
    cursorOff();
    dontWriteOnScreen();
    int input = getInput();
    while(input != 0) input = getInput();
    cursorOn();
    writeOnScreen();
}

void outputQ9(char ** ids,char ** names,int valids,bool f){
    if(interactive == false){
        commandAtual++;

        char fileName[50];

        memset(fileName,'\0',50);

        snprintf(fileName, 49, "Resultados/command%d_output.txt", commandAtual);

        FILE * outputFile = fopen(fileName, "a");
        if(!outputFile){
            perror("Query 9 command line did not open, probably file name wrong.\n");
            return;
        }
        if(f== true){
            for(int k = 0; k<valids;k++){
                if(k>0) fprintf(outputFile,"\n");
                fprintf(outputFile,"--- %d ---\n",k+1);
                fprintf(outputFile,"id: %s\n",ids[k]);
                fprintf(outputFile,"name: %s\n",names[k]);
            }
        }else{
            for(int k = 0; k<valids;k++){
                fprintf(outputFile,"%s;%s\n",ids[k],names[k]);
            } 
        }
        fclose(outputFile);
        return;
    }
    int index = 0;
    cursorOff();
    printQ9(f,5,&index,ids,names,valids);
    dontWriteOnScreen();
    int input = getInput();
    while(input != 0){
        if(input == DOWN){
            if(index >= valids){
                input = getInput();
                continue;
            }
            printQ9(f,5,&index,ids,names,valids);
            input = getInput();
            continue;
        }
        if(input == UP){
            int rewinder = 0;
            while(rewinder < 2){
                if(index > 0) index -= 1;
                while(index > 0 && (index % 5) != 0) index -= 1;
                rewinder++;
            }
            printQ9(f,5,&index,ids,names,valids);
            input = getInput();
            continue;
        }
        input = getInput();
    }
    cursorOn();
    writeOnScreen();
}