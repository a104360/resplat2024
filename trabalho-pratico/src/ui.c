#include "../include/ui.h"
#include <ncurses.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>
#include <string.h>

WINDOW * terminal;

static WINDOW * drawMainMenu(int bWidth, int bHeight) {
    int width = bWidth * 0.70;
    int height = bHeight * 0.90; 
    int x = 0.16 * bWidth;
    int y = 0.06 * bHeight;
    WINDOW *main = newwin(height, width, y, x);
    refresh();
    box(main, 0, 0);
    mvwprintw(main,0.1 * height,(int)((width - 42)/ 2),"Bem-vindo à nossa plataforma de reservas");
    wrefresh(main);
    return main;
}

static WINDOW * drawSearchBox(int bWidth, int bHeight){
    int width = (bWidth * 0.70);
    int height = (bHeight * 0.90) * 0.9;
    int x = (0.16 * bWidth) + (0.15 * width);
    WINDOW * search = newwin(3,width * 0.7,height,x);
    mvwprintw(search,1,1,"> ");
    refresh();
    box(search,0,0);
    wrefresh(search);
    return search;
}

static void requestSomething(WINDOW * menu,int bWidth,int bHeight,const char * message){
    int length = strlen(message);
    int x = (bWidth - length) / 2;
    mvwprintw(menu,0.5 * bHeight,x,"%s",message);
    wrefresh(menu);
}

static void warning(int yW,int xW,int heightW,int widthW,const char * line){
    WINDOW * warning = newwin(5,50,heightW * 0.7,((widthW - 50) / 2) + xW);
    refresh();
    mvwprintw(warning,1,5,"%s inserido é inválido.",line);
    mvwprintw(warning,3,5,"Por favor, tentar de novo.");
    box(warning,0,0);
    wrefresh(warning);
    getch();
    wclear(warning);
    wrefresh(warning);
    delwin(warning);
    refresh();
}

static void newSearch(WINDOW * search,char * buffer,int max){
    for(int i = 0; i < max;buffer[i] = '\0',i++);
    wclear(search);
    box(search,0,0);
    mvwprintw(search, 1, 1, "> ");
    wmove(search,1,3);
    wrefresh(search);
    wgetnstr(search, buffer,max);
}

static bool checkPath(const char * path){
    char * dup = strdup(path);
    dup[6] = '\0';
    if(strcoll(dup,"../../") != 0){
        free(dup);
        return false;
    }
    free(dup);
    return true;
}

static bool checkMode(const char * mode){
    char * dup = strdup(mode);
    dup[1] = '\0';
    if(!strcasecmp(dup,"t") || !strcasecmp(dup,"f")){
        free(dup);
        return true;
    }
    free(dup);
    return false;
}

static bool checkQuery(const char * line){
    if(line[0] == '1') return true;
    return false;
}

static char * getPath(WINDOW * search,int yW, int xW,int heightW,int widthW){
    char * buffer = malloc(sizeof(char) * 51);
    mvwprintw(search, 1, 1, "> ");
    wrefresh(search);
    wgetnstr(search, buffer, 50);

    while(checkPath(buffer) != true){
        warning(yW,xW,heightW,widthW,"Path");
        newSearch(search,buffer,50);
    }
    return buffer;
}

static char * getQuery(WINDOW * search,int yW, int xW,int heightW,int widthW){
    char * buffer = malloc(sizeof(char) * 101);
    newSearch(search,buffer,100);

    while(checkQuery(buffer) != true){
        warning(yW,xW,heightW,widthW,"Query");
        newSearch(search,buffer,100);
        refresh();
    }
    return buffer;
}


static bool getMode(WINDOW * search,int yW, int xW,int heightW,int widthW){
    char * buffer = malloc(sizeof(char) * 2);
    newSearch(search,buffer,2);

    while(checkMode(buffer) != true){
        warning(yW,xW,heightW,widthW,"Mode");
        newSearch(search,buffer,2);
        refresh();
    }
    if(!strcasecmp(buffer,"f")){
        wclear(search);
        box(search,0,0);
        wrefresh(search);
        free(buffer);
        return false;
    }
    wclear(search);
    box(search,0,0);
    wrefresh(search);
    free(buffer);
    return true;
}






