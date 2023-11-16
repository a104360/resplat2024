#ifndef INTERPRETER_H
#define INTERPRETER_H
#include "../include/catalogs.h" 
#include "../include/dataStructs.h"


int verTamanhoLinha(char * );

void readEntryFile(UsersDatabase * uDatabase,ReservationsDatabase * rDatabase,FlightsDatabase * fDatabase,PassangersDatabase * pDatabase,int agrc, char **argv);

#endif