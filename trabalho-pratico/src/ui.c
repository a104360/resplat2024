#include "../include/ui.h"
#include "../include/statistics.h"
#include "../include/parser.h"
#include "../include/interpreter.h"
#include <ncurses.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>
#include <string.h>

WINDOW * terminal;
int dist;

#define NEWPAGE wclear(terminal);\
    box(terminal,0,0);\


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
    int size = strlen(path);
    char * buffer = malloc(sizeof(char) * (size + 20));
    memset(buffer,'\0',size + 20);
    strncpy(buffer,path,size);
    
    if(path[size] == '/') strncat(buffer,"users.csv",10);
    else strncat(buffer,"/users.csv",11);
    FILE * test = NULL;
    test = fopen(buffer,"r");
    if(test == NULL){
        free(buffer);
        return false;
    }
    fclose(test);
    test = NULL;

    memset(buffer,'\0',size + 20);
    strncpy(buffer,path,size);
    
    if(path[size-1] == '/') strncat(buffer,"reservations.csv",18);
    else strncat(buffer,"/reservations.csv",18);
    test = fopen(buffer,"r");
    if(test == NULL){
        free(buffer);
        return false;
    }
    fclose(test);
    test = NULL;

    memset(buffer,'\0',size + 20);
    strncpy(buffer,path,size);
    
    if(path[size-1] == '/') strncat(buffer,"flights.csv",13);
    else strncat(buffer,"/flights.csv",13);
    test = fopen(buffer,"r");
    if(test == NULL){
        free(buffer);
        return false;
    }
    fclose(test);
    test = NULL;

    memset(buffer,'\0',size + 20);
    strncpy(buffer,path,size);
    
    if(path[size-1] == '/') strncat(buffer,"passengers.csv",16);
    else strncat(buffer,"/passengers.csv",16);
    test = fopen(buffer,"r");
    if(test == NULL){
        free(buffer);
        return false;
    }
    fclose(test);
    test = NULL;

    free(buffer);
    return true;
}

/*static bool checkMode(const char * mode){
    char * dup = strdup(mode);
    dup[1] = '\0';
    if(!strcasecmp(dup,"t") || !strcasecmp(dup,"f")){
        free(dup);
        return true;
    }
    free(dup);
    return false;
}*/

