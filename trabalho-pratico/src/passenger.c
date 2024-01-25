#include "../include/passenger.h"
#include "../include/utils.h"
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
        ffree((void **) &p->flight_id); 
        ffree((void **) &p->user_id); 
        ffree((void **) &p); 
    }
}

size_t getPassengerSize(){
    return sizeof(struct passenger);
}


void setPassengerFlightId(Passenger * passenger,const char * line){
    if(passenger == NULL || line == NULL) return;
    
    ffree((void **) &passenger->flight_id);

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
    
    ffree((void **) &passenger->user_id);
    
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
    setPassengerFlightId(dest,passengerFlightId);
    ffree((void **) &passengerFlightId);
    
    
    char * passengerUserId = getPassengerUserId(src);
    setPassengerUserId(dest,passengerUserId);
    ffree((void **) &passengerUserId);

}

