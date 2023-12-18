#ifndef INTERPRETER_H
#define INTERPRETER_H
#include "../include/catalogs.h" 
#include "../include/dataStructs.h"


int verTamanhoLinha(const char *);

char * limpaToken(char *);

Time * firstDateQ5(const char *);

Time * secondDateQ5(const char *);

Time * firstDateQ8(const char *);

Time * secondDateQ8(const char *);

char * airportName(const char *);

void readEntryFile(const UsersDatabase,const ReservationsDatabase,const FlightsDatabase,const PassengersDatabase *,int, char **);

#endif