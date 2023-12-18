#ifndef PASSENGER_H
#define PASSENGER_H

typedef struct passenger Passenger;



Passenger * createPassenger();

void initPassenger(Passenger *);

void destroyPassenger(Passenger *);




void setPassengerFlightId(Passenger *, const char *);
char *getPassengerFlightId(Passenger *);

void setPassengerUserId(Passenger *, const char *);
char *getPassengerUserId(Passenger *);

void copyPassenger(Passenger *,Passenger *);

#endif