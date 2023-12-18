#ifndef PASSENGER_H
#define PASSENGER_H

typedef struct passanger Passanger;



Passanger * createPassanger();

void initPassanger(Passanger *);

void destroyPassanger(Passanger *);




void setPassangerFlightId(Passanger *, const char *);
char *getPassangerFlightId(Passanger *);

void setPassangerUserId(Passanger *, const char *);
char *getPassangerUserId(Passanger *);

void copyPassanger(Passanger *,Passanger *);

#endif