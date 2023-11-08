#ifndef DATATYPES_H
#define DATATYPES_H

enum structs;

typedef struct time Time;

typedef struct user User;

typedef struct flight Flight;

typedef struct reservation Reservation;

typedef struct passanger Passanger;




void initUser(User *);

void initFlight(Flight *);

void initReservation(Reservation *);

void initPassanger(Passanger *);

User * createUser();

Flight * createFlight();

Reservation * createReservation();

Passanger * createPassanger();



void setUserId(User *,char *);

void setUserName(User *,char *);

void setUserEmail(User *,char *);

void setUserBday(User *,Time *);

void setUserSex(User *,char *);

void setUser(User *,char *);

#endif