void printQ1User(int dist,int F, char * name, char sex, int age, char * country_code , 
            char * passport , char * number_of_flights, char * number_of_reservations, char * total_spent){
    noecho();
    wclear(terminal);
    box(terminal,0,0);
    if(F == false)mvwprintw(terminal,dist,20,"%s;%c;%d;%s;%s;%s;%s,%s",name,sex,age,country_code,passport,number_of_flights,number_of_reservations,total_spent);
    else {
        mvwprintw(terminal,dist,20,"--- 1 ---");
        mvwprintw(terminal,dist + 1,20,"name: %s",name);
        mvwprintw(terminal,dist + 2,20,"sex: %c",sex);
        mvwprintw(terminal,dist + 3,20,"age: %d",age);
        mvwprintw(terminal,dist + 4,20,"country_code: %s",country_code);
        mvwprintw(terminal,dist + 5,20,"passport: %s",passport);
        mvwprintw(terminal,dist + 6,20,"number_of_flights: %s",number_of_flights);
        mvwprintw(terminal,dist + 7,20,"number_of_reservations: %s",number_of_reservations);
        mvwprintw(terminal,dist + 8,20,"total_spent: %s",total_spent);
    }
    wrefresh(terminal);
}

void printQ1Flight(int dist,int F, char * airline, char * plane_model , char * origin, 
            char * destination,char * schedule_departure_date , char * schedule_arrival_date, int passengers, int delay){

    noecho();
    wclear(terminal);
    box(terminal,0,0);
    if(F == false)mvwprintw(terminal,dist,20,"%s;%s;%s;%s;%s;%s;%d;%d",airline,plane_model,origin,destination,schedule_departure_date,schedule_arrival_date,passengers,delay);
    else {
        mvwprintw(terminal,dist,20,"--- 1 ---");
        mvwprintw(terminal,dist + 1,20,"airline: %s", airline);
        mvwprintw(terminal,dist + 2,20,"plane_model: %s", plane_model);
        mvwprintw(terminal,dist + 3,20,"origin: %s", origin);
        mvwprintw(terminal,dist + 4,20,"destination: %s", destination);
        mvwprintw(terminal,dist + 5,20,"schedule_departure_date: %s", schedule_departure_date);
        mvwprintw(terminal,dist + 6,20,"schedule_arrival_date: %s", schedule_arrival_date);
        mvwprintw(terminal,dist + 7,20,"passengers: %d", passengers);
        mvwprintw(terminal,dist + 8,20,"delay: %d", delay);
    }
    wrefresh(terminal);
}

void printQ1Reservation(int dist,int F, char * hotel_id, char * hotel_name , int hotel_stars, char * begin_date , char * end_date , 
            bool includes_breakfast, int nights, double total_price){
    noecho();
    wclear(terminal);
    box(terminal,0,0);
    if(F == false){
        if(includes_breakfast == true) mvwprintw(terminal,dist,20,"%s;%s;%d;%s;%s;True;%d;%.3f",hotel_id,hotel_name,hotel_stars,begin_date,end_date,nights,total_price);
        else mvwprintw(terminal,dist,20,"%s;%s;%d;%s;%s;False;%d;%.3f",hotel_id,hotel_name,hotel_stars,begin_date,end_date,nights,total_price);
    }
    else {
        mvwprintw(terminal,dist,20,"--- 1 ---");
        mvwprintw(terminal,dist + 1,20,"hotel_id: %s", hotel_id);
        mvwprintw(terminal,dist + 2,20,"hotel_name: %s", hotel_name);
        mvwprintw(terminal,dist + 3,20,"hotel_stars: %d", hotel_stars);
        mvwprintw(terminal,dist + 4,20,"begin_date: %s", begin_date);
        mvwprintw(terminal,dist + 5,20,"end_date: %s", end_date);
        if(includes_breakfast == true) mvwprintw(terminal,dist + 6,20,"True");
        else mvwprintw(terminal,dist + 6,20,"False");
        mvwprintw(terminal,dist + 7,20,"nights: %d", nights);
        mvwprintw(terminal,dist + 8,20,"total_price: %.3f", total_price);
    }
    wrefresh(terminal);
}


