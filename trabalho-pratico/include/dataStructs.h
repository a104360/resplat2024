#ifndef DATASTRUCTS_H
#define DATASTRUCTS_H
#include <stdbool.h>
#include "../include/passenger.h"



typedef struct passengersDB PassengersDatabase;

PassengersDatabase * createPassengerDatabase();

void insertPassenger(void * , void * );

int getNumAllPassengers(const PassengersDatabase * );

Passenger * lookupPassengerUID(const PassengersDatabase *,const char *);

Passenger * lookupPassengerFID(const PassengersDatabase *,const char *);

Passenger ** getAllPassengers(const PassengersDatabase * );

void destroyPassengersDB(PassengersDatabase *);

#endif