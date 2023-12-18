#include "../include/dataStructs.h"
#include "../include/passenger.h"
#include <stdlib.h>
#include <stdio.h>
#include <glib.h>

#define BUFFERSIZE 1000



typedef struct passengersDB {
    Passenger ** passengers;
    unsigned int max;
    unsigned int numPassengers;
} PassengersDatabase;


PassengersDatabase * createPassengerDatabase(){
    PassengersDatabase * db = malloc(sizeof(struct passengersDB));
    if (!db) {
        fprintf(stderr, "Error: Memory allocation failed for PassengersDatabase.\n");
        exit(EXIT_FAILURE);
    }
    db->max = BUFFERSIZE;
    db->numPassengers = 0;
    db->passengers = malloc(sizeof(Passenger *) * db->max);
    for(int i = 0;i < db->max;i++) db->passengers[i] = NULL;
    return db;
}

void insertPassenger(void * dataStruct, void * passengerData){
    //Casting the arguments
    PassengersDatabase * table = (PassengersDatabase *) dataStruct;
    Passenger * passenger = (Passenger *) passengerData;
/*
    if(table->numPassengers == 0){ // First insertion of the table
        table->passengers = malloc(sizeof(Passenger *) * (table->max));
        if(!table->passengers){
            if(table) free(table);
            table = NULL;
            return;
        }
        table->passengers[table->numPassengers] = passenger;
        table->numPassengers++;
        return;

    } else {*/
        if(table->numPassengers >= table->max){
            Passenger ** temp = realloc(table->passengers, (table->max * 2) * sizeof(Passenger *));
                if (!temp) {
                    fprintf(stderr, "Error: Memory reallocation failed in insertPassenger.\n");
                    for(int i = 0;i < table->max;i++){
                        table->passengers[i] = NULL;
                    }
                    free(table->passengers);
                    table->passengers = NULL;
                    free(table);
                    table = NULL;
                    return;
                }
                table->passengers = temp;
                table->max *= 2;
            }
        table->passengers[table->numPassengers] = passenger;
        table->numPassengers++;
        //}
}


Passenger * lookupPassengerUID(const PassengersDatabase * database,const char * id){
    for(int i = 0;i < database->numPassengers;i++){
        char * uId = getPassengerUserId(database->passengers[i]);
        if (database->passengers[i] && strcoll(uId, id) == 0){
            free(uId);
            uId = NULL;
            return database->passengers[i];
        }
        free(uId);
        uId = NULL;
    }
    return NULL;
}

Passenger * lookupPassengerFID(const PassengersDatabase * database,const char * id){
    if(database == NULL || id == NULL) return NULL;
    for(int i = 0;i < database->numPassengers;i++){
        char * fId = getPassengerFlightId(database->passengers[i]);
        if (database->passengers[i] && strcoll(fId, id) == 0) {
            free(fId);
            return database->passengers[i];
        }
        free(fId);
    }
    return NULL;
}

int getNumAllPassengers(const PassengersDatabase * database){
    return database->numPassengers;
}

Passenger ** getAllPassengers(const PassengersDatabase * database){
    return database->passengers;
}

void destroyPassengersDB(PassengersDatabase * database){
    for(int i = 0;i < database->numPassengers;i++){
        destroyPassenger(database->passengers[i]);
    }
    free(database->passengers);
    database->passengers = NULL;
    free(database);
    database = NULL;
}   