void printQ2(bool f,int * command,int dist,int npp,Reservation ** reservations,int n1,int * rCount, Flight ** flights,int n2,int * fCount){
    int yChunk = 1;
    if(f == false){ // Normal Mode
        if(reservations && n1 > 0 && flights && n2 > 0){ // There is both reservations and flights to be written
            int max = n1 + n2;
            while(yChunk - 1 < max && yChunk - 1 < npp){
                if(*rCount < n1 && *fCount < n2){ // Both the arrays have not reached their limit 
                    Time * rTime = getReservBeginDate(reservations[*rCount]);
                    Time * fTime = getFlightSDepartureDate(flights[*fCount]);
                    if(compareTimes(rTime,fTime) == true){ // Flight is more recent that the reservation
                        char * time = timeToString(fTime);
                        time[10] = '\0';
                        char * fId = getFlightId(flights[*fCount]);
                        mvwprintw(terminal,dist * yChunk,20,"%s;%s;flight",fId,time);
                        yChunk++;
                        *fCount += 1;
                        ffree((void **) &time);
                        ffree((void **) &fId);
                    }
                    else{ // Reservation is more recent that the flight
                        char * time = timeToString(rTime);
                        time[10] = '\0';
                        char * rId = getReservId(reservations[*rCount]);
                        mvwprintw(terminal,dist * yChunk,20,"%s;%s;reservation",rId,time);
                        yChunk++;
                        *rCount += 1;
                        ffree((void **) &time);
                        ffree((void **) &rId);
                    }
                    destroyTime(rTime);
                    destroyTime(fTime);
                    continue;
                }
                if(*rCount < n1 && *fCount >= n2){ // Flights array have reached his limit
                    Time * rTime = getReservBeginDate(reservations[*rCount]);
                    char * time = timeToString(rTime);
                    time[10] = '\0';
                    char * rId = getReservId(reservations[*rCount]);
                    mvwprintw(terminal,dist * yChunk,20,"%s;%s;reservation",rId,time);
                    yChunk++;
                    *rCount += 1;
                    ffree((void **) &time);
                    ffree((void **) &rId);
                    destroyTime(rTime);
                    continue;
                }
                if(*rCount >= n1 && *fCount < n2){ // Reservations array have reached his limit
                    Time * fTime = getFlightSDepartureDate(flights[*fCount]);
                    char * time = timeToString(fTime);
                    time[10] = '\0';
                    char * fId = getFlightId(flights[*fCount]);
                    mvwprintw(terminal,dist * yChunk,20,"%s;%s;flight",fId,time);
                    yChunk++;
                    *fCount += 1;
                    ffree((void **) &time);
                    ffree((void **) &fId);
                    destroyTime(fTime);
                    continue;
                }
            }
            wrefresh(terminal);
            return;
        }else{
            if(reservations && n1 > 0){ // There only is reservations to be written
                while(*rCount < n1 && (yChunk - 1) < npp){
                    Time * rTime = getReservBeginDate(reservations[*rCount]);
                    char * time = timeToString(rTime);
                    time[10] = '\0';
                    char * rId = getReservId(reservations[*rCount]);
                    mvwprintw(terminal,dist * yChunk,20,"%s;%s",rId,time);
                    yChunk++;
                    *rCount += 1;
                    ffree((void **) &time);
                    ffree((void **) &rId);
                    destroyTime(rTime);
                }
                return;
            }
            if(flights && n2 > 0){ // There only is flights to be written
                while(*fCount < n2 && yChunk - 1 < npp){
                    Time * fTime = getFlightSDepartureDate(flights[*fCount]);
                    char * time = timeToString(fTime);
                    time[10] = '\0';
                    char * fId = getFlightId(flights[*fCount]);
                    mvwprintw(terminal,dist * yChunk,20,"%s;%s",fId,time);
                    yChunk++;
                    *fCount += 1;
                    ffree((void **) &time);
                    ffree((void **) &fId);
                    destroyTime(fTime);
                }
                return;
            }
        }
    }else{ // F Mode
        if(reservations && n1 > 0 && flights && n2 > 0){ // There is both reservations and flights to be written
            
            int max = n1 + n2;

            while(*rCount + *fCount + 2 < max && yChunk - 1 < npp){
                if(*rCount < n1 && *fCount < n2){ // Both the arrays have not reached their limit 
                    Time * rTime = getReservBeginDate(reservations[*rCount]);
                    Time * fTime = getFlightSDepartureDate(flights[*fCount]);
                    if(compareTimes(rTime,fTime) == true){ // Flight is more recent that the reservation
                        char * time = timeToString(fTime);
                        time[10] = '\0';
                        char * fId = getFlightId(flights[*fCount]);
                        mvwprintw(terminal,(dist * yChunk),20,"--- %d ---",command);
                        mvwprintw(terminal,(dist * yChunk) + 1,20,"id: %s",fId);
                        mvwprintw(terminal,(dist * yChunk) + 2,20,"date: %s",time);
                        mvwprintw(terminal,(dist * yChunk) + 3,20,"type: flight");
                        yChunk++;
                        *fCount += 1;
                        *command += 1;
                        ffree((void **) &time);
                        ffree((void **) &fId);
                    }
                    else{ // Reservation is more recent that the flight
                        char * time = timeToString(rTime);
                        time[10] = '\0';
                        char * rId = getReservId(reservations[*rCount]);
                        mvwprintw(terminal,(dist * yChunk),20,"--- %d ---",command);
                        mvwprintw(terminal,(dist * yChunk) + 1,20,"id: %s",rId);
                        mvwprintw(terminal,(dist * yChunk) + 2,20,"date: %s",time);
                        mvwprintw(terminal,(dist * yChunk) + 3,20,"type: reservation");
                        yChunk++;
                        *rCount += 1;
                        *command += 1;
                        ffree((void **) &time);
                        ffree((void **) &rId);
                    }
                    destroyTime(rTime);
                    destroyTime(fTime);
                    continue;
                }
                if(*rCount < n1 && *fCount >= n2){ // Flights array have reached his limit, but the reservations has not
                    while (*rCount < n1 && yChunk - 1 < npp)
                    {                
                        Time * rTime = getReservBeginDate(reservations[*rCount]);
                        char * time = timeToString(rTime);
                        time[10] = '\0';
                        char * rId = getReservId(reservations[*rCount]);
                        mvwprintw(terminal,(dist * yChunk),20,"--- %d ---",command + 1);
                        mvwprintw(terminal,(dist * yChunk) + 1,20,"id: %s",rId);
                        mvwprintw(terminal,(dist * yChunk) + 2,20,"date: %s",time);
                        mvwprintw(terminal,(dist * yChunk) + 3,20,"type: reservation");
                        yChunk++;
                        *rCount += 1;
                        *command += 1;
                        ffree((void **) &time);
                        ffree((void **) &rId);
                        destroyTime(rTime);
                    }
                    return;
                }
                if(reservations && flights && *rCount == n1 && *fCount < n2){ // Reservations array have reached his limit but the flights have not
                    while (*fCount < n2 && yChunk - 1 < npp)
                    {
                        Time * fTime = getFlightSDepartureDate(flights[*fCount]);
                        char * time = timeToString(fTime);
                        time[10] = '\0';
                        char * fId = getFlightId(flights[*fCount]);
                        mvwprintw(terminal,(dist * yChunk),20,"--- %d ---",command + 1);
                        mvwprintw(terminal,(dist * yChunk) + 1,20,"id: %s",fId);
                        mvwprintw(terminal,(dist * yChunk) + 2,20,"date: %s",time);
                        mvwprintw(terminal,(dist * yChunk) + 3,20,"type: flight");
                        yChunk++;
                        *fCount += 1;
                        *command += 1;
                        ffree((void **) &time);
                        ffree((void **) &fId);
                        destroyTime(fTime);
                    }
                    return;
                }
            }
            return;


        }else{
            if(reservations && n1 > 0 && !flights){ // There only is reservations to be written
                while(*rCount < n1){
                    Time * rTime = getReservBeginDate(reservations[*rCount]);
                    char * time = timeToString(rTime);
                    time[10] = '\0';
                    char * rId = getReservId(reservations[*rCount]);
                    mvwprintw(terminal,(dist * yChunk),20,"--- %d ---",command);
                    mvwprintw(terminal,(dist * yChunk) + 1,20,"id: %s",rId);
                    mvwprintw(terminal,(dist * yChunk) + 2,20,"date: %s",time);
                    yChunk++;
                    *rCount += 1;
                    *command += 1;
                    ffree((void **) &time);
                    ffree((void **) &rId);
                    destroyTime(rTime);
                }
                return;
            }
            if(flights && n2 > 0 && !reservations){ // There only is flights to be written
                while(*fCount < n2){
                    Time * fTime = getFlightSDepartureDate(flights[*fCount]);
                    char * time = timeToString(fTime);
                    time[10] = '\0';
                    char * fId = getFlightId(flights[*fCount]);
                    mvwprintw(terminal,(dist * yChunk),20,"--- %d ---",command + 1);
                    mvwprintw(terminal,(dist * yChunk) + 1,20,"id: %s",fId);
                    mvwprintw(terminal,(dist * yChunk) + 2,20,"date: %s",time);
                    yChunk++;
                    *fCount += 1;
                    *command += 1;
                    ffree((void **) &time);
                    ffree((void **) &fId);
                    destroyTime(fTime);
                }
                return;
            }
        }
    }
}