static bool checkQuery(const char * line){
    char * dup = strdup(line);
    char * token = NULL;
    char * saveptr = NULL;
    token = strtok_r(dup," ",&saveptr);
    if(strlen(token) > 2){
        free(dup);
        return false;
    }
    int n = atoi(token);
    if(token == 0){
        free(dup);
        return false;
    }
    Time * buffer = NULL;
    switch (n)
    {
    case 1:
        token = strtok_r(NULL," \n\0",&saveptr);
        if(token == NULL){
            free(dup);
            return false;
        }
        free(dup);
        return true;
        break;

    case 2:
        token = strtok_r(NULL," \n\0",&saveptr);
        if(token == NULL){
            free(dup);
            return false;
        }
        token = strtok_r(NULL," \n\0",&saveptr);
        if(token == NULL){
            free(dup);
            return true;
        }
        if(strcasecmp(token,"flights") != 0 && strcasecmp(token,"reservations") != 0){
            free(dup);
            return false;
        }
        free(dup);
        return true;        
        break;
    case 3:
        token = strtok_r(NULL," \n\0",&saveptr);
        if(!token){
            free(dup);
            return false;
        }
        free(dup);
        return true;
        break;
    case 4:
        token = strtok_r(NULL," \n\0",&saveptr);
        if(!token){
            free(dup);
            return false;
        }
        free(dup);
        return true;
        break;
    case 5:
        token = strtok_r(NULL," ",&saveptr); // Name
        if(!token){
            free(dup);
            return false;
        }

        token = strtok_r(NULL,"\"",&saveptr); // First Date
        if(!token){
            free(dup);
            return false;
        }
        buffer = dateCheck(token);
        if(buffer == NULL){
            free(dup);
            return false;
        }
        destroyTime(buffer);

        if(saveptr[0] == '\0' || saveptr[0] == '\n' || saveptr[1] == '\0' || saveptr[1] == '\n'){ 
            free(dup);
            return false;
        }
        saveptr = &saveptr[1]; // Skipping the space between the dates

        token = strtok_r(NULL,"\"",&saveptr); // Second date 
        if(!token){
            free(dup);
            return false;
        }
        buffer = dateCheck(token);
        if(buffer == NULL){
            free(dup);
            return false;
        }
        destroyTime(buffer);

        free(dup);
        return true;
        break;
    case 6:
        token = strtok_r(NULL," ",&saveptr); // Year 
        if(!token){
            free(dup);
            return false;
        }
        if(atoi(token) == 0){
            free(dup);
            return false;
        }

        token = strtok_r(NULL," \n\0",&saveptr); // N 
        if(!token){
            free(dup);
            return false;
        }
        if(atoi(token) == 0){
            free(dup);
            return false;
        }
        free(dup);
        return true;
        break;
    case 7:
        token = strtok_r(NULL," \n\0",&saveptr);
        if(!token){
            free(dup);
            return false;
        }
        if(atoi(token) == 0){
            free(dup);
            return false;
        }
        free(dup);
        return true;
        break;
    case 8:
        token = strtok_r(NULL," \n\0",&saveptr);
        if(!token){
            free(dup);
            return false;
        }
        token = strtok_r(NULL," \n\0",&saveptr);
        if(!token){
            free(dup);
            return false;
        }
        buffer = dateCheck(token);
        if(!buffer){
            free(dup);
            return false;
        }
        destroyTime(buffer);

        token = strtok_r(NULL," \n\0",&saveptr);
        if(!token){
            free(dup);
            return false;
        }
        buffer = dateCheck(token);
        if(!buffer){
            free(dup);
            return false;
        }
        destroyTime(buffer);
        free(dup);
        return true;
        break;
    case 9:
        token = strtok_r(NULL," \n\0",&saveptr);
        if(!token){
            free(dup);
            return false;
        }

        free(dup);
        break;

    default:
        if(dup) free(dup);
        return false;
        break;
    }
    return true;
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


/*static bool getMode(WINDOW * search,int yW, int xW,int heightW,int widthW){
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
}*/






void printQ1User(bool F, char * name, char sex, int age, char * country_code , 
            char * passport , int number_of_flights, int number_of_reservations,double total_spent){
    noecho();
    NEWPAGE;
    if(F == false)mvwprintw(terminal,dist,20,"%s;%c;%d;%s;%s;%d;%d,%.3f",name,sex,age,country_code,passport,number_of_flights,number_of_reservations,total_spent);
    else {
        mvwprintw(terminal,dist,20,"--- 1 ---");
        mvwprintw(terminal,dist + 1,20,"name: %s",name);
        mvwprintw(terminal,dist + 2,20,"sex: %c",sex);
        mvwprintw(terminal,dist + 3,20,"age: %d",age);
        mvwprintw(terminal,dist + 4,20,"country_code: %s",country_code);
        mvwprintw(terminal,dist + 5,20,"passport: %s",passport);
        mvwprintw(terminal,dist + 6,20,"number_of_flights: %d",number_of_flights);
        mvwprintw(terminal,dist + 7,20,"number_of_reservations: %d",number_of_reservations);
        mvwprintw(terminal,dist + 8,20,"total_spent: %.3f",total_spent);
    }
    wrefresh(terminal);
}

void printQ1Flight(bool F, char * airline, char * plane_model , char * origin, 
            char * destination,char * schedule_departure_date , char * schedule_arrival_date, int passengers, int delay){

    noecho();
    NEWPAGE;
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

void printQ1Reservation(bool F, char * hotel_id, char * hotel_name , int hotel_stars, char * begin_date , char * end_date , 
            bool includes_breakfast, int nights, double total_price){
    noecho();
    NEWPAGE;
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


void printQ2(bool f,int * command,int npp,Reservation ** reservations,int n1,int * rCount, Flight ** flights,int n2,int * fCount){
    NEWPAGE;
    if(*command < 0) *command = 0;
    if(*rCount < 0) *rCount = 0;
    if(*fCount < 0) *fCount = 0;
    int yChunk = 1;
    if(f == false){ // Normal Mode
        if(reservations && *rCount < n1 && flights && *fCount < n2){ // There is both reservations and flights to be written
            int max = n1 + n2;
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
                    *command += 1;
                    ffree(time);
                    ffree(fId);
                }
                else{ // Reservation is more recent that the flight
                    char * time = timeToString(rTime);
                    time[10] = '\0';
                    char * rId = getReservId(reservations[*rCount]);
                    mvwprintw(terminal,dist * yChunk,20,"%s;%s;reservation",rId,time);
                    yChunk++;
                    *rCount += 1;
                    *command += 1;
                    ffree(time);
                    ffree(rId);
                }
                destroyTime(rTime);
                destroyTime(fTime);
            }
            if(*rCount < n1 && *fCount >= n2){ // Flights array have reached his limit
                Time * rTime = getReservBeginDate(reservations[*rCount]);
                char * time = timeToString(rTime);
                time[10] = '\0';
                char * rId = getReservId(reservations[*rCount]);
                mvwprintw(terminal,dist * yChunk,20,"%s;%s;reservation",rId,time);
                yChunk++;
                *rCount += 1;
                *command += 1;
                ffree(time);
                ffree(rId);
                destroyTime(rTime);
            }
            if(*rCount >= n1 && *fCount < n2){ // Reservations array have reached his limit
                Time * fTime = getFlightSDepartureDate(flights[*fCount]);
                char * time = timeToString(fTime);
                time[10] = '\0';
                char * fId = getFlightId(flights[*fCount]);
                mvwprintw(terminal,dist * yChunk,20,"%s;%s;flight",fId,time);
                yChunk++;
                *fCount += 1;
                *command += 1;
                ffree(time);
                ffree(fId);
                destroyTime(fTime);
            }
            
            while(*command < max && ((*command) % (npp) != 0)){
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
                        *command += 1;
                        ffree(time);
                        ffree(fId);
                    }
                    else{ // Reservation is more recent that the flight
                        char * time = timeToString(rTime);
                        time[10] = '\0';
                        char * rId = getReservId(reservations[*rCount]);
                        mvwprintw(terminal,dist * yChunk,20,"%s;%s;reservation",rId,time);
                        yChunk++;
                        *rCount += 1;
                        *command += 1;
                        ffree(time);
                        ffree(rId);
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
                    *command += 1;
                    ffree(time);
                    ffree(rId);
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
                    *command += 1;
                    ffree(time);
                    ffree(fId);
                    destroyTime(fTime);
                    continue;
                }
                break;
            }
            wrefresh(terminal);
            return;
        }else{
            if(*rCount < n1 && *fCount >= n2){ // There only is reservations to be written
                Time * rTime = getReservBeginDate(reservations[*rCount]);
                char * time = timeToString(rTime);
                time[10] = '\0';
                char * rId = getReservId(reservations[*rCount]);
                mvwprintw(terminal,dist * yChunk,20,"%s;%s;reservation",rId,time);
                yChunk++;
                *rCount += 1;
                *command += 1;
                ffree(time);
                ffree(rId);
                destroyTime(rTime);
                while(*rCount < n1 && ((*command % (npp)) != 0)){
                    Time * rTime = getReservBeginDate(reservations[*rCount]);
                    char * time = timeToString(rTime);
                    time[10] = '\0';
                    char * rId = getReservId(reservations[*rCount]);
                    mvwprintw(terminal,dist * yChunk,20,"%s;%s;reservation",rId,time);
                    yChunk++;
                    *rCount += 1;
                    *command += 1;
                    ffree(time);
                    ffree(rId);
                    destroyTime(rTime);
                }
                wrefresh(terminal);
                return;
            }
            if(flights && *fCount < n2){ // There only is flights to be written
                Time * fTime = getFlightSDepartureDate(flights[*fCount]);
                char * time = timeToString(fTime);
                time[10] = '\0';
                char * fId = getFlightId(flights[*fCount]);
                mvwprintw(terminal,dist * yChunk,20,"%s;%s;flight",fId,time);
                yChunk++;
                *fCount += 1;
                *command += 1;
                ffree(time);
                ffree(fId);
                destroyTime(fTime);
                while(*fCount < n2 && (*command % (npp) != 0)){
                    Time * fTime = getFlightSDepartureDate(flights[*fCount]);
                    char * time = timeToString(fTime);
                    time[10] = '\0';
                    char * fId = getFlightId(flights[*fCount]);
                    mvwprintw(terminal,dist * yChunk,20,"%s;%s;flight",fId,time);
                    yChunk++;
                    *fCount += 1;
                    *command += 1;
                    ffree(time);
                    ffree(fId);
                    destroyTime(fTime);
                }
                wrefresh(terminal);
                return;
            }
            wrefresh(terminal);
            return;
        }
    }else{ // F Mode
        if(reservations && *rCount < n1 && flights && *fCount < n2){ // There is both reservations and flights to be written
            int max = n1 + n2;
            if(*rCount < n1 && *fCount < n2){ // Both the arrays have not reached their limit 
                Time * rTime = getReservBeginDate(reservations[*rCount]);
                Time * fTime = getFlightSDepartureDate(flights[*fCount]);
                if(compareTimes(rTime,fTime) == true){ // Flight is more recent that the reservation
                    char * time = timeToString(fTime);
                    time[10] = '\0';
                    char * fId = getFlightId(flights[*fCount]);
                    mvwprintw(terminal,(dist * yChunk),20,"--- %d ---",*command + 1);
                    mvwprintw(terminal,(dist * yChunk) + 1,20,"id: %s",fId);
                    mvwprintw(terminal,(dist * yChunk) + 2,20,"date: %s",time);
                    mvwprintw(terminal,(dist * yChunk) + 3,20,"type: flight");
                    yChunk++;
                    *fCount += 1;
                    *command += 1;
                    ffree(time);
                    ffree(fId);
                }
                else{ // Reservation is more recent that the flight
                    char * time = timeToString(rTime);
                    time[10] = '\0';
                    char * rId = getReservId(reservations[*rCount]);
                    mvwprintw(terminal,(dist * yChunk),20,"--- %d ---",*command + 1);
                    mvwprintw(terminal,(dist * yChunk) + 1,20,"id: %s",rId);
                    mvwprintw(terminal,(dist * yChunk) + 2,20,"date: %s",time);
                    mvwprintw(terminal,(dist * yChunk) + 3,20,"type: reservation");
                    yChunk++;
                    *rCount += 1;
                    *command += 1;
                    ffree(time);
                    ffree(rId);
                }
                destroyTime(rTime);
                destroyTime(fTime);
            }
            if(*rCount < n1 && *fCount >= n2){ // Flights array have reached his limit
                Time * rTime = getReservBeginDate(reservations[*rCount]);
                char * time = timeToString(rTime);
                time[10] = '\0';
                char * rId = getReservId(reservations[*rCount]);
                mvwprintw(terminal,(dist * yChunk),20,"--- %d ---",*command + 1);
                mvwprintw(terminal,(dist * yChunk) + 1,20,"id: %s",rId);
                mvwprintw(terminal,(dist * yChunk) + 2,20,"date: %s",time);
                mvwprintw(terminal,(dist * yChunk) + 3,20,"type: reservation");
                yChunk++;
                *rCount += 1;
                *command += 1;
                ffree(time);
                ffree(rId);
                destroyTime(rTime);
            }
            if(*rCount >= n1 && *fCount < n2){ // Reservations array have reached his limit
                Time * fTime = getFlightSDepartureDate(flights[*fCount]);
                char * time = timeToString(fTime);
                time[10] = '\0';
                char * fId = getFlightId(flights[*fCount]);
                mvwprintw(terminal,(dist * yChunk),20,"--- %d ---",*command + 1);
                mvwprintw(terminal,(dist * yChunk) + 1,20,"id: %s",fId);
                mvwprintw(terminal,(dist * yChunk) + 2,20,"date: %s",time);
                mvwprintw(terminal,(dist * yChunk) + 3,20,"type: flight");
                yChunk++;
                *fCount += 1;
                *command += 1;
                ffree(time);
                ffree(fId);
                destroyTime(fTime);
            }
            
            while(*command < max && ((*command) % (npp) != 0)){
                if(*rCount < n1 && *fCount < n2){ // Both the arrays have not reached their limit 
                    Time * rTime = getReservBeginDate(reservations[*rCount]);
                    Time * fTime = getFlightSDepartureDate(flights[*fCount]);
                    if(compareTimes(rTime,fTime) == true){ // Flight is more recent that the reservation
                        char * time = timeToString(fTime);
                        time[10] = '\0';
                        char * fId = getFlightId(flights[*fCount]);
                        mvwprintw(terminal,(dist * yChunk),20,"--- %d ---",*command + 1);
                        mvwprintw(terminal,(dist * yChunk) + 1,20,"id: %s",fId);
                        mvwprintw(terminal,(dist * yChunk) + 2,20,"date: %s",time);
                        mvwprintw(terminal,(dist * yChunk) + 3,20,"type: flight");
                        yChunk++;
                        *fCount += 1;
                        *command += 1;
                        ffree(time);
                        ffree(fId);
                    }
                    else{ // Reservation is more recent that the flight
                        char * time = timeToString(rTime);
                        time[10] = '\0';
                        char * rId = getReservId(reservations[*rCount]);
                        mvwprintw(terminal,(dist * yChunk),20,"--- %d ---",*command + 1);
                        mvwprintw(terminal,(dist * yChunk) + 1,20,"id: %s",rId);
                        mvwprintw(terminal,(dist * yChunk) + 2,20,"date: %s",time);
                        mvwprintw(terminal,(dist * yChunk) + 3,20,"type: reservation");
                        yChunk++;
                        *rCount += 1;
                        *command += 1;
                        ffree(time);
                        ffree(rId);
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
                    mvwprintw(terminal,(dist * yChunk),20,"--- %d ---",*command + 1);
                    mvwprintw(terminal,(dist * yChunk) + 1,20,"id: %s",rId);
                    mvwprintw(terminal,(dist * yChunk) + 2,20,"date: %s",time);
                    mvwprintw(terminal,(dist * yChunk) + 3,20,"type: reservation");
                    yChunk++;
                    *rCount += 1;
                    *command += 1;
                    ffree(time);
                    ffree(rId);
                    destroyTime(rTime);
                    continue;
                }
                if(*rCount >= n1 && *fCount < n2){ // Reservations array have reached his limit
                    Time * fTime = getFlightSDepartureDate(flights[*fCount]);
                    char * time = timeToString(fTime);
                    time[10] = '\0';
                    char * fId = getFlightId(flights[*fCount]);
                    mvwprintw(terminal,(dist * yChunk),20,"--- %d ---",*command + 1);
                    mvwprintw(terminal,(dist * yChunk) + 1,20,"id: %s",fId);
                    mvwprintw(terminal,(dist * yChunk) + 2,20,"date: %s",time);
                    mvwprintw(terminal,(dist * yChunk) + 3,20,"type: flight");
                    yChunk++;
                    *fCount += 1;
                    *command += 1;
                    ffree(time);
                    ffree(fId);
                    destroyTime(fTime);
                    continue;
                }
                break;
            }
            wrefresh(terminal);
            return;
        }else{
            if(*rCount < n1 && *fCount >= n2){ // There only is reservations to be written
                Time * rTime = getReservBeginDate(reservations[*rCount]);
                char * time = timeToString(rTime);
                time[10] = '\0';
                char * rId = getReservId(reservations[*rCount]);
                mvwprintw(terminal,(dist * yChunk),20,"--- %d ---",*command + 1);
                mvwprintw(terminal,(dist * yChunk) + 1,20,"id: %s",rId);
                mvwprintw(terminal,(dist * yChunk) + 2,20,"date: %s",time);
                mvwprintw(terminal,(dist * yChunk) + 3,20,"type: reservation");
                yChunk++;
                *rCount += 1;
                *command += 1;
                ffree(time);
                ffree(rId);
                destroyTime(rTime);
                while(*rCount < n1 && ((*command % (npp)) != 0)){
                    Time * rTime = getReservBeginDate(reservations[*rCount]);
                    char * time = timeToString(rTime);
                    time[10] = '\0';
                    char * rId = getReservId(reservations[*rCount]);
                    mvwprintw(terminal,(dist * yChunk),20,"--- %d ---",*command + 1);
                    mvwprintw(terminal,(dist * yChunk) + 1,20,"id: %s",rId);
                    mvwprintw(terminal,(dist * yChunk) + 2,20,"date: %s",time);
                    mvwprintw(terminal,(dist * yChunk) + 3,20,"type: reservation");
                    yChunk++;
                    *rCount += 1;
                    *command += 1;
                    ffree(time);
                    ffree(rId);
                    destroyTime(rTime);
                }
                wrefresh(terminal);
                return;
            }
            if(flights && *fCount < n2){ // There only is flights to be written
                Time * fTime = getFlightSDepartureDate(flights[*fCount]);
                char * time = timeToString(fTime);
                time[10] = '\0';
                char * fId = getFlightId(flights[*fCount]);
                mvwprintw(terminal,(dist * yChunk),20,"--- %d ---",*command + 1);
                mvwprintw(terminal,(dist * yChunk) + 1,20,"id: %s",fId);
                mvwprintw(terminal,(dist * yChunk) + 2,20,"date: %s",time);
                mvwprintw(terminal,(dist * yChunk) + 3,20,"type: flight");
                yChunk++;
                *fCount += 1;
                *command += 1;
                ffree(time);
                ffree(fId);
                destroyTime(fTime);
                while(*fCount < n2 && (*command % (npp) != 0)){
                    Time * fTime = getFlightSDepartureDate(flights[*fCount]);
                    char * time = timeToString(fTime);
                    time[10] = '\0';
                    char * fId = getFlightId(flights[*fCount]);
                    mvwprintw(terminal,(dist * yChunk),20,"--- %d ---",*command + 1);
                    mvwprintw(terminal,(dist * yChunk) + 1,20,"id: %s",fId);
                    mvwprintw(terminal,(dist * yChunk) + 2,20,"date: %s",time);
                    mvwprintw(terminal,(dist * yChunk) + 3,20,"type: flight");
                    yChunk++;
                    *fCount += 1;
                    *command += 1;
                    ffree(time);
                    ffree(fId);
                    destroyTime(fTime);
                }
                wrefresh(terminal);
                return;
            }
            wrefresh(terminal);
            return;
        }
        
    }
}




void printQ3(bool f,double rating){
    NEWPAGE;
    if(f == false){
        mvwprintw(terminal,dist,20,"%.3f",rating);
        wrefresh(terminal);
        return;
    }
    mvwprintw(terminal,dist,20,"--- 1 ---");
    mvwprintw(terminal,dist + 1,20,"rating: %.3f",rating);
    wrefresh(terminal);
}


void printQ4(bool f,int npp,int * index,Reservation ** reservation,int max){
    NEWPAGE;
    if(*index < 0) *index = 0;
    int yChunk = 1;
    if(f == false){
        if(*index < max && reservation[*index]){
            char * id = getReservId(reservation[*index]);
            Time * bTime = getReservBeginDate(reservation[*index]);
            Time * eTime = getReservEndDate(reservation[*index]);
            char * stringBTime = timeToString(bTime);
            char * stringETime = timeToString(eTime);
            char * uId = getReservUserId(reservation[*index]);
            int rating = getReservRating(reservation[*index]);
            int n = numberOfDays(bTime,eTime);

            mvwprintw(terminal,dist * yChunk,20,"%s;%s;%s;%s;%d;%.3f",id,stringBTime,stringETime,uId,rating,getTotalSpentOnReserv(reservation[*index],n));

            ffree(id);
            ffree(stringBTime);
            ffree(stringETime);
            ffree(uId);
            destroyTime(bTime);
            destroyTime(eTime);
        }
        *index += 1;
        yChunk++;
        while(*index < max && (*index % npp) != 0){
            if(reservation[*index]){
                char * id = getReservId(reservation[*index]);
                Time * bTime = getReservBeginDate(reservation[*index]);
                Time * eTime = getReservEndDate(reservation[*index]);
                char * stringBTime = timeToString(bTime);
                char * stringETime = timeToString(eTime);
                char * uId = getReservUserId(reservation[*index]);
                int rating = getReservRating(reservation[*index]);
                int n = numberOfDays(bTime,eTime);

                mvwprintw(terminal,dist * yChunk,20,"%s;%s;%s;%s;%d;%.3f",id,stringBTime,stringETime,uId,rating,getTotalSpentOnReserv(reservation[*index],n));

                ffree(id);
                ffree(stringBTime);
                ffree(stringETime);
                ffree(uId);
                destroyTime(bTime);
                destroyTime(eTime);
            }
            *index += 1;
            yChunk++;
        }
        wrefresh(terminal);
        return;
    }

    if(*index < max && reservation[*index]){
        char * id = getReservId(reservation[*index]);
        Time * bTime = getReservBeginDate(reservation[*index]);
        Time * eTime = getReservEndDate(reservation[*index]);
        char * stringBTime = timeToString(bTime);
        char * stringETime = timeToString(eTime);
        char * uId = getReservUserId(reservation[*index]);
        int rating = getReservRating(reservation[*index]);
        int n = numberOfDays(bTime,eTime);
        
        mvwprintw(terminal,(dist * yChunk) - 4,20,"--- %d ---",*index + 1);
        mvwprintw(terminal,(dist * yChunk) - 3,20,"id: %s",id);
        mvwprintw(terminal,(dist * yChunk) - 2,20,"begin_date: %s",stringBTime);
        mvwprintw(terminal,(dist * yChunk) - 1,20,"end_date: %s",stringETime);
        mvwprintw(terminal,(dist * yChunk) + 0,20,"user_id: %s",uId);
        mvwprintw(terminal,(dist * yChunk) + 1,20,"rating: %d",rating);
        mvwprintw(terminal,(dist * yChunk) + 2,20,"total_price: %0.3f",getTotalSpentOnReserv(reservation[*index],n));

        ffree(id);
        ffree(stringBTime);
        ffree(stringETime);
        ffree(uId);
        destroyTime(bTime);
        destroyTime(eTime);
    }
    *index += 1;
    yChunk++;
    int i = 1;
    while(*index < max && (*index % npp) != 0){
        if(reservation[*index]){
            char * id = getReservId(reservation[*index]);
            Time * bTime = getReservBeginDate(reservation[*index]);
            Time * eTime = getReservEndDate(reservation[*index]);
            char * stringBTime = timeToString(bTime);
            char * stringETime = timeToString(eTime);
            char * uId = getReservUserId(reservation[*index]);
            int rating = getReservRating(reservation[*index]);
            int n = numberOfDays(bTime,eTime);
            
            mvwprintw(terminal,(dist * yChunk) - 4 + i,20,"--- %d ---",*index + 1);
            mvwprintw(terminal,(dist * yChunk) - 3 + i,20,"id: %s",id);
            mvwprintw(terminal,(dist * yChunk) - 2 + i,20,"begin_date: %s",stringBTime);
            mvwprintw(terminal,(dist * yChunk) - 1 + i,20,"end_date: %s",stringETime);
            mvwprintw(terminal,(dist * yChunk) + 0 + i,20,"user_id: %s",uId);
            mvwprintw(terminal,(dist * yChunk) + 1 + i,20,"rating: %d",rating);
            mvwprintw(terminal,(dist * yChunk) + 2 + i,20,"total_price: %0.3f",getTotalSpentOnReserv(reservation[*index],n));
            
            i++;

            ffree(id);
            ffree(stringBTime);
            ffree(stringETime);
            ffree(uId);
            destroyTime(bTime);
            destroyTime(eTime);
        }
        *index += 1;
        yChunk++;
    }
    wrefresh(terminal);
}

void printQ5(bool f,int npp,int* index,Flight** flight,int max){
    NEWPAGE;
    if(*index < 0) *index = 0;
    int yChunk = 1;
    if(f == false){
        if(*index < max && flight[*index]){
            char * fId = getFlightId(flight[*index]);
            Time * sDD = getFlightSDepartureDate(flight[*index]);
            char * sDepDate = timeToString(sDD);
            char * destination = getFlightDestination(flight[*index]);
            char * airline = getFlightAirline(flight[*index]);
            char * planeModel = getFlightPlaneModel(flight[*index]);
            mvwprintw(terminal,dist * yChunk,13,"%s;%s;%s;%s;%s",
            fId,
            sDepDate,
            destination,
            airline,
            planeModel);
            destroyTime(sDD);
            ffree(fId);
            ffree(sDepDate);
            ffree(destination);
            ffree(airline);
            ffree(planeModel);
        }
        *index += 1;
        yChunk++;
        while(*index < max && (*index % npp) != 0){
            if(flight[*index]){
                char * fId = getFlightId(flight[*index]);
                Time * sDD = getFlightSDepartureDate(flight[*index]);
                char * sDepDate = timeToString(sDD);
                char * destination = getFlightDestination(flight[*index]);
                char * airline = getFlightAirline(flight[*index]);
                char * planeModel = getFlightPlaneModel(flight[*index]);
                mvwprintw(terminal,dist * yChunk,13,"%s;%s;%s;%s;%s",
                fId,
                sDepDate,
                destination,
                airline,
                planeModel);
                destroyTime(sDD);
                ffree(fId);
                ffree(sDepDate);
                ffree(destination);
                ffree(airline);
                ffree(planeModel);
                *index += 1;
                yChunk++;
            }
        }
        wrefresh(terminal);
        return;
    }
    if(*index < max && flight[*index]){
        char * fId = getFlightId(flight[*index]);
        Time * sDD = getFlightSDepartureDate(flight[*index]);
        char * sDepDate = timeToString(sDD);
        char * destination = getFlightDestination(flight[*index]);
        char * airline = getFlightAirline(flight[*index]);
        char * planeModel = getFlightPlaneModel(flight[*index]);
        mvwprintw(terminal,(dist * yChunk) - 3,20,"--- %d ---",*index + 1);
        mvwprintw(terminal,(dist * yChunk) - 2,20,"id: %s",fId);
        mvwprintw(terminal,(dist * yChunk) - 1,20,"schedule_departure_date: %s",sDepDate);
        mvwprintw(terminal,(dist * yChunk) + 0,20,"destination: %s",destination);
        mvwprintw(terminal,(dist * yChunk) + 1,20,"airline: %s",airline);
        mvwprintw(terminal,(dist * yChunk) + 2,20,"plane_model: %s",planeModel);
        destroyTime(sDD);
        ffree(fId);
        ffree(sDepDate);
        ffree(destination);
        ffree(airline);
        ffree(planeModel);
    }
    *index += 1;
    yChunk++;
    while(*index < max && (*index % npp) != 0){
        if(*index < max && flight[*index]){
        char * fId = getFlightId(flight[*index]);
        Time * sDD = getFlightSDepartureDate(flight[*index]);
        char * sDepDate = timeToString(sDD);
        char * destination = getFlightDestination(flight[*index]);
        char * airline = getFlightAirline(flight[*index]);
        char * planeModel = getFlightPlaneModel(flight[*index]);
        mvwprintw(terminal,(dist * yChunk) - 3,20,"--- %d ---",*index + 1);
        mvwprintw(terminal,(dist * yChunk) - 2,20,"id: %s",fId);
        mvwprintw(terminal,(dist * yChunk) - 1,20,"schedule_departure_date: %s",sDepDate);
        mvwprintw(terminal,(dist * yChunk) + 0,20,"destination: %s",destination);
        mvwprintw(terminal,(dist * yChunk) + 1,20,"airline: %s",airline);
        mvwprintw(terminal,(dist * yChunk) + 2,20,"plane_model: %s",planeModel);
        destroyTime(sDD);
        ffree(fId);
        ffree(sDepDate);
        ffree(destination);
        ffree(airline);
        ffree(planeModel);
        }
        *index += 1;
        yChunk++;
    }
    wrefresh(terminal);
}

void printQ6(bool f,int npp,int * index,int max,char ** names,int * passengers){
    NEWPAGE;
    if(*index < 0) *index = 0;
    int yChunk = 1;
    if(f == false){
        if(*index < max && names[*index]){
            mvwprintw(terminal,dist * yChunk,39,"%s;%d",names[*index],passengers[*index]);
        }
        yChunk++;
        *index += 1;
        while(*index < max && (*index % npp) != 0){
            if(*index < max && names[*index]){
                mvwprintw(terminal,dist * yChunk,39,"%s;%d",names[*index],passengers[*index]);
            }
            yChunk++;
            *index += 1;
            continue;
        }
        wrefresh(terminal);
        return;
    }
    if(*index < max && names[*index]){
        mvwprintw(terminal,(dist * yChunk),35,"--- %d ---",*index + 1);
        mvwprintw(terminal,(dist * yChunk) + 1,35,"name: %s",names[*index]);
        mvwprintw(terminal,(dist * yChunk) + 2,35,"passengers: %d",passengers[*index]);
    }
    yChunk++;
    *index += 1;
    while(*index < max && (*index % npp) != 0){
        if(*index < max && names[*index]){
            mvwprintw(terminal,(dist * yChunk),35,"--- %d ---",*index + 1);
            mvwprintw(terminal,(dist * yChunk) + 1,35,"name: %s",names[*index]);
            mvwprintw(terminal,(dist * yChunk) + 2,35,"passengers: %d",passengers[*index]);
        }
        yChunk++;
        *index += 1;
    }
    wrefresh(terminal);
}

void printQ7(bool f,int npp,int * index,SingularRecord * table,int max){
    NEWPAGE;
    if(*index < 0) *index = 0;
    int yChunk = 1;
    if(f == false){
        if(*index < max){
            char * airport = getSRecordName(table,*index);
            int delay = getSRecordListElement(table,*index);
            mvwprintw(terminal,dist * yChunk,20,"%s;%d",airport,delay);
            ffree(airport);
        }
        yChunk++;
        *index += 1;
        while(*index < max && (*index % npp) != 0){
            char * airport = getSRecordName(table,*index);
            int delay = getSRecordListElement(table,*index);
            mvwprintw(terminal,dist * yChunk,20,"%s;%d",airport,delay);
            ffree(airport);
            yChunk++;
            *index += 1;
        }
        wrefresh(terminal);
        return;
    }
    if(*index < max){
        char * airport = getSRecordName(table,*index);
        int delay = getSRecordListElement(table,*index);
        mvwprintw(terminal,(dist * yChunk),20,"--- %d ---",*index + 1);
        mvwprintw(terminal,(dist * yChunk) + 1,20,"name: %s",airport);
        mvwprintw(terminal,(dist * yChunk) + 2,20,"median: %d",delay);
        ffree(airport);
    }
    yChunk++;
    *index += 1;
    while(*index < max && (*index % npp) != 0){
        char * airport = getSRecordName(table,*index);
        int delay = getSRecordListElement(table,*index);
        mvwprintw(terminal,(dist * yChunk),20,"--- %d ---",*index + 1);
        mvwprintw(terminal,(dist * yChunk) + 1,20,"name: %s",airport);
        mvwprintw(terminal,(dist * yChunk) + 2,20,"median: %d",delay);
        ffree(airport);
        yChunk++;
        *index += 1;
    }
    wrefresh(terminal);
}

void printQ8(bool f,int revenue){
    NEWPAGE;
    if(f == false){
        mvwprintw(terminal,dist,20,"%d",revenue);
        wrefresh(terminal);
        return;
    }
    mvwprintw(terminal,dist,20,"--- 1 ---");
    mvwprintw(terminal,dist + 1,20,"revenue: %d",revenue);
    wrefresh(terminal);
}

void printQ9(bool f,int npp,int * index,char ** ids,char ** names,int max){
    NEWPAGE;
    int yChunk = 1;
    if(f == false){
        while(yChunk - 1 < npp && *index < max){
            mvwprintw(terminal,dist * yChunk,20,"%s;%s",ids[*index],names[*index]);
            yChunk++;
            *index += 1;
        }
        wrefresh(terminal);
        return;
    }
    while(yChunk - 1 < npp && *index < max){
        mvwprintw(terminal,(dist * yChunk),20,"--- %d ---",*index + 1);
        mvwprintw(terminal,(dist * yChunk) + 1,20,"id: %s",ids[*index]);
        mvwprintw(terminal,(dist * yChunk) + 2,20,"name: %s",names[*index]);
        yChunk++;
        *index += 1;
    }
    wrefresh(terminal);
}

int getInput(){
    int ch = getch();
    if(ch == 'q') return 0;
    if(ch == 'w' || ch == KEY_UP) return 1;
    if(ch == 's' || ch == KEY_DOWN) return -1;
    return 10;
}

void menus(){
    initscr();
    raw();
    cursorOn();
    keypad(stdscr,true);

    int scrWidth = 0,scrHeight = 0;
    getmaxyx(stdscr,scrHeight,scrWidth);
    int width = scrWidth;
    int height = scrHeight;
    
    
    const int windowWidth = 0.7 * scrWidth;
    const int windowHeight = 0.9 * scrHeight;


    const int xW = 0.16 * scrWidth;
    const int yW = 0.06 * scrHeight;

    dist = (height - 5) / (5 + 1);

    terminal = drawMainMenu(width,height);
    keypad(terminal,true);
    requestSomething(terminal,windowWidth,windowHeight,"Por favor, insira o path para os csvs.");


    WINDOW * search = drawSearchBox(width,height);

    char * buffer = getPath(search,yW,xW,windowHeight,windowWidth);

    Users * uDatabase = validateUsers(buffer);

    Reservations * rDatabase = validateReservations(uDatabase,buffer);

    Flights * fDatabase = validateFlights(buffer);


    Passengers * pDatabase = validatePassengers(uDatabase,fDatabase,buffer);

    free(buffer);
    buffer = NULL;

    wclear(search);
    box(search,0,0);
    wrefresh(search);

    requestSomething(terminal,windowWidth,windowHeight,"Por favor, insira a query e parametros (h para ajuda).");

    wclear(search);
    box(search,0,0);
    wrefresh(search);

    char * query = getQuery(search,yW,xW,windowHeight,windowWidth);
    
    readQuery(uDatabase,rDatabase,fDatabase,pDatabase,query);

    wclear(terminal);
    delwin(terminal);
    endwin();
}

void dontWriteOnScreen(){
    noecho();
}

void writeOnScreen(){
    echo();
}

void cursorOn(){
    curs_set(1);
}

void cursorOff(){
    curs_set(0);
}