#ifndef OUTPUT_H
#define OUTPUT_H
#include "../include/dataTypes.h"

void outputQ1User(int , char * , char , int , char * , char * , char * , char * , char * );

void outputQ1Flight(int , char * , char * , char * , char * , char * , char * , int , int);

void outputQ1Reservation(int , char * , char * , int , char * , char * , bool, int , int);

void outputQ2(Reservation ** , Flight ** );

#endif