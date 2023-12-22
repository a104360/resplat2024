#ifndef INTERPRETER_H
#define INTERPRETER_H
#include "../include/utils.h"
#include "../include/user.h" 
#include "../include/reservation.h"
#include "../include/flight.h"
#include "../include/passengers.h"

int verTamanhoLinha(const char *);

char * limpaToken(char *);

Time * firstDateQ5(const char *);

Time * secondDateQ5(const char *);

Time * firstDateQ8(const char *);

Time * secondDateQ8(const char *);

char * airportName(const char *);

void readEntryFile(const Users *,const Reservations *,const Flights *,const Passengers *,int, char **);

#endif