void printQ3(bool f,int dist,double rating){
    if(f == false){
        mvwprintw(terminal,dist,20,"%.3f",rating);
        wrefresh(terminal);
        return;
    }
    mvwprintw(terminal,dist,20,"--- 1 ---");
    mvwprintw(terminal,dist + 1,20,"rating: %.3f",rating);
    wrefresh(terminal);
}


void printQ4(bool f,int dist,int npp,int * index,Reservation ** reservation,int max){
    int yChunk = 1;
    if(f == false){
        while(*index < max && yChunk - 1 < npp){
            if(reservation[*index]){
                char * id = getReservId(reservation[*index]);
                Time * bTime = getReservBeginDate(reservation[*index]);
                Time * eTime = getReservEndDate(reservation[*index]);
                char * stringBTime = timeToString(bTime);
                char * stringETime = timeToString(eTime);
                char * uId = getReservUserId(reservation[*index]);
                int rating = getReservRating(reservation[*index]);
                int n = numberOfDays(bTime,eTime);

                mvwprintw(terminal,dist * yChunk,20,"%s;%s;%s;%s;%d;%0.3f",id,stringBTime,stringETime,uId,rating,getTotalSpentOnReserv(reservation[*index],n));

                ffree((void **) &id);
                ffree((void **) &stringBTime);
                ffree((void **) &stringETime);
                ffree((void **) &uId);
                destroyTime(bTime);
                destroyTime(eTime);
            }
            *index += 1;
            yChunk++;
        }
        wrefresh(terminal);
        return;
    }
    while(*index < max && yChunk - 1 < npp){
        if(reservation[*index]){
            char * id = getReservId(reservation[*index]);
            Time * bTime = getReservBeginDate(reservation[*index]);
            Time * eTime = getReservEndDate(reservation[*index]);
            char * stringBTime = timeToString(bTime);
            char * stringETime = timeToString(eTime);
            char * uId = getReservUserId(reservation[*index]);
            int rating = getReservRating(reservation[*index]);
            int n = numberOfDays(bTime,eTime);
            
            mvwprintw(terminal,(dist * yChunk),20,"--- %d ---",*index + 1);
            mvwprintw(terminal,(dist * yChunk) + 1,20,"id: %s",id);
            mvwprintw(terminal,(dist * yChunk) + 2,20,"begin_date: %s",stringBTime);
            mvwprintw(terminal,(dist * yChunk) + 3,20,"end_date: %s",stringETime);
            mvwprintw(terminal,(dist * yChunk) + 4,20,"user_id: %s",uId);
            mvwprintw(terminal,(dist * yChunk) + 5,20,"rating: %d",rating);
            mvwprintw(terminal,(dist * yChunk) + 6,20,"total_price: %0.3f",getTotalSpentOnReserv(reservation[*index],n));

            ffree((void **) &id);
            ffree((void **) &stringBTime);
            ffree((void **) &stringETime);
            ffree((void **) &uId);
            destroyTime(bTime);
            destroyTime(eTime);
        }
        *index += 1;
        yChunk++;
    }
}

