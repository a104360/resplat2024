#ifndef DATASTRUCTS_H
#define DATASTRUCTS_H
#include <stdbool.h>
#include "../include/dataTypes.h"



typedef struct passangersDB PassangersDatabase;

PassangersDatabase * createPassangerDatabase();

void insertPassanger(void * , void * );

int getNumAllPassangers(const PassangersDatabase * );

Passanger * lookupPassangerUID(const PassangersDatabase *,const char *);

Passanger * lookupPassangerFID(const PassangersDatabase *,const char *);

Passanger ** getAllPassangers(const PassangersDatabase * );

void destroyPassangersDB(PassangersDatabase *);

#endif