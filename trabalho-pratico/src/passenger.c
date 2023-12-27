#include "../include/passenger.h"
#include <stdlib.h>
#include <string.h>


typedef struct passenger{
    char * flight_id;
    char * user_id;
} Passenger;



// *** Passenger related functions *** 

 Passenger * createPassenger(){
    Passenger * p = malloc(sizeof(struct passenger));
    initPassenger(p);
    return p;
}

  void initPassenger(Passenger * passenger){
    passenger->flight_id = NULL;
    passenger->user_id = NULL;
}

  void destroyPassenger(Passenger * p) {
    if (p != NULL) {
        if(p->flight_id != NULL){
            free(p->flight_id); 
            p->flight_id = NULL;
        }
        if(p->user_id != NULL){
            free(p->user_id); 
            p->user_id = NULL;
        }
        free(p); 
        p = NULL;
    }
}

size_t getPassengerSize(){
    return sizeof(struct passenger);
}


 void setPassengerFlightId(Passenger * passenger,const char * line){
    if(passenger == NULL || line == NULL) return;
    if(passenger->flight_id){
        if(strlen(line) > strlen(passenger->flight_id)){
            char * temp = realloc(passenger->flight_id,strlen(line)+ 1);
            strncpy(temp,line,strlen(line));
            temp[strlen(line)] = '\0';
            passenger->flight_id = temp;
            return;
        }else{
            strncpy(passenger->flight_id,line,strlen(passenger->flight_id));
            passenger->flight_id[strlen(passenger->flight_id)] = '\0';
            return;
        }
    }
    passenger->flight_id = strdup(line);
}

 char *getPassengerFlightId(Passenger * passenger){
    if(passenger == NULL) return NULL;
    if(passenger->flight_id == NULL) return NULL;
    if(passenger->flight_id != NULL){
        char * flight_id = strdup(passenger->flight_id);
        return flight_id;
    }
    return NULL;
}


  void setPassengerUserId(Passenger * passenger,const char * line){
    if(passenger == NULL || line == NULL) return;
    if(passenger->user_id){
        if(strlen(line) > strlen(passenger->user_id)){
            char * temp = realloc(passenger->user_id,strlen(line)+ 1);
            strncpy(temp,line,strlen(line));
            temp[strlen(line)] = '\0';
            passenger->user_id = temp;
            return;
        }else{
            strncpy(passenger->user_id,line,strlen(passenger->user_id));
            passenger->user_id[strlen(passenger->user_id)] = '\0';
            return;
        }
    }
    passenger->user_id = strdup(line);
}

 char *getPassengerUserId(Passenger * passenger){
    if(passenger == NULL) return NULL;
    if(passenger->user_id){
        char * user_id = strdup(passenger->user_id);
        return user_id;
    }
    return NULL;
}


void copyPassenger(Passenger * dest,Passenger * src){
    if(dest == NULL || src == NULL) return;
    char * passengerFlightId = getPassengerFlightId(src);
    char * passengerUserId = getPassengerUserId(src);

    setPassengerFlightId(dest,passengerFlightId);
    setPassengerUserId(dest,passengerUserId);

    free(passengerFlightId);
    passengerFlightId = NULL;
    free(passengerUserId);
    passengerUserId = NULL;
}