void printQ5(bool f,int dist,int npp,int* index,Flight** flight,int max){
    int yChunk = 1;
    if(f == false){
        while(*index < max && yChunk - 1 < npp){
            if(flight[*index]){
            char * fId = getFlightId(flight[*index]);
            Time * sDD = getFlightSDepartureDate(flight[*index]);
            char * sDepDate = timeToString(sDD);
            char * destination = getFlightDestination(flight[*index]);
            char * airline = getFlightAirline(flight[*index]);
            char * planeModel = getFlightPlaneModel(flight[*index]);
            mvwprintw(terminal,dist * yChunk,20,"%s;%s;%s;%s;%s",
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
            *index += 1;
            yChunk++;
            }
        }
        return;
    }
    while(*index < max && yChunk - 1 < npp){
        if(flight[*index]){
        char * fId = getFlightId(flight[*index]);
        Time * sDD = getFlightSDepartureDate(flight[*index]);
        char * sDepDate = timeToString(sDD);
        char * destination = getFlightDestination(flight[*index]);
        char * airline = getFlightAirline(flight[*index]);
        char * planeModel = getFlightPlaneModel(flight[*index]);
        mvwprintw(terminal,(dist * yChunk),20,"--- %d ---",*index + 1);
        mvwprintw(terminal,(dist * yChunk) + 1,20,"id: %s",fId);
        mvwprintw(terminal,(dist * yChunk) + 2,20,"schedule_departure_date: %s",sDepDate);
        mvwprintw(terminal,(dist * yChunk) + 3,20,"destination: %s",destination);
        mvwprintw(terminal,(dist * yChunk) + 4,20,"airline: %s",airline);
        mvwprintw(terminal,(dist * yChunk) + 5,20,"plane_model: %s",planeModel);
        destroyTime(sDD);
        ffree((void **) &fId);
        ffree((void **) &sDepDate);
        ffree((void **) &destination);
        ffree((void **) &airline);
        ffree((void **) &planeModel);
        *index += 1;
        yChunk++;
        }
    }
    wrefresh(terminal);
}

void printQ6(bool f,int dist,int npp,int * index,int max,char ** names,int * passengers){
    int yChunk = 1;
    if(f == false){
        while(yChunk - 1 < npp && *index < max){
            if(names[*index]){
                mvwprintw(terminal,dist * yChunk,20,"%s;%d",names[*index],passengers[*index]);
                yChunk++;
                *index += 1;
                continue;
            }
        }
        wrefresh(terminal);
        return;
    }
    while(yChunk - 1 < npp && *index < max){
        if(names[*index]){
            mvwprintw(terminal,(dist * yChunk),20,"--- %d ---",*index + 1);
            mvwprintw(terminal,(dist * yChunk) + 1,20,"name: %s",names[*index]);
            mvwprintw(terminal,(dist * yChunk) + 2,20,"passengers: %d",passengers[*index]);
            yChunk++;
            *index += 1;
        }
    }
    wrefresh(terminal);
}

void printQ7(bool f,int dist,int npp,int * index,SingularRecord * table,int max){
    int yChunk = 1;
    if(f == false){
        while(yChunk - 1 < npp && *index < max){
            char * airport = getSRecordName(table,*index);
            int delay = getSRecordListElement(table,*index);
            mvwprintw(terminal,dist * yChunk,20,"%s;%d",airport,delay);
            ffree((void **) &airport);
            yChunk++;
            *index += 1;
        }
        wrefresh(terminal);
        return;
    }
    while(yChunk - 1 < npp && *index < max){
        char * airport = getSRecordName(table,*index);
        int delay = getSRecordListElement(table,*index);
        mvwprintw(terminal,(dist * yChunk),20,"--- %d ---");
        mvwprintw(terminal,(dist * yChunk) + 1,20,"name: %s",airport);
        mvwprintw(terminal,(dist * yChunk) + 2,20,"median: %s",delay);
        ffree((void **) &airport);
        yChunk++;
        *index += 1;
    }
    wrefresh(terminal);
}

void printQ8(bool f,int dist,int revenue){
    if(f == false){
        mvwprintw(terminal,dist,20,"%d",revenue);
        wrefresh(terminal);
        return;
    }
    mvwprintw(terminal,dist,20,"--- 1 ---");
    mvwprintw(terminal,dist + 1,"revenue: %d",revenue);
    wrefresh(terminal);
}


// PODE NAO SER NECESSARIO
static void printPageNF(WINDOW * window,int * count,int dist,int nPerPage, char ** names,int size){
    wclear(window);
    box(window,0,0);
    int y = 1;

    mvwprintw(window,dist * y, 20,"%s",names[*count]);
    y++;
    *count += 1;
    while(((*count % nPerPage) != 0) && *count < size){
        mvwprintw(window,dist * y,20,"%s",names[*count]);
        y++;
        *count += 1;
    }
    wrefresh(window);
    return;
    
}

void printQ9(bool f,int dist,int npp,int * index,char ** ids,char ** names,int max){
    
}

// FALTA ATUALIZAR
void navigatePages(WINDOW * window,int height,int width,int nPerPage,int size,char ** names,bool f){
    noecho();
    keypad(window,TRUE);
    int dist = (height - nPerPage) / (nPerPage + 1);
    int count = 0;
    int y = 1;
    wclear(window);
    box(window,0,0);
    wrefresh(window);
    refresh();
    if(f == false){
        printPageNF(window,&count,dist,nPerPage,names,size);
        int ch = getch();
        while(ch != 'q'){
            if((ch == 's' || ch == KEY_DOWN) && count < size){
                printPageNF(window,&count,dist,nPerPage,names,size);
                wrefresh(window);
                ch = getch();
                continue;
            }
            if(ch == 'w' || ch == KEY_UP){
                wclear(window);
                box(window,0,0);
                count -= nPerPage * 2;
                if(count < 0) count = 0;
                printPageNF(window,&count,dist,nPerPage,names,size);
                wrefresh(window);
                ch = getch();
                continue;
            }
            else{
                ch = getch();
                continue;
            }
        }
    }else{
        mvwprintw(window,dist * y - 1, 20,"---%d---",count + 1);
        mvwprintw(window,dist * y, 20,"%s",names[count]);
        y++;
        count++;
        while(((count % nPerPage) != 0) && count < size){
            mvwprintw(window,dist * y - 1, 20,"---%d---",count + 1);
            mvwprintw(window,dist * y,20,"%s",names[count]);
            y++;
            count++;
        }
        wrefresh(window);
        int ch = getch();
        while(ch != 'q'){
            if((ch == 's' || ch == KEY_DOWN) && count < size){
                wclear(window);
                box(window,0,0);
                y = 1;
                mvwprintw(window,dist * y - 1, 20,"---%d---",count + 1);
                mvwprintw(window,dist * y,20,"%s",names[count]);
                y++;
                count++;
                while(((count % nPerPage) != 0) && count < size){
                    mvwprintw(window,dist * y - 1, 20,"---%d---",count + 1);
                    mvwprintw(window,dist * y,20,"%s",names[count]);
                    y++;
                    count++;
                }
                wrefresh(window);
                ch = getch();
                continue;
            }
            if(ch == 'w' || ch == KEY_UP){
                wclear(window);
                box(window,0,0);
                count -= nPerPage * 2;
                if(count < 0) count = 0;
                y = 1;
                mvwprintw(window,dist * y - 1, 20,"---%d---",count + 1);
                mvwprintw(window,dist * y,20,"%s",names[count]);
                y++;
                count++;
                while(((count % nPerPage) != 0) && count < size){
                    mvwprintw(window,dist * y - 1, 20,"---%d---",count + 1);
                    mvwprintw(window,dist * y,20,"%s",names[count]);
                    y++;
                    count++;
                }
                wrefresh(window);
                ch = getch();
                continue;
            }
            else{
                ch = getch();
                continue;
            }
        }
    }
    wclear(window);
}


void interactive(){
    initscr();
    cbreak();
    keypad(stdscr,true);

    int scrWidth = 0,scrHeight = 0;
    getmaxyx(stdscr,scrHeight,scrWidth);
    int width = scrWidth;
    int height = scrHeight;
    
    
    const int windowWidth = 0.7 * scrWidth;
    const int windowHeight = 0.9 * scrHeight;


    const int xW = 0.16 * scrWidth;
    const int yW = 0.06 * scrHeight;



    terminal = drawMainMenu(width,height);
    keypad(terminal,true);
    requestSomething(terminal,windowWidth,windowHeight,"Por favor, insira o path para os csvs.");


    WINDOW * search = drawSearchBox(width,height);

    char * buffer = getPath(search,yW,xW,windowHeight,windowWidth);
    free(buffer);
    buffer = NULL;

    wclear(search);
    box(search,0,0);
    wrefresh(search);

    requestSomething(terminal,windowWidth,windowHeight,"Por favor, insira o modo para os outputs(F ou T).");

    bool mode = getMode(search,yW,xW,windowHeight,windowWidth);
    
    requestSomething(terminal,windowWidth,windowHeight,"Por favor, insira a query e parametros (h para ajuda).");

    char * query = getQuery(search,yW,xW,windowHeight,windowWidth);

    

    wclear(terminal);
    delwin(terminal);
    endwin();
}