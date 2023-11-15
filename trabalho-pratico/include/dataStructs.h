#ifndef DATASTRUCTS_H
#define DATASTRUCTS_H
#include <stdbool.h>


typedef struct passangersDB PassangersDatabase;

PassangersDatabase * createPassangerDatabase();

void insertPassanger(void * , void * );

int getNumAllPassangers(const PassangersDatabase * );

Passanger ** getAllPassangers(const PassangersDatabase * );

void destroyPassangersDB(PassangersDatabase *);

#endif